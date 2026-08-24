/****************************************************************************
 *
 *  $Workfile: ICE_API.h $
 *  Copyright (c) 1997 DataCard Corporation.  All Rights Reserved.
 *
 ****************************************************************************
 *
 *  $Archive: /Driver/NT/include/ICE_API.h $
 *  $Revision: 17 $
 *  $Date: 6/18/06 2:54p $
 *  Created by: Hans Erickson
 *  Modified by: $Author: Agarwas $
 *
 *  Description:
 *    This file contains the implementation of the ICE API.
 *
 ***$Nokeywords:$************************************************************/

/*
 * Copyright 1997 DataCard Corp.
 *
 */
  
#ifndef __ICE_API_H__
#define __ICE_API_H__

/* This will cause this file to be imported correctly into C++ files */
#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32 /* always defined for Win32 applications */
#include <wtypes.h> /* for SYSTEMTIME */
#ifndef ICEAPI
#define ICEAPI	__declspec( dllimport ) WINAPI
#endif
#ifndef ICEVAR
#define ICEVAR	__declspec( dllimport )
#endif
#else /* we're compiling for Win16 */
#ifndef ICEAPI
#define  ICEAPI   __export WINAPI
#endif
#ifndef ICEVAR
#define  ICEVAR   __export
#endif
#endif

#ifdef UNICODE
#define __UnformatNTT __UnformatNTTA  

#else
#define __UnformatNTT __UnformatNTTA

#endif // UNICODE
/*
 * These functions provide functionality for converting and formatting
 * magstripe strings for the given track type.
 */
#ifndef NO_ICE_STRINGS

#ifdef UNICODE
#define MS_FORMAT_IATA(trk, str) {char tmp[MAX_ICE_MS_TRACK_LENGTH*3]; char* p = (char*)trk.TrackData;\
                                  trk.nLength = wcstombs(tmp, str, MAX_ICE_MS_TRACK_LENGTH);\
                                  memmove (trk.TrackData, (LPBYTE)tmp, MAX_ICE_MS_TRACK_LENGTH);\
                                  while (*p) {*p = toupper(*p); p++;}}
#define MS_FORMAT_ABA(trk, str) {char tmp[MAX_ICE_MS_TRACK_LENGTH*3]; char* p = (char*)trk.TrackData;\
                                  trk.nLength = wcstombs(tmp, str, MAX_ICE_MS_TRACK_LENGTH);\
                                  memmove (trk.TrackData, (LPBYTE)tmp, MAX_ICE_MS_TRACK_LENGTH);}
#define MS_FORMAT_TTS(trk, str) {char tmp[MAX_ICE_MS_TRACK_LENGTH*3]; char* p = (char*)trk.TrackData;\
                                  trk.nLength = wcstombs(tmp, str, MAX_ICE_MS_TRACK_LENGTH);\
                                  memmove (trk.TrackData, (LPBYTE)tmp, MAX_ICE_MS_TRACK_LENGTH);}
#define MS_FORMAT_NTT(trk, str) {char tmp[MAX_ICE_MS_TRACK_LENGTH*3]; char* p = (char*)trk.TrackData;\
                                  trk.nLength = wcstombs(tmp, str, MAX_ICE_MS_TRACK_LENGTH);\
                                  memmove (trk.TrackData, (LPBYTE)tmp, MAX_ICE_MS_TRACK_LENGTH);}
#else
#define MS_FORMAT_IATA(trk, str) {char* p = (char*)trk.TrackData; trk.nLength = strlen(str); strcpy((char*)trk.TrackData, str);\
                                  while (*p) {*p = toupper(*p); p++;}}
#define MS_FORMAT_ABA(trk, str) {char* p = (char*)trk.TrackData; trk.nLength = strlen(str); strcpy((char*)trk.TrackData, str);}
#define MS_FORMAT_TTS(trk, str) {char* p = (char*)trk.TrackData; trk.nLength = strlen(str); strcpy((char*)trk.TrackData, str);}
#define MS_FORMAT_NTT(trk, str) {char* p = (char*)trk.TrackData; trk.nLength = strlen(str); strcpy((char*)trk.TrackData, str);}
#endif // UNICODE

#endif // NO_ICE_STRINGS

#include "CRD_API.h"

/* Global variable definitions */
extern HINSTANCE ICEVAR __hResInstance;

