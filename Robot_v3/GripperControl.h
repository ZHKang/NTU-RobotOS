#pragma once
#include "afxwin.h"


// GripperControl ��ܤ��

class GripperControl : public CDialogEx
{
	DECLARE_DYNAMIC(GripperControl)

public:
	GripperControl(CWnd* pParent = NULL);   // �зǫغc�禡
	virtual ~GripperControl();

// ��ܤ�����
	enum { IDD = IDD_Gripper };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩
	DECLARE_MESSAGE_MAP()
public:
	CButton GripConnect_Btn;
	CButton GripDisconnect_Btn;
	CButton GripCommand_Btn;
	afx_msg void OnBnClickedGripconnect();
	afx_msg void OnBnClickedGripperdisconnect();
	afx_msg void OnBnClickedGripcommand();
};
