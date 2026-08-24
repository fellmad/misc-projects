/****************************************************************************
 *
 *  $Workfile: crd_api.h $
 *  Copyright (c) 2006 DataCard Corporation.  All Rights Reserved.
 *
 ****************************************************************************
 *
 *  $Archive: /Driver/NT/include/crd_api.h $
 *  $Revision: 10 $
 *  $Date: 1/29/07 1:41p $
 *  Created by: Sangeeta Agarwal
 *  Modified by: $Author: Yangk $
 *
 *  Description:
 *    This file contains the implementation of the Card printer API.
 *
 ***$Nokeywords:$************************************************************/

/*
 * Copyright 1997 DataCard Corp.
 *
 */
  
#ifndef __CRD_API_H__
#define __CRD_API_H__

/* This will cause this file to be imported correctly into C++ files */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32 /* always defined for Win32 applications */
#include <wtypes.h> /* for SYSTEMTIME */
#ifndef CRDAPI
#define CRDAPI	__declspec( dllimport ) WINAPI
#endif
#ifndef CRDVAR
#define CRDVAR	__declspec( dllimport )
#endif
#endif

#ifdef UNICODE
#define __UnformatNTT __UnformatNTTA  

#else
#define __UnformatNTT __UnformatNTTA

#endif // UNICODE

   
/* Global variable definitions */
extern HINSTANCE CRDVAR __hResInstance1;

/* Macro definitions */

/*
 * The "CRD_RES" macro can be used in a "FormatMessage" function to get the proper language
 * version
 */
HINSTANCE CRDAPI __GetCrdResInstance();
#define CRD_RES __GetCrdResInstance()

/*
 * The "CRD_LAST_ERROR()" macro should be used with the value returned by "GetLastError",
 * which can be used in the "FormatMessage" function.  If the value returned by this macro
 * is zero, then the error is a system level.  Otherwise, it is an CRD error, and
 * "FormatMessage" should be used with the "FORMAT_MESSAGE_FROM_HMODULE" argument.
 */
#define CRD_LAST_ERROR(x)	((x & APPLICATION_ERROR_MASK)?(x & ~(APPLICATION_ERROR_MASK | ERROR_SEVERITY_ERROR)):0)


#define MAX_ICE_MS_TRACK_LENGTH  256
#define MAX_LOT_NUMBER_LENGTH  9

   /* Data types */
#define ICE_NO_DATA              0x00000000
#define ICE_GRAPHICS_FRONT       0x00000001
#define ICE_GRAPHICS_BACK        0x00000002
#define ICE_MAGSTRIPE_FRONT      0x00000004
#define ICE_MAGSTRIPE_BACK       0x00000008
#define ICE_SMARTCARD_FRONT      0x00000010
#define ICE_SMARTCARD_BACK       0x00000020
#define ICE_READ_MAGSTRIPE_FRONT 0x00000040
#define ICE_READ_MAGSTRIPE_BACK  0x00000080
#define GAL_OPTION1_FRONT        0x00000100
#define GAL_OPTION2_FRONT        0x00000200
#define GAL_OPTION1_BACK         0x00000400
#define GAL_OPTION2_BACK         0x00000800
#define GAL_OPTION1_FRONT2       0x00001000
#define GAL_OPTION2_FRONT2       0x00002000
#define GAL_OPTION1_BACK2        0x00004000
#define GAL_OPTION2_BACK2        0x00008000
#define ICE_OPTICAL_FRONT        0x00010000
#define ICE_OPTICAL_BACK         0x00020000
#define ICE_MAG_BEFORE_SC_FRONT  0x00040000
#define ICE_MAG_BEFORE_SC_BACK   0x00080000
#define ICE_BARCODE_FRONT		 0x00100000	
#define ICE_BARCODE_BACK		 0x00200000
#define ICE_SC_BEFORE_BC_FRONT   0x00400000
#define ICE_SC_BEFORE_BC_BACK    0x00800000	
#define CRD_BARCODE_FRONT		 0x00100000	
#define CRD_BARCODE_BACK		 0x00200000
#define CRD_SC_BEFORE_BC_FRONT   0x00400000
#define CRD_SC_BEFORE_BC_BACK    0x00800000
#define CRD_INDENT_FRONT		 0x01000000
#define CRD_INDENT_BACK		     0x02000000

