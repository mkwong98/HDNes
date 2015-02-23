#include "StdAfx.h"
#include "sysState.h"



void fill_audio(void *data,Uint8 *stream,int len)
{
	Uint16 *buff;
	int i;
	int length;
	buff = (Uint16*)stream;

	double stepPerSample[5];
	Uint8 vol[5];
	Uint16 result[5];

	////sq1
	if(apuCore->lc[CHANNEL_SQUARE1].enabled && (apuCore->lc[CHANNEL_SQUARE1].currentVal > 0) && apuCore->channelPeriod[CHANNEL_SQUARE1] >= 8 && apuCore->sq1Sweep.targetPeriod <= 0x07FF){
		vol[CHANNEL_SQUARE1] = (apuCore->sq1Env.disableDecay? apuCore->sq1Env.constVol:apuCore->sq1Env.counter);
		//2 cpu clocks per apu clock, PERIOD + 1 apu clocks per sequence step
		stepPerSample[CHANNEL_SQUARE1] = mixer->clockPerSample / (double)((apuCore->channelPeriod[CHANNEL_SQUARE1] + 1) * 2);
	}
	else{
		vol[CHANNEL_SQUARE1] = 0;
	}

	//sq2
	if(apuCore->lc[CHANNEL_SQUARE2].enabled && (apuCore->lc[CHANNEL_SQUARE2].currentVal > 0) && apuCore->channelPeriod[CHANNEL_SQUARE2] >= 8 && apuCore->sq2Sweep.targetPeriod <= 0x07FF){
		vol[CHANNEL_SQUARE2] = (apuCore->sq2Env.disableDecay? apuCore->sq2Env.constVol:apuCore->sq2Env.counter);
		stepPerSample[CHANNEL_SQUARE2] = mixer->clockPerSample / (double)((apuCore->channelPeriod[CHANNEL_SQUARE2] + 1) * 2);
	}
	else{
		vol[CHANNEL_SQUARE2] = 0;
	}

	//tri
	if(apuCore->lc[CHANNEL_TRIANGLE].enabled && (apuCore->lc[CHANNEL_TRIANGLE].currentVal > 0) && apuCore->linearCounter.currentVal > 0 && apuCore->channelPeriod[CHANNEL_TRIANGLE] > 1){
		vol[CHANNEL_TRIANGLE] = 1;
		stepPerSample[CHANNEL_TRIANGLE] = mixer->clockPerSample / ((double)(apuCore->channelPeriod[CHANNEL_TRIANGLE] + 1));
	}
	else{
		vol[CHANNEL_TRIANGLE] = 0;
	}

	//noise
	if(apuCore->lc[CHANNEL_NOISE].enabled && (apuCore->lc[CHANNEL_NOISE].currentVal > 0)){
		vol[CHANNEL_NOISE] = (apuCore->noiseEnv.disableDecay? apuCore->noiseEnv.constVol:apuCore->noiseEnv.counter);
		stepPerSample[CHANNEL_NOISE] = mixer->clockPerSample / (double)((apuCore->channelPeriod[CHANNEL_NOISE] + 1) * 2);
	}
	else{
		vol[CHANNEL_NOISE] = 0;
	}


	for(i = 0; i < 4; ++i){
		if(vol[i] == 0){
			mixer->step[i] = 0.0;
			mixer->lastFreq[i] = stepPerSample[i];
		}
	}

	buff = (Uint16*)stream;
	//2 bytes to 1 16 bits sample
	length = len / 2;
	for(i = 0; i < length; i += 2){
		if(vol[CHANNEL_SQUARE1] > 0){
			result[CHANNEL_SQUARE1] = (apuCore->dutyCycle[apuCore->sq1Duty][(short)(mixer->step[CHANNEL_SQUARE1])] ? vol[CHANNEL_SQUARE1] : 0);
			mixer->step[CHANNEL_SQUARE1] += stepPerSample[CHANNEL_SQUARE1];
			while(mixer->step[CHANNEL_SQUARE1] >= 8.0){
				mixer->step[CHANNEL_SQUARE1] -= 8.0;
			}
		}
		else{
			result[CHANNEL_SQUARE1] = 0;
		}

		if(vol[CHANNEL_SQUARE2] > 0){
			result[CHANNEL_SQUARE2] = (apuCore->dutyCycle[apuCore->sq2Duty][(short)(mixer->step[CHANNEL_SQUARE2])] ?  vol[CHANNEL_SQUARE2] : 0);
			mixer->step[CHANNEL_SQUARE2] += stepPerSample[CHANNEL_SQUARE2];
			while(mixer->step[CHANNEL_SQUARE2] >= 8.0){
				mixer->step[CHANNEL_SQUARE2] -= 8.0;
			}
		}
		else{
			result[CHANNEL_SQUARE2] = 0;
		}

		if(vol[CHANNEL_TRIANGLE] > 0){
			result[CHANNEL_TRIANGLE] = apuCore->triCycle[(short)(mixer->step[CHANNEL_TRIANGLE])];
			mixer->step[CHANNEL_TRIANGLE] += stepPerSample[CHANNEL_TRIANGLE];
			while(mixer->step[CHANNEL_TRIANGLE] >= 32.0){
				mixer->step[CHANNEL_TRIANGLE] -= 32.0;
			}
		}
		else{
			result[CHANNEL_TRIANGLE] = 0;
		}

		if(vol[CHANNEL_NOISE] > 0){
			result[CHANNEL_NOISE] = ((apuCore->shiftReg & 0x0001) == 0x000? vol[CHANNEL_NOISE]:0);
			mixer->step[CHANNEL_NOISE] += stepPerSample[CHANNEL_NOISE];
			while(mixer->step[CHANNEL_NOISE] >= 1.0){
				apuCore->shiftNoiseReg();
				mixer->step[CHANNEL_NOISE] -= 1.0;
			}
		}
		else{
			result[CHANNEL_NOISE] = 0;
		}

		//always output counter value
		result[CHANNEL_DMC] = apuCore->apuBuffer[CHANNEL_DMC][apuCore->apuBufferCounter];

		if(apuCore->apuBufferFilled > 1){
			++(apuCore->apuBufferCounter);
			--(apuCore->apuBufferFilled);
			if(apuCore->apuBufferCounter >= APU_BUFFER_SIZE){
				apuCore->apuBufferCounter -= APU_BUFFER_SIZE;
			}
		}


		buff[i] = 492 * (result[CHANNEL_SQUARE1] + result[CHANNEL_SQUARE2]) + 557 * result[CHANNEL_TRIANGLE] + 323 * result[CHANNEL_NOISE] + 219 * result[CHANNEL_DMC];
		if(buff[i] > 32767){
			buff[i] = 32767;
		}
		buff[i + 1] = buff[i];
	}


}


