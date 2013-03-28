
// F2 mouseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "F2 mouse.h"
#include "F2 mouseDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CF2mouseDlg dialog



CF2mouseDlg::CF2mouseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CF2mouseDlg::IDD, pParent)
	, mouseflag(FALSE)
	, m_xpos(0)
	, m_ypos(0)
	, m_time(0)
	, m_oldpoint(0)
	, m_tposX(0)
	, m_tposY(0)
	, m_tpos(0,0)
	, m_rawword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CF2mouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_X, m_xpos);
	DDX_Text(pDX, IDC_Y, m_ypos);
	DDX_Text(pDX, IDC_tposX, m_tposX);
	DDX_Text(pDX, IDC_tposY, m_tposY);
	DDX_Control(pDX, IDC_POSTEST1, m_key[0]);
	DDX_Control(pDX, IDC_POSTEST2, m_key[1]);
}

BEGIN_MESSAGE_MAP(CF2mouseDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_POSTEST1, &CF2mouseDlg::OnBnClickedPostest1)
	ON_BN_CLICKED(IDC_POSTEST2, &CF2mouseDlg::OnBnClickedPostest2)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CF2mouseDlg message handlers

BOOL CF2mouseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CF2mouseDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CF2mouseDlg::OnPaint()
{
	if (IsIconic())
	{
		//original part draw mouse cursor
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
		CDialogEx::OnPaint();
	}

	//own part draw curves
	CPaintDC dc(this);
	HBRUSH hB;
	hB=CreateSolidBrush(RGB(0,255,255));
	SelectObject(dc,hB);
	//Rectangle(dc,Startx,Starty,Startx+wid-1,Starty+lon-1);
	DeleteObject(hB);
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CF2mouseDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CF2mouseDlg::OnBnClickedPostest1()
{
	// TODO: Add your control notification handler code here
	//UpdateData();
	GetDlgItem(IDC_POSTEST1)->GetWindowRect(&m_tcontrol);
	m_tpos=m_tcontrol.CenterPoint();
	m_tposX=m_tpos.x;
	m_tposY=m_tpos.y;
	UpdateData(FALSE);
}

void CF2mouseDlg::OnBnClickedPostest2()
{
	// TODO: Add your control notification handler code here
	//UpdateData();
	MessageBox(_T("Hello"));
	UpdateData(FALSE);
}

void CF2mouseDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	StrokePoint spoint;
		/*CDC *pDC=GetDC();
	pDC->MoveTo(m_ptOrigin);
	pDC->LineTo(point) */
    CDC *pdc=GetDC();
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	CPen *pOldPen=pdc->SelectObject(&pen);
    //dc.SetROP2(R2_BLACK);
	if(mouseflag)
	{
		  //record point
	      m_xpos=point.x;
	      m_ypos=point.y;
		  m_time++;
		  spoint.x=m_xpos;
		  spoint.y=m_ypos;
		  spoint.time=m_time;
		  stroke.push_back(spoint);
	      UpdateData(FALSE);
		  
		  //draw gesture
		  pdc->MoveTo(m_oldpoint);
		  pdc->LineTo(point);
		  m_oldpoint=point;
	     // pdc->SelectObject(pOldPen);
	}    
	ReleaseDC(pdc);
	DeleteObject(pOldPen);
	CDialogEx::OnMouseMove(nFlags, point);
}


void CF2mouseDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mouseflag=TRUE;
	m_oldpoint=point;
	CDialogEx::OnLButtonDown(nFlags, point);
}


void CF2mouseDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	mouseflag=FALSE;
	m_xpos=0;
	m_ypos=0;
	UpdateData(FALSE);	
	//clear gesture
	/*
	CDC *pDC=GetDC();
	pDC->SetROP2(R2_NOTXORPEN);
    CPen pen(PS_SOLID,1,RGB(255,0,0));
	CPen *pOldPen=pDC->SelectObject(&pen);
	CPoint tpoint;
	//erase starting point
	m_oldpoint.x=stroke.at(0).x;
	m_oldpoint.y=stroke.at(0).y;
    pDC->MoveTo(m_oldpoint);
	pDC->LineTo(m_oldpoint);
	//erase all
	for(int i=0;i<m_time-1;i++)
	{
		m_oldpoint.x=stroke.at(i).x;
		m_oldpoint.y=stroke.at(i).y;
	    tpoint.x=stroke.at(i+1).x;
		tpoint.y=stroke.at(i+1).y;
		pDC->MoveTo(m_oldpoint);
		pDC->LineTo(tpoint);
	}
	m_time=0;
	stroke.clear();
	ReleaseDC(pDC);
    DeleteObject(pOldPen);*/
	Invalidate(); //InvalidateRgn();
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CF2mouseDlg::getLetter()
{
	//m_key[0].OnMouseLeave();
}