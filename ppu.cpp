#include "StdAfx.h"
#include "sysState.h"
#include <time.h>
#include <Shlwapi.h>


ppu::ppu(void)
{
	for(int i = 0; i < 34; ++i){
		bgPatternIDFretched[i] = 0;
		bgPaletteFretched[i] = 0;
		bgPatternDataFretched[i][0] = 0;
		bgPatternDataFretched[i][1] = 0;
		bgAddressFretched[i] = BAD_ADDRESS;
	}
	for(int i = 0; i < 8; ++i){
		spRowFretched[i] = 0;
		spPatternDataFretched[i][0] = 0;
		spPatternDataFretched[i][1] = 0;
		spAddressFretched[i] = BAD_ADDRESS;
	}

}


ppu::~ppu(void)
{
}

void ppu::init(){
	initState();
	sprOverflow = false;
	spr0hit = false;
	write2003(0);
}

void ppu::reset(){
	initState();
	writeDisabledPeriod = 29658;
}

void ppu::initState(){
	writeDisabledPeriod = 0;
	for(int i = 0; i < 8; ++i){
		reg[i] = 0;
	}
	newWrite = true;
	write2000(0);
	write2001(0);
	lastRegWrite = 0;
	offsetX = 0;
	tmpVRAMAddress = 0;
	vRAMAddress = 0;
	screenX = 0;
	screenY = 241;
	curCycle = 0;
	vBlankFlag = false;
	oldVBlankFlag = false;
	signalNMI = false;
	signalFrameReady = false;
	oddFrame = false;
	frameCount = 0;
	bgLoadingY = 0;

	//init fretch and eval
	ZeroMemory(bgPatternIDFretched, 34);
	ZeroMemory(bgPaletteFretched, 34);
	bgTileToLoad = 0;
	bgFretchNameTableAddress = 0;

	spTileToLoad = 0;
	ZeroMemory(spPatternDataFretched, 16);
	oam2AddressToWrite = 0;
	spBytesToCopy = 0;
}



Uint16 ppu::getSprPatternAddress(Uint8 patternID){
	if(useLargeSpr)
		return ((patternID & 0x01) << 12) | ((patternID & 0xFE) << 4);
	else
		return sprPatternTable | (patternID << 4);
}


