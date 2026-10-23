/*****************************************************************************
*                                                                            *
*       Source title:   F16821.CPP											 *
*                       (xxx Bowplus xxx)									 *
*						(Based on NU1680 commercial part)					 *
*																			 *
*         Written by:   Xina                                                 *
*   Last Modified by:   Xina                                                 *
*               Date:   26/10/22                                             *
*        Current Rev:   01                                                   *
*                                                                            *
*        Description:               									     *
*   Revision History:                                                        *
*                                                                            *
*****************************************************************************/

/*********************************************************************
=====================================================================
NU1682 Final Test Program 25C -- turret 8site -- NU1682 NU1685 NU1687 NU1682A
=====================================================================

Chip ................................. GCNU1682A0
Device ............................... NU1682PCNB, NU1685PCNB, NU1687PCNB, NU1682APCNB
Program Number (Final Test, QC) ...... F16821
Tester ............................... STS8200
F16821 HIB Number (QFN) .............. SU8192, Acco Generic Board
F16821 CIB Number (QFN) .............. DN2000026
F16821 PIB Number .................... N/A
F16821 Probe Card Number ............. N/A
F16821 PBD Number .................... N/A
Mount and Bond ....................... N/A
Test temperature Probe Test .......... 25degC
Test temperature Probe Test QC........ 25degC
Diagnostic Program Number ............ Included in Test Program
Product Engineer ..................... Xina Fu
Test Engineer ........................ Xina Fu
Probe Program written by ........ .....Xina Fu
DIB/PIB Diagnostic Program written by  Xina Fu
DIB/PIB Diagnostic Program checked by  Xina Fu

/***************************************************************************************************************
**********************************************************************************
Program Revision History: 
=========================
Rev   Level	   Originator	   Date	      	Auditor         Date		Testtime/insertion
-----------------------------------------------------------------------------------
00    NPI      Xina         2026.08.18      Dennis       2026.08.18     4.8s/8 site
01    Minor    Xina         2026.10.22      Dennis       2026.10.22     4.8s/8 site
**********************************************************************************
**********************************************************************************
Change History:
===============
00: initial version.
01: 
	1) Add NU1682A device name, different is TRIM_QI_ID=0x11 (QI_ID2.2)
	2) Add NU1682PCNB-ABA0-FT, NU1685PCNB-ABA0-FT, NU1687PCNB-ABA0-FT device name
	3) Add grade-based selection of good units, limit different
	=======================================================================
	| Grade  |     RAC_HS      |     RAC_LS      | TRIM_ISNS_GAIN_STEP0    |
	| bin1   |   HL: 143mohm   |   HL: 62mohm    |       HL: 1.1		   |
	| bin2   |   HL: 160mohm   |   HL: 85mohm    |       HL: 2		       |
	=======================================================================


remark:
1) program update must change PGM_VER
2) STSSetHardwareCheck(FALSE);//量产必须删掉！！！
***************************************************************************************************************/


#include "stdafx.h"
#include <time.h>
#include <math.h> 
#include <stdlib.h>
#include <stdint.h>
//#include "BoardCheck.h"
//#include "sub.h"

//multisite settings should be included here

//#define K0_DIO3_INTB      0, 32, 64, 96, 128+0, 128+32, 128+64, 128+96
//#define K1_AC_CAP         1, 33, 65, 97, 128+1, 128+33, 128+65, 128+97
//#define K2_VRECT_V5V_CAP  2, 34, 66, 98, 128+2, 128+34, 128+66, 128+98
//#define K3_VOUT_CAP       3, 35, 67, 99, 128+3, 128+35, 128+67, 128+99
//#define K4_IIC_PULLUP     4, 36, 68, 100, 128+4, 128+36, 128+68, 128+100
//#define K5_DIO2_ENB       5, 37, 69, 101, 128+5, 128+37, 128+69, 128+101
//#define K6_INTB_PULLUP    6, 38, 70, 102, 128+6, 128+38, 128+70, 128+102
//#define K7_SINK_PULLUP    7, 39, 71, 103, 128+7, 128+39, 128+71, 128+103
//#define K8_OVI4_AC1_SCL   8, 40, 72, 104, 128+8, 128+40, 128+72, 128+104
//#define K9_OVI5_AC2_SDA   9, 41, 73, 105, 128+9, 128+41, 128+73, 128+105
//#define K10_OVI6_ENB_COMM1  10, 42, 74, 106, 128+10, 128+42, 128+74, 128+106
//#define K11_OVI7_VOUT_COMM2 11, 43, 75, 107, 128+11, 128+43, 128+75, 128+107
//#define K12_PVI0H_VRECT   12, 44, 76, 108, 128+12, 128+44, 128+76, 128+108
//#define K13_PVI0H_PGND    13, 45, 77, 109, 128+13, 128+45, 128+77, 128+109
//#define K14_PVI0H_SINK    14, 46, 78, 110, 128+14, 128+46, 128+78, 128+110
//#define K15_PVI0L_AC1     15, 47, 79, 111, 128+15, 128+47, 128+79, 128+111
//#define K16_PVI0L_AC2     16, 48, 80, 112, 128+16, 128+48, 128+80, 128+112
//#define K17_PVI0L_VOUT    17, 49, 81, 113, 128+17, 128+49, 128+81, 128+113
//#define K18_PVI0L_V5V     18, 50, 82, 114, 128+18, 128+50, 128+82, 128+114
//#define K19_PVI0L_VRECT   19, 51, 83, 115, 128+19, 128+51, 128+83, 128+115
//#define K20_PVI0L_COMM2   20, 52, 84, 116, 128+20, 128+52, 128+84, 128+116
//#define K21_PGNDF_PGNDS   21, 53, 85, 117, 128+21, 128+53, 128+85, 128+117
//#define K22_DIO_EEPROM    22, 54, 86, 118, 128+22, 128+54, 128+86, 128+118
//#define K23_QTMU_SINK     23, 55, 87, 119, 128+23, 128+55, 128+87, 128+119
//#define K24_QTMU_INTB     24, 56, 88, 120, 128+24, 128+56, 128+88, 128+120
//#define K25_QVM_FPVI      25, 57, 89, 121, 128+25, 128+57, 128+89, 128+121
//#define K26_BUFF_INTB     26, 58, 90, 122, 128+26, 128+58, 128+90, 128+122
//#define K27_PVI0L_COMM1   27, 59, 91, 123, 128+27, 128+59, 128+91, 128+123
//#define K_OVI_CHB   K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA, K10_OVI6_ENB_COMM1, K11_OVI7_VOUT_COMM2


#define SITE_COUNT	8
//RegisterManager manager;
/*The following code was created for STS PinPlanner,don't modify*/ 
/****STS_PINPLANNER_CODE_BEGIN****/
#define STS_SITE_NUM 8
#define NUM_SITES 8
/****PIN GROUP DEFINITION****/
SPEC spec;
TREG dut;
RegisterManager manager;

string pgs_path;

FOVI VRECT(0, "VRECT");

FOVI V5V(1, "V5V");

FOVI INTB(2, "INTB");

FOVI SINK(3, "SINK");

FOVI AC1(4, "AC1");
FOVI SCL(4, "SCL");

FOVI AC2(5, "AC2");
FOVI SDA(5, "SDA");

FOVI ENB(6, "ENB");
FOVI COMM1(6, "COMM1");

FOVI VOUT(7, "VOUT");
FOVI COMM2(7, "COMM2");

FPVI10 FPVI0(0, "FPVI0");
QTMU_PLUS QTMU(0, "QTMU");
QVM Qvm(0, "Qvm");
DIO_PLUS dioplus;
CBIT128 cbit;

GPFOVI FOVI_ALL("FOVI_ALL", VRECT, V5V, INTB, SINK, AC1, AC2, ENB, VOUT);
GPFOVI FOVI_CHB("FOVI_CHB", SCL, SDA, COMM1, COMM2);
GPFOVI POWER_VRECT_V5V("POWER_VRECT_V5V", VRECT, V5V);


DIO_PLUS_PINGROUP_DEF_REG(IIC_pins)			 // 注册名为”IIC_pins”的管脚分组
"SCL", "SDA"									// 注册向量文件中的管脚
DIO_PLUS_PINGROUP_DEF_REG_END(IIC_pins)      // 结束管脚分组注册


DIO_PLUS_PINGROUP_DEF_REG(SCAN_pins)			 // 注册名为”SCAN_pins”的管脚分组
"SCL", "SDA", "ENB", "INTB"							// 注册向量文件中的管脚
DIO_PLUS_PINGROUP_DEF_REG_END(SCAN_pins)      // 结束管脚分组注册


DIO_PLUS_I2CSITE_DEF_REG(i2c_site1, 0, 0, 1);
DIO_PLUS_I2CSITE_DEF_REG(i2c_site2, 1, 4, 5);
DIO_PLUS_I2CSITE_DEF_REG(i2c_site3, 2, 8, 9);
DIO_PLUS_I2CSITE_DEF_REG(i2c_site4, 3, 12, 13);
DIO_PLUS_I2CSITE_DEF_REG(i2c_site5, 4, 16, 17);
DIO_PLUS_I2CSITE_DEF_REG(i2c_site6, 5, 20, 21);
DIO_PLUS_I2CSITE_DEF_REG(i2c_site7, 6, 24, 25);
DIO_PLUS_I2CSITE_DEF_REG(i2c_site8, 7, 28, 29);
DIO_PLUS::I2CSite *pI2CSites[] = { &i2c_site1, &i2c_site2, &i2c_site3, &i2c_site4, &i2c_site5, &i2c_site6, &i2c_site7, &i2c_site8 };


/****multisite settings should be included here****/
DUT_API void HardWareCfg()
{
	STSSetModuleToSite(MD_FOVI, SITE_1, 0, 1, 2, 3, 4, 5, 6, 7, -1);
	STSSetModuleToSite(MD_FOVI, SITE_2, 8, 9, 10, 11, 12, 13, 14, 15, -1);
	STSSetModuleToSite(MD_FOVI, SITE_3, 16, 17, 18, 19, 20, 21, 22, 23, -1);
	STSSetModuleToSite(MD_FOVI, SITE_4, 24, 25, 26, 27, 28, 29, 30, 31, -1);
	STSSetModuleToSite(MD_FOVI, SITE_5, 32, 33, 34, 35, 36, 37, 38, 39, -1);
	STSSetModuleToSite(MD_FOVI, SITE_6, 40, 41, 42, 43, 44, 45, 46, 47, -1);
	STSSetModuleToSite(MD_FOVI, SITE_7, 48, 49, 50, 51, 52, 53, 54, 55, -1);
	STSSetModuleToSite(MD_FOVI, SITE_8, 56, 57, 58, 59, 60, 61, 62, 63, -1);
	STSSetModuleToSite(MD_QVM, SITE_1, 0, -1);
	STSSetModuleToSite(MD_QVM, SITE_2, 1, -1);
	STSSetModuleToSite(MD_QVM, SITE_3, 2, -1);
	STSSetModuleToSite(MD_QVM, SITE_4, 3, -1);
	STSSetModuleToSite(MD_QVM, SITE_5, 4, -1);
	STSSetModuleToSite(MD_QVM, SITE_6, 5, -1);
	STSSetModuleToSite(MD_QVM, SITE_7, 6, -1);
	STSSetModuleToSite(MD_QVM, SITE_8, 7, -1);
	STSSetModuleToSite(MD_QTMUPLUS, SITE_1, 0, -1);
	STSSetModuleToSite(MD_QTMUPLUS, SITE_2, 1, -1);
	STSSetModuleToSite(MD_QTMUPLUS, SITE_3, 2, -1);
	STSSetModuleToSite(MD_QTMUPLUS, SITE_4, 3, -1);
	STSSetModuleToSite(MD_QTMUPLUS, SITE_5, 4, -1);
	STSSetModuleToSite(MD_QTMUPLUS, SITE_6, 5, -1);
	STSSetModuleToSite(MD_QTMUPLUS, SITE_7, 6, -1);
	STSSetModuleToSite(MD_QTMUPLUS, SITE_8, 7, -1);
	STSSetModuleToSite(MD_FPVI10, SITE_1, 0, -1);
	STSSetModuleToSite(MD_FPVI10, SITE_2, 2, -1);
	STSSetModuleToSite(MD_FPVI10, SITE_3, 4, -1);
	STSSetModuleToSite(MD_FPVI10, SITE_4, 6, -1);
	STSSetModuleToSite(MD_FPVI10, SITE_5, 8, -1);
	STSSetModuleToSite(MD_FPVI10, SITE_6, 10, -1);
	STSSetModuleToSite(MD_FPVI10, SITE_7, 12, -1);
	STSSetModuleToSite(MD_FPVI10, SITE_8, 14, -1);
}
/****STS_PINPLANNER_CODE_END****/


extern "C" int GetPgsFullPath(LPTSTR pgsPath, int chNum);  //here error

bool DO_TRIM = true;
bool QC = false;
bool QC_PGM = true;
bool DEBUG = false;
bool POWER_FLAG = false;//true=有上下电；false=去上下电，节省测试时间

bool PN_FLAG = true;//true=P管；false=N管
int newmethod = 1;//如果TRIM_BG_1没有问题，TRIM_BG（旧测试方法）会删掉

int	Global_test_id = 1; // uid
int cal_Type = 0;
int	VoltageGP, TempCharGP;
char selectstr[] = "FT,QC,HTOL_FT,HTOL_QC,TempChar";
int	HTOL_HAST_FLAG = 0; // 默认不烧录HTOL/HAST code
int	Global_FTQC_FLAG = 0; // 默认FT测试
int	PartID_Num = 0; // 仅用于可靠性T0编号

int Global_Tempchar_Program_Flag = 0;
char selectTemp[] = "-40℃,-20℃,0℃,25℃,85℃,100℃,125℃";
char selectVoltage[] = "3.3V,5V,5.5V";
int ini_tc_flag = 0;
int ask_tc_flag = 1;
double Global_temp[SITE_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
double VRECT_Volt = 5.5;
double ENB_Volt = 5;


int Temperature = 0;
//int	TempCharGP1, TempCharGP2;
int i_TempCharGP = 0;
int i_Temperature = 0;
int i_Voltage = 0;
int Temp_clear = 0;
char TempRetest[] = "No,Yes";

#define FOR_EACH_VALID_SITE(site) for (site = 0; site < NUM_SITES; site++) if (MsSiteStat(site))

inline int MsSiteStat(int treg_site)
{
	BYTE treg_stat[NUM_SITES] = { 0 };
	int a;
	a = STSGetSiteStatus(treg_stat, NUM_SITES);
	return (int)treg_stat[treg_site];
}

int globalsite;
BYTE sitesta[SITE_NUM];
unsigned char ulWriteData[SITE_NUM] = { 0 };
int site = 0;
double adresult[SITE_COUNT] = { 0.0 };
double adresult0[SITE_COUNT] = { 0.0 };
double adresult1[SITE_COUNT] = { 0.0 };
double adresult2[SITE_COUNT] = { 0.0 };
double adresult3[SITE_COUNT] = { 0.0 };
double adresult4[SITE_COUNT] = { 0.0 };
double adresult5[SITE_COUNT] = { 0.0 };
double adresult6[SITE_COUNT] = { 0.0 };
double adresult7[SITE_COUNT] = { 0.0 };
double adresult8[SITE_COUNT] = { 0.0 };
double AC1_HS_init[SITE_COUNT] = { 0.0 };
double AC1_LS_init[SITE_COUNT] = { 0.0 };
double AC2_HS_init[SITE_COUNT] = { 0.0 };
double AC2_LS_init[SITE_COUNT] = { 0.0 };
double VRECT_VOUT_init[SITE_COUNT] = { 0.0 };
double VRECT_COMM1_init[SITE_COUNT] = { 0.0 };
double VRECT_COMM2_init[SITE_COUNT] = { 0.0 };
double INTB_init[SITE_COUNT] = { 0.0 };
double SINK_init[SITE_COUNT] = { 0.0 };
double SCL_init[SITE_COUNT] = { 0.0 };
double SDA_init[SITE_COUNT] = { 0.0 };
double COMM1_init[SITE_COUNT] = { 0.0 };
double COMM2_init[SITE_COUNT] = { 0.0 };
double ENB_init[SITE_COUNT] = { 0.0 };
double V5V_init[SITE_COUNT] = { 0.0 };
double VOUT_init[SITE_COUNT] = { 0.0 };
double VRECT_init[SITE_COUNT] = { 0.0 };
//boardcheck set
int BoardCheckPass = 0;
int board_check_repeat = -1; //No repeat
int ClassFailCount = 0;

//Read code
int DEV_ADDR = 0XC0;//device address
int EFUSE_READ[11][SITE_NUM] = { 0 };
int INIT_READ_0XF7[SITE_NUM] = { 0 };
bool burn_flag_all[SITE_NUM];//1=need to trim, 0=already trim
int init_read_VBG_CODE[SITE_NUM] = { 0 };
int init_read_ZTC_CODE[SITE_NUM] = { 0 };
int init_read_ADC_VREF_BUFFER_CODE[SITE_NUM] = { 0 };
int init_read_ADC_VIN_BUFFER_CODE[SITE_NUM] = { 0 };
int init_read_OSC_CODE[SITE_NUM] = { 0 };
int init_read_COMP_OFF_AC1_CODE[SITE_NUM] = { 0 };
int init_read_COMP_OFF_AC2_CODE[SITE_NUM] = { 0 };
int init_read_ISNS_GAIN_CODE[SITE_NUM] = { 0 };
int init_read_ISNS_OFFSET_CODE[SITE_NUM] = { 0 };
int init_read_TRIM_ACLOW_EN[SITE_NUM] = { 0 };
int init_read_TTP_FSK_DIS[SITE_NUM] = { 0 };
int init_read_AC_CHECK_500K[SITE_NUM] = { 0 };
int init_read_TRIM_DEIVICE_ID[SITE_NUM] = { 0 };
int init_read_0XF7_BIT2_CODE[SITE_NUM] = { 0 };
int init_read_0XF7_BIT3_CODE[SITE_NUM] = { 0 };
int init_read_0XF7_BIT4_CODE[SITE_NUM] = { 0 };
int init_read_0XF7_BIT5_CODE[SITE_NUM] = { 0 };

int EFUSE_READ_FINAL[11][SITE_NUM] = { 0 };
int EFUSE_READ_FINAL2[11][SITE_NUM] = { 0 };
int FINAL_READ_0XF7[SITE_NUM] = { 0 };
int final_read_VBG_CODE[SITE_NUM] = { 0 };
int final_read_ZTC_CODE[SITE_NUM] = { 0 };
int final_read_ADC_VREF_BUFFER_CODE[SITE_NUM] = { 0 };
int final_read_ADC_VIN_BUFFER_CODE[SITE_NUM] = { 0 };
int final_read_OSC_CODE[SITE_NUM] = { 0 };
int final_read_COMP_OFF_AC1_CODE[SITE_NUM] = { 0 };
int final_read_COMP_OFF_AC2_CODE[SITE_NUM] = { 0 };
int final_read_ISNS_GAIN_CODE[SITE_NUM] = { 0 };
int final_read_ISNS_OFFSET_CODE[SITE_NUM] = { 0 };
int final_read_TRIM_ACLOW_EN[SITE_NUM] = { 0 };
int final_read_TTP_FSK_DIS[SITE_NUM] = { 0 };
int final_read_AC_CHECK_500K[SITE_NUM] = { 0 };
int final_read_TRIM_DEIVICE_ID[SITE_NUM] = { 0 };
int final_read_TRIM_QI_ID[SITE_NUM] = { 0 };
int final_read_0XF7_BIT2_CODE[SITE_NUM] = { 0 };
int final_read_0XF7_BIT3_CODE[SITE_NUM] = { 0 };
int final_read_0XF7_BIT4_CODE[SITE_NUM] = { 0 };
int final_read_0XF7_BIT5_CODE[SITE_NUM] = { 0 };
//burn read
int BEFORE_BURN_0XF7[SITE_NUM] = { 0 };
int before_burn_0XF7_BIT2_CODE[SITE_NUM] = { 1, 1, 1, 1, 1, 1, 1, 1 };
int before_burn_0XF7_BIT3_CODE[SITE_NUM] = { 0 };
int before_burn_0XF7_BIT4_CODE[SITE_NUM] = { 0 };
int before_burn_0XF7_BIT5_CODE[SITE_NUM] = { 0 };

int AFTER_BURN_0XF7[SITE_NUM] = { 0 };
int after_burn_0XF7_BIT2_CODE[SITE_NUM] = { 0 };
int after_burn_0XF7_BIT3_CODE[SITE_NUM] = { 0 };
int after_burn_0XF7_BIT4_CODE[SITE_NUM] = { 0 };
int after_burn_0XF7_BIT5_CODE[SITE_NUM] = { 0 };

int READ_0X75[SITE_NUM] = { 0 };
int read_0X75_BIT1_CODE[SITE_NUM] = { 0 };
int read_0X75_BIT3_CODE[SITE_NUM] = { 0 };
int read_0X75_BIT4_CODE[SITE_NUM] = { 0 };

//htol code
int before_burn_READ_0X39[SITE_NUM] = { 0 };
int before_burn_LDO_ON_OPT_CODE[SITE_NUM] = { 0 };
int before_burn_ILOAD_OPT_CODE[SITE_NUM] = { 0 };
int before_burn_READ_0X3B[SITE_NUM] = { 0 };
int before_burn_SCP_OFF_LDO_DIS_CODE[SITE_NUM] = { 0 };
int before_burn_OCP_OFF_LDO_DIS_CODE[SITE_NUM] = { 0 };
int before_burn_OTP_OFF_LDO_DIS_CODE[SITE_NUM] = { 0 };
int before_burn_OVP2_OFF_SR_DIS_CODE[SITE_NUM] = { 0 };
int before_burn_READ_0X38[SITE_NUM] = { 0 };
int before_burn_MTP_VOUT_SET_CODE[SITE_NUM] = { 0 };
int before_burn_READ_0X89[SITE_NUM] = { 0 };
int before_burn_TRIM_DIG_IOUT_OFFSET_CODE[SITE_NUM] = { 0 };
int before_burn_READ_0X86[SITE_NUM] = { 0 };
int before_burn_TRIM_ISNS_OFFSET_CODE[SITE_NUM] = { 0 };
int before_burn_READ_0X85[SITE_NUM] = { 0 };
int before_burn_TRIM_ISNS_GAIN_CODE[SITE_NUM] = { 0 };
int before_burn_READ_0X87[SITE_NUM] = { 0 };
int before_burn_TRIM_ADC_VIN_BUFFER_CODE[SITE_NUM] = { 0 };
int before_burn_READ_0X32[SITE_NUM] = { 0 };
int before_burn_MTP_DUMMY_0_CODE[SITE_NUM] = { 0 };
int before_burn_READ_0X81[SITE_NUM] = { 0 };
int before_burn_TRIM_DIS_CLPH_ADAP_CODE[SITE_NUM] = { 0 };

int after_burn_READ_0X39[SITE_NUM] = { 0 };
int after_burn_LDO_ON_OPT_CODE[SITE_NUM] = { 0 };
int after_burn_ILOAD_OPT_CODE[SITE_NUM] = { 0 };
int after_burn_READ_0X3B[SITE_NUM] = { 0 };
int after_burn_SCP_OFF_LDO_DIS_CODE[SITE_NUM] = { 0 };
int after_burn_OCP_OFF_LDO_DIS_CODE[SITE_NUM] = { 0 };
int after_burn_OTP_OFF_LDO_DIS_CODE[SITE_NUM] = { 0 };
int after_burn_OVP2_OFF_SR_DIS_CODE[SITE_NUM] = { 0 };
int after_burn_READ_0X38[SITE_NUM] = { 0 };
int after_burn_MTP_VOUT_SET_CODE[SITE_NUM] = { 0 };
int after_burn_READ_0X88[SITE_NUM] = { 0 };
int after_burn_TRIM_DIG_IOUT_OFFSET_CODE[SITE_NUM] = { 0 };
int after_burn_READ_0X86[SITE_NUM] = { 0 };
int after_burn_TRIM_ISNS_OFFSET_CODE[SITE_NUM] = { 0 };
int after_burn_READ_0X85[SITE_NUM] = { 0 };
int after_burn_TRIM_ISNS_GAIN_CODE[SITE_NUM] = { 0 };
int after_burn_READ_0X87[SITE_NUM] = { 0 };
int after_burn_TRIM_VRECT_DMY_DIS_CODE[SITE_NUM] = { 0 };
int after_burn_READ_0X32[SITE_NUM] = { 0 };
int after_burn_MTP_DUMMY_0_CODE[SITE_NUM] = { 0 };
int after_burn_READ_0X81[SITE_NUM] = { 0 };
int after_burn_TRIM_DIS_CLPH_ADAP_CODE[SITE_NUM] = { 0 };

int before_burn_READ_0X33[SITE_NUM] = { 0 };
int after_burn_READ_0X33[SITE_NUM] = { 0 };



int BURN_READ[11][SITE_NUM] = { 0 };
int Burn_Same_As_Read_Flag[SITE_NUM] = { 0 };

int Burn_Same_As_EEPROM0_READ[SITE_NUM] = { 0 };
int Burn_Same_As_EEPROM1_READ[SITE_NUM] = { 0 };
int Burn_Same_As_EEPROM2_READ[SITE_NUM] = { 0 };
int Burn_Same_As_EEPROM3_READ[SITE_NUM] = { 0 };
int Burn_Same_As_EEPROM4_READ[SITE_NUM] = { 0 };
int Burn_Same_As_EEPROM5_READ[SITE_NUM] = { 0 };
int Burn_Same_As_EEPROM6_READ[SITE_NUM] = { 0 };
int Burn_Same_As_EEPROM7_READ[SITE_NUM] = { 0 };
int Burn_Same_As_EEPROM8_READ[SITE_NUM] = { 0 };
int Burn_Same_As_EEPROM9_READ[SITE_NUM] = { 0 };
int Burn_Same_As_EEPROMA_READ[SITE_NUM] = { 0 };

int before_burn_VBG_CODE[SITE_NUM] = { 0 };
int before_burn_ZTC_CODE[SITE_NUM] = { 0 };
int before_burn_ADC_VREF_BUFFER_CODE[SITE_NUM] = { 0 };
int before_burn_ADC_VIN_BUFFER_CODE[SITE_NUM] = { 0 };
int before_burn_OSC_CODE[SITE_NUM] = { 0 };
int before_burn_COMP_OFF_AC1_CODE[SITE_NUM] = { 0 };
int before_burn_COMP_OFF_AC2_CODE[SITE_NUM] = { 0 };
int before_burn_ISNS_GAIN_CODE[SITE_NUM] = { 0 };
int before_burn_ISNS_OFFSET_CODE[SITE_NUM] = { 0 };
int before_burn_TRIM_ACLOW_EN[SITE_NUM] = { 0 };
int before_burn_TTP_FSK_DIS[SITE_NUM] = { 0 };
int before_burn_AC_CHECK_500K[SITE_NUM] = { 0 };
int before_burn_TRIM_DEIVICE_ID[SITE_NUM] = { 0 };
unsigned char before_burn_check[SITE_NUM] = { 0 };
unsigned char before_burn_0x80[SITE_NUM] = { 0 };
unsigned char before_burn_0x81[SITE_NUM] = { 0 };
unsigned char before_burn_0x82[SITE_NUM] = { 0 };
unsigned char before_burn_0x83[SITE_NUM] = { 0 };
unsigned char before_burn_0x84[SITE_NUM] = { 0 };
unsigned char before_burn_0x85[SITE_NUM] = { 0 };
unsigned char before_burn_0x86[SITE_NUM] = { 0 };
unsigned char before_burn_0x87[SITE_NUM] = { 0 };
unsigned char before_burn_0x88[SITE_NUM] = { 0 };
unsigned char before_burn_0x89[SITE_NUM] = { 0 };
unsigned char before_burn_0x8A[SITE_NUM] = { 0 };

int after_burn_VBG_CODE[SITE_NUM] = { 0 };
int after_burn_ZTC_CODE[SITE_NUM] = { 0 };
int after_burn_ADC_VREF_BUFFER_CODE[SITE_NUM] = { 0 };
int after_burn_ADC_VIN_BUFFER_CODE[SITE_NUM] = { 0 };
int after_burn_OSC_CODE[SITE_NUM] = { 0 };
int after_burn_COMP_OFF_AC1_CODE[SITE_NUM] = { 0 };
int after_burn_COMP_OFF_AC2_CODE[SITE_NUM] = { 0 };
int after_burn_ISNS_GAIN_CODE[SITE_NUM] = { 0 };
int after_burn_ISNS_OFFSET_CODE[SITE_NUM] = { 0 };
int after_burn_TRIM_ACLOW_EN[SITE_NUM] = { 0 };
int after_burn_TTP_FSK_DIS[SITE_NUM] = { 0 };
int after_burn_AC_CHECK_500K[SITE_NUM] = { 0 };
int after_burn_TRIM_DEIVICE_ID[SITE_NUM] = { 0 };
int after_burn_TRIM_QI_ID[SITE_NUM] = { 0 };

unsigned char after_burn_0x80[SITE_NUM] = { 0 };
unsigned char after_burn_0x81[SITE_NUM] = { 0 };
unsigned char after_burn_0x82[SITE_NUM] = { 0 };
unsigned char after_burn_0x83[SITE_NUM] = { 0 };
unsigned char after_burn_0x84[SITE_NUM] = { 0 };
unsigned char after_burn_0x85[SITE_NUM] = { 0 };
unsigned char after_burn_0x86[SITE_NUM] = { 0 };
unsigned char after_burn_0x87[SITE_NUM] = { 0 };
unsigned char after_burn_0x88[SITE_NUM] = { 0 };
unsigned char after_burn_0x89[SITE_NUM] = { 0 };
unsigned char after_burn_0x8A[SITE_NUM] = { 0 };

int read_data[SITE_NUM] = { 0 };
int read_pass[SITE_NUM] = { 0 };

bool CIBCheck(int &nBtn, BOOL &flag_pass)
{
	BoardCheck bc;
	Cvi_config vi; // default FV,3V,0A,FOVIe_5V,FOVI_10MA,FPVIe_5V,FPVI_10MA,10ms,100 sample times,10 us interval
	DWORD tnum = 1;

	double value = 1e-5;
	double	a[8][80] = { 0.0 };

	HardWareCfg();
	AstBindingAllModule();
	
	STSSetSiteStatus(0xFF);//set to enable site1 to site8

	//double site_check_specl = 0;
	//double site_check_spech = 0;
	double result[SITE_NUM] = { 0 };
 	BYTE site_sta[SITE_NUM];
 	STSGetSiteStatus(site_sta, SITE_NUM);

	FOR_EACH_VALID_SITE(site)
	{
		if (STSGetUserPriority() == 1)
		{
			bc.SetSiteConnected(site, 1);
		}
		else
		{
			if (site_sta[site] == 1)
				bc.SetSiteConnected(site, 1);
			else  bc.SetSiteConnected(site, 0);
		}
	}
// 	BYTE sitestatus[SITE_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };//判断工位是否有效 1有效 0被屏蔽
// 	StsGetSiteStatus(sitestatus, SITE_COUNT);

	if (BoardCheckPass == 0)
	{
		int CONTACT_CHECK_FLAG = 0;
		double	i_1mA = -1e-3;

		V5V.Set(FI, i_1mA, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(2);

		V5V.MeasureVI(10, 10);

		//FOR_EACH_VALID_SITE(site)
		//{

		//	a[site][0] = V5V.GetMeasResult(site, MVRET);

		//	if (a[site][0] > -1 && site_sta[site] == 1)//判断是否全部open
		//	{
		//		CONTACT_CHECK_FLAG = 1;
		//	}
		//}
		V5V.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		V5V.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

		cbit.SetOn(-1);
		delay_us(3000);

		if (CONTACT_CHECK_FLAG == 0)
		{
			//-------------------------  SITES_CHECK -------------------------//

			//-------------------------  SITES_CHECK -------------------------//

			//----------INTB K25_OFF OK----------
			cbit.SetOn(K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_relay(INTB, Qvm, vi, tnum++, "K21_ON_K25_OFF_QVM_check", 2, 4, "V", result);

			//all board check fail might K21(PGNDF_PGNDS) fail

			//----------VRECT-AC1 K12_K15_FPVI0 K25_ON OK----------
			cbit.SetOn(K12_PVI0H_VRECT, K15_PVI0L_AC1, K25_QVM_FPVI, K21_PGNDF_PGNDS, -1);//fpvi0 H-VRECT, L-AC1
			wait_relay();
			bc.test_relay(FPVI0, Qvm, vi, tnum++, "K12_K15_K25_ON_check", 2, 4, "V", result);

			//----------SINK-AC2 K14_K16_FPVI0 OK----------
			cbit.SetOn(K14_PVI0H_SINK, K16_PVI0L_AC2, K25_QVM_FPVI, K21_PGNDF_PGNDS, -1);//fpvi0 H-SINK, L-AC2
			wait_relay();
			bc.test_relay(FPVI0, Qvm, vi, tnum++, "K14_K16_K25_ON_check", 2, 4, "V", result);

			//----------VOUT K13_K17_FPVI0 FOVI7 OK----------
			cbit.SetOn(K13_PVI0H_PGND, K17_PVI0L_VOUT, K21_PGNDF_PGNDS, -1);//fpvi0 H-PGND, L-VOUT
			wait_relay();
			bc.test_relay(VOUT, FPVI0, vi, tnum++, "K13_K17_ON_K11_OFF_check", 2, 4, "V", result);

			cbit.SetOn(K17_PVI0L_VOUT, K21_PGNDF_PGNDS, -1);//fpvi0 H-PGND, L-VOUT
			wait_relay();
			bc.test_relay(VOUT, FPVI0, vi, tnum++, "K13_OFF_check", -0.5, 0.5, "V", result);

			cbit.SetOn(-1);//fpvi0 H-PGND, L-VOUT
			wait_relay();
			bc.test_relay(VOUT, FPVI0, vi, tnum++, "K17_OFF_check", -0.5, 0.5, "V", result);

			//----------V5V K13_K18_FPVI0 FOVI1 OK----------
			cbit.SetOn(K13_PVI0H_PGND, K18_PVI0L_V5V, K21_PGNDF_PGNDS, -1);//fpvi0 H-PGND, L-V5V
			wait_relay();
			bc.test_relay(V5V, FPVI0, vi, tnum++, "K13_K18_ON_check", 2, 4, "V", result);

			cbit.SetOn(K13_PVI0H_PGND, K21_PGNDF_PGNDS, -1);//fpvi0 H-PGND, L-V5V
			wait_relay();
			bc.test_relay(V5V, FPVI0, vi, tnum++, "K18_OFF_check", -0.2, 0.2, "V", result);

			//----------VRECT K13_K19_FPVI0 FOVI0 OK----------
			cbit.SetOn(K13_PVI0H_PGND, K19_PVI0L_VRECT, K21_PGNDF_PGNDS, -1);//fpvi0 H-PGND, L-VRECT
			wait_relay();
			bc.test_relay(VRECT, FPVI0, vi, tnum++, "K13_K19_ON_check", 2, 4, "V", result);

			cbit.SetOn(K13_PVI0H_PGND, K21_PGNDF_PGNDS, -1);//fpvi0 H-PGND, L-VRECT
			wait_relay();
			bc.test_relay(VRECT, FPVI0, vi, tnum++, "K19_OFF_check", -0.2, 0.2, "V", result);

			//----------COMM2 K11_K13_K20_FPVI0 FOVI7 OK----------
			cbit.SetOn(K11_OVI7_VOUT_COMM2, K13_PVI0H_PGND, K20_PVI0L_COMM2, K21_PGNDF_PGNDS, -1);//fpvi0 H-PGND, L-COMM2
			wait_relay();
			bc.test_relay(COMM2, FPVI0, vi, tnum++, "K11_K13_K20_ON_check", 2, 4, "V", result);

			cbit.SetOn(K11_OVI7_VOUT_COMM2, K13_PVI0H_PGND, K21_PGNDF_PGNDS, -1);//fpvi0 H-PGND, L-COMM2
			wait_relay();
			bc.test_relay(COMM2, FPVI0, vi, tnum++, "K20_OFF_check", -0.2, 0.2, "V", result);

			//----------COMM1 K10_K13_K27_FPVI0 FOVI6 OK----------
			cbit.SetOn(K10_OVI6_ENB_COMM1, K13_PVI0H_PGND, K27_PVI0L_COMM1, K21_PGNDF_PGNDS, -1);//fpvi0 H-PGND, L-COMM1
			wait_relay();
			bc.test_relay(COMM1, FPVI0, vi, tnum++, "K10_K13_K27_ON_check", 2, 4, "V", result);

			cbit.SetOn(K10_OVI6_ENB_COMM1, K13_PVI0H_PGND, K21_PGNDF_PGNDS, -1);//fpvi0 H-PGND, L-COMM1
			wait_relay();
			bc.test_relay(COMM1, FPVI0, vi, tnum++, "K27_OFF_check", -0.2, 0.2, "V", result);

			//----------FOVI_CHB K8_K9_OFF OK----------
			cbit.SetOn(K13_PVI0H_PGND, K15_PVI0L_AC1, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_relay(AC1, FPVI0, vi, 1, "K13_K15_ON_K8_OFF_check", 2, 4, "V", result);

			cbit.SetOn(K13_PVI0H_PGND, K16_PVI0L_AC2, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_relay(AC2, FPVI0, vi, tnum++, "K13_K15_ON_K9_OFF_check", 2, 4, "V", result);



			//----------SINK K23_QTMU OK----------
			cbit.SetOn(K23_QTMU_SINK, -1);
			wait_relay();
			bc.test_qtmu(SINK, QTMU, QTMU_PLUS_SINGLE_SOURCE, tnum++, "K23_ON_QTMU_check", 600, 800, "us", result);
			cbit.SetOn(-1);
			wait_relay();
			bc.test_qtmu(SINK, QTMU, QTMU_PLUS_SINGLE_SOURCE, tnum++, "K23_OFF_QTMU_check", -20, 20, "us", result);

			//----------INTB K24_QTMU OK----------
			cbit.SetOn(K24_QTMU_INTB, -1);
			wait_relay();
			bc.test_qtmu(INTB, QTMU, QTMU_PLUS_SINGLE_SOURCE, tnum++, "K24_ON_QTMU_check", 600, 800, "us", result);
			cbit.SetOn(-1);
			wait_relay();
			bc.test_qtmu(INTB, QTMU, QTMU_PLUS_SINGLE_SOURCE, tnum++, "K24_OFF_QTMU_check", -20, 20, "us", result);

			//----------K22_ON OK----------
			cbit.SetOn(K8_OVI4_AC1_SCL, K22_DIO_EEPROM, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_relay(SCL, "SCL", "SCL", vi, tnum++, "K22_ON_DIO_check", -0.5, 0.5, "V", result);

			//----------SCL K8_FOVI4 K22_DIO0 OK----------
			cbit.SetOn(K8_OVI4_AC1_SCL, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_relay(SCL, "SCL", "SCL", vi, tnum++, "K8_ON_K22_OFF_DIO0_check", 2, 4, "V", result);
			
			//----------SDA K9_FOVI5 K22_DIO1 OK----------
			cbit.SetOn(K9_OVI5_AC2_SDA, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_relay(SDA, "SDA", "SDA", vi, tnum++, "K9_ON_K22_OFF_DIO1_check", 2, 4, "V", result);

			//----------ENB K5_DIO2 FOVI6 OK----------
			cbit.SetOn(K5_DIO2_ENB, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_relay(ENB, "ENB", "ENB", vi, tnum++, "K5_ON_K10_OFF_DIO2_check", 2, 4, "V", result);

			cbit.SetOn(K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_relay(ENB, "ENB", "ENB", vi, tnum++, "K5_OFF_DIO2_check", -1, 1, "V", result);

			//----------INTB K0_DIO3 FOVI2 OK----------
			cbit.SetOn(K0_DIO3_INTB, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_relay(INTB, "INTB", "INTB", vi, tnum++, "K0_ON_DIO3_check", 2, 4, "V", result);

			cbit.SetOn(K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_relay(INTB, "INTB", "INTB", vi, tnum++, "K0_OFF_DIO3_check", -1, 1, "V", result);//

			//----------OPA189_Buffer K25_K26_QVM OK----------
			cbit.SetOn(K26_BUFF_INTB, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_relay(INTB, Qvm, vi, tnum++, "K25_OFF_K26_ON_buffer_check", 2, 4, "V", result);


			//----------SCL SDA K4, PULLUP FOVI4 FOVI5 OK----------
			cbit.SetOn(K4_IIC_PULLUP, K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_r(PULL_UP, SCL, tnum++, "K4_ON_SCL_PULLUP_check", 1.8, 2.2, "kOhm", result);
			bc.test_r(PULL_UP, SDA, tnum++, "K4_ON_SDA_PULLUP_check", 1.8, 2.2, "kOhm", result);

			//----------INTB K6, PULLUP OK----------
			cbit.SetOn(K6_INTB_PULLUP, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_r(PULL_UP, INTB, tnum++, "K6_ON_PULLUP_check", 0.8, 1.2, "kOhm", result);

			cbit.SetOn(K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_r(PULL_UP, INTB, tnum++, "K6_OFF_PULLUP_check", -0.2, 0.2, "kOhm", result);

			//----------SINK K7, PULLUP OK----------
			cbit.SetOn(K7_SINK_PULLUP, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_r(PULL_UP, SINK, tnum++, "K7_ON_PULLUP_check", 1.8, 2.2, "kOhm", result);

			cbit.SetOn(K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_r(PULL_UP, SINK, tnum++, "K7_OFF_PULLUP_check", -0.2, 0.2, "kOhm", result);

			//----------AC K1, C_AC OK----------
			cbit.SetOn(K1_AC_CAP, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_cap_to_gnd(AC1, tnum++, "K1_ON_C_AC1_check", 0.8, 1.2, "uF", result);
			bc.test_cap_to_gnd(AC2, tnum++, "K1_ON_C_AC2_check", 0.8, 1.2, "uF", result);


			//----------VOUT K3, C1_C_VOUT OK----------
			cbit.SetOn(K3_VOUT_CAP, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_cap_to_gnd(VOUT, tnum++, "K3_ON_C_VOUT_check", 3.4, 6, "uF", result);

			//----------VRECT V5V K2, C1_C2_VRECT C1_C_V5V OK----------
			cbit.SetOn(K2_VRECT_V5V_CAP, K21_PGNDF_PGNDS, -1);
			wait_relay();
			bc.test_cap_to_gnd(V5V, tnum++, "K2_ON_C_V5V_check", 0.8, 1.2, "uF", result);
			bc.test_cap_to_gnd(VRECT, tnum++, "K2_ON_C2_VRECT_check", 8, 12, "uF", result);



			if (CONTACT_CHECK_FLAG == 0)
			{
				if (bc.check_results_summary())
				{
					flag_pass = true;// Board check pass
					board_check_repeat = 0;
				}
				else
				{
					if (board_check_repeat < 0)
						bc.Display();
					nBtn = bc.get_nBtn();
					flag_pass = bc.IsCheckPass();// Board check fail
					bc.report();

				}
				nBtn = bc.get_nBtn();
			}
			else
			{
				ClassFailCount ++;

				flag_pass = false;// Board check fail

				LPCSTR Reminder_message = "BoardCheck 错误！\n请保证做BoardCheck时候socket中不要放芯片！\n点击《确定》退出，拿掉芯片，再次完成BoardCheck";
				LPCSTR  Reminder_header = "BoardCheck失效提示信息";
				StsMessageBox(Reminder_message, Reminder_header);//-----------Printf(Board Check 测试需要Probe针不能接触芯片)
			}

			return flag_pass;

		}
	}

	return 0;

}
//if needed, you can move the following functions to the file of test.cpp.
//Do not change the definition of these functions, or the pgs can not be loaded.
DUT_API void UserLoad()
{
	int nErr = 0;

	//nErr = dioplus.LoadVectorFile("F16821.vecdio");  // load vector file
	nErr = dioplus.LoadVectorFile("F16821_debug.vecdio");  // load vector file

 	int nBtn = BTN_REDO;
 	BOOL flag_pass = FALSE;
 	if (STSGetUserPriority() == 2 || STSGetUserPriority() == 3)//OPERATOR=1/ENGINEER=2/ADMIN=3
 	{

		if (MessageBoxA(NULL, "是否跳过boardcheck! \n\n请确认测试座里是否存在样品，有-是(Y)\n没有-否(N)", "诊断提示对话框", MB_YESNO) == IDNO)
		{
			CIBCheck(nBtn, flag_pass);//后期加弹窗选择
		}

		STSSetHardwareCheck(FALSE);//量产必须删掉！！！For QVM check
 	}
 	else
 	{
 		//=======Operator 模式 必须要做BoardCheck
 		CIBCheck(nBtn, flag_pass);

		if (MessageBoxA(NULL, "部分工位检测失效! \n\n如果继续测试，选择-是(Y)\n如果退出，选择-否(N)", "诊断提示对话框", MB_YESNO) == IDNO)
		{
			PostQuitMessage(0);
		}
 	}


	DIO_PLUS::I2CByteNum key123(1, 2, 1);
	char pgsfullpath[300];
	GetPgsFullPath(pgsfullpath, 300);
	string fullpathpgs(pgsfullpath);
	string pathofpgs = "";
	int pos = fullpathpgs.find_last_of('\\');
	if (pos > -1)
	{
		pathofpgs = fullpathpgs.substr(0, pos + 1);
	}
	string pathoftreg = pathofpgs;

// 	fclose(stdout);
// 	FreeConsole();

	//用于华宇定制化 UI load程序
	char pcData[MAX_PATH]{};
	STSGetPgsPath(pcData, MAX_PATH);

	char pcPgsPath[MAX_PATH]{};
	sprintf(pcPgsPath, "%bowplus.spec", pcData);

	string pathofspec = "\\bowplus.spec";
	spec.initial(pathofspec.c_str());
	//spec.initial(pcPgsPath);


	//不同PN spec & tempchar select
	if (STSGetUserPriority() == 2 || STSGetUserPriority() == 3)//OPERATOR=1/ENGINEER=2/ADMIN=3
	{
		int part_select = 0;
		char selectpartnum[] = "NU1682,NU1685,NU1687,NU1682A";//V01 add NU1682A
		part_select = STSSetInitSelectDialog("PART NUMBER Select", 4, 0, selectpartnum);
		if (part_select == 0)
		{
			spec.select_device("NU1682");
			pathoftreg = pathofpgs + "\\NU1682.treg";
			dut.init(pathoftreg.c_str(), SITE_NUM, QC, DO_TRIM);
		}
		else if (part_select == 1)
		{
			spec.select_device("NU1685");
			pathoftreg = pathofpgs + "\\NU1685.treg";
			dut.init(pathoftreg.c_str(), SITE_NUM, QC, DO_TRIM);
		}
		else if (part_select == 2)
		{
			spec.select_device("NU1687");
			pathoftreg = pathofpgs + "\\NU1687.treg";
			dut.init(pathoftreg.c_str(), SITE_NUM, QC, DO_TRIM);
		}
		else if (part_select == 3)//V01 add NU1682A
		{
			spec.select_device("NU1682A");
			pathoftreg = pathofpgs + "\\NU1682A.treg";
			dut.init(pathoftreg.c_str(), SITE_NUM, QC, DO_TRIM);
		}

		////Global_FTQC_FLAG = STSSetInitSelectDialog("TEST METHOD Select", 4, 0, selectstr);
		////Global_test_id = STSSetInitSelectDialog("test number", 30, 0, start_number);
		Global_test_id = 0;
		cal_Type = STSSetInitSelectDialog("TEST METHOD Select", 5, 0, selectstr);//FT QC TEMPCHAR HTOL_FT HTOL_QC
		if (cal_Type == 0)//FT
		{
			HTOL_HAST_FLAG = 0;
			Global_FTQC_FLAG = 0;
			TempCharGP = 3;//25

			STSSetUseLimitbyName("FT");//Limit select
		}
		if (cal_Type == 1)//QC
		{
			HTOL_HAST_FLAG = 0;
			Global_FTQC_FLAG = 1;
			TempCharGP = 3;//25

			STSSetUseLimitbyName("QA");//Limit select
		}
		if (cal_Type == 2)//HTOL&HAST_FT
		{
			HTOL_HAST_FLAG = 1;
			Global_FTQC_FLAG = 0;
			TempCharGP = 3;//25

			STSSetUseLimitbyName("FT");//Limit select
		}
		if (cal_Type == 3)//HTOL&HAST_QC
		{
			HTOL_HAST_FLAG = 1;
			Global_FTQC_FLAG = 1;
			TempCharGP = 3;//25

			STSSetUseLimitbyName("QA");//Limit select
		}
		if (cal_Type == 4)//tempchar
		{
			HTOL_HAST_FLAG = 0;
			Global_FTQC_FLAG = 1;
			Global_Tempchar_Program_Flag = 1;

			STSSetUseLimitbyName("QA");//Limit select

			TempCharGP = STSSetInitSelectDialog("Temp Select", 7, 0, selectTemp);
			VoltageGP = STSSetInitSelectDialog("Voltage Select", 3, 0, selectVoltage);

			ini_tc_flag = 1;
			ask_tc_flag = 0;
		}
	}
	//不同PN spec & tempchar select后期打开，前期为debug方便先关闭

	QTMU.Init();
	Qvm.Init();
	cbit.Init();
	dioplus.Init();
	dioplus.I2CInit(8);
	dioplus.I2CSetRegAddresByteCount(2);
	double period = 2 * 1e-6; //500k for function test
	dioplus.I2CSetClockPeriod(period);
	dioplus.I2CSetSCLDelay(0, period / 2);
	dioplus.I2CSetSDADelay(period / 6, period / 2, period * 2 / 3);

	dioplus.SetVIH(5.0f);
	dioplus.SetVIL(0.0f);
	dioplus.SetVOH(2.2f);
	dioplus.SetVOL(0.4f);
	delay_ms(1);

	/*****************************AWG load start**************************************/
	int sam = 100;
	double awg_pattern29[100] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern29[0], sam, 1, 3, 1.5);
	VOUT.AwgLoader("VOUT_SCP_F", FV, FOVI_10V, FOVI_100MA, awg_pattern29, sam);// 15mv/step

	double awg_pattern30[100] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern30[0], sam, 1, 1.5, 3);
	VOUT.AwgLoader("VOUT_SCP_R", FV, FOVI_10V, FOVI_100MA, awg_pattern30, sam);// 15mv/step

	double awg_pattern31[100] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern31[0], sam, 1, 5.1, 5.8);
	VRECT.AwgLoader("VSP_VRECTM5_R", FV, FOVI_10V, FOVI_100MA, awg_pattern31, sam);// 7mv/step

	double awg_pattern32[100] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern32[0], sam, 1, 5.5, 4.8);
	VRECT.AwgLoader("VSP_VRECTM5_F", FV, FOVI_10V, FOVI_100MA, awg_pattern32, sam);// 7mv/step

	double awg_pattern33[100] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern33[0], sam, 1, 3.5, 2.5);
	VOUT.AwgLoader("VOUT_GD_F", FV, FOVI_10V, FOVI_100MA, awg_pattern33, sam);// 10mv/step

	double awg_pattern34[100] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern34[0], sam, 1, 2.5, 3.5);
	VOUT.AwgLoader("VOUT_GD_R", FV, FOVI_10V, FOVI_100MA, awg_pattern34, sam);// 10mv/step

	sam = 200;
	double awg_pattern3[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern3[0], sam, 1, 3.5, 2.5);
	VRECT.AwgLoader("VRECT_UVLO_F", FV, FOVI_5V, FOVI_100MA, awg_pattern3, sam);// 5mv/step

	double awg_pattern4[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern4[0], sam, 1, 2.5, 3.5);
	VRECT.AwgLoader("VRECT_UVLO_R", FV, FOVI_5V, FOVI_100MA, awg_pattern4, sam);// 5mv/step

	//sam = 100;
	double awg_pattern5[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern5[0], sam, 1, 0.5, 1.5);
	ENB.AwgLoader("VPDET_EN_R", FV, FOVI_5V, FOVI_100MA, awg_pattern5, sam);// 5mv/step

	double awg_pattern6[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern6[0], sam, 1, 1.5, 0.5);
	ENB.AwgLoader("VPDET_EN_F", FV, FOVI_5V, FOVI_100MA, awg_pattern6, sam);// 5mv/step

	double awg_pattern7[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern7[0], sam, 1, 0.5, 1.5);
	SCL.AwgLoader("VTH_SCL_R", FV, FOVI_5V, FOVI_10MA, awg_pattern7, sam);// 5mv/step

	double awg_pattern8[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern8[0], sam, 1, 1.5, 0.5);
	SCL.AwgLoader("VTH_SCL_F", FV, FOVI_5V, FOVI_10MA, awg_pattern8, sam);// 5mv/step

	double awg_pattern9[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern9[0], sam, 1, 0.5, 1.5);
	SDA.AwgLoader("VTH_SDA_R", FV, FOVI_5V, FOVI_10MA, awg_pattern9, sam);// 5mv/step

	double awg_pattern10[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern10[0], sam, 1, 1.5, 0.5);
	SDA.AwgLoader("VTH_SDA_F", FV, FOVI_5V, FOVI_10MA, awg_pattern10, sam);// 5mv/step

	//sam = 200;
	double awg_pattern11[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern11[0], sam, 1, 2, 4);
	AC1.AwgLoader("AC1_FSK_R", FV, FOVI_5V, FOVI_10MA, awg_pattern11, sam);// 10mv/step

	double awg_pattern12[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern12[0], sam, 1, 4, 1);
	AC1.AwgLoader("AC1_FSK_F", FV, FOVI_5V, FOVI_10MA, awg_pattern12, sam);// 15mv/step

	double awg_pattern25[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern25[0], sam, 1, 9.5, 17);
	VRECT.AwgLoader("VRECT_OVP_R", FV, FOVI_20V, FOVI_1A, awg_pattern25, sam);// 37.5mv/step

	double awg_pattern26[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern26[0], sam, 1, 13, 5.5);
	VRECT.AwgLoader("VRECT_OVP_F", FV, FOVI_20V, FOVI_1A, awg_pattern26, sam);// 37.5mv/step

	double awg_pattern35[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern35[0], sam, 1, 0, -0.5);
	VOUT.AwgLoader("LOAD_300mA_R", FI, FOVI_10V, FOVI_1A, awg_pattern35, sam);// 2.5mA/step

	double awg_pattern36[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern36[0], sam, 1, -0.5, 0);
	VOUT.AwgLoader("LOAD_300mA_F", FI, FOVI_10V, FOVI_1A, awg_pattern36, sam);// 2.5mA/step

	//sam = 300;
	double awg_pattern27[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern27[0], sam, 1, 0, 1);
	FPVI0.AwgLoader("IOUT_OCP_R", FI, FPVI10_10V, FPVI10_1A, awg_pattern27, sam);// PGND-VOUT,5mA/step

	double awg_pattern28[200] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern28[0], sam, 1, 1, 0);
	FPVI0.AwgLoader("IOUT_OCP_F", FI, FPVI10_10V, FPVI10_1A, awg_pattern28, sam);// PGND-VOUT,5mA/step

	sam = 400;
	double awg_pattern1[400] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern1[0], sam, 1, -0.2, 0.1);
	AC1.AwgLoader("AC1_LS_OFF_TRIM", FV, FOVI_1V, FOVI_10MA, awg_pattern1, sam);// 0.75mv/step

	double awg_pattern2[400] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern2[0], sam, 1, -0.2, 0.1);
	AC2.AwgLoader("AC2_LS_OFF_TRIM", FV, FOVI_1V, FOVI_10MA, awg_pattern2, sam);// 0.75mv/step

	double awg_pattern13[400] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern13[0], sam, 1, -0.2, 0.1);
	AC1.AwgLoader("AC1_LS_OFF", FV, FOVI_1V, FOVI_10MA, awg_pattern13, sam);// 0.75mv/step

	double awg_pattern14[400] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern14[0], sam, 1, -0.2, 0.1);
	AC2.AwgLoader("AC2_LS_OFF", FV, FOVI_1V, FOVI_10MA, awg_pattern14, sam);// 0.75mv/step

	double awg_pattern15[400] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern15[0], sam, 1, 0, -0.2);
	AC1.AwgLoader("AC1_LS_ON", FV, FOVI_1V, FOVI_10MA, awg_pattern15, sam);// 0.5mv/step

	double awg_pattern16[400] = { 0.0 };
	STSAWGCreateRampData(&awg_pattern16[0], sam, 1, 0, -0.2);
	AC2.AwgLoader("AC2_LS_ON", FV, FOVI_1V, FOVI_10MA, awg_pattern16, sam);// 0.5mv/step
	/*****************************AWG load stop**************************************/
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//initialize function will be called before all the test functions.
DUT_API void InitBeforeTestFlow()
{
	dut.sot();
	dut.trim.set_trim_allowed(true);
	QTMU.Init();
	Qvm.Init();
	cbit.Init();
	dioplus.Init();
	dioplus.I2CInit(8);
	DIO_PLUS::I2CByteNum key123(1, 1, 1);
	dioplus.I2CSetRegAddresByteCount(1);
	double period = 2 * 1e-6; //500k for function test
	dioplus.I2CSetClockPeriod(period);
	dioplus.I2CSetSCLDelay(0, period / 2);
	dioplus.I2CSetSDADelay(period / 6, period / 2, period * 2 / 3);

	dioplus.SetVIH(5.0f);
	dioplus.SetVIL(0.0f);
	dioplus.SetVOH(2.2f);
	dioplus.SetVOL(0.4f);
	delay_ms(1);

	VRECT_Volt = 5.5;//FT QA测试
	ENB_Volt = 5;//FT QA测试

	if (Global_Tempchar_Program_Flag == 1)
	{

		if (ini_tc_flag == 1)
		{
			spec("V5V").unprotect() = spec("V5V_CHAR")[VoltageGP], spec("V5V").protect();
			spec("VRECT").unprotect() = spec("VRECT_CHAR")[VoltageGP], spec("VRECT").protect();
			spec("ENB").unprotect() = spec("ENB_CHAR")[VoltageGP], spec("ENB").protect();

			i_Voltage = VoltageGP + 1;
			i_Temperature = TempCharGP;
			ini_tc_flag = 0;
		}
		else
		{
			if (ask_tc_flag == 1)
			{
				ask_tc_flag = 0;

				//voltage table
				if (i_Voltage < spec("Num_VoltageTable"))
				{
					VoltageGP = i_Voltage;
					i_Voltage++;
				}

				TempCharGP = i_Temperature;

				spec("V5V").unprotect() = spec("V5V_CHAR")[VoltageGP], spec("V5V").protect();
				spec("VRECT").unprotect() = spec("VRECT_CHAR")[VoltageGP], spec("VRECT").protect();
				spec("ENB").unprotect() = spec("ENB_CHAR")[VoltageGP], spec("ENB").protect();

				Temp_clear = STSSetInitSelectDialog("Temp Retest", 2, 0, TempRetest);
			}

		}


		if (Temp_clear == 1)
		{
			Temp_clear = 0;

			TempCharGP = STSSetInitSelectDialog("Temp Select", 7, 0, selectTemp);

			VoltageGP = STSSetInitSelectDialog("Voltage Select", 3, 0, selectVoltage);

			i_Voltage = VoltageGP + 1;

			i_Temperature = TempCharGP;

			spec("V5V").unprotect() = spec("V5V_CHAR")[VoltageGP], spec("V5V").protect();
			spec("VRECT").unprotect() = spec("VRECT_CHAR")[VoltageGP], spec("VRECT").protect();
			spec("ENB").unprotect() = spec("ENB_CHAR")[VoltageGP], spec("ENB").protect();
		}

		if (i_Voltage >= spec("Num_VoltageTable"))
		{
			i_Voltage = 0;

			//temperature table
			i_Temperature++;
		}

		if (i_Temperature >= spec("Num_Temperature_Table"))
		{
			i_Temperature = 0;
		}
		VRECT_Volt = spec("VRECT");//temp char测试
		ENB_Volt = spec("ENB");//temp char测试

	}

}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//initializefunction will be called after all the test functions.
DUT_API void InitAfterTestFlow()
{		
	FPVI0.Set(FV, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	//ALLPINS_INITIALIZE_0V_2V_10MA_ON();
	VRECT.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	V5V.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	INTB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	SINK.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	ENB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	VOUT.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.Set(FV, 0, FPVI10_2V, FPVI10_10MA, RELAY_OFF);
	//ALLPINS_INITIALIZE_0V_2V_10MA_OFF();
	FOVI_ALL.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	delay_us(500);

	cbit.SetOn(-1);
	QTMU.Disconnect();
	Qvm.Disconnect();
	dioplus.Disconnect();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
//Fail site hardware set function will be called after failed params, it can be called for serveral times. 
DUT_API void SetupFailSite(const unsigned char*byFailSite)
{	

	FPVI0.Set(FV, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	//ALLPINS_INITIALIZE_0V_2V_10MA_ON();
	VRECT.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	V5V.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	INTB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	SINK.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	ENB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	VOUT.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.Set(FV, 0, FPVI10_2V, FPVI10_10MA, RELAY_OFF);
	//ALLPINS_INITIALIZE_0V_2V_10MA_OFF();
	FOVI_ALL.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

}
/************************************************************************/
/*                                                                      */
/************************************************************************/

DUT_API int DEVICE_INFO(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *DEVICE_NAME = StsGetParam(funcindex, "DEVICE_NAME");
    CParam *VRECT_VOLTAGE = StsGetParam(funcindex, "VRECT_VOLTAGE");
    CParam *V5V_VOLTAGE = StsGetParam(funcindex, "V5V_VOLTAGE");
    CParam *ENB_VOLTAGE = StsGetParam(funcindex, "ENB_VOLTAGE");
    CParam *HTOL_HAST_DO = StsGetParam(funcindex, "HTOL_HAST_DO");
    CParam *FT_QA_FLAG = StsGetParam(funcindex, "FT_QA_FLAG");
    CParam *PGM_VER = StsGetParam(funcindex, "PGM_VER");
    CParam *GOLBAL_TEMP = StsGetParam(funcindex, "GOLBAL_TEMP");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	Temperature = spec("Temperature")[TempCharGP];

	FOR_EACH_VALID_SITE(site)
	{
		DEVICE_NAME->SetTestResult(site, 0, spec("PT_PROG"));
		VRECT_VOLTAGE->SetTestResult(site, 0, spec("VRECT"));
		V5V_VOLTAGE->SetTestResult(site, 0, spec("V5V"));
		ENB_VOLTAGE->SetTestResult(site, 0, spec("ENB"));
		HTOL_HAST_DO->SetTestResult(site, 0, HTOL_HAST_FLAG);
		FT_QA_FLAG->SetTestResult(site, 0, Global_FTQC_FLAG);
		PGM_VER->SetTestResult(site, 0, 0);//program update
		GOLBAL_TEMP->SetTestResult(site, 0, Temperature);
	}


    return 0;
}

DUT_API int KELVIN_CHECK(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *VRECT_Kelvin = StsGetParam(funcindex, "VRECT_Kelvin");
    CParam *V5V_Kelvin = StsGetParam(funcindex, "V5V_Kelvin");
    CParam *INTB_Kelvin = StsGetParam(funcindex, "INTB_Kelvin");
    CParam *SINK_Kelvin = StsGetParam(funcindex, "SINK_Kelvin");
    CParam *AC1_Kelvin = StsGetParam(funcindex, "AC1_Kelvin");
    CParam *AC2_Kelvin = StsGetParam(funcindex, "AC2_Kelvin");
    CParam *ENB_Kelvin = StsGetParam(funcindex, "ENB_Kelvin");
    CParam *VOUT_Kelvin = StsGetParam(funcindex, "VOUT_Kelvin");
    CParam *SCL_Kelvin = StsGetParam(funcindex, "SCL_Kelvin");
    CParam *SDA_Kelvin = StsGetParam(funcindex, "SDA_Kelvin");
    CParam *COMM1_Kelvin = StsGetParam(funcindex, "COMM1_Kelvin");
    CParam *COMM2_Kelvin = StsGetParam(funcindex, "COMM2_Kelvin");
//}}AFX_STS_PARAM_PROTOTYPES
	// TODO: Add your function code here
	double Radresult_kelvin_data[STS_SITE_NUM];
	double I_Kelvin[STS_SITE_NUM] = { 0 };
	double V_Kelvin[STS_SITE_NUM] = { 0 };

	//VRECT kelvin check
	cbit.SetOn(K13_PVI0H_PGND, K19_PVI0L_VRECT, -1);
	wait_relay();
	kelvin_measure(FPVI0, VRECT, -0.0001, Radresult_kelvin_data);
	SERIAL	VRECT_Kelvin->SetTestResult(SITE, 0, Radresult_kelvin_data[SITE]);

	//V5V kelvin check
	cbit.SetOn(K13_PVI0H_PGND, K18_PVI0L_V5V, -1);
	wait_relay();
	kelvin_measure(FPVI0, V5V, -0.0001, Radresult_kelvin_data);
	SERIAL	V5V_Kelvin->SetTestResult(SITE, 0, Radresult_kelvin_data[SITE]);

	//AC1 kelvin check
	cbit.SetOn(K13_PVI0H_PGND, K15_PVI0L_AC1, -1);
	wait_relay();
	kelvin_measure(FPVI0, AC1, -0.0001, Radresult_kelvin_data);
	SERIAL	AC1_Kelvin->SetTestResult(SITE, 0, Radresult_kelvin_data[SITE]);

	//AC2 kelvin check
	cbit.SetOn(K13_PVI0H_PGND, K16_PVI0L_AC2, -1);
	wait_relay();
	kelvin_measure(FPVI0, AC2, -0.0001, Radresult_kelvin_data);
	SERIAL	AC2_Kelvin->SetTestResult(SITE, 0, Radresult_kelvin_data[SITE]);

	//VOUT kelvin check
	cbit.SetOn(K13_PVI0H_PGND, K17_PVI0L_VOUT, -1);
	wait_relay();
	kelvin_measure(FPVI0, VOUT, -0.0001, Radresult_kelvin_data);
	SERIAL	VOUT_Kelvin->SetTestResult(SITE, 0, Radresult_kelvin_data[SITE]);

	//COMM1 kelvin check
	cbit.SetOn(K13_PVI0H_PGND, K27_PVI0L_COMM1, -1);
	wait_relay();
	kelvin_measure(FPVI0, COMM1, -0.0001, Radresult_kelvin_data);
	SERIAL	COMM1_Kelvin->SetTestResult(SITE, 0, Radresult_kelvin_data[SITE]);

	//COMM2 kelvin check
	cbit.SetOn(K13_PVI0H_PGND, K20_PVI0L_COMM2, -1);
	wait_relay();
	kelvin_measure(FPVI0, COMM2, -0.0001, Radresult_kelvin_data);
	SERIAL	COMM2_Kelvin->SetTestResult(SITE, 0, Radresult_kelvin_data[SITE]);


	//INTB kelvin check
	cbit.SetOn(K6_INTB_PULLUP, -1);
	wait_relay();
	INTB.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_SENSE_ON);
	delay_us(500);
	INTB.MeasureVI(20, 10);
	SERIAL
	{
		V_Kelvin[SITE] = INTB.GetMeasResult(SITE, MVRET);
		//I_Kelvin[SITE] = INTB.GetMeasResult(SITE, MIRET);
		//Radresult_kelvin_data[SITE] = V_Kelvin[SITE] / I_Kelvin[SITE];
		INTB_Kelvin->SetTestResult(SITE, 0, V_Kelvin[SITE]);
	}
	INTB.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	//SINK kelvin check
	cbit.SetOn(K7_SINK_PULLUP, -1);
	wait_relay();
	SINK.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_SENSE_ON);
	delay_us(500);
	SINK.MeasureVI(20, 10);
	SERIAL
	{
		V_Kelvin[SITE] = SINK.GetMeasResult(SITE, MVRET);
		//I_Kelvin[SITE] = SINK.GetMeasResult(SITE, MIRET);
		//Radresult_kelvin_data[SITE] = -V_Kelvin[SITE] / I_Kelvin[SITE];
		SINK_Kelvin->SetTestResult(SITE, 0, V_Kelvin[SITE]);
	}
	SINK.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	dioplus.SetVIH(3.0f);//3v
	dioplus.SetVIL(0.0f);

	//ENB kelvin check
	cbit.SetOn(K5_DIO2_ENB, -1);
	wait_relay();
	dioplus.Connect("ENB");
	ENB.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_SENSE_ON);
	delay_us(500);

	dioplus.Run("checkstart", "checkhigh");//set high level=3v
	delay_us(500);
	ENB.MeasureVI(10, 10);

	dioplus.Run("checkhigh", "checkstop");//set high Z
	ENB.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	
	SERIAL
	{
		V_Kelvin[SITE] = ENB.GetMeasResult(SITE, MVRET);

		ENB_Kelvin->SetTestResult(SITE, 0, V_Kelvin[SITE]);
	}
	dioplus.Disconnect("ENB");

	//SCL kelvin check
	dioplus.Connect("SCL");
	SCL.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_SENSE_ON);
	delay_us(500);

	dioplus.Run("checkstart", "checkhigh");//set high level=3v
	delay_us(500);
	SCL.MeasureVI(10, 10);

	dioplus.Run("checkhigh", "checkstop");//set high Z
	SCL.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

	SERIAL
	{
		V_Kelvin[SITE] = SCL.GetMeasResult(SITE, MVRET);

		SCL_Kelvin->SetTestResult(SITE, 0, V_Kelvin[SITE]);
	}
	dioplus.Disconnect("SCL");

	//SDA kelvin check
	dioplus.Connect("SDA");
	SDA.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_SENSE_ON);
	delay_us(500);

	dioplus.Run("checkstart", "checkhigh");//set high level=3v
	delay_us(500);
	SDA.MeasureVI(10, 10);

	dioplus.Run("checkhigh", "checkstop");//set high Z
	SDA.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

	SERIAL
	{
		V_Kelvin[SITE] = SDA.GetMeasResult(SITE, MVRET);

		SDA_Kelvin->SetTestResult(SITE, 0, V_Kelvin[SITE]);
	}
	dioplus.Disconnect("SDA");

	//cbit.SetOn(K2_VRECT_V5V_CAP, -1);
	//wait_relay();
	//VRECT.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	//delay_us(200);
	//VRECT.Set(FI, 0.0001, FOVI_5V, FOVI_10MA, RELAY_ON);
	//delay_us(2000);

	//VRECT.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = VRECT.GetMeasResult(site, MVRET);
	//	adresult2[site] = VRECT.GetMeasResult(site, MIRET);
	//	adresult[site] = adresult1[site] / (adresult2[site] + 1e-32);

	//	VRECT_Kelvin->SetTestResult(site, 0, adresult[site]);// ohm

	//}
	//VRECT.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	//delay_us(1000);
	//VRECT.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	//delay_us(200);

	//cbit.SetOn(-1);
	//wait_relay();
	//V5V.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	//delay_us(200);
	//V5V.Set(FI, -0.0001, FOVI_5V, FOVI_10MA, RELAY_ON);
	//delay_us(3000);

	//V5V.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = V5V.GetMeasResult(site, MVRET);
	//	adresult2[site] = V5V.GetMeasResult(site, MIRET);
	//	adresult[site] = adresult1[site] / (adresult2[site] + 1e-32)*1e-3;

	//	V5V_Kelvin->SetTestResult(site, 0, adresult[site]);// Kohm

	//}
	//V5V.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	//delay_us(1000);
	//V5V.Set(FI, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	//delay_us(200);

	//cbit.SetOn(K21_PGNDF_PGNDS, -1);
	//wait_relay();
	//INTB.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	//delay_us(200);
	//INTB.Set(FI, -0.0001, FOVI_2V, FOVI_10MA, RELAY_ON);
	//delay_us(1000);

	//INTB.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = INTB.GetMeasResult(site, MVRET);
	//	adresult2[site] = INTB.GetMeasResult(site, MIRET);
	//	adresult[site] = adresult1[site] / (adresult2[site] + 1e-32);

	//	INTB_Kelvin->SetTestResult(site, 0, adresult1[site]);

	//}
	//INTB.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	//delay_us(1000);
	//INTB.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	//delay_us(200);

	//SINK.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	//delay_us(200);
	//SINK.Set(FV, 1, FOVI_2V, FOVI_10MA, RELAY_ON);
	//delay_us(1000);

	//SINK.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = SINK.GetMeasResult(site, MVRET);
	//	//adresult2[site] = SINK.GetMeasResult(site, MIRET);
	//	//adresult[site] = adresult1[site] / (adresult2[site] + 1e-32);
	//	
	//	SINK_Kelvin->SetTestResult(site, 0, adresult1[site]);

	//}
	//SINK.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	//delay_us(1000);
	//SINK.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	//delay_us(200);

	//AC1.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(200);
	//AC1.Set(FI, 0.0001, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);

	//AC1.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = AC1.GetMeasResult(site, MVRET);
	//	adresult2[site] = AC1.GetMeasResult(site, MIRET);
	//	adresult[site] = adresult1[site] / (adresult2[site] + 1e-32);

	//	AC1_Kelvin->SetTestResult(site, 0, adresult[site]);// ohm

	//}
	//AC1.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);
	//AC1.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_OFF);
	//delay_us(200);

	//AC2.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(200);
	//AC2.Set(FI, 0.0001, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);

	//AC2.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = AC2.GetMeasResult(site, MVRET);
	//	adresult2[site] = AC2.GetMeasResult(site, MIRET);
	//	adresult[site] = adresult1[site] / (adresult2[site] + 1e-32);

	//	AC2_Kelvin->SetTestResult(site, 0, adresult[site]);// ohm

	//}
	//AC2.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);
	//AC2.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_OFF);
	//delay_us(200);

	//ENB.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(200);
	//ENB.Set(FI, 0.01, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);

	//ENB.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = ENB.GetMeasResult(site, MVRET);
	//	adresult2[site] = ENB.GetMeasResult(site, MIRET);
	//	adresult[site] = adresult1[site] / (adresult2[site] + 1e-32);

	//	ENB_Kelvin->SetTestResult(site, 0, adresult[site]);// ohm

	//}
	//ENB.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);
	//ENB.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_OFF);
	//delay_us(200);

	//VOUT.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(200);
	//VOUT.Set(FI, 0.01, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);

	//VOUT.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = VOUT.GetMeasResult(site, MVRET);
	//	adresult2[site] = VOUT.GetMeasResult(site, MIRET);
	//	adresult[site] = adresult1[site] / (adresult2[site] + 1e-32);

	//	VOUT_Kelvin->SetTestResult(site, 0, adresult[site]);// ohm

	//}
	//VOUT.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);
	//VOUT.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_OFF);
	//delay_us(200);

	//cbit.SetOn(K_OVI_CHB, -1);//SCL,SDA,COMM1,COMM2 connect FOVI RES
	//SCL.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(200);
	//SCL.Set(FI, 0.01, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);

	//SCL.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = SCL.GetMeasResult(site, MVRET);
	//	adresult2[site] = SCL.GetMeasResult(site, MIRET);
	//	adresult[site] = adresult1[site] / (adresult2[site] + 1e-32);

	//	SCL_Kelvin->SetTestResult(site, 0, adresult[site]);// ohm

	//}
	//SCL.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);
	//SCL.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_OFF);
	//delay_us(200);

	//SDA.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(200);
	//SDA.Set(FI, 0.01, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);

	//SDA.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = SDA.GetMeasResult(site, MVRET);
	//	adresult2[site] = SDA.GetMeasResult(site, MIRET);
	//	adresult[site] = adresult1[site] / (adresult2[site] + 1e-32);

	//	SDA_Kelvin->SetTestResult(site, 0, adresult[site]);// ohm

	//}
	//SDA.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);
	//SDA.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_OFF);
	//delay_us(200);

	//COMM1.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(200);
	//COMM1.Set(FI, 0.01, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);

	//COMM1.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = COMM1.GetMeasResult(site, MVRET);
	//	adresult2[site] = COMM1.GetMeasResult(site, MIRET);
	//	adresult[site] = adresult1[site] / (adresult2[site] + 1e-32);

	//	COMM1_Kelvin->SetTestResult(site, 0, adresult[site]);// ohm

	//}
	//COMM1.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);
	//COMM1.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_OFF);
	//delay_us(200);

	//COMM2.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(200);
	//COMM2.Set(FI, 0.01, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);

	//COMM2.MeasureVI(30, 10);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	adresult1[site] = COMM2.GetMeasResult(site, MVRET);
	//	adresult2[site] = COMM2.GetMeasResult(site, MIRET);
	//	adresult[site] = adresult1[site] / (adresult2[site] + 1e-32);

	//	COMM2_Kelvin->SetTestResult(site, 0, adresult[site]);// ohm

	//}
	//COMM2.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_ON);
	//delay_us(1000);
	//COMM2.Set(FI, 0, FOVI_2V, FOVI_100MA, RELAY_OFF);
	//delay_us(200);


	return 0;
}

DUT_API int P2P_LEAKAGE(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *P2P_LEAKAGE_INTB = StsGetParam(funcindex, "P2P_LEAKAGE_INTB");
    CParam *P2P_LEAKAGE_SINK = StsGetParam(funcindex, "P2P_LEAKAGE_SINK");
    CParam *P2P_LEAKAGE_VRECT = StsGetParam(funcindex, "P2P_LEAKAGE_VRECT");
    CParam *P2P_LEAKAGE_AC2 = StsGetParam(funcindex, "P2P_LEAKAGE_AC2");
    CParam *P2P_LEAKAGE_COMM2 = StsGetParam(funcindex, "P2P_LEAKAGE_COMM2");
    CParam *P2P_LEAKAGE_AC1 = StsGetParam(funcindex, "P2P_LEAKAGE_AC1");
    CParam *P2P_LEAKAGE_COMM1 = StsGetParam(funcindex, "P2P_LEAKAGE_COMM1");
    CParam *P2P_LEAKAGE_V5V = StsGetParam(funcindex, "P2P_LEAKAGE_V5V");
    CParam *P2P_LEAKAGE_VOUT = StsGetParam(funcindex, "P2P_LEAKAGE_VOUT");
    CParam *P2P_LEAKAGE_ENB = StsGetParam(funcindex, "P2P_LEAKAGE_ENB");
    CParam *P2P_LEAKAGE_SCL = StsGetParam(funcindex, "P2P_LEAKAGE_SCL");
    CParam *P2P_LEAKAGE_SDA = StsGetParam(funcindex, "P2P_LEAKAGE_SDA");
    CParam *P2P_LEAKAGE_INTB_R = StsGetParam(funcindex, "P2P_LEAKAGE_INTB_R");
    CParam *P2P_LEAKAGE_SINK_R = StsGetParam(funcindex, "P2P_LEAKAGE_SINK_R");
    CParam *P2P_LEAKAGE_VRECT_R = StsGetParam(funcindex, "P2P_LEAKAGE_VRECT_R");
    CParam *P2P_LEAKAGE_AC2_R = StsGetParam(funcindex, "P2P_LEAKAGE_AC2_R");
    CParam *P2P_LEAKAGE_COMM2_R = StsGetParam(funcindex, "P2P_LEAKAGE_COMM2_R");
    CParam *P2P_LEAKAGE_AC1_R = StsGetParam(funcindex, "P2P_LEAKAGE_AC1_R");
    CParam *P2P_LEAKAGE_COMM1_R = StsGetParam(funcindex, "P2P_LEAKAGE_COMM1_R");
    CParam *P2P_LEAKAGE_V5V_R = StsGetParam(funcindex, "P2P_LEAKAGE_V5V_R");
    CParam *P2P_LEAKAGE_VOUT_R = StsGetParam(funcindex, "P2P_LEAKAGE_VOUT_R");
    CParam *P2P_LEAKAGE_ENB_R = StsGetParam(funcindex, "P2P_LEAKAGE_ENB_R");
    CParam *P2P_LEAKAGE_SCL_R = StsGetParam(funcindex, "P2P_LEAKAGE_SCL_R");
    CParam *P2P_LEAKAGE_SDA_R = StsGetParam(funcindex, "P2P_LEAKAGE_SDA_R");
    CParam *NO_RETEST = StsGetParam(funcindex, "NO_RETEST");
//}}AFX_STS_PARAM_PROTOTYPES
	// TODO: Add your function code here

	double VIN = 0.05;
	double adresult[SITE_COUNT] = { 1, 1, 1, 1, 1, 1, 1, 1 };
	int first_test_flag[SITE_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };  // 1 fail,0 pass
	int second_test_flag[SITE_COUNT] = { 1, 1, 1, 1, 1, 1, 1, 1 }; // 1 fail,0 pass. 默认第二次测试为fail，若pass则no retest
	int no_retest_flag[SITE_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };   // 1 fail,0 pass
	double low_limit = 0;
	double high_limit = 0;
	double bc_array[SITE_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };//烧断时用数组传参给测试机
	double rt_array[SITE_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };//第二次测P2P时用数组传参给测试机

	BYTE sitestatus[SITE_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };//判断工位是否有效 1有效 0被屏蔽
	StsGetSiteStatus(sitestatus, SITE_COUNT);


	//为数据连贯，默认第二次全pass
	FOR_EACH_VALID_SITE(site)
	{
		P2P_LEAKAGE_SCL_R->SetTestResult(site, 0, 0);
		P2P_LEAKAGE_SDA_R->SetTestResult(site, 0, 0);
		P2P_LEAKAGE_COMM1_R->SetTestResult(site, 0, 0);
		P2P_LEAKAGE_COMM2_R->SetTestResult(site, 0, 0);
		P2P_LEAKAGE_SINK_R->SetTestResult(site, 0, 0);
		P2P_LEAKAGE_INTB_R->SetTestResult(site, 0, 0);
		P2P_LEAKAGE_AC1_R->SetTestResult(site, 0, 0);
		P2P_LEAKAGE_AC2_R->SetTestResult(site, 0, 0);
		P2P_LEAKAGE_VRECT_R->SetTestResult(site, 0, 0);
		P2P_LEAKAGE_V5V_R->SetTestResult(site, 0, 0);
		P2P_LEAKAGE_VOUT_R->SetTestResult(site, 0, 0);
		P2P_LEAKAGE_ENB_R->SetTestResult(site, 0, 0);
	}

	CParam *p2p_output[12] = {
		P2P_LEAKAGE_INTB, P2P_LEAKAGE_SINK, P2P_LEAKAGE_VRECT, P2P_LEAKAGE_AC2, P2P_LEAKAGE_COMM2,
		P2P_LEAKAGE_COMM1, P2P_LEAKAGE_AC1, P2P_LEAKAGE_V5V, P2P_LEAKAGE_VOUT, P2P_LEAKAGE_ENB,
		P2P_LEAKAGE_SCL, P2P_LEAKAGE_SDA
	};
	int tk = 0;
	//用于记录第一次测试是否有fail，若有，需要进行烧断测试
	int ftd_array[12];//记录第一次测试结果，可以定位到pad. 0 pass, 1 fail
	int ftr_array[12][SITE_COUNT];//记录第一次测试结果，可以定位到site，pad. 0 pass, 1 fail

	for (int pin = 0; pin < 12; pin++)
	{
		ftd_array[pin] = 0;
		FOR_EACH_VALID_SITE(site)
		{
			ftr_array[pin][site] = 0;
		}
	}

	ALLPINS_INITIALIZE_0V_1V_1MA_ON();

	//INTB
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;

	cbit.SetOn(K9_OVI5_AC2_SDA, -1);
	wait_relay();

	INTB.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	INTB.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	INTB.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = INTB.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_INTB->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[0][site] = 1;
			ftd_array[0] = 1;
			first_test_flag[site] = 1;
		}
	}

	INTB.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	INTB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);

	//SINK
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;
	//K8_OVI4_AC1_SCL close
	SINK.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	SINK.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	SINK.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = SINK.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_SINK->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[1][site] = 1;
			ftd_array[1] = 1;
			first_test_flag[site] = 1;
		}
	}

	SINK.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	SINK.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);

	//VRECT
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;
	//K8_OVI4_AC1_SCL close
	VRECT.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	VRECT.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	VRECT.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = VRECT.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_VRECT->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[2][site] = 1;
			ftd_array[2] = 1;
			first_test_flag[site] = 1;
		}
	}

	VRECT.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	VRECT.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);

	//AC2
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;

	cbit.SetOn(K11_OVI7_VOUT_COMM2, -1);
	wait_relay();

	AC2.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	AC2.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	AC2.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = AC2.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_AC2->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[3][site] = 1;
			ftd_array[3] = 1;
			first_test_flag[site] = 1;
		}
	}

	AC2.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	AC2.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);

	//COMM2
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;
	//K11_OVI7_VOUT_COMM2 close
	COMM2.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	COMM2.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	COMM2.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = COMM2.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_COMM2->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[4][site] = 1;
			ftd_array[4] = 1;
			first_test_flag[site] = 1;
		}
	}

	COMM2.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	COMM2.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);

	//COMM1
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;

	cbit.SetOn(K10_OVI6_ENB_COMM1, -1);
	wait_relay();

	COMM1.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	COMM1.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	COMM1.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = COMM1.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_COMM1->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[5][site] = 1;
			ftd_array[5] = 1;
			first_test_flag[site] = 1;
		}
	}

	COMM1.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	COMM1.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);


	//AC1
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;
	//K10_OVI6_ENB_COMM1 close
	AC1.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	AC1.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	AC1.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = AC1.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_AC1->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[6][site] = 1;
			ftd_array[6] = 1;
			first_test_flag[site] = 1;
		}
	}

	AC1.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	AC1.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);

	//V5V
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;
	//K10_OVI6_ENB_COMM1 close
	V5V.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	V5V.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	V5V.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = V5V.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_V5V->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[7][site] = 1;
			ftd_array[7] = 1;
			first_test_flag[site] = 1;
		}
	}

	V5V.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	V5V.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);

	//VOUT
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;
	//K10_OVI6_ENB_COMM1 close
	VOUT.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	VOUT.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	VOUT.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = VOUT.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_VOUT->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[8][site] = 1;
			ftd_array[8] = 1;
			first_test_flag[site] = 1;
		}
	}

	VOUT.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	VOUT.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);

	//ENB
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;

	cbit.SetOn(K8_OVI4_AC1_SCL, -1);
	wait_relay();

	ENB.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	ENB.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	ENB.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = ENB.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_ENB->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[9][site] = 1;
			ftd_array[9] = 1;
			first_test_flag[site] = 1;
		}
	}

	ENB.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	ENB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);

	//SCL
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;

	cbit.SetOn(K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA, -1);
	wait_relay();

	SCL.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	SCL.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	SCL.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = SCL.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_SCL->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[10][site] = 1;
			ftd_array[10] = 1;
			first_test_flag[site] = 1;
		}
	}

	SCL.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	SCL.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);

	//SDA
	low_limit = p2p_output[tk]->GetMinLimit()* 1e-9;
	high_limit = p2p_output[tk]->GetMaxLimit()* 1e-9;
	tk += 1;
	//K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA close
	SDA.Set(FV, VIN, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_us(500);
	SDA.Set(FV, VIN, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);

	SDA.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = SDA.GetMeasResult(site, MIRET);

		P2P_LEAKAGE_SDA->SetTestResult(site, 0, adresult[site] * 1E+9);//nA

		if ((adresult[site] < low_limit || adresult[site] > high_limit) && sitestatus[site] == 1)
		{
			ftr_array[11][site] = 1;
			ftd_array[11] = 1;
			first_test_flag[site] = 1;
		}
	}

	SDA.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	SDA.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);

	//第一次P2P测完,检索fail进行烧断测试
	for (int pin = 0; pin < 12; pin++)//遍历12个pad
	{
		if (ftd_array[pin] == 1)//定位到出现fail的pad
		{
			//bc_array[0] = 0;
			//bc_array[1] = 0;
			//bc_array[2] = 0;
			//bc_array[3] = 0;
			//rt_array[0] = 0;
			//rt_array[1] = 0;
			//rt_array[2] = 0;
			//rt_array[3] = 0;
			FOR_EACH_VALID_SITE(site)//定位到是哪个site，更新数组，准备传参
			{
				if (ftr_array[pin][site] == 1)
				{
					bc_array[site] = 0.01;//10mA
					rt_array[site] = VIN;//50mV
				}
			}

			low_limit = p2p_output[pin]->GetMinLimit()* 1e-9;
			high_limit = p2p_output[pin]->GetMaxLimit()* 1e-9;

			if (pin == 0)//INTB
			{
				cbit.SetOn(K9_OVI5_AC2_SDA, -1);
				wait_relay();

				INTB.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				INTB.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				INTB.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				INTB.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				INTB.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				INTB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				INTB.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				INTB.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				INTB.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = INTB.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_INTB_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				INTB.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				INTB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}

			if (pin == 1)//SINK
			{
				//K8_OVI4_AC1_SCL close
				SINK.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SINK.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SINK.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				SINK.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SINK.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SINK.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				SINK.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				SINK.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				SINK.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = SINK.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_SINK_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				SINK.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				SINK.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}

			if (pin == 2)//VRECT
			{
				//K8_OVI4_AC1_SCL close
				VRECT.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				VRECT.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				VRECT.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				VRECT.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				VRECT.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				VRECT.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				VRECT.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				VRECT.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				VRECT.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = VRECT.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_VRECT_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				VRECT.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				VRECT.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}

			if (pin == 3)//AC2
			{
				cbit.SetOn(K11_OVI7_VOUT_COMM2, -1);
				wait_relay();

				AC2.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				AC2.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				AC2.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				AC2.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				AC2.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				AC2.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				AC2.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				AC2.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				AC2.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = AC2.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_AC2_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				AC2.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				AC2.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}

			if (pin == 4)//COMM2
			{
				//K11_OVI7_VOUT_COMM2 close
				COMM2.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				COMM2.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				COMM2.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				COMM2.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				COMM2.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				COMM2.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				COMM2.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				COMM2.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				COMM2.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = COMM2.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_COMM2_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				COMM2.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				COMM2.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}

			if (pin == 5)//COMM1
			{
				cbit.SetOn(K10_OVI6_ENB_COMM1, -1);
				wait_relay();

				COMM1.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				COMM1.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				COMM1.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				COMM1.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				COMM1.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				COMM1.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				COMM1.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				COMM1.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				COMM1.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = COMM1.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_COMM1_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				COMM1.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				COMM1.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}

			if (pin == 6)//AC1
			{
				//K10_OVI6_ENB_COMM1 close
				AC1.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				AC1.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				AC1.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				AC1.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				AC1.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				AC1.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				AC1.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				AC1.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				AC1.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = AC1.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_AC1_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				AC1.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				AC1.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}

			if (pin == 7)//V5V
			{
				//K10_OVI6_ENB_COMM1 close
				V5V.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				V5V.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				V5V.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				V5V.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				V5V.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				V5V.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				V5V.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				V5V.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				V5V.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = V5V.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_V5V_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				V5V.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				V5V.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}

			if (pin == 8)//VOUT
			{
				//K10_OVI6_ENB_COMM1 close
				VOUT.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				VOUT.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				VOUT.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				VOUT.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				VOUT.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				VOUT.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				VOUT.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				VOUT.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				VOUT.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = VOUT.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_VOUT_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				VOUT.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				VOUT.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}

			if (pin == 9)//ENB
			{
				cbit.SetOn(K8_OVI4_AC1_SCL, -1);
				wait_relay();

				ENB.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				ENB.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				ENB.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				ENB.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				ENB.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				ENB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				ENB.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				ENB.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				ENB.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = ENB.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_ENB_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				ENB.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				ENB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}

			if (pin == 10)//SCL
			{
				cbit.SetOn(K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA, -1);
				wait_relay();

				SCL.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SCL.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SCL.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				SCL.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SCL.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SCL.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				SCL.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				SCL.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				SCL.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = SCL.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_SCL_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				SCL.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				SCL.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}

			if (pin == 11)//SDA
			{
				//K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA close
				SDA.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SDA.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SDA.SetSyn(FI, bc_array, SITE_COUNT, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_ms(5);
				SDA.Set(FI, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SDA.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
				delay_us(500);
				SDA.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);

				SDA.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1MA, RELAY_ON);
				delay_us(500);
				SDA.SetSyn(FV, rt_array, SITE_COUNT, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);

				SDA.MeasureVI(50, 10);

				FOR_EACH_VALID_SITE(site)
				{
					adresult[site] = SDA.GetMeasResult(site, MIRET);

					if (ftr_array[pin][site] == 1)
					{
						P2P_LEAKAGE_SDA_R->SetTestResult(site, 0, adresult[site] * 1E+9);

						if (adresult[site] > low_limit && adresult[site] < high_limit)
						{
							second_test_flag[site] = 0;
						}
					}
				}

				SDA.Set(FV, 0, FOVI_1V, FOVI_1UA, RELAY_ON);
				delay_us(500);
				SDA.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
			}
		}
	}

	FOVI_ALL.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_OFF);
	delay_ms(1);

	FOR_EACH_VALID_SITE(site)
	{
		if (first_test_flag[site] == 1 && second_test_flag[site] == 0)//第一次P2P有fail，且有pad在烧断后pass
		{
			no_retest_flag[site] = 1;
		}

		NO_RETEST->SetTestResult(site, 0, no_retest_flag[site]);
	}

	cbit.SetOn(-1);
	return 0;
}
 

 
DUT_API int INIT_OS(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *VRECT_INIT_OS = StsGetParam(funcindex, "VRECT_INIT_OS");
    CParam *V5V_INIT_OS = StsGetParam(funcindex, "V5V_INIT_OS");
    CParam *INTB_INIT_OS = StsGetParam(funcindex, "INTB_INIT_OS");
    CParam *SINK_INIT_OS = StsGetParam(funcindex, "SINK_INIT_OS");
    CParam *AC1_INIT_OS = StsGetParam(funcindex, "AC1_INIT_OS");
    CParam *AC2_INIT_OS = StsGetParam(funcindex, "AC2_INIT_OS");
    CParam *ENB_INIT_OS = StsGetParam(funcindex, "ENB_INIT_OS");
    CParam *VOUT_INIT_OS = StsGetParam(funcindex, "VOUT_INIT_OS");
    CParam *SCL_INIT_OS = StsGetParam(funcindex, "SCL_INIT_OS");
    CParam *SDA_INIT_OS = StsGetParam(funcindex, "SDA_INIT_OS");
    CParam *COMM1_INIT_OS = StsGetParam(funcindex, "COMM1_INIT_OS");
    CParam *COMM2_INIT_OS = StsGetParam(funcindex, "COMM2_INIT_OS");
    CParam *VRECT_AC1_INIT_OS = StsGetParam(funcindex, "VRECT_AC1_INIT_OS");
    CParam *VRECT_AC2_INIT_OS = StsGetParam(funcindex, "VRECT_AC2_INIT_OS");
    CParam *VRECT_VOUT_INIT_OS = StsGetParam(funcindex, "VRECT_VOUT_INIT_OS");
    CParam *VRECT_V5V_INIT_OS = StsGetParam(funcindex, "VRECT_V5V_INIT_OS");
    CParam *VRECT_COMM1_INIT_OS = StsGetParam(funcindex, "VRECT_COMM1_INIT_OS");
    CParam *VRECT_COMM2_INIT_OS = StsGetParam(funcindex, "VRECT_COMM2_INIT_OS");
    CParam *Temp_OS = StsGetParam(funcindex, "Temp_OS");
    CParam *Temp_delta = StsGetParam(funcindex, "Temp_delta");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	double	i_1mA = -1e-3;
	ALLPINS_INITIALIZE_0V_2V_10MA_ON();
	FOVI_ALL.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	FOVI_ALL.Set(FI, i_1mA, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	FOVI_ALL.MeasureVI(200, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = VRECT.GetMeasResult(site, MVRET);
		VRECT_INIT_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = V5V.GetMeasResult(site, MVRET);
		V5V_INIT_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = INTB.GetMeasResult(site, MVRET);
		INTB_INIT_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = SINK.GetMeasResult(site, MVRET);
		SINK_INIT_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = AC1.GetMeasResult(site, MVRET);
		AC1_INIT_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = AC2.GetMeasResult(site, MVRET);
		AC2_INIT_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = ENB.GetMeasResult(site, MVRET);
		ENB_INIT_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = VOUT.GetMeasResult(site, MVRET);
		VOUT_INIT_OS->SetTestResult(site, 0, adresult[site]);
	}
	FOVI_ALL.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	FOVI_ALL.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);

	cbit.SetOn(K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA, K10_OVI6_ENB_COMM1, K11_OVI7_VOUT_COMM2, -1);
	wait_relay();
	FOVI_CHB.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	FOVI_CHB.Set(FI, i_1mA, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	FOVI_CHB.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = SCL.GetMeasResult(site, MVRET);
		SCL_INIT_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = SDA.GetMeasResult(site, MVRET);
		SDA_INIT_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = COMM1.GetMeasResult(site, MVRET);
		COMM1_INIT_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = COMM2.GetMeasResult(site, MVRET);
		COMM2_INIT_OS->SetTestResult(site, 0, adresult[site]);

		Temp_OS->SetTestResult(site, 0, 0);
		Temp_delta->SetTestResult(site, 0, 0);
	}
	FOVI_CHB.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	FOVI_CHB.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	
	if (Global_Tempchar_Program_Flag == 1)
	{
		//Temperature//-40 -20 0 25 85 100 125
		double adresult_scl[SITE_COUNT] = { 0, 0, 0, 0, 0, 0, 0, 0 };
		SCL.Set(FI, i_1mA, FOVI_2V, FOVI_10MA, RELAY_ON);
		delay_ms(20);
		SCL.MeasureVI(50, 10);
		FOR_EACH_VALID_SITE(site)
		{
			adresult_scl[site] = SCL.GetMeasResult(site, MVRET);

			Global_temp[site] = (adresult_scl[site] + 0.6206) / 0.001;

			Temp_OS->SetTestResult(site, 0, Global_temp[site]);
			Temp_delta->SetTestResult(site, 0, Global_temp[site] - Temperature);
		}
		SCL.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
		delay_ms(5);
		SCL.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
		delay_ms(3);
		SCL.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
		delay_ms(1);
	}


	//Diode
	//FOR_EACH_VALID_SITE(site)
	//{
		//TC_GO->SetTestResult(site, 0, ask_tc_flag);
	//}


	//VRECT-AC1
	cbit.SetOn(K12_PVI0H_VRECT, K15_PVI0L_AC1, -1);
	wait_relay();
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	VRECT.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_AC1_INIT_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	//VRECT-AC2
	cbit.SetOn(K12_PVI0H_VRECT, K16_PVI0L_AC2, -1);
	wait_relay();

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_AC2_INIT_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	//VRECT-VOUT
	cbit.SetOn(K12_PVI0H_VRECT, K17_PVI0L_VOUT, -1);
	wait_relay();

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_VOUT_INIT_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	//VRECT-V5V
	cbit.SetOn(K12_PVI0H_VRECT, K18_PVI0L_V5V, -1);
	wait_relay();

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_V5V_INIT_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	//VRECT-COMM1
	cbit.SetOn(K12_PVI0H_VRECT, K27_PVI0L_COMM1, -1);
	wait_relay();

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_COMM1_INIT_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	//VRECT-COMM2
	cbit.SetOn(K12_PVI0H_VRECT, K20_PVI0L_COMM2, -1);
	wait_relay();

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_COMM2_INIT_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_OFF);
	VRECT.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);

    return 0;
}
 
DUT_API int INIT_LEAKAGE(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *IQ_STRESS_VRECT_DS = StsGetParam(funcindex, "IQ_STRESS_VRECT_DS");
    CParam *ISHUTDOWN_STRESS_VRECT = StsGetParam(funcindex, "ISHUTDOWN_STRESS_VRECT");
    CParam *V5V_INIT_LEAK = StsGetParam(funcindex, "V5V_INIT_LEAK");
    CParam *AC1_HS_INIT_LEAK_SCM = StsGetParam(funcindex, "AC1_HS_INIT_LEAK_SCM");
    CParam *AC1_LS_INIT_LEAK_SCM = StsGetParam(funcindex, "AC1_LS_INIT_LEAK_SCM");
    CParam *AC2_HS_INIT_LEAK_SCM = StsGetParam(funcindex, "AC2_HS_INIT_LEAK_SCM");
    CParam *AC2_LS_INIT_LEAK_SCM = StsGetParam(funcindex, "AC2_LS_INIT_LEAK_SCM");
    CParam *VOUT_INIT_LEAK = StsGetParam(funcindex, "VOUT_INIT_LEAK");
    CParam *VRECT_INIT_LEAK = StsGetParam(funcindex, "VRECT_INIT_LEAK");
    CParam *ENB_INIT_LEAK = StsGetParam(funcindex, "ENB_INIT_LEAK");
    CParam *VRECT_VOUT_INIT_LEAK_17V = StsGetParam(funcindex, "VRECT_VOUT_INIT_LEAK_17V");
    CParam *VRECT_COMM1_INIT_LEAK_17V = StsGetParam(funcindex, "VRECT_COMM1_INIT_LEAK_17V");
    CParam *VRECT_COMM2_INIT_LEAK_17V = StsGetParam(funcindex, "VRECT_COMM2_INIT_LEAK_17V");
    CParam *INTB_INIT_LEAK = StsGetParam(funcindex, "INTB_INIT_LEAK");
    CParam *SINK_INIT_LEAK_SCM = StsGetParam(funcindex, "SINK_INIT_LEAK_SCM");
    CParam *SCL_INIT_LEAK = StsGetParam(funcindex, "SCL_INIT_LEAK");
    CParam *SDA_INIT_LEAK = StsGetParam(funcindex, "SDA_INIT_LEAK");
    CParam *COMM1_INIT_LEAK_SCM = StsGetParam(funcindex, "COMM1_INIT_LEAK_SCM");
    CParam *COMM2_INIT_LEAK_SCM = StsGetParam(funcindex, "COMM2_INIT_LEAK_SCM");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here
	ask_tc_flag = 1;

	//IQ
	dioplus.I2CConnect();

	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_us(200);
	VRECT.Set(FV, VRECT_Volt, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);

	manager.setfields({ { FORCE_DMY_OFF, 1 } });
	delay_ms(1);

	VRECT.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = VRECT.GetMeasResult(site, MIRET);
		IQ_STRESS_VRECT_DS->SetTestResult(site, 0, adresult[site] * 1E+3);
	}
	manager.setfields({ { FORCE_DMY_OFF, 0 } });

	//Ishutdown
	ENB.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	VRECT.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = VRECT.GetMeasResult(site, MIRET);
		ISHUTDOWN_STRESS_VRECT->SetTestResult(site, 0, adresult[site] * 1E+3);
	}


	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);

	//AC1 HS Leakage
	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, -1);
	wait_relay();
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_us(200);
	VRECT.Set(FV, 5.5, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	manager.setfields({ { FORCE_RECT_LS_OFF, 1 }, { FORCE_RECT_HS_OFF, 1 } });
	delay_us(500);

	VRECT.Set(FV, 17, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	AC1.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(10);//拉低AC
	AC1.Set(FV, 0, FOVI_20V, FOVI_100UA, RELAY_ON);
	delay_ms(30);//等待AC稳定

	if (Global_Tempchar_Program_Flag == 1)
	{
		delay_ms(2);
	}
	AC1.MeasureVI(100, 10);
	FOR_EACH_VALID_SITE(site)
	{
		AC1_HS_init[site] = AC1.GetMeasResult(site, MIRET);
		AC1_HS_INIT_LEAK_SCM->SetTestResult(site, 0, AC1_HS_init[site] * 1E+6);
	}


	//ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//delay_ms(1);
	//ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);

	////AC1 HS Leakage
	////VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	////delay_us(500);
	////VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	////delay_us(500);
	////VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	////delay_us(500);
	//cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP/*, K1_AC_CAP*/, -1);
	//wait_relay();
	//TM_ENTER_vi(VRECT, 5.5, FOVI_20V, FOVI_100MA);
	//manager.setfields({ { FORCE_RECT_LS_OFF, 1 }, { FORCE_RECT_HS_OFF, 1 } });
	//delay_us(500);
	//I2CWriteAllSites(0XF7, 0X00);
	//delay_us(1000);


	//AC1.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON, 1);
	//delay_ms(10);
	//AC1.Set(FV, 0, FOVI_1V, FOVI_100UA, RELAY_ON, 1);
	//delay_ms(10);
	//VRECT.Set(FV, 17, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	//delay_ms(2);
	//if (Global_Tempchar_Program_Flag == 1)
	//{
	//	delay_ms(2);
	//}
	//AC1.MeasureVI(500, 100);
	//FOR_EACH_VALID_SITE(site)
	//{
	//	AC1_HS_init[site] = AC1.GetMeasResult(site, MIRET);
	//	AC1_HS_INIT_LEAK_SCM->SetTestResult(site, 0, AC1_HS_init[site] * 1E+6);
	//}

	//AC1.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	//delay_us(100);


	//AC1 LS Leakage
	AC1.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_us(100);

	AC1.Set(FV, 17, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	delay_ms(1);
	AC1.Set(FV, 17, FOVI_20V, FOVI_100UA, RELAY_ON);
	delay_ms(2);

	if (Global_Tempchar_Program_Flag == 1)
	{
		delay_ms(2);
	}
	AC1.MeasureVI(100, 10);
	FOR_EACH_VALID_SITE(site)
	{
		AC1_LS_init[site] = AC1.GetMeasResult(site, MIRET);
		AC1_LS_INIT_LEAK_SCM->SetTestResult(site, 0, AC1_LS_init[site] * 1E+6);
	}
	AC1.Set(FV, 17, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	AC1.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	AC1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_us(100);
	AC1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_OFF);
	delay_us(100);

	//AC2 HS Leakage
	//VRECT.Set(FV, 5.5, FOVI_20V, FOVI_100MA, RELAY_ON);
	//manager.setfields({ { FORCE_RECT_LS_OFF, 1 }, { FORCE_RECT_HS_OFF, 1 } });
	//delay_us(500);

	//VRECT.Set(FV, 17, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
	AC2.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	AC2.Set(FV, 0, FOVI_20V, FOVI_100UA, RELAY_ON);
	delay_ms(30);//等待AC稳定

	if (Global_Tempchar_Program_Flag == 1)
	{
		delay_ms(2);
	}
	AC2.MeasureVI(100, 10);
	FOR_EACH_VALID_SITE(site)
	{
		AC2_HS_init[site] = AC2.GetMeasResult(site, MIRET);
		AC2_HS_INIT_LEAK_SCM->SetTestResult(site, 0, AC2_HS_init[site] * 1E+6);
	}

	//AC2 LS Leakage
	AC2.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_us(100);

	AC2.Set(FV, 17, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	delay_ms(2);
	AC2.Set(FV, 17, FOVI_20V, FOVI_100UA, RELAY_ON);
	delay_ms(2);

	if (Global_Tempchar_Program_Flag == 1)
	{
		delay_ms(2);
	}
	AC2.MeasureVI(100, 10);
	FOR_EACH_VALID_SITE(site)
	{
		AC2_LS_init[site] = AC2.GetMeasResult(site, MIRET);
		AC2_LS_INIT_LEAK_SCM->SetTestResult(site, 0, AC2_LS_init[site] * 1E+6);
	}
	AC2.Set(FV, 17, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	AC2.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	delay_ms(1);
	AC2.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	delay_us(500);

	//VRECT-VOUT Leakage, VRECT=17V

	TM_ENTER_vi(VRECT, 5.5, FOVI_20V, FOVI_1A);
	VOUT.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);

	manager.setfields({ { FORCE_DMY_OFF, 1 }, { I2C_ILOAD_H, 1 } });
	delay_ms(1);

	VRECT.Set(FV, 17, FOVI_20V, FOVI_1A, RELAY_ON, 1);
	VOUT.Set(FV, 0, FOVI_5V, FOVI_100UA, RELAY_ON);
	delay_us(500);

	VOUT.MeasureVI(50, 10);

	FOR_EACH_VALID_SITE(site)
	{
		VRECT_VOUT_init[site] = VOUT.GetMeasResult(site, MIRET);

		VRECT_VOUT_INIT_LEAK_17V->SetTestResult(site, 0, VRECT_VOUT_init[site] * 1E+6);
	}
	VRECT.Set(FV, 0, FOVI_20V, FOVI_1A, RELAY_ON, 1);
	VOUT.Set(FV, 0, FOVI_5V, FOVI_100UA, RELAY_OFF);
	delay_us(500);

	//VRECT-COMM1 Leakage, VRECT=17V
	cbit.SetOn(K2_VRECT_V5V_CAP, K_OVI_CHB, -1);//FOVI connect SCL, SDA, COMM1, COMM2
	wait_relay();
	TM_ENTER_vi(VRECT, 5.5, FOVI_20V, FOVI_1A);	
	manager.setfields({ { FORCE_DMY_OFF, 1 }, { I2C_ILOAD_H, 1 } });
	delay_ms(1);

	VRECT.Set(FV, 17, FOVI_20V, FOVI_1A, RELAY_ON, 0.5);
	COMM1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	COMM1.Set(FV, 0, FOVI_5V, FOVI_1UA, RELAY_ON);
	delay_ms(1);

	COMM1.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		VRECT_COMM1_init[site] = COMM1.GetMeasResult(site, MIRET);
		VRECT_COMM1_INIT_LEAK_17V->SetTestResult(site, 0, VRECT_COMM1_init[site] * 1E+9);
	}
	COMM1.Set(FV, 0, FOVI_5V, FOVI_1UA, RELAY_OFF);
	delay_us(500);

	//VRECT-COMM2 Leakage, VRECT=17V
	COMM2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	COMM2.Set(FV, 0, FOVI_5V, FOVI_1UA, RELAY_ON);
	delay_ms(1);

	COMM2.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		VRECT_COMM2_init[site] = COMM2.GetMeasResult(site, MIRET);
		VRECT_COMM2_INIT_LEAK_17V->SetTestResult(site, 0, VRECT_COMM2_init[site] * 1E+9);
	}
	VRECT.Set(FV, 0, FOVI_20V, FOVI_1A, RELAY_ON, 1);
	delay_ms(1);
	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	COMM2.Set(FV, 0, FOVI_5V, FOVI_1UA, RELAY_OFF);
	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	delay_us(500);

	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 } });
	delay_ms(2);
	dioplus.I2CDisconnect();

	//INTB Leakage
	INTB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	INTB.Set(FV, 6, FOVI_10V, FOVI_10MA, RELAY_ON);//MAX=6V
	delay_ms(1);
	INTB.Set(FV, 6, FOVI_10V, FOVI_1UA, RELAY_ON);//MAX=6V
	delay_us(500);
	INTB.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		INTB_init[site] = INTB.GetMeasResult(site, MIRET);
		INTB_INIT_LEAK->SetTestResult(site, 0, INTB_init[site] * 1E+9);
	}
	INTB.Set(FV, 6, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_us(100);
	INTB.Set(FV, 6, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_us(100);
	INTB.Set(FV, 6, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);
	INTB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	INTB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	//SINK Leakage
	SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	SINK.Set(FV, 17, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	SINK.Set(FV, 17, FOVI_20V, FOVI_1UA, RELAY_ON);
	delay_us(1000);
	SINK.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		SINK_init[site] = SINK.GetMeasResult(site, MIRET);
	
		SINK_INIT_LEAK_SCM->SetTestResult(site, 0, SINK_init[site] * 1E+9);
	}
	SINK.Set(FV, 17, FOVI_20V, FOVI_10UA, RELAY_ON);
	delay_us(500);
	SINK.Set(FV, 17, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);
	
	//SCL Leakage
	SCL.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	SCL.Set(FV, 6, FOVI_10V, FOVI_10MA, RELAY_ON, 1);//MAX=6V
	delay_ms(1);
	SCL.Set(FV, 6, FOVI_10V, FOVI_1UA, RELAY_ON);//MAX=6V
	delay_us(500);
	SCL.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		SCL_init[site] = SCL.GetMeasResult(site, MIRET);
		SCL_INIT_LEAK->SetTestResult(site, 0, SCL_init[site] * 1E+9);
	}
	SCL.Set(FV, 6, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_us(100);
	SCL.Set(FV, 6, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_us(100);
	SCL.Set(FV, 6, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);
	SCL.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	SCL.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	//SDA Leakage
	SDA.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	SDA.Set(FV, 6, FOVI_10V, FOVI_10MA, RELAY_ON, 1);//MAX=6V
	delay_ms(1);
	SDA.Set(FV, 6, FOVI_10V, FOVI_1UA, RELAY_ON);//MAX=6V
	delay_us(500);
	SDA.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		SDA_init[site] = SDA.GetMeasResult(site, MIRET);
		SDA_INIT_LEAK->SetTestResult(site, 0, SDA_init[site] * 1E+9);
	}
	SDA.Set(FV, 6, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_us(100); 
	SDA.Set(FV, 6, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_us(100); 
	SDA.Set(FV, 6, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);
	SDA.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);
	SDA.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	dioplus.I2CConnect();
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);//spike check add
	delay_us(500);
	TM_ENTER_vi(VRECT, 5.5, FOVI_20V, FOVI_1A);
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 } });
	VRECT.Set(FV, 17, FOVI_20V, FOVI_1A, RELAY_ON, 1);
	delay_us(500);

	//COMM1 Leakage
	COMM1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	COMM1.Set(FV, 17, FOVI_20V, FOVI_10MA, RELAY_ON, 0.5);
	delay_ms(1);
	COMM1.Set(FV, 17, FOVI_20V, FOVI_1UA, RELAY_ON);
	delay_ms(2); 
	COMM1.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		COMM1_init[site] = COMM1.GetMeasResult(site, MIRET);

		COMM1_INIT_LEAK_SCM->SetTestResult(site, 0, COMM1_init[site] * 1E+9);
	}
	COMM1.Set(FV, 17, FOVI_20V, FOVI_10UA, RELAY_ON);
	delay_us(500);
	COMM1.Set(FV, 17, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	COMM1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	COMM1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);

	//COMM2 Leakage
	COMM2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	COMM2.Set(FV, 17, FOVI_20V, FOVI_10MA, RELAY_ON, 0.5);
	delay_ms(1);
	COMM2.Set(FV, 17, FOVI_20V, FOVI_1UA, RELAY_ON);
	delay_ms(2);
	COMM2.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		COMM2_init[site] = COMM2.GetMeasResult(site, MIRET);
		COMM2_INIT_LEAK_SCM->SetTestResult(site, 0, COMM2_init[site] * 1E+9);
	}
	COMM2.Set(FV, 17, FOVI_20V, FOVI_10UA, RELAY_ON);
	delay_us(500);
	COMM2.Set(FV, 17, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_1A, RELAY_ON, 1);
	COMM2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_1A, RELAY_OFF);
	COMM2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);
	cbit.SetOn(K2_VRECT_V5V_CAP, K4_IIC_PULLUP, -1);//FOVI connect AC1, AC2, ENB, VOUT
	//dioplus.I2CDisconnect();

	//ENB Leakage
	ENB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	ENB.Set(FV, 6, FOVI_10V, FOVI_10MA, RELAY_ON,0.5);
	delay_ms(1);
	ENB.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		ENB_init[site] = ENB.GetMeasResult(site, MIRET);
		ENB_INIT_LEAK->SetTestResult(site, 0, ENB_init[site] * 1E+6);
	}
	ENB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	ENB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	//V5V Leakage	
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//delay_us(500);

	VRECT.Set(FV, 6, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
	V5V.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);	
	manager.setfields({ { FORCE_DMY_OFF, 1 } });
	V5V.Set(FV, 6, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);

	V5V.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		V5V_init[site] = V5V.GetMeasResult(site, MIRET);

		V5V_INIT_LEAK->SetTestResult(site, 0, V5V_init[site] * 1E+3);
	}
	VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_us(500);
	VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_OFF);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);//OFF，否则影响VOUT leakage

	//VOUT Leakage
	VRECT.Set(FV, 10, FOVI_20V, FOVI_1A, RELAY_ON, 1);
	VOUT.Set(FV, 10, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	manager.setfields({ { I2C_CTRL, 1 }, { FORCE_DMY_OFF, 1 } });
	delay_us(500);

	VOUT.Set(FV, 10, FOVI_20V, FOVI_10MA, RELAY_ON, 0.5);
	delay_ms(1);
	VOUT.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		VOUT_init[site] = VOUT.GetMeasResult(site, MIRET);

		VOUT_INIT_LEAK->SetTestResult(site, 0, VOUT_init[site] * 1E+6);
	}
	VOUT.Set(FV, 10, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
	delay_us(500);
	//VRECT.Set(FV, 0, FOVI_20V, FOVI_1A, RELAY_ON);
	//V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//VOUT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	//delay_us(500);
	//
	//VRECT.Set(FV, 0, FOVI_20V, FOVI_1A, RELAY_OFF);
	//VOUT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	//
	////VRECT Leakage
	//TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);	
	manager.setfields({ { I2C_CTRL, 1 }, { FORCE_DMY_OFF, 1 }, { I2C_DIS_OVP_FAST, 1 } });
	delay_us(500);

	//int INIT_READ_AFTER[SITE_NUM] = { 0 };
	//dioplus.I2CReadAll(0XC0, 0X92, 1);
	//SERIAL INIT_READ_AFTER[SITE] = pI2CSites[SITE]->GetDataByteValue(0);

	VRECT.Set(FV, 17, FOVI_20V, FOVI_1A, RELAY_ON, 0.5);
	V5V.Set(FV, 5.1, FOVI_10V, FOVI_100MA, RELAY_ON);
	VOUT.Set(FV, 5.1, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);
	VRECT.Set(FV, 17, FOVI_20V, FOVI_10MA, RELAY_ON, 0.5);//need 10mA RANGE to save delay time
	delay_ms(15);//need,add cap

	VRECT.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		VRECT_init[site] = VRECT.GetMeasResult(site, MIRET);
		
		VRECT_INIT_LEAK->SetTestResult(site, 0, VRECT_init[site] * 1E+6);
	}
	VRECT.Set(FV, 17, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
	delay_us(200);

	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	VOUT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	VOUT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	
    return 0;
}

DUT_API int OVST_TEST(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *OVST_MLDO_delta = StsGetParam(funcindex, "OVST_MLDO_delta");
    CParam *OVST_MLDO_I1 = StsGetParam(funcindex, "OVST_MLDO_I1");
    CParam *OVST_MLDO_I2 = StsGetParam(funcindex, "OVST_MLDO_I2");
    CParam *OVST_MLDO_I3 = StsGetParam(funcindex, "OVST_MLDO_I3");
    CParam *OVST_HS_AC1_delta = StsGetParam(funcindex, "OVST_HS_AC1_delta");
    CParam *OVST_HS_AC1_I1 = StsGetParam(funcindex, "OVST_HS_AC1_I1");
    CParam *OVST_HS_AC1_I2 = StsGetParam(funcindex, "OVST_HS_AC1_I2");
    CParam *OVST_HS_AC1_I3 = StsGetParam(funcindex, "OVST_HS_AC1_I3");
    CParam *OVST_HS_AC2_delta = StsGetParam(funcindex, "OVST_HS_AC2_delta");
    CParam *OVST_HS_AC2_I1 = StsGetParam(funcindex, "OVST_HS_AC2_I1");
    CParam *OVST_HS_AC2_I2 = StsGetParam(funcindex, "OVST_HS_AC2_I2");
    CParam *OVST_HS_AC2_I3 = StsGetParam(funcindex, "OVST_HS_AC2_I3");
    CParam *OVST_LS_AC1_delta = StsGetParam(funcindex, "OVST_LS_AC1_delta");
    CParam *OVST_LS_AC1_I1 = StsGetParam(funcindex, "OVST_LS_AC1_I1");
    CParam *OVST_LS_IAC1 = StsGetParam(funcindex, "OVST_LS_IAC1");
    CParam *OVST_LS_AC1_I2 = StsGetParam(funcindex, "OVST_LS_AC1_I2");
    CParam *OVST_LS_AC1_I3 = StsGetParam(funcindex, "OVST_LS_AC1_I3");
    CParam *OVST_LS_AC2_delta = StsGetParam(funcindex, "OVST_LS_AC2_delta");
    CParam *OVST_LS_AC2_I1 = StsGetParam(funcindex, "OVST_LS_AC2_I1");
    CParam *OVST_LS_IAC2 = StsGetParam(funcindex, "OVST_LS_IAC2");
    CParam *OVST_LS_AC2_I2 = StsGetParam(funcindex, "OVST_LS_AC2_I2");
    CParam *OVST_LS_AC2_I3 = StsGetParam(funcindex, "OVST_LS_AC2_I3");
//}}AFX_STS_PARAM_PROTOTYPES
	// TODO: Add your function code here

	//MLDO OVST
	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K3_VOUT_CAP, - 1);
	dioplus.I2CConnect();
	wait_relay();

	VOUT.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	TM_ENTER_vi(VRECT, 5.5, FOVI_20V, FOVI_100MA);
	VOUT.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
	SINK.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	
	manager.setfields({ { I2C_CTRL, 1 }, { TMOD_CTRL, 7 } });
	delay_ms(1);

	SINK.Set(FV, 5.5, FOVI_20V, FOVI_100UA, RELAY_ON);
	delay_ms(2);
	SINK.MeasureVI(50, 10);
	SERIAL	adresult1[SITE] = SINK.GetMeasResult(SITE, MIRET);

	SINK.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	if (Global_FTQC_FLAG == 0)
	{
		SINK.Set(FV, 13, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(100);//wait 100ms stress
		SERIAL
		{
			adresult3[SITE] = SINK.GetMeasResult(SITE, MIRET);
			OVST_MLDO_I3->SetTestResult(SITE, 0, adresult3[SITE] * 1e6);//uA
		}
		SINK.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
	}
	SINK.Set(FV, 5.5, FOVI_20V, FOVI_100UA, RELAY_ON);
	delay_ms(2);
	SINK.MeasureVI(50, 10);

	SERIAL	
	{ 
		adresult2[SITE] = SINK.GetMeasResult(SITE, MIRET); //check delta current
		adresult[SITE] = adresult2[SITE] - adresult1[SITE];
		OVST_MLDO_delta->SetTestResult(SITE, 0, adresult[SITE] * 1e9);//nA
		OVST_MLDO_I1->SetTestResult(SITE, 0, adresult1[SITE] * 1e6);//uA
		OVST_MLDO_I2->SetTestResult(SITE, 0, adresult2[SITE] * 1e6);//uA
	}
	SINK.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	VOUT.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	VOUT.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);
	delay_us(200);

	if (PN_FLAG)
	{
		//P管AC1 HS OVST
		AC1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_us(500);

		AC1.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON,1);
		manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_RECT_HS, 1 }, { FORCE_SINK_OFF, 1 }, { TMOD_CTRL, 5 } });
		delay_ms(1);

		VRECT.Set(FV, 10.5, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
		AC1.Set(FV, 10.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		SINK.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON, 1);
		delay_ms(2);
		AC1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		AC1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);
		SINK.Set(FV, 5.5, FOVI_20V, FOVI_1MA, RELAY_ON);
		delay_ms(30);//等待SINK电流稳定
		if (Global_Tempchar_Program_Flag == 1)
		{
			delay_ms(50);
		}

		SINK.MeasureVI(100, 10);

		SERIAL	adresult1[SITE] = SINK.GetMeasResult(SITE, MIRET);
		
		if (Global_FTQC_FLAG == 0)
		{
			VRECT.Set(FV, 13, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
			delay_ms(100);//wait 100ms stress
			
			SINK.MeasureVI(100, 10);
			SERIAL
			{
				adresult3[SITE] = SINK.GetMeasResult(SITE, MIRET);
				OVST_HS_AC1_I3->SetTestResult(SITE, 0, adresult3[SITE] * 1e6);//uA
			}
		}
		VRECT.Set(FV, 10.5, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
		delay_ms(5);//等待SINK电流稳定
		if (Global_Tempchar_Program_Flag == 1)
		{
			delay_ms(20);
		}

		SINK.MeasureVI(100, 10);

		SERIAL
		{
			adresult2[SITE] = SINK.GetMeasResult(SITE, MIRET); //check delta current
			adresult[SITE] = adresult1[SITE] - adresult2[SITE];
			OVST_HS_AC1_delta->SetTestResult(SITE, 0, adresult[SITE] * 1e6);//uA
			OVST_HS_AC1_I1->SetTestResult(SITE, 0, adresult1[SITE] * 1e6);//uA
			OVST_HS_AC1_I2->SetTestResult(SITE, 0, adresult2[SITE] * 1e6);//uA
		}

		//SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		SINK.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);//avoid spike
		VRECT.Set(FV, 5.5, FOVI_20V, FOVI_100MA, RELAY_ON, 1);//TM
		//delay_ms(1);

		//P管AC2 HS OVST
		AC2.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON, 1);
		manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_RECT_HS, 1 }, { FORCE_SINK_OFF, 1 },*/ { TMOD_CTRL, 6 } });
		delay_ms(1);

		VRECT.Set(FV, 10.5, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
		AC2.Set(FV, 10.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		//SINK.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(2);
		AC2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
		AC2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);
		SINK.Set(FV, 5.5, FOVI_20V, FOVI_1MA, RELAY_ON);
		delay_ms(10);//等待SINK电流稳定
		SINK.MeasureVI(50, 10);

		SERIAL	adresult1[SITE] = SINK.GetMeasResult(SITE, MIRET);

		if (Global_FTQC_FLAG == 0)
		{
			VRECT.Set(FV, 13, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
			delay_ms(100);//wait 100ms stress

			SINK.MeasureVI(100, 10);
			SERIAL
			{
				adresult3[SITE] = SINK.GetMeasResult(SITE, MIRET);
				OVST_HS_AC2_I3->SetTestResult(SITE, 0, adresult3[SITE] * 1e6);//uA
			}
		}
		VRECT.Set(FV, 10.5, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
		delay_ms(5);//等待SINK电流稳定
		SINK.MeasureVI(50, 10);

		SERIAL
		{
			adresult2[SITE] = SINK.GetMeasResult(SITE, MIRET); //check delta current
			adresult[SITE] = adresult2[SITE] - adresult1[SITE];
			OVST_HS_AC2_delta->SetTestResult(SITE, 0, adresult[SITE] * 1e6);
			OVST_HS_AC2_I1->SetTestResult(SITE, 0, adresult1[SITE] * 1e6);
			OVST_HS_AC2_I2->SetTestResult(SITE, 0, adresult2[SITE] * 1e6);
		}
		SINK.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
		delay_ms(1);
		SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);
		VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
		delay_us(200);
	}
	else
	{
		//N管AC1 HS OVST
		AC1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_us(500);

		AC1.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		SINK.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC2.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_RECT_HS, 1 }, { TMOD_CTRL, 0x05 } });
		delay_ms(1);

		SINK.Set(FV, 10.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC1.Set(FV, 5.7, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC2.Set(FV, 5.7, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(2);

		SINK.Set(FV, 10.5, FOVI_20V, FOVI_1MA, RELAY_ON);
		AC1.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC2.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(2);

		SINK.MeasureVI(50, 10);

		SERIAL	adresult1[SITE] = SINK.GetMeasResult(SITE, MIRET);
		
		SINK.Set(FV, 10.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		if (Global_FTQC_FLAG == 0)
		{
			SINK.Set(FV, 13, FOVI_20V, FOVI_10MA, RELAY_ON);
			delay_ms(100);//wait 100ms stress
		}
		SINK.Set(FV, 10.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(2);
		SINK.MeasureVI(50, 10);

		SERIAL
		{
			adresult2[SITE] = SINK.GetMeasResult(SITE, MIRET); //check delta current
			adresult[SITE] = adresult2[SITE] - adresult1[SITE];
			OVST_HS_AC1_delta->SetTestResult(SITE, 0, adresult[SITE] * 1E+6);
		}

		//N管AC2 HS OVST
		AC2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		VRECT.Set(FV, 5.5, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
		delay_us(1000);

		AC2.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		SINK.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC1.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		SINK.Set(FV, 10.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC1.Set(FV, 5.7, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC2.Set(FV, 5.7, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(2);

		SINK.Set(FV, 10.5, FOVI_20V, FOVI_1MA, RELAY_ON);
		AC1.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC2.Set(FV, 5.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(2);

		SINK.MeasureVI(50, 10);

		SERIAL	adresult1[SITE] = SINK.GetMeasResult(SITE, MIRET);
		
		SINK.Set(FV, 10.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		if (Global_FTQC_FLAG == 0)
		{
			SINK.Set(FV, 13, FOVI_20V, FOVI_10MA, RELAY_ON);
			delay_ms(100);//wait 100ms stress
		}
		SINK.Set(FV, 10.5, FOVI_20V, FOVI_10MA, RELAY_ON);
		delay_ms(2);
		SINK.MeasureVI(50, 10);

		SERIAL
		{
			adresult2[SITE] = SINK.GetMeasResult(SITE, MIRET); //check delta current
			adresult[SITE] = adresult2[SITE] - adresult1[SITE];
			OVST_HS_AC2_delta->SetTestResult(SITE, 0, adresult[SITE] * 1E+6);
		}
		AC2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		AC1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
		VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
		delay_ms(1);
		AC2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);
		SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);
		AC1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);
		VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
		delay_us(200);

	}
	//AC1 LS OVST
	//V5V voltage change from 5V to 5.2V, stress voltage from 7.5V to 6.5V--optimize yield, 2026.05.29
	//cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K3_VOUT_CAP, -1);
	//wait_relay();
	TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);//5V
	V5V.Set(FV, 5.2, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_VCP, 0 }, { TRIM_VRECT_DMY_DIS, 1 }, { I2C_EN_RECT_LS, 1 } });
	delay_ms(1);

	AC2.Set(FV, 5.5, FOVI_10V, FOVI_100MA, RELAY_ON);
	V5V.Set(FV, 5.2, FOVI_10V, FOVI_10MA, RELAY_ON);
	AC1.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	AC1.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(1);

	AC2.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	AC2.Set(FV, 5.5, FOVI_10V, FOVI_100MA, RELAY_ON);
	AC1.Set(FV, -0.2, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(1);

	AC1.Set(FV, -0.02, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(20);//等待AC1电压稳定
	V5V.MeasureVI(50, 10);
	AC1.MeasureVI(50, 10);

	SERIAL
	{
		adresult1[SITE] = V5V.GetMeasResult(SITE, MIRET);
		adresult5[SITE] = AC1.GetMeasResult(SITE, MIRET);
	}

	if (Global_FTQC_FLAG == 0)
	{
		V5V.Set(FV, 5.2, FOVI_10V, FOVI_100MA, RELAY_ON, 1);
		VRECT.Set(FV, 6.5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);//7.5
		AC2.Set(FV, 6.5, FOVI_10V, FOVI_100MA, RELAY_ON);//7.5
		V5V.Set(FV, 6.5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);//7.5
		delay_ms(100);//wait 100ms stress

		V5V.MeasureVI(50, 10);
		SERIAL
		{
			adresult3[SITE] = V5V.GetMeasResult(SITE, MIRET);
			OVST_LS_AC1_I3->SetTestResult(SITE, 0, adresult3[SITE] * 1e6);
		}
	}
	V5V.Set(FV, 5.2, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	V5V.Set(FV, 5.2, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(2);

	V5V.MeasureVI(50, 10);

	SERIAL
	{
		adresult2[SITE] = V5V.GetMeasResult(SITE, MIRET); //check delta current
		adresult[SITE] = adresult2[SITE] - adresult1[SITE];
		OVST_LS_AC1_delta->SetTestResult(SITE, 0, adresult[SITE] * 1e6);
		OVST_LS_AC1_I1->SetTestResult(SITE, 0, adresult1[SITE] * 1e6);
		OVST_LS_IAC1->SetTestResult(SITE, 0, -adresult5[SITE] * 1e3);
		OVST_LS_AC1_I2->SetTestResult(SITE, 0, adresult2[SITE] * 1e6);
	}

	//AC2 LS OVST
	//V5V voltage change from 5V to 5.2V, stress voltage from 7.5V to 6.5V--optimize yield, 2026.05.29
	V5V.Set(FV, 5.2, FOVI_10V, FOVI_100MA, RELAY_ON);//5V
	delay_ms(2); 

	VRECT.Set(FV, 5.5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	AC1.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON);
	AC2.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON); 
	delay_us(200);

	AC1.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_us(200);
	V5V.Set(FV, 5.2, FOVI_10V, FOVI_10MA, RELAY_ON);
	AC1.Set(FV, 5.5, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	AC1.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	AC1.Set(FV, 5.5, FOVI_10V, FOVI_100MA, RELAY_ON);
	AC2.Set(FV, -0.2, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(1);

	AC2.Set(FV, -0.02, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(20);//等待AC2电压稳定
	V5V.MeasureVI(50, 10);
	AC2.MeasureVI(50, 10);

	SERIAL
	{
		adresult1[SITE] = V5V.GetMeasResult(SITE, MIRET);
		adresult5[SITE] = AC2.GetMeasResult(SITE, MIRET);
	}

	if (Global_FTQC_FLAG == 0)
	{
		V5V.Set(FV, 5.2, FOVI_10V, FOVI_100MA, RELAY_ON, 1);
		VRECT.Set(FV, 6.5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);//7.5
		AC1.Set(FV, 6.5, FOVI_10V, FOVI_100MA, RELAY_ON);//7.5
		V5V.Set(FV, 6.5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);//7.5
		delay_ms(100);//wait 100ms stress

		V5V.MeasureVI(50, 10);
		SERIAL
		{
			adresult3[SITE] = V5V.GetMeasResult(SITE, MIRET);
			OVST_LS_AC2_I3->SetTestResult(SITE, 0, adresult3[SITE] * 1E+6);

		}
	}
	V5V.Set(FV, 5.2, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	V5V.Set(FV, 5.2, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	V5V.MeasureVI(50, 10);

	SERIAL
	{
		adresult2[SITE] = V5V.GetMeasResult(SITE, MIRET); //check delta current
		adresult[SITE] = adresult2[SITE] - adresult1[SITE];
		OVST_LS_AC2_delta->SetTestResult(SITE, 0, adresult[SITE] * 1E+6);
		OVST_LS_AC2_I1->SetTestResult(SITE, 0, adresult1[SITE] * 1E+6);
		OVST_LS_IAC2->SetTestResult(SITE, 0, -adresult5[SITE] * 1E+3);
		OVST_LS_AC2_I2->SetTestResult(SITE, 0, adresult2[SITE] * 1E+6);

	}
	V5V.Set(FV, 5.2, FOVI_10V, FOVI_100MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(1);

	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	AC1.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	AC1.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	AC2.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_OFF);

	return 0;
}

DUT_API int INIT_READ(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *INIT_VBG_CODE = StsGetParam(funcindex, "INIT_VBG_CODE");
    CParam *INIT_ZTC_CODE = StsGetParam(funcindex, "INIT_ZTC_CODE");
    CParam *INIT_ADC_VREF_BUFFER_CODE = StsGetParam(funcindex, "INIT_ADC_VREF_BUFFER_CODE");
    CParam *INIT_ADC_VIN_BUFFER_CODE = StsGetParam(funcindex, "INIT_ADC_VIN_BUFFER_CODE");
    CParam *INIT_OSC_CODE = StsGetParam(funcindex, "INIT_OSC_CODE");
    CParam *INIT_COMP_OFF_AC1_CODE = StsGetParam(funcindex, "INIT_COMP_OFF_AC1_CODE");
    CParam *INIT_COMP_OFF_AC2_CODE = StsGetParam(funcindex, "INIT_COMP_OFF_AC2_CODE");
    CParam *INIT_ISNS_GAIN_CODE = StsGetParam(funcindex, "INIT_ISNS_GAIN_CODE");
    CParam *INIT_ISNS_OFFSET_CODE = StsGetParam(funcindex, "INIT_ISNS_OFFSET_CODE");
    CParam *INIT_TRIM_ACLOW_EN = StsGetParam(funcindex, "INIT_TRIM_ACLOW_EN");
    CParam *INIT_TTP_FSK_DIS = StsGetParam(funcindex, "INIT_TTP_FSK_DIS");
    CParam *INIT_AC_CHECK_500K = StsGetParam(funcindex, "INIT_AC_CHECK_500K");
    CParam *INIT_TRIM_DEIVICE_ID = StsGetParam(funcindex, "INIT_TRIM_DEIVICE_ID");
    CParam *INIT_0XF7_BIT2_TRIM_LOCK = StsGetParam(funcindex, "INIT_0XF7_BIT2_TRIM_LOCK");
    CParam *INIT_0XF7_BIT3_OPT2_LOCK = StsGetParam(funcindex, "INIT_0XF7_BIT3_OPT2_LOCK");
    CParam *INIT_0XF7_BIT4_OPT1_LOCK = StsGetParam(funcindex, "INIT_0XF7_BIT4_OPT1_LOCK");
    CParam *INIT_0XF7_BIT5_OPT1_BAK_LOCK = StsGetParam(funcindex, "INIT_0XF7_BIT5_OPT1_BAK_LOCK");
    CParam *Initial_Read_0080 = StsGetParam(funcindex, "Initial_Read_0080");
    CParam *Initial_Read_0081 = StsGetParam(funcindex, "Initial_Read_0081");
    CParam *Initial_Read_0082 = StsGetParam(funcindex, "Initial_Read_0082");
    CParam *Initial_Read_0083 = StsGetParam(funcindex, "Initial_Read_0083");
    CParam *Initial_Read_0084 = StsGetParam(funcindex, "Initial_Read_0084");
    CParam *Initial_Read_0085 = StsGetParam(funcindex, "Initial_Read_0085");
    CParam *Initial_Read_0086 = StsGetParam(funcindex, "Initial_Read_0086");
    CParam *Initial_Read_0087 = StsGetParam(funcindex, "Initial_Read_0087");
    CParam *Initial_Read_0088 = StsGetParam(funcindex, "Initial_Read_0088");
    CParam *Initial_Read_0089 = StsGetParam(funcindex, "Initial_Read_0089");
    CParam *Initial_Read_008A = StsGetParam(funcindex, "Initial_Read_008A");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, -1);
	dioplus.I2CConnect();
	wait_relay();

	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0XF7, 1);

    SERIAL
	{
		INIT_READ_0XF7[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0xF7 value

		init_read_0XF7_BIT2_CODE[SITE] = (unsigned char(INIT_READ_0XF7[SITE]) & 0X04) >> 2; //0XF7 bit2 
		init_read_0XF7_BIT3_CODE[SITE] = (unsigned char(INIT_READ_0XF7[SITE]) & 0X08) >> 3; //0XF7 bit3 
		init_read_0XF7_BIT4_CODE[SITE] = (unsigned char(INIT_READ_0XF7[SITE]) & 0X10) >> 4; //0XF7 bit4 	
		init_read_0XF7_BIT5_CODE[SITE] = (unsigned char(INIT_READ_0XF7[SITE]) & 0X20) >> 5; //0XF7 bit5 
	}

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X80, 11);//read trim reg code
	for (int reg = 0; reg < 11; reg++)
	{
		EFUSE_READ[reg][0] = i2c_site1.GetDataByteValue(reg);  // i2c site1 get the reg byte value
		EFUSE_READ[reg][1] = i2c_site2.GetDataByteValue(reg);  // i2c site2 get the reg byte value
		EFUSE_READ[reg][2] = i2c_site3.GetDataByteValue(reg);  // i2c site3 get the reg byte value
		EFUSE_READ[reg][3] = i2c_site4.GetDataByteValue(reg);  // i2c site4 get the reg byte value
		EFUSE_READ[reg][4] = i2c_site5.GetDataByteValue(reg);  // i2c site5 get the reg byte value
		EFUSE_READ[reg][5] = i2c_site6.GetDataByteValue(reg);  // i2c site6 get the reg byte value
		EFUSE_READ[reg][6] = i2c_site7.GetDataByteValue(reg);  // i2c site7 get the reg byte value
		EFUSE_READ[reg][7] = i2c_site8.GetDataByteValue(reg);  // i2c site8 get the reg byte value
	}

	SERIAL
	{
		if (Global_FTQC_FLAG == 0)
		{
					if (init_read_0XF7_BIT2_CODE[SITE] == 0)//trim lock=0, no trim before
					{
						burn_flag_all[SITE] = true;
			 		}
			 		else
			 		{
			 			burn_flag_all[SITE] = false;
			 		}

					QC_PGM = false;

		}
		else
		{
			burn_flag_all[SITE] = false;

			DO_TRIM = false;
			QC = true;
			QC_PGM = true;
		}
	}
	for (int reg = 0; reg < BANK_NUM; ++reg)
	{
		string TB_str;
		TB_str = "EEPROM" + spec.int2str(reg);

		// set trim flag, and disable trim node allow if trimmed
		SERIAL
		{
			dut.assy(TB_str.c_str()).set_read_back((EFUSE_READ[reg][SITE]), SITE);
			dut.assy(TB_str.c_str()).copy_read_to_prog();
			//dut.assy(TB_str.c_str()).copy_read_to_saved();
			if (Global_FTQC_FLAG != 0)//QC
			{
				dut.assy(TB_str.c_str()).copy_read_to_work(SITE);
			}
			for (unsigned int node_no = 0; node_no < dut.assy(TB_str.c_str()).count(); ++node_no)
			{
				string node_name(dut.assy(TB_str.c_str())[node_no].get_node_name());

				if (dut.find(node_name.c_str()) == FOUND_TRIM)									// judge if it is trim node, not sel node
					dut.trim(node_name.c_str()).set_trim_allowed(burn_flag_all[SITE], SITE);	// if burn_flag is false, disable trim allow, else enable
			}
		}
	}

	FOR_EACH_VALID_SITE(site)
	{
		init_read_VBG_CODE[site] = dut.trim("TRIM_BG").get_read_back(site);//EEPROM1 bit2~7
		init_read_ZTC_CODE[site] = dut.trim("TRIM_ZTC").get_read_back(site);//EEPROM4 bit3~7
		init_read_ADC_VREF_BUFFER_CODE[site] = dut.trim("TRIM_ADC_VREF_BUFFER").get_read_back(site);//EEPROM2 bit2~7
		init_read_ADC_VIN_BUFFER_CODE[site] = dut.trim("TRIM_ADC_VIN_BUFFER").get_read_back(site);//EEPROM7 bit2~7
		init_read_OSC_CODE[site] = dut.trim("TRIM_OSC").get_read_back(site);//EEPROM3 bit1~7
		init_read_COMP_OFF_AC1_CODE[site] = dut.trim("TRIM_LS1_COMP").get_read_back(site);//EEPROM0 bit4~7
		init_read_COMP_OFF_AC2_CODE[site] = dut.trim("TRIM_LS2_COMP").get_read_back(site);//EEPROM0 bit0~3
		init_read_ISNS_GAIN_CODE[site] = dut.trim("TRIM_ISNS_GAIN").get_read_back(site);//EEPROM5 bit1~7
		init_read_ISNS_OFFSET_CODE[site] = dut.trim("TRIM_ISNS_OFFSET").get_read_back(site);//EEPROM6 bit2~7
		init_read_TRIM_ACLOW_EN[site] = dut.sel("TRIM_ACLOW_EN").get_read_back(site);//EEPROM2 bit1
		init_read_TTP_FSK_DIS[site] = dut.sel("TTP_FSK_DIS").get_read_back(site);//EEPROM9 bit6
		init_read_AC_CHECK_500K[site] = dut.sel("AC_CHECK_500K").get_read_back(site);//EEPROM9 bit5
		init_read_TRIM_DEIVICE_ID[site] = dut.sel("TRIM_DEIVICE_ID").get_read_back(site);//EEPROMA bit2~4

	}


	FOR_EACH_VALID_SITE(site)
	{
		INIT_VBG_CODE->SetTestResult(site, 0, init_read_VBG_CODE[site]);
		INIT_ZTC_CODE->SetTestResult(site, 0, init_read_ZTC_CODE[site]);
		INIT_ADC_VREF_BUFFER_CODE->SetTestResult(site, 0, init_read_ADC_VREF_BUFFER_CODE[site]);
		INIT_ADC_VIN_BUFFER_CODE->SetTestResult(site, 0, init_read_ADC_VIN_BUFFER_CODE[site]);
		INIT_OSC_CODE->SetTestResult(site, 0, init_read_OSC_CODE[site]);
		INIT_COMP_OFF_AC1_CODE->SetTestResult(site, 0, init_read_COMP_OFF_AC1_CODE[site]);
		INIT_COMP_OFF_AC2_CODE->SetTestResult(site, 0, init_read_COMP_OFF_AC2_CODE[site]);
		INIT_ISNS_GAIN_CODE->SetTestResult(site, 0, init_read_ISNS_GAIN_CODE[site]);
		INIT_ISNS_OFFSET_CODE->SetTestResult(site, 0, init_read_ISNS_OFFSET_CODE[site]);
		//select PN
		INIT_TRIM_ACLOW_EN->SetTestResult(site, 0, init_read_TRIM_ACLOW_EN[site]);
		INIT_TTP_FSK_DIS->SetTestResult(site, 0, init_read_TTP_FSK_DIS[site]);
		INIT_AC_CHECK_500K->SetTestResult(site, 0, init_read_AC_CHECK_500K[site]);
		INIT_TRIM_DEIVICE_ID->SetTestResult(site, 0, init_read_TRIM_DEIVICE_ID[site]);

		INIT_0XF7_BIT2_TRIM_LOCK->SetTestResult(site, 0, init_read_0XF7_BIT2_CODE[site]);
		INIT_0XF7_BIT3_OPT2_LOCK->SetTestResult(site, 0, init_read_0XF7_BIT3_CODE[site]);
		INIT_0XF7_BIT4_OPT1_LOCK->SetTestResult(site, 0, init_read_0XF7_BIT4_CODE[site]);
		INIT_0XF7_BIT5_OPT1_BAK_LOCK->SetTestResult(site, 0, init_read_0XF7_BIT5_CODE[site]);

		Initial_Read_0080->SetTestResult(site, 0, unsigned char(EFUSE_READ[0][site]));
		Initial_Read_0081->SetTestResult(site, 0, unsigned char(EFUSE_READ[1][site]));
		Initial_Read_0082->SetTestResult(site, 0, unsigned char(EFUSE_READ[2][site]));
		Initial_Read_0083->SetTestResult(site, 0, unsigned char(EFUSE_READ[3][site]));
		Initial_Read_0084->SetTestResult(site, 0, unsigned char(EFUSE_READ[4][site]));
		Initial_Read_0085->SetTestResult(site, 0, unsigned char(EFUSE_READ[5][site]));
		Initial_Read_0086->SetTestResult(site, 0, unsigned char(EFUSE_READ[6][site]));
		Initial_Read_0087->SetTestResult(site, 0, unsigned char(EFUSE_READ[7][site]));
		Initial_Read_0088->SetTestResult(site, 0, unsigned char(EFUSE_READ[8][site]));
		Initial_Read_0089->SetTestResult(site, 0, unsigned char(EFUSE_READ[9][site]));
		Initial_Read_008A->SetTestResult(site, 0, unsigned char(EFUSE_READ[10][site]));
	}

	if (POWER_FLAG)
	{
		TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);
	}
    return 0;
} 
 
DUT_API int VBG_TRIM(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *TRIM_BG_pre = StsGetParam(funcindex, "TRIM_BG_pre");
    CParam *TRIM_BG_pre_bit = StsGetParam(funcindex, "TRIM_BG_pre_bit");
    CParam *TRIM_BG_post = StsGetParam(funcindex, "TRIM_BG_post");
    CParam *TRIM_BG_post_bit = StsGetParam(funcindex, "TRIM_BG_post_bit");
    CParam *TRIM_BG_target = StsGetParam(funcindex, "TRIM_BG_target");
    CParam *TRIM_BG_guessed = StsGetParam(funcindex, "TRIM_BG_guessed");
    CParam *TRIM_BG_updated = StsGetParam(funcindex, "TRIM_BG_updated");
    CParam *TRIM_BG_STEP0 = StsGetParam(funcindex, "TRIM_BG_STEP0");
    CParam *TRIM_BG_STEP1 = StsGetParam(funcindex, "TRIM_BG_STEP1");
    CParam *TRIM_BG_STEP2 = StsGetParam(funcindex, "TRIM_BG_STEP2");
    CParam *TRIM_BG_STEP3 = StsGetParam(funcindex, "TRIM_BG_STEP3");
    CParam *TRIM_BG_STEP4 = StsGetParam(funcindex, "TRIM_BG_STEP4");
    CParam *TRIM_BG_STEP5 = StsGetParam(funcindex, "TRIM_BG_STEP5");
    CParam *TRIM_BG_STEP6 = StsGetParam(funcindex, "TRIM_BG_STEP6");
    CParam *TRIM_BG_STEP7 = StsGetParam(funcindex, "TRIM_BG_STEP7");
    CParam *TRIM_BG_STEP8 = StsGetParam(funcindex, "TRIM_BG_STEP8");
    CParam *TRIM_BG_STEP9 = StsGetParam(funcindex, "TRIM_BG_STEP9");
    CParam *TRIM_BG_STEP10 = StsGetParam(funcindex, "TRIM_BG_STEP10");
    CParam *TRIM_BG_STEP11 = StsGetParam(funcindex, "TRIM_BG_STEP11");
    CParam *TRIM_BG_STEP12 = StsGetParam(funcindex, "TRIM_BG_STEP12");
    CParam *TRIM_BG_STEP13 = StsGetParam(funcindex, "TRIM_BG_STEP13");
    CParam *TRIM_BG_STEP14 = StsGetParam(funcindex, "TRIM_BG_STEP14");
    CParam *TRIM_BG_STEP15 = StsGetParam(funcindex, "TRIM_BG_STEP15");
    CParam *TRIM_BG_STEP16 = StsGetParam(funcindex, "TRIM_BG_STEP16");
    CParam *TRIM_BG_STEP17 = StsGetParam(funcindex, "TRIM_BG_STEP17");
    CParam *TRIM_BG_STEP18 = StsGetParam(funcindex, "TRIM_BG_STEP18");
    CParam *TRIM_BG_STEP19 = StsGetParam(funcindex, "TRIM_BG_STEP19");
    CParam *TRIM_BG_STEP20 = StsGetParam(funcindex, "TRIM_BG_STEP20");
    CParam *TRIM_BG_STEP21 = StsGetParam(funcindex, "TRIM_BG_STEP21");
    CParam *TRIM_BG_STEP22 = StsGetParam(funcindex, "TRIM_BG_STEP22");
    CParam *TRIM_BG_STEP23 = StsGetParam(funcindex, "TRIM_BG_STEP23");
    CParam *TRIM_BG_STEP24 = StsGetParam(funcindex, "TRIM_BG_STEP24");
    CParam *TRIM_BG_STEP25 = StsGetParam(funcindex, "TRIM_BG_STEP25");
    CParam *TRIM_BG_STEP26 = StsGetParam(funcindex, "TRIM_BG_STEP26");
    CParam *TRIM_BG_STEP27 = StsGetParam(funcindex, "TRIM_BG_STEP27");
    CParam *TRIM_BG_STEP28 = StsGetParam(funcindex, "TRIM_BG_STEP28");
    CParam *TRIM_BG_STEP29 = StsGetParam(funcindex, "TRIM_BG_STEP29");
    CParam *TRIM_BG_STEP30 = StsGetParam(funcindex, "TRIM_BG_STEP30");
    CParam *TRIM_BG_STEP31 = StsGetParam(funcindex, "TRIM_BG_STEP31");
    CParam *TRIM_BG_STEP32 = StsGetParam(funcindex, "TRIM_BG_STEP32");
    CParam *TRIM_BG_STEP33 = StsGetParam(funcindex, "TRIM_BG_STEP33");
    CParam *TRIM_BG_STEP34 = StsGetParam(funcindex, "TRIM_BG_STEP34");
    CParam *TRIM_BG_STEP35 = StsGetParam(funcindex, "TRIM_BG_STEP35");
    CParam *TRIM_BG_STEP36 = StsGetParam(funcindex, "TRIM_BG_STEP36");
    CParam *TRIM_BG_STEP37 = StsGetParam(funcindex, "TRIM_BG_STEP37");
    CParam *TRIM_BG_STEP38 = StsGetParam(funcindex, "TRIM_BG_STEP38");
    CParam *TRIM_BG_STEP39 = StsGetParam(funcindex, "TRIM_BG_STEP39");
    CParam *TRIM_BG_STEP40 = StsGetParam(funcindex, "TRIM_BG_STEP40");
    CParam *TRIM_BG_STEP41 = StsGetParam(funcindex, "TRIM_BG_STEP41");
    CParam *TRIM_BG_STEP42 = StsGetParam(funcindex, "TRIM_BG_STEP42");
    CParam *TRIM_BG_STEP43 = StsGetParam(funcindex, "TRIM_BG_STEP43");
    CParam *TRIM_BG_STEP44 = StsGetParam(funcindex, "TRIM_BG_STEP44");
    CParam *TRIM_BG_STEP45 = StsGetParam(funcindex, "TRIM_BG_STEP45");
    CParam *TRIM_BG_STEP46 = StsGetParam(funcindex, "TRIM_BG_STEP46");
    CParam *TRIM_BG_STEP47 = StsGetParam(funcindex, "TRIM_BG_STEP47");
    CParam *TRIM_BG_STEP48 = StsGetParam(funcindex, "TRIM_BG_STEP48");
    CParam *TRIM_BG_STEP49 = StsGetParam(funcindex, "TRIM_BG_STEP49");
    CParam *TRIM_BG_STEP50 = StsGetParam(funcindex, "TRIM_BG_STEP50");
    CParam *TRIM_BG_STEP51 = StsGetParam(funcindex, "TRIM_BG_STEP51");
    CParam *TRIM_BG_STEP52 = StsGetParam(funcindex, "TRIM_BG_STEP52");
    CParam *TRIM_BG_STEP53 = StsGetParam(funcindex, "TRIM_BG_STEP53");
    CParam *TRIM_BG_STEP54 = StsGetParam(funcindex, "TRIM_BG_STEP54");
    CParam *TRIM_BG_STEP55 = StsGetParam(funcindex, "TRIM_BG_STEP55");
    CParam *TRIM_BG_STEP56 = StsGetParam(funcindex, "TRIM_BG_STEP56");
    CParam *TRIM_BG_STEP57 = StsGetParam(funcindex, "TRIM_BG_STEP57");
    CParam *TRIM_BG_STEP58 = StsGetParam(funcindex, "TRIM_BG_STEP58");
    CParam *TRIM_BG_STEP59 = StsGetParam(funcindex, "TRIM_BG_STEP59");
    CParam *TRIM_BG_STEP60 = StsGetParam(funcindex, "TRIM_BG_STEP60");
    CParam *TRIM_BG_STEP61 = StsGetParam(funcindex, "TRIM_BG_STEP61");
    CParam *TRIM_BG_STEP62 = StsGetParam(funcindex, "TRIM_BG_STEP62");
    CParam *TRIM_BG_STEP63 = StsGetParam(funcindex, "TRIM_BG_STEP63");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here
	DWORD Trim_PRE_CODE[SITE_NUM] = { 0 };

	Qvm.Connect();
	if (POWER_FLAG)
	{
		cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, -1);//未使用buffer
		dioplus.I2CConnect();
		wait_relay();
		TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);//5V
	}
	else
	{
		V5V.Set(FV, spec("V5V"), FOVI_10V, FOVI_100MA, RELAY_ON);//5V
	}
	INTB.Set(FV, 0, FOVI_2V, FOVI_1MA, RELAY_OFF);


	manager.setfields({ { I2C_CTRL, 1 }, { EN_ANA_MUX, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { MUX_ANA, 0x0B } });
	delay_ms(1);

	dut.trim("TRIM_BG").execute(measure_VBG_trim, spec, funcindex, funclabel, 1, 0, "TRIM_BG");

	if (POWER_FLAG)
	{
		TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);//5V
	}
	//V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//ENB.Set(FV, 0, FOVI_2V, FOVI_1MA, RELAY_OFF);


    return 0;
}

DUT_API int VBG_OPT_TRIM(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *TRIM_BG_OPT_pre = StsGetParam(funcindex, "TRIM_BG_OPT_pre");
    CParam *TRIM_BG_OPT_pre_bit = StsGetParam(funcindex, "TRIM_BG_OPT_pre_bit");
    CParam *TRIM_BG_OPT_post = StsGetParam(funcindex, "TRIM_BG_OPT_post");
    CParam *TRIM_BG_OPT_post_bit = StsGetParam(funcindex, "TRIM_BG_OPT_post_bit");
    CParam *TRIM_BG_OPT_target = StsGetParam(funcindex, "TRIM_BG_OPT_target");
    CParam *TRIM_BG_OPT_guessed = StsGetParam(funcindex, "TRIM_BG_OPT_guessed");
    CParam *TRIM_BG_OPT_updated = StsGetParam(funcindex, "TRIM_BG_OPT_updated");
    CParam *TRIM_BG_OPT_STEP0 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP0");
    CParam *TRIM_BG_OPT_STEP1 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP1");
    CParam *TRIM_BG_OPT_STEP2 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP2");
    CParam *TRIM_BG_OPT_STEP3 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP3");
    CParam *TRIM_BG_OPT_STEP4 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP4");
    CParam *TRIM_BG_OPT_STEP5 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP5");
    CParam *TRIM_BG_OPT_STEP6 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP6");
    CParam *TRIM_BG_OPT_STEP7 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP7");
    CParam *TRIM_BG_OPT_STEP8 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP8");
    CParam *TRIM_BG_OPT_STEP9 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP9");
    CParam *TRIM_BG_OPT_STEP10 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP10");
    CParam *TRIM_BG_OPT_STEP11 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP11");
    CParam *TRIM_BG_OPT_STEP12 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP12");
    CParam *TRIM_BG_OPT_STEP13 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP13");
    CParam *TRIM_BG_OPT_STEP14 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP14");
    CParam *TRIM_BG_OPT_STEP15 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP15");
    CParam *TRIM_BG_OPT_STEP16 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP16");
    CParam *TRIM_BG_OPT_STEP17 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP17");
    CParam *TRIM_BG_OPT_STEP18 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP18");
    CParam *TRIM_BG_OPT_STEP19 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP19");
    CParam *TRIM_BG_OPT_STEP20 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP20");
    CParam *TRIM_BG_OPT_STEP21 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP21");
    CParam *TRIM_BG_OPT_STEP22 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP22");
    CParam *TRIM_BG_OPT_STEP23 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP23");
    CParam *TRIM_BG_OPT_STEP24 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP24");
    CParam *TRIM_BG_OPT_STEP25 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP25");
    CParam *TRIM_BG_OPT_STEP26 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP26");
    CParam *TRIM_BG_OPT_STEP27 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP27");
    CParam *TRIM_BG_OPT_STEP28 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP28");
    CParam *TRIM_BG_OPT_STEP29 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP29");
    CParam *TRIM_BG_OPT_STEP30 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP30");
    CParam *TRIM_BG_OPT_STEP31 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP31");
    CParam *TRIM_BG_OPT_STEP32 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP32");
    CParam *TRIM_BG_OPT_STEP33 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP33");
    CParam *TRIM_BG_OPT_STEP34 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP34");
    CParam *TRIM_BG_OPT_STEP35 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP35");
    CParam *TRIM_BG_OPT_STEP36 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP36");
    CParam *TRIM_BG_OPT_STEP37 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP37");
    CParam *TRIM_BG_OPT_STEP38 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP38");
    CParam *TRIM_BG_OPT_STEP39 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP39");
    CParam *TRIM_BG_OPT_STEP40 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP40");
    CParam *TRIM_BG_OPT_STEP41 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP41");
    CParam *TRIM_BG_OPT_STEP42 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP42");
    CParam *TRIM_BG_OPT_STEP43 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP43");
    CParam *TRIM_BG_OPT_STEP44 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP44");
    CParam *TRIM_BG_OPT_STEP45 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP45");
    CParam *TRIM_BG_OPT_STEP46 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP46");
    CParam *TRIM_BG_OPT_STEP47 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP47");
    CParam *TRIM_BG_OPT_STEP48 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP48");
    CParam *TRIM_BG_OPT_STEP49 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP49");
    CParam *TRIM_BG_OPT_STEP50 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP50");
    CParam *TRIM_BG_OPT_STEP51 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP51");
    CParam *TRIM_BG_OPT_STEP52 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP52");
    CParam *TRIM_BG_OPT_STEP53 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP53");
    CParam *TRIM_BG_OPT_STEP54 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP54");
    CParam *TRIM_BG_OPT_STEP55 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP55");
    CParam *TRIM_BG_OPT_STEP56 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP56");
    CParam *TRIM_BG_OPT_STEP57 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP57");
    CParam *TRIM_BG_OPT_STEP58 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP58");
    CParam *TRIM_BG_OPT_STEP59 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP59");
    CParam *TRIM_BG_OPT_STEP60 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP60");
    CParam *TRIM_BG_OPT_STEP61 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP61");
    CParam *TRIM_BG_OPT_STEP62 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP62");
    CParam *TRIM_BG_OPT_STEP63 = StsGetParam(funcindex, "TRIM_BG_OPT_STEP63");
//}}AFX_STS_PARAM_PROTOTYPES
	// TODO: Add your function code here
	if (Global_Tempchar_Program_Flag == 0)
	{
		return 0;
	}

	DWORD Trim_PRE_CODE[SITE_NUM] = { 0 };

	unsigned char vbg_writdata[STS_SITE_NUM] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned char trimcode2[STS_SITE_NUM] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	double vbgtrim_table[64][STS_SITE_NUM];


	Qvm.Connect();
	if (POWER_FLAG)
	{
		cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, -1);//未使用buffer
		dioplus.I2CConnect();
		wait_relay();
		TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}

	INTB.Set(FV, 0, FOVI_2V, FOVI_1MA, RELAY_OFF);

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { TMOD_CTRL, 0x09 }, { I2C_EN_OSC, 1 } });
	manager.setfields({ { EN_ANA_MUX, 1 }, { MUX_ANA, 0x09 } });
	manager.setfields({ { TRIM_ADC_VREF_BUFFER, 0x20 } });
	delay_ms(1);

	CParam *VBG_OPT_code[64] =
	{
		TRIM_BG_OPT_STEP0, TRIM_BG_OPT_STEP1, TRIM_BG_OPT_STEP2, TRIM_BG_OPT_STEP3, TRIM_BG_OPT_STEP4, TRIM_BG_OPT_STEP5, TRIM_BG_OPT_STEP6, TRIM_BG_OPT_STEP7,
		TRIM_BG_OPT_STEP8, TRIM_BG_OPT_STEP9, TRIM_BG_OPT_STEP10, TRIM_BG_OPT_STEP11, TRIM_BG_OPT_STEP12, TRIM_BG_OPT_STEP13, TRIM_BG_OPT_STEP14, TRIM_BG_OPT_STEP15,
		TRIM_BG_OPT_STEP16, TRIM_BG_OPT_STEP17, TRIM_BG_OPT_STEP18, TRIM_BG_OPT_STEP19, TRIM_BG_OPT_STEP20, TRIM_BG_OPT_STEP21, TRIM_BG_OPT_STEP22, TRIM_BG_OPT_STEP23,
		TRIM_BG_OPT_STEP24, TRIM_BG_OPT_STEP25, TRIM_BG_OPT_STEP26, TRIM_BG_OPT_STEP27, TRIM_BG_OPT_STEP28, TRIM_BG_OPT_STEP29, TRIM_BG_OPT_STEP30, TRIM_BG_OPT_STEP31,
		TRIM_BG_OPT_STEP32, TRIM_BG_OPT_STEP33, TRIM_BG_OPT_STEP34, TRIM_BG_OPT_STEP35, TRIM_BG_OPT_STEP36, TRIM_BG_OPT_STEP37, TRIM_BG_OPT_STEP38, TRIM_BG_OPT_STEP39,
		TRIM_BG_OPT_STEP40, TRIM_BG_OPT_STEP41, TRIM_BG_OPT_STEP42, TRIM_BG_OPT_STEP43, TRIM_BG_OPT_STEP44, TRIM_BG_OPT_STEP45, TRIM_BG_OPT_STEP46, TRIM_BG_OPT_STEP47,
		TRIM_BG_OPT_STEP48, TRIM_BG_OPT_STEP49, TRIM_BG_OPT_STEP50, TRIM_BG_OPT_STEP51, TRIM_BG_OPT_STEP52, TRIM_BG_OPT_STEP53, TRIM_BG_OPT_STEP54, TRIM_BG_OPT_STEP55,
		TRIM_BG_OPT_STEP56, TRIM_BG_OPT_STEP57, TRIM_BG_OPT_STEP58, TRIM_BG_OPT_STEP59, TRIM_BG_OPT_STEP60, TRIM_BG_OPT_STEP61, TRIM_BG_OPT_STEP62, TRIM_BG_OPT_STEP63
	};


	for (int j = 0; j < 64; j++)
	{
		FOR_EACH_VALID_SITE(site)
		{
			vbg_writdata[site] = j << 2;//
		}

		trimcode2[0] = vbg_writdata[0];
		trimcode2[1] = vbg_writdata[1];
		trimcode2[2] = vbg_writdata[2];
		trimcode2[3] = vbg_writdata[3];
		trimcode2[4] = vbg_writdata[4];
		trimcode2[5] = vbg_writdata[5];
		trimcode2[6] = vbg_writdata[6];
		trimcode2[7] = vbg_writdata[7];

		I2CWritedata(0x81, trimcode2);
		delay_ms(1);

		Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);

		FOR_EACH_VALID_SITE(site)
		{
			vbgtrim_table[j][site] = Qvm.GetMeasResult(site, MVRET);

			VBG_OPT_code[j]->SetTestResult(site, 0, vbgtrim_table[j][site]);

		}

	}


	//dut.trim("TRIM_BG_OTP").execute(measure_VBG_trim, spec, funcindex, funclabel, 1, 0, "TRIM_BG");

	if (POWER_FLAG)
	{
		TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
		//INTB.Set(FI, 0, FOVI_2V, FOVI_100UA, RELAY_OFF);
	}
	return 0;
}

DUT_API int ZTC_TRIM(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *TRIM_ZTC_pre = StsGetParam(funcindex, "TRIM_ZTC_pre");
    CParam *TRIM_ZTC_pre_bit = StsGetParam(funcindex, "TRIM_ZTC_pre_bit");
    CParam *TRIM_ZTC_post = StsGetParam(funcindex, "TRIM_ZTC_post");
    CParam *TRIM_ZTC_post_bit = StsGetParam(funcindex, "TRIM_ZTC_post_bit");
    CParam *TRIM_ZTC_target = StsGetParam(funcindex, "TRIM_ZTC_target");
    CParam *TRIM_ZTC_guessed = StsGetParam(funcindex, "TRIM_ZTC_guessed");
    CParam *TRIM_ZTC_updated = StsGetParam(funcindex, "TRIM_ZTC_updated");
    CParam *TRIM_ZTC_STEP0 = StsGetParam(funcindex, "TRIM_ZTC_STEP0");
    CParam *TRIM_ZTC_STEP1 = StsGetParam(funcindex, "TRIM_ZTC_STEP1");
    CParam *TRIM_ZTC_STEP2 = StsGetParam(funcindex, "TRIM_ZTC_STEP2");
    CParam *TRIM_ZTC_STEP3 = StsGetParam(funcindex, "TRIM_ZTC_STEP3");
    CParam *TRIM_ZTC_STEP4 = StsGetParam(funcindex, "TRIM_ZTC_STEP4");
    CParam *TRIM_ZTC_STEP5 = StsGetParam(funcindex, "TRIM_ZTC_STEP5");
    CParam *TRIM_ZTC_STEP6 = StsGetParam(funcindex, "TRIM_ZTC_STEP6");
    CParam *TRIM_ZTC_STEP7 = StsGetParam(funcindex, "TRIM_ZTC_STEP7");
    CParam *TRIM_ZTC_STEP8 = StsGetParam(funcindex, "TRIM_ZTC_STEP8");
    CParam *TRIM_ZTC_STEP9 = StsGetParam(funcindex, "TRIM_ZTC_STEP9");
    CParam *TRIM_ZTC_STEP10 = StsGetParam(funcindex, "TRIM_ZTC_STEP10");
    CParam *TRIM_ZTC_STEP11 = StsGetParam(funcindex, "TRIM_ZTC_STEP11");
    CParam *TRIM_ZTC_STEP12 = StsGetParam(funcindex, "TRIM_ZTC_STEP12");
    CParam *TRIM_ZTC_STEP13 = StsGetParam(funcindex, "TRIM_ZTC_STEP13");
    CParam *TRIM_ZTC_STEP14 = StsGetParam(funcindex, "TRIM_ZTC_STEP14");
    CParam *TRIM_ZTC_STEP15 = StsGetParam(funcindex, "TRIM_ZTC_STEP15");
    CParam *TRIM_ZTC_STEP16 = StsGetParam(funcindex, "TRIM_ZTC_STEP16");
    CParam *TRIM_ZTC_STEP17 = StsGetParam(funcindex, "TRIM_ZTC_STEP17");
    CParam *TRIM_ZTC_STEP18 = StsGetParam(funcindex, "TRIM_ZTC_STEP18");
    CParam *TRIM_ZTC_STEP19 = StsGetParam(funcindex, "TRIM_ZTC_STEP19");
    CParam *TRIM_ZTC_STEP20 = StsGetParam(funcindex, "TRIM_ZTC_STEP20");
    CParam *TRIM_ZTC_STEP21 = StsGetParam(funcindex, "TRIM_ZTC_STEP21");
    CParam *TRIM_ZTC_STEP22 = StsGetParam(funcindex, "TRIM_ZTC_STEP22");
    CParam *TRIM_ZTC_STEP23 = StsGetParam(funcindex, "TRIM_ZTC_STEP23");
    CParam *TRIM_ZTC_STEP24 = StsGetParam(funcindex, "TRIM_ZTC_STEP24");
    CParam *TRIM_ZTC_STEP25 = StsGetParam(funcindex, "TRIM_ZTC_STEP25");
    CParam *TRIM_ZTC_STEP26 = StsGetParam(funcindex, "TRIM_ZTC_STEP26");
    CParam *TRIM_ZTC_STEP27 = StsGetParam(funcindex, "TRIM_ZTC_STEP27");
    CParam *TRIM_ZTC_STEP28 = StsGetParam(funcindex, "TRIM_ZTC_STEP28");
    CParam *TRIM_ZTC_STEP29 = StsGetParam(funcindex, "TRIM_ZTC_STEP29");
    CParam *TRIM_ZTC_STEP30 = StsGetParam(funcindex, "TRIM_ZTC_STEP30");
    CParam *TRIM_ZTC_STEP31 = StsGetParam(funcindex, "TRIM_ZTC_STEP31");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	DWORD Trim_PRE_CODE[SITE_NUM] = { 0 };

	if (POWER_FLAG)
	{
		//Qvm.Disconnect();
		cbit.SetOn(/*K4_IIC_PULLUP,*/ K2_VRECT_V5V_CAP, -1);//未接SCL,SDA上拉，读寄存器注意添加！SCL,SDA上拉和DIO都会对低压测试下INTB产生影响
		dioplus.I2CConnect();
		wait_relay();
		TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);//5V,need to power down
	}

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_IBIAS_IO, 2 } ,{ EN_ANA_MUX, 0 }, { MUX_ANA, 0 } });

	INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_us(200);

	INTB.Set(FV, 1, FOVI_2V, FOVI_100UA, RELAY_ON);
	//delay_ms(2);
	dut.trim("TRIM_ZTC").execute(measure_ZTC_trim, spec, funcindex, funclabel, 1, 0, "TRIM_ZTC");

	INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_OFF);

	if (POWER_FLAG)
	{
		TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
    return 0;
}
 
DUT_API int ADC_VREF_BUFFER_TRIM(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *TRIM_ADC_VREF_BUFFER_pre = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_pre");
    CParam *TRIM_ADC_VREF_BUFFER_pre_bit = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_pre_bit");
    CParam *TRIM_ADC_VREF_BUFFER_post = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_post");
    CParam *TRIM_ADC_VREF_BUFFER_post_bit = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_post_bit");
    CParam *TRIM_ADC_VREF_BUFFER_target = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_target");
    CParam *TRIM_ADC_VREF_BUFFER_guessed = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_guessed");
    CParam *TRIM_ADC_VREF_BUFFER_updated = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_updated");
    CParam *TRIM_ADC_VREF_BUFFER_STEP0 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP0");
    CParam *TRIM_ADC_VREF_BUFFER_STEP1 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP1");
    CParam *TRIM_ADC_VREF_BUFFER_STEP2 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP2");
    CParam *TRIM_ADC_VREF_BUFFER_STEP3 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP3");
    CParam *TRIM_ADC_VREF_BUFFER_STEP4 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP4");
    CParam *TRIM_ADC_VREF_BUFFER_STEP5 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP5");
    CParam *TRIM_ADC_VREF_BUFFER_STEP6 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP6");
    CParam *TRIM_ADC_VREF_BUFFER_STEP7 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP7");
    CParam *TRIM_ADC_VREF_BUFFER_STEP8 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP8");
    CParam *TRIM_ADC_VREF_BUFFER_STEP9 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP9");
    CParam *TRIM_ADC_VREF_BUFFER_STEP10 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP10");
    CParam *TRIM_ADC_VREF_BUFFER_STEP11 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP11");
    CParam *TRIM_ADC_VREF_BUFFER_STEP12 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP12");
    CParam *TRIM_ADC_VREF_BUFFER_STEP13 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP13");
    CParam *TRIM_ADC_VREF_BUFFER_STEP14 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP14");
    CParam *TRIM_ADC_VREF_BUFFER_STEP15 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP15");
    CParam *TRIM_ADC_VREF_BUFFER_STEP16 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP16");
    CParam *TRIM_ADC_VREF_BUFFER_STEP17 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP17");
    CParam *TRIM_ADC_VREF_BUFFER_STEP18 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP18");
    CParam *TRIM_ADC_VREF_BUFFER_STEP19 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP19");
    CParam *TRIM_ADC_VREF_BUFFER_STEP20 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP20");
    CParam *TRIM_ADC_VREF_BUFFER_STEP21 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP21");
    CParam *TRIM_ADC_VREF_BUFFER_STEP22 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP22");
    CParam *TRIM_ADC_VREF_BUFFER_STEP23 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP23");
    CParam *TRIM_ADC_VREF_BUFFER_STEP24 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP24");
    CParam *TRIM_ADC_VREF_BUFFER_STEP25 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP25");
    CParam *TRIM_ADC_VREF_BUFFER_STEP26 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP26");
    CParam *TRIM_ADC_VREF_BUFFER_STEP27 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP27");
    CParam *TRIM_ADC_VREF_BUFFER_STEP28 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP28");
    CParam *TRIM_ADC_VREF_BUFFER_STEP29 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP29");
    CParam *TRIM_ADC_VREF_BUFFER_STEP30 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP30");
    CParam *TRIM_ADC_VREF_BUFFER_STEP31 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP31");
    CParam *TRIM_ADC_VREF_BUFFER_STEP32 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP32");
    CParam *TRIM_ADC_VREF_BUFFER_STEP33 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP33");
    CParam *TRIM_ADC_VREF_BUFFER_STEP34 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP34");
    CParam *TRIM_ADC_VREF_BUFFER_STEP35 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP35");
    CParam *TRIM_ADC_VREF_BUFFER_STEP36 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP36");
    CParam *TRIM_ADC_VREF_BUFFER_STEP37 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP37");
    CParam *TRIM_ADC_VREF_BUFFER_STEP38 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP38");
    CParam *TRIM_ADC_VREF_BUFFER_STEP39 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP39");
    CParam *TRIM_ADC_VREF_BUFFER_STEP40 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP40");
    CParam *TRIM_ADC_VREF_BUFFER_STEP41 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP41");
    CParam *TRIM_ADC_VREF_BUFFER_STEP42 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP42");
    CParam *TRIM_ADC_VREF_BUFFER_STEP43 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP43");
    CParam *TRIM_ADC_VREF_BUFFER_STEP44 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP44");
    CParam *TRIM_ADC_VREF_BUFFER_STEP45 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP45");
    CParam *TRIM_ADC_VREF_BUFFER_STEP46 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP46");
    CParam *TRIM_ADC_VREF_BUFFER_STEP47 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP47");
    CParam *TRIM_ADC_VREF_BUFFER_STEP48 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP48");
    CParam *TRIM_ADC_VREF_BUFFER_STEP49 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP49");
    CParam *TRIM_ADC_VREF_BUFFER_STEP50 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP50");
    CParam *TRIM_ADC_VREF_BUFFER_STEP51 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP51");
    CParam *TRIM_ADC_VREF_BUFFER_STEP52 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP52");
    CParam *TRIM_ADC_VREF_BUFFER_STEP53 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP53");
    CParam *TRIM_ADC_VREF_BUFFER_STEP54 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP54");
    CParam *TRIM_ADC_VREF_BUFFER_STEP55 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP55");
    CParam *TRIM_ADC_VREF_BUFFER_STEP56 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP56");
    CParam *TRIM_ADC_VREF_BUFFER_STEP57 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP57");
    CParam *TRIM_ADC_VREF_BUFFER_STEP58 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP58");
    CParam *TRIM_ADC_VREF_BUFFER_STEP59 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP59");
    CParam *TRIM_ADC_VREF_BUFFER_STEP60 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP60");
    CParam *TRIM_ADC_VREF_BUFFER_STEP61 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP61");
    CParam *TRIM_ADC_VREF_BUFFER_STEP62 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP62");
    CParam *TRIM_ADC_VREF_BUFFER_STEP63 = StsGetParam(funcindex, "TRIM_ADC_VREF_BUFFER_STEP63");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	if (POWER_FLAG)
	{
		cbit.SetOn(/*K4_IIC_PULLUP,*/ K2_VRECT_V5V_CAP, -1);//未使用buffer
		Qvm.Connect();
		dioplus.I2CConnect();
		wait_relay();
	}
	TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);//5V


	manager.setfields({ { I2C_CTRL, 1 }, { EN_ANA_MUX, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { MUX_ANA, 0x0B } });
	//INTB.Set(FI, 0, FOVI_5V, FOVI_100UA, RELAY_ON);
	//delay_ms(2);
	//V5V.Set(FV, spec("V5V"), FOVI_10V, FOVI_100MA, RELAY_ON);
	dut.trim("TRIM_ADC_VREF_BUFFER").execute(measure_ADC_VREF_BUFFER_trim, spec, funcindex, funclabel, 1, 0, "TRIM_ADC_VREF_BUFFER");
	
	if (POWER_FLAG)
	{
		TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
		//INTB.Set(FI, 0, FOVI_5V, FOVI_100UA, RELAY_OFF);
	}

    return 0;
}
 
DUT_API int ADC_VIN_BUFFER_TRIM(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *TRIM_ADC_VIN_BUFFER_pre = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_pre");
    CParam *TRIM_ADC_VIN_BUFFER_pre_bit = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_pre_bit");
    CParam *TRIM_ADC_VIN_BUFFER_post = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_post");
    CParam *TRIM_ADC_VIN_BUFFER_post_bit = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_post_bit");
    CParam *TRIM_ADC_VIN_BUFFER_target = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_target");
    CParam *TRIM_ADC_VIN_BUFFER_guessed = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_guessed");
    CParam *TRIM_ADC_VIN_BUFFER_updated = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_updated");
    CParam *TRIM_ADC_VIN_BUFFER_STEP0 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP0");
    CParam *TRIM_ADC_VIN_BUFFER_STEP1 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP1");
    CParam *TRIM_ADC_VIN_BUFFER_STEP2 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP2");
    CParam *TRIM_ADC_VIN_BUFFER_STEP3 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP3");
    CParam *TRIM_ADC_VIN_BUFFER_STEP4 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP4");
    CParam *TRIM_ADC_VIN_BUFFER_STEP5 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP5");
    CParam *TRIM_ADC_VIN_BUFFER_STEP6 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP6");
    CParam *TRIM_ADC_VIN_BUFFER_STEP7 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP7");
    CParam *TRIM_ADC_VIN_BUFFER_STEP8 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP8");
    CParam *TRIM_ADC_VIN_BUFFER_STEP9 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP9");
    CParam *TRIM_ADC_VIN_BUFFER_STEP10 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP10");
    CParam *TRIM_ADC_VIN_BUFFER_STEP11 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP11");
    CParam *TRIM_ADC_VIN_BUFFER_STEP12 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP12");
    CParam *TRIM_ADC_VIN_BUFFER_STEP13 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP13");
    CParam *TRIM_ADC_VIN_BUFFER_STEP14 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP14");
    CParam *TRIM_ADC_VIN_BUFFER_STEP15 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP15");
    CParam *TRIM_ADC_VIN_BUFFER_STEP16 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP16");
    CParam *TRIM_ADC_VIN_BUFFER_STEP17 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP17");
    CParam *TRIM_ADC_VIN_BUFFER_STEP18 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP18");
    CParam *TRIM_ADC_VIN_BUFFER_STEP19 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP19");
    CParam *TRIM_ADC_VIN_BUFFER_STEP20 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP20");
    CParam *TRIM_ADC_VIN_BUFFER_STEP21 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP21");
    CParam *TRIM_ADC_VIN_BUFFER_STEP22 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP22");
    CParam *TRIM_ADC_VIN_BUFFER_STEP23 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP23");
    CParam *TRIM_ADC_VIN_BUFFER_STEP24 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP24");
    CParam *TRIM_ADC_VIN_BUFFER_STEP25 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP25");
    CParam *TRIM_ADC_VIN_BUFFER_STEP26 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP26");
    CParam *TRIM_ADC_VIN_BUFFER_STEP27 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP27");
    CParam *TRIM_ADC_VIN_BUFFER_STEP28 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP28");
    CParam *TRIM_ADC_VIN_BUFFER_STEP29 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP29");
    CParam *TRIM_ADC_VIN_BUFFER_STEP30 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP30");
    CParam *TRIM_ADC_VIN_BUFFER_STEP31 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP31");
    CParam *TRIM_ADC_VIN_BUFFER_STEP32 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP32");
    CParam *TRIM_ADC_VIN_BUFFER_STEP33 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP33");
    CParam *TRIM_ADC_VIN_BUFFER_STEP34 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP34");
    CParam *TRIM_ADC_VIN_BUFFER_STEP35 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP35");
    CParam *TRIM_ADC_VIN_BUFFER_STEP36 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP36");
    CParam *TRIM_ADC_VIN_BUFFER_STEP37 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP37");
    CParam *TRIM_ADC_VIN_BUFFER_STEP38 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP38");
    CParam *TRIM_ADC_VIN_BUFFER_STEP39 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP39");
    CParam *TRIM_ADC_VIN_BUFFER_STEP40 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP40");
    CParam *TRIM_ADC_VIN_BUFFER_STEP41 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP41");
    CParam *TRIM_ADC_VIN_BUFFER_STEP42 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP42");
    CParam *TRIM_ADC_VIN_BUFFER_STEP43 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP43");
    CParam *TRIM_ADC_VIN_BUFFER_STEP44 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP44");
    CParam *TRIM_ADC_VIN_BUFFER_STEP45 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP45");
    CParam *TRIM_ADC_VIN_BUFFER_STEP46 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP46");
    CParam *TRIM_ADC_VIN_BUFFER_STEP47 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP47");
    CParam *TRIM_ADC_VIN_BUFFER_STEP48 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP48");
    CParam *TRIM_ADC_VIN_BUFFER_STEP49 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP49");
    CParam *TRIM_ADC_VIN_BUFFER_STEP50 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP50");
    CParam *TRIM_ADC_VIN_BUFFER_STEP51 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP51");
    CParam *TRIM_ADC_VIN_BUFFER_STEP52 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP52");
    CParam *TRIM_ADC_VIN_BUFFER_STEP53 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP53");
    CParam *TRIM_ADC_VIN_BUFFER_STEP54 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP54");
    CParam *TRIM_ADC_VIN_BUFFER_STEP55 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP55");
    CParam *TRIM_ADC_VIN_BUFFER_STEP56 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP56");
    CParam *TRIM_ADC_VIN_BUFFER_STEP57 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP57");
    CParam *TRIM_ADC_VIN_BUFFER_STEP58 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP58");
    CParam *TRIM_ADC_VIN_BUFFER_STEP59 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP59");
    CParam *TRIM_ADC_VIN_BUFFER_STEP60 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP60");
    CParam *TRIM_ADC_VIN_BUFFER_STEP61 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP61");
    CParam *TRIM_ADC_VIN_BUFFER_STEP62 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP62");
    CParam *TRIM_ADC_VIN_BUFFER_STEP63 = StsGetParam(funcindex, "TRIM_ADC_VIN_BUFFER_STEP63");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	if (POWER_FLAG)
	{
		dioplus.Disconnect("INTB");
		cbit.SetOn(K2_VRECT_V5V_CAP, -1);//未使用buffer
		wait_relay();

		TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);//5V
	}
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { TM_ADC, 1 }, { TM_CH_SEL, 7 }, { TM_ADC_EN, 1 }, { EN_ANA_MUX, 1 }, { MUX_ANA, 0x0e } });
	//delay_ms(1);
	//INTB.Set(FI, 0, FOVI_2V, FOVI_100UA, RELAY_OFF);

	dut.trim("TRIM_ADC_VIN_BUFFER").execute(measure_ADC_VIN_BUFFER_trim, spec, funcindex, funclabel, 1, 0, "TRIM_ADC_VIN_BUFFER");

	//INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_OFF);
	Qvm.Disconnect();
	delay_us(200);

	TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);//5V


    return 0;
}
 
DUT_API int OSC_TRIM(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *TRIM_OSC_pre = StsGetParam(funcindex, "TRIM_OSC_pre");
    CParam *TRIM_OSC_pre_bit = StsGetParam(funcindex, "TRIM_OSC_pre_bit");
    CParam *TRIM_OSC_post = StsGetParam(funcindex, "TRIM_OSC_post");
    CParam *TRIM_OSC_post_bit = StsGetParam(funcindex, "TRIM_OSC_post_bit");
    CParam *TRIM_OSC_target = StsGetParam(funcindex, "TRIM_OSC_target");
    CParam *TRIM_OSC_guessed = StsGetParam(funcindex, "TRIM_OSC_guessed");
    CParam *TRIM_OSC_updated = StsGetParam(funcindex, "TRIM_OSC_updated");
    CParam *TRIM_OSC_STEP0 = StsGetParam(funcindex, "TRIM_OSC_STEP0");
    CParam *TRIM_OSC_STEP1 = StsGetParam(funcindex, "TRIM_OSC_STEP1");
    CParam *TRIM_OSC_STEP2 = StsGetParam(funcindex, "TRIM_OSC_STEP2");
    CParam *TRIM_OSC_STEP3 = StsGetParam(funcindex, "TRIM_OSC_STEP3");
    CParam *TRIM_OSC_STEP4 = StsGetParam(funcindex, "TRIM_OSC_STEP4");
    CParam *TRIM_OSC_STEP5 = StsGetParam(funcindex, "TRIM_OSC_STEP5");
    CParam *TRIM_OSC_STEP6 = StsGetParam(funcindex, "TRIM_OSC_STEP6");
    CParam *TRIM_OSC_STEP7 = StsGetParam(funcindex, "TRIM_OSC_STEP7");
    CParam *TRIM_OSC_STEP8 = StsGetParam(funcindex, "TRIM_OSC_STEP8");
    CParam *TRIM_OSC_STEP9 = StsGetParam(funcindex, "TRIM_OSC_STEP9");
    CParam *TRIM_OSC_STEP10 = StsGetParam(funcindex, "TRIM_OSC_STEP10");
    CParam *TRIM_OSC_STEP11 = StsGetParam(funcindex, "TRIM_OSC_STEP11");
    CParam *TRIM_OSC_STEP12 = StsGetParam(funcindex, "TRIM_OSC_STEP12");
    CParam *TRIM_OSC_STEP13 = StsGetParam(funcindex, "TRIM_OSC_STEP13");
    CParam *TRIM_OSC_STEP14 = StsGetParam(funcindex, "TRIM_OSC_STEP14");
    CParam *TRIM_OSC_STEP15 = StsGetParam(funcindex, "TRIM_OSC_STEP15");
    CParam *TRIM_OSC_STEP16 = StsGetParam(funcindex, "TRIM_OSC_STEP16");
    CParam *TRIM_OSC_STEP17 = StsGetParam(funcindex, "TRIM_OSC_STEP17");
    CParam *TRIM_OSC_STEP18 = StsGetParam(funcindex, "TRIM_OSC_STEP18");
    CParam *TRIM_OSC_STEP19 = StsGetParam(funcindex, "TRIM_OSC_STEP19");
    CParam *TRIM_OSC_STEP20 = StsGetParam(funcindex, "TRIM_OSC_STEP20");
    CParam *TRIM_OSC_STEP21 = StsGetParam(funcindex, "TRIM_OSC_STEP21");
    CParam *TRIM_OSC_STEP22 = StsGetParam(funcindex, "TRIM_OSC_STEP22");
    CParam *TRIM_OSC_STEP23 = StsGetParam(funcindex, "TRIM_OSC_STEP23");
    CParam *TRIM_OSC_STEP24 = StsGetParam(funcindex, "TRIM_OSC_STEP24");
    CParam *TRIM_OSC_STEP25 = StsGetParam(funcindex, "TRIM_OSC_STEP25");
    CParam *TRIM_OSC_STEP26 = StsGetParam(funcindex, "TRIM_OSC_STEP26");
    CParam *TRIM_OSC_STEP27 = StsGetParam(funcindex, "TRIM_OSC_STEP27");
    CParam *TRIM_OSC_STEP28 = StsGetParam(funcindex, "TRIM_OSC_STEP28");
    CParam *TRIM_OSC_STEP29 = StsGetParam(funcindex, "TRIM_OSC_STEP29");
    CParam *TRIM_OSC_STEP30 = StsGetParam(funcindex, "TRIM_OSC_STEP30");
    CParam *TRIM_OSC_STEP31 = StsGetParam(funcindex, "TRIM_OSC_STEP31");
    CParam *TRIM_OSC_STEP32 = StsGetParam(funcindex, "TRIM_OSC_STEP32");
    CParam *TRIM_OSC_STEP33 = StsGetParam(funcindex, "TRIM_OSC_STEP33");
    CParam *TRIM_OSC_STEP34 = StsGetParam(funcindex, "TRIM_OSC_STEP34");
    CParam *TRIM_OSC_STEP35 = StsGetParam(funcindex, "TRIM_OSC_STEP35");
    CParam *TRIM_OSC_STEP36 = StsGetParam(funcindex, "TRIM_OSC_STEP36");
    CParam *TRIM_OSC_STEP37 = StsGetParam(funcindex, "TRIM_OSC_STEP37");
    CParam *TRIM_OSC_STEP38 = StsGetParam(funcindex, "TRIM_OSC_STEP38");
    CParam *TRIM_OSC_STEP39 = StsGetParam(funcindex, "TRIM_OSC_STEP39");
    CParam *TRIM_OSC_STEP40 = StsGetParam(funcindex, "TRIM_OSC_STEP40");
    CParam *TRIM_OSC_STEP41 = StsGetParam(funcindex, "TRIM_OSC_STEP41");
    CParam *TRIM_OSC_STEP42 = StsGetParam(funcindex, "TRIM_OSC_STEP42");
    CParam *TRIM_OSC_STEP43 = StsGetParam(funcindex, "TRIM_OSC_STEP43");
    CParam *TRIM_OSC_STEP44 = StsGetParam(funcindex, "TRIM_OSC_STEP44");
    CParam *TRIM_OSC_STEP45 = StsGetParam(funcindex, "TRIM_OSC_STEP45");
    CParam *TRIM_OSC_STEP46 = StsGetParam(funcindex, "TRIM_OSC_STEP46");
    CParam *TRIM_OSC_STEP47 = StsGetParam(funcindex, "TRIM_OSC_STEP47");
    CParam *TRIM_OSC_STEP48 = StsGetParam(funcindex, "TRIM_OSC_STEP48");
    CParam *TRIM_OSC_STEP49 = StsGetParam(funcindex, "TRIM_OSC_STEP49");
    CParam *TRIM_OSC_STEP50 = StsGetParam(funcindex, "TRIM_OSC_STEP50");
    CParam *TRIM_OSC_STEP51 = StsGetParam(funcindex, "TRIM_OSC_STEP51");
    CParam *TRIM_OSC_STEP52 = StsGetParam(funcindex, "TRIM_OSC_STEP52");
    CParam *TRIM_OSC_STEP53 = StsGetParam(funcindex, "TRIM_OSC_STEP53");
    CParam *TRIM_OSC_STEP54 = StsGetParam(funcindex, "TRIM_OSC_STEP54");
    CParam *TRIM_OSC_STEP55 = StsGetParam(funcindex, "TRIM_OSC_STEP55");
    CParam *TRIM_OSC_STEP56 = StsGetParam(funcindex, "TRIM_OSC_STEP56");
    CParam *TRIM_OSC_STEP57 = StsGetParam(funcindex, "TRIM_OSC_STEP57");
    CParam *TRIM_OSC_STEP58 = StsGetParam(funcindex, "TRIM_OSC_STEP58");
    CParam *TRIM_OSC_STEP59 = StsGetParam(funcindex, "TRIM_OSC_STEP59");
    CParam *TRIM_OSC_STEP60 = StsGetParam(funcindex, "TRIM_OSC_STEP60");
    CParam *TRIM_OSC_STEP61 = StsGetParam(funcindex, "TRIM_OSC_STEP61");
    CParam *TRIM_OSC_STEP62 = StsGetParam(funcindex, "TRIM_OSC_STEP62");
    CParam *TRIM_OSC_STEP63 = StsGetParam(funcindex, "TRIM_OSC_STEP63");
    CParam *TRIM_OSC_STEP64 = StsGetParam(funcindex, "TRIM_OSC_STEP64");
    CParam *TRIM_OSC_STEP65 = StsGetParam(funcindex, "TRIM_OSC_STEP65");
    CParam *TRIM_OSC_STEP66 = StsGetParam(funcindex, "TRIM_OSC_STEP66");
    CParam *TRIM_OSC_STEP67 = StsGetParam(funcindex, "TRIM_OSC_STEP67");
    CParam *TRIM_OSC_STEP68 = StsGetParam(funcindex, "TRIM_OSC_STEP68");
    CParam *TRIM_OSC_STEP69 = StsGetParam(funcindex, "TRIM_OSC_STEP69");
    CParam *TRIM_OSC_STEP70 = StsGetParam(funcindex, "TRIM_OSC_STEP70");
    CParam *TRIM_OSC_STEP71 = StsGetParam(funcindex, "TRIM_OSC_STEP71");
    CParam *TRIM_OSC_STEP72 = StsGetParam(funcindex, "TRIM_OSC_STEP72");
    CParam *TRIM_OSC_STEP73 = StsGetParam(funcindex, "TRIM_OSC_STEP73");
    CParam *TRIM_OSC_STEP74 = StsGetParam(funcindex, "TRIM_OSC_STEP74");
    CParam *TRIM_OSC_STEP75 = StsGetParam(funcindex, "TRIM_OSC_STEP75");
    CParam *TRIM_OSC_STEP76 = StsGetParam(funcindex, "TRIM_OSC_STEP76");
    CParam *TRIM_OSC_STEP77 = StsGetParam(funcindex, "TRIM_OSC_STEP77");
    CParam *TRIM_OSC_STEP78 = StsGetParam(funcindex, "TRIM_OSC_STEP78");
    CParam *TRIM_OSC_STEP79 = StsGetParam(funcindex, "TRIM_OSC_STEP79");
    CParam *TRIM_OSC_STEP80 = StsGetParam(funcindex, "TRIM_OSC_STEP80");
    CParam *TRIM_OSC_STEP81 = StsGetParam(funcindex, "TRIM_OSC_STEP81");
    CParam *TRIM_OSC_STEP82 = StsGetParam(funcindex, "TRIM_OSC_STEP82");
    CParam *TRIM_OSC_STEP83 = StsGetParam(funcindex, "TRIM_OSC_STEP83");
    CParam *TRIM_OSC_STEP84 = StsGetParam(funcindex, "TRIM_OSC_STEP84");
    CParam *TRIM_OSC_STEP85 = StsGetParam(funcindex, "TRIM_OSC_STEP85");
    CParam *TRIM_OSC_STEP86 = StsGetParam(funcindex, "TRIM_OSC_STEP86");
    CParam *TRIM_OSC_STEP87 = StsGetParam(funcindex, "TRIM_OSC_STEP87");
    CParam *TRIM_OSC_STEP88 = StsGetParam(funcindex, "TRIM_OSC_STEP88");
    CParam *TRIM_OSC_STEP89 = StsGetParam(funcindex, "TRIM_OSC_STEP89");
    CParam *TRIM_OSC_STEP90 = StsGetParam(funcindex, "TRIM_OSC_STEP90");
    CParam *TRIM_OSC_STEP91 = StsGetParam(funcindex, "TRIM_OSC_STEP91");
    CParam *TRIM_OSC_STEP92 = StsGetParam(funcindex, "TRIM_OSC_STEP92");
    CParam *TRIM_OSC_STEP93 = StsGetParam(funcindex, "TRIM_OSC_STEP93");
    CParam *TRIM_OSC_STEP94 = StsGetParam(funcindex, "TRIM_OSC_STEP94");
    CParam *TRIM_OSC_STEP95 = StsGetParam(funcindex, "TRIM_OSC_STEP95");
    CParam *TRIM_OSC_STEP96 = StsGetParam(funcindex, "TRIM_OSC_STEP96");
    CParam *TRIM_OSC_STEP97 = StsGetParam(funcindex, "TRIM_OSC_STEP97");
    CParam *TRIM_OSC_STEP98 = StsGetParam(funcindex, "TRIM_OSC_STEP98");
    CParam *TRIM_OSC_STEP99 = StsGetParam(funcindex, "TRIM_OSC_STEP99");
    CParam *TRIM_OSC_STEP100 = StsGetParam(funcindex, "TRIM_OSC_STEP100");
    CParam *TRIM_OSC_STEP101 = StsGetParam(funcindex, "TRIM_OSC_STEP101");
    CParam *TRIM_OSC_STEP102 = StsGetParam(funcindex, "TRIM_OSC_STEP102");
    CParam *TRIM_OSC_STEP103 = StsGetParam(funcindex, "TRIM_OSC_STEP103");
    CParam *TRIM_OSC_STEP104 = StsGetParam(funcindex, "TRIM_OSC_STEP104");
    CParam *TRIM_OSC_STEP105 = StsGetParam(funcindex, "TRIM_OSC_STEP105");
    CParam *TRIM_OSC_STEP106 = StsGetParam(funcindex, "TRIM_OSC_STEP106");
    CParam *TRIM_OSC_STEP107 = StsGetParam(funcindex, "TRIM_OSC_STEP107");
    CParam *TRIM_OSC_STEP108 = StsGetParam(funcindex, "TRIM_OSC_STEP108");
    CParam *TRIM_OSC_STEP109 = StsGetParam(funcindex, "TRIM_OSC_STEP109");
    CParam *TRIM_OSC_STEP110 = StsGetParam(funcindex, "TRIM_OSC_STEP110");
    CParam *TRIM_OSC_STEP111 = StsGetParam(funcindex, "TRIM_OSC_STEP111");
    CParam *TRIM_OSC_STEP112 = StsGetParam(funcindex, "TRIM_OSC_STEP112");
    CParam *TRIM_OSC_STEP113 = StsGetParam(funcindex, "TRIM_OSC_STEP113");
    CParam *TRIM_OSC_STEP114 = StsGetParam(funcindex, "TRIM_OSC_STEP114");
    CParam *TRIM_OSC_STEP115 = StsGetParam(funcindex, "TRIM_OSC_STEP115");
    CParam *TRIM_OSC_STEP116 = StsGetParam(funcindex, "TRIM_OSC_STEP116");
    CParam *TRIM_OSC_STEP117 = StsGetParam(funcindex, "TRIM_OSC_STEP117");
    CParam *TRIM_OSC_STEP118 = StsGetParam(funcindex, "TRIM_OSC_STEP118");
    CParam *TRIM_OSC_STEP119 = StsGetParam(funcindex, "TRIM_OSC_STEP119");
    CParam *TRIM_OSC_STEP120 = StsGetParam(funcindex, "TRIM_OSC_STEP120");
    CParam *TRIM_OSC_STEP121 = StsGetParam(funcindex, "TRIM_OSC_STEP121");
    CParam *TRIM_OSC_STEP122 = StsGetParam(funcindex, "TRIM_OSC_STEP122");
    CParam *TRIM_OSC_STEP123 = StsGetParam(funcindex, "TRIM_OSC_STEP123");
    CParam *TRIM_OSC_STEP124 = StsGetParam(funcindex, "TRIM_OSC_STEP124");
    CParam *TRIM_OSC_STEP125 = StsGetParam(funcindex, "TRIM_OSC_STEP125");
    CParam *TRIM_OSC_STEP126 = StsGetParam(funcindex, "TRIM_OSC_STEP126");
    CParam *TRIM_OSC_STEP127 = StsGetParam(funcindex, "TRIM_OSC_STEP127");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here


	dioplus.I2CConnect();
	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K7_SINK_PULLUP, K23_QTMU_SINK, -1);
	QTMU.Connect();
	wait_relay();

	//SINK.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);

	//SINK.Set(FV, 5, FOVI_10V, FOVI_10MA, RELAY_ON);

	manager.setfields({ { I2C_CTRL, 1 }, { EN_DIG_MUX, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { MUX_DIG, 0x02 } });
	//delay_ms(1);

	QTMU.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_1MHz);
	QTMU.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_1MHz);
	QTMU.SetStartTrigger(1.4, QTMU_PLUS_NEG_SLOPE);
	QTMU.SetInSource(QTMU_PLUS_SINGLE_SOURCE);//SINK

	dut.trim("TRIM_OSC").execute(measure_OSC_trim, spec, funcindex, funclabel, 1, 0, "TRIM_OSC");

	//SINK.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);

	//SINK.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	QTMU.Disconnect();
	cbit.SetOn(-1);//NEED
    return 0;
}
 
DUT_API int COMP_OFF_AC1_TRIM(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *TRIM_LS1_COMP_pre = StsGetParam(funcindex, "TRIM_LS1_COMP_pre");
    CParam *TRIM_LS1_COMP_pre_bit = StsGetParam(funcindex, "TRIM_LS1_COMP_pre_bit");
    CParam *TRIM_LS1_COMP_post = StsGetParam(funcindex, "TRIM_LS1_COMP_post");
    CParam *TRIM_LS1_COMP_post_bit = StsGetParam(funcindex, "TRIM_LS1_COMP_post_bit");
    CParam *TRIM_LS1_COMP_target = StsGetParam(funcindex, "TRIM_LS1_COMP_target");
    CParam *TRIM_LS1_COMP_guessed = StsGetParam(funcindex, "TRIM_LS1_COMP_guessed");
    CParam *TRIM_LS1_COMP_updated = StsGetParam(funcindex, "TRIM_LS1_COMP_updated");
    CParam *TRIM_LS1_COMP_STEP0 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP0");
    CParam *TRIM_LS1_COMP_STEP1 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP1");
    CParam *TRIM_LS1_COMP_STEP2 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP2");
    CParam *TRIM_LS1_COMP_STEP3 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP3");
    CParam *TRIM_LS1_COMP_STEP4 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP4");
    CParam *TRIM_LS1_COMP_STEP5 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP5");
    CParam *TRIM_LS1_COMP_STEP6 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP6");
    CParam *TRIM_LS1_COMP_STEP7 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP7");
    CParam *TRIM_LS1_COMP_STEP8 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP8");
    CParam *TRIM_LS1_COMP_STEP9 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP9");
    CParam *TRIM_LS1_COMP_STEP10 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP10");
    CParam *TRIM_LS1_COMP_STEP11 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP11");
    CParam *TRIM_LS1_COMP_STEP12 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP12");
    CParam *TRIM_LS1_COMP_STEP13 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP13");
    CParam *TRIM_LS1_COMP_STEP14 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP14");
    CParam *TRIM_LS1_COMP_STEP15 = StsGetParam(funcindex, "TRIM_LS1_COMP_STEP15");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	FPVI0.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
	cbit.SetOn(K2_VRECT_V5V_CAP, K1_AC_CAP, K4_IIC_PULLUP, K7_SINK_PULLUP, -1);//未使用buffer
	wait_relay();

	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_ENTER_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
	else
	{
		TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);
	}
	//TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { TMOD_CTRL, 1 }, { EN_DIG_MUX, 1 }, { MUX_DIG, 0x04 } });
	manager.setfields({ { I2C_EN_RECT_LS, 1 }, { TRIM_EN_MOT_MULTI, 1 } });
	//delay_ms(1);

	dut.trim("TRIM_LS1_COMP").execute(measure_AC1_LS_OFF_trim, spec, funcindex, funclabel, 1, 0, "TRIM_LS1_COMP");

	AC1.Set(FV, 0.1, FOVI_1V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	AC1.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	SINK.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_ms(1);

	if (POWER_FLAG)
	{
		if (Global_Tempchar_Program_Flag == 1)
		{
			TM_EXIT_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
		}
		else
		{
			TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);
		}
		AC1.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_OFF);
		AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
		SINK.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_OFF);
		delay_ms(1);
		dioplus.I2CDisconnect();
		cbit.SetOn(-1);//NEED
	}

    return 0;
}
 
DUT_API int COMP_OFF_AC2_TRIM(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *TRIM_LS2_COMP_pre = StsGetParam(funcindex, "TRIM_LS2_COMP_pre");
    CParam *TRIM_LS2_COMP_pre_bit = StsGetParam(funcindex, "TRIM_LS2_COMP_pre_bit");
    CParam *TRIM_LS2_COMP_post = StsGetParam(funcindex, "TRIM_LS2_COMP_post");
    CParam *TRIM_LS2_COMP_post_bit = StsGetParam(funcindex, "TRIM_LS2_COMP_post_bit");
    CParam *TRIM_LS2_COMP_target = StsGetParam(funcindex, "TRIM_LS2_COMP_target");
    CParam *TRIM_LS2_COMP_guessed = StsGetParam(funcindex, "TRIM_LS2_COMP_guessed");
    CParam *TRIM_LS2_COMP_updated = StsGetParam(funcindex, "TRIM_LS2_COMP_updated");
    CParam *TRIM_LS2_COMP_STEP0 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP0");
    CParam *TRIM_LS2_COMP_STEP1 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP1");
    CParam *TRIM_LS2_COMP_STEP2 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP2");
    CParam *TRIM_LS2_COMP_STEP3 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP3");
    CParam *TRIM_LS2_COMP_STEP4 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP4");
    CParam *TRIM_LS2_COMP_STEP5 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP5");
    CParam *TRIM_LS2_COMP_STEP6 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP6");
    CParam *TRIM_LS2_COMP_STEP7 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP7");
    CParam *TRIM_LS2_COMP_STEP8 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP8");
    CParam *TRIM_LS2_COMP_STEP9 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP9");
    CParam *TRIM_LS2_COMP_STEP10 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP10");
    CParam *TRIM_LS2_COMP_STEP11 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP11");
    CParam *TRIM_LS2_COMP_STEP12 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP12");
    CParam *TRIM_LS2_COMP_STEP13 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP13");
    CParam *TRIM_LS2_COMP_STEP14 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP14");
    CParam *TRIM_LS2_COMP_STEP15 = StsGetParam(funcindex, "TRIM_LS2_COMP_STEP15");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	if (POWER_FLAG)
	{
		dioplus.I2CConnect();
		cbit.SetOn(K2_VRECT_V5V_CAP, K1_AC_CAP, K4_IIC_PULLUP, K7_SINK_PULLUP, -1);//未使用buffer
		wait_relay();

		if (Global_Tempchar_Program_Flag == 1)
		{
			TM_ENTER_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
		}
		else
		{
			TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);
		}
		//TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);

		manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { TMOD_CTRL, 1 }, { EN_DIG_MUX, 1 }, { MUX_DIG, 0x05 } });
		manager.setfields({ { I2C_EN_RECT_LS, 1 }, { TRIM_EN_MOT_MULTI, 1 } });
		//delay_ms(1);
	}
	else
	{
		manager.setfields({ { MUX_DIG, 0x05 } });
		delay_ms(1);
	}

	dut.trim("TRIM_LS2_COMP").execute(measure_AC2_LS_OFF_trim, spec, funcindex, funclabel, 1, 0, "TRIM_LS2_COMP");

	AC2.Set(FV, 0.1, FOVI_1V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
	SINK.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_ms(1);

	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_EXIT_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
	else
	{
		TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);
	}

	dioplus.I2CDisconnect();
	AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	AC2.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_OFF);
	SINK.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_OFF);
	cbit.SetOn(-1);//NEED

    return 0;
}
 
DUT_API int ISNS_GAIN_TRIM(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *TRIM_ISNS_GAIN_pre = StsGetParam(funcindex, "TRIM_ISNS_GAIN_pre");
    CParam *TRIM_ISNS_GAIN_pre_bit = StsGetParam(funcindex, "TRIM_ISNS_GAIN_pre_bit");
    CParam *TRIM_ISNS_GAIN_post = StsGetParam(funcindex, "TRIM_ISNS_GAIN_post");
    CParam *TRIM_ISNS_GAIN_post_bit = StsGetParam(funcindex, "TRIM_ISNS_GAIN_post_bit");
    CParam *TRIM_ISNS_GAIN_target = StsGetParam(funcindex, "TRIM_ISNS_GAIN_target");
    CParam *TRIM_ISNS_GAIN_guessed = StsGetParam(funcindex, "TRIM_ISNS_GAIN_guessed");
    CParam *TRIM_ISNS_GAIN_updated = StsGetParam(funcindex, "TRIM_ISNS_GAIN_updated");
    CParam *TRIM_ISNS_GAIN_STEP0 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP0");
    CParam *TRIM_ISNS_GAIN_STEP1 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP1");
    CParam *TRIM_ISNS_GAIN_STEP2 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP2");
    CParam *TRIM_ISNS_GAIN_STEP3 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP3");
    CParam *TRIM_ISNS_GAIN_STEP4 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP4");
    CParam *TRIM_ISNS_GAIN_STEP5 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP5");
    CParam *TRIM_ISNS_GAIN_STEP6 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP6");
    CParam *TRIM_ISNS_GAIN_STEP7 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP7");
    CParam *TRIM_ISNS_GAIN_STEP8 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP8");
    CParam *TRIM_ISNS_GAIN_STEP9 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP9");
    CParam *TRIM_ISNS_GAIN_STEP10 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP10");
    CParam *TRIM_ISNS_GAIN_STEP11 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP11");
    CParam *TRIM_ISNS_GAIN_STEP12 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP12");
    CParam *TRIM_ISNS_GAIN_STEP13 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP13");
    CParam *TRIM_ISNS_GAIN_STEP14 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP14");
    CParam *TRIM_ISNS_GAIN_STEP15 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP15");
    CParam *TRIM_ISNS_GAIN_STEP16 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP16");
    CParam *TRIM_ISNS_GAIN_STEP17 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP17");
    CParam *TRIM_ISNS_GAIN_STEP18 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP18");
    CParam *TRIM_ISNS_GAIN_STEP19 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP19");
    CParam *TRIM_ISNS_GAIN_STEP20 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP20");
    CParam *TRIM_ISNS_GAIN_STEP21 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP21");
    CParam *TRIM_ISNS_GAIN_STEP22 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP22");
    CParam *TRIM_ISNS_GAIN_STEP23 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP23");
    CParam *TRIM_ISNS_GAIN_STEP24 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP24");
    CParam *TRIM_ISNS_GAIN_STEP25 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP25");
    CParam *TRIM_ISNS_GAIN_STEP26 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP26");
    CParam *TRIM_ISNS_GAIN_STEP27 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP27");
    CParam *TRIM_ISNS_GAIN_STEP28 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP28");
    CParam *TRIM_ISNS_GAIN_STEP29 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP29");
    CParam *TRIM_ISNS_GAIN_STEP30 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP30");
    CParam *TRIM_ISNS_GAIN_STEP31 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP31");
    CParam *TRIM_ISNS_GAIN_STEP32 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP32");
    CParam *TRIM_ISNS_GAIN_STEP33 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP33");
    CParam *TRIM_ISNS_GAIN_STEP34 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP34");
    CParam *TRIM_ISNS_GAIN_STEP35 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP35");
    CParam *TRIM_ISNS_GAIN_STEP36 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP36");
    CParam *TRIM_ISNS_GAIN_STEP37 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP37");
    CParam *TRIM_ISNS_GAIN_STEP38 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP38");
    CParam *TRIM_ISNS_GAIN_STEP39 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP39");
    CParam *TRIM_ISNS_GAIN_STEP40 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP40");
    CParam *TRIM_ISNS_GAIN_STEP41 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP41");
    CParam *TRIM_ISNS_GAIN_STEP42 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP42");
    CParam *TRIM_ISNS_GAIN_STEP43 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP43");
    CParam *TRIM_ISNS_GAIN_STEP44 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP44");
    CParam *TRIM_ISNS_GAIN_STEP45 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP45");
    CParam *TRIM_ISNS_GAIN_STEP46 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP46");
    CParam *TRIM_ISNS_GAIN_STEP47 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP47");
    CParam *TRIM_ISNS_GAIN_STEP48 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP48");
    CParam *TRIM_ISNS_GAIN_STEP49 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP49");
    CParam *TRIM_ISNS_GAIN_STEP50 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP50");
    CParam *TRIM_ISNS_GAIN_STEP51 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP51");
    CParam *TRIM_ISNS_GAIN_STEP52 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP52");
    CParam *TRIM_ISNS_GAIN_STEP53 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP53");
    CParam *TRIM_ISNS_GAIN_STEP54 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP54");
    CParam *TRIM_ISNS_GAIN_STEP55 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP55");
    CParam *TRIM_ISNS_GAIN_STEP56 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP56");
    CParam *TRIM_ISNS_GAIN_STEP57 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP57");
    CParam *TRIM_ISNS_GAIN_STEP58 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP58");
    CParam *TRIM_ISNS_GAIN_STEP59 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP59");
    CParam *TRIM_ISNS_GAIN_STEP60 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP60");
    CParam *TRIM_ISNS_GAIN_STEP61 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP61");
    CParam *TRIM_ISNS_GAIN_STEP62 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP62");
    CParam *TRIM_ISNS_GAIN_STEP63 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP63");
    CParam *TRIM_ISNS_GAIN_STEP64 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP64");
    CParam *TRIM_ISNS_GAIN_STEP65 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP65");
    CParam *TRIM_ISNS_GAIN_STEP66 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP66");
    CParam *TRIM_ISNS_GAIN_STEP67 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP67");
    CParam *TRIM_ISNS_GAIN_STEP68 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP68");
    CParam *TRIM_ISNS_GAIN_STEP69 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP69");
    CParam *TRIM_ISNS_GAIN_STEP70 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP70");
    CParam *TRIM_ISNS_GAIN_STEP71 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP71");
    CParam *TRIM_ISNS_GAIN_STEP72 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP72");
    CParam *TRIM_ISNS_GAIN_STEP73 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP73");
    CParam *TRIM_ISNS_GAIN_STEP74 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP74");
    CParam *TRIM_ISNS_GAIN_STEP75 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP75");
    CParam *TRIM_ISNS_GAIN_STEP76 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP76");
    CParam *TRIM_ISNS_GAIN_STEP77 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP77");
    CParam *TRIM_ISNS_GAIN_STEP78 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP78");
    CParam *TRIM_ISNS_GAIN_STEP79 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP79");
    CParam *TRIM_ISNS_GAIN_STEP80 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP80");
    CParam *TRIM_ISNS_GAIN_STEP81 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP81");
    CParam *TRIM_ISNS_GAIN_STEP82 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP82");
    CParam *TRIM_ISNS_GAIN_STEP83 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP83");
    CParam *TRIM_ISNS_GAIN_STEP84 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP84");
    CParam *TRIM_ISNS_GAIN_STEP85 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP85");
    CParam *TRIM_ISNS_GAIN_STEP86 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP86");
    CParam *TRIM_ISNS_GAIN_STEP87 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP87");
    CParam *TRIM_ISNS_GAIN_STEP88 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP88");
    CParam *TRIM_ISNS_GAIN_STEP89 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP89");
    CParam *TRIM_ISNS_GAIN_STEP90 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP90");
    CParam *TRIM_ISNS_GAIN_STEP91 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP91");
    CParam *TRIM_ISNS_GAIN_STEP92 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP92");
    CParam *TRIM_ISNS_GAIN_STEP93 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP93");
    CParam *TRIM_ISNS_GAIN_STEP94 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP94");
    CParam *TRIM_ISNS_GAIN_STEP95 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP95");
    CParam *TRIM_ISNS_GAIN_STEP96 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP96");
    CParam *TRIM_ISNS_GAIN_STEP97 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP97");
    CParam *TRIM_ISNS_GAIN_STEP98 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP98");
    CParam *TRIM_ISNS_GAIN_STEP99 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP99");
    CParam *TRIM_ISNS_GAIN_STEP100 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP100");
    CParam *TRIM_ISNS_GAIN_STEP101 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP101");
    CParam *TRIM_ISNS_GAIN_STEP102 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP102");
    CParam *TRIM_ISNS_GAIN_STEP103 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP103");
    CParam *TRIM_ISNS_GAIN_STEP104 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP104");
    CParam *TRIM_ISNS_GAIN_STEP105 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP105");
    CParam *TRIM_ISNS_GAIN_STEP106 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP106");
    CParam *TRIM_ISNS_GAIN_STEP107 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP107");
    CParam *TRIM_ISNS_GAIN_STEP108 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP108");
    CParam *TRIM_ISNS_GAIN_STEP109 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP109");
    CParam *TRIM_ISNS_GAIN_STEP110 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP110");
    CParam *TRIM_ISNS_GAIN_STEP111 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP111");
    CParam *TRIM_ISNS_GAIN_STEP112 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP112");
    CParam *TRIM_ISNS_GAIN_STEP113 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP113");
    CParam *TRIM_ISNS_GAIN_STEP114 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP114");
    CParam *TRIM_ISNS_GAIN_STEP115 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP115");
    CParam *TRIM_ISNS_GAIN_STEP116 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP116");
    CParam *TRIM_ISNS_GAIN_STEP117 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP117");
    CParam *TRIM_ISNS_GAIN_STEP118 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP118");
    CParam *TRIM_ISNS_GAIN_STEP119 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP119");
    CParam *TRIM_ISNS_GAIN_STEP120 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP120");
    CParam *TRIM_ISNS_GAIN_STEP121 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP121");
    CParam *TRIM_ISNS_GAIN_STEP122 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP122");
    CParam *TRIM_ISNS_GAIN_STEP123 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP123");
    CParam *TRIM_ISNS_GAIN_STEP124 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP124");
    CParam *TRIM_ISNS_GAIN_STEP125 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP125");
    CParam *TRIM_ISNS_GAIN_STEP126 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP126");
    CParam *TRIM_ISNS_GAIN_STEP127 = StsGetParam(funcindex, "TRIM_ISNS_GAIN_STEP127");
    CParam *TRIM_ISNS_GAIN_retestflag = StsGetParam(funcindex, "TRIM_ISNS_GAIN_retestflag");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here
	double period = 10 * 1e-6; //100k for function test
	dioplus.I2CSetClockPeriod(period);
	dioplus.I2CSetSCLDelay(0, period / 2);
	dioplus.I2CSetSDADelay(period / 6, period / 2, period * 2 / 3);

	dioplus.SetVIH(5.0f);
	dioplus.SetVIL(0.0f);
	dioplus.SetVOH(2.2f);
	dioplus.SetVOL(0.4f);
	delay_ms(1);
	cbit.SetOn(K2_VRECT_V5V_CAP, K4_IIC_PULLUP, K3_VOUT_CAP, K13_PVI0H_PGND, K17_PVI0L_VOUT,K11_OVI7_VOUT_COMM2, - 1);//FPVI0H_PGND,FPVI0L_VOUT; disconnect VOUT FOVI resource
	dioplus.I2CConnect();
	//Qvm.Connect();
	QTMU.Disconnect(); 
	wait_relay();

	VOUT.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);//GND-VOUT
	INTB.Set(FI, 0, FOVI_2V, FOVI_1MA, RELAY_ON);
	//INTB.Set(FV, 0, FOVI_2V, FOVI_1MA, RELAY_OFF);
	delay_us(500);

	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_ENTER_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_1A);
	}
	else
	{
		TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
	}

	//A0的VOUT dummyload默认关，无需手动配置
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_VCP, 1 }, 
	{ I2C_EN_LDO_PWR, 1 }, { I2C_DIS_SS, 1 }, { I2C_REF_IN, 0x80 }/*, { I2C_ILOAD_H, 1 }*/, { EN_ANA_MUX, 1 }, { MUX_ANA, 0x08 } });
	//delay_ms(1);
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	FPVI0.SetClamp(75, 75);

	dut.trim("TRIM_ISNS_GAIN").execute(measure_ISNS_GAIN_trim, spec, funcindex, funclabel, 1, 0, "TRIM_ISNS_GAIN");
	
	//20260514 ADD
	Trim_Retest(measure_ISNS_GAIN_retest, 128, 11, funcindex, funclabel, "TRIM_ISNS_GAIN");

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	//INTB.Set(FI, 0, FOVI_2V, FOVI_1MA, RELAY_ON);
	FPVI0.SetClamp(100, 100);
	delay_ms(1);
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);//GND-VOUT

	if (POWER_FLAG)
	{
		if (Global_Tempchar_Program_Flag == 1)
		{
			TM_EXIT_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_1A);
		}
		else
		{
			TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
		}

		INTB.Set(FV, 0, FOVI_2V, FOVI_1MA, RELAY_ON);
		delay_us(200);


		FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);//GND-VOUT
		INTB.Set(FV, 0, FOVI_2V, FOVI_1MA, RELAY_OFF);
		dioplus.I2CDisconnect();
		Qvm.Disconnect();

	}

    return 0;
}
 
DUT_API int ISNS_OFFSET_TRIM(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *ISNS_10mA_SCM = StsGetParam(funcindex, "ISNS_10mA_SCM");
    CParam *ISNS_ADC_OS_50mA = StsGetParam(funcindex, "ISNS_ADC_OS_50mA");
    CParam *ISNS_ADC_OS_50mA_Ivout = StsGetParam(funcindex, "ISNS_ADC_OS_50mA_Ivout");
    CParam *ISNS_ADC_OS_500mA_DS = StsGetParam(funcindex, "ISNS_ADC_OS_500mA_DS");
    CParam *ISNS_ADC_OS_500mA_Ivout = StsGetParam(funcindex, "ISNS_ADC_OS_500mA_Ivout");
    CParam *TRIM_ISNS_OFFSET_pre = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_pre");
    CParam *TRIM_ISNS_OFFSET_pre_bit = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_pre_bit");
    CParam *TRIM_ISNS_OFFSET_post = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_post");
    CParam *TRIM_ISNS_OFFSET_post_bit = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_post_bit");
    CParam *TRIM_ISNS_OFFSET_target = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_target");
    CParam *TRIM_ISNS_OFFSET_guessed = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_guessed");
    CParam *TRIM_ISNS_OFFSET_updated = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_updated");
    CParam *TRIM_ISNS_OFFSET_STEP0 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP0");
    CParam *TRIM_ISNS_OFFSET_STEP1 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP1");
    CParam *TRIM_ISNS_OFFSET_STEP2 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP2");
    CParam *TRIM_ISNS_OFFSET_STEP3 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP3");
    CParam *TRIM_ISNS_OFFSET_STEP4 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP4");
    CParam *TRIM_ISNS_OFFSET_STEP5 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP5");
    CParam *TRIM_ISNS_OFFSET_STEP6 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP6");
    CParam *TRIM_ISNS_OFFSET_STEP7 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP7");
    CParam *TRIM_ISNS_OFFSET_STEP8 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP8");
    CParam *TRIM_ISNS_OFFSET_STEP9 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP9");
    CParam *TRIM_ISNS_OFFSET_STEP10 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP10");
    CParam *TRIM_ISNS_OFFSET_STEP11 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP11");
    CParam *TRIM_ISNS_OFFSET_STEP12 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP12");
    CParam *TRIM_ISNS_OFFSET_STEP13 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP13");
    CParam *TRIM_ISNS_OFFSET_STEP14 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP14");
    CParam *TRIM_ISNS_OFFSET_STEP15 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP15");
    CParam *TRIM_ISNS_OFFSET_STEP16 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP16");
    CParam *TRIM_ISNS_OFFSET_STEP17 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP17");
    CParam *TRIM_ISNS_OFFSET_STEP18 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP18");
    CParam *TRIM_ISNS_OFFSET_STEP19 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP19");
    CParam *TRIM_ISNS_OFFSET_STEP20 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP20");
    CParam *TRIM_ISNS_OFFSET_STEP21 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP21");
    CParam *TRIM_ISNS_OFFSET_STEP22 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP22");
    CParam *TRIM_ISNS_OFFSET_STEP23 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP23");
    CParam *TRIM_ISNS_OFFSET_STEP24 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP24");
    CParam *TRIM_ISNS_OFFSET_STEP25 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP25");
    CParam *TRIM_ISNS_OFFSET_STEP26 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP26");
    CParam *TRIM_ISNS_OFFSET_STEP27 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP27");
    CParam *TRIM_ISNS_OFFSET_STEP28 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP28");
    CParam *TRIM_ISNS_OFFSET_STEP29 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP29");
    CParam *TRIM_ISNS_OFFSET_STEP30 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP30");
    CParam *TRIM_ISNS_OFFSET_STEP31 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP31");
    CParam *TRIM_ISNS_OFFSET_STEP32 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP32");
    CParam *TRIM_ISNS_OFFSET_STEP33 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP33");
    CParam *TRIM_ISNS_OFFSET_STEP34 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP34");
    CParam *TRIM_ISNS_OFFSET_STEP35 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP35");
    CParam *TRIM_ISNS_OFFSET_STEP36 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP36");
    CParam *TRIM_ISNS_OFFSET_STEP37 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP37");
    CParam *TRIM_ISNS_OFFSET_STEP38 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP38");
    CParam *TRIM_ISNS_OFFSET_STEP39 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP39");
    CParam *TRIM_ISNS_OFFSET_STEP40 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP40");
    CParam *TRIM_ISNS_OFFSET_STEP41 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP41");
    CParam *TRIM_ISNS_OFFSET_STEP42 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP42");
    CParam *TRIM_ISNS_OFFSET_STEP43 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP43");
    CParam *TRIM_ISNS_OFFSET_STEP44 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP44");
    CParam *TRIM_ISNS_OFFSET_STEP45 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP45");
    CParam *TRIM_ISNS_OFFSET_STEP46 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP46");
    CParam *TRIM_ISNS_OFFSET_STEP47 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP47");
    CParam *TRIM_ISNS_OFFSET_STEP48 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP48");
    CParam *TRIM_ISNS_OFFSET_STEP49 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP49");
    CParam *TRIM_ISNS_OFFSET_STEP50 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP50");
    CParam *TRIM_ISNS_OFFSET_STEP51 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP51");
    CParam *TRIM_ISNS_OFFSET_STEP52 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP52");
    CParam *TRIM_ISNS_OFFSET_STEP53 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP53");
    CParam *TRIM_ISNS_OFFSET_STEP54 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP54");
    CParam *TRIM_ISNS_OFFSET_STEP55 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP55");
    CParam *TRIM_ISNS_OFFSET_STEP56 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP56");
    CParam *TRIM_ISNS_OFFSET_STEP57 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP57");
    CParam *TRIM_ISNS_OFFSET_STEP58 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP58");
    CParam *TRIM_ISNS_OFFSET_STEP59 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP59");
    CParam *TRIM_ISNS_OFFSET_STEP60 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP60");
    CParam *TRIM_ISNS_OFFSET_STEP61 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP61");
    CParam *TRIM_ISNS_OFFSET_STEP62 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP62");
    CParam *TRIM_ISNS_OFFSET_STEP63 = StsGetParam(funcindex, "TRIM_ISNS_OFFSET_STEP63");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here
	
	//double period = 2 * 1e-6; //500k for function test
	//dioplus.I2CSetClockPeriod(period);
	//dioplus.I2CSetSCLDelay(0, period / 2);
	//dioplus.I2CSetSDADelay(period / 6, period / 2, period * 2 / 3);

	//dioplus.SetVIH(5.0f);
	//dioplus.SetVIL(0.0f);
	//dioplus.SetVOH(2.2f);
	//dioplus.SetVOL(0.4f); 
	int data_adc_h[SITE_COUNT] = { 0 };
	int data_adc_l[SITE_COUNT] = { 0 };
	int read_adc_code[SITE_COUNT] = { 0 };
	double adc_ana_input[SITE_COUNT] = { 0.0 };
	Qvm.Connect();

	if (POWER_FLAG)
	{
		dioplus.I2CConnect();
		cbit.SetOn(K2_VRECT_V5V_CAP, K4_IIC_PULLUP, K3_VOUT_CAP, K13_PVI0H_PGND, K17_PVI0L_VOUT, K11_OVI7_VOUT_COMM2, -1);//FPVI0H_PGND,FPVI0L_VOUT; disconnect VOUT FOVI resource
		wait_relay();

		//VOUT.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
		VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
		if (Global_Tempchar_Program_Flag == 1)
		{
			TM_ENTER_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_1A);
		}
		else
		{
			TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
		}
		delay_ms(1);

		//A0的VOUT dummyload默认关，无需手动配置
		manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_VCP, 1 },
		{ I2C_EN_LDO_PWR, 1 }, { I2C_DIS_SS, 1 }, { I2C_REF_IN, 0x80 }/*, { I2C_ILOAD_H, 1 }*/, { EN_ANA_MUX, 1 }, { MUX_ANA, 0x08 } });
		delay_ms(1);
	}

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	//INTB.Set(FI, 0, FOVI_2V, FOVI_1MA, RELAY_ON);
	INTB.Set(FV, 0, FOVI_2V, FOVI_1MA, RELAY_OFF);
	FPVI0.SetClamp(75, 75);


	dut.trim("TRIM_ISNS_OFFSET").execute(measure_ISNS_OFFSET_trim, spec, funcindex, funclabel, 1, 0, "TRIM_ISNS_OFFSET");

	Qvm.Disconnect();
	delay_ms(1);


	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	//INTB.Set(FI, 0, FOVI_5V, FOVI_1MA, RELAY_ON);
	delay_us(200);
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);//GND-VOUT
	FPVI0.SetClamp(100, 100);

	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_EXIT_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_1A);
	}
	else
	{
		TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
	}
	FPVI0.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);//GND-VOUT
	delay_us(200);

	FPVI0.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);//GND-VOUT
	INTB.Set(FI, 0, FOVI_5V, FOVI_1MA, RELAY_OFF);
	
// 	if (Global_FTQC_FLAG == 1)//QC
// 	{
// 		if (Global_Tempchar_Program_Flag == 1)
// 		{
// 			TM_EXIT_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_1A);
// 		}
// 		else
// 		{
// 			TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
// 		}
// 		delay_ms(1);
// 
// 		if (Global_Tempchar_Program_Flag == 1)
// 		{
// 			TM_ENTER_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_1A);
// 		}
// 		else
// 		{
// 			TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
// 		}
// 		//A0的VOUT dummyload默认关，无需手动配置
// 		manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_VCP, 1 },
// 		{ I2C_EN_LDO_PWR, 1 }, { I2C_DIS_SS, 1 }, { I2C_REF_IN, 0x80 }/*, { I2C_ILOAD_H, 1 }*/, { EN_ANA_MUX, 1 }, { MUX_ANA, 0x08 } });
// 		delay_ms(1);
// 	}
// 
// 
// 	EEPROM_ISNS_OFFSET_trim();
// 	delay_ms(3);
// 
// 	//ISNS ADC 10mA
// 	INTB.Set(FI, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
// 	FPVI0.Set(FI, 0.01, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT=10mA
// 	delay_ms(1);
// 	if (Global_Tempchar_Program_Flag == 1)
// 	{
// 		delay_ms(5);
// 	}
// 	INTB.MeasureVI(50, 10);
// 
// 	SERIAL
// 	{
// 		adresult[SITE] = INTB.GetMeasResult(SITE, MVRET);
// 		ISNS_10mA_SCM->SetTestResult(SITE, 0, adresult[SITE] * 1E3);//mV
// 	}
// 	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
// 	INTB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
// 	delay_ms(3);
// 	TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
// 	INTB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_OFF);
// 	delay_ms(1);
// 	TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
// 
// 	EEPROM_ISNS_OFFSET_trim();
// 	delay_ms(3);
// 
// 	//ISNSADC_OS_0.05A
// 	//manager.setfields({ { EN_ANA_MUX, 0 }, { MUX_ANA, 0 }, { I2C_ILOAD_H, 1 }, { T_RSAMPLE, 1 }, { TM_ADC, 1 }, { TM_CH_SEL, 1 } });
// 	//manager.setfields({  { TM_ADC_START, 0 }, { TM_CONTINUE_MODE, 0 }, { TM_ADC_EN, 0 } });
// 	manager.historyClear();//clear history value
// 	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_VCP, 1 },
// 	{ I2C_EN_LDO_PWR, 1 }, { I2C_DIS_SS, 1 }, { I2C_REF_IN, 0x80 }, { I2C_ILOAD_H, 1 }, { T_RSAMPLE, 1 }, { TM_ADC, 1 }, { TM_CH_SEL, 1 } });
// 	delay_ms(2);
// 	manager.setfields({ { TM_ADC_START, 1 }, { TM_CONTINUE_MODE, 1 }, { TM_ADC_EN, 1 } });
// 	delay_ms(10);
// 
// 
// 	FPVI0.Set(FI, 0.05, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT=50mA
// 	delay_ms(2);
// 	FPVI0.Set(FI, 0.05, FPVI10_10V, FPVI10_100MA, RELAY_ON);//GND-VOUT=50mA
// 	delay_ms(2);
// 
// 	manager.setfields({ { TM_CONTINUE_MODE, 0 } });
// 	delay_ms(2);
// 
// 	FPVI0.MeasureVI(50, 10);
// 	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X98, 2);
// 
// 	SERIAL
// 	{
// 		adresult5[SITE] = FPVI0.GetMeasResult(SITE, MIRET);
// 		data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x98 value
// 		data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x99 value
// 	}
// 
// 	SERIAL
// 	{
// 		read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x98 bit0~7 + 0x99 bit0~1
// 		adc_ana_input[SITE] = double(read_adc_code[SITE]) / 1023 * 2;
// 		adresult1[SITE] = adc_ana_input[SITE] - adresult5[SITE];
// 		adresult[SITE] = adresult1[SITE] * 1e3;
// 
// 		ISNS_ADC_OS_50mA->SetTestResult(SITE, 0, adresult[SITE]);
// 		ISNS_ADC_OS_50mA_Ivout->SetTestResult(SITE, 0, adresult5[SITE] * 1e3);
// 	}
// 	FPVI0.Set(FI, 0.05, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT=50mA
// 	delay_ms(2);
// 	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
// 	//manager.setfields({ { TM_ADC_START, 0 }, { TM_CONTINUE_MODE, 0 }, { TM_ADC_EN, 0 } });
// 	delay_ms(2);
// 
// 	//ISNSADC_OS_0.5A
// 	manager.setfields({ { TM_ADC_START, 1 }, { TM_CONTINUE_MODE, 1 }, { TM_ADC_EN, 1 } });
// 
// 	FPVI0.Set(FI, 0.5, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT=500mA
// 	delay_ms(2);
// 
// 	manager.setfields({ { TM_CONTINUE_MODE, 0 } });
// 	delay_ms(15);//delay for read stably
// 
// 	FPVI0.MeasureVI(50, 10);
// 	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X3F, 2);
// 
// 	SERIAL
// 	{
// 		adresult6[SITE] = FPVI0.GetMeasResult(SITE, MIRET);
// 		data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x3f value
// 		data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x40 value
// 	}
// 
// 	//delay_ms(2);
// 	//dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X3F, 2);
// 	//SERIAL
// 	//{
// 	//	data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x3f value
// 	//	data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x40 value
// 	//}
// 
// 	SERIAL
// 	{
// 		read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x98 bit0~7 + 0x99 bit0~1
// 		adc_ana_input[SITE] = double(read_adc_code[SITE]) / 1023 * 2;
// 		adresult2[SITE] = adc_ana_input[SITE] - adresult6[SITE];
// 		adresult[SITE] = adresult2[SITE] * 1e3;
// 
// 		ISNS_ADC_OS_500mA_DS->SetTestResult(SITE, 0, adresult[SITE]);
// 		ISNS_ADC_OS_500mA_Ivout->SetTestResult(SITE, 0, adresult6[SITE] * 1e3);
// 	}
// 	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
// 	delay_ms(2);
// 
// 	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);//GND-VOUT=10mA
// 	delay_ms(1);
// 	//if (POWER_FLAG)
// 	//{
// 	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);//GND-VOUT
// 	FPVI0.SetClamp(100, 100);
// 
// 	if (Global_Tempchar_Program_Flag == 1)
// 	{
// 		TM_EXIT_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_1A);
// 	}
// 	else
// 	{
// 		TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
// 	}
// 	FPVI0.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);//GND-VOUT
// 	delay_ms(1);
// 
// 	FPVI0.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);//GND-VOUT
// 	dioplus.I2CDisconnect();

    return 0;
}
 
DUT_API int EFUSE_BURN(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *Burn_Pass_flag = StsGetParam(funcindex, "Burn_Pass_flag");
    CParam *AFTER_BURN_VBG_CODE = StsGetParam(funcindex, "AFTER_BURN_VBG_CODE");
    CParam *AFTER_BURN_ZTC_CODE = StsGetParam(funcindex, "AFTER_BURN_ZTC_CODE");
    CParam *AFTER_BURN_ADC_VREF_BUFFER_CODE = StsGetParam(funcindex, "AFTER_BURN_ADC_VREF_BUFFER_CODE");
    CParam *AFTER_BURN_ADC_VIN_BUFFER_CODE = StsGetParam(funcindex, "AFTER_BURN_ADC_VIN_BUFFER_CODE");
    CParam *AFTER_BURN_OSC_CODE = StsGetParam(funcindex, "AFTER_BURN_OSC_CODE");
    CParam *AFTER_BURN_COMP_OFF_AC1_CODE = StsGetParam(funcindex, "AFTER_BURN_COMP_OFF_AC1_CODE");
    CParam *AFTER_BURN_COMP_OFF_AC2_CODE = StsGetParam(funcindex, "AFTER_BURN_COMP_OFF_AC2_CODE");
    CParam *AFTER_BURN_ISNS_GAIN_CODE = StsGetParam(funcindex, "AFTER_BURN_ISNS_GAIN_CODE");
    CParam *AFTER_BURN_ISNS_OFFSET_CODE = StsGetParam(funcindex, "AFTER_BURN_ISNS_OFFSET_CODE");
    CParam *AFTER_BURN_TRIM_ACLOW_EN_82 = StsGetParam(funcindex, "AFTER_BURN_TRIM_ACLOW_EN_82");
    CParam *AFTER_BURN_TRIM_ACLOW_EN_85 = StsGetParam(funcindex, "AFTER_BURN_TRIM_ACLOW_EN_85");
    CParam *AFTER_BURN_TRIM_ACLOW_EN_87 = StsGetParam(funcindex, "AFTER_BURN_TRIM_ACLOW_EN_87");
    CParam *AFTER_BURN_TRIM_ACLOW_EN_82A = StsGetParam(funcindex, "AFTER_BURN_TRIM_ACLOW_EN_82A");
    CParam *AFTER_BURN_TTP_FSK_DIS_82 = StsGetParam(funcindex, "AFTER_BURN_TTP_FSK_DIS_82");
    CParam *AFTER_BURN_TTP_FSK_DIS_85 = StsGetParam(funcindex, "AFTER_BURN_TTP_FSK_DIS_85");
    CParam *AFTER_BURN_TTP_FSK_DIS_87 = StsGetParam(funcindex, "AFTER_BURN_TTP_FSK_DIS_87");
    CParam *AFTER_BURN_TTP_FSK_DIS_82A = StsGetParam(funcindex, "AFTER_BURN_TTP_FSK_DIS_82A");
    CParam *AFTER_BURN_AC_CHECK_500K_82 = StsGetParam(funcindex, "AFTER_BURN_AC_CHECK_500K_82");
    CParam *AFTER_BURN_AC_CHECK_500K_85 = StsGetParam(funcindex, "AFTER_BURN_AC_CHECK_500K_85");
    CParam *AFTER_BURN_AC_CHECK_500K_87 = StsGetParam(funcindex, "AFTER_BURN_AC_CHECK_500K_87");
    CParam *AFTER_BURN_AC_CHECK_500K_82A = StsGetParam(funcindex, "AFTER_BURN_AC_CHECK_500K_82A");
    CParam *AFTER_BURN_TRIM_DEIVICE_ID_82 = StsGetParam(funcindex, "AFTER_BURN_TRIM_DEIVICE_ID_82");
    CParam *AFTER_BURN_TRIM_DEIVICE_ID_85 = StsGetParam(funcindex, "AFTER_BURN_TRIM_DEIVICE_ID_85");
    CParam *AFTER_BURN_TRIM_DEIVICE_ID_87 = StsGetParam(funcindex, "AFTER_BURN_TRIM_DEIVICE_ID_87");
    CParam *AFTER_BURN_TRIM_DEIVICE_ID_82A = StsGetParam(funcindex, "AFTER_BURN_TRIM_DEIVICE_ID_82A");
    CParam *AFTER_BURN_TRIM_QI_ID_82 = StsGetParam(funcindex, "AFTER_BURN_TRIM_QI_ID_82");
    CParam *AFTER_BURN_TRIM_QI_ID_85 = StsGetParam(funcindex, "AFTER_BURN_TRIM_QI_ID_85");
    CParam *AFTER_BURN_TRIM_QI_ID_87 = StsGetParam(funcindex, "AFTER_BURN_TRIM_QI_ID_87");
    CParam *AFTER_BURN_TRIM_QI_ID_82A = StsGetParam(funcindex, "AFTER_BURN_TRIM_QI_ID_82A");
    CParam *DEVICE_FLAG = StsGetParam(funcindex, "DEVICE_FLAG");
    CParam *AFTER_BURN_0XF7_BIT2_TRIM_LOCK = StsGetParam(funcindex, "AFTER_BURN_0XF7_BIT2_TRIM_LOCK");
    CParam *AFTER_BURN_0XF7_BIT3_OPT2_LOCK = StsGetParam(funcindex, "AFTER_BURN_0XF7_BIT3_OPT2_LOCK");
    CParam *AFTER_BURN_0XF7_BIT4_OPT1_LOCK = StsGetParam(funcindex, "AFTER_BURN_0XF7_BIT4_OPT1_LOCK");
    CParam *AFTER_BURN_0XF7_BIT5_OPT1_BAK_LOCK = StsGetParam(funcindex, "AFTER_BURN_0XF7_BIT5_OPT1_BAK_LOCK");
    CParam *AFTER_BURN_LDO_ON_OPT_CODE = StsGetParam(funcindex, "AFTER_BURN_LDO_ON_OPT_CODE");
    CParam *AFTER_BURN_SCP_OFF_LDO_DIS_CODE = StsGetParam(funcindex, "AFTER_BURN_SCP_OFF_LDO_DIS_CODE");
    CParam *AFTER_BURN_OCP_OFF_LDO_DIS_CODE = StsGetParam(funcindex, "AFTER_BURN_OCP_OFF_LDO_DIS_CODE");
    CParam *AFTER_BURN_OTP_OFF_LDO_DIS_CODE = StsGetParam(funcindex, "AFTER_BURN_OTP_OFF_LDO_DIS_CODE");
    CParam *AFTER_BURN_OVP2_OFF_SR_DIS_CODE = StsGetParam(funcindex, "AFTER_BURN_OVP2_OFF_SR_DIS_CODE");
    CParam *AFTER_BURN_MTP_VOUT_SET_CODE = StsGetParam(funcindex, "AFTER_BURN_MTP_VOUT_SET_CODE");
    CParam *AFTER_BURN_TRIM_VRECT_DMY_DIS_CODE = StsGetParam(funcindex, "AFTER_BURN_TRIM_VRECT_DMY_DIS_CODE");
    CParam *AFTER_BURN_ILOAD_OPT_CODE = StsGetParam(funcindex, "AFTER_BURN_ILOAD_OPT_CODE");
    CParam *AFTER_BURN_MTP_DUMMY_0_CODE = StsGetParam(funcindex, "AFTER_BURN_MTP_DUMMY_0_CODE");
    CParam *AFTER_BURN_TRIM_DIS_CLPH_ADAP_CODE = StsGetParam(funcindex, "AFTER_BURN_TRIM_DIS_CLPH_ADAP_CODE");
    CParam *before_burn_Read_0033 = StsGetParam(funcindex, "before_burn_Read_0033");
    CParam *after_burn_Read_0033 = StsGetParam(funcindex, "after_burn_Read_0033");
    CParam *after_burn_Read_0080 = StsGetParam(funcindex, "after_burn_Read_0080");
    CParam *after_burn_Read_0081 = StsGetParam(funcindex, "after_burn_Read_0081");
    CParam *after_burn_Read_0082 = StsGetParam(funcindex, "after_burn_Read_0082");
    CParam *after_burn_Read_0083 = StsGetParam(funcindex, "after_burn_Read_0083");
    CParam *after_burn_Read_0084 = StsGetParam(funcindex, "after_burn_Read_0084");
    CParam *after_burn_Read_0085 = StsGetParam(funcindex, "after_burn_Read_0085");
    CParam *after_burn_Read_0086 = StsGetParam(funcindex, "after_burn_Read_0086");
    CParam *after_burn_Read_0087 = StsGetParam(funcindex, "after_burn_Read_0087");
    CParam *after_burn_Read_0088 = StsGetParam(funcindex, "after_burn_Read_0088");
    CParam *after_burn_Read_0089 = StsGetParam(funcindex, "after_burn_Read_0089");
    CParam *after_burn_Read_008A = StsGetParam(funcindex, "after_burn_Read_008A");
//}}AFX_STS_PARAM_PROTOTYPES
	// TODO: Add your function code here
	int device_id_true[SITE_NUM] = { 0 };
	int Burn_Error[SITE_NUM] = { 0 };
	unsigned char burn_0x72[SITE_NUM] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	unsigned char burn_0x74[SITE_NUM] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
	//initialize before_burn_0XF7_BIT2_CODE=1
	for (site = 0; site < SITE_NUM; site++)
	{
		before_burn_0XF7_BIT2_CODE[site] = 1;
	}

	dioplus.I2CConnect();
	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, -1);//未使用buffer
	wait_relay();
	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	//DIO_PLUS::I2CSite *pI2CSites[] = { &i2c_site1, &i2c_site2, &i2c_site3, &i2c_site4, &i2c_site5, &i2c_site6, &i2c_site7, &i2c_site8 };

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0XF7, 1);
	SERIAL BEFORE_BURN_0XF7[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0xF7 value

	SERIAL
	{
		before_burn_0XF7_BIT2_CODE[SITE] = (unsigned char(BEFORE_BURN_0XF7[SITE]) & 0X04) >> 2; //0XF7 bit2 
		before_burn_0XF7_BIT3_CODE[SITE] = (unsigned char(BEFORE_BURN_0XF7[SITE]) & 0X08) >> 3; //0XF7 bit3 
		before_burn_0XF7_BIT4_CODE[SITE] = (unsigned char(BEFORE_BURN_0XF7[SITE]) & 0X10) >> 4; //0XF7 bit4 	
		before_burn_0XF7_BIT5_CODE[SITE] = (unsigned char(BEFORE_BURN_0XF7[SITE]) & 0X20) >> 5; //0XF7 bit5 

		if (Global_FTQC_FLAG == 0)
		{
			if (before_burn_0XF7_BIT2_CODE[SITE] == 0)//trim lock=0, no trim before
			{
				burn_flag_all[SITE] = true;
				burn_0x72[SITE] = 0x03;
				burn_0x74[SITE] = 0x3c;

			}
			else
			{
				burn_flag_all[SITE] = false;
				burn_0x72[SITE] = 0x00;
				burn_0x74[SITE] = 0x00;
			}

		}
		else
		{
			burn_flag_all[SITE] = false;
		}
	}

		// get trim best code
	FOR_EACH_VALID_SITE(site)
	{
		before_burn_VBG_CODE[site] = dut.trim("TRIM_BG").get_working(site);//EEPROM1 bit2~7
		before_burn_ZTC_CODE[site] = dut.trim("TRIM_ZTC").get_working(site);//EEPROM4 bit3~7
		before_burn_ADC_VREF_BUFFER_CODE[site] = dut.trim("TRIM_ADC_VREF_BUFFER").get_working(site);//EEPROM2 bit2~7
		before_burn_ADC_VIN_BUFFER_CODE[site] = dut.trim("TRIM_ADC_VIN_BUFFER").get_working(site);//EEPROM7 bit2~7
		before_burn_OSC_CODE[site] = dut.trim("TRIM_OSC").get_working(site);//EEPROM3 bit1~7
		before_burn_COMP_OFF_AC1_CODE[site] = dut.trim("TRIM_LS1_COMP").get_working(site);//EEPROM0 bit4~7
		before_burn_COMP_OFF_AC2_CODE[site] = dut.trim("TRIM_LS2_COMP").get_working(site);//EEPROM0 bit0~3
		before_burn_ISNS_GAIN_CODE[site] = dut.trim("TRIM_ISNS_GAIN").get_working(site);//EEPROM5 bit1~7
		before_burn_ISNS_OFFSET_CODE[site] = dut.trim("TRIM_ISNS_OFFSET").get_working(site);//EEPROM6 bit2~7
		before_burn_TRIM_ACLOW_EN[site] = dut.sel("TRIM_ACLOW_EN").get_working(site);//EEPROM2 bit1
		before_burn_TTP_FSK_DIS[site] = dut.sel("TTP_FSK_DIS").get_working(site);//EEPROM9 bit6
		before_burn_AC_CHECK_500K[site] = dut.sel("AC_CHECK_500K").get_working(site);//EEPROM9 bit5
		before_burn_TRIM_DEIVICE_ID[site] = dut.sel("TRIM_DEIVICE_ID").get_working(site);//EEPROMA bit2~4


		before_burn_0x80[site] = dut.assy("EEPROM0").get_working(site);   //reg0x80
		before_burn_0x81[site] = dut.assy("EEPROM1").get_working(site);   //reg0x81
		before_burn_0x82[site] = dut.assy("EEPROM2").get_working(site);   //reg0x82
		before_burn_0x83[site] = dut.assy("EEPROM3").get_working(site);   //reg0x83
		before_burn_0x84[site] = dut.assy("EEPROM4").get_working(site);   //reg0x84
		before_burn_0x85[site] = dut.assy("EEPROM5").get_working(site);   //reg0x85
		before_burn_0x86[site] = dut.assy("EEPROM6").get_working(site);   //reg0x86
		before_burn_0x87[site] = dut.assy("EEPROM7").get_working(site);   //reg0x87
		before_burn_0x88[site] = dut.assy("EEPROM8").get_working(site);   //reg0x88
		before_burn_0x89[site] = dut.assy("EEPROM9").get_working(site);   //reg0x89
		before_burn_0x8A[site] = dut.assy("EEPROM10").get_working(site);  //reg0x8A

		//add for efuse burn
		before_burn_check[site] = before_burn_VBG_CODE[site] + before_burn_ZTC_CODE[site] + before_burn_ADC_VREF_BUFFER_CODE[site] + before_burn_ADC_VIN_BUFFER_CODE[site] + before_burn_OSC_CODE[site] +
			before_burn_COMP_OFF_AC1_CODE[site] + before_burn_COMP_OFF_AC2_CODE[site] + before_burn_ISNS_GAIN_CODE[site] + before_burn_ISNS_OFFSET_CODE[site];

		//if (before_burn_check[site] == 0)
		//{
		//	burn_flag_all[site] = false;
		//}

	}

	// write trim best code
	I2CWritedata(0x80, before_burn_0x80);
	I2CWritedata(0x81, before_burn_0x81);
	I2CWritedata(0x82, before_burn_0x82);
	I2CWritedata(0x83, before_burn_0x83);
	I2CWritedata(0x84, before_burn_0x84);
	I2CWritedata(0x85, before_burn_0x85);
	I2CWritedata(0x86, before_burn_0x86);
	I2CWritedata(0x87, before_burn_0x87);
	I2CWritedata(0x88, before_burn_0x88);
	I2CWritedata(0x89, before_burn_0x89);
	I2CWritedata(0x8A, before_burn_0x8A);

	///////////////////////////////Write HTOL code, 2025.11.16 add////////////////////////////
	//HAST code is the same as HTOL code
	if (HTOL_HAST_FLAG == 1)
	{
		manager.setfields({ { TRIM_BG, unsigned char(before_burn_VBG_CODE[site]) } });//HTOL_HAST: rewrite VBG code,避免setfields覆盖VBG code
		manager.setfields({ /*{ LDO_ON_OPT, 1 }, { SCP_OFF_LDO_DIS, 1 }, { OCP_OFF_LDO_DIS, 1 }, { OTP_OFF_LDO_DIS, 1 }, { OVP2_OFF_SR_DIS, 1 },
							{ MTP_VOUT_SET, 0xFF },*/{ TRIM_VRECT_DMY_DIS, 1 },/* { ILOAD_OPT, 0x03 }, { MTP_DUMMY_0, 0x00 },*/{ TRIM_DIS_CLPH_ADAP, 1 } });
	}
	///////////////////////////////Write HTOL code, 2025.11.16 add////////////////////////////

	delay_ms(1);


	I2CWritedata(0x72, burn_0x72);
	I2CWritedata(0x74, burn_0x74);
	//I2CWriteAllSites(0x72, 0x03);//40us(default)
	//I2CWriteAllSites(0x74, 0x3c);//烧录
	delay_ms(2);

	//结束判断，循环读该寄存器，直到0X75 bit1为1
	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X75, 1);

	int read_counter = 0;
	//while (read_counter < 10)
	//{

	//	READ_0X75[site] = pI2CSites[site]->GetDataByteValue(0);  //get 0x75 value

	//	read_0X75_BIT1_CODE[site] = (unsigned char(READ_0X75[site]) & 0X02) >> 1; //0X75 bit1 
	//	read_0X75_BIT3_CODE[site] = (unsigned char(READ_0X75[site]) & 0X08) >> 3; //0X75 bit3 
	//	read_0X75_BIT4_CODE[site] = (unsigned char(READ_0X75[site]) & 0X10) >> 4; //0X75 bit4 	

	//	if (read_0X75_BIT3_CODE[site] == 1 || read_0X75_BIT4_CODE[site] == 1)
	//	{
	//		Burn_Error[site] = 1;//burn fail
	//		read_counter = 5;//退出循环
	//	}

	//	if (read_0X75_BIT1_CODE[site] == 1)
	//	{
	//		break;
	//	}
	//	else
	//	{
	//		read_counter++;
	//	}

	//	delay_ms(1);
	//}
	//I2CWriteAllSites(0x74, 0x87);//clear prog cmd
	//delay_ms(1);

	FOR_EACH_VALID_SITE(site)
	{
		if (HTOL_HAST_FLAG == 1)
		{
			/////////////////////////////////只能单site，用于可靠性T0编号，2025.11.17/////////////////////////////////
			//const char* part_num = STSGetPartIDText(site);
			//unsigned char ababab[9]{};
			//unsigned char before_burn_0x33[SITE_NUM]{};
			//int abcc = 0;
			//int abcd = 0;
			//for (abcc = 0; part_num[abcc] > 47; abcc++)
			//{
			//	ababab[abcc] = part_num[abcc]-48;
			//}
			//abcc--;
			//before_burn_0x33[site] += ababab[abcc];
			//for (; abcc>0; abcc--)
			//{
			//	before_burn_0x33[site] = before_burn_0x33[site] + ababab[abcd++] * pow(10, abcc);
			//}
			//before_burn_0x33[site] = before_burn_0x33[site] * 2;
			//I2CWritedata(0x33, before_burn_0x33);
			////I2CWriteAllSites(0x33, before_burn_0x33);

			//dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X33, 1);
			//SERIAL before_burn_READ_0X33[SITE] = pI2CSites[SITE]->GetDataByteValue(0);
			//before_burn_Read_0033->SetTestResult(site, 0, unsigned char(before_burn_READ_0X33[site]) >> 1);

			///////////////////////////////Write HTOL/HAST code, 2025.11.16 add////////////////////////////
			//HAST code is the same as HTOL code
			//////////opt2 burn////////
			manager.setfields({ { LDO_ON_OPT, 1 }, { SCP_OFF_LDO_DIS, 1 }, { OCP_OFF_LDO_DIS, 1 }, { OTP_OFF_LDO_DIS, 1 }, { OVP2_OFF_SR_DIS, 1 },
			{ MTP_VOUT_SET, 0xFF }/*, { TRIM_VRECT_DMY_DIS, 1 }*/, { ILOAD_OPT, 0x03 }, /*{ MTP_DUMMY_0, 0x00 }, { TRIM_DIS_CLPH_ADAP, 1 }*/ });
			delay_ms(1);
			I2CWriteAllSites(0x72, 0x03);//40us(default)
			I2CWriteAllSites(0x74, 0x3e);//烧录

			//结束判断，循环读该寄存器，直到0X75 bit1为1
			dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X75, 1);

			while (read_counter < 10)
			{

				READ_0X75[site] = pI2CSites[site]->GetDataByteValue(0);  //get 0x75 value

				read_0X75_BIT1_CODE[site] = (unsigned char(READ_0X75[site]) & 0X02) >> 1; //0X75 bit1 
				read_0X75_BIT3_CODE[site] = (unsigned char(READ_0X75[site]) & 0X08) >> 3; //0X75 bit3 
				read_0X75_BIT4_CODE[site] = (unsigned char(READ_0X75[site]) & 0X10) >> 4; //0X75 bit4 	

				if (read_0X75_BIT3_CODE[site] == 1 || read_0X75_BIT4_CODE[site] == 1)
				{
					Burn_Error[site] = 1;//burn fail
					read_counter = 5;//退出循环
				}

				if (read_0X75_BIT1_CODE[site] == 1)
				{
					break;
				}
				else
				{
					read_counter++;
				}

				delay_ms(1);
			}
			I2CWriteAllSites(0x74, 0x87);//clear prog cmd

			//////////opt1 burn////////
			manager.setfields({ /*{ LDO_ON_OPT, 1 }, { SCP_OFF_LDO_DIS, 1 }, { OCP_OFF_LDO_DIS, 1 }, { OTP_OFF_LDO_DIS, 1 }, { OVP2_OFF_SR_DIS, 1 },
								{ MTP_VOUT_SET, 0xFF }, { TRIM_VRECT_DMY_DIS, 1 }, { ILOAD_OPT, 0x03 },*/{ MTP_DUMMY_0, 0x00 }/*, { TRIM_DIS_CLPH_ADAP, 1 }*/ });
			delay_ms(1);

			I2CWriteAllSites(0x72, 0x03);//40us(default)
			I2CWriteAllSites(0x74, 0x3d);//烧录

			//结束判断，循环读该寄存器，直到0X75 bit1为1
			dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X75, 1);

			while (read_counter < 10)
			{

				READ_0X75[site] = pI2CSites[site]->GetDataByteValue(0);  //get 0x75 value

				read_0X75_BIT1_CODE[site] = (unsigned char(READ_0X75[site]) & 0X02) >> 1; //0X75 bit1 
				read_0X75_BIT3_CODE[site] = (unsigned char(READ_0X75[site]) & 0X08) >> 3; //0X75 bit3 
				read_0X75_BIT4_CODE[site] = (unsigned char(READ_0X75[site]) & 0X10) >> 4; //0X75 bit4 	

				if (read_0X75_BIT3_CODE[site] == 1 || read_0X75_BIT4_CODE[site] == 1)
				{
					Burn_Error[site] = 1;//burn fail
					read_counter = 5;//退出循环
				}

				if (read_0X75_BIT1_CODE[site] == 1)
				{
					break;
				}
				else
				{
					read_counter++;
				}

				delay_ms(1);
			}
			I2CWriteAllSites(0x74, 0x87);//clear prog cmd
		}
	}
	///////////////////////////////Write HTOL/HAST code, 2025.11.16 add////////////////////////////

	I2CWriteAllSites(0x74, 0x87);//clear prog cmd
	delay_ms(1);
	I2CWriteAllSites(0xF7, 0x00);


	manager.historyClear();//clear history value
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 1);

	//burn read back
	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0XF7, 1);
	SERIAL AFTER_BURN_0XF7[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0xF7 value

	SERIAL
	{
		after_burn_0XF7_BIT2_CODE[SITE] = (unsigned char(AFTER_BURN_0XF7[SITE]) & 0X04) >> 2; //0XF7 bit2 
		after_burn_0XF7_BIT3_CODE[SITE] = (unsigned char(AFTER_BURN_0XF7[SITE]) & 0X08) >> 3; //0XF7 bit3 
		after_burn_0XF7_BIT4_CODE[SITE] = (unsigned char(AFTER_BURN_0XF7[SITE]) & 0X10) >> 4; //0XF7 bit4 	
		after_burn_0XF7_BIT5_CODE[SITE] = (unsigned char(AFTER_BURN_0XF7[SITE]) & 0X20) >> 5; //0XF7 bit5 

		AFTER_BURN_0XF7_BIT2_TRIM_LOCK->SetTestResult(SITE, 0, after_burn_0XF7_BIT2_CODE[SITE]);
		AFTER_BURN_0XF7_BIT3_OPT2_LOCK->SetTestResult(SITE, 0, after_burn_0XF7_BIT3_CODE[SITE]);
		AFTER_BURN_0XF7_BIT4_OPT1_LOCK->SetTestResult(SITE, 0, after_burn_0XF7_BIT4_CODE[SITE]);
		AFTER_BURN_0XF7_BIT5_OPT1_BAK_LOCK->SetTestResult(SITE, 0, after_burn_0XF7_BIT5_CODE[SITE]);

	}

	//read back burn code
	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X80, 11);//read trim reg code
	for (int reg = 0; reg < 11; reg++)
	{
		BURN_READ[reg][0] = i2c_site1.GetDataByteValue(reg);  // i2c site1 get the reg byte value
		BURN_READ[reg][1] = i2c_site2.GetDataByteValue(reg);  // i2c site2 get the reg byte value
		BURN_READ[reg][2] = i2c_site3.GetDataByteValue(reg);  // i2c site3 get the reg byte value
		BURN_READ[reg][3] = i2c_site4.GetDataByteValue(reg);  // i2c site4 get the reg byte value
		BURN_READ[reg][4] = i2c_site5.GetDataByteValue(reg);  // i2c site5 get the reg byte value
		BURN_READ[reg][5] = i2c_site6.GetDataByteValue(reg);  // i2c site6 get the reg byte value
		BURN_READ[reg][6] = i2c_site7.GetDataByteValue(reg);  // i2c site7 get the reg byte value
		BURN_READ[reg][7] = i2c_site8.GetDataByteValue(reg);  // i2c site8 get the reg byte value
	}

	for (int reg = 0; reg < BANK_NUM; ++reg)
	{
		string TB_str;
		TB_str = "EEPROM" + spec.int2str(reg);

		// set trim flag, and disable trim node allow if trimmed
		SERIAL
		{
			dut.assy(TB_str.c_str()).set_read_back((BURN_READ[reg][SITE]), SITE);
			dut.assy(TB_str.c_str()).copy_work_to_prog();
		}

	}

	/////////////////////////////////用于可靠性T0编号，2025.11.17/////////////////////////////////
	//if (PartID_Num == 0)
	//{
	//	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X33, 1);
	//	SERIAL after_burn_READ_0X33[SITE] = pI2CSites[SITE]->GetDataByteValue(0);
	//}

	///////////////////////////////Read HTOL/HAST code, 2025.11.16 add////////////////////////////
	//HAST code is the same as HTOL code
	if (HTOL_HAST_FLAG == 1)
	{
		dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X32, 1);
		SERIAL after_burn_READ_0X32[SITE] = pI2CSites[SITE]->GetDataByteValue(0);

		dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X38, 3);
		SERIAL
		{
			after_burn_READ_0X38[SITE] = pI2CSites[SITE]->GetDataByteValue(0);
			after_burn_READ_0X39[SITE] = pI2CSites[SITE]->GetDataByteValue(1);
			after_burn_READ_0X3B[SITE] = pI2CSites[SITE]->GetDataByteValue(3);
		}

		dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X81, 1);
		SERIAL after_burn_READ_0X81[SITE] = pI2CSites[SITE]->GetDataByteValue(0);


		dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X88, 1);
		SERIAL after_burn_READ_0X88[SITE] = pI2CSites[SITE]->GetDataByteValue(0);


		SERIAL
		{
			after_burn_LDO_ON_OPT_CODE[SITE] = (unsigned char(after_burn_READ_0X39[SITE]) & 0X60) >> 5; //0X39 bit5~6 
			after_burn_SCP_OFF_LDO_DIS_CODE[SITE] = (unsigned char(after_burn_READ_0X3B[SITE]) & 0X20) >> 5; //0X3B bit5 
			after_burn_OCP_OFF_LDO_DIS_CODE[SITE] = (unsigned char(after_burn_READ_0X3B[SITE]) & 0X10) >> 4; //0X3B bit4 
			after_burn_OTP_OFF_LDO_DIS_CODE[SITE] = (unsigned char(after_burn_READ_0X3B[SITE]) & 0X08) >> 3; //0X3B bit3 
			after_burn_OVP2_OFF_SR_DIS_CODE[SITE] = (unsigned char(after_burn_READ_0X3B[SITE]) & 0X04) >> 2; //0X3B bit2 
			after_burn_MTP_VOUT_SET_CODE[SITE] = unsigned char(after_burn_READ_0X38[SITE]); //0X38 bit0~7 
			after_burn_TRIM_VRECT_DMY_DIS_CODE[SITE] = (unsigned char(after_burn_READ_0X88[SITE]) & 0X04) >> 2; //0X88 bit2
			after_burn_ILOAD_OPT_CODE[SITE] = unsigned char(after_burn_READ_0X39[SITE]) & 0X03; //0X39 bit0~1 
			after_burn_MTP_DUMMY_0_CODE[SITE] = unsigned char(after_burn_READ_0X32[SITE]) & 0X0F; //0X32 bit0~3
			after_burn_TRIM_DIS_CLPH_ADAP_CODE[SITE] = unsigned char(after_burn_READ_0X81[SITE]) & 0X01; //0X81 bit0
		}
	}
	///////////////////////////////Read HTOL/HAST code, 2025.11.16 add////////////////////////////


	FOR_EACH_VALID_SITE(site)
	{
		after_burn_VBG_CODE[site] = dut.trim("TRIM_BG").get_read_back(site);//EEPROM1 bit2~7
		after_burn_ZTC_CODE[site] = dut.trim("TRIM_ZTC").get_read_back(site);//EEPROM4 bit3~7
		after_burn_ADC_VREF_BUFFER_CODE[site] = dut.trim("TRIM_ADC_VREF_BUFFER").get_read_back(site);//EEPROM2 bit2~7
		after_burn_ADC_VIN_BUFFER_CODE[site] = dut.trim("TRIM_ADC_VIN_BUFFER").get_read_back(site);//EEPROM7 bit2~7
		after_burn_OSC_CODE[site] = dut.trim("TRIM_OSC").get_read_back(site);//EEPROM3 bit1~7
		after_burn_COMP_OFF_AC1_CODE[site] = dut.trim("TRIM_LS1_COMP").get_read_back(site);//EEPROM0 bit4~7
		after_burn_COMP_OFF_AC2_CODE[site] = dut.trim("TRIM_LS2_COMP").get_read_back(site);//EEPROM0 bit0~3
		after_burn_ISNS_GAIN_CODE[site] = dut.trim("TRIM_ISNS_GAIN").get_read_back(site);//EEPROM5 bit1~7
		after_burn_ISNS_OFFSET_CODE[site] = dut.trim("TRIM_ISNS_OFFSET").get_read_back(site);//EEPROM6 bit2~7
		after_burn_TRIM_ACLOW_EN[site] = dut.sel("TRIM_ACLOW_EN").get_read_back(site);//EEPROM2 bit1
		after_burn_TTP_FSK_DIS[site] = dut.sel("TTP_FSK_DIS").get_read_back(site);//EEPROM9 bit6
		after_burn_AC_CHECK_500K[site] = dut.sel("AC_CHECK_500K").get_read_back(site);//EEPROM9 bit5
		after_burn_TRIM_DEIVICE_ID[site] = dut.sel("TRIM_DEIVICE_ID").get_read_back(site);//EEPROMA bit2~4
		after_burn_TRIM_QI_ID[site] = dut.sel("TRIM_QI_ID").get_read_back(site);//EEPROMA bit0~1
	}

	SERIAL
	{
		if (burn_flag_all[SITE] == true)
		{
			Burn_Same_As_EEPROM0_READ[SITE] = dut.assy("EEPROM0").comp_prog_to_read(SITE);
			Burn_Same_As_EEPROM1_READ[SITE] = dut.assy("EEPROM1").comp_prog_to_read(SITE);
			Burn_Same_As_EEPROM2_READ[SITE] = dut.assy("EEPROM2").comp_prog_to_read(SITE);
			Burn_Same_As_EEPROM3_READ[SITE] = dut.assy("EEPROM3").comp_prog_to_read(SITE);
			Burn_Same_As_EEPROM4_READ[SITE] = dut.assy("EEPROM4").comp_prog_to_read(SITE);
			Burn_Same_As_EEPROM5_READ[SITE] = dut.assy("EEPROM5").comp_prog_to_read(SITE);
			Burn_Same_As_EEPROM6_READ[SITE] = dut.assy("EEPROM6").comp_prog_to_read(SITE);
			Burn_Same_As_EEPROM7_READ[SITE] = dut.assy("EEPROM7").comp_prog_to_read(SITE);
			Burn_Same_As_EEPROM8_READ[SITE] = dut.assy("EEPROM8").comp_prog_to_read(SITE);
			Burn_Same_As_EEPROM9_READ[SITE] = dut.assy("EEPROM9").comp_prog_to_read(SITE);
			//Burn_Same_As_EEPROMA_READ[SITE] = dut.assy("EEPROM10").comp_prog_to_read(SITE);

			if (HTOL_HAST_FLAG == 0)
			{
				Burn_Same_As_EEPROM8_READ[SITE] = dut.assy("EEPROM8").comp_prog_to_read(SITE);//htol/hast burn 0x88 bit2

				if (Burn_Same_As_EEPROM0_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM1_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM2_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM3_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM4_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM5_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM6_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM7_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM8_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM9_READ[SITE] == 1 /*&&
					Burn_Same_As_EEPROMA_READ[SITE] == 1*/)
				{
					Burn_Same_As_Read_Flag[SITE] = 1;
				}
				else
				{

					Burn_Same_As_Read_Flag[SITE] = 0;

				}
			}
			else
			{

				if (Burn_Same_As_EEPROM0_READ[SITE] == 1 &&
					//Burn_Same_As_EEPROM1_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM2_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM3_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM4_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM5_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM6_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM7_READ[SITE] == 1 &&
					//Burn_Same_As_EEPROM8_READ[SITE] == 1 &&
					Burn_Same_As_EEPROM9_READ[SITE] == 1 &&
					//Burn_Same_As_EEPROMA_READ[SITE] == 1 &&
					after_burn_VBG_CODE[SITE] == before_burn_VBG_CODE[SITE] &&

					after_burn_LDO_ON_OPT_CODE[SITE] == 1 &&
					after_burn_SCP_OFF_LDO_DIS_CODE[SITE] == 1 &&
					after_burn_OCP_OFF_LDO_DIS_CODE[SITE] == 1 &&
					after_burn_OTP_OFF_LDO_DIS_CODE[SITE] == 1 &&
					after_burn_OVP2_OFF_SR_DIS_CODE[SITE] == 1 &&
					after_burn_MTP_VOUT_SET_CODE[SITE] == 255 &&
					after_burn_TRIM_VRECT_DMY_DIS_CODE[SITE] == 1 &&
					after_burn_ILOAD_OPT_CODE[SITE] == 3 &&
					after_burn_MTP_DUMMY_0_CODE[SITE] == 0 &&
					after_burn_TRIM_DIS_CLPH_ADAP_CODE[SITE] == 1)
				{
					Burn_Same_As_Read_Flag[SITE] = 1;
				}
				else
				{

					Burn_Same_As_Read_Flag[SITE] = 0;

				}
			}

		}
		else
		{

			Burn_Same_As_Read_Flag[SITE] = 1;
		}

		if (Burn_Error[SITE] == 1)
		{
			Burn_Pass_flag->SetTestResult(SITE, 0, 0);
		}
		else
		{
			Burn_Pass_flag->SetTestResult(SITE, 0, Burn_Same_As_Read_Flag[SITE]);

		}
	}

	FOR_EACH_VALID_SITE(site)
	{
		//select PN is different option code
		if (spec("PT_PROG") == 1682)
		{
			device_id_true[site] = 1;
			AFTER_BURN_TRIM_ACLOW_EN_82->SetTestResult(site, 0, after_burn_TRIM_ACLOW_EN[site]);
			AFTER_BURN_TTP_FSK_DIS_82->SetTestResult(site, 0, after_burn_TTP_FSK_DIS[site]);
			AFTER_BURN_AC_CHECK_500K_82->SetTestResult(site, 0, after_burn_AC_CHECK_500K[site]);
			AFTER_BURN_TRIM_DEIVICE_ID_82->SetTestResult(site, 0, after_burn_TRIM_DEIVICE_ID[site]);
			AFTER_BURN_TRIM_QI_ID_82->SetTestResult(site, 0, after_burn_TRIM_QI_ID[site]);
		}
		else if (spec("PT_PROG") == 1685)
		{
			device_id_true[site] = 1;
			AFTER_BURN_TRIM_ACLOW_EN_85->SetTestResult(site, 0, after_burn_TRIM_ACLOW_EN[site]);
			AFTER_BURN_TTP_FSK_DIS_85->SetTestResult(site, 0, after_burn_TTP_FSK_DIS[site]);
			AFTER_BURN_AC_CHECK_500K_85->SetTestResult(site, 0, after_burn_AC_CHECK_500K[site]);
			AFTER_BURN_TRIM_DEIVICE_ID_85->SetTestResult(site, 0, after_burn_TRIM_DEIVICE_ID[site]);
			AFTER_BURN_TRIM_QI_ID_85->SetTestResult(site, 0, after_burn_TRIM_QI_ID[site]);
		}
		else if (spec("PT_PROG") == 1687)
		{
			device_id_true[site] = 1;
			AFTER_BURN_TRIM_ACLOW_EN_87->SetTestResult(site, 0, after_burn_TRIM_ACLOW_EN[site]);
			AFTER_BURN_TTP_FSK_DIS_87->SetTestResult(site, 0, after_burn_TTP_FSK_DIS[site]);
			AFTER_BURN_AC_CHECK_500K_87->SetTestResult(site, 0, after_burn_AC_CHECK_500K[site]);
			AFTER_BURN_TRIM_DEIVICE_ID_87->SetTestResult(site, 0, after_burn_TRIM_DEIVICE_ID[site]);
			AFTER_BURN_TRIM_QI_ID_87->SetTestResult(site, 0, after_burn_TRIM_QI_ID[site]);
		}
		else if (spec("PT_PROG") == 16821) //V01 add
		{
			device_id_true[site] = 1;
			AFTER_BURN_TRIM_ACLOW_EN_82A->SetTestResult(site, 0, after_burn_TRIM_ACLOW_EN[site]);
			AFTER_BURN_TTP_FSK_DIS_82A->SetTestResult(site, 0, after_burn_TTP_FSK_DIS[site]);
			AFTER_BURN_AC_CHECK_500K_82A->SetTestResult(site, 0, after_burn_AC_CHECK_500K[site]);
			AFTER_BURN_TRIM_DEIVICE_ID_82A->SetTestResult(site, 0, after_burn_TRIM_DEIVICE_ID[site]);
			AFTER_BURN_TRIM_QI_ID_82A->SetTestResult(site, 0, after_burn_TRIM_QI_ID[site]);
		}

		DEVICE_FLAG->SetTestResult(site, 0, device_id_true[site]);
		AFTER_BURN_VBG_CODE->SetTestResult(site, 0, after_burn_VBG_CODE[site]);
		AFTER_BURN_ZTC_CODE->SetTestResult(site, 0, after_burn_ZTC_CODE[site]);
		AFTER_BURN_ADC_VREF_BUFFER_CODE->SetTestResult(site, 0, after_burn_ADC_VREF_BUFFER_CODE[site]);
		AFTER_BURN_ADC_VIN_BUFFER_CODE->SetTestResult(site, 0, after_burn_ADC_VIN_BUFFER_CODE[site]);
		AFTER_BURN_OSC_CODE->SetTestResult(site, 0, after_burn_OSC_CODE[site]);
		AFTER_BURN_COMP_OFF_AC1_CODE->SetTestResult(site, 0, after_burn_COMP_OFF_AC1_CODE[site]);
		AFTER_BURN_COMP_OFF_AC2_CODE->SetTestResult(site, 0, after_burn_COMP_OFF_AC2_CODE[site]);
		AFTER_BURN_ISNS_GAIN_CODE->SetTestResult(site, 0, after_burn_ISNS_GAIN_CODE[site]);
		AFTER_BURN_ISNS_OFFSET_CODE->SetTestResult(site, 0, after_burn_ISNS_OFFSET_CODE[site]);
		
		////select PN is different code
		//AFTER_BURN_TRIM_ACLOW_EN->SetTestResult(site, 0, after_burn_TRIM_ACLOW_EN[site]);
		//AFTER_BURN_TTP_FSK_DIS->SetTestResult(site, 0, after_burn_TTP_FSK_DIS[site]);
		//AFTER_BURN_AC_CHECK_500K->SetTestResult(site, 0, after_burn_AC_CHECK_500K[site]);
		//AFTER_BURN_TRIM_DEIVICE_ID->SetTestResult(site, 0, after_burn_TRIM_DEIVICE_ID[site]);
		/////////////////////////////HTOL code///////////////////////////////
		if (HTOL_HAST_FLAG == 1)
		{
			AFTER_BURN_LDO_ON_OPT_CODE->SetTestResult(site, 0, after_burn_LDO_ON_OPT_CODE[site]);
			AFTER_BURN_SCP_OFF_LDO_DIS_CODE->SetTestResult(site, 0, after_burn_SCP_OFF_LDO_DIS_CODE[site]);
			AFTER_BURN_OCP_OFF_LDO_DIS_CODE->SetTestResult(site, 0, after_burn_OCP_OFF_LDO_DIS_CODE[site]);
			AFTER_BURN_OTP_OFF_LDO_DIS_CODE->SetTestResult(site, 0, after_burn_OTP_OFF_LDO_DIS_CODE[site]);
			AFTER_BURN_OVP2_OFF_SR_DIS_CODE->SetTestResult(site, 0, after_burn_OVP2_OFF_SR_DIS_CODE[site]);
			AFTER_BURN_MTP_VOUT_SET_CODE->SetTestResult(site, 0, after_burn_MTP_VOUT_SET_CODE[site]);
			AFTER_BURN_TRIM_VRECT_DMY_DIS_CODE->SetTestResult(site, 0, after_burn_TRIM_VRECT_DMY_DIS_CODE[site]);
			AFTER_BURN_ILOAD_OPT_CODE->SetTestResult(site, 0, after_burn_ILOAD_OPT_CODE[site]);
			AFTER_BURN_MTP_DUMMY_0_CODE->SetTestResult(site, 0, after_burn_MTP_DUMMY_0_CODE[site]);
			AFTER_BURN_TRIM_DIS_CLPH_ADAP_CODE->SetTestResult(site, 0, after_burn_TRIM_DIS_CLPH_ADAP_CODE[site]);
		}
		after_burn_Read_0033->SetTestResult(site, 0, unsigned char(after_burn_READ_0X33[site]));
		after_burn_Read_0080->SetTestResult(site, 0, unsigned char(BURN_READ[0][site]));
		after_burn_Read_0081->SetTestResult(site, 0, unsigned char(BURN_READ[1][site]));
		after_burn_Read_0082->SetTestResult(site, 0, unsigned char(BURN_READ[2][site]));
		after_burn_Read_0083->SetTestResult(site, 0, unsigned char(BURN_READ[3][site]));
		after_burn_Read_0084->SetTestResult(site, 0, unsigned char(BURN_READ[4][site]));
		after_burn_Read_0085->SetTestResult(site, 0, unsigned char(BURN_READ[5][site]));
		after_burn_Read_0086->SetTestResult(site, 0, unsigned char(BURN_READ[6][site]));
		after_burn_Read_0087->SetTestResult(site, 0, unsigned char(BURN_READ[7][site]));
		after_burn_Read_0088->SetTestResult(site, 0, unsigned char(BURN_READ[8][site]));
		after_burn_Read_0089->SetTestResult(site, 0, unsigned char(BURN_READ[9][site]));
		after_burn_Read_008A->SetTestResult(site, 0, unsigned char(BURN_READ[10][site]));
	}

	TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	return 0;
}

DUT_API int T_Shutdown(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *IRPPO = StsGetParam(funcindex, "IRPPO");
    CParam *TSD_H = StsGetParam(funcindex, "TSD_H");
    CParam *TSD_L = StsGetParam(funcindex, "TSD_L");
//}}AFX_STS_PARAM_PROTOTYPES
	// TODO: Add your function code here
	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K7_SINK_PULLUP, -1);//未使用buffer
	dioplus.I2CConnect();
	wait_relay();
	TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { EN_ANA_MUX, 1 }, { MUX_ANA, 0x0A } });
	INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(1);

	INTB.Set(FV, 1, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(1);
	V5V.MeasureVI(50, 10);

	INTB.MeasureVI(50, 10);
	SERIAL
	{
		adresult0[SITE] = INTB.GetMeasResult(SITE, MIRET);
		adresult[SITE] = adresult0[SITE] * 1e6;
		IRPPO->SetTestResult(SITE, 0, adresult[SITE]);
	}
	INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	//TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);

	INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_OFF);

	////////////////////////Thermal Shutdown，SINK=high////////////////////////
	if (POWER_FLAG)
	{
		cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K7_SINK_PULLUP, -1);//未使用buffer
		wait_relay();
		TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { EN_DIG_MUX, 1 }, { MUX_DIG, 1 }, { I2C_EN_TSD, 1 } });
	SINK.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	SINK.MeasureVI(20, 10);
	SERIAL
	{
		adresult1[SITE] = SINK.GetMeasResult(SITE, MVRET);
		TSD_H->SetTestResult(SITE, 0, adresult1[SITE]);
	}
	////////////////////////Thermal Shutdown，SINK=low////////////////////////
	if (Global_Tempchar_Program_Flag == 1)
	{
		manager.setfields({ { TRIM_DIS_OTP, 0 } });
	}
	manager.setfields({ { TMOD_CTRL, 0x08 } });
	delay_ms(1);
	SINK.MeasureVI(20, 10);
	SERIAL
	{
		adresult2[SITE] = SINK.GetMeasResult(SITE, MVRET);
		TSD_L->SetTestResult(SITE, 0, adresult2[SITE]);
	}

	TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	SINK.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	//dioplus.I2CDisconnect();

	return 0;
}

DUT_API int V5V_TEST(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *VRECT_UVLO_UP_DS = StsGetParam(funcindex, "VRECT_UVLO_UP_DS");
    CParam *VRECT_UVLO_DOWN_DS = StsGetParam(funcindex, "VRECT_UVLO_DOWN_DS");
    CParam *VRECT_UVLO_HYS = StsGetParam(funcindex, "VRECT_UVLO_HYS");
    CParam *V5V_PRE_SCM = StsGetParam(funcindex, "V5V_PRE_SCM");
    CParam *V5V_LDO_DS = StsGetParam(funcindex, "V5V_LDO_DS");
    CParam *V5V_DROP_OUT_SCM = StsGetParam(funcindex, "V5V_DROP_OUT_SCM");
    CParam *V5V_LDO_LOAD_REG = StsGetParam(funcindex, "V5V_LDO_LOAD_REG");
    CParam *V5V_LDO_LINE_REG = StsGetParam(funcindex, "V5V_LDO_LINE_REG");
    CParam *IMAX_V5V_DS = StsGetParam(funcindex, "IMAX_V5V_DS");
    CParam *ISHORT_V5V_DS = StsGetParam(funcindex, "ISHORT_V5V_DS");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here
	
	double volt[NUM_SITES] = { 0.0 };
	double enb_I1[SITE_COUNT] = { 0.0 };

	if (POWER_FLAG)
	{
		cbit.SetOn(K2_VRECT_V5V_CAP, K4_IIC_PULLUP, K7_SINK_PULLUP, -1);
		dioplus.I2CConnect();
		wait_relay();
	}
	TM_ENTER_vi(VRECT, VRECT_Volt, FOVI_10V, FOVI_100MA);

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_OSC, 1 } });
	V5V.Set(FI, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	V5V.Set(FI, -0.01, FOVI_10V, FOVI_100MA, RELAY_ON);//10mA
	delay_ms(1);
	V5V.MeasureVI(20, 10);
	SERIAL
	{
		adresult1[SITE] = V5V.GetMeasResult(SITE, MVRET);
		V5V_PRE_SCM->SetTestResult(SITE, 0, adresult1[SITE]);
	}

	//V5V_LDO: V5V=-30MA, datasheet update from 10mA to 30mA
	manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_OSC, 1 },*/ { I2C_EN_LDO1, 1 } });
	V5V.Set(FI, -0.03, FOVI_10V, FOVI_100MA, RELAY_ON);//10mA
	delay_ms(1);
	
	V5V.MeasureVI(20, 10);
	SERIAL
	{
		adresult2[SITE] = V5V.GetMeasResult(SITE, MVRET);
		V5V_LDO_DS->SetTestResult(SITE, 0, adresult2[SITE]);
	}

	//V5V DROP OUT:VRECT=4.8V, V5V=-10MA
	V5V.Set(FI, -0.01, FOVI_10V, FOVI_100MA, RELAY_ON);//10mA
	VRECT.Set(FV, 4.8, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(3);
	VRECT.MeasureVI(20, 10);
	V5V.MeasureVI(20, 10);
	SERIAL
	{
		adresult3[SITE] = VRECT.GetMeasResult(SITE, MVRET);
		adresult4[SITE] = V5V.GetMeasResult(SITE, MVRET);

		adresult[SITE] = adresult3[SITE] - adresult4[SITE];
		V5V_DROP_OUT_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}

	//V5V LDO load regulation
	VRECT.Set(FV, VRECT_Volt, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	V5V.Set(FI, -0.001, FOVI_10V, FOVI_100MA, RELAY_ON);//1mA
	delay_ms(1);

	V5V.MeasureVI(20, 10);
	SERIAL adresult5[SITE] = V5V.GetMeasResult(SITE, MVRET);

	V5V.Set(FI, -0.02, FOVI_10V, FOVI_100MA, RELAY_ON);//20mA
	delay_ms(1);
	V5V.MeasureVI(20, 10);
	SERIAL
	{
		adresult6[SITE] = V5V.GetMeasResult(SITE, MVRET);
		//might add ABS
		adresult[SITE] = (adresult5[SITE] - adresult6[SITE])/(20-1)*1e3;/// unit: ohm
		V5V_LDO_LOAD_REG->SetTestResult(SITE, 0, adresult[SITE]);
	}

	//V5V LDO line regulation
	//V5V.Set(FI, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//delay_ms(1);
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 1);

	//V5V.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF, 1);

	//TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);
	//delay_ms(1);

	//manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_OSC, 1 } });
	//manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_LDO1, 1 } });
	//delay_ms(1);

	V5V.Set(FI, -0.005, FOVI_10V, FOVI_100MA, RELAY_ON);//5mA
	delay_ms(1);
	V5V.MeasureVI(20, 10);

	SERIAL adresult7[SITE] = V5V.GetMeasResult(SITE, MVRET);

	VRECT.Set(FV, 10, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);

	V5V.MeasureVI(20, 10);
	SERIAL
	{
		adresult8[SITE] = V5V.GetMeasResult(SITE, MVRET);

		adresult[SITE] = (adresult7[SITE] - adresult8[SITE]) / (10 - 5.5) * 100;//%
		V5V_LDO_LINE_REG->SetTestResult(SITE, 0, adresult[SITE]);
	}

	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	V5V.Set(FI, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//delay_ms(1);

	//V5V IMAX
	if (spec("VRECT") == 5.2)
	{
		VRECT_Volt = 5.5;
	}
	TM_ENTER_vi(VRECT, VRECT_Volt, FOVI_10V, FOVI_1A);

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_LDO1, 1 } });
	V5V.Set(FI, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	delay_ms(1);

	V5V.MeasureVI(20, 10);
	SERIAL
	{
		adresult1[SITE] = V5V.GetMeasResult(SITE, MVRET);
		volt[SITE] = adresult1[SITE] - 0.5;
	}
	V5V.Set(FI, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_us(500); 
	V5V.Set(FI, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	TM_EXIT_vi(VRECT, VRECT_Volt, FOVI_10V, FOVI_1A);

	V5V.SetSyn(FV, volt, NUM_SITES, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);//4.6V
	delay_ms(1);

	TM_ENTER_vi(VRECT, VRECT_Volt, FOVI_10V, FOVI_1A);
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_LDO1, 1 } });
	delay_ms(1);

	V5V.MeasureVI(50, 10);
	SERIAL
	{
		adresult[SITE] = V5V.GetMeasResult(SITE, MIRET);
		IMAX_V5V_DS->SetTestResult(SITE, 0, adresult[SITE] * 1e3);//mA
	}
	V5V.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.1);
	VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.1);
	delay_ms(1);
	V5V.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_OFF);//断电重新进TM
	delay_us(500);


	//V5V ISHORT
	V5V.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
	
	V5V.Set(FV, 1, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
	delay_ms(1);

	V5V.MeasureVI(50, 10);
	SERIAL
	{
		adresult[SITE] = V5V.GetMeasResult(SITE, MIRET);
		ISHORT_V5V_DS->SetTestResult(SITE, 0, adresult[SITE] * 1e3);//mA
	}
	V5V.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
	delay_us(500);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_us(200);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);

	//VRECT UVLO
	cbit.SetOn( K4_IIC_PULLUP, -1);
	VRECT.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_us(200);
	VRECT.Set(FV, 3.5, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	int interval = 10;
	double Trig = 700e-6;
	int sam = 200;
	int Trig_Point_F[SITE_NUM] = { 0 };
	int Trig_Point_R[SITE_NUM] = { 0 };
	//VRECT sweep from 3.5V to 2.5V
	VRECT.AwgSelect("VRECT_UVLO_F", 0, sam - 1, sam - 1, interval);
	VRECT.SetMeasITrig(Trig, TRIG_FALLING);
	VRECT.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&VRECT);
	STSEnableMeas(&VRECT);
	//STSAWGRunTriggerStop(&VRECT, &VRECT, &VRECT);
	STSAWGRun();

	SERIAL
	{
		Trig_Point_F[SITE] = int(VRECT.GetMeasResult(SITE, MIRET, TRIG_RESULT));
		if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
		{
			Trig_Point_F[SITE] = 999;
			VRECT_UVLO_DOWN_DS->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
		}
		else
		{
			adresult1[SITE] = VRECT.GetMeasResult(SITE, MVRET, Trig_Point_F[SITE]);
			VRECT_UVLO_DOWN_DS->SetTestResult(SITE, 0, adresult1[SITE]);
		}
	}

	//VRECT sweep from 2.5V to 3.5V
	VRECT.AwgSelect("VRECT_UVLO_R", 0, sam - 1, sam - 1, interval);
	VRECT.SetMeasITrig(Trig, TRIG_RISING);
	VRECT.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&VRECT);
	STSEnableMeas(&VRECT);
	//STSAWGRunTriggerStop(&VRECT, &VRECT, &VRECT);
	STSAWGRun();

	SERIAL
	{
		Trig_Point_R[SITE] = int(VRECT.GetMeasResult(SITE, MIRET, TRIG_RESULT));
		if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
		{
			Trig_Point_R[SITE] = 999;
			VRECT_UVLO_UP_DS->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
			VRECT_UVLO_HYS->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
		}
		else
		{
			adresult2[SITE] = VRECT.GetMeasResult(SITE, MVRET, Trig_Point_R[SITE]);
			adresult[SITE] = adresult2[SITE] - adresult1[SITE];
			VRECT_UVLO_UP_DS->SetTestResult(SITE, 0, adresult2[SITE]);
			VRECT_UVLO_HYS->SetTestResult(SITE, 0, adresult[SITE]);

		}
	}
	VRECT.Set(FV, 3.5, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_us(500);

	VRECT.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	VRECT.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_OFF);

    return 0;
}
 
DUT_API int PING_DET(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *VPDET_EN_UP_DS = StsGetParam(funcindex, "VPDET_EN_UP_DS");
    CParam *VPDET_EN_DOWN_DS = StsGetParam(funcindex, "VPDET_EN_DOWN_DS");
    CParam *IPDET_EN_DS = StsGetParam(funcindex, "IPDET_EN_DS");
    CParam *RENB_DS = StsGetParam(funcindex, "RENB_DS");
    CParam *crude_bg = StsGetParam(funcindex, "crude_bg");
    CParam *crude_vref_1P15V = StsGetParam(funcindex, "crude_vref_1P15V");
    CParam *crude_ibiasp_1uA = StsGetParam(funcindex, "crude_ibiasp_1uA");
    CParam *OSC_64K = StsGetParam(funcindex, "OSC_64K");
    CParam *PDET_TIMEOUT_DS = StsGetParam(funcindex, "PDET_TIMEOUT_DS");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	cbit.SetOn(K2_VRECT_V5V_CAP, K4_IIC_PULLUP, K7_SINK_PULLUP, -1);
	dioplus.I2CConnect();
	wait_relay();

	TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	ENB.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	SINK.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(200);

	manager.setfields({ { I2C_CTRL, 1 }, { EN_DIG_MUX, 1 }, { I2C_EN_LDO1, 1 }/*, { I2C_EN_OSC, 1 }, { TMOD_CTRL, 0x09 }*/, { MUX_DIG, 0x15 } });
	ENB.Set(FV, 0.5, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	int interval = 10;
	double Trig = 2.5;
	int sam = 200;
	int Trig_Point_R[SITE_NUM] = { 0 };
	int Trig_Point_F[SITE_NUM] = { 0 };
	//ENB sweep from 0.5V to 1.5V
	ENB.AwgSelect("VPDET_EN_R", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_FALLING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	ENB.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&ENB);
	STSEnableMeas(&ENB, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &ENB);

	SERIAL
	{
		Trig_Point_R[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));

		if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
		{
			Trig_Point_R[SITE] = 999;
			VPDET_EN_UP_DS->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
		}
		else
		{
			adresult1[SITE] = ENB.GetMeasResult(SITE, MVRET, Trig_Point_R[SITE]);
			VPDET_EN_UP_DS->SetTestResult(SITE, 0, adresult1[SITE]);
		}
	}

	//ENB sweep from 1.5V to 0.5V
	ENB.AwgSelect("VPDET_EN_F", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_RISING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	ENB.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&ENB);
	STSEnableMeas(&ENB, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &ENB);

	SERIAL
	{
		Trig_Point_F[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));

		if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
		{
			Trig_Point_F[SITE] = 999;
			VPDET_EN_DOWN_DS->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
			//VPDET_EN_HYS->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
		}
		else
		{
			adresult2[SITE] = ENB.GetMeasResult(SITE, MVRET, Trig_Point_F[SITE]);
			//adresult[SITE] = adresult2[SITE] - adresult1[SITE];
			VPDET_EN_DOWN_DS->SetTestResult(SITE, 0, adresult2[SITE]);
			//VPDET_EN_HYS->SetTestResult(SITE, 0, adresult[SITE]);
		}
	}

	ENB.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	SINK.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);
	SINK.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);

	//IPDET_EN
	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);
	ENB.Set(FV, ENB_Volt, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	ENB.Set(FV, ENB_Volt, FOVI_10V, FOVI_1MA, RELAY_ON);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);
	//V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	//delay_ms(1);
	ENB.MeasureVI(50, 10);
	SERIAL
	{
		adresult[SITE] = ENB.GetMeasResult(SITE, MIRET);

		if (spec("ENB") == 1.8 || spec("ENB") == 3.3)
		{
			adresult[SITE] = adresult[SITE] + 5*1e-6;//TEMP CHAR 1.8V/3.3V条件下low limit放宽5uA(即5~30uA)
		}
		IPDET_EN_DS->SetTestResult(SITE, 0, adresult[SITE] * 1e6);//uA
	}
	ENB.Set(FV, ENB_Volt, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_ms(1);

	//ENB pull down resistor
	//TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);
	ENB.Set(FV, 0.3, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_ms(2);
	ENB.MeasureVI(50, 10);
	SERIAL
	{
		adresult0[SITE] = ENB.GetMeasResult(SITE, MIRET);
		adresult[SITE] = 0.3 / adresult0[SITE] * 1e-6;//MΩ
		RENB_DS->SetTestResult(SITE, 0, adresult[SITE]);
	}

	ENB.Set(FV, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	INTB.Set(FI, 0, FOVI_5V, FOVI_1MA, RELAY_ON);
	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);
	ENB.Set(FV, 2.5, FOVI_10V, FOVI_1MA, RELAY_ON,0.5);
	ENB.Set(FV, ENB_Volt, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_ms(1);

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { EN_ANA_MUX, 1 }, { MUX_ANA, 0x0F } });
	delay_ms(3);//NEED
	if (Global_Tempchar_Program_Flag == 1)
	{
		delay_ms(10);
	}

	INTB.MeasureVI(20, 10);
	SERIAL
	{
		adresult[SITE] = INTB.GetMeasResult(SITE, MVRET);
		crude_bg->SetTestResult(SITE, 0, adresult[SITE]);
	}


	manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { EN_ANA_MUX, 1 },*/{ MUX_ANA, 0x02 } });
	//ENB.Set(FV, ENB_Volt, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_ms(1);

	INTB.MeasureVI(20, 10);
	SERIAL
	{
		adresult[SITE] = INTB.GetMeasResult(SITE, MVRET);
		crude_vref_1P15V->SetTestResult(SITE, 0, adresult[SITE]);
	}
	INTB.Set(FV, 0, FOVI_5V, FOVI_1MA, RELAY_ON);
	delay_us(200);


	manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { EN_ANA_MUX, 1 },*/ { MUX_ANA, 0x01 } });
	//ENB.Set(FV, ENB_Volt, FOVI_10V, FOVI_1MA, RELAY_ON);
	INTB.Set(FV, 1, FOVI_5V, FOVI_1MA, RELAY_ON, 1);
	delay_ms(1);

	INTB.MeasureVI(50, 10);
	SERIAL
	{
		adresult[SITE] = INTB.GetMeasResult(SITE, MIRET);
		crude_ibiasp_1uA->SetTestResult(SITE, 0, adresult[SITE]*1e6);//uA
	}
	INTB.Set(FV, 0, FOVI_5V, FOVI_1MA, RELAY_ON);
	ENB.Set(FV, 0, FOVI_10V, FOVI_1MA, RELAY_ON);
	TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	INTB.Set(FV, 0, FOVI_5V, FOVI_1MA, RELAY_OFF);
	ENB.Set(FV, 0, FOVI_10V, FOVI_1MA, RELAY_OFF);

	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K6_INTB_PULLUP, K24_QTMU_INTB, -1);
	QTMU.Connect();
	wait_relay();

	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	manager.setfields({ { I2C_CTRL, 1 }, { TMOD_CTRL, 0x04 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 } });
	ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	QTMU.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	QTMU.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	QTMU.SetStartTrigger(2.5, QTMU_PLUS_NEG_SLOPE);
	QTMU.SetStopTrigger(2.5, QTMU_PLUS_POS_SLOPE);
	QTMU.SetInSource(QTMU_PLUS_SINGLE_SOURCE);//INTB
	QTMU.SetSinglePulseMeas(QTMU_PLUS_COARSE, QTMU_PLUS_TIME_US, 0);
	QTMU.SetTimeOut(10);
	delay_ms(2);

	ENB.Set(FV, ENB_Volt, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);

	QTMU.SinglePlsMeas(0);

	SERIAL
	{
		adresult[SITE] = QTMU.GetMeasureResult(SITE);//INTB
		PDET_TIMEOUT_DS->SetTestResult(SITE, 0, adresult[SITE] * 1e-3);//UNIT: ms
	}
	ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);


	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K7_SINK_PULLUP, K23_QTMU_SINK, -1);
	wait_relay();

	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	manager.setfields({ { I2C_CTRL, 1 }, { EN_DIG_MUX, 1 }, { I2C_EN_LDO1, 1 }, { MUX_DIG, 0x16 } });
	ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	ENB.Set(FV, ENB_Volt, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);
	if (spec("V5V") == 3.3)
	{
		ENB.Set(FV, 2, FOVI_10V, FOVI_100MA, RELAY_ON, 1);
		delay_ms(1);
	}

	QTMU.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_1MHz);
	QTMU.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_1MHz);
	QTMU.SetStartTrigger(2.5, QTMU_PLUS_NEG_SLOPE);
	QTMU.SetInSource(QTMU_PLUS_SINGLE_SOURCE);//SINK

	QTMU.MeasFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 20, 10); //cycle number=20, timeout=10ms
	SERIAL
	{
		adresult[SITE] = QTMU.GetMeasureResult(SITE);//SINK
		OSC_64K->SetTestResult(SITE, 0, adresult[SITE]);
	}

	ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	ENB.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	if (POWER_FLAG)
	{
		TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);
		//QTMU.Disconnect();
	}
    return 0;
}
 
DUT_API int FREQ_TEST(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *OSC_4M_SCM = StsGetParam(funcindex, "OSC_4M_SCM");
    CParam *POST_OSC_48M_SCM = StsGetParam(funcindex, "POST_OSC_48M_SCM");
    CParam *IIC_FRQ_20KHz = StsGetParam(funcindex, "IIC_FRQ_20KHz");
    CParam *IIC_FRQ_400KHz_DS = StsGetParam(funcindex, "IIC_FRQ_400KHz_DS");
    CParam *IIC_FRQ_1MHz = StsGetParam(funcindex, "IIC_FRQ_1MHz");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here
	
	if (POWER_FLAG)
	{
		cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K7_SINK_PULLUP, K23_QTMU_SINK, -1);
		dioplus.I2CConnect();
		QTMU.Connect();
		wait_relay();
		TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
	manager.setfields({ { I2C_CTRL, 1 }, { EN_DIG_MUX, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { MUX_DIG, 0x18 } });
	delay_ms(1);

	QTMU.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_1MHz);
	QTMU.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_1MHz);
	QTMU.SetStartTrigger(2.5, QTMU_PLUS_NEG_SLOPE);
	QTMU.SetInSource(QTMU_PLUS_SINGLE_SOURCE);//SINK

	QTMU.MeasFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 20, 10); //cycle number=20, timeout=10ms
	SERIAL
	{
		adresult[SITE] = QTMU.GetMeasureResult(SITE);//SINK
		OSC_4M_SCM->SetTestResult(SITE, 0, adresult[SITE] * 64 * 1e-3);//Mhz
	}

	manager.setfields({ /*{ I2C_CTRL, 1 }, { EN_DIG_MUX, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 },*/ { MUX_DIG, 0x02 } });
	delay_ms(1);
	QTMU.MeasFreq(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 20, 10); //cycle number=20, timeout=10ms
	SERIAL
	{
		adresult[SITE] = QTMU.GetMeasureResult(SITE);//SINK
		POST_OSC_48M_SCM->SetTestResult(SITE, 0, adresult[SITE] * 64 * 12 * 1e-3);
	}
	TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);

	///////////////////////////LC FREQ (NMOS test)///////////////////////////
	//TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);
	//SINK.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_ON);

	//manager.setfields({ { TMOD_CTRL, 0x05 } });
	//delay_ms(1);
	//SINK.MeasureVI(20, 10);
	//SERIAL adresult1[SITE] = SINK.GetMeasResult(SITE, MVRET);

	//SINK.Set(FI, 0.001, FOVI_10V, FOVI_10MA, RELAY_ON);
	//delay_ms(1);
	//SINK.MeasureVI(20, 10);
	//SERIAL
	//{
	//	adresult2[SITE] = SINK.GetMeasResult(SITE, MVRET);
	//	adresult[SITE] = adresult2[SITE] - adresult1[SITE];
	//	LC_FREQ_2MHz->SetTestResult(SITE, 0, adresult[SITE]);
	//}
	//SINK.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	//TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);

	//SINK.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	///////////////////////////IIC FREQ///////////////////////////
	cbit.SetOn(K2_VRECT_V5V_CAP, K4_IIC_PULLUP, -1);//未使用buffer
	wait_relay();

	I2CFreqRead(20*1e3, DEV_ADDR, 0x08, read_data, read_pass);//Freq=20K
	SERIAL IIC_FRQ_20KHz->SetTestResult(SITE, 0, read_pass[SITE]);

	I2CFreqRead(400*1e3, DEV_ADDR, 0x08, read_data, read_pass);//Freq=400K
	SERIAL IIC_FRQ_400KHz_DS->SetTestResult(SITE, 0, read_pass[SITE]);

	I2CFreqRead(1000*1e3, DEV_ADDR, 0x08, read_data, read_pass);//Freq=1M
	SERIAL IIC_FRQ_1MHz->SetTestResult(SITE, 0, read_pass[SITE]);

	//dioplus.I2CDisconnect();
	QTMU.Disconnect();

	//SCL.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	//SDA.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	//delay_ms(1);
	//SCL.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	//SDA.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	double period1 = 2 * 1e-6; //reset to 500k
	dioplus.I2CSetClockPeriod(period1);
	dioplus.I2CSetSDADelay(period1 / 6, period1 / 2, period1 * 2 / 3);
	dioplus.I2CSetSCLDelay(0, period1 / 2);


	//int READ_0X08[SITE_NUM] = { 0 };
	//int read_pass[SITE_NUM] = { 0 };

	//double period1 = 50 * 1e-6; //20k for function test
	//dioplus.I2CSetClockPeriod(period1);
	//dioplus.I2CSetSDADelay(period1 / 6, period1 / 3, period1 * 2 / 3);
	//dioplus.I2CSetSCLDelay(0, period1 / 2);

	//dioplus.SetVIH(3.3f);
	//dioplus.SetVIL(0.0f);
	//dioplus.SetVOH(2.2f);
	//dioplus.SetVOL(0.5f);

	//TM_ENTER(V5V, 5);
	//manager.setfields({ { COMM2_DIS, 1 } });
	//delay_ms(1);

	//DIO_PLUS::I2CSite *pI2CSites[] = { &i2c_site1, &i2c_site2, &i2c_site3, &i2c_site4, &i2c_site5, &i2c_site6, &i2c_site7, &i2c_site8 };

	//dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X08, 1);
	//READ_0X08[0] = i2c_site1.GetDataByteValue(0);  // i2c site1 get the 1 byte value
	//READ_0X08[1] = i2c_site2.GetDataByteValue(0);  // i2c site2 get the 1 byte value
	//READ_0X08[2] = i2c_site3.GetDataByteValue(0);  // i2c site3 get the 1 byte value
	//READ_0X08[3] = i2c_site4.GetDataByteValue(0);  // i2c site4 get the 1 byte value
	//READ_0X08[4] = i2c_site5.GetDataByteValue(0);  // i2c site5 get the 1 byte value
	//READ_0X08[5] = i2c_site6.GetDataByteValue(0);  // i2c site6 get the 1 byte value
	//READ_0X08[6] = i2c_site7.GetDataByteValue(0);  // i2c site7 get the 1 byte value
	//READ_0X08[7] = i2c_site8.GetDataByteValue(0);  // i2c site8 get the 1 byte value

	//SERIAL
	//{
	//	if (READ_0X08[SITE]==0x02)
	//	{
	//		read_pass[SITE] = 1;
	//		IIC_FRQ_20KHz->SetTestResult(SITE, 0, read_pass[SITE]);

	//	}
	//	else
	//	{
	//		read_pass[SITE] = 0;
	//		IIC_FRQ_20KHz->SetTestResult(SITE, 0, read_pass[SITE]);
	//	}
	//}

    return 0;
}

DUT_API int SCAN_CHAIN(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *SCAN_FLAG = StsGetParam(funcindex, "SCAN_FLAG");
//}}AFX_STS_PARAM_PROTOTYPES
	// TODO: Add your function code here

	int nErr = 0;
	BYTE sitestatus[STS_SITE_NUM] = { 0, 0, 0, 0, 0, 0, 0, 0 };//判断工位是否有效 1有效 0被屏蔽
	StsGetSiteStatus(sitestatus, STS_SITE_NUM);

	Qvm.Disconnect();
	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K5_DIO2_ENB, K0_DIO3_INTB, K6_INTB_PULLUP, -1);
	dioplus.Connect();
	wait_relay();

	dioplus.SetVIH(5.0f);
	dioplus.SetVIL(0.0f);
	dioplus.SetVOH(1.0f);
	dioplus.SetVOL(0.2f);
	//INTB.Set(FV, 5, FOVI_5V, FOVI_10MA, RELAY_ON);
	//INTB.SetClamp(80, 80);
	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	//enter scan mode
	I2CWriteAllSites(0xF9, 0X00);
	I2CWriteAllSites(0xF9, 0Xaa);
	I2CWriteAllSites(0xF9, 0X55);
	I2CWriteAllSites(0xF9, 0Xa5);
	I2CWriteAllSites(0xF9, 0X5a);
	delay_ms(1);

	nErr = dioplus.Run("scan_start", "scan_stop", 1);
	//const DIO_PLUS::FailLineInfo *pFailLineInfo = NULL;
	
	int rtn_flag = 0;
	int rt_array[STS_SITE_NUM] = { 0 };
	int failcount[STS_SITE_NUM] = { 0 };
	int Scanout_CH[STS_SITE_NUM] = { 3, 7, 11, 15, 19, 23, 27, 31 };

	SERIAL
	{
		failcount[SITE] = dioplus.GetChannelFailCount(Scanout_CH[SITE]);
		//dioplus.SaveFailMap();
		adresult[SITE] = failcount[SITE];
		if (adresult[SITE] > 0 && sitestatus[SITE] == 1)
		{
			rtn_flag = 1;
			rt_array[SITE] = 1;
		}
	}

	//if (rtn_flag == 1)
	//{
	//	nErr = dioplus.Run("scan_start", "scan_stop", 1);
	//	dioplus.SaveFailMap();
	//	for (site = 0; site < STS_SITE_NUM; site++)
	//	{
	//		failcount[site] = dioplus.GetChannelFailCount(Scanout_CH[site]);
	//		adresult[site] = failcount[site];
	//	
	//	}
	//}

	SERIAL SCAN_FLAG->SetTestResult(SITE, 0, adresult[SITE]);


	if (POWER_FLAG)
	{
		TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);
		//INTB.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
		//INTB.SetClamp(100, 100);
		dioplus.Disconnect();
	}

	return 0;
}

DUT_API int IDDQ_TEST(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *iddq_current_base = StsGetParam(funcindex, "iddq_current_base");
    CParam *iddq_current = StsGetParam(funcindex, "iddq_current");
    CParam *iddq_fail = StsGetParam(funcindex, "iddq_fail");
    CParam *iddq_current1 = StsGetParam(funcindex, "iddq_current1");
    CParam *iddq_fail1 = StsGetParam(funcindex, "iddq_fail1");
    CParam *iddq_current2 = StsGetParam(funcindex, "iddq_current2");
    CParam *iddq_fail2 = StsGetParam(funcindex, "iddq_fail2");
    CParam *iddq_current3 = StsGetParam(funcindex, "iddq_current3");
    CParam *iddq_fail3 = StsGetParam(funcindex, "iddq_fail3");
    CParam *iddq_current4 = StsGetParam(funcindex, "iddq_current4");
    CParam *iddq_fail4 = StsGetParam(funcindex, "iddq_fail4");
    CParam *iddq_current5 = StsGetParam(funcindex, "iddq_current5");
    CParam *iddq_fail5 = StsGetParam(funcindex, "iddq_fail5");
    CParam *iddq_current6 = StsGetParam(funcindex, "iddq_current6");
    CParam *iddq_fail6 = StsGetParam(funcindex, "iddq_fail6");
    CParam *iddq_current7 = StsGetParam(funcindex, "iddq_current7");
    CParam *iddq_fail7 = StsGetParam(funcindex, "iddq_fail7");
    CParam *iddq_current8 = StsGetParam(funcindex, "iddq_current8");
    CParam *iddq_fail8 = StsGetParam(funcindex, "iddq_fail8");
    CParam *iddq_current9 = StsGetParam(funcindex, "iddq_current9");
    CParam *iddq_fail9 = StsGetParam(funcindex, "iddq_fail9");
    CParam *iddq_current10 = StsGetParam(funcindex, "iddq_current10");
    CParam *iddq_fail10 = StsGetParam(funcindex, "iddq_fail10");
    CParam *iddq_current11 = StsGetParam(funcindex, "iddq_current11");
    CParam *iddq_fail11 = StsGetParam(funcindex, "iddq_fail11");
    CParam *iddq_current12 = StsGetParam(funcindex, "iddq_current12");
    CParam *iddq_fail12 = StsGetParam(funcindex, "iddq_fail12");
    CParam *iddq_current13 = StsGetParam(funcindex, "iddq_current13");
    CParam *iddq_fail13 = StsGetParam(funcindex, "iddq_fail13");
    CParam *iddq_current14 = StsGetParam(funcindex, "iddq_current14");
    CParam *iddq_fail14 = StsGetParam(funcindex, "iddq_fail14");
    CParam *iddq_current15 = StsGetParam(funcindex, "iddq_current15");
    CParam *iddq_fail15 = StsGetParam(funcindex, "iddq_fail15");
    CParam *iddq_current16 = StsGetParam(funcindex, "iddq_current16");
    CParam *iddq_fail16 = StsGetParam(funcindex, "iddq_fail16");
    CParam *iddq_current17 = StsGetParam(funcindex, "iddq_current17");
    CParam *iddq_fail17 = StsGetParam(funcindex, "iddq_fail17");
    CParam *iddq_current18 = StsGetParam(funcindex, "iddq_current18");
    CParam *iddq_fail18 = StsGetParam(funcindex, "iddq_fail18");
    CParam *iddq_current19 = StsGetParam(funcindex, "iddq_current19");
    CParam *iddq_fail19 = StsGetParam(funcindex, "iddq_fail19");
//}}AFX_STS_PARAM_PROTOTYPES
	// TODO: Add your function code here
	int nErr = 0;
	int failcount[STS_SITE_NUM] = { 0 };
	int Scanout_CH[STS_SITE_NUM] = { 3, 7, 11, 15, 19, 23, 27, 31 };
	int rtn_flag = 0;
	double IDDQ_V5V_CURRENT_result[STS_SITE_NUM] = { 0 };
	BYTE sitestatus[STS_SITE_NUM] = { 0 };//判断工位是否有效 1有效 0被屏蔽
	StsGetSiteStatus(sitestatus, STS_SITE_NUM);

	if (POWER_FLAG)
	{
		cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K5_DIO2_ENB, K0_DIO3_INTB, K6_INTB_PULLUP, -1);
		dioplus.Connect();
		wait_relay();

		TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);

		//enter scan mode
		I2CWriteAllSites(0xF9, 0X00);
		I2CWriteAllSites(0xF9, 0Xaa);
		I2CWriteAllSites(0xF9, 0X55);
		I2CWriteAllSites(0xF9, 0Xa5);
		I2CWriteAllSites(0xF9, 0X5a);
		delay_ms(5);
	}
	V5V.Set(FV, 5, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(2); 
	if (Global_Tempchar_Program_Flag == 1)
	{
		delay_ms(10);
	}
	V5V.MeasureVI(20, 10);
	SERIAL
	{
		adresult1[SITE] = V5V.GetMeasResult(SITE, MIRET);
		iddq_current_base->SetTestResult(SITE, 0, adresult1[SITE] * 1000000);
	}
	V5V.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1); 

	nErr = dioplus.Run("iddq_start", "iddq_pat1", 1);

	V5V.Set(FV, 5, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_ms(2);
	V5V.MeasureVI(20, 10);
	V5V.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	SERIAL
	{
		failcount[SITE] = dioplus.GetChannelFailCount(Scanout_CH[SITE]);
		adresult[SITE] = failcount[SITE];
		IDDQ_V5V_CURRENT_result[SITE] = V5V.GetMeasResult(SITE, MIRET);
		iddq_current->SetTestResult(SITE, 0, IDDQ_V5V_CURRENT_result[SITE] * 1000000);	//scale to uA

		iddq_fail->SetTestResult(SITE, 0, adresult[SITE]);
		if (IDDQ_V5V_CURRENT_result[SITE] > 0.00001 && sitestatus[SITE] == 1)
			rtn_flag = 1;
	}

	CParam *iddq_pat_X[36] =
	{
		iddq_current1, iddq_fail1, iddq_current2, iddq_fail2, iddq_current3, iddq_fail3, iddq_current4, iddq_fail4,
		iddq_current5, iddq_fail5, iddq_current6, iddq_fail6, iddq_current7, iddq_fail7, iddq_current8, iddq_fail8,
		iddq_current9, iddq_fail9, iddq_current10, iddq_fail10, iddq_current11, iddq_fail11, iddq_current12, iddq_fail12,
		iddq_current13, iddq_fail13, iddq_current14, iddq_fail14, iddq_current15, iddq_fail15, iddq_current16, iddq_fail16,
		iddq_current17, iddq_fail17, iddq_current18, iddq_fail18,
	};

	for (int i= 1; i < 19; ++i) 
	{  
		string str_start;
		string str_stop;

		str_start = "iddq_pat" + std::to_string(i);
		str_stop = "iddq_pat" + std::to_string(i + 1);

		nErr = dioplus.Run(str_start.c_str(), str_stop.c_str(), 1);
		V5V.Set(FV, 5, FOVI_10V, FOVI_1MA, RELAY_ON);
		delay_ms(4);
		V5V.MeasureVI(20, 10);
		V5V.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON);
		delay_ms(2);
		SERIAL
		{
			failcount[SITE] = dioplus.GetChannelFailCount(Scanout_CH[SITE]);
			adresult[SITE] = failcount[SITE];
			IDDQ_V5V_CURRENT_result[SITE] = V5V.GetMeasResult(SITE, MIRET);

			iddq_pat_X[2 * (i - 1) + 0]->SetTestResult(SITE, 0, IDDQ_V5V_CURRENT_result[SITE] * 1000000);	//scale to uA
			iddq_pat_X[2 * (i - 1) + 1]->SetTestResult(SITE, 0, adresult[SITE]);

			if (IDDQ_V5V_CURRENT_result[SITE] > 0.00001 && sitestatus[SITE] == 1)
				rtn_flag = 1;
		}
	}

	nErr = dioplus.Run("iddq_pat19", "iddq_stop", 1);
	V5V.Set(FV, 5, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_ms(3);
	V5V.MeasureVI(20, 10);

	SERIAL
	{
		failcount[SITE] = dioplus.GetChannelFailCount(Scanout_CH[SITE]);
		adresult[SITE] = failcount[SITE];
		IDDQ_V5V_CURRENT_result[SITE] = V5V.GetMeasResult(SITE, MIRET);
		iddq_current19->SetTestResult(SITE, 0, IDDQ_V5V_CURRENT_result[SITE] * 1000000);	//scale to uA

		iddq_fail19->SetTestResult(SITE, 0, adresult[SITE]);
		if (IDDQ_V5V_CURRENT_result[SITE] > 0.00001 && sitestatus[SITE] == 1)
			rtn_flag = 1;
	}
	
	//dioplus.SaveFailMap();
	
	V5V.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	dioplus.Disconnect();

	return 0;
}

DUT_API int IO_TEST(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *VTH_SCL_UP_DS = StsGetParam(funcindex, "VTH_SCL_UP_DS");
    CParam *VTH_SCL_DOWN_DS = StsGetParam(funcindex, "VTH_SCL_DOWN_DS");
    CParam *VTH_SCL_HYS = StsGetParam(funcindex, "VTH_SCL_HYS");
    CParam *VTH_SDA_UP_DS = StsGetParam(funcindex, "VTH_SDA_UP_DS");
    CParam *VTH_SDA_DOWN_DS = StsGetParam(funcindex, "VTH_SDA_DOWN_DS");
    CParam *VTH_SDA_HYS = StsGetParam(funcindex, "VTH_SDA_HYS");
    CParam *VOL_SDA_DS = StsGetParam(funcindex, "VOL_SDA_DS");
    CParam *VOL_INTB_DS = StsGetParam(funcindex, "VOL_INTB_DS");
    CParam *Ibias_SCL_DS = StsGetParam(funcindex, "Ibias_SCL_DS");
    CParam *Ibias_SDA_DS = StsGetParam(funcindex, "Ibias_SDA_DS");
    CParam *Ibias_INTB_DS = StsGetParam(funcindex, "Ibias_INTB_DS");
    CParam *RSINK_SCM = StsGetParam(funcindex, "RSINK_SCM");
    CParam *RCOMM1_code0_SCM = StsGetParam(funcindex, "RCOMM1_code0_SCM");
    CParam *RCOMM1_code1_SCM = StsGetParam(funcindex, "RCOMM1_code1_SCM");
    CParam *RCOMM2_code0_SCM = StsGetParam(funcindex, "RCOMM2_code0_SCM");
    CParam *RCOMM2_code1_SCM = StsGetParam(funcindex, "RCOMM2_code1_SCM");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	cbit.SetOn(K2_VRECT_V5V_CAP, K4_IIC_PULLUP, - 1);
	dioplus.I2CConnect();
	wait_relay();

	TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	manager.setfields({ { I2C_CTRL, 1 }, { EN_DIG_MUX, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { MUX_DIG, 0x13 } });
	delay_ms(1);
	
	cbit.SetOn(K2_VRECT_V5V_CAP, K7_SINK_PULLUP, K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA, -1);
	dioplus.Disconnect();
	wait_relay();

	SCL.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	SINK.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_us(200);
	SCL.Set(FV, 0.5, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	int interval = 10;
	double Trig = 2.5;
	int sam = 200;
	int Trig_Point_R[SITE_NUM] = { 0 };
	int Trig_Point_F[SITE_NUM] = { 0 };
	//SCL sweep from 0.5V to 1.5V
	SCL.AwgSelect("VTH_SCL_R", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_FALLING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	SCL.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&SCL);
	STSEnableMeas(&SCL, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &SCL);

	SERIAL
	{
		Trig_Point_R[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));

		if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
		{
			Trig_Point_R[SITE] = 999;
			VTH_SCL_UP_DS->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
		}
		else
		{
			adresult1[SITE] = SCL.GetMeasResult(SITE, MVRET, Trig_Point_R[SITE]);
			VTH_SCL_UP_DS->SetTestResult(SITE, 0, adresult1[SITE]);
		}
	}

	//SCL sweep from 1.5V to 0.5V
	SCL.AwgSelect("VTH_SCL_F", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_RISING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	SCL.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&SCL);
	STSEnableMeas(&SCL, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &SCL);

	SERIAL
	{
		Trig_Point_F[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));

		if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
		{
			Trig_Point_F[SITE] = 999;
			VTH_SCL_DOWN_DS->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
			VTH_SCL_HYS->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
		}
		else
		{
			adresult2[SITE] = SCL.GetMeasResult(SITE, MVRET, Trig_Point_F[SITE]);
			adresult[SITE] = adresult1[SITE] - adresult2[SITE];
			VTH_SCL_DOWN_DS->SetTestResult(SITE, 0, adresult2[SITE]);
			VTH_SCL_HYS->SetTestResult(SITE, 0, adresult[SITE]);
		}
	}
	SCL.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	SCL.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	//delay_ms(1);

	dioplus.I2CConnect();
	delay_ms(1);

	cbit.SetOn(K2_VRECT_V5V_CAP, K4_IIC_PULLUP, -1);
	wait_relay();
	manager.setfields({ /*{ I2C_CTRL, 1 }, { EN_DIG_MUX, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 },*/ { MUX_DIG, 0x14 } });
	delay_ms(1);

	cbit.SetOn(K2_VRECT_V5V_CAP, K7_SINK_PULLUP, K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA, -1);
	dioplus.I2CDisconnect();
	wait_relay();

	SDA.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(200);
	SDA.Set(FV, 0.5, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	//SDA sweep from 0.5V to 1.5V
	SDA.AwgSelect("VTH_SDA_R", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_FALLING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	SDA.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&SDA);
	STSEnableMeas(&SDA, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &SDA);

	SERIAL
	{
		Trig_Point_R[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));

		if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
		{
			Trig_Point_R[SITE] = 999;
			VTH_SDA_UP_DS->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
		}
		else
		{
			adresult1[SITE] = SDA.GetMeasResult(SITE, MVRET, Trig_Point_R[SITE]);
			VTH_SDA_UP_DS->SetTestResult(SITE, 0, adresult1[SITE]);
		}
	}

	//SDA sweep from 1.5V to 0.5V
	SDA.AwgSelect("VTH_SDA_F", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_RISING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	SDA.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&SDA);
	STSEnableMeas(&SDA, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &SDA);

	SERIAL
	{
		Trig_Point_F[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));

		if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
		{
			Trig_Point_F[SITE] = 999;
			VTH_SDA_DOWN_DS->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
			VTH_SDA_HYS->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
		}
		else
		{
			adresult2[SITE] = SDA.GetMeasResult(SITE, MVRET, Trig_Point_F[SITE]);
			adresult[SITE] = adresult1[SITE] - adresult2[SITE];
			VTH_SDA_DOWN_DS->SetTestResult(SITE, 0, adresult2[SITE]);
			VTH_SDA_HYS->SetTestResult(SITE, 0, adresult[SITE]);
		}
	}
	SDA.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	SDA.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	//delay_ms(1);


	dioplus.I2CConnect();
	delay_ms(1);

	manager.historyClear();//clear history value
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 },{ I2C_SDA, 1 } });
	delay_ms(1);


	dioplus.I2CDisconnect();
	delay_ms(1);

	SDA.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	SDA.Set(FV, 0.1, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	SDA.MeasureVI(50, 10);
	SERIAL
	{
		adresult1[SITE] = SDA.GetMeasResult(SITE, MIRET);
		adresult[SITE] = 0.005 * 0.1 / adresult1[SITE];//pulldown voltage of SDA
		VOL_SDA_DS->SetTestResult(SITE, 0, adresult[SITE]);
	}
	SDA.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	SDA.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_OFF);
	TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);//下电，否则SDA被拉低，无法写IIC


	cbit.SetOn(K2_VRECT_V5V_CAP, K4_IIC_PULLUP, -1);
	dioplus.I2CConnect();
	wait_relay();

	TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_INT_OUT, 1 } });
	INTB.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	INTB.Set(FV, 0.1, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	INTB.MeasureVI(50, 10);
	SERIAL
	{
		adresult1[SITE] = INTB.GetMeasResult(SITE, MIRET);
		adresult[SITE] = 0.005 * 0.1 / adresult1[SITE];//pulldown voltage of INTB
		VOL_INTB_DS->SetTestResult(SITE, 0, adresult[SITE]);
	}
	INTB.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	INTB.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_OFF);


	manager.setfields({ { I2C_INT_OUT, 0 } });//Clear
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_IBIAS_IO, 0x04 } });
	delay_ms(1);

	cbit.SetOn(K2_VRECT_V5V_CAP, /*K4_IIC_PULLUP,*/ K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA, -1);
	dioplus.I2CDisconnect();
	wait_relay();


	SCL.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_us(500);
	SCL.Set(FV, 1, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(1);
	SCL.MeasureVI(50, 10);
	SERIAL
	{
		adresult1[SITE] = SCL.GetMeasResult(SITE, MIRET);
		adresult[SITE] = -adresult1[SITE] * 1e6;//有上拉要减上拉电流
		Ibias_SCL_DS->SetTestResult(SITE, 0, adresult[SITE]);
	}
	SCL.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_us(500);
	SCL.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_OFF);
	//delay_ms(1);

	dioplus.I2CConnect();
	delay_ms(1);
	manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 },*/ { I2C_IBIAS_IO, 0x08 } });
	delay_ms(1);
	dioplus.I2CDisconnect();
	SDA.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(1);

	SDA.Set(FV, 1, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(1);
	SDA.MeasureVI(50, 10);
	SERIAL
	{
		adresult1[SITE] = SDA.GetMeasResult(SITE, MIRET);
		adresult[SITE] = -adresult1[SITE] * 1e6;//有上拉要减上拉电流
		Ibias_SDA_DS->SetTestResult(SITE, 0, adresult[SITE]);
	}
	SDA.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_us(500);
	SDA.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_OFF);

	cbit.SetOn(K2_VRECT_V5V_CAP/*, K4_IIC_PULLUP, K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA*/, -1);
	dioplus.I2CConnect();
	delay_ms(1);

	manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 },*/{ I2C_IBIAS_IO, 0x02 } });
	INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(1);
	//INTB.MeasureVI(50, 10);
	if (spec("V5V") == 3.3)
	{
		dioplus.I2CDisconnect();
		wait_relay();
	}

	INTB.Set(FV, 1, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(1);
	INTB.MeasureVI(50, 10);
	SERIAL
	{
		adresult1[SITE] = INTB.GetMeasResult(SITE, MIRET);
		adresult[SITE] = -adresult1[SITE] * 1e6;//有上拉要减上拉电流
		Ibias_INTB_DS->SetTestResult(SITE, 0, adresult[SITE]);
	}
	INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_us(500);
	INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_OFF);
	TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	if (spec("V5V") == 3.3)
	{
		dioplus.I2CConnect();
		wait_relay();
	}

	//pulldown resistor of SINK
	cbit.SetOn(K2_VRECT_V5V_CAP, K4_IIC_PULLUP, K10_OVI6_ENB_COMM1, K11_OVI7_VOUT_COMM2, -1);
	wait_relay();

	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_ENTER_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
	else
	{
		TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);
	}
	SINK.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_SINK_ON, 1 } });
	delay_ms(1);

	SINK.Set(FV, 0.1, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	SINK.MeasureVI(50, 10);
	SERIAL
	{
		adresult1[SITE] = SINK.GetMeasResult(SITE, MIRET);
		adresult[SITE] = 0.1 / adresult1[SITE];
		RSINK_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}
	SINK.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	SINK.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_OFF);


	//COMM1 pin pull down resistor 5Ω
	COMM1.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
	manager.setfields({ { I2C_SINK_ON, 0 }});//Clear
	manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 },*/{ I2C_COM1_ON, 1 }, { LOAD0_COMM_RDSON_OPT, 0 } });
	COMM1.Set(FV, 0.1, FOVI_1V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);

	COMM1.MeasureVI(50, 10);
	SERIAL
	{
		adresult1[SITE] = COMM1.GetMeasResult(SITE, MIRET);
		adresult2[SITE] = COMM1.GetMeasResult(SITE, MVRET);
		adresult[SITE] = adresult2[SITE] / (adresult1[SITE] + 1e-32);
		RCOMM1_code0_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}

	//COMM1 pin pull down resistor 10Ω
	manager.setfields({ { LOAD0_COMM_RDSON_OPT, 1 } });
	delay_ms(1);
	COMM1.MeasureVI(50, 10);
	SERIAL
	{
		adresult1[SITE] = COMM1.GetMeasResult(SITE, MIRET);
		adresult2[SITE] = COMM1.GetMeasResult(SITE, MVRET);
		adresult[SITE] = adresult2[SITE] / (adresult1[SITE] + 1e-32);
		RCOMM1_code1_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}

	COMM1.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	COMM1.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_OFF);

	//COMM2 pin pull down resistor 5Ω
	COMM2.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	manager.setfields({{ I2C_COM1_ON, 0 } });//Clear
	manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 },*/{ I2C_COM2_ON, 1 }, { LOAD0_COMM_RDSON_OPT, 0 } });
	delay_ms(1);

	COMM2.Set(FV, 0.1, FOVI_1V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);
	COMM2.MeasureVI(50, 10);
	SERIAL
	{
		adresult1[SITE] = COMM2.GetMeasResult(SITE, MIRET);
		adresult2[SITE] = COMM2.GetMeasResult(SITE, MVRET);
		adresult[SITE] = adresult2[SITE] / (adresult1[SITE] + 1e-32);
		RCOMM2_code0_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}

	//COMM2 pin pull down resistor 10Ω
	manager.setfields({ { LOAD0_COMM_RDSON_OPT, 1 } });
	delay_ms(1);
	COMM2.MeasureVI(50, 10);
	SERIAL
	{
		adresult1[SITE] = COMM2.GetMeasResult(SITE, MIRET);
		adresult2[SITE] = COMM2.GetMeasResult(SITE, MVRET);
		adresult[SITE] = adresult2[SITE] / (adresult1[SITE] + 1e-32);
		RCOMM2_code1_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}

	COMM2.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	COMM2.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_OFF);
	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_EXIT_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
	else
	{
		TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);
	}
    return 0;
}
 
DUT_API int RDSON(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *RAC1_HS_DS = StsGetParam(funcindex, "RAC1_HS_DS");
    CParam *RAC1_LS_DS = StsGetParam(funcindex, "RAC1_LS_DS");
    CParam *RAC1_LS_V = StsGetParam(funcindex, "RAC1_LS_V");
    CParam *RAC1_LS_I = StsGetParam(funcindex, "RAC1_LS_I");
    CParam *RAC2_HS_DS = StsGetParam(funcindex, "RAC2_HS_DS");
    CParam *RAC2_LS_DS = StsGetParam(funcindex, "RAC2_LS_DS");
    CParam *RAC2_LS_V = StsGetParam(funcindex, "RAC2_LS_V");
    CParam *RAC2_LS_I = StsGetParam(funcindex, "RAC2_LS_I");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	//HS_AC1_RON
	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K12_PVI0H_VRECT, K15_PVI0L_AC1, K25_QVM_FPVI, -1);//FPVI H_VRECT, FPVI L_AC1
	dioplus.I2CConnect();
	Qvm.Connect();
	wait_relay();

	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	AC2.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	delay_us(500);

	VRECT.Set(FV, 5.5, FOVI_10V, FOVI_1A, RELAY_ON, 1);
	AC1.Set(FI, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	AC2.Set(FV, 5.5, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
	delay_us(500);

	AC2.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);//大电流拉到地
	delay_us(500);

	AC1.Set(FI, -0.1, FOVI_10V, FOVI_1A, RELAY_ON);
	delay_ms(2);

	AC1.MeasureVI(50, 10);
	Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);//VRECT-AC1

	SERIAL
	{
		adresult0[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
		adresult1[SITE] = AC1.GetMeasResult(SITE, MIRET);
		adresult[SITE] = -adresult0[SITE] / (adresult1[SITE] + 1e-32) * 1e3;//mohm
		RAC1_HS_DS->SetTestResult(SITE, 0, adresult[SITE]);
	}
	AC1.Set(FI, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	delay_ms(1);
	AC1.Set(FI, 0, FOVI_10V, FOVI_1A, RELAY_OFF);
	AC2.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_OFF);
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_OFF);
	//delay_ms(1);

	//cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K13_PVI0H_PGND, K15_PVI0L_AC1, K25_QVM_FPVI, -1);//FPVI H_VRECT, FPVI L_AC1
	//TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);

	//LS_AC1_RON
	if (Global_Tempchar_Program_Flag == 1)
	{
		VRECT.Set(FV, spec("V5V"), FOVI_10V, FOVI_1A, RELAY_ON);
		V5V.Set(FV, spec("V5V"), FOVI_10V, FOVI_1A, RELAY_ON);
		delay_ms(2);
	}
	TM_RGE_WRITE();

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_RECT_LS, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 } });
	delay_ms(1);

	if (Global_Tempchar_Program_Flag == 1)
	{
		AC2.Set(FV, spec("V5V"), FOVI_10V, FOVI_1A, RELAY_ON, 1);
		AC2.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
		delay_ms(1);
		AC2.Set(FV, spec("V5V"), FOVI_10V, FOVI_1A, RELAY_ON, 1);
		AC1.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON);
		delay_ms(1);
	}
	else
	{
		AC2.Set(FV, 5.5, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
		AC2.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
		delay_ms(1);
		AC2.Set(FV, 5.5, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
		AC1.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON);
		delay_ms(1);
	}

	AC1.Set(FV, -0.2, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(2);
	AC1.Set(FV, -0.05, FOVI_1V, FOVI_1A, RELAY_ON);//Voltage:current=1:1
	delay_ms(2);

	AC1.MeasureVI(50, 10);
	//Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);//VRECT-AC1

	SERIAL
	{
		adresult2[SITE] = AC1.GetMeasResult(SITE, MIRET);
		adresult3[SITE] = AC1.GetMeasResult(SITE, MVRET);
		//adresult3[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
		adresult[SITE] = adresult3[SITE] / (adresult2[SITE] + 1e-32) * 1e3;//mohm
		RAC1_LS_DS->SetTestResult(SITE, 0, adresult[SITE]);

		RAC1_LS_V->SetTestResult(SITE, 0, adresult3[SITE] * 1e3);//MV
		RAC1_LS_I->SetTestResult(SITE, 0, adresult2[SITE]);

	}
	AC1.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON);
	AC2.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	delay_ms(1);
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
	if (Global_Tempchar_Program_Flag == 1)
	{
		VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
		V5V.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
		delay_ms(1);
		V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
		delay_us(500);
		V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	}
	else
	{
		VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
	}
	delay_ms(1);
	AC2.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_OFF);//avoid VRECT spike

	//HS_AC2_RON
	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K12_PVI0H_VRECT, K16_PVI0L_AC2, K25_QVM_FPVI, -1);//FPVI H_VRECT, FPVI L_AC2
	wait_relay();

	VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	AC1.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	delay_us(500);

	VRECT.Set(FV, 5.5, FOVI_10V, FOVI_1A, RELAY_ON, 1);
	AC2.Set(FI, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	AC1.Set(FV, 5.5, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
	delay_us(500);

	AC1.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);//大电流拉到地
	delay_us(500);
	AC2.Set(FI, -0.1, FOVI_10V, FOVI_1A, RELAY_ON);
	delay_ms(2);

	AC2.MeasureVI(50, 10);
	Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);//VRECT-AC1

	SERIAL
	{
		adresult0[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
		adresult1[SITE] = AC2.GetMeasResult(SITE, MIRET);
		adresult[SITE] = -adresult0[SITE] / (adresult1[SITE] + 1e-32) * 1e3;//mohm
		RAC2_HS_DS->SetTestResult(SITE, 0, adresult[SITE]);
	}
	AC2.Set(FI, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	delay_ms(1);
	AC2.Set(FI, 0, FOVI_10V, FOVI_1A, RELAY_OFF);
	AC1.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_OFF);
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_OFF);
	//delay_ms(1);


	//cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K13_PVI0H_PGND, K16_PVI0L_AC2, K25_QVM_FPVI, -1);//FPVI H_VRECT, FPVI L_AC1
	//TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);

	//LS_AC2_RON
	if (Global_Tempchar_Program_Flag == 1)
	{
		VRECT.Set(FV, spec("V5V"), FOVI_10V, FOVI_1A, RELAY_ON);
		V5V.Set(FV, spec("V5V"), FOVI_10V, FOVI_1A, RELAY_ON);
		delay_ms(2);
	}
	TM_RGE_WRITE();

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_RECT_LS, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 } });
	delay_ms(1);

	if (Global_Tempchar_Program_Flag == 1)
	{
		AC1.Set(FV, spec("V5V"), FOVI_10V, FOVI_1A, RELAY_ON, 1);
		AC1.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
		delay_ms(1);
		AC1.Set(FV, spec("V5V"), FOVI_10V, FOVI_1A, RELAY_ON, 1);
		AC2.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON);
		delay_ms(1);
	}
	else
	{
		AC1.Set(FV, 5.5, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
		AC1.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
		delay_us(500);
		AC1.Set(FV, 5.5, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
		AC2.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON);
		delay_us(500);
	}
	AC2.Set(FV, -0.2, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(1);
	AC2.Set(FV, -0.05, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(2);

	AC2.MeasureVI(50, 10);
	//Qvm.MeasureLADC(100, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);//VRECT-AC2

	SERIAL
	{
		adresult2[SITE] = AC2.GetMeasResult(SITE, MIRET);
		adresult3[SITE] = AC2.GetMeasResult(SITE, MVRET);
		//adresult3[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
		adresult[SITE] = adresult3[SITE] / (adresult2[SITE] + 1e-32) * 1e3;//mohm
		RAC2_LS_DS->SetTestResult(SITE, 0, adresult[SITE]);

		RAC2_LS_V->SetTestResult(SITE, 0, adresult3[SITE] * 1e3);//MV
		RAC2_LS_I->SetTestResult(SITE, 0, adresult2[SITE]);

	}

	AC1.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
	AC2.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON, 0.5);
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
	if (Global_Tempchar_Program_Flag == 1)
	{
		VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
		V5V.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
		delay_ms(1);
		V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
		delay_us(500);
		V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	}
	else
	{
		VRECT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON, 0.5);
	}
	delay_ms(1);
	AC1.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	VRECT.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON);
	delay_us(500);

	AC1.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_OFF);
	AC2.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_OFF);
	VRECT.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_OFF);

	Qvm.Disconnect();

    return 0;
}
 
DUT_API int RECTIFIER(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *COMP_ON_AC1_SCM = StsGetParam(funcindex, "COMP_ON_AC1_SCM");
    CParam *COMP_OFF_AC1_SCM = StsGetParam(funcindex, "COMP_OFF_AC1_SCM");
    CParam *COMP_ON_AC2_SCM = StsGetParam(funcindex, "COMP_ON_AC2_SCM");
    CParam *COMP_OFF_AC2_SCM = StsGetParam(funcindex, "COMP_OFF_AC2_SCM");
    CParam *AC1_FSK_UP_SCM = StsGetParam(funcindex, "AC1_FSK_UP_SCM");
    CParam *AC1_FSK_DOWN_SCM = StsGetParam(funcindex, "AC1_FSK_DOWN_SCM");
    CParam *AC1_FSK_HYS = StsGetParam(funcindex, "AC1_FSK_HYS");
    CParam *MOT_AC1_00_ON_TIME_SCM = StsGetParam(funcindex, "MOT_AC1_00_ON_TIME_SCM");
    CParam *MOT_AC1_01_ON_TIME_SCM = StsGetParam(funcindex, "MOT_AC1_01_ON_TIME_SCM");
    CParam *MOT_AC1_10_ON_TIME_SCM = StsGetParam(funcindex, "MOT_AC1_10_ON_TIME_SCM");
    CParam *MOT_AC1_11_ON_TIME_SCM = StsGetParam(funcindex, "MOT_AC1_11_ON_TIME_SCM");
    CParam *MOT_AC2_00_ON_TIME_SCM = StsGetParam(funcindex, "MOT_AC2_00_ON_TIME_SCM");
    CParam *MOT_AC2_01_ON_TIME_SCM = StsGetParam(funcindex, "MOT_AC2_01_ON_TIME_SCM");
    CParam *MOT_AC2_10_ON_TIME_SCM = StsGetParam(funcindex, "MOT_AC2_10_ON_TIME_SCM");
    CParam *MOT_AC2_11_ON_TIME_SCM = StsGetParam(funcindex, "MOT_AC2_11_ON_TIME_SCM");
    CParam *MOFT_AC1_00_OFF_TIME_SCM = StsGetParam(funcindex, "MOFT_AC1_00_OFF_TIME_SCM");
    CParam *MOFT_AC1_01_OFF_TIME_SCM = StsGetParam(funcindex, "MOFT_AC1_01_OFF_TIME_SCM");
    CParam *MOFT_AC1_10_OFF_TIME_SCM = StsGetParam(funcindex, "MOFT_AC1_10_OFF_TIME_SCM");
    CParam *MOFT_AC1_11_OFF_TIME_SCM = StsGetParam(funcindex, "MOFT_AC1_11_OFF_TIME_SCM");
    CParam *MOFT_AC2_00_OFF_TIME_SCM = StsGetParam(funcindex, "MOFT_AC2_00_OFF_TIME_SCM");
    CParam *MOFT_AC2_01_OFF_TIME_SCM = StsGetParam(funcindex, "MOFT_AC2_01_OFF_TIME_SCM");
    CParam *MOFT_AC2_10_OFF_TIME_SCM = StsGetParam(funcindex, "MOFT_AC2_10_OFF_TIME_SCM");
    CParam *MOFT_AC2_11_OFF_TIME_SCM = StsGetParam(funcindex, "MOFT_AC2_11_OFF_TIME_SCM");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here
	cbit.SetOn(K1_AC_CAP, K2_VRECT_V5V_CAP, K4_IIC_PULLUP, K7_SINK_PULLUP, K23_QTMU_SINK, -1);//未使用buffer
	dioplus.I2CConnect();
	wait_relay();

	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_ENTER_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
	else
	{
		TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);
	}
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { TMOD_CTRL, 1 }, { EN_DIG_MUX, 1 }, { MUX_DIG, 0x04 }, { I2C_EN_RECT_LS, 1 }, { TRIM_EN_MOT_MULTI, 1 } });

	AC1.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	SINK.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_ms(1);

	if (Global_Tempchar_Program_Flag == 1)
	{
		AC2.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC2.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
	}
	else
	{
		AC2.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC2.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
	}


	int interval = 10;
	double Trig = 2.5;
	int sam = 400;
	int Trig_Point_R[SITE_NUM] = { 0 };
	int Trig_Point_F[SITE_NUM] = { 0 };

	//AC1 sweep from 0V to -0.2V
	AC1.AwgSelect("AC1_LS_ON", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_FALLING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	AC1.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&AC1);
	STSEnableMeas(&AC1, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &AC1);

	SERIAL
	{
		Trig_Point_F[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
		{
			Trig_Point_F[SITE] = 999;
			COMP_ON_AC1_SCM->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
		}
		else
		{
			adresult1[SITE] = AC1.GetMeasResult(SITE, MVRET, Trig_Point_F[SITE]);
			adresult1[SITE] = adresult1[SITE] * 1e3;//mV
			COMP_ON_AC1_SCM->SetTestResult(SITE, 0, adresult1[SITE]);
		}
	}

	//AC1 sweep from -0.2V to 0.1V
	AC1.AwgSelect("AC1_LS_OFF", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_RISING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	AC1.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&AC1);
	STSEnableMeas(&AC1, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &AC1);

	SERIAL
	{
		Trig_Point_R[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
		{
			Trig_Point_R[SITE] = 999;
			COMP_OFF_AC1_SCM->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
		}
		else
		{
			adresult2[SITE] = AC1.GetMeasResult(SITE, MVRET, Trig_Point_R[SITE]);
			adresult2[SITE] = adresult2[SITE] * 1e3;//mV
			COMP_OFF_AC1_SCM->SetTestResult(SITE, 0, adresult2[SITE]);
		}
	}
	AC1.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);


	//manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { TMOD_CTRL, 1 }, { EN_DIG_MUX, 1 }, { I2C_EN_RECT_LS, 1 }, { TRIM_EN_MOT_MULTI, 1 } });
	manager.setfields({ { MUX_DIG, 0x05 } });
	delay_ms(1);

	AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
	//SINK.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	if (Global_Tempchar_Program_Flag == 1)
	{
		AC1.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC1.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
	}
	else
	{
		AC1.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		AC1.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);
	}


	//AC2 sweep from 0V to -0.2V
	AC2.AwgSelect("AC2_LS_ON", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_FALLING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	AC2.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&AC2);
	STSEnableMeas(&AC2, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &AC2);

	SERIAL
	{
		Trig_Point_F[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
		{
			Trig_Point_F[SITE] = 999;
			COMP_ON_AC2_SCM->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
		}
		else
		{
			adresult1[SITE] = AC2.GetMeasResult(SITE, MVRET, Trig_Point_F[SITE]);
			adresult1[SITE] = adresult1[SITE] * 1e3;//mV
			COMP_ON_AC2_SCM->SetTestResult(SITE, 0, adresult1[SITE]);
		}
	}

	//AC2 sweep from -0.2V to 0.1V
	AC2.AwgSelect("AC2_LS_OFF", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_RISING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	AC2.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&AC2);
	STSEnableMeas(&AC2, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &AC2);

	SERIAL
	{
		Trig_Point_R[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
		{
			Trig_Point_R[SITE] = 999;
			COMP_OFF_AC2_SCM->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
		}
		else
		{
			adresult2[SITE] = AC2.GetMeasResult(SITE, MVRET, Trig_Point_R[SITE]);
			adresult2[SITE] = adresult2[SITE] * 1e3;//mV
			COMP_OFF_AC2_SCM->SetTestResult(SITE, 0, adresult2[SITE]);
		}
	}
	AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	AC1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_1V, FOVI_10MA, RELAY_OFF);
	
	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_EXIT_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_100MA);

		TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);
		manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_RECT_LS, 1 }, { EN_DIG_MUX, 1 }, { MUX_DIG, 0x08 } });
		delay_ms(2);
	}
	else
	{
		manager.setfields({ { MIN_OFF_SET, 0x00 }, { TMOD_CTRL, 0 }, { TRIM_EN_MOT_MULTI, 0 } });
		manager.setfields({/* { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_RECT_LS, 1 }, { EN_DIG_MUX, 1 }, */{ MUX_DIG, 0x08 } });
		delay_ms(2);
	}

	AC1.Set(FV, 2, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	//AC1 sweep from 2V to 4V
	sam = 200;
	AC1.AwgSelect("AC1_FSK_R", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_RISING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	AC1.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&AC1);
	STSEnableMeas(&AC1, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &AC1);

	SERIAL
	{
		Trig_Point_R[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
		{
			Trig_Point_R[SITE] = 999;
			AC1_FSK_UP_SCM->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
		}
		else
		{
			adresult1[SITE] = AC1.GetMeasResult(SITE, MVRET, Trig_Point_R[SITE]);
			AC1_FSK_UP_SCM->SetTestResult(SITE, 0, adresult1[SITE]);
		}
	}

	//AC1 sweep from 4V to 1V
	AC1.AwgSelect("AC1_FSK_F", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_FALLING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	AC1.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&AC1);
	STSEnableMeas(&AC1, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &AC1);

	SERIAL
	{
		Trig_Point_F[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
		{
			Trig_Point_F[SITE] = 999;
			AC1_FSK_DOWN_SCM->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
			AC1_FSK_HYS->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
		}
		else
		{
			adresult2[SITE] = AC1.GetMeasResult(SITE, MVRET, Trig_Point_F[SITE]);
			adresult[SITE] = adresult1[SITE] - adresult2[SITE];
			AC1_FSK_DOWN_SCM->SetTestResult(SITE, 0, adresult2[SITE]);
			AC1_FSK_HYS->SetTestResult(SITE, 0, adresult[SITE]);
		}
	}
	AC1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);

	cbit.SetOn(K1_AC_CAP, K2_VRECT_V5V_CAP, K4_IIC_PULLUP/*, K7_SINK_PULLUP*/, K23_QTMU_SINK, -1);//未使用buffer
	QTMU.Connect();
	wait_relay();

	SINK.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	SINK.SetClamp(12, 12);
	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_ENTER_TEMPCHAR(VRECT,V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
	else
	{
		TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);

	}

	SINK.Set(FV, 1.5, FOVI_5V, FOVI_100MA, RELAY_ON);//上拉
	////////////////////////AC1 Low side minimal On time, 50ns/150ns/300ns/200ns////////////////////////
	CParam *MOT_AC1_X[4] =
	{
		MOT_AC1_00_ON_TIME_SCM, MOT_AC1_01_ON_TIME_SCM, MOT_AC1_10_ON_TIME_SCM, MOT_AC1_11_ON_TIME_SCM,
	};

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { TMOD_CTRL, 1 }, { EN_DIG_MUX, 1 }/*, { I2C_EN_RECT_LS, 1 }, { TRIM_EN_MOT_MULTI, 1 }*/, { MUX_DIG, 0x06 } });
	for (int n = 0; n < 4; n++)
	{
		if (n == 0)
			manager.setfields({ { MOT_SET, 0x00 } });//00, 50ns
		if (n == 1)
			manager.setfields({ { MOT_SET, 0x01 } });//01, 150ns
		if (n == 2)
			manager.setfields({ { MOT_SET, 0x02 } });//10, 300ns
		if (n == 3)
			manager.setfields({ { MOT_SET, 0x03 } });//11, 200ns
		manager.setfields({  { I2C_EN_RECT_LS, 1 }, { TRIM_EN_MOT_MULTI, 1 } });

		AC1.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
		AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		if (Global_Tempchar_Program_Flag == 1)
		{
			AC2.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC2.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON, 1);
			delay_ms(2);
		}
		else
		{
			AC2.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC2.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON, 0.5);
			delay_ms(1);
		}

		QTMU.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
		QTMU.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
		QTMU.SetStartTrigger(0.4, QTMU_PLUS_NEG_SLOPE);//0.25
		QTMU.SetStopTrigger(0.3, QTMU_PLUS_POS_SLOPE);//0.2
		QTMU.SetInSource(QTMU_PLUS_SINGLE_SOURCE);//SINK
		QTMU.SetSinglePulseMeas(QTMU_PLUS_COARSE, QTMU_PLUS_TIME_NS, 0);
		QTMU.SetTimeOut(2);
		//delay_ms(2);

		//AC1 sweep from 0V to -0.2V
		//AC1.AwgSelect("AC1_LS_ON", 0, sam - 1, sam - 1, interval);
		//SINK.SetMeasVTrig(Trig, TRIG_FALLING);
		//SINK.MeasureVI(sam, interval, MEAS_AWG);
		//AC1.MeasureVI(sam, interval, MEAS_AWG);
		//STSEnableAWG(&AC1);
		//STSEnableMeas(&AC1, &SINK);
		//STSAWGRun();
		AC1.Set(FV, -0.2, FOVI_2V, FOVI_10MA, RELAY_ON, 1);
		delay_ms(1);

		QTMU.SinglePlsMeas(0);
		//QTMU.Meas(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 10);//SINK

		SERIAL
		{
			adresult[SITE] = QTMU.GetMeasureResult(SITE);//SINK
			MOT_AC1_X[n] -> SetTestResult(SITE, 0, adresult[SITE] * 1e3);//UNIT: ns
		}

	}

	AC1.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);


	////////////////////////AC1 Low side minimal OFF time, 50ns/120ns/320ns/320ns////////////////////////
	CParam *MOFT_AC1_X[4] =
	{
		MOFT_AC1_00_OFF_TIME_SCM, MOFT_AC1_01_OFF_TIME_SCM, MOFT_AC1_10_OFF_TIME_SCM, MOFT_AC1_11_OFF_TIME_SCM,
	};

	manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { TMOD_CTRL, 1 }, { EN_DIG_MUX, 1 },
			{ MUX_DIG, 0x07 }, { I2C_EN_RECT_LS, 1 }, { TRIM_EN_MOT_MULTI, 1 },*/{ MUX_DIG, 0x07 }, { MOT_SET, 0x00 } });
	for (int n = 0; n < 4; n++)
	{
		if (n == 0)
			manager.setfields({ { MIN_OFF_SET, 0x00 } });//00, 50ns
		if (n == 1)
			manager.setfields({ { MIN_OFF_SET, 0x01 } });//01, 120ns
		if (n == 2)
			manager.setfields({ { MIN_OFF_SET, 0x02 } });//10, 320ns
		if (n == 3)
			manager.setfields({ { MIN_OFF_SET, 0x03 } });//11, 320ns
		delay_ms(1);

		if (Global_Tempchar_Program_Flag == 1)
		{
			AC2.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC2.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON);
		}
		else
		{
			AC2.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC2.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON);
		}

		AC1.Set(FV, -0.2, FOVI_2V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		QTMU.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
		QTMU.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
		QTMU.SetStartTrigger(0.4, QTMU_PLUS_NEG_SLOPE);//0.2
		QTMU.SetStopTrigger(0.3, QTMU_PLUS_POS_SLOPE);//0.2
		QTMU.SetInSource(QTMU_PLUS_SINGLE_SOURCE);//SINK
		QTMU.SetSinglePulseMeas(QTMU_PLUS_COARSE, QTMU_PLUS_TIME_NS, 0);
		QTMU.SetTimeOut(2);
		//delay_ms(2);

		//AC1 sweep from -0.2V to 0.1V
		//AC1.AwgSelect("AC1_LS_OFF", 0, sam - 1, sam - 1, interval);
		//SINK.SetMeasVTrig(Trig, TRIG_FALLING);
		//SINK.MeasureVI(sam, interval, MEAS_AWG);
		//AC1.MeasureVI(sam, interval, MEAS_AWG);
		//STSEnableAWG(&AC1);
		//STSEnableMeas(&AC1, &SINK);
		//STSAWGRun();
		AC1.Set(FV, 1, FOVI_2V, FOVI_10MA, RELAY_ON, 0.5); 
		delay_ms(1);


		QTMU.SinglePlsMeas(0);
		//QTMU.Meas(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 10);//SINK

		SERIAL
		{
			adresult[SITE] = QTMU.GetMeasureResult(SITE);//SINK
			MOFT_AC1_X[n]->SetTestResult(SITE, 0, adresult[SITE] * 1e3);//UNIT: ns
		}

		AC1.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
		AC2.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	}

	delay_ms(1);
	AC2.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);


	////////////////////////AC2 Low side minimal On time, 50ns/150ns/300ns/200ns////////////////////////
	CParam *MOT_AC2_X[4] =
	{
		MOT_AC2_00_ON_TIME_SCM, MOT_AC2_01_ON_TIME_SCM, MOT_AC2_10_ON_TIME_SCM, MOT_AC2_11_ON_TIME_SCM,
	};

	manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { TMOD_CTRL, 1 }, { EN_DIG_MUX, 1 },
			{ MUX_DIG, 0x09 }, { I2C_EN_RECT_LS, 1 }, { TRIM_EN_MOT_MULTI, 1 },*/{ MUX_DIG, 0x09 }, { MIN_OFF_SET, 0x00 } });
	for (int n = 0; n < 4; n++)
	{
		if (n == 0)
			manager.setfields({ { MOT_SET, 0x00 } });//00, 50ns
		if (n == 1)
			manager.setfields({ { MOT_SET, 0x01 } });//01, 150ns
		if (n == 2)
			manager.setfields({ { MOT_SET, 0x02 } });//10, 300ns
		if (n == 3)
			manager.setfields({ { MOT_SET, 0x03 } });//11, 200ns
		delay_ms(1);

		AC2.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
		AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		if (Global_Tempchar_Program_Flag == 1)
		{
			AC1.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON, 0.5);
			delay_us(500);

			AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC1.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON, 0.5);
			delay_ms(1);
		}
		else
		{
			AC1.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON, 0.5);
			delay_us(500);

			AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC1.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON, 0.5);
			delay_ms(1);
		}


		QTMU.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
		QTMU.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
		QTMU.SetStartTrigger(0.4, QTMU_PLUS_NEG_SLOPE);//0.18
		QTMU.SetStopTrigger(0.3, QTMU_PLUS_POS_SLOPE);//0.2
		QTMU.SetInSource(QTMU_PLUS_SINGLE_SOURCE);//SINK
		QTMU.SetSinglePulseMeas(QTMU_PLUS_COARSE, QTMU_PLUS_TIME_NS, 0);
		QTMU.SetTimeOut(2);
		//delay_ms(2);

		//AC2 sweep from 0V to -0.2V
		//AC2.AwgSelect("AC2_LS_ON", 0, sam - 1, sam - 1, interval);
		//SINK.SetMeasVTrig(Trig, TRIG_FALLING);
		//SINK.MeasureVI(sam, interval, MEAS_AWG);
		//AC1.MeasureVI(sam, interval, MEAS_AWG);
		//STSEnableAWG(&AC2);
		//STSEnableMeas(&AC2, &SINK);
		//STSAWGRun();
		AC2.Set(FV, -0.2, FOVI_2V, FOVI_10MA, RELAY_ON, 0.5);
		delay_ms(1);

		QTMU.SinglePlsMeas(0);
		//QTMU.Meas(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 10);//SINK

		SERIAL
		{
			adresult[SITE] = QTMU.GetMeasureResult(SITE);//SINK
			MOT_AC2_X[n]->SetTestResult(SITE, 0, adresult[SITE] * 1e3);//UNIT: ns
		}

	}

	AC2.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	////////////////////////AC2 Low side minimal OFF time, 50ns/120ns/320ns/320ns////////////////////////
	CParam *MOFT_AC2_X[4] =
	{
		MOFT_AC2_00_OFF_TIME_SCM, MOFT_AC2_01_OFF_TIME_SCM, MOFT_AC2_10_OFF_TIME_SCM, MOFT_AC2_11_OFF_TIME_SCM,
	};

	manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { TMOD_CTRL, 1 }, { EN_DIG_MUX, 1 },
						{ MUX_DIG, 0x0A }, { I2C_EN_RECT_LS, 1 }, { TRIM_EN_MOT_MULTI, 1 },*/{ MUX_DIG, 0x0A }, { MOT_SET, 0x00 } });
	for (int n = 0; n < 4; n++)
	{
		if (n == 0)
			manager.setfields({ { MIN_OFF_SET, 0x00 } });//00, 50ns
		if (n == 1)
			manager.setfields({ { MIN_OFF_SET, 0x01 } });//01, 120ns
		if (n == 2)
			manager.setfields({ { MIN_OFF_SET, 0x02 } });//10, 320ns
		if (n == 3)
			manager.setfields({ { MIN_OFF_SET, 0x03 } });//11, 320ns
		delay_ms(1);

		if (Global_Tempchar_Program_Flag == 1)
		{
			AC1.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON, 0.5);
			delay_us(500);

			AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC1.Set(FV, spec("V5V"), FOVI_10V, FOVI_10MA, RELAY_ON, 0.5);
		}
		else
		{
			AC1.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON, 0.5);
			delay_us(500);

			AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
			delay_ms(1);

			AC1.Set(FV, 5.5, FOVI_10V, FOVI_10MA, RELAY_ON, 0.5);
		}

		AC2.Set(FV, -0.2, FOVI_2V, FOVI_10MA, RELAY_ON);
		delay_ms(1);

		QTMU.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
		QTMU.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
		QTMU.SetStartTrigger(0.4, QTMU_PLUS_NEG_SLOPE);//0.18
		QTMU.SetStopTrigger(0.3, QTMU_PLUS_POS_SLOPE);//0.2
		QTMU.SetInSource(QTMU_PLUS_SINGLE_SOURCE);//SINK
		QTMU.SetSinglePulseMeas(QTMU_PLUS_COARSE, QTMU_PLUS_TIME_NS, 0);
		QTMU.SetTimeOut(2);
		//delay_ms(2);

		//AC2 sweep from -0.2V to 0.1V
		//AC2.AwgSelect("AC2_LS_OFF", 0, sam - 1, sam - 1, interval);
		//SINK.SetMeasVTrig(Trig, TRIG_FALLING);
		//SINK.MeasureVI(sam, interval, MEAS_AWG);
		//AC1.MeasureVI(sam, interval, MEAS_AWG);
		//STSEnableAWG(&AC2);
		//STSEnableMeas(&AC2, &SINK);
		//STSAWGRun();
		AC2.Set(FV, 1, FOVI_2V, FOVI_10MA, RELAY_ON, 0.5);
		delay_ms(1);

		QTMU.SinglePlsMeas(0);
		//QTMU.Meas(QTMU_PLUS_COARSE, QTMU_PLUS_TRNG_US, 10);//SINK

		SERIAL
		{
			adresult[SITE] = QTMU.GetMeasureResult(SITE);//SINK
			MOFT_AC2_X[n]->SetTestResult(SITE, 0, adresult[SITE] * 1e3);//UNIT: ns
		}

		AC2.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
		AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
		//delay_ms(1);
	}

	SINK.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);//上拉
	SINK.SetClamp(100, 100);
	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_EXIT_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
	else
	{
		TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_100MA);
	}
	AC2.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	AC1.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	SINK.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_OFF);
	QTMU.Disconnect();

    return 0;
}
 
DUT_API int VRECT_OVP(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *VRECT_DFT_OVP_UP_DS = StsGetParam(funcindex, "VRECT_DFT_OVP_UP_DS");
    CParam *VRECT_DFT_OVP_DOWN = StsGetParam(funcindex, "VRECT_DFT_OVP_DOWN");
    CParam *VRECT_DFT_OVP_HYS_DS = StsGetParam(funcindex, "VRECT_DFT_OVP_HYS_DS");
    CParam *VRECT_OVP1_code0_UP_DS = StsGetParam(funcindex, "VRECT_OVP1_code0_UP_DS");
    CParam *VRECT_OVP1_code0_DOWN = StsGetParam(funcindex, "VRECT_OVP1_code0_DOWN");
    CParam *VRECT_OVP1_code0_HYS_DS = StsGetParam(funcindex, "VRECT_OVP1_code0_HYS_DS");
    CParam *VRECT_OVP1_code1_UP_DS = StsGetParam(funcindex, "VRECT_OVP1_code1_UP_DS");
    CParam *VRECT_OVP1_code1_DOWN = StsGetParam(funcindex, "VRECT_OVP1_code1_DOWN");
    CParam *VRECT_OVP1_code1_HYS_DS = StsGetParam(funcindex, "VRECT_OVP1_code1_HYS_DS");
    CParam *VRECT_OVP2_code0_UP_DS = StsGetParam(funcindex, "VRECT_OVP2_code0_UP_DS");
    CParam *VRECT_OVP2_code0_DOWN = StsGetParam(funcindex, "VRECT_OVP2_code0_DOWN");
    CParam *VRECT_OVP2_code0_HYS_DS = StsGetParam(funcindex, "VRECT_OVP2_code0_HYS_DS");
    CParam *VRECT_OVP2_code1_UP_DS = StsGetParam(funcindex, "VRECT_OVP2_code1_UP_DS");
    CParam *VRECT_OVP2_code1_DOWN = StsGetParam(funcindex, "VRECT_OVP2_code1_DOWN");
    CParam *VRECT_OVP2_code1_HYS_DS = StsGetParam(funcindex, "VRECT_OVP2_code1_HYS_DS");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K7_SINK_PULLUP, -1);
	dioplus.I2CConnect();
	wait_relay();

	TM_ENTER_vi(VRECT, 5.5, FOVI_20V, FOVI_1A);

	manager.setfields({ { I2C_CTRL, 1 }, { EN_DIG_MUX, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { MUX_DIG, 0x0D } });
	SINK.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_ms(1);

	CParam *VRECT_OVP_X[15] =
	{
		VRECT_DFT_OVP_UP_DS, VRECT_DFT_OVP_DOWN, VRECT_DFT_OVP_HYS_DS,
		VRECT_OVP1_code0_UP_DS, VRECT_OVP1_code0_DOWN, VRECT_OVP1_code0_HYS_DS,
		VRECT_OVP1_code1_UP_DS, VRECT_OVP1_code1_DOWN, VRECT_OVP1_code1_HYS_DS,
		VRECT_OVP2_code0_UP_DS, VRECT_OVP2_code0_DOWN, VRECT_OVP2_code0_HYS_DS,
		VRECT_OVP2_code1_UP_DS, VRECT_OVP2_code1_DOWN, VRECT_OVP2_code1_HYS_DS,
	};

	int interval = 10;
	double Trig = 2.5;
	int sam = 200;
	int Trig_Point_F[SITE_NUM] = { 0 };
	int Trig_Point_R[SITE_NUM] = { 0 };

	for (int n = 0; n < 5; n++)
	{
		
		if (n == 1) 
			manager.setfields({ { FORCE_SINK_OFF, 1 }, { I2C_EN_OVP, 1 }, { MUX_DIG, 0x0E }, { VRECT_OVP1_THD, 0 } });
		if (n == 2)	
			manager.setfields({ /*{ FORCE_SINK_OFF, 1 }, { I2C_EN_OVP, 1 }, { MUX_DIG, 0x0E }, */{ VRECT_OVP1_THD, 1 } });
		if (n == 3)	
			manager.setfields({ { I2C_DIS_OVP_FAST, 1 }, /*{ FORCE_SINK_OFF, 1 }, { I2C_EN_OVP, 1 },*/ { MUX_DIG, 0x0F }, { VRECT_OVP2_THD, 0 } });
		if (n == 4)
			manager.setfields({ /*{ I2C_DIS_OVP_FAST, 1 }, { FORCE_SINK_OFF, 1 }, { I2C_EN_OVP, 1 }, { MUX_DIG, 0x0F }, */{ VRECT_OVP2_THD, 1 } });
		VRECT.Set(FV, 9.5, FOVI_20V, FOVI_1A, RELAY_ON, 0.5);
		delay_ms(1);
	
		//VRECT sweep from 9.5V to 17V
		VRECT.AwgSelect("VRECT_OVP_R", 0, sam - 1, sam - 1, interval);
		SINK.SetMeasVTrig(Trig, TRIG_FALLING);
		SINK.MeasureVI(sam, interval, MEAS_AWG);
		VRECT.MeasureVI(sam, interval, MEAS_AWG);
		STSEnableAWG(&VRECT);
		STSEnableMeas(&VRECT, &SINK);
		STSAWGRunTriggerStop(&SINK, &SINK, &VRECT);
		//STSAWGRun();

		SERIAL
		{
			Trig_Point_R[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
			if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
			{
				Trig_Point_R[SITE] = 999;
				VRECT_OVP_X[3 * n + 0]->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
			}
			else
			{
				adresult1[SITE] = VRECT.GetMeasResult(SITE, MVRET, Trig_Point_R[SITE]);
				VRECT_OVP_X[3 * n + 0]->SetTestResult(SITE, 0, adresult1[SITE]);
			}
		}
		VRECT.Set(FV, 13, FOVI_20V, FOVI_1A, RELAY_ON, 1);
		delay_ms(1);
		//VRECT sweep from 13V to 5.5V
		VRECT.AwgSelect("VRECT_OVP_F", 0, sam - 1, sam - 1, interval);
		SINK.SetMeasVTrig(Trig, TRIG_RISING);
		SINK.MeasureVI(sam, interval, MEAS_AWG);
		VRECT.MeasureVI(sam, interval, MEAS_AWG);
		STSEnableAWG(&VRECT);
		STSEnableMeas(&VRECT, &SINK);
		STSAWGRunTriggerStop(&SINK, &SINK, &VRECT);
		SERIAL
		{
			Trig_Point_F[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
			if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
			{
				Trig_Point_F[SITE] = 999;
				VRECT_OVP_X[3 * n + 1]->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
				VRECT_OVP_X[3 * n + 2]->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
			}
			else
			{
				adresult2[SITE] = VRECT.GetMeasResult(SITE, MVRET, Trig_Point_F[SITE]);
				adresult[SITE] = adresult1[SITE] - adresult2[SITE];
				VRECT_OVP_X[3 * n + 1]->SetTestResult(SITE, 0, adresult2[SITE]);
				VRECT_OVP_X[3 * n + 2]->SetTestResult(SITE, 0, adresult[SITE]);
			}
		}

		VRECT.Set(FV, 5.5, FOVI_20V, FOVI_1A, RELAY_ON);
		delay_ms(1);
	}

	if (POWER_FLAG)
	{
		TM_EXIT_vi(VRECT, 5.5, FOVI_20V, FOVI_1A);
		SINK.Set(FV, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
		delay_ms(1);
		SINK.Set(FV, 0, FOVI_10V, FOVI_100UA, RELAY_OFF);
		delay_ms(1);
	}
	else
	{
		TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
	}
	return 0;
}
 
DUT_API int MLDO_TEST(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *VOUT_SCP_UP = StsGetParam(funcindex, "VOUT_SCP_UP");
    CParam *VOUT_SCP_DOWN_DS = StsGetParam(funcindex, "VOUT_SCP_DOWN_DS");
    CParam *VOUT_SCP_HYS_DS = StsGetParam(funcindex, "VOUT_SCP_HYS_DS");
    CParam *VOUT_GD_UP = StsGetParam(funcindex, "VOUT_GD_UP");
    CParam *VOUT_GD_DOWN = StsGetParam(funcindex, "VOUT_GD_DOWN");
    CParam *VOUT_GD_HYS = StsGetParam(funcindex, "VOUT_GD_HYS");
    CParam *VSP_VRECTM5_UP = StsGetParam(funcindex, "VSP_VRECTM5_UP");
    CParam *VSP_VRECTM5_DOWN = StsGetParam(funcindex, "VSP_VRECTM5_DOWN");
    CParam *VSP_VRECTM5_HYS = StsGetParam(funcindex, "VSP_VRECTM5_HYS");
    CParam *VREF_2V = StsGetParam(funcindex, "VREF_2V");
    CParam *VCP_1OF10 = StsGetParam(funcindex, "VCP_1OF10");
    CParam *VREF_VOUT = StsGetParam(funcindex, "VREF_VOUT");
    CParam *VOUT_ACC_3P5V_DS = StsGetParam(funcindex, "VOUT_ACC_3P5V_DS");
    CParam *VOUT_ACC_5V_DS = StsGetParam(funcindex, "VOUT_ACC_5V_DS");
    CParam *VOUT_ACC_9V_DS = StsGetParam(funcindex, "VOUT_ACC_9V_DS");
    CParam *VOUT_AEG_DS = StsGetParam(funcindex, "VOUT_AEG_DS");
    CParam *VOUT_STEP_DS = StsGetParam(funcindex, "VOUT_STEP_DS");
    CParam *VOUT_DROP_SCM = StsGetParam(funcindex, "VOUT_DROP_SCM");
    CParam *VOUT_DUMMY_LOAD = StsGetParam(funcindex, "VOUT_DUMMY_LOAD");
    CParam *VOUT_LOAD_UP = StsGetParam(funcindex, "VOUT_LOAD_UP");
    CParam *VOUT_LOAD_DOWN = StsGetParam(funcindex, "VOUT_LOAD_DOWN");
    CParam *VOUT_LOAD_HYS = StsGetParam(funcindex, "VOUT_LOAD_HYS");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	if (POWER_FLAG)
	{
		cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP/*, K3_VOUT_CAP*/, K7_SINK_PULLUP, -1);
		dioplus.I2CConnect();
		wait_relay();
		SINK.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	}

	VOUT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_us(200);

	VOUT.Set(FV, 5.5, FOVI_10V, FOVI_100MA, RELAY_ON);
	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
	else
	{
		TM_ENTER_vi(V5V, 5.5, FOVI_10V, FOVI_100MA);
	}
	manager.setfields({ { I2C_CTRL, 1 }, { EN_DIG_MUX, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_LDO_PWR, 1 }, { I2C_EN_OSC, 1 }, { MUX_DIG, 0x10 } });
	//VOUT.Set(FV, 4.5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);

	int interval = 10;
	double Trig = 2.5;
	int sam = 100;
	int Trig_Point_F[SITE_NUM] = { 0 };
	int Trig_Point_R[SITE_NUM] = { 0 };

	//VOUT sweep from 3V to 1.5V
	VOUT.AwgSelect("VOUT_SCP_F", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_FALLING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	VOUT.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&VOUT);
	STSEnableMeas(&VOUT, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &VOUT);
	SERIAL
	{
		Trig_Point_F[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
		{
			Trig_Point_F[SITE] = 999;
			VOUT_SCP_DOWN_DS->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
		}
		else
		{
			adresult1[SITE] = VOUT.GetMeasResult(SITE, MVRET, Trig_Point_F[SITE]);
			VOUT_SCP_DOWN_DS->SetTestResult(SITE, 0, adresult1[SITE]);
		}
	}
	//VOUT.Set(FV, 1.5, FOVI_10V, FOVI_100MA, RELAY_ON);
	//delay_ms(2);
	//VOUT sweep from 1.5V to 3V
	VOUT.AwgSelect("VOUT_SCP_R", 0, sam - 1, sam - 1, interval);
	SINK.SetMeasVTrig(Trig, TRIG_RISING);
	SINK.MeasureVI(sam, interval, MEAS_AWG);
	VOUT.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&VOUT);
	STSEnableMeas(&VOUT, &SINK);
	STSAWGRunTriggerStop(&SINK, &SINK, &VOUT);
	SERIAL
	{
		Trig_Point_R[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
		{
			Trig_Point_R[SITE] = 999;
			VOUT_SCP_UP->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
			VOUT_SCP_HYS_DS->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
		}
		else
		{
			adresult2[SITE] = VOUT.GetMeasResult(SITE, MVRET, Trig_Point_R[SITE]);
			adresult[SITE] = adresult2[SITE] - adresult1[SITE];
			VOUT_SCP_UP->SetTestResult(SITE, 0, adresult2[SITE]);
			VOUT_SCP_HYS_DS->SetTestResult(SITE, 0, adresult[SITE]);
		}
	}
	SINK.Set(FV, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	//VOUT.Set(FV, 4.5, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_us(200);
	SINK.Set(FV, 0, FOVI_10V, FOVI_100UA, RELAY_OFF);
	INTB.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	VOUT.Set(FV, 3.5, FOVI_10V, FOVI_100MA, RELAY_ON);

	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	}
	manager.setfields({ { I2C_CTRL, 1 }, { EN_ANA_MUX, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_LDO_PWR, 1 }, { I2C_EN_OSC, 1 }, { TMOD_CTRL, 0x0D } });
	delay_ms(1);

	if (spec("V5V") == 3.3)
	{
		Trig = 1.5;
	}
	//VOUT sweep from 3.5V to 2.5V
	VOUT.AwgSelect("VOUT_GD_F", 0, sam - 1, sam - 1, interval);
	INTB.SetMeasVTrig(Trig, TRIG_FALLING);
	INTB.MeasureVI(sam, interval, MEAS_AWG);
	VOUT.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&VOUT);
	STSEnableMeas(&VOUT, &INTB);
	STSAWGRunTriggerStop(&INTB, &INTB, &VOUT);
	SERIAL
	{
		Trig_Point_F[SITE] = int(INTB.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
		{
			Trig_Point_F[SITE] = 999;
			VOUT_GD_DOWN->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
		}
		else
		{
			adresult1[SITE] = VOUT.GetMeasResult(SITE, MVRET, Trig_Point_F[SITE]);
			VOUT_GD_DOWN->SetTestResult(SITE, 0, adresult1[SITE]);
		}
	}

	//VOUT sweep from 2.5V to 3.5V
	VOUT.AwgSelect("VOUT_GD_R", 0, sam - 1, sam - 1, interval);
	INTB.SetMeasVTrig(Trig, TRIG_RISING);
	INTB.MeasureVI(sam, interval, MEAS_AWG);
	VOUT.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&VOUT);
	STSEnableMeas(&VOUT, &INTB);
	STSAWGRunTriggerStop(&INTB, &INTB, &VOUT);
	SERIAL
	{
		Trig_Point_R[SITE] = int(INTB.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
		{
			Trig_Point_R[SITE] = 999;
			VOUT_GD_UP->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
			VOUT_GD_HYS->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
		}
		else
		{
			adresult2[SITE] = VOUT.GetMeasResult(SITE, MVRET, Trig_Point_R[SITE]);
			adresult[SITE] = adresult2[SITE] - adresult1[SITE];
			VOUT_GD_UP->SetTestResult(SITE, 0, adresult2[SITE]);
			VOUT_GD_HYS->SetTestResult(SITE, 0, adresult[SITE]);
		}
	}

	if (spec("V5V") == 3.3)
	{
		Trig = 2.5;
	}
	TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	VOUT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	VOUT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);


	TM_ENTER_vi(VRECT, 5.1, FOVI_10V, FOVI_100MA);

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { EN_ANA_MUX, 1 }, { I2C_EN_VCP, 1 }, { MUX_ANA, 0x03 } });
	delay_ms(1);

	//VRECT sweep from 5.1V to 5.8V
	VRECT.AwgSelect("VSP_VRECTM5_R", 0, sam - 1, sam - 1, interval);
	INTB.SetMeasVTrig(Trig, TRIG_FALLING);
	INTB.MeasureVI(sam, interval, MEAS_AWG);
	VRECT.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&VRECT);
	STSEnableMeas(&VRECT, &INTB);
	STSAWGRunTriggerStop(&INTB, &INTB, &VRECT);
	SERIAL
	{
		Trig_Point_R[SITE] = int(INTB.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
		{
			Trig_Point_R[SITE] = 999;
			VSP_VRECTM5_UP->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
		}
		else
		{
			adresult1[SITE] = VRECT.GetMeasResult(SITE, MVRET, Trig_Point_R[SITE]);
			VSP_VRECTM5_UP->SetTestResult(SITE, 0, adresult1[SITE]);
		}
	}

	//VRECT sweep from 5.5V to 4.8V
	VRECT.AwgSelect("VSP_VRECTM5_F", 0, sam - 1, sam - 1, interval);
	INTB.SetMeasVTrig(Trig, TRIG_RISING);
	INTB.MeasureVI(sam, interval, MEAS_AWG);
	VRECT.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&VRECT);
	STSEnableMeas(&VRECT, &INTB);
	STSAWGRunTriggerStop(&INTB, &INTB, &VRECT);
	SERIAL
	{
		Trig_Point_F[SITE] = int(INTB.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
		{
			Trig_Point_F[SITE] = 999;
			VSP_VRECTM5_DOWN->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
			VSP_VRECTM5_HYS->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
		}
		else
		{
			adresult2[SITE] = VRECT.GetMeasResult(SITE, MVRET, Trig_Point_F[SITE]);
			adresult[SITE] = adresult1[SITE] - adresult2[SITE];
			VSP_VRECTM5_DOWN->SetTestResult(SITE, 0, adresult2[SITE]);
			VSP_VRECTM5_HYS->SetTestResult(SITE, 0, adresult[SITE]);
		}
	}
	TM_EXIT_vi(VRECT, 5.1, FOVI_10V, FOVI_100MA);

	//VRECT.Set(FV, 5.5, FOVI_10V, FOVI_100MA, RELAY_ON, 1);
	TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { EN_ANA_MUX, 1 }, { MUX_ANA, 0x07 } });
	delay_ms(1);

	if (Global_Tempchar_Program_Flag == 1)
	{
		delay_ms(5);
	}

	INTB.MeasureVI(20, 10);
	SERIAL
	{
		adresult[SITE] = INTB.GetMeasResult(SITE, MVRET);
		VREF_2V->SetTestResult(SITE, 0, adresult[SITE]);
	}
	TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	INTB.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_OFF);

	cbit.SetOn(K4_IIC_PULLUP, -1);//FPVI H_PGND, FPVI L_VOUT
	Qvm.Connect();
	wait_relay();

	INTB.Set(FI, 0, FOVI_2V, FOVI_1UA, RELAY_OFF);
	TM_ENTER_vi(VRECT, 5.7, FOVI_10V, FOVI_100MA);

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { EN_ANA_MUX, 1 }, { I2C_EN_VCP, 1 }, { MUX_ANA, 0x04 } });
	delay_ms(5);//need

	VRECT.MeasureVI(20, 10);
	//INTB.MeasureVI(20, 10);
	

	Qvm.MeasureLADC(50, 10, QVM_LADC_2V, QVM_LADC_40KHz, MEAS_NORMAL);
	SERIAL	adresult0[SITE] = Qvm.GetMeasResult(SITE, AVERAGE_RESULT);
	
	SERIAL
	{
		//adresult0[SITE] = INTB.GetMeasResult(SITE, MVRET);
		adresult1[SITE] = VRECT.GetMeasResult(SITE, MVRET);

		adresult[SITE] = adresult0[SITE] * 10 - adresult1[SITE];

		VCP_1OF10->SetTestResult(SITE, 0, adresult[SITE]);
	}

	Qvm.Disconnect();
	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	INTB.Set(FI, 0, FOVI_2V, FOVI_1UA, RELAY_ON);
	delay_ms(1);


	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K3_VOUT_CAP, K17_PVI0L_VOUT, K13_PVI0H_PGND, -1);//FPVI H_PGND, FPVI L_VOUT
	wait_relay();
	
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//PGND-VOUT
	TM_ENTER_vi(VRECT, 5.5, FOVI_20V, FOVI_1A);

	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { EN_ANA_MUX, 1 }, { I2C_EN_VCP, 1 },
		{ I2C_DIS_SS, 1 }, { I2C_EN_LDO_PWR, 1 }, { I2C_REF_IN, 0x80 }, { MUX_ANA, 0x06 } });

	FPVI0.Set(FI, 0.5, FPVI10_10V, FPVI10_1A, RELAY_ON);//PGND-VOUT
	delay_ms(2);
	INTB.MeasureVI(20, 10);
	SERIAL
	{
		adresult[SITE] = INTB.GetMeasResult(SITE, MVRET);
		VREF_VOUT->SetTestResult(SITE, 0, adresult[SITE]);
	}
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//PGND-VOUT
	INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(1);
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);//PGND-VOUT
	INTB.Set(FV, 0, FOVI_2V, FOVI_100UA, RELAY_OFF);
	delay_us(500);


	if (Global_Tempchar_Program_Flag == 1)
	{
		VRECT.Set(FV, spec("VRECT"), FOVI_20V, FOVI_1A, RELAY_ON, 0.5);
	}
	manager.setfields({/* { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_VCP, 1 },
		{ I2C_DIS_SS, 1 }, { I2C_EN_LDO_PWR, 1 }, { I2C_REF_IN, 0x80 },*/ { MUX_ANA, 0 }, { EN_ANA_MUX, 0 }});
	
	FPVI0.Set(FI, 0.001, FPVI10_10V, FPVI10_100MA, RELAY_ON);//PGND-VOUT
	delay_ms(1);
	FPVI0.MeasureVI(20, 10);
	SERIAL
	{
		adresult1[SITE] = FPVI0.GetMeasResult(SITE, MVRET);//PGND-VOUT
		adresult1[SITE] = -adresult1[SITE];
		VOUT_ACC_5V_DS->SetTestResult(SITE, 0, adresult1[SITE]);
	}
	FPVI0.Set(FI, 0.01, FPVI10_10V, FPVI10_100MA, RELAY_ON);//PGND-VOUT
	manager.setfields({{ I2C_REF_IN, 0x5A } });//8b'01011010 vout=3.5V
	delay_ms(1);
	FPVI0.MeasureVI(20, 10);
	SERIAL
	{
		adresult2[SITE] = FPVI0.GetMeasResult(SITE, MVRET);//PGND-VOUT
		adresult2[SITE] = -adresult2[SITE];
		VOUT_ACC_3P5V_DS->SetTestResult(SITE, 0, adresult2[SITE]);
	}

	manager.setfields({ { I2C_REF_IN, 0xE6 } });//8b'11100110 vout=9V
	
	if (Global_Tempchar_Program_Flag == 1)
	{
		VRECT.Set(FV, spec("VRECT") + 4, FOVI_20V, FOVI_1A, RELAY_ON, 0.5);//9.2V,10.2V,11V

	}
	else
	{
		VRECT.Set(FV, 9.5, FOVI_20V, FOVI_1A, RELAY_ON, 0.5);
	}
	delay_ms(1);
	FPVI0.MeasureVI(20, 10);
	SERIAL
	{
		adresult3[SITE] = FPVI0.GetMeasResult(SITE, MVRET);//PGND-VOUT
		adresult3[SITE] = -adresult3[SITE];
		VOUT_ACC_9V_DS->SetTestResult(SITE, 0, adresult3[SITE]);
	}

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);//PGND-VOUT
	delay_ms(1);
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_10A, RELAY_ON);//PGND-VOUT
	FPVI0.SetClamp(60, 60);
	delay_us(500);
	VRECT.Set(FV, VRECT_Volt, FOVI_20V, FOVI_1A, RELAY_ON, 0.5);
	delay_us(500);

	VRECT.Set(FV, VRECT_Volt, FOVI_10V, FOVI_1A, RELAY_ON);
	delay_us(500);
	manager.setfields({ { I2C_REF_IN, 0x80 } });//8'b10000000 vout=5V
	FPVI0.Set(FI, 1, FPVI10_10V, FPVI10_10A, RELAY_ON);//PGND-VOUT
	delay_ms(2);
	FPVI0.MeasureVI(20, 10);
	SERIAL
	{
		adresult[SITE] = FPVI0.GetMeasResult(SITE, MVRET);//PGND-VOUT
		adresult[SITE] = -adresult[SITE];
		VOUT_AEG_DS->SetTestResult(SITE, 0, adresult[SITE]);
	}
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_10A, RELAY_ON);//PGND-VOUT
	delay_ms(2);

	if (spec("VRECT") == 5.2)
	{
		manager.setfields({ { I2C_REF_IN, 0x76 } });//8'b01110110,temp char低压set
	}
	FPVI0.Set(FI, 0.5, FPVI10_10V, FPVI10_10A, RELAY_ON);//PGND-VOUT
	delay_ms(2);
	FPVI0.MeasureVI(20, 10);
	SERIAL adresult1[SITE] = FPVI0.GetMeasResult(SITE, MVRET);//PGND-VOUT

	if (spec("VRECT") == 5.2)
	{
		manager.setfields({ { I2C_REF_IN, 0x80 } });//10000000,temp char低压set
	}
	else
	{
		manager.setfields({ { I2C_REF_IN, 0x8A } });//10001010
	}
	delay_ms(2);
	FPVI0.MeasureVI(20, 10);
	SERIAL
	{
		adresult2[SITE] = FPVI0.GetMeasResult(SITE, MVRET);//PGND-VOUT
		adresult[SITE] = -(adresult2[SITE] - adresult1[SITE]) / 10 * 1e3;// unit: mV
		VOUT_STEP_DS->SetTestResult(SITE, 0, adresult[SITE]);
	}
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_10A, RELAY_ON);//PGND-VOUT
	delay_ms(1);

	
	if (Global_Tempchar_Program_Flag == 1)
	{
		FPVI0.SetClamp(80, 80);
		manager.setfields({/* { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_VCP, 1 },
						   { I2C_DIS_SS, 1 }, { I2C_EN_LDO_PWR, 1 },*/{ I2C_REF_IN, 0xC0 } }); //TEMP CHAR set
		VRECT.Set(FV, spec("VRECT"), FOVI_10V, FOVI_1A, RELAY_ON, 0.1);
	}
	else
	{
		manager.setfields({/* { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_VCP, 1 },
						   { I2C_DIS_SS, 1 }, { I2C_EN_LDO_PWR, 1 },*/{ I2C_REF_IN, 0x83 } }); //set VOUT=5.12V
		VRECT.Set(FV, 5, FOVI_10V, FOVI_1A, RELAY_ON, 0.1);
	}
	FPVI0.Set(FI, 1, FPVI10_10V, FPVI10_10A, RELAY_ON);//PGND-VOUT
	delay_ms(2);
	FPVI0.MeasureVI(20, 10);
	VRECT.MeasureVI(20, 10);

	SERIAL
	{
		adresult0[SITE] = FPVI0.GetMeasResult(SITE, MVRET);//PGND-VOUT
		adresult1[SITE] = VRECT.GetMeasResult(SITE, MVRET);
		adresult2[SITE] = FPVI0.GetMeasResult(SITE, MIRET);//PGND-VOUT
		adresult[SITE] = (adresult1[SITE] - (-adresult0[SITE])) / (adresult2[SITE] + 1e-32)* 1e3;// FT

		VOUT_DROP_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_10A, RELAY_ON);//PGND-VOUT
	delay_ms(1);
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//PGND-VOUT
	delay_ms(1);

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);//PGND-VOUT
	FPVI0.SetClamp(100, 100);
	//VRECT.Set(FV, 5.5, FOVI_10V, FOVI_1A, RELAY_ON);
	delay_ms(1);

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_100MA, RELAY_OFF);//PGND-VOUT

	if (POWER_FLAG)
	{
		TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
		cbit.SetOn(K4_IIC_PULLUP, K6_INTB_PULLUP, K2_VRECT_V5V_CAP, K3_VOUT_CAP, -1);
		wait_relay();
		TM_ENTER_vi(VRECT, 9.5, FOVI_10V, FOVI_100MA);
	}
	else
	{
		cbit.SetOn(K4_IIC_PULLUP, K6_INTB_PULLUP, K2_VRECT_V5V_CAP, K3_VOUT_CAP, -1);
		wait_relay();
		VRECT.Set(FV, 9.5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	}
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_VCP, 1 },
	{ I2C_DIS_SS, 1 }, { I2C_EN_LDO_PWR, 1 }, { I2C_REF_IN, 0xe6 } });//8b'11100110,vout=9V
	delay_ms(3);//NEED WAIT
	VRECT.MeasureVI(50, 10);
	SERIAL adresult1[SITE] = VRECT.GetMeasResult(SITE, MIRET);

	manager.setfields({ { VOUT_DMY_EN, 1 } });
	delay_ms(1);
	VRECT.MeasureVI(50, 10);
	SERIAL
	{
		adresult2[SITE] = VRECT.GetMeasResult(SITE, MIRET);
		adresult[SITE] = (adresult2[SITE] - adresult1[SITE])* 1e3;//mA
		VOUT_DUMMY_LOAD->SetTestResult(SITE, 0, adresult[SITE]);
	}

	VRECT.Set(FV, 5.5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);

	manager.historyClear();//clear history value

	VRECT.Set(FV, 5.5, FOVI_10V, FOVI_1A, RELAY_ON);
	VOUT.Set(FI, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	INTB.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_ms(1); 
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_DIS_SS, 1 }, { I2C_EN_VCP, 1 },
			{ EN_ANA_MUX, 1 }, { I2C_EN_LDO_PWR, 1 }, { I2C_REF_IN, 0x80 }, { TMOD_CTRL, 0x0E } });
	delay_ms(1);

	interval = 20;
	Trig = 4.9; //INTB 4.6V~5.1V
	sam = 200;
	//VOUT sweep from 0A to -0.5A
	VOUT.AwgSelect("LOAD_300mA_R", 0, sam - 1, sam - 1, interval);
	INTB.SetMeasVTrig(Trig, TRIG_RISING);
	INTB.MeasureVI(sam, interval, MEAS_AWG);
	VOUT.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&VOUT);
	STSEnableMeas(&VOUT, &INTB);
	STSAWGRunTriggerStop(&INTB, &INTB, &VOUT);
	SERIAL
	{
		Trig_Point_R[SITE] = int(INTB.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
		{
			Trig_Point_R[SITE] = 999;
			VOUT_LOAD_UP->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
		}
		else
		{
			adresult1[SITE] = VOUT.GetMeasResult(SITE, MIRET, Trig_Point_R[SITE]);
			VOUT_LOAD_UP->SetTestResult(SITE, 0, -adresult1[SITE]);//sourcing current
		}
	}

	//VOUT sweep from -0.5A to 0A
	VOUT.AwgSelect("LOAD_300mA_F", 0, sam - 1, sam - 1, interval);
	INTB.SetMeasVTrig(Trig, TRIG_FALLING);
	INTB.MeasureVI(sam, interval, MEAS_AWG);
	VOUT.MeasureVI(sam, interval, MEAS_AWG);
	STSEnableAWG(&VOUT);
	STSEnableMeas(&VOUT, &INTB);
	STSAWGRunTriggerStop(&INTB, &INTB, &VOUT);
	SERIAL
	{
		Trig_Point_F[SITE] = int(INTB.GetMeasResult(SITE, MVRET, TRIG_RESULT));
		if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
		{
			Trig_Point_F[SITE] = 999;
			VOUT_LOAD_DOWN->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
			VOUT_LOAD_HYS->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
		}
		else
		{
			adresult2[SITE] = VOUT.GetMeasResult(SITE, MIRET, Trig_Point_F[SITE]);
			adresult[SITE] = adresult2[SITE] - adresult1[SITE];
			VOUT_LOAD_DOWN->SetTestResult(SITE, 0, -adresult2[SITE]);//sourcing current
			VOUT_LOAD_HYS->SetTestResult(SITE, 0, adresult[SITE]);
		}
	}
	VOUT.Set(FI, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	INTB.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_ms(1);

	TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
	VOUT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_ON);
	INTB.Set(FV, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_us(500);

	dioplus.I2CDisconnect();
	VOUT.Set(FV, 0, FOVI_10V, FOVI_1A, RELAY_OFF);
	INTB.Set(FV, 0, FOVI_10V, FOVI_100UA, RELAY_OFF);
	delay_us(500);

    return 0;
}

DUT_API int IOUT_OCP(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *IOUT_OCP_00_UP_DS = StsGetParam(funcindex, "IOUT_OCP_00_UP_DS");
    CParam *IOUT_OCP_00_DOWN = StsGetParam(funcindex, "IOUT_OCP_00_DOWN");
    CParam *IOUT_OCP_00_HYS_DS = StsGetParam(funcindex, "IOUT_OCP_00_HYS_DS");
    CParam *IOUT_OCP_01_UP_DS = StsGetParam(funcindex, "IOUT_OCP_01_UP_DS");
    CParam *IOUT_OCP_01_DOWN = StsGetParam(funcindex, "IOUT_OCP_01_DOWN");
    CParam *IOUT_OCP_01_HYS_DS = StsGetParam(funcindex, "IOUT_OCP_01_HYS_DS");
    CParam *IOUT_OCP_10_UP_DS = StsGetParam(funcindex, "IOUT_OCP_10_UP_DS");
    CParam *IOUT_OCP_10_DOWN = StsGetParam(funcindex, "IOUT_OCP_10_DOWN");
    CParam *IOUT_OCP_10_HYS_DS = StsGetParam(funcindex, "IOUT_OCP_10_HYS_DS");
    CParam *IOUT_OCP_11_UP_DS = StsGetParam(funcindex, "IOUT_OCP_11_UP_DS");
    CParam *IOUT_OCP_11_DOWN = StsGetParam(funcindex, "IOUT_OCP_11_DOWN");
    CParam *IOUT_OCP_11_HYS_DS = StsGetParam(funcindex, "IOUT_OCP_11_HYS_DS");
//}}AFX_STS_PARAM_PROTOTYPES
	// TODO: Add your function code here
	double analog_meas[SITE_COUNT] = { 0.0 };
	double cal_out1[SITE_COUNT] = { 0.0 };
	double cal_out2[SITE_COUNT] = { 0.0 };

	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, K3_VOUT_CAP, K7_SINK_PULLUP, K17_PVI0L_VOUT, K13_PVI0H_PGND, -1);//FPVI H_PGND, FPVI L_VOUT
	dioplus.I2CConnect();
	wait_relay();

	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_ENTER_TEMPCHAR(VRECT,V5V, spec("V5V"), FOVI_10V, FOVI_1A);
	}
	else
	{
		TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
	}

	manager.setfields({ { I2C_CTRL, 1 }, { EN_DIG_MUX, 1 }, { I2C_DIS_SS, 0x08 }, { I2C_EN_LDO1, 1 }, { I2C_EN_VCP, 1 }, { I2C_EN_LDO_PWR, 1 }, { I2C_REF_IN, 0x80 }, { I2C_EN_OSC, 1 }, { MUX_DIG, 0x11 } });
	delay_ms(1);

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);//PGND-VOUT
	SINK.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);//VOUT
	VOUT.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	delay_us(200);
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//PGND-VOUT
	delay_ms(1);

	CParam *IOUT_OCP_X[6] =
	{
		IOUT_OCP_01_UP_DS, IOUT_OCP_01_DOWN, IOUT_OCP_01_HYS_DS,
		IOUT_OCP_10_UP_DS, IOUT_OCP_10_DOWN, IOUT_OCP_10_HYS_DS,
	};

	int interval = 10;
	double Trig = 2.5;
	int sam = 200;
	int Trig_Point_F[SITE_NUM] = { 0 };
	int Trig_Point_R[SITE_NUM] = { 0 };

// 	for (int n = 0; n < 2; n++)
// 	{
// 		if (n == 0)
// 			manager.setfields({ { LDO_OCP_THD, 0x01 } });//01, 0.6A
// 		if (n == 1)
// 			manager.setfields({ { LDO_OCP_THD, 0x02 } });//10, 0.8A
// 		delay_ms(3);
// 
// 		//PGND-VOUT sweep from 0A to 1A
// 		FPVI0.AwgSelect("IOUT_OCP_R", 0, sam - 1, sam - 1, interval);
// 		SINK.SetMeasVTrig(Trig, TRIG_FALLING);
// 		SINK.MeasureVI(sam, interval, MEAS_AWG);
// 		FPVI0.MeasureVI(sam, interval, MEAS_AWG);
// 		STSEnableAWG(&FPVI0);
// 		STSEnableMeas(&FPVI0, &SINK);
// 		STSAWGRunTriggerStop(&SINK, &SINK, &FPVI0);
// 		//STSAWGRun();
// 		SERIAL
// 		{
// 			Trig_Point_R[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
// 			if (Trig_Point_R[SITE]<0 || Trig_Point_R[SITE]>sam - 1)
// 			{
// 				Trig_Point_R[SITE] = 999;
// 				IOUT_OCP_X[3 * n + 0]->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
// 			}
// 			else
// 			{
// 				adresult1[SITE] = FPVI0.GetMeasResult(SITE, MIRET, Trig_Point_R[SITE]);
// 				IOUT_OCP_X[3 * n + 0]->SetTestResult(SITE, 0, adresult1[SITE]);
// 			}
// 		}
// 
// 		//PGND-VOUT sweep from 1A to 0A
// 		FPVI0.AwgSelect("IOUT_OCP_F", 0, sam - 1, sam - 1, interval);
// 		SINK.SetMeasVTrig(Trig, TRIG_RISING);
// 		SINK.MeasureVI(sam, interval, MEAS_AWG);
// 		FPVI0.MeasureVI(sam, interval, MEAS_AWG);
// 		STSEnableAWG(&FPVI0);
// 		STSEnableMeas(&FPVI0, &SINK);
// 		STSAWGRunTriggerStop(&SINK, &SINK, &FPVI0);
// 		SERIAL
// 		{
// 			Trig_Point_F[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
// 			if (Trig_Point_F[SITE]<0 || Trig_Point_F[SITE]>sam - 1)
// 			{
// 				Trig_Point_F[SITE] = 999;
// 				IOUT_OCP_X[3 * n + 1]->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
// 				IOUT_OCP_X[3 * n + 2]->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
// 			}
// 			else
// 			{
// 				adresult2[SITE] = FPVI0.GetMeasResult(SITE, MIRET, Trig_Point_F[SITE]);
// 				adresult[SITE] = adresult1[SITE] - adresult2[SITE];
// 				IOUT_OCP_X[3 * n + 1]->SetTestResult(SITE, 0, adresult2[SITE]);
// 				IOUT_OCP_X[3 * n + 2]->SetTestResult(SITE, 0, adresult[SITE]);
// 			}
// 		}
// 
// 		FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//PGND-VOUT
// 		delay_ms(1);
// 
// 	}


	CParam *IOUT_OCP_Y[12] =
	{
		IOUT_OCP_00_UP_DS, IOUT_OCP_00_DOWN, IOUT_OCP_00_HYS_DS,
		IOUT_OCP_01_UP_DS, IOUT_OCP_01_DOWN, IOUT_OCP_01_HYS_DS,
		IOUT_OCP_10_UP_DS, IOUT_OCP_10_DOWN, IOUT_OCP_10_HYS_DS,
		IOUT_OCP_11_UP_DS, IOUT_OCP_11_DOWN, IOUT_OCP_11_HYS_DS,
	};

	manager.setfields({ { EN_ANA_MUX, 1 }, { MUX_ANA, 0x08 }, { TRIM_ISNS_GAIN, 0x40 } });//add, 2025.11.8
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//PGND-VOUT
	INTB.Set(FI, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_ms(1);

	for (int n = 0; n < 4; n++)
	{
		if (n == 0)
			manager.setfields({ { LDO_OCP_THD, 0x00 } });//00, 1.2A
		if (n == 1)
			manager.setfields({ { LDO_OCP_THD, 0x01 } });//01, 0.6A
		if (n == 2)
			manager.setfields({ { LDO_OCP_THD, 0x02 } });//10, 0.8A
		if (n == 3)
			manager.setfields({ { LDO_OCP_THD, 0x03 } });//11, 1A
		delay_ms(2);


		FPVI0.Set(FI, 0.2, FPVI10_10V, FPVI10_1A, RELAY_ON);//PGND-VOUT
		delay_ms(2);
		INTB.MeasureVI(50, 10);
		SERIAL analog_meas[SITE] = INTB.GetMeasResult(SITE, MVRET);

		
		FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//PGND-VOUT
		delay_ms(1);

		//PGND-VOUT sweep from 0A to 1A
		FPVI0.AwgSelect("IOUT_OCP_R", 0, sam - 1, sam - 1, interval);
		SINK.SetMeasVTrig(Trig, TRIG_FALLING);
		SINK.MeasureVI(sam, interval, MEAS_AWG);
		FPVI0.MeasureVI(sam, interval, MEAS_AWG);
		STSEnableAWG(&FPVI0);
		STSEnableMeas(&FPVI0, &SINK);
		STSAWGRunTriggerStop(&SINK, &SINK, &FPVI0);
		//STSAWGRun();
		SERIAL
		{
			Trig_Point_R[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
			if (Trig_Point_R[SITE]<=0 || Trig_Point_R[SITE]>=sam - 1)
			{
				Trig_Point_R[SITE] = 999;
				IOUT_OCP_Y[3 * n + 0]->SetTestResult(SITE, 0, Trig_Point_R[SITE]);
			}
			else
			{
				adresult1[SITE] = FPVI0.GetMeasResult(SITE, MIRET, Trig_Point_R[SITE]);
				cal_out1[SITE] = adresult1[SITE] * (analog_meas[SITE] / 0.2);

				IOUT_OCP_Y[3 * n + 0]->SetTestResult(SITE, 0, cal_out1[SITE]);
			}
		}

		//PGND-VOUT sweep from 1A to 0A
		FPVI0.AwgSelect("IOUT_OCP_F", 0, sam - 1, sam - 1, interval);
		SINK.SetMeasVTrig(Trig, TRIG_RISING);
		SINK.MeasureVI(sam, interval, MEAS_AWG);
		FPVI0.MeasureVI(sam, interval, MEAS_AWG);
		STSEnableAWG(&FPVI0);
		STSEnableMeas(&FPVI0, &SINK);
		STSAWGRunTriggerStop(&SINK, &SINK, &FPVI0);
		SERIAL
		{
			Trig_Point_F[SITE] = int(SINK.GetMeasResult(SITE, MVRET, TRIG_RESULT));
			if (Trig_Point_F[SITE]<=0 || Trig_Point_F[SITE]>=sam - 1)
			{
				Trig_Point_F[SITE] = 999;
				IOUT_OCP_Y[3 * n + 1]->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
				IOUT_OCP_Y[3 * n + 2]->SetTestResult(SITE, 0, Trig_Point_F[SITE]);
			}
			else
			{
				adresult2[SITE] = FPVI0.GetMeasResult(SITE, MIRET, Trig_Point_F[SITE]);
				cal_out2[SITE] = adresult2[SITE] * (analog_meas[SITE] / 0.2);
				adresult[SITE] = cal_out1[SITE] - cal_out2[SITE];
				IOUT_OCP_Y[3 * n + 1]->SetTestResult(SITE, 0, cal_out2[SITE]);
				IOUT_OCP_Y[3 * n + 2]->SetTestResult(SITE, 0, adresult[SITE]);
			}
		}

		FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//PGND-VOUT
		delay_ms(1);

	}

	FPVI0.SetClamp(100, 100);

	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_EXIT_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_1A);
	}
	else
	{
		TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
	}
	FPVI0.Set(FV, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//PGND-VOUT
	SINK.Set(FV, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	INTB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_ms(1);
	FPVI0.Set(FV, 0, FPVI10_10V, FPVI10_1A, RELAY_OFF);//PGND-VOUT
	SINK.Set(FV, 0, FOVI_10V, FOVI_100UA, RELAY_OFF);
	INTB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_OFF);
	delay_ms(1);


	return 0;
}

DUT_API int DUMMY_LOAD(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *Idmy_max_0001_DS = StsGetParam(funcindex, "Idmy_max_0001_DS");
    CParam *Idmy_max_0010_DS = StsGetParam(funcindex, "Idmy_max_0010_DS");
    CParam *Idmy_max_0100_DS = StsGetParam(funcindex, "Idmy_max_0100_DS");
    CParam *Idmy_max_1000_DS = StsGetParam(funcindex, "Idmy_max_1000_DS");
    CParam *Idmy_max_1111_DS = StsGetParam(funcindex, "Idmy_max_1111_DS");
    CParam *Idmy_dis = StsGetParam(funcindex, "Idmy_dis");
    CParam *V_CLAPH = StsGetParam(funcindex, "V_CLAPH");
    CParam *V_CLAPL = StsGetParam(funcindex, "V_CLAPL");
//}}AFX_STS_PARAM_PROTOTYPES
	// TODO: Add your function code here
	CParam *Idmy_max_X[5] =
	{
		Idmy_max_0001_DS, Idmy_max_0010_DS, Idmy_max_0100_DS, Idmy_max_1000_DS, Idmy_max_1111_DS,
	};

	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, -1);
	dioplus.I2CConnect();
	wait_relay();

	TM_ENTER_vi(VRECT, 5.5, FOVI_20V, FOVI_100MA);
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_DUMMY, 0 } });

	for (int n = 0; n < 5; n++)
	{
		if (n == 0)
			manager.setfields({ { I2C_PSEU_R, 0x01 } });//0001
		if (n == 1)
			manager.setfields({ { I2C_PSEU_R, 0x02 } });//0010
		if (n == 2)
			manager.setfields({ { I2C_PSEU_R, 0x04 } });//0100
		if (n == 3)
			manager.setfields({ { I2C_PSEU_R, 0x08 } });//1000
		if (n == 4)
			manager.setfields({ { I2C_PSEU_R, 0x0F } });//1111
		delay_ms(2);

		VRECT.MeasureVI(50, 10);
		SERIAL adresult1[SITE] = VRECT.GetMeasResult(SITE, MIRET);
	
		manager.setfields({ { I2C_EN_DUMMY, 1 } });
		delay_ms(2);

		VRECT.MeasureVI(50, 10);
		SERIAL
		{
			adresult2[SITE] = VRECT.GetMeasResult(SITE, MIRET);
			adresult[SITE] = -(adresult1[SITE] - adresult2[SITE]) * 1e3;
			Idmy_max_X[n]->SetTestResult(SITE, 0, adresult[SITE]);
		}
		manager.setfields({ { I2C_EN_DUMMY, 0 } });
	}

	//A0 add
	manager.setfields({ { I2C_EN_DUMMY, 1 }, { I2C_PSEU_R, 0x0F } });
	delay_ms(1);
	VRECT.MeasureVI(50, 10);
	SERIAL
	{
		adresult1[SITE] = VRECT.GetMeasResult(SITE, MIRET);
	}

	manager.setfields({ { TRIM_VRECT_DMY_DIS, 1 } });
	delay_ms(1);
	VRECT.MeasureVI(50, 10);
	SERIAL
	{
		adresult2[SITE] = VRECT.GetMeasResult(SITE, MIRET);
		adresult[SITE] = (adresult1[SITE] - adresult2[SITE]) * 1e3;
		Idmy_dis->SetTestResult(SITE, 0, adresult[SITE]);//mA
	}

	VRECT.Set(FV, 12, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);
	
	VRECT.Set(FV, 12, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	manager.setfields({ { TRIM_VRECT_DMY_DIS, 0 } });
	manager.setfields({ /*{ I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 },*/{ I2C_EN_DUMMY, 1 }, { I2C_EN_OSC, 0 }, { I2C_PSEU_R, 0x00 } });
	delay_ms(7);//减少delay会不稳定，VRECT升不到target
	VRECT.MeasureVI(20, 10);
	SERIAL
	{
		adresult[SITE] = VRECT.GetMeasResult(SITE, MVRET);
		V_CLAPH->SetTestResult(SITE, 0, adresult[SITE]);
	}

	TM_EXIT_vi(VRECT, 12, FOVI_20V, FOVI_10MA);

	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_10MA);
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_DUMMY, 1 }, { I2C_PSEU_R, 0x0F } });
	delay_ms(1);

	V5V.MeasureVI(20, 10);
	SERIAL
	{
		adresult[SITE] = V5V.GetMeasResult(SITE, MVRET);
		V_CLAPL->SetTestResult(SITE, 0, adresult[SITE]);
	}

	if (POWER_FLAG)
	{
		TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_10MA);
	}
	else
	{
		V5V.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	}
	return 0;
}

DUT_API int ADC_TEST(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *INTB_ADC_1V_SCM = StsGetParam(funcindex, "INTB_ADC_1V_SCM");
    CParam *INTB_ADC_1P8V_SCM = StsGetParam(funcindex, "INTB_ADC_1P8V_SCM");
    CParam *SCL_ADC_SCM = StsGetParam(funcindex, "SCL_ADC_SCM");
    CParam *SDA_ADC_SCM = StsGetParam(funcindex, "SDA_ADC_SCM");
    CParam *VRECT_ADC_5V_SCM = StsGetParam(funcindex, "VRECT_ADC_5V_SCM");
    CParam *VRECT_ADC_5V_NOL_DS = StsGetParam(funcindex, "VRECT_ADC_5V_NOL_DS");
    CParam *VRECT_ADC_9V_SCM = StsGetParam(funcindex, "VRECT_ADC_9V_SCM");
    CParam *VRECT_ADC_9V_NOL_DS = StsGetParam(funcindex, "VRECT_ADC_9V_NOL_DS");
    CParam *ISNS_10mA_AF_SCM = StsGetParam(funcindex, "ISNS_10mA_AF_SCM");
    CParam *ISNS_ADC_OS_50mA_AF = StsGetParam(funcindex, "ISNS_ADC_OS_50mA_AF");
    CParam *ISNS_ADC_OS_50mA_Ivout_AF = StsGetParam(funcindex, "ISNS_ADC_OS_50mA_Ivout_AF");
    CParam *ISNS_ADC_OS_500mA_AF_DS = StsGetParam(funcindex, "ISNS_ADC_OS_500mA_AF_DS");
    CParam *ISNS_ADC_OS_500mA_Ivout_AF = StsGetParam(funcindex, "ISNS_ADC_OS_500mA_Ivout_AF");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here
	int data_adc_h[SITE_COUNT] = { 0 };
	int data_adc_l[SITE_COUNT] = { 0 };
	int read_adc_code[SITE_COUNT] = { 0 };
	int readtimecount = 5;
	double arry[10][SITE_COUNT] = { 0 };
	double adc_temp[SITE_COUNT] = { 0, 0, 0, 0 };

	double adc_ana_input[SITE_COUNT] = { 0.0 };
	double vrect_meas1[SITE_NUM] = { 0.0 };
	double vrect_meas2[SITE_NUM] = { 0.0 };

	cbit.SetOn(K4_IIC_PULLUP/*, K2_VRECT_V5V_CAP*/, -1);
	dioplus.I2CConnect();
	wait_relay();
	TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);

	/////////////////////////////////INTB ADC 1V/////////////////////////////////
	INTB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	INTB.Set(FV, 1, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	V5V.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	INTB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	//INTB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	//delay_ms(1);

	//dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X49, 2);
	//SERIAL
	//{
	//	data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x49 value
	//	data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x4A value
	//}
	//SERIAL
	//{
	//	read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x49 bit0~7 + 0x4A bit0~1
	//	adresult[SITE] = double(read_adc_code[SITE]) / 1023 * 2;//adc_ana_input

	//	INTB_ADC_1V_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	//}
	for (int i = 0; i < readtimecount; i++)
	{
		dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X49, 2);
	
		SERIAL
		{
			data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x49 value
			data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x4A value
			read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x49 bit0~7 + 0x4A bit0~1
			adc_temp[SITE] = double(read_adc_code[SITE]) / 1023 * 2;//adc_ana_input
			arry[i][SITE] = adc_temp[SITE];
		}
	}

	SERIAL
	{
		adresult[SITE] = calculateAverageWithoutMinMax(arry, readtimecount);

		INTB_ADC_1V_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}



	/////////////////////////////////INTB ADC 1.8V/////////////////////////////////
	INTB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	TM_RGE_WRITE();

	INTB.Set(FV, 1.8, FOVI_2V, FOVI_10MA, RELAY_ON);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	V5V.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	INTB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	//INTB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	//delay_ms(3);

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X49, 2);
	SERIAL
	{
		data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x49 value
		data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x4A value
	}
		SERIAL
	{
		read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x49 bit0~7 + 0x4A bit0~1
		adresult[SITE] = double(read_adc_code[SITE]) / 1023 * 2;//adc_ana_input

		INTB_ADC_1P8V_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}

	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);

	/////////////////////////////////VRECT ADC/////////////////////////////////
	//TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	//if (Global_Tempchar_Program_Flag == 1)
	//{
	//	V5V.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON, 1);
	//}
	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, -1);
	wait_relay();
	VRECT.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);
	TM_RGE_WRITE();

	manager.historyClear();//clear history value
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_OSC, 1 }, { T_RSAMPLE, 1 }, { TM_ADC, 1 }, { TM_CH_SEL, 0x03 }, { TM_CONTINUE_MODE, 0 }, { TM_ADC_EN, 1 }, { TM_ADC_START, 1 } });
	delay_ms(1);

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X98, 2);

	SERIAL
	{
		data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x98 value
		data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x99 value
	}

	SERIAL
	{
		read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x98 bit0~7 + 0x99 bit0~1
		adresult[SITE] = double(read_adc_code[SITE]) / 1023 * 2 * 5;//adc_ana_input

		VRECT_ADC_5V_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}

	//////////////////////////////////////add 20260522////////////////////////////////////////
	I2CWriteAllSites(0XF7, 0X00);
	delay_us(1000);

	VRECT.MeasureVI(50, 10);
	SERIAL vrect_meas1[SITE] = VRECT.GetMeasResult(SITE, MVRET);

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X43, 2);

	SERIAL
	{
		data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x43 value
		data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x44 value
	}

	SERIAL
	{
		read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x43 bit0~7 + 0x44 bit0~1
		adresult[SITE] = double(read_adc_code[SITE]) / 1023 * 2 * 5;//adc_ana_input
		adresult0[SITE] = (adresult[SITE] - vrect_meas1[SITE])*1e3;//mV
		VRECT_ADC_5V_NOL_DS->SetTestResult(SITE, 0, adresult0[SITE]);
	}

	//////////////////////////////////////add 20260522////////////////////////////////////////


	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	delay_ms(1);

	//VRECT=9V need to reset power
	VRECT.Set(FV, 9, FOVI_10V, FOVI_100MA, RELAY_ON, 1);
	delay_ms(1);
	TM_RGE_WRITE();

	manager.historyClear();//clear history value
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_OSC, 1 }, { T_RSAMPLE, 1 }, { TM_ADC, 1 }, { TM_CH_SEL, 0x03 }, { TM_CONTINUE_MODE, 0 }, { TM_ADC_EN, 1 }, { TM_ADC_START, 1 } });
	delay_ms(1);
	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X98, 2);

	SERIAL
	{
		data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x98 value
		data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x99 value
	}

	SERIAL
	{
		read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x98 bit0~7 + 0x99 bit0~1
		adresult[SITE] = double(read_adc_code[SITE]) / 1023 * 2 * 5;//adc_ana_input

		VRECT_ADC_9V_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}

	//////////////////////////////////////add 20260522////////////////////////////////////////
	I2CWriteAllSites(0XF7, 0X00);
	delay_us(1000);

	VRECT.MeasureVI(50, 10);
	SERIAL vrect_meas1[SITE] = VRECT.GetMeasResult(SITE, MVRET);

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X43, 2);

	SERIAL
	{
		data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x43 value
		data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x44 value
	}

	SERIAL
	{
		read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x43 bit0~7 + 0x44 bit0~1
		adresult[SITE] = double(read_adc_code[SITE]) / 1023 * 2 * 5;//adc_ana_input
		adresult0[SITE] = (adresult[SITE] - vrect_meas1[SITE])*1e3;//mV
		VRECT_ADC_9V_NOL_DS->SetTestResult(SITE, 0, adresult0[SITE]);
	}

	//////////////////////////////////////add 20260522////////////////////////////////////////

	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 1);
	delay_ms(1);

	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	//V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	//delay_ms(1);

	/////////////////////////////////SCL ADC/////////////////////////////////
	TM_ENTER_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);

	cbit.SetOn(K2_VRECT_V5V_CAP, K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA, -1);
	dioplus.I2CDisconnect();
	wait_relay();

	INTB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	SCL.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	SDA.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(200);

	INTB.Set(FV, 0.3, FOVI_2V, FOVI_10MA, RELAY_ON);
	SCL.Set(FV, 1, FOVI_2V, FOVI_10MA, RELAY_ON);
	SDA.Set(FV, 1, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);
	V5V.Set(FV, spec("V5V"), FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);

	SCL.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	SDA.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_ms(1);

	SCL.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	SDA.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	delay_ms(1);
	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, -1);
	dioplus.I2CConnect();
	wait_relay();

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X4D, 2);

	SERIAL
	{
		data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x4D value
		data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x4E value
	}

	SERIAL
	{
		read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x4D bit0~7 + 0x4E bit0~1
		adresult[SITE] = double(read_adc_code[SITE]) / 1023 * 2;//adc_ana_input

		SCL_ADC_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}

	/////////////////////////////////SDA ADC/////////////////////////////////
	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X4B, 2);

	SERIAL
	{
		data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x4B value
		data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x4C value
	}

	SERIAL
	{
		read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x4B bit0~7 + 0x4C bit0~1
		adresult[SITE] = double(read_adc_code[SITE]) / 1023 * 2;//adc_ana_input

		SDA_ADC_SCM->SetTestResult(SITE, 0, adresult[SITE]);
	}

	INTB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	TM_EXIT_vi(V5V, spec("V5V"), FOVI_10V, FOVI_100MA);
	INTB.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);


	cbit.SetOn(K2_VRECT_V5V_CAP, K4_IIC_PULLUP, K3_VOUT_CAP, K13_PVI0H_PGND, K17_PVI0L_VOUT, K11_OVI7_VOUT_COMM2, -1);//FPVI0H_PGND,FPVI0L_VOUT; disconnect VOUT FOVI resource
	wait_relay();

	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_us(200);
	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_ENTER_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_1A);
	}
	else
	{
		TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
	}

	//A0的VOUT dummyload默认关，无需手动配置
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_VCP, 1 },
	{ I2C_EN_LDO_PWR, 1 }, { I2C_DIS_SS, 1 }, { I2C_REF_IN, 0x80 }/*, { I2C_ILOAD_H, 1 }*/, { EN_ANA_MUX, 1 }, { MUX_ANA, 0x08 } });

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	FPVI0.SetClamp(75, 75);
	delay_ms(1);


	//ISNS ADC 10mA FINAL
	INTB.Set(FI, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	FPVI0.Set(FI, 0.01, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT=10mA
	delay_ms(1);

	INTB.MeasureVI(50, 10);

	SERIAL
	{
		adresult[SITE] = INTB.GetMeasResult(SITE, MVRET);
		ISNS_10mA_AF_SCM->SetTestResult(SITE, 0, adresult[SITE] * 1E3);//mV
	}
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	INTB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_ON);
	delay_ms(3);
	TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
	INTB.Set(FV, 0, FOVI_1V, FOVI_1MA, RELAY_OFF);
	delay_ms(1);
	VRECT.Set(FV, 0, FOVI_1V, FOVI_100MA, RELAY_ON); 
	delay_us(200);
	TM_ENTER_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);

	//ISNSADC_OS_0.05A
	//manager.setfields({ { EN_ANA_MUX, 0 }, { MUX_ANA, 0 }, { I2C_ILOAD_H, 1 }, { T_RSAMPLE, 1 }, { TM_ADC, 1 }, { TM_CH_SEL, 1 } });
	//manager.setfields({  { TM_ADC_START, 0 }, { TM_CONTINUE_MODE, 0 }, { TM_ADC_EN, 0 } });
	manager.historyClear();//clear history value
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 }, { I2C_EN_VCP, 1 },
	{ I2C_EN_LDO_PWR, 1 }, { I2C_DIS_SS, 1 }, { I2C_REF_IN, 0x80 }, { I2C_ILOAD_H, 1 }, { T_RSAMPLE, 1 }, { TM_ADC, 1 }, { TM_CH_SEL, 1 } });
	manager.setfields({ { TM_ADC_START, 1 }, { TM_CONTINUE_MODE, 1 }, { TM_ADC_EN, 1 } });
	delay_ms(1);


	FPVI0.Set(FI, 0.05, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT=50mA
	delay_ms(1);
	FPVI0.Set(FI, 0.05, FPVI10_10V, FPVI10_100MA, RELAY_ON);//GND-VOUT=50mA
	delay_ms(1);

	manager.setfields({ { TM_CONTINUE_MODE, 0 } });
	delay_ms(1);

	FPVI0.MeasureVI(50, 10);
	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X98, 2);

	SERIAL
	{
		adresult5[SITE] = FPVI0.GetMeasResult(SITE, MIRET);
		data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x98 value
		data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x99 value
	}

	SERIAL
	{
		read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x98 bit0~7 + 0x99 bit0~1
		adc_ana_input[SITE] = double(read_adc_code[SITE]) / 1023 * 2;
		adresult1[SITE] = adc_ana_input[SITE] - adresult5[SITE];
		adresult[SITE] = adresult1[SITE] * 1e3;

		ISNS_ADC_OS_50mA_AF->SetTestResult(SITE, 0, adresult[SITE]);
		ISNS_ADC_OS_50mA_Ivout_AF->SetTestResult(SITE, 0, adresult5[SITE] * 1e3);
	}
	FPVI0.Set(FI, 0.05, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT=50mA
	delay_ms(1);
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	//manager.setfields({ { TM_ADC_START, 0 }, { TM_CONTINUE_MODE, 0 }, { TM_ADC_EN, 0 } });
	delay_ms(1);

	//ISNSADC_OS_0.5A
	manager.setfields({ { TM_ADC_START, 1 }, { TM_CONTINUE_MODE, 1 }, { TM_ADC_EN, 1 } });

	FPVI0.Set(FI, 0.5, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT=500mA
	delay_ms(1);

	manager.setfields({ { TM_CONTINUE_MODE, 0 } });
	delay_ms(2);//delay for read stably

	FPVI0.MeasureVI(50, 10);
	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X3F, 2);

	SERIAL
	{
		adresult6[SITE] = FPVI0.GetMeasResult(SITE, MIRET);
		data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x3f value
		data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x40 value
	}

	//delay_ms(2);
	//dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X3F, 2);
	//SERIAL
	//{
	//	data_adc_l[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0x3f value
	//	data_adc_h[SITE] = pI2CSites[SITE]->GetDataByteValue(1);  //get 0x40 value
	//}

	SERIAL
	{
		read_adc_code[SITE] = data_adc_h[SITE] * 256 + data_adc_l[SITE];//adc_out_code: 0x98 bit0~7 + 0x99 bit0~1
		adc_ana_input[SITE] = double(read_adc_code[SITE]) / 1023 * 2;
		adresult2[SITE] = adc_ana_input[SITE] - adresult6[SITE];
		adresult[SITE] = adresult2[SITE] * 1e3;

		ISNS_ADC_OS_500mA_AF_DS->SetTestResult(SITE, 0, adresult[SITE]);
		ISNS_ADC_OS_500mA_Ivout_AF->SetTestResult(SITE, 0, adresult6[SITE] * 1e3);
	}
	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);//GND-VOUT
	delay_ms(1);

	FPVI0.Set(FI, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);//GND-VOUT=10mA
	FPVI0.SetClamp(100, 100);


	if (Global_Tempchar_Program_Flag == 1)
	{
		TM_EXIT_TEMPCHAR(VRECT, V5V, spec("V5V"), FOVI_10V, FOVI_1A);
	}
	else
	{
		TM_EXIT_vi(VRECT, 5.5, FOVI_10V, FOVI_1A);
	}

	FPVI0.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);//GND-VOUT
	delay_us(200);

	FPVI0.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_OFF);//GND-VOUT
	dioplus.I2CDisconnect();

    return 0;
}
 
DUT_API int FINAL_READ(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *FINAL_VBG_CODE = StsGetParam(funcindex, "FINAL_VBG_CODE");
    CParam *FINAL_ZTC_CODE = StsGetParam(funcindex, "FINAL_ZTC_CODE");
    CParam *FINAL_ADC_VREF_BUFFER_CODE = StsGetParam(funcindex, "FINAL_ADC_VREF_BUFFER_CODE");
    CParam *FINAL_ADC_VIN_BUFFER_CODE = StsGetParam(funcindex, "FINAL_ADC_VIN_BUFFER_CODE");
    CParam *FINAL_OSC_CODE = StsGetParam(funcindex, "FINAL_OSC_CODE");
    CParam *FINAL_COMP_OFF_AC1_CODE = StsGetParam(funcindex, "FINAL_COMP_OFF_AC1_CODE");
    CParam *FINAL_COMP_OFF_AC2_CODE = StsGetParam(funcindex, "FINAL_COMP_OFF_AC2_CODE");
    CParam *FINAL_ISNS_GAIN_CODE = StsGetParam(funcindex, "FINAL_ISNS_GAIN_CODE");
    CParam *FINAL_ISNS_OFFSET_CODE = StsGetParam(funcindex, "FINAL_ISNS_OFFSET_CODE");
    CParam *FINAL_BURN_TRIM_ACLOW_EN_82 = StsGetParam(funcindex, "FINAL_BURN_TRIM_ACLOW_EN_82");
    CParam *FINAL_BURN_TRIM_ACLOW_EN_85 = StsGetParam(funcindex, "FINAL_BURN_TRIM_ACLOW_EN_85");
    CParam *FINAL_BURN_TRIM_ACLOW_EN_87 = StsGetParam(funcindex, "FINAL_BURN_TRIM_ACLOW_EN_87");
    CParam *FINAL_BURN_TRIM_ACLOW_EN_82A = StsGetParam(funcindex, "FINAL_BURN_TRIM_ACLOW_EN_82A");
    CParam *FINAL_BURN_TTP_FSK_DIS_82 = StsGetParam(funcindex, "FINAL_BURN_TTP_FSK_DIS_82");
    CParam *FINAL_BURN_TTP_FSK_DIS_85 = StsGetParam(funcindex, "FINAL_BURN_TTP_FSK_DIS_85");
    CParam *FINAL_BURN_TTP_FSK_DIS_87 = StsGetParam(funcindex, "FINAL_BURN_TTP_FSK_DIS_87");
    CParam *FINAL_BURN_TTP_FSK_DIS_82A = StsGetParam(funcindex, "FINAL_BURN_TTP_FSK_DIS_82A");
    CParam *FINAL_BURN_AC_CHECK_500K_82 = StsGetParam(funcindex, "FINAL_BURN_AC_CHECK_500K_82");
    CParam *FINAL_BURN_AC_CHECK_500K_85 = StsGetParam(funcindex, "FINAL_BURN_AC_CHECK_500K_85");
    CParam *FINAL_BURN_AC_CHECK_500K_87 = StsGetParam(funcindex, "FINAL_BURN_AC_CHECK_500K_87");
    CParam *FINAL_BURN_AC_CHECK_500K_82A = StsGetParam(funcindex, "FINAL_BURN_AC_CHECK_500K_82A");
    CParam *FINAL_BURN_TRIM_DEIVICE_ID_82 = StsGetParam(funcindex, "FINAL_BURN_TRIM_DEIVICE_ID_82");
    CParam *FINAL_BURN_TRIM_DEIVICE_ID_85 = StsGetParam(funcindex, "FINAL_BURN_TRIM_DEIVICE_ID_85");
    CParam *FINAL_BURN_TRIM_DEIVICE_ID_87 = StsGetParam(funcindex, "FINAL_BURN_TRIM_DEIVICE_ID_87");
    CParam *FINAL_BURN_TRIM_DEIVICE_ID_82A = StsGetParam(funcindex, "FINAL_BURN_TRIM_DEIVICE_ID_82A");
    CParam *FINAL_BURN_TRIM_QI_ID_82 = StsGetParam(funcindex, "FINAL_BURN_TRIM_QI_ID_82");
    CParam *FINAL_BURN_TRIM_QI_ID_85 = StsGetParam(funcindex, "FINAL_BURN_TRIM_QI_ID_85");
    CParam *FINAL_BURN_TRIM_QI_ID_87 = StsGetParam(funcindex, "FINAL_BURN_TRIM_QI_ID_87");
    CParam *FINAL_BURN_TRIM_QI_ID_82A = StsGetParam(funcindex, "FINAL_BURN_TRIM_QI_ID_82A");
    CParam *FINAL_0XF7_BIT2_TRIM_LOCK = StsGetParam(funcindex, "FINAL_0XF7_BIT2_TRIM_LOCK");
    CParam *FINAL_0XF7_BIT3_OPT2_LOCK = StsGetParam(funcindex, "FINAL_0XF7_BIT3_OPT2_LOCK");
    CParam *FINAL_0XF7_BIT4_OPT1_LOCK = StsGetParam(funcindex, "FINAL_0XF7_BIT4_OPT1_LOCK");
    CParam *FINAL_0XF7_BIT5_OPT1_BAK_LOCK = StsGetParam(funcindex, "FINAL_0XF7_BIT5_OPT1_BAK_LOCK");
    CParam *final_Read_0080 = StsGetParam(funcindex, "final_Read_0080");
    CParam *final_Read_0081 = StsGetParam(funcindex, "final_Read_0081");
    CParam *final_Read_0082 = StsGetParam(funcindex, "final_Read_0082");
    CParam *final_Read_0083 = StsGetParam(funcindex, "final_Read_0083");
    CParam *final_Read_0084 = StsGetParam(funcindex, "final_Read_0084");
    CParam *final_Read_0085 = StsGetParam(funcindex, "final_Read_0085");
    CParam *final_Read_0086 = StsGetParam(funcindex, "final_Read_0086");
    CParam *final_Read_0087 = StsGetParam(funcindex, "final_Read_0087");
    CParam *final_Read_0088 = StsGetParam(funcindex, "final_Read_0088");
    CParam *final_Read_0089 = StsGetParam(funcindex, "final_Read_0089");
    CParam *final_Read_008A = StsGetParam(funcindex, "final_Read_008A");
    CParam *EFUSE_Read1 = StsGetParam(funcindex, "EFUSE_Read1");
    CParam *EFUSE_Read2 = StsGetParam(funcindex, "EFUSE_Read2");
    CParam *REG_0X30 = StsGetParam(funcindex, "REG_0X30");
    CParam *REG_0X31 = StsGetParam(funcindex, "REG_0X31");
    CParam *REG_0X32 = StsGetParam(funcindex, "REG_0X32");
    CParam *REG_0X33 = StsGetParam(funcindex, "REG_0X33");
    CParam *REG_0X34 = StsGetParam(funcindex, "REG_0X34");
    CParam *REG_0X35 = StsGetParam(funcindex, "REG_0X35");
    CParam *REG_0X36 = StsGetParam(funcindex, "REG_0X36");
    CParam *REG_0X37 = StsGetParam(funcindex, "REG_0X37");
    CParam *REG_0X38 = StsGetParam(funcindex, "REG_0X38");
    CParam *REG_0X39 = StsGetParam(funcindex, "REG_0X39");
    CParam *REG_0X3A = StsGetParam(funcindex, "REG_0X3A");
    CParam *REG_0X3B = StsGetParam(funcindex, "REG_0X3B");
    CParam *REG_0X3C = StsGetParam(funcindex, "REG_0X3C");
    CParam *REG_0X3D = StsGetParam(funcindex, "REG_0X3D");
    CParam *REG_0X3E = StsGetParam(funcindex, "REG_0X3E");
    CParam *REG_0X81_bit1 = StsGetParam(funcindex, "REG_0X81_bit1");
    CParam *REG_0X82_bit0_1 = StsGetParam(funcindex, "REG_0X82_bit0_1");
    CParam *REG_0X83_bit0 = StsGetParam(funcindex, "REG_0X83_bit0");
    CParam *REG_0X84_bit0_2 = StsGetParam(funcindex, "REG_0X84_bit0_2");
    CParam *REG_0X85_bit0 = StsGetParam(funcindex, "REG_0X85_bit0");
    CParam *REG_0X86_bit0_1 = StsGetParam(funcindex, "REG_0X86_bit0_1");
    CParam *REG_0X87_bit0_1 = StsGetParam(funcindex, "REG_0X87_bit0_1");
    CParam *REG_0X88 = StsGetParam(funcindex, "REG_0X88");
    CParam *REG_0X89 = StsGetParam(funcindex, "REG_0X89");
    CParam *REG_0X8A = StsGetParam(funcindex, "REG_0X8A");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	cbit.SetOn(K4_IIC_PULLUP, K2_VRECT_V5V_CAP, -1);
	dioplus.I2CConnect();
	wait_relay();

	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0XF7, 1);

	SERIAL
	{
		FINAL_READ_0XF7[SITE] = pI2CSites[SITE]->GetDataByteValue(0);  //get 0xF7 value

		final_read_0XF7_BIT2_CODE[SITE] = (unsigned char(FINAL_READ_0XF7[SITE]) & 0X04) >> 2; //0XF7 bit2 
		final_read_0XF7_BIT3_CODE[SITE] = (unsigned char(FINAL_READ_0XF7[SITE]) & 0X08) >> 3; //0XF7 bit3 
		final_read_0XF7_BIT4_CODE[SITE] = (unsigned char(FINAL_READ_0XF7[SITE]) & 0X10) >> 4; //0XF7 bit4 	
		final_read_0XF7_BIT5_CODE[SITE] = (unsigned char(FINAL_READ_0XF7[SITE]) & 0X20) >> 5; //0XF7 bit5 
	}

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X80, 11);//read trim reg code
	for (int reg = 0; reg < 11; reg++)
	{
		EFUSE_READ_FINAL[reg][0] = i2c_site1.GetDataByteValue(reg);  // i2c site1 get the reg byte value
		EFUSE_READ_FINAL[reg][1] = i2c_site2.GetDataByteValue(reg);  // i2c site2 get the reg byte value
		EFUSE_READ_FINAL[reg][2] = i2c_site3.GetDataByteValue(reg);  // i2c site3 get the reg byte value
		EFUSE_READ_FINAL[reg][3] = i2c_site4.GetDataByteValue(reg);  // i2c site4 get the reg byte value
		EFUSE_READ_FINAL[reg][4] = i2c_site5.GetDataByteValue(reg);  // i2c site5 get the reg byte value
		EFUSE_READ_FINAL[reg][5] = i2c_site6.GetDataByteValue(reg);  // i2c site6 get the reg byte value
		EFUSE_READ_FINAL[reg][6] = i2c_site7.GetDataByteValue(reg);  // i2c site7 get the reg byte value
		EFUSE_READ_FINAL[reg][7] = i2c_site8.GetDataByteValue(reg);  // i2c site8 get the reg byte value
	}
	
	for (int reg = 0; reg < BANK_NUM; ++reg)
	{
		string TB_str;
		TB_str = "EEPROM" + spec.int2str(reg);

		// set trim flag, and disable trim node allow if trimmed
		SERIAL
		{
			dut.assy(TB_str.c_str()).set_read_back((EFUSE_READ_FINAL[reg][SITE]), SITE);
			//dut.assy(TB_str.c_str()).copy_read_to_prog();
			//dut.assy(TB_str.c_str()).copy_read_to_saved();
			if (Global_FTQC_FLAG != 0)//QC
			{
				dut.assy(TB_str.c_str()).copy_read_to_work(SITE);
			}
			for (unsigned int node_no = 0; node_no < dut.assy(TB_str.c_str()).count(); ++node_no)
			{
				string node_name(dut.assy(TB_str.c_str())[node_no].get_node_name());

				if (dut.find(node_name.c_str()) == FOUND_TRIM)									// judge if it is trim node, not sel node
					dut.trim(node_name.c_str()).set_trim_allowed(burn_flag_all[SITE], SITE);	// if burn_flag is false, disable trim allow, else enable
			}
		}
	}


	FOR_EACH_VALID_SITE(site)
	{
		final_read_VBG_CODE[site] = dut.trim("TRIM_BG").get_read_back(site);//EEPROM1 bit2~7
		final_read_ZTC_CODE[site] = dut.trim("TRIM_ZTC").get_read_back(site);//EEPROM4 bit3~7
		final_read_ADC_VREF_BUFFER_CODE[site] = dut.trim("TRIM_ADC_VREF_BUFFER").get_read_back(site);//EEPROM2 bit2~7
		final_read_ADC_VIN_BUFFER_CODE[site] = dut.trim("TRIM_ADC_VIN_BUFFER").get_read_back(site);//EEPROM7 bit2~7
		final_read_OSC_CODE[site] = dut.trim("TRIM_OSC").get_read_back(site);//EEPROM3 bit1~7
		final_read_COMP_OFF_AC1_CODE[site] = dut.trim("TRIM_LS1_COMP").get_read_back(site);//EEPROM0 bit4~7
		final_read_COMP_OFF_AC2_CODE[site] = dut.trim("TRIM_LS2_COMP").get_read_back(site);//EEPROM0 bit0~3
		final_read_ISNS_GAIN_CODE[site] = dut.trim("TRIM_ISNS_GAIN").get_read_back(site);//EEPROM5 bit1~7
		final_read_ISNS_OFFSET_CODE[site] = dut.trim("TRIM_ISNS_OFFSET").get_read_back(site);//EEPROM6 bit2~7
		final_read_TRIM_ACLOW_EN[site] = dut.sel("TRIM_ACLOW_EN").get_read_back(site);//EEPROM2 bit1
		final_read_TTP_FSK_DIS[site] = dut.sel("TTP_FSK_DIS").get_read_back(site);//EEPROM9 bit6
		final_read_AC_CHECK_500K[site] = dut.sel("AC_CHECK_500K").get_read_back(site);//EEPROM9 bit5
		final_read_TRIM_DEIVICE_ID[site] = dut.sel("TRIM_DEIVICE_ID").get_read_back(site);//EEPROMA bit2~4
		final_read_TRIM_QI_ID[site] = dut.sel("TRIM_QI_ID").get_read_back(site);//EEPROMA bit0~1
	}


	FOR_EACH_VALID_SITE(site)
	{
		FINAL_VBG_CODE->SetTestResult(site, 0, final_read_VBG_CODE[site]);
		FINAL_ZTC_CODE->SetTestResult(site, 0, final_read_ZTC_CODE[site]);
		FINAL_ADC_VREF_BUFFER_CODE->SetTestResult(site, 0, final_read_ADC_VREF_BUFFER_CODE[site]);
		FINAL_ADC_VIN_BUFFER_CODE->SetTestResult(site, 0, final_read_ADC_VIN_BUFFER_CODE[site]);
		FINAL_OSC_CODE->SetTestResult(site, 0, final_read_OSC_CODE[site]);
		FINAL_COMP_OFF_AC1_CODE->SetTestResult(site, 0, final_read_COMP_OFF_AC1_CODE[site]);
		FINAL_COMP_OFF_AC2_CODE->SetTestResult(site, 0, final_read_COMP_OFF_AC2_CODE[site]);
		FINAL_ISNS_GAIN_CODE->SetTestResult(site, 0, final_read_ISNS_GAIN_CODE[site]);
		FINAL_ISNS_OFFSET_CODE->SetTestResult(site, 0, final_read_ISNS_OFFSET_CODE[site]);
		//select PN
		if (spec("PT_PROG") == 1682)
		{
			FINAL_BURN_TRIM_ACLOW_EN_82->SetTestResult(site, 0, final_read_TRIM_ACLOW_EN[site]);
			FINAL_BURN_TTP_FSK_DIS_82->SetTestResult(site, 0, final_read_TTP_FSK_DIS[site]);
			FINAL_BURN_AC_CHECK_500K_82->SetTestResult(site, 0, final_read_AC_CHECK_500K[site]);
			FINAL_BURN_TRIM_DEIVICE_ID_82->SetTestResult(site, 0, final_read_TRIM_DEIVICE_ID[site]);
			FINAL_BURN_TRIM_QI_ID_82->SetTestResult(site, 0, final_read_TRIM_QI_ID[site]);
		}
		else if (spec("PT_PROG") == 1685)
		{
			FINAL_BURN_TRIM_ACLOW_EN_85->SetTestResult(site, 0, final_read_TRIM_ACLOW_EN[site]);
			FINAL_BURN_TTP_FSK_DIS_85->SetTestResult(site, 0, final_read_TTP_FSK_DIS[site]);
			FINAL_BURN_AC_CHECK_500K_85->SetTestResult(site, 0, final_read_AC_CHECK_500K[site]);
			FINAL_BURN_TRIM_DEIVICE_ID_85->SetTestResult(site, 0, final_read_TRIM_DEIVICE_ID[site]);
			FINAL_BURN_TRIM_QI_ID_85->SetTestResult(site, 0, final_read_TRIM_QI_ID[site]);
		}
		else if (spec("PT_PROG") == 1687)
		{
			FINAL_BURN_TRIM_ACLOW_EN_87->SetTestResult(site, 0, final_read_TRIM_ACLOW_EN[site]);
			FINAL_BURN_TTP_FSK_DIS_87->SetTestResult(site, 0, final_read_TTP_FSK_DIS[site]);
			FINAL_BURN_AC_CHECK_500K_87->SetTestResult(site, 0, final_read_AC_CHECK_500K[site]);
			FINAL_BURN_TRIM_DEIVICE_ID_87->SetTestResult(site, 0, final_read_TRIM_DEIVICE_ID[site]);
			FINAL_BURN_TRIM_QI_ID_87->SetTestResult(site, 0, final_read_TRIM_QI_ID[site]);
		}
		else if (spec("PT_PROG") == 16821)
		{
			FINAL_BURN_TRIM_ACLOW_EN_82A->SetTestResult(site, 0, final_read_TRIM_ACLOW_EN[site]);
			FINAL_BURN_TTP_FSK_DIS_82A->SetTestResult(site, 0, final_read_TTP_FSK_DIS[site]);
			FINAL_BURN_AC_CHECK_500K_82A->SetTestResult(site, 0, final_read_AC_CHECK_500K[site]);
			FINAL_BURN_TRIM_DEIVICE_ID_82A->SetTestResult(site, 0, final_read_TRIM_DEIVICE_ID[site]);
			FINAL_BURN_TRIM_QI_ID_82A->SetTestResult(site, 0, final_read_TRIM_QI_ID[site]);
		}
		//FINAL_TRIM_ACLOW_EN->SetTestResult(site, 0, final_read_TRIM_ACLOW_EN[site]);
		//FINAL_TTP_FSK_DIS->SetTestResult(site, 0, final_read_TTP_FSK_DIS[site]);
		//FINAL_AC_CHECK_500K->SetTestResult(site, 0, final_read_AC_CHECK_500K[site]);
		//FINAL_TRIM_DEIVICE_ID->SetTestResult(site, 0, final_read_TRIM_DEIVICE_ID[site]);

		FINAL_0XF7_BIT2_TRIM_LOCK->SetTestResult(site, 0, final_read_0XF7_BIT2_CODE[site]);
		FINAL_0XF7_BIT3_OPT2_LOCK->SetTestResult(site, 0, final_read_0XF7_BIT3_CODE[site]);
		FINAL_0XF7_BIT4_OPT1_LOCK->SetTestResult(site, 0, final_read_0XF7_BIT4_CODE[site]);
		FINAL_0XF7_BIT5_OPT1_BAK_LOCK->SetTestResult(site, 0, final_read_0XF7_BIT5_CODE[site]);

		final_Read_0080->SetTestResult(site, 0, unsigned char(EFUSE_READ_FINAL[0][site]));
		final_Read_0081->SetTestResult(site, 0, unsigned char(EFUSE_READ_FINAL[1][site]));
		final_Read_0082->SetTestResult(site, 0, unsigned char(EFUSE_READ_FINAL[2][site]));
		final_Read_0083->SetTestResult(site, 0, unsigned char(EFUSE_READ_FINAL[3][site]));
		final_Read_0084->SetTestResult(site, 0, unsigned char(EFUSE_READ_FINAL[4][site]));
		final_Read_0085->SetTestResult(site, 0, unsigned char(EFUSE_READ_FINAL[5][site]));
		final_Read_0086->SetTestResult(site, 0, unsigned char(EFUSE_READ_FINAL[6][site]));
		final_Read_0087->SetTestResult(site, 0, unsigned char(EFUSE_READ_FINAL[7][site]));
		final_Read_0088->SetTestResult(site, 0, unsigned char(EFUSE_READ_FINAL[8][site]));
		final_Read_0089->SetTestResult(site, 0, unsigned char(EFUSE_READ_FINAL[9][site]));
		final_Read_008A->SetTestResult(site, 0, unsigned char(EFUSE_READ_FINAL[10][site]));
	}


	///////////////////////////////2026.2.4 A0 add, efuse reg read and compare///////////////////////////////
	DWORD reg_read_data[STS_SITE_NUM] = { 0 };
	int REGS_30_3e[15][SITE_NUM] = { 0 };
	int REGS_81_8a[10][SITE_NUM] = { 0 };
	int READ_0x81_bit1[SITE_NUM] = { 0 };
	int READ_0x82_bit0_1[SITE_NUM] = { 0 };
	int READ_0x83_bit0[SITE_NUM] = { 0 };
	int READ_0x84_bit0_2[SITE_NUM] = { 0 };
	int READ_0x85_bit0[SITE_NUM] = { 0 };
	int READ_0x86_bit0_1[SITE_NUM] = { 0 };
	int READ_0x87_bit0_1[SITE_NUM] = { 0 };
	int READ_0x88[SITE_NUM] = { 0 };
	int READ_0x89[SITE_NUM] = { 0 };
	int READ_0x8a[SITE_NUM] = { 0 };

	
	// 0x30_0x3e
	CParam *reg_30_3e[15] =
	{

		REG_0X30, REG_0X31, REG_0X32, REG_0X33, REG_0X34, REG_0X35, REG_0X36, REG_0X37,
		REG_0X38, REG_0X39, REG_0X3A, REG_0X3B, REG_0X3C, REG_0X3D, REG_0X3E,
	};
	int bytesToRead1 = 0x3e - 0x30 + 1;  // 15 bytes

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0x30, bytesToRead1);
	for (int reg = 0; reg < 15; reg++)
	{
		REGS_30_3e[reg][0] = i2c_site1.GetDataByteValue(reg);  // i2c site1 get the reg byte value
		REGS_30_3e[reg][1] = i2c_site2.GetDataByteValue(reg);  // i2c site2 get the reg byte value
		REGS_30_3e[reg][2] = i2c_site3.GetDataByteValue(reg);  // i2c site3 get the reg byte value
		REGS_30_3e[reg][3] = i2c_site4.GetDataByteValue(reg);  // i2c site4 get the reg byte value
		REGS_30_3e[reg][4] = i2c_site5.GetDataByteValue(reg);  // i2c site5 get the reg byte value
		REGS_30_3e[reg][5] = i2c_site6.GetDataByteValue(reg);  // i2c site6 get the reg byte value
		REGS_30_3e[reg][6] = i2c_site7.GetDataByteValue(reg);  // i2c site7 get the reg byte value
		REGS_30_3e[reg][7] = i2c_site8.GetDataByteValue(reg);  // i2c site8 get the reg byte value

		SERIAL reg_30_3e[reg + 0]->SetTestResult(SITE, 0, REGS_30_3e[reg][SITE]);

	}

	SERIAL
	{
		//0x32 flag: default=0x08, HTOL=0x00
		if (HTOL_HAST_FLAG == 1 && REGS_30_3e[2][SITE] == 0)
		{
			REG_0X32->SetTestResult(SITE, 0, 1);
		}
		else if (HTOL_HAST_FLAG == 0 && REGS_30_3e[2][SITE] == 8)
		{
			REG_0X32->SetTestResult(SITE, 0, 1);
		}
		else
		{
			REG_0X32->SetTestResult(SITE, 0, 0);
		}

		//0x38 flag: default=0x7D, HTOL=0xFF
		if (HTOL_HAST_FLAG == 1 && REGS_30_3e[8][SITE] == 255)
		{
			REG_0X38->SetTestResult(SITE, 0, 1);
		}
		else if (HTOL_HAST_FLAG == 0 && REGS_30_3e[8][SITE] == 125)
		{
			REG_0X38->SetTestResult(SITE, 0, 1);
		}
		else
		{
			REG_0X38->SetTestResult(SITE, 0, 0);
		}

		//0x39 flag: default=0x00, HTOL=0x03
		if (HTOL_HAST_FLAG == 1 && REGS_30_3e[9][SITE] == 3)
		{
			REG_0X39->SetTestResult(SITE, 0, 1);
		}
		else if (HTOL_HAST_FLAG == 0 && REGS_30_3e[9][SITE] == 0)
		{
			REG_0X39->SetTestResult(SITE, 0, 1);
		}
		else
		{
			REG_0X39->SetTestResult(SITE, 0, 0);
		}

		//0x3B flag: default=0x02, HTOL=0x3E
		if (HTOL_HAST_FLAG == 1 && REGS_30_3e[11][SITE] == 62)
		{
			REG_0X3B->SetTestResult(SITE, 0, 1);
		}
		else if (HTOL_HAST_FLAG == 0 && REGS_30_3e[11][SITE] == 2)
		{
			REG_0X3B->SetTestResult(SITE, 0, 1);
		}
		else
		{
			REG_0X3B->SetTestResult(SITE, 0, 0);
		}


	}


	int bytesToRead2 = 0x8a - 0x81 + 1;  // 10 bytes

	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0x81, bytesToRead2);
	for (int reg = 0; reg < 10; reg++)
	{
		REGS_81_8a[reg][0] = i2c_site1.GetDataByteValue(reg);  // i2c site1 get the reg byte value
		REGS_81_8a[reg][1] = i2c_site2.GetDataByteValue(reg);  // i2c site2 get the reg byte value
		REGS_81_8a[reg][2] = i2c_site3.GetDataByteValue(reg);  // i2c site3 get the reg byte value
		REGS_81_8a[reg][3] = i2c_site4.GetDataByteValue(reg);  // i2c site4 get the reg byte value
		REGS_81_8a[reg][4] = i2c_site5.GetDataByteValue(reg);  // i2c site5 get the reg byte value
		REGS_81_8a[reg][5] = i2c_site6.GetDataByteValue(reg);  // i2c site6 get the reg byte value
		REGS_81_8a[reg][6] = i2c_site7.GetDataByteValue(reg);  // i2c site7 get the reg byte value
		REGS_81_8a[reg][7] = i2c_site8.GetDataByteValue(reg);  // i2c site8 get the reg byte value
	}

	SERIAL
	{
		READ_0x81_bit1[SITE] = (unsigned char(REGS_81_8a[0][SITE]) & 0X02) >> 1; //0X81 bit1
		READ_0x82_bit0_1[SITE] = unsigned char(REGS_81_8a[1][SITE]) & 0X03; //0X82 bit0~1
		READ_0x83_bit0[SITE] = unsigned char(REGS_81_8a[2][SITE]) & 0X01; //0X83 bit0
		READ_0x84_bit0_2[SITE] = unsigned char(REGS_81_8a[3][SITE]) & 0X07; //0X84 bit0~2
		READ_0x85_bit0[SITE] = unsigned char(REGS_81_8a[4][SITE]) & 0X01; //0X85 bit0
		READ_0x86_bit0_1[SITE] = unsigned char(REGS_81_8a[5][SITE]) & 0X03; //0X86 bit0~1
		READ_0x87_bit0_1[SITE] = unsigned char(REGS_81_8a[6][SITE]) & 0X03; //0X87 bit0~1
		READ_0x88[SITE] = unsigned char(REGS_81_8a[7][SITE]); //0X88
		READ_0x89[SITE] = unsigned char(REGS_81_8a[8][SITE]); //0X89
		READ_0x8a[SITE] = unsigned char(REGS_81_8a[9][SITE]); //0X8a

		/////                  NU1682   NU1685   NU1687  NU1682A  /////
		/////  TRIN_ACLOW_EN    0X00     0X00	  0X01    0X00	/////
		/////   TTP_FSK_DIS     0X01     0X00	  0X00    0X01	/////
		/////  AC_CHECK_500K    0X01     0X01	  0X00    0X01	/////
		/////  TRIM_DEVICE_ID   0X02     0X05	  0X07    0X02	/////
		/////  TRIM_QI_ID       0X00     0X00	  0X00    0X11	/////

		if (spec("PT_PROG") == 1682 && READ_0x89[SITE] == 96 && READ_0x8a[SITE] == 136)
		{
			READ_0x89[SITE] = 1;//0110 0000
			READ_0x8a[SITE] = 1;//1000 1000
		}
		else if (spec("PT_PROG") == 1685 && READ_0x89[SITE] == 32 && READ_0x8a[SITE] == 148)
		{
			READ_0x89[SITE] = 1;//0010 0000
			READ_0x8a[SITE] = 1;//1001 0100
		}
		else if (spec("PT_PROG") == 1687 && READ_0x89[SITE] == 0 && READ_0x8a[SITE] == 156 && READ_0x82_bit0_1[SITE] == 2)
		{
			READ_0x89[SITE] = 1;//0000 0000
			READ_0x8a[SITE] = 1;//1001 1100
			READ_0x82_bit0_1[SITE] = 0;//FLAG, not real value
		}
		if (spec("PT_PROG") == 16821 && READ_0x89[SITE] == 96 && READ_0x8a[SITE] == 139)//V01 add NU1682A
		{
			READ_0x89[SITE] = 1;//0110 0000
			READ_0x8a[SITE] = 1;//1000 1011
		}
	}
	FOR_EACH_VALID_SITE(site)
	{
		REG_0X81_bit1->SetTestResult(site, 0, READ_0x81_bit1[site]);
		REG_0X82_bit0_1->SetTestResult(site, 0, READ_0x82_bit0_1[site]);
		REG_0X83_bit0->SetTestResult(site, 0, READ_0x83_bit0[site]);
		REG_0X84_bit0_2->SetTestResult(site, 0, READ_0x84_bit0_2[site]);
		REG_0X85_bit0->SetTestResult(site, 0, READ_0x85_bit0[site]);
		REG_0X86_bit0_1->SetTestResult(site, 0, READ_0x86_bit0_1[site]);
		REG_0X87_bit0_1->SetTestResult(site, 0, READ_0x87_bit0_1[site]);
		REG_0X88->SetTestResult(site, 0, READ_0x88[site]);
		REG_0X89->SetTestResult(site, 0, READ_0x89[site]);
		REG_0X8A->SetTestResult(site, 0, READ_0x8a[site]);

	}
	///////////////////////////////2026.2.4 A0 add, read 0x00~0xF9 and compare///////////////////////////////


	///////////////A0 add, 20260427, efuse read back1///////////////
	manager.setfields({ { NVM_SETTING, 0x01 }, { I2C_OTP_CMD, 0x78 } });
	delay_ms(1);
	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X80, 11);//read trim reg code

	SERIAL
	{
		if (after_burn_VBG_CODE[SITE] == final_read_VBG_CODE[SITE] &&
		after_burn_ZTC_CODE[SITE] == final_read_ZTC_CODE[SITE] &&
		after_burn_ADC_VREF_BUFFER_CODE[SITE] == final_read_ADC_VREF_BUFFER_CODE[SITE] &&
		after_burn_ADC_VIN_BUFFER_CODE[SITE] == final_read_ADC_VIN_BUFFER_CODE[SITE] &&
		after_burn_OSC_CODE[SITE] == final_read_OSC_CODE[SITE] &&
		after_burn_COMP_OFF_AC1_CODE[SITE] == final_read_COMP_OFF_AC1_CODE[SITE] &&
		after_burn_COMP_OFF_AC2_CODE[SITE] == final_read_COMP_OFF_AC2_CODE[SITE] &&
		after_burn_ISNS_GAIN_CODE[SITE] == final_read_ISNS_GAIN_CODE[SITE] &&
		after_burn_ISNS_OFFSET_CODE[SITE] == final_read_ISNS_OFFSET_CODE[SITE])
		{
			EFUSE_Read1->SetTestResult(SITE, 0, 1);
		}
		else
		{
			EFUSE_Read1->SetTestResult(SITE, 0, 0);
		}
	}
	///////////////A0 add, 20260427, efuse read back2///////////////
	manager.setfields({ { NVM_SETTING, 0x10 }, { I2C_OTP_CMD, 0x78 } });
	delay_ms(1);
	dioplus.I2CRead(pI2CSites, sizeof(pI2CSites) / sizeof(pI2CSites[0]), DEV_ADDR, 0X80, 11);//read trim reg code
	
	SERIAL
	{
		if (after_burn_VBG_CODE[SITE] == final_read_VBG_CODE[SITE] &&
		after_burn_ZTC_CODE[SITE] == final_read_ZTC_CODE[SITE] &&
		after_burn_ADC_VREF_BUFFER_CODE[SITE] == final_read_ADC_VREF_BUFFER_CODE[SITE] &&
		after_burn_ADC_VIN_BUFFER_CODE[SITE] == final_read_ADC_VIN_BUFFER_CODE[SITE] &&
		after_burn_OSC_CODE[SITE] == final_read_OSC_CODE[SITE] &&
		after_burn_COMP_OFF_AC1_CODE[SITE] == final_read_COMP_OFF_AC1_CODE[SITE] &&
		after_burn_COMP_OFF_AC2_CODE[SITE] == final_read_COMP_OFF_AC2_CODE[SITE] &&
		after_burn_ISNS_GAIN_CODE[SITE] == final_read_ISNS_GAIN_CODE[SITE] &&
		after_burn_ISNS_OFFSET_CODE[SITE] == final_read_ISNS_OFFSET_CODE[SITE])
		{
			EFUSE_Read2->SetTestResult(SITE, 0, 1);
		}
		else
		{
			EFUSE_Read2->SetTestResult(SITE, 0, 0);
		}
	}
	///////////////////////////////////////////////////////////////////

	TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);

    return 0;
}
 
DUT_API int FINAL_LEAKAGE(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *V5V_FINAL_LEAK = StsGetParam(funcindex, "V5V_FINAL_LEAK");
    CParam *AC1_HS_FINAL_LEAK = StsGetParam(funcindex, "AC1_HS_FINAL_LEAK");
    CParam *AC1_LS_FINAL_LEAK = StsGetParam(funcindex, "AC1_LS_FINAL_LEAK");
    CParam *AC2_HS_FINAL_LEAK = StsGetParam(funcindex, "AC2_HS_FINAL_LEAK");
    CParam *AC2_LS_FINAL_LEAK = StsGetParam(funcindex, "AC2_LS_FINAL_LEAK");
    CParam *VOUT_FINAL_LEAK = StsGetParam(funcindex, "VOUT_FINAL_LEAK");
    CParam *VRECT_FINAL_LEAK = StsGetParam(funcindex, "VRECT_FINAL_LEAK");
    CParam *ENB_FINAL_LEAK = StsGetParam(funcindex, "ENB_FINAL_LEAK");
    CParam *VRECT_VOUT_FINAL_LEAK_11V = StsGetParam(funcindex, "VRECT_VOUT_FINAL_LEAK_11V");
    CParam *VRECT_COMM1_FINAL_LEAK_11V = StsGetParam(funcindex, "VRECT_COMM1_FINAL_LEAK_11V");
    CParam *VRECT_COMM2_FINAL_LEAK_11V = StsGetParam(funcindex, "VRECT_COMM2_FINAL_LEAK_11V");
    CParam *INTB_FINAL_LEAK_DS = StsGetParam(funcindex, "INTB_FINAL_LEAK_DS");
    CParam *SINK_FINAL_LEAK = StsGetParam(funcindex, "SINK_FINAL_LEAK");
    CParam *SCL_FINAL_LEAK_DS = StsGetParam(funcindex, "SCL_FINAL_LEAK_DS");
    CParam *SDA_FINAL_LEAK_DS = StsGetParam(funcindex, "SDA_FINAL_LEAK_DS");
    CParam *COMM1_FINAL_LEAK = StsGetParam(funcindex, "COMM1_FINAL_LEAK");
    CParam *COMM2_FINAL_LEAK = StsGetParam(funcindex, "COMM2_FINAL_LEAK");
    CParam *V5V_FINAL_LEAK_Delta = StsGetParam(funcindex, "V5V_FINAL_LEAK_Delta");
    CParam *AC1_HS_FINAL_LEAK_Delta = StsGetParam(funcindex, "AC1_HS_FINAL_LEAK_Delta");
    CParam *AC1_LS_FINAL_LEAK_Delta = StsGetParam(funcindex, "AC1_LS_FINAL_LEAK_Delta");
    CParam *AC2_HS_FINAL_LEAK_Delta = StsGetParam(funcindex, "AC2_HS_FINAL_LEAK_Delta");
    CParam *AC2_LS_FINAL_LEAK_Delta = StsGetParam(funcindex, "AC2_LS_FINAL_LEAK_Delta");
    CParam *VOUT_FINAL_LEAK_Delta = StsGetParam(funcindex, "VOUT_FINAL_LEAK_Delta");
    CParam *VRECT_FINAL_LEAK_Delta = StsGetParam(funcindex, "VRECT_FINAL_LEAK_Delta");
    CParam *ENB_FINAL_LEAK_Delta = StsGetParam(funcindex, "ENB_FINAL_LEAK_Delta");
    CParam *VRECT_VOUT_FINAL_LEAK_Delta = StsGetParam(funcindex, "VRECT_VOUT_FINAL_LEAK_Delta");
    CParam *VRECT_COMM1_FINAL_LEAK_Delta = StsGetParam(funcindex, "VRECT_COMM1_FINAL_LEAK_Delta");
    CParam *VRECT_COMM2_FINAL_LEAK_Delta = StsGetParam(funcindex, "VRECT_COMM2_FINAL_LEAK_Delta");
    CParam *INTB_FINAL_LEAK_Delta = StsGetParam(funcindex, "INTB_FINAL_LEAK_Delta");
    CParam *SINK_FINAL_LEAK_Delta = StsGetParam(funcindex, "SINK_FINAL_LEAK_Delta");
    CParam *SCL_FINAL_LEAK_Delta = StsGetParam(funcindex, "SCL_FINAL_LEAK_Delta");
    CParam *SDA_FINAL_LEAK_Delta = StsGetParam(funcindex, "SDA_FINAL_LEAK_Delta");
    CParam *COMM1_FINAL_LEAK_Delta = StsGetParam(funcindex, "COMM1_FINAL_LEAK_Delta");
    CParam *COMM2_FINAL_LEAK_Delta = StsGetParam(funcindex, "COMM2_FINAL_LEAK_Delta");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here

	cbit.SetOn(K2_VRECT_V5V_CAP, -1);
	dioplus.I2CConnect();
	wait_relay();

	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_us(500);

	VRECT.Set(FV, 5.5, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(2);

	//AC1 HS Leakage
	manager.setfields({ { FORCE_RECT_LS_OFF, 1 }, { FORCE_RECT_HS_OFF, 1 } });
	delay_us(500);

	VRECT.Set(FV, 11, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	AC1.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(10);//拉低AC
	AC1.Set(FV, 0, FOVI_20V, FOVI_100UA, RELAY_ON);
	delay_ms(30);//等待AC稳定

	AC1.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = AC1.GetMeasResult(site, MIRET);
		adresult1[site] = AC1_HS_init[site] - adresult[site];

		AC1_HS_FINAL_LEAK->SetTestResult(site, 0, adresult[site] * 1E+6);
		AC1_HS_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+6);

	}

	//AC1 LS Leakage
	AC1.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_us(100);

	AC1.Set(FV, 11, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	delay_ms(1);
	AC1.Set(FV, 11, FOVI_20V, FOVI_100UA, RELAY_ON);
	delay_ms(10);//wait current stable
	AC1.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = AC1.GetMeasResult(site, MIRET);
		adresult1[site] = AC1_LS_init[site] - adresult[site];
		AC1_LS_FINAL_LEAK->SetTestResult(site, 0, adresult[site] * 1E+6);
		AC1_LS_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+6);
	}
	AC1.Set(FV, 11, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	AC1.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	AC1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_us(100);
	AC1.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_OFF);
	delay_us(100);

	//AC2 HS Leakage
	//VRECT.Set(FV, 5.5, FOVI_20V, FOVI_100MA, RELAY_ON);
	//manager.setfields({ { FORCE_RECT_LS_OFF, 1 }, { FORCE_RECT_HS_OFF, 1 } });
	//delay_us(500);

	//VRECT.Set(FV, 11, FOVI_20V, FOVI_100MA, RELAY_ON);
	AC2.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	AC2.Set(FV, 0, FOVI_20V, FOVI_100UA, RELAY_ON);
	delay_ms(30);

	AC2.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = AC2.GetMeasResult(site, MIRET);
		adresult1[site] = AC2_HS_init[site] - adresult[site];
		AC2_HS_FINAL_LEAK->SetTestResult(site, 0, adresult[site] * 1E+6);
		AC2_HS_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+6);
	}

	//AC2 LS Leakage
	AC2.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_us(100);

	AC2.Set(FV, 11, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	delay_ms(2);
	AC2.Set(FV, 11, FOVI_20V, FOVI_100UA, RELAY_ON);
	delay_ms(10);//wait current stable
	AC2.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = AC2.GetMeasResult(site, MIRET);
		adresult1[site] = AC2_LS_init[site] - adresult[site];
		AC2_LS_FINAL_LEAK->SetTestResult(site, 0, adresult[site] * 1E+6);
		AC2_LS_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+6);
	}
	AC2.Set(FV, 11, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_us(500);
	AC2.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	delay_ms(1);
	AC2.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	delay_us(500);

	//VRECT-VOUT Leakage, VRECT=17V

	TM_ENTER_vi(VRECT, 5.5, FOVI_20V, FOVI_100MA);
	VOUT.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);

	manager.setfields({ { FORCE_DMY_OFF, 1 }, { I2C_ILOAD_H, 1 } });
	delay_ms(1);

	VRECT.Set(FV, 11, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	VOUT.Set(FV, 0, FOVI_5V, FOVI_100UA, RELAY_ON);
	delay_ms(2);

	VOUT.MeasureVI(50, 10);

	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = VOUT.GetMeasResult(site, MIRET);
		adresult1[site] = VRECT_VOUT_init[site] - adresult[site];

		VRECT_VOUT_FINAL_LEAK_11V->SetTestResult(site, 0, adresult[site] * 1E+6);
		VRECT_VOUT_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+6);
	}
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	VOUT.Set(FV, 0, FOVI_5V, FOVI_100UA, RELAY_OFF);
	delay_us(500);

	//VRECT-COMM1 Leakage, VRECT=17V
	cbit.SetOn(K2_VRECT_V5V_CAP, K_OVI_CHB, -1);//FOVI connect SCL, SDA, COMM1, COMM2
	wait_relay();
	TM_ENTER_vi(VRECT, 5.5, FOVI_20V, FOVI_100MA);
	manager.setfields({ { FORCE_DMY_OFF, 1 }, { I2C_ILOAD_H, 1 } });
	delay_ms(1);

	VRECT.Set(FV, 11, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	COMM1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	COMM1.Set(FV, 0, FOVI_5V, FOVI_1UA, RELAY_ON);
	delay_ms(1);

	COMM1.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = COMM1.GetMeasResult(site, MIRET);
		adresult1[site] = VRECT_COMM1_init[site] - adresult[site];
		VRECT_COMM1_FINAL_LEAK_11V->SetTestResult(site, 0, adresult[site] * 1E+9);
		VRECT_COMM1_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+9);
	}
	COMM1.Set(FV, 0, FOVI_5V, FOVI_1UA, RELAY_OFF);
	delay_us(500);

	//VRECT-COMM2 Leakage, VRECT=17V
	COMM2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	COMM2.Set(FV, 0, FOVI_5V, FOVI_1UA, RELAY_ON);
	delay_ms(1);

	COMM2.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = COMM2.GetMeasResult(site, MIRET);
		adresult1[site] = VRECT_COMM2_init[site] - adresult[site];
		VRECT_COMM2_FINAL_LEAK_11V->SetTestResult(site, 0, adresult[site] * 1E+9);
		VRECT_COMM2_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+9);
	}
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(2);
	COMM2.Set(FV, 0, FOVI_5V, FOVI_1UA, RELAY_OFF);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	delay_us(500);

	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 } });
	dioplus.I2CDisconnect();

	//INTB Leakage
	INTB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(1000);

	INTB.Set(FV, 5, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	INTB.Set(FV, 5, FOVI_10V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	INTB.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = INTB.GetMeasResult(site, MIRET);
		adresult1[site] = INTB_init[site] - adresult[site];
		INTB_FINAL_LEAK_DS->SetTestResult(site, 0, adresult[site] * 1E+9);
		INTB_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+9);
	}
	INTB.Set(FV, 5, FOVI_10V, FOVI_10UA, RELAY_ON);
	delay_us(500);
	INTB.Set(FV, 5, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	INTB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	INTB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	//SINK Leakage
	SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	SINK.Set(FV, 11, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	SINK.Set(FV, 11, FOVI_20V, FOVI_1UA, RELAY_ON);
	delay_ms(1);
	SINK.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = SINK.GetMeasResult(site, MIRET);
		adresult1[site] = SINK_init[site] - adresult[site];

		SINK_FINAL_LEAK->SetTestResult(site, 0, adresult[site] * 1E+9);
		SINK_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+9);
	}
	SINK.Set(FV, 11, FOVI_20V, FOVI_10UA, RELAY_ON);
	delay_us(500);
	SINK.Set(FV, 11, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	SINK.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);

	//SCL Leakage
	SCL.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	SCL.Set(FV, 5, FOVI_10V, FOVI_10MA, RELAY_ON, 1);
	delay_ms(1);
	SCL.Set(FV, 5, FOVI_10V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	SCL.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = SCL.GetMeasResult(site, MIRET);
		adresult1[site] = SCL_init[site] - adresult[site];
		SCL_FINAL_LEAK_DS->SetTestResult(site, 0, adresult[site] * 1E+9);
		SCL_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+9);
	}
	SCL.Set(FV, 5, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_us(100);
	SCL.Set(FV, 5, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_us(100);
	SCL.Set(FV, 5, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);
	SCL.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	SCL.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	//SDA Leakage
	SDA.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	SDA.Set(FV, 5, FOVI_10V, FOVI_10MA, RELAY_ON, 1);
	delay_ms(1);
	SDA.Set(FV, 5, FOVI_10V, FOVI_1UA, RELAY_ON);
	delay_us(500);
	SDA.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = SDA.GetMeasResult(site, MIRET);
		adresult1[site] = SDA_init[site] - adresult[site];
		SDA_FINAL_LEAK_DS->SetTestResult(site, 0, adresult[site] * 1E+9);
		SDA_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+9);
	}
	SDA.Set(FV, 5, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_us(100);
	SDA.Set(FV, 5, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_us(100);
	SDA.Set(FV, 5, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(100);
	SDA.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	TM_EXIT_vi(V5V, 5, FOVI_10V, FOVI_100MA);
	SDA.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	dioplus.I2CConnect();
	TM_ENTER_vi(VRECT, 5.5, FOVI_20V, FOVI_100MA);
	manager.setfields({ { I2C_CTRL, 1 }, { I2C_EN_LDO1, 1 }, { I2C_EN_OSC, 1 } });
	VRECT.Set(FV, 11, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	delay_us(500);

	//COMM1 Leakage
	COMM1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	COMM1.Set(FV, 11, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	COMM1.Set(FV, 11, FOVI_20V, FOVI_1UA, RELAY_ON);
	delay_ms(2);
	COMM1.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = COMM1.GetMeasResult(site, MIRET);
		adresult1[site] = COMM1_init[site] - adresult[site];

		COMM1_FINAL_LEAK->SetTestResult(site, 0, adresult[site] * 1E+9);
		COMM1_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+9);
	}
	COMM1.Set(FV, 11, FOVI_20V, FOVI_10UA, RELAY_ON);
	delay_us(500);
	COMM1.Set(FV, 11, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	COMM1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(2000);
	COMM1.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);

	//COMM2 Leakage
	COMM2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	COMM2.Set(FV, 11, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	COMM2.Set(FV, 11, FOVI_20V, FOVI_1UA, RELAY_ON);
	delay_ms(2);
	COMM2.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = COMM2.GetMeasResult(site, MIRET);
		adresult1[site] = COMM2_init[site] - adresult[site];
		COMM2_FINAL_LEAK->SetTestResult(site, 0, adresult[site] * 1E+9);
		COMM2_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+9);
	}
	COMM2.Set(FV, 11, FOVI_20V, FOVI_10UA, RELAY_ON);
	delay_us(500);
	COMM2.Set(FV, 11, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_ms(1);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	COMM2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_ON);
	delay_us(2000);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	COMM2.Set(FV, 0, FOVI_20V, FOVI_10MA, RELAY_OFF);
	cbit.SetOn(K2_VRECT_V5V_CAP, K3_VOUT_CAP, K4_IIC_PULLUP, - 1);//FOVI connect AC1, AC2, ENB, VOUT

	//ENB Leakage
	ENB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	ENB.Set(FV, 5, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(2);
	ENB.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = ENB.GetMeasResult(site, MIRET);
		adresult1[site] = ENB_init[site] - adresult[site];

		ENB_FINAL_LEAK->SetTestResult(site, 0, adresult[site] * 1E+6);
		ENB_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+6);
	}
	ENB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	ENB.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	//V5V Leakage	
	//VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//delay_us(500);

	V5V.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(1);
	manager.setfields({ { FORCE_DMY_OFF, 1 } });
	VRECT.Set(FV, 5, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_ms(2);

	V5V.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = V5V.GetMeasResult(site, MIRET);
		adresult1[site] = V5V_init[site] - adresult[site];

		V5V_FINAL_LEAK->SetTestResult(site, 0, adresult[site] * 1E+3);
		V5V_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+3);
	}
	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	delay_us(500);
	VRECT.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);//OFF，否则影响VOUT leakage

	//VOUT Leakage
	TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);

	manager.setfields({ { I2C_CTRL, 1 }, { FORCE_DMY_OFF, 1 } });
	VRECT.Set(FV, 9, FOVI_20V, FOVI_100MA, RELAY_ON, 1);
	VOUT.Set(FV, 9, FOVI_20V, FOVI_100MA, RELAY_ON, 1); 
	delay_us(500);

	VOUT.Set(FV, 9, FOVI_20V, FOVI_10MA, RELAY_ON, 0.5);
	delay_ms(2);
	VOUT.MeasureVI(50, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = VOUT.GetMeasResult(site, MIRET);
		adresult1[site] = VOUT_init[site] - adresult[site];

		VOUT_FINAL_LEAK->SetTestResult(site, 0, adresult[site] * 1E+6);
		VOUT_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+6);
	}
	VOUT.Set(FV, 9, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
	delay_us(500);
	//VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	//V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	//VOUT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	//delay_us(500);
	//
	//VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	//VOUT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);//NEED OFF

	//VRECT Leakage
	//TM_ENTER_vi(V5V, 5, FOVI_10V, FOVI_100MA);	
	manager.setfields({ { I2C_CTRL, 1 }, { FORCE_DMY_OFF, 1 }, { I2C_DIS_OVP_FAST, 1 } });
	delay_us(500);

	VRECT.Set(FV, 11, FOVI_20V, FOVI_100MA, RELAY_ON, 2);
	V5V.Set(FV, 5.1, FOVI_10V, FOVI_100MA, RELAY_ON);
	VOUT.Set(FV, 5.1, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(1);

	VRECT.Set(FV, 11, FOVI_20V, FOVI_10MA, RELAY_ON, 0.5);//need 10mA RANGE to save delay time
	delay_ms(15);//need, add cap

	VRECT.MeasureVI(100, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = VRECT.GetMeasResult(site, MIRET);
		adresult1[site] = VRECT_init[site] - adresult[site];

		VRECT_FINAL_LEAK->SetTestResult(site, 0, adresult[site] * 1E+6);
		VRECT_FINAL_LEAK_Delta->SetTestResult(site, 0, adresult1[site] * 1E+6);
	}
	VRECT.Set(FV, 11, FOVI_20V, FOVI_100MA, RELAY_ON, 0.5);
	delay_us(200);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON, 0.5);
	VOUT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_ON);
	delay_ms(1);
	VRECT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	V5V.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	VOUT.Set(FV, 0, FOVI_20V, FOVI_100MA, RELAY_OFF);
	cbit.SetOn(-1);
	dioplus.I2CDisconnect();


    return 0;
}
 
DUT_API int FINAL_OS(short funcindex, LPCTSTR funclabel)
{
//{{AFX_STS_PARAM_PROTOTYPES
    CParam *VRECT_FINAL_OS = StsGetParam(funcindex, "VRECT_FINAL_OS");
    CParam *V5V_FINAL_OS = StsGetParam(funcindex, "V5V_FINAL_OS");
    CParam *INTB_FINAL_OS = StsGetParam(funcindex, "INTB_FINAL_OS");
    CParam *SINK_FINAL_OS = StsGetParam(funcindex, "SINK_FINAL_OS");
    CParam *AC1_FINAL_OS = StsGetParam(funcindex, "AC1_FINAL_OS");
    CParam *AC2_FINAL_OS = StsGetParam(funcindex, "AC2_FINAL_OS");
    CParam *ENB_FINAL_OS = StsGetParam(funcindex, "ENB_FINAL_OS");
    CParam *VOUT_FINAL_OS = StsGetParam(funcindex, "VOUT_FINAL_OS");
    CParam *SCL_FINAL_OS = StsGetParam(funcindex, "SCL_FINAL_OS");
    CParam *SDA_FINAL_OS = StsGetParam(funcindex, "SDA_FINAL_OS");
    CParam *COMM1_FINAL_OS = StsGetParam(funcindex, "COMM1_FINAL_OS");
    CParam *COMM2_FINAL_OS = StsGetParam(funcindex, "COMM2_FINAL_OS");
    CParam *VRECT_AC1_FINAL_OS = StsGetParam(funcindex, "VRECT_AC1_FINAL_OS");
    CParam *VRECT_AC2_FINAL_OS = StsGetParam(funcindex, "VRECT_AC2_FINAL_OS");
    CParam *VRECT_VOUT_FINAL_OS = StsGetParam(funcindex, "VRECT_VOUT_FINAL_OS");
    CParam *VRECT_V5V_FINAL_OS = StsGetParam(funcindex, "VRECT_V5V_FINAL_OS");
    CParam *VRECT_COMM1_FINAL_OS = StsGetParam(funcindex, "VRECT_COMM1_FINAL_OS");
    CParam *VRECT_COMM2_FINAL_OS = StsGetParam(funcindex, "VRECT_COMM2_FINAL_OS");
//}}AFX_STS_PARAM_PROTOTYPES
    // TODO: Add your function code here
	double	i_1mA = -1e-3;
	ALLPINS_INITIALIZE_0V_2V_10MA_ON();
	FOVI_ALL.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	FOVI_ALL.Set(FI, i_1mA, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	FOVI_ALL.MeasureVI(10, 20);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = VRECT.GetMeasResult(site, MVRET);
		VRECT_FINAL_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = V5V.GetMeasResult(site, MVRET);
		V5V_FINAL_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = INTB.GetMeasResult(site, MVRET);
		INTB_FINAL_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = SINK.GetMeasResult(site, MVRET);
		SINK_FINAL_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = AC1.GetMeasResult(site, MVRET);
		AC1_FINAL_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = AC2.GetMeasResult(site, MVRET);
		AC2_FINAL_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = ENB.GetMeasResult(site, MVRET);
		ENB_FINAL_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = VOUT.GetMeasResult(site, MVRET);
		VOUT_FINAL_OS->SetTestResult(site, 0, adresult[site]);
	}
	FOVI_ALL.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	FOVI_ALL.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);

	cbit.SetOn(K8_OVI4_AC1_SCL, K9_OVI5_AC2_SDA, K10_OVI6_ENB_COMM1, K11_OVI7_VOUT_COMM2, -1);
	wait_relay();
	FOVI_CHB.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	FOVI_CHB.Set(FI, i_1mA, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(1000);
	FOVI_CHB.MeasureVI(10, 20);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = SCL.GetMeasResult(site, MVRET);
		SCL_FINAL_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = SDA.GetMeasResult(site, MVRET);
		SDA_FINAL_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = COMM1.GetMeasResult(site, MVRET);
		COMM1_FINAL_OS->SetTestResult(site, 0, adresult[site]);

		adresult[site] = COMM2.GetMeasResult(site, MVRET);
		COMM2_FINAL_OS->SetTestResult(site, 0, adresult[site]);
	}
	FOVI_CHB.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);
	FOVI_CHB.Set(FI, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);

	//VRECT-AC1
	cbit.SetOn(K12_PVI0H_VRECT, K15_PVI0L_AC1, -1);
	wait_relay();
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	VRECT.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_ON);
	delay_us(500);

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_AC1_FINAL_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	//VRECT-AC2
	cbit.SetOn(K12_PVI0H_VRECT, K16_PVI0L_AC2, -1);
	wait_relay();

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_AC2_FINAL_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	//VRECT-VOUT
	cbit.SetOn(K12_PVI0H_VRECT, K17_PVI0L_VOUT, -1);
	wait_relay();

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_VOUT_FINAL_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	//VRECT-V5V
	cbit.SetOn(K12_PVI0H_VRECT, K18_PVI0L_V5V, -1);
	wait_relay();

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_V5V_FINAL_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	//VRECT-COMM1
	cbit.SetOn(K12_PVI0H_VRECT, K27_PVI0L_COMM1, -1);
	wait_relay();

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_COMM1_FINAL_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	//VRECT-COMM2
	cbit.SetOn(K12_PVI0H_VRECT, K20_PVI0L_COMM2, -1);
	wait_relay();

	FPVI0.Set(FI, i_1mA, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);
	FPVI0.MeasureVI(20, 10);
	FOR_EACH_VALID_SITE(site)
	{
		adresult[site] = FPVI0.GetMeasResult(site, MVRET);
		VRECT_COMM2_FINAL_OS->SetTestResult(site, 0, adresult[site]);
	}
	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_ON);
	delay_us(1000);

	FPVI0.Set(FI, 0, FPVI10_2V, FPVI10_10MA, RELAY_OFF);
	VRECT.Set(FV, 0, FOVI_2V, FOVI_10MA, RELAY_OFF);
	delay_us(500);
	cbit.SetOn(-1);

    return 0;
}
 