/* Macro definitions */
#define TRACK1_FONT_NAME TEXT("Track 1 - Magnetic stripe")
#define TRACK2_FONT_NAME TEXT("Track 2 - Magnetic stripe")
#define TRACK3_FONT_NAME TEXT("Track 3 - Magnetic stripe")
#define TRACKJ_FONT_NAME TEXT("Track NTT - Magnetic stripe")

#define TOP_COAT_ON_BRUSH  BLACK_BRUSH
#define TOP_COAT_OFF_BRUSH WHITE_BRUSH 

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

/*
 * These define mag stripe track density(Encoded bits per
 * inch of magnetic stripe media) for the printer.
 */
typedef enum
{
   ICE_MS_DEFAULT_DENSITY  = 0,
   ICE_MS_75               = 75,
   ICE_MS_210              = 210,
} IceDensityType;

/*
 * These define mag stripe track char length(Encoded data bits
 * per character) for the printer.
 */
typedef enum
{
   ICE_MS_DEFAULT_CHARLEN = 0,
   ICE_MS_CHAR_1       = 1,
   ICE_MS_CHAR_2       = 2,
   ICE_MS_CHAR_3       = 3,
   ICE_MS_CHAR_4       = 4,
   ICE_MS_CHAR_5       = 5,
   ICE_MS_CHAR_6       = 6,
   ICE_MS_CHAR_7       = 7,
   ICE_MS_CHAR_8       = 8,
} IceCharType;

/*
 * MAGSTRIPE_LRC
 *
 */
typedef enum
{
    ICE_MS_DEFAULT_LRC = 0,
    ICE_MS_NONE_LRC = 1,
    ICE_MS_EVEN_LRC = 2,
    ICE_MS_ODD_LRC = 3,	
} MAGSTRIPE_LRC;

/*
* MAGSTRIPE_PARITY
*
*/
typedef enum
{
    ICE_MS_DEFAULT_PARITY = 0,
    ICE_MS_NONE_PARITY = 1,
    ICE_MS_EVEN_PARITY = 2,
    ICE_MS_ODD_PARITY = 3	
} MAGSTRIPE_PARITY;

typedef enum
{
    ICE_DEFAULT_SETMASK = 0x00,
	ICE_DEFAULT_SETMASK_210	=  0x20,	// 6 bits per char NOT RELATED TO BPI (DENSITY)
	ICE_DEFAULT_SETMASK_75	 = 0x30,		// 4 bits per char NOT RELATED TO BPI (DENSITY)
    ICE_MAXIMUM_SETMASK = 0xff
} MAGSTRIPE_SETMASK;

typedef enum
{
    ICE_DEFAULT_CHAR = 0x100,
    ICE_HIGH_CHAR =	0xff,
    ICE_LOW_CHAR = 	0x00
} MAGSTRIPE_CHARS;


/*
 * These define mag stripe track start sentinal adjustment.
 */
typedef enum
{
   ICE_MS_DEFAULT_SSA = 0,
   ICE_MS_MINIMUM_SSA = 20,
   ICE_MS_MAXIMUM_SSA = 500,
} IceSSAType;

/*
 * These define maximum number of encodable data characters on a Track.
 */
typedef enum
{
   ICE_MS_DEFAULT_MAXCHARS = 0,
} IceMaxChars;

typedef enum
{
   ICE_MS_DEFAULT_SENTINEL = 256,
} IceSentinels;

/*
 * These specify mag stripe coercivities.
 */
typedef enum
{
   ICE_MS_COERCIVITY_NO_CHANGE  = 0,
   ICE_MS_COERCIVITY_HICO       = 1,
   ICE_MS_COERCIVITY_LOCO       = 2,
   ICE_MS_COERCIVITY_50mA       = 3,
   ICE_MS_COERCIVITY_75mA       = 4,
   ICE_MS_COERCIVITY_100mA      = 5,
   ICE_MS_COERCIVITY_RESERVED0  = 6,
   ICE_MS_COERCIVITY_RESERVED1  = 7,
   ICE_MS_COERCIVITY_RESERVED2  = 8,
   ICE_MS_COERCIVITY_RESERVED3  = 9,
   
   ICE_MS_COERCIVITY_USE_DRIVER = 10
} IceCoercivityType;


