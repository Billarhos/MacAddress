
/*
Generic implementation of the MacAddress extension.
This file should perform any platform-indepedentent functionality
(e.g. error checking) before calling platform-dependent implementations.
*/

/*
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

/**
 * @page EDKExtensionMacAddressSource Mac Address Extension Source Code and Project Files
 *
 * MacAddress.mkf (includes this extension as a subproject):
 * @include MacAddress.mkf
 *
 * Internal header (source/h/MacAddress_internal.h):
 * @include ../h/MacAddress_internal.h
 *
 * Generic source (source/generic/MacAddressApp.cpp):
 * @include MacAddress.cpp
 *
 * Windows source (source/windows/MacAddress_platform.cpp):
 * @include ../windows/MacAddress_platform.cpp
 */

#include "MacAddress_internal.h"
#include "s3eEdk.h"

s3eResult MacAddressInit()
{
    //Add any generic initialisation code here
    return MacAddressInit_platform();
}

void MacAddressTerminate()
{
    //Add any generic termination code here
    MacAddressTerminate_platform();
}

void MacAddressComplete()
{
    MACADDRESSGLOBALS->m_MacAddressRunning = false;
}

//s3eResult MacAddress(uint32 & addressNumber, std::string & addressString)
uint64	GetMacAddressAsNumber()
{
     MACADDRESSGLOBALS->m_MacAddressRunning = true;

 	 uint64 address = (uint64)(intptr_t)s3eEdkThreadRunOnOS((s3eEdkThreadFunc)get_MacAddressAsNumber, 0);
	 while (MACADDRESSGLOBALS->m_MacAddressRunning)
        {
            s3eEdkThreadSleep(20);
        }
	 return address;
}

const char*	GetMacAddressAsString()
{
     MACADDRESSGLOBALS->m_MacAddressRunning = true;

  	 const char* address = (const char*)(intptr_t)s3eEdkThreadRunOnOS((s3eEdkThreadFunc)get_MacAddressAsString, 0);
	 while (MACADDRESSGLOBALS->m_MacAddressRunning)
        {
            s3eEdkThreadSleep(20);
        }
	 return address;
}
