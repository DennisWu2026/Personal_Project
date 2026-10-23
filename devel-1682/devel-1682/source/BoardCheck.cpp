#pragma once

#include "stdafx.h"
#include "BoardCheck.h"
#include "sub.h"
#include "assert.h"
#include <fstream>
#include <time.h>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <algorithm>
#include <cctype>
#pragma comment(lib, "User32.lib")
#pragma comment(lib, "Gdi32.lib")

extern "C" int GetPgsFullPath(LPTSTR pgsPath, int chNum);
extern int site;
BoardCheck *boardcheck_ptr;
DWORD serial;

#define ID_REDO					100
#define ID_EXIT                 101
#define ID_LISTBOX              102

//int globalsite_BC;
//BYTE sitesta_BC[SITE_NUM];
//#define SITE_BC globalsite_BC
//#define SERIAL_BC \
//		StsGetSiteStatus(sitesta_BC, SITE_NUM); \
//        for(globalsite_BC=0;globalsite_BC<SITE_NUM;globalsite_BC++) \
//			if(sitesta_BC[SITE_BC]) \

int globalsite_BC;
#define SITE_BC globalsite_BC
#define SERIAL_BC \
        for(globalsite_BC=0;globalsite_BC<SITE_NUM;globalsite_BC++) \
			if(site_connected[SITE_BC]) \

#define REALLOC(ptr,type,count)              \
    {                                        \
        int siz=sizeof(type)*(count);        \
        if(ptr) {                            \
            ptr=(type*)realloc(ptr,siz);     \
            assert(ptr);                     \
		        } else {                             \
            ptr=(type*)malloc(siz);          \
            assert(ptr);                     \
            memset(ptr,0,siz);               \
		        }                                    \
        assert(ptr);                         \
    }
#define FREE(ptr) if(ptr) {free(ptr);ptr=NULL;}

// common funcitons
string int2str(DWORD n) {

	char t[64];
	int i = 0;

	if (n == 0)
		return "0";

	while (n) {
		t[i++] = char((n % 10) + '0');
		n /= 10;
	}
	t[i] = 0;

	string result(t);
	result = result.assign(result.rbegin(), result.rend());

	return result;
}

string float2str(double f){
	char buf[64];
	_gcvt_s(buf, 64, f, 8);
	string result(buf);
	if (result.length() > 1)
		if (result.find(".") == result.length() - 1){
			string temp(result, 0, result.length() - 1);
			result = temp;
		}
	return result;
}

BOOL IsFileExist(const char * file_name){
	fstream file;
	file.open(file_name, ios::in);
	if (!file){
		return FALSE;
	}
	else{
		file.close();
		return TRUE;
	}

}

BOOL IsFileOpen(string file){
	HANDLE hFile = CreateFile(file.c_str(),		 // file to open
		GENERIC_READ,		 // open for reading
		0,					 // share for reading
		NULL,				 // default security
		OPEN_EXISTING,		 // existing file only
		FILE_ATTRIBUTE_NORMAL,// normal file
		NULL);				 // no attr. template

	if (hFile == INVALID_HANDLE_VALUE){	// file is open
		CloseHandle(hFile);
		return TRUE;
	}
	else{
		CloseHandle(hFile);
		return FALSE;
	}
}

string GetSysTime(void){
	time_t raw_time;
	tm time_info;
	time(&raw_time);
	localtime_s(&time_info, &raw_time);
	char c_time[32];

	strftime(c_time, sizeof(c_time), "%Y-%m-%d,%H:%M:%S", &time_info);
	string str_time(c_time);

	return str_time;
}


// 设置文本颜色
void SetColorBC(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// 重置文本颜色为默认值
void ResetColorBC() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7); // 7 是默认的白色文本
}

// 函数用于将数据写入CSV文件
void writeCSV(const std::string& filename, const std::vector<std::vector<std::string>>& data) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "无法打开文件以进行写入" << std::endl;
		return;
	}

	for (const auto& row : data) {
		for (size_t col = 0; col < row.size(); ++col) {
			file << row[col];
			if (col < row.size() - 1) {
				file << ","; // 在除了最后一个单元格之外的所有单元格后添加逗号
			}
		}
		file << "\n"; // 每一行数据后添加换行符
	}

	file.close();
}
std::string doubleToStringWithPrecision(double value, int num) {
	std::ostringstream out;
	out << std::fixed << std::setprecision(num) << value;
	return out.str();
}

string to_string_format(double  in_data)
{
	string aa;
	if (in_data > 9999)
	{
		in_data = 9999;
	}
	if (in_data < -9999)
	{
		in_data = -9999;
	}
	if (abs(in_data)>9999)
	{
		aa=doubleToStringWithPrecision(in_data, 0);
	}
	else
	{
		aa=doubleToStringWithPrecision(in_data, 2);
	}
	return aa;
}


DialogTemplate::DialogTemplate(LPCSTR caption, DWORD style, int x, int y, int w, int h,
	LPCSTR font, WORD fontSize)
{
	usedBufferLength = sizeof(DLGTEMPLATE);
	totalBufferLength = usedBufferLength;

	dialogTemplate = (DLGTEMPLATE*)malloc(totalBufferLength);
	assert(dialogTemplate);

	dialogTemplate->style = style;

	if (font != NULL) {
		dialogTemplate->style |= DS_SETFONT;
	}

	dialogTemplate->x = x;
	dialogTemplate->y = y;
	dialogTemplate->cx = w;
	dialogTemplate->cy = h;
	dialogTemplate->cdit = 0;

	dialogTemplate->dwExtendedStyle = 0;

	// The dialog box doesn't have a menu or a special class
	//AppendData(_T("\0"), 2);
	//AppendData(_T("\0"), 2);
	//lzg
	AppendData("\0", 2);
	AppendData("\0", 2);

	// Add the dialog's caption to the template
	AppendString(caption);

	if (font != NULL) {
		AppendData(&fontSize, sizeof(WORD));
		AppendString(font);
	}

}

void DialogTemplate::AddComponent(LPCSTR type, LPCSTR caption, DWORD style, DWORD exStyle,
	int x, int y, int w, int h, WORD id)
{
	DLGITEMTEMPLATE item;

	item.style = style;
	item.x = x;
	item.y = y;
	item.cx = w;
	item.cy = h;
	item.id = id;

	item.dwExtendedStyle = exStyle;

	AppendData(&item, sizeof(DLGITEMTEMPLATE));

	AppendString(type);
	AppendString(caption);

	WORD creationDataLength = 0;
	AppendData(&creationDataLength, sizeof(WORD));

	// Increment the component count
	dialogTemplate->cdit++;
}


void DialogTemplate::AddButton(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
	int w, int h, WORD id)
{
	AddStandardComponent(0x0080, caption, style, exStyle, x, y, w, h, id);

	WORD creationDataLength = 0;
	AppendData(&creationDataLength, sizeof(WORD));

}

void DialogTemplate::AddEditBox(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
	int w, int h, WORD id)
{
	AddStandardComponent(0x0081, caption, style, exStyle, x, y, w, h, id);

	WORD creationDataLength = 0;
	AppendData(&creationDataLength, sizeof(WORD));
}

void DialogTemplate::AddStatic(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
	int w, int h, WORD id)
{
	AddStandardComponent(0x0082, caption, style, exStyle, x, y, w, h, id);

	WORD creationDataLength = 0;
	AppendData(&creationDataLength, sizeof(WORD));
}

void DialogTemplate::AddListBox(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
	int w, int h, WORD id)
{
	AddStandardComponent(0x0083, caption, style, exStyle, x, y, w, h, id);

	WORD creationDataLength = 0;
	AppendData(&creationDataLength, sizeof(WORD));
}

void DialogTemplate::AddScrollBar(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
	int w, int h, WORD id)
{
	AddStandardComponent(0x0084, caption, style, exStyle, x, y, w, h, id);

	WORD creationDataLength = 0;
	AppendData(&creationDataLength, sizeof(WORD));
}

void DialogTemplate::AddComboBox(LPCSTR caption, DWORD style, DWORD exStyle, int x, int y,
	int w, int h, WORD id)
{
	AddStandardComponent(0x0085, caption, style, exStyle, x, y, w, h, id);

	WORD creationDataLength = 0;
	AppendData(&creationDataLength, sizeof(WORD));
}

/**
* Returns a pointer to the Win32 dialog template which the object
* represents. This pointer may become invalid if additional
* components are added to the template.
*/

DialogTemplate::operator const DLGTEMPLATE*() const
{
	return dialogTemplate;
}

DialogTemplate::~DialogTemplate()
{
	free(dialogTemplate);
}

void DialogTemplate::AddStandardComponent(WORD type, LPCSTR caption, DWORD style,
	DWORD exStyle, int x, int y, int w, int h, WORD id)
{
	DLGITEMTEMPLATE item;

	// DWORD algin the beginning of the component data
	AlignData(sizeof(DWORD));

	item.style = style;
	item.x = x;
	item.y = y;
	item.cx = w;
	item.cy = h;
	item.id = id;

	item.dwExtendedStyle = exStyle;

	AppendData(&item, sizeof(DLGITEMTEMPLATE));

	WORD preType = 0xFFFF;

	AppendData(&preType, sizeof(WORD));
	AppendData(&type, sizeof(WORD));

	AppendString(caption);

	// Increment the component count
	dialogTemplate->cdit++;
}

void DialogTemplate::AlignData(int size)
{
	int paddingSize = usedBufferLength % size;

	if (paddingSize != 0) {
		EnsureSpace(paddingSize);
		usedBufferLength += paddingSize;
	}
}

void DialogTemplate::AppendString(LPCSTR string)
{
	int length = MultiByteToWideChar(CP_ACP, 0, string, -1, NULL, 0);

	WCHAR* wideString = (WCHAR*)malloc(sizeof(WCHAR) * length);
	MultiByteToWideChar(CP_ACP, 0, string, -1, wideString, length);

	AppendData(wideString, length * sizeof(WCHAR));
	free(wideString);
}

void DialogTemplate::AppendData(void* data, int dataLength)
{
	EnsureSpace(dataLength);

	memcpy((char*)dialogTemplate + usedBufferLength, data, dataLength);
	usedBufferLength += dataLength;
}

void DialogTemplate::EnsureSpace(int length)
{
	if (length + usedBufferLength > totalBufferLength) {
		totalBufferLength += length * 2;

		void* newBuffer = malloc(totalBufferLength);
		assert(newBuffer);
		memcpy(newBuffer, dialogTemplate, usedBufferLength);

		free(dialogTemplate);
		dialogTemplate = (DLGTEMPLATE*)newBuffer;
	}
}

///////////////////
//
// BoardCheckButton
//
///////////////////
BoardCheckButton::BoardCheckButton(char *aname, int aid, int def_style)
{
	name = _strdup(aname);
	id = aid;
	style = def_style;
}

BoardCheckButton::~BoardCheckButton()
{
	FREE(name);
}

int BoardCheckButton::width()
{
	return (int)(strlen(name)*4.1 + 30);
}

int BoardCheckButton::height()
{
	return 15;
}

void BoardCheckButton::create_dialog(DialogTemplate *dialog, int x, int y, int *newid)
{
	dialog->AddButton(name, WS_VISIBLE | WS_TABSTOP | style, 0, x, y, width(), height(), id);
}


///////////////////
//
// BoardCheckListBox
//
///////////////////
BoardCheckListBox::BoardCheckListBox(char *aname, int aid, int def_style)
{
	name = _strdup(aname);
	id = aid;
	style = def_style;
}

BoardCheckListBox::~BoardCheckListBox()
{
	FREE(name);
}

int BoardCheckListBox::width()
{
	return 291;
}

int BoardCheckListBox::height()
{
	return 267;
}

void BoardCheckListBox::create_dialog(DialogTemplate *dialog, int x, int y, int *newid)
{
	dialog->AddListBox(name, WS_VISIBLE | WS_HSCROLL | LBS_OWNERDRAWVARIABLE | LBS_HASSTRINGS | style, 0, x, y, width(), height(), id);
}

//void BoardCheckListBox::command(HWND hDlg,int code,int target_id)
//{
//if(code==LB_ADDSTRING && target_id==id) {
//SendDlgItemMessage(hDlg,ID_LISTBOX,LB_ADDSTRING,0,(LPARAM)"Try to add string....");
//SendDlgItemMessage(hDlg,ID_LISTBOX,LB_ADDSTRING,0,(LPARAM)"Try to add string....");
//}
//}


