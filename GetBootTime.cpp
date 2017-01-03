// GetBootTime.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GetBootTime.h"
#include <windows.h>


int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	SYSTEMTIME cT;
	WCHAR wzOutput[MAX_PATH];
	DWORD T;
	DWORD TotalSec;
	WORD Sec;
	DWORD TotalMin;
	WORD Min;
	DWORD TotalHour;
	WORD Hour;
	WORD Day;
	WORD Month;

	T = GetTickCount();
	GetLocalTime(&cT);
	TotalSec = T / 1000;
	Sec= TotalSec % 60;
	TotalMin = TotalSec / 60;
	Min = TotalMin % 60;
	TotalHour = TotalMin / 60;
	Hour = TotalHour % 24;
	Day = TotalHour / 24;
	Month = Day / 30;


	if (cT.wSecond >= Sec)
	{
		cT.wSecond = cT.wSecond - Sec;
	}
	else if (cT.wMinute > 0)
	{
		cT.wMinute --;
		cT.wSecond = cT.wSecond + 60 - Sec;
	}
	else if (cT.wHour > 0)
	{
		cT.wHour -- ;
		cT.wMinute += 59;
		cT.wSecond = cT.wSecond + 60 - Sec;
	}
	else
	{
		cT.wHour += 23 ;
		cT.wMinute += 59;
		cT.wSecond = cT.wSecond + 60 - Sec;
	}

	if (cT.wMinute >= Min)
	{
		cT.wMinute = cT.wMinute - Min;
	}
	else if (cT.wHour > 0)
	{
		cT.wHour --;
		cT.wMinute = cT.wMinute + 60 - Min;
	}
	else if (cT.wDay > 0)
	{
		cT.wDay --;
		cT.wHour += 23;
		cT.wMinute = cT.wMinute + 60 - Min;
	}
	else if (cT.wMonth > 0)
	{
		cT.wMonth --;
		cT.wDay += 29;
		cT.wHour += 23;
		cT.wMinute = cT.wMinute + 60 - Min;
	}
	else
	{
		cT.wYear --;
		cT.wMonth += 11;
		cT.wDay += 29;
		cT.wHour += 23;
		cT.wMinute = cT.wMinute + 60 - Min;
	}

	if (cT.wHour > Hour)
	{
		cT.wHour = cT.wHour - Hour;
	}
	else if (cT.wDay > 0)
	{
		cT.wDay -- ;
		cT.wHour = cT.wHour + 24 - Hour;
	}
	else if (cT.wMonth > 0)
	{
		cT.wMonth --;
		cT.wDay += 29;
		cT.wHour = cT.wHour + 24 - Hour;
	}
	else
	{
		cT.wYear --;
		cT.wMonth += 11;
		cT.wDay += 29;
		cT.wHour = cT.wHour + 24 - Hour;
	}


	if (cT.wDay > Day)
	{
		cT.wDay = cT.wDay - Day;
	}
	else if (cT.wMonth > 0)
	{
		cT.wMonth --;
		cT.wDay = cT.wDay + 30 - Day;
	}
	else
	{
		cT.wYear --;
		cT.wMonth += 11;
		cT.wDay = cT.wDay + 30 - Day;
	}

	if (cT.wMonth > Month)
	{
		cT.wMonth = cT.wMonth - Day;
	}
	else
	{
		cT.wYear --;
		cT.wMonth = cT.wMonth + 12 - Month;
	}

	wsprintfW(wzOutput, L"%d-%d-%d %d:%d:%d", cT.wYear, cT.wMonth, cT.wDay, cT.wHour, cT.wMinute, cT.wSecond);

	MessageBoxW(NULL, wzOutput, L"今日开机时间", MB_OK);

	return 0;
}