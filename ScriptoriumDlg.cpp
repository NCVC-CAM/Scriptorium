// ScriptoriumDlg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "Scriptorium.h"
#include "ScriptoriumDlg.h"
#include "atlbase.h"
#include "io.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ﾌｧｲﾙ参照
static	CString	FileReference(const CString& strFile, BOOL bRead, UINT nFilterID);

/////////////////////////////////////////////////////////////////////////////
// アプリケーションのバージョン情報で使われている CAboutDlg ダイアログ

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// ダイアログ データ
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard は仮想関数のオーバーライドを生成します
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV のサポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// メッセージ ハンドラがありません。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumDlg ダイアログ

CScriptoriumDlg::CScriptoriumDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CScriptoriumDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CScriptoriumDlg)
	m_strEditSuffix = _T("");
	m_strEditOUT = _T("");
	m_strEditIN = _T("");
	m_strComboSF = _T("");
	//}}AFX_DATA_INIT

	/////////////////////////
	// InitInstance()でもらった値の処理
	/////////////////////////
	CScriptoriumApp*	pApp = AfxGetScriptoriumApp();
	CScriptOption*		pOpt = pApp->GetScriptOption();	
	m_blCHK1 = pOpt->m_dwChk[0];
	m_blCHK2 = pOpt->m_dwChk[1];
	m_blCHK3 = pOpt->m_dwChk[2];
	m_strEditSuffix = pOpt->m_strSuffix;

	for ( POSITION pos = pOpt->m_ltSF.GetHeadPosition(); pos; ) {
		CString strTmp = pOpt->m_ltSF.GetNext(pos);
		if ( ::GetFileAttributes(strTmp) != 0xFFFFFFFF) // 実在するﾌｧｲﾙのみリストにほりこんでいく
			m_ltScript.AddHead( strTmp );
	}
	
	m_strInFileName = pApp->m_strInFileName;
	m_strOutFileName = pApp->m_strOutFileName;
	m_bDetail = pOpt->m_dwChk[3];	// 設定ボタン状態

	// メモ: LoadIcon は Win32 の DestroyIcon のサブシーケンスを要求しません。
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScriptoriumDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CScriptoriumDlg)
	DDX_Control(pDX, IDC_BUTTON_RUN, m_ctRunButton);
	DDX_Control(pDX, IDC_EDIT_OUT, m_ctEditOUT);
	DDX_Control(pDX, IDC_EDIT_IN, m_ctEditIN);
	DDX_Control(pDX, IDC_COMBO_SF, m_cbxComboSF);
	DDX_Control(pDX, IDC_STATIC_GRIN, m_ct_GRIN);
	DDX_Control(pDX, IDC_STATIC_GROUT, m_ct_GROUT);
	DDX_Control(pDX, IDC_STATIC_GRSF, m_ct_GRSF);
	DDX_Control(pDX, IDC_EDIT_SUFFIX, m_ctSuffix);
	DDX_Control(pDX, IDC_CHECK3, m_ctCHK3);
	DDX_Control(pDX, IDC_CHECK2, m_ctCHK2);
	DDX_Control(pDX, IDC_CHECK1, m_ctCHK1);
	DDX_Control(pDX, IDC_STATIC_OUT, m_ct_STOUT);
	DDX_Control(pDX, IDC_STATIC_IN, m_ct_STIN);
	DDX_Control(pDX, IDC_STATIC_SF, m_ct_STSF);
	DDX_Control(pDX, IDC_BUTTON_OPTION, m_btn_option);
	DDX_Check(pDX, IDC_CHECK1, m_blCHK1);
	DDX_Check(pDX, IDC_CHECK2, m_blCHK2);
	DDX_Check(pDX, IDC_CHECK3, m_blCHK3);
	DDX_Text(pDX, IDC_EDIT_SUFFIX, m_strEditSuffix);
	DDX_Text(pDX, IDC_EDIT_OUT, m_strEditOUT);
	DDX_Text(pDX, IDC_EDIT_IN, m_strEditIN);
	DDX_CBString(pDX, IDC_COMBO_SF, m_strComboSF);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CScriptoriumDlg, CDialog)
	//{{AFX_MSG_MAP(CScriptoriumDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_OPTION, OnButtonOption)
	ON_BN_CLICKED(IDC_BUTTON_REFSC, OnButtonRefsc)
	ON_BN_CLICKED(IDC_BUTTON_REFIN, OnButtonRefin)
	ON_BN_CLICKED(IDC_BUTTON_REFOUT, OnButtonRefout)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_SF, OnSelchangeScript)
	ON_EN_KILLFOCUS(IDC_EDIT_IN, OnKillfocusEditIn)
	ON_EN_KILLFOCUS(IDC_EDIT_OUT, OnKillfocusEditOut)
	ON_CBN_KILLFOCUS(IDC_COMBO_SF, OnKillfocusComboSf)
	//}}AFX_MSG_MAP

	// 書き込みオッケーメッセージ
    ON_MESSAGE(WM_USER_WRITE, StrWriteOK)
	// ドラッグされた
	ON_MESSAGE(WM_USER_DRAGCONTROL, DragOnControl)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumDlg メッセージ ハンドラ

