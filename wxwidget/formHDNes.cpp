///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "formHDNes.h"

///////////////////////////////////////////////////////////////////////////

fraHDNes::fraHDNes( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_notebook2 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	panBasic1 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText5 = new wxStaticText( panBasic1, wxID_ANY, wxT("Game ROM file"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer51->Add( m_staticText5, 1, wxALL, 5 );
	
	m_filePicker1 = new wxFilePickerCtrl( panBasic1, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE );
	bSizer51->Add( m_filePicker1, 5, wxALL, 5 );
	
	
	bSizer2->Add( bSizer51, 1, 0, 5 );
	
	m_button2 = new wxButton( panBasic1, wxID_ANY, wxT("Start game"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( m_button2, 0, wxALL, 5 );
	
	
	panBasic1->SetSizer( bSizer2 );
	panBasic1->Layout();
	bSizer2->Fit( panBasic1 );
	m_notebook2->AddPage( panBasic1, wxT("General"), true );
	m_panel6 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText6 = new wxStaticText( m_panel6, wxID_ANY, wxT("Player 1"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer9->Add( m_staticText6, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer44;
	bSizer44 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP1 = new wxStaticText( m_panel6, wxID_ANY, wxT("Up"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP1->Wrap( -1 );
	lblP1->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer11->Add( lblP1, 0, wxALL, 5 );
	
	wxArrayString cbo1UPChoices;
	cbo1UP = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo1UPChoices, 0 );
	cbo1UP->SetSelection( 0 );
	bSizer11->Add( cbo1UP, 0, wxALL, 5 );
	
	
	bSizer44->Add( bSizer11, 1, 0, 5 );
	
	wxBoxSizer* bSizer111;
	bSizer111 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP11 = new wxStaticText( m_panel6, wxID_ANY, wxT("Down"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP11->Wrap( -1 );
	lblP11->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer111->Add( lblP11, 0, wxALL, 5 );
	
	wxArrayString cbo1DOWNChoices;
	cbo1DOWN = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo1DOWNChoices, 0 );
	cbo1DOWN->SetSelection( 0 );
	bSizer111->Add( cbo1DOWN, 0, wxALL, 5 );
	
	
	bSizer44->Add( bSizer111, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer112;
	bSizer112 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP12 = new wxStaticText( m_panel6, wxID_ANY, wxT("Left"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP12->Wrap( -1 );
	lblP12->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer112->Add( lblP12, 0, wxALL, 5 );
	
	wxArrayString cbo1LEFTChoices;
	cbo1LEFT = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo1LEFTChoices, 0 );
	cbo1LEFT->SetSelection( 0 );
	bSizer112->Add( cbo1LEFT, 0, wxALL, 5 );
	
	
	bSizer44->Add( bSizer112, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1121;
	bSizer1121 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP121 = new wxStaticText( m_panel6, wxID_ANY, wxT("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP121->Wrap( -1 );
	lblP121->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer1121->Add( lblP121, 0, wxALL, 5 );
	
	wxArrayString cbo1RIGHTChoices;
	cbo1RIGHT = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo1RIGHTChoices, 0 );
	cbo1RIGHT->SetSelection( 0 );
	bSizer1121->Add( cbo1RIGHT, 0, wxALL, 5 );
	
	
	bSizer44->Add( bSizer1121, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1122;
	bSizer1122 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP122 = new wxStaticText( m_panel6, wxID_ANY, wxT("A"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP122->Wrap( -1 );
	lblP122->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer1122->Add( lblP122, 0, wxALL, 5 );
	
	wxArrayString cbo1AChoices;
	cbo1A = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo1AChoices, 0 );
	cbo1A->SetSelection( 0 );
	bSizer1122->Add( cbo1A, 0, wxALL, 5 );
	
	
	bSizer44->Add( bSizer1122, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1123;
	bSizer1123 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP123 = new wxStaticText( m_panel6, wxID_ANY, wxT("B"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP123->Wrap( -1 );
	lblP123->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer1123->Add( lblP123, 0, wxALL, 5 );
	
	wxArrayString cbo1BChoices;
	cbo1B = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo1BChoices, 0 );
	cbo1B->SetSelection( 0 );
	bSizer1123->Add( cbo1B, 0, wxALL, 5 );
	
	
	bSizer44->Add( bSizer1123, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1124;
	bSizer1124 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP124 = new wxStaticText( m_panel6, wxID_ANY, wxT("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP124->Wrap( -1 );
	lblP124->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer1124->Add( lblP124, 0, wxALL, 5 );
	
	wxArrayString cbo1SELECTChoices;
	cbo1SELECT = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo1SELECTChoices, 0 );
	cbo1SELECT->SetSelection( 0 );
	bSizer1124->Add( cbo1SELECT, 0, wxALL, 5 );
	
	
	bSizer44->Add( bSizer1124, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1125;
	bSizer1125 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP125 = new wxStaticText( m_panel6, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP125->Wrap( -1 );
	lblP125->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer1125->Add( lblP125, 0, wxALL, 5 );
	
	wxArrayString cbo1STARTChoices;
	cbo1START = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo1STARTChoices, 0 );
	cbo1START->SetSelection( 0 );
	bSizer1125->Add( cbo1START, 0, wxALL, 5 );
	
	
	bSizer44->Add( bSizer1125, 1, wxEXPAND, 5 );
	
	
	bSizer9->Add( bSizer44, 1, wxEXPAND, 5 );
	
	
	bSizer8->Add( bSizer9, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText7 = new wxStaticText( m_panel6, wxID_ANY, wxT("Player 2"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer10->Add( m_staticText7, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer1126;
	bSizer1126 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP126 = new wxStaticText( m_panel6, wxID_ANY, wxT("Up"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP126->Wrap( -1 );
	lblP126->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer1126->Add( lblP126, 0, wxALL, 5 );
	
	wxArrayString cbo2UPChoices;
	cbo2UP = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo2UPChoices, 0 );
	cbo2UP->SetSelection( 0 );
	bSizer1126->Add( cbo2UP, 0, wxALL, 5 );
	
	
	bSizer43->Add( bSizer1126, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1127;
	bSizer1127 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP127 = new wxStaticText( m_panel6, wxID_ANY, wxT("Down"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP127->Wrap( -1 );
	lblP127->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer1127->Add( lblP127, 0, wxALL, 5 );
	
	wxArrayString cbo2DOWNChoices;
	cbo2DOWN = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo2DOWNChoices, 0 );
	cbo2DOWN->SetSelection( 0 );
	bSizer1127->Add( cbo2DOWN, 0, wxALL, 5 );
	
	
	bSizer43->Add( bSizer1127, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1128;
	bSizer1128 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP128 = new wxStaticText( m_panel6, wxID_ANY, wxT("Left"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP128->Wrap( -1 );
	lblP128->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer1128->Add( lblP128, 0, wxALL, 5 );
	
	wxArrayString cbo2LEFTChoices;
	cbo2LEFT = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo2LEFTChoices, 0 );
	cbo2LEFT->SetSelection( 0 );
	bSizer1128->Add( cbo2LEFT, 0, wxALL, 5 );
	
	
	bSizer43->Add( bSizer1128, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1129;
	bSizer1129 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP129 = new wxStaticText( m_panel6, wxID_ANY, wxT("Right"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP129->Wrap( -1 );
	lblP129->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer1129->Add( lblP129, 0, wxALL, 5 );
	
	wxArrayString cbo2RIGHTChoices;
	cbo2RIGHT = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo2RIGHTChoices, 0 );
	cbo2RIGHT->SetSelection( 0 );
	bSizer1129->Add( cbo2RIGHT, 0, wxALL, 5 );
	
	
	bSizer43->Add( bSizer1129, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11210;
	bSizer11210 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP1210 = new wxStaticText( m_panel6, wxID_ANY, wxT("A"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP1210->Wrap( -1 );
	lblP1210->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer11210->Add( lblP1210, 0, wxALL, 5 );
	
	wxArrayString cbo2AChoices;
	cbo2A = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo2AChoices, 0 );
	cbo2A->SetSelection( 0 );
	bSizer11210->Add( cbo2A, 0, wxALL, 5 );
	
	
	bSizer43->Add( bSizer11210, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11211;
	bSizer11211 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP1211 = new wxStaticText( m_panel6, wxID_ANY, wxT("B"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP1211->Wrap( -1 );
	lblP1211->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer11211->Add( lblP1211, 0, wxALL, 5 );
	
	wxArrayString cbo2BChoices;
	cbo2B = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo2BChoices, 0 );
	cbo2B->SetSelection( 0 );
	bSizer11211->Add( cbo2B, 0, wxALL, 5 );
	
	
	bSizer43->Add( bSizer11211, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11212;
	bSizer11212 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP1212 = new wxStaticText( m_panel6, wxID_ANY, wxT("Select"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP1212->Wrap( -1 );
	lblP1212->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer11212->Add( lblP1212, 0, wxALL, 5 );
	
	wxArrayString cbo2SELECTChoices;
	cbo2SELECT = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo2SELECTChoices, 0 );
	cbo2SELECT->SetSelection( 0 );
	bSizer11212->Add( cbo2SELECT, 0, wxALL, 5 );
	
	
	bSizer43->Add( bSizer11212, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11213;
	bSizer11213 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP1213 = new wxStaticText( m_panel6, wxID_ANY, wxT("Start"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP1213->Wrap( -1 );
	lblP1213->SetMinSize( wxSize( 50,-1 ) );
	
	bSizer11213->Add( lblP1213, 0, wxALL, 5 );
	
	wxArrayString cbo2STARTChoices;
	cbo2START = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cbo2STARTChoices, 0 );
	cbo2START->SetSelection( 0 );
	bSizer11213->Add( cbo2START, 0, wxALL, 5 );
	
	
	bSizer43->Add( bSizer11213, 1, wxEXPAND, 5 );
	
	
	bSizer10->Add( bSizer43, 1, wxEXPAND, 5 );
	
	
	bSizer8->Add( bSizer10, 1, wxEXPAND, 5 );
	
	
	bSizer6->Add( bSizer8, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText8 = new wxStaticText( m_panel6, wxID_ANY, wxT("Special keys"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer7->Add( m_staticText8, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer432;
	bSizer432 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer115;
	bSizer115 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP14 = new wxStaticText( m_panel6, wxID_ANY, wxT("End game"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP14->Wrap( -1 );
	lblP14->SetMinSize( wxSize( 80,-1 ) );
	
	bSizer115->Add( lblP14, 0, wxALL, 5 );
	
	wxArrayString cboEndGameChoices;
	cboEndGame = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboEndGameChoices, 0 );
	cboEndGame->SetSelection( 0 );
	bSizer115->Add( cboEndGame, 0, wxALL, 5 );
	
	
	bSizer432->Add( bSizer115, 2, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer113;
	bSizer113 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP13 = new wxStaticText( m_panel6, wxID_ANY, wxT("Save state"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP13->Wrap( -1 );
	lblP13->SetMinSize( wxSize( 80,-1 ) );
	
	bSizer113->Add( lblP13, 0, wxALL, 5 );
	
	wxArrayString cboSaveStateChoices;
	cboSaveState = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboSaveStateChoices, 0 );
	cboSaveState->SetSelection( 0 );
	bSizer113->Add( cboSaveState, 0, wxALL, 5 );
	
	
	bSizer432->Add( bSizer113, 2, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer114;
	bSizer114 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP15 = new wxStaticText( m_panel6, wxID_ANY, wxT("Load state"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP15->Wrap( -1 );
	lblP15->SetMinSize( wxSize( 80,-1 ) );
	
	bSizer114->Add( lblP15, 0, wxALL, 5 );
	
	wxArrayString cboLoadStateChoices;
	cboLoadState = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboLoadStateChoices, 0 );
	cboLoadState->SetSelection( 0 );
	bSizer114->Add( cboLoadState, 0, wxALL, 5 );
	
	
	bSizer432->Add( bSizer114, 2, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1141;
	bSizer1141 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP151 = new wxStaticText( m_panel6, wxID_ANY, wxT("Screen capture"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP151->Wrap( -1 );
	lblP151->SetMinSize( wxSize( 80,-1 ) );
	
	bSizer1141->Add( lblP151, 0, wxALL, 5 );
	
	wxArrayString cboScreenCapChoices;
	cboScreenCap = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboScreenCapChoices, 0 );
	cboScreenCap->SetSelection( 0 );
	bSizer1141->Add( cboScreenCap, 0, wxALL, 5 );
	
	
	bSizer432->Add( bSizer1141, 2, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer11411;
	bSizer11411 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP1511 = new wxStaticText( m_panel6, wxID_ANY, wxT("Generate data"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP1511->Wrap( 80 );
	lblP1511->SetToolTip( wxT("Export the data of current frame to the graphics pack editor. Only available to manual mode.") );
	lblP1511->SetMinSize( wxSize( 80,-1 ) );
	
	bSizer11411->Add( lblP1511, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxArrayString cboDataCapChoices;
	cboDataCap = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboDataCapChoices, 0 );
	cboDataCap->SetSelection( 0 );
	cboDataCap->SetToolTip( wxT("Export the data of current frame to the graphics pack editor. Only available to manual mode.") );
	
	bSizer11411->Add( cboDataCap, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer432->Add( bSizer11411, 2, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer114111;
	bSizer114111 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP15111 = new wxStaticText( m_panel6, wxID_ANY, wxT("Pause"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP15111->Wrap( 80 );
	lblP15111->SetToolTip( wxT("Pause and unpause the game") );
	lblP15111->SetMinSize( wxSize( 80,-1 ) );
	
	bSizer114111->Add( lblP15111, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxArrayString cboPauseChoices;
	cboPause = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboPauseChoices, 0 );
	cboPause->SetSelection( 0 );
	cboPause->SetToolTip( wxT("Pause and unpause the game") );
	
	bSizer114111->Add( cboPause, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer432->Add( bSizer114111, 2, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer114112;
	bSizer114112 = new wxBoxSizer( wxHORIZONTAL );
	
	lblP15112 = new wxStaticText( m_panel6, wxID_ANY, wxT("Run frame"), wxDefaultPosition, wxDefaultSize, 0 );
	lblP15112->Wrap( 80 );
	lblP15112->SetToolTip( wxT("Run 1 frame and pause the game. ") );
	lblP15112->SetMinSize( wxSize( 80,-1 ) );
	
	bSizer114112->Add( lblP15112, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxArrayString cboRunFrameChoices;
	cboRunFrame = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboRunFrameChoices, 0 );
	cboRunFrame->SetSelection( 0 );
	bSizer114112->Add( cboRunFrame, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer432->Add( bSizer114112, 2, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer82;
	bSizer82 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText62 = new wxStaticText( m_panel6, wxID_ANY, wxT("Cont. sc capture"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText62->Wrap( 80 );
	m_staticText62->SetMinSize( wxSize( 80,-1 ) );
	
	bSizer82->Add( m_staticText62, 0, wxALL, 5 );
	
	wxArrayString cboContCapChoices;
	cboContCap = new wxChoice( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboContCapChoices, 0 );
	cboContCap->SetSelection( 0 );
	bSizer82->Add( cboContCap, 0, wxALL, 5 );
	
	
	bSizer432->Add( bSizer82, 1, wxEXPAND, 5 );
	
	
	bSizer432->Add( 0, 0, 2, wxEXPAND, 5 );
	
	
	bSizer432->Add( 0, 0, 2, wxEXPAND, 5 );
	
	
	bSizer432->Add( 0, 0, 2, wxEXPAND, 5 );
	
	
	bSizer432->Add( 0, 0, 2, wxEXPAND, 5 );
	
	
	bSizer432->Add( 0, 0, 2, wxEXPAND, 5 );
	
	
	bSizer432->Add( 0, 0, 2, wxEXPAND, 5 );
	
	
	bSizer432->Add( 0, 0, 2, wxEXPAND, 5 );
	
	
	bSizer432->Add( 0, 0, 2, wxEXPAND, 5 );
	
	
	bSizer7->Add( bSizer432, 1, wxEXPAND, 5 );
	
	
	bSizer6->Add( bSizer7, 1, wxEXPAND, 5 );
	
	
	m_panel6->SetSizer( bSizer6 );
	m_panel6->Layout();
	bSizer6->Fit( m_panel6 );
	m_notebook2->AddPage( m_panel6, wxT("Input"), false );
	panVideo1 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( panVideo1, wxID_ANY, wxT("Screen size:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer5->Add( m_staticText1, 0, wxALL, 5 );
	
	m_radioBtn1 = new wxRadioButton( panVideo1, wxID_ANY, wxT("1x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioBtn1->SetValue( true ); 
	bSizer5->Add( m_radioBtn1, 0, wxALL, 5 );
	
	m_radioBtn2 = new wxRadioButton( panVideo1, wxID_ANY, wxT("2x"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_radioBtn2, 0, wxALL, 5 );
	
	m_radioBtn3 = new wxRadioButton( panVideo1, wxID_ANY, wxT("4x"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioBtn3->SetValue( true ); 
	bSizer5->Add( m_radioBtn3, 0, wxALL, 5 );
	
	m_radioBtn4 = new wxRadioButton( panVideo1, wxID_ANY, wxT("Custom"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( m_radioBtn4, 0, wxALL, 5 );
	
	m_staticText2 = new wxStaticText( panVideo1, wxID_ANY, wxT("width"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer5->Add( m_staticText2, 0, wxALL, 5 );
	
	txtwidth = new wxTextCtrl( panVideo1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	txtwidth->SetMaxLength( 0 ); 
	bSizer5->Add( txtwidth, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( panVideo1, wxID_ANY, wxT("X"), wxDefaultPosition, wxSize( 10,-1 ), wxALIGN_CENTRE );
	m_staticText4->Wrap( -1 );
	bSizer5->Add( m_staticText4, 0, wxALL, 5 );
	
	m_staticText3 = new wxStaticText( panVideo1, wxID_ANY, wxT("height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer5->Add( m_staticText3, 0, wxALL, 5 );
	
	txtheight = new wxTextCtrl( panVideo1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	txtheight->SetMaxLength( 0 ); 
	bSizer5->Add( txtheight, 0, wxALL, 5 );
	
	
	bSizer3->Add( bSizer5, 1, wxEXPAND, 5 );
	
	chkUsePack = new wxCheckBox( panVideo1, wxID_ANY, wxT("Use graphics pack"), wxDefaultPosition, wxDefaultSize, 0 );
	chkUsePack->SetValue(true); 
	bSizer3->Add( chkUsePack, 0, wxALL, 5 );
	
	wxString rbxGenerateDataChoices[] = { wxT("Automatic"), wxT("Manual"), wxT("None") };
	int rbxGenerateDataNChoices = sizeof( rbxGenerateDataChoices ) / sizeof( wxString );
	rbxGenerateData = new wxRadioBox( panVideo1, wxID_ANY, wxT("Generate data for graphics pack editor"), wxDefaultPosition, wxDefaultSize, rbxGenerateDataNChoices, rbxGenerateDataChoices, 1, wxRA_SPECIFY_COLS );
	rbxGenerateData->SetSelection( 0 );
	bSizer3->Add( rbxGenerateData, 0, wxALL, 5 );
	
	chkNearEdge = new wxCheckBox( panVideo1, wxID_ANY, wxT("Ignore tiles near the edge of the screen when generating data"), wxDefaultPosition, wxDefaultSize, 0 );
	chkNearEdge->SetValue(true); 
	chkNearEdge->SetToolTip( wxT("Useful for games which display garbage tiles along the edge of the screen") );
	
	bSizer3->Add( chkNearEdge, 0, wxALL, 5 );
	
	chkCHRRamEdit = new wxCheckBox( panVideo1, wxID_ANY, wxT("Do not use address matching and data generation for CHR RAM game"), wxDefaultPosition, wxDefaultSize, 0 );
	chkCHRRamEdit->SetToolTip( wxT("Useful for games that modify the tile data before putting it into the CHR RAM") );
	
	bSizer3->Add( chkCHRRamEdit, 0, wxALL, 5 );
	
	
	panVideo1->SetSizer( bSizer3 );
	panVideo1->Layout();
	bSizer3->Fit( panVideo1 );
	m_notebook2->AddPage( panVideo1, wxT("Video"), false );
	panAudio1 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer771;
	bSizer771 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer79;
	bSizer79 = new wxBoxSizer( wxVERTICAL );
	
	
	bSizer771->Add( bSizer79, 5, wxEXPAND, 5 );
	
	chkUseAudioPack = new wxCheckBox( panAudio1, wxID_ANY, wxT("Use audio pack"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer771->Add( chkUseAudioPack, 0, wxALL, 5 );
	
	
	panAudio1->SetSizer( bSizer771 );
	panAudio1->Layout();
	bSizer771->Fit( panAudio1 );
	m_notebook2->AddPage( panAudio1, wxT("Audio"), false );
	m_panel7 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer341;
	bSizer341 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer39;
	bSizer39 = new wxBoxSizer( wxHORIZONTAL );
	
	btnLoadPack = new wxButton( m_panel7, wxID_ANY, wxT("Load pack data"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( btnLoadPack, 0, wxALL, 5 );
	
	btnSavePack = new wxButton( m_panel7, wxID_ANY, wxT("Save pack data"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( btnSavePack, 0, wxALL, 5 );
	
	m_staticText27 = new wxStaticText( m_panel7, wxID_ANY, wxT("Graphics pack scale"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	bSizer39->Add( m_staticText27, 0, wxALL, 5 );
	
	optPackScale1 = new wxRadioButton( m_panel7, wxID_ANY, wxT("1x"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( optPackScale1, 0, wxALL, 5 );
	
	optPackScale2 = new wxRadioButton( m_panel7, wxID_ANY, wxT("2x"), wxDefaultPosition, wxDefaultSize, 0 );
	optPackScale2->SetValue( true ); 
	bSizer39->Add( optPackScale2, 0, wxALL, 5 );
	
	optPackScale4 = new wxRadioButton( m_panel7, wxID_ANY, wxT("4x"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer39->Add( optPackScale4, 0, wxALL, 5 );
	
	
	bSizer341->Add( bSizer39, 0, 0, 5 );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText25 = new wxStaticText( m_panel7, wxID_ANY, wxT("Screen shot"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	bSizer31->Add( m_staticText25, 0, wxALL, 5 );
	
	wxArrayString cboScreenChoices;
	cboScreen = new wxChoice( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboScreenChoices, 0 );
	cboScreen->SetSelection( 0 );
	bSizer31->Add( cboScreen, 0, wxALL, 5 );
	
	btnOptimizeScreenEdit = new wxButton( m_panel7, wxID_ANY, wxT("Optimize"), wxDefaultPosition, wxDefaultSize, 0 );
	btnOptimizeScreenEdit->SetToolTip( wxT("Remove screen shots which all of its tiles can be found in other screens.") );
	
	bSizer31->Add( btnOptimizeScreenEdit, 0, wxALL, 5 );
	
	
	bSizer42->Add( bSizer31, 0, 0, 5 );
	
	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText32 = new wxStaticText( m_panel7, wxID_ANY, wxT("Tiles"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	bSizer46->Add( m_staticText32, 0, wxALL, 5 );
	
	lstScreenTiles = new wxListBox( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, wxLB_EXTENDED ); 
	lstScreenTiles->SetMinSize( wxSize( 200,200 ) );
	
	bSizer46->Add( lstScreenTiles, 1, wxALL, 5 );
	
	
	bSizer42->Add( bSizer46, 1, wxEXPAND, 5 );
	
	
	bSizer30->Add( bSizer42, 4, wxEXPAND, 5 );
	
	pnlScreen = new wxPanel( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer30->Add( pnlScreen, 3, wxALL|wxEXPAND, 5 );
	
	
	bSizer341->Add( bSizer30, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText31 = new wxStaticText( m_panel7, wxID_ANY, wxT("Map the selected tile to custom tile:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	bSizer37->Add( m_staticText31, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText26 = new wxStaticText( m_panel7, wxID_ANY, wxT("Image"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	bSizer34->Add( m_staticText26, 0, wxALL, 5 );
	
	wxArrayString cboImageChoices;
	cboImage = new wxChoice( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboImageChoices, 0 );
	cboImage->SetSelection( 0 );
	bSizer34->Add( cboImage, 0, wxALL, 5 );
	
	m_filePicker2 = new wxFilePickerCtrl( m_panel7, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.png"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	bSizer34->Add( m_filePicker2, 0, wxALL, 5 );
	
	btnRemoveImage = new wxButton( m_panel7, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer34->Add( btnRemoveImage, 0, wxALL, 5 );
	
	
	bSizer37->Add( bSizer34, 0, 0, 5 );
	
	wxBoxSizer* bSizer431;
	bSizer431 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText33 = new wxStaticText( m_panel7, wxID_ANY, wxT("Warning: adding a file with same name will overwrite the existing file"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	bSizer431->Add( m_staticText33, 0, wxALL, 5 );
	
	m_staticText28 = new wxStaticText( m_panel7, wxID_ANY, wxT("Tile location (Click on the image to select a tile)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	bSizer431->Add( m_staticText28, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText29 = new wxStaticText( m_panel7, wxID_ANY, wxT("X"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	bSizer38->Add( m_staticText29, 0, wxALL, 5 );
	
	txtMapX = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer38->Add( txtMapX, 0, wxALL, 5 );
	
	m_staticText30 = new wxStaticText( m_panel7, wxID_ANY, wxT("Y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	bSizer38->Add( m_staticText30, 0, wxALL, 5 );
	
	txtMapY = new wxTextCtrl( m_panel7, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer38->Add( txtMapY, 0, wxALL, 5 );
	
	m_staticText63 = new wxStaticText( m_panel7, wxID_ANY, wxT("Brightness"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText63->Wrap( -1 );
	bSizer38->Add( m_staticText63, 0, wxALL, 5 );
	
	txtBrightness = new wxTextCtrl( m_panel7, wxID_ANY, wxT("100"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer38->Add( txtBrightness, 0, wxALL, 5 );
	
	m_staticText64 = new wxStaticText( m_panel7, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText64->Wrap( -1 );
	bSizer38->Add( m_staticText64, 0, wxALL, 5 );
	
	
	bSizer431->Add( bSizer38, 1, 0, 5 );
	
	
	bSizer37->Add( bSizer431, 2, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );
	
	chkDefaultTile = new wxCheckBox( m_panel7, wxID_ANY, wxT("Use as default for this tile ID regardless of palette"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer40->Add( chkDefaultTile, 0, wxALL, 5 );
	
	
	bSizer37->Add( bSizer40, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	btnConfirmTile = new wxButton( m_panel7, wxID_ANY, wxT("Confirm selection"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer41->Add( btnConfirmTile, 0, wxALL, 5 );
	
	btnCancelSelection = new wxButton( m_panel7, wxID_ANY, wxT("Cancel selection"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer41->Add( btnCancelSelection, 0, wxALL, 5 );
	
	m_button6 = new wxButton( m_panel7, wxID_ANY, wxT("Auto generate"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button6->SetToolTip( wxT("If a screen shot is selected, 'Auto generate' will create one file with background tiles with matching positions. If 'All' is selected, 'Auto generate' will create files with tiles packed together.") );
	
	bSizer41->Add( m_button6, 0, wxALL, 5 );
	
	
	bSizer37->Add( bSizer41, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer511;
	bSizer511 = new wxBoxSizer( wxHORIZONTAL );
	
	btn_Swap = new wxButton( m_panel7, wxID_ANY, wxT("Batch mapping"), wxDefaultPosition, wxDefaultSize, 0 );
	btn_Swap->SetToolTip( wxT("Copy the mappings of a range of tiles and apply them to another location with a different palette. Useful for palette swap.") );
	
	bSizer511->Add( btn_Swap, 0, wxALL, 5 );
	
	btn_MapDarkPalette = new wxButton( m_panel7, wxID_ANY, wxT("Map dark palette"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer511->Add( btn_MapDarkPalette, 0, wxALL, 5 );
	
	btn_CustomizePalette = new wxButton( m_panel7, wxID_ANY, wxT("Customize palette"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer511->Add( btn_CustomizePalette, 0, wxALL, 5 );
	
	
	bSizer37->Add( bSizer511, 1, wxEXPAND, 5 );
	
	
	bSizer36->Add( bSizer37, 1, wxEXPAND, 5 );
	
	
	bSizer33->Add( bSizer36, 4, wxEXPAND, 5 );
	
	pnlImage = new wxPanel( m_panel7, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer33->Add( pnlImage, 3, wxEXPAND | wxALL, 5 );
	
	
	bSizer341->Add( bSizer33, 1, wxEXPAND, 5 );
	
	
	m_panel7->SetSizer( bSizer341 );
	m_panel7->Layout();
	bSizer341->Fit( m_panel7 );
	m_notebook2->AddPage( m_panel7, wxT("Graphics Pack Editor"), false );
	m_panel8 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer67;
	bSizer67 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxHORIZONTAL );
	
	btnLoadAudioPack = new wxButton( m_panel8, wxID_ANY, wxT("Load audio pack data"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer68->Add( btnLoadAudioPack, 0, wxALL, 5 );
	
	btnSaveAudioPack = new wxButton( m_panel8, wxID_ANY, wxT("Save audio pack data"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer68->Add( btnSaveAudioPack, 0, wxALL, 5 );
	
	
	bSizer67->Add( bSizer68, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText50 = new wxStaticText( m_panel8, wxID_ANY, wxT("Playing rules"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText50->Wrap( -1 );
	bSizer69->Add( m_staticText50, 0, wxALL, 5 );
	
	lstMusic = new wxListCtrl( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	lstMusic->SetMinSize( wxSize( 650,150 ) );
	
	bSizer69->Add( lstMusic, 0, wxALL, 5 );
	
	
	bSizer67->Add( bSizer69, 5, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer70;
	bSizer70 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer74;
	bSizer74 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText56 = new wxStaticText( m_panel8, wxID_ANY, wxT("Priority"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText56->Wrap( -1 );
	bSizer74->Add( m_staticText56, 0, wxALL, 5 );
	
	spinMusicPriority = new wxSpinCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 10000, 50 );
	bSizer74->Add( spinMusicPriority, 0, wxALL, 5 );
	
	m_staticText57 = new wxStaticText( m_panel8, wxID_ANY, wxT("(the smaller the number, the higher the priority)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText57->Wrap( 450 );
	bSizer74->Add( m_staticText57, 0, wxALL, 5 );
	
	chkGotoNext = new wxCheckBox( m_panel8, wxID_ANY, wxT("Do not replace the write and continue to check the next rule"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer74->Add( chkGotoNext, 0, wxALL, 5 );
	
	
	bSizer70->Add( bSizer74, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText51 = new wxStaticText( m_panel8, wxID_ANY, wxT("Plays when writing to RAM address $"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	bSizer72->Add( m_staticText51, 0, wxALL, 5 );
	
	txtMusicRAMAddress = new wxTextCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	txtMusicRAMAddress->SetMaxLength( 4 ); 
	bSizer72->Add( txtMusicRAMAddress, 0, wxALL, 5 );
	
	m_staticText55 = new wxStaticText( m_panel8, wxID_ANY, wxT("with value $"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText55->Wrap( -1 );
	bSizer72->Add( m_staticText55, 0, wxALL, 5 );
	
	txtMusicRAMValue = new wxTextCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer72->Add( txtMusicRAMValue, 0, wxALL, 5 );
	
	m_staticText581 = new wxStaticText( m_panel8, wxID_ANY, wxT("(leave blank to accept all values)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText581->Wrap( -1 );
	bSizer72->Add( m_staticText581, 0, wxALL, 5 );
	
	
	bSizer70->Add( bSizer72, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer791;
	bSizer791 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer80;
	bSizer80 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText59 = new wxStaticText( m_panel8, wxID_ANY, wxT("Additional conditions"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText59->Wrap( -1 );
	bSizer80->Add( m_staticText59, 0, wxALL, 5 );
	
	txtConditions = new wxTextCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer80->Add( txtConditions, 3, wxALL, 5 );
	
	
	bSizer791->Add( bSizer80, 1, wxEXPAND, 5 );
	
	m_staticText60 = new wxStaticText( m_panel8, wxID_ANY, wxT("(Each condition consists of one value on the left, one value on the right and one operator in the middle. Value can be a RAM address in hex with prefix 'A', a Hex value with prefix '$' or the value of the write as 'W'. The operator can be '==', '<=', '>=' or '!='. Multiple conditions are separated by ';' and all conditions must be satisfied for the music file to play.  Eg \"A50==$1;A3<A4;A1==W\")"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText60->Wrap( 600 );
	bSizer791->Add( m_staticText60, 2, wxALL, 5 );
	
	
	bSizer70->Add( bSizer791, 4, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer77;
	bSizer77 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText58 = new wxStaticText( m_panel8, wxID_ANY, wxT("Replace the write to that RAM address with another value $"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText58->Wrap( -1 );
	bSizer77->Add( m_staticText58, 0, wxALL, 5 );
	
	txtMusicRAMNewValue = new wxTextCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer77->Add( txtMusicRAMNewValue, 0, wxALL, 5 );
	
	m_staticText571 = new wxStaticText( m_panel8, wxID_ANY, wxT("(leave blank to write the same value)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText571->Wrap( -1 );
	bSizer77->Add( m_staticText571, 0, wxALL, 5 );
	
	
	bSizer70->Add( bSizer77, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer73;
	bSizer73 = new wxBoxSizer( wxVERTICAL );
	
	wxString rbxMusciPlayTypeChoices[] = { wxT("Repeat"), wxT("Once and stop"), wxT("Once and return to previous"), wxT("Once on a separate channel") };
	int rbxMusciPlayTypeNChoices = sizeof( rbxMusciPlayTypeChoices ) / sizeof( wxString );
	rbxMusciPlayType = new wxRadioBox( m_panel8, wxID_ANY, wxT("Play type"), wxDefaultPosition, wxDefaultSize, rbxMusciPlayTypeNChoices, rbxMusciPlayTypeChoices, 4, wxRA_SPECIFY_COLS );
	rbxMusciPlayType->SetSelection( 0 );
	bSizer73->Add( rbxMusciPlayType, 0, wxALL, 5 );
	
	
	bSizer70->Add( bSizer73, 2, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer75;
	bSizer75 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText54 = new wxStaticText( m_panel8, wxID_ANY, wxT("Audio file to play"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText54->Wrap( -1 );
	bSizer75->Add( m_staticText54, 0, wxALL, 5 );
	
	wxArrayString cboMP3fileChoices;
	cboMP3file = new wxChoice( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboMP3fileChoices, 0 );
	cboMP3file->SetSelection( 0 );
	bSizer75->Add( cboMP3file, 0, wxALL, 5 );
	
	m_filePicker4 = new wxFilePickerCtrl( m_panel8, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.ogg*"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	bSizer75->Add( m_filePicker4, 0, wxALL, 5 );
	
	
	bSizer70->Add( bSizer75, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer76;
	bSizer76 = new wxBoxSizer( wxHORIZONTAL );
	
	btnAddMP3 = new wxButton( m_panel8, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer76->Add( btnAddMP3, 0, wxALL, 5 );
	
	btnConfirmMP3 = new wxButton( m_panel8, wxID_ANY, wxT("Modify"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer76->Add( btnConfirmMP3, 0, wxALL, 5 );
	
	btnCancelMP3 = new wxButton( m_panel8, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer76->Add( btnCancelMP3, 0, wxALL, 5 );
	
	
	bSizer70->Add( bSizer76, 1, wxEXPAND, 5 );
	
	
	bSizer67->Add( bSizer70, 9, wxEXPAND, 5 );
	
	
	m_panel8->SetSizer( bSizer67 );
	m_panel8->Layout();
	bSizer67->Fit( m_panel8 );
	m_notebook2->AddPage( m_panel8, wxT("Audio Pack Editor"), false );
	m_panel11 = new wxPanel( m_notebook2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer81;
	bSizer81 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText61 = new wxStaticText( m_panel11, wxID_ANY, wxT("Pause or Run Frame to update the values"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	bSizer81->Add( m_staticText61, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer83;
	bSizer83 = new wxBoxSizer( wxHORIZONTAL );
	
	lstMemory = new wxListCtrl( m_panel11, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxLC_REPORT );
	bSizer83->Add( lstMemory, 1, wxEXPAND, 5 );
	
	
	bSizer81->Add( bSizer83, 1, wxEXPAND, 5 );
	
	
	m_panel11->SetSizer( bSizer81 );
	m_panel11->Layout();
	bSizer81->Fit( m_panel11 );
	m_notebook2->AddPage( m_panel11, wxT("RAM Viewer"), false );
	
	bSizer1->Add( m_notebook2, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::powerButtonClicked ), NULL, this );
	cbo1UP->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1UP ), NULL, this );
	cbo1DOWN->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1DOWN ), NULL, this );
	cbo1LEFT->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1LEFT ), NULL, this );
	cbo1RIGHT->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1RIGHT ), NULL, this );
	cbo1A->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1A ), NULL, this );
	cbo1B->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1B ), NULL, this );
	cbo1SELECT->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1SELECT ), NULL, this );
	cbo1START->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1START ), NULL, this );
	cbo2UP->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2UP ), NULL, this );
	cbo2DOWN->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2DOWN ), NULL, this );
	cbo2LEFT->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2LEFT ), NULL, this );
	cbo2RIGHT->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2RIGHT ), NULL, this );
	cbo2A->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2A ), NULL, this );
	cbo2B->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2B ), NULL, this );
	cbo2SELECT->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2SELECT ), NULL, this );
	cbo2START->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2START ), NULL, this );
	cboEndGame->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputEndGame ), NULL, this );
	cboSaveState->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputSaveState ), NULL, this );
	cboLoadState->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputLoadState ), NULL, this );
	cboScreenCap->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputScreenCap ), NULL, this );
	cboDataCap->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputDataCap ), NULL, this );
	cboPause->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputPause ), NULL, this );
	cboRunFrame->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputRunFrame ), NULL, this );
	cboContCap->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputContCap ), NULL, this );
	m_radioBtn1->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::screen1x ), NULL, this );
	m_radioBtn2->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::screen2x ), NULL, this );
	m_radioBtn3->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::screen4x ), NULL, this );
	m_radioBtn4->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::screenxx ), NULL, this );
	txtwidth->Connect( wxEVT_KEY_UP, wxKeyEventHandler( fraHDNes::screenWidth ), NULL, this );
	txtheight->Connect( wxEVT_KEY_UP, wxKeyEventHandler( fraHDNes::screenHeight ), NULL, this );
	chkUsePack->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fraHDNes::toggleGraphicsPack ), NULL, this );
	rbxGenerateData->Connect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( fraHDNes::toggleEditPack ), NULL, this );
	chkNearEdge->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fraHDNes::toggleEdgeData ), NULL, this );
	chkCHRRamEdit->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fraHDNes::toggleCHRRamEdit ), NULL, this );
	chkUseAudioPack->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fraHDNes::toggleAudioPack ), NULL, this );
	btnLoadPack->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::loadPackData ), NULL, this );
	btnSavePack->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::savePackData ), NULL, this );
	optPackScale1->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::setPackScale ), NULL, this );
	optPackScale2->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::setPackScale ), NULL, this );
	optPackScale4->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::setPackScale ), NULL, this );
	cboScreen->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::showScreenShot ), NULL, this );
	btnOptimizeScreenEdit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::optimizeScreenEdit ), NULL, this );
	lstScreenTiles->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( fraHDNes::screenTileSelected ), NULL, this );
	cboImage->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::showCustomImage ), NULL, this );
	m_filePicker2->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( fraHDNes::addImageToPack ), NULL, this );
	btnRemoveImage->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::removeImageFromPack ), NULL, this );
	btnConfirmTile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::confirmImgSelection ), NULL, this );
	btnCancelSelection->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::cancelSelection ), NULL, this );
	m_button6->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::genHDPack ), NULL, this );
	btn_Swap->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::addBatchMapping ), NULL, this );
	btn_MapDarkPalette->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::AddDarkMapping ), NULL, this );
	btn_CustomizePalette->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::customizePaletteClicked ), NULL, this );
	pnlImage->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( fraHDNes::ImageTileSelected ), NULL, this );
	btnLoadAudioPack->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::loadAudioPack ), NULL, this );
	btnSaveAudioPack->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::saveAudioPack ), NULL, this );
	lstMusic->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fraHDNes::musicSelected ), NULL, this );
	m_filePicker4->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( fraHDNes::addMP3ToPick ), NULL, this );
	btnAddMP3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::addMP3 ), NULL, this );
	btnConfirmMP3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::changeMP3 ), NULL, this );
	btnCancelMP3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::deleteMP3 ), NULL, this );
}

fraHDNes::~fraHDNes()
{
	// Disconnect Events
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::powerButtonClicked ), NULL, this );
	cbo1UP->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1UP ), NULL, this );
	cbo1DOWN->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1DOWN ), NULL, this );
	cbo1LEFT->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1LEFT ), NULL, this );
	cbo1RIGHT->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1RIGHT ), NULL, this );
	cbo1A->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1A ), NULL, this );
	cbo1B->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1B ), NULL, this );
	cbo1SELECT->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1SELECT ), NULL, this );
	cbo1START->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input1START ), NULL, this );
	cbo2UP->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2UP ), NULL, this );
	cbo2DOWN->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2DOWN ), NULL, this );
	cbo2LEFT->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2LEFT ), NULL, this );
	cbo2RIGHT->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2RIGHT ), NULL, this );
	cbo2A->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2A ), NULL, this );
	cbo2B->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2B ), NULL, this );
	cbo2SELECT->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2SELECT ), NULL, this );
	cbo2START->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::input2START ), NULL, this );
	cboEndGame->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputEndGame ), NULL, this );
	cboSaveState->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputSaveState ), NULL, this );
	cboLoadState->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputLoadState ), NULL, this );
	cboScreenCap->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputScreenCap ), NULL, this );
	cboDataCap->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputDataCap ), NULL, this );
	cboPause->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputPause ), NULL, this );
	cboRunFrame->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputRunFrame ), NULL, this );
	cboContCap->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::inputContCap ), NULL, this );
	m_radioBtn1->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::screen1x ), NULL, this );
	m_radioBtn2->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::screen2x ), NULL, this );
	m_radioBtn3->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::screen4x ), NULL, this );
	m_radioBtn4->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::screenxx ), NULL, this );
	txtwidth->Disconnect( wxEVT_KEY_UP, wxKeyEventHandler( fraHDNes::screenWidth ), NULL, this );
	txtheight->Disconnect( wxEVT_KEY_UP, wxKeyEventHandler( fraHDNes::screenHeight ), NULL, this );
	chkUsePack->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fraHDNes::toggleGraphicsPack ), NULL, this );
	rbxGenerateData->Disconnect( wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler( fraHDNes::toggleEditPack ), NULL, this );
	chkNearEdge->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fraHDNes::toggleEdgeData ), NULL, this );
	chkCHRRamEdit->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fraHDNes::toggleCHRRamEdit ), NULL, this );
	chkUseAudioPack->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( fraHDNes::toggleAudioPack ), NULL, this );
	btnLoadPack->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::loadPackData ), NULL, this );
	btnSavePack->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::savePackData ), NULL, this );
	optPackScale1->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::setPackScale ), NULL, this );
	optPackScale2->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::setPackScale ), NULL, this );
	optPackScale4->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( fraHDNes::setPackScale ), NULL, this );
	cboScreen->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::showScreenShot ), NULL, this );
	btnOptimizeScreenEdit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::optimizeScreenEdit ), NULL, this );
	lstScreenTiles->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( fraHDNes::screenTileSelected ), NULL, this );
	cboImage->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( fraHDNes::showCustomImage ), NULL, this );
	m_filePicker2->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( fraHDNes::addImageToPack ), NULL, this );
	btnRemoveImage->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::removeImageFromPack ), NULL, this );
	btnConfirmTile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::confirmImgSelection ), NULL, this );
	btnCancelSelection->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::cancelSelection ), NULL, this );
	m_button6->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::genHDPack ), NULL, this );
	btn_Swap->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::addBatchMapping ), NULL, this );
	btn_MapDarkPalette->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::AddDarkMapping ), NULL, this );
	btn_CustomizePalette->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::customizePaletteClicked ), NULL, this );
	pnlImage->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( fraHDNes::ImageTileSelected ), NULL, this );
	btnLoadAudioPack->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::loadAudioPack ), NULL, this );
	btnSaveAudioPack->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::saveAudioPack ), NULL, this );
	lstMusic->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( fraHDNes::musicSelected ), NULL, this );
	m_filePicker4->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( fraHDNes::addMP3ToPick ), NULL, this );
	btnAddMP3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::addMP3 ), NULL, this );
	btnConfirmMP3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::changeMP3 ), NULL, this );
	btnCancelMP3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( fraHDNes::deleteMP3 ), NULL, this );
	
}

