#include "StdAfx.h"
#include "apu.h"
#include "sysState.h"



apu::apu(void)
{
	lcLoadValue[0x00] = 10;
	lcLoadValue[0x01] = 254;
	lcLoadValue[0x02] = 20;
	lcLoadValue[0x03] = 2;
	lcLoadValue[0x04] = 40;
	lcLoadValue[0x05] = 4;
	lcLoadValue[0x06] = 80;
	lcLoadValue[0x07] = 6;
	lcLoadValue[0x08] = 160;
	lcLoadValue[0x09] = 8;
	lcLoadValue[0x0A] = 60;
	lcLoadValue[0x0B] = 10;
	lcLoadValue[0x0C] = 14;
	lcLoadValue[0x0D] = 12;
	lcLoadValue[0x0E] = 26;
	lcLoadValue[0x0F] = 14;
	lcLoadValue[0x10] = 12;
	lcLoadValue[0x11] = 16;
	lcLoadValue[0x12] = 24;
	lcLoadValue[0x13] = 18;
	lcLoadValue[0x14] = 48;
	lcLoadValue[0x15] = 20;
	lcLoadValue[0x16] = 96;
	lcLoadValue[0x17] = 22;
	lcLoadValue[0x18] = 192;
	lcLoadValue[0x19] = 24;
	lcLoadValue[0x1A] = 72;
	lcLoadValue[0x1B] = 26;
	lcLoadValue[0x1C] = 16;
	lcLoadValue[0x1D] = 28;
	lcLoadValue[0x1E] = 32;
	lcLoadValue[0x1F] = 30;

	dutyCycle[0][0] = 0;
	dutyCycle[0][1] = 1;
	dutyCycle[0][2] = 0;
	dutyCycle[0][3] = 0;
	dutyCycle[0][4] = 0;
	dutyCycle[0][5] = 0;
	dutyCycle[0][6] = 0;
	dutyCycle[0][7] = 0;
	dutyCycle[1][0] = 0;
	dutyCycle[1][1] = 1;
	dutyCycle[1][2] = 1;
	dutyCycle[1][3] = 0;
	dutyCycle[1][4] = 0;
	dutyCycle[1][5] = 0;
	dutyCycle[1][6] = 0;
	dutyCycle[1][7] = 0;
	dutyCycle[2][0] = 0;
	dutyCycle[2][1] = 1;
	dutyCycle[2][2] = 1;
	dutyCycle[2][3] = 1;
	dutyCycle[2][4] = 1;
	dutyCycle[2][5] = 0;
	dutyCycle[2][6] = 0;
	dutyCycle[2][7] = 0;
	dutyCycle[3][0] = 1;
	dutyCycle[3][1] = 0;
	dutyCycle[3][2] = 0;
	dutyCycle[3][3] = 1;
	dutyCycle[3][4] = 1;
	dutyCycle[3][5] = 1;
	dutyCycle[3][6] = 1;
	dutyCycle[3][7] = 1;

	triCycle[0] = 0;
	triCycle[1] = 1;
	triCycle[2] = 2;
	triCycle[3] = 3;
	triCycle[4] = 4;
	triCycle[5] = 5;
	triCycle[6] = 6;
	triCycle[7] = 7;
	triCycle[8] = 8;
	triCycle[9] = 9;
	triCycle[10] = 10;
	triCycle[11] = 11;
	triCycle[12] = 12;
	triCycle[13] = 13;
	triCycle[14] = 14;
	triCycle[15] = 15;
	triCycle[16] = 15;
	triCycle[17] = 14;
	triCycle[18] = 13;
	triCycle[19] = 12;
	triCycle[20] = 11;
	triCycle[21] = 10;
	triCycle[22] = 9;
	triCycle[23] = 8;
	triCycle[24] = 7;
	triCycle[25] = 6;
	triCycle[26] = 5;
	triCycle[27] = 4;
	triCycle[28] = 3;
	triCycle[29] = 2;
	triCycle[30] = 1;
	triCycle[31] = 0;

	noiseLen[0] = 4;
	noiseLen[1] = 8;
	noiseLen[2] = 16;
	noiseLen[3] = 32;
	noiseLen[4] = 64;
	noiseLen[5] = 96;
	noiseLen[6] = 128;
	noiseLen[7] = 160;
	noiseLen[8] = 202;
	noiseLen[9] = 254;
	noiseLen[10] = 380;
	noiseLen[11] = 508;
	noiseLen[12] = 762;
	noiseLen[13] = 1016;
	noiseLen[14] = 2034;
	noiseLen[15] = 4068;

	dmcRate[0] = 428 / 2;
	dmcRate[1] = 380 / 2;
	dmcRate[2] = 340 / 2;
	dmcRate[3] = 320 / 2;
	dmcRate[4] = 286 / 2;
	dmcRate[5] = 254 / 2;
	dmcRate[6] = 226 / 2;
	dmcRate[7] = 214 / 2;
	dmcRate[8] = 190 / 2;
	dmcRate[9] = 160 / 2;
	dmcRate[10] = 142 / 2;
	dmcRate[11] = 128 / 2;
	dmcRate[12] = 106 / 2;
	dmcRate[13] = 84 / 2;
	dmcRate[14] = 72 / 2;
	dmcRate[15] = 54 / 2;

	dmcPeriodCounter = 0;
	apuBufferCounter = 0;
	apuBufferFilled = 0;
	for(int i = 0; i < 5; ++i){
		apuBuffer[i][0] = 0;
		apuCounterAcc[i] = 0;
	}
	bufferFillClock = 0;
	newDMCCycle = true;
}


