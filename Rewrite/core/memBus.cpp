#include "memBus.h"

memBus::memBus()
{
    //ctor
}

memBus::~memBus()
{
    //dtor
}

Uint8 memRead(Uint16 address){
	if(address < 0x2000){
		return internalRAM[address & 0x07FF];
	}

}


