#include <stdio.h>
#include "calc.h"

int main(int arc, char *arv[])
{
	int x = 100;
	int y = 10;
	int result;
	
	result = add (x , y);
	printf("x add y eql:%d\n", result);
	
	result = sub (x , y);
	printf("x sub y eql:%d\n", result);

	result = mul (x , y);
	printf("x mul y eql:%d\n", result);

	result = div (x , y);
	printf("x div y eql:%d\n", result);
	
}