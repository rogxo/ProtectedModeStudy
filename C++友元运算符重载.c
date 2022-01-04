#include<stdio.h>

class CTestOperator
{
public:
	
	CTestOperator();
	friend CTestOperator operator++(CTestOperator& t,int a);
	friend void Print(CTestOperator& t);

private:
	int x;
	int y;
	
};

void Print(CTestOperator& t)
{
	printf("%d\t%d\n", t.x, t.y);
}

CTestOperator::CTestOperator()
{
	this->x = 10;
	this->y = 20;
}

CTestOperator operator++(CTestOperator& t,int a)
{
	t.x++;
	t.y++;
	return t;
}

void test()
{
	CTestOperator t;
	Print(t);
	t++;
	Print(t);
}

int main()
{
	test();
	return 0;
}