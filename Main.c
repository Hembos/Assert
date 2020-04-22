#include "Header.h"


int main()
{
	SystemOpen(10);
	Assert(1 != 1, "qwe");
	Assert(12 != 12, "qwe");
	FatalError(1 == 1, "qwe", 1);
	SystemClose();
	return 0;
}