///////////////////
//
// BoardCheckGroup
//
///////////////////
BoardCheckGroup::BoardCheckGroup(int vertical, int aospace, int aispace)
{
	is_vertical = vertical;
	no = 0;
	ospace = aospace;
	ispace = aispace;
	member = NULL;
}

BoardCheckGroup::~BoardCheckGroup()
{
	int i;
	for (i = 0; i<no; i++)
		delete member[i];
	FREE(member);
}

void BoardCheckGroup::add(BoardCheckElement *el)
{
	REALLOC(member, LPBoardCheckElement, ++no);
	member[no - 1] = el;
}

void BoardCheckGroup::get(HWND hDlg)
{
	int i;
	for (i = 0; i<count(); i++)
		member[i]->get(hDlg);
}

void BoardCheckGroup::set(HWND hDlg)
{
	int i;
	for (i = 0; i<count(); i++)
		member[i]->set(hDlg);
}

void BoardCheckGroup::dlg_file(HWND hDlg, char *fname, int len)
{
	int i;
	for (i = 0; i<count(); i++)
		member[i]->dlg_file(hDlg, fname, len);
}

void BoardCheckGroup::create_dialog(DialogTemplate *dialog, int x, int y, int *newid)
{
	int i;
	int offs = ospace;
	if (!count())
		return;
	for (i = 0; i<count(); i++)
		if (is_vertical) {
			member[i]->create_dialog(dialog, x + ospace, y + offs, newid);
			offs += member[i]->height() + ispace;
		}
		else {
			member[i]->create_dialog(dialog, x + offs, y + ospace, newid);
			offs += member[i]->width() + ispace;
		}
		id = (*newid)++;
		if (ospace && ispace)
			dialog->AddStatic("", WS_VISIBLE | SS_GRAYFRAME, 0, x, y, width(), height(), id);
}

void BoardCheckGroup::command(HWND hDlg, int code, int target_id)
{
	int i;
	for (i = 0; i<count(); i++)
		member[i]->command(hDlg, code, target_id);
}

int BoardCheckGroup::count()
{
	return no;
}

int BoardCheckGroup::width()
{
	int i;
	int w = 0;
	int cnt = count();
	if (!cnt)
		return 0;
	if (is_vertical) {
		for (i = 0; i<cnt; i++)
			if (member[i]->width()>w)
				w = member[i]->width();
	}
	else {
		for (i = 0; i<cnt; i++)
			w += member[i]->width();
		if (cnt)
			w += (cnt - 1)*ispace;
	}
	return w + 2 * ospace;
}

int BoardCheckGroup::height()
{
	int i;
	int w = 0;
	int cnt = count();
	if (!cnt)
		return 0;
	if (!is_vertical) {
		for (i = 0; i<cnt; i++)
			if (member[i]->height()>w)
				w = member[i]->height();
	}
	else {
		for (i = 0; i<cnt; i++)
			w += member[i]->height();
		if (cnt)
			w += (cnt - 1)*ispace;
	}
	return w + 2 * ospace;
}

///////////////////
//
// BoardCheck
//
///////////////////

BoardCheck::BoardCheck()
{
	input = NULL;
	buttons = NULL;
	dialog = NULL;
	CheckPass = FALSE;
	nBtn = BTN_NONE;
	create_input();
	for (int site = 0; site<SITE_NUM; ++site){
		site_connected[site] = 0;
		check_result[site] = TRUE;
	}
}

BoardCheck::~BoardCheck()
{
	if (!dialog){
		delete dialog;
		dialog = NULL;
	}
	if (!input){
		delete input;
		input = NULL;
	}
	if (!listbox){
		delete listbox;
		listbox = NULL;
	}
	if (!buttons){
		delete buttons;
		buttons = NULL;
	}
}

BOOL CALLBACK  BoardCheckDialogProc(HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{

	switch (iMsg) {
	case WM_INITDIALOG:
	{
		for (vector<string>::iterator it = boardcheck_ptr->display_vec.begin(); it != boardcheck_ptr->display_vec.end(); ++it){
			// Add string into listbox
			SendDlgItemMessage(hDlg, ID_LISTBOX, LB_ADDSTRING, 0, (LPARAM)(*it).c_str());
		}

		SendMessage(GetDlgItem(hDlg, ID_LISTBOX), LB_SETHORIZONTALEXTENT, /*boardcheck_ptr->nMaxExtent*/2000, 0);

		return TRUE;
	}
	break;

	case WM_COMMAND:
	{
		//// Redo Board Check
		if (wParam == ID_REDO) {
			boardcheck_ptr->nBtn = BTN_REDO;
			EndDialog(hDlg, TRUE);
			return TRUE;
		}
		//// Exit
		if (wParam == ID_EXIT) {
			boardcheck_ptr->nBtn = BTN_EXIT;
			EndDialog(hDlg, TRUE);
			//PostQuitMessage(0);	// Exit ATE UI
			return TRUE;
		}
		if ((wParam & 0xFF) == ID_LISTBOX) {
			return TRUE;
		}
		if (wParam == IDCANCEL) {
			boardcheck_ptr->nBtn = BTN_CANCEL;
			EndDialog(hDlg, TRUE);
			//PostQuitMessage(0);	// Exit ATE UI 
			return TRUE;
		}
		//boardcheck_ptr->input->command(hDlg,HIWORD(wParam),LOWORD (wParam));
	}
	break;
	case WM_CTLCOLORLISTBOX:
		break;
	case WM_DRAWITEM:
	{
		LPDRAWITEMSTRUCT lpDrawItem = (LPDRAWITEMSTRUCT)lParam;
		if (lpDrawItem->CtlType == ODT_LISTBOX || lpDrawItem->CtlID == ID_LISTBOX){
			if (lpDrawItem->itemID == -1)	break;

			char szItemString[2000];
			int nItemStringLen;

			SendDlgItemMessage(hDlg, ID_LISTBOX, LB_GETTEXT, (WPARAM)lpDrawItem->itemID, (LPARAM)szItemString);
			nItemStringLen = strlen(szItemString);

			// 设置选中一行时，这一行加边框
			if ((lpDrawItem->itemState & ODS_SELECTED) && (lpDrawItem->itemAction & (ODA_SELECT | ODA_DRAWENTIRE))){
				DrawFocusRect(lpDrawItem->hDC, &lpDrawItem->rcItem);
				//InvertRect(lpDrawItem->hDC, &lpDrawItem->rcItem); //反色
			}
			else if (!(lpDrawItem->itemState & ODS_SELECTED) && (lpDrawItem->itemAction & ODA_SELECT)){
				DrawFocusRect(lpDrawItem->hDC, &lpDrawItem->rcItem);
				//InvertRect(lpDrawItem->hDC, &lpDrawItem->rcItem); //反色
			}

			string item_str(szItemString, 0, nItemStringLen - 1);

			// 文字颜色
			if (item_str.find("FAIL") != string::npos){
				SetTextColor(lpDrawItem->hDC, RGB(255, 0, 0));
			}
			else {
				SetTextColor(lpDrawItem->hDC, RGB(0, 0, 0));
			}

			// 文字背景色
			if (lpDrawItem->itemState & ODS_SELECTED){	// 设置被选中行的背景颜色
				SetBkMode(lpDrawItem->hDC, OPAQUE);
				//SetBkColor(lpDrawItem->hDC, RGB(255, 255, 255));
				SetBkColor(lpDrawItem->hDC, GetSysColor(COLOR_GRAYTEXT));
			}
			else {
				SetBkMode(lpDrawItem->hDC, OPAQUE);
				SetBkColor(lpDrawItem->hDC, GetSysColor(COLOR_WINDOW));
			}

			DrawText(lpDrawItem->hDC, szItemString, nItemStringLen, &lpDrawItem->rcItem, DT_LEFT | DT_SINGLELINE);
			return TRUE;
		}
	}
	break;
	}
	return FALSE;
}


void BoardCheck::Display(void)
{
	int id = 200; // start value for ids
	HWND shell = GetForegroundWindow();

	if (!IsCheckPass()){
		output_format();

		//delete_input();
		create_input();
		buttons->add(new BoardCheckButton("重做诊断", ID_REDO, BS_DEFPUSHBUTTON));
		buttons->add(new BoardCheckButton("退出", ID_EXIT, BS_DEFPUSHBUTTON));
		listbox->add(new BoardCheckListBox("ListBox", ID_LISTBOX));

		string str_result("诊断结果：");
		SERIAL_BC{
			if (check_result[SITE_BC]){
				str_result = str_result + "工位(" + int2str(SITE_BC + 1) + ") Pass ";
			}
			else {
				str_result = str_result + "工位(" + int2str(SITE_BC + 1) + ") Fail ";
			}
		}
		dialog = new DialogTemplate(str_result.c_str(), WS_CAPTION | DS_CENTER, 10, 10, 600, 300);
		input->create_dialog(dialog, 0, 0, &id);
		boardcheck_ptr = this;
		INT_PTR ret = DialogBoxIndirectA(NULL,
			*dialog,
			shell,
			(DLGPROC)BoardCheckDialogProc);

		delete dialog;
		dialog = NULL;
	}
}

void BoardCheck::create_input(void)
{
	input = new BoardCheckGroup(1, 4, 0);            // vertical aligned

	listbox = new BoardCheckGroup(0, 0, 0);
	input->add(listbox);

	buttons = new BoardCheckGroup(0, 4, 4);
	input->add(buttons);
}

void BoardCheck::delete_input(void)
{
	if (listbox->count()){
		delete listbox;
		listbox = NULL;
	}
	if (buttons->count()){
		delete buttons;
		buttons = NULL;
	}
	if (input->count()){
		delete input;
		input = NULL;
	}
}

BOOL BoardCheck::log(DWORD tnum, const char *component, double *result, double lolim, double hilim, const char *unit)
{
	bc_log.component_vec.push_back(component);
	bc_log.tnum_map[component] = tnum;
	bc_log.lolim_map[component] = lolim;
	bc_log.hilim_map[component] = hilim;
	bc_log.unit_map[component] = unit;

	SERIAL_BC bc_log.data_map[component][SITE_BC] = result[SITE_BC];
	SERIAL_BC{
		if ((result[SITE_BC] >= lolim) && (result[SITE_BC] <= hilim)){
			bc_log.flag_map[component][SITE_BC] = "PASS";
		}
		else{
			bc_log.flag_map[component][SITE_BC] = "FAIL";
			CheckPass = FALSE;
			check_result[SITE_BC] = FALSE;
		}
	}
	//SERIAL_BC result[SITE_BC] = 9999;

	return TRUE;
}

BOOL BoardCheck::test_log(DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1)
{
	double result[SITE_NUM] = { 0 };
	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ',')) {
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}



	return TRUE;
}


BOOL BoardCheck::output_format()
{
	//for (vector<string>::iterator it = bc_log.component_vec.begin(); it != bc_log.component_vec.end(); ++it){
	//	string temp("T" + int2str(bc_log.tnum_map[*it]) + "   ");
	//	SERIAL_BC{
	//		temp = temp + "SITE" + int2str(SITE_BC + 1) + "=" + bc_log.flag_map[*it][SITE_BC] + "(" + float2str(bc_log.data_map[*it][SITE_BC]) + bc_log.unit_map[*it] + ")   ";
	//	}
	//	temp = temp + "Low Limit=" + float2str(bc_log.lolim_map[*it]) + bc_log.unit_map[*it] + "   ";
	//	temp = temp + "High Limit=" + float2str(bc_log.hilim_map[*it]) + bc_log.unit_map[*it] + "   ";
	//	temp = temp + *it;
	//	display_vec.push_back(temp);
	//}

	for (std::map<string, MyData>::iterator it = m_boardcheck_results[0].begin(); it != m_boardcheck_results[0].end(); ++it)
	{
		string temp_str= it->first;
		int longth =temp_str.size();
		for (int i = 0; i <25 - longth; i++)
		{
			temp_str = temp_str + " ";
		}
		temp_str = temp_str + ":  ";
		SERIAL_BC{		
			temp_str = temp_str + "SITE" + int2str(SITE_BC + 1) + "=" + it->second.flag + "(" + to_string_format(it->second.test_data) + it->second.unit + ")         ";
		}

		display_vec.push_back(temp_str);
	}

	return TRUE;
}

