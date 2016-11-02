#ifndef CPU_H
#define CPU_H

#include <corePart.h>


class cpu : public corePart
{
    public:
        cpu();
        virtual ~cpu();

        void reset();
        void saveState(fstream* statefile);
        void loadState(fstream* statefile);

    protected:

    private:
};

#endif // CPU_H
