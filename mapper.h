#include "stdafx.h"
#pragma once
class mapper
{
public:
	mapper(void);
	~mapper(void);
    
    virtual void runCatchUp(unsigned int cycle) = 0;
	virtual void resetCycleCount() = 0;
	virtual void writeCPUData(Uint16 address, Uint8 data) = 0;
	virtual Uint8 readCPUData(Uint16 address, bool opRead) = 0;
	virtual void writePPUData(Uint16 address, Uint8 data) = 0;
	virtual Uint8 readPPUData(Uint16 address) = 0;
	virtual Uint8 getTilePalette(Uint8 tableX, Uint8 tableY, Uint8 tileX, Uint8 tileY);
	virtual void getPattern(Uint16 address, Uint8 row, bool isFirst, Uint8& data, Uint32& patternAddress, Uint32& ramAddress) = 0;
    virtual void saveState(fstream* statefile) = 0;
    virtual void loadState(fstream* statefile) = 0;

};
