declare FIXP_OPERATION{
	input	as;
	input	a[18];
	input	bs;
	input	b[18];
	output	rs;
	output	r[18];
	func_in	calc_add(as, a, bs, b);
	func_in	calc_mul(as, a, bs, b);
}
