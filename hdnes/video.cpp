#include "stdafx.h"
#include "sysState.h"
#include <SDL\SDL_image.h>

using namespace std;

video::video(void){
    screenSizeOption = 1;
    screenSizeWidth = DISPLAY_WIDTH;
    screenSizeWidth = DISPLAY_HEIGHT;
	usePack = true;
	editRecordingType = 0;
	cutEdgeTiles = false;
	chrRamMatch = false;
	packData = 0;
	editData = 0;
	clockPerFrame = CLOCKS_PER_SEC / 60;
	initColour();
	bgCBufferSize = 190080 * sizeof(GLfloat); //33 tiles * 240 scanline * 6 vertex * 4 values
	capRate = 5;
}

void video::RefreshPackSize(){
	packSize = (romDat->chrPageCount > 0 ? romDat->chrPageCount * 0x200 : romDat->prgPageCount * 0x400);
}

void video::init(){
	SDL_ShowCursor(SDL_DISABLE);
	RefreshPackSize();
	CleanHiResPack();
	ReadHiResPack();
	ReadPackEdit();
	lastClock = clock();
	waitFrame = false;
    switch (screenSizeOption) {
        case SCREEN_SIZE_1X:
            screenSizeWidth = DISPLAY_WIDTH;
            screenSizeHeight = DISPLAY_HEIGHT;
            break;
        case SCREEN_SIZE_2X:
            screenSizeWidth = DISPLAY_WIDTH * 2;
            screenSizeHeight = DISPLAY_HEIGHT * 2;
            break;
        case SCREEN_SIZE_4X:
            screenSizeWidth = DISPLAY_WIDTH * 4;
            screenSizeHeight = DISPLAY_HEIGHT * 4;
            break;
        default:
            break;
    }
    
	if((Surf_Display = SDL_CreateWindow("HDNes", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenSizeWidth, screenSizeHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)) == NULL) {
        initState = false;
		writeLog("Cannot create display surface with SDL_SetVideoMode");
		return;
    }
	glcontext = SDL_GL_CreateContext(Surf_Display);
	glewInit(); 
	
	//init resource
	initBuffer();
	initPatternArea();
	for(int i = 0; i < 256; i++){
		flagsTexture[i] = 0;
	}

    glShadeModel(GL_SMOOTH);
	glEnable (GL_BLEND);
	glEnable (GL_DEPTH_TEST);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);

	//bg program
	glVShader = make_shader(GL_VERTEX_SHADER, "hdnesBGV.glsl");
	glPShader = make_shader(GL_FRAGMENT_SHADER, "hdnesBGF.glsl");
	glProgID = make_program(glVShader, glPShader);

	uniTexture = glGetUniformLocation(glProgID, "textureb");
	uniTextureBase = glGetUniformLocation(glProgID, "texturebBase");
	uniXOffset = glGetUniformLocation(glProgID, "xOffset");
	uniFlagBG = glGetUniformLocation(glProgID, "flags");

	atrVectCoord = glGetAttribLocation(glProgID, "position");
	atrTextCoord = glGetAttribLocation(glProgID, "textCoord");

	//sp program 1
	glVShaderSp1 = make_shader(GL_VERTEX_SHADER, "hdnesSPV.glsl");
	glPShaderSp1 = make_shader(GL_FRAGMENT_SHADER, "hdnesSPF1.glsl");
	glProgIDSp1 = make_program(glVShaderSp1, glPShaderSp1);

	uniTextureSp1 = glGetUniformLocation(glProgIDSp1, "textureb");
	uniTextureBaseSp1 = glGetUniformLocation(glProgIDSp1, "texturebBase");
	uniFlagSp1 = glGetUniformLocation(glProgIDSp1, "flagsSP1");
	atrVectCoordSp1 = glGetAttribLocation(glProgIDSp1, "position");
	atrTextCoordSp1 = glGetAttribLocation(glProgIDSp1, "textCoord");

	//sp program 2
	glVShaderSp2 = make_shader(GL_VERTEX_SHADER, "hdnesSPV.glsl");
	glPShaderSp2 = make_shader(GL_FRAGMENT_SHADER, "hdnesSPF2.glsl");
	glProgIDSp2 = make_program(glVShaderSp2, glPShaderSp2);

	uniTextureSp2 = glGetUniformLocation(glProgIDSp2, "textureb");
	uniTextureBaseSp2 = glGetUniformLocation(glProgIDSp2, "texturebBase");
	uniFlagSp2 = glGetUniformLocation(glProgIDSp2, "flagsSP2");
	atrVectCoordSp2 = glGetAttribLocation(glProgIDSp2, "position");
	atrTextCoordSp2 = glGetAttribLocation(glProgIDSp2, "textCoord");

	//textures
	hdTextureRef = make_texture(packScale * TEXTURE_CACHE_TILE_COL_COUNT * 8, packScale * TEXTURE_CACHE_TILE_ROW_COUNT * 8, hdTextureCache, GL_TEXTURE_2D, 4, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8);
	baseTextureRef = make_texture(TEXTURE_CACHE_TILE_COL_COUNT * 8, TEXTURE_CACHE_TILE_ROW_COUNT * 8, baseTextureCache, GL_TEXTURE_2D, 4, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8);

	xOffsetTexture = make_texture(256, 1, bgXTexture, GL_TEXTURE_1D, GL_R8UI, GL_RED_INTEGER, GL_UNSIGNED_BYTE);
	flagsTextureT = make_texture(256, 1, flagsTexture, GL_TEXTURE_1D, GL_R8UI, GL_RED_INTEGER, GL_UNSIGNED_BYTE);

	sampler = make_sampler();
	baseSampler = make_sampler();
	xOffsetSampler = make_sampler();
	flagSampler = make_sampler();

	capScreenFlag = false;
	capDataFlag = false;
	initState = true;
	contCapFlag = false;
	contCapCounter = 0;

	memset(hdPatternInUse, 0xFF, TEXTURE_CACHE_TILE_COUNT);
	memset(basePatternInUse, 0xFF, TEXTURE_CACHE_TILE_COUNT);
	memset(bgHDResult, 0xFF, 4 * 0x3C0 * 2);
	memset(spHDResult, 0xFF, 64 * 2 * 2);
	hdResultInInitState = true;
	minHDIdx = 0;
	minBaseIdx = 0;
	maxHDIdx = 0;
	maxBaseIdx = 0;
	blankHDIdx = 0;
	blankBaseIdx = 0;
}

video::~video(void){
	CleanHiResPack();
	CleanPackEdit();
}

void video::cleanUp(){
	SDL_GL_DeleteContext(glcontext); 
	SDL_DestroyWindow(Surf_Display);
	Surf_Display = NULL;
	glDeleteTextures(1, &hdTextureRef);
	glDeleteTextures(1, &baseTextureRef);
	glDeleteTextures(1, &xOffsetTexture);
	glDeleteTextures(1, &flagsTextureT);
	glDeleteShader(glVShader);
	glDeleteShader(glPShader);
	glDeleteProgram(glProgID);
	glDeleteShader(glVShaderSp1);
	glDeleteShader(glPShaderSp1);
	glDeleteProgram(glProgIDSp1);
	glDeleteShader(glVShaderSp2);
	glDeleteShader(glPShaderSp2);
	glDeleteProgram(glProgIDSp2);
	glDeleteBuffers(1, &bgCBufferRef);
	glDeleteBuffers(1, &bgVBufferRef);
	glDeleteBuffers(1, &spCBufferRef);
	glDeleteBuffers(1, &spVBufferRef);
	free(hdTextureCache);

	guiForm->refreshGraphicsPackGUI();
}

bool video::getInitState(){
	return initState;
}