apu::~apu(void)
{
}

void apu::init(){
	reset();
}

void apu::reset(){
	curCycle = 0;
	fcCycleCounter = 0;
	write4000(0);
	write4001(0);
	write4002(0);
	write4003(0);
	write4004(0);
	write4005(0);
	write4006(0);
	write4007(0);
	write4008(0);
	write400A(0);
	write400B(0);
	write400C(0);
	write400E(0);
	write400F(0);
	write4010(0);
	write4011(0);
	write4012(0);
	write4013(0);
	write4015(0);
	write4017(0);
	sq1Env.counter = 0;
	sq2Env.counter = 0;
	noiseEnv.counter = 0;
	dmcCounter = 0;
	dmcBytes = 0;
	sampleBuffer = 0;
	bitsRemaining = 0;
	shiftReg = 1;
	sq1Sweep.targetPeriod = 0;
	sq2Sweep.targetPeriod = 0;
}

void apu::runCatchUp(unsigned int cycle){
	while(curCycle < cycle){
		if(fcMode5Step){
			switch (fcCycleCounter){
			case FC5STEP1:
				clockFC1();
				clockFC2();
				break;
			case FC5STEP2:
				clockFC1();
				break;
			case FC5STEP3:
				clockFC1();
				clockFC2();
				break;
			case FC5STEP4:
				clockFC1();
				break;
			case FC5STEP5:
				fcCycleCounter = -1;
				break;
			}
		}
		else{
			switch (fcCycleCounter){
			case FC4STEP1:
				clockFC1();
				break;
			case FC4STEP2:
				clockFC1();
				clockFC2();
				break;
			case FC4STEP3:
				clockFC1();
				break;
			case FC4STEP4:
				clockFC1();
				clockFC2();
				fcCycleCounter = -1;
				if(!fcInterruptDisable) signalIRQ = true;
				break;
			}
		}
        if ((curCycle & 0x01) == 0x00) {
            //run at even cpu cycles
			//clockSq1Timer();
			//clockSq2Timer();
	        clockDMC();
        }
		++bufferFillClock;
		if(bufferFillClock >= mixer->clockPerSample){
			fillAPUBuffer();	
			bufferFillClock -= mixer->clockPerSample;
		}
		if(fcCycleCounter == -1){
			mixer->resumeLastMusic();
		}
		++curCycle;
		++fcCycleCounter;
	}
	if(signalIRQ){
		cpuCore->setIRQ();
	}
}



	
Uint8 apu::readReg(Uint8 address){
	return (address == 0x15? read4015(): 0);
}

