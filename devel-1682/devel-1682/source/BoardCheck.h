/*****************************************************************************
*                                                                            *
*       Source title:   BoardCheck.h                                         *
*                       (board checker for AccoTest programs)                *
*         Written by:	    				                                 *
*        Description:					                                     *
*                                                                            *
*   Revision History:                                                        *
*                                                                            *
*     mm/dd/yy  r.rr  - Original coding.                                     *
*                                                                            *
*****************************************************************************/

/*
REVISION BLOCK:
-Rev. -- Date -------------------------------------------------------------------------------
1  8/20/25   upgrade to 8200 Xina
----------------------------------------------------------------------------------------------
*/


#pragma once
#include "stdafx.h"
#include <map>
#include <vector>
#include <string>
#include <Windows.h>
#include <iostream>
#include <type_traits> // 用于类型特征识别

using namespace std;

#define BTN_REDO 2000
#define BTN_EXIT 2001
#define BTN_NONE 2002
#define BTN_CANCEL 2003

#define SITE_NUM 8

struct MyData {
	bool check_status;
	double  test_data;
	double  high_limit;
	double  low_limit;
	string unit;
	string flag;
};

enum PULLUP_FLAG
{
	PULL_UP,
	PULL_DOWN
};

//class CBIT_LIB
//{
//
//public:
//	void create_data_block(string str_1, ...);
//	void updateBoardCheckResults(string  str_input, bool *chk_status, double *test_value);
//	void set_data_after_boardcheck(double *test_value, double hlimit, double llimit, bool *check_stat);
//private:
//	map<string, MyData>m_boardcheck_results[SITE_NUM];
//	double m_test_value[SITE_NUM];
//	double m_hlimit;
//	double m_llimit;
//	double m_check_stat[SITE_NUM];
//};



class DialogTemplate;

class DialogTemplate
{
public:
	DialogTemplate(LPCSTR caption, DWORD style);

	DialogTemplate(LPCSTR caption, DWORD style, int x, int y, int w, int h,
		LPCSTR font = NULL, WORD fontSize = 8);
	void AddComponent(LPCSTR type, LPCSTR caption, DWORD style, DWORD exStyle,
		int x, int y, int w, int h, WORD id);
	void AddButton(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
		int w, int h, WORD id);
	void AddEditBox(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
		int w, int h, WORD id);
	void AddStatic(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
		int w, int h, WORD id);
	void AddListBox(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
		int w, int h, WORD id);
	void AddScrollBar(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
		int w, int h, WORD id);
	void AddComboBox(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
		int w, int h, WORD id);
	operator const DLGTEMPLATE*() const;
	virtual ~DialogTemplate();

protected:
	// Prevent copying and assignments (by private definition)
	DialogTemplate operator=(const DialogTemplate &x) { return *this; }
	DialogTemplate(DialogTemplate &x) {}

	void AddStandardComponent(WORD type, LPCSTR caption, DWORD style,
		DWORD exStyle, int x, int y, int w, int h, WORD id);
	void AlignData(int size);
	void AppendString(LPCSTR string);
	void AppendData(void* data, int dataLength);
	void EnsureSpace(int length);

private:

	DLGTEMPLATE* dialogTemplate;
	int totalBufferLength;
	int usedBufferLength;

};


////////////////
//
// Base classes For Windows interface
//
////////////////
class BoardCheckElement
{
public:
	virtual ~BoardCheckElement() {};
	virtual void get(HWND hDlg) = 0;
	virtual void set(HWND hDlg) = 0;
	virtual void dlg_file(HWND hDlg, char *fname, int len) = 0;
	virtual int width() = 0;
	virtual int height() = 0;
	virtual void create_dialog(DialogTemplate *dialog, int x, int y, int *newid) = 0;
	virtual void command(HWND hDlg, int code, int target_id) {};
	int id;
	static int tagged_filename;     // Allow tags names in file name components
};
typedef BoardCheckElement *LPBoardCheckElement;


class BoardCheckButton : public BoardCheckElement
{
public:
	BoardCheckButton(char *aname, int aid, int def_style = BS_PUSHBUTTON);
	virtual ~BoardCheckButton();
	virtual int width();
	virtual int height();
	virtual void get(HWND hDlg) {};
	virtual void set(HWND hDlg) {};
	virtual void dlg_file(HWND hDlg, char *fname, int len) {};
	virtual void create_dialog(DialogTemplate *dialog, int x, int y, int *newid);
protected:
	// Prevent copying and assignments (by private definition)
	BoardCheckButton operator=(const BoardCheckButton &x) { return *this; }
	BoardCheckButton(BoardCheckButton &x) {}
	char *name;
	int style;
};