BOOL BoardCheck::IsCheckPass()
{
	for (vector<string>::iterator it = bc_log.component_vec.begin(); it != bc_log.component_vec.end(); ++it){
		SERIAL_BC{
			if (bc_log.flag_map[*it][SITE_BC] == "FAIL")
			return FALSE;
		}
	}
	return TRUE;
}

BOOL BoardCheck::report()
{
	char pgsfullpath[300];
	GetPgsFullPath(pgsfullpath, 300);
	string fullpathpgs(pgsfullpath);
	string pathofpgs = "";
	int pos = fullpathpgs.find_last_of('\\');
	if (pos > -1)
	{
		pathofpgs = fullpathpgs.substr(0, pos + 1);
	}
	string file_bc = pathofpgs + "source\\bc.csv";

	if (IsFileOpen(file_bc.c_str())){
		MessageBoxA(NULL, "请确认 bc.csv 文件是否已打开？\n如果打开，请关闭，否则数据无法保存", "诊断提示对话框", MB_OK);
	}

	fstream file;
	file.open(file_bc.c_str(), ios::app);

	string time(GetSysTime());
	string result_flag;
	if (IsCheckPass())
		result_flag = "PASS";
	else
		result_flag = "FAIL";
	file << "Time," + time << "," << "Final," + result_flag + ",Serial," + int2str(++serial) << endl;
	for (vector<string>::iterator it = bc_log.component_vec.begin(); it != bc_log.component_vec.end(); ++it){
		string temp("T" + int2str(bc_log.tnum_map[*it]) + ",");
		SERIAL_BC{
			temp = temp + "SITE" + int2str(SITE_BC + 1) + "," + bc_log.flag_map[*it][SITE_BC] + "," + float2str(bc_log.data_map[*it][SITE_BC]) + ",";
		}
		temp = temp + "Low Limit," + float2str(bc_log.lolim_map[*it]) + ",";
		temp = temp + "High Limit," + float2str(bc_log.hilim_map[*it]) + "," + bc_log.unit_map[*it] + ",";
		temp = temp + "\"" + *it + "\"";
		file << temp << endl;
	}

	file.flush();
	file.close();

	return TRUE;
}

double get_scale(string str_unit){
	if ((str_unit == "mA") || (str_unit == "mV") || (str_unit == "mOhm") || (str_unit == "mF") || (str_unit == "mUnit"))
		return 1e3;
	else if ((str_unit == "uA") || (str_unit == "uV") || (str_unit == "uF") || (str_unit == "uUnit"))
		return 1e6;
	else if ((str_unit == "nA") || (str_unit == "nV") || (str_unit == "nF") || (str_unit == "nUnit"))
		return 1e9;
	else if ((str_unit == "pA") || (str_unit == "pV") || (str_unit == "pF") || (str_unit == "pUnit"))
		return 1e12;
	else if ((str_unit == "kOhm") || (str_unit == "kUnit"))
		return 1e-3;
	else if ((str_unit == "MOhm") || (str_unit == "MUnit"))
		return 1e-6;

	return 1;
}


double PULL_5V_REAL[SITE_NUM];
//**********************************1.CAP *************************//
// 定义一个结构体，包含两个int型成员
struct MyStruct {
	int a;
	int b;

	// 可以添加一个成员函数来计算a和b的和，但这不是必需的
	int sum() const {
		return a + b;
	}
};

//// 在类定义外部定义模板成员函数
//template <typename T>
//void BoardCheck::display(T value) 
//{
//	 //这里我们假设T是MyStruct类型，并直接访问其成员进行计算
//	 //注意：这种做法只有在T确实是MyStruct时才有效，否则会导致编译错误。
//	 //为了更通用和健壮的代码，应该使用类型萃取或类型特征来检查T的类型。
//	//if (constexpr(is_same_v<T, MyStruct>)) {
//	//	cout << "Sum of a and b: " << value.a + value.b << endl;
//	//}
//	//else {
//	//	// 对于其他类型，我们仍然使用原来的输出方式
//	//	cout << "Value: " << value << endl;
//	//}
//}


//template <typename T >
//BOOL BoardCheck::test_fg(T *Power, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1 )
//{
//	double result[SITE_NUM] = { 0 };
//	double MeasV1[SITE_NUM] = { 0 };
//	double MeasV2[SITE_NUM] = { 0 };
//	double cap_i_real[SITE_NUM] = { 0 };
//
//	if constexpr(std::is_same_v<T, FOVI>)
//	{
//		//FOVI Power_FOVI = &Power;
//		//FOVI_IRNG i_range;
//		//double cap_i = lolim / get_scale(unit) * 5 / 5e-3; //换算成标准单位F，计算应该force电流，A
//		//i_range = get_fovi_i_range(cap_i);//选择合适的电流量程；
//		//Power_FOVI.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON); // discharge
//		//delay_ms(20);
//		//Power_FOVI.Set(FI, 0, FOVI_10V, i_range, RELAY_ON);
//		//delay_ms(1);
//		//Power_FOVI.Set(FI, cap_i, FOVI_10V, i_range, RELAY_ON);
//		//delay_ms(1);
//		//Power_FOVI.MeasureVI(10, 10);
//		//SERIAL_BC MeasV1[SITE_BC] = Power_FOVI.GetMeasResult(SITE_BC, MVRET);
//		//delay_ms(5);
//		//Power_FOVI.MeasureVI(10, 10);
//		//SERIAL_BC MeasV2[SITE_BC] = Power_FOVI.GetMeasResult(SITE_BC, MVRET);
//		//SERIAL_BC cap_i_real[SITE_BC] = Power_FOVI.GetMeasResult(SITE_BC, MIRET);
//		//SERIAL_BC result[SITE_BC] = (cap_i_real[SITE_BC] * 5.1e-3) / (MeasV2[SITE_BC] - MeasV1[SITE_BC] + 1e-12) * get_scale(unit); // F
//		//Power_FOVI.Set(FI, 0, FOVI_10V, i_range, RELAY_ON);
//		//Power_FOVI.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
//		//delay_ms(5);
//		//Power_FOVI.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
//		//delay_ms(2);
//	}
//	//else if constexpr(std::is_same_v<T, FPVI10>)
//	//{
//	//	FPVI10_IRNG i_range;
//	//	double cap_i = lolim / get_scale(unit) * 5 / 5e-3; // A
//	//	i_range = get_fpvi_i_range(cap_i);
//	//	Power.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON); // discharge
//	//	delay_ms(20);
//	//	Power.Set(FI, 0, FPVI10_10V, i_range, RELAY_ON);
//	//	delay_ms(1);
//	//	Power.Set(FI, cap_i, FPVI10_10V, i_range, RELAY_ON);
//	//	delay_ms(1);
//	//	Power.MeasureVI(10, 10);
//	//	SERIAL_BC MeasV1[SITE_BC] = Power.GetMeasResult(SITE_BC, MVRET);
//	//	delay_ms(5);
//	//	Power.MeasureVI(10, 10);
//	//	SERIAL_BC MeasV2[SITE_BC] = Power.GetMeasResult(SITE_BC, MVRET);
//	//	SERIAL_BC result[SITE_BC] = (cap_i * 5e-3) / (MeasV2[SITE_BC] - MeasV1[SITE_BC] + 1e-12) * get_scale(unit); // F
//	//	Power.Set(FI, 0, FPVI10_10V, i_range, RELAY_ON);
//	//	Power.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);
//	//	Power.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
//	//}
//	//else if constexpr(std::is_same_v<T, ACM>)
//	//{
//	//	ACM_IRNG i_range;
//	//	double cap_i = lolim / get_scale(unit) * 5 / 5e-3; // A
//	//	i_range = get_acm_i_range(cap_i);
//	//	Power.Set(FV, 0, ACM_N2P18V, ACM_200MA, ACM_RELAY_ON); // discharge
//	//	delay_ms(20);
//	//	Power.Set(FI, 0, ACM_N2P18V, i_range, ACM_RELAY_ON);
//	//	delay_ms(1);
//	//	Power.Set(FI, cap_i, ACM_N2P18V, i_range, ACM_RELAY_ON);
//	//	delay_ms(1);
//	//	Power.MeasureVI(ACM_MV, 10, 10);
//	//	SERIAL_BC MeasV1[SITE_BC] = acm_res1.GetMeasResult(SITE_BC);
//	//	delay_ms(5);
//	//	Power.MeasureVI(ACM_MV, 10, 10);
//	//	SERIAL_BC MeasV2[SITE_BC] = acm_res1.GetMeasResult(SITE_BC);
//	//	SERIAL_BC result[SITE_BC] = (cap_i * 5e-3) / (MeasV2[SITE_BC] - MeasV1[SITE_BC] + 1e-12) * get_scale(unit); // F
//	//	Power.Set(FI, 0, ACM_N2P18V, i_range, ACM_RELAY_ON);
//	//	Power.Set(FV, 0, ACM_N2P18V, ACM_20MA, ACM_RELAY_ON);
//	//	Power.Set(FV, 0, ACM_N2P18V, ACM_20MA, ACM_RELAY_OFF);
//	//}
//	//else if constexpr(std::is_same_v<T, ACM200>)
//	//{
//	//	ACM200_IRNG i_range;
//	//	double cap_i = lolim / get_scale(unit) * 5 / 5e-3; //换算成标准单位F，计算应该force电流，A
//	//	i_range = get_fovi_i_range(cap_i);//选择合适的电流量程；
//	//	Power.Set(FV, 0, ACM200_10V, ACM200_100MA, ACM200_RELAY_ON); // discharge
//	//	delay_ms(20);
//	//	Power.Set(FI, 0, ACM200_10V, i_range, ACM200_RELAY_ON);
//	//	delay_ms(1);
//	//	Power.Set(FI, cap_i, ACM200_10V, i_range, ACM200_RELAY_ON);
//	//	delay_ms(1);
//	//	Power.MeasureVI(10, 10);
//	//	SERIAL_BC MeasV1[SITE_BC] = Power.GetMeasResult(SITE_BC, MVRET);
//	//	delay_ms(5);
//	//	Power.MeasureVI(10, 10);
//	//	SERIAL_BC MeasV2[SITE_BC] = Power.GetMeasResult(SITE_BC, MVRET);
//	//	SERIAL_BC cap_i_real[SITE_BC] = Power.GetMeasResult(SITE_BC, MIRET);
//	//	SERIAL_BC result[SITE_BC] = (cap_i_real[SITE_BC] * 5.1e-3) / (MeasV2[SITE_BC] - MeasV1[SITE_BC] + 1e-12) * get_scale(unit); // F
//	//	Power.Set(FI, 0, ACM200_10V, i_range, ACM200_RELAY_ON);
//	//	Power.Set(FV, 0, ACM200_10V, FOVI_10MA, ACM200_RELAY_ON);
//	//	delay_ms(5);
//	//	Power.Set(FV, 0, ACM200_10V, FOVI_10MA, ACM200_RELAY_OFF);
//	//	delay_ms(2);
//	//}
//	//else
//	//{
//
//	//}
//
//
//
//	//if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
//	//if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);
//
//	return TRUE;
//}

//****************************************define component测试方法*****************************************//

