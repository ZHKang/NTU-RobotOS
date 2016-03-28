#include "stdafx.h"
#include <Windows.h>
#include "ProjectPlay.h"
#include <vector>
///////////////////////////////
#include <algorithm>
#include <iterator>

#ifdef use_namespace
using namespace ROBOOP;
#endif
using namespace std;
int gAtom_DOF;
int gNTU8DOF_DOF;
const bool debug = 1;
COpenGLControl pOpenGLControl;
static Matrix Atom_T0(4,4);
static ColumnVector Atom_q0(6);
bool ProjectPlay::gAtom_RestFinish = true;
int ProjectPlay::MotorControlSwitch = 1;
static TwinCAT_COM *TWCAT;  // TwinCAT Class�ŧi
std::vector<Matrix> TrajAllQ;   // �]�y��Ϊ��x�}  Nx6 ,N = ;
Matrix ResetAtomTraj;
std::vector<ColumnVector> TrajSetPt;//  �]�w�@�Ӥ@���I �W���C���I�������y��
std::vector<float> TrajTimes; // Trajectory �C�@��set���ɶ�
std::vector<int> TrajTypes;  // Trajectory �C�@��set���y��t��k
std::vector<ColumnVector> TrajALLtimes;  // Trajectory �������ɶ�
bool Atom_Motorsend = false;

ProjectPlay::ProjectPlay(){}
ProjectPlay::~ProjectPlay(){
}
//
const Real Atom_data_DH[] = 
{
	// joint_type, theta, d,a,alpha, thetamin, thetamax, joint_offset,/**/ m, cm x, cm y, cm z, Ixx, Ixy, Ixz, Iyy,Iyz, Izz, lock
	0, 0, 1.22, 0,M_PI/2, 0, 0, 0,/* */  1.74, 0, 0.01, 1.18,/* */ 0.00461, 0, 0, 0.00373, 0, 0.00226, 0,
	0, 0, 0, 0, M_PI/2, 0, 0, M_PI,/* */ 0.353, -0.000563, 0.0189, 0.00805, /* */0.000314, 0, 0, 0.000276, 0, 0.000264, 0, 
	0, 0, 0.371, 0.01, M_PI/2.0, 0, 0, M_PI,/* */ 1.995, -0.004689, 0.00023, 0.2346,/* */ 0.0152, 0, 0, 0.0151, 0, 0.001, 0,
	0, 0, 0, -0.01, -M_PI/2.0, 0, 0, -M_PI/2,/* */ 0.236, 0.0347, 0.00691, 0.000406, /* */ 0.00023, 0, 0, 0.000305, 0, 0.000193, 0, 
	0, 0, 0.28, 0, M_PI/2.0, 0, 0, M_PI,/* */ 1.331, 0.00103, 0.000588, 0.1606,/* */ 0.00566, 0, 0, 0.00558, 0, 0.000569, 0, 
	0, 0, 0, 0.1451, M_PI/2.0, 0, 0, M_PI/2.0,/* */ 0.274, 0.000177, 0.0371, -0.00124,/* */ 0.000198, 0, 0, 0.000124, 0, 0.000134, 0
};

const Real Atom_motor[] =  // Im Gr B Cf [3863 3257 2642 2642 2642 2232]
{
	1.2e-5, 200, 0, 0, // using + and - directions average
	1.2e-5, 250, 0, 0,
	1.1e-6, 200, 0, 0,
	1.1e-6, 250, 0, 0,
	1.1e-6, 200, 0, 0,
	3.8e-7, 300, 0, 0
};

const Real NTU8DOF_data_DH[] = 
{
	// theta, d,a,alpha
	0, 0,        1.2, 0,M_PI/2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, M_PI/2, 0.275, 0,M_PI/2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, M_PI/2, 0.108, 0,M_PI/2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0,      0.300, 0,M_PI/2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, M_PI/2,-0.108, 0,M_PI/2.0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
	0, 0.0,    0.275, 0,M_PI/2.0, 0, 0, 0, 4.8, -0.0203, -0.0141, 0.07, 0.066, 0, 0, 0.086, 0, 0.0125, 0,
	0, -M_PI/2,0.108, 0,M_PI/2.0, 0, 0, 0, 0.82, 0, 0.019, 0, 0.0018, 0, 0, 0.0013, 0, 0.0018, 0, 
	0, 0,      0.200, 0,     0.0, 0, 0, 0, 0.34, 0.0, 0.0, 0.0, 0.0003, 0.0, 0.0, 0.0004, 0.0, 0.0003, 0
};
const Real NTU8DOF_motor[] =  // Im Gr B Cf
{
	200e-6, -62.6111, 0, 0, // using + and - directions average
	200e-6, 107.815, 0, 0,
	200e-6, -53.7063, 0, 0,
	33e-6,  76.0364, 0, 0,
	33e-6,  71.923,  0, 0,
	33e-6,  76.686,  0, 0,
	33e-6,  71.923,  0, 0,
	33e-6,  76.686,  0, 0
};
// joint_type, theta, d, a, alpha, thetamin, thetamax, joint_offset, m,cm x, cm y, cm z, Ixx, Ixy, Ixz, Iyy, Iyz, Izz, Immobile
const Real PUMA560_data[] =
{
0, 0, 0, 0,  M_PI/2.0, /*  */0, 0, 0, /*  */ 0, 0, 0, 0,/*  */ 0, 0, 0, 0.35, 0, 0, 0, 
0, 0, 0, 0.4318, 0, /*  */0, 0, 0,/*  */ 17.4, -0.3638, 0.006, 0.2275,/*  */ 0.13, 0, 0, 0.524, 0, 0.539, 0, 
0, 0, 0.15005, 0.0203, -M_PI/2.0,/*  */ 0, 0, 0,/*  */ 4.8, -0.0203, -0.0141, 0.07,/*  */ 0.066, 0, 0, 0.086, 0, 0.0125, 0,
0, 0, 0.4318, 0.0, M_PI/2.0,/*  */ 0, 0, 0,/*  */ 0.82, 0, 0.019, 0,/*  */ 0.0018, 0, 0, 0.0013, 0, 0.0018, 0, 
0, 0, 0, 0, -M_PI/2.0,/*  */ 0, 0, 0,/*  */ 0.34, 0.0, 0.0, 0.0,/*  */ 0.0003, 0.0, 0.0, 0.0004, 0.0, 0.0003, 0, 
0, 0, 0, 0, 0,/*  */ 0, 0, 0,/*  */ 0.09, 0.0, 0.0, 0.032,/*  */ 0.00015, 0.0, 0.0, 0.00015, 0.0, 0.00004, 0};
const Real PUMA560_motor[] = //Im, Gr, B, Cf, 
{200e-6, -62.6111, 1.48e-3, (.395 +.435)/2, /* using + and - directions average */
200e-6, 107.815, .817e-3, (.126 + .071)/2,
200e-6, -53.7063, 1.38e-3, (.132	+ .105)/2,
33e-6,   76.0364, 71.2e-6, (11.2e-3 + 16.9e-3)/2,
33e-6,   71.923, 82.6e-6, (9.26e-3 + 14.5e-3)/2,
33e-6,   76.686, 36.7e-6, (3.96e-3 + 10.5e-3)/2};
//  Robot Model
Robot robot_atom, robot_NTU8DOF;
Matrix K;
Matrix Atom_qRestAll;   //  reset �Ϊ� delta q �C�C�ߦ^�h

