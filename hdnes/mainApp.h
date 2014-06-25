#pragma once
#include "stdafx.h"
#include "sysSetting.h"
#include "fraHDNesImp.h"

class mainApp : public wxApp
{
public:
	fraHDNesImp*	mainForm;
	bool initOK;
	mainApp(void);
	~mainApp(void);
	virtual bool OnInit();
};

