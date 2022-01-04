#include<stdio.h>

void change1(int *pa)
{
	*pa = 22;
	pa = (int*)0x11111111;	//指针类型可以随便改指针变量的值
}
void change2(int &a)
{
	a = 22;
	__asm
	{
		mov eax,11111111h
		mov [ebp+8],eax	//引用类型不可更改引用的位置，通过内联汇编强行改掉，实际反汇编跟指针类型一样，只不过被编译器限制了
	}
}

void test1()
{
	int a = 10;
	change1(&a);
	
	int tmp = 0;
	__asm
	{
		mov eax,[esp-4];
		mov tmp,eax	//获取上层函数栈中“指针”的值
	}
	printf("%x\n", tmp);

	tmp = 0;

	change2(a);
	__asm
	{
		mov eax,[esp-4]
		mov tmp,eax	//获取上层函数栈中“指针”的值
	}
	printf("%x\n", tmp);

}

int main()
{
	test1();
}