void setReadyResumeLastMusic(int channel){
	mixer->readyResumeLastMusic = true;
}

void audio::init(){
	Mix_Init(MIX_INIT_OGG | MIX_INIT_MP3);
	Mix_OpenAudio(SAMPLE_RATE, AUDIO_U16SYS, 2, AUDIO_BUFFER_SIZE);

    clockPerSample = 1789773.0 / (double)SAMPLE_RATE;
	for(int i = 0; i < 256; ++i){
		apuCore->apuAccAR[i] = ((float)i) * 2.0 / clockPerSample; 
	}
    for(int i = 0; i < 5; ++i){
    	step[i] = 0;
		lastFreq[i] = 0;
    }
	Mix_HookMusic(fill_audio, NULL);
	playingMP3 = -1;
    playingChannel = -1;
	readyResumeLastMusic = false;
	ReadAudioPack();

	string filename;
	music.clear();
	for(unsigned int i = 0; i < mp3List.size(); ++i){
		filename = getHDPackPath() + string("\\") + mp3List[i];
		music.push_back(Mix_LoadWAV(filename.c_str()));
	}
}

audio::audio(void)
{
	usePack = true;
	playingMP3 = -1;
    playingChannel = -1;
	for(unsigned int i = 0; i < music.size(); ++i){
		Mix_FreeChunk(music[i]);
	}
	music.clear();
}


audio::~audio(void)
{
	if(playingMP3 >= 0){
		Mix_HaltChannel(playingChannel);
	}
	for(unsigned int i = 0; i < music.size(); ++i){
		Mix_FreeChunk(music[i]);
	}
	playingMP3 = -1;
	Mix_HaltMusic();
    Mix_CloseAudio();
	Mix_Quit();
}

