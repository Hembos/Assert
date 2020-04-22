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
	int index;
	int CountAssert;
	BOOL ignore;
	int return_value;
} ASSERT;

void My_Assert(char* File, int Line, char* message);
void Fatal_Error(char* File, int Line, char* message, int return_value);
void SystemOpen(int CountAssert);
void SystemClose();
ASSERT* Temp(ASSERT* MyAssert, BOOL FatalError);
int WINAPI WinAssert(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdSh);
int WINAPI WinFatalError(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpszCmdParam, _In_ int nCmdShow);