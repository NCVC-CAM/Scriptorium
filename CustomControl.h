#if !defined(AFX_CUSTOMCONTROL_H__51D7D85E_FE21_48A6_A16D_F3C454F4B158__INCLUDED_)
#define AFX_CUSTOMCONTROL_H__51D7D85E_FE21_48A6_A16D_F3C454F4B158__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CustomControl.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CCustomStatic �E�B���h�E

class CCustomStatic : public CStatic
{
// �R���X�g���N�V����
public:
	CCustomStatic();

// �A�g���r���[�g
public:
	CString	m_strDragFile;	// �h���b�O���ꂽ�t�@�C����

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CCustomStatic)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CCustomStatic();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CCustomStatic)
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CUSTOMCONTROL_H__51D7D85E_FE21_48A6_A16D_F3C454F4B158__INCLUDED_)
