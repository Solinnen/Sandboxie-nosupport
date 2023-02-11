/*
 * Copyright 2004-2020 Sandboxie Holdings, LLC 
 *
 * This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//---------------------------------------------------------------------------
// Sandboxie Driver Globals
//---------------------------------------------------------------------------


#ifndef _MY_DRIVER_H
#define _MY_DRIVER_H

#include "../../SandMan/nosupport.h"


#pragma optimize("y", off)
// HACK ALERT we must fix this 32 vs. 64 bit handle problem.
#pragma warning(disable : 4311)     //  warning C4311: 'type cast': pointer truncation from 'HANDLE' to 'ULONG'
#pragma warning(disable : 4312)     //  warning C4312: 'type cast': conversion from 'ULONG' to 'HANDLE' of greater size
#pragma warning(disable : 4477)     //  warning C4477: 'swprintf' : format string '%s' requires an argument of type 'unsigned short *', but variadic argument 2 has type ''
#pragma warning(disable : 4267)     //  warning C4267: '=': conversion from 'size_t' to 'ULONG', possible loss of data



#include "my_winnt.h"

#include "common/defines.h"
#include "common/list.h"
#include "common/map.h"
#include "common/pool.h"
#include "common/ntproto.h"
#include "log.h"
#include "mem.h"

#define NTSTRSAFE_LIB
#include <ntstrsafe.h>

//---------------------------------------------------------------------------
// Defines
//---------------------------------------------------------------------------


#define DRIVER_WINDOWS_XP       2
#define DRIVER_WINDOWS_2003     3
#define DRIVER_WINDOWS_VISTA    4
#define DRIVER_WINDOWS_7        5
#define DRIVER_WINDOWS_8        6
#define DRIVER_WINDOWS_81       7
#define DRIVER_WINDOWS_10       8

#define DRIVER_BUILD_WINDOWS_10_CU  15063
#define DRIVER_BUILD_WINDOWS_10_FCU 16299

#define TRACE_NONE              0
#define TRACE_ALLOW             1
#define TRACE_DENY              2
#define TRACE_IGNORE            4

#define USE_PROCESS_MAP

#define USE_MATCH_PATH_EX

#define USE_TEMPLATE_PATHS

#define HOOK_WIN32K

//---------------------------------------------------------------------------
// Structures and Types
//---------------------------------------------------------------------------


typedef struct _BOX                 BOX;
typedef struct _CONF_EXPAND_ARGS    CONF_EXPAND_ARGS;
typedef struct _PROCESS             PROCESS;
typedef struct _THREAD              THREAD;
typedef struct _KEY_MOUNT           KEY_MOUNT;


//---------------------------------------------------------------------------
// Function Pointers to Missing Zw Functions
//---------------------------------------------------------------------------


#ifdef OLD_DDK
extern P_NtSetInformationToken          ZwSetInformationToken;
#endif // OLD_DDK

#ifdef _M_ARM64
NTSTATUS Sbie_CallZwServiceFunction_asm(UINT_PTR arg1, UINT_PTR arg2, UINT_PTR arg3, UINT_PTR arg4, UINT_PTR arg5, UINT_PTR arg6, UINT_PTR arg7, UINT_PTR arg8, 
    UINT_PTR arg9, UINT_PTR arg10, UINT_PTR arg11, UINT_PTR arg12, UINT_PTR arg13, UINT_PTR arg14, UINT_PTR arg15, UINT_PTR arg16, UINT_PTR arg17, UINT_PTR arg18, UINT_PTR arg19,
    UINT_PTR svc_num);

extern void*                            Driver_KiServiceInternal;
extern USHORT                           ZwCreateToken_num;
extern USHORT                           ZwCreateTokenEx_num;
#else
extern P_NtCreateToken                  ZwCreateToken;
extern P_NtCreateTokenEx                ZwCreateTokenEx;
#endif

//---------------------------------------------------------------------------
// Functions
//---------------------------------------------------------------------------


NTSTATUS Driver_Api_Unload(PROCESS *proc, ULONG64 *parms);

ULONG Driver_GetRegDword(
    const WCHAR *KeyPath, const WCHAR *ValueName);


//---------------------------------------------------------------------------
// Variables
//---------------------------------------------------------------------------


extern const ULONG tzuk;

extern const WCHAR *Driver_S_1_5_18;
extern const WCHAR *Driver_S_1_5_19;
extern const WCHAR *Driver_S_1_5_20;

extern DRIVER_OBJECT *Driver_Object;

extern WCHAR *Driver_Version;

extern ULONG Driver_OsVersion;
extern ULONG Driver_OsBuild;

extern POOL *Driver_Pool;

extern WCHAR *Driver_RegistryPath;

extern WCHAR *Driver_HomePathDos;
extern WCHAR *Driver_HomePathNt;
extern ULONG  Driver_HomePathNt_Len;

extern const WCHAR *Driver_Sandbox;

extern const WCHAR *Driver_Empty;

//extern const WCHAR *Driver_OpenProtectedStorage;

extern PSECURITY_DESCRIPTOR Driver_PublicSd;
extern PACL Driver_PublicAcl;

extern PSECURITY_DESCRIPTOR Driver_LowLabelSd;

extern volatile BOOLEAN Driver_Unloading;

extern const WCHAR *Key_Registry_Machine;

extern UNICODE_STRING Driver_Altitude;

extern ULONG Process_Flags1;
extern ULONG Process_Flags2;
extern ULONG Process_Flags3;

//---------------------------------------------------------------------------


#endif // _MY_DRIVER_H
