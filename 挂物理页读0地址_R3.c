// zz.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"

char x[]= "aaaaa";

int main(int argc, char* argv[])
{
	printf("%x\n",&x);
	
	while(1)
		printf("Address 0x0=%x\n",*(int*)0);

	getchar();
	return 0;
}

