// Scriptorium.cpp : アプリケーション用クラスの定義を行います。
//

#include "stdafx.h"
#include "Scriptorium.h"
#include "ScriptoriumDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumApp

BEGIN_MESSAGE_MAP(CScriptoriumApp, CWinApp)
	//{{AFX_MSG_MAP(CScriptoriumApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumApp クラスの構築

CScriptoriumApp::CScriptoriumApp()
{
	// TODO: この位置に構築用のコードを追加してください。
	// ここに InitInstance 中の重要な初期化処理をすべて記述してください。
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CScriptoriumApp オブジェクト

CScriptoriumApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumApp クラスの初期化

BOOL CScriptoriumApp::InitInstance()
{
//	AfxEnableControlContainer();

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif

	//////////////////////////////
	// 二重起動防止 ～ 引数渡し
	//////////////////////////////
	HWND   hWnd;
	HANDLE hMap;
	LPSTR  pMap;
	//LPSTR  wBuf;
	if((hWnd = ::FindWindow(NULL, "Scriptorium")))
	{
		//AfxMessageBox("２回目の起動");
		// 引数あるときファイルマッピング
		if (__argc >= 2) {
			hMap = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, 1024, "SCRIPTORIUM");
			if(hMap){
				pMap = (LPSTR)::MapViewOfFile(hMap, FILE_MAP_WRITE, 0, 0, 0);
				if(pMap){
					::ZeroMemory(pMap, 1024);
					lstrcpy(pMap, __argv[1]);
					::UnmapViewOfFile(pMap);
					::SendMessage(hWnd, WM_USER_WRITE, NULL, NULL);
				}
				CloseHandle(hMap);
			}
		}
		//if(::IsIconic(hWnd)) ::ShowWindow(hWnd,SW_RESTORE);
		::SetForegroundWindow(hWnd);
		return FALSE;
	}

	////////////////////////////
	// オプション初期化
	////////////////////////////
	if ( !m_opt.InitInstance() )
		return FALSE;

	////////////////////////////
	// 引数取得
	////////////////////////////
	if (__argc >= 2) {
		char chrDrv[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
		_splitpath(__argv[1], chrDrv, chrDir, chrFile, chrExt);
		CString	strFile(chrFile);
		// In について
		m_strInFileName = __argv[1];
		// Out について
		m_strOutFileName = lstrcat(chrDrv, lstrcat(chrDir, chrFile)) + m_opt.GetSuffix() + chrExt;
		
	}

	CScriptoriumDlg dlg;
	m_pMainWnd = &dlg;	
	int nResponse = dlg.DoModal();

	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}
