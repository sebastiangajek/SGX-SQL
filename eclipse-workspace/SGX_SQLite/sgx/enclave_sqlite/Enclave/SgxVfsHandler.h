#ifndef SGX_VFS_HANDLER
#define SGX_VFS_HANDLER

#include <string.h>
using namespace std;

/*
** Make sure we can call this stuff from C++.
*/
#ifdef __cplusplus
extern "C" {
#endif

string getSgxVfsName();

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
