// SpaceShipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpaceShip.h"
#include "SpaceShipDlg.h"
#include "stdlib.h"

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ifREarth (REarth <= sqrt(xKoorShip*xKoorShip + yKoorShip*yKoorShip) - 2*mX)		// условие, в полете тело или нет
#define ifRAtmosphere (HAtm >= sqrt(xKoorShip*xKoorShip + yKoorShip*yKoorShip) - 2*mX)	// условие, вошли ли в атмосферу


const double M = 5.98E24;			// масса Земли
const double REarth = 6371000;		// радиус Земли
const double G = 6.674E-11;			// гравитационная постоянная
const double grav = 9.87;			// ускорение свободного падения на поверхнсти Земли
const double P0 = 1.225;			// давление воздуха у поверхности Земли (кг/м^3)
const double R = 8.31446261815324;	// универсальная газовая постоянная (Дж/(моль*К))
const double T = 223;				// температура по Кельвину
const double Mair = 0.02898;		// молярная масса воздуха (кг/моль)

double k1 = 0,						// отвечает за часть формулы, связанной с рботой двигателя
	k2 = 0;							// отвечает за часть формулы, связанной с атмосферой

// Конструктор
SpaceShipDlg::SpaceShipDlg(CWnd* pParent)
: CDialog(SpaceShipDlg::IDD, pParent)
, H0Real(300000)					// м
, V0(7700)							// м/с
, mX(30 * 1000)
, dt(-2.7217616353373391)			//dt = (0.001 - 0.0015) * 2 * M_PI*(REarth + H0Real) / V0;
, ntimeout(10)
, V(0)
, H(300000)
, mT(2)
, m(100)
, Fdrag(120)
, ifTGraf(TRUE)
, ifEGraf(TRUE)
, ifVGraf(TRUE)
, ifMainGraf(TRUE)
, TimerOn(0)
, ActiveTime(1)
, enableTime(FALSE)
, curVx(0)
, curVy(0)
, startPositionX(0)
, startPositionY(0)
, startPositionXA(0)
, startPositionYA(0)
, startPositionXB(6371000 + 3000000)
, startPositionYB(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// Для изменения отображаемых данных
void SpaceShipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);				// родительская функция
	DDX_Text(pDX, IDC_HEIGHT, H0Real);			// DDX - это реализация функций обмена данными с диалоговым окном. Работает на основе связи переменной и идентификатора элемента управления в окне
	DDX_Text(pDX, IDC_V0, V0);
	DDX_Text(pDX, IDC_V, V);
	DDX_Text(pDX, IDC_H, H);
	DDX_Text(pDX, IDC_DT, dt);
	DDX_Text(pDX, IDC_ACTIVE_TIME, ActiveTime);
	DDX_Text(pDX, IDC_VXY, TimerOn);
	DDX_Text(pDX, IDC_EDITK, Fdrag);
}

BEGIN_MESSAGE_MAP(SpaceShipDlg, CDialog)		// таблица откликов на сообщения. BEGIN_MESSAGE_MAP(Класс реагирующий, Класс родитель)
	ON_WM_PAINT()													// отрисовка
	ON_WM_QUERYDRAGICON()

	ON_BN_CLICKED(IDC_START, &SpaceShipDlg::OnBnClickedStart)		// нажатие на кнопку Старт
	ON_BN_CLICKED(IDC_STOP, &SpaceShipDlg::OnBnClickedStop)			// нажатие на кнопку Стоп
	ON_WM_TIMER()													// "тик" таймера
	ON_BN_CLICKED(IDC_TIMER_ON, &SpaceShipDlg::OnBnClickedButton1)	// нажатие на кнопку Включить тормозные двигатели
	ON_BN_CLICKED(IDC_A, &SpaceShipDlg::OnBnClickedA)				// нажатие на кнопку а)
	ON_BN_CLICKED(IDC_B, &SpaceShipDlg::OnBnClickedB)				// нажатие на кнопку б)
END_MESSAGE_MAP()


// SpaceShipDlg message handlers

