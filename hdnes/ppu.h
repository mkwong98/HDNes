#pragma once

struct sprite{
	Uint8 y;
	Uint8 x;
	Uint8 patternID;
	Uint8 paletteID;
	bool isBack;
	bool hFlip;
	bool vFlip;
};

class ppu
{
public:
	Uint8 lastRegWrite;

	bool enabled;
	bool signalNMI;
	bool signalFrameReady;
	bool oddFrame;

	Uint16 screenX;
	Uint16 screenY;

	Uint32 curCycle;
	Uint32 frameCount;

	unsigned int writeDisabledPeriod;
	Uint8 reg[8];
	sprite spriteList[64];

	//reg 2000
	Uint8 baseNameTableAddress;
	Uint8 aIncSize;
	Uint16 sprPatternTable;
	Uint16 bgTilePatternTable;
	bool useLargeSpr;
	Uint8 sprHeight;
	bool enableVBlank;
	void write2000(Uint8 data);

	//reg 2001
	bool useGrayscale;
	bool showBGOnLeft;
	bool showSprOnLeft;
	bool showBG;
	bool showSpr;
	bool intensifyR;
	bool intensifyG;
	bool intensifyB;
	void write2001(Uint8 data);

	//reg 2002
	bool sprOverflow;
	bool spr0hit;
	bool spr0hitDone;
	Uint8 spr0PatternData[8][2];
	Uint8 spr0PatternData2[8][2];

	bool vBlankFlag;
	bool oldVBlankFlag;
	Uint8 read2002();

	//reg 2003
	Uint8 oamAddress;
	void write2003(Uint8 data);

	//reg 2004
	void write2004(Uint8 data);
	Uint8 read2004();

	//shared by 2005, 2006
	bool newWrite;
	Uint8 offsetX;
	Uint16 tmpVRAMAddress;
	Uint16 vRAMAddress;

	//reg 2005
	void write2005(Uint8 data);

	//reg 2006
	void write2006(Uint8 data);

	//reg 2007
	void write2007(Uint8 data);
	Uint8 read2007();

	//sprite evaluation
	Uint8 dataToWriteOAM2;
	bool enableWriteOAM2;
	Uint16 spAddressToEval;
	Uint16 oam2AddressToWrite;
	Uint8 spFound;
	bool spEvalStateCheckY;
	bool spYInRange;
	Uint8 spBytesToCopy;

	//tile fretch
	Uint8 bgLoadingY;
	Uint8 bgTileToLoad;
	Uint16 bgFretchNameTableAddress;
	Uint8 bgPatternIDFretched[34];
	Uint8 bgPaletteFretched[34];
	Uint8 bgPatternDataFretched[34][2];
	Uint32 bgAddressFretched[34];
	Uint32 bgRAMAddress[34];

	Uint8 spTileToLoad;
	Uint8 spPatternDataFretched[8][2];
	Uint8 spRowFretched[8];
	Uint32 spAddressFretched[8];
	Uint32 spRAMAddress[8];
	bool isSp0;
	bool lastIsSp0;

	//rendering
	Uint8 currentBgTile;
	Uint8 currentBgX;
	Uint16 currentSpX[8];
	Uint8 tmpSprRAM2[32];

	void runCatchUp(unsigned int cycle);
	void runStep();
	void readSprList();
	Uint16 getSprPatternAddress(Uint8 patternID);

	ppu(void);
	~ppu(void);

	void init();
	void reset();
	void initState();
	void resetCycleCount();

	Uint8 readReg(Uint8 address);
	void writeReg(Uint8 address, Uint8 data);
	

	//4014
	void transferDMA(Uint8 data);
    
    void saveState(fstream* statefile);
    void loadState(fstream* statefile);
	void saveSprObjects(string path);
	void saveVRam(string path);
};