void apu::writeReg(Uint8 address, Uint8 data){
	//if(cpuCore->runLog){
	//	char tps[64];
	//	sprintf(tps, "  address:%02X data:%02X \n", address, data );
	//	cpuCore->myfile << tps;
	//}

	switch(address){
	case 0:
		write4000(data);
		break;
	case 1:
		write4001(data);
		break;
	case 2:
		write4002(data);
		break;
	case 3:
		write4003(data);
		break;
	case 4:
		write4004(data);
		break;
	case 5:
		write4005(data);
		break;
	case 6:
		write4006(data);
		break;
	case 7:
		write4007(data);
		break;
	case 8:
		write4008(data);
		break;
	case 0x0A:
		write400A(data);
		break;
	case 0x0B:
		write400B(data);
		break;
	case 0x0C:
		write400C(data);
		break;
	case 0x0E:
		write400E(data);
		break;
	case 0x0F:
		write400F(data);
		break;
	case 0x10:
		write4010(data);
		break;
	case 0x11:
		write4011(data);
		break;
	case 0x12:
		write4012(data);
		break;
	case 0x13:
		write4013(data);
		break;
	case 0x15:
		write4015(data);
		break;
	case 0x17:
		write4017(data);
		break;

	}
}

//sq1
void apu::write4000(Uint8 data){
	reg[0] = data;
	sq1Duty = (data >> 6);
	lc[CHANNEL_SQUARE1].halted = ((data & 0x20) != 0);
	sq1Env.loop = lc[CHANNEL_SQUARE1].halted;
	sq1Env.disableDecay = ((data & 0x10) != 0);
	if(sq1Env.disableDecay)
		sq1Env.constVol = (data & 0x0F);
	else
		sq1Env.dividerPeriod = ((data & 0x0F) + 1);
	vol[CHANNEL_SQUARE1] = envVol(sq1Env);
}

void apu::write4001(Uint8 data){
	reg[1] = data;
	sq1Sweep.enabled = ((data & 0x80) != 0);
	sq1Sweep.dividerPeriod = ((data >> 4) & 0x07) + 1;
	sq1Sweep.negate = ((data & 0x08) != 0);
	sq1Sweep.shift = (data & 0x07);
	sq1Sweep.reload = true;
}

void apu::write4002(Uint8 data){
	reg[2] = data;
	channelPeriod[CHANNEL_SQUARE1] &= 0x0700;
	channelPeriod[CHANNEL_SQUARE1] |= data;
	sq1Timer = channelPeriod[CHANNEL_SQUARE1];
}

void apu::write4003(Uint8 data){
	reg[3] = data;
	channelPeriod[CHANNEL_SQUARE1] &= 0x00FF;
	channelPeriod[CHANNEL_SQUARE1] |= ((data & 0x07) << 8);
	sq1Timer = channelPeriod[CHANNEL_SQUARE1];
	lc[CHANNEL_SQUARE1].length = lcLoadValue[data >> 3];
	if(lc[CHANNEL_SQUARE1].enabled){
		lc[CHANNEL_SQUARE1].currentVal = lc[CHANNEL_SQUARE1].length;
		sq1Env.startFlag = true;
	}
	else{
		lc[CHANNEL_SQUARE1].currentVal = 0;
	}
}