// Инициализация окна
BOOL SpaceShipDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Для того, чтобы космический аппарат при старте программы был в указанном месте
	startPositionY = H0Real + H;
	startPositionYA = H0Real + H;
	startPositionYB = H0Real + H;

	// Главное окно
	frameWnd = GetDlgItem(IDC_MAINGRAF);
	frameDc = frameWnd->GetDC();
	frameWnd->GetClientRect(&rect);

	pMemDc.CreateCompatibleDC(frameDc);
	bmp.CreateCompatibleBitmap(frameDc, rect.Width(), rect.Height());
	tmp = pMemDc.SelectObject(&bmp);
	//

	// График потенциальной энергии
	frameWnd = GetDlgItem(IDC_U_GRAF);
	UDc = frameWnd->GetDC();
	frameWnd->GetClientRect(&Urect);

	UpMemDc.CreateCompatibleDC(UDc);
	Ubmp.CreateCompatibleBitmap(UDc, Urect.Width(), Urect.Height());
	Utmp = UpMemDc.SelectObject(&Ubmp);
	//

	// График кинетической энергии
	frameWnd = GetDlgItem(IDC_T_GRAF);
	TDc = frameWnd->GetDC();
	frameWnd->GetClientRect(&Trect);

	TpMemDc.CreateCompatibleDC(TDc);
	Tbmp.CreateCompatibleBitmap(TDc, Trect.Width(), Trect.Height());
	Ttmp = TpMemDc.SelectObject(&Tbmp);
	//

	// График полной энергии
	frameWnd = GetDlgItem(IDC_E_GRAF);
	EDc = frameWnd->GetDC();
	frameWnd->GetClientRect(&Erect);

	EpMemDc.CreateCompatibleDC(EDc);
	Ebmp.CreateCompatibleBitmap(EDc, Erect.Width(), Erect.Height());
	Etmp = EpMemDc.SelectObject(&Ebmp);
	//

	// График скорости от времени
	frameWnd = GetDlgItem(IDC_V_GRAF);
	VDc = frameWnd->GetDC();
	frameWnd->GetClientRect(&Vrect);

	VMemDc.CreateCompatibleDC(VDc);
	Vbmp.CreateCompatibleBitmap(VDc, Vrect.Width(), Vrect.Height());
	Vtmp = VMemDc.SelectObject(&Vbmp);
	//

	UpdateData(TRUE);				// обновить информацию
	H0 = H;							// высота
	HAtm = 170000 + REarth;			// граница атмосферы

	xKoorShip = startPositionXA;	// задание начальной координаты по x
	yKoorShip = startPositionYA;	// задание начальной координаты по y
	Vx = V;							// задание начальной скорости по x
	Vy = 0;							// задание начальной скорости по y
	RealTime = 0;					// текущее время

	oldxKoorShip = startPositionXA;	// предыдущие координаты в начальный момент времени должны совпадать с текущими
	oldyKoorShip = startPositionYA;	// предыдущие координаты в начальный момент времени должны совпадать с текущими

	OnBnClickedA();					// по умолчанию выбирается вариант а)

	return TRUE;					// return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

// Обработка события рисования
void SpaceShipDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();

		// Отрисовка траектории
		DrawShipTraectory(&pMemDc, rect);
		frameDc->BitBlt(0, 0, rect.Width(), rect.Height(), &pMemDc, 0, 0, SRCCOPY);

		// Отрисовка графиков энергий
		DrawUGraf(&UpMemDc, Urect);
		UDc->BitBlt(0, 0, Urect.Width(), Urect.Height(), &UpMemDc, 0, 0, SRCCOPY);
		DrawTGraf(&TpMemDc, Trect);
		TDc->BitBlt(0, 0, Trect.Width(), Trect.Height(), &TpMemDc, 0, 0, SRCCOPY);
		DrawEGraf(&EpMemDc, Erect);
		EDc->BitBlt(0, 0, Erect.Width(), Erect.Height(), &EpMemDc, 0, 0, SRCCOPY);

		// Отрисовка графика зависимости скорости от времени
		DrawVGraf(&VMemDc, Vrect);
		VDc->BitBlt(0, 0,Vrect.Width(), Vrect.Height(), &VMemDc, 0, 0, SRCCOPY);

		// Отрисовка планеты и корабля
		DrawEarth(frameDc, rect);
		DrawShip(frameDc, rect);
	}
}

