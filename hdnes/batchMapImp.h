#pragma once
#include "..\wxwidget\formhdnes.h"
#include "video.h"

class batchMapImp :
	public batchMap
{
protected:
	bitmapE* firstTileCache;
	bitmapE* paletteTileCache;
	int newImgW;
	int newImgH;

	void loadImage( wxCommandEvent& event );
	void firstTileSelected( wxCommandEvent& event );
	void lastTileSelected( wxCommandEvent& event );
	void showNewImage( wxCommandEvent& event );
	void addImageToPack( wxFileDirPickerEvent& event );
	void addMappings( wxCommandEvent& event );
	void cancel( wxCommandEvent& event );
	void ImageTileSelected( wxMouseEvent& event );
	void showNewPalette( wxCommandEvent& event );

public:
	batchMapImp();
	~batchMapImp();
	void showSourceImg();
	void refreshImg(wxImage img, int poffsetx, int poffsety, int pdrawW, int pdrawH, int poffsetx2, int poffsety2, int pdrawW2, int pdrawH2);
	void loadNewImg();
};

