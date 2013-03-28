#pragma once

// CkeyButton

class CkeyButton : public CButton
{
	DECLARE_DYNAMIC(CkeyButton)

public:
	char m_letter;
	CkeyButton();
	virtual ~CkeyButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void setLetter(char letter);
    char getLetter();
	afx_msg void OnMouseLeave();
};


