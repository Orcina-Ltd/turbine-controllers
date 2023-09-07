#include <windows.h>
#include "OrcFxAPI.h"

void __stdcall RegisterCapabilities(LPDWORD lpCapabilities)
{
    *lpCapabilities = *lpCapabilities | efcUnicode | efcImplicitIntegration;
}