/* Error definitions */
typedef enum
{
   ICE_API_ERR_FIRST = 800,
   ICE_API_ERR_TRACK1_LENGTH = ICE_API_ERR_FIRST,
   ICE_API_ERR_TRACK2_LENGTH,
   ICE_API_ERR_TRACK3_LENGTH,
   ICE_API_ERR_TRACK4_LENGTH,
   ICE_API_ERR_TRACK1_CHAR_RANGE,
   ICE_API_ERR_TRACK2_CHAR_RANGE,
   ICE_API_ERR_TRACK3_CHAR_RANGE,
   ICE_API_ERR_TRACK4_CHAR_RANGE,
   ICE_API_ERR_NOT_ICE_PRINTER,
   ICE_API_ERR_INTERNAL,
   ICE_API_ERR_OUT_OF_SEQUENCE,
   ICE_API_ERR_INCONSISTENT_VALUE,
   ICE_API_ERR_UNSUPPORTED_VALUE,
   ICE_API_ERR_PRINTER_ERROR,
   ICE_API_ERR_TIMEOUT,   
   ICE_API_ERR_INVALID_BPI_VALUE,
   ICE_API_ERR_INVALID_BPC_VALUE,
   ICE_API_ERR_INVALID_MAXCHARS_VALUE,
   ICE_API_ERR_INVALID_SSA_VALUE,
   ICE_API_ERR_INVALID_LRC_VALUE,
   ICE_API_ERR_INVALID_CHAR_PARITY_VALUE,
   ICE_API_ERR_INVALID_START_SENTINEL_VALUE,
   ICE_API_ERR_INVALID_END_SENTINEL_VALUE,
   ICE_API_ERR_INVALID_HIGH_CHAR_VALUE,
   ICE_API_ERR_INVALID_LOW_CHAR_VALUE,
   ICE_API_ERR_INVALID_SET_MASK_VALUE,
   
   ICE_API_ERR_LAST = ICE_API_ERR_INVALID_SET_MASK_VALUE //ICE_API_ERR_TIMEOUT
} ICE_API_ERRS;

/*
 * These define mag stripe track types for the printer.
 */
typedef enum
{
   ICE_MS_IAT              = 0,
   ICE_MS_TRIPLE_IATA      = 1,
   ICE_MS_TRIPLE_BINARY    = 2,
   ICE_MS_AAMVA            = 3,
   ICE_MS_NTT              = 4,
   ICE_MS_RESERVED0        = 5,
   ICE_MS_RESERVED1        = 6,
   ICE_MS_CUSTOM           = 7,
   ICE_MS_USE_DRIVER       = 8,
   ICE_MS_USE_PRINTER      = 9,
	ICE_MS_RESERVED2		= 10,
	ICE_MS_RESERVED3		= 11,
} IceTrackType;

/*
 * These define the legal smart card commands that
 * can be used by SmartCardContinue.
 */
typedef enum
{
   ICE_SMART_CARD_GOOD  = 0,
   ICE_SMART_CARD_ABORT = 1
} IceSmartCardCommand;

/*
 * These define the legal bar code commands that
 * can be used by BarCodeContinue.
*/
typedef enum	
{
   BARCODE_GOOD  = 2,
   BARCODE_ABORT = 3
} BarCodeCommand;	

/*
* BarCodeContinue
*/
BOOL CRDAPI BarCodeContinue(HDC /*hDC*/, DWORD /*dwCommand*/);

/*
* FeedCardEx
*/
BOOL CRDAPI FeedCardEx(HDC /*hDC*/,
                     DWORD /*dwCardData*/);


