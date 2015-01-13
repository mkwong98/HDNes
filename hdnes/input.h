#pragma once

#define BUTTON_A		0
#define BUTTON_B		1
#define BUTTON_SELECT	2
#define BUTTON_START	3
#define BUTTON_UP		4
#define BUTTON_DOWN		5
#define BUTTON_LEFT		6
#define BUTTON_RIGHT	7

#define BUTTON_COUNT	8

#define SETTING_SCREENCAP	0
#define SETTING_END_EMU		1
#define SETTING_SAVE_STATE  2
#define SETTING_LOAD_STATE  3

#define SETTING_PAUSE		4
#define SETTING_RUN_FRAME   5
#define SETTING_CAP_DATA    6
#define SETTING_CONT_CAP    7

#define SETTING_COUNT		8

struct button{
	bool recordedState;
	bool currentState;
	SDL_Scancode assignedKey;
};

class input
{
public:
	button controller[2][BUTTON_COUNT];
	button setting[SETTING_COUNT];
	Uint8 currentRead1P;
	Uint8 currentRead2P;
	bool readReady;

	input(void);
	~input(void);
	void Init();
	void handleEvent(SDL_Event event);
	button* findKeyButton(SDL_Scancode key);
	int findSettingButton(SDL_Scancode key);
    
	Uint8 readReg(Uint8 address);
	void writeReg(Uint8 address, Uint8 data);

	//config settings
	void readConfig(string value);
	void saveConfig(fstream* inifile);
};

