#ifndef GAMEPAD_H
#define GAMEPAD_H

#include <corePart.h>


class gamepad : public corePart
{
    public:
        gamepad();
        virtual ~gamepad();

        void reset();
        void saveState(fstream* statefile);
        void loadState(fstream* statefile);
        void init();
        void init2();

        Uint8 read4016();
        void write4016(Uint8 value);
        Uint8 read4017();
        void write4017(Uint8 value);

    protected:

    private:
};

#endif // GAMEPAD_H
