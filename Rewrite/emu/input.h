#ifndef INPUT_H
#define INPUT_H

#include "../classList.h"
#include <emuPart.h>

#define KEY_IDX_CNT 38

#define KEY_IDX_P1_UP    	0
#define KEY_IDX_P1_DOWN  	1
#define KEY_IDX_P1_LEFT  	2
#define KEY_IDX_P1_RIGHT 	3
#define KEY_IDX_P1_SELECT	4
#define KEY_IDX_P1_START 	5
#define KEY_IDX_P1_A	    6
#define KEY_IDX_P1_B    	7

#define KEY_IDX_P2_UP    	8
#define KEY_IDX_P2_DOWN  	9
#define KEY_IDX_P2_LEFT  	10
#define KEY_IDX_P2_RIGHT 	11
#define KEY_IDX_P2_SELECT	12
#define KEY_IDX_P2_START 	13
#define KEY_IDX_P2_A	    14
#define KEY_IDX_P2_B    	15

#define KEY_IDX_F1_PAUSE                16
#define KEY_IDX_F1_ADVANCE_FRAME        17
#define KEY_IDX_F1_CAPTURE_SCREEN       18
#define KEY_IDX_F1_TOOGLE_CONT_SCR_CAP  19
#define KEY_IDX_F1_RESET                20

#define KEY_IDX_F2_SAVE_STATE       21
#define KEY_IDX_F2_LOAD_STATE       22
#define KEY_IDX_F2_LOAD_LAST_STATE  23
#define KEY_IDX_F2_ROTATE_STATE     24

#define KEY_IDX_F3_SLOT1    25
#define KEY_IDX_F3_SLOT2    26
#define KEY_IDX_F3_SLOT3    27
#define KEY_IDX_F3_SLOT4    28
#define KEY_IDX_F3_SLOT5    29
#define KEY_IDX_F3_SLOT6    30
#define KEY_IDX_F3_SLOT7    31
#define KEY_IDX_F3_SLOT8    32
#define KEY_IDX_F3_SLOT9    33
#define KEY_IDX_F3_SLOT10   34

#define KEY_IDX_F4_HD_CAP_FRAME         35
#define KEY_IDX_F4_TOOGLE_AUTO_HD_CAP   36
#define KEY_IDX_F4_TOOGLE_IGNORE_EDGE   37

#define KEY_IDX_F0_STOP 255

#define KEY_MAP_DIR_AXIS_POSITIVE  0
#define KEY_MAP_DIR_AXIS_NEGATIVE  1
#define KEY_MAP_MIN_AXIS_POSITIVE   10000
#define KEY_MAP_MIN_AXIS_NEGATIVE   -10000

struct keyMap{
    Uint32 type;
    SDL_JoystickID jID;
    union{
        int partID;
        SDL_Keycode keyCode;
    };
    Uint8 direction;
};

class input : public emuPart
{
    public:
        vector<SDL_Joystick*> joysticks;
        keyMap keyMaps[KEY_IDX_CNT];

        input();
        virtual ~input();
        string partName();
        void saveConfigLines(fstream* fs);
        void saveGameConfigLines(fstream* fs);
        void loadConfigVal(const string& hdr, const string& value);
        void initGameConfig();

        void startGame();
        void endGame();

        string inputNameForKeyIdx(int keyIdx);
        string inputName(keyMap km);
        string inputMapToConfigStr(keyMap km);
        string joystickGUIDStrFromID(SDL_JoystickID id);
        SDL_JoystickID joystickIDFromGUIDStr(const string& guidStr);
        keyMap inputConfigStrToMap(const string& value);
        void getKeyMapInput(Uint8 keyIdx);
        void handleUserInput();
    protected:

    private:
        void changeKeyMapToKeyboard(Uint8 keyIdx, SDL_Keycode keyCode);

};

#endif // INPUT_H
