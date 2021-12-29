#include<stdio.h>
#include<Windows.h>


int TestSegment()
{
	WORD val_cs = 0;
	WORD val_ds = 0;
	WORD val_ss = 0;

	DWORD dwTemp = 11111111;
	DWORD dwResult = 0;

	__asm
	{
		xor eax, eax
		mov ax, cs
		mov val_cs, ax

		xor eax, eax
		mov ax, ds
		mov val_ds, ax

		xor eax, eax
		mov ax, ss
		mov val_ss, ax

		xor eax, eax
		mov ax, cs
		//mov ds, ax

		//lds ax,dwTemp


		//xor eax, eax
		//mov ax, ds
		//mov val_ds, ax


		lea eax, dword ptr ds : [dwTemp]
		mov eax, dword ptr ds : [eax]
		lea ebx, dword ptr ds : [dwResult]
		mov dword ptr ds : [dwResult] , eax

		//call getaddr	//5 Bytes long

		//jmp far func
	}
	printf("cs=%x\tds=%x\tss=%x\n", val_cs, val_ds, val_ss);
	printf("%d\n", dwResult);

	system("pause");

	return 0;
}

void __declspec(naked) func()
{
	__asm
	{
		jmp far eax
		//jmp far dword ptr[eax]
	}
}

void __declspec(naked) getaddr()
{
	__asm
	{
		mov eax,dword ptr [esp]
		add eax, 5	//skip call far 指令
		ret
	}
}


void __declspec(naked) TestJmpFar()
{
	__asm
	{
		int 3
		retn 4
	}
}

int main(int argc, char* argv[], char* envp[])
{
	//__asm
	//{
	//	push 0x12345678
	//	call 0x20:0x12345678
	//}
	TestSegment();
}
