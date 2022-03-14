// ScriptoriumDlg.cpp : �C���v�������e�[�V���� �t�@�C��
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

// ̧�َQ��
static	CString	FileReference(const CString& strFile, BOOL bRead, UINT nFilterID);

/////////////////////////////////////////////////////////////////////////////
// �A�v���P�[�V�����̃o�[�W�������Ŏg���Ă��� CAboutDlg �_�C�A���O

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂�
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
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
		// ���b�Z�[�W �n���h��������܂���B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumDlg �_�C�A���O

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
	// InitInstance()�ł�������l�̏���
	/////////////////////////
	CScriptoriumApp*	pApp = AfxGetScriptoriumApp();
	CScriptOption*		pOpt = pApp->GetScriptOption();	
	m_blCHK1 = pOpt->m_dwChk[0];
	m_blCHK2 = pOpt->m_dwChk[1];
	m_blCHK3 = pOpt->m_dwChk[2];
	m_strEditSuffix = pOpt->m_strSuffix;

	for ( POSITION pos = pOpt->m_ltSF.GetHeadPosition(); pos; ) {
		CString strTmp = pOpt->m_ltSF.GetNext(pos);
		if ( ::GetFileAttributes(strTmp) != 0xFFFFFFFF) // ���݂���̧�ق̂݃��X�g�ɂق肱��ł���
			m_ltScript.AddHead( strTmp );
	}
	
	m_strInFileName = pApp->m_strInFileName;
	m_strOutFileName = pApp->m_strOutFileName;
	m_bDetail = pOpt->m_dwChk[3];	// �ݒ�{�^�����

	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
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

	// �������݃I�b�P�[���b�Z�[�W
    ON_MESSAGE(WM_USER_WRITE, StrWriteOK)
	// �h���b�O���ꂽ
	ON_MESSAGE(WM_USER_DRAGCONTROL, DragOnControl)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumDlg ���b�Z�[�W �n���h��

BOOL CScriptoriumDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���ڂ��V�X�e�� ���j���[�֒ǉ����܂��B

	// IDM_ABOUTBOX �̓R�}���h ���j���[�͈̔͂łȂ���΂Ȃ�܂���B
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

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B

	// D&D����
	m_ct_STSF.DragAcceptFiles();
	m_ct_STIN.DragAcceptFiles();
	m_ct_STOUT.DragAcceptFiles();

	// �E�B���h�E�̕\����Ԃ𕜌�
	CScriptOption*		pOpt = AfxGetScriptoriumApp()->GetScriptOption();
	CPoint	pt(pOpt->m_dwPos[0], pOpt->m_dwPos[1]);
	MoveDlgWindow( &pt );

	// ���W�X�g�����瓾�� ScriptFile ��\��
	AddComboBox();

	// �������瓾�� InFile�COutFile ��\��
	PathSetDlgItemPath(m_strInFileName, IDC_STATIC_IN, m_strEditIN);
	PathSetDlgItemPath(m_strOutFileName, IDC_STATIC_OUT, m_strEditOUT);

	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
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

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CScriptoriumDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
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
	// ���݂̑I���X�N���v�g���擾
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
		m_strScript = strResult;	// ���߽GET!

		PathSetDlgItemPath(m_strScript, IDC_STATIC_SF, m_strComboSF);
	}
}

