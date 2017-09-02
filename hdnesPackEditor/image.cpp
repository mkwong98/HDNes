#include "image.h"
#include "coreData.h"

image::image()
{
    fileName = "";
}

image::~image()
{
    if(fileName != "") delete(imageData);
}

void image::load(string path){
    fileName = path;
    imageData = new wxImage((coreData::cData->packPath + "\\" + path).c_str());
}