void ppu::runStep(){
	Uint8 bgPix;
	Uint8 spPix;
	Uint8 colourID;

	//a new frame
	if(screenX == 0 && screenY == 0){
		vid->startFrame();
		spr0hitDone = false;
		++frameCount;
	}

	if(screenX == 0 && screenY < 240){
		vid->initScanlineData(screenY);
	}
	if(screenY < 240 && (screenX % 8 == 0) && screenX <= 256 && enabled){
		vid->setBGStripData(screenY, screenX >> 3);
	}


	//if(screenY < 240 && screenX == 256 && enabled){
	//	vid->setScanlineData();
	//}

	if(screenY < 240 && screenX < 256 && enabled){
		if(screenX == 0){
			currentBgTile = 0;
			currentBgX = offsetX;
			for(int i = 0; i < 8; ++i){
				currentSpX[i] = 0;
			}
			for(int i = 0; i < 32; ++i){
				tmpSprRAM2[i] = memDat->sprRAM2[i];
			}
		}

		//render pixel
		//get bg pix
		bgPix = ((bgPatternDataFretched[currentBgTile][0] >> (7 - currentBgX)) & 0x01) | (((bgPatternDataFretched[currentBgTile][1] >> (7 - currentBgX)) & 0x01) << 1);
		for (int i = 0; i < 8; ++i){
			if(tmpSprRAM2[i * 4 + 3] == 0 && currentSpX[i] == 0){
				vid->setSPStripData(screenY, screenX, i);
			}
		}
		//check spr
		for (int i = 0; i < 8; ++i){
			spPix = 0;
			if(tmpSprRAM2[i * 4] != 0xFF){
				if(tmpSprRAM2[i * 4 + 3] == 0 && currentSpX[i] < 8){
					if(spPatternDataFretched[i][0] != 0 || spPatternDataFretched[i][1] != 0){
						//check hflip
						if(((tmpSprRAM2[i * 4 + 2] >> 6) & 0x01) != 0){
							spPix = ((spPatternDataFretched[i][0] >> currentSpX[i]) & 0x01) | (((spPatternDataFretched[i][1] >> currentSpX[i]) & 0x01) << 1);
						}
						else{
							spPix = ((spPatternDataFretched[i][0] >> (7 - currentSpX[i])) & 0x01) | (((spPatternDataFretched[i][1] >> (7 - currentSpX[i])) & 0x01) << 1);					
						}					
						if(spPix != 0){
							if(lastIsSp0 && bgPix != 0 && !spr0hit && !spr0hitDone && i == 0 && showBG && showSpr && ((showBGOnLeft && showSprOnLeft) || screenX >= 8) && screenX < 255){
								spr0hit = true;
								spr0hitDone = true;
							}
							if(((tmpSprRAM2[i * 4 + 2] >> 5) & 0x01) != 0){
								//sp is back
								if(bgPix == 0){
									//render sp
									colourID = memDat->paletteTable[(tmpSprRAM2[i * 4 + 2] & 0x03) | 0x04][spPix];
								}
								else{
									//render bg
									colourID = memDat->paletteTable[bgPaletteFretched[currentBgTile]][bgPix];
								}
							}
							else{
								//render sp
								colourID = memDat->paletteTable[(tmpSprRAM2[i * 4 + 2] & 0x03) | 0x04][spPix];
							}
							break;
						} 
					}
				}
			}
		}


		++currentBgX;
		if(currentBgX == 8){
			++currentBgTile;
			currentBgX = 0;
		}
		//shift all sprite pixel
		for (int i = 0; i < 8; ++i){
			if(tmpSprRAM2[i * 4] != 0xFF){
				if(tmpSprRAM2[i * 4 + 3] == 0){
					++currentSpX[i];
				}		
				else{
					--tmpSprRAM2[i * 4 + 3];
				}
			}
		}
	}
	
	//prerender line
	if(screenY == 261){
		if(screenX == 0){
			vBlankFlag = false;
			spr0hit = false;
			sprOverflow = false;
		}
		if(screenX == 304 && enabled){
			//vertical scroll bits are reloaded if rendering is enabled
			//v:111101111100000=t:111101111100000
			vRAMAddress = (vRAMAddress & 0x041F) | (tmpVRAMAddress & 0xFBE0);
			bgLoadingY = (vRAMAddress >> 12) & 0x07;
		}
		if(screenX == 328 && showBG && oddFrame){
			//skip one cycle on odd frame
			++screenX;
		}
	}

	//sprite evaluation
	if(screenY < 240 && enabled){
		if(screenX == 0){
			enableWriteOAM2 = true;
			spAddressToEval = 0;
			oam2AddressToWrite = 0;
			spFound = 0;
			spEvalStateCheckY = true;
			spYInRange = false;
			isSp0 = false;
		}
		if(screenX < 256){
			if((screenX & 0x01) == 0){
				//even cycles
				if(screenX < 64){
					if(screenX == 0){
						spBytesToCopy = 32;
					}
					//init OAM2 to $FF
					dataToWriteOAM2 = 0xFF;
				}
				else{
					if(spAddressToEval < 256){
						if(screenX == 64){
							oam2AddressToWrite = 0;
						}
						//read OAM
						dataToWriteOAM2 = memDat->sprRAM[spAddressToEval];
						if(spEvalStateCheckY){
							//check Y in range
							spYInRange = (dataToWriteOAM2 <= screenY && (dataToWriteOAM2 + sprHeight) > screenY);
							if(spYInRange){
								if(spFound < 8){
									if(spFound == 0 && spAddressToEval == 0){
										isSp0 = true; 
									}
									++spFound;
								}
								else{
									sprOverflow = true;
								}
								spEvalStateCheckY = false;
								spBytesToCopy = 4;
								++spAddressToEval;
							}
							else{
								spAddressToEval += 4;
								if(spFound == 8){
									++spAddressToEval;
								}
							}
						}
						else{
							++spAddressToEval;
						}
					}
					else{
						//all sprite passed
					}
				}
			}
			else{
				//On odd cycles, data is written to secondary OAM
				if(enableWriteOAM2){
					if(spBytesToCopy > 0){
						memDat->sprRAM2[oam2AddressToWrite] = dataToWriteOAM2;
						++oam2AddressToWrite;
					}
				}
				else{
					//(unless writes are inhibited, in which case it will read the value in secondary OAM instead)
					dataToWriteOAM2 = memDat->sprRAM2[oam2AddressToWrite];
				}

				if(spBytesToCopy > 0){
					--spBytesToCopy;
					if(spBytesToCopy == 0){
						spEvalStateCheckY = true;
						if(spFound == 8){
							enableWriteOAM2 = false;
						}
					}
				}
			}
		}
		else if(screenX == 256){
			lastIsSp0 = isSp0;
		}
		else if(screenX < 320){
			//fretch tiles see below
		}
		else{
			//read first byte in OAM2
		}
	}

	//reset bg fretch
	if(screenX == 320){
		bgFretchNameTableAddress = 0x2000 | (vRAMAddress & 0x0FFF);
		bgTileToLoad = 0;
	}
	if(1 == 0){
		saveVRam(setting->exeDir + "\\screen\\");
	}
	//fretch tile data
	if((screenY < 240 || screenY == 261) && enabled){
		if(screenX < 256 || (screenX >= 320 && screenX < 336)){
			//bg fretch
			
			switch(screenX % 8){
			case 0:
				//start read name table byte
				break;
			case 1:
				//finish read name table byte
				bgPatternIDFretched[bgTileToLoad] = memDat->ppuBusRead(bgFretchNameTableAddress);
				break;
			case 2:
				//start read attribute table byte
				break;
			case 3:
				//finish read attribute table byte
				bgPaletteFretched[bgTileToLoad] = mmc->getTilePalette((bgFretchNameTableAddress >> 10) & 0x0001, (bgFretchNameTableAddress >> 11) & 0x0001,  bgFretchNameTableAddress & 0x001F,  (bgFretchNameTableAddress >> 5) & 0x001F);
				break;
			case 4:
				//start read tile bitmap A
				break;
			case 5:
				//finish read tile bitmap A
				mmc->getPattern(bgTilePatternTable | (bgPatternIDFretched[bgTileToLoad] << 4), bgLoadingY, true, bgPatternDataFretched[bgTileToLoad][0], bgAddressFretched[bgTileToLoad], bgRAMAddress[bgTileToLoad]);
				break;
			case 6:
				//start read tile bitmap B
				break;
			case 7:
				
				//finish read tile bitmap B
				mmc->getPattern(bgTilePatternTable | (bgPatternIDFretched[bgTileToLoad] << 4), bgLoadingY, false, bgPatternDataFretched[bgTileToLoad][1], bgAddressFretched[bgTileToLoad], bgRAMAddress[bgTileToLoad]);
				++bgTileToLoad;
				if((bgFretchNameTableAddress & 0x001F) == 0x001F){
					//end of name table, flip bit 10 to switch table
					if((bgFretchNameTableAddress & 0x0400) == 0){
						bgFretchNameTableAddress = (bgFretchNameTableAddress | 0x0400) & 0xFFE0;
					}
					else{
						bgFretchNameTableAddress = bgFretchNameTableAddress & 0xFBE0;
					}
				}
				else{
					++bgFretchNameTableAddress;
				}
				
				break;
				
			}
			
		}
		else if(screenX < 320){
			if(screenX == 256){

				spTileToLoad = 0;
				bgLoadingY = (vRAMAddress >> 12) & 0x07;
				++bgLoadingY;
				if(bgLoadingY == 8){
					bgLoadingY = 0;
					if((vRAMAddress & 0x03E0) == 0x03E0){
						//reached max coarse y, flip back to 0
						vRAMAddress = vRAMAddress & 0xFC1F;
					}
					else if((vRAMAddress & 0x03A0) == 0x03A0){
						//end of name table, flip bit 11 to switch table
						if((vRAMAddress & 0x0800) == 0){
							vRAMAddress = (vRAMAddress | 0x0800) & 0xFC1F;
						}
						else{
							vRAMAddress = vRAMAddress & 0xF41F;
						}
					}
					else{
						vRAMAddress += 0x0020;
					}
				}
				vRAMAddress = (vRAMAddress & 0x0FFF) | (bgLoadingY << 12); 
			}
			if(screenX == 257){
				//v:0000010000011111=t:0000010000011111
				vRAMAddress = (vRAMAddress & 0xFBE0) | (tmpVRAMAddress & 0x041F);
				
			}
			
			//sprite fretch
			if(spTileToLoad < 8){
				switch(screenX % 8){
				case 0:
					//start read garbage name table byte
					break;
				case 1:
					//finish read garbage name table byte
					break;
				case 2:
					//start read garbage name table byte
					break;
				case 3:
					//finish read garbage name table byte
					break;
				case 4:
					//start read tile bitmap A
					break;
				case 5:
					//finish read tile bitmap A
					//check vertical flip
					spRowFretched[spTileToLoad] = ((memDat->sprRAM2[spTileToLoad * 4 + 2] >> 7) != 0 ? sprHeight - 1 - (screenY - memDat->sprRAM2[spTileToLoad * 4]): screenY - memDat->sprRAM2[spTileToLoad * 4]);
					mmc->getPattern(getSprPatternAddress(memDat->sprRAM2[spTileToLoad * 4 + 1]), spRowFretched[spTileToLoad], true, spPatternDataFretched[spTileToLoad][0], spAddressFretched[spTileToLoad], spRAMAddress[spTileToLoad]);
					break;
				case 6:
					//start read tile bitmap B
					break;
				case 7:
					//finish read tile bitmap B
					mmc->getPattern(getSprPatternAddress(memDat->sprRAM2[spTileToLoad * 4 + 1]), spRowFretched[spTileToLoad], false, spPatternDataFretched[spTileToLoad][1], spAddressFretched[spTileToLoad], spRAMAddress[spTileToLoad]);
					//if spTileToLoad > sprite count then load dummy
					break;
				}
			}
			if(screenX % 8 == 7) ++spTileToLoad;
		}
		else if(screenX < 340){
			//two dummy read
			switch(screenX){
			case 336:
				//start read name table byte
				break;
			case 337:
				//finish read name table byte
				break;
			case 338:
				//start read name table byte
				break;
			case 339:
				//finish read name table byte
				break;
			}
		}
		else{
			//idle
		}
	}
	else if(screenY == 240){
		//idle
		if(screenX == 340){
			vBlankFlag = true;

		}
	}
	else if(screenY == 241){
	}
	else{
		//idle
	}

	++screenX;
	if(screenX == 341){
		screenX = 0;
		++screenY;
		if(screenY == 240){
			signalFrameReady = true;
		}
		if(screenY == 262){
			screenY = 0;
		}
	}

	if(enableVBlank && vBlankFlag && !oldVBlankFlag){
		signalNMI = true;
	}
	oldVBlankFlag = vBlankFlag;
	if(writeDisabledPeriod > 0) --writeDisabledPeriod;
	++curCycle;

}

