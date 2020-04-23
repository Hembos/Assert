#include "Assert.h"

ASSERT* MyAssert;
int index = 0;
int CountAssert;

void SystemOpen(int Count)
{
	MyAssert = malloc(Count * sizeof(ASSERT));
	for (int i = 0; i < Count; i++)
	{
		MyAssert[i].ignore = FALSE;
	}
	CountAssert = Count;
}

void SystemClose()
{
	free(MyAssert);
}

void My_Assert(char* File, int Line, char* message)
{
	if (MyAssert[index].ignore != TRUE)
	{
		MyAssert[index].FileName = File;
		MyAssert[index].NumberLine = Line;
		MyAssert[index].message = message;

		index++;
		WinAssert(MyAssert, CountAssert, index);
	}
	
}

void Fatal_Error(char* File, int Line, char* message, int return_value)
{
	MyAssert[index].FileName = File;
	MyAssert[index].NumberLine = Line;
	MyAssert[index].message = message;
	WinFatalError(MyAssert, CountAssert, return_value, index);
	index++;
}
