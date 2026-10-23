// F16821.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
extern "C" int GetPgsFullPath(LPTSTR pgsPath, int chNum);  //here error


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
    }
	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
DUT_API void UserInit()
{
	bool TestTypeloadWrong = true;
	bool PNloadWrong = true;
	char PnData[256] = { 0 };
	char PnLable[256] = { 0 };
	char TestTypeData[256] = { 0 };

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

	if (STSGetUserPriority() == 1) {//OPERATOR=1/ENGINEER=2/ADMIN=3
		//if (1){//OPERATOR=1/ENGINEER=2/ADMIN=3

		//STSGetSTDInfo(MIR_PART_TYP, PnData, PnLable);// MIR_PART_TYP confuse with DUT_Name
		STSGetSTDInfo(MIR_PROT_COD, PnData, PnLable);//  Change from PART_TYP to PROT_COD

		if ((strcmp(PnData, "NU1682PCNB-AAA0-FT") == 0) || (strcmp(PnData, "NU1682PCNB-ABA0-FT") == 0))
		{
			spec.select_device("NU1682");
			pathoftreg = pathofpgs + "\\NU1682.treg";
			dut.init(pathoftreg.c_str(), SITE_NUM, QC, DO_TRIM);
			PNloadWrong = false;

		}
		else if ((strcmp(PnData, "NU1685PCNB-AAA0-FT") == 0) || (strcmp(PnData, "NU1685PCNB-ABA0-FT") == 0))
		{
			spec.select_device("NU1685");
			pathoftreg = pathofpgs + "\\NU1685.treg";
			dut.init(pathoftreg.c_str(), SITE_NUM, QC, DO_TRIM);
			PNloadWrong = false;

		}
		else if ((strcmp(PnData, "NU1687PCNB-AAA0-FT") == 0) || (strcmp(PnData, "NU1687PCNB-ABA0-FT") == 0))
		{
			spec.select_device("NU1687");
			pathoftreg = pathofpgs + "\\NU1687.treg";
			dut.init(pathoftreg.c_str(), SITE_NUM, QC, DO_TRIM);
			PNloadWrong = false;

		}
		else if ((strcmp(PnData, "NU1682APCNB-ABA0-FT") == 0))//V01 add NU1682A
		{
			spec.select_device("NU1682A");
			pathoftreg = pathofpgs + "\\NU1682A.treg";
			dut.init(pathoftreg.c_str(), SITE_NUM, QC, DO_TRIM);
			PNloadWrong = false;

		}
		const char* partid = spec.get_device_str();//partid=NU1682/NU1685/NU1687

		if (PNloadWrong)
		{
			StsMessageBox("Could not parse part number", "Error Message", MB_OK | MB_ICONSTOP);
			exit(0);
		}
		// =======check FT/RT/QC=======================
		STSGetSTDInfo(MIR_TEST_COD, TestTypeData, PnLable);
		if (strcmp(TestTypeData, "FT") == 0 || strcmp(TestTypeData, "RT") == 0)
		{
			Global_FTQC_FLAG = 0;
			TestTypeloadWrong = false;
			TempCharGP = 3;//25
			STSSetUseLimitbyName("FT");//Limit select
		}
		else if (strcmp(TestTypeData, "QC") == 0)
		{
			Global_FTQC_FLAG = 1;
			TestTypeloadWrong = false;
			TempCharGP = 3;//25
			STSSetUseLimitbyName("QA");//Limit select
		}
		if (TestTypeloadWrong)
		{
			StsMessageBox("Could not parse Test Type", "Error Message", MB_OK | MB_ICONSTOP);
			exit(0);
		}

	}
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
DUT_API void UserExit()
{		
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
DUT_API void OnSot()
{
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

DUT_API void BinOutDut()
{	
	dut.eot();
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
DUT_API void OnNewLot(const char *Lotid)
{
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
DUT_API void OnWaferEnd(const char *Lotid)
{			
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
DUT_API void UserInitAfterLoad()
{
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

