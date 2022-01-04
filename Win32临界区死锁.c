#include<stdio.h>
#include<Windows.h>

CRITICAL_SECTION cs_a;
CRITICAL_SECTION cs_b;

int a;
int b;

void ThreadProc2()
{
	while (true)
	{
		printf("thread2 a = %d b = %d\n", a,b);
		EnterCriticalSection(&cs_a);
		Sleep(500);
				EnterCriticalSection(&cs_b);
		a++;	b++;
				LeaveCriticalSection(&cs_b);
		
		LeaveCriticalSection(&cs_a);
		Sleep(500);
	}
}

////////////////////////
解决方案：所有线程临界区取得和释放顺序相同
////////////////////////

void ThreadProc1()
{
	while (true)
	{
		printf("thread1 a = %d b = %d\n", a, b);
		EnterCriticalSection(&cs_b);
		Sleep(500);
				EnterCriticalSection(&cs_a);
		a++;	b++;
				LeaveCriticalSection(&cs_a);

		LeaveCriticalSection(&cs_b);
		Sleep(500);
	}
}


int main()
{
	InitializeCriticalSection(&cs_a);
	InitializeCriticalSection(&cs_b);
	HANDLE hThread1 = NULL;
	HANDLE hThread2 = NULL;
	hThread1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc1,NULL,0,NULL);
	hThread2 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadProc2,NULL,0,NULL);
	if (!hThread1 ||!hThread2)
	{
		return 0;
	}
	WaitForSingleObject(hThread1, INFINITE);
	WaitForSingleObject(hThread2, INFINITE);

	CloseHandle(hThread1);
	CloseHandle(hThread2);


	return 0;
}