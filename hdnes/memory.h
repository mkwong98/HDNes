#pragma once
using namespace std;
//control read or write to all internal memory

class memory
{
public:
	Uint8 cpuRAM[0x800];	
	Uint8 sprRAM[0x100];
	Uint8 sprRAM2[32];
	Uint8 nameTable[4][0x3C0];
	Uint8 nameTableMirroring[2][2];
	Uint8 attributeTable[4][64];
	Uint8 paletteTable[8][4];
	Uint8 bgColourID;

	memory(void);
	~memory(void);

	Uint8 cpuBusRead(Uint16 address);
	Uint8 cpuBusRead(Uint16 address, bool opRead);
	void cpuBusWrite(Uint16 address, Uint8 data);
	void cpuBusInit();

	Uint8 ppuBusRead(Uint16 address);
	void ppuBusWrite(Uint16 address, Uint8 data);
    
    void saveState(fstream* statefile);
    void loadState(fstream* statefile);

};