BOOL CScriptoriumDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニュー項目をシステム メニューへ追加します。

	// IDM_ABOUTBOX はコマンド メニューの範囲でなければなりません。
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

	// このダイアログ用のアイコンを設定します。フレームワークはアプリケーションのメイン
	// ウィンドウがダイアログでない時は自動的に設定しません。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンを設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンを設定
	
	// TODO: 特別な初期化を行う時はこの場所に追加してください。

	// D&D許可
	m_ct_STSF.DragAcceptFiles();
	m_ct_STIN.DragAcceptFiles();
	m_ct_STOUT.DragAcceptFiles();

	// ウィンドウの表示状態を復元
	CScriptOption*		pOpt = AfxGetScriptoriumApp()->GetScriptOption();
	CPoint	pt(pOpt->m_dwPos[0], pOpt->m_dwPos[1]);
	MoveDlgWindow( &pt );

	// レジストリから得た ScriptFile を表示
	AddComboBox();

	// 引数から得た InFile，OutFile を表示
	PathSetDlgItemPath(m_strInFileName, IDC_STATIC_IN, m_strEditIN);
	PathSetDlgItemPath(m_strOutFileName, IDC_STATIC_OUT, m_strEditOUT);

	return TRUE;  // TRUE を返すとコントロールに設定したフォーカスは失われません。
}

void CScriptoriumDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// もしダイアログボックスに最小化ボタンを追加するならば、アイコンを描画する
// コードを以下に記述する必要があります。MFC アプリケーションは document/view
// モデルを使っているので、この処理はフレームワークにより自動的に処理されます。

void CScriptoriumDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画用のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// クライアントの矩形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンを描画します。
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// システムは、ユーザーが最小化ウィンドウをドラッグしている間、
// カーソルを表示するためにここを呼び出します。
HCURSOR CScriptoriumDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CScriptoriumDlg::OnButtonOption() 
{
	m_bDetail = !m_bDetail;
	MoveDlgWindow();
}

void CScriptoriumDlg::OnButtonRefsc() 
{
	// 現在の選択スクリプトを取得
	int	nIndex = m_cbxComboSF.GetCurSel();

	CString strFullPath;
	if ( nIndex >= 0 ){
		POSITION	pos = (POSITION)m_cbxComboSF.GetItemDataPtr(nIndex);
		strFullPath = m_ltScript.GetAt(pos);
	}else{
		strFullPath = "";
	}

	CString	strResult( FileReference(strFullPath, TRUE, IDS_SCRIPT_FILTER) );
	if ( !strResult.IsEmpty() ) {
		m_strScript = strResult;	// ﾌﾙﾊﾟｽGET!
		PathSetDlgItemPath(m_strScript, IDC_STATIC_SF, m_strComboSF);
	}
}