void audio::ReadAudioPack(){
	string path = getHDPackPath();
	DWORD ftyp = GetFileAttributesA(path.c_str());
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY){

		//read the file
		fstream inifile;
		string line;

		inifile.open(path + "\\audio.txt", ios::in);
		if (inifile.is_open()){
			mp3List.clear();
			musicList.clear();
			while ( inifile.good() ){
				std::getline(inifile, line);
				if(line.substr(0, 5) == "<mp3>"){
                    //read a mp3 file
					string mp3Name = line.substr(5, string::npos);
					mp3List.push_back(mp3Name);
				}
                else if(line.substr(0, 7) == "<music>"){
                    vector<string> lineTokens;

                    split(line.substr(7, string::npos), ',', lineTokens);
                    if (lineTokens.size() >= 8) {
                        musicPiece b;
						b.priority = stoi(lineTokens[0]);
						b.ramAddress = stoi(lineTokens[1], nullptr, 16);
						b.hasCheck = (lineTokens[2] == "Y");
						b.checkValue = stoi(lineTokens[3], nullptr, 16);
						b.hasReplace = (lineTokens[4] == "Y");
						b.replaceValue = stoi(lineTokens[5], nullptr, 16);
						b.playType = stoi(lineTokens[6]);
						b.mp3Idx = stoi(lineTokens[7]);

						if(lineTokens.size() >= 9){
							b.conditions = lineTokens[8];
						}
						if(lineTokens.size() >= 10){
							b.gotoNext = (lineTokens[9] == "Y");
						}
						else{
							b.gotoNext = false;
						}

						compileCondition(b);
						musicList.push_back(b);
					}
                }
			}
			inifile.close();
		}
	}
}

void audio::SaveAudioPack(){
	//get directory and check exists
    string path = getHDPackPath();
	_mkdir(path.c_str());
	DWORD ftyp = GetFileAttributesA(path.c_str());
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY){
		string filename;
 		fstream logfile;
		char tmpStr[20];

		filename = path + "\\audio.txt";
		logfile.open(filename, ios::out | ios::trunc);
		if (logfile.is_open()){
			for(unsigned int i = 0; i < mp3List.size(); ++i){
				logfile << "<mp3>" + mp3List[i] + "\n";
			}

			for(unsigned int i = 0; i < musicList.size(); ++i){
				musicPiece b = musicList[i];
				logfile << "<music>" + to_string((long double)b.priority) + "," ;
				sprintf_s(tmpStr,"%x",b.ramAddress);
				logfile << tmpStr;
				logfile << (b.hasCheck? ",Y,": ",N,");
				sprintf_s(tmpStr,"%x",b.checkValue);
				logfile << tmpStr;
				logfile << (b.hasReplace? ",Y,": ",N,");
				sprintf_s(tmpStr,"%x",b.replaceValue);
				logfile << tmpStr;
				logfile << "," + to_string((long double)b.playType) + "," 
					+ to_string((long double)b.mp3Idx) + ",";
				logfile << b.conditions;
				logfile << (b.gotoNext ? ",Y,": ",N,");
				logfile << "\n";
			}
			logfile.close();
		}
	}
}

void audio::CleanAudioPack(){
	for(unsigned int i = 0; i < music.size(); ++i){
		Mix_FreeChunk(music[i]);
	}
	music.clear();
	mp3List.clear();
	musicList.clear();
}

void audio::resumeLastMusic(){
	if(readyResumeLastMusic && playingChannel != -1){
		Mix_Resume(playingChannel);
	} 
}

