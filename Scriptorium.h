// Scriptorium.h : SCRIPTORIUM �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_SCRIPTORIUM_H__7C17CB9F_3D62_461B_9B77_8676C312B2BB__INCLUDED_)
#define AFX_SCRIPTORIUM_H__7C17CB9F_3D62_461B_9B77_8676C312B2BB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��
#include "ScriptOption.h"

/////////////////////////////////////////////////////////////////////////////
// CScriptoriumApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� Scriptorium.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CScriptoriumApp : public CWinApp
{
	CScriptOption	m_opt;		// Scriptorium��߼��

public:
	CScriptoriumApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CScriptoriumApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
	CScriptOption*	GetScriptOption(void) {
		return &m_opt;
	}

	// �������
	CString	m_strInFileName;
	CString	m_strOutFileName;

	//{{AFX_MSG(CScriptoriumApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SCRIPTORIUM_H__7C17CB9F_3D62_461B_9B77_8676C312B2BB__INCLUDED_)
