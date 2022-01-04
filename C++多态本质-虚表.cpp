#include<windows.h>
#include<stdio.h>


class Test
{
public:

	int a = 1;
	int b = 2;

	void func1()
	{
		return;
	}
	virtual void func2()
	{
		return;
	}
};

class Base
{
public:
	int a = 1;
	int b = 2;
	virtual void Func1()
	{
		puts("Func1");
	}
	virtual void Func2()
	{
		puts("Func2");
	}
	virtual void Func3()
	{
		puts("Func3");
	}

private:

};

class Sub:Base
{
public:
	virtual void Func5()
	{
		puts("Func4");
	}virtual void Func4()
	{
		puts("Func5");
	}virtual void Func6()
	{
		puts("Func6");
	}
};

class SubSub:Sub
{
public:
	virtual void Func7()
	{
		puts("Func7");
	}virtual void Func8()
	{
		puts("Func8");
	}virtual void Func9()
	{
		puts("Func9");
	}
};

class Override:Base
{
public:
	virtual void Func4()
	{
		puts("Func4");
	}
	virtual void Func5()
	{
		puts("Func5");
	}
	virtual void Func6()
	{
		puts("Func6");
	}
	virtual void Func2()
	{
		puts("Func2 Override");
	}virtual void Func1()
	{
		puts("Func1 Override");
	}
};

class Override2:Override
{
public:
	virtual void Func7()
	{
		puts("Func7");
	}virtual void Func8()
	{
		puts("Func8");
	}virtual void Func9()
	{
		puts("Func9");
	}

	virtual void Func1()
	{
		puts("Func1 Override2");
	}
	virtual void Func4()
	{
		puts("Func4 Override2");
	}
};

void test1()	//通过对象调用时，虚函数和普通成员函数都是直接CALL(E8 ...)
{
	Test t;
	t.func1();
	t.func2();
}

void test2()	//通过类指针调用时，虚函数变为间接CALL(FF ...)
{
	Test t;
	Test* pt = &t;
	pt->func1();
	pt->func2();
}

void test3()
{
	typedef void(*Proc)(void);
	Sub s;
	Sub* ps = &s;
	ps->Func4();

	for (size_t i = 0; i < 6; i++)
	{
		Proc vtFunc = (Proc)(*(int*)(*(int*)(&s) + 0x4 * i));	//对象的地址的前4字节为虚表的地址，虚表里保存虚函数的地址
		printf("0x%x\t", (int)vtFunc);	//单继承无重写，虚表按顺序来，父类到子类虚函数依次排列
		vtFunc();
	}
	
}

void test4()
{
	typedef void(*Proc)(void);
	Override s;
	Override* ps = &s;
	
	ps->Func1();
	
	for (size_t i = 0; i < 4; i++)
	{
		Proc vtFunc = (Proc)(*(int*)(*(int*)(&s) + 0x4 * i));
		printf("0x%x\t", (int)vtFunc);	//单继承有重写，虚表中的函数地址会被重写的函数替换掉
		vtFunc();
	}
}

void test5()
{
	typedef void(*Proc)(void);
	SubSub s;
	SubSub* ps = &s;

	ps->Func7();

	for (size_t i = 0; i < 9; i++)
	{
		Proc vtFunc = (Proc)(*(int*)(*(int*)(&s) + 0x4 * i));
		printf("0x%x\t", (int)vtFunc);	//多层继承无重写，虚表按顺序来，父类到子类再到子子类虚函数依次排列
		vtFunc();
	}

}

void test6()
{
	typedef void(*Proc)(void);
	Override2 s;
	Override2* ps = &s;

	ps->Func4();

	for (size_t i = 0; i < 9; i++)
	{
		Proc vtFunc = (Proc)(*(int*)(*(int*)(&s) + 0x4 * i));
		printf("0x%08x\t", (int)vtFunc);	//多层继承有重写，
		vtFunc();
	}

}

void CheckVt()
{
	Base b1;
	Base b2;
	Sub s;
	Base* pb1 = &b1;
	Base* pb2 = &b2;
	Sub* ps = &s;
	printf("0x%08x\n0x%08x\n", *(int*)pb1, *(int*)pb2);
	
}

int main()
{
	//test6();
	CheckVt();
	return 0;
}