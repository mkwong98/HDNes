#include "StdAfx.h"
#include "batchMapImp.h"
#include "sysState.h"
#include <wx/rawbmp.h>
#include <Shlwapi.h>


batchMapImp::batchMapImp():batchMap(NULL){
	cboImage->Clear();
	for(unsigned int i = 0; i < vid->bmpInfos.size(); i++){
		cboImage->Append(wxString(vid->bmpInfos[i].filename.c_str(), wxConvUTF8));
	}
	cboNewImage->Clear();
	for(unsigned int i = 0; i < vid->bmpInfos.size(); i++){
		cboNewImage->Append(wxString(vid->bmpInfos[i].filename.c_str(), wxConvUTF8));
	}
    
    
	firstTileCache = NULL;
    paletteTileCache = NULL;
}

batchMapImp::~batchMapImp(){
	if(firstTileCache){
		free(firstTileCache);
	}
	if(paletteTileCache){
		free(paletteTileCache);
	}
}


void batchMapImp::loadImage( wxCommandEvent& event ) { 
	
	//load tiles
	lstFirstTile->Clear();
	lstLastTile->Clear();
	lstNewPalette->Clear();

	showSourceImg();

	bitmapE b;
	bitmapF c;
	string tiledisplay;
	vector<bitmapE> v;
	if(firstTileCache){
		free(firstTileCache);
	}
	
	for(unsigned int i = 0; i < vid->packSize; i++){
		if(vid->packData[i] != BAD_ADDRESS){
			for(unsigned int j = 0; j < vid->tdata[vid->packData[i]].bitmapP.size(); j++){
				//for each tile in the pack
				c = vid->tdata[vid->packData[i]].bitmapP[j];
				if(c.bitmapID == cboImage->GetSelection()){
					b.bitmapID = c.bitmapID;
					b.colors = c.colors;
					if(romDat->chrPageCount == 0){
						b.rawDat = c.rawDat;
					}
					b.patternAddress = vid->tdata[vid->packData[i]].patternAddress;
					b.x = c.x;
					b.y = c.y;
                    b.brightness = c.brightness;
					v.push_back(b);
				}
			}
		}
	}
	if(v.size() > 0){
		firstTileCache = (bitmapE*)malloc(v.size() * sizeof(bitmapE));
		for(unsigned int i = 0; i < v.size(); i++){
			firstTileCache[i] = v[i];
			tiledisplay = to_string((long double)(firstTileCache[i].patternAddress)) + "," + vid->GetPaletteString(firstTileCache[i].colors) + "," + to_string((long double)(firstTileCache[i].brightness * 100)) + "%";
			lstFirstTile->Append(wxString(tiledisplay.c_str(), wxConvUTF8), &firstTileCache[i]);
		}
	}
}

