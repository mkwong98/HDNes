#pragma once
#include "mapper.h"
class mapper4 :public mapper{
private:
	Uint16 chrMask;
	Uint16 chrSwitchMask;
	Uint16 prgSwitchMask;
	Uint8 chrMode;
	Uint8 prgMode;
	Uint8 regAddress;

	Uint8 mapReg[8];
	Uint8* chrPtr[8];
	Uint8* prgPtr[4];
	Uint32 lastPrgRead;

    bool irqEnabled;
    Uint8 irqValue;
    Uint8 irqCounter;
	bool irqFlag;
	int scanlineNo;
    
	void setBankSwitching();
    void setMirroring();

public:
	mapper4(void);
	~mapper4(void);

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

