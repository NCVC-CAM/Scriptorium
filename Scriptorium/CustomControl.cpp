// CustomControl.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "Scriptorium.h"
#include "CustomControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCustomStatic

CCustomStatic::CCustomStatic()
{
}

CCustomStatic::~CCustomStatic()
{
}


BEGIN_MESSAGE_MAP(CCustomStatic, CStatic)
	//{{AFX_MSG_MAP(CCustomStatic)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCustomStatic メッセージ ハンドラ

void CCustomStatic::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if ( ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0) == 1 ) {
		TCHAR szFileName[_MAX_PATH];
		::DragQueryFile(hDropInfo, 0, szFileName, _MAX_PATH);
		m_strDragFile = szFileName;
//		SetSel(0, -1);
//		SetFocus();
		// ドラッグされたことを親に通知
		// この場合，フルパスをファイル名だけの表示にする
		GetParent()->SendMessage(WM_USER_DRAGCONTROL, (WPARAM)GetDlgCtrlID());
	}
	::DragFinish(hDropInfo);
	
	CStatic::OnDropFiles(hDropInfo);
}
