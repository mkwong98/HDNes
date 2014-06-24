#include "StdAfx.h"
#include "sysState.h"

enum ADDRMODE { IMP, ACC, IMM, ADR, ABS, IND, REL, ABX, ABY, ZPG, ZPX, ZPY, INX, INY, ERR, NUM_ADDR_MODES };

enum ADDRMODE TraceAddrMode[256] =
{
	IMM, INX, ERR, INX, ZPG, ZPG, ZPG, ZPG, IMP, IMM, ACC, IMM, ABS, ABS, ABS, ABS, REL, INY, ERR, INY, ZPX, ZPX, ZPX, ZPX, IMP, ABY, IMP, ABY, ABX, ABX, ABX, ABX,
	ADR, INX, ERR, INX, ZPG, ZPG, ZPG, ZPG, IMP, IMM, ACC, IMM, ABS, ABS, ABS, ABS, REL, INY, ERR, INY, ZPX, ZPX, ZPX, ZPX, IMP, ABY, IMP, ABY, ABX, ABX, ABX, ABX,
	IMP, INX, ERR, INX, ZPG, ZPG, ZPG, ZPG, IMP, IMM, ACC, IMM, ADR, ABS, ABS, ABS, REL, INY, ERR, INY, ZPX, ZPX, ZPX, ZPX, IMP, ABY, IMP, ABY, ABX, ABX, ABX, ABX,
	IMP, INX, ERR, INX, ZPG, ZPG, ZPG, ZPG, IMP, IMM, ACC, IMM, IND, ABS, ABS, ABS, REL, INY, ERR, INY, ZPX, ZPX, ZPX, ZPX, IMP, ABY, IMP, ABY, ABX, ABX, ABX, ABX,
	IMM, INX, IMM, INX, ZPG, ZPG, ZPG, ZPG, IMP, IMM, IMP, IMM, ABS, ABS, ABS, ABS, REL, INY, ERR, INY, ZPX, ZPX, ZPY, ZPY, IMP, ABY, IMP, ABY, ABX, ABX, ABY, ABY,
	IMM, INX, IMM, INX, ZPG, ZPG, ZPG, ZPG, IMP, IMM, IMP, IMM, ABS, ABS, ABS, ABS, REL, INY, ERR, INY, ZPX, ZPX, ZPY, ZPY, IMP, ABY, IMP, ABY, ABX, ABX, ABY, ABY,
	IMM, INX, IMM, INX, ZPG, ZPG, ZPG, ZPG, IMP, IMM, IMP, IMM, ABS, ABS, ABS, ABS, REL, INY, ERR, INY, ZPX, ZPX, ZPX, ZPX, IMP, ABY, IMP, ABY, ABX, ABX, ABX, ABX,
	IMM, INX, IMM, INX, ZPG, ZPG, ZPG, ZPG, IMP, IMM, IMP, IMM, ABS, ABS, ABS, ABS, REL, INY, ERR, INY, ZPX, ZPX, ZPX, ZPX, IMP, ABY, IMP, ABY, ABX, ABX, ABX, ABX
};

Uint8 AddrBytes[NUM_ADDR_MODES] = {1, 1, 2, 3, 3, 3, 2, 3, 3, 2, 2, 2, 2, 2, 1};

char TraceArr[256][5] =
{
	" BRK", " ORA", "*HLT", "*SLO", "*NOP", " ORA", " ASL", "*SLO", " PHP", " ORA", " ASL", "*AAC", "*NOP", " ORA", " ASL", "*SLO",
	" BPL", " ORA", "*HLT", "*SLO", "*NOP", " ORA", " ASL", "*SLO", " CLC", " ORA", "*NOP", "*SLO", "*NOP", " ORA", " ASL", "*SLO",
	" JSR", " AND", "*HLT", "*RLA", " BIT", " AND", " ROL", "*RLA", " PLP", " AND", " ROL", "*AAC", " BIT", " AND", " ROL", "*RLA",
	" BMI", " AND", "*HLT", "*RLA", "*NOP", " AND", " ROL", "*RLA", " SEC", " AND", "*NOP", "*RLA", "*NOP", " AND", " ROL", "*RLA",
	" RTI", " EOR", "*HLT", "*SRE", "*NOP", " EOR", " LSR", "*SRE", " PHA", " EOR", " LSR", "*ASR", " JMP", " EOR", " LSR", "*SRE",
	" BVC", " EOR", "*HLT", "*SRE", "*NOP", " EOR", " LSR", "*SRE", " CLI", " EOR", "*NOP", "*SRE", "*NOP", " EOR", " LSR", "*SRE",
	" RTS", " ADC", "*HLT", "*RRA", "*NOP", " ADC", " ROR", "*RRA", " PLA", " ADC", " ROR", "*ARR", " JMP", " ADC", " ROR", "*RRA",
	" BVS", " ADC", "*HLT", "*RRA", "*NOP", " ADC", " ROR", "*RRA", " SEI", " ADC", "*NOP", "*RRA", "*NOP", " ADC", " ROR", "*RRA",
	"*NOP", " STA", "*NOP", "*SAX", " STY", " STA", " STX", "*SAX", " DEY", "*NOP", " TXA", " ???", " STY", " STA", " STX", "*SAX",
	" BCC", " STA", "*HLT", " ???", " STY", " STA", " STX", "*SAX", " TYA", " STA", " TXS", " ???", " ???", " STA", " ???", " ???",
	" LDY", " LDA", " LDX", "*LAX", " LDY", " LDA", " LDX", "*LAX", " TAY", " LDA", " TAX", "*ATX", " LDY", " LDA", " LDX", "*LAX",
	" BCS", " LDA", "*HLT", "*LAX", " LDY", " LDA", " LDX", "*LAX", " CLV", " LDA", " TSX", " ???", " LDY", " LDA", " LDX", "*LAX",
	" CPY", " CMP", "*NOP", "*DCP", " CPY", " CMP", " DEC", "*DCP", " INY", " CMP", " DEX", "*AXS", " CPY", " CMP", " DEC", "*DCP",
	" BNE", " CMP", "*HLT", "*DCP", "*NOP", " CMP", " DEC", "*DCP", " CLD", " CMP", "*NOP", "*DCP", "*NOP", " CMP", " DEC", "*DCP",
	" CPX", " SBC", "*NOP", "*ISB", " CPX", " SBC", " INC", "*ISB", " INX", " SBC", " NOP", "*SBC", " CPX", " SBC", " INC", "*ISB",
	" BEQ", " SBC", "*HLT", "*ISB", "*NOP", " SBC", " INC", "*ISB", " SED", " SBC", "*NOP", "*ISB", "*NOP", " SBC", " INC", "*ISB"
};