class BoardCheckListBox : public BoardCheckElement
{
public:
	BoardCheckListBox(char *aname, int aid, int def_style = LBS_NOTIFY | WS_VSCROLL | WS_BORDER);
	virtual ~BoardCheckListBox();
	virtual int width();
	virtual int height();
	virtual void get(HWND hDlg) {};
	virtual void set(HWND hDlg) {};
	virtual void dlg_file(HWND hDlg, char *fname, int len) {};
	virtual void create_dialog(DialogTemplate *dialog, int x, int y, int *newid);
	//virtual void command(HWND hDlg,int code,int target_id);
protected:
	// Prevent copying and assignments (by private definition)
	BoardCheckListBox operator=(const BoardCheckListBox &x) { return *this; }
	BoardCheckListBox(BoardCheckListBox &x) {}
	char *name;
	int style;
};

class BoardCheckGroup : public BoardCheckElement
{
public:
	BoardCheckGroup(int vertical, int aospace, int aispace);
	virtual ~BoardCheckGroup();
	void add(BoardCheckElement *el);
	virtual int width();
	virtual int height();
	virtual void get(HWND hDlg);
	virtual void set(HWND hDlg);
	virtual void dlg_file(HWND hDlg, char *fname, int len);
	virtual void create_dialog(DialogTemplate *dialog, int x, int y, int *newid);
	virtual void command(HWND hDlg, int code, int target_id);
	int count();
protected:
	// Prevent copying and assignments (by private definition)
	BoardCheckGroup operator=(const BoardCheckGroup &x) { return *this; }
	BoardCheckGroup(BoardCheckGroup &x) {}
	int is_vertical;
	int no;
	int ospace;     // outer space (space to other elements)
	int ispace;     // inner space (space between elements)
	LPBoardCheckElement *member;
};


class CBC_log
{
public:
	CBC_log(void) {}
	~CBC_log(void) {}
	void clear(void) {
		component_vec.clear();
		tnum_map.clear();
		lolim_map.clear();
		hilim_map.clear();
		unit_map.clear();
		data_map.clear();
		flag_map.clear();
	}

	vector<string> component_vec;
	map<string, DWORD> tnum_map;				// map<component, test_number>
	map<string, double> lolim_map;				// map<component, low_lim>
	map<string, double> hilim_map;				// map<component, high_lim>
	map<string, string> unit_map;				// map<component, unit>
	map<string, map<DWORD, double>> data_map;	// map<component, map<site, data>>
	map<string, map<DWORD, string>> flag_map;	// map<component, map<site, pass or fail>>
};

class Cvi_config
{
public:
	Cvi_config(){
		mode = FV;
		v = 3;
		i = 0;
		v_range = FOVI_5V;
		i_range = FOVI_10MA;
		fpvi_v_range = FPVI10_5V;
		fpvi_i_range = FPVI10_10MA;
		i_range = FOVI_10MA;
		delay = 10; // ms
		sample_times = 100;
		sample_period = 10;	// us
	}

	void init(void){
		mode = FV;
		v = 3;
		i = 0;
		v_range = FOVI_5V;
		i_range = FOVI_10MA;
		delay = 10; // ms
		sample_times = 100;
		sample_period = 10;	// us	
	}
	void fovi_set(int mode_val = FV, double v_val = 3, double i_val = 0, FOVI_VRNG v_range_val = FOVI_5V, FOVI_IRNG i_range_val = FOVI_10MA, int delay_val = 10, int sample_times_val = 100, int sample_period_val = 10){
		mode = mode_val;
		v = v_val;
		i = i_val;
		v_range = v_range_val;
		i_range = i_range_val;
		delay = delay_val;
		sample_times = sample_times_val;
		sample_period = sample_period_val;
	}

	~Cvi_config() {}

	int mode;
	double v;
	double i;
	FOVI_VRNG v_range;
	FOVI_IRNG i_range;
	FPVI10_VRNG fpvi_v_range;
	FPVI10_IRNG fpvi_i_range;

	int delay;
	int sample_times;
	int sample_period;
};


