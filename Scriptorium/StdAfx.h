// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���A
//            �܂��͎Q�Ɖ񐔂������A�����܂�ύX����Ȃ�
//            �v���W�F�N�g��p�̃C���N���[�h �t�@�C�����L�q���܂��B
//

#if !defined(AFX_STDAFX_H__6E34BA2A_E0A4_4BCC_BA39_11D110CF23A9__INCLUDED_)
#define AFX_STDAFX_H__6E34BA2A_E0A4_4BCC_BA39_11D110CF23A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Windows �w�b�_�[����w�ǎg�p����Ȃ��X�^�b�t�����O���܂��B

#include <afxwin.h>         // MFC �̃R�A����ѕW���R���|�[�l���g
#include <afxext.h>         // MFC �̊g������
#include <afxdisp.h>        // MFC �̃I�[�g���[�V���� �N���X
#include <afxdtctl.h>		// MFC �� Internet Explorer 4 �R���� �R���g���[�� �T�|�[�g
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC �� Windows �R���� �R���g���[�� �T�|�[�g
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "atlbase.h"
#include "shlwapi.h"

#define	AfxGetScriptoriumApp()	((CScriptoriumApp *)AfxGetApp())
#define	SIZEOF(a)	( sizeof(a)/sizeof(a[0]) )

// User Message
#define WM_USER_WRITE		WM_USER + 100
#define	WM_USER_DRAGCONTROL	WM_USER + 101	// WPARAM -> nID

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_STDAFX_H__6E34BA2A_E0A4_4BCC_BA39_11D110CF23A9__INCLUDED_)
