/*
 * Internal header for the MacAddress extension.
 *
 * This file should be used for any common function definitions etc that need to
 * be shared between the platform-dependent and platform-indepdendent parts of
 * this extension.
 *
 * NOTE: This file was originally written by the extension builder, but will not
 * be overwritten (unless --force is specified) and is intended to be modified.
 */
#ifndef MACADDRESS_INTERNAL_H
#define MACADDRESS_INTERNAL_H

#include "MacAddress.h"
#include "MacAddress_autodefs.h"


struct MacAddressGlobals
{
    bool m_MacAddressRunning;
};

/**
 * Initialise the extension.  This is called once then the extension is first
 * accessed by s3eregister.  If this function returns S3E_RESULT_ERROR the
 * extension will be reported as not-existing on the device.
 */
s3eResult MacAddressInit();

/**
 * Platform-specific initialisation, implemented on each platform
 */
s3eResult MacAddressInit_platform();

/**
 * Terminate the extension.  This is called once on shutdown, but only if the
 * extension was loader and Init() was successful.
 */
void MacAddressTerminate();

/**
 * Platform-specific termination, implemented on each platform
 */
void MacAddressTerminate_platform();

/**
 * Platform-specific code to display message box.
 */

uint64	get_MacAddressAsNumber();

const char*	get_MacAddressAsString();

/**
 * Called by platform code when dialog has been closed.
 */
void MacAddressComplete();

#endif /* !MACADDRESS_INTERNAL_H */
