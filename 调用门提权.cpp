//他妈的，调试蓝屏了几十次
//未解决错误 IRQL_XXXX 蓝屏

#include "stdafx.h"
#include<Windows.h>

DWORD dwBuffer = 0;
BYTE GDT[6] = {0};

//eq gdtr+8*9 0040ec00`00081020
void __declspec(naked) CallGate1()
{
	_asm
	{
		int 3
		retf
	}
}

//eq gdtr+8*9 0040ec00`00081020
//eq gdtr+8*9 0040ec00`0008d4a0
void __declspec(naked) CallGate2()
{
	_asm
	{
		//int 3
		pushad
		pushfd

		//mov dwBuffer,ebx
		//mov eax,0x8003f00c
		//mov ebx,[eax]

		sgdt GDT

		popad
		popfd
		retf
	}
}

void PrintRes()
{
	printf("dwBuffer=%x\n",dwBuffer);
	printf("GDTR=%x\tGDTL=%x\n",*(DWORD*)&GDT[2],*(WORD*)GDT);
}

int main()
{
	BYTE buffer[6] = { 0 };
	*(DWORD*)&buffer[0] = 0x12345678;
	*(WORD*)&buffer[4] = 0x48;
	
	_asm
	{
		pushad
		pushfd
		call fword ptr [buffer]
		popfd
		popad
	}

	PrintRes();
	getchar();

	return 0;
}
