///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __MAINFORM_H__
#define __MAINFORM_H__

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
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/scrolbar.h>
#include <wx/notebook.h>
#include <wx/frame.h>
#include <wx/filepicker.h>
#include <wx/dialog.h>

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
		wxNotebook* m_notebook1;
		wxPanel* m_panel1;
		wxStaticText* m_staticText4;
		wxSpinCtrl* spnSkipBytes;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText6;
		wxSpinCtrl* zoomRom;
		wxStaticText* m_staticText7;
		wxStaticText* m_staticText9;
		wxStaticText* m_staticText10;
		wxButton* m_button2;
		wxButton* m_button3;
		wxButton* m_button4;
		wxButton* m_button5;
		wxPanel* pnlRom;
		wxScrollBar* romVScroll;
		wxScrollBar* romHScroll;
		
		// Virtual event handlers, overide them in your derived class
		virtual void MenuFileNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileSaveAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileGen( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileExit( wxCommandEvent& event ) { event.Skip(); }
		virtual void skipBytesChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void zoomRomChanged( wxSpinEvent& event ) { event.Skip(); }
		virtual void romBGColour( wxCommandEvent& event ) { event.Skip(); }
		virtual void romColour1( wxCommandEvent& event ) { event.Skip(); }
		virtual void romColour2( wxCommandEvent& event ) { event.Skip(); }
		virtual void romColour3( wxCommandEvent& event ) { event.Skip(); }
		virtual void rowViewSizeChanged( wxSizeEvent& event ) { event.Skip(); }
		virtual void romViewVScrolled( wxScrollEvent& event ) { event.Skip(); }
		virtual void romViewHScrolled( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		
		mainForm( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("HDNes Graphics Pack Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 800,471 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~mainForm();
	
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
		
		newProjectDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 517,149 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~newProjectDialog();
	
};

#endif //__MAINFORM_H__