void CScriptoriumDlg::OnButtonRefin() 
{
	UpdateData();

	// InFile �ɂ���
	CString	strResult( FileReference(m_strInFileName, TRUE, IDS_NCD_FILTER) );
	if ( strResult.IsEmpty() )
		return;
	m_strInFileName = strResult;
	PathSetDlgItemPath(m_strInFileName, IDC_STATIC_IN, m_strEditIN);

	// OutFile �ɂ���
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	_splitpath_s(m_strInFileName, chrDrive, chrDir, chrFile, chrExt);

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

	
	// ������̧�� �`�F�b�N
	if( m_strScript.IsEmpty() ){
		AfxMessageBox("������̧�� ����͂��Ă��������B");
		m_cbxComboSF.SetFocus();
	}
	else if ( m_strComboSF.IsEmpty() ){
		AfxMessageBox("������̧�� ����͂��Ă��������B");
		m_cbxComboSF.SetFocus();
	}
	else if ( ::GetFileAttributes(m_strScript) == 0xFFFFFFFF ){
		AfxMessageBox( m_strScript + " �͑��݂��܂���B");
		m_cbxComboSF.SetFocus();
		m_cbxComboSF.SetEditSel(0,-1);
	}
	else if ( ::GetFileAttributes(m_strScript) & dwNGFlag ){
		AfxMessageBox( m_strScript + " �͕s���ȃt�@�C���ł��B");
		m_cbxComboSF.SetFocus();
		m_cbxComboSF.SetEditSel(0,-1);
	}

	// ����̧�� �`�F�b�N
	else if ( m_strInFileName.IsEmpty() ){
		AfxMessageBox("����̧�� ����͂��Ă��������B");
		m_ctEditIN.SetFocus();
	}
	else if ( m_strEditIN.IsEmpty() ){
		AfxMessageBox("����̧�� ����͂��Ă��������B");
		m_ctEditIN.SetFocus();
	}
	else if ( ::GetFileAttributes(m_strInFileName) == 0xFFFFFFFF ){
		AfxMessageBox( m_strInFileName + " �͑��݂��܂���B");
		m_ctEditIN.SetFocus();
		m_ctEditIN.SetSel(0,-1);
	}
	else if ( ::GetFileAttributes(m_strInFileName) & dwNGFlag ){
		AfxMessageBox( m_strInFileName + " �͕s���ȃt�@�C���ł��B");
		m_ctEditIN.SetFocus();
		m_ctEditIN.SetSel(0,-1);
	}

	// �o��̧�� �`�F�b�N
	else if ( m_strOutFileName.IsEmpty() ){
		AfxMessageBox("�o��̧�� ����͂��Ă��������B");
		m_ctEditOUT.SetFocus();
	}
	else if ( m_strEditOUT.IsEmpty() ){
		AfxMessageBox("�o��̧�� ����͂��Ă��������B");
		m_ctEditOUT.SetFocus();
	}
	
	else {
		
		dwAttri = ::GetFileAttributes(m_strOutFileName);
		if ( dwAttri != 0xFFFFFFFF ) {
			// �t�@�C��������Ƃ�
			if ( dwAttri & (dwNGFlag|FILE_ATTRIBUTE_READONLY) ){
				AfxMessageBox( m_strOutFileName + " �͕s���ȃt�@�C���ł��B");
				m_ctEditOUT.SetFocus();
				m_ctEditOUT.SetSel(0,-1);
				return;
			}
			
			else if (AfxMessageBox(m_strOutFileName + " �͊��ɑ��݂��܂��B\n�㏑�����܂���?", MB_YESNO|MB_DEFBUTTON2) == IDNO){
				m_ctEditOUT.SetFocus();
				m_ctEditOUT.SetSel(0,-1);
				return;
			}
			}
		else {
			// �������݌����̃t�H���_���`�F�b�N
			HANDLE hFile = CreateFile(m_strOutFileName, GENERIC_READ | GENERIC_WRITE, NULL, NULL,
				CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
			
			// �o�̓t�@�C�����������݌����̃t�H���_�����`�F�b�N GetLastError() == 5:�A�N�Z�X����
			if (hFile == INVALID_HANDLE_VALUE && GetLastError() == 5) {

				//�������݌����`�F�b�N�I��
				CloseHandle(hFile);
				AfxMessageBox("�o��̧�ق͏������݌����\�ȃt�H���_��I�����ĉ������B");
				m_ctEditOUT.SetFocus();
				return;
			}

			//�`�F�b�N�p�t�@�C���폜
			DeleteFile(m_strOutFileName);

			//�������݌����`�F�b�N�I��
			CloseHandle(hFile);
		}


		CString tmpStr;
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory( &si, sizeof(si) );						// �w�肳�ꂽ�̈��0�Ŗ��߂�
		si.cb = sizeof( si );								// �����̗̈���i�[���郁���o�ɓ����
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;

		//�X�N���v�g�g���q Python or Perl����
		char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
		_splitpath_s(m_strScript, chrDrive, chrDir, chrFile, chrExt);

		CString strEXE;										//���ʊg���q�i�[
		//Python�̏ꍇ
		if (_stricmp(chrExt, ".py") == 0) {
			strEXE = "python";
		}
		//Perl�̏ꍇ
		else if (_stricmp(chrExt, ".pl") == 0) {
			strEXE = "perl";
		}
		//�ǂ���ł������ꍇ
		if(strEXE.IsEmpty()) {
			AfxMessageBox("�X�N���v�g�t�@�C����Perl��Python�`����I�����ĉ������B");
		}
		else {
			tmpStr = strEXE +" \"" + m_strScript + "\" \"" + m_strInFileName + "\" \"" + m_strOutFileName + "\"";
			if (CreateProcess(NULL, (LPSTR)(LPCTSTR)tmpStr, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi) != 0) {
				CloseHandle(pi.hThread);						// �X���b�h�̃n���h���͎g��Ȃ��̂ł����j��
				WaitForSingleObject(pi.hProcess, INFINITE);	// �v���Z�X���I������܂ł܂�
				CloseHandle(pi.hProcess);						// �����v���Z�X�̃n���h���͎g��Ȃ��̂Ŕj��
			}
		}
		
/*		
		// �f�o�b�O�p
		CString tmpStr = "perl \"" + m_strScript + "\" \"" + m_strInFileName + "\" \"" + m_strOutFileName + "\"";
		AfxMessageBox(tmpStr);
*/		
		if(m_blCHK3) AfxMessageBox("�������܂����B", MB_ICONINFORMATION);
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
	// �_�C�A���O��񂩂�CScriptOption�փf�[�^��n��

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

// �������݃I�b�P�[���b�Z�[�W��M
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
			// In �ɂ���
			_splitpath_s(pMap, chrDrive, chrDir, chrFile, chrExt);
			CString	strFile(chrFile);
			m_strInFileName = pMap;
			// Out �ɂ���
			m_strOutFileName = lstrcat(chrDrive, lstrcat(chrDir, chrFile)) + m_strEditSuffix + chrExt;
			PathSetDlgItemPath(m_strInFileName, IDC_STATIC_IN, m_strEditIN);
			PathSetDlgItemPath(m_strOutFileName, IDC_STATIC_OUT, m_strEditOUT);

			UnmapViewOfFile(pMap);
		}
		CloseHandle(hMap);
	}

	return 0;
}

