// AtomJointCtL.cpp : ��@��
//

#include "stdafx.h"
#include "Robot_v3.h"
#include "AtomJointCtL.h"
#include "afxdialogex.h"


// include Main Dlg
#include "global_value.h"
#include "ProjectPlay.h"
#include <string>

using namespace std;
float AtomJointCtL::Atom_thetaALL[6] = {0.0};
float AtomJointCtL::Atom_CarAll[6] = {0.0};
// AtomJointCtL ��ܤ��
IMPLEMENT_DYNAMIC(AtomJointCtL, CDialogEx)

AtomJointCtL::AtomJointCtL(CWnd* pParent /*=NULL*/)
	: CDialogEx(AtomJointCtL::IDD, pParent)
{
}

AtomJointCtL::~AtomJointCtL()
{
}

void AtomJointCtL::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, CEdit_theta1);
	DDX_Control(pDX, IDC_EDIT2, CEdit_theta2);
	DDX_Control(pDX, IDC_EDIT3, CEdit_theta3);
	DDX_Control(pDX, IDC_EDIT4, CEdit_theta4);
	DDX_Control(pDX, IDC_EDIT5, CEdit_theta5);
	DDX_Control(pDX, IDC_EDIT6, CEdit_theta6);
	DDX_Control(pDX, IDC_EDIT7, CEdit_x);
	DDX_Control(pDX, IDC_EDIT8, CEdit_y);
	DDX_Control(pDX, IDC_EDIT9, CEdit_z);
	DDX_Control(pDX, IDC_EDIT10, CEdit_rx);
	DDX_Control(pDX, IDC_EDIT11, CEdit_ry);
	DDX_Control(pDX, IDC_EDIT12, CEdit_rz);
	DDX_Control(pDX, IDC_AtomConnect, ControllerConnect);
	DDX_Control(pDX, IDC_AtomDisconnect, ControllerDisconnect);
	DDX_Control(pDX, IDC_AtomReset, AtomRestBtn);
	AtomControlInit();
}


BEGIN_MESSAGE_MAP(AtomJointCtL, CDialogEx)
	ON_BN_CLICKED(IDC_J1n, &AtomJointCtL::OnBnClickedJ1n)
	ON_BN_CLICKED(IDC_J1n2, &AtomJointCtL::OnBnClickedJ1n2)
	ON_BN_CLICKED(IDC_J1n3, &AtomJointCtL::OnBnClickedJ1n3)
	ON_BN_CLICKED(IDC_J1n4, &AtomJointCtL::OnBnClickedJ1n4)
	ON_BN_CLICKED(IDC_J1n5, &AtomJointCtL::OnBnClickedJ1n5)
	ON_BN_CLICKED(IDC_J1n6, &AtomJointCtL::OnBnClickedJ1n6)
	ON_BN_CLICKED(IDC_J1n7, &AtomJointCtL::OnBnClickedJ1n7)
	ON_BN_CLICKED(IDC_J1n8, &AtomJointCtL::OnBnClickedJ1n8)
	ON_BN_CLICKED(IDC_J1n9, &AtomJointCtL::OnBnClickedJ1n9)
	ON_BN_CLICKED(IDC_J1n10, &AtomJointCtL::OnBnClickedJ1n10)
	ON_BN_CLICKED(IDC_J1n11, &AtomJointCtL::OnBnClickedJ1n11)
	ON_BN_CLICKED(IDC_J1n12, &AtomJointCtL::OnBnClickedJ1n12)
	ON_EN_CHANGE(IDC_EDIT1, &AtomJointCtL::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &AtomJointCtL::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &AtomJointCtL::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &AtomJointCtL::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &AtomJointCtL::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &AtomJointCtL::OnEnChangeEdit6)
	ON_BN_CLICKED(IDC_xp, &AtomJointCtL::OnBnClickedxp)
	ON_EN_CHANGE(IDC_EDIT7, &AtomJointCtL::OnEnChangeEdit7)
	ON_BN_CLICKED(IDC_xn, &AtomJointCtL::OnBnClickedxn)
	ON_BN_CLICKED(IDC_yp, &AtomJointCtL::OnBnClickedyp)
	ON_BN_CLICKED(IDC_yn, &AtomJointCtL::OnBnClickedyn)
	ON_BN_CLICKED(IDC_zp, &AtomJointCtL::OnBnClickedzp)
	ON_BN_CLICKED(IDC_zn, &AtomJointCtL::OnBnClickedzn)
	ON_EN_CHANGE(IDC_EDIT8, &AtomJointCtL::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, &AtomJointCtL::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, &AtomJointCtL::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, &AtomJointCtL::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, &AtomJointCtL::OnEnChangeEdit12)
	ON_BN_CLICKED(IDC_rxp, &AtomJointCtL::OnBnClickedrxp)
	ON_BN_CLICKED(IDC_rxn, &AtomJointCtL::OnBnClickedrxn)
	ON_BN_CLICKED(IDC_ryp, &AtomJointCtL::OnBnClickedryp)
	ON_BN_CLICKED(IDC_ryn, &AtomJointCtL::OnBnClickedryn)
	ON_BN_CLICKED(IDC_rzp, &AtomJointCtL::OnBnClickedrzp)
	ON_BN_CLICKED(IDC_rzn, &AtomJointCtL::OnBnClickedrzn)
	ON_BN_CLICKED(IDC_ArrFw, &AtomJointCtL::OnBnClickedArrfw)
	ON_BN_CLICKED(IDC_AtomConnect, &AtomJointCtL::OnBnClickedAtomconnect)
	ON_BN_CLICKED(IDC_AtomDisconnect, &AtomJointCtL::OnBnClickedAtomdisconnect)
	ON_BN_CLICKED(IDC_AtomSave, &AtomJointCtL::OnBnClickedAtomsave)
	ON_BN_CLICKED(IDC_AtomLoad, &AtomJointCtL::OnBnClickedAtomload)
	ON_BN_CLICKED(IDC_AtomReset, &AtomJointCtL::OnBnClickedAtomreset)
