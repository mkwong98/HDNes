///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 21 2016)
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
	
	btnRomViewBGColour = new wxButton( m_panel1, wxID_ANY, wxT("Background"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( btnRomViewBGColour, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnRomViewColour1 = new wxButton( m_panel1, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( btnRomViewColour1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnRomViewColour2 = new wxButton( m_panel1, wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( btnRomViewColour2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnRomViewColour3 = new wxButton( m_panel1, wxID_ANY, wxT("3"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( btnRomViewColour3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
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
	zoomRom->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::zoomRomChanged ), NULL, this );
	btnRomViewBGColour->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romBGColour ), NULL, this );
	btnRomViewColour1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour1 ), NULL, this );
	btnRomViewColour2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour2 ), NULL, this );
	btnRomViewColour3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour3 ), NULL, this );
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
	zoomRom->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::zoomRomChanged ), NULL, this );
	btnRomViewBGColour->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romBGColour ), NULL, this );
	btnRomViewColour1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour1 ), NULL, this );
	btnRomViewColour2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour2 ), NULL, this );
	btnRomViewColour3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour3 ), NULL, this );
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

colourSelectDialog::colourSelectDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );
	
	wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 4, 16, 0, 0 );
	
	pnlColour00 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pnlColour00->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );
	
	gSizer1->Add( pnlColour00, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour01 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour01, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour02 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour02, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour03 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour03, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour04 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour04, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour05 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour05, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour06 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour06, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour07 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour07, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour08 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour08, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour09 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour09, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour0A = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour0A, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour0B = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour0B, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour0C = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour0C, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour0D = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour0D, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour0E = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour0E, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour0F = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour0F, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour10 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour10, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour11 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour11, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour12 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour12, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour13 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour13, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour14 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour14, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour15 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour15, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour16 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour16, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour17 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour17, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour18 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour18, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour19 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour19, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour1A = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour1A, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour1B = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour1B, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour1C = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour1C, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour1D = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour1D, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour1E = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour1E, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour1F = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour1F, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour20 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour20, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour21 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour21, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour22 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour22, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour23 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour23, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour24 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour24, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour25 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour25, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour26 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour26, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour27 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour27, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour28 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour28, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour29 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour29, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour2A = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour2A, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour2B = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour2B, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour2C = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour2C, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour2D = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour2D, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour2E = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour2E, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour2F = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour2F, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour30 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour30, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour31 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour31, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour32 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour32, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour33 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour33, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour34 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour34, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour35 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour35, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour36 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour36, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour37 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour37, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour38 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour38, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour39 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour39, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour3A = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour3A, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour3B = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour3B, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour3C = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour3C, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour3D = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour3D, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour3E = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour3E, 1, wxEXPAND | wxALL, 5 );
	
	pnlColour3F = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	gSizer1->Add( pnlColour3F, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer10->Add( gSizer1, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Left click a box to choose that colour. Right click to change the colour of that box."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer11->Add( m_staticText8, 0, wxALL, 5 );
	
	
	bSizer10->Add( bSizer11, 0, 0, 5 );
	
	
	this->SetSizer( bSizer10 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( colourSelectDialog::colourSelectInit ) );
	pnlColour00->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour00->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour01->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour01->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour02->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour02->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour03->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour03->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour04->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour04->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour05->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour05->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour06->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour06->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour07->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour07->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour08->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour08->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour09->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour09->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0A->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0A->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0B->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0B->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0C->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0C->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0D->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0D->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0E->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0E->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0F->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0F->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour10->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour10->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour11->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour11->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour12->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour12->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour13->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour13->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour14->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour14->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour15->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour15->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour16->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour16->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour17->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour17->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour18->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour18->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour19->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour19->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1A->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1A->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1B->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1B->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1C->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1C->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1D->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1D->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1E->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1E->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1F->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1F->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour20->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour20->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour21->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour21->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour22->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour22->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour23->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour23->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour24->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour24->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour25->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour25->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour26->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour26->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour27->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour27->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour28->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour28->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour29->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour29->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2A->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2A->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2B->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2B->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2C->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2C->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2D->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2D->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2E->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2E->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2F->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2F->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour30->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour30->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour31->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour31->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour32->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour32->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour33->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour33->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour34->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour34->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour35->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour35->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour36->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour36->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour37->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour37->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour38->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour38->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour39->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour39->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3A->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3A->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3B->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3B->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3C->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3C->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3D->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3D->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3E->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3E->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3F->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3F->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
}

colourSelectDialog::~colourSelectDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( colourSelectDialog::colourSelectInit ) );
	pnlColour00->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour00->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour01->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour01->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour02->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour02->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour03->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour03->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour04->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour04->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour05->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour05->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour06->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour06->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour07->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour07->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour08->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour08->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour09->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour09->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0A->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0A->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0B->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0B->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0C->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0C->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0D->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0D->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0E->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0E->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour0F->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour0F->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour10->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour10->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour11->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour11->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour12->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour12->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour13->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour13->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour14->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour14->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour15->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour15->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour16->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour16->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour17->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour17->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour18->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour18->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour19->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour19->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1A->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1A->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1B->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1B->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1C->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1C->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1D->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1D->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1E->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1E->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour1F->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour1F->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour20->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour20->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour21->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour21->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour22->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour22->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour23->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour23->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour24->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour24->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour25->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour25->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour26->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour26->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour27->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour27->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour28->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour28->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour29->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour29->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2A->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2A->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2B->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2B->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2C->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2C->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2D->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2D->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2E->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2E->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour2F->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour2F->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour30->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour30->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour31->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour31->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour32->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour32->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour33->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour33->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour34->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour34->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour35->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour35->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour36->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour36->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour37->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour37->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour38->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour38->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour39->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour39->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3A->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3A->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3B->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3B->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3C->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3C->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3D->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3D->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3E->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3E->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	pnlColour3F->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( colourSelectDialog::colourLClick ), NULL, this );
	pnlColour3F->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( colourSelectDialog::colourRClick ), NULL, this );
	
}
