
// MyCalibration.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyCalibrationApp: 
// �йش����ʵ�֣������ MyCalibration.cpp
//

class CMyCalibrationApp : public CWinApp
{
public:
	CMyCalibrationApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyCalibrationApp theApp;