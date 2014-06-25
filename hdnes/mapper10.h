#pragma once
#include "mapper.h"
class mapper10 :public mapper{
private:
	Uint16 chrMask;
	Uint16 chrSwitchMask;
	Uint16 prgSwitchMask;
	Uint8 chrMode[2];
	Uint8 mapReg[6];
	Uint8* prgPtr[4];
	Uint8* chrPtr[2];
	Uint32 lastPrgRead;

	void setMirroring();
	void setBankSwitching();
	void setChrBankSwitching();
	void setChrMode(Uint16 address);

public:
	mapper10(void);
	~mapper10(void);

    void runCatchUp(unsigned int cycle);
    void resetCycleCount();

	void writeCPUData(Uint16 address, Uint8 data);
	Uint8 readCPUData(Uint16 address, bool opRead);
	void writePPUData(Uint16 address, Uint8 data);
	Uint8 readPPUData(Uint16 address);
	
	void getPattern(Uint16 address, Uint8 row, bool isFirst, Uint8& data, Uint32& patternAddress, Uint32& ramAddress);

    void saveState(fstream* statefile);
    void loadState(fstream* statefile);

};

