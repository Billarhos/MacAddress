
/*
 * windows-specific implementation of the MacAddress extension.
 * Add any platform-specific functionality here.
 *
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */

#include "MacAddress_internal.h"
#include <stdio.h>
#include <windows.h>
#include <Iphlpapi.h>

static char macString[256];

s3eResult MacAddressInit_platform()
{
    //Add any platform-specific initialisation code here
    return S3E_RESULT_SUCCESS;
}

void MacAddressTerminate_platform()
{
	//Add any platform-specific termination code here
}

uint64 get_MacAddressAsNumber()
{
	IP_ADAPTER_INFO AdapterInfo[16];		// Allocate information for up to 16 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);	// Save memory size of buffer

	DWORD dwStatus = GetAdaptersInfo(		// Call GetAdapterInfo
		AdapterInfo,						// [out] buffer to receive data
		&dwBufLen);							// [in] size of receive data buffer
	
	if (dwStatus != ERROR_SUCCESS)
	{
		MacAddressComplete();
		return 0;
	}

	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; // Contains pointer to current adapter info
	uint64 MACdword = pAdapterInfo->Address[5] + ((uint64)pAdapterInfo->Address[4] << 8) + ((uint64)pAdapterInfo->Address[3] << 16) + ((uint64)pAdapterInfo->Address[2] << 24)
						+ ((uint64)pAdapterInfo->Address[1] << 32) + ((uint64)pAdapterInfo->Address[0] << 40);
		
	MacAddressComplete();
    return MACdword;
}

const char* get_MacAddressAsString()
{
	IP_ADAPTER_INFO AdapterInfo[16];		// Allocate information for up to 16 NICs
	DWORD dwBufLen = sizeof(AdapterInfo);	// Save memory size of buffer

	DWORD dwStatus = GetAdaptersInfo(		// Call GetAdapterInfo
		AdapterInfo,						// [out] buffer to receive data
		&dwBufLen);							// [in] size of receive data buffer
	
	if (dwStatus != ERROR_SUCCESS)
	{
		MacAddressComplete();
		return NULL;
	}

	PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo; // Contains pointer to current adapter info
	
	sprintf_s (macString, "%02X-%02X-%02X-%02X-%02X-%02X", pAdapterInfo->Address[0], pAdapterInfo->Address[1],
	pAdapterInfo->Address[2], pAdapterInfo->Address[3], pAdapterInfo->Address[4], pAdapterInfo->Address[5]);
		
	MacAddressComplete();
    
	return macString;
}
