#include "StdAfx.h"
#include <fstream>
#include <Shlwapi.h>
#include "sysState.h"



sysSetting::sysSetting(void)
{
	CHAR szPath[MAX_PATH];

    GetModuleFileNameA( NULL, szPath, MAX_PATH );
	PathRemoveFileSpecA(szPath);
	exeDir = string(szPath);

	if(!loadSetting()){
		loadDefaultSetting();
	}
	progDir = exeDir + "\\shader\\";
	logDir = exeDir + "\\log\\";
	

	//create log file name
	char buffer [80];
    time_t timer;
	struct tm * timeinfo;
	
	time(&timer);
	timeinfo = localtime (&timer);
	strftime (buffer,80,"%Y%m%d%H%M%S",timeinfo);
	logName = logDir + buffer + ".log";

}


sysSetting::~sysSetting(void)
{
	saveSetting();
}

bool sysSetting::loadSetting(void){
	fstream inifile;
	string line;

	inifile.open(exeDir + "\\hdnes.ini", ios::in);
	if (inifile.is_open()){
		while ( inifile.good() ){
			std::getline(inifile, line);
			loadLine(line);
		}
		inifile.close();
		return true;
	}
	return false;
}

void sysSetting::loadLine(string pline){
	unsigned found = pline.find(":");
	string token;
	string value;
	if (found!=std::string::npos){
		token = pline.substr (0,found); 
		value = pline.substr (found + 1, std::string::npos);
		if (token.compare("gamePath") == 0){
			gamePath = value;
		}
		if (token.compare("input") == 0){
			inputCore->readConfig(value);
		}
		if (token.compare("video") == 0){
			vid->readConfig(value);
		}
		if (token.compare("audio") == 0){
			mixer->readConfig(value);
		}
        
	}
		
}

void sysSetting::loadDefaultSetting(){
	gamePath = exeDir + "\\";

}

void sysSetting::saveSetting(){
	fstream inifile;

	inifile.open(exeDir + "\\hdnes.ini", ios::out);
	inifile << "gamePath:" + gamePath + "\n";
    inputCore->saveConfig(&inifile);
    vid->saveConfig(&inifile);
    mixer->saveConfig(&inifile);
	inifile.close();
}
