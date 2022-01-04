#include<stdio.h>
//#include <typeinfo>

template<class T>
void PrintArray(T array, int length)
{
	puts("Index\tValue");
	for (int i = 0; i < length; i++)
	{
		printf("  %d\t  %d\n", i, array[i]);
	}
	putchar('\n');
}

template<class T>
bool BubbleSort(T array, int length)	//升序排列
{
	if (length < 1)
		return false;
	for (int i = 0; i < length - 1; i++)
	{
		for (int j = 0; j < length - 1 - i; j++)
		{
			if (array[j]>array[j+1])
			{
				register int tmp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = tmp;
			}
		}
	}
	return true;
}

template<class T,class E>
int BinarySearch(T array,int length,E element)	//升序查找
{
	if (length < 1)
		return -1;
	int begin = 0, end = length - 1, index = 0;

	while (begin <= end)
	{
		index = (begin + end) >> 1;
		if (element < array[index])
		{
			end = index - 1;
		}
		else if(element > array[index])
		{
			begin = index + 1;
		}
		else
		{
			return index;
		}
	}
	return -1;
}

template<class T>
bool swap(T* a, T* b)
{
	if (!a || !b)
		return false;
	register T tmp = 0;

	tmp = *a;
	*a = *b;
	*b = tmp;
	return true;
}

void test1()
{
	int a[10] = { 1,42,32,44,6,7,8,9,87,99 };
	BubbleSort(a, sizeof(a)/sizeof(a[0]));
	PrintArray(a, 10);
	printf("%d in array index %d\n",87, BinarySearch(a, sizeof(a) / sizeof(a[0]), 87));
}

void test2()
{
	//模板的实质：在编译过程中生成“多个”程序中会调用到的不同类型的函数，硬编码到不同地址(复制了好几份代码)
	//模板和泛型是一个概念，只不过在Java和C++中实现方式不同，Java中进行了类型转换再调用同一个函数，而C++则比较硬的把所有可能用到的类型统统编译进二进制文件
	//相对而言，同一泛型/模板Java程序编译出来是比C++要小的，而C++效率比较高（空间换时间）
	int a = 1, b = 2;
	swap(&a, &b);
	printf("a=%d b=%d\n", a, b);
	float c = 1, d = 2;
	swap(&c, &d);
	printf("c=%f d=%f\n", c, d);
	short e = 1, f = 2;
	swap(&e, &f);
	printf("e=%d f=%d\n", e, f);
	//用多少个类型编译多少进去
}

int main()
{
	test2();
}