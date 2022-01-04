#include<windows.h>
#include<stdio.h>

void Msg()
{
	//MessageBoxA(0,0,0,0);
	printf("I was called!");
}

int main()
{
	int a = 0;
	int* p = &a;
	p = p + 4;
	*p = (int)Msg;
	return 0;
}