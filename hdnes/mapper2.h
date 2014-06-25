#pragma once
#include "mapper.h"
class mapper2 :public mapper{
private:
	Uint8 prgReg;
	Uint8* prgPtr[2];
	Uint32 lastPrgRead;

	void setBankSwitching();
public:
	mapper2(void);
	~mapper2(void);
    
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

