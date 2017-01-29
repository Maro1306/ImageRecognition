#include <stdio.h>
#include <math.h>

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

int main(void){
	double x = 5.1415926;
	printf("%d\n", dec2int(x));

	return 0;
}