void ppu::runCatchUp(unsigned int cycle){
	while(curCycle < cycle) runStep();
}

Uint8 ppu::readReg(Uint8 address){
	switch(address){
	case 2:
		return read2002();
		break;
	case 4:
		return read2004();
		break;
	case 7:
		return read2007();
		break;
	}
	return 0;
}

void ppu::writeReg(Uint8 address, Uint8 data){
	lastRegWrite = data;
	switch(address){
	case 0:
		write2000(data);
		break;
	case 1:
		write2001(data);
		break;
	case 3:
		write2003(data);
		break;
	case 4:
		write2004(data);
		break;
	case 5:
		write2005(data);
		break;
	case 6:
		write2006(data);
		break;
	case 7:
		write2007(data);
		break;
	}
}

void ppu::write2000(Uint8 data){
	if(writeDisabledPeriod == 0){
		tmpVRAMAddress &= 0xF3FF;
		tmpVRAMAddress |= ((data & 0x03) << 10);
		baseNameTableAddress = (data & 0x03);
		aIncSize = ((data & 0x04) != 0? 32: 1);
		sprPatternTable = ((data & 0x08) != 0? 0x1000: 0x0000);
		bgTilePatternTable = ((data & 0x10) != 0? 0x1000: 0x0000);
		useLargeSpr = ((data & 0x20) != 0);
		sprHeight = (useLargeSpr?16:8);
		enableVBlank = ((data & 0x80) != 0);
		reg[0] = data;
	}
}

