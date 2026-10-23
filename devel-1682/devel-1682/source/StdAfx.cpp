// stdafx.cpp : source file that includes just the standard includes
//	DUT.pch will be the pre-compiled header
//	stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
//
//void convert_dec_to_binary(int dec_num, int bit_size, char* abinary_arry)
//{
//
//	for (int i = 0; i < bit_size + 1; i++)
//	{
//		abinary_arry[i] = (dec_num % 2) + 48;//转化为0或1对应的ASCII码
//		dec_num = dec_num / 2;
//		if (i == (bit_size))
//		{
//			abinary_arry[i] = '\0';
//		}
//	}
//}
//
////-----------------------------------------ININREADER-------------------------------------------//
////#define _CRT_SECURE_NO_WARNINGS
//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
//#include"StdAfx.h"
//#include <stdlib.h>
//#include <stdio.h>
//#include <float.h>
////#include <math.h>
//#include <assert.h>
//
////#include "treg.h"
////#include "inireader.h"
//#include<string>
//#include <windows.h>
//#include <ctime>
//static void   strcat_dynamic(char **destination, const char *source);
//static void   clean(char **source);
//static int    cmpstr(const char *str1, const char *str2);
//int sites = 0;

//BC_Data::BC_Data()
//{
//
//	Print_BC_Start_information();
//	char File_Path[512] = "";
//	char File_Name[512] = "F16821_Board_Check_Results";
//	char txt_format[10] = "TXT";
//	time_t  Now = time(0);
//	char currentTime[128] = "";
//	strcat(currentTime, ctime(&Now));
//	strncat(File_Name, currentTime, 128);
//	strncat(File_Name, txt_format, 10);
//	for (int i = 0; i < 512; i++)
//	{
//		if (File_Name[i] == ' ' || File_Name[i] == ':')
//		{
//			File_Name[i] = '_';
//		}
//		if (File_Name[i] == '\n')
//		{
//			File_Name[i] = '.';
//		}
//	}
//	STSGetPgsPath(File_Path, 512);//Get boardcheck datalog stroge addres
//	//STSCBGetSaveFilePath(File_Path, 512);//Get boardcheck datalog stroge addres
//	//STSGetPgsPath(File_Path, 512);//Get boardcheck datalog stroge address
//
//	strncat(File_Path, File_Name, 512);//Merge stroge  address and file name
//
//	for (int i = 0; i < 512; i++)
//	{
//		file_path_name[i] = File_Path[i];
//	}
//
//
//
//	FILE *fptr;
//
//	fptr = fopen(file_path_name, "w");//Clear document
//	fclose(fptr);
//	fptr = fopen(file_path_name, "a+");//open document
//	fprintf(fptr, "Test Name ");
//	for (int i = 0; i < 256; i++)
//	{
//		fprintf(fptr, " ");
//	}
//	fprintf(fptr, "\t\t TestValue");
//	fprintf(fptr, " \tUnit \tLowerLimit \tUpperLimit\n");
//	fclose(fptr);
//}
//
//BC_Data::~BC_Data()
//{
//	printf_s("\n");
//	printf_s("---\n");
//	printf_s("--------Board Check 已经完成, 本窗口将在3秒后关闭--------\n");
//	printf_s("\n");
//	printf_s("\n");
//	if (ClassFailCount == 0)
//	{
//		printf_s("Board Check 测试结果是  <<<<<<<< Pass  >>>>>>>>>\n");
//	}
//	else
//	{
//		printf_s("Board Check 测试结果是  <<<<<<<< Fail  >>>>>>>>>\n");
//	}
//	printf_s("\n");
//	printf_s("\n");
//	printf_s("----Board Check already finished, Current window will close in 5 seconds ----\n");
//	delay_ms(5000);
//
//	fclose(stdout);
//	FreeConsole();
//
//}
//void BC_Data::Save_data_into_file(string bc_name, double *bc_results, string bc_unit, double bc_lowlimit, double bc_upperlimit)
//{
//
//	Up_limit = bc_upperlimit;
//	Low_limit = bc_lowlimit;
//	FOR_EACH_SITE(sites, SITE_NUM)
//	{
//		Test_results[sites] = bc_results[sites];
//	}
//
//	strcpy_s(Test_Name, bc_name.c_str());
//	strcpy_s(Test_Unit, bc_unit.c_str());
//
//	int testname_size = 0;
//	int find_flag = 0;
//	for (int i = 0; i < 256; i++)
//	{
//		if (Test_Name[i] == '\0' && find_flag == 0)
//		{
//			testname_size = i;
//			find_flag = 1;
//		}
//	}
//
//
//	FILE *fptr;
//	FOR_EACH_SITE(sites, SITE_NUM)
//	{
//		fptr = fopen(file_path_name, "a+");//open document
//		fprintf(fptr, "%s", Test_Name);
//		for (int i = 0; i < 256 - testname_size; i++)
//		{
//			fprintf(fptr, " ");
//		}
//		fprintf(fptr, " sites[%d]", sites + 1);
//		if (sites < 9)
//		{
//			fprintf(fptr, " ");
//		}
//		if (Test_results[sites]<Up_limit &&Test_results[sites]>Low_limit)
//		{
//			fprintf(fptr, " check Passed,  Value is \t %6.3f \t %s \t %6.3f \t %6.3f\n", Test_results[sites], Test_Unit, Low_limit, Up_limit);
//			BC_Fail[sites] = false;
//			PF_Results_Array[nSum][sites] = true;
//			PF_Name_array[nSum] = bc_name;
//		}
//		else
//		{
//			fprintf(fptr, " check Failed,  Value is \t %6.3f \t %s \t %6.3f \t %6.3f\n", Test_results[sites], Test_Unit, Low_limit, Up_limit);
//			BC_Fail[sites] = true;
//			ClassFailCount++;
//			PF_Results_Array[nSum][sites] = false;
//			PF_Name_array[nSum] = bc_name;
//		}
//		fclose(fptr);
//	}
//
//	nSum++;
//
//}
//
//void BC_Data::Save_data_into_file(string bc_name, double *bc_results, int bc_unit, double bc_lowlimit, double bc_upperlimit)
//{
//
//	Up_limit = bc_upperlimit;
//	Low_limit = bc_lowlimit;
//	FOR_EACH_SITE(sites, SITE_NUM)
//	{
//		Test_results[sites] = bc_results[sites];
//	}
//
//	strcpy_s(Test_Name, bc_name.c_str());
//	if (bc_unit == 1)
//	{
//		string unit_temp = "Ohm";
//		strcpy_s(Test_Unit, unit_temp.c_str());
//	}
//	if (bc_unit == 2)
//	{
//		string unit_temp = "KOhm";
//		strcpy_s(Test_Unit, unit_temp.c_str());
//	}
//	if (bc_unit == 3)
//	{
//		string unit_temp = "nF";
//		strcpy_s(Test_Unit, unit_temp.c_str());
//	}
//	if (bc_unit == 4)
//	{
//		string unit_temp = "uF";
//		strcpy_s(Test_Unit, unit_temp.c_str());
//	}
//	if (bc_unit == 5)
//	{
//		string unit_temp = "V";
//		strcpy_s(Test_Unit, unit_temp.c_str());
//	}
//	if (bc_unit == 6)
//	{
//		string unit_temp = "mA";
//		strcpy_s(Test_Unit, unit_temp.c_str());
//	}
//	if (bc_unit == 7)
//	{
//		string unit_temp = "uA";
//		strcpy_s(Test_Unit, unit_temp.c_str());
//	}
//	if (bc_unit == 8)
//	{
//		string unit_temp = "PF";
//		strcpy_s(Test_Unit, unit_temp.c_str());
//	}
//
//
//
//
//
//	int testname_size = 0;
//	int find_flag = 0;
//	for (int i = 0; i < 256; i++)
//	{
//		if (Test_Name[i] == '\0' && find_flag == 0)
//		{
//			testname_size = i;
//			find_flag = 1;
//		}
//	}
//
//
//	FILE *fptr;
//	FOR_EACH_SITE(sites, SITE_NUM)
//	{
//		fptr = fopen(file_path_name, "a+");//open document
//		fprintf(fptr, "%s", Test_Name);
//		for (int i = 0; i < 256 - testname_size; i++)
//		{
//			fprintf(fptr, " ");
//		}
//		fprintf(fptr, " sites[%d]", sites + 1);
//		if (sites < 9)
//		{
//			fprintf(fptr, " ");
//		}
//		if (Test_results[sites]<Up_limit &&Test_results[sites]>Low_limit)
//		{
//			fprintf(fptr, " check Passed,  Value is      %f      %s ,      %f      %f\n", Test_results[sites], Test_Unit, Low_limit, Up_limit);
//			BC_Fail[sites] = false;
//			PF_Results_Array[nSum][sites] = true;
//			PF_Name_array[nSum] = bc_name;
//		}
//		else
//		{
//			fprintf(fptr, "  check Failed,  Value is      %f      %s ,        %f     %f\n", Test_results[sites], Test_Unit, Low_limit, Up_limit);
//			BC_Fail[sites] = true;
//			ClassFailCount++;
//			PF_Results_Array[nSum][sites] = false;
//			PF_Name_array[nSum] = bc_name;
//		}
//		//fclose(fptr);
//	}
//
//	nSum++;
//
//}
//
//int BC_Data::ClassFailCount = 0;
//int BC_Data::nSum = 0;
//bool BC_Data::PF_Results_Array[4096][MS_MAX_SITES] = { 0 };
//string BC_Data::PF_Name_array[4096] = {};
//
//void BC_Data::Print_BC_Start_information()
//{
//	if (AllocConsole())//(AttachConsole(ATTACH_PARENT_PROCESS))//
//	{
//		SetConsoleTitleA("AccoTEST Debug Window");
//		freopen("conout$", "w+t", stdout);
//		::DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
//	}
//	printf_s("----------------------Reminder---提示窗----------------------\n");
//	printf_s("---------------------\n");
//	printf_s("---------------------\n");
//	printf_s("---------------------\n");
//	printf_s("---------------------\n");
//	printf_s("---------------------正在执行Board check, 请等待,---------------------执行完成后窗口自动关闭。--------------------- \n");
//	printf_s("---------------------\n");
//	printf_s("--------------------------Board check is  performing,  please wait until Board Check Done-----------------------------\n");
//
//
//}
//void BC_Data::Printf_BC_Finish_information()
//{
//	char Log_Fail_Name[256];
//	char Log_Fail_results[10];
//	for (int i = 0; i < 10; i++)
//	{
//		FOR_EACH_SITE(sites, SITE_NUM)
//		{
//			strcpy(Log_Fail_results, "Passed");//add items result init
//			strcpy_s(Log_Fail_Name, PF_Name_array[i].c_str());
//			if (PF_Results_Array[i][sites] == 0)
//			{
//				strcpy(Log_Fail_results, "Failed");
//			}
//			printf_s("BoardCheck:  sites[%d]  Components << %s >>  Check Results is:   <%s> \n", sites + 1, Log_Fail_Name, Log_Fail_results);
//		}
//	}
//	//printf_s("\n");
//	//printf_s("---\n");
//	//printf_s("----Board Check 已经完成,， 本窗口将在3秒后关闭。。。。。\n");
//	//printf_s("\n");
//	//printf_s("\n");
//	//if (ClassCount == 0)
//	//{
//	//	printf_s("Board Check 测试结果是  <<<<<<<< Pass  >>>>>>>>>\n");
//	//}
//	//else
//	//{
//	//	printf_s("Board Check 测试结果是  <<<<<<<< Fail  >>>>>>>>>\n");
//	//}
//	//printf_s("\n");
//	//printf_s("\n");
//	//printf_s("----Board Check already finished, Current window will close in 3 second 。。。。。\n");
//	//delay_ms(3000);
//
//	//fclose(stdout);
//	//FreeConsole();
//}
//// TODO: reference any additional headers you need in STDAFX.H
//// and not in this file
