#pragma once

class cart
{
private:

public:
	string gameName;
	bool romLoaded;

	Uint8 mapperID;
	Uint8 chrPageCount;
	Uint8 prgPageCount;

	bool mirrorV;
	bool scr4x;

	bool useBat;
	bool useTrain;
    bool batChanged;

	Uint8* prgROM;
	Uint8* chrROM;
	Uint8* chrRAM;
	Uint8* batDat;
	Uint8* scr4RAM;
    Uint32* chrRAMAddress;
    Uint32 lastPrgRead;

	cart();
	~cart(void);
	void loadRom(string name);
    void loadBat();
    void saveBat();
	bool getLoadState();
	void clean();
    
    void saveState(fstream* statefile);
    void loadState(fstream* statefile);

};