void ppu::write2001(Uint8 data){
	if(writeDisabledPeriod == 0){
		useGrayscale = ((data & 0x01) != 0);
		showBGOnLeft = ((data & 0x02) != 0);
		showSprOnLeft = ((data & 0x04) != 0);
		showBG = ((data & 0x08) != 0);
		showSpr = ((data & 0x10) != 0);
		intensifyR = ((data & 0x20) != 0);
		intensifyG = ((data & 0x40) != 0);
		intensifyB = ((data & 0x80) != 0);
		enabled = ((data & 0x18) != 0);
		reg[1] = data;
	}
}

Uint8 ppu::read2002(){
	reg[2] = lastRegWrite & 0x1F;
	if(sprOverflow) reg[2] |= 0x20;
	if(spr0hit) reg[2] |= 0x40;
	if(oldVBlankFlag) reg[2] |= 0x80;

	vBlankFlag = false;
	newWrite = true;

	return reg[2];
}

void ppu::write2003(Uint8 data){
	reg[3] = data;
}

Uint8 ppu::read2004(){
	if(screenY >= 240){
		return memDat->sprRAM[reg[3]];
	}
	else{
		return dataToWriteOAM2;
	}
}

void ppu::write2004(Uint8 data){
	memDat->sprRAM[reg[3]] = data;
	++reg[3];
}