Uint8 codeLen[256] =
{   
	//0    1    2    3    4    5    6    7    8    9    A    B    C    D    E    F
	  7,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   0,   4,   6,   0, //0
	  2,   5,   0,   0,   0,   4,   6,   0,   2,   4,   0,   0,   0,   4,   7,   0, //1
	  6,   6,   0,   0,   3,   3,   5,   0,   4,   2,   2,   0,   4,   4,   6,   0, //2
	  2,   5,   0,   0,   0,   4,   6,   0,   2,   4,   0,   0,   0,   4,   7,   0, //3
	  4,   6,   0,   0,   0,   3,   5,   0,   3,   2,   2,   0,   3,   6,   6,   0, //4
	  2,   5,   0,   0,   0,   4,   6,   0,   2,   4,   0,   0,   0,   0,   7,   0, //5
	  6,   6,   0,   0,   0,   3,   5,   0,   4,   2,   2,   0,   5,   0,   6,   0, //6
	  2,   5,   0,   0,   0,   4,   6,   0,   2,   4,   0,   0,   0,   0,   7,   0, //7
	  4,   6,   0,   0,   3,   3,   3,   0,   2,   0,   2,   0,   4,   4,   4,   0, //8
	  2,   6,   0,   0,   4,   4,   4,   0,   2,   5,   2,   0,   0,   0,   0,   0, //9
	  2,   6,   2,   0,   3,   3,   3,   0,   2,   2,   2,   0,   4,   4,   4,   0, //A
	  2,   5,   0,   0,   4,   4,   4,   0,   2,   4,   2,   0,   4,   4,   4,   0, //B
	  2,   6,   0,   0,   3,   3,   5,   0,   2,   2,   2,   0,   4,   4,   6,   0, //C
	  2,   5,   0,   0,   0,   4,   6,   0,   2,   4,   0,   0,   0,   4,   7,   0, //D
	  2,   6,   0,   0,   3,   3,   5,   0,   2,   2,   2,   0,   4,   4,   6,   0, //E
	  2,   5,   0,   0,   0,   4,   6,   0,   2,   4,   0,   0,   0,   4,   7,   0  //F
};


void cpu::DecodeInstruction (Uint16 Addr, char *str1)
{
	Uint8 OpData[3] = {0, 0, 0};
	Uint16 Operand = 0, MidAddr = 0;
	int EffectiveAddr = -1;
	OpData[0] = memDat->cpuBusRead(Addr);
	switch (TraceAddrMode[OpData[0]])
	{
	case IND:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		OpData[2] = memDat->cpuBusRead(Addr+2);
		Operand = OpData[1] | (OpData[2] << 8);
		EffectiveAddr = memDat->cpuBusRead(Operand) | (memDat->cpuBusRead(Operand+1) << 8);
		break;
	case ADR:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		OpData[2] = memDat->cpuBusRead(Addr+2);Operand = OpData[1] | (OpData[2] << 8);
		break;
	case ABS:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		OpData[2] = memDat->cpuBusRead(Addr+2);Operand = OpData[1] | (OpData[2] << 8);
		EffectiveAddr = Operand;
		break;
	case ABX:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		OpData[2] = memDat->cpuBusRead(Addr+2);Operand = OpData[1] | (OpData[2] << 8);
		EffectiveAddr = (Operand + regX) & 0xFFFF;
		break;
	case ABY:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		OpData[2] = memDat->cpuBusRead(Addr+2);Operand = OpData[1] | (OpData[2] << 8);
		EffectiveAddr = (Operand + regY) & 0xFFFF;
		break;
	case IMM:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		Operand = OpData[1];
		break;
	case ZPG:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		Operand = OpData[1];
		EffectiveAddr = Operand;
		break;
	case ZPX:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		Operand = OpData[1];
		EffectiveAddr = (Operand + regX) & 0xFF;
		break;
	case ZPY:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		Operand = OpData[1];
		EffectiveAddr = (Operand + regY) & 0xFF;
		break;
	case INX:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		Operand = OpData[1];
		MidAddr = (Operand + regX) & 0xFF;
		EffectiveAddr = memDat->cpuBusRead(MidAddr) | (memDat->cpuBusRead((MidAddr+1) & 0xFF) << 8);
		break;
	case INY:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		Operand = OpData[1];
		MidAddr = memDat->cpuBusRead(Operand) | (memDat->cpuBusRead((Operand+1) & 0xFF) << 8);
		EffectiveAddr = (MidAddr + regY) & 0xFFFF;
		break;
	case IMP:
		break;
	case ACC:
		break;
	case ERR:
		break;
	case REL:
		OpData[1] = memDat->cpuBusRead(Addr+1);
		Operand = Addr+2+(signed char)OpData[1];
		break;
	default:
		break;
	}
	// Use this for outputting to debug logfile
	if (str1)
	{
		switch (TraceAddrMode[memDat->cpuBusRead(Addr)])
		{
		case IMP:
		case ERR:	sprintf(str1, "%04X  %02X       %s                           ",			Addr, OpData[0],			TraceArr[OpData[0]]);									break;
		case ACC:	sprintf(str1, "%04X  %02X       %s A                         ",			Addr, OpData[0],			TraceArr[OpData[0]]);									break;
		case IMM:	sprintf(str1, "%04X  %02X %02X    %s #$%02X                      ",		Addr, OpData[0], OpData[1],		TraceArr[OpData[0]], Operand);								break;
		case REL:	sprintf(str1, "%04X  %02X %02X    %s $%04X                     ",		Addr, OpData[0], OpData[1],		TraceArr[OpData[0]], Operand);								break;
		case ZPG:	sprintf(str1, "%04X  %02X %02X    %s $%02X = %02X                  ",		Addr, OpData[0], OpData[1],		TraceArr[OpData[0]], Operand, (Operand >= 0x2000 && Operand <= 0x20FF ? 0xFF : memDat->cpuBusRead(Operand)));					break;
		case ZPX:	sprintf(str1, "%04X  %02X %02X    %s $%02X,X @ %02X = %02X           ",		Addr, OpData[0], OpData[1],		TraceArr[OpData[0]], Operand, EffectiveAddr,(EffectiveAddr >= 0x2000 && EffectiveAddr <= 0x20FF ? 0xFF :  memDat->cpuBusRead(EffectiveAddr)));		break;
		case ZPY:	sprintf(str1, "%04X  %02X %02X    %s $%02X,Y @ %02X = %02X           ",		Addr, OpData[0], OpData[1],		TraceArr[OpData[0]], Operand, EffectiveAddr, (EffectiveAddr >= 0x2000 && EffectiveAddr <= 0x20FF ? 0xFF : memDat->cpuBusRead(EffectiveAddr)));		break;
		case INX:	sprintf(str1, "%04X  %02X %02X    %s ($%02X,X) @ %02X = %04X = %02X  ",		Addr, OpData[0], OpData[1],		TraceArr[OpData[0]], Operand, MidAddr, EffectiveAddr, (EffectiveAddr >= 0x2000 && EffectiveAddr <= 0x20FF ? 0xFF : memDat->cpuBusRead(EffectiveAddr)));	break;
		case INY:	sprintf(str1, "%04X  %02X %02X    %s ($%02X),Y = %04X @ %04X = %02X",		Addr, OpData[0], OpData[1],		TraceArr[OpData[0]], Operand, MidAddr, EffectiveAddr, (EffectiveAddr >= 0x2000 && EffectiveAddr <= 0x20FF ? 0xFF : memDat->cpuBusRead(EffectiveAddr)));	break;
		case ADR:	sprintf(str1, "%04X  %02X %02X %02X %s $%04X                     ",		Addr, OpData[0], OpData[1], OpData[2],	TraceArr[OpData[0]], Operand);								break;
		case ABS:	sprintf(str1, "%04X  %02X %02X %02X %s $%04X = %02X                ",		Addr, OpData[0], OpData[1], OpData[2],	TraceArr[OpData[0]], Operand, (Operand >= 0x2000 && Operand <= 0x20FF ? 0xFF : memDat->cpuBusRead(Operand)));					break;
		case IND:	sprintf(str1, "%04X  %02X %02X %02X %s ($%04X) = %04X            ",		Addr, OpData[0], OpData[1], OpData[2],	TraceArr[OpData[0]], Operand, EffectiveAddr);						break;
		case ABX:	sprintf(str1, "%04X  %02X %02X %02X %s $%04X,X @ %04X = %02X       ",		Addr, OpData[0], OpData[1], OpData[2],	TraceArr[OpData[0]], Operand, EffectiveAddr, (EffectiveAddr >= 0x2000 && EffectiveAddr <= 0x20FF ? 0xFF : memDat->cpuBusRead(EffectiveAddr)));		break;
		case ABY:	sprintf(str1, "%04X  %02X %02X %02X %s $%04X,Y @ %04X = %02X       ",		Addr, OpData[0], OpData[1], OpData[2],	TraceArr[OpData[0]], Operand, EffectiveAddr, (EffectiveAddr >= 0x2000 && EffectiveAddr <= 0x20FF ? 0xFF : memDat->cpuBusRead(EffectiveAddr)));		break;
		default:	strcpy(str1, "                                             ");																			break;
		}
	}
}