#ifndef _CARDSTAT_H_
#pragma pack(1)
typedef struct {
   DWORD JobId; 
   DWORD CardNum;
   HANDLE hPrinter;
}CARDIDTYPE, FAR *LPCARDIDTYPE;
#pragma pack()

typedef struct {
   BOOL        bActive; /* TRUE until card has been printed or cancelled */
   BOOL        bSuccess; /* TRUE if card printed successfully. 
                           Not valid until Active field is FALSE. */
} CARD_INFO_1, *PCARD_INFO_1, FAR *LPCARD_INFO_1;

#ifdef _WIN32
typedef struct {
   DWORD       dwCopiesPrinted; /* for cards with multiple copies */
   DWORD       dwRemakeAttempts;
   SYSTEMTIME  TimeCompleted;
} CARD_INFO_2, *PCARD_INFO_2, FAR *LPCARD_INFO_2;
#endif
#endif


typedef struct {
   DWORD dwTrackBPI;       // Track density 
   DWORD dwTrackBPC;       // Track character length. No. of encoded data bits per character 
} MAGSTRIPE_TRACK_INFO_1, *PCARD_MAGSTRIPE_TRACK_1, FAR *LPMAGSTRIPE_TRACK_INFO_1;

typedef struct {
   DWORD dwTrackBPI;       // Track density
   DWORD dwTrackBPC;       // Track character length. No. of encoded data bits per character
   DWORD dwTrackSSA;       // Track start sentinal adjustment
   DWORD dwTrackMaxChars;  // maximum number of encodable data characters on a Track
} MAGSTRIPE_TRACK_INFO_2, *PCARD_MAGSTRIPE_TRACK_2, FAR *LPMAGSTRIPE_TRACK_INFO_2;

typedef struct {
   DWORD dwTrackBPI;       // Track density
   DWORD dwTrackBPC;       // Track character length. No. of encoded data bits per character
   DWORD dwTrackSSA;       // Track start sentinal adjustment
   DWORD dwTrackMaxChars;  // maximum number of encodable data characters on a Track
   DWORD dwTrackLRC;			// Track commulative parity check	
   DWORD dwTrackCharParity;			// Track vertical Parity
   DWORD dwTrackStartSentinel;	// Track start sentenial
   DWORD dwTrackEndSentinel;	// Track end sentenial
   DWORD dwTrackHighChar;		// Track greatest ordinal value
   DWORD dwTrackLowChar;		// Track least ordinal value
   DWORD dwTrackCharSetMask;	// Track character set differential, (char ssent - mask)
} MAGSTRIPE_TRACK_INFO_3, *PCARD_MAGSTRIPE_TRACK_3, FAR *LPMAGSTRIPE_TRACK_INFO_3;

typedef struct {
   DWORD dwTrackBPI;       // Track density
   DWORD dwTrackBPC;       // Track character length. No. of encoded data bits per character
   DWORD dwTrackSSA;       // Track start sentinal adjustment
   DWORD dwTrackMaxChars;  // maximum number of encodable data characters on a Track
   DWORD dwTrackLRC;			// Track commulative parity check	
   DWORD dwTrackCharParity;			// Track vertical Parity
   DWORD dwTrackStartSentinel;	// Track start sentenial
   DWORD dwTrackEndSentinel;	// Track end sentenial
   DWORD dwTrackHighChar;		// Track greatest ordinal value
   DWORD dwTrackLowChar;		// Track least ordinal value
   DWORD dwTrackCharSetMask;	// Track character set differential, (char ssent - mask)
   DWORD dwNumberOfStartSentinels; // number of StartSentinels for SDS encoding
   DWORD dwNumberOfRecords;        // number of times data is repeated for SDS encoding
   DWORD dwNumberOfNulls;          // number of null (gap) characters for SDS encoding
} MAGSTRIPE_TRACK_INFO_4, *PCARD_MAGSTRIPE_TRACK_4, FAR *LPMAGSTRIPE_TRACK_INFO_4;


typedef struct {      
   DWORD winJobID;                /* windows Job ID */
   DWORD prnJobId;                /* printer Job ID */
   DWORD cardNum;                 /* 0 based card number within a job */
   DWORD copyNum;                 /* 0 based copy number within a job */
} CARD_PRINTER_JOB_INFO_1, *PCARD_PRINTER_JOB_INFO_1, FAR *LPCARD_PRINTER_JOB_INFO_1;