void ppu::write2005(Uint8 data){
	//change scrolling by pixels so 3 LS bits are taken as offset 
	//and the remaining is the tile data index
	//activeAddress = 0yyyABYYYYYXXXXX
	//offsetX = xxx
	//AB = bit 0 and 1 of reg2000
	if(writeDisabledPeriod == 0){
		if(newWrite){
			offsetX = (data & 0x07);
			tmpVRAMAddress &= 0xFFE0;
			tmpVRAMAddress |= (data >> 3);
		}
		else{
			tmpVRAMAddress &= 0x0C1F;
			tmpVRAMAddress |= ((data & 0xF8) << 2);
			tmpVRAMAddress |= ((data & 0x07) << 12);
		}
		newWrite = !newWrite;
	}
}

void ppu::write2006(Uint8 data){
	if(writeDisabledPeriod == 0){
		if(newWrite){
			tmpVRAMAddress &= 0x00FF;
			tmpVRAMAddress |= ((data & 0x3F) << 8);
		}
		else{
			tmpVRAMAddress &= 0xFF00;
			tmpVRAMAddress |= data;
			vRAMAddress = tmpVRAMAddress;
			bgLoadingY = (vRAMAddress >> 12) & 0x07;
		}
		newWrite = !newWrite;
	}
}

Uint8 ppu::read2007(){
	Uint8 buffer;

	if(screenY < 240 && screenX < 256 && enabled){
		buffer = 0;
	}
	else{
		if(vRAMAddress < 0x3F00){
			buffer = reg[7];
			reg[7] = memDat->ppuBusRead(vRAMAddress);
		}
		else{
			buffer =  memDat->ppuBusRead(vRAMAddress);
			//read the mirrored value into buffer
			reg[7] = memDat->ppuBusRead(vRAMAddress & 0xEFFF);
		}
	}
	vRAMAddress += aIncSize;
	if(vRAMAddress > 0x3FFF){
		vRAMAddress -= 0x4000;
	}
	bgLoadingY = (vRAMAddress >> 12) & 0x07;
	return buffer;
}

