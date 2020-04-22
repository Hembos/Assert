#include "Header.h"

ASSERT* MyAssert;
HINSTANCE Assert;
HINSTANCE FatalError;
HINSTANCE hPrevInst;
LPSTR lpszArgs;
int nWinMode;

void SystemOpen(int CountAssert)
{
	MyAssert = malloc(CountAssert * sizeof(ASSERT));
	MyAssert->index = 0;
	MyAssert->CountAssert = CountAssert;
	for (int i = 0; i < CountAssert; i++)
	{
		MyAssert[i].ignore = FALSE;
	}
}

void SystemClose()
{
	free(MyAssert);
}

void My_Assert(char* File, int Line, char* message)
{
	if (MyAssert[MyAssert->index].ignore != TRUE)
	{
		MyAssert[MyAssert->index].FileName = File;
		MyAssert[MyAssert->index].NumberLine = Line;
		MyAssert[MyAssert->index].message = message;

		MyAssert = Temp(MyAssert, FALSE);
		MyAssert->index++;
		WinAssert(Assert, hPrevInst, lpszArgs, nWinMode);
	}
	
}

void Fatal_Error(char* File, int Line, char* message, int return_value)
{
	MyAssert[MyAssert->index].FileName = File;
	MyAssert[MyAssert->index].NumberLine = Line;
	MyAssert[MyAssert->index].message = message;
	MyAssert[MyAssert->index].return_value = return_value;
	MyAssert = Temp(MyAssert, TRUE);
	WinFatalError(FatalError, hPrevInst, lpszArgs, nWinMode);
	MyAssert->index++;
}