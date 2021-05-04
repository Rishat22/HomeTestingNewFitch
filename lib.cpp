#include "lib.h"

#include "version.h"

int version()
{
#if(defined PROJECT_VERSION_PATCH)
	return PROJECT_VERSION_PATCH;
#else
	return 0;
#endif
}
