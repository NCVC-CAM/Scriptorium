// Scriptorium.cpp : �A�v���P�[�V�����p�N���X�̒�`���s���܂��B
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
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumApp �N���X�̍\�z

CScriptoriumApp::CScriptoriumApp()
{
	// TODO: ���̈ʒu�ɍ\�z�p�̃R�[�h��ǉ����Ă��������B
	// ������ InitInstance ���̏d�v�ȏ��������������ׂċL�q���Ă��������B
}

/////////////////////////////////////////////////////////////////////////////
// �B��� CScriptoriumApp �I�u�W�F�N�g

CScriptoriumApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumApp �N���X�̏�����

BOOL CScriptoriumApp::InitInstance()
{
//	AfxEnableControlContainer();

	// �W���I�ȏ���������
	// ���������̋@�\���g�p�����A���s�t�@�C���̃T�C�Y��������������
	//  ��Έȉ��̓���̏��������[�`���̒�����s�K�v�Ȃ��̂��폜����
	//  ���������B

#ifdef _AFXDLL
	Enable3dControls();			// ���L DLL ���� MFC ���g���ꍇ�͂������R�[�����Ă��������B
#else
	Enable3dControlsStatic();	// MFC �ƐÓI�Ƀ����N����ꍇ�͂������R�[�����Ă��������B
#endif

	//////////////////////////////
	// ��d�N���h�~ �` �����n��
	//////////////////////////////
	HWND   hWnd;
	HANDLE hMap;
	LPSTR  pMap;
	//LPSTR  wBuf;
	if((hWnd = ::FindWindow(NULL, "Scriptorium")))
	{
		//AfxMessageBox("�Q��ڂ̋N��");
		// ��������Ƃ��t�@�C���}�b�s���O
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
	// �I�v�V����������
	////////////////////////////
	if ( !m_opt.InitInstance() )
		return FALSE;

	////////////////////////////
	// �����擾
	////////////////////////////
	if (__argc >= 2) {
		char chrDrv[_MAX_PATH], chrDir[_MAX_PATH], chrFile[_MAX_PATH], chrExt[_MAX_PATH];
		_splitpath(__argv[1], chrDrv, chrDir, chrFile, chrExt);
		CString	strFile(chrFile);
		// In �ɂ���
		m_strInFileName = __argv[1];
		// Out �ɂ���
		m_strOutFileName = lstrcat(chrDrv, lstrcat(chrDir, chrFile)) + m_opt.GetSuffix() + chrExt;
		
	}

	CScriptoriumDlg dlg;
	m_pMainWnd = &dlg;	
	int nResponse = dlg.DoModal();

	// �_�C�A���O�������Ă���A�v���P�[�V�����̃��b�Z�[�W �|���v���J�n������́A
	// �A�v���P�[�V�������I�����邽�߂� FALSE ��Ԃ��Ă��������B
	return FALSE;
}