typedef struct {
   LPSTR ErrorNumber;           /* Error Number */
   LPSTR ErrorString; 	         /* Description of the error */
   LPSTR ResolutionString;      /* Description of the resolution for the error. */
   DWORD HelpID;                 /* help identifier for the error */
} CARD_ERROR_INFO_1_A, *PCARD_ERROR_INFO_1_A, FAR *LPCARD_ERROR_INFO_1_A;

#ifndef HOST_16BIT
typedef struct {
   LPWSTR ErrorNumber;           /* Error Number */
   LPWSTR ErrorString; 	         /* Description of the error */
   LPWSTR ResolutionString;      /* Description of the resolution for the error. */
   DWORD HelpID;                 /* help identifier for the error */
} CARD_ERROR_INFO_1_W, *PCARD_ERROR_INFO_1_W, FAR *LPCARD_ERROR_INFO_1_W;
#endif

enum CommandType
{
   ABORT_CARD, 
   ABORT_CARD_NO_EJECT,
   ABORT_ALL_CARDS,
   RESUME_CARD,
   RESTART_PRINTER
};

#if defined _UNICODE || defined UNICODE
#define CARD_ERROR_INFO_1 CARD_ERROR_INFO_1_W
#define PCARD_ERROR_INFO_1 PCARD_ERROR_INFO_1_W
#define LPCARD_ERROR_INFO_1 LPCARD_ERROR_INFO_1_W
#define GetCardPrinterErrors GetCardPrinterErrorsW
#define GetCardPrinterStatus GetCardPrinterStatusW
#define ClearAllCardErrors ClearAllCardErrorsW
#define DisplayCardError DisplayCardErrorW
#define GetHelpFileName GetHelpFileNameW
#define SendPrinterCommand SendPrinterCommandW
#define RunFirmwareUpdateUtility RunFirmwareUpdateUtilityW
#define CleanCardPrinter CleanCardPrinterW
#define GetInputHopperStatus GetInputHopperStatusW
#define IsDatacardPrinter IsDatacardPrinterW
#define GetDriverClassEx GetDriverClassExW


#else
#define CARD_ERROR_INFO_1 CARD_ERROR_INFO_1_A
#define PCARD_ERROR_INFO_1 PCARD_ERROR_INFO_1_A
#define LPCARD_ERROR_INFO_1 LPCARD_ERROR_INFO_1_A
#define GetCardPrinterErrors GetCardPrinterErrorsA
#define GetCardPrinterStatus GetCardPrinterStatusA
#define ClearAllCardErrors ClearAllCardErrorsA
#define DisplayCardError DisplayCardErrorA
#define GetHelpFileName GetHelpFileNameA
#define SendPrinterCommand SendPrinterCommandA
#define RunFirmwareUpdateUtility RunFirmwareUpdateUtilityA
#define CleanCardPrinter CleanCardPrinterA
#define GetInputHopperStatus GetInputHopperStatusA
#define IsDatacardPrinter IsDatacardPrinterA
#define GetDriverClassEx GetDriverClassExA

#endif // UNICODE

/* Function definitions */

/*
 * SetTopCoatMode
 */
BOOL ICEAPI SetTopCoatMode(HDC /*hDC*/, BOOL /*bEnable*/);

/*
 * RotateCardSide
 */
BOOL ICEAPI RotateCardSide(HDC /*hDC*/, BOOL /*bRotate*/);

/*
 * SetMagstripeFormat
 */
BOOL ICEAPI SetMagstripeFormat(HDC /*hDC*/,
                               DWORD /*dwTrackFormat*/,
                               DWORD /*dwCoercivity*/);
 
/*
 * SetCustomMagstripeFormat
 */
BOOL ICEAPI SetCustomMagstripeFormat(HDC /*hDC*/,
                                    DWORD    /*level*/,
                                    LPBYTE   /*pTrackInfo1*/,
                                    LPBYTE   /*pTrackInfo2*/,
                                    LPBYTE   /*pTrackInfo3*/,
                                    DWORD    /*cbBuf - size of structure pointed to by pTrackInfo1,
                                                pTrackInfo2,pTrackInfo3 */,
                                    LPDWORD  /*pcbNeeded - Points to a value that specifies the 
                                                number of bytes required if cbBuf is too small. */,
                                    DWORD    /*dwBaseTrackFormat*/,
                                    DWORD    /*dwCoercivity*/);

