///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __GUIFRAME_H__
#define __GUIFRAME_H__

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
#include <wx/stc/stc.h>
#include <wx/propgrid/propgrid.h>
#include <wx/webview.h>
#include <wx/webviewfshandler.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/spinctrl.h>
#include <wx/statbox.h>
#include <wx/dataview.h>
#include <wx/button.h>
#include <wx/scrolwin.h>
#include <wx/clrpicker.h>
#include <wx/slider.h>
#include <wx/grid.h>

///////////////////////////////////////////////////////////////////////////

#define MENU_STC_AUTOCOMP_CANCELLED 1000
#define MENU_STC_AUTOCOMP_CHAR_DELETED 1001
#define MENU_STC_AUTOCOMP_SELECTION 1002
#define MENU_STC_CALLTIP_CLICK 1003
#define MENU_STC_CHANGE 1004
#define MENU_STC_CHARADDED 1005
#define MENU_STC_DOUBLECLICK 1006
#define MENU_STC_DWELLEND 1007
#define MENU_STC_DWELLSTART 1008
#define MENU_STC_HOTSPOT_CLICK 1009
#define MENU_STC_HOTSPOT_DCLICK 1010
#define MENU_STC_HOTSPOT_RELEASE_CLICK 1011
#define MENU_STC_INDICATOR_CLICK 1012
#define MENU_STC_INDICATOR_RELEASE 1013
#define MENU_STC_KEY 1014
#define MENU_STC_MACRORECORD 1015
#define MENU_STC_MARGINCLICK 1016
#define MENU_STC_MODIFIED 1017
#define MENU_STC_NEEDSHOWN 1018
#define MENU_STC_PAINTED 1019
#define MENU_STC_ROMODIFYATTEMPT 1020
#define MENU_STC_SAVEPOINTLEFT 1021
#define MENU_STC_SAVEPOINTREACHED 1022
#define MENU_STC_STYLENEEDED 1023
#define MENU_STC_UPDATEUI 1024
#define MENU_STC_URIDROPPED 1025
#define MENU_STC_USERLISTSELECTION 1026
#define MENU_STC_ZOOM 1027

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame 
{
	private:
	
	protected:
		wxMenuBar* m_menubar1;
		wxMenu* m_menu1;
		wxMenuItem* m_menuItem33;
		wxMenuItem* m_menuItem34;
		wxMenuItem* m_menuItem35;
		wxMenu* m_menu2;
		wxStyledTextCtrl* m_scintilla1;
		wxPropertyGrid* m_propgrid;
		wxDataViewListCtrl* m_EventLog;
		wxWebView* m_browser;
		wxWebView* m_STCDoc;
		wxStatusBar* statusBar;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onAuiPaneClose( wxAuiManagerEvent& event ) { event.Skip(); }
		virtual void OnAuiPaneMaxemize( wxAuiManagerEvent& event ) { event.Skip(); }
		virtual void OnAuiPaneRestore( wxAuiManagerEvent& event ) { event.Skip(); }
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void onViewEventLog( wxCommandEvent& event ) { event.Skip(); }
		virtual void onViewSciDoc( wxCommandEvent& event ) { event.Skip(); }
		virtual void onViewStcDoc( wxCommandEvent& event ) { event.Skip(); }
		virtual void On3rdColumnMenu( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSTCLogMenu( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("wxWidgets Application Template"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 900,675 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
		wxAuiManager m_mgr;
		
		~GUIFrame();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MyDialog1
///////////////////////////////////////////////////////////////////////////////
class MyDialog1 : public wxDialog 
{
	private:
	
	protected:
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnEraseBackground( wxEraseEvent& event ) { event.Skip(); }
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		
	
	public:
		wxPanel* m_panel1;
		
		MyDialog1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~MyDialog1();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MyDialog2
///////////////////////////////////////////////////////////////////////////////
class MyDialog2 : public wxDialog 
{
	private:
	
	protected:
		wxStaticBoxSizer* sbSizer1;
		wxTextCtrl* m_textCtrl1;
		wxStaticText* m_staticText1;
		wxSpinCtrl* m_spinCtrl1;
		wxDataViewCtrl* m_dataView1;
		wxObjectDataPtr<wxDataViewListStore> dvlsModel;
		wxButton* m_button5;
		wxButton* m_button1;
		wxButton* m_button2;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onText( wxCommandEvent& event ) { event.Skip(); }
		virtual void onClose( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOK( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyDialog2( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~MyDialog2();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MyDialog3
///////////////////////////////////////////////////////////////////////////////
class MyDialog3 : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText2;
		wxTextCtrl* m_textCtrl2;
		wxStaticText* m_staticText3;
		wxTextCtrl* m_textCtrl3;
		wxButton* m_button3;
		wxButton* m_button4;
		wxPanel* m_panel2;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onCancel( wxCommandEvent& event ) { event.Skip(); }
		virtual void onOK( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyDialog3( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Press a keyboard key..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~MyDialog3();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class GUIRGBADialog
///////////////////////////////////////////////////////////////////////////////
class GUIRGBADialog : public wxDialog 
{
	private:
	
	protected:
		wxScrolledWindow* m_scrolledWindow1;
		wxBoxSizer* bSizer14;
		wxColourPickerCtrl* m_colourPicker1;
		wxSlider* m_slider1;
		wxStaticText* m_staticText4;
		wxButton* m_button6;
		wxButton* m_button7;
		wxButton* m_button8;
		wxPanel* m_panel3;
		wxButton* m_button9;
		wxButton* m_button10;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onColorChanged( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void onSlider( wxScrollEvent& event ) { event.Skip(); }
		virtual void onSetTransparent( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSetWhite( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSetBlack( wxCommandEvent& event ) { event.Skip(); }
		virtual void onPreviewPaint( wxPaintEvent& event ) { event.Skip(); }
		
	
	public:
		
		GUIRGBADialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("RGBA Data"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER ); 
		~GUIRGBADialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class MyDialog5
///////////////////////////////////////////////////////////////////////////////
class MyDialog5 : public wxDialog 
{
	private:
	
	protected:
		wxPanel* m_panel1;
		wxPanel* m_panel5;
		wxPanel* m_panel8;
		wxPanel* m_panel6;
		wxBoxSizer* bSizer22;
		wxStaticText* m_staticText1;
		wxSpinCtrl* m_spinCtrl1;
		wxStaticText* m_staticText2;
		wxSpinCtrl* m_spinCtrl2;
		wxButton* m_button1;
		wxPanel* m_panel9;
		wxPanel* m_panel10;
		wxPanel* m_panel11;
		wxStyledTextCtrl* m_STC;
		wxPanel* m_panel16;
		wxPanel* m_panel161;
		wxPanel* m_panel162;
		wxPanel* m_panel163;
		wxTextCtrl* m_textCtrl1;
		wxTextCtrl* m_textCtrl3;
		wxTextCtrl* m_textCtrl2;
		wxPanel* m_panel15;
		wxPanel* m_panel24;
		wxPanel* m_panel3;
		wxPanel* m_panel4;
		wxBoxSizer* bSizer5;
		wxGrid* m_grid1;
		wxMenu* m_menu3;
		wxMenuItem* m_menuItem5;
		wxButton* m_button2;
		wxButton* m_button3;
		wxButton* m_button14;
		
		// Virtual event handlers, overide them in your derived class
		virtual void onB( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCopy( wxCommandEvent& event ) { event.Skip(); }
		virtual void onPaste( wxCommandEvent& event ) { event.Skip(); }
		virtual void onUseSpins( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MyDialog5( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxCAPTION|wxRESIZE_BORDER ); 
		~MyDialog5();
		
		void m_grid1OnContextMenu( wxMouseEvent &event )
		{
			m_grid1->PopupMenu( m_menu3, event.GetPosition() );
		}
	
};

#endif //__GUIFRAME_H__
