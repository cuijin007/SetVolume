// SetVolumeDlg.h : ͷ�ļ�
//

#pragma once
#define WM_SHOWTASK WM_USER+1

// CSetVolumeDlg �Ի���
class CSetVolumeDlg : public CDialog
{
// ����
public:
	CSetVolumeDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SETVOLUME_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	
	void OnOK();
	void OnClose();

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedSmall();
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	
};
