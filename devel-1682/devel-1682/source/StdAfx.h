// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__3811CD50_B7B0_42B9_9E73_805A91708537__INCLUDED_)
#define AFX_STDAFX_H__3811CD50_B7B0_42B9_9E73_805A91708537__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


// Insert your headers here
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <windows.h>

#define DUT_API extern "C" __declspec(dllexport)
#include <string>
using namespace std;
#include "usertype.h"
#include "userres.h"
#include "inireader.h"
#include "treg.h"
#include "SPEC.h"
#include "sub.h"
#include "ATEregisters.h"
#include "BoardCheck.h"

#define I2C_ADDR_DEVICE  0xC0//// for Bowplus device
#define I2C_TRIM_BANK 0x80

#define K0_DIO3_INTB      0, 32, 64, 96, 128+0, 128+32, 128+64, 128+96
#define K1_AC_CAP         1, 33, 65, 97, 128+1, 128+33, 128+65, 128+97
#define K2_VRECT_V5V_CAP  2, 34, 66, 98, 128+2, 128+34, 128+66, 128+98
#define K3_VOUT_CAP       3, 35, 67, 99, 128+3, 128+35, 128+67, 128+99
#define K4_IIC_PULLUP     4, 36, 68, 100, 128+4, 128+36, 128+68, 128+100
#define K5_DIO2_ENB       5, 37, 69, 101, 128+5, 128+37, 128+69, 128+101
#define K6_INTB_PULLUP    6, 38, 70, 102, 128+6, 128+38, 128+70, 128+102
#define K7_SINK_PULLUP    7, 39, 71, 103, 128+7, 128+39, 128+71, 128+103
#define K8_OVI4_AC1_SCL   8, 40, 72, 104, 128+8, 128+40, 128+72, 128+104
#define K9_OVI5_AC2_SDA   9, 41, 73, 105, 128+9, 128+41, 128+73, 128+105
#define K10_OVI6_ENB_COMM1  10, 42, 74, 106, 128+10, 128+42, 128+74, 128+106
#define K11_OVI7_VOUT_COMM2 11, 43, 75, 107, 128+11, 128+43, 128+75, 128+107
#define K12_PVI0H_VRECT   12, 44, 76, 108, 128+12, 128+44, 128+76, 128+108
#define K13_PVI0H_PGND    13, 45, 77, 109, 128+13, 128+45, 128+77, 128+109
#define K14_PVI0H_SINK    14, 46, 78, 110, 128+14, 128+46, 128+78, 128+110
#define K15_PVI0L_AC1     15, 47, 79, 111, 128+15, 128+47, 128+79, 128+111
#define K16_PVI0L_AC2     16, 48, 80, 112, 128+16, 128+48, 128+80, 128+112
#define K17_PVI0L_VOUT    17, 49, 81, 113, 128+17, 128+49, 128+81, 128+113
#define K18_PVI0L_V5V     18, 50, 82, 114, 128+18, 128+50, 128+82, 128+114
#define K19_PVI0L_VRECT   19, 51, 83, 115, 128+19, 128+51, 128+83, 128+115
#define K20_PVI0L_COMM2   20, 52, 84, 116, 128+20, 128+52, 128+84, 128+116
#define K21_PGNDF_PGNDS   21, 53, 85, 117, 128+21, 128+53, 128+85, 128+117
#define K22_DIO_EEPROM    22, 54, 86, 118, 128+22, 128+54, 128+86, 128+118
#define K23_QTMU_SINK     23, 55, 87, 119, 128+23, 128+55, 128+87, 128+119
#define K24_QTMU_INTB     24, 56, 88, 120, 128+24, 128+56, 128+88, 128+120
#define K25_QVM_FPVI      25, 57, 89, 121, 128+25, 128+57, 128+89, 128+121
#define K26_BUFF_INTB     26, 58, 90, 122, 128+26, 128+58, 128+90, 128+122
#define K27_PVI0L_COMM1   27, 59, 91, 123, 128+27, 128+59, 128+91, 128+123
#define K_OVI_CHB   K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA, K10_OVI6_ENB_COMM1, K11_OVI7_VOUT_COMM2


extern TREG dut;
extern SPEC spec;
extern DIO_PLUS dioplus;
// TODO: reference additional headers your program requires here

// SERIAL for active site
extern int globalsite;
extern BYTE sitesta[SITE_NUM];
#define SITE globalsite
#define SERIAL \
	StsGetSiteStatus(sitesta, SITE_NUM);  for (globalsite = 0; globalsite < SITE_NUM; globalsite++)  if (sitesta[globalsite])

extern unsigned char ulWriteData[SITE_NUM];
extern string int2str(DWORD n);
extern int Global_FTQC_FLAG;
extern int	TempCharGP;
extern bool DO_TRIM;
extern bool QC;
#define BANK_NUM 11 

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__3811CD50_B7B0_42B9_9E73_805A91708537__INCLUDED_)