/*
 * EncodeMagstripe
 */
BOOL ICEAPI EncodeMagstripe(HDC /*hDC*/,
			     LPCTRACKDATA /*pTrack1*/,
			     LPCTRACKDATA /*pTrack2*/,
			     LPCTRACKDATA /*pTrack3*/,
			     LPCTRACKDATA /*reserved*/);

/*
 * ReadMagstripe
 */
BOOL ICEAPI ReadMagstripe(HDC /*hDC*/,
			   LPTRACKDATA /*pTrack1*/,
			   LPTRACKDATA /*pTrack2*/,
			   LPTRACKDATA /*pTrack3*/,
			   LPTRACKDATA /*reserved*/);

/*
 * SetInteractiveMode
 */
BOOL ICEAPI SetInteractiveMode(HDC /*hDC*/,
                               BOOL /*bEnable*/);

/*
 * SmartCardContinue
 */
BOOL ICEAPI SmartCardContinue(HDC /*hDC*/, DWORD /*dwCommand*/);

/*
 * FeedCard
 */
BOOL ICEAPI FeedCard(HDC /*hDC*/,
                     DWORD /*dwCardData*/);


BOOL ICEAPI GetCardId(HDC hdc, LPCARDIDTYPE pCardId);
BOOL ICEAPI GetCardStatus(CARDIDTYPE CardId, DWORD level, LPBYTE pData,
                   DWORD cbBuf, LPDWORD pcbNeeded );


BOOL ICEAPI GetCardPrinterErrors (LPTSTR lpPrinterName,DWORD level,LPCARD_ERROR_INFO_1 lpbErrorInfo, 
                                    DWORD cbBuf, LPDWORD lpdwNeeded,LPDWORD lpdwError);
BOOL ICEAPI GetCardPrinterStatus (LPTSTR lpPrinterName, DWORD level,LPCARD_PRINTER_JOB_INFO_1 lpbJobStatus,
                                DWORD cbBuf, LPDWORD lpdwNeeded,LPDWORD lpdwActiveJobs);
BOOL ICEAPI ClearAllCardErrors (LPTSTR lpPrinterName);
BOOL ICEAPI DisplayCardError (LPTSTR lpPrinterName, BOOL bDisplay);
BOOL ICEAPI GetHelpFileName (LPTSTR lpPrinterName, LPTSTR lpHelpFileName,DWORD  cbBuf, LPDWORD lpdwNeeded);
BOOL ICEAPI SendPrinterCommand (LPTSTR lpPrinterName, DWORD dwPrnJobId,DWORD dwCommand);

BOOL ICEAPI __UnformatNTTA(LPCTRACKDATA pTrackJIn, LPTRACKDATA pTrackJOut);

/* Macro definitions */

/*
 * The "ICE_RES" macro can be used in a "FormatMessage" function to get the proper language
 * version
 */
HINSTANCE ICEAPI __GetIceResInstance();
#define ICE_RES __GetIceResInstance()

/*
 * The "ICE_LAST_ERROR()" macro should be used with the value returned by "GetLastError",
 * which can be used in the "FormatMessage" function.  If the value returned by this macro
 * is zero, then the error is a system level.  Otherwise, it is an ICE error, and
 * "FormatMessage" should be used with the "FORMAT_MESSAGE_FROM_HMODULE" argument.
 */
#define ICE_LAST_ERROR(x)	((x & APPLICATION_ERROR_MASK)?(x & ~(APPLICATION_ERROR_MASK | ERROR_SEVERITY_ERROR)):0)


/***************************************************************************
GetCardPrinterInfo() functions
****************************************************************************/

#if defined(UNICODE) | defined(_UNICODE)
#define GetCardPrinterInfo GetCardPrinterInfoW
#define GetCardPrinterPollingState GetCardPrinterPollingStateW
#define GetCardPrinterPollingStateEx GetCardPrinterPollingStateExW
#define ResumePrinterPolling ResumePrinterPollingW

#else // UNICODE
#define GetCardPrinterInfo GetCardPrinterInfoA
#define GetCardPrinterPollingState GetCardPrinterPollingStateA
#define GetCardPrinterPollingStateEx GetCardPrinterPollingStateExA
#define ResumePrinterPolling ResumePrinterPollingA

#endif // UNICODE


