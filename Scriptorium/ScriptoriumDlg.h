// ScriptoriumDlg.h : ヘッダー ファイル
//

#if !defined(AFX_SCRIPTORIUMDLG_H__EF4F0784_71A8_45A5_B861_C0A8F34F3EA6__INCLUDED_)
#define AFX_SCRIPTORIUMDLG_H__EF4F0784_71A8_45A5_B861_C0A8F34F3EA6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CustomControl.h"

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumDlg ダイアログ

class CScriptoriumDlg : public CDialog
{
	BOOL	m_bDetail;
	CString	m_strScript, m_strInFileName, m_strOutFileName;
	CStringList m_ltScript;
	void	MoveDlgWindow(const CPoint* = NULL);
	void	PathSetDlgItemPath(LPCTSTR lpszFullPath, UINT nID, CString& strEdit);
	void	AddComboBox(void);
	void	AddScriptHistory(LPCTSTR);
	CString CScriptoriumDlg::GetActiveScript(void);

// 構築
public:
	CScriptoriumDlg(CWnd* pParent = NULL);	// 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CScriptoriumDlg)
	enum { IDD = IDD_SCRIPTORIUM_DIALOG };
	CButton	m_ctRunButton;
	CEdit	m_ctEditOUT;
	CEdit	m_ctEditIN;
	CComboBox	m_cbxComboSF;
	CButton	m_ct_GRIN;
	CButton	m_ct_GROUT;
	CButton	m_ct_GRSF;
	CEdit	m_ctSuffix;
	CButton	m_ctCHK3;
	CButton	m_ctCHK2;
	CButton	m_ctCHK1;
	CCustomStatic	m_ct_STOUT;
	CCustomStatic	m_ct_STIN;
	CCustomStatic	m_ct_STSF;
	CButton	m_btn_option;
	BOOL	m_blCHK1;
	BOOL	m_blCHK2;
	BOOL	m_blCHK3;
	CString	m_strEditSuffix;
	CString	m_strEditOUT;
	CString	m_strEditIN;
	CString	m_strComboSF;
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CScriptoriumDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	HICON m_hIcon;

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CScriptoriumDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonOption();
	afx_msg void OnButtonRefsc();
	afx_msg void OnButtonRefin();
	afx_msg void OnButtonRefout();
	afx_msg void OnButtonRun();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeScript();
	afx_msg void OnKillfocusEditIn();
	afx_msg void OnKillfocusEditOut();
	afx_msg void OnKillfocusComboSf();
	//}}AFX_MSG
	// 書き込みオッケー
    afx_msg LRESULT StrWriteOK(WPARAM, LPARAM);
	// ドラッグされた
    afx_msg LRESULT DragOnControl(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SCRIPTORIUMDLG_H__EF4F0784_71A8_45A5_B861_C0A8F34F3EA6__INCLUDED_)
