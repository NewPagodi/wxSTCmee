///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	m_mgr.SetManagedWindow(this);
	m_mgr.SetFlags(wxAUI_MGR_DEFAULT);
	
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	m_menuItem33 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Event log") ) , wxEmptyString, wxITEM_CHECK );
	m_menu1->Append( m_menuItem33 );
	m_menuItem33->Check( true );
	
	m_menuItem34 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Scintilla documentation") ) , wxEmptyString, wxITEM_CHECK );
	m_menu1->Append( m_menuItem34 );
	m_menuItem34->Check( true );
	
	m_menuItem35 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("STC documentation") ) , wxEmptyString, wxITEM_CHECK );
	m_menu1->Append( m_menuItem35 );
	m_menuItem35->Check( true );
	
	m_menu1->AppendSeparator();
	
	wxMenuItem* m_menuItem1;
	m_menuItem1 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Scintilla names") ) , wxEmptyString, wxITEM_CHECK );
	m_menu1->Append( m_menuItem1 );
	
	m_menubar1->Append( m_menu1, wxT("View") ); 
	
	m_menu2 = new wxMenu();
	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( m_menu2, MENU_STC_AUTOCOMP_CANCELLED, wxString( wxT("wxSTC_AUTOCOMP_CANCELLED") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem2 );
	
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu2, MENU_STC_AUTOCOMP_CHAR_DELETED, wxString( wxT("wxSTC_AUTOCOMP_CHAR_DELETED") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem3 );
	
	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem( m_menu2, MENU_STC_AUTOCOMP_SELECTION, wxString( wxT("wxSTC_AUTOCOMP_SELECTION") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem4 );
	
	wxMenuItem* m_menuItem5;
	m_menuItem5 = new wxMenuItem( m_menu2, MENU_STC_CALLTIP_CLICK, wxString( wxT("wxSTC_CALLTIP_CLICK") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem5 );
	
	wxMenuItem* m_menuItem6;
	m_menuItem6 = new wxMenuItem( m_menu2, MENU_STC_CHANGE, wxString( wxT("wxSTC_CHANGE") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem6 );
	
	wxMenuItem* m_menuItem7;
	m_menuItem7 = new wxMenuItem( m_menu2, MENU_STC_CHARADDED, wxString( wxT("wxSTC_CHARADDED") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem7 );
	
	wxMenuItem* m_menuItem8;
	m_menuItem8 = new wxMenuItem( m_menu2, MENU_STC_DOUBLECLICK, wxString( wxT("wxSTC_DOUBLECLICK") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem8 );
	
	wxMenuItem* m_menuItem9;
	m_menuItem9 = new wxMenuItem( m_menu2, MENU_STC_DWELLEND, wxString( wxT("wxSTC_DWELLEND") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem9 );
	
	wxMenuItem* m_menuItem10;
	m_menuItem10 = new wxMenuItem( m_menu2, MENU_STC_DWELLSTART, wxString( wxT("wxSTC_DWELLSTART") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem10 );
	
	wxMenuItem* m_menuItem11;
	m_menuItem11 = new wxMenuItem( m_menu2, MENU_STC_HOTSPOT_CLICK, wxString( wxT("wxSTC_HOTSPOT_CLICK") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem11 );
	
	wxMenuItem* m_menuItem12;
	m_menuItem12 = new wxMenuItem( m_menu2, MENU_STC_HOTSPOT_DCLICK, wxString( wxT("wxSTC_HOTSPOT_DCLICK") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem12 );
	
	wxMenuItem* m_menuItem13;
	m_menuItem13 = new wxMenuItem( m_menu2, MENU_STC_HOTSPOT_RELEASE_CLICK, wxString( wxT("wxSTC_HOTSPOT_RELEASE_CLICK") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem13 );
	
	wxMenuItem* m_menuItem14;
	m_menuItem14 = new wxMenuItem( m_menu2, MENU_STC_INDICATOR_CLICK, wxString( wxT("wxSTC_INDICATOR_CLICK") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem14 );
	
	wxMenuItem* m_menuItem15;
	m_menuItem15 = new wxMenuItem( m_menu2, MENU_STC_INDICATOR_RELEASE, wxString( wxT("wxSTC_INDICATOR_RELEASE") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem15 );
	
	wxMenuItem* m_menuItem16;
	m_menuItem16 = new wxMenuItem( m_menu2, MENU_STC_KEY, wxString( wxT("wxSTC_KEY") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem16 );
	
	wxMenuItem* m_menuItem17;
	m_menuItem17 = new wxMenuItem( m_menu2, MENU_STC_MACRORECORD, wxString( wxT("wxSTC_MACRORECORD") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem17 );
	
	wxMenuItem* m_menuItem18;
	m_menuItem18 = new wxMenuItem( m_menu2, MENU_STC_MARGINCLICK, wxString( wxT("wxSTC_MARGINCLICK") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem18 );
	
	wxMenuItem* m_menuItem19;
	m_menuItem19 = new wxMenuItem( m_menu2, MENU_STC_MODIFIED, wxString( wxT("wxSTC_MODIFIED") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem19 );
	
	wxMenuItem* m_menuItem20;
	m_menuItem20 = new wxMenuItem( m_menu2, MENU_STC_NEEDSHOWN, wxString( wxT("wxSTC_NEEDSHOWN") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem20 );
	
	wxMenuItem* m_menuItem21;
	m_menuItem21 = new wxMenuItem( m_menu2, MENU_STC_PAINTED, wxString( wxT("wxSTC_PAINTED") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem21 );
	
	wxMenuItem* m_menuItem22;
	m_menuItem22 = new wxMenuItem( m_menu2, MENU_STC_ROMODIFYATTEMPT, wxString( wxT("wxSTC_ROMODIFYATTEMPT") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem22 );
	
	wxMenuItem* m_menuItem23;
	m_menuItem23 = new wxMenuItem( m_menu2, MENU_STC_SAVEPOINTLEFT, wxString( wxT("wxSTC_SAVEPOINTLEFT") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem23 );
	
	wxMenuItem* m_menuItem24;
	m_menuItem24 = new wxMenuItem( m_menu2, MENU_STC_SAVEPOINTREACHED, wxString( wxT("wxSTC_SAVEPOINTREACHED") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem24 );
	
	wxMenuItem* m_menuItem25;
	m_menuItem25 = new wxMenuItem( m_menu2, MENU_STC_STYLENEEDED, wxString( wxT("wxSTC_STYLENEEDED") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem25 );
	
	wxMenuItem* m_menuItem26;
	m_menuItem26 = new wxMenuItem( m_menu2, MENU_STC_UPDATEUI, wxString( wxT("wxSTC_UPDATEUI") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem26 );
	
	wxMenuItem* m_menuItem27;
	m_menuItem27 = new wxMenuItem( m_menu2, MENU_STC_URIDROPPED, wxString( wxT("wxSTC_URIDROPPED") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem27 );
	
	wxMenuItem* m_menuItem28;
	m_menuItem28 = new wxMenuItem( m_menu2, MENU_STC_USERLISTSELECTION, wxString( wxT("wxSTC_USERLISTSELECTION") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem28 );
	
	wxMenuItem* m_menuItem29;
	m_menuItem29 = new wxMenuItem( m_menu2, MENU_STC_ZOOM, wxString( wxT("wxSTC_ZOOM") ) , wxEmptyString, wxITEM_CHECK );
	m_menu2->Append( m_menuItem29 );
	
	m_menubar1->Append( m_menu2, wxT("Logged Events") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	m_scintilla1 = new wxStyledTextCtrl(this);
	m_mgr.AddPane( m_scintilla1, wxAuiPaneInfo() .Name( wxT("m_scintilla1") ).Center() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BottomDockable( false ).TopDockable( false ).RightDockable( false ).Floatable( false ).CentrePane() );
	
	m_propgrid = new wxPropertyGrid(this,wxID_ANY,wxDefaultPosition,wxDefaultSize,wxPG_SPLITTER_AUTO_CENTER);
	m_mgr.AddPane( m_propgrid, wxAuiPaneInfo() .Name( wxT("m_propgrid") ).Right() .CaptionVisible( false ).CloseButton( false ).PaneBorder( false ).Dock().Resizable().FloatingSize( wxSize( -1,-1 ) ).DockFixed( false ).BottomDockable( false ).TopDockable( false ).LeftDockable( false ).Floatable( false ).BestSize( wxSize( 450,-1 ) ) );
	
	m_EventLog = new wxDataViewListCtrl(this,wxID_ANY);
	m_EventLog->AppendTextColumn("Time");
	m_EventLog->AppendTextColumn("Event Type");
	m_EventLog->AppendTextColumn("AnnotationsLinesAdded");
	m_EventLog->AppendTextColumn("Key");
	m_EventLog->AppendTextColumn("FoldLevelNow");
	m_EventLog->AppendTextColumn("FoldLevelPrev");
	m_EventLog->AppendTextColumn("Length");
	m_EventLog->AppendTextColumn("Line");
	m_EventLog->AppendTextColumn("LinesAdded");
	m_EventLog->AppendTextColumn("ListType");
	m_EventLog->AppendTextColumn("LParam");
	m_EventLog->AppendTextColumn("Margin");
	m_EventLog->AppendTextColumn("Message");
	m_EventLog->AppendTextColumn("ModificationType");
	m_EventLog->AppendTextColumn("Modifiers");
	m_EventLog->AppendTextColumn("Position");
	m_EventLog->AppendTextColumn("Text");
	m_EventLog->AppendTextColumn("Token");
	m_EventLog->AppendTextColumn("Updated");
	m_EventLog->AppendTextColumn("WParam");
	m_EventLog->AppendTextColumn("X");
	m_EventLog->AppendTextColumn("Y");
	m_mgr.AddPane( m_EventLog, wxAuiPaneInfo() .Name( wxT("m_EventLog") ).Bottom() .MaximizeButton( true ).PaneBorder( false ).Dock().Resizable().FloatingSize( wxSize( -1,-1 ) ).DockFixed( false ).Row( 1 ) );
	
	m_browser = wxWebView::New(this, wxID_ANY);
	   m_browser->RegisterHandler(wxSharedPtr<wxWebViewHandler>(new wxWebViewFSHandler("memory")));
	m_mgr.AddPane( m_browser, wxAuiPaneInfo() .Name( wxT("m_browser") ).Bottom() .MaximizeButton( true ).PaneBorder( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ).BestSize( wxSize( -1,200 ) ) );
	
	m_STCDoc = wxWebView::New(this, wxID_ANY);
	m_STCDoc->RegisterHandler(wxSharedPtr<wxWebViewHandler>(new wxWebViewFSHandler("memory")));
	m_mgr.AddPane( m_STCDoc, wxAuiPaneInfo() .Name( wxT("m_STCDoc") ).Bottom() .MaximizeButton( true ).PaneBorder( false ).Dock().Resizable().FloatingSize( wxDefaultSize ).DockFixed( false ) );
	
	statusBar = this->CreateStatusBar( 2, wxST_SIZEGRIP, wxID_ANY );
	
	m_mgr.Update();
	
	// Connect Events
	this->Connect( wxEVT_AUI_PANE_CLOSE, wxAuiManagerEventHandler( GUIFrame::onAuiPaneClose ) );
	this->Connect( wxEVT_AUI_PANE_MAXIMIZE, wxAuiManagerEventHandler( GUIFrame::OnAuiPaneMaxemize ) );
	this->Connect( wxEVT_AUI_PANE_RESTORE, wxAuiManagerEventHandler( GUIFrame::OnAuiPaneRestore ) );
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Connect( m_menuItem33->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onViewEventLog ) );
	this->Connect( m_menuItem34->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onViewSciDoc ) );
	this->Connect( m_menuItem35->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onViewStcDoc ) );
	this->Connect( m_menuItem1->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::On3rdColumnMenu ) );
	this->Connect( m_menuItem2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem3->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem4->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem5->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem6->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem7->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem8->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem9->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem10->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem11->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem12->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem13->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem14->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem15->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem16->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem17->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem18->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem19->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem20->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem21->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem22->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem23->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem24->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem25->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem26->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem27->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem28->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Connect( m_menuItem29->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_AUI_PANE_CLOSE, wxAuiManagerEventHandler( GUIFrame::onAuiPaneClose ) );
	this->Disconnect( wxEVT_AUI_PANE_MAXIMIZE, wxAuiManagerEventHandler( GUIFrame::OnAuiPaneMaxemize ) );
	this->Disconnect( wxEVT_AUI_PANE_RESTORE, wxAuiManagerEventHandler( GUIFrame::OnAuiPaneRestore ) );
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onViewEventLog ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onViewSciDoc ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onViewStcDoc ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::On3rdColumnMenu ) );
	this->Disconnect( MENU_STC_AUTOCOMP_CANCELLED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_AUTOCOMP_CHAR_DELETED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_AUTOCOMP_SELECTION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_CALLTIP_CLICK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_CHANGE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_CHARADDED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_DOUBLECLICK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_DWELLEND, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_DWELLSTART, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_HOTSPOT_CLICK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_HOTSPOT_DCLICK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_HOTSPOT_RELEASE_CLICK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_INDICATOR_CLICK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_INDICATOR_RELEASE, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_KEY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_MACRORECORD, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_MARGINCLICK, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_MODIFIED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_NEEDSHOWN, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_PAINTED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_ROMODIFYATTEMPT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_SAVEPOINTLEFT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_SAVEPOINTREACHED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_STYLENEEDED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_UPDATEUI, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_URIDROPPED, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_USERLISTSELECTION, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	this->Disconnect( MENU_STC_ZOOM, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::onSTCLogMenu ) );
	
	m_mgr.UnInit();
	
}

MyDialog1::MyDialog1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 525,700 ), wxTAB_TRAVERSAL );
	bSizer1->Add( m_panel1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_panel1->Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( MyDialog1::OnEraseBackground ), NULL, this );
	m_panel1->Connect( wxEVT_PAINT, wxPaintEventHandler( MyDialog1::OnPaint ), NULL, this );
}

MyDialog1::~MyDialog1()
{
	// Disconnect Events
	m_panel1->Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( MyDialog1::OnEraseBackground ), NULL, this );
	m_panel1->Disconnect( wxEVT_PAINT, wxPaintEventHandler( MyDialog1::OnPaint ), NULL, this );
	
}

MyDialog2::MyDialog2( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );
	
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Text") ), wxVERTICAL );
	
	m_textCtrl1 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE );
	sbSizer1->Add( m_textCtrl1, 1, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, wxT("Current Style:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer5->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_spinCtrl1 = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 255, 0 );
	bSizer5->Add( m_spinCtrl1, 0, wxALL, 5 );
	
	
	sbSizer1->Add( bSizer5, 0, wxALIGN_RIGHT, 5 );
	
	
	bSizer3->Add( sbSizer1, 1, wxEXPAND|wxALL, 5 );
	
	m_dataView1 = new wxDataViewCtrl(this,wxID_ANY,wxDefaultPosition,wxSize(150,-1)) ;
	dvlsModel = new wxDataViewListStore;
	
	m_dataView1->AssociateModel( dvlsModel.get() );
	
	dvlsModel->AppendColumn ("string");
	dvlsModel->AppendColumn ("long");
	
	m_dataView1->AppendTextColumn ("Character", 0,wxDATAVIEW_CELL_INERT,65, wxALIGN_LEFT);
	bSizer3->Add( m_dataView1, 0, wxALL|wxEXPAND, 5 );
	
	
	bSizer2->Add( bSizer3, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button5 = new wxButton( this, wxID_ANY, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button5->Hide();
	
	bSizer4->Add( m_button5, 0, wxALL, 5 );
	
	m_button1 = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button1, 0, wxALL, 5 );
	
	m_button2 = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button2, 0, wxALL, 5 );
	
	
	bSizer2->Add( bSizer4, 0, wxALL|wxALIGN_RIGHT, 5 );
	
	
	this->SetSizer( bSizer2 );
	this->Layout();
	bSizer2->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_textCtrl1->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyDialog2::onText ), NULL, this );
	m_button5->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog2::onClose ), NULL, this );
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog2::onCancel ), NULL, this );
	m_button2->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog2::onOK ), NULL, this );
}

MyDialog2::~MyDialog2()
{
	// Disconnect Events
	m_textCtrl1->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( MyDialog2::onText ), NULL, this );
	m_button5->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog2::onClose ), NULL, this );
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog2::onCancel ), NULL, this );
	m_button2->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog2::onOK ), NULL, this );
	
}

MyDialog3::MyDialog3( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, wxT("Key"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer1->Add( m_staticText2, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_textCtrl2 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer1->Add( m_textCtrl2, 0, wxALL, 5 );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("KeyCode"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer1->Add( m_staticText3, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxTOP|wxBOTTOM|wxLEFT, 5 );
	
	m_textCtrl3 = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	fgSizer1->Add( m_textCtrl3, 0, wxALL, 5 );
	
	
	bSizer6->Add( fgSizer1, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button3 = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer7->Add( m_button3, 0, wxALL, 5 );
	
	m_button4 = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button4->Enable( false );
	
	bSizer7->Add( m_button4, 0, wxALL, 5 );
	
	
	bSizer6->Add( bSizer7, 0, wxALL, 5 );
	
	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,1 ), wxTAB_TRAVERSAL|wxWANTS_CHARS );
	bSizer6->Add( m_panel2, 1, wxEXPAND | wxALL, 5 );
	
	
	this->SetSizer( bSizer6 );
	this->Layout();
	bSizer6->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_button3->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog3::onCancel ), NULL, this );
	m_button4->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog3::onOK ), NULL, this );
}

