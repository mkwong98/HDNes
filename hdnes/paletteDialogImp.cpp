#include "StdAfx.h"
#include "sysState.h"
#include <wx/rawbmp.h>
#include <Shlwapi.h>
#include "paletteDialogImp.h"


paletteDialogImp::paletteDialogImp():paletteDialog(NULL){
	selectedX = 0;
	selectedY = 0;
	showSelectedCellColor();
}

paletteDialogImp::~paletteDialogImp(){
}

void paletteDialogImp::paletteCellSelected( wxMouseEvent& event ){
    //calculate which cell is clicked
	selectedX = event.GetPosition().x * 16.0f / (float)pnlPalette->GetSize().GetWidth();
	selectedY = event.GetPosition().y * 4.0f / (float)pnlPalette->GetSize().GetHeight();

	showSelectedCellColor();

	wxClientDC* objDC;
	objDC = new wxClientDC(pnlPalette);
	refreshPalette(objDC);
	delete objDC;

}

void paletteDialogImp::newColorSelected( wxColourPickerEvent& event ){
    //set the selected colour to the selected cell
	wxColour c = colorPicker->GetColour();
    vid->colourList[selectedY * 16 + selectedX] = (c.Red() << 24) | (c.Green() << 16) | (c.Blue() << 8) | 0xFF;
 
	wxClientDC* objDC;
	objDC = new wxClientDC(pnlPalette);
	refreshPalette(objDC);
	delete objDC;
}

void paletteDialogImp::paletteFileSelected( wxFileDirPickerEvent& event ){
    //read a colour set directly from a file
    string filename = string(event.GetPath().char_str());
    vid->ReadPalette(filename);

	wxClientDC* objDC;
	objDC = new wxClientDC(pnlPalette);
	refreshPalette(objDC);
	delete objDC;    
}

void paletteDialogImp::refreshPalette(wxDC* dc){
	wxImage* img;
	wxImage scaledImg;
	wxBitmap bmp;

	Uint16 offX;
	Uint16 offY;
	Uint16 boxWidth;
	Uint16 boxHeight;

    //paint the current colour set to an image
	img = new wxImage(16, 4, true);
	img->InitAlpha();
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 16; j++){
			img->SetAlpha(j, i, 255);
			img->SetRGB(j, i, (vid->colourList[i * 16 + j] & 0xFF000000) >> 24, (vid->colourList[i * 16 + j] & 0x00FF0000) >> 16, (vid->colourList[i * 16 + j] & 0x0000FF00) >> 8);
		}
	}
    //enlarge the image to the panel size and draw a box around the selected cell
	scaledImg = img->Scale(pnlPalette->GetSize().GetWidth(), pnlPalette->GetSize().GetHeight());
	offX = selectedX * pnlPalette->GetSize().GetWidth() / 16;
	offY = selectedY * pnlPalette->GetSize().GetHeight() / 4;
	boxWidth = pnlPalette->GetSize().GetWidth() / 16;
	boxHeight = pnlPalette->GetSize().GetHeight() / 4;

	for(int i = 0; i < boxHeight - 1; i++){
		scaledImg.SetAlpha(offX, offY + i, 255);
		scaledImg.SetRGB(offX, offY + i, 255, 255 , 255);

		scaledImg.SetAlpha(offX + 1, offY + i + 1, 255);
		scaledImg.SetRGB(offX + 1, offY + i + 1, 0, 0, 0);

		scaledImg.SetAlpha(offX + boxWidth - 2, offY + i, 255);
		scaledImg.SetRGB(offX + boxWidth - 2, offY + i, 255, 255 , 255);

		scaledImg.SetAlpha(offX + boxWidth - 1, offY + i + 1, 255);
		scaledImg.SetRGB(offX + boxWidth - 1, offY + i + 1, 0, 0, 0);

	}

	for(int i = 0; i < boxWidth - 1; i++){
		scaledImg.SetAlpha(offX + i, offY, 255);
		scaledImg.SetRGB(offX + i, offY, 255, 255 , 255);

		scaledImg.SetAlpha(offX + i + 1, offY + 1, 255);
		scaledImg.SetRGB(offX + i + 1, offY + 1, 0, 0, 0);

		scaledImg.SetAlpha(offX + i, offY + boxHeight - 2, 255);
		scaledImg.SetRGB(offX + i, offY + boxHeight - 2, 255, 255 , 255);

		scaledImg.SetAlpha(offX + i + 1, offY + boxHeight - 1, 255);
		scaledImg.SetRGB(offX + i + 1, offY + boxHeight - 1, 0, 0, 0);

	}

	bmp = wxBitmap(scaledImg);
	
	dc->DrawBitmap(bmp, 0, 0);
	delete img;
}

void paletteDialogImp::paletteRepaint( wxPaintEvent& event ){
	wxPaintDC dc((wxWindow*)(event.GetEventObject()));
	refreshPalette(&dc);
}


void paletteDialogImp::showSelectedCellColor(){
    //get the colour of the selected cell and set it to the colour picker
	Uint32 color = vid->colourList[selectedY * 16 + selectedX];
	wxColour c((color & 0xFF000000) >> 24, (color & 0x00FF0000) >> 16, (color & 0x0000FF00) >> 8, 255);
	colorPicker->SetColour(c);
}