void batchMapImp::refreshImg(wxImage img, int poffsetx, int poffsety, int pdrawW, int pdrawH, 
							int poffsetx2, int poffsety2, int pdrawW2, int pdrawH2){
	int neww, newh;

	wxImage objimg;
	int offsetx;
	int offsety;
	int drawW;
	int drawH;


	if(img.GetWidth() / img.GetHeight() > pnlOldImg->GetSize().GetWidth() / pnlOldImg->GetSize().GetHeight()){
		neww = pnlOldImg->GetSize().GetWidth();
		newh = img.GetHeight() * pnlOldImg->GetSize().GetWidth() / img.GetWidth();
	}
	else{
		newh = pnlOldImg->GetSize().GetHeight();	
		neww = img.GetWidth() * pnlOldImg->GetSize().GetHeight() / img.GetHeight();
	}
	objimg = img.Scale(neww, newh);
	if(!objimg.HasAlpha()) objimg.InitAlpha(); 

	if(pdrawW > 0 && pdrawH > 0 ){
		offsetx = poffsetx * neww / img.GetWidth();
		offsety = poffsety * newh / img.GetHeight();
		drawW = pdrawW * neww / img.GetWidth();
		drawH = pdrawH * newh / img.GetHeight();
		if(offsety + drawH < objimg.GetHeight() && offsetx + drawW < objimg.GetWidth()){
			for(int i = offsetx; i < offsetx + drawW; i++){
				objimg.SetRGB(i, offsety + 1, 0, 0, 0);
				objimg.SetAlpha(i, offsety + 1, 255);
				if(offsety + 1 + drawH < objimg.GetHeight()){
					objimg.SetRGB(i, offsety + 1 + drawH, 0, 0, 0);
					objimg.SetAlpha(i, offsety + 1 + drawH, 255);
				}
			}
			for(int j = offsety; j < offsety + drawH; j++){
				objimg.SetRGB(offsetx + 1, j, 0, 0, 0);
				objimg.SetAlpha(offsetx + 1, j, 255);
				if(offsetx + 1 + drawW < objimg.GetWidth()){
					objimg.SetRGB(offsetx + 1 + drawW, j, 0, 0, 0);
					objimg.SetAlpha(offsetx + 1 + drawW, j, 255);
				}
			}
			for(int i = offsetx; i < offsetx + drawW; i++){
				objimg.SetRGB(i, offsety, 255, 255, 255);
				objimg.SetAlpha(i, offsety, 255);
				if(offsety + drawH < objimg.GetHeight()){
					objimg.SetRGB(i, offsety + drawH, 255, 255, 255);
					objimg.SetAlpha(i, offsety + drawH, 255);
				}
			}
			for(int j = offsety; j < offsety + drawH; j++){
				objimg.SetRGB(offsetx, j, 255, 255, 255);
				objimg.SetAlpha(offsetx, j, 255);
				if(offsetx + drawW< objimg.GetWidth()){
					objimg.SetRGB(offsetx + drawW, j, 255, 255, 255);
					objimg.SetAlpha(offsetx + drawW, j, 255);
				}
			}
		}
	}

	if(pdrawW2 > 0 && pdrawH2 > 0){
		offsetx = poffsetx2 * neww / img.GetWidth();
		offsety = poffsety2 * newh / img.GetHeight();
		drawW = pdrawW2 * neww / img.GetWidth();
		drawH = pdrawH2 * newh / img.GetHeight();

		if(offsety + drawH < objimg.GetHeight() && offsetx + drawW < objimg.GetWidth()){
			for(int i = offsetx; i < offsetx + drawW; i++){
				objimg.SetRGB(i, offsety + 1, 0, 0, 0);
				objimg.SetAlpha(i, offsety + 1, 255);
				if(offsety + 1 + drawH < objimg.GetHeight()){
					objimg.SetRGB(i, offsety + 1 + drawH, 0, 0, 0);
					objimg.SetAlpha(i, offsety + 1 + drawH, 255);
				}
			}
			for(int j = offsety; j < offsety + drawH; j++){
				objimg.SetRGB(offsetx + 1, j, 0, 0, 0);
				objimg.SetAlpha(offsetx + 1, j, 255);
				if(offsetx + 1 + drawW < objimg.GetWidth()){
					objimg.SetRGB(offsetx + 1 + drawW, j, 0, 0, 0);
					objimg.SetAlpha(offsetx + 1 + drawW, j, 255);
				}
			}
			for(int i = offsetx; i < offsetx + drawW; i++){
				objimg.SetRGB(i, offsety, 255, 255, 255);
				objimg.SetAlpha(i, offsety, 255);
				if(offsety + drawH < objimg.GetHeight()){
					objimg.SetRGB(i, offsety + drawH, 255, 255, 255);
					objimg.SetAlpha(i, offsety + drawH, 255);
				}
			}
			for(int j = offsety; j < offsety + drawH; j++){
				objimg.SetRGB(offsetx, j, 255, 255, 255);
				objimg.SetAlpha(offsetx, j, 255);
				if(offsetx + drawW< objimg.GetWidth()){
					objimg.SetRGB(offsetx + drawW, j, 255, 255, 255);
					objimg.SetAlpha(offsetx + drawW, j, 255);
				}
			}
		}
	}


	pnlOldImg->ClearBackground();
	wxClientDC* objDC = new wxClientDC(pnlOldImg);
	objDC->DrawBitmap(wxBitmap(objimg), 0, 0);
	delete objDC;

}

