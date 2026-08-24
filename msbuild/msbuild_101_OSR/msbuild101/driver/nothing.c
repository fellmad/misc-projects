///////////////////////////////////////////////////////////////////////////////
//
//    (C) Copyright 1995 - 2013 OSR Open Systems Resources, Inc.
//    All Rights Reserved
//
//    This sofware is supplied for instructional purposes only.
//
//    OSR Open Systems Resources, Inc. (OSR) expressly disclaims any warranty
//    for this software.  THIS SOFTWARE IS PROVIDED  "AS IS" WITHOUT WARRANTY
//    OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING, WITHOUT LIMITATION,
//    THE IMPLIED WARRANTIES OF MECHANTABILITY OR FITNESS FOR A PARTICULAR
//    PURPOSE.  THE ENTIRE RISK ARISING FROM THE USE OF THIS SOFTWARE REMAINS
//    WITH YOU.  OSR's entire liability and your exclusive remedy shall not
//    exceed the price paid for this material.  In no event shall OSR or its
//    suppliers be liable for any damages whatsoever (including, without
//    limitation, damages for loss of business profit, business interruption,
//    loss of business information, or any other pecuniary loss) arising out
//    of the use or inability to use this software, even if OSR has been
//    advised of the possibility of such damages.  Because some states/
//    jurisdictions do not allow the exclusion or limitation of liability for
//    consequential or incidental damages, the above limitation may not apply
//    to you.
//
//    OSR Open Systems Resources, Inc.
//    105 Route 101A Suite 19
//    Amherst, NH 03031  (603) 595-6500 FAX: (603) 595-6503
//    email bugs to: bugs@osr.com
//
//
//    MODULE:
//
//        NOTHING.C
//
//    ABSTRACT:
//
//      This file contains the skeleton code for a device driver
//      that does absolutely nothing.
//
//    AUTHOR(S):
//
//        OSR Open Systems Resources, Inc.
//
//    REVISION:
//
//
///////////////////////////////////////////////////////////////////////////////
#include <ntddk.h>
#include "nothing.h"


///////////////////////////////////////////////////////////////////////////////
//
//  DriverEntry
//
//    This routine is called by Windows when the driver is first loaded.
//
//  INPUTS:
//
//      DriverObject - Address of the DRIVER_OBJECT created by
//                     Windows for this driver.
//
//      RegistryPath - UNICODE_STRING which represents this drivers KEY in the
//                     Registry.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//      STATUS_SUCCESS.
//
//  IRQL:
//
//    This routine is called at IRQL == PASSIVE_LEVEL.
//
//  NOTES:
//
//
///////////////////////////////////////////////////////////////////////////////
NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
) {

    UNREFERENCED_PARAMETER(DriverObject);
    UNREFERENCED_PARAMETER(RegistryPath);

    //
    // Unload function
    //
    DriverObject->DriverUnload = NothingUnload;

    return (STATUS_SUCCESS);
}

///////////////////////////////////////////////////////////////////////////////
//
//  NothingUnload
//
//    This routine is our dynamic unload entry point.  We are called here when
//    the OS wants to unload our driver.  It is our responsibility to release any
//    resources we allocated.
//
//  INPUTS:
//
//      DriverObject - Address of our DRIVER_OBJECT.
//
//  OUTPUTS:
//
//      None.
//
//  RETURNS:
//
//      None.
//
//  IRQL:
//
//    This routine is called at IRQL == PASSIVE_LEVEL.
//
//  NOTES:
//
///////////////////////////////////////////////////////////////////////////////
VOID
NothingUnload(
    _In_ PDRIVER_OBJECT DriverObject
) {

    UNREFERENCED_PARAMETER(DriverObject);
    return;
}
