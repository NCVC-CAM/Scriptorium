// CustomControl.cpp : �C���v�������e�[�V���� �t�@�C��
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
// CCustomStatic ���b�Z�[�W �n���h��

void CCustomStatic::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	if ( ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0) == 1 ) {
		TCHAR szFileName[_MAX_PATH];
		::DragQueryFile(hDropInfo, 0, szFileName, _MAX_PATH);
		m_strDragFile = szFileName;
//		SetSel(0, -1);
//		SetFocus();
		// �h���b�O���ꂽ���Ƃ�e�ɒʒm
		// ���̏ꍇ�C�t���p�X���t�@�C���������̕\���ɂ���
		GetParent()->SendMessage(WM_USER_DRAGCONTROL, (WPARAM)GetDlgCtrlID());
	}
	::DragFinish(hDropInfo);
	
	CStatic::OnDropFiles(hDropInfo);
}