//**********************************1.CAP *************************//
//对地电容
//【1.1 FOVI源 CAP】
BOOL BoardCheck::test_cap_to_gnd(FOVI &fovi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM] = { 0 };
	double MeasV1[SITE_NUM] = { 0 };
	double MeasV2[SITE_NUM] = { 0 };
	double cap_i_real[SITE_NUM] = { 0 };
	FOVI_IRNG i_range;

	double cap_i = lolim / get_scale(unit) * 5 / 5e-3; //换算成标准单位F，计算应该force电流，A
	i_range = get_fovi_i_range(cap_i);//选择合适的电流量程；
	fovi_res.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON); // discharge
	delay_ms(20);
	fovi_res.Set(FI, 0, FOVI_10V, i_range, RELAY_ON);
	delay_ms(1);
	fovi_res.Set(FI, cap_i, FOVI_10V, i_range, RELAY_ON);
	delay_ms(1);
	fovi_res.MeasureVI(10, 10);
	SERIAL_BC MeasV1[SITE_BC] = fovi_res.GetMeasResult(SITE_BC, MVRET);
	delay_ms(5);
	fovi_res.MeasureVI(10, 10);
	fovi_res.Set(FI, 0, FOVI_10V, i_range, RELAY_ON);
	SERIAL_BC MeasV2[SITE_BC] = fovi_res.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC cap_i_real[SITE_BC] = fovi_res.GetMeasResult(SITE_BC, MIRET);
	SERIAL_BC result[SITE_BC] =(cap_i_real[SITE_BC] * 5.1e-3) / (MeasV2[SITE_BC] - MeasV1[SITE_BC] + 1e-12) * get_scale(unit); // F
	fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(20);
	fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	delay_ms(10);

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	site_connected[0];
	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}


	return TRUE;
}
//【1.2 FPVI源 CAP】
BOOL BoardCheck::test_cap_to_gnd(FPVI10 &fpvi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM] = { 0 };
	double MeasV1[SITE_NUM] = { 0 };
	double MeasV2[SITE_NUM] = { 0 };
	FPVI10_IRNG i_range;

	double cap_i = lolim / get_scale(unit) * 5 / 5e-3; // A
	i_range = get_fpvi_i_range(cap_i);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON); // discharge
	delay_ms(20);
	fpvi_res.Set(FI, 0, FPVI10_10V, i_range, RELAY_ON);
	delay_ms(1);
	fpvi_res.Set(FI, cap_i, FPVI10_10V, i_range, RELAY_ON);
	delay_ms(1);
	fpvi_res.MeasureVI(10, 10);
	SERIAL_BC MeasV1[SITE_BC] = fpvi_res.GetMeasResult(SITE_BC, MVRET);
	delay_ms(5);
	fpvi_res.MeasureVI(10, 10);
	SERIAL_BC MeasV2[SITE_BC] = fpvi_res.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC result[SITE_BC] = (cap_i * 5e-3) / (MeasV2[SITE_BC] - MeasV1[SITE_BC] + 1e-12) * get_scale(unit); // F

	fpvi_res.Set(FI, 0, FPVI10_10V, i_range, RELAY_ON);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	delay_ms(20);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}


//源-源之间的电容

//【1.3 FPVI10-FOVI CAP】FOVI给0
BOOL BoardCheck::test_cap_between_pin(FPVI10 &fpvi_res, FOVI &fovi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM] = { 0 };
	double MeasV1[SITE_NUM] = { 0 };
	double MeasV2[SITE_NUM] = { 0 };
	FPVI10_IRNG i_range;

	double cap_i = lolim / get_scale(unit) * 5 / 5e-3; // A
	i_range = get_fpvi_i_range(cap_i);

	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON); // discharge
	fovi_res.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON); // fovi resource short to ground
	delay_ms(20);
	fpvi_res.Set(FI, 0, FPVI10_10V, i_range, RELAY_ON);
	delay_ms(1);

	fpvi_res.Set(FI, cap_i, FPVI10_10V, i_range, RELAY_ON);
	delay_ms(1);

	fpvi_res.MeasureVI(10, 10);
	SERIAL_BC MeasV1[SITE_BC] = fpvi_res.GetMeasResult(SITE_BC, MVRET);
	delay_ms(5);
	fpvi_res.MeasureVI(10, 10);
	SERIAL_BC MeasV2[SITE_BC] = fpvi_res.GetMeasResult(SITE_BC, MVRET);

	SERIAL_BC result[SITE_BC] = (cap_i * 5e-3) / (MeasV2[SITE_BC] - MeasV1[SITE_BC] + 1e-12) * get_scale(unit); // F

	fpvi_res.Set(FI, 0, FPVI10_10V, i_range, RELAY_ON);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);
	fovi_res.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_ON);
	delay_ms(20);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_OFF);
	fovi_res.Set(FV, 0, FOVI_5V, FOVI_100MA, RELAY_OFF);

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;

	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}

	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}



//**********************************2.RES ********F*****************//
////对地电阻：flag=PULL_DOWN,上拉电阻flag=PULL_UP;
//【2.1 FOVI源 RES】
BOOL BoardCheck::test_r(PULLUP_FLAG P_flag, FOVI &fovi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1)
{
	double result_v1[SITE_NUM];
	double result_i1[SITE_NUM];
	double result_v2[SITE_NUM];
	double result_i2[SITE_NUM];
	double result_r[SITE_NUM];
	double pullup_base_v[SITE_NUM];

	fovi_res.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(10);
	fovi_res.MeasureVI(100, 10);

	for (site = 0; site < SITE_NUM; site++)
	{
		pullup_base_v[site] = fovi_res.GetMeasResult(site, MVRET);
	}

	fovi_res.Set(FI, -0.001, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(10);
	fovi_res.MeasureVI(100, 10);
	for (site = 0; site < SITE_NUM; site++)
	{
		result_v1[site] = fovi_res.GetMeasResult(site, MVRET);
		result_i1[site] = fovi_res.GetMeasResult(site, MIRET);
	}

	fovi_res.Set(FI, -0.005, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(10);
	fovi_res.MeasureVI(100, 10);
	fovi_res.Set(FI, 0, FOVI_10V, FOVI_10MA, RELAY_ON);

	fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(10);
	fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	delay_ms(10);

	for (site = 0; site < SITE_NUM; site++)
	{
		result_v2[site] = fovi_res.GetMeasResult(site, MVRET);
		result_i2[site] = fovi_res.GetMeasResult(site, MIRET);
		result_r[site] = (result_v2[site] - result_v1[site]) /( result_i2[site] - result_i1[site]);
		//result_r[site] = (result_v[site] - pullup_base_v[site]) / result_i[site];
		result_r[site] = result_r[site] * get_scale(unit);
	}

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result_r[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result_r, lolim, hilim, unit);

	//fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	//delay_ms(10);
	//i_set = 2 / (lolim + hilim)*get_scale(unit); //电阻上产生1V的压降
	//if (i_set > 1.0) i_set = 1.0;
	//if (i_set < 1.0e-4)
	//{
	//	i_set = 10 * i_set;
	//}
	//FOVI_IRNG i_range;
	//FOVI_VRNG v_range;
	//i_range = get_fovi_i_range(i_set);
	//if (P_flag == PULL_DOWN)
	//	v_range = get_fovi_v_range(i_set*hilim / get_scale(unit));
	//else
	//	v_range = get_fovi_v_range(5 - i_set*lolim / get_scale(unit));
	//fovi_res.Set(FV, 0, v_range, i_range, RELAY_ON);
	//fovi_res.Set(FI, 0, v_range, i_range, RELAY_ON);
	//delay_ms(1);
	//if (P_flag == PULL_DOWN)
	//	fovi_res.Set(FI, i_set, v_range, i_range, RELAY_ON);
	//else
	//	fovi_res.Set(FI, -i_set, v_range, i_range, RELAY_ON);
	//delay_ms(10);
	//fovi_res.MeasureVI(40, 10);
	//SERIAL_BC{
	//	result_v[SITE_BC] = fovi_res.GetMeasResult(SITE_BC, MVRET);
	//	result_i[SITE_BC] = fovi_res.GetMeasResult(SITE_BC, MIRET);
	//	if (P_flag == PULL_DOWN)
	//	{
	//		result_r[SITE_BC] = result_v[SITE_BC] / (result_i[SITE_BC] + 1e-32);
	//	}
	//	else
	//	{
	//		result_r[SITE_BC] = (5 - result_v[SITE_BC]) / (result_i[SITE_BC] + 1e-32);
	//	}
	//	result_r[SITE_BC] = result_r[SITE_BC] * get_scale(unit);
	//}
	//fovi_res.Set(FI, 0, v_range, i_range, RELAY_ON);
	//delay_ms(20);
	//fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	//delay_ms(10);
	//fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);

	//if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result_r[SITE_BC];
	//if (result1 == NULL) log(tnum++, component, result_r, lolim, hilim, unit);


	//---------------------Save datalog
	set_data_after_boardcheck(result_r, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}


	return TRUE;
}

//【2.2 FPVI源 RES】
BOOL BoardCheck::test_r(PULLUP_FLAG P_flag, FPVI10 &fpvi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1)
{
	double result_v[SITE_NUM];
	double result_i[SITE_NUM];
	double result_r[SITE_NUM];

	double i_set;
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	delay_ms(10);

	i_set = 2 / (lolim + hilim)*get_scale(unit);
	if (i_set > 1.0) i_set = 1.0;
	if (i_set < 1.0e-4)
	{
		i_set = 10 * i_set;
	}
	FPVI10_IRNG i_range;
	FPVI10_VRNG v_range;
	i_range = get_fpvi_i_range(i_set);
	if (P_flag == PULL_DOWN)
		v_range = get_fpvi_v_range(i_set*hilim / get_scale(unit));
	else
		v_range = get_fpvi_v_range(5 - i_set*hilim / get_scale(unit));
	fpvi_res.Set(FI, 0, v_range, i_range, RELAY_ON);
	if (P_flag == PULL_DOWN)
		fpvi_res.Set(FI, i_set, v_range, i_range, RELAY_ON);
	else
		fpvi_res.Set(FI, -i_set, v_range, i_range, RELAY_ON);
	delay_ms(10);
	fpvi_res.MeasureVI(40, 10);
	SERIAL_BC{
		result_v[SITE_BC] = fpvi_res.GetMeasResult(SITE_BC, MVRET);
		result_i[SITE_BC] = fpvi_res.GetMeasResult(SITE_BC, MIRET);
		if (P_flag == PULL_DOWN)
			result_r[SITE_BC] = result_v[SITE_BC] / (result_i[SITE_BC] + 1e-32);
		else
			result_r[SITE_BC] = (5 - result_v[SITE_BC]) / (result_i[SITE_BC] + 1e-32);

		result_r[SITE_BC] = result_r[SITE_BC] * get_scale(unit);
	}
	fpvi_res.Set(FI, 0, v_range, i_range, RELAY_ON);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	delay_ms(10);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result_r[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result_r, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result_r, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}

//源-源电阻
//【2.3 FOVI源-FOVI源 RES】 (res2给0,变成对地电阻)
BOOL BoardCheck::test_r(FOVI &fovi_res1, FOVI &fovi_res2, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result_v[SITE_NUM];
	double result_r[SITE_NUM];
	double i_set;
	//if (delay <= 0){
	//	string comment;
	//	comment = "T" + int2str(tnum) + " " + component + " test_r delay can't be less than 0ms";
	//	MessageBoxA(NULL, comment.c_str(), "诊断提示对话框", MB_OK);
	//	return FALSE;
	//}
	i_set = 0.8 / (lolim + hilim)*get_scale(unit);

	if (i_set > 0.2) i_set = 0.2;
	if (i_set < 1.0e-4)
	{
		i_set = 10 * i_set;
	}
	FOVI_IRNG i_range;

	i_range = get_fovi_i_range(i_set);
	fovi_res2.Set(FV, 0, FOVI_10V, i_range, RELAY_ON);
	fovi_res1.Set(FI, 0, FOVI_10V, i_range, RELAY_ON);
	fovi_res1.Set(FI, i_set, FOVI_10V, i_range, RELAY_ON);
	delay_ms(10);
	fovi_res1.MeasureVI(40, 10);
	SERIAL_BC{
		result_v[SITE_BC] = fovi_res1.GetMeasResult(SITE_BC, MVRET);
		result_r[SITE_BC] = result_v[SITE_BC] / (i_set + 1e-32);
		result_r[SITE_BC] = result_r[SITE_BC] * get_scale(unit);
	}
	fovi_res1.Set(FI, 0, FOVI_10V, i_range, RELAY_ON);
	fovi_res2.Set(FV, 0, FOVI_10V, i_range, RELAY_ON);

	fovi_res1.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	fovi_res2.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(10);
	fovi_res1.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);
	fovi_res2.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_OFF);


	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result_r[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result_r, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result_r, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}


	return TRUE;
}
//源-源电阻
//【2.4 FPVI源-FPVI源 RES】(res2给0,变成对地电阻)
BOOL BoardCheck::test_r(FPVI10 &fpvi_res1, FPVI10 &fpvi_res2, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result_v[SITE_NUM];
	double result_r[SITE_NUM];
	double i_set;
	//if (delay <= 0){
	//	string comment;
	//	comment = "T" + int2str(tnum) + " " + component + " test_r delay can't be less than 0ms";
	//	MessageBoxA(NULL, comment.c_str(), "诊断提示对话框", MB_OK);
	//	return FALSE;
	//}
	i_set = 0.8 / (lolim + hilim)*get_scale(unit);

	if (i_set > 0.2) i_set = 0.2;
	if (i_set < 1.0e-4)
	{
		i_set = 10 * i_set;
	}
	FPVI10_IRNG i_range;

	i_range = get_fpvi_i_range(i_set);
	fpvi_res2.Set(FV, 0, FPVI10_10V, i_range, RELAY_ON);
	fpvi_res1.Set(FI, 0, FPVI10_10V, i_range, RELAY_ON);
	fpvi_res1.Set(FI, i_set, FPVI10_10V, i_range, RELAY_ON);
	delay_ms(10);
	fpvi_res1.MeasureVI(40, 10);
	SERIAL_BC{
		result_v[SITE_BC] = fpvi_res1.GetMeasResult(SITE_BC, MVRET);
		result_r[SITE_BC] = result_v[SITE_BC] / (i_set + 1e-32);
		result_r[SITE_BC] = result_r[SITE_BC] * get_scale(unit);
	}
	fpvi_res1.Set(FI, 0, FPVI10_10V, i_range, RELAY_ON);
	fpvi_res2.Set(FV, 0, FPVI10_10V, i_range, RELAY_ON);

	fpvi_res1.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);
	fpvi_res2.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);
	delay_ms(10);
	fpvi_res1.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_OFF);
	fpvi_res2.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_OFF);


	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result_r[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result_r, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result_r, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}


	return TRUE;
}
//**********************************2.RES *************************//


