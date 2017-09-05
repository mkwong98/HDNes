///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "mainForm.h"

///////////////////////////////////////////////////////////////////////////

mainForm::mainForm( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar = new wxMenuBar( 0 );
	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItemNew;
	m_menuItemNew = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("New Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItemNew );
	
	wxMenuItem* m_menuItemOpen;
	m_menuItemOpen = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Open Project...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItemOpen );
	
	m_menu3->AppendSeparator();
	
	wxMenuItem* m_menuSave;
	m_menuSave = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Save Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuSave );
	
	wxMenuItem* m_menuSaveAs;
	m_menuSaveAs = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Save Project As...") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuSaveAs );
	
	m_menu3->AppendSeparator();
	
	wxMenuItem* m_menuItemGen;
	m_menuItemGen = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Generate Pack Data") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItemGen );
	
	m_menu3->AppendSeparator();
	
	wxMenuItem* m_menuClose;
	m_menuClose = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Close Project") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuClose );
	
	m_menu3->AppendSeparator();
	
	wxMenuItem* m_menuExit;
	m_menuExit = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Exit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuExit );
	
	m_menubar->Append( m_menu3, wxT("File") ); 
	
	this->SetMenuBar( m_menubar );
	
	m_statusBar = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4 = new wxStaticText( m_panel1, wxID_ANY, wxT("Skip bytes:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer7->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	spnSkipBytes = new wxSpinCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 15, 0 );
	spnSkipBytes->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer7->Add( spnSkipBytes, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText5 = new wxStaticText( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer7->Add( m_staticText5, 0, wxALL, 5 );
	
	m_staticText6 = new wxStaticText( m_panel1, wxID_ANY, wxT("Zoom:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer7->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	zoomRom = new wxSpinCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, 1 );
	zoomRom->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer7->Add( zoomRom, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText7 = new wxStaticText( m_panel1, wxID_ANY, wxT("X"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer7->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText9 = new wxStaticText( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer7->Add( m_staticText9, 0, wxALL, 5 );
	
	m_staticText10 = new wxStaticText( m_panel1, wxID_ANY, wxT("Palette: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer7->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button2 = new wxButton( m_panel1, wxID_ANY, wxT("Back ground"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button3 = new wxButton( m_panel1, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button4 = new wxButton( m_panel1, wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_button5 = new wxButton( m_panel1, wxID_ANY, wxT("3"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer6->Add( bSizer7, 0, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableRow( 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );
	
	pnlRom = new wxPanel( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	fgSizer1->Add( pnlRom, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	romVScroll = new wxScrollBar( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL );
	bSizer10->Add( romVScroll, 1, wxALL, 5 );
	
	
	fgSizer1->Add( bSizer10, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	romHScroll = new wxScrollBar( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	bSizer13->Add( romHScroll, 1, wxALL, 5 );
	
	
	fgSizer1->Add( bSizer13, 1, wxEXPAND, 5 );
	
	
	bSizer6->Add( fgSizer1, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer6 );
	m_panel1->Layout();
	bSizer6->Fit( m_panel1 );
	m_notebook1->AddPage( m_panel1, wxT("ROM Viewer"), false );
	
	bSizer5->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer5 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( m_menuItemNew->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileNew ) );
	this->Connect( m_menuItemOpen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileOpen ) );
	this->Connect( m_menuSave->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileSave ) );
	this->Connect( m_menuSaveAs->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileSaveAs ) );
	this->Connect( m_menuItemGen->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileGen ) );
	this->Connect( m_menuClose->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileGen ) );
	this->Connect( m_menuExit->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileExit ) );
	spnSkipBytes->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::skipBytesChanged ), NULL, this );
	zoomRom->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::zoomRomChanged ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romBGColour ), NULL, this );
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour1 ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour2 ), NULL, this );
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour3 ), NULL, this );
	pnlRom->Connect( wxEVT_SIZE, wxSizeEventHandler( mainForm::rowViewSizeChanged ), NULL, this );
	romVScroll->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romHScroll->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
}

mainForm::~mainForm()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileNew ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileOpen ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileSave ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileSaveAs ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileGen ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileGen ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileExit ) );
	spnSkipBytes->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::skipBytesChanged ), NULL, this );
	zoomRom->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::zoomRomChanged ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romBGColour ), NULL, this );
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour1 ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour2 ), NULL, this );
	m_button5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour3 ), NULL, this );
	pnlRom->Disconnect( wxEVT_SIZE, wxSizeEventHandler( mainForm::rowViewSizeChanged ), NULL, this );
	romVScroll->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romVScroll->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::romViewVScrolled ), NULL, this );
	romHScroll->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	romHScroll->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::romViewHScrolled ), NULL, this );
	
}

newProjectDialog::newProjectDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("ROM file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer2->Add( m_staticText3, 0, wxALL, 5 );
	
	filePickRom = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.nes"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer2->Add( filePickRom, 1, wxALL, 5 );
	
	
	bSizer1->Add( bSizer2, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Graphics pack location:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer3->Add( m_staticText4, 0, wxALL, 5 );
	
	dirPickPack = new wxDirPickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_DEFAULT_STYLE );
	bSizer3->Add( dirPickPack, 1, wxALL, 5 );
	
	
	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer5->Add( m_staticText5, 1, wxALL, 5 );
	
	btnNewProjectOK = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( btnNewProjectOK, 0, wxALL, 5 );
	
	
	bSizer1->Add( bSizer5, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	btnNewProjectOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( newProjectDialog::fileSelected ), NULL, this );
}

newProjectDialog::~newProjectDialog()
{
	// Disconnect Events
	btnNewProjectOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( newProjectDialog::fileSelected ), NULL, this );
	
}
