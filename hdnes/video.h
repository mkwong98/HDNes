#pragma once
#include "stdafx.h"
#include <vector>

#define SCREEN_SIZE_1X 0
#define SCREEN_SIZE_2X 1
#define SCREEN_SIZE_4X 2
#define SCREEN_SIZE_XX 3

#define RECORDING_TYPE_AUTO 0
#define RECORDING_TYPE_MANU 1
#define RECORDING_TYPE_NONE 2

#define PATTERN_SIZE 1200

#define HD_TILE_NO_MATCH    0xFFFE
#define HD_TILE_NOT_CHECKED 0xFFFF

#define TEXTURE_CACHE_TILE_COUNT     0x1000  //64 * 64
#define TEXTURE_CACHE_TILE_ROW_COUNT 64 
#define TEXTURE_CACHE_TILE_COL_COUNT 64 
#define TEXTURE_CACHE_TILE_COL_SHIFT 3  // (y/64) * 8 

struct rawPattern{
	Uint32 pixStrip1;
	Uint32 pixStrip2;
	Uint32 pixStrip3;
	Uint32 pixStrip4;
};

struct scale1Pattern{
	Uint32 pixel0;
	Uint32 pixel1;
	Uint32 pixel2;
	Uint32 pixel3;
	Uint32 pixel4;
	Uint32 pixel5;
	Uint32 pixel6;
	Uint32 pixel7;
};

struct scale2Pattern{
	Uint32 pixel0;
	Uint32 pixel1;
	Uint32 pixel2;
	Uint32 pixel3;
	Uint32 pixel4;
	Uint32 pixel5;
	Uint32 pixel6;
	Uint32 pixel7;
	Uint32 pixel8;
	Uint32 pixel9;
	Uint32 pixel10;
	Uint32 pixel11;
	Uint32 pixel12;
	Uint32 pixel13;
	Uint32 pixel14;
	Uint32 pixel15;
};

struct scale4Pattern{
	Uint32 pixel0;
	Uint32 pixel1;
	Uint32 pixel2;
	Uint32 pixel3;
	Uint32 pixel4;
	Uint32 pixel5;
	Uint32 pixel6;
	Uint32 pixel7;
	Uint32 pixel8;
	Uint32 pixel9;
	Uint32 pixel10;
	Uint32 pixel11;
	Uint32 pixel12;
	Uint32 pixel13;
	Uint32 pixel14;
	Uint32 pixel15;
	Uint32 pixel16;
	Uint32 pixel17;
	Uint32 pixel18;
	Uint32 pixel19;
	Uint32 pixel20;
	Uint32 pixel21;
	Uint32 pixel22;
	Uint32 pixel23;
	Uint32 pixel24;
	Uint32 pixel25;
	Uint32 pixel26;
	Uint32 pixel27;
	Uint32 pixel28;
	Uint32 pixel29;
	Uint32 pixel30;
	Uint32 pixel31;
};

union colorCombo{
	Uint32 colorValues;
	struct{
		Uint16 color1;
		Uint8 color2;
		Uint8 color3;
	};
};

struct patternDat{
	Uint32 patternAddress;
	colorCombo colors;
	rawPattern rawDat;
	Uint8 lookupIdx;
	Uint16 index;
    GLfloat brightness;
	Uint16 hdResult;
};


struct bitmapE{//GUI use
	Uint32 patternAddress;
	Uint32 bitmapID;
    colorCombo colors;
	rawPattern rawDat;
    int x;
    int y;
    GLfloat brightness;
};

struct bitmapF{
	Uint32 bitmapID;
    colorCombo colors;
	rawPattern rawDat;
    int x;
    int y;
    GLfloat brightness;
    bool isBg;

	bool isMetaSpr;
	Uint16 metaSprId;
	Uint8 metaSprPartId;
};

struct TileData{
	vector<bitmapF> bitmapP;
    int defaultID;
	Uint32 patternAddress;
};

struct bmpInfo{
    int width;
    int height;
	string filename;
};


struct metaSpritePart{
	Uint32 patternAddress;
    colorCombo colors;
	rawPattern rawDat;

	Sint16 relativeX;
	Sint16 relativeY;
	bool relativeHFlip;
	bool relativeVFlip;
	bool isSecond;
};

struct metaSprite{
	Uint16 id;
	string name;
	Uint32 bitmapID;
    GLfloat brightness;
	vector<metaSpritePart> parts;
	Uint16 priority;
	bool useLargeSpr;
};


//editing struct
struct screenTile{
    bool isBg;
	Uint32 patternAddress;
	colorCombo colors;
	rawPattern rawDat;
    int x;
    int y;
    string tileName;
};

class video
{
public:
	SDL_Window * Surf_Display;
	SDL_GLContext glcontext;
	bool initState;

    int screenSizeOption;
    int screenSizeWidth;
    int screenSizeHeight;
    
	clock_t lastClock;
	clock_t clockPerFrame;
	bool waitFrame;

	//colour values
	Uint32 colourList[64];

	//opengl section
	GLuint glProgID;
	GLuint glProgIDSp1;
	GLuint glProgIDSp2;
	GLuint glVShader;
	GLuint glVShaderSp1;
	GLuint glVShaderSp2;
	GLuint glPShader;
	GLuint glPShaderSp1;
	GLuint glPShaderSp2;

	GLuint uniTexture;
	GLuint uniTextureBase;
	GLuint uniXOffset;
	GLuint uniFlagBG;


	GLuint uniTextureSp1;
	GLuint uniTextureBaseSp1;
	GLuint uniTextureSp2;
	GLuint uniTextureBaseSp2;

	GLuint uniFlagSp1;
	GLuint uniFlagSp2;