void CScriptoriumDlg::OnButtonRefin() 
{
	UpdateData();

	// InFile について
	CString	strResult( FileReference(m_strInFileName, TRUE, IDS_NCD_FILTER) );
	if ( strResult.IsEmpty() )
		return;
	m_strInFileName = strResult;
	PathSetDlgItemPath(m_strInFileName, IDC_STATIC_IN, m_strEditIN);

	// OutFile について
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	_splitpath(m_strInFileName, chrDrive, chrDir, chrFile, chrExt);
	m_strOutFileName  = lstrcat(lstrcat(chrDrive, chrDir), chrFile) + m_strEditSuffix + chrExt;
	PathSetDlgItemPath(m_strOutFileName, IDC_STATIC_OUT, m_strEditOUT);	
//	UpdateData(FALSE);
}

void CScriptoriumDlg::OnButtonRefout() 
{
	CString	strResult( FileReference(m_strOutFileName, FALSE, IDS_NCD_FILTER) );
	if ( !strResult.IsEmpty() ) {
		m_strOutFileName = strResult;
		PathSetDlgItemPath(m_strOutFileName, IDC_STATIC_OUT, m_strEditOUT);	
//		UpdateData(FALSE);
	}
}

void CScriptoriumDlg::OnButtonRun() 
{
	m_ctRunButton.SetFocus();
	UpdateData();

	DWORD	dwNGFlag = FILE_ATTRIBUTE_DIRECTORY | FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_SYSTEM;
	DWORD	dwAttri;

	TCHAR    szDrive[_MAX_DRIVE],
		szDir[_MAX_DIR],
		szFileName[_MAX_FNAME],
		szExt[_MAX_EXT];

	_tsplitpath_s(m_strOutFileName,
		szDrive, _MAX_DRIVE, szDir, _MAX_DIR,
		szFileName, _MAX_FNAME, szExt, _MAX_EXT);

	CString strFullPath(szDrive);    
	strFullPath += szDir;

	DWORD ErrCode;

	// 書き込み権限のフォルダかチェック
	HANDLE hFile = CreateFile(m_strOutFileName, GENERIC_READ | GENERIC_WRITE, NULL, NULL,
		CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	// ｽｸﾘﾌﾟﾄﾌｧｲﾙ チェック
	if( m_strScript.IsEmpty() ){
		AfxMessageBox("ｽｸﾘﾌﾟﾄﾌｧｲﾙ を入力してください。");
		m_cbxComboSF.SetFocus();
	}
	else if ( m_strComboSF.IsEmpty() ){
		AfxMessageBox("ｽｸﾘﾌﾟﾄﾌｧｲﾙ を入力してください。");
		m_cbxComboSF.SetFocus();
	}
	else if ( ::GetFileAttributes(m_strScript) == 0xFFFFFFFF ){
		AfxMessageBox( m_strScript + " は存在しません。");
		m_cbxComboSF.SetFocus();
		m_cbxComboSF.SetEditSel(0,-1);
	}
	else if ( ::GetFileAttributes(m_strScript) & dwNGFlag ){
		AfxMessageBox( m_strScript + " は不正なファイルです。");
		m_cbxComboSF.SetFocus();
		m_cbxComboSF.SetEditSel(0,-1);
	}

	// 入力ﾌｧｲﾙ チェック
	else if ( m_strInFileName.IsEmpty() ){
		AfxMessageBox("入力ﾌｧｲﾙ を入力してください。");
		m_ctEditIN.SetFocus();
	}
	else if ( m_strEditIN.IsEmpty() ){
		AfxMessageBox("入力ﾌｧｲﾙ を入力してください。");
		m_ctEditIN.SetFocus();
	}
	else if ( ::GetFileAttributes(m_strInFileName) == 0xFFFFFFFF ){
		AfxMessageBox( m_strInFileName + " は存在しません。");
		m_ctEditIN.SetFocus();
		m_ctEditIN.SetSel(0,-1);
	}
	else if ( ::GetFileAttributes(m_strInFileName) & dwNGFlag ){
		AfxMessageBox( m_strInFileName + " は不正なファイルです。");
		m_ctEditIN.SetFocus();
		m_ctEditIN.SetSel(0,-1);
	}

	// 出力ﾌｧｲﾙ チェック
	else if ( m_strOutFileName.IsEmpty() ){
		AfxMessageBox("出力ﾌｧｲﾙ を入力してください。");
		m_ctEditOUT.SetFocus();
	}
	else if ( m_strEditOUT.IsEmpty() ){
		AfxMessageBox("出力ﾌｧｲﾙ を入力してください。");
		m_ctEditOUT.SetFocus();
	}
	
	// 出力ファイルが書き込み権限のフォルダ内かチェック
	else if (hFile == INVALID_HANDLE_VALUE) {
		ErrCode = GetLastError();

		// 5:アクセス拒否 
		if (ErrCode == 5) {
			AfxMessageBox("出力ﾌｧｲﾙは書き込み権限可能なフォルダを選択して下さい。");
			m_ctEditOUT.SetFocus();
		}
	}
	
	
	else {
		dwAttri = ::GetFileAttributes(m_strOutFileName);
		if ( dwAttri != 0xFFFFFFFF ) {
			// ファイルがあるとき
			if ( dwAttri & (dwNGFlag|FILE_ATTRIBUTE_READONLY) ){
				AfxMessageBox( m_strOutFileName + " は不正なファイルです。");
				m_ctEditOUT.SetFocus();
				m_ctEditOUT.SetSel(0,-1);
				return;
			}
			else if (AfxMessageBox(m_strOutFileName + " は既に存在します。\n上書きしますか?", MB_YESNO|MB_DEFBUTTON2) == IDNO){
				m_ctEditOUT.SetFocus();
				m_ctEditOUT.SetSel(0,-1);
				return;
			}
		}
	
		CString tmpStr;
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory( &si, sizeof(si) );						// 指定された領域を0で埋める
		si.cb = sizeof( si );								// 自分の領域を格納するメンバに入れる
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;
		tmpStr = "perl \"" + m_strScript + "\" \"" + m_strInFileName + "\" \"" + m_strOutFileName + "\"";
		if ( CreateProcess(NULL, (LPSTR)(LPCTSTR)tmpStr, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi) != 0 ){
			CloseHandle( pi.hThread );						// スレッドのハンドルは使わないのですぐ破棄
			WaitForSingleObject( pi.hProcess, INFINITE );	// プロセスが終了するまでまつ
			CloseHandle( pi.hProcess );						// もうプロセスのハンドルは使わないので破棄
		}
/*		
		// デバッグ用
		CString tmpStr = "perl \"" + m_strScript + "\" \"" + m_strInFileName + "\" \"" + m_strOutFileName + "\"";
		AfxMessageBox(tmpStr);
*/		
		if(m_blCHK3) AfxMessageBox("完了しました。", MB_ICONINFORMATION);
		if(m_blCHK1) ShellExecute(NULL, "open", m_strOutFileName, NULL, NULL, SW_SHOWNORMAL);
		if(m_blCHK2) CDialog::OnOK();

		AddScriptHistory(m_strScript);
		AddComboBox();  
	}
}

void CScriptoriumDlg::OnDestroy() 
{
	UpdateData();

	CScriptOption*		pOpt = AfxGetScriptoriumApp()->GetScriptOption();
	// ダイアログ情報からCScriptOptionへデータを渡す

	// Position
	CRect winRect;
	GetWindowRect(&winRect);
	
	pOpt->m_dwPos[0] = winRect.left;
	pOpt->m_dwPos[1] = winRect.top;

	pOpt->m_dwChk[0] = m_blCHK1;
	pOpt->m_dwChk[1] = m_blCHK2;
	pOpt->m_dwChk[2] = m_blCHK3;
	pOpt->m_dwChk[3] = m_bDetail;

	pOpt->m_strSuffix = m_strEditSuffix;

	pOpt->m_ltSF.RemoveAll();
	for ( POSITION pos = m_ltScript.GetHeadPosition(); pos; ) {
		pOpt->m_ltSF.AddTail( m_ltScript.GetNext(pos) );
	}

	CDialog::OnDestroy();
}

// 書き込みオッケーメッセージ受信
LRESULT CScriptoriumDlg::StrWriteOK(WPARAM wParam, LPARAM lParam)
{
	UpdateData();

	HANDLE hMap;
	LPSTR  pMap;
	hMap = OpenFileMapping(FILE_MAP_READ, FALSE, "SCRIPTORIUM");
	if(hMap){
		pMap = (LPSTR)::MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);
		if(pMap){
			char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
			// In について
			_splitpath(pMap, chrDrive, chrDir, chrFile, chrExt);
			CString	strFile(chrFile);
			m_strInFileName = pMap;
			// Out について
			m_strOutFileName = lstrcat(chrDrive, lstrcat(chrDir, chrFile)) + m_strEditSuffix + chrExt;
			PathSetDlgItemPath(m_strInFileName, IDC_STATIC_IN, m_strEditIN);
			PathSetDlgItemPath(m_strOutFileName, IDC_STATIC_OUT, m_strEditOUT);

			UnmapViewOfFile(pMap);
		}
		CloseHandle(hMap);
	}

	return 0;
}

