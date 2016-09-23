#pragma once
#include "common.h"
#include "wx\wx.h"

class mainApp : public wxApp{
public:
	bool initOK;
	mainApp(void);
	~mainApp(void);
	bool OnInit();
};
