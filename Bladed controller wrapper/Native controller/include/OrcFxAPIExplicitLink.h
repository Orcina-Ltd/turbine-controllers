#ifndef _orcfxapiexplicitlink_
#define _orcfxapiexplicitlink_

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>

#ifdef __cplusplus
namespace Orcina {
extern "C" {
#endif /* __cplusplus */

void __stdcall InitializeOrcFxAPI(HMODULE Module);

#ifdef __cplusplus
}
}
#endif  /* __cplusplus */

#endif /* !_orcfxapiexplicitlink_ */