// D&D処理
LRESULT CScriptoriumDlg::DragOnControl(WPARAM wParam, LPARAM lParam)
{
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	CString	strFullPath( m_ct_STSF.m_strDragFile );

	// フルパスをファイル名表記に
	switch ( wParam ) {
	case IDC_STATIC_SF:
		m_strScript = strFullPath;
		PathSetDlgItemPath(m_strScript, IDC_STATIC_SF, m_strComboSF);
		break;
	case IDC_STATIC_IN:
		m_strInFileName = m_ct_STIN.m_strDragFile;
		_splitpath(m_strInFileName, chrDrive, chrDir, chrFile, chrExt);
		m_strOutFileName = lstrcat(chrDrive, lstrcat(chrDir, chrFile)) + m_strEditSuffix + chrExt;
		PathSetDlgItemPath(m_strInFileName, IDC_STATIC_IN, m_strEditIN);
		PathSetDlgItemPath(m_strOutFileName, IDC_STATIC_OUT, m_strEditOUT);
		break;
	case IDC_STATIC_OUT:
		m_strOutFileName = m_ct_STOUT.m_strDragFile;
		PathSetDlgItemPath(m_strOutFileName, IDC_STATIC_OUT, m_strEditOUT);
		break;
	default:
		return 0;
	};

	UpdateData(FALSE);
	return 0;
}