#if defined _UNICODE || defined UNICODE
#define GetRibbonInfo GetRibbonInfoW
#define GetIndentRibbonInfo GetIndentRibbonInfoW
#define GetLaminatorMaterialInfo GetLaminatorMaterialInfoW
#define GetClearCardStatus GetClearCardStatusW
#define SetMagstripeConfiguration   SetMagstripeConfigurationW
#define EncodeMagstripeEx   EncodeMagstripeExW
#define CleanLaminatorModules CleanLaminatorModulesW

#else
#define GetRibbonInfo GetRibbonInfoA
#define GetIndentRibbonInfo GetIndentRibbonInfoA
#define GetLaminatorMaterialInfo GetLaminatorMaterialInfoA
#define GetClearCardStatus GetClearCardStatusA
#define SetMagstripeConfiguration   SetMagstripeConfigurationA
#define EncodeMagstripeEx   EncodeMagstripeExA
#define CleanLaminatorModules CleanLaminatorModulesA

#endif // UNICODE
   
   
/*
 * The "CRD_RES" macro can be used in a "FormatMessage" function to get the proper language
 * version
 */
HINSTANCE CRDAPI __GetCrdResInstance();
#define CRD_RES __GetCrdResInstance()   
   
   /* Ribbon type definitions */
   typedef enum		
   {
         SUPPLY_UNKNOWN_RIBBON      = 1,
         SUPPLY_YMC_RIBBON          = 2,
         SUPPLY_YMCT_RIBBON         = 3,
         SUPPLY_YMCK_RIBBON         = 4,
         SUPPLY_YMCKT_RIBBON        = 5,
         SUPPLY_YMCKK_RIBBON        = 6,
         SUPPLY_YMCKKT_RIBBON       = 7,
         SUPPLY_YMCKTKT_RIBBON      = 8,
         SUPPLY_YMCTKT_RIBBON       = 9,
         SUPPLY_YMCKFKT_RIBBON      = 10,
         SUPPLY_K_RIBBON            = 11,
         SUPPLY_KT_RIBBON           = 12,
         SUPPLY_TONAL_RIBBON        = 13,
         SUPPLY_DARKBLUE_RIBBON     = 14,
         SUPPLY_WHITE_RIBBON        = 15,
         SUPPLY_RED_RIBBON          = 16,
         SUPPLY_SILVER_RIBBON       = 17,
         SUPPLY_SCRATCH_OFF_RIBBON  = 18,
         SUPPLY_GOLD_RIBBON         = 19,
         SUPPLY_GREEN_RIBBON        = 20,
         SUPPLY_HOLOFLECK_RIBBON    = 21,
         SUPPLY_NO_RIBBON           = 22,
         SUPPLY_YMCKT_SHORT_RIBBON  = 23,
         SUPPLY_YMCKTK_RIBBON       = 24,
         SUPPLY_YMCKOP_RIBBON       = 25,
         SUPPLY_YMCKOPK_RIBBON      = 26,
         SUPPLY_YMCKOPKOP_RIBBON    = 27,
		 SUPPLY_KTT_RIBBON          = 28,
   } SUPPLY_RIBBON_TYPES;
   
/* Laminator supply type definitions */
   typedef enum		
   {
	   SUPPLY_MATERIAL_UNKNOWN             = 1,  /* unknown material */

	   /* Magna AIT and ICIV material types */
	   SUPPLY_MATERIAL_PATCH            = 2, 
	   SUPPLY_MATERIAL_TOPCOAT          = 3,

	   /* Other Material types */
	   SUPPLY_MATERIAL_CLEAR_PATCH_0_5  = 4,  /* Patch, 0.5 mil */
	   SUPPLY_MATERIAL_CLEAR_PATCH_1_0  = 5,  /* Patch, 1.0 mil */
	   SUPPLY_MATERIAL_HOLO_PATCH_0_6   = 6,  /* Patch, 0.6 mil Holo */
	   SUPPLY_MATERIAL_HOLO_PATCH_1_0   = 7,  /* Patch, 1.0 mil Holo */
	   SUPPLY_MATERIAL_CLEAR_TOPCOAT    = 8,  /* Topcoat, Clear */
	   SUPPLY_MATERIAL_HOLO_TOPCOAT     = 9,  /* Topcoat, Holo */
	   SUPPLY_MATERIAL_HOLO_REG_TOPCOAT = 10, /* Topcoat, Reg Holo */
	   SUPPLY_MATERIAL_REG_PATCH_0_6    = 11, /* Patch, 0.6 mil Reg */
	   SUPPLY_MATERIAL_REG_PATCH_1_0    = 12, /* Patch, 1.0 mil Reg */
   } LAMINATOR_SUPPLY_MATERIAL_TYPE; 

