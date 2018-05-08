#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#pragma once
#include "common.h"
#include <wx\wx.h>

#define SDL_MAIN_HANDLED
#include <SDL2\SDL.h>

class hdnesPackEditormainForm;

class main : public wxApp{
public:
    static hdnesPackEditormainForm* mForm;
    static string exeDir;
    static string intToHex(int value);
    static string intToStr(int value);
    static string floatToStr(float value);
    static string paletteToStr(vector<array<Uint8, 4>> p);
    static vector<string> split(const string &s, char delim, vector<string> &elems);
    static void hexToByteArray(const string &s, UINT8* ar);
    static string trim(string pStr);
    static void drawRect(wxImage &img, wxPoint pt, wxPoint rectSize, wxColour c);
    static void drawLine(wxImage &img, wxPoint pt, int len, wxColour c, bool hDir);

	main(void);
	~main(void);
    bool OnInit();
    int OnExit();
};

#endif // MAIN_H_INCLUDED