// 詳細表示の可否
void CScriptoriumDlg::MoveDlgWindow(const CPoint* lppt)
{
//	CScriptOption*	pOpt = AfxGetScriptoriumApp()->GetScriptOption();
	CPoint	pt;
	int dlgHeight;

	if ( lppt ) {
		pt.x = lppt->x;
		pt.y = lppt->y;
	}
	else {
		CRect winRect;
		GetWindowRect(&winRect);
		pt.x = winRect.left;
		pt.y = winRect.top;
	}

	if(m_bDetail){
		m_btn_option.SetWindowText("設定(&P) >>");
		dlgHeight = 310;
		// ﾀﾌﾞ移動を抑制するために，ｵﾌﾟｼｮﾝｺﾝﾄﾛｰﾙを無効にする
		m_ctCHK1.EnableWindow(FALSE);
		m_ctCHK2.EnableWindow(FALSE);
		m_ctCHK3.EnableWindow(FALSE);
		m_ctSuffix.EnableWindow(FALSE);
	}else{
		m_btn_option.SetWindowText("設定(&P) <<");
		dlgHeight = 476;
		// ﾀﾌﾞ移動を復活するために，ｵﾌﾟｼｮﾝｺﾝﾄﾛｰﾙを有効にする
		m_ctCHK1.EnableWindow(TRUE);
		m_ctCHK2.EnableWindow(TRUE);
		m_ctCHK3.EnableWindow(TRUE);
		m_ctSuffix.EnableWindow(TRUE);
	}

//		CRect winRect;
//		GetWindowRect(&winRect);

	MoveWindow(pt.x, pt.y, 396, dlgHeight, TRUE);
}