/*
 * These define mag stripe configuration for the printer.
 */
typedef enum
{

	NTT_BINARY                    = 101,
	MAX_NUMBER_OF_CHARACTERS      = 102,
} MagstripeConfig;

/*
 * This is the track data format that is used by EncodeMagstripe and EncodeMagstripeEx.
 */
typedef struct tagTRACKDATA
{
   UINT nLength;
   BYTE TrackData[MAX_ICE_MS_TRACK_LENGTH];
} TRACKDATA, FAR* LPTRACKDATA;
typedef const LPTRACKDATA LPCTRACKDATA;

#pragma pack(1)
   typedef struct _tagPRINTER_RIBBON_INFO
   {
      DWORD RibbonType;                            /* Ribbon Type */
      BYTE  LotNumber[MAX_LOT_NUMBER_LENGTH];		/* Ribbon Lot Number */ 
      DWORD PartNumber;									   /* Ribbon Part Number */
      DWORD PercentRemaining;                      /* Ribbon percent remaining */
      DWORD tagStatus;                              //status of the tag...programed, empty
   } PRINTER_RIBBON_INFO, FAR* LPPRINTER_RIBBON_INFO;
#pragma pack()
   typedef const LPPRINTER_RIBBON_INFO LPCPRINTER_RIBBON_INFO;
   

#pragma pack(1)
   typedef struct _tagPRINTER_INDENT_RIBBON_INFO
   {
	   DWORD IndenterInstalled;                      /* Indenter installed */
	   DWORD PercentRemaining;                      /* Ribbon percent remaining */
	   DWORD RibbonEncoderCount;                      /* Ribbon encoder count */
	   DWORD PartNumber;						   /* Ribbon Part Number */
   } PRINTER_INDENT_RIBBON_INFO, FAR* LPPRINTER_INDENT_RIBBON_INFO;
#pragma pack()
   typedef const LPPRINTER_INDENT_RIBBON_INFO LPCPRINTER_INDENT_RIBBON_INFO;


#pragma pack(1)		
   typedef struct _tagLAMINATOR_SUPPLY_MATERIAL_INFO
   {
      DWORD StationInstalled;							/* 0 = station not installed, 1 = station installed */
      DWORD MaterialType;                       /* Laminator material Type */
      BYTE  LotNumber[MAX_LOT_NUMBER_LENGTH];	/* Laminator material Lot Number */
      DWORD PartNumber;                         /* Laminator material Part Number */    
      DWORD Maximumlength;                      /* Laminator material maximum length in mm */
      DWORD CurrentLength;                      /* Laminator merial current length in mm */
   } LAMINATOR_SUPPLY_MATERIAL_INFO, FAR* LPLAMINATOR_SUPPLY_MATERIAL_INFO;
