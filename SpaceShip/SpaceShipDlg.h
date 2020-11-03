// SpaceShipDlg.h : header file
//

#pragma once
#include "afxwin.h"

#define ID_TIMER1 1000

struct RKresult
{
	double t;
	double x;
	double y;
	double Vx;
	double Vy;
	double xOld;
	double yOld;
	double oldVx;
	double oldVy;
	double curE;
	RKresult(double t_, double x_, double y_, double Vx_, double Vy_)
	{
		t = t_;
		x = x_;
		y = y_;
		Vx = Vx_;
		Vy = Vy_;

		xOld = x_;
		yOld = y_;
	};
};

// SpaceShipDlg dialog
class SpaceShipDlg : public CDialog
{
	// Construction
public:
	SpaceShipDlg(CWnd* pParent = NULL);	// standard constructor
	CWnd *frameWnd;			// ����� ����

	CRect frameRect,		// ������� ��� ���������
		rect,
		Vrect,				// ������� ��� ��������� ������� �������� �� �������
		Urect,				// ������� ��� ��������� ������� ������������� �������
		Trect,				// ������� ��� ��������� ������� ������������ �������
		Erect;				// ������� ��� ��������� ������� ������ �������

	CDC *frameDc;			// ��� ��������

	CDC	*UDc;				// ��� ������� ������������� �������
	CDC	*TDc;				// ��� ������� ������������ �������
	CDC *EDc;				// ��� ������� ������ �������
	CDC *VDc;				// ��� ������� �������� �� �������

	CDC pMemDc,				// �������� ��� ��������� (� ������)
		UpMemDc,
		TpMemDc,
		EpMemDc,
		VMemDc;
	CBitmap bmp, *tmp,		// ��� �������� �����������
		Ubmp, *Utmp,		// ��� ������� ������������� �������
		Tbmp, *Ttmp,		// ��� ������� ������������ �������
		Ebmp, *Etmp,		// ��� ������� ������ �������
		Vbmp, *Vtmp;		// ��� ������� ��������

	CBrush brush,
		*oldbrush;			// ����� ��� ���������
	CPen pen,
		*oldpen;			// ���� ��� ���������

	int xCenter,			// ����� �� �
		yCenter,			// ����� �� Y
		osiT,				// ��� t ��� ��������
		osiTU,				// ��� t ��� ������� ������������� �������
		osiTT,				// ��� t ��� ������� ������������ �������
		osiTE,				// ��� t ��� ������� ������ �������
		osiV,				// ��� t ��� ������� ��������
		nTimer,				// ��� �������
		ntimeout;			// ��� �������
	double 
		xKoorShip,			// ������� ���������� (x)
		yKoorShip,			// ������� ���������� (y)
		HAtm,				// ������ ���������
		H,					// ������
		oldxKoorShip,		// ���������� ���������� (x)
		oldyKoorShip,		// ���������� ���������� (y)
		Vx,					// ������� �������� �� x
		Vy,					// ������� �������� �� y
		V,					// ��������
		m,					// ����� ������������ ��������
		RealTime,			// ��� �������
		TimerOn,			// ��� �������
		mX, mT,				// ���������� ���������
		Fdrag,				// ���� �������� �������������
		startPositionX,		// ��������� ������� �� ���������� x
		startPositionY,		// ��������� ������� �� ���������� y
		startPositionXA,	// ��������� ������� �� ���������� x ��� ������ �
		startPositionYA,	// ��������� ������� �� ���������� y ��� ������ �
		startPositionXB,	// ��������� ������� �� ���������� x ��� ������ �
		startPositionYB;	// ��������� ������� �� ���������� y ��� ������ �
	double ActiveTime;		// ����� ������ ��������� ����������
	double H0Real;			// ��������� ������ ��� ������ ��������
	double H0;				// ��������� ������ ��� ������ ����������
	double V0;				// ��������� ��������
	double dt;				// ������-t
	bool enableTime;		// �������� �� ���������
	bool ifMainGraf, ifUGraf, ifTGraf, ifEGraf, ifVGraf;	// ������������ ��

	// Dialog Data
	enum { IDD = IDD_SPACESHIP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();						// ���������� ��� ������������� ����������� ����
	afx_msg void OnPaint();								// ���������� ��� ������� ���������
	afx_msg void DrawEarth(CDC *pDc, CRect r);			// ���������� ����� � ����� ���������
	afx_msg void DrawShip(CDC *pDc, CRect r);			// ���������� ����������� �������
	afx_msg void DrawShipTraectory(CDC *pDc, CRect r);	// ���������� ���������� (����������� ����������)
	afx_msg void DrawUGraf(CDC *pDc, CRect r);			// ��� ��������� ������� ������������� �������
	afx_msg void DrawTGraf(CDC *pDc, CRect r);			// ��� ��������� ������� ������������ �������
	afx_msg void DrawEGraf(CDC *pDc, CRect r);			// ��� ��������� ������� �������� �� �������
	afx_msg void DrawVGraf(CDC *pDc, CRect r);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()								// ��� ������� �������� �� ���������
public:
	afx_msg void OnBnClickedStart();					// ���������� ��� ������� ������� �� ������ �����
	afx_msg void OnTimer(UINT nIDEvent);				// ���������� �� ������ "���" �������
	afx_msg void OnBnClickedStop();						// ���������� ��� ������� ������� �� ������ ����
	afx_msg void OnBnClickedButton1();					// ���������� ��� ������� ������� �� ������ �������� ��������� ���������
	void SendParameters();								// ������ ����������

	double f(double t, double x, double y, double vx, double vy);			// ��� 2 ������ ������� � 1 � 2 ������ ��� x
	double g(double t, double x, double y, double vx, double vy);			// ��� 2 ������ ������� � 1 � 2 ������ ��� y
	RKresult RKMethod(double t, double x, double y, double vx, double vy);	// ����� �����-����� ��� 1 � 2 ������
public:
	double curVx;
public:
	double curVy;
public:
	double k;
	afx_msg void OnBnClickedA();						// ���������� ��� ������� ������� �� ������ �)
	afx_msg void OnBnClickedB();						// ���������� ��� ������� ������� �� ������ �)
};
