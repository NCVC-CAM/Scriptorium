#if !defined(AFX_CUSTOMCONTROL_H__51D7D85E_FE21_48A6_A16D_F3C454F4B158__INCLUDED_)
#define AFX_CUSTOMCONTROL_H__51D7D85E_FE21_48A6_A16D_F3C454F4B158__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomControl.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CCustomStatic ウィンドウ

class CCustomStatic : public CStatic
{
// コンストラクション
public:
	CCustomStatic();

// アトリビュート
public:
	CString	m_strDragFile;	// ドラッグされたファイル名

// オペレーション
public:

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CCustomStatic)
	//}}AFX_VIRTUAL

// インプリメンテーション
public:
	virtual ~CCustomStatic();

	// 生成されたメッセージ マップ関数
protected:
	//{{AFX_MSG(CCustomStatic)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CUSTOMCONTROL_H__51D7D85E_FE21_48A6_A16D_F3C454F4B158__INCLUDED_)