void ppu::write2007(Uint8 data){
	if(!(screenY < 240 && screenX < 256 && enabled)){
		memDat->ppuBusWrite(vRAMAddress, data);
		vRAMAddress += aIncSize;
		if(vRAMAddress > 0x3FFF){
			vRAMAddress -= 0x4000;
		}
		bgLoadingY = (vRAMAddress >> 12) & 0x07;
	}
}

void ppu::transferDMA(Uint8 data){
	Uint16 address;
	address = (data << 8);
	for(Uint16 i = 0; i < 256; ++i){
		memDat->sprRAM[reg[3]] = memDat->cpuBusRead(address);
		++reg[3];
		++address;
	}
	cpuCore->runDMA();
}


void ppu::resetCycleCount(){
	curCycle = curCycle % 1023;
}

void ppu::saveState(fstream* statefile){
    statefile->write((char *)(&lastRegWrite), sizeof(Uint8));
    statefile->write((char *)(&enabled), sizeof(bool));
    statefile->write((char *)(&signalNMI), sizeof(bool));
    statefile->write((char *)(&signalFrameReady), sizeof(bool));
    statefile->write((char *)(&oddFrame), sizeof(bool));
    statefile->write((char *)(&screenX), sizeof(Uint16));
    statefile->write((char *)(&screenY), sizeof(Uint16));
    statefile->write((char *)(&curCycle), sizeof(Uint32));
    statefile->write((char *)(&frameCount), sizeof(Uint32));
    statefile->write((char *)(&writeDisabledPeriod), sizeof(unsigned int));
    statefile->write((char *)(reg), sizeof(Uint8) * 8);
    statefile->write((char *)(spriteList), sizeof(sprite) * 64);
    statefile->write((char *)(&baseNameTableAddress), sizeof(Uint8));
    statefile->write((char *)(&aIncSize), sizeof(Uint8));
    statefile->write((char *)(&sprPatternTable), sizeof(Uint16));
    statefile->write((char *)(&bgTilePatternTable), sizeof(Uint16));
    statefile->write((char *)(&useLargeSpr), sizeof(bool));
    statefile->write((char *)(&sprHeight), sizeof(Uint8));
    statefile->write((char *)(&enableVBlank), sizeof(bool));
    statefile->write((char *)(&useGrayscale), sizeof(bool));
    statefile->write((char *)(&showBGOnLeft), sizeof(bool));
    statefile->write((char *)(&showSprOnLeft), sizeof(bool));
    statefile->write((char *)(&showBG), sizeof(bool));
    statefile->write((char *)(&showSpr), sizeof(bool));
    statefile->write((char *)(&intensifyR), sizeof(bool));
    statefile->write((char *)(&intensifyG), sizeof(bool));
    statefile->write((char *)(&intensifyB), sizeof(bool));
    statefile->write((char *)(&sprOverflow), sizeof(bool));
    statefile->write((char *)(&spr0hit), sizeof(bool));
    statefile->write((char *)(&spr0hitDone), sizeof(bool));
    statefile->write((char *)(spr0PatternData), sizeof(Uint8) * 16);
    statefile->write((char *)(spr0PatternData2), sizeof(Uint8) * 16);
    statefile->write((char *)(&vBlankFlag), sizeof(bool));
    statefile->write((char *)(&oldVBlankFlag), sizeof(bool));
    statefile->write((char *)(&oamAddress), sizeof(Uint8));
    statefile->write((char *)(&newWrite), sizeof(bool));
    statefile->write((char *)(&offsetX), sizeof(Uint8));
    statefile->write((char *)(&tmpVRAMAddress), sizeof(Uint16));
    statefile->write((char *)(&vRAMAddress), sizeof(Uint16));
    statefile->write((char *)(&dataToWriteOAM2), sizeof(Uint8));
    statefile->write((char *)(&enableWriteOAM2), sizeof(bool));
    statefile->write((char *)(&spAddressToEval), sizeof(Uint16));
    statefile->write((char *)(&oam2AddressToWrite), sizeof(Uint16));
    statefile->write((char *)(&spFound), sizeof(Uint8));
    statefile->write((char *)(&spEvalStateCheckY), sizeof(bool));
    statefile->write((char *)(&spYInRange), sizeof(bool));
    statefile->write((char *)(&spBytesToCopy), sizeof(Uint8));
    statefile->write((char *)(&bgLoadingY), sizeof(Uint8));
    statefile->write((char *)(&bgTileToLoad), sizeof(Uint8));
    statefile->write((char *)(&bgFretchNameTableAddress), sizeof(Uint16));
    statefile->write((char *)(bgPatternIDFretched), sizeof(Uint8) * 34);
    statefile->write((char *)(bgPaletteFretched), sizeof(Uint8) * 34);
    statefile->write((char *)(bgPatternDataFretched), sizeof(Uint8) * 34 * 2);
    statefile->write((char *)(bgAddressFretched), sizeof(Uint32) * 34);
    statefile->write((char *)(bgRAMAddress), sizeof(Uint32) * 34);
    statefile->write((char *)(&spTileToLoad), sizeof(Uint8));
    statefile->write((char *)(&spPatternDataFretched), sizeof(Uint8) * 16);
    statefile->write((char *)(spRowFretched), sizeof(Uint8) * 8);
    statefile->write((char *)(spAddressFretched), sizeof(Uint32) * 8);
    statefile->write((char *)(spRAMAddress), sizeof(Uint32) * 8);
    statefile->write((char *)(&isSp0), sizeof(bool));
    statefile->write((char *)(&lastIsSp0), sizeof(bool));
    statefile->write((char *)(&currentBgTile), sizeof(Uint8));
    statefile->write((char *)(&currentBgX), sizeof(Uint8));
    statefile->write((char *)(currentSpX), sizeof(Uint16) * 8);
    statefile->write((char *)(tmpSprRAM2), sizeof(Uint8) * 32);
}