class BoardCheck
{
public:
	BoardCheck();
	~BoardCheck();
	void Sot();
	friend BOOL CALLBACK  BoardCheckDialogProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam);

	FOVI_VRNG get_fovi_v_range(double v){
		if (v < 0)
			v = -v;
		if (v <= 1)
			return FOVI_1V;
		if (v <= 2)
			return FOVI_2V;
		else if (v <= 5)
			return FOVI_5V;
		else if (v <= 10)
			return FOVI_10V;
		else if (v <= 20)
			return FOVI_20V;
		else if (v <= 50)
			return FOVI_50V;
		else
			return FOVI_5V;
	}

	FPVI10_VRNG get_fpvi_v_range(double v){
		if (v < 0)
			v = -v;
		if (v <= 0.1)
			return FPVI10_100MV;
		if (v <= 1)
			return FPVI10_1V;
		else if (v <= 2)
			return FPVI10_2V;
		else if (v <= 5)
			return FPVI10_5V;
		else if (v <= 10)
			return FPVI10_10V;
		else if (v <= 20)
			return FPVI10_20V;
		else if (v <= 50)
			return FPVI10_50V;
		else if (v <= 100)
			return FPVI10_100V;
		else
			return FPVI10_1V;
	}
	FOVI_IRNG get_fovi_i_range(double i){
		if (i < 0)
			i = -i;
		if (i <= 1e-6)
			return FOVI_1UA;
		else if (i <= 10e-6)
			return FOVI_10UA;
		else if (i <= 100e-6)
			return FOVI_100UA;
		else if (i <= 1e-3)
			return FOVI_1MA;
		else if (i <= 10e-3)
			return FOVI_10MA;
		else if (i <= 100e-3)
			return FOVI_100MA;
		else if (i <= 1)
			return FOVI_1A;
		else
			return FOVI_1MA;
	}

	FPVI10_IRNG get_fpvi_i_range(double i){
		if (i < 0)
			i = -i;
		if (i <= 10e-6)
			return FPVI10_10UA;
		else if (i <= 100e-6)
			return FPVI10_100UA;
		else if (i <= 1e-3)
			return FPVI10_1MA;
		else if (i <= 10e-3)
			return FPVI10_10MA;
		else if (i <= 100e-3)
			return FPVI10_100MA;
		else if (i <= 1)
			return FPVI10_1A;
		else if (i <= 10)
			return FPVI10_10A;
		else
			return FPVI10_1MA;
	}


	void SetSiteConnected(int site, BOOL value) { site_connected[site] = value; }
	BOOL GetSiteConnected(int site) { return site_connected[site]; }
	BOOL IsNoSiteConnected(void) { for (int site = 0; site<SITE_NUM; ++site) if (site_connected[site]) return FALSE; return TRUE; }
	void ClearSiteConnected(void) { for (int site = 0; site<SITE_NUM; ++site) site_connected[site] = 0; }
	BOOL IsCheckPass(void);
	int get_nBtn(void) { return nBtn; }
	void Display(void);
	BOOL output_format(void);
	BOOL report(void);
	BOOL Board_ID_Check(const char* boardName, const char* rev, const char* SCLChannel, const char* SDAChannel);
	BOOL Board_ID_Write(const char* boardName, const char* rev, const char* number, const char* SCLChannel, const char* SDAChannel);
	BOOL Board_ID_Read(string* boardName, string* rev, string* number, const char* SCLChannel, const char* SDAChannel);


	//****************************************define component测试方法*****************************************//

	//**********************************1.CAP *************************//
	//RES=Resistence, res=resource

	//对地电容
	//【1.1 FOVI源 CAP】
	BOOL test_cap_to_gnd(FOVI &fovi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【1.2 FPVI源 CAP】
	BOOL test_cap_to_gnd(FPVI10 &fpvi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	//源-源之间的电容
	//【1.3 FPVI-FOVI CAP】
	BOOL test_cap_between_pin(FPVI10 &fpvi_res, FOVI &fovi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);


	//**********************************2.RES *************************//
	//对地电阻：pull_flag=0,上拉电阻pull_flag=1;
	//【2.1 FOVI源 RES】
	BOOL test_r(PULLUP_FLAG flag, FOVI &fovi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【2.2 FPVI源 RES】
	BOOL test_r(PULLUP_FLAG flag, FPVI10 &fpvi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	//源-源电阻
	//【2.3 FOVI源-FOVI源 RES】(res2给0,变成对地电阻)
	BOOL test_r(FOVI &fovi_res1, FOVI &fovi_res2, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【2.4 FPVI源-FPVI源 RES】(res2给0,变成对地电阻)
	BOOL test_r(FPVI10 &fpvi_res1, FPVI10 &fpvi_res2, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);


	//**********************************3.Relay:Check 电压*************************//
	//***************单个源对地/固定源(VI源)
	//【3.1 FOVI源 relay】
	BOOL test_relay(FOVI &fovi_res, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【3.2 FPVI源 relay】
	BOOL test_relay(FPVI10 &fpvi_res, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	//***************两个源之间check(VI源）
	//【3.3 FOVI-FOVI源 relay, FOVI force,FOVI measure】
	BOOL test_relay(FOVI &fovi_force, FOVI &fovi_measure, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【3.4 FOVI-FPVI源 relay, FOVI force,FPVI measure】
	BOOL test_relay(FOVI &fovi_force, FPVI10 &fpvi_measure, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【3.5 FPVI-FPVI源 relay, FPVI force,FPVI measure】
	BOOL test_relay(FPVI10 &fpvi_force, FPVI10 &fpvi_measure, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	 
	//***************两个源之间check(VI-DIO源）
	//【3.6 FOVI-DIO源 relay, DIO force，FOVI measure】
	BOOL test_relay(FOVI &fovi_measure, const char* lpszGroupPinName, const char* lpszPinName, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【3.7 FPVI-DIO源 relay, DIO force，FPVI measure】
	BOOL test_relay(FPVI10 &fpvi_measure, const char* lpszGroupPinName, const char* lpszPinName, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	//***************两个源之间check(VI-QVM源）
	//【3.8 FOVI-QVM源 relay,  FOVI force QVM measure】
	BOOL test_relay(FOVI &fovi_force, QVM &qvm_res, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【3.9 FPVI-QVM源 relay,  FPVI force，QVM measure】
	BOOL test_relay(FPVI10 &fpvi_force, QVM &qvm_res, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	//***************两个源之间check(VI-QTMU源）
	//【3.10 FOVI-QTMU源 relay,  FOVI force QTMU measure】
	BOOL test_qtmu(FOVI &fovi_res, QTMU_PLUS &qtmu, BYTE source, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【3.11 FPVI-QTMU源 relay,  FPVI force QTMU measure】
	BOOL test_qtmu(FPVI10 &fpvi_res, QTMU_PLUS &qtmu, BYTE source, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	//***************三个源之间check
	//【3.12 FOVI-FOVI-FPVI源 relay】
	BOOL test_relay(FOVI &fovi_res1, FOVI &fovi_res2, FPVI10 &fpvi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	

	// 4.only measure
	//【4.1 fovi量电压】
	BOOL test_v(FOVI &FOVI_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【4.2 fpvi量电压】
	BOOL test_v(FPVI10 &FPVI10_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	//【4.3 fovi量小电阻】mhom
	BOOL test_r_small(FOVI &FOVI_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【4.4 fpvi量小电阻】mhom
	BOOL test_r_small(FPVI10 &FPVI10_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	//【4.5 fovi量kelvin电阻】10k
	BOOL test_r_kelvin(FOVI &FOVI_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【4.6 fpvi量kelvin电阻】10k
	BOOL test_r_kelvin(FPVI10 &FPVI10_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	//【4.7 fovi FI=10UA量电压】
	BOOL test_v_p2p(FOVI &FOVI_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	//【4.8 fpvi FI=10UA量电压】
	BOOL test_v_p2p(FPVI10 &FPVI10_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	////【4.9 fovi量kelvin电阻】ohm
	//BOOL test_kelvin_ohm(FOVI &FOVI_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);
	////【4.10 fpvi量kelvin电阻】ohm
	//BOOL test_kelvin_ohm(FPVI10 &FPVI10_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	BOOL log(DWORD tnum, const char* component, double* result, double lolim, double hilim, const char* unit);
	BOOL test_log(DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 = NULL);

	void create_data_block(string str_1, ...);
	void updateBoardCheckResults(string  str_input, string unit_input);
	void set_data_after_boardcheck(double *test_value, double hlimit, double llimit);
	bool check_results_summary();
	void SetConsoleTextSize(int fontSize);
private:
	// Prevent copying and assignments (by private definition)
	BoardCheck operator=(const BoardCheck &x) { return *this; }
	BoardCheck(BoardCheck &x) {}
	void create_input(void);
	void delete_input(void);
	BoardCheckGroup *input;
	BoardCheckGroup *buttons;    // deleted with input
	BoardCheckGroup *listbox;    // deleted with input

	DialogTemplate *dialog;
	CBC_log bc_log;
	vector<string> display_vec;
	//int nMaxExtent;
	BOOL CheckPass;				// result of all site
	BOOL check_result[SITE_NUM];// result of each site
	int nBtn;
	BOOL site_connected[SITE_NUM];


	map<string, MyData>m_boardcheck_results[SITE_NUM];
	double m_test_value[SITE_NUM];
	double m_hlimit;
	double m_llimit;
	bool m_check_stat[SITE_NUM];

};