END_MESSAGE_MAP()


// AtomJointCtL �T���B�z�`��
void AtomJointCtL::AtomControlInit()
{
	// initial theta 1~6  Edit control text
	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}

	// initial Cartesian Edit control text
	Matrix R0;
	ColumnVector P0, Rxyz0;
	robot_atom.kine(R0,P0);
	Rxyz0 = irpy(R0)*180/M_PI;

	//  �s�iglobal vector ���t�@��dialog��
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = P0(1);
	Atom_CarAll[1] = P0(2);
	Atom_CarAll[2] = P0(3);
	Atom_CarAll[3] = Rxyz0(1);
	Atom_CarAll[4] = Rxyz0(2);
	Atom_CarAll[5] = Rxyz0(3);

	///////////  �q�bcedit box�W
	CString str;
	str.Format("%.1f",theta[0]);
	CEdit_theta1.SetWindowTextA(str);
	str.Format("%.1f",theta[1]);
	CEdit_theta2.SetWindowTextA(str);
	str.Format("%.1f",theta[2]);
	CEdit_theta3.SetWindowTextA(str);
	str.Format("%.1f",theta[3]);
	CEdit_theta4.SetWindowTextA(str);
	str.Format("%.1f",theta[4]);
	CEdit_theta5.SetWindowTextA(str);
	str.Format("%.1f",theta[5]);
	CEdit_theta6.SetWindowTextA(str);

	str.Format("%.4f",(float)P0(1));
	CEdit_x.SetWindowTextA(str);
	str.Format("%.4f",(float)P0(2));
	CEdit_y.SetWindowTextA(str);
	str.Format("%.4f",(float)P0(3));
	CEdit_z.SetWindowTextA(str);
	str.Format("%.4f",(float)Rxyz0(1));
	CEdit_rx.SetWindowTextA(str);
	str.Format("%.4f",(float)Rxyz0(2));
	CEdit_ry.SetWindowTextA(str);
	str.Format("%.4f",(float)Rxyz0(3));
	CEdit_rz.SetWindowTextA(str);
}

void AtomJointCtL::OnBnClickedJ1n()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 1;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	CString str;
	str.Format("%.1f",theta[0]);
	CEdit_theta1.SetWindowTextA(str);


	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedJ1n2()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 2;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	CString str;
	str.Format("%.1f",theta[0]);
	CEdit_theta1.SetWindowTextA(str);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedJ1n3()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 3;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);
	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (float)(robot_atom.get_q(i+1))*180/M_PI;
	}
	CString str;
	str.Format("%.1f",theta[1]);
	CEdit_theta1.SetWindowTextA(str);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedJ1n4()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 4;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);
	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	CString str;
	str.Format("%.1f",theta[1]);
	CEdit_theta1.SetWindowTextA(str);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedJ1n5()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 5;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);
	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
		CString str;
	str.Format("%.1f",theta[2]);
	CEdit_theta1.SetWindowTextA(str);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedJ1n6()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 6;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);
	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	CString str;
	str.Format("%.1f",theta[2]);
	CEdit_theta6.SetWindowTextA(str);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedJ1n7()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 7;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);
	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	CString str;

	str.Format("%.1f",theta[3]);
	CEdit_theta6.SetWindowTextA(str);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedJ1n8()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 8;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);
	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	CString str;
	str.Format("%.1f",theta[3]);
	CEdit_theta4.SetWindowTextA(str);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedJ1n9()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 9;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);
	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	CString str;
	str.Format("%.1f",theta[4]);
	CEdit_theta5.SetWindowTextA(str);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedJ1n10()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 10;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);
	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (float)(robot_atom.get_q(i+1))*180/M_PI;
	}
	CString str;
	str.Format("%.1f",theta[4]);
	CEdit_theta5.SetWindowTextA(str);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedJ1n11()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 11;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);
	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	CString str;
	str.Format("%.1f",theta[5]);
	CEdit_theta6.SetWindowTextA(str);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedJ1n12()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 12;
	ProjectPlay mProject;
	mProject.project_AtomStep(num);
	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	CString str;
	str.Format("%.1f",theta[5]);
	CEdit_theta6.SetWindowTextA(str);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}



