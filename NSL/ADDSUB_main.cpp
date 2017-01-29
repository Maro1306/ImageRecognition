#include "systemc.h"
#include "ADDSUB.sh"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PLUS	0
#define MINUS	1

ADDSUB *as_i;

sc_clock clk("clk");
sc_signal<bool> reset("reset");
sc_signal<sc_uint<1> > as;
sc_signal<sc_uint<18> > a;
sc_signal<sc_uint<1> > bs;
sc_signal<sc_uint<18> > b;
sc_signal<sc_uint<1> > rs;
sc_signal<sc_uint<18> > r;
sc_signal<sc_uint<1> > exec;

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

void exec_add(int a_sign, int b_sign){
	double a_dec, b_dec;
	double answer;

	as = a_sign;
	a_dec = (double)rand()/RAND_MAX*5.0;
	a = dec2int(a_dec);
	bs = b_sign;
	b_dec = (double)rand()/RAND_MAX*5.0;
	b = dec2int(b_dec);
	exec = 1;
	sc_start(1, SC_NS);

	answer = (a_sign==PLUS ? 1 : -1) * a_dec + (b_sign==PLUS ? 1 : -1) * b_dec;

	cout << (a_sign==PLUS ? "" : "-") << a_dec;
	cout << (b_sign==PLUS ? " + " : " - ") << b_dec;
	cout << " = " << (rs.read()==PLUS ? "" : "-") << int2dec(r.read());
	cout << "     " << answer << "\n";
}

/*
void exec_mul(int a_sign, int b_sign){
	double a_dec, b_dec;
	double answer;
	
	as = a_sign;
	a_dec = (double)rand()/RAND_MAX*3.0;
	a = dec2int(a_dec);
	bs = b_sign;
	b_dec = (double)rand()/RAND_MAX*3.0;
	b = dec2int(b_dec);
	calc_mul = 1;
	sc_start(1, SC_NS);

	answer = (a_sign==b_sign ? 1 : -1) * a_dec * b_dec;

	cout << (a_sign==PLUS ? "" : "-") << a_dec;
	cout << " * " << (b_sign==PLUS ? "" : "-") << b_dec;
	cout << " = " << (rs.read()==PLUS ? "" : "-") << int2dec(r.read());
	cout << "     " << answer << "\n";

	calc_mul = 0;
}
*/

int sc_main(int argc, char **argv){
	as_i = new ADDSUB("as_i");

	as_i->m_clock(clk);
	as_i->p_reset(reset);
	as_i->as(as);
	as_i->a(a);
	as_i->bs(bs);
	as_i->b(b);
	as_i->rs(rs);
	as_i->r(r);
	as_i->exec(exec);

	sc_start(0, SC_NS);
	reset = 1;
	sc_start(1, SC_NS);
	reset = 0;

	cout << "\n\n\n";

	srand(time(NULL));

	exec_add(PLUS, PLUS);
	exec_add(PLUS, PLUS);
	exec_add(PLUS, MINUS);
	exec_add(PLUS, MINUS);
	exec_add(MINUS, PLUS);
	exec_add(MINUS, PLUS);
	exec_add(MINUS, MINUS);
	exec_add(MINUS, MINUS);

	cout << "\n\n\n";

	return 0;
}