//**********************************3.Relay:Check 电压*************************//
//***************单个源对地/固定源(VI源)
//【3.1 FOVI源 relay】对地继电器，mohm
BOOL BoardCheck::test_relay(FOVI &fovi_res, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];
	double voltage[SITE_NUM];
	double current[SITE_NUM];

	if (vi.mode == FV)
		fovi_res.Set(FV, vi.v, vi.v_range, vi.i_range, RELAY_ON);//default: vi.mode=FV,3V,measure I，clamp，FOVI 10mA
	else
		fovi_res.Set(FI, vi.i, vi.v_range, vi.i_range, RELAY_ON);

	delay_ms(vi.delay);
	fovi_res.MeasureVI(vi.sample_times, vi.sample_period);

	SERIAL_BC voltage[SITE_BC] = fovi_res.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC current[SITE_BC] = fovi_res.GetMeasResult(SITE_BC, MIRET);
	SERIAL_BC result[SITE_BC] = voltage[SITE_BC] / current[SITE_BC] * get_scale(unit);
	fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(10);
	fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;

}
//【3.2 FPVI源 relay】对地继电器 mohm
BOOL BoardCheck::test_relay(FPVI10 &fpvi_res, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];
	double voltage[SITE_NUM];
	double current[SITE_NUM];

	if (vi.mode == FV)
		fpvi_res.Set(FV, vi.v, vi.fpvi_v_range, vi.fpvi_i_range, RELAY_ON); //default: vi.mode = FV, 3V, measure I，clamp，FPVI 10mA
	else
		fpvi_res.Set(FI, vi.i, vi.fpvi_v_range, vi.fpvi_i_range, RELAY_ON);

	delay_ms(vi.delay);
	fpvi_res.MeasureVI(vi.sample_times, vi.sample_period);

	SERIAL_BC voltage[SITE_BC] = fpvi_res.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC current[SITE_BC] = fpvi_res.GetMeasResult(SITE_BC, MIRET);
	SERIAL_BC result[SITE_BC] = voltage[SITE_BC] / current[SITE_BC] * get_scale(unit);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	delay_ms(10);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;

}

//【3.3 FOVI-FOVI源 relay, FOVI force,FOVI measure】电阻ohm
BOOL BoardCheck::test_relay(FOVI &fovi_force, FOVI &fovi_measure, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];
	double voltage[SITE_NUM];
	double current[SITE_NUM];
	double voltage_force[SITE_NUM];

	fovi_force.Set(FV, vi.v, vi.v_range, vi.i_range, RELAY_ON);//3V,FOVI_5V,FOVI_10mA,
	fovi_measure.Set(FI, 0, vi.v_range, FOVI_10MA, RELAY_ON);
	delay_ms(vi.delay);

	fovi_force.MeasureVI(vi.sample_times, vi.sample_period);
	fovi_measure.MeasureVI(vi.sample_times, vi.sample_period);

	SERIAL_BC voltage_force[SITE_BC] = fovi_force.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC voltage[SITE_BC] = fovi_measure.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC current[SITE_BC] = fovi_measure.GetMeasResult(SITE_BC, MIRET);
	SERIAL_BC result[SITE_BC] = voltage[SITE_BC] / current[SITE_BC] * get_scale(unit);

	fovi_force.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	fovi_measure.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(10);
	fovi_force.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	fovi_measure.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;

}
//【3.4 FOVI-FPVI源 relay, FOVI force,FPVI measure】电阻ohm
BOOL BoardCheck::test_relay(FOVI &fovi_force, FPVI10 &fpvi_measure, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];
	double voltage[SITE_NUM];
	double current[SITE_NUM];
	double voltage_force[SITE_NUM];

	fovi_force.Set(FV, vi.v, vi.v_range, vi.i_range, RELAY_ON);//3V,FOVI_5V,FOVI_10mA,
	fpvi_measure.Set(FI, 0, vi.fpvi_v_range, FPVI10_10MA, RELAY_ON);//FPVI10_10MA
	delay_ms(vi.delay);

	fovi_force.MeasureVI(vi.sample_times, vi.sample_period);
	fpvi_measure.MeasureVI(vi.sample_times, vi.sample_period);

	SERIAL_BC voltage_force[SITE_BC] = fovi_force.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC voltage[SITE_BC] = fpvi_measure.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC current[SITE_BC] = fpvi_measure.GetMeasResult(SITE_BC, MIRET);
//	SERIAL_BC result[SITE_BC] = abs(abs(voltage_force[SITE_BC]) - abs(voltage[SITE_BC])) / current[SITE_BC] * get_scale(unit);
	SERIAL_BC result[SITE_BC] = abs(voltage[SITE_BC])* get_scale(unit);

	fovi_force.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	fpvi_measure.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_ms(10);
	fovi_force.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	fpvi_measure.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);


	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;

}
//【3.5 FPVI-FPVI源 relay, FPVI force,FPVI measure】电阻ohm
BOOL BoardCheck::test_relay(FPVI10 &fpvi_force, FPVI10 &fpvi_measure, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];
	double voltage[SITE_NUM];
	double current[SITE_NUM];
	double voltage_force[SITE_NUM];

	fpvi_force.Set(FV, vi.v, vi.fpvi_v_range, vi.fpvi_i_range, RELAY_ON);//3V,FPVI_5V,FPVI_10mA,
	fpvi_measure.Set(FI, 0, vi.fpvi_v_range, FPVI10_10MA, RELAY_ON);
	delay_ms(vi.delay);

	fpvi_force.MeasureVI(vi.sample_times, vi.sample_period);
	fpvi_measure.MeasureVI(vi.sample_times, vi.sample_period);

	SERIAL_BC voltage_force[SITE_BC] = fpvi_force.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC voltage[SITE_BC] = fpvi_measure.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC current[SITE_BC] = fpvi_measure.GetMeasResult(SITE_BC, MIRET);
	SERIAL_BC result[SITE_BC] = abs(voltage_force[SITE_BC] - voltage[SITE_BC]) / current[SITE_BC] * get_scale(unit);

	fpvi_force.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	fpvi_measure.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_ms(10);
	fpvi_force.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);
	fpvi_measure.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}


	return TRUE;

}

//【3.6 FOVI-DIO源 relay, DIO force，FOVI measure】
BOOL BoardCheck::test_relay(FOVI &fovi_measure, const char* lpszGroupPinName, const char* lpszPinName, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];

	dioplus.Connect(lpszGroupPinName);
	fovi_measure.Set(FI, 0, vi.v_range, vi.i_range, RELAY_ON);
	//fovi_measure.Set(FI, vi.i, vi.v_range, vi.i_range, RELAY_ON);//i=0,FOVI_5V,FOVI_10MA;
	delay_ms(vi.delay);

	dioplus.SetVIH(vi.v);//3v
	dioplus.SetVIL(0.0f);
	delay_ms(1);

	dioplus.Run("checkstart", "checkhigh");//set high level=3v
	delay_ms(2);
	fovi_measure.MeasureVI(10, 10);

	dioplus.Run("checkhigh", "checkstop");//set high Z
	delay_ms(2);
	fovi_measure.Set(FI, 0, vi.v_range, vi.i_range, RELAY_ON);
	delay_ms(2);

	fovi_measure.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	delay_ms(10);
	fovi_measure.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);

	SERIAL_BC result[SITE_BC] = fovi_measure.GetMeasResult(SITE_BC, MVRET)* get_scale(unit);

	dioplus.Disconnect(lpszGroupPinName);
	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL)	log(tnum++, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}
//【3.7 FPVI - DIO源 relay, DIO force，FPVI measure】
BOOL BoardCheck::test_relay(FPVI10 &fpvi_measure, const char* lpszGroupPinName, const char* lpszPinName, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];

	dioplus.Connect(lpszGroupPinName);
	fpvi_measure.Set(FI, 0, vi.fpvi_v_range, vi.fpvi_i_range, RELAY_ON);
	fpvi_measure.Set(FI, vi.i, vi.fpvi_v_range, vi.fpvi_i_range, RELAY_ON);//i=0,FPVI10_5V,FPVI10_10MA;
	delay_ms(vi.delay);

	dioplus.SetVIH(vi.v);//3v
	dioplus.SetVIL(0.0f);
	delay_ms(1);

	dioplus.Run("checkstart", "checkhigh");//set high level=3v
	delay_ms(2);
	fpvi_measure.MeasureVI(10, 10);

	dioplus.Run("checkhigh", "checkstop");//set high Z
	delay_ms(2);
	fpvi_measure.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_ON);
	delay_ms(10);
	fpvi_measure.Set(FV, 0, FPVI10_5V, FPVI10_10MA, RELAY_OFF);

	SERIAL_BC result[SITE_BC] = fpvi_measure.GetMeasResult(SITE_BC, MVRET)* get_scale(unit);

	dioplus.Disconnect(lpszGroupPinName);
	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL)	log(tnum++, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}


	return TRUE;
}


//==================================================两个源之间check(VI-QVM源）================================================================//
//【3.8 FOVI-QVM源 relay,  FOVI force QVM measure】电压3V
BOOL BoardCheck::test_relay(FOVI &fovi_force, QVM &qvm_res, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];
	double qvm_results[SITE_NUM];
	QVM_LADC_VRANG v_range = QVM_LADC_5V;
	qvm_res.Connect();
	delay_ms(5);
	fovi_force.Set(FV, vi.v, vi.v_range, vi.i_range, RELAY_ON);//V=3V，FOVI_5V,FOVI_10mA
	delay_ms(vi.delay);
	qvm_res.MeasureLADC(100, 10, v_range, QVM_LADC_10KHz, MEAS_NORMAL);
	
	for (site = 0; site < SITE_NUM/2; site++)//qvm板卡配置一块，只能使用4ch；配置两块时换成SITE_NUM
	{
		result[site] = qvm_res.GetMeasResult(site);
		result[site] = abs(result[site] * get_scale(unit));
	}

	fovi_force.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);//V=3V，FOVI_5V,FOVI_10mA
	delay_ms(10);
	fovi_force.Set(FV, 0,FOVI_10V, FOVI_10MA, RELAY_OFF);//V=3V，FOVI_5V,FOVI_10mA
	//SERIAL_BC	result1[SITE_BC] = result[SITE_BC];

	//if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);
	qvm_res.Disconnect();

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}
//【3.9 FPVI-QVM源 relay,  FPVI force，QVM measure】电压3V
BOOL BoardCheck::test_relay(FPVI10 &fpvi_force, QVM &qvm_res, Cvi_config &vi, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];

	QVM_LADC_VRANG v_range = QVM_LADC_5V;
	qvm_res.Connect();
	delay_ms(5);
	fpvi_force.Set(FV, vi.v, vi.fpvi_v_range, vi.fpvi_i_range, RELAY_ON); //V = 3V，FPVI10_5V, FPVI10_10mA
	delay_ms(vi.delay);
	qvm_res.MeasureLADC(100, 10, v_range, QVM_LADC_10KHz, MEAS_NORMAL);

	//QVM_GP_MEASURE(result, grp_no);
	for (site = 0; site < SITE_NUM/2; site++)//qvm板卡配置一块，只能使用4ch；配置两块时换成SITE_NUM
	{
		result[site] = qvm_res.GetMeasResult(site, MVRET);
		result[site] = abs(result[site] * get_scale(unit));
	}
	fpvi_force.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	delay_ms(10);
	fpvi_force.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
	qvm_res.Disconnect();