bool ATomThreadClose = false;
bool ForceSensorThreadClose = false;
const int Atom_RedunctionRate[] = {200,250,200,250,200,300};  //  �ª���Encoder Count ratio +-���ܤ�V
const int Atom_MotorCountRatio[] = {4*512,4*512,4*512,4*512,4*512,4*512};  //  �ª���Encoder Count ratio +-���ܤ�V
const float ATom_MotorTorqueConst[] = {39.8, 39.8, 37.83,37.83,37.83,32.1}; // Torque const mNm/A
const float ATom_MotorPeakCurrent[] = {6,6,2,2,2,1}; // Peak Current A

std::vector<std::vector<float>> SaveALLTimes;
std::vector<std::vector<float>> SaveALLRefq;   //  Output Reference Theta
std::vector<std::vector<float>> SaveALLRefqd;   //  Output Reference Theta dot
std::vector<std::vector<float>> SaveALLRefqdd;   //  Output Reference theta ddot
std::vector<std::vector<float>> SaveALLRefTor;   //  Output Reference Torque
std::vector<std::vector<float>> SaveALLFeedbackq;   //  Output feedback theta
std::vector<std::vector<float>> SaveALLFeedbackqd;   //  Output feedback theta dot
std::vector<std::vector<float>> SaveALLFeedbackqdd;   //  Output feedback theta ddot
std::vector<std::vector<float>> SaveALLFeedbackTorque;   //  Output feedback Torque
void AllSaveFileClear()
{
	//SaveALLTimes.clear();
	SaveALLRefq.clear();
	SaveALLRefqd.clear();
	SaveALLRefqdd.clear();
	SaveALLRefTor.clear();
	SaveALLFeedbackq.clear();
	SaveALLFeedbackqd.clear();
	SaveALLFeedbackqdd.clear();
	SaveALLFeedbackTorque.clear();
}

