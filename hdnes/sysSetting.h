#pragma once
#include "StdAfx.h"
using namespace std;

class sysSetting
{
private:
	bool loadSetting(void);
	void loadDefaultSetting();
	void loadLine(string pline);
	void saveSetting();
public:
	sysSetting(void);
	~sysSetting(void);

	string exeDir;
	string gamePath;
	string progDir;
	string logDir;
	string logName;
	Uint32 version;

	Uint32 debugVal;
};

