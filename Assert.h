#ifdef _DEBUG
#define Assert(condition, message) if(!condition)My_Assert(__FILE__, __LINE__, message)
#else 
#define Assert(condition, message) 
#endif // _DEBUG
#define FatalError(condition, message, return_value) if(!condition)Fatal_Error(__FILE__, __LINE__, message, return_value);else;

#include <Windows.h>

typedef struct
{
	int NumberLine;
	char* FileName;
	char* message;
	BOOL ignore;
} ASSERT;

void My_Assert(char* File, int Line, char* message);
void Fatal_Error(char* File, int Line, char* message, int return_value);
void SystemOpen(int CountAssert);
void SystemClose();
int WINAPI WinAssert(ASSERT* MyAssert, int CountAssert, int index);
int WINAPI WinFatalError(ASSERT* MyAssert, int CountAssert, int Return_value, int index);