void ppu::loadState(fstream* statefile){
    statefile->read((char *)(&lastRegWrite), sizeof(Uint8));
    statefile->read((char *)(&enabled), sizeof(bool));
    statefile->read((char *)(&signalNMI), sizeof(bool));
    statefile->read((char *)(&signalFrameReady), sizeof(bool));
    statefile->read((char *)(&oddFrame), sizeof(bool));
    statefile->read((char *)(&screenX), sizeof(Uint16));
    statefile->read((char *)(&screenY), sizeof(Uint16));
    statefile->read((char *)(&curCycle), sizeof(Uint32));
    statefile->read((char *)(&frameCount), sizeof(Uint32));
    statefile->read((char *)(&writeDisabledPeriod), sizeof(unsigned int));
    statefile->read((char *)(reg), sizeof(Uint8) * 8);
    statefile->read((char *)(spriteList), sizeof(sprite) * 64);
    statefile->read((char *)(&baseNameTableAddress), sizeof(Uint8));
    statefile->read((char *)(&aIncSize), sizeof(Uint8));
    statefile->read((char *)(&sprPatternTable), sizeof(Uint16));
    statefile->read((char *)(&bgTilePatternTable), sizeof(Uint16));
    statefile->read((char *)(&useLargeSpr), sizeof(bool));
    statefile->read((char *)(&sprHeight), sizeof(Uint8));
    statefile->read((char *)(&enableVBlank), sizeof(bool));
    statefile->read((char *)(&useGrayscale), sizeof(bool));
    statefile->read((char *)(&showBGOnLeft), sizeof(bool));
    statefile->read((char *)(&showSprOnLeft), sizeof(bool));
    statefile->read((char *)(&showBG), sizeof(bool));
    statefile->read((char *)(&showSpr), sizeof(bool));
    statefile->read((char *)(&intensifyR), sizeof(bool));
    statefile->read((char *)(&intensifyG), sizeof(bool));
    statefile->read((char *)(&intensifyB), sizeof(bool));
    statefile->read((char *)(&sprOverflow), sizeof(bool));
    statefile->read((char *)(&spr0hit), sizeof(bool));
    statefile->read((char *)(&spr0hitDone), sizeof(bool));
    statefile->read((char *)(spr0PatternData), sizeof(Uint8) * 16);
    statefile->read((char *)(spr0PatternData2), sizeof(Uint8) * 16);
    statefile->read((char *)(&vBlankFlag), sizeof(bool));
    statefile->read((char *)(&oldVBlankFlag), sizeof(bool));
    statefile->read((char *)(&oamAddress), sizeof(Uint8));
    statefile->read((char *)(&newWrite), sizeof(bool));
    statefile->read((char *)(&offsetX), sizeof(Uint8));
    statefile->read((char *)(&tmpVRAMAddress), sizeof(Uint16));
    statefile->read((char *)(&vRAMAddress), sizeof(Uint16));
    statefile->read((char *)(&dataToWriteOAM2), sizeof(Uint8));
    statefile->read((char *)(&enableWriteOAM2), sizeof(bool));
    statefile->read((char *)(&spAddressToEval), sizeof(Uint16));
    statefile->read((char *)(&oam2AddressToWrite), sizeof(Uint16));
    statefile->read((char *)(&spFound), sizeof(Uint8));
    statefile->read((char *)(&spEvalStateCheckY), sizeof(bool));
    statefile->read((char *)(&spYInRange), sizeof(bool));
    statefile->read((char *)(&spBytesToCopy), sizeof(Uint8));
    statefile->read((char *)(&bgLoadingY), sizeof(Uint8));
    statefile->read((char *)(&bgTileToLoad), sizeof(Uint8));
    statefile->read((char *)(&bgFretchNameTableAddress), sizeof(Uint16));
    statefile->read((char *)(bgPatternIDFretched), sizeof(Uint8) * 34);
    statefile->read((char *)(bgPaletteFretched), sizeof(Uint8) * 34);
    statefile->read((char *)(bgPatternDataFretched), sizeof(Uint8) * 34 * 2);
    statefile->read((char *)(bgAddressFretched), sizeof(Uint32) * 34);
    statefile->read((char *)(bgRAMAddress), sizeof(Uint32) * 34);
    statefile->read((char *)(&spTileToLoad), sizeof(Uint8));
    statefile->read((char *)(&spPatternDataFretched), sizeof(Uint8) * 16);
    statefile->read((char *)(spRowFretched), sizeof(Uint8) * 8);
    statefile->read((char *)(spAddressFretched), sizeof(Uint32) * 8);
    statefile->read((char *)(spRAMAddress), sizeof(Uint32) * 8);
    statefile->read((char *)(&isSp0), sizeof(bool));
    statefile->read((char *)(&lastIsSp0), sizeof(bool));
    statefile->read((char *)(&currentBgTile), sizeof(Uint8));
    statefile->read((char *)(&currentBgX), sizeof(Uint8));
    statefile->read((char *)(currentSpX), sizeof(Uint16) * 8);
    statefile->read((char *)(tmpSprRAM2), sizeof(Uint8) * 32);
}