BOOL ICEAPI GetCardPrinterInfo (LPTSTR pPrinterName, DWORD dwInfoType,
                         LPBYTE pCardPrinterInfo, DWORD cbBuf, 
                         LPDWORD lpcbData);
// pPrinterName - name of the printer
// dwInfoType - selects the desired type of information
// pCardPrinterInfo - points to a buffer, provided by caller, to receive the information
// cbBuf - Length of the buffer provided by caller
// lpcbData - pointer to a DWORD to receive the length of the requested information.

// If the function fails, the LastError value will indicate the cause of failure.
// For values of dwInfoType other than CARD_PRINTER_INFO_TYPE_MODEL, the driver
// must be in communication with the printer to obtain the requested information.
//  Otherwise, an API error will be returned in LastError.

// The contents and size of the returned data are specified as follows,
// for each enumerated value of the dwInfoType parameter:

enum GET_CARD_PRINTER_INFO_TYPES
{
   CARD_PRINTER_INFO_TYPE_MODEL = 1,
//	Gives the Model information for the printer
   CARD_PRINTER_INFO_TYPE_BASIC,
//	Returns information specific to the attached printer:
   CARD_PRINTER_INFO_TYPE_CLEANING,
// Returns information about cleaning capabilities of the printer.	 
   CARD_PRINTER_INFO_TYPE_MAGSTRIPE,
//	Returns information on each magstripe station in the printer.
   CARD_PRINTER_INFO_TYPE_SMARTCARD,
//	Returns information on each SmartCard station in the printer.
   CARD_PRINTER_INFO_TYPE_TOPCOAT,
//	Returns information on each Topcoat or Overlay station in the printer.
   CARD_PRINTER_INFO_TYPE_CARD_COUNT
//	Returns information on each Topcoat or Overlay station in the printer.
};

typedef struct _tagCARD_PRINTER_INFO_MODEL
{
	LPTSTR   PrinterModel;
	LPTSTR   DriverVersion;
	BOOL		EdgeToEdgeSupported;
} CARD_PRINTER_INFO_MODEL;

typedef struct _tagCARD_PRINTER_INFO_BASIC
{
	BOOL		ColorSupported;
	BOOL		ManualDuplexSupported;
	BOOL		AutoDuplexSupported;
	LPTSTR	SerialNumber;
	DWORD		FirmwareMajorVersion;
	DWORD		FirmwareMinorVersion;
	DWORD		PreferredFirmwareMajorVersion;
	DWORD		PreferredFirmwareMinorVersion;
} CARD_PRINTER_INFO_BASIC;


typedef struct _tagCLEANING_INFO
{
	BOOL		AutoCleaningSupported;
	DWORD		IntervalSetting;
	DWORD		MinimumRecommendedInterval;
	DWORD		MaximumRecommendedInterval;
	DWORD		CountSinceLastCleaning;
} CARD_PRINTER_INFO_CLEANING;

typedef struct tagMAGSTRIPE_STATION_INFO
{
   BOOL        bInstalled;
   BOOL        bEnabled;
   DWORD       MagstripeUnitType;
} MAGSTRIPE_STATION_INFO;

typedef struct tagCARD_PRINTER_INFO_MAGSTRIPE
{
	DWORD			            MagstripeUnitCount;
	MAGSTRIPE_STATION_INFO	MagstripeUnits[1];
} CARD_PRINTER_INFO_MAGSTRIPE;

typedef struct tagSMARTCARD_STATION_INFO
{
   BOOL        bInstalled;
   BOOL        bEnabled;
} SMARTCARD_STATION_INFO;

typedef struct tagCARD_PRINTER_INFO_SMARTCARD
{
	DWORD			            SmartcardUnitCount;
	SMARTCARD_STATION_INFO  SmartcardUnits[1];
} CARD_PRINTER_INFO_SMARTCARD;


typedef struct tagCARD_PRINTER_INFO_TOPCOAT_OVERLAY
{
	DWORD			         TopcoatOverlayUnitCount;
	DWORD             	TopcoatOverlayUnitTypes[1];
} CARD_PRINTER_INFO_TOPCOAT_OVERLAY;

