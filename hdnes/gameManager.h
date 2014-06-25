#pragma once

using namespace std;

class gameManager
{
private:
	bool initialize();
	void cleanup();
	float clockRatio;

public:
	gameManager();
	~gameManager(void);

	void start();
    void saveState();
    void loadState();
    
	bool continuePlay;
    bool saveStateFlag;
    bool loadStateFlag;
	Sint8 pauseFrame;
	Sint8 waitPauseCommand;
};