// Отрисовка траектории
void SpaceShipDlg::DrawShipTraectory(CDC *pDc, CRect r)
{
	// Определение центра окна, где будем рисовать орбиту
	xCenter = (int)((r.Width())*0.5);
	yCenter = (int)((r.Height())*0.5);

	if (ifMainGraf)
	{
		pDc->Rectangle(&r);
		pDc->MoveTo(xCenter + oldxKoorShip / mX, int(yCenter - oldyKoorShip / mX));
		ifMainGraf = FALSE;
	}

	pen.CreatePen(2, 1, RGB(120, 120, 120));
	oldpen = pDc->SelectObject(&pen);

	pDc->LineTo((int)(xKoorShip / mX) + xCenter, (int)(-yKoorShip / mX) + yCenter);	// к короблю

	pDc->SelectObject(oldpen);
	pen.DeleteObject();
}

// Отрисовка Планеты с Осями
void SpaceShipDlg::DrawEarth(CDC *pDc, CRect r)
{
	pen.CreatePen(2, 1, RGB(167, 167, 167));
	oldpen = pDc->SelectObject(&pen);

	// Оси
	pDc->MoveTo(r.left, yCenter);
	pDc->LineTo(r.right, yCenter);
	pDc->MoveTo(xCenter, r.top);
	pDc->LineTo(xCenter, r.bottom);

	pDc->SelectObject(oldpen);
	pen.DeleteObject();

	brush.CreateSolidBrush(RGB(50, 120, 255));
	oldbrush = pDc->SelectObject(&brush);

	// Замля
	pDc->Ellipse(xCenter - REarth / mX,
		yCenter - REarth / mX,
		xCenter + REarth / mX,
		yCenter + REarth / mX);

	pDc->SelectObject(oldbrush);	// возврат старой кисти
	brush.DeleteObject();

	pDc->MoveTo(xCenter, yCenter);
}

// Отрисовка космического аппарата
void SpaceShipDlg::DrawShip(CDC *pDc, CRect r)
{
	int RShip = 2;	// размеры космического аппарата
	if (ifRAtmosphere) brush.CreateSolidBrush(RGB(0, 255, 0));
	else brush.CreateSolidBrush(RGB(255, 0, 0));
	oldbrush = pDc->SelectObject(&brush);

	// Рисуем космический аппарат
	pDc->Ellipse((int)(xKoorShip / mX - RShip + xCenter),
		(int)(-yKoorShip / mX - RShip + yCenter),
		(int)(xKoorShip / mX + RShip + xCenter),
		(int)(-yKoorShip / mX + RShip + yCenter));

	pDc->SelectObject(oldbrush);
	brush.DeleteObject();
}

// Отрисовка графика скорости от времени
void SpaceShipDlg::DrawVGraf(CDC *pDc, CRect r)
{
	int VyCenter = r.Height() - 1;
	double coef = (r.Height() / V0) * 0.8;

	if (ifVGraf)
	{
		pDc->Rectangle(&r);

		pDc->MoveTo(0, VyCenter);
		pDc->LineTo(r.right, VyCenter);

		pDc->TextOutW(2, 2, _T("Скорость"));
		pDc->TextOutW(r.right - 42, VyCenter - 18, _T("время"));

		ifVGraf = FALSE;
	}

	pDc->MoveTo(1, 0);
	pDc->LineTo(1, r.bottom);

	if (osiV >= r.Width()*mT)
	{
		osiV = 0;
		pDc->Rectangle(&r);

		pDc->MoveTo(0, VyCenter);
		pDc->LineTo(r.right, VyCenter);

		pDc->TextOutW(2, 2, _T("Скорость"));
		pDc->TextOutW(r.right - 42, VyCenter - 18, _T("время"));
	}

	// Рисуем точку в соответствующем месте
	//pDc->SetPixel(int(osiV / mT), int((V / 1000) * 10) - r.Height()/2, RGB(0, 0, 255));
	pDc->SetPixel(int(osiV / mT), r.Height() - int(V * coef), RGB(0, 0, 255));

	pDc->SelectObject(oldpen);
	pen.DeleteObject();
}