void batchMapImp::showSourceImg(){
	int ox1, oy1, ow1, oh1, ox2, oy2, ow2, oh2;

	if(cboImage->GetSelection() == wxNOT_FOUND) return;

	string filename = getHDPackPath() + "\\" + vid->bmpInfos[cboImage->GetSelection()].filename;
	wxImage objImageImg = wxImage(wxString(filename.c_str(), wxConvUTF8));

	bitmapE* b;
	ox1 = 0; oy1 = 0; ow1 = 0; oh1 = 0;
	ox2 = 0; oy2 = 0; ow2 = 0; oh2 = 0;
	if(lstFirstTile->GetSelection() != wxNOT_FOUND){
		b = (bitmapE*)lstFirstTile->GetClientData(lstFirstTile->GetSelection());
		ox1 = b->x;
		oy1 = b->y;
		ow1 = 8 * vid->packScale;
		oh1 = 8 * vid->packScale;
	}
	if(lstLastTile->GetSelection() != wxNOT_FOUND){
		b = (bitmapE*)lstLastTile->GetClientData(lstLastTile->GetSelection());
		ox2 = b->x;
		oy2 = b->y;
		ow2 = 8 * vid->packScale;
		oh2 = 8 * vid->packScale;
	}
	refreshImg(objImageImg, ox1, oy1, ow1, oh1, ox2, oy2, ow2, oh2);
}

	
void batchMapImp::firstTileSelected( wxCommandEvent& event ) { 
	lstLastTile->Clear();
	lstNewPalette->Clear();
	showSourceImg();

	bitmapE* b;
	bitmapE* b2;
	string tiledisplay;

	if(lstFirstTile->GetSelection() == wxNOT_FOUND) return;
	
	b = (bitmapE*)lstFirstTile->GetClientData(lstFirstTile->GetSelection());
	//get list of tiles with matching palette and add to last tile list
	for(int i = lstFirstTile->GetSelection(); i < lstFirstTile->GetCount(); i++){
		b2 = (bitmapE*)lstFirstTile->GetClientData(i);
		if(i > lstFirstTile->GetSelection() && b->colors.colorValues == b2->colors.colorValues){
			tiledisplay = to_string((long double)(b2->patternAddress));
			lstLastTile->Append(wxString(tiledisplay.c_str(), wxConvUTF8), b2);
		}
	}

	//add list of other palette
    bitmapE d;
    bitmapF c;
    vector<bitmapE> v;
    if(paletteTileCache){
        free(paletteTileCache);
    }
        
    if(vid->editData[b->patternAddress] != BAD_ADDRESS){
        for(unsigned int j = 0; j < vid->etiledata[vid->editData[b->patternAddress]].bitmapP.size(); j++){
            c = vid->etiledata[vid->editData[b->patternAddress]].bitmapP[j];
            d.bitmapID = c.bitmapID;
            d.colors = c.colors;
			if(romDat->chrPageCount == 0){
				d.rawDat = c.rawDat;
			}
            d.patternAddress = b->patternAddress;
            d.x = c.x;
            d.y = c.y;
            d.brightness = c.brightness;
            v.push_back(d);
        }
    }
    if(v.size() > 0){
        paletteTileCache = (bitmapE*)malloc(v.size() * sizeof(bitmapE));
        for(unsigned int i = 0; i < v.size(); i++){
            paletteTileCache[i] = v[i];
			tiledisplay = vid->GetPaletteString(paletteTileCache[i].colors);
            lstNewPalette->Append(wxString(tiledisplay.c_str(), wxConvUTF8), &paletteTileCache[i]);
        }
    }
}
	
void batchMapImp::lastTileSelected( wxCommandEvent& event ) { 
	if(cboImage->GetSelection() == wxNOT_FOUND) return;
	showSourceImg(); 
}

void batchMapImp::showNewPalette( wxCommandEvent& event ) {
	wxImage objimg;
	int offsetx;
	int offsety;
	int drawW;
	int drawH;
	
	if(lstNewPalette->GetSelection() == wxNOT_FOUND) return;

	bitmapE* b = (bitmapE*)lstNewPalette->GetClientData(lstNewPalette->GetSelection());
    
	if(b == NULL) return;

	string filename = getEditPackPath() + vid->screenFileNameList[b->bitmapID];
	objimg = wxImage(wxString((filename + ".png").c_str(), wxConvUTF8));
    
	//draw a box in the screenshot
	offsetx = b->x * objimg.GetWidth() / DISPLAY_WIDTH;
	offsety = b->y * objimg.GetHeight() / DISPLAY_HEIGHT;
	drawW = 8 * objimg.GetWidth() / DISPLAY_WIDTH;
	drawH = 8 * objimg.GetHeight() / DISPLAY_HEIGHT;
    
    refreshImg(objimg, offsetx, offsety, drawW, drawW, 0, 0, 0, 0);
}

	
void batchMapImp::showNewImage( wxCommandEvent& event ) { 
	loadNewImg();
}