void CScriptoriumDlg::PathSetDlgItemPath
	(LPCTSTR lpszFullPath, UINT nID, CString& strEdit)
{
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];

	// Staticｺﾝﾄﾛｰﾙのﾊﾟｽ省略形
	_splitpath(lpszFullPath, chrDrive, chrDir, chrFile, chrExt);
	::PathSetDlgItemPath(m_hWnd, nID, lstrcat(chrDrive, chrDir));
	// Editｺﾝﾄﾛｰﾙ(DDX CString)に対してﾌｧｲﾙ名
	strEdit = lstrcat(chrFile, chrExt);
	
	// Editｺﾝﾄﾛｰﾙに対する更新
	UpdateData(FALSE);
}

void CScriptoriumDlg::AddComboBox(void)
{
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];

	m_cbxComboSF.ResetContent();
	POSITION	addpos;
	for ( POSITION pos = m_ltScript.GetHeadPosition(); pos; ) {
		addpos = pos;
		_splitpath(m_ltScript.GetNext(pos), chrDrive, chrDir, chrFile, chrExt);
		m_cbxComboSF.SetItemDataPtr( m_cbxComboSF.AddString(lstrcat(chrFile, chrExt)), addpos );
	}
	if (!m_ltScript.IsEmpty()){
		m_strScript = m_ltScript.GetHead();
		PathSetDlgItemPath(m_strScript, IDC_STATIC_SF, m_strComboSF);
	}
}

void CScriptoriumDlg::AddScriptHistory(LPCTSTR lpszScript)
{
	POSITION	pos2;
	for ( POSITION pos = m_ltScript.GetHeadPosition(); pos; ) {
		pos2 = pos;
		if ( m_ltScript.GetNext(pos).CompareNoCase(lpszScript) == 0 ) {
			m_ltScript.RemoveAt(pos2);
			m_ltScript.AddHead(lpszScript);
			return;
		}
	}
	// 履歴に見つからなければ履歴に登録(MAX 10個)
	if ( m_ltScript.GetCount() > 9 ) m_ltScript.RemoveTail();
	m_ltScript.AddHead(lpszScript);
}

CString CScriptoriumDlg::GetActiveScript()
{
	// 現在の選択スクリプトを取得して返す
	int	nIndex = m_cbxComboSF.GetCurSel();
	if ( nIndex < 0 )
		return m_ltScript.GetTail();
	POSITION	pos = (POSITION)m_cbxComboSF.GetItemDataPtr(nIndex);
	CString strFullPath( m_ltScript.GetAt(pos) );
	return strFullPath;
}

void CScriptoriumDlg::OnSelchangeScript() 
{
	// コンボボックスから選択したら
	m_strScript = GetActiveScript();
	PathSetDlgItemPath(m_strScript, IDC_STATIC_SF, m_strComboSF);
}

