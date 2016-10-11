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
	rbnCurrentSlot = new wxRadioBox( m_panel1, wxID_ANY, wxT("Current state slot"), wxDefaultPosition, wxDefaultSize, rbnCurrentSlotNChoices, rbnCurrentSlotChoices, 1, wxRA_SPECIFY_ROWS );
	rbnCurrentSlot->SetSelection( 0 );
	bSizer2->Add( rbnCurrentSlot, 0, wxALL, 5 );
	
	chkRotateSlot = new wxCheckBox( m_panel1, wxID_ANY, wxT("Automatically rotate current slot after each time the game state is saved"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( chkRotateSlot, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	btnSaveState = new wxButton( m_panel1, wxID_ANY, wxT("Save state"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( btnSaveState, 0, wxALL, 5 );
	
	btnLoadState = new wxButton( m_panel1, wxID_ANY, wxT("Load state"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( btnLoadState, 0, wxALL, 5 );
	
	btnLoadLastState = new wxButton( m_panel1, wxID_ANY, wxT("Load state from the last state slot saved"), wxDefaultPosition, wxDefaultSize, 0 );
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
	
	wxArrayString m_choice1Choices;
	m_choice1 = new wxChoice( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	bSizer13->Add( m_choice1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
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
	
	wxArrayString m_choice2Choices;
	m_choice2 = new wxChoice( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice2Choices, 0 );
	m_choice2->SetSelection( 0 );
	bSizer12->Add( m_choice2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText4 = new wxStaticText( m_panel8, wxID_ANY, wxT("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer12->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice3Choices;
	m_choice3 = new wxChoice( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice3Choices, 0 );
	m_choice3->SetSelection( 0 );
	bSizer12->Add( m_choice3, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer9->Add( bSizer12, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	m_panel6 = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText9 = new wxStaticText( m_panel6, wxID_ANY, wxT("Down"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer15->Add( m_staticText9, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice8Choices;
	m_choice8 = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice8Choices, 0 );
	m_choice8->SetSelection( 0 );
	bSizer15->Add( m_choice8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
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
	
	wxArrayString m_choice4Choices;
	m_choice4 = new wxChoice( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice4Choices, 0 );
	m_choice4->SetSelection( 0 );
	fgSizer1->Add( m_choice4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText6 = new wxStaticText( m_panel7, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer1->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice5Choices;
	m_choice5 = new wxChoice( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice5Choices, 0 );
	m_choice5->SetSelection( 0 );
	fgSizer1->Add( m_choice5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText7 = new wxStaticText( m_panel7, wxID_ANY, wxT("B"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer1->Add( m_staticText7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice6Choices;
	m_choice6 = new wxChoice( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice6Choices, 0 );
	m_choice6->SetSelection( 0 );
	fgSizer1->Add( m_choice6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText8 = new wxStaticText( m_panel7, wxID_ANY, wxT("A"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer1->Add( m_staticText8, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice7Choices;
	m_choice7 = new wxChoice( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice7Choices, 0 );
	m_choice7->SetSelection( 0 );
	fgSizer1->Add( m_choice7, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	m_panel7->SetSizer( fgSizer1 );
	m_panel7->Layout();
	fgSizer1->Fit( m_panel7 );
	bSizer10->Add( m_panel7, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer6->Add( bSizer10, 0, wxEXPAND, 5 );
	
	
	bSizer22->Add( bSizer6, 0, wxEXPAND, 5 );
	
	
	m_panel8->SetSizer( bSizer22 );
	m_panel8->Layout();
	bSizer22->Fit( m_panel8 );
	bSizer5->Add( m_panel8, 0, wxEXPAND | wxALL, 5 );
	
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
	
	wxArrayString m_choice11Choices;
	m_choice11 = new wxChoice( m_panel51, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice11Choices, 0 );
	m_choice11->SetSelection( 0 );
	bSizer131->Add( m_choice11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
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
	
	wxArrayString m_choice21Choices;
	m_choice21 = new wxChoice( m_panel81, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice21Choices, 0 );
	m_choice21->SetSelection( 0 );
	bSizer121->Add( m_choice21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText41 = new wxStaticText( m_panel81, wxID_ANY, wxT("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer121->Add( m_staticText41, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice31Choices;
	m_choice31 = new wxChoice( m_panel81, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice31Choices, 0 );
	m_choice31->SetSelection( 0 );
	bSizer121->Add( m_choice31, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer91->Add( bSizer121, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer141;
	bSizer141 = new wxBoxSizer( wxVERTICAL );
	
	m_panel61 = new wxPanel( m_panel81, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer151;
	bSizer151 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText91 = new wxStaticText( m_panel61, wxID_ANY, wxT("Down"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText91->Wrap( -1 );
	bSizer151->Add( m_staticText91, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice81Choices;
	m_choice81 = new wxChoice( m_panel61, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice81Choices, 0 );
	m_choice81->SetSelection( 0 );
	bSizer151->Add( m_choice81, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
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
	
	wxArrayString m_choice41Choices;
	m_choice41 = new wxChoice( m_panel71, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice41Choices, 0 );
	m_choice41->SetSelection( 0 );
	fgSizer11->Add( m_choice41, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText61 = new wxStaticText( m_panel71, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	fgSizer11->Add( m_staticText61, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice51Choices;
	m_choice51 = new wxChoice( m_panel71, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice51Choices, 0 );
	m_choice51->SetSelection( 0 );
	fgSizer11->Add( m_choice51, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText71 = new wxStaticText( m_panel71, wxID_ANY, wxT("B"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText71->Wrap( -1 );
	fgSizer11->Add( m_staticText71, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice61Choices;
	m_choice61 = new wxChoice( m_panel71, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice61Choices, 0 );
	m_choice61->SetSelection( 0 );
	fgSizer11->Add( m_choice61, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText81 = new wxStaticText( m_panel71, wxID_ANY, wxT("A"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText81->Wrap( -1 );
	fgSizer11->Add( m_staticText81, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice71Choices;
	m_choice71 = new wxChoice( m_panel71, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice71Choices, 0 );
	m_choice71->SetSelection( 0 );
	fgSizer11->Add( m_choice71, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
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
	
	
	m_panel4->SetSizer( bSizer5 );
	m_panel4->Layout();
	bSizer5->Fit( m_panel4 );
	m_notebook1->AddPage( m_panel4, wxT("Gamepad"), false );
	m_panel13 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer25;
	bSizer25 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText24 = new wxStaticText( m_panel13, wxID_ANY, wxT("Pause/resume"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer3->Add( m_staticText24, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice37Choices;
	m_choice37 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice37Choices, 0 );
	m_choice37->SetSelection( 0 );
	fgSizer3->Add( m_choice37, 0, wxALL, 5 );
	
	m_staticText25 = new wxStaticText( m_panel13, wxID_ANY, wxT("Advance by 1 frame"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( 100 );
	fgSizer3->Add( m_staticText25, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice22Choices;
	m_choice22 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice22Choices, 0 );
	m_choice22->SetSelection( 0 );
	fgSizer3->Add( m_choice22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText26 = new wxStaticText( m_panel13, wxID_ANY, wxT("Capture screen"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( 100 );
	fgSizer3->Add( m_staticText26, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice23Choices;
	m_choice23 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice23Choices, 0 );
	m_choice23->SetSelection( 0 );
	fgSizer3->Add( m_choice23, 0, wxALL, 5 );
	
	m_staticText27 = new wxStaticText( m_panel13, wxID_ANY, wxT("Toggle continuous screen capture"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( 100 );
	fgSizer3->Add( m_staticText27, 0, wxALL, 5 );
	
	wxArrayString m_choice24Choices;
	m_choice24 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice24Choices, 0 );
	m_choice24->SetSelection( 0 );
	fgSizer3->Add( m_choice24, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText411 = new wxStaticText( m_panel13, wxID_ANY, wxT("Stop emulation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText411->Wrap( -1 );
	fgSizer3->Add( m_staticText411, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice211Choices;
	m_choice211 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice211Choices, 0 );
	m_choice211->SetSelection( 0 );
	fgSizer3->Add( m_choice211, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer25->Add( fgSizer3, 0, wxEXPAND, 5 );
	
	m_staticline1 = new wxStaticLine( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer25->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText20 = new wxStaticText( m_panel13, wxID_ANY, wxT("Save state"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer5->Add( m_staticText20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice17Choices;
	m_choice17 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice17Choices, 0 );
	m_choice17->SetSelection( 0 );
	fgSizer5->Add( m_choice17, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText211 = new wxStaticText( m_panel13, wxID_ANY, wxT("Load state"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	fgSizer5->Add( m_staticText211, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice18Choices;
	m_choice18 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice18Choices, 0 );
	m_choice18->SetSelection( 0 );
	fgSizer5->Add( m_choice18, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText22 = new wxStaticText( m_panel13, wxID_ANY, wxT("Load last state saved"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( 100 );
	fgSizer5->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice19Choices;
	m_choice19 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice19Choices, 0 );
	m_choice19->SetSelection( 0 );
	fgSizer5->Add( m_choice19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText23 = new wxStaticText( m_panel13, wxID_ANY, wxT("Rotate to next state slot"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( 100 );
	fgSizer5->Add( m_staticText23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice20Choices;
	m_choice20 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice20Choices, 0 );
	m_choice20->SetSelection( 0 );
	fgSizer5->Add( m_choice20, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer25->Add( fgSizer5, 1, wxEXPAND, 5 );
	
	
	bSizer24->Add( bSizer25, 0, wxEXPAND, 5 );
	
	m_staticline2 = new wxStaticLine( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_VERTICAL );
	bSizer24->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText28 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	fgSizer4->Add( m_staticText28, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice25Choices;
	m_choice25 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice25Choices, 0 );
	m_choice25->SetSelection( 0 );
	fgSizer4->Add( m_choice25, 0, wxALL, 5 );
	
	m_staticText29 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	fgSizer4->Add( m_staticText29, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice26Choices;
	m_choice26 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice26Choices, 0 );
	m_choice26->SetSelection( 0 );
	fgSizer4->Add( m_choice26, 0, wxALL, 5 );
	
	m_staticText30 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 3"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer4->Add( m_staticText30, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice27Choices;
	m_choice27 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice27Choices, 0 );
	m_choice27->SetSelection( 0 );
	fgSizer4->Add( m_choice27, 0, wxALL, 5 );
	
	m_staticText311 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 4"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText311->Wrap( -1 );
	fgSizer4->Add( m_staticText311, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice28Choices;
	m_choice28 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice28Choices, 0 );
	m_choice28->SetSelection( 0 );
	fgSizer4->Add( m_choice28, 0, wxALL, 5 );
	
	m_staticText32 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 5"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer4->Add( m_staticText32, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice29Choices;
	m_choice29 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice29Choices, 0 );
	m_choice29->SetSelection( 0 );
	fgSizer4->Add( m_choice29, 0, wxALL, 5 );
	
	m_staticText33 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 6"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	fgSizer4->Add( m_staticText33, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice30Choices;
	m_choice30 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice30Choices, 0 );
	m_choice30->SetSelection( 0 );
	fgSizer4->Add( m_choice30, 0, wxALL, 5 );
	
	m_staticText34 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 7"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	fgSizer4->Add( m_staticText34, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice311Choices;
	m_choice311 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice311Choices, 0 );
	m_choice311->SetSelection( 0 );
	fgSizer4->Add( m_choice311, 0, wxALL, 5 );
	
	m_staticText35 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 8"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer4->Add( m_staticText35, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice32Choices;
	m_choice32 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice32Choices, 0 );
	m_choice32->SetSelection( 0 );
	fgSizer4->Add( m_choice32, 0, wxALL, 5 );
	
	m_staticText36 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 9"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	fgSizer4->Add( m_staticText36, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice33Choices;
	m_choice33 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice33Choices, 0 );
	m_choice33->SetSelection( 0 );
	fgSizer4->Add( m_choice33, 0, wxALL, 5 );
	
	m_staticText37 = new wxStaticText( m_panel13, wxID_ANY, wxT("State slot 10"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	fgSizer4->Add( m_staticText37, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice34Choices;
	m_choice34 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice34Choices, 0 );
	m_choice34->SetSelection( 0 );
	fgSizer4->Add( m_choice34, 0, wxALL, 5 );
	
	
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
	
	wxArrayString m_choice35Choices;
	m_choice35 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice35Choices, 0 );
	m_choice35->SetSelection( 0 );
	fgSizer6->Add( m_choice35, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText39 = new wxStaticText( m_panel13, wxID_ANY, wxT("Toggle automatic frame data capture"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( 100 );
	fgSizer6->Add( m_staticText39, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice36Choices;
	m_choice36 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice36Choices, 0 );
	m_choice36->SetSelection( 0 );
	fgSizer6->Add( m_choice36, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText44 = new wxStaticText( m_panel13, wxID_ANY, wxT("Toggle ignore graphics near the edge of the screen"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( 100 );
	fgSizer6->Add( m_staticText44, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	wxArrayString m_choice38Choices;
	m_choice38 = new wxChoice( m_panel13, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice38Choices, 0 );
	m_choice38->SetSelection( 0 );
	fgSizer6->Add( m_choice38, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
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
	
	wxString m_radioBox2Choices[] = { wxT("1x"), wxT("2x"), wxT("4x") };
	int m_radioBox2NChoices = sizeof( m_radioBox2Choices ) / sizeof( wxString );
	m_radioBox2 = new wxRadioBox( m_panel2, wxID_ANY, wxT("Screen size"), wxDefaultPosition, wxDefaultSize, m_radioBox2NChoices, m_radioBox2Choices, 1, wxRA_SPECIFY_ROWS );
	m_radioBox2->SetSelection( 0 );
	bSizer27->Add( m_radioBox2, 0, wxALL, 5 );
	
	
	bSizer26->Add( bSizer27, 0, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText42 = new wxStaticText( m_panel2, wxID_ANY, wxT(" Rate of continuous screen capture: 1 screen in every"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	bSizer28->Add( m_staticText42, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_spinCtrl1 = new wxSpinCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 300, 5 );
	bSizer28->Add( m_spinCtrl1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	m_staticText43 = new wxStaticText( m_panel2, wxID_ANY, wxT("frame(s)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	bSizer28->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer26->Add( bSizer28, 0, wxEXPAND, 5 );
	
	m_checkBox2 = new wxCheckBox( m_panel2, wxID_ANY, wxT("Use HD graphics pack when available "), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( m_checkBox2, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );
	
	m_checkBox3 = new wxCheckBox( m_panel2, wxID_ANY, wxT("Automatically capture frame data for making HD graphics pack"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer29->Add( m_checkBox3, 0, wxALL, 5 );
	
	m_checkBox5 = new wxCheckBox( m_panel2, wxID_ANY, wxT("CHR-ROM games"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer29->Add( m_checkBox5, 0, wxALL, 5 );
	
	m_checkBox6 = new wxCheckBox( m_panel2, wxID_ANY, wxT("CHR-RAM games"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer29->Add( m_checkBox6, 0, wxALL, 5 );
	
	
	bSizer26->Add( bSizer29, 0, wxEXPAND, 5 );
	
	m_checkBox4 = new wxCheckBox( m_panel2, wxID_ANY, wxT("Ignore graphics near the edge of the screen"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( m_checkBox4, 0, wxALL, 5 );
	
	
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
	
	m_slider1 = new wxSlider( m_panel3, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_BOTTOM|wxSL_HORIZONTAL|wxSL_LABELS );
	m_slider1->SetMinSize( wxSize( 200,-1 ) );
	
	bSizer31->Add( m_slider1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer30->Add( bSizer31, 0, wxEXPAND, 5 );
	
	m_checkBox21 = new wxCheckBox( m_panel3, wxID_ANY, wxT("Use HD music pack when available "), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer30->Add( m_checkBox21, 0, wxALL, 5 );
	
	
	m_panel3->SetSizer( bSizer30 );
	m_panel3->Layout();
	bSizer30->Fit( m_panel3 );
	m_notebook1->AddPage( m_panel3, wxT("Audio"), false );
	
	bSizer1->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	btnStart->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::startGame ), NULL, this );
}

mainFrame::~mainFrame()
{
	// Disconnect Events
	btnStart->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainFrame::startGame ), NULL, this );
	
}