// D&D����
LRESULT CScriptoriumDlg::DragOnControl(WPARAM wParam, LPARAM lParam)
{
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	CString	strFullPath( m_ct_STSF.m_strDragFile );

	// �t���p�X���t�@�C�����\�L��
	switch ( wParam ) {
	case IDC_STATIC_SF:
		m_strScript = strFullPath;
		PathSetDlgItemPath(m_strScript, IDC_STATIC_SF, m_strComboSF);
		break;
	case IDC_STATIC_IN:
		m_strInFileName = m_ct_STIN.m_strDragFile;
		_splitpath_s(m_strInFileName, chrDrive, chrDir, chrFile, chrExt);
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

// �ڍו\���̉�
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
		m_btn_option.SetWindowText("�ݒ�(&P) >>");
		dlgHeight = 310;
		// ��ވړ���}�����邽�߂ɁC��߼�ݺ��۰ق𖳌��ɂ���
		m_ctCHK1.EnableWindow(FALSE);
		m_ctCHK2.EnableWindow(FALSE);
		m_ctCHK3.EnableWindow(FALSE);
		m_ctSuffix.EnableWindow(FALSE);
	}else{
		m_btn_option.SetWindowText("�ݒ�(&P) <<");
		dlgHeight = 476;
		// ��ވړ��𕜊����邽�߂ɁC��߼�ݺ��۰ق�L���ɂ���
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

	// Static���۰ق��߽�ȗ��`
	_splitpath_s(lpszFullPath, chrDrive, chrDir, chrFile, chrExt);
	::PathSetDlgItemPath(m_hWnd, nID, lstrcat(chrDrive, chrDir));
	// Edit���۰�(DDX CString)�ɑ΂���̧�ٖ�
	strEdit = lstrcat(chrFile, chrExt);
	
	// Edit���۰قɑ΂���X�V
	UpdateData(FALSE);
}

void CScriptoriumDlg::AddComboBox(void)
{
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];

	m_cbxComboSF.ResetContent();
	POSITION	addpos;
	for ( POSITION pos = m_ltScript.GetHeadPosition(); pos; ) {
		addpos = pos;
		_splitpath_s(m_ltScript.GetNext(pos), chrDrive, chrDir, chrFile, chrExt);
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
	// �����Ɍ�����Ȃ���Η����ɓo�^(MAX 10��)
	if ( m_ltScript.GetCount() > 9 ) m_ltScript.RemoveTail();
	m_ltScript.AddHead(lpszScript);
}

CString CScriptoriumDlg::GetActiveScript()
{
	// ���݂̑I���X�N���v�g���擾���ĕԂ�
	int	nIndex = m_cbxComboSF.GetCurSel();
	if ( nIndex < 0 )
		return m_ltScript.GetTail();
	POSITION	pos = (POSITION)m_cbxComboSF.GetItemDataPtr(nIndex);
	CString strFullPath( m_ltScript.GetAt(pos) );
	return strFullPath;
}

void CScriptoriumDlg::OnSelchangeScript() 
{
	// �R���{�{�b�N�X����I��������
	m_strScript = GetActiveScript();
	PathSetDlgItemPath(m_strScript, IDC_STATIC_SF, m_strComboSF);
}

void CScriptoriumDlg::OnKillfocusComboSf() 
{
	// �����ޯ���̴�ި���ޯ������̫������O�ꂽ��
	UpdateData();
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	_splitpath_s(m_strComboSF, chrDrive, chrDir, chrFile, chrExt);
	CString strDir(lstrcat(chrDrive, chrDir));
	if ( strDir.IsEmpty() ){	// ���͂��ꂽ̧�ٖ����߽��񂪂Ȃ��Ƃ�
		_splitpath_s(m_strScript, chrDrive, chrDir, chrFile, chrExt);
		m_strScript = lstrcat(chrDrive, chrDir) + m_strComboSF;
	}else{
		m_strScript = m_strComboSF;
	}
	PathSetDlgItemPath(m_strScript, IDC_STATIC_SF, m_strComboSF);
}

void CScriptoriumDlg::OnKillfocusEditIn() 
{
	// ����̧�ق̴�ި���ޯ������̫������O�ꂽ��
	UpdateData();
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	_splitpath_s(m_strEditIN, chrDrive, chrDir, chrFile, chrExt);
	CString strDir(lstrcat(chrDrive, chrDir));
	if ( strDir.IsEmpty() ){	// ���͂��ꂽ̧�ٖ����߽��񂪂Ȃ��Ƃ�
		_splitpath_s(m_strInFileName, chrDrive, chrDir, chrFile, chrExt);
		m_strInFileName = lstrcat(chrDrive, chrDir) + m_strEditIN;
	}else{
		m_strInFileName = m_strEditIN;
	}
	PathSetDlgItemPath(m_strInFileName, IDC_STATIC_IN, m_strEditIN);
}

void CScriptoriumDlg::OnKillfocusEditOut() 
{
	// �o��̧�ق̴�ި���ޯ������̫������O�ꂽ��
	UpdateData();
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	_splitpath_s(m_strEditOUT, chrDrive, chrDir, chrFile, chrExt);
	CString strDir(lstrcat(chrDrive, chrDir));
	if ( strDir.IsEmpty() ){
		_splitpath_s(m_strOutFileName, chrDrive, chrDir, chrFile, chrExt);
		m_strOutFileName = lstrcat(chrDrive, chrDir) + m_strEditOUT;
	}else{
		m_strOutFileName = m_strEditOUT;
	}
	PathSetDlgItemPath(m_strOutFileName, IDC_STATIC_OUT, m_strEditOUT);
}

/////////////////////////////////////////////////////////////////////////////
// ��ފ֐�

CString FileReference(const CString& strInFile, BOOL bRead, UINT nFilterID)
{
	char chrDrive[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
	_splitpath_s(strInFile, chrDrive, chrDir, chrFile, chrExt);
	CString strFile(lstrcat(chrFile, chrExt)),
			strPath(lstrcat(chrDrive, chrDir)), strResult, strFilter, strAllFilter, strDefFilter;

	strFilter.LoadString(nFilterID);
	strAllFilter.LoadString(IDS_ALL_FILTER);
	int	n = strFilter.Find('\n');
	strDefFilter = strFilter.Left(n);		// '\n' �܂ł���̫��̨�����擾
	strFilter = strFilter.Mid(n+1);			// '\n' �ȍ~���޲�۸�̨�����擾

	DWORD	dwFlags = OFN_HIDEREADONLY;
	if ( bRead )
		dwFlags |= OFN_FILEMUSTEXIST;		// ̧�ّ��ݕK�{(�ǂݍ��ݎ�)
//	else
//		dwFlags |= OFN_OVERWRITEPROMPT;		// �ۑ����̏㏑���m�F

	CFileDialog c(bRead, strDefFilter, strFile, dwFlags, strFilter+strAllFilter);
	c.m_ofn.lpstrInitialDir = strPath;
	
	if(c.DoModal() == IDOK)
		strResult = c.GetPathName();  //���߽GET!

	return strResult;
}