void batchMapImp::loadNewImg(){
	wxClientDC* objDC;
	int neww, newh;
	wxImage img;
	wxImage objimg;
	int offsetx;
	int offsety;
	int drawW;
	int drawH;
	
	if(cboNewImage->GetSelection() == wxNOT_FOUND) return;

	string filename = getHDPackPath() + "\\" + vid->bmpInfos[cboNewImage->GetSelection()].filename;
	img = wxImage(wxString(filename.c_str(), wxConvUTF8));
	newImgW = img.GetWidth();
	newImgH = img.GetHeight();

	if(newImgW / newImgH > pnlNewImage->GetSize().GetWidth() / pnlNewImage->GetSize().GetHeight()){
		neww = pnlNewImage->GetSize().GetWidth();
		newh = newImgH * pnlNewImage->GetSize().GetWidth() / newImgW;
	}
	else{
		newh = pnlNewImage->GetSize().GetHeight();	
		neww = newImgW * pnlNewImage->GetSize().GetHeight() / newImgH;
	}
	objimg = img.Scale(neww, newh);
	if(!objimg.HasAlpha()) objimg.InitAlpha(); 


	if(string(txtMapX->GetValue().char_str()).compare("") != 0 
		&& string(txtMapY->GetValue().char_str()).compare("") != 0){
		offsetx = stoi(string(txtMapX->GetValue().char_str())) * neww / newImgW;
		offsety = stoi(string(txtMapY->GetValue().char_str())) * newh / newImgH;
		drawW = 8 * vid->packScale * neww / newImgW;
		drawH = 8 * vid->packScale * newh / newImgH;

		if(offsety + drawH < objimg.GetHeight() && offsetx + drawW < objimg.GetWidth()){
			for(int i = offsetx; i < offsetx + drawW; i++){
				objimg.SetRGB(i, offsety + 1, 0, 0, 0);
				objimg.SetAlpha(i, offsety + 1, 255);
				if(offsety + 1 + drawH < objimg.GetHeight()){
					objimg.SetRGB(i, offsety + 1 + drawH, 0, 0, 0);
					objimg.SetAlpha(i, offsety + 1 + drawH, 255);
				}
			}
			for(int j = offsety; j < offsety + drawH; j++){
				objimg.SetRGB(offsetx + 1, j, 0, 0, 0);
				objimg.SetAlpha(offsetx + 1, j, 255);
				if(offsetx + 1 + drawW < objimg.GetWidth()){
					objimg.SetRGB(offsetx + 1 + drawW, j, 0, 0, 0);
					objimg.SetAlpha(offsetx + 1 + drawW, j, 255);
				}
			}
			for(int i = offsetx; i < offsetx + drawW; i++){
				objimg.SetRGB(i, offsety, 255, 255, 255);
				objimg.SetAlpha(i, offsety, 255);
				if(offsety + drawH < objimg.GetHeight()){
					objimg.SetRGB(i, offsety + drawH, 255, 255, 255);
					objimg.SetAlpha(i, offsety + drawH, 255);
				}
			}
			for(int j = offsety; j < offsety + drawH; j++){
				objimg.SetRGB(offsetx, j, 255, 255, 255);
				objimg.SetAlpha(offsetx, j, 255);
				if(offsetx + drawW< objimg.GetWidth()){
					objimg.SetRGB(offsetx + drawW, j, 255, 255, 255);
					objimg.SetAlpha(offsetx + drawW, j, 255);
				}
			}
		}
	}


	pnlNewImage->ClearBackground();
	objDC = new wxClientDC(pnlNewImage);
	objDC->DrawBitmap(wxBitmap(objimg), 0, 0);
	delete objDC;
}

	
void batchMapImp::addImageToPack( wxFileDirPickerEvent& event ) { 
	string filename = string(m_filePicker2->GetPath().char_str());
	wxImage objImg;
	//load image for image size
	objImg = wxImage(wxString(filename.c_str(), wxConvUTF8));

	//create hd pack dir
	string packdir = getHDPackPath() + "\\";
    _mkdir(packdir.c_str());

	//get file name
	CHAR szPath[MAX_PATH];
	filename.copy(szPath, MAX_PATH, 0);
	szPath[filename.length()] = NULL;
	PathStripPathA(szPath);

	objImg.SaveFile(wxString((packdir + string(szPath)).c_str(), wxConvUTF8));

	vid->AddHiResImg(string(szPath));
	cboNewImage->Append(wxString(szPath, wxConvUTF8));
	cboNewImage->SetSelection(vid->bmpInfos.size() - 1);

	loadNewImg();
}
	
