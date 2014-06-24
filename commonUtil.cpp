#pragma once
#include "stdafx.h"
#include <vector>
#include <sstream>
#include <Shlwapi.h>
#include "sysState.h"

using namespace std;

vector<string> split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

string removeSpace(const string &s){
    stringstream ss(s);
    string item;
	string result = "";
    while(getline(ss, item, ' ')) {
		result += item;
    }
    return result;
}

string getROMDirPath(){
	CHAR szPath[MAX_PATH];
	romDat->gameName.copy(szPath, MAX_PATH, 0);
	szPath[romDat->gameName.length()] = NULL;
	PathRemoveFileSpecA(szPath);
    return string(szPath);
}

string getROMName(){
	CHAR szPath[MAX_PATH];
	string romName = getHDPackPath();
	romName.copy(szPath, MAX_PATH, 0);
	szPath[romName.length()] = NULL;
	PathStripPathA(szPath);
    return string(szPath);
}

string getHDPackPath(){
	CHAR szPath[MAX_PATH];
	romDat->gameName.copy(szPath, MAX_PATH, 0);
	szPath[romDat->gameName.length()] = NULL;
	PathRemoveExtensionA(szPath);
    return string(szPath);
}

string getEditPackPath(){
    return setting->exeDir + "\\edit\\" + getROMName() + "\\";
}

void writeLog(string s){
 	fstream logfile;

	_mkdir(setting->logDir.c_str());

	logfile.open(setting->logName, ios::out | ios::app);
	if (logfile.is_open()){
		logfile << s + "\n"; 
		logfile.close();
	}
}

string int_to_hex(Uint16 i){
  std::stringstream stream;
  stream << std::hex << i;
  return stream.str();
}