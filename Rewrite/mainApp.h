#pragma once
#include "common.h"
#include <wx\wx.h>

class mainApp : public wxApp{
public:
	Uint8 initState;
	mainApp(void);
	~mainApp(void);
	bool OnInit();
};