void batchMapImp::addMappings( wxCommandEvent& event ) { 

	if(string(txtMapX->GetValue().char_str()).compare("") != 0 
	&& string(txtMapY->GetValue().char_str()).compare("") != 0
	&& cboImage->GetSelection() != wxNOT_FOUND
	&& cboNewImage->GetSelection() != wxNOT_FOUND
	&& lstFirstTile->GetSelection() != wxNOT_FOUND
	&& lstLastTile->GetSelection() != wxNOT_FOUND
	&& lstNewPalette->GetSelection() != wxNOT_FOUND){

		bitmapF c;
		bitmapF f;
		bitmapF newMap;

		bitmapE* b = (bitmapE*)lstFirstTile->GetClientData(lstFirstTile->GetSelection());
		bitmapE* d = (bitmapE*)lstNewPalette->GetClientData(lstNewPalette->GetSelection());
		int newOffsetX = stoi(string(txtMapX->GetValue().char_str())) - b->x; 
		int newOffsetY = stoi(string(txtMapY->GetValue().char_str())) - b->y;
        GLfloat newBrightness = stof(string(txtBrightness->GetValue().char_str())) / 100;

		newMap.bitmapID = cboNewImage->GetSelection();
		newMap.colors = d->colors;
        newMap.brightness = newBrightness;

		int tileIDFrom = b->patternAddress;
		int tileIDTo = ((bitmapE*)lstLastTile->GetClientData(lstLastTile->GetSelection()))->patternAddress;

		for(int i = tileIDFrom; i <= tileIDTo; i++){
			//find current maping
			if(vid->packData[i] != BAD_ADDRESS){
				bool hasOldMapping = false;
				bool hasMatchSource = false;
				int oldMappingIdx;
				for(unsigned int j = 0; j < vid->tdata[vid->packData[i]].bitmapP.size(); j++){
					//for each tile within range
					c = vid->tdata[vid->packData[i]].bitmapP[j];
					if(romDat->chrPageCount == 0){
						newMap.rawDat = c.rawDat; 
					}
					//if palette matches the source
					if(c.colors.colorValues == b->colors.colorValues){
						hasMatchSource = true;
						f = c;
					}
					//if palette matches the destination
					if(c.colors.colorValues == d->colors.colorValues){
						hasOldMapping = true;
						oldMappingIdx = j;
					}
				}
				if(hasMatchSource){
					newMap.x = f.x + newOffsetX;
					newMap.y = f.y + newOffsetY;
                    if (newMap.x >= 0 && newMap.y >= 0) {
                        if(hasOldMapping){
                            //replace old
                            vid->tdata[vid->packData[i]].bitmapP[oldMappingIdx] = newMap;
                        }
                        else{
                            //add new
                            vid->tdata[vid->packData[i]].bitmapP.push_back(newMap);
                        }
                    }
				}

			}
		}
		this->EndModal(1);
	}
}
	
void batchMapImp::cancel( wxCommandEvent& event ) { 
	this->EndModal(0);
}
	
void batchMapImp::ImageTileSelected( wxMouseEvent& event ) { 
	int selectX;
	int selectY;
	float scale;

	if(newImgW / newImgH > pnlNewImage->GetSize().GetWidth() / pnlNewImage->GetSize().GetHeight()){
		scale = (float)newImgW / (float)pnlNewImage->GetSize().GetWidth();
	}
	else{
		scale = (float)newImgH / (float)pnlNewImage->GetSize().GetHeight();
	}

	selectX = event.GetPosition().x * scale;
	selectX = selectX - (selectX % (8 * vid->packScale));
	selectY = event.GetPosition().y * scale;
	selectY = selectY - (selectY % (8 * vid->packScale));

	if(selectX < newImgW && selectY < newImgH){
		txtMapX->SetValue(wxString(to_string((long double)(selectX)).c_str(), wxConvUTF8)); 
		txtMapY->SetValue(wxString(to_string((long double)(selectY)).c_str(), wxConvUTF8));
		loadNewImg();
	}
}
