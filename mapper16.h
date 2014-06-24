#pragma once
#include "mapper.h"

#define EEPROM_STANDBY       0
#define EEPROM_STANDBY_END   1
#define EEPROM_RW_SELECT     2
#define EEPROM_WAIT_ADDRESS  3
#define EEPROM_WAIT_DATA     4
#define EEPROM_OUTPUT        5

#define EEPROM_TYPE_UNKNOWN	 0
#define EEPROM_TYPE_256		 1
#define EEPROM_TYPE_128 	 2

class mapper16 :public mapper{
private:
	Uint8 reg[16];
	Uint8* chrPtr[8];
	Uint8* prgPtr[2];
	Uint32 lastPrgRead;

	Uint32 curCycle;
    Uint16 irqCounter;
    bool irqEnabled;
	bool irqFlag;

    Uint8 eepromMode;
    Uint8 eepromLines;
    Uint8 eepromAddress;
    Uint8 bitCounter;
    Uint8 eepromTemp;
    bool eepromIsReading;
	Uint8 eepromRead;
	Uint8 eepromType;
    
	void setBankSwitching();
    void handleEEPROMWrite();
public:
	mapper16(void);
	~mapper16(void);
    
    void runCatchUp(unsigned int cycle);
    void resetCycleCount();

	void writeCPUData(Uint16 address, Uint8 data);
	Uint8 readCPUData(Uint16 address, bool opRead);
	void writePPUData(Uint16 address, Uint8 data);
	Uint8 readPPUData(Uint16 address);
	
	void getPattern(Uint16 address, Uint8 row, bool isFirst, Uint8& data, Uint32& patternAddress, Uint32& ramAddress);
    
    void setMirroring();
    
    void saveState(fstream* statefile);
    void loadState(fstream* statefile);


};