void ppu::saveSprObjects(string path){
	fstream logfile;
    
	logfile.open(path + "Spr.dat", ios::out | ios::trunc);
	if (logfile.is_open()){
		for(unsigned int i = 0; i < 64; ++i){
			logfile << to_string((long double)memDat->sprRAM[i * 4]) 
				+ ", " + to_string((long double)memDat->sprRAM[i * 4 + 1]) 
				+ ", " + to_string((long double)memDat->sprRAM[i * 4 + 2]) 
				+ "; " + to_string((long double)memDat->sprRAM[i * 4 + 3]) + "\n";

		}
		logfile.close();
	}

}

void ppu::saveVRam(string path){
	fstream logfile;
    Uint16 ad = 0x2000;
	char tps[64];
	logfile.open(path + "Vram.dat", ios::out | ios::trunc);
	if (logfile.is_open()){
		for(Uint16 k = 0; k < 8; ++k){
			sprintf(tps, "%02X;", ad);
			logfile << tps; 
			logfile << "\n";
			for(Uint16 i = 0; i < 32; ++i){
				for(Uint16 j = 0; j < 32; ++j){
					sprintf(tps, "%02X;", memDat->ppuBusRead(ad));
					logfile << tps; 
					++ad;
				}
				logfile << "\n";
			}
			logfile << "\n";
		}
		logfile.close();
	}
}