batchMap::batchMap( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer341;
	bSizer341 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText25 = new wxStaticText( this, wxID_ANY, wxT("Select the source image:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	bSizer31->Add( m_staticText25, 0, wxALL, 5 );
	
	wxArrayString cboImageChoices;
	cboImage = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboImageChoices, 0 );
	cboImage->SetSelection( 0 );
	bSizer31->Add( cboImage, 0, wxALL, 5 );
	
	
	bSizer42->Add( bSizer31, 0, 0, 5 );
	
	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText32 = new wxStaticText( this, wxID_ANY, wxT("The first tile:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	m_staticText32->SetMinSize( wxSize( 130,-1 ) );
	
	bSizer46->Add( m_staticText32, 0, wxALL, 5 );
	
	lstFirstTile = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	lstFirstTile->SetMinSize( wxSize( 200,100 ) );
	
	bSizer46->Add( lstFirstTile, 0, wxALL, 5 );
	
	
	bSizer42->Add( bSizer46, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer87;
	bSizer87 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText62 = new wxStaticText( this, wxID_ANY, wxT("The last tile:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText62->Wrap( -1 );
	m_staticText62->SetMinSize( wxSize( 130,-1 ) );
	
	bSizer87->Add( m_staticText62, 0, wxALL, 5 );
	
	lstLastTile = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	lstLastTile->SetMinSize( wxSize( 200,100 ) );
	
	bSizer87->Add( lstLastTile, 0, wxALL, 5 );
	
	
	bSizer42->Add( bSizer87, 1, wxEXPAND, 5 );
	
	
	bSizer30->Add( bSizer42, 1, wxEXPAND, 5 );
	
	pnlOldImg = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer30->Add( pnlOldImg, 1, wxALL|wxEXPAND, 5 );
	
	
	bSizer341->Add( bSizer30, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxHORIZONTAL );
	
	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer88;
	bSizer88 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText621 = new wxStaticText( this, wxID_ANY, wxT("Select a new palette:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText621->Wrap( -1 );
	m_staticText621->SetMinSize( wxSize( 130,-1 ) );
	
	bSizer88->Add( m_staticText621, 0, wxALL, 5 );
	
	lstNewPalette = new wxListBox( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 ); 
	lstNewPalette->SetMinSize( wxSize( 200,100 ) );
	
	bSizer88->Add( lstNewPalette, 0, wxALL, 5 );
	
	
	bSizer36->Add( bSizer88, 4, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer37;
	bSizer37 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText26 = new wxStaticText( this, wxID_ANY, wxT("Add new mappings to image:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	bSizer34->Add( m_staticText26, 0, wxALL, 5 );
	
	wxArrayString cboNewImageChoices;
	cboNewImage = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboNewImageChoices, 0 );
	cboNewImage->SetSelection( 0 );
	bSizer34->Add( cboNewImage, 0, wxALL, 5 );
	
	m_filePicker2 = new wxFilePickerCtrl( this, wxID_ANY, wxEmptyString, wxT("Select a file"), wxT("*.png"), wxDefaultPosition, wxDefaultSize, wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	bSizer34->Add( m_filePicker2, 0, wxALL, 5 );
	
	
	bSizer37->Add( bSizer34, 1, 0, 5 );
	
	wxBoxSizer* bSizer431;
	bSizer431 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText33 = new wxStaticText( this, wxID_ANY, wxT("Warning: adding a file with same name will overwrite the existing file"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	bSizer431->Add( m_staticText33, 0, wxALL, 5 );
	
	m_staticText28 = new wxStaticText( this, wxID_ANY, wxT("Select new location for the first tile (Click on the image to select a tile)"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	bSizer431->Add( m_staticText28, 0, wxALL, 5 );
	
	
	bSizer37->Add( bSizer431, 2, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer89;
	bSizer89 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText29 = new wxStaticText( this, wxID_ANY, wxT("X"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	bSizer38->Add( m_staticText29, 0, wxALL, 5 );
	
	txtMapX = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer38->Add( txtMapX, 0, wxALL, 5 );
	
	m_staticText30 = new wxStaticText( this, wxID_ANY, wxT("Y"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	bSizer38->Add( m_staticText30, 0, wxALL, 5 );
	
	txtMapY = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer38->Add( txtMapY, 0, wxALL, 5 );
	
	m_staticText65 = new wxStaticText( this, wxID_ANY, wxT("Brightness"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText65->Wrap( -1 );
	bSizer38->Add( m_staticText65, 0, wxALL, 5 );
	
	txtBrightness = new wxTextCtrl( this, wxID_ANY, wxT("100"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer38->Add( txtBrightness, 0, wxALL, 5 );
	
	m_staticText66 = new wxStaticText( this, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText66->Wrap( -1 );
	bSizer38->Add( m_staticText66, 0, wxALL, 5 );
	
	
	bSizer89->Add( bSizer38, 1, 0, 5 );
	
	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );
	
	btnAddMappings = new wxButton( this, wxID_ANY, wxT("Add mappings"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer41->Add( btnAddMappings, 0, wxALL, 5 );
	
	btnCancel = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer41->Add( btnCancel, 0, wxALL, 5 );
	
	
	bSizer89->Add( bSizer41, 1, wxEXPAND, 5 );
	
	
	bSizer37->Add( bSizer89, 2, wxEXPAND, 5 );
	
	
	bSizer36->Add( bSizer37, 5, wxEXPAND, 5 );
	
	
	bSizer33->Add( bSizer36, 1, wxEXPAND, 5 );
	
	pnlNewImage = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer33->Add( pnlNewImage, 1, wxEXPAND | wxALL, 5 );
	
	
	bSizer341->Add( bSizer33, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer341 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	cboImage->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( batchMap::loadImage ), NULL, this );
	lstFirstTile->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( batchMap::firstTileSelected ), NULL, this );
	lstLastTile->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( batchMap::lastTileSelected ), NULL, this );
	lstNewPalette->Connect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( batchMap::showNewPalette ), NULL, this );
	cboNewImage->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( batchMap::showNewImage ), NULL, this );
	m_filePicker2->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( batchMap::addImageToPack ), NULL, this );
	btnAddMappings->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( batchMap::addMappings ), NULL, this );
	btnCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( batchMap::cancel ), NULL, this );
	pnlNewImage->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( batchMap::ImageTileSelected ), NULL, this );
}

batchMap::~batchMap()
{
	// Disconnect Events
	cboImage->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( batchMap::loadImage ), NULL, this );
	lstFirstTile->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( batchMap::firstTileSelected ), NULL, this );
	lstLastTile->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( batchMap::lastTileSelected ), NULL, this );
	lstNewPalette->Disconnect( wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler( batchMap::showNewPalette ), NULL, this );
	cboNewImage->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( batchMap::showNewImage ), NULL, this );
	m_filePicker2->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( batchMap::addImageToPack ), NULL, this );
	btnAddMappings->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( batchMap::addMappings ), NULL, this );
	btnCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( batchMap::cancel ), NULL, this );
	pnlNewImage->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( batchMap::ImageTileSelected ), NULL, this );
	
}

paletteDialog::paletteDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer84;
	bSizer84 = new wxBoxSizer( wxVERTICAL );
	
	pnlPalette = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pnlPalette->SetMinSize( wxSize( 128,32 ) );
	
	bSizer84->Add( pnlPalette, 4, wxEXPAND | wxALL, 5 );
	
	m_panel13 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer86;
	bSizer86 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText67 = new wxStaticText( m_panel13, wxID_ANY, wxT("Click on a cell and select a new color:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText67->Wrap( -1 );
	bSizer86->Add( m_staticText67, 0, wxALL, 5 );
	
	colorPicker = new wxColourPickerCtrl( m_panel13, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_SHOW_LABEL );
	bSizer86->Add( colorPicker, 0, wxALL, 5 );
	
	m_staticText68 = new wxStaticText( m_panel13, wxID_ANY, wxT("or import a palette from a file:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText68->Wrap( -1 );
	bSizer86->Add( m_staticText68, 0, wxALL, 5 );
	
	selectPalette = new wxFilePickerCtrl( m_panel13, wxID_ANY, wxEmptyString, wxT("Import palette from a file"), wxT("*.*"), wxDefaultPosition, wxDefaultSize, wxFLP_CHANGE_DIR|wxFLP_FILE_MUST_EXIST|wxFLP_OPEN );
	bSizer86->Add( selectPalette, 0, wxALL, 5 );
	
	
	m_panel13->SetSizer( bSizer86 );
	m_panel13->Layout();
	bSizer86->Fit( m_panel13 );
	bSizer84->Add( m_panel13, 0, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer84 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	pnlPalette->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( paletteDialog::paletteCellSelected ), NULL, this );
	pnlPalette->Connect( wxEVT_PAINT, wxPaintEventHandler( paletteDialog::paletteRepaint ), NULL, this );
	colorPicker->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( paletteDialog::newColorSelected ), NULL, this );
	selectPalette->Connect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( paletteDialog::paletteFileSelected ), NULL, this );
}

paletteDialog::~paletteDialog()
{
	// Disconnect Events
	pnlPalette->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( paletteDialog::paletteCellSelected ), NULL, this );
	pnlPalette->Disconnect( wxEVT_PAINT, wxPaintEventHandler( paletteDialog::paletteRepaint ), NULL, this );
	colorPicker->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( paletteDialog::newColorSelected ), NULL, this );
	selectPalette->Disconnect( wxEVT_COMMAND_FILEPICKER_CHANGED, wxFileDirPickerEventHandler( paletteDialog::paletteFileSelected ), NULL, this );
	
}