// 
// 	if (result1 != NULL) SERIAL_BC result1[SITE_BC] = result[SITE_BC];
// 	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}

//***************两个源之间check(VI-QTMU源）
//【3.10 FOVI - QTMU源 relay, FOVI force QTMU measure】时间：1000us
BOOL BoardCheck::test_qtmu(FOVI &fovi_res, QTMU_PLUS &qtmu, BYTE source, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];
	
	fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);

	qtmu.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu.SetStartTrigger(0.5, QTMU_PLUS_POS_SLOPE);
	qtmu.SetStopTrigger(4.5, QTMU_PLUS_POS_SLOPE);
	qtmu.SetInSource(source);
	qtmu.Connect();
	qtmu.SetSinglePulseMeas(QTMU_PLUS_COARSE, QTMU_PLUS_TIME_US, 0);
	qtmu.SetTimeOut(2);

	fovi_res.Set(FV, 5, FOVI_10V, FOVI_10MA, RELAY_ON, 1);
	delay_ms(2);
	qtmu.SinglePlsMeas(0);

	fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(10);
	fovi_res.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	qtmu.Disconnect();

	for (site = 0; site < SITE_NUM; site++)
	{
		result[site] = qtmu.GetMeasureResult(site);
	}
	if (result1 != NULL) SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}
//【3.11 FPVI-QTMU源 relay,  FPVI force QTMU measure】时间：1000us
BOOL BoardCheck::test_qtmu(FPVI10 &fpvi_res, QTMU_PLUS &qtmu, BYTE source, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];
	
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);


	qtmu.SetStartInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu.SetStopInput(QTMU_PLUS_IMPEDANCE_1M, QTMU_PLUS_VRNG_5V, QTMU_PLUS_FILTER_PASS);
	qtmu.SetStartTrigger(0.5, QTMU_PLUS_POS_SLOPE);
	qtmu.SetStopTrigger(4.5, QTMU_PLUS_POS_SLOPE);
	qtmu.SetInSource(source);
	qtmu.Connect();
	qtmu.SetSinglePulseMeas(QTMU_PLUS_COARSE, QTMU_PLUS_TIME_US, 0);
	qtmu.SetTimeOut(2);

	fpvi_res.Set(FV, 5, FPVI10_10V, FPVI10_10MA, RELAY_ON, 1);
	delay_ms(2);
	qtmu.SinglePlsMeas(0);

	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	delay_ms(10);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);

	qtmu.Disconnect();

	for (site = 0; site < SITE_NUM; site++)
	{
		result[site] = qtmu.GetMeasureResult(site);
	}
	if (result1 != NULL) SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}

//***************三个源之间check
//【3.12 FOVI-FOVI-FPVI源 relay】（FOVI1 force 1V,FOVI2 force 3.6V,FPVI measure) 电阻ohm
BOOL BoardCheck::test_relay(FOVI &fovi_res1, FOVI &fovi_res2, FPVI10 &fpvi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1){
	double result[SITE_NUM];
	double voltage[SITE_NUM];
	double current[SITE_NUM];
	double voltage_res1[SITE_NUM];
	double voltage_res2[SITE_NUM];
	fovi_res1.Set(FV, 1, FOVI_5V, FOVI_10MA, RELAY_ON);
	fovi_res2.Set(FV, 3.6, FOVI_5V, FOVI_10MA, RELAY_ON);
	fpvi_res.Set(FI, 2e-3, FPVI10_10V, FPVI10_10MA, RELAY_ON);//2mA
	delay_ms(10);
	fpvi_res.MeasureVI(10, 10);
	fovi_res1.MeasureVI(10, 10);
	fovi_res2.MeasureVI(10, 10);
	SERIAL_BC voltage_res1[SITE_BC] = fovi_res1.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC voltage_res2[SITE_BC] = fovi_res2.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC voltage[SITE_BC] = fpvi_res.GetMeasResult(SITE_BC, MVRET);
	SERIAL_BC current[SITE_BC] = fpvi_res.GetMeasResult(SITE_BC, MIRET);
	SERIAL_BC result[SITE_BC] = abs(abs(voltage_res2[SITE_BC] - voltage_res1[SITE_BC]) - abs(voltage[SITE_BC])) / current[SITE_BC] * get_scale(unit);
	fovi_res1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	fovi_res2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_ON);
	fpvi_res.Set(FI, 0, FPVI10_10V, FPVI10_10UA, RELAY_ON);
	delay_ms(10);
	fovi_res1.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	fovi_res2.Set(FV, 0, FOVI_5V, FOVI_10MA, RELAY_OFF);
	fpvi_res.Set(FI, 0, FPVI10_10V, FPVI10_10UA, RELAY_OFF);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}
	return TRUE;
}



//*****************************4.only measure*************************//
//【4.1 fovi量电压】
BOOL BoardCheck::test_v(FOVI &FOVI_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1)	//measure v
{


	double result[SITE_NUM];
	FOVI_meas.Set(FI, 0, FOVI_20V, FOVI_100UA, RELAY_ON);
	delay_ms(5);
	FOVI_meas.MeasureVI(30, 100);
	SERIAL_BC result[SITE_BC] = FOVI_meas.GetMeasResult(SITE_BC, MVRET) * get_scale(unit);

	FOVI_meas.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_OFF);

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	FOVI_meas.Set(FI, 0, FOVI_10V, FOVI_100UA, RELAY_ON);
	delay_ms(10);
	FOVI_meas.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	delay_ms(2);
	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}

//【4.2 fpvi量电压】
BOOL BoardCheck::test_v(FPVI10 &FPVI10_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1)	//measure v
{
	double result[SITE_NUM];
	FPVI10_meas.Set(FI, 0, FPVI10_100MV, FPVI10_100MA, RELAY_ON);
	delay_ms(5);
	FPVI10_meas.MeasureVI(30, 100);
	SERIAL_BC result[SITE_BC] = FPVI10_meas.GetMeasResult(SITE_BC, MVRET) * get_scale(unit);

	FPVI10_meas.Set(FI, 0, FPVI10_10V, FPVI10_100UA, RELAY_OFF);

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	FPVI10_meas.Set(FI, 0, FPVI10_10V, FPVI10_100UA, RELAY_ON);
	delay_ms(10);
	FPVI10_meas.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
	delay_ms(2);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}
	return TRUE;
}

