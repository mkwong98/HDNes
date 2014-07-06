#pragma once
#include "..\wxwidget\formhdnes.h"
#include "video.h"
#include "audio.h"

class fraHDNesImp :
	public fraHDNes
{
protected:
	wxImage objScreenImg;
	wxBitmap objScreenBmp;
	bitmapE* screenTileCache;

	wxImage objImageImg;
	wxBitmap objImageBmp;
	batchMap* bmDialog;
	paletteDialog* pDialog;

	void powerButtonClicked( wxCommandEvent& event );
	void input1UP( wxCommandEvent& event );
	void input1DOWN( wxCommandEvent& event );
	void input1LEFT( wxCommandEvent& event );
	void input1RIGHT( wxCommandEvent& event );
	void input1A( wxCommandEvent& event );
	void input1B( wxCommandEvent& event );
	void input1SELECT( wxCommandEvent& event );
	void input1START( wxCommandEvent& event );

	void input2UP( wxCommandEvent& event );
	void input2DOWN( wxCommandEvent& event );
	void input2LEFT( wxCommandEvent& event );
	void input2RIGHT( wxCommandEvent& event );
	void input2A( wxCommandEvent& event );
	void input2B( wxCommandEvent& event );
	void input2SELECT( wxCommandEvent& event );
	void input2START( wxCommandEvent& event );

	void screen1x( wxCommandEvent& event );
	void screen2x( wxCommandEvent& event );
	void screen4x( wxCommandEvent& event );
	void screenxx( wxCommandEvent& event );
	void screenWidth( wxKeyEvent& event );
	void screenHeight( wxKeyEvent& event );
	void toggleGraphicsPack( wxCommandEvent& event );
	void toggleEditPack( wxCommandEvent& event );
	void toggleEdgeData( wxCommandEvent& event );
	void toggleCHRRamEdit( wxCommandEvent& event );
	void loadPackData( wxCommandEvent& event );
	void savePackData( wxCommandEvent& event );
	void setPackScale( wxCommandEvent& event );
	void showScreenShot( wxCommandEvent& event );
	void screenTileSelected( wxCommandEvent& event );
	void showCustomImage( wxCommandEvent& event );
	void addImageToPack( wxFileDirPickerEvent& event );
	void ImageTileSelected( wxMouseEvent& event );
	void confirmImgSelection( wxCommandEvent& event );
	void cancelSelection( wxCommandEvent& event );
	void genHDPack( wxCommandEvent& event );
	void inputEndGame( wxCommandEvent& event );
	void inputSaveState( wxCommandEvent& event );
	void inputLoadState( wxCommandEvent& event );
	void inputScreenCap( wxCommandEvent& event );
	void inputDataCap( wxCommandEvent& event );
	void inputPause( wxCommandEvent& event );
	void inputRunFrame( wxCommandEvent& event );
	void inputContCap( wxCommandEvent& event );
	void addBatchMapping( wxCommandEvent& event );
	void optimizeScreenEdit( wxCommandEvent& event );
	void customizePaletteClicked( wxCommandEvent& event );

	Sint16 editingMusic;
	void loadAudioPack( wxCommandEvent& event );
	void saveAudioPack( wxCommandEvent& event );
	void addMP3ToPack( wxFileDirPickerEvent& event );
	void addMP3( wxCommandEvent& event );
	void changeMP3( wxCommandEvent& event );
	void deleteMP3( wxCommandEvent& event );
	void musicSelected( wxListEvent& event );
	void toggleAudioPack( wxCommandEvent& event );
	void removeImageFromPack( wxCommandEvent& event );
	void AddDarkMapping( wxCommandEvent& event );

public:
	fraHDNesImp();
	~fraHDNesImp();
    int keycodes[SDLK_LAST];
    void addKeyCode(wxChoice* cbobox);
	void showKeyCode(wxChoice* cbobox, SDLKey key);
	void refreshGUI();
    void refreshInputGUI();
    void refreshVideoGUI();
    void refreshAudioGUI();

	void refreshGraphicsPackGUI();
	void loadScreen();
	void loadScreenTiles();
	void refreshScreenBitmap();
	void displayScreenBitmap();
	void loadImage();
	void refreshImageBitmap();
	void displayImageBitmap();

	void refreshAudioPackGUI();
    void refreshMP3GUI();
    void addMP3Field();

	void refreshRAMGUI();

	static string GetTileDisplayString(bitmapE* b);
	static wxString GetCellContentsString(wxListCtrl* wxc, long row_number, int column);
};