typedef struct tagCARD_PRINTER_INFO_CARD_COUNT
{
	DWORD			         PrinterCycleCount;
	DWORD             	PrinterCardCount;         /* Non-ICIV only */
   DWORD                PrintHeadCycleCount;
   DWORD                CurrHeadCycleCount;
   DWORD                CurrUncleanCycleCount;    /* Non-ICIV only */
   DWORD                MaxUncleanCycleCount;     /* Non-ICIV only */
   DWORD                PickedCardCount;          /* ICIV only */
   DWORD                CurrPickedCardCount;      /* ICIV only */
   DWORD                GoodCardCount;            /* ICIV only */
   DWORD                CurrGoodCardCount;        /* ICIV only */
   DWORD                RejectCardCount;          /* ICIV only */
   DWORD                CurrRejectCardCount;      /* ICIV only */
   DWORD                LostCardCount;            /* ICIV only */
   DWORD                CurrLostCardCount;        /* ICIV only */
   DWORD                CyclesWithoutParticle;    /* ICIV only */
} CARD_PRINTER_INFO_CARD_COUNT, FAR *LPCARD_PRINTER_INFO_CARD_COUNT;

//
// Option stations types
//
typedef enum
{
   OPTIONSTATION_NOT_INSTALLED = 1,
   OPTIONSTATION_NOT_ENABLED,
   OPTIONSTATION_TOPCOAT,
   OPTIONSTATION_OVERLAY
} TOPCOATOVERLAY_UNIT_TYPES;

// Magstripe head types for MAGSTRIPE_STATION_INFO
enum MAGSTRIPE_UNIT_TYPE
{
	MSTYPE_IAT = 1,
	MSTYPE_NTT = 2
};


typedef enum
{
   DONOTAPPLY,
   FRONTSIDE,
   BACKSIDE,
   BOTHSIDES,
   FRONTSIDETWICE
} SET_MATERIAL_APPLY_SETTINGS;

/*
 * SetApplyMaterialSetting
 */
BOOL ICEAPI SetApplyMaterialSetting(HDC hdc, DWORD dwSetting, DWORD dwOptionNum );



enum PollingState
{
   STATE_RESPONDING,
   STATE_NOT_RESPONDING,
   STATE_SUSPENDED,
   STATE_BUSY,                   //only returned by GetPollingStatusEx
   STATE_NETWORK_NOT_RESPONDING, //only returned by GetPollingStatusEx
};

/***************************************************************************
  End of GetCardPrinterInfo() functions
****************************************************************************/


BOOL ICEAPI GetCardPrinterPollingState (LPTSTR pPrinterName, LPDWORD pPollingState);
// pPrinterName - name of the printer
// pPollingState - pointer to receive the DWORD value of the polling state.
// If the function fails, the value of LastError will be set to indicate the failure.

BOOL ICEAPI GetCardPrinterPollingStateEx (LPTSTR pPrinterName, LPDWORD pPollingState);
// pPrinterName - name of the printer
// pPollingState - pointer to receive the DWORD value of the extended polling state.
// If the function fails, the value of LastError will be set to indicate the failure.


BOOL ICEAPI ResumePrinterPolling (LPTSTR pPrinterName, BOOL bResumePolling);
// pPrinterName - name of the printer
// bResumePolling - BOOL value to resume or suspend polling
// If the function fails, the value of LastError will be set to indicate the failure. 

DWORD ICEAPI PrinterAPIMajorVersion();
// This function returns the major version number of ice_api.dll

DWORD ICEAPI PrinterAPIMinorVersion();
// This function returns the minor version number of ice_api.dll

BOOL ICEAPI RunFirmwareUpdateUtility (LPTSTR pPrinterName);
// Starts the firmware update utility.

BOOL ICEAPI CleanCardPrinter (LPTSTR pPrinterName);
// Causes a Cleaning Card cycle to be executed.

/***************************************************************************
 "hopper empty" detection functionality
****************************************************************************/

enum INPUT_HOPPER_STATUS
{
   REQUEST_NOT_SUPPORTED,
   INPUT_HOPPER_NOT_EMPTY,
   INPUT_HOPPER_IS_EMPTY
};

DWORD ICEAPI GetInputHopperStatus(LPTSTR pPrinterName);

/***************************************************************************
  End of "hopper empty" detection functionality
****************************************************************************/

BOOL ICEAPI IsDatacardPrinter(LPTSTR pPrinterName);
DWORD ICEAPI GetDriverClassEx(LPTSTR pPrinterName);

/* End of 'extern "C" {' defintion */
#ifdef __cplusplus
};
#endif


#endif /* #ifndef __ICE_API_H__ */
