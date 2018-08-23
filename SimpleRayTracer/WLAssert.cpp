#include "WLAssert.h"
#include <cassert>
#include <Windows.h>

void wlAssert(const bool condition, const char * message) 
{
	if (condition) {
		return;
	}

	OutputDebugString(message);
	assert(condition);
}
