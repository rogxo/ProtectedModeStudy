#include<stdio.h>

void change1(int *pa)
{
	*pa = 22;
	pa = (int*)0x11111111;	//ָ�����Ϳ�������ָ�������ֵ
}
void change2(int &a)
{
	a = 22;
	__asm
	{
		mov eax,11111111h
		mov [ebp+8],eax	//�������Ͳ��ɸ������õ�λ�ã�ͨ���������ǿ�иĵ���ʵ�ʷ�����ָ������һ����ֻ������������������
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
		mov tmp,eax	//��ȡ�ϲ㺯��ջ�С�ָ�롱��ֵ
	}
	printf("%x\n", tmp);

	tmp = 0;

	change2(a);
	__asm
	{
		mov eax,[esp-4]
		mov tmp,eax	//��ȡ�ϲ㺯��ջ�С�ָ�롱��ֵ
	}
	printf("%x\n", tmp);

}

int main()
{
	test1();
}