// AtomControl.cpp : ��@��
//

#include "stdafx.h"
#include "Robot_v3.h"
#include "AtomControl.h"
#include "afxdialogex.h"
///////////////////////////////
#include "ProjectPlay.h"

//#include "global_value.h"
//#include "ProjectPlay.h"


// AtomControl ��ܤ��

IMPLEMENT_DYNAMIC(AtomControl, CDialogEx)

AtomControl::AtomControl(CWnd* pParent /*=NULL*/)
	: CDialogEx(AtomControl::IDD, pParent)
{

}

AtomControl::~AtomControl()
{
}

void AtomControl::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(AtomControl, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &AtomControl::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_TorqueCtl, &AtomControl::OnBnClickedTorquectl)
	ON_BN_CLICKED(IDC_Impedance, &AtomControl::OnBnClickedImpedance)
	ON_BN_CLICKED(IDC_BUTTON2, &AtomControl::OnBnClickedButton2)
END_MESSAGE_MAP()


// AtomControl �T���B�z�`��


void AtomControl::OnBnClickedButton1()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	ProjectPlay mProject;
	mProject.Atom_dynamics_Test();
}




void AtomControl::OnBnClickedTorquectl()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	ProjectPlay mProjectPlay;
	mProjectPlay.Atom_torqueCtl();
}


void AtomControl::OnBnClickedImpedance()
{
	// TODO: �b���[�J����i���B�z�`���{���X
}


void AtomControl::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	ProjectPlay mProjectPlay;
	mProjectPlay.Project_test();
}