DWORD WINAPI Thread_Atom_motor( LPVOID lpParam ) 
{
	cout<<"== Atom Motor Thread Open ! =="<<endl;
	// ALL save File initial
	AllSaveFileClear();

	ColumnVector qn(gAtom_DOF);
	// Trajectory big matrix to each sub columnvector 
	ColumnVector TrajtempQ(6);
	////  �p�� Initial set command matrix
	//float *Command;
	//Command = new float [6];
	// TwinCAT initial  matrix
	static long set_position[6];
	static long read_position[6];
	static long read_velocity[6];
	static short read_tor[6];
	for(int k=0;k<6;k++){read_tor[k]=0;read_position[k]=0;read_velocity[k]=0;}  //  initial feedback Position torque
	// initial �h��^�Ӫ��x�} q qd qdd torque �h=Reference,�^��=Feedback
	std::vector<float> _tempRefq;
	std::vector<float> _tempFeedbackq;
	std::vector<float> _tempFeedbackqd;
	std::vector<float> _tempFeedbackqdd;
	std::vector<float> _tempFeedbackTorque;
	//  Other parameters
	int TrajRowCount = 1;  // �s��y��ɭp��C�խn��X���I
	int TrajSetpointCount = 0;  // �s��y�� ���X��
	////   Thread Start
	while(1)
	{
		switch(ProjectPlay::MotorControlSwitch)
		{
		case 1: //  Position control
			qn = robot_atom.get_available_q();
			// ------- �e�X�h -----
			_tempRefq.clear();
			for (int i=0;i<6;i++)
			{
				set_position[i]=(qn(i+1))/(2*M_PI)*Atom_RedunctionRate[i]*Atom_MotorCountRatio[i];  //  4*512 = count ratio = 2Pi
				_tempRefq.push_back((float)qn(i+1));
			}
			SaveALLRefq.push_back(_tempRefq);   //  �s�ɥ�
			if (Atom_Motorsend)
			{			
				TWCAT->EtherCATSetEncoder_iPOS(set_position);
				TCatIoOutputUpdate( TASK_ARM_CST_PORTNUMBER );
				TCatIoInputUpdate( TASK_ARM_CST_PORTNUMBER );
				// -------  �^�^�^�ӨӨӨ� -----
				TWCAT->EtherCATReadTorque_iPOS(read_tor);
				TWCAT->EtherCATReadVelocity_iPOS(read_velocity);
				TWCAT->EtherCATReadEncoder_iPOS(read_position);
				//  �s��
				_tempFeedbackq.clear();_tempFeedbackqd.clear();_tempFeedbackTorque.clear();
				for (int i=0;i<6;i++){
					_tempFeedbackq.push_back(read_position[i]*(2*M_PI)/Atom_RedunctionRate[i]/Atom_MotorCountRatio[i]);  // Unit: Rad
					_tempFeedbackqd.push_back(read_velocity[i]*(2*M_PI)/(Atom_RedunctionRate[i]*Atom_MotorCountRatio[i])/0.001);  //Unit Rad/s
					_tempFeedbackTorque.push_back(read_tor[i]);  // Unit Nm
				}
				SaveALLFeedbackq.push_back(_tempFeedbackq);
				SaveALLFeedbackqd.push_back(_tempFeedbackqd);
				SaveALLFeedbackTorque.push_back(_tempFeedbackTorque);
			}
			break;
		case 2: // Torque control
			break;
		case 3: // Velocity control
			break;
		case 4: // continuous position control (Trajectory)
			if (TrajSetpointCount != TrajAllQ.size())
			{
				if (TrajRowCount!=TrajAllQ[TrajSetpointCount].size()/6)
				{
					TrajtempQ = TrajAllQ[TrajSetpointCount].row(TrajRowCount).AsColumn();
					robot_atom.set_q(TrajtempQ);
					TrajRowCount++;
				}
				else   // �᧹�@��Trajectory Matrix ��U�@�� �ҥHTrajSetpointCount++
				{
					TrajRowCount = 1;  // �@�խy��̭����X��Row
					TrajSetpointCount++;
				}
			}
			else
			{
				cout<<"�᧹�P~~~~"<<endl;
				TrajRowCount = 1;
				TrajSetpointCount = 0;
				ProjectPlay::MotorControlSwitch = 1;
				break;
			}
			// ------- �e�X�h -----
			qn = robot_atom.get_available_q();
			_tempRefq.clear();
			for (int i=0;i<6;i++)
			{
				set_position[i]=(qn(i+1))/(2*M_PI)*Atom_RedunctionRate[i]*Atom_MotorCountRatio[i];  //  4*512 = count ratio = 2Pi
				_tempRefq.push_back((float)qn(i+1));
			}
			SaveALLRefq.push_back(_tempRefq);   //  �s�ɥ�
			if (Atom_Motorsend)  // ���F����O
			{
				TWCAT->EtherCATSetEncoder_iPOS(set_position);
				TCatIoOutputUpdate( TASK_ARM_CST_PORTNUMBER );
				TCatIoInputUpdate( TASK_ARM_CST_PORTNUMBER );
				// -------  �^�^�^�ӨӨӨ� -----
				TWCAT->EtherCATReadTorque_iPOS(read_tor);
				TWCAT->EtherCATReadEncoder_iPOS(read_position);
				TWCAT->EtherCATReadVelocity_iPOS(read_velocity);
				//  �s��
				_tempFeedbackq.clear();_tempFeedbackqd.clear();_tempFeedbackTorque.clear();
				for (int i=0;i<6;i++){
					read_position[i] = read_position[i]*(2*M_PI)/Atom_RedunctionRate[i]/Atom_MotorCountRatio[i];
					read_velocity[i] = read_velocity[i]*(2*M_PI)/(Atom_RedunctionRate[i]*Atom_MotorCountRatio[i])/0.001;
					read_tor[i] = read_tor[i]/65520*2*ATom_MotorPeakCurrent[i]*Atom_RedunctionRate[i];
					_tempFeedbackq.push_back(read_position[i]);  // Unit: Rad
					_tempFeedbackqd.push_back(read_velocity[i]);  //Unit Rad/s
					_tempFeedbackTorque.push_back(read_tor[i]);  // Unit Nm
				}
				SaveALLFeedbackq.push_back(_tempFeedbackq);
				SaveALLFeedbackqd.push_back(_tempFeedbackqd);
				SaveALLFeedbackTorque.push_back(_tempFeedbackTorque);
			}
			break;
		case 5:  // Reset Atom
			if (ResetAtomTraj.Nrows() != TrajRowCount)
			{
				TrajtempQ = ResetAtomTraj.row(TrajRowCount).AsColumn();
				robot_atom.set_q(TrajtempQ);
				TrajRowCount++;
			}
			else
			{
				cout<<" Reset Finish "<<endl;
				TrajRowCount = 1;
				ProjectPlay::MotorControlSwitch = 1;
				break;
			}
			qn = robot_atom.get_available_q();
			// ------- �e�X�h -----
			for (int i=0;i<6;i++)
				set_position[i]=(qn(i+1))/(2*M_PI)*Atom_RedunctionRate[i]*Atom_MotorCountRatio[i];  //  4*512 = count ratio = 2Pi
			if (Atom_Motorsend)  // ���F����O
			{			
				TWCAT->EtherCATSetEncoder_iPOS(set_position);
				TCatIoOutputUpdate( TASK_ARM_CST_PORTNUMBER );
				TCatIoInputUpdate( TASK_ARM_CST_PORTNUMBER );
			}
			break;
		case 6:   // ����Ƴ�����
			break;
		}
		// reset 
		Sleep(5.0);
		if (ATomThreadClose)
			return 0;
	};
}

void ProjectPlay::project_ATomThreadClose()
{
	ATomThreadClose = true;
}

DWORD WINAPI Thread_ForceSensor( LPVOID lpParam ) 
{
	cout<<"== ForceSensor Thread Open ! =="<<endl;
	double SensorData[6];
	////   Thread Start
	while(1)
	{
		ForceSensor::getForceTorqe(SensorData);

		for(int i=0;i<6;i++)
			printf("%.2f ",SensorData[i]);
			//cout << SensorData[i] << " ";
		cout << endl;
		// reset 
		Sleep(5.0);
		if (ForceSensorThreadClose)
			return 0;
	};
}

void ProjectPlay::project_ForceSensorThreadClose()
{
	ForceSensorThreadClose = true;
}

