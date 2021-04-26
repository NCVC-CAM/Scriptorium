// Scriptorium.h : SCRIPTORIUM アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_SCRIPTORIUM_H__7C17CB9F_3D62_461B_9B77_8676C312B2BB__INCLUDED_)
#define AFX_SCRIPTORIUM_H__7C17CB9F_3D62_461B_9B77_8676C312B2BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル
#include "ScriptOption.h"

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumApp:
// このクラスの動作の定義に関しては Scriptorium.cpp ファイルを参照してください。
//

class CScriptoriumApp : public CWinApp
{
	CScriptOption	m_opt;		// Scriptoriumｵﾌﾟｼｮﾝ

public:
	CScriptoriumApp();

// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CScriptoriumApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション
	CScriptOption*	GetScriptOption(void) {
		return &m_opt;
	}

	// 引数情報
	CString	m_strInFileName;
	CString	m_strOutFileName;

	//{{AFX_MSG(CScriptoriumApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SCRIPTORIUM_H__7C17CB9F_3D62_461B_9B77_8676C312B2BB__INCLUDED_)
