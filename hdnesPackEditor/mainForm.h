///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/statusbr.h>
#include <wx/treectrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/radiobut.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/scrolbar.h>
#include <wx/listctrl.h>
#include <wx/textctrl.h>
#include <wx/notebook.h>
#include <wx/splitter.h>
#include <wx/frame.h>
#include <wx/filepicker.h>
#include <wx/dialog.h>
#include <wx/combobox.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class mainForm
///////////////////////////////////////////////////////////////////////////////
class mainForm : public wxFrame
{
	private:

	protected:
		wxMenuBar* m_menubar;
		wxMenu* m_menu3;
		wxStatusBar* m_statusBar;
		wxNotebook* pnlGameObjects;
		wxPanel* m_panel67;
		wxSplitterWindow* m_splitter2;
		wxPanel* m_panel70;
		wxTreeCtrl* treeGameObjs;
		wxPanel* m_panel71;
		wxNotebook* nbkGameObject;
		wxPanel* pnlObj;
		wxRadioButton* rbnObjectSprite;
		wxRadioButton* rbnObjectBG;
		wxStaticText* m_staticText101;
		wxButton* btnGameObjBGColour;
		wxStaticText* m_staticText12;
		wxStaticText* m_staticText16;
		wxSpinCtrl* spnBrightness;
		wxStaticText* m_staticText18;
		wxStaticText* m_staticText271;
		wxCheckBox* chkGameObjIsDefault;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText61;
		wxSpinCtrl* zoomGameObjs;
		wxStaticText* m_staticText611;
		wxChoice* cboFrameRange;
		wxPanel* pnlGameObjRaw;
		wxScrollBar* scrGameObjRawV;
		wxScrollBar* scrGameObjRawH;
		wxPanel* pnlGameObjNew;
		wxScrollBar* scrGameObjNewV;
		wxScrollBar* scrGameObjNewH;
		wxPanel* pnlSwaps;
		wxListCtrl* lstSwaps;
		wxStaticText* m_staticText181;
		wxTextCtrl* txtSwapName;
		wxListCtrl* lstPalettes;
		wxStaticText* m_staticText19;
		wxStaticText* lblOrgPalette;
		wxPanel* pnlOrgPaletteBG;
		wxPanel* pnlOrgPalette1;
		wxPanel* pnlOrgPalette2;
		wxPanel* pnlOrgPalette3;
		wxStaticText* m_staticText261;
		wxStaticText* m_staticText21;
		wxTextCtrl* txtSwapPaletteNew;
		wxButton* btnNewPaletteBG;
		wxButton* btnNewPalette1;
		wxButton* btnNewPalette2;
		wxButton* btnNewPalette3;
		wxStaticText* m_staticText22;
		wxSpinCtrl* spnSwapNewBrightness;
		wxStaticText* m_staticText23;
		wxStaticText* m_staticText24;
		wxSpinCtrl* spnSwapRotateHue;
		wxStaticText* m_staticText26;
		wxStaticText* m_staticText27;
		wxSpinCtrl* spnSwapNewSaturation;
		wxStaticText* m_staticText28;
		wxButton* btnAddSwap;
		wxButton* btnUpdateSwap;
		wxButton* btnDeleteSwap;
		wxPanel* pnlBGImage;
		wxButton* btnBGImage;
		wxStaticText* m_staticText51;
		wxSpinCtrl* spnBGBrightness;
		wxStaticText* m_staticText52;
		wxStaticText* m_staticText53;
		wxStaticText* m_staticText54;
		wxStaticText* m_staticText55;
		wxSpinCtrl* spnBGHScrollRate;
		wxStaticText* m_staticText58;
		wxStaticText* m_staticText56;
		wxStaticText* m_staticText57;
		wxSpinCtrl* spnBGVScrollRate;
		wxStaticText* m_staticText59;
		wxCheckBox* chkBgShowBehind;
		wxPanel* pnlBGImageDisplay;
		wxPanel* pnlConditions;
		wxListCtrl* lstConditions;
		wxStaticText* m_staticText281;
		wxChoice* cboConditionType;
		wxStaticText* m_staticText29;
		wxStaticText* m_staticText30;
		wxTextCtrl* txtConditionName;
		wxStaticText* m_staticText48;
		wxCheckBox* chkConditionNegative;
		wxPanel* pnlConditionType1;
		wxStaticText* m_staticText31;
		wxTextCtrl* txtConditionX;
		wxStaticText* m_staticText32;
		wxStaticText* m_staticText33;
		wxTextCtrl* txtConditionY;
		wxStaticText* m_staticText34;
		wxStaticText* m_staticText35;
		wxTextCtrl* txtConditionTile;
		wxStaticText* m_staticText36;
		wxStaticText* m_staticText37;
		wxTextCtrl* txtConditionPalette;
		wxPanel* pnlConditionType2;
		wxStaticText* m_staticText38;
		wxTextCtrl* txtConditionAddress1;
		wxStaticText* m_staticText39;
		wxStaticText* m_staticText40;
		wxChoice* cboConditionOp;
		wxStaticText* m_staticText41;
		wxStaticText* m_staticText42;
		wxTextCtrl* txtConditionAddress2;
		wxPanel* pnlConditionType3;
		wxStaticText* m_staticText43;
		wxTextCtrl* txtConditionAddress;
		wxStaticText* m_staticText44;
		wxStaticText* m_staticText45;
		wxChoice* cboConditionOp2;
		wxStaticText* m_staticText46;
		wxStaticText* m_staticText47;
		wxTextCtrl* txtConditionValue;
		wxPanel* pnlConditionType0;
		wxStaticText* m_staticText50;
		wxButton* cmdConditionAdd;
		wxButton* cmdConditionUpdate;
		wxButton* cmdConditionDelete;
		wxPanel* pnlAnimation;
		wxListCtrl* lstFrameRange;
		wxPanel* m_panel92;
		wxStaticText* m_staticText591;
		wxSpinCtrl* spnFrameRangeCnt;
		wxStaticText* m_staticText62;
		wxStaticText* m_staticText60;
		wxTextCtrl* txtFrameRangeName;
		wxButton* cmdFrameRangeAdd;
		wxButton* cmdFrameRangeUpdate;
		wxButton* cmdFrameRangeDelete;
		wxButton* cmdFrameRangeMoveUp;
		wxButton* cmdFrameRangeMoveDown;
		wxPanel* m_panel72;
		wxSplitterWindow* m_splitter21;
		wxPanel* m_panel741;
		wxListCtrl* lstHDImg;
		wxButton* btnHDImgAdd;
		wxButton* btnHDImgRemove;
		wxPanel* m_panel75;
		wxSplitterWindow* m_splitter3;
		wxPanel* m_panel76;
		wxListCtrl* lstHDImgTiles;
		wxPanel* pnlHDImg;
		wxPanel* m_panel1;
		wxStaticText* m_staticText6;
		wxSpinCtrl* zoomRom;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText10;
		wxButton* btnRomViewBGColour;
		wxButton* btnRomViewColour1;
		wxButton* btnRomViewColour2;
		wxButton* btnRomViewColour3;
		wxTextCtrl* txtRomViewPalette;
		wxPanel* pnlRom;
		wxScrollBar* romVScroll;
		wxScrollBar* romHScroll;

