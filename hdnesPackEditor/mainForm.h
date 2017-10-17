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
#include <wx/textctrl.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/scrolbar.h>
#include <wx/treectrl.h>
#include <wx/splitter.h>
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
		wxPanel* m_panel67;
		wxSplitterWindow* m_splitter2;
		wxPanel* m_panel70;
		wxTreeCtrl* treeGameObjs;
		wxPanel* m_panel71;
		wxStaticText* m_staticText61;
		wxSpinCtrl* zoomGameObjs;
		wxStaticText* m_staticText11;
		wxPanel* pnlGameObjRaw;
		wxScrollBar* scrGameObjRawV;
		wxScrollBar* scrGameObjRawH;
		wxStaticText* m_staticText12;
		wxPanel* pnlGameObjNew;
		wxScrollBar* scrGameObjNewV;
		wxScrollBar* scrGameObjNewH;
		
		// Virtual event handlers, overide them in your derived class
		virtual void closeWindow( wxCloseEvent& event ) { event.Skip(); }
		virtual void MenuFileNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileOpen( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileSaveAs( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileGen( wxCommandEvent& event ) { event.Skip(); }
		virtual void MenuFileExit( wxCommandEvent& event ) { event.Skip(); }
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
		virtual void gameObjTItemBeginEdit( wxTreeEvent& event ) { event.Skip(); }
		virtual void gameObjTItemChangeName( wxTreeEvent& event ) { event.Skip(); }
		virtual void gameObjTItemOpenMenu( wxTreeEvent& event ) { event.Skip(); }
		virtual void gameObjTItemSelected( wxTreeEvent& event ) { event.Skip(); }
		virtual void zoomGameObjsChanged( wxSpinEvent& event ) { event.Skip(); }
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
		
	
	public:
		
		mainForm( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("HDNes Graphics Pack Editor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 816,626 ), long style = wxDEFAULT_FRAME_STYLE|wxRESIZE_BORDER|wxTAB_TRAVERSAL );
		
		~mainForm();
		
		void m_splitter2OnIdle( wxIdleEvent& )
		{
			m_splitter2->SetSashPosition( 150 );
			m_splitter2->Disconnect( wxEVT_IDLE, wxIdleEventHandler( mainForm::m_splitter2OnIdle ), NULL, this );
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

#endif //__MAINFORM_H__