void apu::write4004(Uint8 data){
	reg[4] = data;
	sq2Duty = (data >> 6);
	lc[CHANNEL_SQUARE2].halted = ((data & 0x20) != 0);
	sq2Env.loop = lc[CHANNEL_SQUARE2].halted;
	sq2Env.disableDecay = ((data & 0x10) != 0);
	if(sq2Env.disableDecay)
		sq2Env.constVol = (data & 0x0F);
	else
		sq2Env.dividerPeriod = ((data & 0x0F) + 1);
	vol[CHANNEL_SQUARE2] = envVol(sq2Env);
}

void apu::write4005(Uint8 data){
	reg[5] = data;
	sq2Sweep.enabled = ((data & 0x80) != 0);
	sq2Sweep.dividerPeriod = ((data >> 4) & 0x07) + 1;
	sq2Sweep.negate = ((data & 0x08) != 0);
	sq2Sweep.shift = (data & 0x07);
	sq2Sweep.reload = true;
}

void apu::write4006(Uint8 data){
	reg[6] = data;
	channelPeriod[CHANNEL_SQUARE2] &= 0x0700;
	channelPeriod[CHANNEL_SQUARE2] |= data;
	sq2Timer = channelPeriod[CHANNEL_SQUARE2];
}

void apu::write4007(Uint8 data){
	reg[7] = data;
	channelPeriod[CHANNEL_SQUARE2] &= 0x00FF;
	channelPeriod[CHANNEL_SQUARE2] |= ((data & 0x07) << 8);
	sq2Timer = channelPeriod[CHANNEL_SQUARE2];
	lc[CHANNEL_SQUARE2].length = lcLoadValue[data >> 3];
	if(lc[CHANNEL_SQUARE2].enabled){
		lc[CHANNEL_SQUARE2].currentVal = lc[CHANNEL_SQUARE2].length;
		sq2Env.startFlag = true;
	}
	else{
		lc[CHANNEL_SQUARE2].currentVal = 0;
	}
}

void apu::write4008(Uint8 data){
	reg[8] = data;
	lc[CHANNEL_TRIANGLE].halted = ((data & 0x80) != 0);
	linearCounter.enabled  = ((data & 0x80) != 0);
	linearCounter.length = (data & 0x7F);
	if(linearCounter.enabled) linearCounter.currentVal = linearCounter.length;
}

void apu::write400A(Uint8 data){
	reg[0x0A] = data;
	channelPeriod[CHANNEL_TRIANGLE] &= 0xFF00;
	channelPeriod[CHANNEL_TRIANGLE] |= data;
}

void apu::write400B(Uint8 data){
	reg[0x0B] = data;
	lc[CHANNEL_TRIANGLE].length = lcLoadValue[data >> 3];
	if(lc[CHANNEL_TRIANGLE].enabled) lc[CHANNEL_TRIANGLE].currentVal = lc[CHANNEL_TRIANGLE].length;
	linearCounter.halted = true;
	channelPeriod[CHANNEL_TRIANGLE] &= 0x00FF;
	channelPeriod[CHANNEL_TRIANGLE] |= ((data & 0x07) << 8);
}

void apu::write400C(Uint8 data){
	reg[0x0C] = data;
	lc[CHANNEL_NOISE].halted = ((data & 0x20) != 0);
	noiseEnv.loop = lc[CHANNEL_NOISE].halted;
	noiseEnv.disableDecay = ((data & 0x10) != 0);
	if(noiseEnv.disableDecay)
		noiseEnv.constVol = (data & 0x0F);
	else
		noiseEnv.dividerPeriod = ((data & 0x0F) + 1);
	vol[CHANNEL_NOISE] = envVol(noiseEnv);
}


void apu::write400E(Uint8 data){
	reg[0x0E] = data;
	noiseModeFlag = ((data & 0x80) != 0);
	channelPeriod[CHANNEL_NOISE] = noiseLen[data & 0x0F];
}

void apu::write400F(Uint8 data){
	reg[0x0F] = data;
	lc[CHANNEL_NOISE].length = lcLoadValue[data >> 3];
	if(lc[CHANNEL_NOISE].enabled) lc[CHANNEL_NOISE].currentVal = lc[CHANNEL_NOISE].length;
	noiseEnv.startFlag = true;
}

