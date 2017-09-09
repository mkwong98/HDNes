#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#pragma once
#include "common.h"
#include <wx\wx.h>

class hdnesPackEditormainForm;

class main : public wxApp{
public:
    static hdnesPackEditormainForm* mForm;
    static string exeDir;

	main(void);
	~main(void);
    bool OnInit();
};

#endif // MAIN_H_INCLUDED