		// Virtual event handlers, overide them in your derived class
		virtual void closeWindow( wxCloseEvent& event ) { event.Skip(); }
		virtual void MenuFileNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileSaveAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileGen( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void gameObjTItemBeginEdit( wxTreeEvent& event ) { event.Skip(); }
		virtual void gameObjTItemChangeName( wxTreeEvent& event ) { event.Skip(); }
		virtual void gameObjTItemOpenMenu( wxTreeEvent& event ) { event.Skip(); }
		virtual void gameObjTItemSelected( wxTreeEvent& event ) { event.Skip(); }
		virtual void gameObjSpriteClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void gameObjBGClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void gameObjBGColour( wxCommandEvent& event ) { event.Skip(); }
		virtual void replaceBrightnessChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void gameObjDefaultClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void zoomGameObjsChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void ShowSelectedFrame( wxCommandEvent& event ) { event.Skip(); }
		virtual void gameObjsRawEnter( wxMouseEvent& event ) { event.Skip(); }
		virtual void gameObjsRawLDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void gameObjsRawLUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void gameObjsRawMove( wxMouseEvent& event ) { event.Skip(); }
		virtual void gameObjsRawRUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void gameObjsRawSizeChanged( wxSizeEvent& event ) { event.Skip(); }
		virtual void gameObjsRawVScrolled( wxScrollEvent& event ) { event.Skip(); }
		virtual void gameObjsRawHScrolled( wxScrollEvent& event ) { event.Skip(); }
		virtual void gameObjsNewEnter( wxMouseEvent& event ) { event.Skip(); }
		virtual void gameObjsNewLDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void gameObjsNewLUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void gameObjsNewMove( wxMouseEvent& event ) { event.Skip(); }
		virtual void gameObjsNewRUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void gameObjsNewSizeChanged( wxSizeEvent& event ) { event.Skip(); }
		virtual void gameObjsNewVScrolled( wxScrollEvent& event ) { event.Skip(); }
		virtual void gameObjsNewHScrolled( wxScrollEvent& event ) { event.Skip(); }
		virtual void SwapSeleted( wxListEvent& event ) { event.Skip(); }
		virtual void SwapPaletteSelected( wxListEvent& event ) { event.Skip(); }
		virtual void SwapPaletteNewChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void SwapNewPaletteBGClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void SwapNewPalette1Clicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void SwapNewPalette2Clicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void SwapNewPalette3Clicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void SwapNewBrightnessChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void SwapRotateHueChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void SwapNewSaturationChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void AddSwapClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void UpdateSwapClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteSwapClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void BGImageSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void BGImageBrightness( wxSpinEvent& event ) { event.Skip(); }
		virtual void BGImageHScrollRate( wxSpinEvent& event ) { event.Skip(); }
		virtual void BGImageVScrollRate( wxSpinEvent& event ) { event.Skip(); }
		virtual void BGImageShowBehindClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void ConditionSelected( wxListEvent& event ) { event.Skip(); }
		virtual void ConditionTypeSelect( wxCommandEvent& event ) { event.Skip(); }
		virtual void ConditionAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void ConditionUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void ConditionDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void FrameRangeItemSelected( wxListEvent& event ) { event.Skip(); }
		virtual void AddFrameRangeClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void UpdateFrameRangeClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void DeleteFrameRangeClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void MoveUpFrameRange( wxCommandEvent& event ) { event.Skip(); }
		virtual void MoveDownFrameRange( wxCommandEvent& event ) { event.Skip(); }
		virtual void HDImgSelected( wxListEvent& event ) { event.Skip(); }
		virtual void HDImgAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void HDImgRemove( wxCommandEvent& event ) { event.Skip(); }
		virtual void HDImgTileSelected( wxListEvent& event ) { event.Skip(); }
		virtual void HDImgEnter( wxMouseEvent& event ) { event.Skip(); }
		virtual void HDImgLDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void HDImgLUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void HDImgMove( wxMouseEvent& event ) { event.Skip(); }
		virtual void HDImgRUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void HDImgSizeChanged( wxSizeEvent& event ) { event.Skip(); }
		virtual void zoomRomChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void romBGColour( wxCommandEvent& event ) { event.Skip(); }
		virtual void romColour1( wxCommandEvent& event ) { event.Skip(); }
		virtual void romColour2( wxCommandEvent& event ) { event.Skip(); }
		virtual void romColour3( wxCommandEvent& event ) { event.Skip(); }
		virtual void romViewPaletteHexChanged( wxCommandEvent& event ) { event.Skip(); }
		virtual void romViewEnter( wxMouseEvent& event ) { event.Skip(); }
		virtual void romViewLDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void romViewLUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void romViewMove( wxMouseEvent& event ) { event.Skip(); }
		virtual void romViewRUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void romViewSizeChanged( wxSizeEvent& event ) { event.Skip(); }
		virtual void romViewVScrolled( wxScrollEvent& event ) { event.Skip(); }
		virtual void romViewHScrolled( wxScrollEvent& event ) { event.Skip(); }


	public:

		mainForm( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("HDNes Graphics Pack Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 980,626 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );

		~mainForm();

		void m_splitter2OnIdle( wxIdleEvent& )
		{
			m_splitter2->SetSashPosition( 150 );
			m_splitter2->Disconnect( wxEVT_IDLE, wxIdleEventHandler( mainForm::m_splitter2OnIdle ), NULL, this );
		}

		void m_splitter21OnIdle( wxIdleEvent& )
		{
			m_splitter21->SetSashPosition( 250 );
			m_splitter21->Disconnect( wxEVT_IDLE, wxIdleEventHandler( mainForm::m_splitter21OnIdle ), NULL, this );
		}

		void m_splitter3OnIdle( wxIdleEvent& )
		{
			m_splitter3->SetSashPosition( 250 );
			m_splitter3->Disconnect( wxEVT_IDLE, wxIdleEventHandler( mainForm::m_splitter3OnIdle ), NULL, this );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class newProjectDialog
///////////////////////////////////////////////////////////////////////////////
class newProjectDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText3;
		wxFilePickerCtrl* filePickRom;
		wxStaticText* m_staticText4;
		wxDirPickerCtrl* dirPickPack;
		wxStaticText* m_staticText5;
		wxButton* btnNewProjectOK;

		// Virtual event handlers, overide them in your derived class
		virtual void fileSelected( wxCommandEvent& event ) { event.Skip(); }


	public:

		newProjectDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Project config"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 517,149 ), long style = wxDEFAULT_DIALOG_STYLE );
		~newProjectDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class colourSelectDialog
///////////////////////////////////////////////////////////////////////////////
class colourSelectDialog : public wxDialog
{
	private:

	protected:
		wxPanel* pnlColour00;
		wxPanel* pnlColour01;
		wxPanel* pnlColour02;
		wxPanel* pnlColour03;
		wxPanel* pnlColour04;
		wxPanel* pnlColour05;
		wxPanel* pnlColour06;
		wxPanel* pnlColour07;
		wxPanel* pnlColour08;
		wxPanel* pnlColour09;
		wxPanel* pnlColour0A;
		wxPanel* pnlColour0B;
		wxPanel* pnlColour0C;
		wxPanel* pnlColour0D;
		wxPanel* pnlColour0E;
		wxPanel* pnlColour0F;
		wxPanel* pnlColour10;
		wxPanel* pnlColour11;
		wxPanel* pnlColour12;
		wxPanel* pnlColour13;
		wxPanel* pnlColour14;
		wxPanel* pnlColour15;
		wxPanel* pnlColour16;
		wxPanel* pnlColour17;
		wxPanel* pnlColour18;
		wxPanel* pnlColour19;
		wxPanel* pnlColour1A;
		wxPanel* pnlColour1B;
		wxPanel* pnlColour1C;
		wxPanel* pnlColour1D;
		wxPanel* pnlColour1E;
		wxPanel* pnlColour1F;
		wxPanel* pnlColour20;
		wxPanel* pnlColour21;
		wxPanel* pnlColour22;
		wxPanel* pnlColour23;
		wxPanel* pnlColour24;
		wxPanel* pnlColour25;
		wxPanel* pnlColour26;
		wxPanel* pnlColour27;
		wxPanel* pnlColour28;
		wxPanel* pnlColour29;
		wxPanel* pnlColour2A;
		wxPanel* pnlColour2B;
		wxPanel* pnlColour2C;
		wxPanel* pnlColour2D;
		wxPanel* pnlColour2E;
		wxPanel* pnlColour2F;
		wxPanel* pnlColour30;
		wxPanel* pnlColour31;
		wxPanel* pnlColour32;
		wxPanel* pnlColour33;
		wxPanel* pnlColour34;
		wxPanel* pnlColour35;
		wxPanel* pnlColour36;
		wxPanel* pnlColour37;
		wxPanel* pnlColour38;
		wxPanel* pnlColour39;
		wxPanel* pnlColour3A;
		wxPanel* pnlColour3B;
		wxPanel* pnlColour3C;
		wxPanel* pnlColour3D;
		wxPanel* pnlColour3E;
		wxPanel* pnlColour3F;
		wxStaticText* m_staticText8;

		// Virtual event handlers, overide them in your derived class
		virtual void colourSelectInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void colourLClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void colourRClick( wxMouseEvent& event ) { event.Skip(); }


	public:

		colourSelectDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Choose a colour"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 774,288 ), long style = wxDEFAULT_DIALOG_STYLE );
		~colourSelectDialog();

};

///////////////////////////////////////////////////////////////////////////////
/// Class replacementDialog
///////////////////////////////////////////////////////////////////////////////
class replacementDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText13;
		wxComboBox* cboImage;
		wxStaticText* m_staticText14;
		wxCheckBox* chkSnapToGrid;
		wxPanel* pnlImage;
		wxButton* m_button9;

		// Virtual event handlers, overide them in your derived class
		virtual void imageSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void mouseClicked( wxMouseEvent& event ) { event.Skip(); }
		virtual void mouseMoved( wxMouseEvent& event ) { event.Skip(); }
		virtual void sizeChanged( wxSizeEvent& event ) { event.Skip(); }
		virtual void replacementConfirm( wxCommandEvent& event ) { event.Skip(); }


	public:

		replacementDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Choose a replacement"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 669,504 ), long style = wxDEFAULT_DIALOG_STYLE|wxMAXIMIZE_BOX|wxMINIMIZE_BOX|wxRESIZE_BORDER );
		~replacementDialog();

};

