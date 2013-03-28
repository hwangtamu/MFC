// CkeyButton.cpp : implementation file
//

#include "stdafx.h"
#include "F2 mouse.h"
#include "CkeyButton.h"
#include "F2 mouseDlg.h"

// CkeyButton

IMPLEMENT_DYNAMIC(CkeyButton, CButton)

CkeyButton::CkeyButton()
: m_letter(0)
{

}

CkeyButton::~CkeyButton()
{
}

BEGIN_MESSAGE_MAP(CkeyButton, CButton)
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()

// CkeyButton message handlers

void CkeyButton::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	//MessageBox(_T("hls"));
	
	CButton::OnMouseLeave();
}

void CkeyButton::setLetter(char letter)
{
    m_letter=letter;
}

char CkeyButton::getLetter()
{
	return m_letter;
}
