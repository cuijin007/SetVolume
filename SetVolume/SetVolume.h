// SetVolume.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSetVolumeApp:
// �йش����ʵ�֣������ SetVolume.cpp
//

class CSetVolumeApp : public CWinApp
{
public:
	CSetVolumeApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSetVolumeApp theApp;