cpu::cpu(void)
{
	for(Uint16 i = 0; i < 0x100; ++i){
		opArr[i] = &cpu::opcodeXX;
	}
	//load function pointer array
	opArr[0x69] = &cpu::opcode69;
	opArr[0x65] = &cpu::opcode65;
	opArr[0x75] = &cpu::opcode75;
	opArr[0x6D] = &cpu::opcode6D;
	opArr[0x7D] = &cpu::opcode7D;
	opArr[0x79] = &cpu::opcode79;
	opArr[0x61] = &cpu::opcode61;
	opArr[0x71] = &cpu::opcode71;

	opArr[0x29] = &cpu::opcode29;
	opArr[0x25] = &cpu::opcode25;
	opArr[0x35] = &cpu::opcode35;
	opArr[0x2D] = &cpu::opcode2D;
	opArr[0x3D] = &cpu::opcode3D;
	opArr[0x39] = &cpu::opcode39;
	opArr[0x21] = &cpu::opcode21;
	opArr[0x31] = &cpu::opcode31;

	opArr[0x0A] = &cpu::opcode0A;
	opArr[0x06] = &cpu::opcode06;
	opArr[0x16] = &cpu::opcode16;
	opArr[0x0E] = &cpu::opcode0E;
	opArr[0x1E] = &cpu::opcode1E;

	opArr[0x24] = &cpu::opcode24;
	opArr[0x2C] = &cpu::opcode2C;

	opArr[0x10] = &cpu::opcode10;
	opArr[0x30] = &cpu::opcode30;
	opArr[0x50] = &cpu::opcode50;
	opArr[0x70] = &cpu::opcode70;
	opArr[0x90] = &cpu::opcode90;
	opArr[0xB0] = &cpu::opcodeB0;
	opArr[0xD0] = &cpu::opcodeD0;
	opArr[0xF0] = &cpu::opcodeF0;

	opArr[0x00] = &cpu::opcode00;

	opArr[0xC9] = &cpu::opcodeC9;
	opArr[0xC5] = &cpu::opcodeC5;
	opArr[0xD5] = &cpu::opcodeD5;
	opArr[0xCD] = &cpu::opcodeCD;
	opArr[0xDD] = &cpu::opcodeDD;
	opArr[0xD9] = &cpu::opcodeD9;
	opArr[0xC1] = &cpu::opcodeC1;
	opArr[0xD1] = &cpu::opcodeD1;

	opArr[0xE0] = &cpu::opcodeE0;
	opArr[0xE4] = &cpu::opcodeE4;
	opArr[0xEC] = &cpu::opcodeEC;

	opArr[0xC0] = &cpu::opcodeC0;
	opArr[0xC4] = &cpu::opcodeC4;
	opArr[0xCC] = &cpu::opcodeCC;

	opArr[0xC6] = &cpu::opcodeC6;
	opArr[0xD6] = &cpu::opcodeD6;
	opArr[0xCE] = &cpu::opcodeCE;
	opArr[0xDE] = &cpu::opcodeDE;

	opArr[0x04] = &cpu::opcode04;
	opArr[0x14] = &cpu::opcode14;
	opArr[0x34] = &cpu::opcode34;
	opArr[0x44] = &cpu::opcode44;
	opArr[0x54] = &cpu::opcode54;
	opArr[0x64] = &cpu::opcode64;
	opArr[0x74] = &cpu::opcode74;
	opArr[0x80] = &cpu::opcode80;
	opArr[0x82] = &cpu::opcode82;
	opArr[0x89] = &cpu::opcode89;
	opArr[0xC2] = &cpu::opcodeC2;
	opArr[0xD4] = &cpu::opcodeD4;
	opArr[0xE2] = &cpu::opcodeE2;
	opArr[0xF4] = &cpu::opcodeF4;

	opArr[0x49] = &cpu::opcode49;
	opArr[0x45] = &cpu::opcode45;
	opArr[0x55] = &cpu::opcode55;
	opArr[0x4D] = &cpu::opcode4D;
	opArr[0x5D] = &cpu::opcode5D;
	opArr[0x59] = &cpu::opcode59;
	opArr[0x41] = &cpu::opcode41;
	opArr[0x51] = &cpu::opcode51;

	opArr[0x18] = &cpu::opcode18;
	opArr[0x38] = &cpu::opcode38;
	opArr[0x58] = &cpu::opcode58;
	opArr[0x78] = &cpu::opcode78;
	opArr[0xB8] = &cpu::opcodeB8;
	opArr[0xD8] = &cpu::opcodeD8;
	opArr[0xF8] = &cpu::opcodeF8;

	opArr[0xE6] = &cpu::opcodeE6;
	opArr[0xF6] = &cpu::opcodeF6;
	opArr[0xEE] = &cpu::opcodeEE;
	opArr[0xFE] = &cpu::opcodeFE;

	opArr[0x4C] = &cpu::opcode4C;
	opArr[0x6C] = &cpu::opcode6C;

	opArr[0x20] = &cpu::opcode20;

	opArr[0xA9] = &cpu::opcodeA9;
	opArr[0xA5] = &cpu::opcodeA5;
	opArr[0xB5] = &cpu::opcodeB5;
	opArr[0xAD] = &cpu::opcodeAD;
	opArr[0xBD] = &cpu::opcodeBD;
	opArr[0xB9] = &cpu::opcodeB9;
	opArr[0xA1] = &cpu::opcodeA1;
	opArr[0xB1] = &cpu::opcodeB1;

	opArr[0xA2] = &cpu::opcodeA2;
	opArr[0xA6] = &cpu::opcodeA6;
	opArr[0xB6] = &cpu::opcodeB6;
	opArr[0xAE] = &cpu::opcodeAE;
	opArr[0xBE] = &cpu::opcodeBE;

	opArr[0xA0] = &cpu::opcodeA0;
	opArr[0xA4] = &cpu::opcodeA4;
	opArr[0xB4] = &cpu::opcodeB4;
	opArr[0xAC] = &cpu::opcodeAC;
	opArr[0xBC] = &cpu::opcodeBC;

	opArr[0x4A] = &cpu::opcode4A;
	opArr[0x46] = &cpu::opcode46;
	opArr[0x56] = &cpu::opcode56;
	opArr[0x4E] = &cpu::opcode4E;
	opArr[0x5E] = &cpu::opcode5E;

	opArr[0x1A] = &cpu::opcode1A; 
	opArr[0x3A] = &cpu::opcode3A; 
	opArr[0x5A] = &cpu::opcode5A; 
	opArr[0x7A] = &cpu::opcode7A; 
	opArr[0xDA] = &cpu::opcodeDA; 
	opArr[0xEA] = &cpu::opcodeEA; 
	opArr[0xFA] = &cpu::opcodeFA; 

	opArr[0x09] = &cpu::opcode09;
	opArr[0x05] = &cpu::opcode05;
	opArr[0x15] = &cpu::opcode15;
	opArr[0x0D] = &cpu::opcode0D;
	opArr[0x1D] = &cpu::opcode1D;
	opArr[0x19] = &cpu::opcode19;
	opArr[0x01] = &cpu::opcode01;
	opArr[0x11] = &cpu::opcode11;

	opArr[0xAA] = &cpu::opcodeAA;
	opArr[0x8A] = &cpu::opcode8A;
	opArr[0xCA] = &cpu::opcodeCA;
	opArr[0xE8] = &cpu::opcodeE8;
	opArr[0xA8] = &cpu::opcodeA8;
	opArr[0x98] = &cpu::opcode98;
	opArr[0x88] = &cpu::opcode88;
	opArr[0xC8] = &cpu::opcodeC8;

	opArr[0x2A] = &cpu::opcode2A;
	opArr[0x26] = &cpu::opcode26;
	opArr[0x36] = &cpu::opcode36;
	opArr[0x2E] = &cpu::opcode2E;
	opArr[0x3E] = &cpu::opcode3E;

	opArr[0x6A] = &cpu::opcode6A;
	opArr[0x66] = &cpu::opcode66;
	opArr[0x76] = &cpu::opcode76;
	opArr[0x6E] = &cpu::opcode6E;
	opArr[0x7E] = &cpu::opcode7E;

	opArr[0x40] = &cpu::opcode40;

	opArr[0x60] = &cpu::opcode60;

	opArr[0xE9] = &cpu::opcodeE9;
	opArr[0xE5] = &cpu::opcodeE5;
	opArr[0xF5] = &cpu::opcodeF5;
	opArr[0xED] = &cpu::opcodeED;
	opArr[0xFD] = &cpu::opcodeFD;
	opArr[0xF9] = &cpu::opcodeF9;
	opArr[0xE1] = &cpu::opcodeE1;
	opArr[0xF1] = &cpu::opcodeF1;

	opArr[0x85] = &cpu::opcode85;
	opArr[0x95] = &cpu::opcode95;
	opArr[0x8D] = &cpu::opcode8D;
	opArr[0x9D] = &cpu::opcode9D;
	opArr[0x99] = &cpu::opcode99;
	opArr[0x81] = &cpu::opcode81;
	opArr[0x91] = &cpu::opcode91;

	opArr[0x9A] = &cpu::opcode9A;
	opArr[0xBA] = &cpu::opcodeBA;
	opArr[0x48] = &cpu::opcode48;
	opArr[0x68] = &cpu::opcode68;
	opArr[0x08] = &cpu::opcode08;
	opArr[0x28] = &cpu::opcode28;

	opArr[0x86] = &cpu::opcode86;
	opArr[0x96] = &cpu::opcode96;
	opArr[0x8E] = &cpu::opcode8E;

	opArr[0x84] = &cpu::opcode84;
	opArr[0x94] = &cpu::opcode94;
	opArr[0x8C] = &cpu::opcode8C;

	opArr[0x0C] = &cpu::opcode0C;
	opArr[0x1C] = &cpu::opcode1C;
	opArr[0x3C] = &cpu::opcode3C;
	opArr[0x5C] = &cpu::opcode5C;
	opArr[0x7C] = &cpu::opcode7C;
	opArr[0xDC] = &cpu::opcodeDC;
	opArr[0xFC] = &cpu::opcodeFC;
	hasIRQ = false;
	runLog = false;
}

