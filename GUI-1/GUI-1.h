
// GUI-1.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CGUI1App:
// See GUI-1.cpp for the implementation of this class
//

class CGUI1App : public CWinApp
{
public:
	CGUI1App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CGUI1App theApp;