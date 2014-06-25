#pragma once
#include <vector>

using namespace std;

vector<string> split(const string &s, char delim, vector<string> &elems);
string removeSpace(const string &s);
string getROMDirPath();
string getROMName();
string getHDPackPath();
string getEditPackPath();
void writeLog(string s);
string int_to_hex(Uint16 i);