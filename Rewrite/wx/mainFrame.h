///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/filepicker.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/radiobox.h>
#include <wx/checkbox.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statline.h>
#include <wx/spinctrl.h>
#include <wx/slider.h>
#include <wx/notebook.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/radiobut.h>
#include <wx/choice.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class mainFrame
///////////////////////////////////////////////////////////////////////////////
class mainFrame : public wxFrame 
{
	private:
	
	protected:
		wxNotebook* m_notebook1;
		wxPanel* m_panel1;
		wxStaticText* m_staticText1;
		wxFilePickerCtrl* fslROMPicker;
		wxButton* btnStart;
		wxRadioBox* rbnCurrentSlot;
		wxCheckBox* chkRotateSlot;
		wxCheckBox* chkOverwriteBat;
		wxButton* btnSaveState;
		wxButton* btnLoadState;
		wxButton* btnLoadLastState;
		wxPanel* m_panel4;
		wxPanel* m_panel8;
		wxStaticText* m_staticText10;
		wxPanel* m_panel5;
		wxStaticText* m_staticText2;
		wxButton* btnP1Up;
		wxStaticText* m_staticText3;
		wxButton* btnP1Left;
		wxStaticText* m_staticText4;
		wxButton* btnP1Right;
		wxPanel* m_panel6;
		wxStaticText* m_staticText9;
		wxButton* btnP1Down;
		wxPanel* m_panel7;
		wxStaticText* m_staticText5;
		wxButton* btnP1Select;
		wxStaticText* m_staticText6;
		wxButton* btnP1Start;
		wxStaticText* m_staticText7;
		wxButton* btnP1B;
		wxStaticText* m_staticText8;
		wxButton* btnP1A;
		wxPanel* m_panel81;
		wxStaticText* m_staticText101;
		wxPanel* m_panel51;
		wxStaticText* m_staticText21;
		wxButton* btnP2Up;
		wxStaticText* m_staticText31;
		wxButton* btnP2Left;
		wxStaticText* m_staticText41;
		wxButton* btnP2Right;
		wxPanel* m_panel61;
		wxStaticText* m_staticText91;
		wxButton* btnP2Down;
		wxPanel* m_panel71;
		wxStaticText* m_staticText51;
		wxButton* btnP2Select;
		wxStaticText* m_staticText61;
		wxButton* btnP2Start;
		wxStaticText* m_staticText71;
		wxButton* btnP2B;
		wxStaticText* m_staticText81;
		wxButton* btnP2A;
		wxPanel* m_panel13;
		wxStaticText* m_staticText24;
		wxButton* btnKeyPause;
		wxStaticText* m_staticText25;
		wxButton* btnKeyAdvanceFrame;
		wxStaticText* m_staticText26;
		wxButton* btnKeyCaptureScreen;
		wxStaticText* m_staticText27;
		wxButton* btnKeyToggleContScrCap;
		wxStaticText* m_staticText411;
		wxButton* btnKeyStop;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText20;
		wxButton* btnKeySaveState;
		wxStaticText* m_staticText211;
		wxButton* btnKeyLoadState;
		wxStaticText* m_staticText22;
		wxButton* btnKeyLoadLastState;
		wxStaticText* m_staticText23;
		wxButton* btnKeyRotateState;
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText28;
		wxButton* btnKeySlot1;
		wxStaticText* m_staticText29;
		wxButton* btnKeySlot2;
		wxStaticText* m_staticText30;
		wxButton* btnKeySlot3;
		wxStaticText* m_staticText311;
		wxButton* btnKeySlot4;
		wxStaticText* m_staticText32;
		wxButton* btnKeySlot5;
		wxStaticText* m_staticText33;
		wxButton* btnKeySlot6;
		wxStaticText* m_staticText34;
		wxButton* btnKeySlot7;
		wxStaticText* m_staticText35;
		wxButton* btnKeySlot8;
		wxStaticText* m_staticText36;
		wxButton* btnKeySlot9;
		wxStaticText* m_staticText37;
		wxButton* btnKeySlot10;
		wxStaticLine* m_staticline3;
		wxStaticText* m_staticText38;
		wxButton* btnKeyHDCapFrame;
		wxStaticText* m_staticText39;
		wxButton* btnKeyToogleAutoHDCap;
		wxStaticText* m_staticText44;
		wxButton* btnKeyToogleIgnoreEdge;
		wxPanel* m_panel2;
		wxRadioBox* rbnScreenSize;
		wxStaticText* m_staticText42;
		wxSpinCtrl* spnContCapRate;
		wxStaticText* m_staticText43;
		wxCheckBox* chkUseHDGraphicsPack;
		wxCheckBox* chkGenHDData;
		wxCheckBox* chkIgnoreEdge;
		wxPanel* m_panel3;
		wxStaticText* m_staticText45;
		wxSlider* sldVolume;
		wxCheckBox* chkUseHDMusicPack;
		wxStatusBar* stbStatus;
		
		// Virtual event handlers, overide them in your derived class
		virtual void romSelected( wxFileDirPickerEvent& event ) { event.Skip(); }
		virtual void startGame( wxCommandEvent& event ) { event.Skip(); }
		virtual void stateSlotSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void rotateSlotSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void overwriteBatSelected( wxCommandEvent& event ) { event.Skip(); }
		virtual void saveStatePressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void loadStatePressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void loadLastPressed( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		mainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("HDNes"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 630,468 ), long style = wxCAPTION|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~mainFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class dlgInput
///////////////////////////////////////////////////////////////////////////////
class dlgInput : public wxDialog 
{
	private:
	
	protected:
		wxRadioButton* m_radioBtn2;
		wxChoice* m_choice39;
		wxRadioButton* m_radioBtn3;
		wxChoice* m_choice40;
		wxChoice* m_choice41;
		wxRadioButton* m_radioBtn1;
		wxButton* m_button5;
		wxButton* m_button6;
	
	public:
		
		dlgInput( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Choose input method"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 364,153 ), long style = wxDEFAULT_DIALOG_STYLE|wxSTAY_ON_TOP ); 
		~dlgInput();
	
};

#endif //__MAINFRAME_H__
