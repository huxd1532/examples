#include<stdio.h>

int add(int x, int y)
{
	return (x + y);
}

int sub(int x, int y)
{
	return (x - y);
}


int mul(int x, int y)
{
	return (x * y);
}

int div(int x, int y)
{
	if ( 0 == y )
	{
		printf("Dividend cannot be\n");
		return -1;
	}
	return (x / y);
}