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
    reloadImg();
}

void image::reloadImg(){
    imageData.LoadFile(wxString((coreData::cData->packPath + "\\" + fileName).c_str()));
    if(!imageData.HasAlpha()) imageData.InitAlpha();
}
