#include "systemc.h"
#include "EXP.sh"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PLUS	0
#define MINUS	1

EXP *exp_i;

sc_clock clk("clk");
sc_signal<bool> reset("reset");
sc_signal<sc_uint<19> > x;
sc_signal<sc_uint<19> > y;
sc_signal<sc_uint<1> > calc;

double int2dec(int x){
	double s = 0;
	int sign = 1;

	if(x >= 262144){
		x -= 262144;
		sign = -1;
	}
	for(int i=-14 ; i<=3 ; i++){
		if(x % 2) s += pow(2.0, (double)i);
		x = x / 2;
	}

	return sign * s;
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
	double x_dec;
	FILE *fp;

	exp_i = new EXP("exp_i");
	exp_i->m_clock(clk);
	exp_i->p_reset(reset);
	exp_i->x(x);
	exp_i->y(y);
	exp_i->calc(calc);

	sc_start(0, SC_NS);
	reset = 0;
	sc_start(1, SC_NS);
	reset = 1;

	fp = popen("gnuplot -persist", "w");
	fprintf(fp, "set terminal png\n");
	fprintf(fp, "set output 'exp_sim_01.png'\n");
	fprintf(fp, "set multiplot\n");
	fprintf(fp, "set xrange [-2.0:2.0]\n");
	fprintf(fp, "set yrange [0:10.0]\n");
	fprintf(fp, "set xlabel 'x'\n");
	fprintf(fp, "set ylabel 'y'\n");
	fprintf(fp, "unset key\n");

	srand(time(NULL));

	fprintf(fp, "plot '-' with points\n");
	for(int i=0 ; i<300 ; i++){
		x_dec = (double)rand()/RAND_MAX*4.0-2.0;
		x = (x_dec>=0 ? 0 : 262144) + dec2int(fabs(x_dec));
		calc = 1;
		sc_start(1, SC_NS);
		calc = 0;
		sc_start(1, SC_NS);
		sc_start(1, SC_NS);
		sc_start(1, SC_NS);
		sc_start(1, SC_NS);
		fprintf(fp, "%lf %lf\n", x_dec, int2dec(y.read()));
	}
	fprintf(fp, "e\n");

	fprintf(fp, "plot '-' with lines\n");
	for(double i=-2.0 ; i<2.0 ; i+=0.1){
		fprintf(fp, "%lf %lf\n", i, exp(i));
	}
	fprintf(fp, "e\n");

	fprintf(fp, "unset multiplot\n");
	pclose(fp);

	return 0;
}