void ProjectPlay::project_InitAtom()
{
	Matrix initrobot, initrobotm;
	initrobot = Matrix(6,19);
	initrobotm = Matrix(6,4);
	initrobot<<Atom_data_DH;
	initrobotm<<Atom_motor;

	robot_atom = Robot(initrobot,initrobotm);   //  Robot model
	gAtom_DOF = robot_atom.get_dof();   // initial Atom_DOF variables
	cout << "Robot D-H parameters\n";
	cout << "theta     d       a     alpha\n";
	cout << setw(7) << setprecision(3) << initrobot.SubMatrix(1,gAtom_DOF,2,5);
	cout<<"Atom DOF = "<<gAtom_DOF<<endl;
	cout<<"\n";
	cout << "Robot D-H inertial parameters\n";
	cout << "  mass     cx       cy      cz     Ixx     Ixy     Ixz     Iyy     Iyz     Izz\n";
	cout << setw(7) << setprecision(3) << initrobot.SubMatrix(1,gAtom_DOF,9,18);
	cout << "\n";
	//cout << "Robot motors inertia, gear ratio, viscous and Coulomb friction coefficients\n";
	//cout << "  Im       Gr       B       Cf\n";
	//cout << setw(7) << setprecision(3) << initrobotm;
	cout << "\n";
	cout << "Robot joints variables\n";
	cout << setw(7) << setprecision(3) << robot_atom.get_q().as_row();
	cout << "\n";
	cout << "Robot Inertia matrix\n";
	cout << setw(7) << setprecision(3) << robot_atom.inertia(robot_atom.get_q());
	cout << "\n";
	cout << "Robot Gravity matrix\n";
	cout << setw(7) << setprecision(3) << robot_atom.G().as_row();
	cout << "\n";
	cout << "Robot Initial Torque\n";
	cout << setw(7) << setprecision(3) << robot_atom.torque(robot_atom.get_q(),robot_atom.get_q(),robot_atom.get_q()).as_row();
	cout << "\n";
	// Initial Cartesian and joint space T0, q0;
	Atom_T0 = robot_atom.kine();
	Atom_q0 = robot_atom.get_available_q();
	/////////////////////////////////////////////////

	pOpenGLControl.glFlagATomStick = true;

	cout<<"/////////////////////////////////////////////////"<<endl;
	//  �Ұ�Tread
	int Data_Of_Thread_1 = 1;
	HANDLE Handle_Of_Thread_1 = 0;
	// variable to hold handle of Thread 1 
	// Aray to store thread handles 
	HANDLE Array_Of_Thread_Handles[3];
	Handle_Of_Thread_1 = CreateThread( NULL, 0, 
		Thread_Atom_motor, &Data_Of_Thread_1, 0, NULL);  
	if ( Handle_Of_Thread_1 == NULL)
		ExitProcess(Data_Of_Thread_1);
	ATomThreadClose = false;
	// initial �y��W��Setpt���x�}
	TrajSetPt.push_back(Atom_q0);
	TrajTimes.push_back(0);
	TrajTypes.push_back(0);
}

void ProjectPlay::project_InitForceSensor()
{
	//  �Ұ�Tread
	int Data_Of_Thread_2 = 1;
	HANDLE Handle_Of_Thread_2 = 0;
	// variable to hold handle of Thread 1 
	// Aray to store thread handles 
	HANDLE Array_Of_Thread_Handles[3];
	Handle_Of_Thread_2 = CreateThread( NULL, 0, 
		Thread_ForceSensor, &Data_Of_Thread_2, 0, NULL);  
	if ( Handle_Of_Thread_2 == NULL)
		ExitProcess(Data_Of_Thread_2);
	ForceSensorThreadClose = false;
}

void ProjectPlay::AtomDynControl()
{
	// Trajectory Planning
}

void ProjectPlay::project_AtomStep(int num)
{

	ColumnVector qn(gAtom_DOF);
	qn = robot_atom.get_q();
	switch(num)
	{
		case 1:
			qn(1) = qn(1)-(0.5/180*M_PI);
			break;
		case 2:
			qn(1) = qn(1)+(0.5/180*M_PI);
			break;
		case 3:
			qn(2) = qn(2)-(0.5/180*M_PI);
			break;
		case 4:
			qn(2) = qn(2)+(0.5/180*M_PI);
			break;
		case 5:
			qn(3) = qn(3)-(0.5/180*M_PI);
			break;
		case 6:
			qn(3) = qn(3)+(0.5/180*M_PI);
			break;
		case 7:
			qn(4) = qn(4)-(0.5/180*M_PI);
			break;
		case 8:
			qn(4) = qn(4)+(0.5/180*M_PI);
			break;
		case 9:
			qn(5) = qn(5)-(0.5/180*M_PI);
			break;
		case 10:
			qn(5) = qn(5)+(0.5/180*M_PI);
			break;
		case 11:
			qn(6) = qn(6)-(0.5/180*M_PI);
			break;
		case 12:
			qn(6) = qn(6)+(0.5/180*M_PI);
			break;

	}
	robot_atom.set_q(qn);
}

