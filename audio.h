#pragma once
#include "stdafx.h"

extern void fill_audio(void *data,Uint8 *stream,int len);
extern void setReadyResumeLastMusic(int channel);

struct musicCondition{
	Uint8 opTypeL;
	Uint16 operandL;
	Uint8 opTypeR;
	Uint16 operandR;
	Uint8 operatorC;
};

struct musicPiece{
	Uint8 priority;
	Uint16 ramAddress;
	bool hasCheck;
	Uint8 checkValue;
	bool hasReplace;
	Uint8 replaceValue;
	Uint8 playType;
	Sint16 mp3Idx;
	Sint16 mp3Idx2;
	string conditions;
	vector<musicCondition> conlist;
	bool gotoNext;

};


class audio
{
public:
	double clockPerSample;
	double step[5];
	double lastFreq[5];

	void init();
	audio(void);
	~audio(void);


    vector<musicPiece> musicList;
    vector<string> mp3List;
	void ReadAudioPack();
	void SaveAudioPack();
	void CleanAudioPack();

	bool usePack;
	Sint16 playingMP3;
	vector<Mix_Chunk *> music;
    int playingChannel;
	bool readyResumeLastMusic;
	Uint8 handleRAMWrite(Uint16 address, Uint8 data);
	void resumeLastMusic();

	//config settings
	void readConfig(string value);
	void saveConfig(fstream* inifile);
	void compileCondition(musicPiece& m);
};

