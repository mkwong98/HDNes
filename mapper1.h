#pragma once
#include "mapper.h"

//mmc1
class mapper1 :
	public mapper
{
private:
	Uint8 writeRegBuffer;
	Uint8 writeNum;
	Uint8 reg[4];

	boolean chr8KMode;
	boolean prg32KMode;
	boolean slotCSwap;
	Uint8 chrReg0;
	Uint8 chrReg1;
	boolean wramDisable;
	Uint8 prgReg;
	Uint32 lastPrgRead;

	Uint8* chrPtr[2];
	Uint8* prgPtr[2];

	void setMirroring();
	void setBankSwitching();

	void writeReg0(Uint8 data);
	void writeReg1(Uint8 data);
	void writeReg2(Uint8 data);
	void writeReg3(Uint8 data);
public:
	mapper1(void);
	~mapper1(void);

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