// Отрисовка графика потенциальной энергии
void SpaceShipDlg::DrawUGraf(CDC *pDc, CRect r)
{
	int UyCenter = r.Height() - 1;
	double coefU = r.Height() / (H0Real * 10);	// *10, чтобы был нормальный график

	if (ifUGraf)
	{
		pDc->Rectangle(&r);

		pDc->MoveTo(0, UyCenter);			// горизонтальная ось
		pDc->LineTo(r.right, UyCenter);


		pDc->TextOutW(2, 2, _T("Потенциальная энергия"));				// вывод оси "Потенциальная энергия"
		pDc->TextOutW(Urect.right - 42, UyCenter - 18, _T("время"));	// вывод оси "время"

		ifUGraf = FALSE;
	}

	pDc->MoveTo(1, 0);						// вертикальная ось
	pDc->LineTo(1, r.bottom);


	if (osiTU >= r.Width()*mT)				// перерисовать, если график заполнен
	{
		osiTU = 0;
		pDc->Rectangle(&r);

		pDc->MoveTo(0, UyCenter);			// горизонтальная ось
		pDc->LineTo(r.right, UyCenter);

		pDc->TextOutW(2, 2, _T("Потенциальная энергия"));
		pDc->TextOutW(r.right - 42, UyCenter - 18, _T("время"));
	}

	// Рисуем точку в соответствующем месте
	pDc->SetPixel(int(osiTU / mT), int(r.Height() - H*coefU), RGB(0, 0, 255));
	//pDc->SetPixel(int(osiTU / mT), int(abs(coefU)), RGB(0, 0, 255));

	pDc->SelectObject(oldpen);
	pen.DeleteObject();
}

// Отрисовка графика кинетической энергии
void SpaceShipDlg::DrawTGraf(CDC *pDc, CRect r)
{
	int TyCenter = r.Height() - 1;
	double coef = r.Height() / (V0*1.7);	// *1,7 чтоб график начинался чуть выше центра

	if (ifTGraf)
	{
		pDc->Rectangle(&r);

		pDc->MoveTo(0, TyCenter);
		pDc->LineTo(r.right, TyCenter);

		pDc->TextOutW(2, 2, _T("Кинетическая энергия"));
		pDc->TextOutW(r.right - 42, TyCenter - 18, _T("время"));

		ifTGraf = FALSE;
	}

	pDc->MoveTo(1, 0);
	pDc->LineTo(1, r.bottom);

	if (osiTT >= r.Width()*mT)
	{
		osiTT = 0;
		pDc->Rectangle(&r);
		pDc->MoveTo(0, TyCenter);
		pDc->LineTo(r.right, TyCenter);

		pDc->TextOutW(2, 2, _T("Кинетическая энергия"));
		pDc->TextOutW(r.right - 42, TyCenter - 18, _T("время"));
	}

	pDc->SetPixel(int(osiTT / mT), int(r.Height() - abs(V*coef)), RGB(0, 0, 255));

	pDc->SelectObject(oldpen);
	pen.DeleteObject();
}

void SpaceShipDlg::DrawEGraf(CDC *pDc, CRect r)
{
	int EyCenter = r.Height() - 1;

	double Efull_begin = G*M / (H0Real + REarth) - V0*V0 / 2;
	double coef = r.Height() / (Efull_begin*2.5);

	if (ifEGraf)
	{
		pDc->Rectangle(&r);

		pDc->MoveTo(0, EyCenter);
		pDc->LineTo(r.right, EyCenter);

		pDc->TextOutW(2, 2, _T("Полная энергия"));
		pDc->TextOutW(r.right - 42, EyCenter - 18, _T("время"));

		ifEGraf = FALSE;
	}

	pDc->MoveTo(1, 0);
	pDc->LineTo(1, r.bottom);

	if (osiTE >= r.Width()*mT)
	{
		osiTE = 0;
		pDc->Rectangle(&r);
		pDc->MoveTo(0, EyCenter);
		pDc->LineTo(r.right, EyCenter);

		pDc->TextOutW(2, 2, _T("Полная энергия"));
		pDc->TextOutW(r.right - 42, EyCenter - 18, _T("время"));
	}

	double Efull = abs(-G*M / (H + REarth) + V*V / 2);
	pDc->SetPixel(int(osiTE / mT), int(Efull*coef), RGB(0, 0, 255));

	UpdateData(FALSE);
	pDc->SelectObject(oldpen);
	pen.DeleteObject();
}

