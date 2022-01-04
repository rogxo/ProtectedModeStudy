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
bool BubbleSort(T array, int length)	//��������
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
int BinarySearch(T array,int length,E element)	//�������
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
	//ģ���ʵ�ʣ��ڱ�����������ɡ�����������л���õ��Ĳ�ͬ���͵ĺ�����Ӳ���뵽��ͬ��ַ(�����˺ü��ݴ���)
	//ģ��ͷ�����һ�����ֻ������Java��C++��ʵ�ַ�ʽ��ͬ��Java�н���������ת���ٵ���ͬһ����������C++��Ƚ�Ӳ�İ����п����õ�������ͳͳ������������ļ�
	//��Զ��ԣ�ͬһ����/ģ��Java�����������Ǳ�C++ҪС�ģ���C++Ч�ʱȽϸߣ��ռ任ʱ�䣩
	int a = 1, b = 2;
	swap(&a, &b);
	printf("a=%d b=%d\n", a, b);
	float c = 1, d = 2;
	swap(&c, &d);
	printf("c=%f d=%f\n", c, d);
	short e = 1, f = 2;
	swap(&e, &f);
	printf("e=%d f=%d\n", e, f);
	//�ö��ٸ����ͱ�����ٽ�ȥ
}

int main()
{
	test2();
}