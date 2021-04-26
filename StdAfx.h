// stdafx.h : 標準のシステム インクルード ファイル、
//            または参照回数が多く、かつあまり変更されない
//            プロジェクト専用のインクルード ファイルを記述します。
//

#if !defined(AFX_STDAFX_H__6E34BA2A_E0A4_4BCC_BA39_11D110CF23A9__INCLUDED_)
#define AFX_STDAFX_H__6E34BA2A_E0A4_4BCC_BA39_11D110CF23A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Windows ヘッダーから殆ど使用されないスタッフを除外します。

#include <afxwin.h>         // MFC のコアおよび標準コンポーネント
#include <afxext.h>         // MFC の拡張部分
#include <afxdisp.h>        // MFC のオートメーション クラス
#include <afxdtctl.h>		// MFC の Internet Explorer 4 コモン コントロール サポート
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC の Windows コモン コントロール サポート
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "atlbase.h"
#include "shlwapi.h"

#define	AfxGetScriptoriumApp()	((CScriptoriumApp *)AfxGetApp())
#define	SIZEOF(a)	( sizeof(a)/sizeof(a[0]) )

// User Message
#define WM_USER_WRITE		WM_USER + 100
#define	WM_USER_DRAGCONTROL	WM_USER + 101	// WPARAM -> nID

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_STDAFX_H__6E34BA2A_E0A4_4BCC_BA39_11D110CF23A9__INCLUDED_)
