///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __FORMHDNES_H__
#define __FORMHDNES_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/filepicker.h>
#include <wx/sizer.h>
#include <wx/button.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/choice.h>
#include <wx/radiobut.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/radiobox.h>
#include <wx/listbox.h>
#include <wx/listctrl.h>
#include <wx/spinctrl.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/dialog.h>
#include <wx/clrpicker.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class fraHDNes
///////////////////////////////////////////////////////////////////////////////
class fraHDNes : public wxFrame 
{
	private:
	
	protected:
		wxNotebook* m_notebook2;
		wxPanel* panBasic1;
		wxStaticText* m_staticText5;
		wxFilePickerCtrl* m_filePicker1;
		wxButton* m_button2;
		wxPanel* m_panel6;
		wxStaticText* m_staticText6;
		wxStaticText* lblP1;
		wxChoice* cbo1UP;
		wxStaticText* lblP11;
		wxChoice* cbo1DOWN;
		wxStaticText* lblP12;
		wxChoice* cbo1LEFT;
		wxStaticText* lblP121;
		wxChoice* cbo1RIGHT;
		wxStaticText* lblP122;
		wxChoice* cbo1A;
		wxStaticText* lblP123;
		wxChoice* cbo1B;
		wxStaticText* lblP124;
		wxChoice* cbo1SELECT;
		wxStaticText* lblP125;
		wxChoice* cbo1START;
		wxStaticText* m_staticText7;
		wxStaticText* lblP126;
		wxChoice* cbo2UP;
		wxStaticText* lblP127;
		wxChoice* cbo2DOWN;
		wxStaticText* lblP128;
		wxChoice* cbo2LEFT;
		wxStaticText* lblP129;
		wxChoice* cbo2RIGHT;
		wxStaticText* lblP1210;
		wxChoice* cbo2A;
		wxStaticText* lblP1211;
		wxChoice* cbo2B;
		wxStaticText* lblP1212;
		wxChoice* cbo2SELECT;
		wxStaticText* lblP1213;
		wxChoice* cbo2START;
		wxStaticText* m_staticText8;
		wxStaticText* lblP14;
		wxChoice* cboEndGame;
		wxStaticText* lblP13;
		wxChoice* cboSaveState;
		wxStaticText* lblP15;
		wxChoice* cboLoadState;
		wxStaticText* lblP151;
		wxChoice* cboScreenCap;
		wxStaticText* lblP1511;
		wxChoice* cboDataCap;
		wxStaticText* lblP15111;
		wxChoice* cboPause;
		wxStaticText* lblP15112;
		wxChoice* cboRunFrame;
		wxStaticText* m_staticText62;
		wxChoice* cboContCap;
		wxPanel* panVideo1;
		wxStaticText* m_staticText1;
		wxRadioButton* m_radioBtn1;
		wxRadioButton* m_radioBtn2;
		wxRadioButton* m_radioBtn3;
		wxRadioButton* m_radioBtn4;
		wxStaticText* m_staticText2;
		wxTextCtrl* txtwidth;
		wxStaticText* m_staticText4;
		wxStaticText* m_staticText3;
		wxTextCtrl* txtheight;
		wxCheckBox* chkUsePack;
		wxRadioBox* rbxGenerateData;
		wxCheckBox* chkNearEdge;
		wxCheckBox* chkCHRRamEdit;
		wxPanel* panAudio1;
		wxCheckBox* chkUseAudioPack;
		wxPanel* m_panel7;
		wxButton* btnLoadPack;
		wxButton* btnSavePack;
		wxStaticText* m_staticText27;
		wxRadioButton* optPackScale1;
		wxRadioButton* optPackScale2;
		wxRadioButton* optPackScale4;
		wxStaticText* m_staticText25;
		wxChoice* cboScreen;
		wxButton* btnOptimizeScreenEdit;
		wxStaticText* m_staticText32;
		wxListBox* lstScreenTiles;
		wxPanel* pnlScreen;
		wxStaticText* m_staticText31;
		wxStaticText* m_staticText26;
		wxChoice* cboImage;
		wxFilePickerCtrl* m_filePicker2;
		wxButton* btnRemoveImage;
		wxStaticText* m_staticText33;
		wxStaticText* m_staticText28;
		wxStaticText* m_staticText29;
		wxTextCtrl* txtMapX;
		wxStaticText* m_staticText30;
		wxTextCtrl* txtMapY;
		wxStaticText* m_staticText63;
		wxTextCtrl* txtBrightness;
		wxStaticText* m_staticText64;
		wxCheckBox* chkDefaultTile;
		wxButton* btnConfirmTile;
		wxButton* btnCancelSelection;
		wxButton* m_button6;
		wxButton* btn_Swap;
		wxButton* btn_MapDarkPalette;
		wxButton* btn_CustomizePalette;
		wxPanel* pnlImage;
		wxPanel* m_panel8;
		wxButton* btnLoadAudioPack;
		wxButton* btnSaveAudioPack;
		wxStaticText* m_staticText50;
		wxListCtrl* lstMusic;
		wxStaticText* m_staticText56;
		wxSpinCtrl* spinMusicPriority;
		wxStaticText* m_staticText57;
		wxCheckBox* chkGotoNext;
		wxStaticText* m_staticText51;
		wxTextCtrl* txtMusicRAMAddress;
		wxStaticText* m_staticText55;
		wxTextCtrl* txtMusicRAMValue;
		wxStaticText* m_staticText581;
		wxStaticText* m_staticText59;
		wxTextCtrl* txtConditions;
		wxStaticText* m_staticText60;
		wxStaticText* m_staticText58;
		wxTextCtrl* txtMusicRAMNewValue;
		wxStaticText* m_staticText571;
		wxRadioBox* rbxMusciPlayType;
		wxStaticText* m_staticText54;
		wxChoice* cboMP3file;
		wxFilePickerCtrl* m_filePicker4;
		wxButton* btnAddMP3;
		wxButton* btnConfirmMP3;
		wxButton* btnCancelMP3;
		wxPanel* m_panel11;
		wxStaticText* m_staticText61;
		wxListCtrl* lstMemory;
		
