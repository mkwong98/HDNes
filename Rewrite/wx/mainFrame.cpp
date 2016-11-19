///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jun 17 2015)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "mainFrame.h"

///////////////////////////////////////////////////////////////////////////

mainFrame::mainFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( m_panel1, wxID_ANY, wxT("Game ROM file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer3->Add( m_staticText1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	fslROMPicker = new wxFilePickerCtrl( m_panel1, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer3->Add( fslROMPicker, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnStart = new wxButton( m_panel1, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer3->Add( btnStart, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer2->Add( bSizer3, 0, wxEXPAND, 5 );
	
	wxString rbnCurrentSlotChoices[] = { wxT("1"), wxT("2"), wxT("3"), wxT("4"), wxT("5"), wxT("6"), wxT("7"), wxT("8"), wxT("9"), wxT("10") };
	int rbnCurrentSlotNChoices = sizeof( rbnCurrentSlotChoices ) / sizeof( wxString );
	rbnCurrentSlot = new wxRadioBox( m_panel1, wxID_ANY, wxT("Current state slot (game specific)"), wxDefaultPosition, wxDefaultSize, rbnCurrentSlotNChoices, rbnCurrentSlotChoices, 1, wxRA_SPECIFY_ROWS );
	rbnCurrentSlot->SetSelection( 0 );
	bSizer2->Add( rbnCurrentSlot, 0, wxALL, 5 );
	
	chkRotateSlot = new wxCheckBox( m_panel1, wxID_ANY, wxT("Automatically rotate current slot after each time the game state is saved"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( chkRotateSlot, 0, wxALL, 5 );
	
	chkOverwriteBat = new wxCheckBox( m_panel1, wxID_ANY, wxT("Load state will overwrite battery backup"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( chkOverwriteBat, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	btnSaveState = new wxButton( m_panel1, wxID_ANY, wxT("Save state"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( btnSaveState, 0, wxALL, 5 );
	
	btnLoadState = new wxButton( m_panel1, wxID_ANY, wxT("Load state"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( btnLoadState, 0, wxALL, 5 );
	
	btnLoadLastState = new wxButton( m_panel1, wxID_ANY, wxT("Load the last saved state"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( btnLoadLastState, 0, wxALL, 5 );
	
	
	bSizer2->Add( bSizer4, 0, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( bSizer2 );
	m_panel1->Layout();
	bSizer2->Fit( m_panel1 );
	m_notebook1->AddPage( m_panel1, wxT("Playing"), true );
	m_panel4 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_panel8 = new wxPanel( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText10 = new wxStaticText( m_panel8, wxID_ANY, wxT("Player 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer22->Add( m_staticText10, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );
	
	m_panel5 = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText2 = new wxStaticText( m_panel5, wxID_ANY, wxT("Up"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer13->Add( m_staticText2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP1Up = new wxButton( m_panel5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( btnP1Up, 0, wxALL, 5 );
	
	
	m_panel5->SetSizer( bSizer13 );
	m_panel5->Layout();
	bSizer13->Fit( m_panel5 );
	bSizer11->Add( m_panel5, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	bSizer9->Add( bSizer11, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText3 = new wxStaticText( m_panel8, wxID_ANY, wxT("Left"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer12->Add( m_staticText3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP1Left = new wxButton( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( btnP1Left, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( m_panel8, wxID_ANY, wxT("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer12->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP1Right = new wxButton( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer12->Add( btnP1Right, 0, wxALL, 5 );
	
	
	bSizer9->Add( bSizer12, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	m_panel6 = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText9 = new wxStaticText( m_panel6, wxID_ANY, wxT("Down"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer15->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP1Down = new wxButton( m_panel6, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer15->Add( btnP1Down, 0, wxALL, 5 );
	
	
	m_panel6->SetSizer( bSizer15 );
	m_panel6->Layout();
	bSizer15->Fit( m_panel6 );
	bSizer14->Add( m_panel6, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer9->Add( bSizer14, 1, wxEXPAND, 5 );
	
	
	bSizer6->Add( bSizer9, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panel7 = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText5 = new wxStaticText( m_panel7, wxID_ANY, wxT("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	fgSizer1->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP1Select = new wxButton( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( btnP1Select, 0, wxALL, 5 );
	
	m_staticText6 = new wxStaticText( m_panel7, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer1->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP1Start = new wxButton( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( btnP1Start, 0, wxALL, 5 );
	
	m_staticText7 = new wxStaticText( m_panel7, wxID_ANY, wxT("B"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer1->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP1B = new wxButton( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( btnP1B, 0, wxALL, 5 );
	
	m_staticText8 = new wxStaticText( m_panel7, wxID_ANY, wxT("A"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP1A = new wxButton( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer1->Add( btnP1A, 0, wxALL, 5 );
	
	
	m_panel7->SetSizer( fgSizer1 );
	m_panel7->Layout();
	fgSizer1->Fit( m_panel7 );
	bSizer10->Add( m_panel7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer6->Add( bSizer10, 0, wxEXPAND, 5 );
	
	
	bSizer22->Add( bSizer6, 0, wxEXPAND, 5 );
	
	
	m_panel8->SetSizer( bSizer22 );
	m_panel8->Layout();
	bSizer22->Fit( m_panel8 );
	bSizer5->Add( m_panel8, 0, wxALL|wxEXPAND, 5 );
	
	m_panel81 = new wxPanel( m_panel4, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER|wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer221;
	bSizer221 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText101 = new wxStaticText( m_panel81, wxID_ANY, wxT("Player 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	bSizer221->Add( m_staticText101, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer91;
	bSizer91 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxVERTICAL );
	
	m_panel51 = new wxPanel( m_panel81, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText21 = new wxStaticText( m_panel51, wxID_ANY, wxT("Up"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer131->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP2Up = new wxButton( m_panel51, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer131->Add( btnP2Up, 0, wxALL, 5 );
	
	
	m_panel51->SetSizer( bSizer131 );
	m_panel51->Layout();
	bSizer131->Fit( m_panel51 );
	bSizer111->Add( m_panel51, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	bSizer91->Add( bSizer111, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer121;
	bSizer121 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText31 = new wxStaticText( m_panel81, wxID_ANY, wxT("Left"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	bSizer121->Add( m_staticText31, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP2Left = new wxButton( m_panel81, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( btnP2Left, 0, wxALL, 5 );
	
	m_staticText41 = new wxStaticText( m_panel81, wxID_ANY, wxT("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer121->Add( m_staticText41, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP2Right = new wxButton( m_panel81, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer121->Add( btnP2Right, 0, wxALL, 5 );
	
	
	bSizer91->Add( bSizer121, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer141;
	bSizer141 = new wxBoxSizer( wxVERTICAL );
	
	m_panel61 = new wxPanel( m_panel81, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer151;
	bSizer151 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText91 = new wxStaticText( m_panel61, wxID_ANY, wxT("Down"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText91->Wrap( -1 );
	bSizer151->Add( m_staticText91, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP2Down = new wxButton( m_panel61, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer151->Add( btnP2Down, 0, wxALL, 5 );
	
	
	m_panel61->SetSizer( bSizer151 );
	m_panel61->Layout();
	bSizer151->Fit( m_panel61 );
	bSizer141->Add( m_panel61, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer91->Add( bSizer141, 1, wxEXPAND, 5 );
	
	
	bSizer61->Add( bSizer91, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panel71 = new wxPanel( m_panel81, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 4, 0, 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText51 = new wxStaticText( m_panel71, wxID_ANY, wxT("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	fgSizer11->Add( m_staticText51, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP2Select = new wxButton( m_panel71, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( btnP2Select, 0, wxALL, 5 );
	
	m_staticText61 = new wxStaticText( m_panel71, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	fgSizer11->Add( m_staticText61, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP2Start = new wxButton( m_panel71, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( btnP2Start, 0, wxALL, 5 );
	
	m_staticText71 = new wxStaticText( m_panel71, wxID_ANY, wxT("B"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	fgSizer11->Add( m_staticText71, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP2B = new wxButton( m_panel71, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( btnP2B, 0, wxALL, 5 );
	
	m_staticText81 = new wxStaticText( m_panel71, wxID_ANY, wxT("A"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	fgSizer11->Add( m_staticText81, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnP2A = new wxButton( m_panel71, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer11->Add( btnP2A, 0, wxALL, 5 );
	
	
	m_panel71->SetSizer( fgSizer11 );
	m_panel71->Layout();
	fgSizer11->Fit( m_panel71 );
	bSizer101->Add( m_panel71, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer61->Add( bSizer101, 0, wxEXPAND, 5 );
	
	
	bSizer221->Add( bSizer61, 0, wxEXPAND, 5 );
	
	
	m_panel81->SetSizer( bSizer221 );
	m_panel81->Layout();
	bSizer221->Fit( m_panel81 );
	bSizer5->Add( m_panel81, 0, wxEXPAND | wxALL, 5 );
	
	m_staticText47 = new wxStaticText( m_panel4, wxID_ANY, wxT("Click the button you wish to change. Then press a key or use the joystick to map input to the button. Press Esc to cancel."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47->Wrap( 580 );
	bSizer5->Add( m_staticText47, 0, 0, 5 );
	
	
	m_panel4->SetSizer( bSizer5 );
	m_panel4->Layout();
	bSizer5->Fit( m_panel4 );
	m_notebook1->AddPage( m_panel4, wxT("Gamepad"), false );
	m_panel13 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText46 = new wxStaticText( m_panel13, wxID_ANY, wxT("Press Esc key to stop the emulator"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	m_staticText46->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer25->Add( m_staticText46, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText24 = new wxStaticText( m_panel13, wxID_ANY, wxT("Pause/resume"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer3->Add( m_staticText24, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeyPause = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( btnKeyPause, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText25 = new wxStaticText( m_panel13, wxID_ANY, wxT("Advance by 1 frame"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( 100 );
	fgSizer3->Add( m_staticText25, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeyAdvanceFrame = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( btnKeyAdvanceFrame, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText26 = new wxStaticText( m_panel13, wxID_ANY, wxT("Capture screen"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( 100 );
	fgSizer3->Add( m_staticText26, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeyCaptureScreen = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( btnKeyCaptureScreen, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText27 = new wxStaticText( m_panel13, wxID_ANY, wxT("Toggle continuous screen capture"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( 100 );
	fgSizer3->Add( m_staticText27, 0, wxALL, 5 );
	
	btnKeyToggleContScrCap = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( btnKeyToggleContScrCap, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText451 = new wxStaticText( m_panel13, wxID_ANY, wxT("Reset"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText451->Wrap( -1 );
	fgSizer3->Add( m_staticText451, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	btnKeyReset = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( btnKeyReset, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer25->Add( fgSizer3, 0, 0, 5 );
	
	m_staticline1 = new wxStaticLine( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer25->Add( m_staticline1, 0, wxALL|wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText20 = new wxStaticText( m_panel13, wxID_ANY, wxT("Save state"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer5->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeySaveState = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( btnKeySaveState, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText211 = new wxStaticText( m_panel13, wxID_ANY, wxT("Load state"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	fgSizer5->Add( m_staticText211, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeyLoadState = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( btnKeyLoadState, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText22 = new wxStaticText( m_panel13, wxID_ANY, wxT("Load last state saved"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( 100 );
	fgSizer5->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeyLoadLastState = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( btnKeyLoadLastState, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText23 = new wxStaticText( m_panel13, wxID_ANY, wxT("Rotate to next state slot"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( 100 );
	fgSizer5->Add( m_staticText23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeyRotateState = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer5->Add( btnKeyRotateState, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer25->Add( fgSizer5, 1, 0, 5 );
	
	
	bSizer24->Add( bSizer25, 0, 0, 5 );
	
	m_staticline2 = new wxStaticLine( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer24->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText28 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	fgSizer4->Add( m_staticText28, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeySlot1 = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnKeySlot1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText29 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizer4->Add( m_staticText29, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeySlot2 = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnKeySlot2, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText30 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer4->Add( m_staticText30, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeySlot3 = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnKeySlot3, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText311 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 4"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText311->Wrap( -1 );
	fgSizer4->Add( m_staticText311, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeySlot4 = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnKeySlot4, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText32 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 5"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer4->Add( m_staticText32, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeySlot5 = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnKeySlot5, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText33 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 6"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	fgSizer4->Add( m_staticText33, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeySlot6 = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnKeySlot6, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText34 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 7"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	fgSizer4->Add( m_staticText34, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeySlot7 = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnKeySlot7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText35 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 8"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer4->Add( m_staticText35, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeySlot8 = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnKeySlot8, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText36 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 9"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	fgSizer4->Add( m_staticText36, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeySlot9 = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnKeySlot9, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText37 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 10"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	fgSizer4->Add( m_staticText37, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeySlot10 = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( btnKeySlot10, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer24->Add( fgSizer4, 0, wxEXPAND, 5 );
	
	m_staticline3 = new wxStaticLine( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer24->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText38 = new wxStaticText( m_panel13, wxID_ANY, wxT("Capture the data from the current frame for HD pack editor"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( 100 );
	fgSizer6->Add( m_staticText38, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeyHDCapFrame = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( btnKeyHDCapFrame, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText39 = new wxStaticText( m_panel13, wxID_ANY, wxT("Toggle automatic frame data capture"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( 100 );
	fgSizer6->Add( m_staticText39, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeyToogleAutoHDCap = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( btnKeyToogleAutoHDCap, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText44 = new wxStaticText( m_panel13, wxID_ANY, wxT("Toggle ignore graphics near the edge of the screen"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( 100 );
	fgSizer6->Add( m_staticText44, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	btnKeyToogleIgnoreEdge = new wxButton( m_panel13, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer6->Add( btnKeyToogleIgnoreEdge, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer24->Add( fgSizer6, 1, wxEXPAND, 5 );
	
	
	m_panel13->SetSizer( bSizer24 );
	m_panel13->Layout();
	bSizer24->Fit( m_panel13 );
	m_notebook1->AddPage( m_panel13, wxT("Function keys"), false );
	m_panel2 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	wxString rbnScreenSizeChoices[] = { wxT("1x"), wxT("2x"), wxT("4x") };
	int rbnScreenSizeNChoices = sizeof( rbnScreenSizeChoices ) / sizeof( wxString );
	rbnScreenSize = new wxRadioBox( m_panel2, wxID_ANY, wxT("Screen size"), wxDefaultPosition, wxDefaultSize, rbnScreenSizeNChoices, rbnScreenSizeChoices, 1, wxRA_SPECIFY_ROWS );
	rbnScreenSize->SetSelection( 0 );
	bSizer27->Add( rbnScreenSize, 0, wxALL, 5 );
	
	
	bSizer26->Add( bSizer27, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText42 = new wxStaticText( m_panel2, wxID_ANY, wxT(" Rate of continuous screen capture: 1 screen in every"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	bSizer28->Add( m_staticText42, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	spnContCapRate = new wxSpinCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 300, 5 );
	bSizer28->Add( spnContCapRate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText43 = new wxStaticText( m_panel2, wxID_ANY, wxT("frame(s)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	bSizer28->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer26->Add( bSizer28, 0, wxEXPAND, 5 );
	
	chkUseHDGraphicsPack = new wxCheckBox( m_panel2, wxID_ANY, wxT("Use HD graphics pack when available "), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( chkUseHDGraphicsPack, 0, wxALL, 5 );
	
	chkGenHDData = new wxCheckBox( m_panel2, wxID_ANY, wxT("Automatically capture frame data for making HD graphics pack"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( chkGenHDData, 0, wxALL, 5 );
	
	chkIgnoreEdge = new wxCheckBox( m_panel2, wxID_ANY, wxT("Ignore graphics near the edge of the screen"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( chkIgnoreEdge, 0, wxALL, 5 );
	
	
	m_panel2->SetSizer( bSizer26 );
	m_panel2->Layout();
	bSizer26->Fit( m_panel2 );
	m_notebook1->AddPage( m_panel2, wxT("Video"), false );
	m_panel3 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText45 = new wxStaticText( m_panel3, wxID_ANY, wxT("Volume(%):"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	bSizer31->Add( m_staticText45, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	sldVolume = new wxSlider( m_panel3, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_BOTTOM|wxSL_HORIZONTAL|wxSL_LABELS );
	sldVolume->SetMinSize( wxSize( 200,-1 ) );
	
	bSizer31->Add( sldVolume, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer30->Add( bSizer31, 0, wxEXPAND, 5 );
	
	chkUseHDMusicPack = new wxCheckBox( m_panel3, wxID_ANY, wxT("Use HD music pack when available "), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer30->Add( chkUseHDMusicPack, 0, wxALL, 5 );
	
	
	m_panel3->SetSizer( bSizer30 );
	m_panel3->Layout();
	bSizer30->Fit( m_panel3 );
	m_notebook1->AddPage( m_panel3, wxT("Audio"), false );
	
	bSizer1->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	stbStatus = this->CreateStatusBar( 1, wxST_SIZEGRIP, wxID_ANY );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	fslROMPicker->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( mainFrame::romSelected ), NULL, this );
	btnStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::startGame ), NULL, this );
	rbnCurrentSlot->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( mainFrame::stateSlotSelected ), NULL, this );
	chkRotateSlot->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainFrame::rotateSlotSelected ), NULL, this );
	chkOverwriteBat->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainFrame::overwriteBatSelected ), NULL, this );
	btnSaveState->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::saveStatePressed ), NULL, this );
	btnLoadState->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::loadStatePressed ), NULL, this );
	btnLoadLastState->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::loadLastPressed ), NULL, this );
	btnP1Up->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1Left->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1Right->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1Down->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1Select->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1Start->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1B->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1A->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Up->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Left->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Right->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Down->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Select->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Start->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2B->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2A->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyPause->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyAdvanceFrame->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyCaptureScreen->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyToggleContScrCap->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySaveState->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyLoadState->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyLoadLastState->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyRotateState->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot6->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot7->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot10->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyHDCapFrame->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyToogleAutoHDCap->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyToogleIgnoreEdge->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	rbnScreenSize->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( mainFrame::screenSizeSelected ), NULL, this );
	spnContCapRate->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainFrame::contCapRateSelected ), NULL, this );
	chkUseHDGraphicsPack->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainFrame::useGPackSelected ), NULL, this );
	chkGenHDData->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainFrame::autoCaptureForHDSelected ), NULL, this );
	chkIgnoreEdge->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainFrame::ignoreEdgeSelected ), NULL, this );
}

mainFrame::~mainFrame()
{
	// Disconnect Events
	fslROMPicker->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( mainFrame::romSelected ), NULL, this );
	btnStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::startGame ), NULL, this );
	rbnCurrentSlot->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( mainFrame::stateSlotSelected ), NULL, this );
	chkRotateSlot->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainFrame::rotateSlotSelected ), NULL, this );
	chkOverwriteBat->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainFrame::overwriteBatSelected ), NULL, this );
	btnSaveState->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::saveStatePressed ), NULL, this );
	btnLoadState->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::loadStatePressed ), NULL, this );
	btnLoadLastState->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::loadLastPressed ), NULL, this );
	btnP1Up->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1Left->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1Right->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1Down->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1Select->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1Start->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1B->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP1A->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Up->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Left->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Right->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Down->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Select->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2Start->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2B->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnP2A->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyPause->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyAdvanceFrame->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyCaptureScreen->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyToggleContScrCap->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySaveState->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyLoadState->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyLoadLastState->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyRotateState->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot6->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot7->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot9->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeySlot10->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyHDCapFrame->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyToogleAutoHDCap->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	btnKeyToogleIgnoreEdge->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::configKeyClicked ), NULL, this );
	rbnScreenSize->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( mainFrame::screenSizeSelected ), NULL, this );
	spnContCapRate->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainFrame::contCapRateSelected ), NULL, this );
	chkUseHDGraphicsPack->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainFrame::useGPackSelected ), NULL, this );
	chkGenHDData->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainFrame::autoCaptureForHDSelected ), NULL, this );
	chkIgnoreEdge->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainFrame::ignoreEdgeSelected ), NULL, this );
	
}

frmWaitInput::frmWaitInput( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_BTNFACE ) );
	
	wxBoxSizer* bSizer32;
	bSizer32 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText48 = new wxStaticText( this, wxID_ANY, wxT("Waiting for input. Can be a key press or input from joystick. Press Esc to cancel."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( 250 );
	bSizer32->Add( m_staticText48, 0, wxALL, 5 );
	
	
	this->SetSizer( bSizer32 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

frmWaitInput::~frmWaitInput()
{
}