cpu::~cpu(void)
{
	//myfile.close();
}

void cpu::runClock(){
	if(!dmaSkip){

		_curCycle = curCycle;
		op = memDat->cpuBusRead(regPC);
		if(runLog){
			Uint16 Addr = (Uint16)regPC;
			char tps[64];
			DecodeInstruction(Addr, tps);
			myfile << tps;
			sprintf(tps, "  A:%02X X:%02X Y:%02X P:%02X SP:%02X CYC:%3i SL:%i\n", regA, regX, regY, getStatusWord(),regSP, ppuCore->curCycle % 341, (ppuCore->screenY == 261?-1:ppuCore->screenY));
			myfile << tps;
		}
		curCycle += codeLen[op];
	}
}

void cpu::init(){
	regA = 0;
	regX = 0;
	regY = 0;
	regSP = 0xFD;
	memDat->cpuBusInit();
	regPC = ((memDat->cpuBusRead(0xFFFD) << 8) | memDat->cpuBusRead(0xFFFC));
	flagC = false;
	flagZ = false;
	flagI = true;
	flagD = false;
	flagV = false;
	flagN = false;
	curCycle = 0;
	oddEvenFlag = 0;
	dmaSkip = false;
	
	////start log
	//runLog = true;
	//myfile.open (setting->progDir + "test_cpu.log", ios::out);
}

void cpu::runCode(){
	Uint32 cyc;
	if(!dmaSkip){
		cyc = _curCycle;
		(this->*opArr[op])();
		oddEvenFlag = (oddEvenFlag + (_curCycle - cyc)) & 0x01;
		curCycle = _curCycle;
	}
	else{
		dmaSkip = false;
	}
}

void cpu::reset(){
	regSP -= 3;
	flagI = true;
	regPC = ((memDat->cpuBusRead(0xFFFD, true) << 8) | memDat->cpuBusRead(0xFFFC, true));
	curCycle = 0;
	oddEvenFlag = 0;
}

void cpu::runNMI(){
	pushStack(regPC >> 8);
	pushStack(regPC & 0x00FF);
	pushStack(getStatusWord());
	regPC = ((memDat->cpuBusRead(0xFFFB) << 8) | memDat->cpuBusRead(0xFFFA));
	flagI = true;
	curCycle += 7;
	oddEvenFlag = (oddEvenFlag + 7) & 0x01;
}

void cpu::runIRQ(){
	if(hasIRQ && !flagI){
		pushStack(regPC >> 8);
		pushStack(regPC & 0x00FF);
		pushStack(getStatusWord());
		regPC = ((memDat->cpuBusRead(0xFFFF) << 8) | memDat->cpuBusRead(0xFFFE));
		flagI = true;
		curCycle += 7;
		oddEvenFlag = (oddEvenFlag + 7) & 0x01;
	}
	hasIRQ = false;
}