Uint8 audio::handleRAMWrite(Uint16 address, Uint8 data){
	musicPiece b;
	if(!usePack) return data;
	for(unsigned int i = 0; i < musicList.size(); ++i){
		b = musicList[i];
		if(b.ramAddress == address){
			if((b.hasCheck && b.checkValue == data) || !b.hasCheck){
				bool conSat = true;
				Uint16 vleft;
				Uint16 vright;
				for(unsigned int j = 0; j < b.conlist.size(); ++j){
					switch (b.conlist[j].opTypeL){
                    case OP_TYPE_ADDRESS:
						vleft = memDat->cpuRAM[b.conlist[j].operandL & 0x07FF];
                        break;
                    case OP_TYPE_VALUE:
                        vleft = b.conlist[j].operandL;
                        break;
                    case OP_TYPE_WRITE:
                        vleft = data;
                        break;
                    default:
                        vleft = 0;
                        break;
                    }

					switch (b.conlist[j].opTypeR){
                    case OP_TYPE_ADDRESS:
                        vright = memDat->cpuRAM[b.conlist[j].operandR & 0x07FF];
                        break;
                    case OP_TYPE_VALUE:
                        vright = b.conlist[j].operandR;
                        break;
                    case OP_TYPE_WRITE:
                        vright = data;
                        break;
                    default:
                        vright = 0;
                        break;
                    }

					switch(b.conlist[j].operatorC){
					case OP_EQUALS_TO:
						conSat = (conSat && (vleft == vright));
						break;
					case OP_GREATER_THAN:
						conSat = (conSat && (vleft >= vright));
						break;
					case OP_LESS_THAN:
						conSat = (conSat && (vleft <= vright));
						break;
					case OP_NOT_EQUAL:
						conSat = (conSat && (vleft != vright));
						break;
					}
				}
				if(conSat && (playingMP3 != b.mp3Idx)){
					if(playingMP3 >= 0 && b.mp3Idx != -2){
						if(b.playType == 0 || b.playType ==1){
							Mix_HaltChannel(playingChannel);
		                    playingChannel = -1;
							playingMP3 = b.mp3Idx;
						}
						else if(b.playType == 2){
							Mix_Pause(playingChannel);
						}
					}
					if(b.mp3Idx >= 0){
						string filename;
						filename = getHDPackPath() + string("\\") + mp3List[b.mp3Idx];
						if(b.playType == 0 || b.playType ==1){
							playingChannel = Mix_PlayChannel(-1, music[b.mp3Idx], (b.playType == 0 ? -1 : 0));
							playingMP3 = b.mp3Idx;
						}
						else {
							//play on another channel
							int difChannel = Mix_PlayChannel(-1, music[b.mp3Idx], 0);
							if(b.playType == 2){
								//resume when finish
								Mix_ChannelFinished(setReadyResumeLastMusic);
							}
						}
					}
				}
				if(!b.gotoNext){
					return (b.hasReplace ? b.replaceValue : data);
				}
			}
		}
	}
	return data;
}

void audio::readConfig(string value){
    vector<string> lineTokens;
    
    split(value, ',', lineTokens);
    if (lineTokens[0].compare("usepack") == 0) {
        usePack = (lineTokens[1].compare("Y") == 0);
    }
}

void audio::saveConfig(fstream* inifile){
    (*inifile) << "audio:usepack," +  string(usePack ? "Y":"N") + "\n";
}

void audio::compileCondition(musicPiece& m){
    vector<string> lineTokens;
	size_t found;
	string leftToken;
	string rightToken;
	string cOp;
	string tmpStr;
	musicCondition c;

	m.conlist.clear();
    split(removeSpace(m.conditions), ';', lineTokens);
	for(unsigned int i = 0; i < lineTokens.size(); ++i){
		found = lineTokens[i].find_last_of("=");
		if(found != string::npos && found > 3){
			rightToken = lineTokens[i].substr(found+1);
			leftToken = lineTokens[i].substr(0, found - 1);
			cOp = lineTokens[i].substr(found - 1, 1);

			if(cOp.compare("=") == 0) c.operatorC = OP_EQUALS_TO;
			if(cOp.compare(">") == 0) c.operatorC = OP_GREATER_THAN;
			if(cOp.compare("<") == 0) c.operatorC = OP_LESS_THAN;
			if(cOp.compare("!") == 0) c.operatorC = OP_NOT_EQUAL;

			tmpStr = rightToken.substr(0, 1);
			tmpStr = rightToken.substr(0, 1);
            if ((tmpStr.compare("A") == 0)){
                c.opTypeR = OP_TYPE_ADDRESS;
                c.operandR = stoi(rightToken.substr(1), nullptr, 16);
            }
            else if ((tmpStr.compare("$") == 0)){
                c.opTypeR = OP_TYPE_VALUE;
                c.operandR = stoi(rightToken.substr(1), nullptr, 16);
            }
            else if ((tmpStr.compare("W") == 0)){
                c.opTypeR = OP_TYPE_WRITE;
                c.operandR = 0;
            }
            else{
                c.opTypeR = OP_TYPE_UNDEFINE;
                c.operandR = 0;
            }

			tmpStr = leftToken.substr(0, 1);
            if ((tmpStr.compare("A") == 0)){
                c.opTypeL = OP_TYPE_ADDRESS;
                c.operandL = stoi(leftToken.substr(1), nullptr, 16);
            }
            else if ((tmpStr.compare("$") == 0)){
                c.opTypeL = OP_TYPE_VALUE;
                c.operandL = stoi(leftToken.substr(1), nullptr, 16);
            }
            else if ((tmpStr.compare("W") == 0)){
                c.opTypeL = OP_TYPE_WRITE;
                c.operandL = 0;
            }
            else{
                c.opTypeL = OP_TYPE_UNDEFINE;
                c.operandL = 0;
            }

			m.conlist.push_back(c);
		}
	}
}
