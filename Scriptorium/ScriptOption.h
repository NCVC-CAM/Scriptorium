// ScriptOption.h: CScriptOption �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPTOPTION_H__CBF574C9_7090_46CF_B58A_32943F437F0C__INCLUDED_)
#define AFX_SCRIPTOPTION_H__CBF574C9_7090_46CF_B58A_32943F437F0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define	SC_WINDOWPOS_LEFT	0
#define	SC_WINDOWPOS_TOP	1

class CScriptOption  
{
	// CScriptoriumApp�CCScriptoriumDlg ���� private���ޕϐ����Q��
	friend	class	CScriptoriumDlg;

	// ��߼�ݒ�`
	CStringList	m_ltSF;			// �����Ďg�p�������X�g
	CString		m_strScript,	// ScriptFile
				m_strSuffix;	// SuffixName
	DWORD		m_dwChk[4];		// 1 or 0 �̃I�v�V����
	// ����ʻ���
	DWORD		m_dwPos[2];		// Left, Top

public:
	CScriptOption();
	virtual ~CScriptOption();

	BOOL	InitInstance(void);

	CString	GetSuffix(void) {
		return m_strSuffix;
	}
};

#endif // !defined(AFX_SCRIPTOPTION_H__CBF574C9_7090_46CF_B58A_32943F437F0C__INCLUDED_)