void apu::shiftNoiseReg(){
	Uint16 feedBack;
	if(noiseModeFlag)
		feedBack = ((shiftReg & 0x0001) ^ ((shiftReg & 0x0040) >> 6));
	else
		feedBack = ((shiftReg & 0x0001) ^ ((shiftReg & 0x0002) >> 1));
	shiftReg = ((shiftReg >> 1) | (feedBack << 14));
}


void apu::write4010(Uint8 data){
	reg[10] = data;
	irqEnabled = ((data & 0x80) != 0);
	if(!irqEnabled){
		signalIRQ = false;
	}
	dmcLoop = ((data & 0x40) != 0);
	dmcOutPutRate = data & 0x0F;
	channelPeriod[CHANNEL_DMC] = dmcRate[dmcOutPutRate];
	dmcPeriodCounter = 0;
}

void apu::write4011(Uint8 data){
	reg[11] = data;
	dmcCounter = data & 0x7F;
}

void apu::write4012(Uint8 data){
	reg[12] = data;
	sampleAddress = (data << 6) | 0xC000;
	newDMCCycle = true;
}

void apu::write4013(Uint8 data){
	reg[13] = data;
	sampleLength = (data << 4) | 0x01;
	newDMCCycle = true;
}

void apu::write4015(Uint8 data){
	reg[15] = data;
	lc[CHANNEL_SQUARE1].enabled = ((data & 0x01) != 0);
	lc[CHANNEL_SQUARE2].enabled = ((data & 0x02) != 0);
	lc[CHANNEL_TRIANGLE].enabled = ((data & 0x04) != 0);
	linearCounter.enabled = ((data & 0x04) != 0);
	lc[CHANNEL_NOISE].enabled = ((data & 0x08) != 0);

	dmcEnabled = ((data & 0x10) != 0);
	if(!dmcEnabled){
		dmcBytes = 0;
	}
	else if(dmcBytes == 0){
		curAddress = sampleAddress;
		dmcBytes = sampleLength;
		newDMCCycle = true;
	}

	for(Uint8 i = 0; i < 4; ++i){
		if(!lc[i].enabled) lc[i].currentVal = 0;
	}
	if(!linearCounter.enabled) linearCounter.currentVal = 0;
	signalDMC = false;
}

Uint8 apu::read4015(){
	reg[15] = 0x00;
	if(signalDMC) reg[15] |= 0x80;
	if(signalIRQ) reg[15] |= 0x40;
	if(dmcBytes > 0) reg[15] |= 0x10;
	if(lc[CHANNEL_NOISE].currentVal != 0) reg[15] |= 0x08;
	if(lc[CHANNEL_TRIANGLE].currentVal != 0) reg[15] |= 0x04;
	if(lc[CHANNEL_SQUARE2].currentVal != 0) reg[15] |= 0x02;
	if(lc[CHANNEL_SQUARE1].currentVal != 0) reg[15] |= 0x01;
	signalIRQ = false;
	return reg[15];
}

void apu::clockFC1(){
	clockEnv(sq1Env);
	vol[CHANNEL_SQUARE1] = envVol(sq1Env);
	clockEnv(sq2Env);			
	vol[CHANNEL_SQUARE2] = envVol(sq2Env);
	clockEnv(noiseEnv);
	vol[CHANNEL_NOISE] = envVol(noiseEnv);
	clockLinear();
}

void apu::clockFC2(){
	clockLC();
	clockSweep1();
	clockSweep2();		
}

void apu::clockLC(){
	for(Uint8 i = 0; i < 4; ++i){
		if(lc[i].currentVal > 0 && !lc[i].halted) --(lc[i].currentVal);
	}
}

Uint8 apu:: envVol(envelope e){
	return (e.disableDecay? e.constVol:e.counter);
}

