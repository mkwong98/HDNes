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
		wxChoice* m_choice1;
		wxStaticText* m_staticText3;
		wxChoice* m_choice2;
		wxStaticText* m_staticText4;
		wxChoice* m_choice3;
		wxPanel* m_panel6;
		wxStaticText* m_staticText9;
		wxChoice* m_choice8;
		wxPanel* m_panel7;
		wxStaticText* m_staticText5;
		wxChoice* m_choice4;
		wxStaticText* m_staticText6;
		wxChoice* m_choice5;
		wxStaticText* m_staticText7;
		wxChoice* m_choice6;
		wxStaticText* m_staticText8;
		wxChoice* m_choice7;
		wxPanel* m_panel81;
		wxStaticText* m_staticText101;
		wxPanel* m_panel51;
		wxStaticText* m_staticText21;
		wxChoice* m_choice11;
		wxStaticText* m_staticText31;
		wxChoice* m_choice21;
		wxStaticText* m_staticText41;
		wxChoice* m_choice31;
		wxPanel* m_panel61;
		wxStaticText* m_staticText91;
		wxChoice* m_choice81;
		wxPanel* m_panel71;
		wxStaticText* m_staticText51;
		wxChoice* m_choice41;
		wxStaticText* m_staticText61;
		wxChoice* m_choice51;
		wxStaticText* m_staticText71;
		wxChoice* m_choice61;
		wxStaticText* m_staticText81;
		wxChoice* m_choice71;
		wxPanel* m_panel13;
		wxStaticText* m_staticText24;
		wxChoice* m_choice37;
		wxStaticText* m_staticText25;
		wxChoice* m_choice22;
		wxStaticText* m_staticText26;
		wxChoice* m_choice23;
		wxStaticText* m_staticText27;
		wxChoice* m_choice24;
		wxStaticText* m_staticText411;
		wxChoice* m_choice211;
		wxStaticLine* m_staticline1;
		wxStaticText* m_staticText20;
		wxChoice* m_choice17;
		wxStaticText* m_staticText211;
		wxChoice* m_choice18;
		wxStaticText* m_staticText22;
		wxChoice* m_choice19;
		wxStaticText* m_staticText23;
		wxChoice* m_choice20;
		wxStaticLine* m_staticline2;
		wxStaticText* m_staticText28;
		wxChoice* m_choice25;
		wxStaticText* m_staticText29;
		wxChoice* m_choice26;
		wxStaticText* m_staticText30;
		wxChoice* m_choice27;
		wxStaticText* m_staticText311;
		wxChoice* m_choice28;
		wxStaticText* m_staticText32;
		wxChoice* m_choice29;
		wxStaticText* m_staticText33;
		wxChoice* m_choice30;
		wxStaticText* m_staticText34;
		wxChoice* m_choice311;
		wxStaticText* m_staticText35;
		wxChoice* m_choice32;
		wxStaticText* m_staticText36;
		wxChoice* m_choice33;
		wxStaticText* m_staticText37;
		wxChoice* m_choice34;
		wxStaticLine* m_staticline3;
		wxStaticText* m_staticText38;
		wxChoice* m_choice35;
		wxStaticText* m_staticText39;
		wxChoice* m_choice36;
		wxStaticText* m_staticText44;
		wxChoice* m_choice38;
		wxPanel* m_panel2;
		wxRadioBox* m_radioBox2;
		wxStaticText* m_staticText42;
		wxSpinCtrl* m_spinCtrl1;
		wxStaticText* m_staticText43;
		wxCheckBox* m_checkBox2;
		wxCheckBox* m_checkBox3;
		wxCheckBox* m_checkBox5;
		wxCheckBox* m_checkBox6;
		wxCheckBox* m_checkBox4;
		wxPanel* m_panel3;
		wxStaticText* m_staticText45;
		wxSlider* m_slider1;
		wxCheckBox* m_checkBox21;
		
		// Virtual event handlers, overide them in your derived class
		virtual void startGame( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		mainFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("HDNes"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 696,398 ), long style = wxCAPTION|wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		
		~mainFrame();
	
};

#endif //__MAINFRAME_H__