void video::clearFrame(){
	bgColourID = memDat->bgColourID;
	if(!ppuCore->useGrayscale){
		glClearColor((colourList[bgColourID & 0x3F] >> 24)/ 255.0f,  ((colourList[bgColourID & 0x3F] >> 16) & 0xFF)/ 255.0f,  ((colourList[bgColourID & 0x3F] >> 8) & 0xFF)/ 255.0f, 1.0f);
	}
	else{
		float v = ((colourList[bgColourID & 0x3F] >> 24) + ((colourList[bgColourID & 0x3F] >> 16) & 0xFF) + ((colourList[bgColourID & 0x3F] >> 8) & 0xFF)) / 3.0f / 255.0f;
		glClearColor(v, v, v, 1.0f);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void video::startFrame(){    
    if(editRecordingType != RECORDING_TYPE_NONE){
		screenTiles.clear();
		allScreenTiles.clear();
	}
	spPatCount = 0;
	lastPatID = TEXTURE_CACHE_TILE_COUNT;
}

void video::displayFrame(){
	if((clock() - lastClock < clockPerFrame)){
		waitFrame = true;
		return;
	}
	else{
		waitFrame = false;
		lastClock += clockPerFrame; 
	}

	clearFrame();

	glBindBuffer(GL_ARRAY_BUFFER, bgCBufferRef);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, spVBufferRef);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glBindBuffer(GL_ARRAY_BUFFER, spCBufferRef);
	glUnmapBuffer(GL_ARRAY_BUFFER);
	
	//is back sp
	glDepthFunc(GL_LESS);
	glDepthMask(true);

	glUseProgram(glProgIDSp1);
	update_texture(uniTextureSp1, hdTextureRef, sampler, 512 * packScale, ((minHDIdx >> 3) & 0x1F8) * packScale, (((maxHDIdx >> 3) & 0x1F8) + 8) * packScale, 512 * packScale, hdTextureCache, GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, 0);
	update_texture(uniTextureBaseSp1, baseTextureRef, baseSampler, 512, ((minBaseIdx >> 3) & 0x1F8), ((maxBaseIdx >> 3) & 0x1F8) + 8, 512, baseTextureCache, GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, 1);
	update_texture(uniFlagSp1, flagsTextureT, flagSampler, 240, 0, 1, 1, flagsTexture, GL_TEXTURE_1D, GL_RED_INTEGER, GL_UNSIGNED_BYTE, 2);

	glBindBuffer(GL_ARRAY_BUFFER, spVBufferRef);
	glVertexAttribPointer(atrVectCoordSp1, 3, GL_SHORT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(atrVectCoordSp1);

	glBindBuffer(GL_ARRAY_BUFFER, spCBufferRef);
	glVertexAttribPointer(atrTextCoordSp1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(atrTextCoordSp1);

	glDrawArrays(GL_TRIANGLES, 0, spPatCount * 6);

	glDisableVertexAttribArray(atrVectCoordSp1);
	glDisableVertexAttribArray(atrTextCoordSp1);

	glDepthFunc(GL_ALWAYS);
	glDepthMask(false);

	glUseProgram(glProgID);

	update_texture(uniTexture, hdTextureRef, sampler, 0, 0, 0, 0, hdTextureCache, GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, 3);
	update_texture(uniTextureBase, baseTextureRef, baseSampler, 0, 0, 0, 0, baseTextureCache, GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, 4);

	update_texture(uniXOffset, xOffsetTexture, xOffsetSampler, 240, 0, 1, 1, bgXTexture, GL_TEXTURE_1D, GL_RED_INTEGER, GL_UNSIGNED_BYTE, 5);
	update_texture(uniFlagBG, flagsTextureT, flagSampler, 240, 0, 1, 1, flagsTexture, GL_TEXTURE_1D, GL_RED_INTEGER, GL_UNSIGNED_BYTE, 6);

	glBindBuffer(GL_ARRAY_BUFFER, bgVBufferRef);
	glVertexAttribPointer(atrVectCoord, 3, GL_SHORT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(atrVectCoord);

	glBindBuffer(GL_ARRAY_BUFFER, bgCBufferRef);
	glVertexAttribPointer(atrTextCoord, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(atrTextCoord);

	glDrawArrays(GL_TRIANGLES, 0, 47520);

	glDisableVertexAttribArray(atrVectCoord);
	glDisableVertexAttribArray(atrTextCoord);

	glDepthFunc(GL_LESS);
	glDepthMask(true);

	glUseProgram(glProgIDSp2);

	update_texture(uniTextureSp2, hdTextureRef, sampler, 0, 0, 0, 0, hdTextureCache, GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, 7);
	update_texture(uniTextureBaseSp2, baseTextureRef, baseSampler, 0, 0, 0, 0, baseTextureCache, GL_TEXTURE_2D, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, 8);

	glBindBuffer(GL_ARRAY_BUFFER, spVBufferRef);
	glVertexAttribPointer(atrVectCoordSp2, 3, GL_SHORT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(atrVectCoordSp2);

	glBindBuffer(GL_ARRAY_BUFFER, spCBufferRef);
	glVertexAttribPointer(atrTextCoordSp2, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(atrTextCoordSp2);
		
	glDrawArrays(GL_TRIANGLES, 0, spPatCount * 6);

	glDisableVertexAttribArray(atrVectCoordSp2);
	glDisableVertexAttribArray(atrTextCoordSp2);

	glUseProgram(0);

	if(capScreenFlag && !contCapFlag){
		capScreen(false);
	}
    
    if (editRecordingType == RECORDING_TYPE_AUTO || capDataFlag) {
        if (screenTiles.size() > 0 || capDataFlag) {
            SavePackEditScreen();
        }
		capDataFlag = false;
    }
	if(contCapFlag && (++contCapCounter >= capRate)){
		contCapCounter = 0;
		capScreen(true);
	}

	SDL_GL_SwapWindow(Surf_Display);

	//capScreen(false);
}

void video::clearScreenData(){
	glBindBuffer(GL_ARRAY_BUFFER, bgCBufferRef);
	glBufferData(GL_ARRAY_BUFFER, bgCBufferSize, NULL, GL_WRITE_ONLY);
	bgCBuffer = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	glBindBuffer(GL_ARRAY_BUFFER, spVBufferRef);
	spVBuffer = (GLshort*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	glBindBuffer(GL_ARRAY_BUFFER, spCBufferRef);
	spCBuffer = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	//if(minBgIdx != maxBgIdx){
	//	capScreen(true);
	//}

	if(maxHDIdx < blankHDIdx){
		blankHDIdx = TEXTURE_CACHE_TILE_COUNT;
	}
	else{
		blankHDIdx = maxHDIdx;
	}
	ZeroMemory(hdPatternInUse, blankHDIdx);
	minHDIdx = maxHDIdx;

	if(maxBaseIdx < blankBaseIdx){
		blankBaseIdx = TEXTURE_CACHE_TILE_COUNT;
	}
	else{
		blankBaseIdx = maxBaseIdx;
	}
	ZeroMemory(basePatternInUse, blankBaseIdx);
	minBaseIdx = maxBaseIdx;

	spPatCount = 0;
}

GLuint video::make_sampler(){
	GLuint tmpsampler;
	glGenSamplers(1, &tmpsampler);
	glSamplerParameteri(tmpsampler, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glSamplerParameteri(tmpsampler, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glSamplerParameteri(tmpsampler, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(tmpsampler, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(tmpsampler, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	return tmpsampler;
}

GLuint video::make_buffer(GLenum target, const void *buffer_data, GLsizei buffer_size)
{
    GLuint buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(target, buffer);
    glBufferData(target, buffer_size, buffer_data, GL_DYNAMIC_DRAW);
    return buffer;
}

GLuint video::make_texture(GLuint width, GLuint height,void *buffer_data, GLuint type,
	GLint internalFormat, GLenum format, GLenum datatype)				
{
	GLuint txtnumber;						// Texture ID
	glGenTextures(1, &txtnumber);					// Create 1 Texture
	glBindTexture(type, txtnumber);		// Bind The Texture
	switch(type){
	case GL_TEXTURE_2D:
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, datatype, buffer_data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	case GL_TEXTURE_1D:
		glTexImage1D(GL_TEXTURE_1D, 0, internalFormat, width, 0, format, datatype, buffer_data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		break;
	}
	return txtnumber;						// Return The Texture ID
}

GLuint video::make_shader(GLenum type, const char *filename)
{
	fstream sourcefile;
    GLchar *source;
    GLuint shader;
    GLint shader_ok;
	GLint size;

	sourcefile.open(setting->progDir + filename, ios::in|ios::binary|ios::ate);
	if(sourcefile.is_open()){
		size = sourcefile.tellg();
		source = new GLchar[size];
		sourcefile.seekg (0, ios::beg);
		sourcefile.read (source, size);
		sourcefile.close();
	}
	else{
		writeLog("Cannot open shader " + string(filename));
        return 0;
	}
	shader = glCreateShader(type);
    glShaderSource(shader, 1, (const GLchar**)&source, &size);
    delete[] source;
    glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
    if (!shader_ok) {
        writeLog("Failed to compile shader "+ string(filename));
		GLsizei loglen;
		GLchar logStr[256];
		glGetShaderInfoLog(shader, 256, &loglen, logStr);
		writeLog(string((char*)logStr));
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint video::make_program(GLuint vertex_shader, GLuint fragment_shader)
{
    GLint program_ok;

    GLuint program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
 
     glGetProgramiv(program, GL_LINK_STATUS, &program_ok);
    if (!program_ok) {
        writeLog("Failed to link shader program");
		if(fragment_shader == glPShader){
			writeLog("Shaders: hdnesBGV.glsl and hdnesBGF.glsl");
		}
		else if(fragment_shader == glPShaderSp1){
			writeLog("Shaders: hdnesSPV.glsl and hdnesSPF1.glsl");
		}
		else if(fragment_shader == glPShaderSp2){
			writeLog("Shaders: hdnesSPV.glsl and hdnesSPF2.glsl");
		}
		GLsizei loglen;
		GLchar logStr[256];
		glGetProgramInfoLog(program, 256, &loglen, logStr);
		writeLog(string((char*)logStr));
        glDeleteProgram(program);
        return 0;
    }
    return program;
}

void video::update_texture(GLuint uniformID, GLuint textureRef, GLuint samplerRef, GLuint width, GLuint oy, GLuint ny, GLuint maxy, void *buffer_data, GLuint type, GLenum format, GLenum datatype, int textureUnitIndex){
	glUniform1i(uniformID, textureUnitIndex);
	glActiveTexture(GL_TEXTURE0 + textureUnitIndex);
	glBindTexture(type, textureRef);
	if(width > 0){
		if(type == GL_TEXTURE_2D){
			if(ny >= oy){
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, oy, width, ny - oy, format, datatype, (Uint32*)buffer_data + (oy * width));
			}
			else{
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, oy, width, maxy - oy, format, datatype, (Uint32*)buffer_data + (oy * width));
				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, ny, format, datatype, buffer_data);
			}
		}
		else{
			glTexSubImage1D(GL_TEXTURE_1D, 0, 0, width, format, datatype, buffer_data);
		}
	}
	glBindSampler(textureUnitIndex, samplerRef);
}


void video::initColour(){
	Uint8 colourDish[64][3];
    
	colourDish[0][0] = 0x80; 
	colourDish[0][1] = 0x80; 
	colourDish[0][2] = 0x80; 
	colourDish[1][0] = 0x00; 
	colourDish[1][1] = 0x3D; 
	colourDish[1][2] = 0xA6; 
	colourDish[2][0] = 0x00; 
	colourDish[2][1] = 0x12; 
	colourDish[2][2] = 0xB0; 
	colourDish[3][0] = 0x44; 
	colourDish[3][1] = 0x00; 
	colourDish[3][2] = 0x96;
	colourDish[4][0] = 0xA1; 
	colourDish[4][1] = 0x00; 
	colourDish[4][2] = 0x5E; 
	colourDish[5][0] = 0xC7; 
	colourDish[5][1] = 0x00; 
	colourDish[5][2] = 0x28; 
	colourDish[6][0] = 0xBA; 
	colourDish[6][1] = 0x06; 
	colourDish[6][2] = 0x00; 
	colourDish[7][0] = 0x8C; 
	colourDish[7][1] = 0x17; 
	colourDish[7][2] = 0x00;
	colourDish[8][0] = 0x5C; 
	colourDish[8][1] = 0x2F; 
	colourDish[8][2] = 0x00; 
	colourDish[9][0] = 0x10; 
	colourDish[9][1] = 0x45; 
	colourDish[9][2] = 0x00; 
	colourDish[10][0] = 0x05; 
	colourDish[10][1] = 0x4A; 
	colourDish[10][2] = 0x00; 
	colourDish[11][0] = 0x00; 
	colourDish[11][1] = 0x47; 
	colourDish[11][2] = 0x2E;
	colourDish[12][0] = 0x00; 
	colourDish[12][1] = 0x41; 
	colourDish[12][2] = 0x66; 
	colourDish[13][0] = 0x00; 
	colourDish[13][1] = 0x00; 
	colourDish[13][2] = 0x00; 
	colourDish[14][0] = 0x05; 
	colourDish[14][1] = 0x05; 
	colourDish[14][2] = 0x05; 
	colourDish[15][0] = 0x05; 
	colourDish[15][1] = 0x05; 
	colourDish[15][2] = 0x05;

	colourDish[16][0] = 0xC7; 
	colourDish[16][1] = 0xC7; 
	colourDish[16][2] = 0xC7; 
	colourDish[17][0] = 0x00; 
	colourDish[17][1] = 0x77; 
	colourDish[17][2] = 0xFF; 
	colourDish[18][0] = 0x21; 
	colourDish[18][1] = 0x55; 
	colourDish[18][2] = 0xFF; 
	colourDish[19][0] = 0x82; 
	colourDish[19][1] = 0x37; 
	colourDish[19][2] = 0xFA;
	colourDish[20][0] = 0xEB; 
	colourDish[20][1] = 0x2F; 
	colourDish[20][2] = 0xB5; 
	colourDish[21][0] = 0xFF; 
	colourDish[21][1] = 0x29; 
	colourDish[21][2] = 0x50; 
	colourDish[22][0] = 0xFF; 
	colourDish[22][1] = 0x22; 
	colourDish[22][2] = 0x00; 
	colourDish[23][0] = 0xD6; 
	colourDish[23][1] = 0x32; 
	colourDish[23][2] = 0x00;
	colourDish[24][0] = 0xC4; 
	colourDish[24][1] = 0x62; 
	colourDish[24][2] = 0x00; 
	colourDish[25][0] = 0x35; 
	colourDish[25][1] = 0x80; 
	colourDish[25][2] = 0x00; 
	colourDish[26][0] = 0x05; 
	colourDish[26][1] = 0x8F; 
	colourDish[26][2] = 0x00; 
	colourDish[27][0] = 0x00; 
	colourDish[27][1] = 0x8A; 
	colourDish[27][2] = 0x55;
	colourDish[28][0] = 0x00; 
	colourDish[28][1] = 0x99; 
	colourDish[28][2] = 0xCC; 
	colourDish[29][0] = 0x21; 
	colourDish[29][1] = 0x21; 
	colourDish[29][2] = 0x21; 
	colourDish[30][0] = 0x09; 
	colourDish[30][1] = 0x09; 
	colourDish[30][2] = 0x09; 
	colourDish[31][0] = 0x09; 
	colourDish[31][1] = 0x09; 
	colourDish[31][2] = 0x09;

	colourDish[32][0] = 0xFE; 
	colourDish[32][1] = 0xFE; 
	colourDish[32][2] = 0xFF; 
	colourDish[33][0] = 0x0F; 
	colourDish[33][1] = 0xD7; 
	colourDish[33][2] = 0xFF; 
	colourDish[34][0] = 0x69; 
	colourDish[34][1] = 0xA2; 
	colourDish[34][2] = 0xFF; 
	colourDish[35][0] = 0xD4; 
	colourDish[35][1] = 0x80; 
	colourDish[35][2] = 0xFF;
	colourDish[36][0] = 0xFF; 
	colourDish[36][1] = 0x45; 
	colourDish[36][2] = 0xF3; 
	colourDish[37][0] = 0xFF; 
	colourDish[37][1] = 0x61; 
	colourDish[37][2] = 0x8B; 
	colourDish[38][0] = 0xFF; 
	colourDish[38][1] = 0x88; 
	colourDish[38][2] = 0x33; 
	colourDish[39][0] = 0xFF; 
	colourDish[39][1] = 0x9C; 
	colourDish[39][2] = 0x12;
	colourDish[40][0] = 0xFA; 
	colourDish[40][1] = 0xBC; 
	colourDish[40][2] = 0x20; 
	colourDish[41][0] = 0x9F; 
	colourDish[41][1] = 0xE3; 
	colourDish[41][2] = 0x0E; 
	colourDish[42][0] = 0x2B; 
	colourDish[42][1] = 0xF0; 
	colourDish[42][2] = 0x35; 
	colourDish[43][0] = 0x0C; 
	colourDish[43][1] = 0xF0; 
	colourDish[43][2] = 0xA4;
	colourDish[44][0] = 0x05; 
	colourDish[44][1] = 0xFB; 
	colourDish[44][2] = 0xFF; 
	colourDish[45][0] = 0x5E; 
	colourDish[45][1] = 0x5E; 
	colourDish[45][2] = 0x5E; 
	colourDish[46][0] = 0x0D; 
	colourDish[46][1] = 0x0D; 
	colourDish[46][2] = 0x0D; 
	colourDish[47][0] = 0x0D; 
	colourDish[47][1] = 0x0D; 
	colourDish[47][2] = 0x0D;

	colourDish[48][0] = 0xFF; 
	colourDish[48][1] = 0xFF; 
	colourDish[48][2] = 0xFF;
	colourDish[49][0] = 0xA6; 
	colourDish[49][1] = 0xFC; 
	colourDish[49][2] = 0xFF; 
	colourDish[50][0] = 0xB3; 
	colourDish[50][1] = 0xEC; 
	colourDish[50][2] = 0xFF; 
	colourDish[51][0] = 0xDA; 
	colourDish[51][1] = 0xAB; 
	colourDish[51][2] = 0xEB;
	colourDish[52][0] = 0xFF; 
	colourDish[52][1] = 0xA8; 
	colourDish[52][2] = 0xF9; 
	colourDish[53][0] = 0xFF; 
	colourDish[53][1] = 0xAB; 
	colourDish[53][2] = 0xB3; 
	colourDish[54][0] = 0xFF; 
	colourDish[54][1] = 0xD2; 
	colourDish[54][2] = 0xB0; 
	colourDish[55][0] = 0xFF; 
	colourDish[55][1] = 0xEF; 
	colourDish[55][2] = 0xA6;
	colourDish[56][0] = 0xFF; 
	colourDish[56][1] = 0xF7; 
	colourDish[56][2] = 0x9C; 
	colourDish[57][0] = 0xD7; 
	colourDish[57][1] = 0xE8; 
	colourDish[57][2] = 0x95; 
	colourDish[58][0] = 0xA6; 
	colourDish[58][1] = 0xED; 
	colourDish[58][2] = 0xAF; 
	colourDish[59][0] = 0xA2; 
	colourDish[59][1] = 0xF2; 
	colourDish[59][2] = 0xDA;
	colourDish[60][0] = 0x99; 
	colourDish[60][1] = 0xFF;
	colourDish[60][2] = 0xFC; 
	colourDish[61][0] = 0xDD; 
	colourDish[61][1] = 0xDD; 
	colourDish[61][2] = 0xDD; 
	colourDish[62][0] = 0x11; 
	colourDish[62][1] = 0x11; 
	colourDish[62][2] = 0x11; 
	colourDish[63][0] = 0x11; 
	colourDish[63][1] = 0x11; 
	colourDish[63][2] = 0x11;
    /*
	colourDish[0][0] = 0x46;
	colourDish[0][1] = 0x46;
	colourDish[0][2] = 0x46;
	colourDish[1][0] = 0x00;
	colourDish[1][1] = 0x06;
	colourDish[1][2] = 0x5A;
	colourDish[2][0] = 0x00;
	colourDish[2][1] = 0x06;
	colourDish[2][2] = 0x78;
	colourDish[3][0] = 0x02;
	colourDish[3][1] = 0x06;
	colourDish[3][2] = 0x73;
	colourDish[4][0] = 0x35;
	colourDish[4][1] = 0x03;
	colourDish[4][2] = 0x4C;
	colourDish[5][0] = 0x57;
	colourDish[5][1] = 0x00;
	colourDish[5][2] = 0x0E;
	colourDish[6][0] = 0x5A;
	colourDish[6][1] = 0x00;
	colourDish[6][2] = 0x00;
	colourDish[7][0] = 0x41;
	colourDish[7][1] = 0x00;
	colourDish[7][2] = 0x00;
	colourDish[8][0] = 0x12;
	colourDish[8][1] = 0x02;
	colourDish[8][2] = 0x00;
	colourDish[9][0] = 0x00;
	colourDish[9][1] = 0x14;
	colourDish[9][2] = 0x00;
	colourDish[10][0] = 0x00;
	colourDish[10][1] = 0x1E;
	colourDish[10][2] = 0x00;
	colourDish[11][0] = 0x00;
	colourDish[11][1] = 0x1E;
	colourDish[11][2] = 0x00;
	colourDish[12][0] = 0x00;
	colourDish[12][1] = 0x15;
	colourDish[12][2] = 0x21;
	colourDish[13][0] = 0x00;
	colourDish[13][1] = 0x00;
	colourDish[13][2] = 0x00;
	colourDish[14][0] = 0x00;
	colourDish[14][1] = 0x00;
	colourDish[14][2] = 0x00;
	colourDish[15][0] = 0x00;
	colourDish[15][1] = 0x00;
	colourDish[15][2] = 0x00;
    
	colourDish[16][0] = 0x9D;
	colourDish[16][1] = 0x9D;
	colourDish[16][2] = 0x9D;
	colourDish[17][0] = 0x00;
	colourDish[17][1] = 0x4A;
	colourDish[17][2] = 0xB9;
	colourDish[18][0] = 0x05;
	colourDish[18][1] = 0x30;
	colourDish[18][2] = 0xE1;
	colourDish[19][0] = 0x57;
	colourDish[19][1] = 0x18;
	colourDish[19][2] = 0xDA;
	colourDish[20][0] = 0x9F;
	colourDish[20][1] = 0x07;
	colourDish[20][2] = 0xA7;
	colourDish[21][0] = 0xCC;
	colourDish[21][1] = 0x02;
	colourDish[21][2] = 0x55;
	colourDish[22][0] = 0xCF;
	colourDish[22][1] = 0x0B;
	colourDish[22][2] = 0x00;
	colourDish[23][0] = 0xA4;
	colourDish[23][1] = 0x23;
	colourDish[23][2] = 0x00;
	colourDish[24][0] = 0x5C;
	colourDish[24][1] = 0x3F;
	colourDish[24][2] = 0x00;
	colourDish[25][0] = 0x0B;
	colourDish[25][1] = 0x58;
	colourDish[25][2] = 0x00;
	colourDish[26][0] = 0x00;
	colourDish[26][1] = 0x66;
	colourDish[26][2] = 0x00;
	colourDish[27][0] = 0x00;
	colourDish[27][1] = 0x67;
	colourDish[27][2] = 0x13;
	colourDish[28][0] = 0x00;
	colourDish[28][1] = 0x5E;
	colourDish[28][2] = 0x6E;
	colourDish[29][0] = 0x00;
	colourDish[29][1] = 0x00;
	colourDish[29][2] = 0x00;
	colourDish[30][0] = 0x00;
	colourDish[30][1] = 0x00;
	colourDish[30][2] = 0x00;
	colourDish[31][0] = 0x00;
	colourDish[31][1] = 0x00;
	colourDish[31][2] = 0x00;
    
	colourDish[32][0] = 0xFE;
	colourDish[32][1] = 0xFE;
	colourDish[32][2] = 0xFE;
	colourDish[33][0] = 0x1F;
	colourDish[33][1] = 0x9E;
	colourDish[33][2] = 0xFF;
	colourDish[34][0] = 0x53;
	colourDish[34][1] = 0x76;
	colourDish[34][2] = 0xFF;
	colourDish[35][0] = 0x98;
	colourDish[35][1] = 0x65;
	colourDish[35][2] = 0xFF;
	colourDish[36][0] = 0xFC;
	colourDish[36][1] = 0x67;
	colourDish[36][2] = 0xFF;
	colourDish[37][0] = 0xFF;
	colourDish[37][1] = 0x6C;
	colourDish[37][2] = 0xB3;
	colourDish[38][0] = 0xFF;
	colourDish[38][1] = 0x74;
	colourDish[38][2] = 0x66;
	colourDish[39][0] = 0xFF;
	colourDish[39][1] = 0x80;
	colourDish[39][2] = 0x14;
	colourDish[40][0] = 0xC4;
	colourDish[40][1] = 0x9A;
	colourDish[40][2] = 0x00;
	colourDish[41][0] = 0x71;
	colourDish[41][1] = 0xB3;
	colourDish[41][2] = 0x00;
	colourDish[42][0] = 0x28;
	colourDish[42][1] = 0xC4;
	colourDish[42][2] = 0x21;
	colourDish[43][0] = 0x00;
	colourDish[43][1] = 0xCB;
	colourDish[43][2] = 0x74;
	colourDish[44][0] = 0x00;
	colourDish[44][1] = 0xBF;
	colourDish[44][2] = 0xD0;
	colourDish[45][0] = 0x2B;
	colourDish[45][1] = 0x2B;
	colourDish[45][2] = 0x2B;
	colourDish[46][0] = 0x00;
	colourDish[46][1] = 0x00;
	colourDish[46][2] = 0x00;
	colourDish[47][0] = 0x00;
	colourDish[47][1] = 0x00;
	colourDish[47][2] = 0x00;
    
	colourDish[48][0] = 0xFF;
	colourDish[48][1] = 0xFF;
	colourDish[48][2] = 0xFF;
	colourDish[49][0] = 0x9E;
	colourDish[49][1] = 0xD5;
	colourDish[49][2] = 0xFF;
	colourDish[50][0] = 0xAF;
	colourDish[50][1] = 0xC0;
	colourDish[50][2] = 0xFF;
	colourDish[51][0] = 0xD0;
	colourDish[51][1] = 0xB8;
	colourDish[51][2] = 0xFF;
	colourDish[52][0] = 0xFE;
	colourDish[52][1] = 0xBF;
	colourDish[52][2] = 0xFF;
	colourDish[53][0] = 0xFF;
	colourDish[53][1] = 0xC0;
	colourDish[53][2] = 0xE0;
	colourDish[54][0] = 0xFF;
	colourDish[54][1] = 0xC3;
	colourDish[54][2] = 0xBD;
	colourDish[55][0] = 0xFF;
	colourDish[55][1] = 0xCA;
	colourDish[55][2] = 0x9C;
	colourDish[56][0] = 0xE7;
	colourDish[56][1] = 0xD5;
	colourDish[56][2] = 0x8B;
	colourDish[57][0] = 0xC5;
	colourDish[57][1] = 0xDF;
	colourDish[57][2] = 0x8E;
	colourDish[58][0] = 0xA6;
	colourDish[58][1] = 0xE6;
	colourDish[58][2] = 0xA3;
	colourDish[59][0] = 0x94;
	colourDish[59][1] = 0xE8;
	colourDish[59][2] = 0xC5;
	colourDish[60][0] = 0x92;
	colourDish[60][1] = 0xE4;
	colourDish[60][2] = 0xEB;
	colourDish[61][0] = 0xA7;
	colourDish[61][1] = 0xA7;
	colourDish[61][2] = 0xA7;
	colourDish[62][0] = 0x00;
	colourDish[62][1] = 0x00;
	colourDish[62][2] = 0x00;
	colourDish[63][0] = 0x00;
	colourDish[63][1] = 0x00;
	colourDish[63][2] = 0x00;
    */
	for(Uint8 i = 0; i < 64; i++){
		colourList[i] = (colourDish[i][0] << 24) | (colourDish[i][1] << 16) | (colourDish[i][2] << 8) | 0xFF;
	}
}


void video::initBuffer(){
	GLsizei vSize;

	//vertex data is fixed
	GLshort vbuffer[142560]; //240*33*6*3

	for(int i = 0; i < 240; i++){
		for(int j = 0; j < 33; j++){
			vbuffer[(i * 33 + j) * 18] = (GLshort)(j * 8);
			vbuffer[(i * 33 + j) * 18 + 1] = -(GLshort)(i);
			vbuffer[(i * 33 + j) * 18 + 2] = (GLshort)(0);

			vbuffer[(i * 33 + j) * 18 + 3] = (GLshort)((j + 1) * 8);
			vbuffer[(i * 33 + j) * 18 + 4] = -(GLshort)(i);
			vbuffer[(i * 33 + j) * 18 + 5] = (GLshort)(1);

			vbuffer[(i * 33 + j) * 18 + 6] = (GLshort)((j + 1) * 8);
			vbuffer[(i * 33 + j) * 18 + 7] = -(GLshort)(i + 1);
			vbuffer[(i * 33 + j) * 18 + 8] = (GLshort)(2);
            
			vbuffer[(i * 33 + j) * 18 + 9] = (GLshort)((j + 1) * 8);
			vbuffer[(i * 33 + j) * 18 + 10] = -(GLshort)(i + 1);
			vbuffer[(i * 33 + j) * 18 + 11] = (GLshort)(2);

			vbuffer[(i * 33 + j) * 18 + 12] = (GLshort)(j * 8);
			vbuffer[(i * 33 + j) * 18 + 13] = -(GLshort)(i + 1);
			vbuffer[(i * 33 + j) * 18 + 14] = (GLshort)(3);

			vbuffer[(i * 33 + j) * 18 + 15] = (GLshort)(j * 8);
			vbuffer[(i * 33 + j) * 18 + 16] = -(GLshort)(i);
			vbuffer[(i * 33 + j) * 18 + 17] = (GLshort)(0);
		}
	}

	vSize = 142560 * sizeof(GLshort);
	bgVBufferRef = make_buffer(GL_ARRAY_BUFFER, 0, vSize);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vSize, vbuffer);

	bgCBufferRef = make_buffer(GL_ARRAY_BUFFER, 0, bgCBufferSize);
	bgCBuffer = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	vSize = 34560 * sizeof(GLshort); //240 * 8 * 6 * 3
	spVBufferRef = make_buffer(GL_ARRAY_BUFFER, 0, vSize);
	spVBuffer = (GLshort*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

	vSize = 46080 * sizeof(GLfloat); //240 * 8 * 6 * 4
	spCBufferRef = make_buffer(GL_ARRAY_BUFFER, 0, vSize);
	spCBuffer = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

}

void video::initPatternArea(){
	spPatCount = 0;
	lastPatID = TEXTURE_CACHE_TILE_COUNT;
	hdTextureCache = (Uint32 *)malloc(packScale * packScale * TEXTURE_CACHE_TILE_COUNT * 4 * 8 * 8);
}

void video::initScanlineData(Uint16 row){
	flagsTexture[row] = 0x00;
	if(ppuCore->showBGOnLeft) flagsTexture[row] = flagsTexture[row] | 0x01;
	if(ppuCore->showSprOnLeft) flagsTexture[row] = flagsTexture[row] | 0x02;
	if(ppuCore->intensifyR) flagsTexture[row] = flagsTexture[row] | 0x04;
	if(ppuCore->intensifyG) flagsTexture[row] = flagsTexture[row] | 0x08;
	if(ppuCore->intensifyB) flagsTexture[row] = flagsTexture[row] | 0x10;
	if(ppuCore->useGrayscale) flagsTexture[row] = flagsTexture[row] | 0x20;

	if(ppuCore->showBG){
		bgXTexture[row] = ppuCore->offsetX;
		if(row % 8 == 0){
			BgRender[row / 8][33] = ppuCore->offsetX;
			BgRender[row / 8][34] = ppuCore->bgLoadingY;
		}
	}
	lastIsHD = false;
}

void video::setBGStripData(Uint16 row, Uint8 bgID){
	GLfloat decodeX;
	GLfloat decodeY;
    GLfloat brightness;
	Uint32 idx;
	Uint8 patternW[5] = {0, 8, 16, 24, 32};
	bool patternMatch;
	rawPattern patternData;
	colorCombo colors;
	bool isHD;
	GLfloat isHDVal;

	idx = ((row * 33) + bgID) * 24;

	if(ppuCore->showBG){
		if(row % 8 == 0){
			BgRender[row / 8][bgID] = ppuCore->bgAddressFretched[bgID];
		}
		colors.color1 = memDat->paletteTable[ppuCore->bgPaletteFretched[bgID]][1];
		colors.color2 = memDat->paletteTable[ppuCore->bgPaletteFretched[bgID]][2];
		colors.color3 = memDat->paletteTable[ppuCore->bgPaletteFretched[bgID]][3];
		prepareTileData(true, ppuCore->bgAddressFretched[bgID], ppuCore->bgTableID[bgID], ppuCore->bgNameTableAddress[bgID], ppuCore->bgLoadingY, colors, 
			ppuCore->bgRAMAddress[bgID], decodeX, decodeY, isHD, brightness);

		isHDVal = (isHD ? 0.0 : 1.0);
		bgCBuffer[idx] = decodeX;
		++idx;
		bgCBuffer[idx] = decodeY;
		++idx;
		bgCBuffer[idx] = brightness;
		++idx;
		bgCBuffer[idx] = isHDVal;
		++idx;

		bgCBuffer[idx] = decodeX + 1 / (GLfloat)TEXTURE_CACHE_TILE_COL_COUNT;
		++idx;
		bgCBuffer[idx] = decodeY;
		++idx;
		bgCBuffer[idx] = brightness;
		++idx;
		bgCBuffer[idx] = isHDVal;
		++idx;

		bgCBuffer[idx] = decodeX + 1 / (GLfloat)TEXTURE_CACHE_TILE_COL_COUNT;
		++idx;
		bgCBuffer[idx] = decodeY + 1 / (GLfloat)(TEXTURE_CACHE_TILE_ROW_COUNT * 8);
		++idx;
		bgCBuffer[idx] = brightness;
		++idx;
		bgCBuffer[idx] = isHDVal;
		++idx;
        
  //      
		bgCBuffer[idx] = decodeX + 1 / (GLfloat)TEXTURE_CACHE_TILE_COL_COUNT;
		++idx;
		bgCBuffer[idx] = decodeY + 1 / (GLfloat)(TEXTURE_CACHE_TILE_ROW_COUNT * 8);
		++idx;
		bgCBuffer[idx] = brightness;
		++idx;
		bgCBuffer[idx] = isHDVal;
		++idx;

		bgCBuffer[idx] = decodeX;
		++idx;
		bgCBuffer[idx] = decodeY + 1 / (GLfloat)(TEXTURE_CACHE_TILE_ROW_COUNT * 8);
		++idx;
		bgCBuffer[idx] = brightness;
		++idx;
		bgCBuffer[idx] = isHDVal;
		++idx;

		bgCBuffer[idx] = decodeX;
		++idx;
		bgCBuffer[idx] = decodeY;
		++idx;
		bgCBuffer[idx] = brightness;
		++idx;
		bgCBuffer[idx] = isHDVal;
		++idx;
	}
	else{
		bgXTexture[row] = 255;
	}

	    
	if(editRecordingType != RECORDING_TYPE_NONE && ppuCore->frameCount > 20 && (chrRamMatch || romDat->chrPageCount > 0)){
        if ((row >=8 && row < 224) || (row < 232 && !cutEdgeTiles)) {
            if(ppuCore->showBG){
				//look up the tile
				//only for top row of the tile
				if(ppuCore->bgLoadingY == 0){
					//bg tiles
					int tileX = (bgID * 8) - ppuCore->offsetX;
					if((tileX >= 8 && tileX <= 240) || ((tileX >= 0 && tileX <= 248) && !cutEdgeTiles)){
						int index = ppuCore->bgAddressFretched[bgID];
						if(index != BAD_ADDRESS){
							TileData t;
							//0 for bg
							t.defaultID = 0;
							t.patternAddress = index;

							int packID = -1;
							int packID2 = -1;
                            
							if(romDat->chrPageCount == 0){
								patternData = *((rawPattern*)(&(romDat->chrRAM[ppuCore->bgRAMAddress[bgID]])));
							}

							if (editData[index] != BAD_ADDRESS){
								TileData* pt;
								pt = &(etiledata[editData[index]]);
								for (unsigned int idx = 0; idx < pt->bitmapP.size(); ++idx)
								{
									if (pt->bitmapP[idx].colors.colorValues == colors.colorValues){
										if(romDat->chrPageCount > 0){
											patternMatch = true;
										}
										else{
											patternMatch = (patternData.pixStrip1 == pt->bitmapP[idx].rawDat.pixStrip1
														&& patternData.pixStrip2 == pt->bitmapP[idx].rawDat.pixStrip2
														&& patternData.pixStrip3 == pt->bitmapP[idx].rawDat.pixStrip3
														&& patternData.pixStrip4 == pt->bitmapP[idx].rawDat.pixStrip4);
										}
										if(patternMatch){
											packID = idx;
										}
									}
								}

								if (packID == -1){
									for (unsigned int idx = 0; idx < screenTiles.size(); ++idx)
									{
										if (screenTiles[idx].patternAddress == ppuCore->bgAddressFretched[bgID]
										&& screenTiles[idx].colors.colorValues == colors.colorValues){
											if(romDat->chrPageCount > 0){
												patternMatch = true;
											}
											else{
												patternMatch = (patternData.pixStrip1 == screenTiles[idx].rawDat.pixStrip1
															&& patternData.pixStrip2 == screenTiles[idx].rawDat.pixStrip2
															&& patternData.pixStrip3 == screenTiles[idx].rawDat.pixStrip3
															&& patternData.pixStrip4 == screenTiles[idx].rawDat.pixStrip4);
											}
											if(patternMatch){
												packID = idx;
											}
										}
									}
								}
								if (allEditData[index] == BAD_ADDRESS){
									t = etiledata[editData[index]];
								}
							}
							else{
								editData[index] = etiledata.size();
								etiledata.push_back(t);
							}
                            
							if (allEditData[index] == BAD_ADDRESS){
								allEditData[index] = allEtiledata.size();
								allEtiledata.push_back(t);
							}
							if (packID != -1){
								for (unsigned int idx = 0; idx < allScreenTiles.size(); ++idx){
									if (allScreenTiles[idx].patternAddress == ppuCore->bgAddressFretched[bgID]
									&& allScreenTiles[idx].colors.colorValues == colors.colorValues){
										if(romDat->chrPageCount > 0){
											patternMatch = true;
										}
										else{
											patternMatch = (patternData.pixStrip1 == allScreenTiles[idx].rawDat.pixStrip1
                                                            && patternData.pixStrip2 == allScreenTiles[idx].rawDat.pixStrip2
                                                            && patternData.pixStrip3 == allScreenTiles[idx].rawDat.pixStrip3
                                                            && patternData.pixStrip4 == allScreenTiles[idx].rawDat.pixStrip4);
										}
										if(patternMatch){
											packID2 = idx;
										}
									}
								}
							}
                            
							if (packID == -1 || packID2 == -1){
								screenTile st;
								st.isBg = true;
								st.patternAddress = ppuCore->bgAddressFretched[bgID];
								st.colors = colors;
								if(romDat->chrPageCount == 0){
									st.rawDat = patternData;
								}
								st.x = tileX;
								st.y = row;
								st.tileName = "";
								if(packID == -1){
									screenTiles.push_back(st); 
								}
								if(packID2 == -1){
									allScreenTiles.push_back(st);
								}
							}
						}
					}
				}
			}
        }
    }
}


void video::setSPStripData(Uint16 row, Uint16 col, Uint8 spID){
	GLfloat decodeX;
	GLfloat decodeY;
    GLfloat brightness;
	Uint32 idx;
	Uint32 idxc;
	Uint8 patternW[5] = {0, 8, 16, 24, 32};
	bool isHD;
	GLfloat isHDVal;

	GLshort spZ;
	GLfloat spY1;
	GLfloat spY2;
	GLfloat spX1;
	GLfloat spX2;
	bool patternMatch;
	rawPattern patternData;
	colorCombo colors;

	idx = spPatCount * 18;
	idxc = spPatCount * 24;

	if((ppuCore->tmpSprRAM2[spID * 4 + 1] != 0xff || ppuCore->tmpSprRAM2[spID * 4 + 2] != 0xff || ppuCore->tmpSprRAM2[spID * 4 + 3] != 0xff) && (ppuCore->spRowFretched[spID] < ppuCore->sprHeight) && ppuCore->showSpr){
		colors.color1 = memDat->paletteTable[(ppuCore->tmpSprRAM2[spID * 4 + 2] & 0x03) | 0x04][1];
		colors.color2 = memDat->paletteTable[(ppuCore->tmpSprRAM2[spID * 4 + 2] & 0x03) | 0x04][2];
		colors.color3 = memDat->paletteTable[(ppuCore->tmpSprRAM2[spID * 4 + 2] & 0x03) | 0x04][3];
		
		prepareTileData(false, ppuCore->spAddressFretched[spID], 0, ppuCore->spEvalAddress[spID] + (ppuCore->spEvalIsTopTile[spID] == 0 ? 0 : 64), ppuCore->spRowFretched[spID], colors,
			ppuCore->spRAMAddress[spID], decodeX, decodeY, isHD, brightness);

		//check is back
		spZ = (GLshort)((((ppuCore->tmpSprRAM2[spID * 4 + 2] >> 5) & 0x01) != 0? 11 : 1) + spID);
		spVBuffer[idx] = (GLshort)(col);
		++idx;
		spVBuffer[idx] = -(GLshort)(row);
		++idx;
		spVBuffer[idx] = spZ;
		++idx;

		spVBuffer[idx] = (GLshort)(col + 8);
		++idx;
		spVBuffer[idx] = -(GLshort)(row);
		++idx;
		spVBuffer[idx] = spZ;
		++idx;

		spVBuffer[idx] = (GLshort)(col + 8);
		++idx;
		spVBuffer[idx] = -(GLshort)(row + 1);
		++idx;
		spVBuffer[idx] = spZ;
		++idx;
  
		spVBuffer[idx] = (GLshort)(col + 8);
		++idx;
		spVBuffer[idx] = -(GLshort)(row + 1);
		++idx;
		spVBuffer[idx] = spZ;
		++idx;

		spVBuffer[idx] = (GLshort)(col);
		++idx;
		spVBuffer[idx] = -(GLshort)(row + 1);
		++idx;
		spVBuffer[idx] = spZ;
		++idx;

		spVBuffer[idx] = (GLshort)(col);
		++idx;
		spVBuffer[idx] = -(GLshort)(row);
		++idx;
		spVBuffer[idx] = spZ;
		++idx;


		//check v flip
		isHDVal = (isHD ? 0.0 : 1.0);
		if(ppuCore->tmpSprRAM2[spID * 4 + 2] >> 7 == 0){
			spY1 = decodeY;
			spY2 = decodeY + 1 / (GLfloat)(TEXTURE_CACHE_TILE_ROW_COUNT * 8);
		}
		else{
			spY1 = decodeY + 1 / (GLfloat)(TEXTURE_CACHE_TILE_ROW_COUNT * 8);
			spY2 = decodeY;
		}

		if(((ppuCore->tmpSprRAM2[spID * 4 + 2] >> 6) & 0x01) == 0){
			spX1 = decodeX;
			spX2 = decodeX + 1 / (GLfloat)TEXTURE_CACHE_TILE_COL_COUNT;
		}
		else{
			spX1 = decodeX + 1 / (GLfloat)TEXTURE_CACHE_TILE_COL_COUNT;
			spX2 = decodeX;
		}

		spCBuffer[idxc] = spX1;
		++idxc;
		spCBuffer[idxc] = spY1;
		++idxc;
		spCBuffer[idxc] = brightness;
		++idxc;
		spCBuffer[idxc] = isHDVal;
		++idxc;

		spCBuffer[idxc] = spX2;
		++idxc;
		spCBuffer[idxc] = spY1;
		++idxc;
		spCBuffer[idxc] = brightness;
		++idxc;
		spCBuffer[idxc] = isHDVal;
		++idxc;

		spCBuffer[idxc] = spX2;
		++idxc;
		spCBuffer[idxc] = spY2;
		++idxc;
		spCBuffer[idxc] = brightness;
		++idxc;
		spCBuffer[idxc] = isHDVal;
		++idxc;
        
		spCBuffer[idxc] = spX2;
		++idxc;
		spCBuffer[idxc] = spY2;
		++idxc;
		spCBuffer[idxc] = brightness;
		++idxc;
		spCBuffer[idxc] = isHDVal;
		++idxc;

		spCBuffer[idxc] = spX1;
		++idxc;
		spCBuffer[idxc] = spY2;
		++idxc;
		spCBuffer[idxc] = brightness;
		++idxc;
		spCBuffer[idxc] = isHDVal;
		++idxc;

		spCBuffer[idxc] = spX1;
		++idxc;
		spCBuffer[idxc] = spY1;
		++idxc;
		spCBuffer[idxc] = brightness;
		++idxc;
		spCBuffer[idxc] = isHDVal;
		++idxc;

		spPatCount++;
	}
	    
	if(editRecordingType != RECORDING_TYPE_NONE && ppuCore->frameCount > 20 && (chrRamMatch || romDat->chrPageCount > 0)){
        if ((row >= 8 && row < 224) || (row < 232 && !cutEdgeTiles)) {
            if(ppuCore->showSpr){
				if(ppuCore->tmpSprRAM2[spID * 4] != 0xff){
					if(((col >= 16  && col <= 248) || (col >= 8 && !cutEdgeTiles)) 
						&& (ppuCore->spRowFretched[spID] == (ppuCore->tmpSprRAM2[spID * 4 + 2] >> 7 == 0 ? 0 : 7)
						|| ppuCore->spRowFretched[spID] == (ppuCore->tmpSprRAM2[spID * 4 + 2] >> 7 == 0 ? 8 : 15))){
						int index = ppuCore->spAddressFretched[spID];
						if(index != BAD_ADDRESS){
							TileData t;
							t.defaultID = 1;
							t.patternAddress = index;

							int packID = -1;
							int packID2 = -1;

							if(romDat->chrPageCount == 0){
								patternData = *((rawPattern*)(&(romDat->chrRAM[ppuCore->spRAMAddress[spID]])));
							}
							if (editData[index] != BAD_ADDRESS){
								TileData* pt;
								pt = &(etiledata[editData[index]]);
								for (unsigned int idx = 0; idx < pt->bitmapP.size(); ++idx){
									if (pt->bitmapP[idx].colors.colorValues == colors.colorValues){
										if(romDat->chrPageCount > 0){
											patternMatch = true;
										}
										else{
											patternMatch = (patternData.pixStrip1 == pt->bitmapP[idx].rawDat.pixStrip1
														&& patternData.pixStrip2 == pt->bitmapP[idx].rawDat.pixStrip2
														&& patternData.pixStrip3 == pt->bitmapP[idx].rawDat.pixStrip3
														&& patternData.pixStrip4 == pt->bitmapP[idx].rawDat.pixStrip4);
										}
										if(patternMatch){
											packID = idx;
										}
									}
								}
								if (packID == -1){
									//check data found in current frame
									for (unsigned int idx = 0; idx < screenTiles.size(); ++idx)
									{
										if (screenTiles[idx].patternAddress == ppuCore->spAddressFretched[spID]
										&& screenTiles[idx].colors.colorValues == colors.colorValues){
											if(romDat->chrPageCount > 0){
												patternMatch = true;
											}
											else{
												patternMatch = (patternData.pixStrip1 == screenTiles[idx].rawDat.pixStrip1
															&& patternData.pixStrip2 == screenTiles[idx].rawDat.pixStrip2
															&& patternData.pixStrip3 == screenTiles[idx].rawDat.pixStrip3
															&& patternData.pixStrip4 == screenTiles[idx].rawDat.pixStrip4);
											}
											if(patternMatch){
												packID = idx;
											}
										}
									}
								}	
								if (allEditData[index] == BAD_ADDRESS){
									t = etiledata[editData[index]];
								}
							}
							else{
								editData[index] = etiledata.size();
								etiledata.push_back(t);
							}

							if (allEditData[index] == BAD_ADDRESS){
								allEditData[index] = allEtiledata.size();
								allEtiledata.push_back(t);
							}

							if (packID != -1){
								for (unsigned int idx = 0; idx < allScreenTiles.size(); ++idx){
									if (allScreenTiles[idx].patternAddress == ppuCore->spAddressFretched[spID]
									&& allScreenTiles[idx].colors.colorValues == colors.colorValues){
										if(romDat->chrPageCount > 0){
											patternMatch = true;
										}
										else{
											patternMatch = (patternData.pixStrip1 == allScreenTiles[idx].rawDat.pixStrip1
														&& patternData.pixStrip2 == allScreenTiles[idx].rawDat.pixStrip2
														&& patternData.pixStrip3 == allScreenTiles[idx].rawDat.pixStrip3
														&& patternData.pixStrip4 == allScreenTiles[idx].rawDat.pixStrip4);
										}
										if(patternMatch){
											packID2 = idx;
										}
									}
								}
							}

							if (packID == -1 || packID2 == -1){
								screenTile st;
								st.isBg = false;
								st.patternAddress = ppuCore->spAddressFretched[spID];
								st.colors = colors;
								if(romDat->chrPageCount == 0){
									st.rawDat = patternData;
								}
								st.x = col;
								st.y = row;
								st.tileName = "";
								if(packID == -1){
									screenTiles.push_back(st); 
								}
								if(packID2 == -1){
									allScreenTiles.push_back(st);
								}
							}
						}
					}
				}
			}
        }
    }
}

void video::initHDResult(){
	if(!hdResultInInitState){
		memset(bgHDResult, 0xFF, 4 * 0x3C0 * 2);
		memset(spHDResult, 0xFF, 64 * 2 * 2);
		hdResultInInitState = true;
	}
}

void video::prepareTileData(bool isBg, Uint32 patternAddress, Uint8 tableID, Uint16 nameTableAddress, Uint8 row,
	colorCombo colors, Uint32 ramAddress, GLfloat& decodedX, GLfloat& decodedY, bool& isHD, GLfloat& brightness){
		bool hasWork = true;

		Uint32 idx;
		Uint16* hdResult;
		Uint16 resultSize;

		bool blankFound = false;
		Uint8 pix;
		Uint32 picPos;
    
		Uint16 readResult;
        bool hasHD;
        Uint32 picPos2;
        bitmapF packbmp;

		bool patternMatch;
		rawPattern patternData;
		Uint16 tilePatternX;
		Uint16 tilePatternY;

		if(isBg){
			hdResult = (Uint16*)bgHDResult;
			resultSize = 0x3C0;
		}
		else{
			hdResult = (Uint16*)spHDResult;
			resultSize = 0;
			if(row >= 8) row -= 8;
		}
		//look up index
		if(patternAddress != BAD_ADDRESS){
			Uint8 lookupIdx = (patternAddress & 0x00FF);

			if(romDat->chrPageCount == 0){
				patternData = *((rawPattern*)(&(romDat->chrRAM[ramAddress])));
			}

			//check for repeating tiles
			if(lastIsHD){
				if(hdPatternData[lastPatID].patternAddress == patternAddress
					&& hdPatternData[lastPatID].colors.colorValues == colors.colorValues){
					if(romDat->chrPageCount > 0){
						patternMatch = true;
					}
					else{
						patternMatch = (patternData.pixStrip1 == hdPatternData[lastPatID].rawDat.pixStrip1
									&& patternData.pixStrip2 == hdPatternData[lastPatID].rawDat.pixStrip2
									&& patternData.pixStrip3 == hdPatternData[lastPatID].rawDat.pixStrip3
									&& patternData.pixStrip4 == hdPatternData[lastPatID].rawDat.pixStrip4);
					}
					if(patternMatch){
						hasWork = false;
						decodedX = ((lastPatID) & 0x3F) / (GLfloat)TEXTURE_CACHE_TILE_COL_COUNT;
						decodedY = ((((lastPatID) >> TEXTURE_CACHE_TILE_COL_SHIFT) & 0x01F8) + row) / (GLfloat)(TEXTURE_CACHE_TILE_ROW_COUNT * 8);
						brightness = hdPatternData[lastPatID].brightness;
						hdPatternInUse[lastPatID] = 1;
						isHD = true;
						return;
					}
				}
			}
			else{
				if(basePatternData[lastPatID].patternAddress == patternAddress
					&& basePatternData[lastPatID].colors.colorValues == colors.colorValues){
					if(romDat->chrPageCount > 0){
						patternMatch = true;
					}
					else{
						patternMatch = (patternData.pixStrip1 == basePatternData[lastPatID].rawDat.pixStrip1
									&& patternData.pixStrip2 == basePatternData[lastPatID].rawDat.pixStrip2
									&& patternData.pixStrip3 == basePatternData[lastPatID].rawDat.pixStrip3
									&& patternData.pixStrip4 == basePatternData[lastPatID].rawDat.pixStrip4);
					}
					if(patternMatch){
						hasWork = false;
						decodedX = ((lastPatID) & 0x3F) / (GLfloat)TEXTURE_CACHE_TILE_COL_COUNT;
						decodedY = ((((lastPatID) >> TEXTURE_CACHE_TILE_COL_SHIFT) & 0x01F8) + row) / (GLfloat)(TEXTURE_CACHE_TILE_ROW_COUNT * 8);
						brightness = 1.0;
						basePatternInUse[lastPatID] = 1;
						isHD = false;
						return;
					}
				}
			}

			//look for matching pattern
			size_t e = hdList[lookupIdx].size();
			if(e > 0){
				const Uint32* lastInt = &hdList[lookupIdx][e - 1];
				Uint32* i = &hdList[lookupIdx][0];
				for( ; i <= lastInt; ++i){
					if(hdPatternData[*i].patternAddress == patternAddress
						&& hdPatternData[*i].colors.colorValues == colors.colorValues){
						if(romDat->chrPageCount > 0){
							patternMatch = true;
						}
						else{
							patternMatch = (patternData.pixStrip1 == hdPatternData[*i].rawDat.pixStrip1
										&& patternData.pixStrip2 == hdPatternData[*i].rawDat.pixStrip2
										&& patternData.pixStrip3 == hdPatternData[*i].rawDat.pixStrip3
										&& patternData.pixStrip4 == hdPatternData[*i].rawDat.pixStrip4);
						}
						if(patternMatch){
							hasWork = false;
							decodedX = ((*i) & 0x3F) / (GLfloat)TEXTURE_CACHE_TILE_COL_COUNT;
							decodedY = ((((*i) >> TEXTURE_CACHE_TILE_COL_SHIFT) & 0x01F8) + row) / (GLfloat)(TEXTURE_CACHE_TILE_ROW_COUNT * 8);
							brightness = hdPatternData[*i].brightness;
							hdPatternInUse[*i] = 1;
							lastIsHD = true;
							lastPatID = *i;
							isHD = true;
							return;
						}
					}
				}
			}
			e = baseList[lookupIdx].size();
			if(e > 0){{
				const Uint32* lastInt = &baseList[lookupIdx][e - 1];
				Uint32* i = &baseList[lookupIdx][0];
				for( ; i <= lastInt; ++i){
					if(basePatternData[*i].patternAddress == patternAddress
						&& basePatternData[*i].colors.colorValues == colors.colorValues){
						if(romDat->chrPageCount > 0){
							patternMatch = true;
						}
						else{
							patternMatch = (patternData.pixStrip1 == basePatternData[*i].rawDat.pixStrip1
										&& patternData.pixStrip2 == basePatternData[*i].rawDat.pixStrip2
										&& patternData.pixStrip3 == basePatternData[*i].rawDat.pixStrip3
										&& patternData.pixStrip4 == basePatternData[*i].rawDat.pixStrip4);
						}
						if(patternMatch){
							hasWork = false;
							decodedX = ((*i) & 0x3F) / (GLfloat)TEXTURE_CACHE_TILE_COL_COUNT;
							decodedY = ((((*i) >> TEXTURE_CACHE_TILE_COL_SHIFT) & 0x01F8) + row) / (GLfloat)(TEXTURE_CACHE_TILE_ROW_COUNT * 8);
							brightness = 1.0;
							basePatternInUse[*i] = 1;
							lastIsHD = false;
							lastPatID = *i;
							isHD = false;
							return;
						}
					}
				}			
			}
		}


        hasHD = false;
        if(usePack){
            //check the tile has HD version
			if((chrRamMatch || romDat->chrPageCount > 0) && patternAddress != BAD_ADDRESS){
				readResult = hdResult[tableID * resultSize + nameTableAddress];
				if((readResult != HD_TILE_NOT_CHECKED)){
					if(readResult == HD_TILE_NO_MATCH){
						hasHD = false;
					}
					else{
						TileData* t;
						hasHD = true;
						t = &(tdata[packData[patternAddress]]);
						packbmp = t->bitmapP[readResult];
					}
				}
				else{
					hdResultInInitState = false;
					hdResult[tableID * resultSize + nameTableAddress] = HD_TILE_NO_MATCH;
					if (packData[patternAddress] != BAD_ADDRESS){
						TileData* t;
						int packID = -1;
						t = &(tdata[packData[patternAddress]]);
						for (unsigned int tidx = 0; tidx < t->bitmapP.size(); ++tidx){
							if (t->bitmapP[tidx].colors.colorValues == colors.colorValues){
								if(romDat->chrPageCount > 0){
									patternMatch = true;
								}
								else{
									patternMatch = (patternData.pixStrip1 == t->bitmapP[tidx].rawDat.pixStrip1
												&& patternData.pixStrip2 == t->bitmapP[tidx].rawDat.pixStrip2
												&& patternData.pixStrip3 == t->bitmapP[tidx].rawDat.pixStrip3
												&& patternData.pixStrip4 == t->bitmapP[tidx].rawDat.pixStrip4);
								}
								if(patternMatch){
									packID = tidx;
									hasHD = true;
									break;
								}
							}
						}
						if (packID == -1 && t->defaultID != -1){ 
							packID = t->defaultID;
							hasHD = true;
						}
						if(hasHD){
							//get scale from hd pack
							packbmp = t->bitmapP[packID];
							hdResult[tableID * resultSize + nameTableAddress] = packID;
						}
					}
				}
			}
        }

		//look for blank space
		if(hasHD){
			idx = maxHDIdx;
			while(!blankFound){
				if(!blankFound && hdPatternInUse[idx] != 1){
					blankFound = true;
				}
				else{
					++idx;
					if(idx >= TEXTURE_CACHE_TILE_COUNT){
						idx = 0;
					}
				}
			}

			tilePatternX = ((idx & 0x3F) << 3) * packScale;
			tilePatternY = ((idx >> TEXTURE_CACHE_TILE_COL_SHIFT) & 0x01F8) * packScale;
		}
		else{
			idx = maxBaseIdx;
			while(!blankFound){
				if(!blankFound && basePatternInUse[idx] != 1){
					blankFound = true;
				}
				else{
					++idx;
					if(idx >= TEXTURE_CACHE_TILE_COUNT){
						idx = 0;
					}
				}
			}

			tilePatternX = (idx & 0x3F) << 3;
			tilePatternY = (idx >> TEXTURE_CACHE_TILE_COL_SHIFT) & 0x01F8;
		}
		decodedX = (idx & 0x3F) / (GLfloat)TEXTURE_CACHE_TILE_COL_COUNT;
		decodedY = (((idx >> TEXTURE_CACHE_TILE_COL_SHIFT) & 0x01F8) + row) / (GLfloat)(TEXTURE_CACHE_TILE_ROW_COUNT * 8);


		lastPatID = idx;
		lastIsHD = hasHD;
		isHD = hasHD;
		if(!hasHD){
            brightness = 1.0f;
			//decode
			picPos = tilePatternY * 512 + tilePatternX;

			if(romDat->chrPageCount > 0){
				patternData = *((rawPattern*)(&(romDat->chrROM[patternAddress << 4])));
			}
			Uint8 patternByte0;
			Uint8 patternByte1;
			Uint8* patternBytes = (Uint8*)&patternData;
			Uint8* patternBytes1 = patternBytes + 8;
			for(int j = 0; j < 8; ++j){
				patternByte0 = *patternBytes;
				++patternBytes;
				patternByte1 = *patternBytes1;
				++patternBytes1;
				for(int i = 7; i >= 0; --i){
					pix = ((patternByte0 >> i) & 0x01) | (((patternByte1 >> i) & 0x01) << 1);
					switch(pix){
					case 0:
						baseTextureCache[picPos] = 0;
						break;
					case 1:
						baseTextureCache[picPos] = colourList[colors.color1 & 0x3F];
						break;
					case 2:
						baseTextureCache[picPos] = colourList[colors.color2 & 0x3F];
						break;
					case 3:
						baseTextureCache[picPos] = colourList[colors.color3 & 0x3F];
						break;
					}
					picPos++;
				}
				picPos += 504;
			}
			maxBaseIdx = idx + 1;
			if(maxBaseIdx >= TEXTURE_CACHE_TILE_COUNT){
				maxBaseIdx = 0;
			}
			if(basePatternInUse[idx] == 0){
				//if previous used then remove the previous record
				baseList[basePatternData[idx].lookupIdx].erase(baseList[basePatternData[idx].lookupIdx].begin() + basePatternData[idx].index);
				//shift remaining entries
				if(baseList[basePatternData[idx].lookupIdx].size() > basePatternData[idx].index){
					for(std::vector<Uint32>::const_iterator i = baseList[basePatternData[idx].lookupIdx].begin() + basePatternData[idx].index; i != baseList[basePatternData[idx].lookupIdx].end(); i++){
						basePatternData[*i].index = basePatternData[*i].index - 1; 
					}
				}
			}
			basePatternInUse[idx] = 1;
			basePatternData[idx].patternAddress = patternAddress;
			basePatternData[idx].colors = colors;
			basePatternData[idx].rawDat = patternData;
			basePatternData[idx].lookupIdx = lookupIdx;
			basePatternData[idx].index = baseList[lookupIdx].size();
			basePatternData[idx].brightness = brightness;
			baseList[lookupIdx].push_back(idx);
		}
        else{
            brightness = packbmp.brightness;
			picPos = tilePatternY * 512 * packScale + tilePatternX;
            picPos2 = (packbmp.y * bmpInfos[packbmp.bitmapID].width + packbmp.x) * 4;

			scale4Pattern* sp4;
			scale4Pattern* rb4;
			scale2Pattern* sp2;
			scale2Pattern* rb2;
			scale1Pattern* sp1;
			scale1Pattern* rb1;

			for(int j = 0; j < 8; ++j){ 
				switch (packScale) {
					case 4:
					
						sp4 = (scale4Pattern*)&(hdTextureCache[picPos]);
						rb4 = (scale4Pattern*)&((rawBits[packbmp.bitmapID])[picPos2]);
						sp4[0] = rb4[0];

						picPos += 2048;
						picPos2 += (bmpInfos[packbmp.bitmapID].width * 4);
						sp4 = (scale4Pattern*)&(hdTextureCache[picPos]);
						rb4 = (scale4Pattern*)&((rawBits[packbmp.bitmapID])[picPos2]);
						sp4[0] = rb4[0];

						picPos += 2048;
						picPos2 += (bmpInfos[packbmp.bitmapID].width * 4);
						sp4 = (scale4Pattern*)&(hdTextureCache[picPos]);
						rb4 = (scale4Pattern*)&((rawBits[packbmp.bitmapID])[picPos2]);
						sp4[0] = rb4[0];

						picPos += 2048;
						picPos2 += (bmpInfos[packbmp.bitmapID].width * 4);
						sp4 = (scale4Pattern*)&(hdTextureCache[picPos]);
						rb4 = (scale4Pattern*)&((rawBits[packbmp.bitmapID])[picPos2]);
						sp4[0] = rb4[0];
					
						picPos += 2048;
						picPos2 += (bmpInfos[packbmp.bitmapID].width * 4);
						break;
					case 2:
						sp2 = (scale2Pattern*)&(hdTextureCache[picPos]);
						rb2 = (scale2Pattern*)&((rawBits[packbmp.bitmapID])[picPos2]);
						sp2[0] = rb2[0];

						picPos += 1024;
						picPos2 += (bmpInfos[packbmp.bitmapID].width * 4);
						sp2 = (scale2Pattern*)&(hdTextureCache[picPos]);
						rb2 = (scale2Pattern*)&((rawBits[packbmp.bitmapID])[picPos2]);
						sp2[0] = rb2[0];

						picPos += 1024;
						picPos2 += (bmpInfos[packbmp.bitmapID].width * 4);
						break;
                    
					default:
						sp1 = (scale1Pattern*)&(hdTextureCache[picPos]);
						rb1 = (scale1Pattern*)&((rawBits[packbmp.bitmapID])[picPos2]);
						sp1[0] = rb1[0];

						picPos += 512;
						picPos2 += (bmpInfos[packbmp.bitmapID].width * 4);
						break;
				}
			}
			maxHDIdx = idx + 1;
			if(maxHDIdx >= TEXTURE_CACHE_TILE_COUNT){
				maxHDIdx = 0;
			}
			if(hdPatternInUse[idx] == 0){
				//if previous used then remove the previous record
				hdList[hdPatternData[idx].lookupIdx].erase(hdList[hdPatternData[idx].lookupIdx].begin() + hdPatternData[idx].index);
				//shift remaining entries
				if(hdList[hdPatternData[idx].lookupIdx].size() > hdPatternData[idx].index){
					for(std::vector<Uint32>::const_iterator i = hdList[hdPatternData[idx].lookupIdx].begin() + hdPatternData[idx].index; i != hdList[hdPatternData[idx].lookupIdx].end(); i++){
						hdPatternData[*i].index = hdPatternData[*i].index - 1; 
					}
				}
			}
			hdPatternInUse[idx] = 1;
			hdPatternData[idx].patternAddress = patternAddress;
			hdPatternData[idx].colors = colors;
			hdPatternData[idx].rawDat = patternData;
			hdPatternData[idx].lookupIdx = lookupIdx;
			hdPatternData[idx].index = hdList[lookupIdx].size();
			hdPatternData[idx].brightness = brightness;
			hdList[lookupIdx].push_back(idx);
        }
	}
}





void video::capScreen(bool useNative){
	char buffer [80];
	char frameCntBuffer[15];
    time_t timer;
	struct tm * timeinfo;
	string filename;
	
	//cpuCore->runLog = !cpuCore->runLog;
	time(&timer);
	timeinfo = localtime (&timer);
	strftime (buffer,80,"%Y%m%d%H%M%S",timeinfo);
	sprintf (frameCntBuffer, "X%013d", ppuCore->frameCount);
	filename = setting->exeDir + "\\screen\\" + buffer + frameCntBuffer + ".png";

	saveScreenToPath(filename, useNative);

	////save graphic strips
	SaveGraphics(setting->exeDir + "\\screen\\" + buffer + to_string((long double)ppuCore->frameCount));   

	////save buffers
	//SaveBuffers(setting->exeDir + "\\screen\\" + buffer + to_string((long double)ppuCore->frameCount));

	////save sprite
	//ppuCore->saveSprObjects(setting->exeDir + "\\screen\\" + buffer + to_string((long double)ppuCore->frameCount));
	//ppuCore->saveVRam(setting->exeDir + "\\screen\\" + buffer + to_string((long double)ppuCore->frameCount));
	//saveBG(setting->exeDir + "\\screen\\" + buffer + to_string((long double)ppuCore->frameCount));


	capScreenFlag = false;
}

void video::saveScreenToPath(string path, bool useNative){
    int capWidth;
    int capHeight;
    int idxX[DISPLAY_WIDTH];
	int idxY[DISPLAY_HEIGHT];

    if (useNative) {
        capWidth = DISPLAY_WIDTH;
        capHeight = DISPLAY_HEIGHT;
		for(unsigned int tmpy = 0; tmpy < DISPLAY_HEIGHT; ++tmpy){
			idxY[tmpy] = screenSizeHeight * tmpy / capHeight;
		}
		for(unsigned int tmpx = 0; tmpx < DISPLAY_WIDTH; ++tmpx){
			idxX[tmpx] = screenSizeWidth * tmpx / capWidth;
		}
    }
    else{
        capWidth = screenSizeWidth;
        capHeight = screenSizeHeight;
    }

	GLubyte *data = (GLubyte *)malloc(4 * screenSizeWidth * screenSizeHeight);
	if(data) {
		glReadPixels(0, 0, screenSizeWidth, screenSizeHeight, GL_RGB, GL_UNSIGNED_BYTE, data);

		SDL_Surface * sc = SDL_CreateRGBSurface(SDL_SWSURFACE, capWidth, capHeight, 24, 0x0000FF, 0x00FF00, 0xFF0000, 0);
		if(sc){
			int i;
			int j;
			int y;
			int runy;
			SDL_LockSurface(sc);
		    for(y = capHeight - 1, runy = 0; y >= 0; --y, ++runy){
				Uint8 *p = (Uint8 *)sc->pixels + y * sc->pitch;
				j = 0;
		        for(unsigned int x = 0; x < capWidth; ++x){
					if (useNative){
						i = 3 * (screenSizeWidth * idxY[runy] + idxX[x]);
					}
					else{
						i = 3 * (screenSizeWidth * runy + x);
					}
					p[j] = data[i];
					i++;
					j++;
					p[j] = data[i];
					i++;
					j++;
					p[j] = data[i];
					j++;
				}	
			}
			SDL_UnlockSurface(sc);
			SDL_SaveBMP(sc, (path + ".bmp").c_str());
			SDL_FreeSurface(sc);
		}
		
		capScreenQueue.push_back(path);
		SDL_Thread* gh;  
		gh = SDL_CreateThread(video::convertScreenCapToPNG, NULL, NULL);
		
	}
	else{
		return;
	}

    free(data);
}

int video::convertScreenCapToPNG(void* data){
	string path;
	wxImage objimg;
	while(vid->capScreenQueue.size() > 0){
		path = vid->capScreenQueue[vid->capScreenQueue.size() - 1];
		vid->capScreenQueue.pop_back();
		objimg = wxImage(wxString((path + ".bmp").c_str(), wxConvUTF8));
		objimg.SaveFile(wxString(path.c_str(), wxConvUTF8));
		remove((path + ".bmp").c_str());
	}
	return 0;
}

void video::SaveHiResPack(){
    char rawPalette[192];
	if(packData == 0) return;

	//get directory and check exists
    string path = getHDPackPath();
	_mkdir(path.c_str());
	DWORD ftyp = GetFileAttributesA(path.c_str());
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY){
		string filename;
 		fstream logfile;

		filename = path + "\\hires.txt";
		logfile.open(filename, ios::out | ios::trunc);
		if (logfile.is_open()){
			logfile << "<ver>2\n";
            logfile << "<scale>" + to_string((long double)packScale) + "\n";
			for(unsigned int i = 0; i < bmpInfos.size(); i++){
				logfile << "<img>" + bmpInfos[i].filename + "\n";
			}

			for(unsigned int i = 0; i < packSize; i++){
				if(packData[i] != BAD_ADDRESS){
					for(unsigned int j = 0; j < tdata[packData[i]].bitmapP.size(); j++){
						bitmapF b = tdata[packData[i]].bitmapP[j];
						logfile << "<tile>" + to_string((long double)i) + "," 
							+ to_string((long double)b.bitmapID) + "," 
							+ to_string((long double)b.colors.color1) + "," 
							+ to_string((long double)b.colors.color2) + "," 
							+ to_string((long double)b.colors.color3) + "," 
							+ to_string((long double)b.x) + "," 
							+ to_string((long double)b.y) + ","
                            + to_string((long double)b.brightness) + ","
							+ (tdata[packData[i]].defaultID == j ? "Y" : "N");
						
						if(romDat->chrPageCount == 0){
							for(int i = 0; i < 16; i++){
								logfile << ", " + to_string((long double)(*((Uint8*)(&(b.rawDat)) + i)));
							}
						}

						logfile << "\n";
					}
				}
			}
			for(unsigned int i = 0; i < metaSprites.size(); i++){
				metaSprite metaspr = metaSprites[i];

				logfile << "<metas>" + metaspr.name + "," 
				+ to_string((long double)metaspr.bitmapID) + "," 
				+ to_string((long double)metaspr.brightness) + ","
				+ to_string((long double)metaspr.priority) + ","
				+ (metaspr.useLargeSpr ? "Y" : "N");
				logfile << "\n";

				for(unsigned int j = 0; j < metaspr.parts.size(); j++){
					metaSpritePart metaPart = metaspr.parts[j];

					logfile << "<metasp>" + to_string((long double)metaPart.patternAddress) + "," 
					+ to_string((long double)metaPart.colors.color1) + "," 
					+ to_string((long double)metaPart.colors.color2) + "," 
					+ to_string((long double)metaPart.colors.color3) + "," 
					+ to_string((long double)metaPart.relativeX) + "," 
					+ to_string((long double)metaPart.relativeY) + ","
					+ (metaPart.relativeHFlip ? "Y" : "N") + ","
					+ (metaPart.relativeVFlip ? "Y" : "N") + ","
					+ (metaPart.isSecond ? "Y" : "N");
					if(romDat->chrPageCount == 0){
						for(int i = 0; i < 16; i++){
							logfile << ", " + to_string((long double)(*((Uint8*)(&(metaPart.rawDat)) + i)));
						}
					}
					logfile << "\n";
				}
			}
			logfile.close();
		}
        filename = path + "\\palette.dat";
		logfile.open(filename, ios::out | ios::binary | ios::trunc);
		if (logfile.is_open()){
            for (int i = 0; i < 64; i++) {
                rawPalette[i * 3] = (colourList[i] >> 24) & 0xff;
                rawPalette[i * 3 + 1] = (colourList[i] >> 16) & 0xff;
                rawPalette[i * 3 + 2] = (colourList[i] >> 8) & 0xff;
            }
            logfile.write((char *)(rawPalette), 192);
            logfile.close();
        }
	}
}


void video::ReadHiResPack(){
    int packVersion = 0;
    int readIdx;
	packData = (Uint32*) malloc(packSize * sizeof(Uint32));
	for(unsigned int i = 0; i < packSize; i++){
		packData[i] = BAD_ADDRESS;
	}
	packScale = 2;
    packVersion = 0;
    initColour();

	//get directory and check exists
    string path = getHDPackPath();
	DWORD ftyp = GetFileAttributesA(path.c_str());
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY){

		//read the file
		fstream inifile;
		string line;

		inifile.open(path + "\\hires.txt", ios::in);
		if (inifile.is_open()){

			while ( inifile.good() ){
				std::getline(inifile, line);
                if(line.substr(0, 5) == "<ver>"){
                    //read version number
					packVersion = stoi(line.substr(5, string::npos));
				}
                else if(line.substr(0, 5) == "<img>"){
                    //read a png file
					string bmpName = line.substr(5, string::npos);
					AddHiResImg(bmpName);
				}
                else if(line.substr(0, 6) == "<tile>"){
                    vector<string> lineTokens;

                    split(line.substr(6, string::npos), ',', lineTokens);
                    if (lineTokens.size() >= 8) {
                        int index = stoi(lineTokens[0]);
                        if (packData[index] == BAD_ADDRESS){
                            packData[index] = tdata.size();
							TileData t;
							t.patternAddress = index;
                            tdata.push_back(t);
                            tdata.back().defaultID = -1;
                        }
                        bitmapF b;
                        b.bitmapID = stoi(lineTokens[1]);
                        b.colors.color1 = stoi(lineTokens[2]);
                        b.colors.color2 = stoi(lineTokens[3]);
                        b.colors.color3 = stoi(lineTokens[4]);
                        b.x = stoi(lineTokens[5]);
                        b.y = stoi(lineTokens[6]);
                        
                        readIdx = 7;
                        if (packVersion > 0) {
                            b.brightness = stof(lineTokens[readIdx]);
                            readIdx++;
                        }
                        else{
                            b.brightness = 1.0f;
                        }
                        
                        if(lineTokens[readIdx] == "Y"){
                            tdata[packData[index]].defaultID = tdata[packData[index]].bitmapP.size();
                            readIdx++;
                        }
						readIdx++;
						if(romDat->chrPageCount == 0){
							for(int i = 0; i < 16; i++){
								*((Uint8*)(&(b.rawDat)) + i) = stoi(lineTokens[readIdx]);
                                readIdx++;
							}
						}                    

                        tdata[packData[index]].bitmapP.push_back(b);          
                    }
                    
                }
                else if(line.substr(0, 7) == "<scale>"){
                    packScale = stoi(line.substr(7, string::npos));
                }
				else if(line.substr(0, 7) == "<metas>"){
                    vector<string> lineTokens;

                    split(line.substr(7, string::npos), ',', lineTokens);
                    if (lineTokens.size() >= 5) {
						metaSprite metaspr;
						metaspr.id = metaSprites.size();
						metaspr.name = lineTokens[0];
						metaspr.bitmapID = stoi(lineTokens[1]);
                        metaspr.brightness = stof(lineTokens[2]);
						metaspr.priority = stoi(lineTokens[3]);
						metaspr.useLargeSpr = (lineTokens[4] == "Y");
						metaSprites.push_back(metaspr);
					}
				}
				else if(line.substr(0, 8) == "<metasp>"){
                    vector<string> lineTokens;

                    split(line.substr(8, string::npos), ',', lineTokens);
                    if (lineTokens.size() >= 9) {
						metaSpritePart metapat;
						metapat.patternAddress = stoi(lineTokens[0]);
                        metapat.colors.color1 = stoi(lineTokens[1]);
                        metapat.colors.color2 = stoi(lineTokens[2]);
                        metapat.colors.color3 = stoi(lineTokens[3]);
                        metapat.relativeX = stoi(lineTokens[4]);
                        metapat.relativeY = stoi(lineTokens[5]);
						metapat.relativeHFlip = (lineTokens[6] == "Y");
						metapat.relativeVFlip = (lineTokens[7] == "Y");
						metapat.isSecond = (lineTokens[8] == "Y");
						if(romDat->chrPageCount == 0){
							for(int i = 9; i < 25; i++){
								*((Uint8*)(&(metapat.rawDat)) + i) = stoi(lineTokens[i]);
							}
						}         
						metaSprite metaspr = metaSprites[metaSprites.size() - 1];
						metaspr.parts.push_back(metapat);
						metaSprites[metaSprites.size() - 1] = metaspr;
					}
				}
			}
			inifile.close();
            
            if(packVersion > 1){
                ReadPalette(path + "\\palette.dat");
            }
		}
	}
}

void video::CleanHiResPack(){
	if(packData){
		free(packData);
		for(unsigned int i = 0; i < rawBits.size(); i++) {
			free(rawBits[i]);
		}
		tdata.clear();
		rawBits.clear();
		bmpInfos.clear();
		metaSprites.clear();
	}
}

void video::AddHiResImg(string filename){
	SDL_Surface * pngs;
	pngs = IMG_Load((getHDPackPath() + "\\" + filename).c_str());
    Uint8* bits = (Uint8*) malloc(pngs->w * pngs->h * 4);
    SDL_LockSurface(pngs);
	int i = 0;
    for(int y = 0; y < pngs->h; y++){
        for(int x = 0; x < pngs->w; x++){
			Uint8 *p = (Uint8 *)pngs->pixels + y * pngs->pitch + x * 4;
			bits[i] = p[3];
			i++;
			bits[i] = p[2];
			i++;
			bits[i] = p[1];
			i++;
			bits[i] = p[0];
			i++;
        }	
    }
    bmpInfo bsize;
    bsize.width = pngs->w;
    bsize.height = pngs->h;
	bsize.filename = filename;
    bmpInfos.push_back(bsize);

    SDL_UnlockSurface(pngs);
    SDL_FreeSurface(pngs);
    rawBits.push_back(bits);
}

void video::RemoveHiResImg(unsigned int pID){
	bmpInfos.erase(bmpInfos.begin() + pID);
}

void video::AddDarkMapping(){
    bool hasMatch;
    TileData* t;
    TileData e;
    bitmapF newD;
	//go through each HD tile
	for(unsigned int i = 0; i < packSize; i++){
		if(packData[i] != BAD_ADDRESS){
            t = &(tdata[packData[i]]);
			if(t->defaultID == -1){
				for(unsigned int j = 0; j < t->bitmapP.size(); j++){
				bitmapF b = t->bitmapP[j];
				if(b.brightness == 1.0f){
					if (editData[i] != BAD_ADDRESS){
						//do not add if it has a default

						
							e = etiledata[editData[i]];
                            //search for a palette of that tile with no HD replacement
							for(unsigned int k = 0; k < e.bitmapP.size(); k++){
                                //only do it when that palette is different from the original
                                if (e.bitmapP[k].colors.colorValues != b.colors.colorValues) {
                                    hasMatch = false;
                                    for(unsigned int l = 0; l < t->bitmapP.size(); l++){
                                        if (t->bitmapP[l].colors.colorValues == e.bitmapP[k].colors.colorValues){
                                            if(romDat->chrPageCount > 0){
                                                hasMatch = true;
                                            }
                                            else{
                                                hasMatch = (e.bitmapP[k].rawDat.pixStrip1 == t->bitmapP[l].rawDat.pixStrip1
                                                            && e.bitmapP[k].rawDat.pixStrip2 == t->bitmapP[l].rawDat.pixStrip2
                                                            && e.bitmapP[k].rawDat.pixStrip3 == t->bitmapP[l].rawDat.pixStrip3
                                                            && e.bitmapP[k].rawDat.pixStrip4 == t->bitmapP[l].rawDat.pixStrip4);
                                            }
                                            if(hasMatch){
                                                break;
                                            }
                                        }
                                        
                                    }
                                    if(!hasMatch) {
                                        //check that palette is a darker version of the HD tile
                                        if(IsDarkerPalette(e.bitmapP[k].colors, b.colors)){
                                            //add a mapping to it and calculate a brightness value for the palette
                                            newD = b;
                                            newD.brightness = CalBrightnessValue(e.bitmapP[k].colors, b.colors);
                                            newD.colors = e.bitmapP[k].colors;
											newD.isBg = e.bitmapP[k].isBg;
                                            t->bitmapP.push_back(newD);
                                        }
                                    }
                                }
							}
						}					
					}
				}
			}
		}
	}
}

string video::GetPaletteString(colorCombo color){
	char tmpStr[10];
	sprintf_s(tmpStr,"%02x,%02x,%02x", color.color1, color.color2, color.color3);
	return string(tmpStr);
}


GLfloat video::CalBrightnessValue(colorCombo color, colorCombo refColor){
    Uint16 b1;
    Uint16 b2;
    
    b1 = ((colourList[color.color1] >> 24) & 0x00FF) + ((colourList[color.color1] >> 16) & 0x00FF) + ((colourList[color.color1] >> 8) & 0x00FF)
		+ ((colourList[color.color2] >> 24) & 0x00FF) + ((colourList[color.color2] >> 16) & 0x00FF) + ((colourList[color.color2] >> 8) & 0x00FF)
		+ ((colourList[color.color3] >> 24) & 0x00FF) + ((colourList[color.color3] >> 16) & 0x00FF) + ((colourList[color.color3] >> 8) & 0x00FF);
    b2 = ((colourList[refColor.color1] >> 24) & 0x00FF) + ((colourList[refColor.color1] >> 16) & 0x00FF) + ((colourList[refColor.color1] >> 8) & 0x00FF)
		+ ((colourList[refColor.color2] >> 24) & 0x00FF) + ((colourList[refColor.color2] >> 16) & 0x00FF) + ((colourList[refColor.color2] >> 8) & 0x00FF)
		+ ((colourList[refColor.color3] >> 24) & 0x00FF) + ((colourList[refColor.color3] >> 16) & 0x00FF) + ((colourList[refColor.color3] >> 8) & 0x00FF);
    if (b2 > 0) {
        return (float)((b1 * 100) / b2) / 100.0f;
    }
    else{
        return 0;
    }
}

bool video::IsDarkerPalette(colorCombo color, colorCombo refColor){
	return IsDarkerColor(color.color1, refColor.color1) && IsDarkerColor(color.color2, refColor.color2) && IsDarkerColor(color.color3, refColor.color3); 
}

bool video::IsDarkerColor(Uint16 color, Uint16 refColor){
	if(color == refColor){
		return true;
	}
    else if(colourList[color] == 0x000000FF){
        //return true for new color is pure black
        return true;
    }
    else if(colourList[refColor] == 0x000000FF){
        //return false for old color is pure black
        return false;
    }
    else if(((color & 0x000F) == 0x0000) || ((color & 0x000F) == 0x000D)){
        //monochrome matching
        if(((refColor & 0x000F) == 0x0000) || ((refColor & 0x000F) == 0x000D)){
            return (colourList[refColor] >= colourList[color]);
        }
        else{
            return false;
        }
    }
    else{
        //color matching
        if(((refColor & 0x000F) == 0x0000) || ((refColor & 0x000F) == 0x000D)){
            return false;
        }
        else{
            Uint16 row1;
            Uint16 row2;
            Uint16 hue1;
            Uint16 hue2;
            Uint16 hueDif;
            
            row1 = (color & 0x00F0) >> 4;
            row2 = (refColor & 0x00F0) >> 4;
            if (row2 > row1){
                hue1 = (color & 0x000F);
                hue2 = (refColor & 0x000F);
                if (hue1 > hue2) {
                    hueDif = hue1 - hue2;
                }
                else{
                    hueDif = hue2 - hue1;
                }
                if((row2 - row1) <=2) {
                    if(hueDif <= 1 || hueDif == 11){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
                else{
                    if(hueDif <= 2 || hueDif >= 10){
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }
            else{
                return false;
            }
        }
    }
}

void video::ReadPackEdit(){
	editData = (Uint32*) malloc(packSize * sizeof(Uint32));
	allEditData = (Uint32*) malloc(packSize * sizeof(Uint32));
	for(unsigned int i = 0; i < packSize; i++){
		editData[i] = BAD_ADDRESS;
		allEditData[i] = BAD_ADDRESS;
	}
	//get directory and check exists
    string path = getEditPackPath();
	_mkdir(path.c_str());

	DWORD ftyp = GetFileAttributesA(path.c_str());
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY){
        
		//read the file
		fstream inifile;
		fstream inifile2;
		string line;
        
        screenNameList.clear();
        screenFileNameList.clear();
        etiledata.clear();
        allEtiledata.clear();
        
		inifile.open(path + "screen.dat", ios::in);
		if (inifile.is_open()){			
			while ( inifile.good() ){
				std::getline(inifile, line);
                vector<string> lineTokens;
                
                split(line, ';', lineTokens);
				if(lineTokens.size() == 2){
					screenFileNameList.push_back(lineTokens[0]);
					screenNameList.push_back(lineTokens[1]);
					inifile2.open(path + lineTokens[0] + ".dat", ios::in);
					if (inifile2.is_open()){
						while ( inifile2.good() ){
							std::getline(inifile2, line);
							vector<string> lineTokens2;
                    
							split(line, ',', lineTokens2);
							if(lineTokens2.size() >= 7){
								int index = stoi(lineTokens2[1]);

                                if (editData[index] == BAD_ADDRESS){
									TileData t;
									if(lineTokens2[0] == "Y"){
										t.defaultID = 0;
									}
									else{
										t.defaultID = 1;
									}
									t.patternAddress = index;
                                    editData[index] = etiledata.size();
                                    etiledata.push_back(t);
                                }

                                bitmapF b;
                                b.isBg = (lineTokens2[0] == "Y");
								b.bitmapID = screenFileNameList.size() - 1;
								b.colors.color1 = stoi(lineTokens2[2]);
								b.colors.color2 = stoi(lineTokens2[3]);
								b.colors.color3 = stoi(lineTokens2[4]);
								b.x = stoi(lineTokens2[5]);
								b.y = stoi(lineTokens2[6]);
								if(romDat->chrPageCount == 0){
									for(int i = 0; i < 16; i++){
										*((Uint8*)(&(b.rawDat)) + i) = stoi(lineTokens2[7 + i]);
									}
								}                    
                                etiledata[editData[index]].bitmapP.push_back(b);

							}
						}
					}
					inifile2.close();
					inifile2.open(path + lineTokens[0] + "_a.dat", ios::in);
					if (inifile2.is_open()){
						while ( inifile2.good() ){
							std::getline(inifile2, line);
							vector<string> lineTokens2;
                            
							split(line, ',', lineTokens2);
							if(lineTokens2.size() >= 7){
								int index = stoi(lineTokens2[1]);
                                
								if (allEditData[index] == BAD_ADDRESS){
									TileData t;
									if(lineTokens2[0] == "Y"){
										t.defaultID = 0;
									}
									else{
										t.defaultID = 1;
									}
									t.patternAddress = index;
                                     allEditData[index] = allEtiledata.size();
                                    allEtiledata.push_back(t);
                                }
								
								bitmapF b;
                                b.isBg = (lineTokens2[0] == "Y");
								b.bitmapID = screenFileNameList.size() - 1;
								b.colors.color1 = stoi(lineTokens2[2]);
								b.colors.color2 = stoi(lineTokens2[3]);
								b.colors.color3 = stoi(lineTokens2[4]);
								b.x = stoi(lineTokens2[5]);
								b.y = stoi(lineTokens2[6]);
								if(romDat->chrPageCount == 0){
									for(int i = 0; i < 16; i++){
										*((Uint8*)(&(b.rawDat)) + i) = stoi(lineTokens2[7 + i]);
									}
								}

                                allEtiledata[allEditData[index]].bitmapP.push_back(b);
							}

						}
					}
					inifile2.close();
				}
			}
			inifile.close();
			guiForm->refreshGraphicsPackGUI();
		}
	}
}

void video::CleanPackEdit(){
	if(editData){
		free(editData);
	}
}

void video::readConfig(string value){
    vector<string> lineTokens;
    
    split(value, ',', lineTokens);
    if (lineTokens[0].compare("screensize") == 0) {
        screenSizeOption = stoi(lineTokens[1]);
        screenSizeWidth = stoi(lineTokens[2]);
        screenSizeHeight = stoi(lineTokens[3]);
    }
    if (lineTokens[0].compare("usepack") == 0) {
        usePack = (lineTokens[1].compare("Y") == 0);
    }
    if (lineTokens[0].compare("editrecordtype") == 0) {
	    editRecordingType = stoi(lineTokens[1]);
    }
    if (lineTokens[0].compare("edgetile") == 0) {
        cutEdgeTiles = (lineTokens[1].compare("Y") != 0);
    }
    if (lineTokens[0].compare("chrRamMatch") == 0) {
        chrRamMatch = (lineTokens[1].compare("Y") == 0);
    }
    if (lineTokens[0].compare("caprate") == 0) {
        capRate = stoi(lineTokens[1]);
    }

}

void video::saveConfig(fstream* inifile){
    (*inifile) << "video:screensize," + to_string((long double)screenSizeOption) + "," + to_string((long double)screenSizeWidth) + "," + to_string((long double)screenSizeHeight) + "\n";
    (*inifile) << "video:usepack," +  string(usePack ? "Y":"N") + "\n";
    (*inifile) << "video:editrecordtype," +  to_string((long double)editRecordingType) + "\n";
    (*inifile) << "video:edgetile," +  string(!cutEdgeTiles ? "Y":"N") + "\n";
    (*inifile) << "video:chrRamMatch," +  string(chrRamMatch ? "Y":"N") + "\n";
    (*inifile) << "video:caprate," +  to_string((long double)capRate) + "\n";
}

void video::SavePackEditScreen(){
	//check for directory
	string path = getEditPackPath();
    
	_mkdir(path.c_str());
	DWORD ftyp = GetFileAttributesA(path.c_str());
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY){
		char buffer[80];
		char frameCntBuffer[15];
		time_t timer;
		struct tm * timeinfo;
		string filename;
    
		//save screen shot first
		time(&timer);
		timeinfo = localtime (&timer);
		strftime (buffer,80,"%Y%m%d%H%M%S",timeinfo);
		sprintf (frameCntBuffer, "X%013d", ppuCore->frameCount);
		filename = path + buffer + frameCntBuffer + ".png";
		saveScreenToPath(filename, TRUE);
    
		//save screen file log
		fstream logfile;
    
		filename = path + buffer + frameCntBuffer + ".dat";
		logfile.open(filename, ios::out | ios::trunc);
		if (logfile.is_open()){
			for(unsigned int i = 0; i < screenTiles.size(); i++){
				screenTile st = screenTiles[i];
				logfile << (st.isBg ? "Y" : "N") + string(", ") + to_string((long double)st.patternAddress) + ", " + to_string((long double)st.colors.color1) + ", " + to_string((long double)st.colors.color2) + ", " + to_string((long double)st.colors.color3) + ", " + to_string((long double)st.x) + ", " + to_string((long double)st.y);
				if(romDat->chrPageCount == 0){
					for(int i = 0; i < 16; i++){
						logfile << ", " + to_string((long double)(*((Uint8*)(&(st.rawDat)) + i)));
					}
				}
				logfile << "\n";

				//chalk it off
				bitmapF b;
				b.bitmapID = screenFileNameList.size();
				b.colors = st.colors;
				b.rawDat = st.rawDat;
                b.isBg = st.isBg;
				b.x = st.x;
				b.y = st.y;
				etiledata[editData[st.patternAddress]].bitmapP.push_back(b);

			}
			logfile.close();
		}
    
		filename = path + buffer + frameCntBuffer + "_a.dat";
		logfile.open(filename, ios::out | ios::trunc);
		if (logfile.is_open()){
			for(unsigned int i = 0; i < allScreenTiles.size(); i++){
				screenTile st = allScreenTiles[i];
				logfile << (st.isBg ? "Y" : "N") + string(", ") + to_string((long double)st.patternAddress) + ", " + to_string((long double)st.colors.color1) + ", " + to_string((long double)st.colors.color2) + ", " + to_string((long double)st.colors.color3) + ", " + to_string((long double)st.x) + ", " + to_string((long double)st.y);
				if(romDat->chrPageCount == 0){
					for(int i = 0; i < 16; i++){
						logfile << ", " + to_string((long double)(*((Uint8*)(&(st.rawDat)) + i)));
					}
				}
				logfile << "\n";

				//chalk it off
				bitmapF b;
				b.bitmapID = screenFileNameList.size();
				b.colors = st.colors;
				b.rawDat = st.rawDat;
                b.isBg = st.isBg;
				b.x = st.x;
				b.y = st.y;
				allEtiledata[allEditData[st.patternAddress]].bitmapP.push_back(b);

			}
			logfile.close();
		}
    
		filename = path + buffer + frameCntBuffer + "_ppu.dat";
		logfile.open(filename, ios::out | ios::binary |  ios::trunc);
		if (logfile.is_open()){
			memDat->savePPUData(&logfile);
			logfile.close();
		}

		//save screen list
		filename = string(buffer) + frameCntBuffer;
		screenNameList.push_back("/");
		screenFileNameList.push_back(filename);
    
        SavePackEditScreenList();


		//save graphic strips
		//SaveGraphics(path + buffer + to_string((long double)ppuCore->frameCount));   

		//save buffers
		//SaveBuffers(path + buffer + to_string((long double)ppuCore->frameCount));
    }

}
                                                                          
void video::SavePackEditScreenList(){
	string path = getEditPackPath();
    string filename;
    fstream logfile;
    
    filename = path + "screen.dat";
    logfile.open(filename, ios::out | ios::trunc);
    if (logfile.is_open()){
        for(unsigned int i = 0; i < screenFileNameList.size(); i++){
            logfile << screenFileNameList[i] + ";" + screenNameList[i] + "\n";
        }
        logfile.close();
    }
}

void video::SaveGraphics(string path){
	SDL_Surface * sc = SDL_CreateRGBSurface(SDL_SWSURFACE, 512, 512, 24, 0x0000FF, 0x00FF00, 0xFF0000, 0);
	if(sc){
		int i = 0;
		SDL_LockSurface(sc);
		for(int y = 0; y < 512; ++y){
		    for(int x = 0; x < 512; ++x){
				Uint8 *p = (Uint8 *)sc->pixels + y * sc->pitch + x * 3;
				for(int c = 0; c < 3; ++c){
					p[c] = (baseTextureCache[i] >> ((3 - c) * 8)) & 0x0000FF;
				}	
				i++;	
			}	
		}
		SDL_UnlockSurface(sc);
		SDL_SaveBMP(sc, (path + "base.bmp").c_str());
		SDL_FreeSurface(sc);
	}
	wxImage objimg = wxImage(wxString((path + "base.bmp").c_str(), wxConvUTF8));
	objimg.SaveFile(wxString((path + "base.png").c_str(), wxConvUTF8));
	remove((path + "base.bmp").c_str());

	//sc = SDL_CreateRGBSurface(SDL_SWSURFACE, 2048, 128, 24, 0x0000FF, 0x00FF00, 0xFF0000, 0);
	//if(sc){
	//	int i = 0;
	//	SDL_LockSurface(sc);
	//	for(int y = 128 - 1; y >= 0; --y){
	//	    for(int x = 0; x < 2048; ++x){
	//			Uint8 *p = (Uint8 *)sc->pixels + y * sc->pitch + x * 3;
	//			for(int c = 0; c < 3; ++c){
	//				p[c] = (spGraphics[i] >> ((3 - c) * 8)) & 0x0000FF;
	//			}	
	//			i++;	
	//		}	
	//	}
	//	SDL_UnlockSurface(sc);
	//	SDL_SaveBMP(sc, (path + "SP.bmp").c_str());
	//	SDL_FreeSurface(sc);
	//}
	//wxImage objimg2 = wxImage(wxString((path + "SP.bmp").c_str(), wxConvUTF8));
	//objimg2.SaveFile(wxString((path + "SP.png").c_str(), wxConvUTF8));
	//remove((path + "SP.bmp").c_str());
}

void video::SaveBuffers(string path){
	//save screen file log
	fstream logfile;
    
	logfile.open(path + "Buffer.dat", ios::out | ios::trunc);
	if (logfile.is_open()){
		for(unsigned int i = 0; i < spPatCount; i++){
			
			logfile << to_string((long double)spVBuffer[i * 12]) 
				+ ", " + to_string((long double)spVBuffer[i * 12 + 1]) 
				+ ", " + to_string((long double)spVBuffer[i * 12 + 2]) 
				+ "; " + to_string((long double)spVBuffer[i * 12 + 3]) 
				+ ", " + to_string((long double)spVBuffer[i * 12 + 4]) 
				+ ", " + to_string((long double)spVBuffer[i * 12 + 5]) 
				+ "; " + to_string((long double)spVBuffer[i * 12 + 6]) 
				+ ", " + to_string((long double)spVBuffer[i * 12 + 7]) 
				+ ", " + to_string((long double)spVBuffer[i * 12 + 8]) 
				+ "; " + to_string((long double)spVBuffer[i * 12 + 9]) 
				+ ", " + to_string((long double)spVBuffer[i * 12 + 10]) 
				+ ", " + to_string((long double)spVBuffer[i * 12 + 11])
				+ "; " + to_string((long double)spCBuffer[i * 8])
				+ ", " + to_string((long double)spCBuffer[i * 8 + 1])
				+ ", " + to_string((long double)spCBuffer[i * 8 + 2])
				+ ", " + to_string((long double)spCBuffer[i * 8 + 3])
				+ ", " + to_string((long double)spCBuffer[i * 8 + 4])
				+ ", " + to_string((long double)spCBuffer[i * 8 + 5])
				+ ", " + to_string((long double)spCBuffer[i * 8 + 6])
				+ ", " + to_string((long double)spCBuffer[i * 8 + 7]) + "\n";
		}
		logfile.close();
	}
}

void video::saveBG(string path){
	//save screen file log
	fstream logfile;
	char tps[64];
    
	logfile.open(path + "Bg.dat", ios::out | ios::trunc);
	if (logfile.is_open()){
		for(int j = 0; j < DISPLAY_HEIGHT / 8; j++){
			logfile << "Line " + to_string((long double)j) 
				+ ", x=" + to_string((long double)BgRender[j][33]) 
				+ ", y=" + to_string((long double)BgRender[j][34]) + "\n    ";
			for(int i = 0; i < 33; i++){
				sprintf(tps, "%02X;", BgRender[j][i]);
				logfile << tps; 
			}
			logfile << "\n";
		}
		logfile.close();
	}
}

void video::OptimizePackEdit(){
    bool tHasWork = true;
    bool tileFound;
    int tScreenIndex = 0;
    int tTileIndex;
    bool patternMatch;
	bitmapF tTile;
	bitmapF tTile2;
    
    while(tHasWork){
        tHasWork = false;
        //for each screen shot
        tileFound = true;
        for (unsigned int j = 0; j < etiledata.size(); j++) {
            for (unsigned int k = 0; k < etiledata[j].bitmapP.size(); k++) {
				tTile = etiledata[j].bitmapP[k];
                if (tTile.bitmapID == tScreenIndex){
                    //go through each unique tiles and look for them in other screen shots
                    tileFound = false;

                    if (allEditData[etiledata[j].patternAddress] != BAD_ADDRESS){
						if(etiledata[j].patternAddress == 13890){
							tileFound = false;
						}
                        int aj = allEditData[etiledata[j].patternAddress];
                        for (unsigned int ak = 0; ak < allEtiledata[aj].bitmapP.size(); ak++) {
							tTile2 = allEtiledata[aj].bitmapP[ak];
                            if (tTile2.bitmapID != tScreenIndex) {
                                if (tTile2.colors.colorValues == tTile.colors.colorValues){
                                    if(romDat->chrPageCount > 0){
                                        patternMatch = true;
                                    }
                                    else{
                                        patternMatch = (tTile2.rawDat.pixStrip1 == tTile.rawDat.pixStrip1
                                                        && tTile2.rawDat.pixStrip2 == tTile.rawDat.pixStrip2
                                                        && tTile2.rawDat.pixStrip3 == tTile.rawDat.pixStrip3
                                                        && tTile2.rawDat.pixStrip4 == tTile.rawDat.pixStrip4);
                                    }
                                    if(patternMatch){
                                        tileFound = true;
                                    }
                                }
                                if (tileFound) break;
                            }
                        }
                    }
                    //has one unique tile which can't be found in other screenshots, so we must keep this shot
                    if (!tileFound) break;
                }
            }
            //has one unique tile which can't be found in other screenshots, so we must keep this shot
            if (!tileFound) break;
        }
        if (tileFound){
            //all tiles are found in other shots, we can remove this shot
            //first transfer all unique to other shots
            for (unsigned int j = 0; j < etiledata.size(); j++) {
                for (unsigned int k = 0; k < etiledata[j].bitmapP.size(); k++) {
					tTile = etiledata[j].bitmapP[k];
                    if (tTile.bitmapID == tScreenIndex){
                        //go through each unique tiles and look for them in other screen shots
                        tileFound = false;
                        if (allEditData[etiledata[j].patternAddress] != BAD_ADDRESS){
							if(etiledata[j].patternAddress == 13890){
								tileFound = false;
							}
                            int aj = allEditData[etiledata[j].patternAddress];
                            for (unsigned int ak = 0; ak < allEtiledata[aj].bitmapP.size(); ak++) {
								tTile2 = allEtiledata[aj].bitmapP[ak];
                                if (tTile2.bitmapID != tScreenIndex) {
                                    if (tTile2.colors.colorValues == tTile.colors.colorValues){
                                        if(romDat->chrPageCount > 0){
                                            patternMatch = true;
                                        }
                                        else{
                                            patternMatch = (tTile2.rawDat.pixStrip1 == tTile.rawDat.pixStrip1
                                                            && tTile2.rawDat.pixStrip2 == tTile.rawDat.pixStrip2
                                                            && tTile2.rawDat.pixStrip3 == tTile.rawDat.pixStrip3
                                                            && tTile2.rawDat.pixStrip4 == tTile.rawDat.pixStrip4);
                                        }
                                        if(patternMatch){
                                            tileFound = true;
                                            //copy it to unique tiles
                                            etiledata[j].bitmapP.push_back(tTile2);
                                        }
                                    }
                                    if (tileFound) break;
                                }
                            }
                        }
                    }
                }
            }

            
            //then remove all tiles from this shot
           for (unsigned int j = 0; j < etiledata.size(); j++) {
	           tTileIndex = 0;
                while (tTileIndex < etiledata[j].bitmapP.size()) {
                    if (etiledata[j].bitmapP[tTileIndex].bitmapID == tScreenIndex){
                        etiledata[j].bitmapP.erase(etiledata[j].bitmapP.begin() + tTileIndex);
                    }
                    else{
                        tTileIndex++;
                    }
                }
            }
            
           for (unsigned int j = 0; j < allEtiledata.size(); ++j) {
	           tTileIndex = 0;
                while (tTileIndex < allEtiledata[j].bitmapP.size()) {
                    if (allEtiledata[j].bitmapP[tTileIndex].bitmapID == tScreenIndex){
                        allEtiledata[j].bitmapP.erase(allEtiledata[j].bitmapP.begin() + tTileIndex);
                    }
                    else{
                        ++tTileIndex;
                    }
                }
            }

		    //remove the shot
            screenFileNameList.erase(screenFileNameList.begin() + tScreenIndex);

			//adjust bmp id for all other tiles
            for (unsigned int j = 0; j < etiledata.size(); j++) {
                for (unsigned int k = 0; k < etiledata[j].bitmapP.size(); k++) {
                    if (etiledata[j].bitmapP[k].bitmapID > tScreenIndex){
						etiledata[j].bitmapP[k].bitmapID--;
					}
				}
			}
            for (unsigned int j = 0; j < allEtiledata.size(); j++) {
                for (unsigned int k = 0; k < allEtiledata[j].bitmapP.size(); k++) {
                    if (allEtiledata[j].bitmapP[k].bitmapID > tScreenIndex){
						allEtiledata[j].bitmapP[k].bitmapID--;
					}
				}
			}
        }
        else{
            tScreenIndex++;
        }
		tHasWork = (tScreenIndex < screenFileNameList.size());
    }
}


void video::RewritePackEdit(){
    //first rewrite the screen list
    SavePackEditScreenList();
    
	string path = getEditPackPath();
    
	_mkdir(path.c_str());
	DWORD ftyp = GetFileAttributesA(path.c_str());
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY){
		string filename;
		//save screen file log
		fstream logfile;
		//over write each screen
		for(int i = 0; i <  screenFileNameList.size(); i++){
			filename = path + screenFileNameList[i] + ".dat";
			logfile.open(filename, ios::out | ios::trunc);
			if (logfile.is_open()){
				for (unsigned int j = 0; j < etiledata.size(); j++) {
					for (unsigned int k = 0; k < etiledata[j].bitmapP.size(); k++) {
						if (etiledata[j].bitmapP[k].bitmapID == i){

							logfile << (etiledata[j].bitmapP[k].isBg ? "Y" : "N") + string(", ")
								+ to_string((long double)etiledata[j].patternAddress) 
								+ ", " + to_string((long double)etiledata[j].bitmapP[k].colors.color1) 
								+ ", " + to_string((long double)etiledata[j].bitmapP[k].colors.color2) 
								+ ", " + to_string((long double)etiledata[j].bitmapP[k].colors.color3) 
								+ ", " + to_string((long double)etiledata[j].bitmapP[k].x) 
								+ ", " + to_string((long double)etiledata[j].bitmapP[k].y);
							if(romDat->chrPageCount == 0){
								for(int i = 0; i < 16; i++){
									logfile << ", " + to_string((long double)(*((Uint8*)(&(etiledata[j].bitmapP[k].rawDat)) + i)));
								}
							}
							logfile << "\n";
						}
					}
				}
				logfile.close();
			}
		}
	}
}

void video::ReadPalette(string path){
    fstream palettefile;
    char rawPalette[192];
    palettefile.open(path, ios::in | ios::binary);
    if (palettefile.is_open()){
        palettefile.read(rawPalette, 192);
        palettefile.close();
        for(int i = 0; i < 64; i++){
            colourList[i] = ((rawPalette[i * 3] << 24) & 0xFF000000) | ((rawPalette[i * 3 + 1] << 16) & 0x00FF0000) | ((rawPalette[i * 3 + 2] << 8) & 0x0000FF00) | 0xFF;
        }
    }
}

/*
Note:
packSize = CHR ROM or PRG ROM size
HD images: info in bmpInfos and pixel data in rawBits

packData[ROM address] stores the index of this address in array tdata
tdata is an array of TileData
TileData has an array of bitmapF and the default
bitmapF has an index of HD image, x and y coordinate in that image, the brightness and the palette


*/


/*
meta sprite check
If a sprite tile is unmatched then
	check that it matches any sprite in any meta sprite
	if has meta sprite then
		check for the origin sprite
		if origin sprite matches then
			use origin sprite to match all others 
			if all matches then
				udpate match result to sprites
			endif
		end if
	end if
end if
*/