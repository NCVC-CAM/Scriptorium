// ScriptOption.cpp: CScriptOption クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Scriptorium.h"
#include "ScriptOption.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CScriptOption::CScriptOption()
{
}

BOOL CScriptOption::InitInstance(void)
{
	int		i = 0;
	CString strEntryOpt;
	CString strEntryPos;
	CString strEntry;
	static	ss_ChkDefault[] = {
		1, 0, 0, 1
	};
	static	ss_PosDefault[] = {
		100, 100
	};
	//////////////////////////
	// レジストリ読み込み
	//////////////////////////
	CRegKey reg;
	if (reg.Create(HKEY_CURRENT_USER, "Software\\MNCT-S\\NCVC\\Scriptorium") != ERROR_SUCCESS)
		return FALSE;

	// Option
	for ( i=0; i<SIZEOF(m_dwChk); i++){
		strEntryOpt.LoadString(i+IDS_REG_OCF);
		if(reg.QueryValue(m_dwChk[i], strEntryOpt) != ERROR_SUCCESS)
			m_dwChk[i] = ss_ChkDefault[i];
	}

	// Position
	DWORD	tmpCK;
	if(reg.QueryValue(tmpCK, "Convert") == ERROR_SUCCESS){
		for ( i=0; i<SIZEOF(m_dwPos); i++ ) {
			strEntryPos.LoadString(i+IDS_REG_POSL);
			if (reg.QueryValue(m_dwPos[i], strEntryPos) != ERROR_SUCCESS)
				m_dwPos[i] = ss_PosDefault[i];
		}
	}else{
		HWND hDeskWnd = ::GetDesktopWindow();
		HDC hDC = ::GetDC(hDeskWnd);
		int pixsx = ::GetDeviceCaps(hDC, LOGPIXELSX);
		::ReleaseDC(hDeskWnd, hDC);
		reg.SetValue(1, "Convert");

		for ( i=0; i<SIZEOF(m_dwPos); i++ ) {
			strEntryPos.LoadString(i+IDS_REG_POSL);
			if (reg.QueryValue( m_dwPos[i], strEntryPos) != ERROR_SUCCESS)
				m_dwPos[i] = ss_PosDefault[i];
			else m_dwPos[i] = m_dwPos[i]*pixsx/1440;
		}

	}

	// ScriptFile
	char chrFull[_MAX_PATH];
	i = 0;
	while ( TRUE ) {
		DWORD aaa = _MAX_PATH;
		strEntry.Format(IDS_REG_SCRIPT, i);
		if(reg.QueryValue(chrFull, strEntry, &aaa) != ERROR_SUCCESS)
			break;
		m_ltSF.AddHead(chrFull);
		i++;
	}

	// SuffixName
	DWORD aaa = _MAX_PATH;
	if(reg.QueryValue(chrFull, "SuffixName", &aaa) == ERROR_SUCCESS)
		m_strSuffix = chrFull;
	else
		m_strSuffix = "_cvted";
	reg.Close();

	return TRUE;
}

CScriptOption::~CScriptOption()
{
/*
	CScriptoriumDlg::OnDestroy() でデータをもらっているので
	ここでレジストリに書き込む
*/
	// ﾚｼﾞｽﾄﾘへｵﾌﾟｼｮﾝ書き込み
	CRegKey reg;
	if (reg.Create(HKEY_CURRENT_USER, "Software\\MNCT-S\\NCVC\\Scriptorium") != ERROR_SUCCESS)
		return;

	int i;
	CString strEntryPos;
	CString strEntryOpt;
	CString	strEntry;

	// Position
	for (i=0; i<SIZEOF(m_dwPos); i++ ) {
		strEntryPos.LoadString(i+IDS_REG_POSL);
		reg.SetValue(m_dwPos[i], strEntryPos);
	}

	// Option
	for (i=0; i<SIZEOF(m_dwChk); i++ ) {
		strEntryOpt.LoadString(i+IDS_REG_OCF);
		reg.SetValue(m_dwChk[i], strEntryOpt);
	}

	// ｽｸﾘﾌﾟﾄﾌｧｲﾙ履歴
	// １回全消ししといて
	for ( i=0; i<=10; i++ ){
		strEntry.Format(IDS_REG_SCRIPT, i);
		if ( reg.DeleteValue(strEntry) != ERROR_SUCCESS )
			break;
	}
	//　んで書き込み
	int k=0;
	for ( POSITION pos = m_ltSF.GetHeadPosition(); pos; k++ ) {
		strEntry.Format(IDS_REG_SCRIPT, k);
		reg.SetValue(m_ltSF.GetNext(pos), strEntry);
	}

	// ｻﾌｨｯｸｽ
	reg.SetValue(m_strSuffix, "SuffixName");
}
