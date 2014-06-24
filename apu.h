#pragma once


#define FC4STEP1	7456  //3728 * 2 cpu cycles
#define FC4STEP2	14912 //7456 * 2
#define FC4STEP3	22370 //11185 * 2
#define FC4STEP4	29828 //14914 * 2

#define FC5STEP1	7456  //3728 * 2 cpu cycles
#define FC5STEP2	14912 //7456 * 2
#define FC5STEP3	22370 //11185 * 2
#define FC5STEP4	29828 //14914 * 2
#define FC5STEP5	37280 //18640 * 2

#define CHANNEL_SQUARE1		0
#define CHANNEL_SQUARE2		1
#define CHANNEL_TRIANGLE	2
#define CHANNEL_NOISE		3
#define CHANNEL_DMC			4


struct lenCounter{
	bool enabled;
	bool halted;
	Uint16 currentVal;
	Uint16 length;
};

struct envelope{
	bool startFlag;
	bool disableDecay;
	bool loop;
	Uint8 dividerPeriod;
	Uint8 dividerCounter;
	Uint8 counter;
	Uint8 constVol;
};

struct sweep{
	bool enabled;
	bool reload;
	Uint8 dividerPeriod;
	Uint8 dividerCounter;
	bool negate;
	Uint8 shift;
	Uint16 targetPeriod;
};

class apu
{
public:
	Uint8 reg[0x16];
	Uint32 curCycle;
	lenCounter lc[5];
	Uint16 channelPeriod[5];
	Uint8 vol[5];
	Uint8 lcLoadValue[0x20];
	Uint8 dutyCycle[4][8];
	Uint8 triCycle[32];
	Uint16 noiseLen[16];
	Uint16 dmcRate[16];

	apu(void);
	~apu(void);

	void init();
	void reset();
	void runCatchUp(unsigned int cycle);
	
	Uint8 readReg(Uint8 address);
	void writeReg(Uint8 address, Uint8 data);


	//sq1
	envelope sq1Env;
	sweep sq1Sweep;
	Uint8 sq1Duty;
	Uint8 sq1SeqCounter;
	Uint16 sq1Timer;
	void write4000(Uint8 data);
	void write4001(Uint8 data);
	void write4002(Uint8 data);
	void write4003(Uint8 data);

	//sq2
	envelope sq2Env;
	sweep sq2Sweep;
	Uint8 sq2Duty;
	Uint8 sq2SeqCounter;
	Uint16 sq2Timer;
	void write4004(Uint8 data);
	void write4005(Uint8 data);
	void write4006(Uint8 data);
	void write4007(Uint8 data);

	//triangle
	lenCounter linearCounter;
	void write4008(Uint8 data);
	void write400A(Uint8 data);
	void write400B(Uint8 data);
	
	//noise
	envelope noiseEnv;
	bool noiseModeFlag;
	Uint16 shiftReg;
	void write400C(Uint8 data);
	void write400E(Uint8 data);
	void write400F(Uint8 data);
	void shiftNoiseReg();

	//DMC
	bool irqEnabled;
	bool dmcLoop;
	Uint8 dmcCounter;
	Uint8 dmcOutPutRate;
	Uint16 sampleAddress;
	Uint16 sampleLength;
	Uint16 curAddress;
	Uint8 sampleBuffer;
	Uint8 bitsRemaining;
	bool dmcSilence;
	Uint16 dmcPeriodCounter;
	bool newDMCCycle;
	double dmcCounterAcc;
	void write4010(Uint8 data);
	void write4011(Uint8 data);
	void write4012(Uint8 data);
	void write4013(Uint8 data);

	Uint8 apuBuffer[5][APU_BUFFER_SIZE];
	Uint16 apuBufferCounter;
	Uint16 apuBufferFilled;
	double bufferFillClock;
	double apuAccAR[256];
	double apuCounterAcc[5];

	//status
	bool dmcEnabled;
	bool signalDMC;
	Uint16 dmcBytes;

	void write4015(Uint8 data);
	Uint8 read4015();

	bool fcMode5Step;
	bool signalIRQ;
	bool fcInterruptDisable;
	Sint16 fcCycleCounter;
	void write4017(Uint8 data);
	
	void clockFC1();
	void clockFC2();
	void clockLC();
	void clockSweep1();
	void clockSweep2();
	void clockEnv(envelope &e);
	void clockLinear();
	void resetCycleCount();

	void clockSq1Timer();
	void clockSq2Timer();
	void clockDMC();
	void fillAPUBuffer();

	Uint8 envVol(envelope e);
    
    void saveState(fstream* statefile);
    void loadState(fstream* statefile);
};