void ProjectPlay::project_AtomCartStep(int num)
{
	Matrix Rn,Tn;
	ColumnVector Pn;
	Tn = robot_atom.kine();
	robot_atom.kine(Rn,Pn);
	float step = 0.001;
	float steprot = 0.5;
	switch (num)
	{
	case 1:
		Pn(1) = Pn(1)+step;
		break;
	case 2:
		Pn(1) = Pn(1)-step;
		break;
	case 3:
		Pn(2) = Pn(2)+step;
		break;
	case 4:
		Pn(2) = Pn(2)-step;
		break;
	case 5:
		Pn(3) = Pn(3)+step;
		break;
	case 6:
		Pn(3) = Pn(3)-step;
		break;
	case 7:
		Tn = Tn*rotx(steprot*M_PI/180);
		break;
	case 8:
		Tn = Tn*rotx(-steprot*M_PI/180);
		break;
	case 9:
		Tn = Tn*roty(steprot*M_PI/180);
		break;
	case 10:
		Tn = Tn*roty(-steprot*M_PI/180);
		break;
	case 11:
		Tn = Tn*rotz(steprot*M_PI/180);
		break;
	case 12:
		Tn = Tn*rotz(-steprot*M_PI/180);
		break;
	default:
		break;
	}
	
	Matrix Tobj(4,4);
	Tobj = Tn;
	for (int i=1;i<=3;i++)
		Tobj(i,4) = (float)Pn(i);
	// get ik q;
	ColumnVector qn;
	qn = robot_atom.inv_kin(Tobj);
	robot_atom.set_q(qn);
}
void ProjectPlay::ProjectPlay_InitNTU8DOF()
{
	Matrix initrobot, initrobotm;
	initrobot = Matrix(8,19);
	initrobotm = Matrix(8,4);
	initrobot<<NTU8DOF_data_DH;
	initrobotm<<NTU8DOF_motor;

	robot_NTU8DOF = Robot(initrobot,initrobotm);   //  Robot model

	gNTU8DOF_DOF = robot_NTU8DOF.get_dof();   // initial Atom_DOF variables
	cout << "Robot D-H parameters\n";
	cout << "theta     d       a     alpha\n";
	cout << setw(7) << setprecision(3) << initrobot.SubMatrix(1,gNTU8DOF_DOF,2,5);
	cout<<"NTU 8 DOF = "<<gNTU8DOF_DOF<<endl;

	///////////////////////////////////////////////////
	int count = 0;
	int Psize = gNTU8DOF_DOF*3;
	Matrix tempR;
	ColumnVector tempP;
	for (int i=1;i<=gNTU8DOF_DOF;i++){
		robot_NTU8DOF.kine(tempR,tempP,i);   // FK �N��i�b������R�P�y��P��X
		gNTU8DOF_P[0+count] = (float)tempP(1);
		gNTU8DOF_P[1+count] = (float)tempP(2);
		gNTU8DOF_P[2+count] = (float)tempP(3);
		//printf("Joint %d :",i);
		//cout<<gAtom_P[0+count]<<"\t"<<gAtom_P[1+count]<<"\t"<<gAtom_P[2+count]<<endl;
		count = count+3;
		//cout<<tempP.as_row()<<endl;
	}
	//  �w�����e�Ϫk
	//  ���t�p��Ϊ��x�}gAtom_P�ƻs�ilocal gl_Atom_P�x�}
	//  �T�O�x�}�@�����ȥi�H�e��
	if (!pOpenGLControl.glFlagNTU8DOFStick)
	{	
		for (int i=0;i<Psize;i++)
		{
			pOpenGLControl.gl_NTU8DOF_P[i] = gNTU8DOF_P[i];
		}
		pOpenGLControl.glFlagNTU8DOFStick = true;
	}
	cout<<"/////////////////////////////////////////////////"<<endl;
}

void ProjectPlay::ControllerConnect()
{
	////  TWINCAT �s�u
	TWCAT = new TwinCAT_COM();
	Atom_Motorsend = true;
}
void ProjectPlay::ControllerDisconnect()
{
	Atom_Motorsend = false;
	TWCAT->~TwinCAT_COM();
}
void ProjectPlay::Atom_dynamics_Test()
{
	std::vector<std::vector<float>> TorqueAll;  //  Base Force All
	ColumnVector qf;
	qf = robot_atom.get_available_q();
	float samp = 0.005;
	float ti = 0.0,tf = 5.0;
	int grid = (int)(tf-ti)/samp+2;
	ColumnVector tout(grid);
	for (int i=1;i<=grid;i++){
		tout(i) = ti+(i-1)*samp;
	}
	Matrix qs,qsd,qsdd;
	qs = robot_jTray(Atom_q0,qf,tout,1);   //  jTraj position
	qsd = robot_jTray(Atom_q0,qf,tout,2);  // velocity
	qsdd = robot_jTray(Atom_q0,qf,tout,3);  //  Acc
	////////////////////////////
	Matrix TorOutAll;
	ColumnVector TorOut;
	ColumnVector tempQ(6),tempQd(6),tempQdd(6);
	tempQ = qs.Row(1).as_column();
	ColumnVector Fext(3), Next(3);
	Real Fxyz[] = {0,0,0};
	Fext<<Fxyz;
	Real Rxyz[] = {0,0,0};
	Next<<Rxyz;
	for (int i=1;i<=grid;i++){
		tempQ = qs.Row(i).as_column();
		tempQd = qsd.Row(i).as_column();
		tempQdd = qsdd.Row(i).as_column();
		TorOut = robot_atom.torque(tempQ,tempQd,tempQdd,Fext,Next);
		std::vector<float> _tempTorque; // for save all output torque
		for (int jj=1;jj<=6;jj++){
			_tempTorque.push_back(TorOut(jj));
		}
		if (debug){
			//cout<<"Torque:\t"<<TorOut.as_row()<<endl;
		}
		//TorOutAll.row(i) = TorOut.as_row();
		TorqueAll.push_back(_tempTorque);
		_tempTorque.clear();
	}

	FileIO(TorqueAll,"TorqueAll_baseForce.txt");
	TorqueAll.clear();
}

