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
	CWnd *frameWnd;			// фрейм окна

	CRect frameRect,		// области для рисования
		rect,
		Vrect,				// область для рисования графика скорости от времени
		Urect,				// область для рисования графика потенциальной энергии
		Trect,				// область для рисования графика кинетической энергии
		Erect;				// область для рисования графика полной энергии

	CDC *frameDc;			// для анимации

	CDC	*UDc;				// для графика потенциальной энергии
	CDC	*TDc;				// для графика кинетической энергии
	CDC *EDc;				// для графика полной энергии
	CDC *VDc;				// для графика скорости от времени

	CDC pMemDc,				// контекст для рисования (в памяти)
		UpMemDc,
		TpMemDc,
		EpMemDc,
		VMemDc;
	CBitmap bmp, *tmp,		// для хранения изображения
		Ubmp, *Utmp,		// для графика потенциальной энергии
		Tbmp, *Ttmp,		// для графика кинетической энергии
		Ebmp, *Etmp,		// для графика полной энергии
		Vbmp, *Vtmp;		// для графика скорости

	CBrush brush,
		*oldbrush;			// кисть для рисования
	CPen pen,
		*oldpen;			// перо для рисования

	int xCenter,			// центр по Х
		yCenter,			// центр по Y
		osiT,				// ось t для графиков
		osiTU,				// ось t для графика потенциальной энергии
		osiTT,				// ось t для графика кинетической энергии
		osiTE,				// ось t для графика полной энергии
		osiV,				// ось t для графика скорости
		nTimer,				// для таймера
		ntimeout;			// для таймера
	double 
		xKoorShip,			// текущие координаты (x)
		yKoorShip,			// текущие координаты (y)
		HAtm,				// высота атмосферы
		H,					// высота
		oldxKoorShip,		// предыдущие координаты (x)
		oldyKoorShip,		// предыдущие координаты (y)
		Vx,					// текущая скорость по x
		Vy,					// текущая скорость по y
		V,					// скорость
		m,					// масса космического аппарата
		RealTime,			// для таймера
		TimerOn,			// для таймера
		mX, mT,				// масштабные множетели
		Fdrag,				// сила лобового сопротивления
		startPositionX,		// начальная позиция по координате x
		startPositionY,		// начальная позиция по координате y
		startPositionXA,	// начальная позиция по координате x для случая А
		startPositionYA,	// начальная позиция по координате y для случая А
		startPositionXB,	// начальная позиция по координате x для случая Б
		startPositionYB;	// начальная позиция по координате y для случая Б
	double ActiveTime;		// время работы тормозных двигателей
	double H0Real;			// начальная Высота над Землей реальная
	double H0;				// начальная Высота над Землей масштабная
	double V0;				// начальная скорость
	double dt;				// дельта-t
	bool enableTime;		// включены ли двигатели
	bool ifMainGraf, ifUGraf, ifTGraf, ifEGraf, ifVGraf;	// отрисовывать ли

	// Dialog Data
	enum { IDD = IDD_SPACESHIP_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


	// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();						// вызывается при инициализации диалогового окна
	afx_msg void OnPaint();								// вызывается при событии рисования
	afx_msg void DrawEarth(CDC *pDc, CRect r);			// нарисовать Землю с осями координат
	afx_msg void DrawShip(CDC *pDc, CRect r);			// нарисовать космический аппарат
	afx_msg void DrawShipTraectory(CDC *pDc, CRect r);	// нарисовать траекторию (продолжение траектории)
	afx_msg void DrawUGraf(CDC *pDc, CRect r);			// для рисования графика потенциальной энергии
	afx_msg void DrawTGraf(CDC *pDc, CRect r);			// для рисования графика кинетической энергии
	afx_msg void DrawEGraf(CDC *pDc, CRect r);			// для рисования графика скорости от времени
	afx_msg void DrawVGraf(CDC *pDc, CRect r);
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()								// для таблицы откликов на сообщения
public:
	afx_msg void OnBnClickedStart();					// вызывается при событии нажатия на кнопку Старт
	afx_msg void OnTimer(UINT nIDEvent);				// вызывается на каждый "тик" таймера
	afx_msg void OnBnClickedStop();						// вызывается при событии нажатия на кнопку Стоп
	afx_msg void OnBnClickedButton1();					// вызывается при событии нажатия на кнопку Включить тормозные двигатели
	void SendParameters();								// расчёт параметров

	double f(double t, double x, double y, double vx, double vy);			// для 2 закона Ньютона в 1 и 2 случае для x
	double g(double t, double x, double y, double vx, double vy);			// для 2 закона Ньютона в 1 и 2 случае для y
	RKresult RKMethod(double t, double x, double y, double vx, double vy);	// метод Рунге-Кутта для 1 и 2 случая
public:
	double curVx;
public:
	double curVy;
public:
	double k;
	afx_msg void OnBnClickedA();						// вызывается при событии нажатия на кнопку а)
	afx_msg void OnBnClickedB();						// вызывается при событии нажатия на кнопку б)
};
