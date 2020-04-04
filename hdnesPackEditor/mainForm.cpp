///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
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

	m_statusBar = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	pnlGameObjects = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel67 = new wxPanel( pnlGameObjects, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );

	m_splitter2 = new wxSplitterWindow( m_panel67, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter2->Connect( wxEVT_IDLE, wxIdleEventHandler( mainForm::m_splitter2OnIdle ), NULL, this );

	m_panel70 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer131;
	bSizer131 = new wxBoxSizer( wxHORIZONTAL );

	treeGameObjs = new wxTreeCtrl( m_panel70, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTR_EDIT_LABELS|wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_SINGLE );
	bSizer131->Add( treeGameObjs, 1, wxALL|wxEXPAND, 5 );


	m_panel70->SetSizer( bSizer131 );
	m_panel70->Layout();
	bSizer131->Fit( m_panel70 );
	m_panel71 = new wxPanel( m_splitter2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer38;
	bSizer38 = new wxBoxSizer( wxVERTICAL );

	nbkGameObject = new wxNotebook( m_panel71, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	pnlObj = new wxPanel( nbkGameObject, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer71;
	bSizer71 = new wxBoxSizer( wxHORIZONTAL );

	rbnObjectSprite = new wxRadioButton( pnlObj, wxID_ANY, wxT("Sprite"), wxDefaultPosition, wxDefaultSize, 0 );
	rbnObjectSprite->SetValue( true );
	bSizer71->Add( rbnObjectSprite, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	rbnObjectBG = new wxRadioButton( pnlObj, wxID_ANY, wxT("Back Ground"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer71->Add( rbnObjectBG, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText101 = new wxStaticText( pnlObj, wxID_ANY, wxT("BG colour: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText101->Wrap( -1 );
	bSizer71->Add( m_staticText101, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	btnGameObjBGColour = new wxButton( pnlObj, wxID_ANY, wxT("..."), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer71->Add( btnGameObjBGColour, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer15->Add( bSizer71, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer36;
	bSizer36 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText12 = new wxStaticText( pnlObj, wxID_ANY, wxT("Replacement:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer36->Add( m_staticText12, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText16 = new wxStaticText( pnlObj, wxID_ANY, wxT("Brightness"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer36->Add( m_staticText16, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	spnBrightness = new wxSpinCtrl( pnlObj, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 100 );
	spnBrightness->SetMaxSize( wxSize( 50,-1 ) );

	bSizer36->Add( spnBrightness, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText18 = new wxStaticText( pnlObj, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	bSizer36->Add( m_staticText18, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText271 = new wxStaticText( pnlObj, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText271->Wrap( -1 );
	bSizer36->Add( m_staticText271, 0, wxALL, 5 );

	chkGameObjIsDefault = new wxCheckBox( pnlObj, wxID_ANY, wxT("Use as default"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer36->Add( chkGameObjIsDefault, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer15->Add( bSizer36, 1, wxEXPAND, 5 );


	bSizer14->Add( bSizer15, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer33;
	bSizer33 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer34;
	bSizer34 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText11 = new wxStaticText( pnlObj, wxID_ANY, wxT("Original:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizer34->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText61 = new wxStaticText( pnlObj, wxID_ANY, wxT("Zoom"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText61->Wrap( -1 );
	bSizer34->Add( m_staticText61, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	zoomGameObjs = new wxSpinCtrl( pnlObj, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 10, 1 );
	zoomGameObjs->SetMinSize( wxSize( 50,-1 ) );

	bSizer34->Add( zoomGameObjs, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer33->Add( bSizer34, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer72;
	bSizer72 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText611 = new wxStaticText( pnlObj, wxID_ANY, wxT("Animation frame:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText611->Wrap( -1 );
	bSizer72->Add( m_staticText611, 0, wxALL, 5 );

	wxArrayString cboFrameRangeChoices;
	cboFrameRange = new wxChoice( pnlObj, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboFrameRangeChoices, 0 );
	cboFrameRange->SetSelection( 0 );
	bSizer72->Add( cboFrameRange, 0, wxALL, 5 );


	bSizer33->Add( bSizer72, 1, wxEXPAND, 5 );


	bSizer14->Add( bSizer33, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer11;
	fgSizer11 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer11->AddGrowableCol( 0 );
	fgSizer11->AddGrowableRow( 0 );
	fgSizer11->SetFlexibleDirection( wxBOTH );
	fgSizer11->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	pnlGameObjRaw = new wxPanel( pnlObj, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pnlGameObjRaw->SetBackgroundColour( wxColour( 0, 0, 0 ) );

	fgSizer11->Add( pnlGameObjRaw, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer101;
	bSizer101 = new wxBoxSizer( wxVERTICAL );

	scrGameObjRawV = new wxScrollBar( pnlObj, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL );
	bSizer101->Add( scrGameObjRawV, 1, wxALL, 5 );


	fgSizer11->Add( bSizer101, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer132;
	bSizer132 = new wxBoxSizer( wxHORIZONTAL );

	scrGameObjRawH = new wxScrollBar( pnlObj, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	bSizer132->Add( scrGameObjRawH, 1, wxALL, 5 );


	fgSizer11->Add( bSizer132, 1, wxEXPAND, 5 );


	bSizer18->Add( fgSizer11, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer18, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );

	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer12->AddGrowableCol( 0 );
	fgSizer12->AddGrowableRow( 0 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	pnlGameObjNew = new wxPanel( pnlObj, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pnlGameObjNew->SetBackgroundColour( wxColour( 0, 0, 0 ) );

	fgSizer12->Add( pnlGameObjNew, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer102;
	bSizer102 = new wxBoxSizer( wxVERTICAL );

	scrGameObjNewV = new wxScrollBar( pnlObj, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_VERTICAL );
	bSizer102->Add( scrGameObjNewV, 1, wxALL, 5 );


	fgSizer12->Add( bSizer102, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer133;
	bSizer133 = new wxBoxSizer( wxHORIZONTAL );

	scrGameObjNewH = new wxScrollBar( pnlObj, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL );
	bSizer133->Add( scrGameObjNewH, 1, wxALL, 5 );


	fgSizer12->Add( bSizer133, 1, wxEXPAND, 5 );


	bSizer20->Add( fgSizer12, 1, wxEXPAND, 5 );


	bSizer16->Add( bSizer20, 1, wxEXPAND, 5 );


	bSizer14->Add( bSizer16, 1, wxEXPAND, 5 );


	pnlObj->SetSizer( bSizer14 );
	pnlObj->Layout();
	bSizer14->Fit( pnlObj );
	nbkGameObject->AddPage( pnlObj, wxT("Object information"), true );
	pnlSwaps = new wxPanel( nbkGameObject, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer40;
	bSizer40 = new wxBoxSizer( wxVERTICAL );

	lstSwaps = new wxListCtrl( pnlSwaps, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizer40->Add( lstSwaps, 2, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer43;
	bSizer43 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText181 = new wxStaticText( pnlSwaps, wxID_ANY, wxT("Palette swap name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText181->Wrap( -1 );
	bSizer43->Add( m_staticText181, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	txtSwapName = new wxTextCtrl( pnlSwaps, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer43->Add( txtSwapName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer40->Add( bSizer43, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer41;
	bSizer41 = new wxBoxSizer( wxHORIZONTAL );

	lstPalettes = new wxListCtrl( pnlSwaps, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizer41->Add( lstPalettes, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer42;
	bSizer42 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer44;
	bSizer44 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText19 = new wxStaticText( pnlSwaps, wxID_ANY, wxT("Original palette:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	bSizer44->Add( m_staticText19, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	lblOrgPalette = new wxStaticText( pnlSwaps, wxID_ANY, wxT("00000000"), wxDefaultPosition, wxDefaultSize, 0 );
	lblOrgPalette->Wrap( -1 );
	bSizer44->Add( lblOrgPalette, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer42->Add( bSizer44, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer45;
	bSizer45 = new wxBoxSizer( wxHORIZONTAL );

	pnlOrgPaletteBG = new wxPanel( pnlSwaps, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer45->Add( pnlOrgPaletteBG, 1, wxALL|wxEXPAND, 5 );

	pnlOrgPalette1 = new wxPanel( pnlSwaps, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer45->Add( pnlOrgPalette1, 1, wxEXPAND | wxALL, 5 );

	pnlOrgPalette2 = new wxPanel( pnlSwaps, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer45->Add( pnlOrgPalette2, 1, wxEXPAND | wxALL, 5 );

	pnlOrgPalette3 = new wxPanel( pnlSwaps, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer45->Add( pnlOrgPalette3, 1, wxEXPAND | wxALL, 5 );


	bSizer42->Add( bSizer45, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer511;
	bSizer511 = new wxBoxSizer( wxVERTICAL );

	m_staticText261 = new wxStaticText( pnlSwaps, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText261->Wrap( -1 );
	bSizer511->Add( m_staticText261, 0, wxALL|wxEXPAND, 5 );


	bSizer42->Add( bSizer511, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer46;
	bSizer46 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText21 = new wxStaticText( pnlSwaps, wxID_ANY, wxT("New palette:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	bSizer46->Add( m_staticText21, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	txtSwapPaletteNew = new wxTextCtrl( pnlSwaps, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !txtSwapPaletteNew->HasFlag( wxTE_MULTILINE ) )
	{
	txtSwapPaletteNew->SetMaxLength( 8 );
	}
	#else
	txtSwapPaletteNew->SetMaxLength( 8 );
	#endif
	bSizer46->Add( txtSwapPaletteNew, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer42->Add( bSizer46, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer48;
	bSizer48 = new wxBoxSizer( wxHORIZONTAL );

	btnNewPaletteBG = new wxButton( pnlSwaps, wxID_ANY, wxT("BG"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer48->Add( btnNewPaletteBG, 1, wxALL|wxEXPAND, 5 );

	btnNewPalette1 = new wxButton( pnlSwaps, wxID_ANY, wxT("1"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer48->Add( btnNewPalette1, 1, wxALL|wxEXPAND, 5 );

	btnNewPalette2 = new wxButton( pnlSwaps, wxID_ANY, wxT("2"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer48->Add( btnNewPalette2, 1, wxALL|wxEXPAND, 5 );

	btnNewPalette3 = new wxButton( pnlSwaps, wxID_ANY, wxT("3"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer48->Add( btnNewPalette3, 1, wxALL|wxEXPAND, 5 );


	bSizer42->Add( bSizer48, 1, wxEXPAND, 5 );


	bSizer41->Add( bSizer42, 1, wxEXPAND, 5 );


	bSizer40->Add( bSizer41, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer52;
	bSizer52 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer53;
	bSizer53 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer49;
	bSizer49 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText22 = new wxStaticText( pnlSwaps, wxID_ANY, wxT("New brightness:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText22->Wrap( -1 );
	bSizer49->Add( m_staticText22, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	spnSwapNewBrightness = new wxSpinCtrl( pnlSwaps, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 100 );
	spnSwapNewBrightness->SetMaxSize( wxSize( 50,-1 ) );

	bSizer49->Add( spnSwapNewBrightness, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText23 = new wxStaticText( pnlSwaps, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	bSizer49->Add( m_staticText23, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer53->Add( bSizer49, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer50;
	bSizer50 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText24 = new wxStaticText( pnlSwaps, wxID_ANY, wxT("Rotate hue:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	bSizer50->Add( m_staticText24, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	spnSwapRotateHue = new wxSpinCtrl( pnlSwaps, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -360, 360, 0 );
	spnSwapRotateHue->SetMaxSize( wxSize( 70,-1 ) );

	bSizer50->Add( spnSwapRotateHue, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText26 = new wxStaticText( pnlSwaps, wxID_ANY, wxT("degrees"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	bSizer50->Add( m_staticText26, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer53->Add( bSizer50, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer51;
	bSizer51 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText27 = new wxStaticText( pnlSwaps, wxID_ANY, wxT("New saturation:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText27->Wrap( -1 );
	bSizer51->Add( m_staticText27, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	spnSwapNewSaturation = new wxSpinCtrl( pnlSwaps, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 100 );
	spnSwapNewSaturation->SetMaxSize( wxSize( 50,-1 ) );

	bSizer51->Add( spnSwapNewSaturation, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText28 = new wxStaticText( pnlSwaps, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	bSizer51->Add( m_staticText28, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer53->Add( bSizer51, 1, wxEXPAND, 5 );


	bSizer52->Add( bSizer53, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer54;
	bSizer54 = new wxBoxSizer( wxHORIZONTAL );

	btnAddSwap = new wxButton( pnlSwaps, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer54->Add( btnAddSwap, 0, wxALIGN_CENTER|wxALIGN_RIGHT, 5 );

	btnUpdateSwap = new wxButton( pnlSwaps, wxID_ANY, wxT("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer54->Add( btnUpdateSwap, 0, wxALIGN_CENTER|wxALIGN_RIGHT, 5 );

	btnDeleteSwap = new wxButton( pnlSwaps, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer54->Add( btnDeleteSwap, 0, wxALIGN_CENTER|wxALIGN_RIGHT, 5 );


	bSizer52->Add( bSizer54, 1, wxEXPAND, 5 );


	bSizer40->Add( bSizer52, 0, wxEXPAND, 5 );


	pnlSwaps->SetSizer( bSizer40 );
	pnlSwaps->Layout();
	bSizer40->Fit( pnlSwaps );
	nbkGameObject->AddPage( pnlSwaps, wxT("Palette swaps"), false );
	pnlBGImage = new wxPanel( nbkGameObject, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer59;
	bSizer59 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer60;
	bSizer60 = new wxBoxSizer( wxHORIZONTAL );

	btnBGImage = new wxButton( pnlBGImage, wxID_ANY, wxT("Select image file"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer60->Add( btnBGImage, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer59->Add( bSizer60, 0, 0, 5 );

	wxBoxSizer* bSizer61;
	bSizer61 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText51 = new wxStaticText( pnlBGImage, wxID_ANY, wxT("Brightness:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	bSizer61->Add( m_staticText51, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	spnBGBrightness = new wxSpinCtrl( pnlBGImage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 100, 100 );
	spnBGBrightness->SetMaxSize( wxSize( 50,-1 ) );

	bSizer61->Add( spnBGBrightness, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText52 = new wxStaticText( pnlBGImage, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText52->Wrap( -1 );
	bSizer61->Add( m_staticText52, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText53 = new wxStaticText( pnlBGImage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText53->Wrap( -1 );
	bSizer61->Add( m_staticText53, 0, wxALL, 5 );

	m_staticText54 = new wxStaticText( pnlBGImage, wxID_ANY, wxT("Scroll rate:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText54->Wrap( -1 );
	bSizer61->Add( m_staticText54, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText55 = new wxStaticText( pnlBGImage, wxID_ANY, wxT("H"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText55->Wrap( -1 );
	bSizer61->Add( m_staticText55, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	spnBGHScrollRate = new wxSpinCtrl( pnlBGImage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 100 );
	spnBGHScrollRate->SetMaxSize( wxSize( 50,-1 ) );

	bSizer61->Add( spnBGHScrollRate, 0, wxALL, 5 );

	m_staticText58 = new wxStaticText( pnlBGImage, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText58->Wrap( -1 );
	bSizer61->Add( m_staticText58, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText56 = new wxStaticText( pnlBGImage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText56->Wrap( -1 );
	bSizer61->Add( m_staticText56, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText57 = new wxStaticText( pnlBGImage, wxID_ANY, wxT("V"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText57->Wrap( -1 );
	bSizer61->Add( m_staticText57, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	spnBGVScrollRate = new wxSpinCtrl( pnlBGImage, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 100 );
	spnBGVScrollRate->SetMaxSize( wxSize( 50,-1 ) );

	bSizer61->Add( spnBGVScrollRate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText59 = new wxStaticText( pnlBGImage, wxID_ANY, wxT("%"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText59->Wrap( -1 );
	bSizer61->Add( m_staticText59, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	chkBgShowBehind = new wxCheckBox( pnlBGImage, wxID_ANY, wxT("Show Behind Background Priority Sprites"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer61->Add( chkBgShowBehind, 0, wxALL, 5 );


	bSizer59->Add( bSizer61, 0, wxEXPAND, 5 );

	pnlBGImageDisplay = new wxPanel( pnlBGImage, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer59->Add( pnlBGImageDisplay, 1, wxEXPAND | wxALL, 5 );


	pnlBGImage->SetSizer( bSizer59 );
	pnlBGImage->Layout();
	bSizer59->Fit( pnlBGImage );
	nbkGameObject->AddPage( pnlBGImage, wxT("Background"), false );
	pnlConditions = new wxPanel( nbkGameObject, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer512;
	bSizer512 = new wxBoxSizer( wxVERTICAL );

	lstConditions = new wxListCtrl( pnlConditions, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizer512->Add( lstConditions, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer521;
	bSizer521 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer55;
	bSizer55 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText281 = new wxStaticText( pnlConditions, wxID_ANY, wxT("Type:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText281->Wrap( -1 );
	bSizer55->Add( m_staticText281, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cboConditionTypeChoices;
	cboConditionType = new wxChoice( pnlConditions, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboConditionTypeChoices, 0 );
	cboConditionType->SetSelection( 0 );
	bSizer55->Add( cboConditionType, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText29 = new wxStaticText( pnlConditions, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText29->Wrap( -1 );
	bSizer55->Add( m_staticText29, 0, wxALL, 5 );

	m_staticText30 = new wxStaticText( pnlConditions, wxID_ANY, wxT("Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	bSizer55->Add( m_staticText30, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	txtConditionName = new wxTextCtrl( pnlConditions, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer55->Add( txtConditionName, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText48 = new wxStaticText( pnlConditions, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText48->Wrap( -1 );
	bSizer55->Add( m_staticText48, 0, wxALL, 5 );

	chkConditionNegative = new wxCheckBox( pnlConditions, wxID_ANY, wxT("Negative condition"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer55->Add( chkConditionNegative, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer521->Add( bSizer55, 0, wxEXPAND, 5 );

	pnlConditionType1 = new wxPanel( pnlConditions, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer56;
	bSizer56 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText31 = new wxStaticText( pnlConditionType1, wxID_ANY, wxT("X:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	bSizer56->Add( m_staticText31, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	txtConditionX = new wxTextCtrl( pnlConditionType1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer56->Add( txtConditionX, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText32 = new wxStaticText( pnlConditionType1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	bSizer56->Add( m_staticText32, 0, wxALL, 5 );

	m_staticText33 = new wxStaticText( pnlConditionType1, wxID_ANY, wxT("Y:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText33->Wrap( -1 );
	bSizer56->Add( m_staticText33, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	txtConditionY = new wxTextCtrl( pnlConditionType1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer56->Add( txtConditionY, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText34 = new wxStaticText( pnlConditionType1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	bSizer56->Add( m_staticText34, 0, wxALL, 5 );

	m_staticText35 = new wxStaticText( pnlConditionType1, wxID_ANY, wxT("Tile:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	bSizer56->Add( m_staticText35, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	txtConditionTile = new wxTextCtrl( pnlConditionType1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer56->Add( txtConditionTile, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText36 = new wxStaticText( pnlConditionType1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	bSizer56->Add( m_staticText36, 0, wxALL, 5 );

	m_staticText37 = new wxStaticText( pnlConditionType1, wxID_ANY, wxT("Palette:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	bSizer56->Add( m_staticText37, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	txtConditionPalette = new wxTextCtrl( pnlConditionType1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer56->Add( txtConditionPalette, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	pnlConditionType1->SetSizer( bSizer56 );
	pnlConditionType1->Layout();
	bSizer56->Fit( pnlConditionType1 );
	bSizer521->Add( pnlConditionType1, 0, wxALL|wxEXPAND, 5 );

	pnlConditionType2 = new wxPanel( pnlConditions, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer57;
	bSizer57 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText38 = new wxStaticText( pnlConditionType2, wxID_ANY, wxT("Address1:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	bSizer57->Add( m_staticText38, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	txtConditionAddress1 = new wxTextCtrl( pnlConditionType2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer57->Add( txtConditionAddress1, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText39 = new wxStaticText( pnlConditionType2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	bSizer57->Add( m_staticText39, 0, wxALL, 5 );

	m_staticText40 = new wxStaticText( pnlConditionType2, wxID_ANY, wxT("Operator:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	bSizer57->Add( m_staticText40, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cboConditionOpChoices;
	cboConditionOp = new wxChoice( pnlConditionType2, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboConditionOpChoices, 0 );
	cboConditionOp->SetSelection( 0 );
	bSizer57->Add( cboConditionOp, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText41 = new wxStaticText( pnlConditionType2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer57->Add( m_staticText41, 0, wxALL, 5 );

	m_staticText42 = new wxStaticText( pnlConditionType2, wxID_ANY, wxT("Address2:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	bSizer57->Add( m_staticText42, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	txtConditionAddress2 = new wxTextCtrl( pnlConditionType2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer57->Add( txtConditionAddress2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	pnlConditionType2->SetSizer( bSizer57 );
	pnlConditionType2->Layout();
	bSizer57->Fit( pnlConditionType2 );
	bSizer521->Add( pnlConditionType2, 0, wxEXPAND | wxALL, 5 );

	pnlConditionType3 = new wxPanel( pnlConditions, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer58;
	bSizer58 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText43 = new wxStaticText( pnlConditionType3, wxID_ANY, wxT("Address:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText43->Wrap( -1 );
	bSizer58->Add( m_staticText43, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	txtConditionAddress = new wxTextCtrl( pnlConditionType3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer58->Add( txtConditionAddress, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText44 = new wxStaticText( pnlConditionType3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText44->Wrap( -1 );
	bSizer58->Add( m_staticText44, 0, wxALL, 5 );

	m_staticText45 = new wxStaticText( pnlConditionType3, wxID_ANY, wxT("Operator:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText45->Wrap( -1 );
	bSizer58->Add( m_staticText45, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	wxArrayString cboConditionOp2Choices;
	cboConditionOp2 = new wxChoice( pnlConditionType3, wxID_ANY, wxDefaultPosition, wxDefaultSize, cboConditionOp2Choices, 0 );
	cboConditionOp2->SetSelection( 0 );
	bSizer58->Add( cboConditionOp2, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_staticText46 = new wxStaticText( pnlConditionType3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText46->Wrap( -1 );
	bSizer58->Add( m_staticText46, 0, wxALL, 5 );

	m_staticText47 = new wxStaticText( pnlConditionType3, wxID_ANY, wxT("Value:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText47->Wrap( -1 );
	bSizer58->Add( m_staticText47, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	txtConditionValue = new wxTextCtrl( pnlConditionType3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer58->Add( txtConditionValue, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	pnlConditionType3->SetSizer( bSizer58 );
	pnlConditionType3->Layout();
	bSizer58->Fit( pnlConditionType3 );
	bSizer521->Add( pnlConditionType3, 0, wxEXPAND | wxALL, 5 );

	pnlConditionType0 = new wxPanel( pnlConditions, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer581;
	bSizer581 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText50 = new wxStaticText( pnlConditionType0, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText50->Wrap( -1 );
	bSizer581->Add( m_staticText50, 0, wxALL, 5 );


	pnlConditionType0->SetSizer( bSizer581 );
	pnlConditionType0->Layout();
	bSizer581->Fit( pnlConditionType0 );
	bSizer521->Add( pnlConditionType0, 0, wxEXPAND | wxALL, 5 );


	bSizer512->Add( bSizer521, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer541;
	bSizer541 = new wxBoxSizer( wxHORIZONTAL );

	cmdConditionAdd = new wxButton( pnlConditions, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer541->Add( cmdConditionAdd, 0, wxALL, 5 );

	cmdConditionUpdate = new wxButton( pnlConditions, wxID_ANY, wxT("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer541->Add( cmdConditionUpdate, 0, wxALL, 5 );

	cmdConditionDelete = new wxButton( pnlConditions, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer541->Add( cmdConditionDelete, 0, wxALL, 5 );


	bSizer512->Add( bSizer541, 0, wxEXPAND, 5 );


	pnlConditions->SetSizer( bSizer512 );
	pnlConditions->Layout();
	bSizer512->Fit( pnlConditions );
	nbkGameObject->AddPage( pnlConditions, wxT("Conditions"), false );
	pnlAnimation = new wxPanel( nbkGameObject, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer62;
	bSizer62 = new wxBoxSizer( wxVERTICAL );

	lstFrameRange = new wxListCtrl( pnlAnimation, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	bSizer62->Add( lstFrameRange, 1, wxALL|wxEXPAND, 5 );

	m_panel92 = new wxPanel( pnlAnimation, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer67;
	bSizer67 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer68;
	bSizer68 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText591 = new wxStaticText( m_panel92, wxID_ANY, wxT("Display for:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText591->Wrap( -1 );
	bSizer68->Add( m_staticText591, 0, wxALL, 5 );

	spnFrameRangeCnt = new wxSpinCtrl( m_panel92, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 9999, 0 );
	bSizer68->Add( spnFrameRangeCnt, 0, wxALL, 5 );

	m_staticText62 = new wxStaticText( m_panel92, wxID_ANY, wxT("frames"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText62->Wrap( -1 );
	bSizer68->Add( m_staticText62, 0, wxALL, 5 );


	bSizer67->Add( bSizer68, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer69;
	bSizer69 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText60 = new wxStaticText( m_panel92, wxID_ANY, wxT("Frame name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText60->Wrap( -1 );
	bSizer69->Add( m_staticText60, 0, wxALL, 5 );

	txtFrameRangeName = new wxTextCtrl( m_panel92, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer69->Add( txtFrameRangeName, 1, wxALL, 5 );


	bSizer67->Add( bSizer69, 1, wxEXPAND, 5 );


	m_panel92->SetSizer( bSizer67 );
	m_panel92->Layout();
	bSizer67->Fit( m_panel92 );
	bSizer62->Add( m_panel92, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer65;
	bSizer65 = new wxBoxSizer( wxHORIZONTAL );

	cmdFrameRangeAdd = new wxButton( pnlAnimation, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( cmdFrameRangeAdd, 0, wxALL, 5 );

	cmdFrameRangeUpdate = new wxButton( pnlAnimation, wxID_ANY, wxT("Update"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( cmdFrameRangeUpdate, 0, wxALL, 5 );

	cmdFrameRangeDelete = new wxButton( pnlAnimation, wxID_ANY, wxT("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( cmdFrameRangeDelete, 0, wxALL, 5 );

	cmdFrameRangeMoveUp = new wxButton( pnlAnimation, wxID_ANY, wxT("Move up"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( cmdFrameRangeMoveUp, 0, wxALL, 5 );

	cmdFrameRangeMoveDown = new wxButton( pnlAnimation, wxID_ANY, wxT("Move down"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer65->Add( cmdFrameRangeMoveDown, 0, wxALL, 5 );


	bSizer62->Add( bSizer65, 0, wxEXPAND, 5 );


	pnlAnimation->SetSizer( bSizer62 );
	pnlAnimation->Layout();
	bSizer62->Fit( pnlAnimation );
	nbkGameObject->AddPage( pnlAnimation, wxT("Animation frames"), false );

	bSizer38->Add( nbkGameObject, 1, wxEXPAND | wxALL, 5 );


	m_panel71->SetSizer( bSizer38 );
	m_panel71->Layout();
	bSizer38->Fit( m_panel71 );
	m_splitter2->SplitVertically( m_panel70, m_panel71, 150 );
	bSizer12->Add( m_splitter2, 1, wxEXPAND, 5 );


	m_panel67->SetSizer( bSizer12 );
	m_panel67->Layout();
	bSizer12->Fit( m_panel67 );
	pnlGameObjects->AddPage( m_panel67, wxT("Game Objects"), true );
	m_panel72 = new wxPanel( pnlGameObjects, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );

	m_splitter21 = new wxSplitterWindow( m_panel72, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter21->Connect( wxEVT_IDLE, wxIdleEventHandler( mainForm::m_splitter21OnIdle ), NULL, this );

	m_panel741 = new wxPanel( m_splitter21, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer261;
	bSizer261 = new wxBoxSizer( wxVERTICAL );

	lstHDImg = new wxListCtrl( m_panel741, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_SINGLE_SEL );
	bSizer261->Add( lstHDImg, 1, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer26;
	bSizer26 = new wxBoxSizer( wxHORIZONTAL );

	btnHDImgAdd = new wxButton( m_panel741, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( btnHDImgAdd, 0, wxALL, 5 );

	btnHDImgRemove = new wxButton( m_panel741, wxID_ANY, wxT("Remove"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer26->Add( btnHDImgRemove, 0, wxALL, 5 );


	bSizer261->Add( bSizer26, 0, wxEXPAND, 5 );


	m_panel741->SetSizer( bSizer261 );
	m_panel741->Layout();
	bSizer261->Fit( m_panel741 );
	m_panel75 = new wxPanel( m_splitter21, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer262;
	bSizer262 = new wxBoxSizer( wxVERTICAL );

	m_splitter3 = new wxSplitterWindow( m_panel75, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D );
	m_splitter3->Connect( wxEVT_IDLE, wxIdleEventHandler( mainForm::m_splitter3OnIdle ), NULL, this );

	m_panel76 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );

	lstHDImgTiles = new wxListCtrl( m_panel76, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT );
	bSizer30->Add( lstHDImgTiles, 1, wxALL|wxEXPAND, 5 );


	m_panel76->SetSizer( bSizer30 );
	m_panel76->Layout();
	bSizer30->Fit( m_panel76 );
	pnlHDImg = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_splitter3->SplitVertically( m_panel76, pnlHDImg, 250 );
	bSizer262->Add( m_splitter3, 1, wxEXPAND, 5 );


	m_panel75->SetSizer( bSizer262 );
	m_panel75->Layout();
	bSizer262->Fit( m_panel75 );
	m_splitter21->SplitVertically( m_panel741, m_panel75, 250 );
	bSizer23->Add( m_splitter21, 1, wxEXPAND, 5 );


	m_panel72->SetSizer( bSizer23 );
	m_panel72->Layout();
	bSizer23->Fit( m_panel72 );
	pnlGameObjects->AddPage( m_panel72, wxT("HD Images"), false );
	m_panel1 = new wxPanel( pnlGameObjects, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
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

	m_staticText9 = new wxStaticText( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer7->Add( m_staticText9, 0, wxALL, 5 );

	m_staticText10 = new wxStaticText( m_panel1, wxID_ANY, wxT("Palette: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer7->Add( m_staticText10, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	btnRomViewBGColour = new wxButton( m_panel1, wxID_ANY, wxT("BG"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer7->Add( btnRomViewBGColour, 0, wxALIGN_CENTER_VERTICAL, 5 );

	btnRomViewColour1 = new wxButton( m_panel1, wxID_ANY, wxT("1"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer7->Add( btnRomViewColour1, 0, wxALIGN_CENTER_VERTICAL, 5 );

	btnRomViewColour2 = new wxButton( m_panel1, wxID_ANY, wxT("2"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer7->Add( btnRomViewColour2, 0, wxALIGN_CENTER_VERTICAL, 5 );

	btnRomViewColour3 = new wxButton( m_panel1, wxID_ANY, wxT("3"), wxDefaultPosition, wxSize( 50,-1 ), 0 );
	bSizer7->Add( btnRomViewColour3, 0, wxALIGN_CENTER_VERTICAL, 5 );

	txtRomViewPalette = new wxTextCtrl( m_panel1, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !txtRomViewPalette->HasFlag( wxTE_MULTILINE ) )
	{
	txtRomViewPalette->SetMaxLength( 8 );
	}
	#else
	txtRomViewPalette->SetMaxLength( 8 );
	#endif
	bSizer7->Add( txtRomViewPalette, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer6->Add( bSizer7, 0, wxEXPAND, 5 );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableRow( 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_ALL );

	pnlRom = new wxPanel( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	pnlRom->SetBackgroundColour( wxColour( 0, 0, 0 ) );

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
	pnlGameObjects->AddPage( m_panel1, wxT("ROM Viewer"), false );

	bSizer5->Add( pnlGameObjects, 1, wxEXPAND | wxALL, 5 );


	this->SetSizer( bSizer5 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( mainForm::closeWindow ) );
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileNew ), this, m_menuItemNew->GetId());
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileOpen ), this, m_menuItemOpen->GetId());
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileSave ), this, m_menuSave->GetId());
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileSaveAs ), this, m_menuSaveAs->GetId());
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileGen ), this, m_menuItemGen->GetId());
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileGen ), this, m_menuClose->GetId());
	m_menu3->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( mainForm::MenuFileExit ), this, m_menuExit->GetId());
	treeGameObjs->Connect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( mainForm::gameObjTItemBeginEdit ), NULL, this );
	treeGameObjs->Connect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( mainForm::gameObjTItemChangeName ), NULL, this );
	treeGameObjs->Connect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( mainForm::gameObjTItemOpenMenu ), NULL, this );
	treeGameObjs->Connect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( mainForm::gameObjTItemSelected ), NULL, this );
	rbnObjectSprite->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( mainForm::gameObjSpriteClicked ), NULL, this );
	rbnObjectBG->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( mainForm::gameObjBGClicked ), NULL, this );
	btnGameObjBGColour->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::gameObjBGColour ), NULL, this );
	spnBrightness->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::replaceBrightnessChanged ), NULL, this );
	chkGameObjIsDefault->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainForm::gameObjDefaultClicked ), NULL, this );
	zoomGameObjs->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::zoomGameObjsChanged ), NULL, this );
	cboFrameRange->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( mainForm::ShowSelectedFrame ), NULL, this );
	pnlGameObjRaw->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( mainForm::gameObjsRawEnter ), NULL, this );
	pnlGameObjRaw->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( mainForm::gameObjsRawLDown ), NULL, this );
	pnlGameObjRaw->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( mainForm::gameObjsRawLUp ), NULL, this );
	pnlGameObjRaw->Connect( wxEVT_MOTION, wxMouseEventHandler( mainForm::gameObjsRawMove ), NULL, this );
	pnlGameObjRaw->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( mainForm::gameObjsRawRUp ), NULL, this );
	pnlGameObjRaw->Connect( wxEVT_SIZE, wxSizeEventHandler( mainForm::gameObjsRawSizeChanged ), NULL, this );
	scrGameObjRawV->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawH->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	pnlGameObjNew->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( mainForm::gameObjsNewEnter ), NULL, this );
	pnlGameObjNew->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( mainForm::gameObjsNewLDown ), NULL, this );
	pnlGameObjNew->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( mainForm::gameObjsNewLUp ), NULL, this );
	pnlGameObjNew->Connect( wxEVT_MOTION, wxMouseEventHandler( mainForm::gameObjsNewMove ), NULL, this );
	pnlGameObjNew->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( mainForm::gameObjsNewRUp ), NULL, this );
	pnlGameObjNew->Connect( wxEVT_SIZE, wxSizeEventHandler( mainForm::gameObjsNewSizeChanged ), NULL, this );
	scrGameObjNewV->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewH->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	lstSwaps->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::SwapSeleted ), NULL, this );
	lstPalettes->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::SwapPaletteSelected ), NULL, this );
	txtSwapPaletteNew->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( mainForm::SwapPaletteNewChanged ), NULL, this );
	btnNewPaletteBG->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::SwapNewPaletteBGClicked ), NULL, this );
	btnNewPalette1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::SwapNewPalette1Clicked ), NULL, this );
	btnNewPalette2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::SwapNewPalette2Clicked ), NULL, this );
	btnNewPalette3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::SwapNewPalette3Clicked ), NULL, this );
	spnSwapNewBrightness->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::SwapNewBrightnessChanged ), NULL, this );
	spnSwapRotateHue->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::SwapRotateHueChanged ), NULL, this );
	spnSwapNewSaturation->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::SwapNewSaturationChanged ), NULL, this );
	btnAddSwap->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::AddSwapClicked ), NULL, this );
	btnUpdateSwap->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::UpdateSwapClicked ), NULL, this );
	btnDeleteSwap->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::DeleteSwapClicked ), NULL, this );
	btnBGImage->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::BGImageSelect ), NULL, this );
	spnBGBrightness->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::BGImageBrightness ), NULL, this );
	spnBGHScrollRate->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::BGImageHScrollRate ), NULL, this );
	spnBGVScrollRate->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::BGImageVScrollRate ), NULL, this );
	chkBgShowBehind->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainForm::BGImageShowBehindClicked ), NULL, this );
	lstConditions->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::ConditionSelected ), NULL, this );
	cboConditionType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( mainForm::ConditionTypeSelect ), NULL, this );
	cmdConditionAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::ConditionAdd ), NULL, this );
	cmdConditionUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::ConditionUpdate ), NULL, this );
	cmdConditionDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::ConditionDelete ), NULL, this );
	lstFrameRange->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::FrameRangeItemSelected ), NULL, this );
	cmdFrameRangeAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::AddFrameRangeClicked ), NULL, this );
	cmdFrameRangeUpdate->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::UpdateFrameRangeClicked ), NULL, this );
	cmdFrameRangeDelete->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::DeleteFrameRangeClicked ), NULL, this );
	cmdFrameRangeMoveUp->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::MoveUpFrameRange ), NULL, this );
	cmdFrameRangeMoveDown->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::MoveDownFrameRange ), NULL, this );
	lstHDImg->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::HDImgSelected ), NULL, this );
	btnHDImgAdd->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::HDImgAdd ), NULL, this );
	btnHDImgRemove->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::HDImgRemove ), NULL, this );
	lstHDImgTiles->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::HDImgTileSelected ), NULL, this );
	pnlHDImg->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( mainForm::HDImgEnter ), NULL, this );
	pnlHDImg->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( mainForm::HDImgLDown ), NULL, this );
	pnlHDImg->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( mainForm::HDImgLUp ), NULL, this );
	pnlHDImg->Connect( wxEVT_MOTION, wxMouseEventHandler( mainForm::HDImgMove ), NULL, this );
	pnlHDImg->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( mainForm::HDImgRUp ), NULL, this );
	pnlHDImg->Connect( wxEVT_SIZE, wxSizeEventHandler( mainForm::HDImgSizeChanged ), NULL, this );
	zoomRom->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::zoomRomChanged ), NULL, this );
	btnRomViewBGColour->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romBGColour ), NULL, this );
	btnRomViewColour1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour1 ), NULL, this );
	btnRomViewColour2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour2 ), NULL, this );
	btnRomViewColour3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour3 ), NULL, this );
	txtRomViewPalette->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( mainForm::romViewPaletteHexChanged ), NULL, this );
	pnlRom->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( mainForm::romViewEnter ), NULL, this );
	pnlRom->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( mainForm::romViewLDown ), NULL, this );
	pnlRom->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( mainForm::romViewLUp ), NULL, this );
	pnlRom->Connect( wxEVT_MOTION, wxMouseEventHandler( mainForm::romViewMove ), NULL, this );
	pnlRom->Connect( wxEVT_RIGHT_UP, wxMouseEventHandler( mainForm::romViewRUp ), NULL, this );
	pnlRom->Connect( wxEVT_SIZE, wxSizeEventHandler( mainForm::romViewSizeChanged ), NULL, this );
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
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( mainForm::closeWindow ) );
	treeGameObjs->Disconnect( wxEVT_COMMAND_TREE_BEGIN_LABEL_EDIT, wxTreeEventHandler( mainForm::gameObjTItemBeginEdit ), NULL, this );
	treeGameObjs->Disconnect( wxEVT_COMMAND_TREE_END_LABEL_EDIT, wxTreeEventHandler( mainForm::gameObjTItemChangeName ), NULL, this );
	treeGameObjs->Disconnect( wxEVT_COMMAND_TREE_ITEM_MENU, wxTreeEventHandler( mainForm::gameObjTItemOpenMenu ), NULL, this );
	treeGameObjs->Disconnect( wxEVT_COMMAND_TREE_SEL_CHANGED, wxTreeEventHandler( mainForm::gameObjTItemSelected ), NULL, this );
	rbnObjectSprite->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( mainForm::gameObjSpriteClicked ), NULL, this );
	rbnObjectBG->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( mainForm::gameObjBGClicked ), NULL, this );
	btnGameObjBGColour->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::gameObjBGColour ), NULL, this );
	spnBrightness->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::replaceBrightnessChanged ), NULL, this );
	chkGameObjIsDefault->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainForm::gameObjDefaultClicked ), NULL, this );
	zoomGameObjs->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::zoomGameObjsChanged ), NULL, this );
	cboFrameRange->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( mainForm::ShowSelectedFrame ), NULL, this );
	pnlGameObjRaw->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( mainForm::gameObjsRawEnter ), NULL, this );
	pnlGameObjRaw->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( mainForm::gameObjsRawLDown ), NULL, this );
	pnlGameObjRaw->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( mainForm::gameObjsRawLUp ), NULL, this );
	pnlGameObjRaw->Disconnect( wxEVT_MOTION, wxMouseEventHandler( mainForm::gameObjsRawMove ), NULL, this );
	pnlGameObjRaw->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( mainForm::gameObjsRawRUp ), NULL, this );
	pnlGameObjRaw->Disconnect( wxEVT_SIZE, wxSizeEventHandler( mainForm::gameObjsRawSizeChanged ), NULL, this );
	scrGameObjRawV->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawV->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::gameObjsRawVScrolled ), NULL, this );
	scrGameObjRawH->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	scrGameObjRawH->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::gameObjsRawHScrolled ), NULL, this );
	pnlGameObjNew->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( mainForm::gameObjsNewEnter ), NULL, this );
	pnlGameObjNew->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( mainForm::gameObjsNewLDown ), NULL, this );
	pnlGameObjNew->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( mainForm::gameObjsNewLUp ), NULL, this );
	pnlGameObjNew->Disconnect( wxEVT_MOTION, wxMouseEventHandler( mainForm::gameObjsNewMove ), NULL, this );
	pnlGameObjNew->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( mainForm::gameObjsNewRUp ), NULL, this );
	pnlGameObjNew->Disconnect( wxEVT_SIZE, wxSizeEventHandler( mainForm::gameObjsNewSizeChanged ), NULL, this );
	scrGameObjNewV->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewV->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::gameObjsNewVScrolled ), NULL, this );
	scrGameObjNewH->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	scrGameObjNewH->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( mainForm::gameObjsNewHScrolled ), NULL, this );
	lstSwaps->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::SwapSeleted ), NULL, this );
	lstPalettes->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::SwapPaletteSelected ), NULL, this );
	txtSwapPaletteNew->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( mainForm::SwapPaletteNewChanged ), NULL, this );
	btnNewPaletteBG->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::SwapNewPaletteBGClicked ), NULL, this );
	btnNewPalette1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::SwapNewPalette1Clicked ), NULL, this );
	btnNewPalette2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::SwapNewPalette2Clicked ), NULL, this );
	btnNewPalette3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::SwapNewPalette3Clicked ), NULL, this );
	spnSwapNewBrightness->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::SwapNewBrightnessChanged ), NULL, this );
	spnSwapRotateHue->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::SwapRotateHueChanged ), NULL, this );
	spnSwapNewSaturation->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::SwapNewSaturationChanged ), NULL, this );
	btnAddSwap->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::AddSwapClicked ), NULL, this );
	btnUpdateSwap->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::UpdateSwapClicked ), NULL, this );
	btnDeleteSwap->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::DeleteSwapClicked ), NULL, this );
	btnBGImage->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::BGImageSelect ), NULL, this );
	spnBGBrightness->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::BGImageBrightness ), NULL, this );
	spnBGHScrollRate->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::BGImageHScrollRate ), NULL, this );
	spnBGVScrollRate->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::BGImageVScrollRate ), NULL, this );
	chkBgShowBehind->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( mainForm::BGImageShowBehindClicked ), NULL, this );
	lstConditions->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::ConditionSelected ), NULL, this );
	cboConditionType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( mainForm::ConditionTypeSelect ), NULL, this );
	cmdConditionAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::ConditionAdd ), NULL, this );
	cmdConditionUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::ConditionUpdate ), NULL, this );
	cmdConditionDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::ConditionDelete ), NULL, this );
	lstFrameRange->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::FrameRangeItemSelected ), NULL, this );
	cmdFrameRangeAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::AddFrameRangeClicked ), NULL, this );
	cmdFrameRangeUpdate->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::UpdateFrameRangeClicked ), NULL, this );
	cmdFrameRangeDelete->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::DeleteFrameRangeClicked ), NULL, this );
	cmdFrameRangeMoveUp->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::MoveUpFrameRange ), NULL, this );
	cmdFrameRangeMoveDown->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::MoveDownFrameRange ), NULL, this );
	lstHDImg->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::HDImgSelected ), NULL, this );
	btnHDImgAdd->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::HDImgAdd ), NULL, this );
	btnHDImgRemove->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::HDImgRemove ), NULL, this );
	lstHDImgTiles->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( mainForm::HDImgTileSelected ), NULL, this );
	pnlHDImg->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( mainForm::HDImgEnter ), NULL, this );
	pnlHDImg->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( mainForm::HDImgLDown ), NULL, this );
	pnlHDImg->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( mainForm::HDImgLUp ), NULL, this );
	pnlHDImg->Disconnect( wxEVT_MOTION, wxMouseEventHandler( mainForm::HDImgMove ), NULL, this );
	pnlHDImg->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( mainForm::HDImgRUp ), NULL, this );
	pnlHDImg->Disconnect( wxEVT_SIZE, wxSizeEventHandler( mainForm::HDImgSizeChanged ), NULL, this );
	zoomRom->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( mainForm::zoomRomChanged ), NULL, this );
	btnRomViewBGColour->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romBGColour ), NULL, this );
	btnRomViewColour1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour1 ), NULL, this );
	btnRomViewColour2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour2 ), NULL, this );
	btnRomViewColour3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( mainForm::romColour3 ), NULL, this );
	txtRomViewPalette->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( mainForm::romViewPaletteHexChanged ), NULL, this );
	pnlRom->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( mainForm::romViewEnter ), NULL, this );
	pnlRom->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( mainForm::romViewLDown ), NULL, this );
	pnlRom->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( mainForm::romViewLUp ), NULL, this );
	pnlRom->Disconnect( wxEVT_MOTION, wxMouseEventHandler( mainForm::romViewMove ), NULL, this );
	pnlRom->Disconnect( wxEVT_RIGHT_UP, wxMouseEventHandler( mainForm::romViewRUp ), NULL, this );
	pnlRom->Disconnect( wxEVT_SIZE, wxSizeEventHandler( mainForm::romViewSizeChanged ), NULL, this );
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

replacementDialog::replacementDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText13 = new wxStaticText( this, wxID_ANY, wxT("Select an image"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	bSizer29->Add( m_staticText13, 0, wxALL, 5 );

	cboImage = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY );
	bSizer29->Add( cboImage, 0, wxALL, 5 );


	bSizer28->Add( bSizer29, 0, 0, 5 );

	wxBoxSizer* bSizer31;
	bSizer31 = new wxBoxSizer( wxVERTICAL );

	m_staticText14 = new wxStaticText( this, wxID_ANY, wxT("Click on the image to choose the location of the replacement. Click once more to choose again."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer31->Add( m_staticText14, 0, wxALL, 5 );

	chkSnapToGrid = new wxCheckBox( this, wxID_ANY, wxT("Snap to grid"), wxDefaultPosition, wxDefaultSize, 0 );
	chkSnapToGrid->SetValue(true);
	bSizer31->Add( chkSnapToGrid, 0, wxALL, 5 );


	bSizer28->Add( bSizer31, 0, wxEXPAND, 5 );

	pnlImage = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer28->Add( pnlImage, 1, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxVERTICAL );

	m_button9 = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer30->Add( m_button9, 0, wxALL, 5 );


	bSizer28->Add( bSizer30, 0, wxALIGN_RIGHT, 5 );


	this->SetSizer( bSizer28 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	cboImage->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( replacementDialog::imageSelected ), NULL, this );
	pnlImage->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( replacementDialog::mouseClicked ), NULL, this );
	pnlImage->Connect( wxEVT_MOTION, wxMouseEventHandler( replacementDialog::mouseMoved ), NULL, this );
	pnlImage->Connect( wxEVT_SIZE, wxSizeEventHandler( replacementDialog::sizeChanged ), NULL, this );
	m_button9->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( replacementDialog::replacementConfirm ), NULL, this );
}

replacementDialog::~replacementDialog()
{
	// Disconnect Events
	cboImage->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( replacementDialog::imageSelected ), NULL, this );
	pnlImage->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( replacementDialog::mouseClicked ), NULL, this );
	pnlImage->Disconnect( wxEVT_MOTION, wxMouseEventHandler( replacementDialog::mouseMoved ), NULL, this );
	pnlImage->Disconnect( wxEVT_SIZE, wxSizeEventHandler( replacementDialog::sizeChanged ), NULL, this );
	m_button9->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( replacementDialog::replacementConfirm ), NULL, this );

}
