#ifndef __AtomControl_H_
#define __AtomControl_H_
#pragma once

#include "afxwin.h"
#include <Windows.h>
#
// AtomControl ��ܤ��

class AtomControl : public CDialogEx
{
	DECLARE_DYNAMIC(AtomControl)

public:
	AtomControl(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~AtomControl();

// ��ܤ�����
	enum { IDD = IDD_AtomControl };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedTorquectl();
	afx_msg void OnBnClickedImpedance();
	afx_msg void OnBnClickedButton2();
};

#endif