void apu::clockEnv(envelope &e){
	if(e.startFlag){
		e.startFlag = false;
		e.counter = 15;
		e.dividerCounter = e.dividerPeriod;
	}
	else{
		--(e.dividerCounter);
		if(e.dividerCounter == 0){
			if(e.counter > 0)
				--e.counter;
			else if(e.loop) 
				e.counter = 15;
			e.dividerCounter = e.dividerPeriod;
		}
	}
}

void apu::clockSweep1(){
	Uint8 oldCounter;
	Uint16 dif;
	bool adjustPeriod;

	adjustPeriod = false;
	oldCounter = sq1Sweep.dividerCounter;
	if(sq1Sweep.reload){
		sq1Sweep.reload = false;
		sq1Sweep.dividerCounter = sq1Sweep.dividerPeriod; 
		if(oldCounter == 0){
			adjustPeriod = true;
		}
	}
	else if(sq1Sweep.dividerCounter > 0){
		--(sq1Sweep.dividerCounter);
	}	
	else if(sq1Sweep.enabled){
		sq1Sweep.dividerCounter = sq1Sweep.dividerPeriod; 
		adjustPeriod = true;
	}
	if(adjustPeriod){
		dif = (channelPeriod[CHANNEL_SQUARE1] >> sq1Sweep.shift);
		if(sq1Sweep.negate)
			sq1Sweep.targetPeriod = channelPeriod[CHANNEL_SQUARE1] - (dif - 1);
		else
			sq1Sweep.targetPeriod = channelPeriod[CHANNEL_SQUARE1] + dif;
		if(channelPeriod[CHANNEL_SQUARE1] >= 8 && sq1Sweep.targetPeriod <= 0x7FF && sq1Sweep.shift > 0){
			channelPeriod[CHANNEL_SQUARE1] = sq1Sweep.targetPeriod;
		}
	}
}


void apu::clockSweep2(){
	Uint8 oldCounter;
	Uint16 dif;
	bool adjustPeriod;


	adjustPeriod = false;
	oldCounter = sq2Sweep.dividerCounter;
	if(sq2Sweep.reload){
		sq2Sweep.reload = false;
		sq2Sweep.dividerCounter = sq2Sweep.dividerPeriod; 
		if(oldCounter == 0){
			adjustPeriod = true;
		}
	}
	else if(sq2Sweep.dividerCounter > 0){
		--(sq2Sweep.dividerCounter);
	}	
	else if(sq2Sweep.enabled){
		sq2Sweep.dividerCounter = sq2Sweep.dividerPeriod; 
		adjustPeriod = true;
	}
	if(adjustPeriod){
		dif = (channelPeriod[CHANNEL_SQUARE2] >> sq2Sweep.shift);
		if(sq2Sweep.negate)
			sq2Sweep.targetPeriod = channelPeriod[CHANNEL_SQUARE2] - dif;
		else
			sq2Sweep.targetPeriod = channelPeriod[CHANNEL_SQUARE2] + dif;
		if(channelPeriod[CHANNEL_SQUARE2] >= 8 && sq2Sweep.targetPeriod <= 0x7FF && sq2Sweep.shift > 0){
			channelPeriod[CHANNEL_SQUARE2] = sq2Sweep.targetPeriod;
		}
	}
}


void apu::write4017(Uint8 data){
	fcMode5Step = ((data & 0x80) != 0);
	fcInterruptDisable = ((data & 0x40) != 0);
	if(fcInterruptDisable) signalIRQ = false;
	fcCycleCounter = -2;
	if(fcMode5Step){
		clockFC1();
		clockFC2();
	}
}

void apu::clockLinear(){
	if(linearCounter.halted)
		linearCounter.currentVal = linearCounter.length;
	else if(linearCounter.currentVal != 0)
		--(linearCounter.currentVal);
	if(!linearCounter.enabled) linearCounter.halted = false;
}

