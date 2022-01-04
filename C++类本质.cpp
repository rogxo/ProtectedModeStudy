#include<windows.h>
#include<stdio.h>

class Test
{
public:
	int a;
	int b;
	int add()
	{
		return a + b;
	}
	int sub()
	{
		return a - b;
	}
	int mul()
	{
		return a * b;
	}
	int div()
	{
		return a / b;
	}

	Test()
	{
	}

	Test(int a,int b)
	{
		this->a = a;
		this->b = b;
	}

	~Test()
	{
		this->a = 0;
		this->b = 0;
	}
};

class SubTest:Test
{
public:
	int c;
	int d;

	SubTest(int a, int b, int c, int d)
	{
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
	}
};

int main()
{
	//Test t(1,2);
	SubTest t(1,2,3,4);
	//t.add(); 
	return 0;
}

/*

类实例化出来的对象一般在创建它的函数栈帧的缓冲区(ebp-4,ebp-8,ebp-C)中
调用成员方法(包括构造器)时会先将参数PUSH进栈再lea ecx,对象地址(一般为该层函数栈缓冲区ebp-8中)；这叫做__thiscall(内平栈，从右到左堆栈传参(32位)，最后传对象指针(this指针，通过ecx传，保存在成员函数栈缓冲区ebp-8处))

*/



