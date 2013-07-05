
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
//#include <sstream>


#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))

#define SAFE_DELETE(p)	{ if (p) { delete (p);	(p)=NULL; }	}
#define SAFE_DELETE_ARRAY(x)  if (x) { delete[] x; x = NULL; }
	
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
	PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD dwRetVal = 0;

	ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);

	pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(sizeof (IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) 
	{
		//printf("Error allocating memory needed to call GetAdaptersinfo\n");
        return 0;
    }
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
	{
        FREE(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(ulOutBufLen);
        if (pAdapterInfo == NULL) 
		{
            //printf("Error allocating memory needed to call GetAdaptersinfo\n");
            return 0;
        }
    }

	uint64 MACdword = pAdapterInfo->Address[5] + ((uint64)pAdapterInfo->Address[4] << 8) + ((uint64)pAdapterInfo->Address[3] << 16) + ((uint64)pAdapterInfo->Address[2] << 24)
						+ ((uint64)pAdapterInfo->Address[1] << 32) + ((uint64)pAdapterInfo->Address[0] << 40);

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) 
	{
        pAdapter = pAdapterInfo;
	}

	if (pAdapterInfo)
        FREE(pAdapterInfo);

	MacAddressComplete();
	return MACdword;
}

void get_MacAddressAsString(char * macAddress)
{
	
	PIP_ADAPTER_INFO pAdapterInfo;
    PIP_ADAPTER_INFO pAdapter = NULL;
	DWORD dwRetVal = 0;

	ULONG ulOutBufLen = sizeof (IP_ADAPTER_INFO);

	pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(sizeof (IP_ADAPTER_INFO));
    if (pAdapterInfo == NULL) 
	{
		//printf("Error allocating memory needed to call GetAdaptersinfo\n");
        return;
    }
	if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) 
	{
        FREE(pAdapterInfo);
        pAdapterInfo = (IP_ADAPTER_INFO *) MALLOC(ulOutBufLen);
        if (pAdapterInfo == NULL) 
		{
            //printf("Error allocating memory needed to call GetAdaptersinfo\n");
            return;
        }
    }

	sprintf(macAddress, "%02X-%02X-%02X-%02X-%02X-%02X", pAdapterInfo->Address[0], pAdapterInfo->Address[1],
	pAdapterInfo->Address[2], pAdapterInfo->Address[3], pAdapterInfo->Address[4], pAdapterInfo->Address[5]);

	if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) 
	{
        pAdapter = pAdapterInfo;
	}

	if (pAdapterInfo)
        FREE(pAdapterInfo);

	MacAddressComplete();

}