void CScriptoriumDlg::OnKillfocusComboSf() 
{
	// ｺﾝﾎﾞﾎﾞｯｸｽのｴﾃﾞｨｯﾄﾎﾞｯｸｽからﾌｫｰｶｽが外れたら
	UpdateData();
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	_splitpath(m_strComboSF, chrDrive, chrDir, chrFile, chrExt);
	CString strDir(lstrcat(chrDrive, chrDir));
	if ( strDir.IsEmpty() ){	// 入力されたﾌｧｲﾙ名にﾊﾟｽ情報がないとき
		_splitpath(m_strScript, chrDrive, chrDir, chrFile, chrExt);
		m_strScript = lstrcat(chrDrive, chrDir) + m_strComboSF;
	}else{
		m_strScript = m_strComboSF;
	}
	PathSetDlgItemPath(m_strScript, IDC_STATIC_SF, m_strComboSF);
}

void CScriptoriumDlg::OnKillfocusEditIn() 
{
	// 入力ﾌｧｲﾙのｴﾃﾞｨｯﾄﾎﾞｯｸｽからﾌｫｰｶｽが外れたら
	UpdateData();
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	_splitpath(m_strEditIN, chrDrive, chrDir, chrFile, chrExt);
	CString strDir(lstrcat(chrDrive, chrDir));
	if ( strDir.IsEmpty() ){	// 入力されたﾌｧｲﾙ名にﾊﾟｽ情報がないとき
		_splitpath(m_strInFileName, chrDrive, chrDir, chrFile, chrExt);
		m_strInFileName = lstrcat(chrDrive, chrDir) + m_strEditIN;
	}else{
		m_strInFileName = m_strEditIN;
	}
	PathSetDlgItemPath(m_strInFileName, IDC_STATIC_IN, m_strEditIN);
}

void CScriptoriumDlg::OnKillfocusEditOut() 
{
	// 出力ﾌｧｲﾙのｴﾃﾞｨｯﾄﾎﾞｯｸｽからﾌｫｰｶｽが外れたら
	UpdateData();
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	_splitpath(m_strEditOUT, chrDrive, chrDir, chrFile, chrExt);
	CString strDir(lstrcat(chrDrive, chrDir));
	if ( strDir.IsEmpty() ){
		_splitpath(m_strOutFileName, chrDrive, chrDir, chrFile, chrExt);
		m_strOutFileName = lstrcat(chrDrive, chrDir) + m_strEditOUT;
	}else{
		m_strOutFileName = m_strEditOUT;
	}
	PathSetDlgItemPath(m_strOutFileName, IDC_STATIC_OUT, m_strEditOUT);
}

/////////////////////////////////////////////////////////////////////////////
// ｻﾌﾞ関数

CString FileReference(const CString& strInFile, BOOL bRead, UINT nFilterID)
{
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	_splitpath(strInFile, chrDrive, chrDir, chrFile, chrExt);
	CString strFile(lstrcat(chrFile, chrExt)),
			strPath(lstrcat(chrDrive, chrDir)), strResult, strFilter, strAllFilter, strDefFilter;

	strFilter.LoadString(nFilterID);
	strAllFilter.LoadString(IDS_ALL_FILTER);
	int	n = strFilter.Find('\n');
	strDefFilter = strFilter.Left(n);		// '\n' までのﾃﾞﾌｫﾙﾄﾌｨﾙﾀを取得
	strFilter = strFilter.Mid(n+1);			// '\n' 以降のﾀﾞｲｱﾛｸﾞﾌｨﾙﾀを取得

	DWORD	dwFlags = OFN_HIDEREADONLY;
	if ( bRead )
		dwFlags |= OFN_FILEMUSTEXIST;		// ﾌｧｲﾙ存在必須(読み込み時)
//	else
//		dwFlags |= OFN_OVERWRITEPROMPT;		// 保存時の上書き確認

	CFileDialog c(bRead, strDefFilter, strFile, dwFlags, strFilter+strAllFilter);
	c.m_ofn.lpstrInitialDir = strPath;
	
	if(c.DoModal() == IDOK)
		strResult = c.GetPathName();  //ﾌﾙﾊﾟｽGET!

	return strResult;
}
