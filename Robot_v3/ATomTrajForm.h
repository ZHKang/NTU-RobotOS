#pragma once
#include "afxwin.h"


// ATomTrajForm ��ܤ��

class ATomTrajForm : public CDialogEx
{
	DECLARE_DYNAMIC(ATomTrajForm)

public:
	ATomTrajForm(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~ATomTrajForm();

// ��ܤ�����
	enum { IDD = IDD_AtomTrajForm };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAtomtrajgo();
	afx_msg void OnBnClickedAtomset();
	CListBox CListBox_AtomSetPoint;
	afx_msg void OnLbnSelchangeList2();
	CComboBox IDC_AtomTrajSelec;
	afx_msg void OnCbnSelchangeTrajselect();
	CEdit CEdit_AtomSetTime;
	afx_msg void OnEnChangeEdittime();
	afx_msg void OnCbnSelchangeCombo3();
	afx_msg void OnCbnSelendokTrajselect();
	CButton mClearListBoxBtn;
	afx_msg void OnBnClickedClearlistbox();
};