void cpu::setIRQ(){
	if(!flagI) hasIRQ = true;
}


//ADC
void cpu::opADC(Uint8 value){
	Uint8 oRegA;
	unsigned int tRegA;
	oRegA = regA;
	tRegA = regA;
	tRegA += value;
	if(flagC) ++tRegA;
	regA = tRegA & 0xFF;
	flagC = (tRegA > 0xFF);
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
	flagV = (((regA ^ value) & (regA ^ oRegA) & 0x80) != 0); 
}

void cpu::opcode69(){
	opADC(memDat->cpuBusRead(regPC+1, true));
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcode65(){
	opADC(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1), true));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcode75(){
	opADC(memDat->cpuBusRead((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF, true));
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcode6D(){
	opADC(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1), true));
	regPC += 3;
	_curCycle += 4;
}

void cpu::opcode7D(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regX + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opADC(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcode79(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regY + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opADC(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcode61(){
	Uint8 address;
	address = regX + memDat->cpuBusRead(regPC+1);
	opADC(memDat->cpuBusRead((memDat->cpuBusRead((address + 1) & 0xFF) << 8) | memDat->cpuBusRead(address), true));
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcode71(){
	Uint8 ad1;
	Uint8 op1;
	Uint16 address;

	op1 = memDat->cpuBusRead(regPC+1);
	ad1 = memDat->cpuBusRead((op1 + 1) & 0xFF);
	address = regY + ((ad1 << 8) | memDat->cpuBusRead(op1));
	opADC(memDat->cpuBusRead(address, true));
	regPC += 2;
	_curCycle += 5;
	if(ad1 != (address >> 8)) ++_curCycle;
}



//AND
void cpu::opAND(Uint8 value){
	regA &= value;
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
}

void cpu::opcode29(){
	opAND(memDat->cpuBusRead(regPC+1, true));
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcode25(){
	opAND(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1), true));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcode35(){
	opAND(memDat->cpuBusRead((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF, true));
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcode2D(){
	opAND(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1), true));
	regPC += 3;
	_curCycle += 4;
}

void cpu::opcode3D(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regX + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opAND(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcode39(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regY + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opAND(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcode21(){
	Uint8 address;
	address = regX + memDat->cpuBusRead(regPC+1);
	opAND(memDat->cpuBusRead((memDat->cpuBusRead((address + 1) & 0xFF) << 8) | memDat->cpuBusRead(address), true));
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcode31(){
	Uint8 ad1;
	Uint8 op1;
	Uint16 address;

	op1 = memDat->cpuBusRead(regPC+1);
	ad1 = memDat->cpuBusRead((op1 + 1) & 0xFF);
	address = regY + ((ad1 << 8) | memDat->cpuBusRead(op1));
	opAND(memDat->cpuBusRead(address, true));
	regPC += 2;
	_curCycle += 5;
	if(ad1 != (address >> 8)) ++_curCycle;
}



//ASL
void cpu::opASL(Uint16 address){
	Uint8 value;
	value = memDat->cpuBusRead(address);
	flagC = ((value & 0x80) != 0);
	value <<= 1;
	memDat->cpuBusWrite(address, value);
	flagZ = (value == 0);
	flagN = ((value & 0x80) != 0);
}

void cpu::opcode0A(){
	flagC = ((regA & 0x80) != 0);
	regA <<= 1;
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcode06(){
	opASL(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 5;
}

void cpu::opcode16(){
	opASL((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF);
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcode0E(){
	opASL((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1));
	regPC += 3;
	_curCycle += 6;
}

void cpu::opcode1E(){
	opASL(regX + ((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 7;
}

//BIT
void cpu::opBIT(Uint8 value){
	flagZ = ((regA & value) == 0);
	flagN = ((value & 0x80) != 0);
	flagV = ((value & 0x40) != 0);
}

void cpu::opcode24(){
	opBIT(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1)));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcode2C(){
	opBIT(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 4;
}


//Branch
void cpu::opBranch(bool doBranch){
	Uint8 oldPage;
	if(doBranch){
		oldPage = (regPC >> 8);
		regPC += 2 + (signed char)(memDat->cpuBusRead(regPC+1));
		_curCycle +=3;
		if((regPC >> 8) != oldPage) ++_curCycle;
	}
	else{
		regPC += 2;
		_curCycle += 2;
	}
}

void cpu::opcode10(){
	opBranch(!flagN);
}

void cpu::opcode30(){
	opBranch(flagN);
}

void cpu::opcode50(){
	opBranch(!flagV);
}

void cpu::opcode70(){
	opBranch(flagV);
}

void cpu::opcode90(){
	opBranch(!flagC);
}

void cpu::opcodeB0(){
	opBranch(flagC);
}

void cpu::opcodeD0(){
	opBranch(!flagZ);
}

void cpu::opcodeF0(){
	opBranch(flagZ);
}



//BRK
void cpu::opcode00(){
	regPC += 2;
	pushStack(regPC >> 8);
	pushStack(regPC & 0x00FF);
	pushStack(getStatusWord() | 0x30);
	regPC = ((memDat->cpuBusRead(0xFFFF) << 8) | memDat->cpuBusRead(0xFFFE));
	flagI = true;
	_curCycle += 7;
}

//CMP
void cpu::opCMP(Uint8 value){
	flagC = (regA >= value);
	flagZ = (regA == value);
	flagN = (((regA - value) & 0x80) != 0);
}

void cpu::opcodeC9(){
	opCMP(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcodeC5(){
	opCMP(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1)));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcodeD5(){
	opCMP(memDat->cpuBusRead((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF));
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcodeCD(){
	opCMP(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 4;
}

void cpu::opcodeDD(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regX + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opCMP(memDat->cpuBusRead(address));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcodeD9(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regY + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opCMP(memDat->cpuBusRead(address));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcodeC1(){
	Uint8 address;
	address = regX + memDat->cpuBusRead(regPC+1);
	opCMP(memDat->cpuBusRead((memDat->cpuBusRead((address + 1) & 0xFF) << 8) | memDat->cpuBusRead(address)));
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcodeD1(){
	Uint8 ad1;
	Uint8 op1;
	Uint16 address;

	op1 = memDat->cpuBusRead(regPC+1);
	ad1 = memDat->cpuBusRead((op1 + 1) & 0xFF);
	address = regY + ((ad1 << 8) | memDat->cpuBusRead(op1));
	opCMP(memDat->cpuBusRead(address));
	regPC += 2;
	_curCycle += 5;
	if(ad1 != (address >> 8)) ++_curCycle;
}



//CPX
void cpu::opCPX(Uint8 value){
	flagC = (regX >= value);
	flagZ = (regX == value);
	flagN = (((regX - value) & 0x80) != 0);
}

void cpu::opcodeE0(){
	opCPX(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcodeE4(){
	opCPX(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1)));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcodeEC(){
	opCPX(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 4;
}


void cpu::opCPY(Uint8 value){
	flagC = (regY >= value);
	flagZ = (regY == value);
	flagN = (((regY - value) & 0x80) != 0);
}

void cpu::opcodeC0(){
	opCPY(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcodeC4(){
	opCPY(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1)));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcodeCC(){
	opCPY(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 4;
}


//DEC
void cpu::opDEC(Uint16 address){
	Uint8 value;
	value = memDat->cpuBusRead(address);
	--value;
	memDat->cpuBusWrite(address, value);
	flagZ = (value == 0);
	flagN = ((value & 0x80) != 0);
}

void cpu::opcodeC6(){
	opDEC(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 5;
}

void cpu::opcodeD6(){
	opDEC((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF);
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcodeCE(){
	opDEC((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1));
	regPC += 3;
	_curCycle += 6;
}

void cpu::opcodeDE(){
	opDEC(regX + ((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 7;
}


//DOP
void cpu::opcode04(){
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcode14(){
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcode34(){
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcode44(){
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcode54(){
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcode64(){
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcode74(){
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcode80(){
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcode82(){
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcode89(){
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcodeC2(){
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcodeD4(){
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcodeE2(){
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcodeF4(){
	regPC += 2;
	_curCycle += 4;
}


//EOR
void cpu::opEOR(Uint8 value){
	regA ^= value;
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
}

void cpu::opcode49(){
	opEOR(memDat->cpuBusRead(regPC+1, true));
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcode45(){
	opEOR(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1), true));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcode55(){
	opEOR(memDat->cpuBusRead((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF));
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcode4D(){
	opEOR(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1), true));
	regPC += 3;
	_curCycle += 4;
}

void cpu::opcode5D(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regX + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opEOR(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcode59(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regY + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opEOR(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcode41(){
	Uint8 address;
	address = regX + memDat->cpuBusRead(regPC+1);
	opEOR(memDat->cpuBusRead((memDat->cpuBusRead((address + 1) & 0xFF) << 8) | memDat->cpuBusRead(address), true));
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcode51(){
	Uint8 ad1;
	Uint8 op1;
	Uint16 address;

	op1 = memDat->cpuBusRead(regPC+1);
	ad1 = memDat->cpuBusRead((op1 + 1) & 0xFF);
	address = regY + ((ad1 << 8) | memDat->cpuBusRead(op1));
	opEOR(memDat->cpuBusRead(address, true));
	regPC += 2;
	_curCycle += 5;
	if(ad1 != (address >> 8)) ++_curCycle;
}

//flag
void cpu::opcode18(){
	flagC = false;
	++regPC;
	_curCycle +=2;
}

void cpu::opcode38(){
	flagC = true;
	++regPC;
	_curCycle +=2;
}

void cpu::opcode58(){
	flagI = false;
	++regPC;
	_curCycle +=2;
}

void cpu::opcode78(){
	flagI = true;
	++regPC;
	_curCycle +=2;
}

void cpu::opcodeB8(){
	flagV = false;
	++regPC;
	_curCycle +=2;
}

void cpu::opcodeD8(){
	flagD = false;
	++regPC;
	_curCycle +=2;
}

void cpu::opcodeF8(){
	flagD = true;
	++regPC;
	_curCycle +=2;
}

//INC
void cpu::opINC(Uint16 address){
	Uint8 value;
	value = memDat->cpuBusRead(address);
	value++;
	memDat->cpuBusWrite(address, value);
	flagZ = (value == 0);
	flagN = ((value & 0x80) != 0);
}

void cpu::opcodeE6(){
	opINC(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 5;
}

void cpu::opcodeF6(){
	opINC((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF);
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcodeEE(){
	opINC((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1));
	regPC += 3;
	_curCycle += 6;
}

void cpu::opcodeFE(){
	opINC(regX + ((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 7;
}

//JMP
void cpu::opJMP(Uint16 address){
	regPC = address;
}

void cpu::opcode4C(){
	opJMP((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1));
	_curCycle += 3;
}

void cpu::opcode6C(){
	Uint8 add1;
	Uint8 add2;
	Uint8 add3;

	add1 = memDat->cpuBusRead(regPC+1);
	add2 = memDat->cpuBusRead(regPC+2);
	add3 = add1 + 1;
	opJMP((memDat->cpuBusRead(((add2 << 8) | add3)) << 8) | memDat->cpuBusRead(((add2 << 8) | add1)));
	_curCycle += 5;
}


//JSR
void cpu::opcode20(){
	Uint16 retAdd;
	retAdd = regPC + 2;
	pushStack(retAdd >> 8);
	pushStack(retAdd & 0x00FF);
	regPC = ((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1));
	_curCycle += 6;
}


//LDA
void cpu::opLDA(Uint8 value){
	regA = value;
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
}

void cpu::opcodeA9(){
	opLDA(memDat->cpuBusRead(regPC+1, true));
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcodeA5(){
	opLDA(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1), true));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcodeB5(){
	opLDA(memDat->cpuBusRead((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF, true));
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcodeAD(){
	opLDA(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1), true));
	regPC += 3;
	_curCycle += 4;
}

void cpu::opcodeBD(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regX + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opLDA(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcodeB9(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regY + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opLDA(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcodeA1(){
	Uint8 address;
	address = regX + memDat->cpuBusRead(regPC+1);
	opLDA(memDat->cpuBusRead((memDat->cpuBusRead((address + 1) & 0xFF) << 8) | memDat->cpuBusRead(address), true));
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcodeB1(){
	Uint8 ad1;
	Uint8 op1;
	Uint16 address;

	op1 = memDat->cpuBusRead(regPC+1);
	ad1 = memDat->cpuBusRead((op1 + 1) & 0xFF);
	address = regY + ((ad1 << 8) | memDat->cpuBusRead(op1));
	opLDA(memDat->cpuBusRead(address, true));
	regPC += 2;
	_curCycle += 5;
	if(ad1 != (address >> 8)) ++_curCycle;
}


//LDX
void cpu::opLDX(Uint8 value){
	regX = value;
	flagZ = (regX == 0);
	flagN = ((regX & 0x80) != 0);
}

void cpu::opcodeA2(){
	opLDX(memDat->cpuBusRead(regPC+1, true));
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcodeA6(){
	opLDX(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1), true));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcodeB6(){
	opLDX(memDat->cpuBusRead((regY + memDat->cpuBusRead(regPC+1)) & 0x00FF, true));
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcodeAE(){
	opLDX(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1), true));
	regPC += 3;
	_curCycle += 4;
}

void cpu::opcodeBE(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regY + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opLDX(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

//LDY
void cpu::opLDY(Uint8 value){
	regY = value;
	flagZ = (regY == 0);
	flagN = ((regY & 0x80) != 0);
}

void cpu::opcodeA0(){
	opLDY(memDat->cpuBusRead(regPC+1, true));
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcodeA4(){
	opLDY(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1), true));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcodeB4(){
	opLDY(memDat->cpuBusRead((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF, true));
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcodeAC(){
	opLDY(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1), true));
	regPC += 3;
	_curCycle += 4;
}

void cpu::opcodeBC(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regX + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opLDY(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}


//LSR
void cpu::opLSR(Uint16 address){
	Uint8 value;
	value = memDat->cpuBusRead(address);
	flagC = ((value & 0x01) != 0);
	value >>= 1;
	memDat->cpuBusWrite(address, value);
	flagZ = (value == 0);
	flagN = ((value & 0x80) != 0);
}

void cpu::opcode4A(){
	flagC = ((regA & 0x01) != 0);
	regA >>= 1;
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcode46(){
	opLSR(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 5;
}

void cpu::opcode56(){
	opLSR((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF);
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcode4E(){
	opLSR((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1));
	regPC += 3;
	_curCycle += 6;
}

void cpu::opcode5E(){
	opLSR(regX + ((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 7;
}

//NOP
void cpu::opcode1A(){
	++regPC;
	_curCycle += 2;
}

void cpu::opcode3A(){
	++regPC;
	_curCycle += 2;
}

void cpu::opcode5A(){
	++regPC;
	_curCycle += 2;
}

void cpu::opcode7A(){
	++regPC;
	_curCycle += 2;
}

void cpu::opcodeDA(){
	++regPC;
	_curCycle += 2;
}

void cpu::opcodeEA(){
	++regPC;
	_curCycle += 2;
}

void cpu::opcodeFA(){
	++regPC;
	_curCycle += 2;
}


//ORA
void cpu::opORA(Uint8 value){
	regA |= value;
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
}

void cpu::opcode09(){
	opORA(memDat->cpuBusRead(regPC+1, true));
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcode05(){
	opORA(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1), true));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcode15(){
	opORA(memDat->cpuBusRead((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF, true));
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcode0D(){
	opORA(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1), true));
	regPC += 3;
	_curCycle += 4;
}

void cpu::opcode1D(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regX + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opORA(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcode19(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regY + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opORA(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcode01(){
	Uint8 address;
	address = regX + memDat->cpuBusRead(regPC+1);
	opORA(memDat->cpuBusRead((memDat->cpuBusRead((address + 1) & 0xFF) << 8) | memDat->cpuBusRead(address), true));
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcode11(){
	Uint8 ad1;
	Uint8 op1;
	Uint16 address;

	op1 = memDat->cpuBusRead(regPC+1);
	ad1 = memDat->cpuBusRead((op1 + 1) & 0xFF);
	address = regY + ((ad1 << 8) | memDat->cpuBusRead(op1));
	opORA(memDat->cpuBusRead(address, true));
	regPC += 2;
	_curCycle += 5;
	if(ad1 != (address >> 8)) ++_curCycle;
}


//Register
void cpu::opcodeAA(){
	regX = regA;
	flagZ = (regX == 0);
	flagN = ((regX & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcode8A(){
	regA= regX;
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcodeCA(){
	--regX;
	flagZ = (regX == 0);
	flagN = ((regX & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcodeE8(){
	++regX;
	flagZ = (regX == 0);
	flagN = ((regX & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcodeA8(){
	regY = regA;
	flagZ = (regY == 0);
	flagN = ((regY & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcode98(){
	regA = regY;
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcode88(){
	--regY;
	flagZ = (regY == 0);
	flagN = ((regY & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcodeC8(){
	++regY;
	flagZ = (regY == 0);
	flagN = ((regY & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}


//ROL
void cpu::opROL(Uint16 address){
	Uint8 value;
	bool oFlagC;
	oFlagC = flagC;

	value = memDat->cpuBusRead(address);
	flagC = ((value & 0x80) != 0);
	value <<= 1;
	if(oFlagC) value |= 0x01;
	memDat->cpuBusWrite(address, value);
	flagZ = (value == 0);
	flagN = ((value & 0x80) != 0);
}

void cpu::opcode2A(){
	bool oFlagC;
	oFlagC = flagC;

	flagC = ((regA & 0x80) != 0);
	regA <<= 1;
	if(oFlagC) regA |= 0x01;
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcode26(){
	opROL(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 5;
}

void cpu::opcode36(){
	opROL((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF);
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcode2E(){
	opROL((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1));
	regPC += 3;
	_curCycle += 6;
}

void cpu::opcode3E(){
	opROL(regX + ((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 7;
}


//ROR
void cpu::opROR(Uint16 address){
	Uint8 value;
	bool oFlagC;
	oFlagC = flagC;

	value = memDat->cpuBusRead(address);
	flagC = ((value & 0x01) != 0);
	value >>= 1;
	if(oFlagC) value |= 0x80;
	memDat->cpuBusWrite(address, value);
	flagZ = (value == 0);
	flagN = ((value & 0x80) != 0);
}

void cpu::opcode6A(){
	bool oFlagC;
	oFlagC = flagC;

	flagC = ((regA & 0x01) != 0);
	regA >>= 1;
	if(oFlagC) regA |= 0x80;
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcode66(){
	opROR(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 5;
}

void cpu::opcode76(){
	opROR((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF);
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcode6E(){
	opROR((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1));
	regPC += 3;
	_curCycle += 6;
}

void cpu::opcode7E(){
	opROR(regX + ((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 7;
}


//RTI
void cpu::opcode40(){
	Uint8 statusW;

	statusW = popStack();
	flagC = ((statusW & 0x01) != 0);
	flagZ = ((statusW & 0x02) != 0);
	flagI = ((statusW & 0x04) != 0);
	flagD = ((statusW & 0x08) != 0);
	flagV = ((statusW & 0x40) != 0);
	flagN = ((statusW & 0x80) != 0);
	regPC = popStack();
	regPC |= (popStack() << 8);

	_curCycle += 6;
}


//RTS
void cpu::opcode60(){
	regPC = popStack();
	regPC |= (popStack() << 8);
	++regPC;
	_curCycle += 6;
}

//SBC
void cpu::opSBC(Uint8 value){
	Uint8 oRegA;
	unsigned int tRegA;
	oRegA = regA;
	tRegA = regA;
	tRegA -= value;
	if(!flagC) --tRegA;
	regA = tRegA & 0xFF;
	flagC = (tRegA < 0x100);
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
	flagV = (((regA ^ (value ^ 0xFF)) & (regA ^ oRegA) & 0x80) != 0); 
}

void cpu::opcodeE9(){
	opSBC(memDat->cpuBusRead(regPC+1, true));
	regPC += 2;
	_curCycle += 2;
}

void cpu::opcodeE5(){
	opSBC(memDat->cpuBusRead(memDat->cpuBusRead(regPC+1), true));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcodeF5(){
	opSBC(memDat->cpuBusRead((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF, true));
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcodeED(){
	opSBC(memDat->cpuBusRead((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1), true));
	regPC += 3;
	_curCycle += 4;
}

void cpu::opcodeFD(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regX + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opSBC(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcodeF9(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regY + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	opSBC(memDat->cpuBusRead(address, true));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcodeE1(){
	Uint8 address;
	address = regX + memDat->cpuBusRead(regPC+1);
	opSBC(memDat->cpuBusRead((memDat->cpuBusRead((address + 1) & 0xFF) << 8) | memDat->cpuBusRead(address), true));
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcodeF1(){
	Uint8 ad1;
	Uint8 op1;
	Uint16 address;

	op1 = memDat->cpuBusRead(regPC+1);
	ad1 = memDat->cpuBusRead((op1 + 1) & 0xFF);
	address = regY + ((ad1 << 8) | memDat->cpuBusRead(op1));
	opSBC(memDat->cpuBusRead(address, true));
	regPC += 2;
	_curCycle += 5;
	if(ad1 != (address >> 8)) ++_curCycle;
}


//STA
void cpu::opSTA(Uint16 address){
	memDat->cpuBusWrite(address, regA);
}

void cpu::opcode85(){
	opSTA(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcode95(){
	opSTA((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF);
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcode8D(){
	opSTA((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1));
	regPC += 3;
	_curCycle += 4;
}

void cpu::opcode9D(){
	opSTA(regX + ((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 5;
}

void cpu::opcode99(){
	opSTA(regY + ((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1)));
	regPC += 3;
	_curCycle += 5;
}

void cpu::opcode81(){
	Uint8 address;
	address = regX + memDat->cpuBusRead(regPC+1);
	opSTA((memDat->cpuBusRead((address + 1) & 0xFF) << 8) | memDat->cpuBusRead(address));
	regPC += 2;
	_curCycle += 6;
}

void cpu::opcode91(){
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+1);
	opSTA(regY + ((memDat->cpuBusRead((op1 + 1) & 0xFF) << 8) | memDat->cpuBusRead(op1)));
	regPC += 2;
	_curCycle += 6;
}


//Stack
void cpu::opcode9A(){
	regSP = regX;
	++regPC;
	_curCycle += 2;
}

void cpu::opcodeBA(){
	regX = regSP;
	flagZ = (regX == 0);
	flagN = ((regX & 0x80) != 0);
	++regPC;
	_curCycle += 2;
}

void cpu::opcode48(){
	pushStack(regA);
	++regPC;
	_curCycle += 3;
}

void cpu::opcode68(){
	regA = popStack();
	flagZ = (regA == 0);
	flagN = ((regA & 0x80) != 0);
	++regPC;
	_curCycle += 4;
}

void cpu::opcode08(){
	pushStack(getStatusWord() | 0x10);
	++regPC;
	_curCycle += 3;
}

void cpu::opcode28(){
	Uint8 statusW;
	statusW = popStack();
	flagC = ((statusW & 0x01) != 0);
	flagZ = ((statusW & 0x02) != 0);
	flagI = ((statusW & 0x04) != 0);
	flagD = ((statusW & 0x08) != 0);
	flagV = ((statusW & 0x40) != 0);
	flagN = ((statusW & 0x80) != 0);
	++regPC;
	_curCycle += 4;
}

//STX
void cpu::opSTX(Uint16 address){
	memDat->cpuBusWrite(address, regX);
}

void cpu::opcode86(){
	opSTX(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcode96(){
	opSTX((regY + memDat->cpuBusRead(regPC+1)) & 0x00FF);
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcode8E(){
	opSTX((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1));
	regPC += 3;
	_curCycle += 4;
}


//STY
void cpu::opSTY(Uint16 address){
	memDat->cpuBusWrite(address, regY);
}

void cpu::opcode84(){
	opSTY(memDat->cpuBusRead(regPC+1));
	regPC += 2;
	_curCycle += 3;
}

void cpu::opcode94(){
	opSTY((regX + memDat->cpuBusRead(regPC+1)) & 0x00FF);
	regPC += 2;
	_curCycle += 4;
}

void cpu::opcode8C(){
	opSTY((memDat->cpuBusRead(regPC+2) << 8) | memDat->cpuBusRead(regPC+1));
	regPC += 3;
	_curCycle += 4;
}


//TOP
void cpu::opcodeTOP(){
	Uint16 address;
	Uint8 op1;

	op1 = memDat->cpuBusRead(regPC+2);
	address = regX + ((op1 << 8) | memDat->cpuBusRead(regPC+1));
	regPC += 3;
	_curCycle += 4;
	if(op1 != (address >> 8)) ++_curCycle;
}

void cpu::opcode0C(){
	regPC += 3;
	_curCycle += 4;
}

void cpu::opcode1C(){
	opcodeTOP();
}

void cpu::opcode3C(){
	opcodeTOP();
}

void cpu::opcode5C(){
	opcodeTOP();
}

void cpu::opcode7C(){
	opcodeTOP();
}

void cpu::opcodeDC(){
	opcodeTOP();
}

void cpu::opcodeFC(){
	opcodeTOP();
}


//Unknown opcode
void cpu::opcodeXX(){
	++regPC;
}

void cpu::pushStack(Uint8 data){
	memDat->cpuBusWrite(0x100 | regSP, data);
	--regSP;
}

Uint8 cpu::popStack(){
	return memDat->cpuBusRead(0x100 | (++regSP));
}

Uint8 cpu::getStatusWord(){
	return 0x20 | (flagC ? 0x01 : 0x00) | (flagZ ? 0x02 : 0x00) | (flagI ? 0x04 : 0x00)
		 | (flagD ? 0x08 : 0x00) | (flagV ? 0x40 : 0x00) | (flagN ? 0x80 : 0x00);
}

void cpu::runDMA(){
	_curCycle += (oddEvenFlag == 0? 513: 514);
	curCycle = _curCycle;
	dmaSkip = true;
}

unsigned int cpu::getCodeRunCycle(){
	return curCycle;
}

void cpu::resetCycleCount(){
	curCycle = curCycle % 341;
}

void cpu::saveState(fstream* statefile){
    statefile->write((char *)(&regPC), sizeof(Uint16));
    statefile->write((char *)(&regSP), sizeof(Uint8));
    statefile->write((char *)(&regA), sizeof(Uint8));
    statefile->write((char *)(&regX), sizeof(Uint8));
    statefile->write((char *)(&regY), sizeof(Uint8));
    statefile->write((char *)(&flagC), sizeof(bool));
    statefile->write((char *)(&flagZ), sizeof(bool));
    statefile->write((char *)(&flagI), sizeof(bool));
    statefile->write((char *)(&flagD), sizeof(bool));
    statefile->write((char *)(&flagV), sizeof(bool));
    statefile->write((char *)(&flagN), sizeof(bool));
    statefile->write((char *)(&curCycle), sizeof(Uint32));
    statefile->write((char *)(&hasIRQ), sizeof(bool));
    statefile->write((char *)(&_curCycle), sizeof(Uint32));
    statefile->write((char *)(&dmaSkip), sizeof(bool));
    statefile->write((char *)(&oddEvenFlag), sizeof(Uint8));
    statefile->write((char *)(&op), sizeof(Uint8));
}


void cpu::loadState(fstream* statefile){
    statefile->read((char *)(&regPC), sizeof(Uint16));
    statefile->read((char *)(&regSP), sizeof(Uint8));
    statefile->read((char *)(&regA), sizeof(Uint8));
    statefile->read((char *)(&regX), sizeof(Uint8));
    statefile->read((char *)(&regY), sizeof(Uint8));
    statefile->read((char *)(&flagC), sizeof(bool));
    statefile->read((char *)(&flagZ), sizeof(bool));
    statefile->read((char *)(&flagI), sizeof(bool));
    statefile->read((char *)(&flagD), sizeof(bool));
    statefile->read((char *)(&flagV), sizeof(bool));
    statefile->read((char *)(&flagN), sizeof(bool));
    statefile->read((char *)(&curCycle), sizeof(Uint32));
    statefile->read((char *)(&hasIRQ), sizeof(bool));
    statefile->read((char *)(&_curCycle), sizeof(Uint32));
    statefile->read((char *)(&dmaSkip), sizeof(bool));
    statefile->read((char *)(&oddEvenFlag), sizeof(Uint8));
    statefile->read((char *)(&op), sizeof(Uint8));
}
