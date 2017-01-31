#include "systemc.h"
#include "RECIPROCAL.sh"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PLUS	0
#define MINUS	1

RECIPROCAL *rec_i;

sc_clock clk("clk");
sc_signal<bool> reset("reset");
sc_signal<sc_uint<2> > count;
sc_signal<sc_uint<19> > x;
sc_signal<sc_uint<19> > y;
sc_signal<sc_uint<1> > calc;

double int2dec(int x){
	double s = 0;

	for(int i=-14 ; i<=3 ; i++){
		if(x % 2) s += pow(2.0, (double)i);
		x = x / 2;
	}

	return s;
}

int dec2int(double x){
	int s = 0;
	int n = (int)x;
	double r = x - (double)n;

	s = n << 14;
	for(int i=13 ; i>=0 ; i--){
		r = r * 2.0;
		if(r >= 1.0){
			s += (int)pow(2.0, (double)i);
			r -= 1.0;
		}
	}

	return s;
}

int sc_main(int argc, char **argv){
	double x_dec, answer;
	FILE *fp;

	rec_i = new RECIPROCAL("rec_i");
	rec_i->m_clock(clk);
	rec_i->p_reset(reset);
	rec_i->count(count);
	rec_i->x(x);
	rec_i->y(y);
	rec_i->calc(calc);

	sc_start(0, SC_NS);
	reset = 0;
	sc_start(1, SC_NS);
	reset = 1;

	fp = popen("gnuplot -persist", "w");
	fprintf(fp, "set terminal png\n");
	fprintf(fp, "set output 'reciprocal_sim_01.png'\n");
	fprintf(fp, "set multiplot\n");
	fprintf(fp, "set xrange [0:10.0]\n");
	fprintf(fp, "set yrange [0:1.0]\n");
	fprintf(fp, "set xlabel 'x'\n");
	fprintf(fp, "set ylabel 'y'\n");
	fprintf(fp, "unset key\n");

	srand(time(NULL));
	fprintf(fp, "plot '-' with points\n");
	for(int i=0 ; i<100 ; i++){
		x_dec = (double)rand()/RAND_MAX*9.0+1.0;
		x = dec2int(x_dec);
		count = 2;
		calc = 1;
		sc_start(1, SC_NS);	// func呼び出し
		calc = 0;
		sc_start(1, SC_NS); // init
		sc_start(1, SC_NS); // exec
		sc_start(1, SC_NS); // exec
		fprintf(fp, "%lf %lf\n", x_dec, int2dec(y.read()));
	}
	fprintf(fp, "e\n");

/*
	fprintf(fp, "plot '-' with points\n");
	for(int i=0 ; i<100 ; i++){
		x_dec = (double)rand()/RAND_MAX*4.0-2.0;
		x = (x_dec>=0 ? 0 : 262144) + dec2int(fabs(x_dec));
		calc = 1;
		sc_start(1, SC_NS);
		fprintf(fp, "%lf %lf\n", x_dec, int2dec(y.read()));
	}
	fprintf(fp, "e\n");
*/

	fprintf(fp, "plot '-' with lines\n");
	for(double i=1.0 ; i<10.0 ; i+=0.1){
		fprintf(fp, "%lf %lf\n", i, 1.0/i);
	}
	fprintf(fp, "e\n");

	fprintf(fp, "unset multiplot\n");
	pclose(fp);

	return 0;
}

