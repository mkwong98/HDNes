#pragma once

#include "sysSetting.h"
#include "gameManager.h"
#include "video.h"
#include "audio.h"
#include "memory.h"
#include "cart.h"
#include "cpu.h"
#include "mapper.h"
#include "ppu.h"
#include "apu.h"
#include "input.h"
#include "fraHDNesImp.h"

//Global vars
extern sysSetting*		setting;
extern gameManager*		gm;
extern video*			vid;
extern audio*			mixer;
extern memory*			memDat;
extern cart*			romDat;
extern cpu*				cpuCore;
extern mapper*			mmc;
extern ppu*				ppuCore;
extern apu*				apuCore;
extern input*			inputCore;
extern fraHDNesImp*     guiForm;

typedef void(cpu::*opcode)();
typedef Uint8(cpu::*opcodeTicks)();

extern opcode opArr[256];
extern opcodeTicks opTicksArr[256];