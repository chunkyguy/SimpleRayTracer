#include "WLAssert.h"
#include <cassert>

#ifdef __APPLE__
  #include <cstdio>
#else
  #include <Windows.h>
#endif


void wlAssert(const bool condition, const char * message) 
{
	if (condition) {
		return;
	}

#ifdef __APPLE__
  printf("%s\n", message);
#else
  OutputDebugStringA(message);
#endif

	assert(condition);
}
