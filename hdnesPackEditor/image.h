#ifndef IMAGE_H
#define IMAGE_H

#include "common.h"

class image
{
    public:
        image();
        virtual ~image();

        string fileName;
        wxImage imageData;

        void load(string path);
        void reloadImg();

    protected:

    private:
};

#endif // IMAGE_H
