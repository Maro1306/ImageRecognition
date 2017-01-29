declare RAM{
	input	address[4];
	input	datai[4];
	output	datao[4];
	func_in	write(address, datai);
	func_in read(address);
}