void ProjectPlay::Atom_torqueCtl()
{
	std::vector<std::vector<float>> ComputeTorqueAll;  //  Base Force All
	std::vector<std::vector<float>> CTRefPositionAll;  //  Base Force All
	std::vector<std::vector<float>> CTRefVelAll;  //  Base Force All
	std::vector<std::vector<float>> CTRefAccAll;  //  Base Force All
	// Trajectory
	ColumnVector qf;
	qf = robot_atom.get_available_q();
	float samp = 0.005;        //  trajectory sampling time
	float ti = 0.0,tf = 5.0;   //  trajectory time tf to ti
	int grid = (int)(tf-ti)/samp+2;
	ColumnVector tout(grid);
	for (int i=1;i<=grid;i++){
		tout(i) = ti+(i-1)*samp;
	}
	Matrix qs,qsd,qsdd;
	qs = robot_jTray(Atom_q0,qf,tout,1);   //  jTraj position
	qsd = robot_jTray(Atom_q0,qf,tout,2);  // velocity
	qsdd = robot_jTray(Atom_q0,qf,tout,3);  //  Acc
	// Control
	DiagonalMatrix Kp(6), Kv(6);
	Kp = 10;   //  q error
	Kv = 20;   //  qdot error
	ColumnVector qtemp,qdtemp,qddtemp;
	Matrix TorAll, Tortemp;
	Computed_torque_method AtomCTM(robot_atom,Kp,Kv);
	//  save file
	/////
	for (int i=1;i<=grid;i++){
		qtemp<<qs.row(i).as_column();
		qdtemp<<qsd.row(i).as_column();
		qddtemp<<qsdd.row(i).as_column();
		robot_atom.set_q(qtemp);
		robot_atom.set_qp(qdtemp);
		Tortemp =  AtomCTM.torque_cmd(robot_atom,qtemp,qdtemp,qddtemp);
		//
		std::vector<float> _tempTorque;
		std::vector<float> _tempRefq;
		std::vector<float> _tempRefqd;
		std::vector<float> _tempRefqdd;
		for (int jj=1;jj<=6;jj++){
			_tempTorque.push_back(Tortemp(jj,1));
			_tempRefq.push_back(qtemp(jj)*180/M_PI);
			_tempRefqd.push_back(qdtemp(jj)*180/M_PI);
			_tempRefqdd.push_back(qddtemp(jj)*180/M_PI);
		}
		//  Using save test
		ComputeTorqueAll.push_back(_tempTorque);
		CTRefPositionAll.push_back(_tempRefq);
		CTRefVelAll.push_back(_tempRefqd);
		CTRefAccAll.push_back(_tempRefqdd);
		_tempTorque.clear();
		_tempRefq.clear();
		_tempRefqd.clear();
		_tempRefqdd.clear();
	}


	FileIO(CTRefPositionAll,"Reference_PositionOut.txt");
	FileIO(CTRefVelAll,"Reference_VelocityOut.txt");
	FileIO(CTRefAccAll,"Reference_AccelerationOut.txt");
	FileIO(ComputeTorqueAll,"Compute_TorqueOut.txt");
	ComputeTorqueAll.clear();
	CTRefPositionAll.clear();
	CTRefVelAll.clear();
	CTRefAccAll.clear();
}
void ProjectPlay::Atom_Impedance()
{
	DiagonalMatrix Mp(6),Dp(6),Kp(6),Mo(6),Do(6),Ko(6);   // Position and Orientation impedance parameters
	Mp = 1;Dp = 1;Kp = 1;  // End-effector Position impedance
	Mp = 1;Do = 1;Ko = 1;  // End-effector Orientation impedance
	Impedance AtomImp(robot_atom,Mp,Dp,Kp,Mo,Do,Ko);   //  Set Atom Robot impedance parameters
}