// The system calls this function to obtain the cursor to displa/ while the user drags
//  the minimized window.
HCURSOR SpaceShipDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Нажатие на кнопку Старт
void SpaceShipDlg::OnBnClickedStart()
{
	UpdateData(TRUE);			// считывание введенных величин

	if (dt > 0)
	{
		MessageBox(L"В нашем случае dt < 0 !!!");
		OnBnClickedStop();
		return;
		
	}

	// Задание начальных значений
	startPositionY = H0Real + REarth;
	startPositionYA = H0Real + REarth;
	startPositionYB = H0Real + REarth;

	TimerOn = 0;
	H0 = H;

	xKoorShip = startPositionX;
	yKoorShip = startPositionY;
	if (V0 == 0)					// чтобы не было ошибок при V0 = 0
	{
		Vx = 0.000001;
	}
	else { Vx = V0; }
	Vy = 0;

	oldxKoorShip = xKoorShip;
	oldyKoorShip = yKoorShip;

	//dt = (0.001 - 0.0015)*2*M_PI*(REarth + H0Real) / V0;
	//

	// Для перерисовки графиков
	osiTU = 0;
	osiTT = 0;
	osiTE = 0;
	osiV = 0;
	ifMainGraf = TRUE;	// очистка от траектории
	ifUGraf = TRUE;		// очистка графика E(пот)
	ifTGraf = TRUE;		// очистка графика E(кин)
	ifEGraf = TRUE;		// очистка графика E(полн)
	ifVGraf = TRUE;
	//

	InvalidateRect(&rect);
	nTimer = SetTimer(ID_TIMER1, ntimeout, NULL);
}

void SpaceShipDlg::OnTimer(UINT nIDEvent)
{
	if (ifREarth)			// если летит над Землей
	{
		SendParameters();

		if (enableTime)		// работает ли двигатель
		{
			TimerOn = TimerOn + double(1) / ntimeout;
			if (TimerOn < ActiveTime)
			{
			}
			else
			{
				enableTime = FALSE;
				TimerOn = 0;
			}
		}

		if (enableTime)	k1 = 1;				// если двигатель запущен
		else k1 = 0;
		if (ifRAtmosphere) k2 = 1;			// если вошли в атмосферу
		else k2 = 0;

		// Применение метода Рунге-Кутта
		RKresult Koor = RKMethod(RealTime, xKoorShip, yKoorShip, Vx, Vy);

		xKoorShip = Koor.x;
		yKoorShip = Koor.y;
		Vx = Koor.Vx;
		Vy = Koor.Vy;
		RealTime = Koor.t;

		oldxKoorShip = Koor.xOld;
		oldyKoorShip = Koor.yOld;

		osiTU = osiTU + 1;
		osiTT = osiTT + 1;
		osiTE = osiTE + 1;
		osiV = osiV + 1;

		V0 = abs(V0);

		UpdateData(FALSE);

		InvalidateRect(&rect); //обновление окна рисования
	}
	else
	{
		H = 0;
		KillTimer(nTimer);
		UpdateData(FALSE);
		ifMainGraf = TRUE;		// очистка
		ifUGraf = TRUE;
		ifTGraf = TRUE;
		ifEGraf = TRUE;
		ifVGraf = TRUE;
	}
}
void SpaceShipDlg::OnBnClickedStop()
{
	ifUGraf = TRUE;
	ifTGraf = TRUE;
	ifEGraf = TRUE;
	ifVGraf = TRUE;
	ifMainGraf = TRUE;
	enableTime = FALSE;
	TimerOn = 0;
	KillTimer(nTimer);
}

void SpaceShipDlg::OnBnClickedButton1()
{
	enableTime = TRUE;
}

void SpaceShipDlg::SendParameters()
{
	V = sqrt(Vx*Vx + Vy*Vy);
	H = (int)(sqrt(xKoorShip*xKoorShip + yKoorShip*yKoorShip) - REarth);

	curVx = Vx;
	curVy = Vy;
	UpdateData(FALSE);
}    

double SpaceShipDlg::f(double t, double x, double y, double vx, double vy)
{
	double h = sqrt(x*x + y*y) - REarth;		// текущая высота над Землёй
	double g = G*M / pow((REarth + h), 2);		// ускорение свободного падения для текущей высоты

	return -G*M / (x*x + y*y)*(x / sqrt(x*x + y*y)) + k1*(0.1*g*vx / sqrt(vx*vx + vy*vy)) - k2*(-Fdrag*P0*exp((-Mair*g*h) / (R*T))*sqrt(vx*vx + vy*vy)*vx);
	
}