void AtomJointCtL::OnEnChangeEdit1()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}


void AtomJointCtL::OnEnChangeEdit2()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}


void AtomJointCtL::OnEnChangeEdit3()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}

void AtomJointCtL::OnEnChangeEdit4()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}


void AtomJointCtL::OnEnChangeEdit5()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}


void AtomJointCtL::OnEnChangeEdit6()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}


void AtomJointCtL::OnBnClickedxp()
{
	// TODO: �b���[�J����i���B�z�`���{���X	
	int num = 1;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn,Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	str.Format("%.4f",Pn(1));
	CEdit_x.SetWindowTextA(str);

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);

}


void AtomJointCtL::OnEnChangeEdit7()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}


void AtomJointCtL::OnBnClickedxn()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 2;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn,Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	str.Format("%.4f",Pn(1));
	CEdit_x.SetWindowTextA(str);

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedyp()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 3;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn,Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	str.Format("%.4f",Pn(2));
	CEdit_y.SetWindowTextA(str);

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedyn()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 4;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn,Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	str.Format("%.4f",Pn(2));
	CEdit_y.SetWindowTextA(str);

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedzp()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 5;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn,Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	str.Format("%.4f",Pn(3));
	CEdit_z.SetWindowTextA(str);

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedzn()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 6;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn,Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	str.Format("%.4f",Pn(3));
	CEdit_z.SetWindowTextA(str);

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnEnChangeEdit8()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}


void AtomJointCtL::OnEnChangeEdit9()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}


void AtomJointCtL::OnEnChangeEdit10()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}


void AtomJointCtL::OnEnChangeEdit11()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}


void AtomJointCtL::OnEnChangeEdit12()
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	UpdateData(TRUE);
}


void AtomJointCtL::OnBnClickedrxp()
{
	// TODO: �b���[�J����i���B�z�`���{���X

	int num = 7;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn, Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	CEdit_rx.SetWindowTextA(str);
	str.Format("%.4f",(float)Rxyz(1));

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedrxn()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 8;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn,Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	CEdit_rx.SetWindowTextA(str);
	str.Format("%.4f",(float)Rxyz(1));

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedryp()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 9;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn,Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	CEdit_ry.SetWindowTextA(str);
	str.Format("%.4f",(float)Rxyz(1));

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedryn()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 10;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn,Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	CEdit_ry.SetWindowTextA(str);
	str.Format("%.4f",(float)Rxyz(1));

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedrzp()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 11;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn,Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	CEdit_rz.SetWindowTextA(str);
	str.Format("%.4f",(float)Rxyz(1));

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedrzn()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int num = 12;
	ProjectPlay mProjectPlay;
	mProjectPlay.project_AtomCartStep(num);

	Matrix Rn; ColumnVector Pn,Rxyz;
	robot_atom.kine(Rn,Pn);
	Rxyz = irpy(Rn)*180/M_PI;
	CString str;
	CEdit_rz.SetWindowTextA(str);
	str.Format("%.4f",(float)Rxyz(1));

	float *theta = NULL;
	theta = new float [gAtom_DOF];
	for (int i=0;i<gAtom_DOF;i++){
		theta[i] = (robot_atom.get_q(i+1))*180/M_PI;
	}
	for (int i=0;i<6;i++)
	{
		Atom_thetaALL[i] = theta[i]*M_PI/180;
	}
	Atom_CarAll[0] = Pn(1);
	Atom_CarAll[1] = Pn(2);
	Atom_CarAll[2] = Pn(3);
	Atom_CarAll[3] = Rxyz(1);
	Atom_CarAll[4] = Rxyz(2);
	Atom_CarAll[5] = Rxyz(3);
}


void AtomJointCtL::OnBnClickedArrfw()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	ProjectPlay mProjectPlay;
}


void AtomJointCtL::OnBnClickedAtomconnect()
{
	// TODO: �b���[�J����i���B�z�`���{���X

	ControllerDisconnect.EnableWindow(true);
	ControllerConnect.EnableWindow(false);

	ProjectPlay mProjectPlay;
	mProjectPlay.ControllerConnect();

}


void AtomJointCtL::OnBnClickedAtomdisconnect()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	ControllerConnect.EnableWindow(true);
	ControllerDisconnect.EnableWindow(false);
	ProjectPlay mProjectPlay;
	mProjectPlay.ControllerDisconnect();
}


void AtomJointCtL::OnBnClickedAtomsave()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	ProjectPlay mProjectPlay;
	mProjectPlay.Project_SaveFile();
}


void AtomJointCtL::OnBnClickedAtomload()
{
	// TODO: �b���[�J����i���B�z�`���{���X
}


void AtomJointCtL::OnBnClickedAtomreset()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	ProjectPlay mProjectPlay;
	mProjectPlay.Atom_Reset();
	UpdateData(TRUE);
}