//【4.3 fovi量小电阻】mhom
BOOL BoardCheck::test_r_small(FOVI &FOVI_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1)
{
	double result_v1[SITE_NUM];
	double result_i1[SITE_NUM];
	double result_v2[SITE_NUM];
	double result_i2[SITE_NUM];
	double result_r[SITE_NUM];
	FOVI_meas.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(20);
	FOVI_meas.Set(FI, 0, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(20);
	FOVI_meas.Set(FI, 0.2, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(2);
	FOVI_meas.MeasureVI(100, 5);
	for (site = 0; site < SITE_NUM; site++)
	{
		result_i1[site] = FOVI_meas.GetMeasResult(site, MIRET);
		result_v1[site] = FOVI_meas.GetMeasResult(site, MVRET);
	}
	FOVI_meas.Set(FI, 0, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(20);
	FOVI_meas.Set(FI, 0.6, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(2);
	FOVI_meas.MeasureVI(100, 5);
	for (site = 0; site < SITE_NUM; site++)
	{
		result_i2[site] = FOVI_meas.GetMeasResult(site, MIRET);
		result_v2[site] = FOVI_meas.GetMeasResult(site, MVRET);
	}
	FOVI_meas.Set(FI, 0, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(20);
	FOVI_meas.Set(FV, 0, FOVI_1V, FOVI_1A, RELAY_ON);
	delay_ms(20);
	FOVI_meas.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(30);
	FOVI_meas.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	delay_ms(30);

	SERIAL_BC
	{
		if (abs(result_i1[SITE_BC] - 0.2) < 0.005)
		{
			result_r[SITE_BC] = (result_v1[SITE_BC] - result_v2[SITE_BC]) / (result_i1[SITE_BC] - result_i2[SITE_BC] + 1e-32);
			result_r[SITE_BC] = result_r[SITE_BC] * 1000;
		}
		else
		{
			result_r[SITE_BC] = 999;
		}
	}

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result_r[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result_r, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result_r, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}

//【4.4 fpvi量小电阻】mhom
BOOL BoardCheck::test_r_small(FPVI10 &FPVI10_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1)
{
	double result_v1[SITE_NUM];
	double result_i1[SITE_NUM];
	double result_v2[SITE_NUM];
	double result_i2[SITE_NUM];
	double result_r[SITE_NUM];
	FPVI10_meas.Set(FV, 0, FPVI10_1V, FPVI10_1A, RELAY_ON);
	delay_ms(20);
	FPVI10_meas.Set(FI, 0, FPVI10_1V, FPVI10_1A, RELAY_ON);
	delay_ms(20);
	FPVI10_meas.Set(FI, 0.2, FPVI10_1V, FPVI10_1A, RELAY_ON);
	delay_ms(2);
	FPVI10_meas.MeasureVI(100, 5);
	for (site = 0; site < SITE_NUM; site++)
	{
		result_i1[site] = FPVI10_meas.GetMeasResult(site, MIRET);
		result_v1[site] = FPVI10_meas.GetMeasResult(site, MVRET);
	}
	FPVI10_meas.Set(FI, 0, FPVI10_1V, FPVI10_1A, RELAY_ON);
	delay_ms(20);
	FPVI10_meas.Set(FI, 0.6, FPVI10_1V, FPVI10_1A, RELAY_ON);
	delay_ms(2);
	FPVI10_meas.MeasureVI(100, 5);
	for (site = 0; site < SITE_NUM; site++)
	{
		result_i2[site] = FPVI10_meas.GetMeasResult(site, MIRET);
		result_v2[site] = FPVI10_meas.GetMeasResult(site, MVRET);
	}
	FPVI10_meas.Set(FI, 0, FPVI10_1V, FPVI10_1A, RELAY_ON);
	delay_ms(20);
	FPVI10_meas.Set(FV, 0, FPVI10_10V, FPVI10_1A, RELAY_ON);
	delay_ms(20);
	FPVI10_meas.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);
	delay_ms(30);
	FPVI10_meas.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_OFF);
	delay_ms(30);

	SERIAL_BC
	{
		if (abs(result_i1[SITE_BC] - 0.2) < 0.005)
		{
			result_r[SITE_BC] = (result_v1[SITE_BC] - result_v2[SITE_BC]) / (result_i1[SITE_BC] - result_i2[SITE_BC] + 1e-32);
			result_r[SITE_BC] = result_r[SITE_BC] * 1000;
		}
		else
		{
			result_r[SITE_BC] = 999;
		}
	}

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result_r[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result_r, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result_r, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}

//【4.5 fovi量kelvin电阻】10k
BOOL BoardCheck::test_r_kelvin(FOVI &FOVI_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1)
{
	double result_v[SITE_NUM];
	double result_i[SITE_NUM];
	double result_r[SITE_NUM];
	FOVI_meas.Set(FV, 0, FOVI_10V, FOVI_100MA, RELAY_ON);
	delay_ms(50);
	FOVI_meas.Set(FV, 0, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_ms(50);
	FOVI_meas.Set(FV, 5, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_ms(10);
	FOVI_meas.MeasureVI(200, 10);
	SERIAL_BC{
		result_v[SITE_BC] = FOVI_meas.GetMeasResult(SITE_BC, MVRET);
		result_i[SITE_BC] = FOVI_meas.GetMeasResult(SITE_BC, MIRET);
		result_r[SITE_BC] = (result_v[SITE_BC]) / (result_i[SITE_BC] + 1e-32);
		result_r[SITE_BC] = result_r[SITE_BC] * get_scale(unit);
	}
	FOVI_meas.Set(FV, 0, FOVI_10V, FOVI_1MA, RELAY_ON);
	delay_ms(20);
	FOVI_meas.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_ON);
	delay_ms(50);
	FOVI_meas.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	delay_ms(50);
	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result_r[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result_r, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result_r, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}

//【4.6 fpvi量kelvin电阻】10k
BOOL BoardCheck::test_r_kelvin(FPVI10 &FPVI10_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1)
{
	double result_v[SITE_NUM];
	double result_i[SITE_NUM];
	double result_r[SITE_NUM];
	FPVI10_meas.Set(FV, 0, FPVI10_10V, FPVI10_100MA, RELAY_ON);
	delay_ms(50);
	FPVI10_meas.Set(FV, 0, FPVI10_10V, FPVI10_1MA, RELAY_ON);
	delay_ms(50);
	FPVI10_meas.Set(FV, 5, FPVI10_10V, FPVI10_1MA, RELAY_ON);
	delay_ms(10);
	FPVI10_meas.MeasureVI(200, 10);
	SERIAL_BC{
		result_v[SITE_BC] = FPVI10_meas.GetMeasResult(SITE_BC, MVRET);
		result_i[SITE_BC] = FPVI10_meas.GetMeasResult(SITE_BC, MIRET);
		result_r[SITE_BC] = (result_v[SITE_BC]) / (result_i[SITE_BC] + 1e-32);
		result_r[SITE_BC] = result_r[SITE_BC] * get_scale(unit);
	}
	FPVI10_meas.Set(FV, 0, FPVI10_10V, FPVI10_1MA, RELAY_ON);
	delay_ms(20);
	FPVI10_meas.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_ON);
	delay_ms(50);
	FPVI10_meas.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
	delay_ms(50);
	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result_r[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result_r, lolim, hilim, unit);

	//---------------------Save datalog
	set_data_after_boardcheck(result_r, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}

//【4.7 fovi FI=10UA量电压】
BOOL BoardCheck::test_v_p2p(FOVI &FOVI_meas, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1)	//measure v
{
	double result[SITE_NUM];
	FOVI_meas.Set(FI, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	FOVI_meas.Set(FI, 1e-5, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(5);
	FOVI_meas.MeasureVI(30, 100);
	SERIAL_BC result[SITE_BC] = FOVI_meas.GetMeasResult(SITE_BC, MVRET) * get_scale(unit);

	FOVI_meas.Set(FI, 0, FOVI_2V, FOVI_100UA, RELAY_OFF);

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	FOVI_meas.Set(FI, 0, FOVI_2V, FOVI_100UA, RELAY_ON);
	delay_ms(10);
	FOVI_meas.Set(FV, 0, FOVI_10V, FOVI_10MA, RELAY_OFF);
	delay_ms(2);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}
//【4.8 fpvi FI=10UA量电压】
BOOL BoardCheck::test_v_p2p(FPVI10 &fpvi_res, DWORD tnum, const char* component, double lolim, double hilim, const char* unit, double *result1)	//measure v
{
	double result[SITE_NUM];
	fpvi_res.Set(FI, 0, FPVI10_2V, FPVI10_100UA, RELAY_ON);
	fpvi_res.Set(FI, 1e-5, FPVI10_2V, FPVI10_100UA, RELAY_ON);
	delay_ms(5);
	fpvi_res.MeasureVI(30, 100);
	SERIAL_BC result[SITE_BC] = fpvi_res.GetMeasResult(SITE_BC, MVRET) * get_scale(unit);

	fpvi_res.Set(FI, 0, FPVI10_2V, FPVI10_100UA, RELAY_OFF);

	if (result1 != NULL)	SERIAL_BC result1[SITE_BC] = result[SITE_BC];
	if (result1 == NULL) log(tnum++, component, result, lolim, hilim, unit);

	fpvi_res.Set(FI, 0, FPVI10_2V, FPVI10_100UA, RELAY_ON);
	delay_ms(10);
	fpvi_res.Set(FV, 0, FPVI10_10V, FPVI10_10MA, RELAY_OFF);
	delay_ms(2);

	//---------------------Save datalog
	set_data_after_boardcheck(result, hilim, lolim);
	std::string input = component;
	std::string unit_input = unit;
	std::stringstream ss(input);
	std::string item;
	std::vector<std::string> comp_name;
	while (std::getline(ss, item, ','))
	{
		std::string::iterator new_end = std::remove_if(item.begin(), item.end(), [](char c)
		{
			return std::isspace(static_cast<unsigned char>(c));
		}
		);
		item.erase(new_end, item.end());
		comp_name.push_back(item);
	}
	// 使用迭代器输出分隔后的字符串
	for (std::vector<std::string>::iterator it = comp_name.begin(); it != comp_name.end(); ++it)
	{
		updateBoardCheckResults(*it, unit_input);
	}

	return TRUE;
}

//BOOL BoardCheck::Board_ID_Check(const char* boardName, const char* rev, const char* SCLChannel, const char* SDAChannel)
//{
//	BYTE EEPROM_ADDR = 0xA4;
//	ULONG nReadData1 = 0;
//	ULONG nReadData[512] = { 0 };
//	string bname_read = "";
//	string brev_read = "";
//	string bname(boardName);
//	string brev(rev);
//	string info;
//	int find = 0;
//	int acknack;
//	char c1[1];
//
//	//total 4k bits =512 bytes
//	dioplus.I2CSet(10000, 1, DCM_REG8, SCLChannel, SDAChannel);
//	dioplus.I2CConnect();//Connect I2C relay
//	dioplus.I2CSetPinLevel(5.0, 0, 2.0, 1.9);
//	dioplus.I2CSetSCLEdge(0, 10000 * 0.7);
//	dioplus.I2CSetSDAEdge(10000 * 0.1, 10000 * 0.995, 10000 * 0.1, 10000 * 0.95);
//	delay_ms(1);
//	dioplus.I2CReadData(EEPROM_ADDR, 0, 1);
//	delay_ms(1);
//	acknack = dioplus.I2CGetNACKIndex(0);
//	nReadData1 = dcm.I2CGetReadData(0, 0);
//	if (nReadData1 == 255)
//	{
//		MessageBoxA(NULL, "没有发现板子编号，请联系工程师解决", "板子编号检测对话框", MB_OK);
//		dcm.I2CDisconnect();
//		return false;
//		//need write data
//	}
//	else
//	{
//		dcm.I2CReadData(EEPROM_ADDR, 0, 64);
//		delay_ms(1);
//		for (int addr = 0; addr < 64; ++addr)
//		{
//			nReadData[addr] = dcm.I2CGetReadData(0, addr);
//			c1[0] = (char)nReadData[addr];//ascii transfer to char
//			if (nReadData[addr] == 124) find++;
//			else if (find == 0)	bname_read = bname_read + c1[0];
//			else if (find == 1)	brev_read = brev_read + c1[0];
//		}
//		dcm.I2CDisconnect();
//		if ((bname_read.compare(bname) == 0) && (brev_read.compare(brev) == 0))
//			return true;
//		else
//		{
//			info = "板子编号与写入值不符，写入值为 ";
//			info.append("板子名：");
//			info.append(bname_read);
//			info.append("板子版本号：");
//			info.append(brev_read);
//			MessageBoxA(NULL, info.c_str(), "板子编号检测对话框", MB_OK);
//			return false;
//		}
//
//
//	}
//	return true;
//
//}
//
//BOOL BoardCheck::Board_ID_Read(string* boardName, string* rev, string* number, const char* SCLChannel, const char* SDAChannel)
//{
//	BYTE EEPROM_ADDR = 0xA4;
//	ULONG nReadData1 = 0;
//	ULONG nReadData[512] = { 0 };
//	string bname_read = "";
//	string brev_read = "";
//	string bnumber_read = "";
//	string info;
//	int find = 0;
//	char c1[1];
//
//	//total 4k bits =512 bytes
//	dcm.I2CSet(10000, 1, DCM_REG8, SCLChannel, SDAChannel);
//	dcm.I2CConnect();//Connect I2C relay
//	dcm.I2CSetPinLevel(5.0, 0, 2.0, 1.9);
//	dcm.I2CSetSCLEdge(0, 10000 * 0.7);
//	dcm.I2CSetSDAEdge(10000 * 0.1, 10000 * 0.995, 10000 * 0.1, 10000 * 0.95);
//	delay_ms(1);
//	dcm.I2CReadData(EEPROM_ADDR, 0, 1);
//	delay_ms(1);
//	nReadData1 = dcm.I2CGetReadData(0, 0);
//	if (nReadData1 == 255)
//	{
//		MessageBoxA(NULL, "没有发现板子编号，请联系工程师解决", "板子编号检测对话框", MB_OK);
//		dcm.I2CDisconnect();
//		return false;
//		//need write data
//	}
//	else
//	{
//		dcm.I2CReadData(EEPROM_ADDR, 0, 64);
//		delay_ms(1);
//		for (int addr = 0; addr < 64; ++addr)
//		{
//			nReadData[addr] = dcm.I2CGetReadData(0, addr);
//			c1[0] = (char)nReadData[addr];//ascii transfer to char
//			if (nReadData[addr] == 124)  find++;
//			else if (find == 0)	bname_read = bname_read + c1[0];
//			else if (find == 1)	brev_read = brev_read + c1[0];
//			else if (find == 2)	bnumber_read = bnumber_read + c1[0];
//		}
//		(*boardName) = bname_read;
//		//boardName( bname_read.c_str());
//		(*rev) = brev_read;
//		(*number) = bnumber_read;
//		dcm.I2CDisconnect();
//		return true;
//
//
//	}
//
//}
//BOOL BoardCheck::Board_ID_Write(const char* boardName, const char* rev, const char* number, const char* SCLChannel, const char* SDAChannel)
//{
//	BYTE EEPROM_ADDR = 0xA4;
//	ULONG nReadData1 = 0;
//	ULONG nReadData[512] = { 0 };
//	string bname(boardName);
//	string brev(rev);
//	string bnumber(number);
//	string info;
//	int find = 0;
//	ULONG ulWriteData[SITE_NUM] = { 0 };
//	//total 4k bits =512 bytes
//	dcm.I2CSet(10000, 1, DCM_REG8, SCLChannel, SDAChannel);
//	dcm.I2CConnect();//Connect I2C relay
//	dcm.I2CSetPinLevel(5.0, 0, 2.0, 1.9);
//	dcm.I2CSetSCLEdge(0, 10000 * 0.7);
//	dcm.I2CSetSDAEdge(10000 * 0.1, 10000 * 0.995, 10000 * 0.1, 10000 * 0.95);
//	//write  board name
//	for (unsigned int i = 0; i < bname.length(); i++){
//		SERIAL ulWriteData[SITE] = (DWORD)bname[i];
//		dcm.I2CWriteData(EEPROM_ADDR, i, 1, ulWriteData);
//		delay_ms(1);
//	}
//	SERIAL ulWriteData[SITE] = 124;//'|'=124
//	dcm.I2CWriteData(EEPROM_ADDR, bname.length(), 1, ulWriteData);
//	delay_ms(1);
//	//write  board rev
//
//	for (unsigned int i = 0; i < brev.length(); i++){
//		SERIAL ulWriteData[SITE] = (DWORD)brev[i];
//		dcm.I2CWriteData(EEPROM_ADDR, bname.length() + i + 1, 1, ulWriteData);
//		delay_ms(1);
//	}
//	SERIAL ulWriteData[SITE] = 124;//'|'=124
//	dcm.I2CWriteData(EEPROM_ADDR, bname.length() + brev.length() + 1, 1, ulWriteData);
//	delay_ms(1);
//	//write  board number
//	for (unsigned int i = 0; i < bnumber.length(); i++){
//		SERIAL ulWriteData[SITE] = (DWORD)bnumber[i];
//		dcm.I2CWriteData(EEPROM_ADDR, bname.length() + brev.length() + i + 2, 1, ulWriteData);
//		delay_ms(1);
//	}
//	SERIAL ulWriteData[SITE] = 124;//'|'=124
//	dcm.I2CWriteData(EEPROM_ADDR, bname.length() + brev.length() + bnumber.length() + 2, 1, ulWriteData);
//	delay_ms(1);
//	dcm.I2CReadData(EEPROM_ADDR, 0, 64);
//	delay_ms(1);
//	for (int addr = 0; addr < 64; ++addr)
//	{
//		nReadData[addr] = dcm.I2CGetReadData(0, addr);
//
//	}
//	dcm.I2CDisconnect();
//	return true;
//
//
//}


//void BoardCheck::create_data_block(string firstString, ...)
//{
//	// 初始化可变参数列表
//	va_list args;
//	va_start(args, firstString);
//	// 循环读取并打印每个字符串，直到遇到NULL
//	char *str;
//	while ((str = va_arg(args, char *)) != NULL) 
//	{
//		updateBoardCheckResults(str);
//	}	
//	va_end(args);// 结束可变参数列表的使用
//}

void regression(int points, double *xin, double *yin, double *offs, double *slope, double *rms_err, double *max_err)
{
	double sx = 0, sy = 0, sxx = 0, syy = 0, sxy = 0;
	double ax, ay;
	double rmserr, maxerr;
	int i;

	for (i = 0; i < points; i++) {
		sx += xin[i]; sy += yin[i];
		sxx += xin[i] * xin[i]; sxy += xin[i] * yin[i];
		syy += yin[i] * yin[i];
	}
	/* calc best line fit */
	ax = sx / points; ay = sy / points;;
	*slope = (sxy - points*ax*ay) / (sxx - points*ax*ax);
	*offs = ay - *slope*ax;

	/* get worst case and rms error compared to best line fit */
	maxerr = sx = sxx = 0;
	for (i = 0; i<points; i++) {
		double err = yin[i] - (xin[i] * *slope + *offs);
		sx += err;
		sxx += err*err;
		if (fabs(err)>fabs(maxerr))
			maxerr = fabs(err);
	}
	rmserr = sqrt((points*sxx - sx*sx) / (points*(points - 1)));

	if (rms_err)
		*rms_err = rmserr;
	if (max_err)
		*max_err = maxerr;
}

// 函数定义，用于处理可变参数并更新map
void BoardCheck::updateBoardCheckResults(string  str_input, string unit_input) {
	std::string stringKey = str_input;
	// 检查map中是否存在该字符串作为键, 如果存在，更新对应的值

	bool found = false;
	for (site = 0; site < SITE_NUM; site++)
	{
		std::map<string, MyData>::iterator it = m_boardcheck_results[site].find(stringKey);

		if (it != m_boardcheck_results[site].end())	// 找到了字符串，打印对应的值
		{
			if (m_boardcheck_results[site][stringKey].check_status == false)// 如果之前时failed就更新当前测试的状态结果，如果是pass的不更新结果
			{
				m_boardcheck_results[site][stringKey].check_status = m_check_stat[site];
				m_boardcheck_results[site][stringKey].test_data = m_test_value[site];
				m_boardcheck_results[site][stringKey].high_limit = m_hlimit;
				m_boardcheck_results[site][stringKey].low_limit = m_llimit;
				m_boardcheck_results[site][stringKey].unit = unit_input;
				if (m_check_stat[site] == TRUE)
				{
					m_boardcheck_results[site][stringKey].flag = "PASS";
				}
				else
				{
					m_boardcheck_results[site][stringKey].flag = "FAIL";
				}
			}
		}
		else// 没有找到字符串，添加到map中，，说明是新的模块，就增加加过
		{		
			m_boardcheck_results[site][stringKey].check_status = m_check_stat[site];
			m_boardcheck_results[site][stringKey].test_data = m_test_value[site];
			m_boardcheck_results[site][stringKey].high_limit = m_hlimit;
			m_boardcheck_results[site][stringKey].low_limit = m_llimit;
			m_boardcheck_results[site][stringKey].unit = unit_input;
			if (m_check_stat[site] == TRUE)
			{
				m_boardcheck_results[site][stringKey].flag = "PASS";
			}
			else
			{
				m_boardcheck_results[site][stringKey].flag = "FAIL";
			}
		}
	}
}

// 注意：printStrings函数在问题描述中并未明确其用途，因此这里没有实现它
// 如果需要实现printStrings函数，可以根据之前的描述进行编写

void BoardCheck::set_data_after_boardcheck(double *test_value, double hlimit, double llimit)
{
	for (site = 0; site < SITE_NUM; site++)
	{
		m_test_value[site] = test_value[site];
		m_hlimit = hlimit;
		m_llimit = llimit;
		if (m_test_value[site] <= m_hlimit && m_test_value[site] >= llimit)
		{
			m_check_stat[site] =true;
		}
		else
		{
			m_check_stat[site] = false;
		}
	}
}


void BoardCheck::SetConsoleTextSize(int fontSize) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;  // 宽度设置为0，由系统决定
	cfi.dwFontSize.Y = fontSize;  // 设置高度
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy(cfi.FaceName, L"Consolas");  // 可以选择其他字体

	SetCurrentConsoleFontEx(hOut, FALSE, &cfi);
}

bool BoardCheck::check_results_summary()
{

	if (AllocConsole())//(AttachConsole(ATTACH_PARENT_PROCESS))//
	{
		COORD size = { 180, 180 };

		SetConsoleTitleA("AccoTEST Debug Window");
		freopen("conout$", "w+t", stdout);
		::DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
		//HANDLE hOUT = GetStdHandle(STD_OUTPUT_HANDLE);//获取标准输出句柄
		//hOUT = GetStdHandle(STD_OUTPUT_HANDLE);
		//设置控制台缓冲区大小
		//SetConsoleScreenBufferSize(hOUT, size);
		//delay_ms(2000);
	}



	cout << std::left << std::setw(20) << "I successed" << std::setw(20) << "I failed" << "paly"<< std::endl;
	cout << std::left << std::setw(20) << "I did" << std::setw(20) << "I fghjbchubru" << "frggvdbr" << std::endl;


	int row_max = SITE_NUM + 6;
	int col_max = 0;
	for (site = 0; site < SITE_NUM; site++)
	{
		for (std::map<string, MyData>::iterator it = m_boardcheck_results[site].begin(); it != m_boardcheck_results[site].end(); ++it)
		{
			col_max++;
		}
		break;
	}

	std::vector<std::vector<std::string>> BoardCheckDatalog(row_max+31, std::vector<std::string>(col_max+2));

	int col_cnt = 0;
	for (site = 0; site < SITE_NUM; site++)
	{
		for (std::map<string, MyData>::iterator it = m_boardcheck_results[site].begin(); it != m_boardcheck_results[site].end(); ++it)
		{
			BoardCheckDatalog[1][col_cnt + 2] = it->first;
			BoardCheckDatalog[2][col_cnt + 2] = to_string(it->second.high_limit);
			BoardCheckDatalog[3][col_cnt + 2] = to_string(it->second.low_limit);
			BoardCheckDatalog[4][col_cnt + 2] = it->second.unit;
			BoardCheckDatalog[5][col_cnt + 2] = "";
			BoardCheckDatalog[1][0] = "ComponentName";
			BoardCheckDatalog[2][0] = "UpperLimit";
			BoardCheckDatalog[3][0] = "LowerLimit";
			BoardCheckDatalog[4][0] = "Unit";
			BoardCheckDatalog[5][0] = "SITE_NO";
			BoardCheckDatalog[1][1] = "CheckResults";
			BoardCheckDatalog[2][1] = "Pass";
			BoardCheckDatalog[3][1] = "Fail";
			BoardCheckDatalog[4][1] = " ";
			BoardCheckDatalog[5][1] = " ";
			col_cnt++;
		}
		break;
	}
	bool BoardcheckAllPass[SITE_NUM];
	for (site = 0; site < SITE_NUM; site++)//---初始化，假定boardcheck都是pass的
	{
		BoardcheckAllPass[site] = TRUE;
	}

	for (site = 0; site < SITE_NUM; site++)
	{
		if (site_connected[site] == 1)
		{
			int col_cnt = 0;
			BoardCheckDatalog[6 + site][1] = "PASS";
			for (std::map<string, MyData>::iterator it = m_boardcheck_results[site].begin(); it != m_boardcheck_results[site].end(); ++it)
			{
				BoardCheckDatalog[6 + site][0] = to_string(site + 1);
				if (it->second.check_status == false)
				{
					BoardCheckDatalog[6 + site][1] ="FAIL";
				}		
				BoardCheckDatalog[6 + site][col_cnt + 2] = to_string(it->second.test_data);
				if (it->second.check_status == false)
				{
					BoardcheckAllPass[site] = false;
				}
				col_cnt++;
			}
		}
	}

	//---------Fail content
	for (site = 0; site < SITE_NUM; site++)
	{
		if (site_connected[site] == 1)
		{
			int col_cnt = 0;
			BoardCheckDatalog[30 + site][1] = "PASS";
			for (std::map<string, MyData>::iterator it = m_boardcheck_results[site].begin(); it != m_boardcheck_results[site].end(); ++it)
			{
				BoardCheckDatalog[30 + site][0] = to_string(site + 1);
				if (it->second.check_status == false)
				{
					BoardCheckDatalog[30 + site][1] = "FAIL";
					BoardCheckDatalog[30 + site][col_cnt + 2] = to_string(it->second.test_data);
				}
				
				if (it->second.check_status == false)
				{
					BoardcheckAllPass[site] = false;
				}
				col_cnt++;
			}
		}
	}


	bool check_pass = true;
	BOOL  Total_BoardCheck_Result = true;
	string  Total_BC_Stat = "--PASS--";
	for (site = 0; site < SITE_NUM; site++)
	{
		if (BoardcheckAllPass[site] == false)
		{
			Total_BoardCheck_Result = false;
			Total_BC_Stat = "--FAIL--";
			check_pass = false;
		}
	}

	auto now = std::time(nullptr);
	std::tm* localTime = std::localtime(&now);
	// 格式化时间字符串用于文件名
	std::stringstream ss;
	ss << std::put_time(localTime, "%Y-%m-%d_%H-%M-%S");
	std::string timestamp = ss.str();
	// 创建文件名
	std::string filename = "BoardCheckLog" + Total_BC_Stat+ timestamp + ".csv";




	// 将数据写入CSV文件
	writeCSV(filename, BoardCheckDatalog);

	SERIAL_BC check_result[SITE_BC] = BoardcheckAllPass[SITE_BC];


	for (site = 0; site < SITE_NUM; site++)
	{
		for (std::map<string, MyData>::iterator it = m_boardcheck_results[site].begin(); it != m_boardcheck_results[site].end(); ++it)
		{
			if (it->second.test_data > it->second.low_limit  &&  it->second.test_data < it->second.high_limit)
			{
				SetColorBC(10);//GREEN
			}
			else
			{
				SetColorBC(FOREGROUND_INTENSITY | FOREGROUND_RED);//RED
			}
			cout << std::left << "SITE[ " << site + 1 << "]  " << std::setw(15) << std::setw(20) << it->first << std::setw(20) << it->second.test_data << std::setw(10) << it->second.low_limit << std::setw(10) << it->second.high_limit << std::setw(5) << it->second.unit << std::setw(5) << std::endl << std::flush;

			//printf_s("SITE[ %-2d]  %-20s%-20s%-10s%-10s%-5s\n",
			//	site + 1,
			//	it->first.c_str(),          // 假设first是std::string
			//	it->second.test_data, // 假设test_data是std::string
			//	it->second.low_limit, // 假设low_limit是std::string
			//	it->second.high_limit,// 假设high_limit是std::string
			//	it->second.unit.c_str());     // 假设unit是std::string


		}
	}

	if (check_pass)
	{
		SetColorBC(13);//RED
		//SetConsoleTextSize(25);
		printf_s("\n");
		printf_s("\n");
		printf_s("  ------------Congratulations!祝贺-------------------\n");
		printf_s("\n");
		delay_ms(200);
		printf_s("  Full Sites Board Check Have-------------- <<Passed>>!\n");
		printf_s("  所有工位的板子自检查已经-------------- <<通过>>!\n");
		system("pause");
		delay_ms(3000);
		printf_s("\n");
		printf_s("  Window will exit automatically.\n");
		printf_s("\n");
		fclose(stdout);
		FreeConsole();
	}
	else
	{
		SetColorBC(14);//RED
		//SetConsoleTextSize(25);
		printf_s("\n");
		printf_s("\n");
		printf_s("  ------------Sorry!-------------------\n");
		printf_s("  ------------抱歉!-------------------\n");
		printf_s("\n");
		delay_ms(200);
		printf_s("  Full Sites Board Check Has-------------- <<Failed>>!\n");
		printf_s("  当前板子存在部分工位的自检不过-------------- <<失败>>!\n");
		system("pause");
		delay_ms(3000);
		printf_s("\n");
		printf_s("   Please Check BoardCheck DataLog...... \n");
		printf_s("\n");
		delay_ms(2000);
		fclose(stdout);
		FreeConsole();
		delay_ms(1);
	}


		return check_pass;
}
//*****************************4.only measure*************************//