		// Virtual event handlers, overide them in your derived class
		virtual void powerButtonClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void input1UP( wxCommandEvent& event ) { event.Skip(); }
		virtual void input1DOWN( wxCommandEvent& event ) { event.Skip(); }
		virtual void input1LEFT( wxCommandEvent& event ) { event.Skip(); }
		virtual void input1RIGHT( wxCommandEvent& event ) { event.Skip(); }
		virtual void input1A( wxCommandEvent& event ) { event.Skip(); }
		virtual void input1B( wxCommandEvent& event ) { event.Skip(); }
		virtual void input1SELECT( wxCommandEvent& event ) { event.Skip(); }
		virtual void input1START( wxCommandEvent& event ) { event.Skip(); }
		virtual void input2UP( wxCommandEvent& event ) { event.Skip(); }
		virtual void input2DOWN( wxCommandEvent& event ) { event.Skip(); }
		virtual void input2LEFT( wxCommandEvent& event ) { event.Skip(); }
		virtual void input2RIGHT( wxCommandEvent& event ) { event.Skip(); }
		virtual void input2A( wxCommandEvent& event ) { event.Skip(); }
		virtual void input2B( wxCommandEvent& event ) { event.Skip(); }
		virtual void input2SELECT( wxCommandEvent& event ) { event.Skip(); }
		virtual void input2START( wxCommandEvent& event ) { event.Skip(); }
		virtual void inputEndGame( wxCommandEvent& event ) { event.Skip(); }
		virtual void inputSaveState( wxCommandEvent& event ) { event.Skip(); }
		virtual void inputLoadState( wxCommandEvent& event ) { event.Skip(); }
		virtual void inputScreenCap( wxCommandEvent& event ) { event.Skip(); }
		virtual void inputDataCap( wxCommandEvent& event ) { event.Skip(); }
		virtual void inputPause( wxCommandEvent& event ) { event.Skip(); }
		virtual void inputRunFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void inputContCap( wxCommandEvent& event ) { event.Skip(); }
		virtual void screen1x( wxCommandEvent& event ) { event.Skip(); }
		virtual void screen2x( wxCommandEvent& event ) { event.Skip(); }
		virtual void screen4x( wxCommandEvent& event ) { event.Skip(); }
		virtual void screenxx( wxCommandEvent& event ) { event.Skip(); }
		virtual void screenWidth( wxKeyEvent& event ) { event.Skip(); }
		virtual void screenHeight( wxKeyEvent& event ) { event.Skip(); }
		virtual void toggleGraphicsPack( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleEditPack( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleEdgeData( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleCHRRamEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void toggleAudioPack( wxCommandEvent& event ) { event.Skip(); }
		virtual void loadPackData( wxCommandEvent& event ) { event.Skip(); }
		virtual void savePackData( wxCommandEvent& event ) { event.Skip(); }
		virtual void setPackScale( wxCommandEvent& event ) { event.Skip(); }
		virtual void showScreenShot( wxCommandEvent& event ) { event.Skip(); }
		virtual void optimizeScreenEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void screenTileSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void showCustomImage( wxCommandEvent& event ) { event.Skip(); }
		virtual void addImageToPack( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void removeImageFromPack( wxCommandEvent& event ) { event.Skip(); }
		virtual void confirmImgSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void cancelSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void genHDPack( wxCommandEvent& event ) { event.Skip(); }
		virtual void addBatchMapping( wxCommandEvent& event ) { event.Skip(); }
		virtual void AddDarkMapping( wxCommandEvent& event ) { event.Skip(); }
		virtual void customizePaletteClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void ImageTileSelected( wxMouseEvent& event ) { event.Skip(); }
		virtual void loadAudioPack( wxCommandEvent& event ) { event.Skip(); }
		virtual void saveAudioPack( wxCommandEvent& event ) { event.Skip(); }
		virtual void musicSelected( wxListEvent& event ) { event.Skip(); }
		virtual void addMP3ToPick( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void addMP3( wxCommandEvent& event ) { event.Skip(); }
		virtual void changeMP3( wxCommandEvent& event ) { event.Skip(); }
		virtual void deleteMP3( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		fraHDNes( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 700,600 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~fraHDNes();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class batchMap
///////////////////////////////////////////////////////////////////////////////
class batchMap : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText25;
		wxChoice* cboImage;
		wxStaticText* m_staticText32;
		wxListBox* lstFirstTile;
		wxStaticText* m_staticText62;
		wxListBox* lstLastTile;
		wxPanel* pnlOldImg;
		wxStaticText* m_staticText621;
		wxListBox* lstNewPalette;
		wxStaticText* m_staticText26;
		wxChoice* cboNewImage;
		wxFilePickerCtrl* m_filePicker2;
		wxStaticText* m_staticText33;
		wxStaticText* m_staticText28;
		wxStaticText* m_staticText29;
		wxTextCtrl* txtMapX;
		wxStaticText* m_staticText30;
		wxTextCtrl* txtMapY;
		wxStaticText* m_staticText65;
		wxTextCtrl* txtBrightness;
		wxStaticText* m_staticText66;
		wxButton* btnAddMappings;
		wxButton* btnCancel;
		wxPanel* pnlNewImage;
		
		// Virtual event handlers, overide them in your derived class
		virtual void loadImage( wxCommandEvent& event ) { event.Skip(); }
		virtual void firstTileSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void lastTileSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void showNewPalette( wxCommandEvent& event ) { event.Skip(); }
		virtual void showNewImage( wxCommandEvent& event ) { event.Skip(); }
		virtual void addImageToPack( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void addMappings( wxCommandEvent& event ) { event.Skip(); }
		virtual void cancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void ImageTileSelected( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		batchMap( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 761,537 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~batchMap();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class paletteDialog
///////////////////////////////////////////////////////////////////////////////
class paletteDialog : public wxDialog 
{
	private:
	
	protected:
		wxPanel* pnlPalette;
		wxPanel* m_panel13;
		wxStaticText* m_staticText67;
		wxColourPickerCtrl* colorPicker;
		wxStaticText* m_staticText68;
		wxFilePickerCtrl* selectPalette;
		
		// Virtual event handlers, overide them in your derived class
		virtual void paletteCellSelected( wxMouseEvent& event ) { event.Skip(); }
		virtual void paletteRepaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void newColorSelected( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void paletteFileSelected( wxFileDirPickerEvent& event ) { event.Skip(); }
		
	
	public:
		
		paletteDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 641,351 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~paletteDialog();
	
};

#endif //__FORMHDNES_H__