#pragma pack()
   typedef const LPLAMINATOR_SUPPLY_MATERIAL_INFO LPCLAMINATOR_SUPPLY_MATERIAL_INFO;

   // GetIndentRibbonInfo function returns the information about indent ribbon installed in the printer
   // pPrinterName - name of the printer
   // lpRibbonInfo - pointer to a buffer to receive the indent ribbon information
   // If the function fails, the value of LastError will be set to indicate the failure.
   BOOL CRDAPI GetIndentRibbonInfo(LPTSTR lpPrinterName, LPPRINTER_INDENT_RIBBON_INFO lpIndentRibbonInfo );

   // GetRibbonInfo function returns the information about ribbon installed in the printer
   // pPrinterName - name of the printer
   // lpRibbonInfo - pointer to a buffer to receive the ribbon information
   // If the function fails, the value of LastError will be set to indicate the failure.
   BOOL CRDAPI GetRibbonInfo(LPTSTR lpPrinterName, LPPRINTER_RIBBON_INFO lpRibbonInfo );

   // GetLaminatorMaterialInfo function returns the information about laminator material installed in the printer
   // pPrinterName - name of the printer
   // dwLaminatorNumber - Laminator station for which information has to be retrieved. This value can be 1 or 2
   // lpMaterialInfo - pointer to a buffer to receive the laminator material information
   // If the function fails, the value of LastError will be set to indicate the failure.
   BOOL CRDAPI GetLaminatorMaterialInfo(LPTSTR lpPrinterName, DWORD dwLaminatorNumber, 
      LPLAMINATOR_SUPPLY_MATERIAL_INFO lpMaterialInfo );
   

   // GetClearCardStatus function returns the clear card status for a particular Datacard printer,
   // pPrinterName - name of the printer
   // pClearCardStatus  - Pointer to a Byte containing status
   // If the function fails, the value of LastError will be set to indicate the failure.
   BOOL CRDAPI GetClearCardStatus(LPTSTR lpPrinterName, LPBYTE pClearCardStatus);

   // SetMagstripeConfiguration function sets a magstripe parameter.

   // pPrinterName - name of the printer
   // HDC - Handle to device Context
   // dwTrackNumber - Track number
   // dwConfigID - Magstripe configuration to be sent to the printer. See MagstripeConfig 
   //              data structure for supported magstripe configuration ID's.
   // dwConfigValue - Value of the configusrtion ID to be sent to the printer.  
   // dwCoercivity - Coercivity value for all tracks.
   BOOL CRDAPI SetMagstripeConfiguration(LPTSTR lpPrinterName, HDC hDC, DWORD dwTrackNumber, 
										DWORD dwConfigID, DWORD dwConfigValue, DWORD dwCoercivity);

   // EncodeMagstripeEx function encodes the magnetic stripe on a card.
   // HDC - Handle to device Context
   // pTrack1 - Address of structure to encode data on track1
   // pTrack2 - Address of structure to encode data on track2
   // pTrack3 - Address of structure to encode data on track3
   // pTrack4 - Reserved. Must be NULL.
   BOOL CRDAPI EncodeMagstripeEx(HDC hDC, LPCTRACKDATA  pTrack1, LPCTRACKDATA  pTrack2, LPCTRACKDATA  pTrack3, LPCTRACKDATA  pTrack4);
	
   // Causes a Cleaning Laminator cycle to be executed.
   BOOL CRDAPI CleanLaminatorModules (LPTSTR pPrinterName);

#pragma pack(1)
   typedef struct tagINDENT_TRACK
   {
	   UINT length;
	   UINT Xlocation;
	   UINT Ylocation;
	   BYTE pindentData[50];
   } INDENT_TRACK , FAR* LPINDENT_TRACK;

   typedef struct tagINDENT_INFO
   {
	   INDENT_TRACK indent;

   } INDENT_INFO, FAR* LPINDENT_INFO;
#pragma pack()

/*
 * SendIndentData
*/
BOOL CRDAPI SendIndentData(HDC /*hDC*/, LPINDENT_TRACK);


#if defined _UNICODE || defined UNICODE
#define GetCardPrinterIndenterStatus GetCardPrinterIndenterStatusW
#else // UNICODE
#define GetCardPrinterIndenterStatus GetCardPrinterIndenterStatusA
#endif // UNICODE

// pPrinterName - name of the printer
DWORD CRDAPI GetCardPrinterIndenterStatus (LPTSTR pPrinterName);

/* End of 'extern "C" {' definition */
#ifdef __cplusplus
};
#endif


#endif /* #ifndef __CRD_API_H__ */