void ProjectPlay::Atom_Reset()
{	
	ColumnVector qf;
	qf = robot_atom.get_available_q();
	float samp = 0.005;
	float ti = 0.0,tf = 5.0;
	int grid = (int)(tf-ti)/samp+2;
	ColumnVector tout(grid);
	for (int i=1;i<=grid;i++){
		tout(i) = ti+(i-1)*samp;
	}
	ResetAtomTraj = robot_jTray(qf,Atom_q0,tout,1);   //  jTraj position
	MotorControlSwitch = 5;
}
void ProjectPlay::FileIO(vector<vector<float>> OutData , const string & filename_)
{
	std::string tempNam = "OutputFile\\";
		tempNam+=filename_;
	ofstream FileOut(tempNam.c_str(),ios::out);
		for (int i=0;i<OutData.size();i++){
			for (int j=0;j<OutData[i].size();j++){
				FileOut<<OutData[i][j]<<"\t";
			}
			FileOut<<"\n";
		}
	FileOut.close();
}
void ProjectPlay::FileIO(vector<float> OutData1 , const string & filename_)
{
	std::string tempNam = "OutputFile\\";
	tempNam+=filename_;
	ofstream FileOut(tempNam.c_str(),ios::out);
	for (int i=0;i<OutData1.size();i++)
		FileOut<<OutData1[i]<<"\n";
	FileOut.close();
}
ReturnMatrix ProjectPlay::robot_jTray(ColumnVector q0, ColumnVector qf, ColumnVector time, int Selec)
{
	ColumnVector tnorm;
	ColumnVector A, B, C, D, E, F;
	tnorm = time/time.maximum();
	A = 6*(qf-q0);
	B = -15*(qf-q0);
	C = 10*(qf-q0);
	E  = 0;
	F = q0;
	Matrix tt(time.nrows(),6),cl(6,q0.nrows()),clv(6,q0.nrows()),cla(6,q0.nrows());
	for (int i=1;i<=time.nrows();i++){
		tt(i,1) = pow(tnorm(i),5);
		tt(i,2) = pow(tnorm(i),4);
		tt(i,3) = pow(tnorm(i),3);
		tt(i,4) = pow(tnorm(i),2);
		tt(i,5) = tnorm(i);
		tt(i,6) = 1;
	}
	for (int i=1;i<=q0.nrows();i++){
		cl(1,i) = A(i);
		cl(2,i) = B(i);
		cl(3,i) = C(i);
		cl(4,i) = 0;
		cl(5,i) = 0;
		cl(6,i) = F(i);
	}
	for (int i=1;i<=q0.nrows();i++){
		clv(1,i) = 0;
		clv(2,i) = 5*A(i);
		clv(3,i) = 4*B(i);
		clv(4,i) = 3*C(i);
		clv(5,i) = 0;
		clv(6,i) = 0;
	}
	for (int i=1;i<=q0.nrows();i++){
		cla(1,i) = 0;
		cla(2,i) = 0;
		cla(3,i) = 20*A(i);
		cla(4,i) = 12*B(i);
		cla(5,i) = 6*C(i);
		cla(6,i) = 0;
	}
	Matrix qs,qsd,qsdd;
	if (Selec==1)
	{
		qs = tt*cl;
		qs.release();
		return qs;
	}
	else if (Selec==2)
	{
		qsd = tt*clv/time.maximum();
		qsd.release();
		return qsd;
	}
	else if (Selec==3)
	{
		qsdd = tt*cla/pow(time.maximum(),2);
		qsdd.release();
		return qsdd;
	}
}
void ProjectPlay::Project_SaveFile()
{
	FileIO(SaveALLTimes,"TrajAllTimes.txt");
	FileIO(SaveALLRefq,"Reference_q.txt");
	FileIO(SaveALLFeedbackq,"Feedback_q.txt");
	FileIO(SaveALLFeedbackqd,"Feedbackk_qd.txt");
	FileIO(SaveALLFeedbackTorque,"Feedback_Torque.txt");
}
void ProjectPlay::Project_test()
{
	int size = SaveALLFeedbackTorque.size();
	ColumnVector qn,qnd,qndd;
	qn = robot_atom.get_available_q();
	qnd = robot_atom.get_available_qp();
	qndd = robot_atom.get_available_qpp();
	cout<<"Reference Torque: "<<robot_atom.torque(qn,qnd,qndd).as_row()<<endl;
	cout<<"Feedback Torque: ";
	for (int j=0;j<6;j++){
		cout<<SaveALLFeedbackTorque[size][j]<<"\t";
	}
	cout<<endl;
}
void ProjectPlay::Atom_TrajectoryGO()
{
	//ColumnVector qn;
	//int TrajSetcount = TrajAllQ.size();
	////
	//for (int i=0;i<TrajSetcount;i++)
	//{
	//	for (int j=0;j<TrajAllQ[i].size()/6;j++)
	//	{
	//		qn = TrajAllQ[i].row(j+1).AsColumn();
	//		cout<<qn.AsRow()<<endl;
	//	}
	//}

	//Atom_Reset();
	//cout<<TrajAllQ.size()-1<<endl;
	AllSaveFileClear();
	MotorControlSwitch = 4;
}
void ProjectPlay::Atom_Setpoint(float thetaAll[6],float times,int types)
{
	TrajectoryPlanning mTrajectoryPlanning;
	Matrix TrajQ;
	ColumnVector qf(6),q0(6);
	for (int i=0;i<6;i++){
		qf(i+1) = thetaAll[i];  //  thetaALL �˶icolumnvector
	}
	TrajSetPt.push_back(qf);
	TrajTimes.push_back(times);
	TrajTypes.push_back(types);
	// 
	int tf = TrajTimes.size();
	float samp = 0.005;
	int grid = (int)((TrajTimes[tf-1]-0)/samp)+2;
	ColumnVector tout(grid);
	for (int i=1;i<=grid;i++)
		tout(i) = 0.0+(i-1)*samp;
	q0 = TrajSetPt[tf-2];
	//  Eigen TrajectoryPlanning function
	Eigen::VectorXd eigq0(6),eigqf(6),eigqfd(6);
	Eigen::MatrixXd EigTraj;
	eigqfd<<0,0,0,0,0,0;
	//  �N�C��SetPoint��times�H��Types�s�X��
	std::vector<float> _tempTimeTypes;
	_tempTimeTypes.clear();
	_tempTimeTypes.push_back(times);
	_tempTimeTypes.push_back(types);
	SaveALLTimes.push_back(_tempTimeTypes);
	switch(types)
	{
	case 0:   // 212
		for (int i=0;i<6;i++)
		{eigq0(i) = q0(i+1);eigqf(i) = qf(i+1);}
		EigTraj = mTrajectoryPlanning.Splines212(eigq0,eigqfd,eigqf,eigqfd,(float)times,1);
		TrajQ = Matrix(EigTraj.rows(),EigTraj.cols());
		for (int i=0;i<EigTraj.rows();i++)
		{
			for (int j=0;j<EigTraj.cols();j++)
			{
				TrajQ(i+1,j+1) = (float)EigTraj(i,j);
			}
		}
		break;
	case 1:   // 434
		for (int i=0;i<6;i++)
		{eigq0(i) = q0(i+1);eigqf(i) = qf(i+1);}
		EigTraj = mTrajectoryPlanning.Splines434(eigq0,eigqfd,eigqfd,eigqf,eigqfd,eigqfd,times,1);
		TrajQ = Matrix(EigTraj.rows(),EigTraj.cols());
		for (int i=0;i<EigTraj.rows();i++)
		{
			for (int j=0;j<EigTraj.cols();j++)
			{
				TrajQ(i+1,j+1) = (float)EigTraj(i,j);
			}
		}
		break;
	case 2:   // 535
		for (int i=0;i<6;i++)
		{eigq0(i) = q0(i+1);eigqf(i) = qf(i+1);}
		EigTraj = mTrajectoryPlanning.Splines535(eigq0,eigqfd,eigqfd,eigqfd,eigqf,eigqfd,eigqfd,eigqfd,times,1);
		TrajQ = Matrix(EigTraj.rows(),EigTraj.cols());
		for (int i=0;i<EigTraj.rows();i++)
		{
			for (int j=0;j<EigTraj.cols();j++)
			{
				TrajQ(i+1,j+1) = (float)EigTraj(i,j);
			}
		}
		break;
	case 3:   // cubic
		for (int i=0;i<6;i++)
		{eigq0(i) = q0(i+1);eigqf(i) = qf(i+1);}
		EigTraj = mTrajectoryPlanning.CubicPolynomials(eigq0,eigqfd,eigqf,eigqfd,times,1);
		TrajQ = Matrix(EigTraj.rows(),EigTraj.cols());
		for (int i=0;i<EigTraj.rows();i++)
		{
			for (int j=0;j<EigTraj.cols();j++)
			{
				TrajQ(i+1,j+1) = (float)EigTraj(i,j);
			}
		}
		break;
	case 4:   // line
		TrajQ = robot_straight(q0,qf,robot_atom,times);
		break;
	case 5:   //  jTraj given q0,qf,time = output(Matrix q, qd, qdd)
		TrajQ = robot_jTray(q0,qf,tout,1);
		break;
	}
	TrajAllQ.push_back(TrajQ);
}
void ProjectPlay::Atom_TrajClear()
{
	Atom_Reset();
	TrajAllQ.clear();
	AllSaveFileClear();
	SaveALLTimes.clear();
	TrajSetPt.push_back(Atom_q0);
	TrajTimes.push_back(0);
	TrajTypes.push_back(0);
}

