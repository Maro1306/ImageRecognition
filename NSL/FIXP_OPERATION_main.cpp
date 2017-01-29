#include "systemc.h"
#include "FIXP_OPERATION.sh"
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define PLUS	0
#define MINUS	1

FIXP_OPERATION *fope_i;

sc_clock clk("clk");
sc_signal<bool> reset("reset");
sc_signal<sc_uint<1> > as;
sc_signal<sc_uint<18> > a;
sc_signal<sc_uint<1> > bs;
sc_signal<sc_uint<18> > b;
sc_signal<sc_uint<1> > rs;
sc_signal<sc_uint<18> > r;
sc_signal<sc_uint<1> > calc_add;
sc_signal<sc_uint<1> > calc_mul;

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
	calc_add = 1;
	sc_start(1, SC_NS);

	answer = (a_sign==PLUS ? 1 : -1) * a_dec + (b_sign==PLUS ? 1 : -1) * b_dec;

	cout << (a_sign==PLUS ? "" : "-") << a_dec;
	cout << (b_sign==PLUS ? " + " : " - ") << b_dec;
	cout << " = " << (rs.read()==PLUS ? "" : "-") << int2dec(r.read());
	cout << "     " << answer << "\n";

	calc_add = 0;
}

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

int sc_main(int argc, char **argv){
	fope_i = new FIXP_OPERATION("fope_i");

	fope_i->m_clock(clk);
	fope_i->p_reset(reset);
	fope_i->as(as);
	fope_i->a(a);
	fope_i->bs(bs);
	fope_i->b(b);
	fope_i->rs(rs);
	fope_i->r(r);
	fope_i->calc_add(calc_add);
	fope_i->calc_mul(calc_mul);

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

	cout << "\n";

	exec_mul(PLUS, PLUS);
	exec_mul(PLUS, PLUS);
	exec_mul(PLUS, MINUS);
	exec_mul(PLUS, MINUS);
	exec_mul(MINUS, PLUS);
	exec_mul(MINUS, PLUS);
	exec_mul(MINUS, MINUS);
	exec_mul(MINUS, MINUS);

	cout << "\n\n\n";

	return 0;
}
