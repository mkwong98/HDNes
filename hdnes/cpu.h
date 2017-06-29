#pragma once

using namespace std;

typedef void(cpu::*opcode)();

class cpu
{
private:
	//commited cpu state
	Uint16 regPC;
	Uint8 regSP;
	Uint8 regA;
	Uint8 regX;
	Uint8 regY;
	bool flagC;
	bool flagZ;
	bool flagI;
	bool flagD;
	bool flagV;
	bool flagN;
	Uint32 curCycle;
	bool hasIRQ;

	//temp cpu state
	Uint32 _curCycle;

	bool dmaSkip;
	Uint8 oddEvenFlag;
	Uint8 op;

	//ADC
	void opcode69();
	void opcode65();
	void opcode75();
	void opcode6D();
	void opcode7D();
	void opcode79();
	void opcode61();
	void opcode71();
	void opADC(Uint8 value);

	//AND
	void opcode29();
	void opcode25();
	void opcode35();
	void opcode2D();
	void opcode3D();
	void opcode39();
	void opcode21();
	void opcode31();
	void opAND(Uint8 value);

	//ASL
	void opcode0A();
	void opcode06();
	void opcode16();
	void opcode0E();
	void opcode1E();
	void opASL(Uint16 address);

	//BIT
	void opcode24();
	void opcode2C();
	void opBIT(Uint8 value);

	//Branch
	void opcode10();
	void opcode30();
	void opcode50();
	void opcode70();
	void opcode90();
	void opcodeB0();
	void opcodeD0();
	void opcodeF0();
	void opBranch(bool doBranch);

	//BRK
	void opcode00();

	//CMP
	void opcodeC9();
	void opcodeC5();
	void opcodeD5();
	void opcodeCD();
	void opcodeDD();
	void opcodeD9();
	void opcodeC1();
	void opcodeD1();
	void opCMP(Uint8 value);

	//CPX
	void opcodeE0();
	void opcodeE4();
	void opcodeEC();
	void opCPX(Uint8 value);

	//CPY
	void opcodeC0();
	void opcodeC4();
	void opcodeCC();
	void opCPY(Uint8 value);

	//DEC
	void opcodeC6();
	void opcodeD6();
	void opcodeCE();
	void opcodeDE();
	void opDEC(Uint16 address);

	//DOP
	void opcode04();
	void opcode14();
	void opcode34();
	void opcode44();
	void opcode54();
	void opcode64();
	void opcode74();
	void opcode80();
	void opcode82();
	void opcode89();
	void opcodeC2();
	void opcodeD4();
	void opcodeE2();
	void opcodeF4();

	//EOR
	void opcode49();
	void opcode45();
	void opcode55();
	void opcode4D();
	void opcode5D();
	void opcode59();
	void opcode41();
	void opcode51();
	void opEOR(Uint8 value);

	//Flag
	void opcode18();
	void opcode38();
	void opcode58();
	void opcode78();
	void opcodeB8();
	void opcodeD8();
	void opcodeF8();

	//INC
	void opcodeE6();
	void opcodeF6();
	void opcodeEE();
	void opcodeFE();
	void opINC(Uint16 address);

	//JMP
	void opcode4C();
	void opcode6C();
	void opJMP(Uint16 address);

	//JSR
	void opcode20();

	//LDA
	void opcodeA9();
	void opcodeA5();
	void opcodeB5();
	void opcodeAD();
	void opcodeBD();
	void opcodeB9();
	void opcodeA1();
	void opcodeB1();
	void opLDA(Uint8 value);

	//LDX
	void opcodeA2();
	void opcodeA6();
	void opcodeB6();
	void opcodeAE();
	void opcodeBE();
	void opLDX(Uint8 value);

	//LDY
	void opcodeA0();
	void opcodeA4();
	void opcodeB4();
	void opcodeAC();
	void opcodeBC();
	void opLDY(Uint8 value);

	//LSR
	void opcode4A();
	void opcode46();
	void opcode56();
	void opcode4E();
	void opcode5E();
	void opLSR(Uint16 address);

	//NOP
	void opcode1A();
	void opcode3A();
	void opcode5A();
	void opcode7A();
	void opcodeDA();
	void opcodeEA();
	void opcodeFA();

	//ORA
	void opcode09();
	void opcode05();
	void opcode15();
	void opcode0D();
	void opcode1D();
	void opcode19();
	void opcode01();
	void opcode11();
	void opORA(Uint8 value);

	//Register
	void opcodeAA();
	void opcode8A();
	void opcodeCA();
	void opcodeE8();
	void opcodeA8();
	void opcode98();
	void opcode88();
	void opcodeC8();

	//ROL
	void opcode2A();
	void opcode26();
	void opcode36();
	void opcode2E();
	void opcode3E();
	void opROL(Uint16 address);

	//ROR
	void opcode6A();
	void opcode66();
	void opcode76();
	void opcode6E();
	void opcode7E();
	void opROR(Uint16 address);

	//RTI
	void opcode40();

	//RTS
	void opcode60();

	//SBC
	void opcodeE9();
	void opcodeE5();
	void opcodeF5();
	void opcodeED();
	void opcodeFD();
	void opcodeF9();
	void opcodeE1();
	void opcodeF1();
	void opSBC(Uint8 value);

	//STA
	void opcode85();
	void opcode95();
	void opcode8D();
	void opcode9D();
	void opcode99();
	void opcode81();
	void opcode91();
	void opSTA(Uint16 address);

	//Stack
	void opcode9A();
	void opcodeBA();
	void opcode48();
	void opcode68();
	void opcode08();
	void opcode28();

	//STX
	void opcode86();
	void opcode96();
	void opcode8E();
	void opSTX(Uint16 address);

	//STY
	void opcode84();
	void opcode94();
	void opcode8C();
	void opSTY(Uint16 address);

	//TOP triple NOP
	void opcode0C();
	void opcode1C();
	void opcode3C();
	void opcode5C();
	void opcode7C();
	void opcodeDC();
	void opcodeFC();
	void opcodeTOP();

	//unknown opcode
	void opcodeXX();

	Uint8 getStatusWord();
	void pushStack(Uint8 data);
	Uint8 popStack();


public:
	cpu(void);
	~cpu(void);
	void init();
	void reset();
	void runClock();
	void runCode();
	void runNMI();
	void runIRQ();
	void setIRQ();
	void runDMA();
	unsigned int getCodeRunCycle();
	void resetCycleCount();

	bool runLog;
	ofstream myfile;

	void DecodeInstruction (Uint16 Addr, char *str1);

    void saveState(fstream* statefile);
    void loadState(fstream* statefile);


};

