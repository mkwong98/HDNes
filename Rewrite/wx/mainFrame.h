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
#include <wx/choice.h>
#include <wx/statline.h>
#include <wx/spinctrl.h>
#include <wx/slider.h>
#include <wx/notebook.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

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
		wxButton* btnSaveState;
		wxButton* btnLoadState;
		wxButton* btnLoadLastState;
		wxPanel* m_panel4;
		wxPanel* m_panel8;
		wxStaticText* m_staticText10;
		wxPanel* m_panel5;
		wxStaticText* m_staticText2;
		wxChoice* cboP1Up;
		wxStaticText* m_staticText3;
		wxChoice* cboP1Left;
		wxStaticText* m_staticText4;
		wxChoice* cboP1Right;
		wxPanel* m_panel6;
		wxStaticText* m_staticText9;
		wxChoice* cboP1Down;
		wxPanel* m_panel7;
		wxStaticText* m_staticText5;
		wxChoice* cboP1Select;
		wxStaticText* m_staticText6;
		wxChoice* cboP1Start;
		wxStaticText* m_staticText7;
		wxChoice* cboP1B;
		wxStaticText* m_staticText8;
		wxChoice* cboP1A;
		wxPanel* m_panel81;
		wxStaticText* m_staticText101;
		wxPanel* m_panel51;
		wxStaticText* m_staticText21;
		wxChoice* cboP2Up;
		wxStaticText* m_staticText31;
		wxChoice* cboP2Left;
		wxStaticText* m_staticText41;
		wxChoice* cboP2Right;
		wxPanel* m_panel61;
		wxStaticText* m_staticText91;
		wxChoice* cboP2Down;
		wxPanel* m_panel71;
		wxStaticText* m_staticText51;
		wxChoice* cboP2Select;
		wxStaticText* m_staticText61;
		wxChoice* cboP2Start;
		wxStaticText* m_staticText71;
		wxChoice* cboP2B;
		wxStaticText* m_staticText81;
		wxChoice* cboP2A;
		wxPanel* m_panel13;
		wxStaticText* m_staticText24;
		wxChoice* cboKeyPause;
		wxStaticText* m_staticText25;
		wxChoice* cboKeyAdvanceFrame;
		wxStaticText* m_staticText26;
		wxChoice* cboKeyCapScreen;
		wxStaticText* m_staticText27;
		wxChoice* cboKeyToggleContSCap;
		wxStaticText* m_staticText411;
		wxChoice* cboKeyStop;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText20;
		wxChoice* cboKeySaveState;
		wxStaticText* m_staticText211;
		wxChoice* cboKeyLoadState;
		wxStaticText* m_staticText22;
		wxChoice* cboKeyLoadLastState;
		wxStaticText* m_staticText23;
		wxChoice* cboKeyRotateSlot;
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText28;
		wxChoice* cboKeySlot1;
		wxStaticText* m_staticText29;
		wxChoice* cboKeySlot2;
		wxStaticText* m_staticText30;
		wxChoice* cboKeySlot3;
		wxStaticText* m_staticText311;
		wxChoice* cboKeySlot4;
		wxStaticText* m_staticText32;
		wxChoice* cboKeySlot5;
		wxStaticText* m_staticText33;
		wxChoice* cboKeySlot6;
		wxStaticText* m_staticText34;
		wxChoice* cboKeySlot7;
		wxStaticText* m_staticText35;
		wxChoice* cboKeySlot8;
		wxStaticText* m_staticText36;
		wxChoice* cboKeySlot9;
		wxStaticText* m_staticText37;
		wxChoice* cboKeySlot10;
		wxStaticLine* m_staticline3;
		wxStaticText* m_staticText38;
		wxChoice* cboKeyHDCapFrame;
		wxStaticText* m_staticText39;
		wxChoice* cboKeyToggleHDCap;
		wxStaticText* m_staticText44;
		wxChoice* cboKeyToggleIgnoreEdge;
		wxPanel* m_panel2;
		wxRadioBox* rbnScreenSize;
		wxStaticText* m_staticText42;
		wxSpinCtrl* spnContCapRate;
		wxStaticText* m_staticText43;
		wxCheckBox* chkUseHDGraphicsPack;
		wxCheckBox* chkGenHDData;
		wxCheckBox* chkGenROM;
		wxCheckBox* chkGenRAM;
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
		virtual void saveStatePressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void loadStatePressed( wxCommandEvent& event ) { event.Skip(); }
		virtual void loadLastPressed( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		mainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("HDNes"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 696,420 ), long style = wxCAPTION|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~mainFrame();
	
};

#endif //__MAINFRAME_H__
