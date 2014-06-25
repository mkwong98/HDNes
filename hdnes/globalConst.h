#define LINE_CYCLE		341
#define SCANLINES		262 
#define DISPLAY_WIDTH	256
#define DISPLAY_HEIGHT	240

#define PPU_VBLANK		0 //line 201 - 260
#define PPU_PRERENDER	1 //line 261
#define PPU_RENDERING	2 //line 0 - 239
#define PPU_IDLE		3 //line 240

#define SAMPLE_RATE 44100
#define AUDIO_BUFFER_SIZE 1024
#define APU_BUFFER_SIZE 2048

#define BAD_ADDRESS		0xFFFFFFFF
#define GEN_HD_WIDTH	128
#define GEN_HD_HEIGHT	128

#define CHR_PAGE_SIZE	0x2000
#define PRG_PAGE_SIZE	0x4000


#define OP_TYPE_ADDRESS		0
#define OP_TYPE_VALUE       1
#define OP_TYPE_WRITE       2
#define OP_TYPE_UNDEFINE	3

#define OP_EQUALS_TO        0
#define OP_GREATER_THAN     1
#define OP_LESS_THAN        2
#define OP_NOT_EQUAL        3