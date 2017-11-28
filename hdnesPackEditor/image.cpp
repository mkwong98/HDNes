#include "image.h"
#include "coreData.h"

image::image()
{
    fileName = "";
}

image::~image()
{
}

void image::load(string path){
    fileName = path;
    imageData.LoadFile(wxString((coreData::cData->packPath + "\\" + path).c_str()));
}
