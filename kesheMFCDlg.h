
// kesheMFCDlg.h: 头文件
//

#pragma once


// CkesheMFCDlg 对话框
class CkesheMFCDlg : public CDialogEx
{
// 构造
public:
	CkesheMFCDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_KESHEMFC_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CButton m_begin;
	CButton m_stop;
	CButton m_exit;
	CEdit m_edit1;
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnBnClickedButton3();
	//afx_msg void OnStnClickedWay4Static();
	CStatic m_cPicture;
	CStatic m_bmp1;
	//CStatic m_bmp2;
	//CStatic m_bmp3;
	//CStatic m_bmp4;
	CEdit m_edit4;
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit5;
	CEdit m_edit6;
	//afx_msg void OnBnClickedButtonExit();
	//afx_msg void OnClose();
};
