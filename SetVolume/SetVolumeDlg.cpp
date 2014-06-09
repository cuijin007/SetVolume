// SetVolumeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SetVolume.h"
#include "SetVolumeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSetVolumeDlg 对话框




CSetVolumeDlg::CSetVolumeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetVolumeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSetVolumeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSetVolumeDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_OPEN, &CSetVolumeDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_CLOSE, &CSetVolumeDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDC_SMALL, &CSetVolumeDlg::OnBnClickedSmall)
	ON_MESSAGE(WM_SHOWTASK ,OnShowTask)
END_MESSAGE_MAP()


// CSetVolumeDlg 消息处理程序

BOOL CSetVolumeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	this->OnBnClickedOpen();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSetVolumeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	if ((nID & 0xFFF0) == SC_CLOSE)
	{
		//ShowWindow(SW_HIDE);
		this->OnBnClickedSmall();
		return;
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSetVolumeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CSetVolumeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define WH_KEYBOARD_LL     13
LRESULT CALLBACK HookFun(int nCode, WPARAM wParam, LPARAM lParam);

HHOOK g_hHook = NULL;

void CSetVolumeDlg::OnBnClickedOpen()
{
	// TODO: 在此添加控件通知处理程序代码
	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookFun, GetModuleHandle(NULL), NULL);
	if(g_hHook == NULL)
		MessageBox(_T("hook failure!"));
	else{
		}
		//MessageBox(_T("OK!"));


}

void CSetVolumeDlg::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	UnhookWindowsHookEx(g_hHook);
}

LRESULT CALLBACK HookFun(int nCode, WPARAM wParam, LPARAM lParam)
{
	CWPSTRUCT* p = (CWPSTRUCT*) lParam;
	if (nCode == HC_ACTION) 
	{ 
		switch (wParam) //wParam中是消息ID
		{ 
		case WM_KEYDOWN: 
			{  
				if(p->lParam == 107) 
				{
					// 'l' 键被按下 
					//do somthing+
					short state=GetKeyState(VK_SHIFT);
					if(state&0x8000)
					{
						keybd_event(175,0,0,0);
						keybd_event(175,0,KEYEVENTF_KEYUP,0);
					}
				}

				if(p->lParam == 109) 
				{
					// 'l' 键被按下 
					//do somthing
					short state=GetKeyState(VK_SHIFT);
					if(state&0x8000)
					{
						keybd_event(174,0,0,0);
						keybd_event(174,0,KEYEVENTF_KEYUP,0);
					}
				}
			} 
		}
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
	return NULL;
}


void CSetVolumeDlg::OnBnClickedSmall()
{
	NOTIFYICONDATA nid; 
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage=WM_SHOWTASK;//自定义的消息名称 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	//strcpy(nid.szTip,_T("音量调节快捷键"));//信息提示条为“计划任务提醒” 
	Shell_NotifyIcon(NIM_ADD,&nid);//在托盘区添加图标 
	ShowWindow(SW_HIDE);//隐藏主窗口 
}

LRESULT CSetVolumeDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME) 
		return 1;
	switch(lParam) 
	{ 
	case WM_RBUTTONUP: // 右键起来时弹出菜单
		{ 
			LPPOINT lpoint = new tagPOINT; // 或者LPPOINT lpoint = new CPoint;
			::GetCursorPos(lpoint); // 得到鼠标位置
			CMenu menu;
			menu.CreatePopupMenu(); // 声明一个弹出式菜单
			menu.AppendMenu(MF_STRING, WM_DESTROY, _T("退出(&X)"));
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);

			HMENU hmenu = menu.Detach(); //资源回收
			menu.DestroyMenu();
			delete lpoint;
		} 
		break; 
	case WM_LBUTTONDBLCLK: // 双击左键的处理
		{ 
			this->ShowWindow(SW_SHOWNORMAL); // 显示主窗口
			this->SetForegroundWindow(); // 置顶显示
		}
		break;
	}
	return 0;
}



void CSetVolumeDlg::OnOK()
{
	this->OnBnClickedSmall();
}

void CSetVolumeDlg::OnClose()
{
	this->OnBnClickedSmall();
}