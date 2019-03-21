#include <iostream>

#include "test.h"

// Setup debug mode, 0 false, 1 true

#define DEBUG 1

#if DEBUG
	#define LOG(x) std::cout << x << std::endl;
#else
	#define LOG(x)
#endif

int main()
{
	Test t();
	LOG(t.getX());
	system("PAUSE");
	return 0;
}