void apu::clockDMC(){
	if(dmcEnabled){
		++dmcPeriodCounter;
		if(dmcPeriodCounter >= channelPeriod[CHANNEL_DMC]){
			if(!dmcSilence){
				if(((sampleBuffer & 0x01) == 0) && dmcCounter > 1){
					dmcCounter -= 2;
				}
				else if(((sampleBuffer & 0x01) != 0) && dmcCounter < 126){
					dmcCounter += 2;
				}
				sampleBuffer >>= 1;
				--bitsRemaining;
				if(bitsRemaining == 0) newDMCCycle = true;
			}
			if(newDMCCycle){
				newDMCCycle = false;
				dmcSilence = true;
				if(dmcEnabled){
					if(dmcBytes > 0){
						sampleBuffer = memDat->cpuBusRead(curAddress);
						if(curAddress == 0xFFFF){
							curAddress = 0x8000;
						}
						else{
							++curAddress;
						}
						--dmcBytes;
						if(dmcBytes == 0){
							if(dmcLoop){
								curAddress = sampleAddress;
								dmcBytes = sampleLength;
							}
							else if(irqEnabled){
								signalIRQ = true;
							}
						}
						dmcSilence = false;
					}
				}
				bitsRemaining = 8;
			}
			dmcPeriodCounter = 0;
		}
	}
	apuCounterAcc[CHANNEL_DMC] += apuAccAR[dmcCounter];
}

void apu::clockSq1Timer(){
	if(sq1Timer > 0){
		--sq1Timer;
	}
	else{
		sq1Timer = channelPeriod[CHANNEL_SQUARE1];
		++sq1SeqCounter;
		if(sq1SeqCounter >= 8) sq1SeqCounter = 0;
	}
	if(lc[CHANNEL_SQUARE1].enabled 
		&& (lc[CHANNEL_SQUARE1].currentVal > 0) 
		&& channelPeriod[CHANNEL_SQUARE1] >= 8 
		&& sq1Sweep.targetPeriod <= 0x07FF 
		&& dutyCycle[sq1Duty][sq1SeqCounter]){
		apuCounterAcc[CHANNEL_SQUARE1] += apuAccAR[(sq1Env.disableDecay? sq1Env.constVol:sq1Env.counter)];
	}
}

void apu::clockSq2Timer(){
	if(sq2Timer > 0){
		--sq2Timer;
	}
	else{
		sq2Timer = channelPeriod[CHANNEL_SQUARE2];
		++sq2SeqCounter;
		if(sq2SeqCounter >= 8) sq2SeqCounter = 0;
	}
	if(lc[CHANNEL_SQUARE2].enabled 
		&& (lc[CHANNEL_SQUARE2].currentVal > 0) 
		&& channelPeriod[CHANNEL_SQUARE2] >= 8 
		&& sq2Sweep.targetPeriod <= 0x07FF 
		&& dutyCycle[sq2Duty][sq2SeqCounter]){
		apuCounterAcc[CHANNEL_SQUARE2] += apuAccAR[(sq2Env.disableDecay? sq2Env.constVol:sq2Env.counter)];
	}
}

void apu::fillAPUBuffer(){
	for(int i = 0; i < 5; ++i){
		apuBuffer[i][(apuBufferCounter + apuBufferFilled) % APU_BUFFER_SIZE] = apuCounterAcc[i];
		apuCounterAcc[i] = 0;
	}
    ++apuBufferFilled;
    if (apuBufferFilled >= APU_BUFFER_SIZE) {
        apuBufferCounter = ((apuBufferCounter + apuBufferFilled)) % APU_BUFFER_SIZE;
        apuBufferFilled = APU_BUFFER_SIZE;
    }
}

void apu::resetCycleCount(){
	curCycle = curCycle % 341;
}


void apu::saveState(fstream* statefile){
    statefile->write((char *)(this), sizeof(apu));
}


void apu::loadState(fstream* statefile){
    statefile->read((char *)(this), sizeof(apu));
}
