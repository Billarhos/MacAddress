/*
 * WARNING: this is an autogenerated file and will be overwritten by
 * the extension interface script.
 */
/*
 * This file contains the automatically generated loader-side
 * functions that form part of the extension.
 *
 * This file is awlays compiled into all loaders but compiles
 * to nothing if this extension is not enabled in the loader
 * at build time.
 */
#include "MacAddress_autodefs.h"
#include "s3eEdk.h"
#include "MacAddress.h"
#include "MacAddress_internal.h"

//Declarations of Init and Term functions
extern s3eResult MacAddressInit();
extern void MacAddressTerminate();


void MacAddressRegisterExt()
{
    /* fill in the function pointer struct for this extension */
    void* funcPtrs[2];
    funcPtrs[0] = (void*)get_MacAddressAsNumber;
    funcPtrs[1] = (void*)get_MacAddressAsString;

    /*
     * Flags that specify the extension's use of locking and stackswitching
     */
    int flags[2] = { 0 };

    /*
     * Register the extension
     */
    s3eEdkRegister("MacAddress", funcPtrs, sizeof(funcPtrs), flags, MacAddressInit, MacAddressTerminate, sizeof(MacAddressGlobals));
}

#if !defined S3E_BUILD_S3ELOADER

#if defined S3E_EDK_USE_STATIC_INIT_ARRAY
int MacAddressStaticInit()
{
    void** p = g_StaticInitArray;
    void* end = p + g_StaticArrayLen;
    while (*p) p++;
    if (p < end)
        *p = (void*)&MacAddressRegisterExt;
    return 0;
}

int g_MacAddressVal = MacAddressStaticInit();

#elif defined S3E_EDK_USE_DLLS
S3E_EXTERN_C S3E_DLL_EXPORT void RegisterExt()
{
    MacAddressRegisterExt();
}
#endif

#endif