	GLuint atrVectCoord;
	GLuint atrTextCoord;
	GLuint atrVectCoordSp1;
	GLuint atrTextCoordSp1;
	GLuint atrVectCoordSp2;
	GLuint atrTextCoordSp2;

	GLuint sampler;
	GLuint baseSampler;
	GLuint xOffsetSampler;
	GLuint flagSampler;
	
	Uint8 bgColourID;
	//textures
	GLuint xOffsetTexture;
	Uint8 bgXTexture[256];

	GLuint flagsTextureT;
	Uint8 flagsTexture[256];

	Uint32 bgFill;

	//data buffers
	GLuint bgVBufferRef;
	GLuint bgCBufferRef;
	GLfloat* bgCBuffer; 
	Uint32 bgCBufferSize;

	GLfloat spTileDataBuffer[5760]; //240*8*3
	GLuint spTileDataBufferRef;

	Uint16 spPatCount;
	GLuint spVBufferRef;
	GLshort* spVBuffer; 
	GLuint spCBufferRef;
	GLfloat* spCBuffer; 

	//graphics
	Uint32* hdTextureCache;
	GLuint hdTextureRef;

	Uint32 baseTextureCache[512 * 512];
	GLuint baseTextureRef;

	std::vector<Uint32> hdList[256];
	std::vector<Uint32> baseList[256];

	patternDat hdPatternData[TEXTURE_CACHE_TILE_COUNT];
	patternDat basePatternData[TEXTURE_CACHE_TILE_COUNT];
	Uint8 hdPatternInUse[TEXTURE_CACHE_TILE_COUNT];
	Uint8 basePatternInUse[TEXTURE_CACHE_TILE_COUNT];
	Uint16 minHDIdx;
	Uint16 minBaseIdx;
	Uint16 maxHDIdx;
	Uint16 maxBaseIdx;
	Uint16 blankHDIdx;
	Uint16 blankBaseIdx;

	Uint16 lastPatID;
	bool lastIsHD;


	bool capScreenFlag; 
	bool capDataFlag;
	bool contCapFlag;
	Uint8 contCapCounter;

	//HD tile result
	Uint16 bgHDResult[4 * 0x3C0];
	Uint16 spHDResult[64 * 2];
	bool hdResultInInitState;

	Uint32 packSize;
	//graphics pack data
    vector<Uint8*> rawBits; //raw picture data
    vector<bmpInfo> bmpInfos;
    vector<TileData> tdata; 
    Uint32* packData;
	Uint8 packScale;
	bool usePack;
	vector<metaSprite>metaSprites;

	//pack edit data
	Uint8 editRecordingType;
	bool cutEdgeTiles;
	bool chrRamMatch;
    vector<TileData> etiledata; 
	Uint32* editData;

	vector<TileData> allEtiledata; 
	Uint32* allEditData;

    //screen values;
    vector<string> screenNameList;
    vector<string> screenFileNameList;
    vector<screenTile> screenTiles; //new tiles in the current screen
    vector<screenTile> allScreenTiles; //all tiles in the current screen

	int capRate;
	vector<string> capScreenQueue;

	void initColour();
	void initBuffer();
	void initPatternArea();

	GLuint make_sampler();
	GLuint make_texture(GLuint width, GLuint height,void *buffer_data, GLuint type, GLint internalFormat, GLenum format, GLenum datatype);
	GLuint make_buffer(GLenum target, const void *buffer_data, GLsizei buffer_size);
	GLuint make_shader(GLenum type, const char *filename);
	GLuint make_program(GLuint vertex_shader, GLuint fragment_shader);
	void BuildPerspProjMat(float *m, float fov, float aspect, float znear, float zfar);
	void update_texture(GLuint uniformID, GLuint textureRef, GLuint samplerRef, GLuint width, GLuint oy, GLuint ny, GLuint maxy, void *buffer_data, GLuint type, GLenum format, GLenum datatype, int textureUnitIndex);

	video(void);
	~video(void);
    void init();
    void cleanUp();

	bool getInitState();
	void clearFrame();
	void startFrame();
	void displayFrame();
	void clearScreenData();
	//void setScanlineData();

	void initHDResult();
	void initScanlineData(Uint16 row);
	void setBGStripData(Uint16 row, Uint8 bgID);
	void setSPStripData(Uint16 row, Uint16 col, Uint8 spID);

	void prepareTileData(bool isBg, Uint32 patternAddress, Uint8 tableID, Uint16 nameTableAddress, Uint8 row,
		colorCombo colors, Uint32 ramAddress, GLfloat& decodedX, GLfloat& decodedY, bool& isHD, GLfloat& brightness);

	void capScreen(bool useNative);
	void saveScreenToPath(string path, bool useNative);
	static int convertScreenCapToPNG(void* data);

	void RefreshPackSize();

	void ReadHiResPack();
	void CleanHiResPack();
	void SaveHiResPack();
	void AddHiResImg(string filename);
 	void RemoveHiResImg(unsigned int pID);
    void AddDarkMapping();
	bool IsDarkerPalette(colorCombo color, colorCombo refColor);
	bool IsDarkerColor(Uint16 color, Uint16 refColor);
    GLfloat CalBrightnessValue(colorCombo color, colorCombo refColor);
	string GetPaletteString(colorCombo color);


	void ReadPackEdit();
	void CleanPackEdit();
    void SavePackEditScreen();
    void OptimizePackEdit();
    void RewritePackEdit();
    void SavePackEditScreenList();
	void SaveGraphics(string path);
	void SaveBuffers(string path);
    void ReadPalette(string path);

    
	//config settings
	void readConfig(string value);
	void saveConfig(fstream* inifile);
    
    Uint32 BgRender[30][35];
	void saveBG(string path);
};