ReturnMatrix ProjectPlay::robot_straight(ColumnVector q0,ColumnVector qf, Robot &_robot, float times)
{
	TrajectoryPlanning mTrajectoryPlanning;
	Matrix qs;
	Robot Robot_Atom_2;
	Robot_Atom_2 = _robot;

	Matrix R0,Rf,T0(4,4),Tf(4,4);
	ColumnVector P0,Pf;
	Robot_Atom_2.set_q(q0);
	T0 = Robot_Atom_2.kine();
	Robot_Atom_2.kine(R0,P0);
	Robot_Atom_2.set_q(qf);
	Tf = Robot_Atom_2.kine();
	Robot_Atom_2.kine(Rf,Pf);
	float distance;
	distance = (Rf-R0).norm_Frobenius()+(Pf-P0).norm_Frobenius();
	map <float, ColumnVector> m1;
	m1.insert(pair<float,ColumnVector> (0.0,q0));
	m1.insert(pair<float,ColumnVector> (distance,qf));

	map<float, ColumnVector>::iterator m1_iter;

	foo(Robot_Atom_2,m1,T0,Tf,q0);

	////////////  212  //////////////
	//  Eigen TrajectoryPlanning function
	Eigen::VectorXd eigq0(6),eigqf(6),eigqfd(6);
	Eigen::MatrixXd EigTraj;
	Eigen::MatrixXd Qvia(m1.size()-2,6);
	eigqfd<<0,0,0,0,0,0;

	for (int i=0;i<6;i++)
	{eigq0(i) = q0(i+1);eigqf(i) = qf(i+1);}

	vector<ColumnVector> temp;
	for(m1_iter = m1.begin(); m1_iter != m1.end(); ++m1_iter){
		temp.push_back(m1_iter->second);
	}
	temp.pop_back();
	temp.erase(temp.begin());

	for(int i = 0, n = temp.size(); i < n; ++i){
		for (int j=0;j<6;j++){
			Qvia(i,j) = temp[i](j+1);
		}
	}

	EigTraj = mTrajectoryPlanning.Splines212(eigq0,eigqfd,eigqf,eigqfd,Qvia,times,1);
	qs = Matrix(EigTraj.rows(),EigTraj.cols());
	for (int i=0;i<EigTraj.rows();i++)
	{
		for (int j=0;j<EigTraj.cols();j++)
		{
			qs(i+1,j+1) = (float)EigTraj(i,j);
		}
	}

	qs.release();
	return qs;
}
void ProjectPlay::foo(Robot foo_robot,map<float,ColumnVector>& m1, Matrix T0,Matrix Tf,ColumnVector q0fix)
{
	//map<float, ColumnVector>::iterator m1_iter;
	//for (m1_iter = m1.begin();m1_iter!=m1.end();m1_iter++)
	//	cout<<m1_iter->second.as_row()<<endl;
	foo_robot.set_q(q0fix);
	Matrix R0fix;ColumnVector P0fix,R0fixCol;
	foo_robot.kine(R0fix,P0fix);
	R0fixCol = irpy(R0fix);

	//
	float rpymax, xyzmax;
	rpymax = 0.00005;
	xyzmax = 0.00005;
	ColumnVector P0(3),Pf(3); Matrix R0(3,3),Rf(3,3);
	ColumnVector q0,qf;
	q0 = foo_robot.inv_kin(T0);
	foo_robot.set_q(q0);
	foo_robot.kine(R0,P0);
	qf = foo_robot.inv_kin(Tf);
	foo_robot.set_q(qf);
	foo_robot.kine(Rf,Pf);


	ColumnVector qm,Pmid;
	qm = (qf+q0)/2;
	Matrix Rmid;
	foo_robot.set_q(qm);
	foo_robot.kine(Rmid,Pmid);

	Matrix R_x(3,3); ColumnVector P_x(3);
	P_x = (P0+Pf)/2;
	ColumnVector tempR0,tempRf;
	tempR0 = irpy(R0).as_column();
	tempRf = irpy(Rf).as_column();
	R_x = rpy((tempR0+tempRf)/2);
	float error_rpy,error_xyz;
	ColumnVector tempRmid,tempR_xc;
	tempRmid = irpy(Rmid);
	tempR_xc = irpy(R_x);


	error_rpy = (tempRmid-tempR_xc).norm_Frobenius();
	error_xyz = (Pmid - P_x).norm_Frobenius();

	ColumnVector q_x; 
	Matrix T_x(4,4);
	
	T_x = 0;T_x(4,4) = 1;
	for (int i=1;i<=3;i++){
		for (int j=1;j<=3;j++){
			T_x(i,j) = R_x(i,j);
		}
	}
	for (int i=1;i<=3;i++)
		T_x(i,4) = P_x(i);

	q_x = foo_robot.inv_kin(T_x);
	if (error_rpy < rpymax && error_xyz < xyzmax)
	{
		m1.insert(pair <float,ColumnVector>(((tempRmid-R0fixCol).norm_Frobenius() + (Pmid-P0fix).norm_Frobenius()), qm));
	}
	else
	{
		m1.insert(pair <float,ColumnVector>(((tempR_xc-R0fixCol).norm_Frobenius() + (P_x-P0fix).norm_Frobenius()), q_x));
		foo(robot_atom,m1,T0,T_x,q0fix);
		foo(robot_atom,m1,T_x,Tf,q0fix);
	}
}

SerialPort GripCon;
void ProjectPlay::GripperConnectOrDisConnect(int types)
{
	if (types ==1)
	{
		GripCon.FAULHABER_Initial("\\\\.\\COM3",115200);
	}
	else
	{
		GripCon.close();
	}
}

void ProjectPlay::Grip_Command(int a)
{
	char send_pose[100];
	string send_command;
	int pose_value;

	if(a==1)   //close
	{
		pose_value=52000;
	}
	else      //open
	{
	    pose_value=-52000;
	}

	send_command = "EN\r";
	GripCon._write((uchar* )send_command.c_str(),send_command.length());

	sprintf(send_pose,"lr%d\r",pose_value);
	send_command = send_pose;
	GripCon._write((uchar* )send_command.c_str(),send_command.length());

	send_command = "m\r";
	GripCon._write((uchar* )send_command.c_str(),send_command.length());
}