double SpaceShipDlg::g(double t, double x, double y, double vx, double vy)
{
	double h = sqrt(x*x + y*y) - REarth;		// текущая высота над Землёй
	double g = G*M / pow((REarth + h), 2);		// ускорение свободного падения для текущей высоты

	return -G*M / (x*x + y*y)*(y / sqrt(x*x + y*y)) + k1*(0.1*g*vy / sqrt(vx*vx + vy*vy)) - k2*(-Fdrag*P0*exp((-Mair*g*h) / (R*T))*sqrt(vx*vx + vy*vy)*vy);
}

RKresult SpaceShipDlg::RKMethod(double t, double x, double y, double vx, double vy)
{
	double k1x, k1y, k2x, k2y, k3x, k3y, k4x, k4y;

	k1x = f(t, x, y, vx, vy)*dt;
	k1y = g(t, x, y, vx, vy)*dt;
	k2x = f(t + dt / 2, x + vx*dt / 2, y + vy*dt / 2, vx + k1x / 2, vy + k1y / 2)*dt;
	k2y = g(t + dt / 2, x + vx*dt / 2, y + vy*dt / 2, vx + k1x / 2, vy + k1y / 2)*dt;
	k3x = f(t + dt / 2, x + vx*dt / 2 + k1x / 4 * dt, y + vy*dt / 2 + k1y / 4 * dt, vx + k2x / 2, vy + k2y / 2)*dt;
	k3y = g(t + dt / 2, x + vx*dt / 2 + k1x / 4 * dt, y + vy*dt / 2 + k1y / 4 * dt, vx + k2x / 2, vy + k2y / 2)*dt;
	k4x = f(t + dt, x + vx*dt + k2x*dt / 2, y + vy*dt + k2y*dt / 2, vx + k3x, vy + k3y)*dt;
	k4y = g(t + dt, x + vx*dt + k2x*dt / 2, y + vy*dt + k2y*dt / 2, vx + k3x, vy + k3y)*dt;

	double tNew = t + dt;
	double xNew = x + vx*dt + ((k1x + k2x + k3x) / 6)*dt;
	double yNew = y + vy*dt + ((k1y + k2y + k3y) / 6)*dt;
	double vxNew = vx + (k1x + 2 * k2x + 2 * k3x + k4x) / 6;
	double vyNew = vy + (k1y + 2 * k2y + 2 * k3y + k4y) / 6;

	RKresult koor4(tNew, xNew, yNew, vxNew, vyNew);
	return koor4;
}

void SpaceShipDlg::OnBnClickedA()
{
	// Чтобы перерисовались графики и остановилось выполнение, если запущено
	ifUGraf = TRUE;
	ifTGraf = TRUE;
	ifEGraf = TRUE;
	ifVGraf = TRUE;
	ifMainGraf = TRUE;
	enableTime = FALSE;
	TimerOn = 0;
	KillTimer(nTimer);

	// Считываем дынные
	UpdateData(TRUE);

	// Начальное положение
	startPositionY = REarth + H0;
	startPositionYA = REarth + H0;
	startPositionYB = REarth + H0;

	startPositionX = startPositionXA;
	startPositionY = startPositionYA;
	xKoorShip = startPositionX;
	yKoorShip = startPositionY;
	oldxKoorShip = xKoorShip;
	oldyKoorShip = yKoorShip;

	// Перерисовать
	ifMainGraf = TRUE;
	InvalidateRect(&rect);
}


void SpaceShipDlg::OnBnClickedB()
{
	// Чтобы перерисовались графики и остановилось выполнение, если запущено
	ifUGraf = TRUE;
	ifTGraf = TRUE;
	ifEGraf = TRUE;
	ifVGraf = TRUE;
	ifMainGraf = TRUE;
	enableTime = FALSE;
	TimerOn = 0;
	KillTimer(nTimer);

	// Считываем дынные
	UpdateData(TRUE);

	// Начальное положение
	startPositionY = REarth + H0;
	startPositionYA = REarth + H0;
	startPositionYB = REarth + H0;

	startPositionX = startPositionXB;
	startPositionY = startPositionYB;
	xKoorShip = startPositionX;
	yKoorShip = startPositionY;
	oldxKoorShip = xKoorShip;
	oldyKoorShip = yKoorShip;

	// Перерисовать
	ifMainGraf = TRUE;
	InvalidateRect(&rect);
}