MyDialog3::~MyDialog3()
{
	// Disconnect Events
	m_button3->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog3::onCancel ), NULL, this );
	m_button4->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog3::onOK ), NULL, this );
	
}

GUIRGBADialog::GUIRGBADialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_scrolledWindow1 = new wxScrolledWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxVSCROLL );
	m_scrolledWindow1->SetScrollRate( 5, 5 );
	bSizer8->Add( m_scrolledWindow1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxEXPAND, 5 );
	
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Color") ), wxVERTICAL );
	
	m_colourPicker1 = new wxColourPickerCtrl( this, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	sbSizer2->Add( m_colourPicker1, 0, wxALL, 5 );
	
	
	bSizer11->Add( sbSizer2, 0, wxALL, 5 );
	
	wxStaticBoxSizer* sbSizer3;
	sbSizer3 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Alpha") ), wxHORIZONTAL );
	
	m_slider1 = new wxSlider( this, wxID_ANY, 255, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	sbSizer3->Add( m_slider1, 0, wxALL, 5 );
	
	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("255"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	sbSizer3->Add( m_staticText4, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
	
	
	bSizer11->Add( sbSizer3, 0, wxALL, 5 );
	
	
	bSizer14->Add( bSizer11, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Reset  Image") ), wxHORIZONTAL );
	
	m_button6 = new wxButton( this, wxID_ANY, wxT("Set Transparent"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_button6, 0, wxALL, 5 );
	
	m_button7 = new wxButton( this, wxID_ANY, wxT("Set White"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_button7, 0, wxALL, 5 );
	
	m_button8 = new wxButton( this, wxID_ANY, wxT("Set Black"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( m_button8, 0, wxALL, 5 );
	
	
	bSizer14->Add( sbSizer4, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	wxStaticBoxSizer* sbSizer5;
	sbSizer5 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Preview") ), wxVERTICAL );
	
	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxTAB_TRAVERSAL );
	sbSizer5->Add( m_panel3, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	bSizer10->Add( sbSizer5, 0, wxALL, 5 );
	
	
	bSizer10->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_button9 = new wxButton( this, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_button9, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	m_button10 = new wxButton( this, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( m_button10, 0, wxALL|wxALIGN_BOTTOM, 5 );
	
	
	bSizer14->Add( bSizer10, 0, wxALL|wxALIGN_RIGHT|wxEXPAND, 5 );
	
	
	bSizer8->Add( bSizer14, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	this->SetSizer( bSizer8 );
	this->Layout();
	bSizer8->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_colourPicker1->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( GUIRGBADialog::onColorChanged ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_button6->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRGBADialog::onSetTransparent ), NULL, this );
	m_button7->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRGBADialog::onSetWhite ), NULL, this );
	m_button8->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRGBADialog::onSetBlack ), NULL, this );
	m_panel3->Connect( wxEVT_PAINT, wxPaintEventHandler( GUIRGBADialog::onPreviewPaint ), NULL, this );
}

GUIRGBADialog::~GUIRGBADialog()
{
	// Disconnect Events
	m_colourPicker1->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( GUIRGBADialog::onColorChanged ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_slider1->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( GUIRGBADialog::onSlider ), NULL, this );
	m_button6->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRGBADialog::onSetTransparent ), NULL, this );
	m_button7->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRGBADialog::onSetWhite ), NULL, this );
	m_button8->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIRGBADialog::onSetBlack ), NULL, this );
	m_panel3->Disconnect( wxEVT_PAINT, wxPaintEventHandler( GUIRGBADialog::onPreviewPaint ), NULL, this );
	
}

MyDialog5::MyDialog5( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxBoxSizer* bSizer191;
	bSizer191 = new wxBoxSizer( wxHORIZONTAL );
	
	m_panel5 = new wxPanel( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel5->SetBackgroundColour( wxColour( 127, 157, 185 ) );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	m_panel8 = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel8->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	m_panel6 = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel6->SetBackgroundColour( wxColour( 235, 234, 219 ) );
	
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );
	
	bSizer22 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText1 = new wxStaticText( m_panel6, wxID_ANY, wxT("Style"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer22->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );
	
	m_spinCtrl1 = new wxSpinCtrl( m_panel6, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	bSizer22->Add( m_spinCtrl1, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	m_staticText2 = new wxStaticText( m_panel6, wxID_ANY, wxT("Indicator"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	bSizer22->Add( m_staticText2, 0, wxALIGN_CENTER_VERTICAL|wxLEFT, 5 );
	
	m_spinCtrl2 = new wxSpinCtrl( m_panel6, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxSP_ARROW_KEYS, 0, 255, 0 );
	bSizer22->Add( m_spinCtrl2, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	m_button1 = new wxButton( m_panel6, wxID_ANY, wxT("Style Selection"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button1->Enable( false );
	
	bSizer22->Add( m_button1, 0, wxALIGN_CENTER_VERTICAL|wxRIGHT|wxLEFT, 5 );
	
	
	bSizer17->Add( bSizer22, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	m_panel6->SetSizer( bSizer17 );
	m_panel6->Layout();
	bSizer17->Fit( m_panel6 );
	bSizer19->Add( m_panel6, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 1 );
	
	m_panel9 = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxSize( -1,1 ), wxTAB_TRAVERSAL );
	m_panel9->SetBackgroundColour( wxColour( 226, 222, 205 ) );
	
	bSizer19->Add( m_panel9, 0, wxEXPAND|wxRIGHT|wxLEFT, 1 );
	
	m_panel10 = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxSize( -1,1 ), wxTAB_TRAVERSAL );
	m_panel10->SetBackgroundColour( wxColour( 214, 210, 194 ) );
	
	bSizer19->Add( m_panel10, 0, wxEXPAND|wxRIGHT|wxLEFT, 1 );
	
	m_panel11 = new wxPanel( m_panel8, wxID_ANY, wxDefaultPosition, wxSize( -1,1 ), wxTAB_TRAVERSAL );
	m_panel11->SetBackgroundColour( wxColour( 203, 199, 184 ) );
	
	bSizer19->Add( m_panel11, 0, wxEXPAND|wxRIGHT|wxLEFT, 1 );
	
	
	bSizer19->Add( 0, 5, 0, 0, 5 );
	
	m_STC = new wxStyledTextCtrl(m_panel8,wxID_ANY, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	bSizer19->Add( m_STC, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 1 );
	
	
	m_panel8->SetSizer( bSizer19 );
	m_panel8->Layout();
	bSizer19->Fit( m_panel8 );
	bSizer16->Add( m_panel8, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 1 );
	
	m_panel16 = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxSize( -1,1 ), wxTAB_TRAVERSAL );
	m_panel16->SetBackgroundColour( wxColour( 149, 147, 133 ) );
	
	bSizer16->Add( m_panel16, 0, wxEXPAND|wxRIGHT|wxLEFT, 1 );
	
	m_panel161 = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxSize( -1,1 ), wxTAB_TRAVERSAL );
	m_panel161->SetBackgroundColour( wxColour( 192, 190, 180 ) );
	
	bSizer16->Add( m_panel161, 0, wxEXPAND|wxRIGHT|wxLEFT, 1 );
	
	m_panel162 = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxSize( -1,1 ), wxTAB_TRAVERSAL );
	m_panel162->SetBackgroundColour( wxColour( 216, 215, 204 ) );
	
	bSizer16->Add( m_panel162, 0, wxEXPAND|wxRIGHT|wxLEFT, 1 );
	
	m_panel163 = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxSize( -1,1 ), wxTAB_TRAVERSAL );
	m_panel163->SetBackgroundColour( wxColour( 232, 232, 221 ) );
	
	bSizer16->Add( m_panel163, 0, wxEXPAND|wxRIGHT|wxLEFT, 1 );
	
	wxBoxSizer* bSizer161;
	bSizer161 = new wxBoxSizer( wxHORIZONTAL );
	
	m_textCtrl1 = new wxTextCtrl( m_panel5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY|wxNO_BORDER );
	bSizer161->Add( m_textCtrl1, 1, wxALIGN_CENTER_HORIZONTAL|wxLEFT, 1 );
	
	m_textCtrl3 = new wxTextCtrl( m_panel5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY|wxNO_BORDER );
	bSizer161->Add( m_textCtrl3, 1, 0, 5 );
	
	m_textCtrl2 = new wxTextCtrl( m_panel5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY|wxNO_BORDER );
	bSizer161->Add( m_textCtrl2, 1, wxRIGHT, 1 );
	
	
	bSizer16->Add( bSizer161, 0, wxEXPAND, 5 );
	
	m_panel15 = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxSize( -1,1 ), wxTAB_TRAVERSAL );
	m_panel15->SetBackgroundColour( wxColour( 217, 214, 192 ) );
	
	bSizer16->Add( m_panel15, 0, wxEXPAND|wxRIGHT|wxLEFT, 1 );
	
	m_panel24 = new wxPanel( m_panel5, wxID_ANY, wxDefaultPosition, wxSize( -1,1 ), wxTAB_TRAVERSAL );
	m_panel24->SetBackgroundColour( wxColour( 223, 220, 202 ) );
	
	bSizer16->Add( m_panel24, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 1 );
	
	
	m_panel5->SetSizer( bSizer16 );
	m_panel5->Layout();
	bSizer16->Fit( m_panel5 );
	bSizer191->Add( m_panel5, 1, wxEXPAND|wxALL, 5 );
	
	m_panel3 = new wxPanel( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel3->SetBackgroundColour( wxColour( 127, 157, 185 ) );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_panel4 = new wxPanel( m_panel3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel4->SetBackgroundColour( wxColour( 255, 255, 255 ) );
	
	bSizer5 = new wxBoxSizer( wxVERTICAL );
	
	m_grid1 = new wxGrid( m_panel4, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), 0 );
	
	// Grid
	m_grid1->CreateGrid( 0, 4 );
	m_grid1->EnableEditing( true );
	m_grid1->EnableGridLines( false );
	m_grid1->EnableDragGridSize( false );
	m_grid1->SetMargins( 0, 0 );
	
	// Columns
	m_grid1->EnableDragColMove( false );
	m_grid1->EnableDragColSize( false );
	m_grid1->SetColLabelSize( 30 );
	m_grid1->SetColLabelValue( 0, wxT("Pos.") );
	m_grid1->SetColLabelValue( 1, wxT("Char.") );
	m_grid1->SetColLabelValue( 2, wxT("Style") );
	m_grid1->SetColLabelValue( 3, wxT("Indic.") );
	m_grid1->SetColLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Rows
	m_grid1->EnableDragRowSize( false );
	m_grid1->SetRowLabelSize( 0 );
	m_grid1->SetRowLabelAlignment( wxALIGN_CENTRE, wxALIGN_CENTRE );
	
	// Label Appearance
	m_grid1->SetLabelFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 90, false, wxEmptyString ) );
	
	// Cell Defaults
	m_grid1->SetDefaultCellAlignment( wxALIGN_LEFT, wxALIGN_TOP );
	m_menu3 = new wxMenu();
	wxMenuItem* m_menuItem4;
	m_menuItem4 = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Copy") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItem4 );
	
	m_menuItem5 = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Paste") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu3->Append( m_menuItem5 );
	
	m_menu3->AppendSeparator();
	
	wxMenuItem* m_menuItem3;
	m_menuItem3 = new wxMenuItem( m_menu3, wxID_ANY, wxString( wxT("Use Spin Controls") ) , wxEmptyString, wxITEM_CHECK );
	m_menu3->Append( m_menuItem3 );
	
	m_grid1->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( MyDialog5::m_grid1OnContextMenu ), NULL, this ); 
	
	bSizer5->Add( m_grid1, 1, wxALL|wxEXPAND, 1 );
	
	
	m_panel4->SetSizer( bSizer5 );
	m_panel4->Layout();
	bSizer5->Fit( m_panel4 );
	bSizer8->Add( m_panel4, 1, wxALL, 1 );
	
	
	m_panel3->SetSizer( bSizer8 );
	m_panel3->Layout();
	bSizer8->Fit( m_panel3 );
	bSizer191->Add( m_panel3, 0, wxEXPAND|wxALL, 5 );
	
	
	bSizer4->Add( bSizer191, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	m_button2 = new wxButton( m_panel1, wxID_CANCEL, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer21->Add( m_button2, 0, wxALL, 5 );
	
	m_button3 = new wxButton( m_panel1, wxID_OK, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer21->Add( m_button3, 0, wxALL, 5 );
	
	m_button14 = new wxButton( m_panel1, wxID_CANCEL, wxT("Close"), wxDefaultPosition, wxDefaultSize, 0 );
	m_button14->Hide();
	
	bSizer21->Add( m_button14, 0, wxALL, 5 );
	
	
	bSizer4->Add( bSizer21, 0, wxALIGN_RIGHT|wxALL, 5 );
	
	
	m_panel1->SetSizer( bSizer4 );
	m_panel1->Layout();
	bSizer4->Fit( m_panel1 );
	bSizer1->Add( m_panel1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_button1->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog5::onB ), NULL, this );
	this->Connect( m_menuItem4->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyDialog5::onCopy ) );
	this->Connect( m_menuItem5->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyDialog5::onPaste ) );
	this->Connect( m_menuItem3->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyDialog5::onUseSpins ) );
}

MyDialog5::~MyDialog5()
{
	// Disconnect Events
	m_button1->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MyDialog5::onB ), NULL, this );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyDialog5::onCopy ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyDialog5::onPaste ) );
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MyDialog5::onUseSpins ) );
	
	delete m_menu3; 
}
