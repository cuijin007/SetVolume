// SetVolumeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SetVolume.h"
#include "SetVolumeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSetVolumeDlg �Ի���




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


// CSetVolumeDlg ��Ϣ�������

BOOL CSetVolumeDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	this->OnBnClickedOpen();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSetVolumeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSetVolumeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define WH_KEYBOARD_LL     13
LRESULT CALLBACK HookFun(int nCode, WPARAM wParam, LPARAM lParam);

HHOOK g_hHook = NULL;

void CSetVolumeDlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, HookFun, GetModuleHandle(NULL), NULL);
	if(g_hHook == NULL)
		MessageBox(_T("hook failure!"));
	else{
		}
		//MessageBox(_T("OK!"));


}

void CSetVolumeDlg::OnBnClickedClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UnhookWindowsHookEx(g_hHook);
}

LRESULT CALLBACK HookFun(int nCode, WPARAM wParam, LPARAM lParam)
{
	CWPSTRUCT* p = (CWPSTRUCT*) lParam;
	if (nCode == HC_ACTION) 
	{ 
		switch (wParam) //wParam������ϢID
		{ 
		case WM_KEYDOWN: 
			{  
				if(p->lParam == 107) 
				{
					// 'l' �������� 
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
					// 'l' �������� 
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
	nid.uCallbackMessage=WM_SHOWTASK;//�Զ������Ϣ���� 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	//strcpy(nid.szTip,_T("�������ڿ�ݼ�"));//��Ϣ��ʾ��Ϊ���ƻ��������ѡ� 
	Shell_NotifyIcon(NIM_ADD,&nid);//�����������ͼ�� 
	ShowWindow(SW_HIDE);//���������� 
}

LRESULT CSetVolumeDlg::OnShowTask(WPARAM wParam,LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME) 
		return 1;
	switch(lParam) 
	{ 
	case WM_RBUTTONUP: // �Ҽ�����ʱ�����˵�
		{ 
			LPPOINT lpoint = new tagPOINT; // ����LPPOINT lpoint = new CPoint;
			::GetCursorPos(lpoint); // �õ����λ��
			CMenu menu;
			menu.CreatePopupMenu(); // ����һ������ʽ�˵�
			menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�˳�(&X)"));
			menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);

			HMENU hmenu = menu.Detach(); //��Դ����
			menu.DestroyMenu();
			delete lpoint;
		} 
		break; 
	case WM_LBUTTONDBLCLK: // ˫������Ĵ���
		{ 
			this->ShowWindow(SW_SHOWNORMAL); // ��ʾ������
			this->SetForegroundWindow(); // �ö���ʾ
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