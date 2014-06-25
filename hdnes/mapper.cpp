#include "StdAfx.h"
#include "sysState.h"


mapper::mapper(void)
{
}


mapper::~mapper(void)
{
}

Uint8 mapper::getTilePalette(Uint8 tableX, Uint8 tableY, Uint8 tileX, Uint8 tileY){
	Uint8 tableID;
	Uint8 paletteDat;
	tableID = memDat->nameTableMirroring[tableX][tableY];
	//combine the top 3 bits
	paletteDat = memDat->attributeTable[tableID][((tileY & 0x1C) << 1) | (tileX >> 2)];
	if((tileX & 0x02) != 0){
		if((tileY & 0x02) != 0){
			return ((paletteDat >> 6) & 0x03);		
		}
		else{
			return ((paletteDat >> 2) & 0x03);		
		}
	}
	else{
		if((tileY & 0x02) != 0){
			return ((paletteDat >> 4) & 0x03);		
		}
		else{
			return (paletteDat & 0x03);		
		}
	}
}

