/***************************************************************
 * Name:      propgridtest03Main.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2014-08-16
 * Copyright:  ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "stcMain.h"
#include <wx/fs_mem.h>
#include <wx/dcmemory.h>

#include "lexers.h"
#include "scintilla/ScintillaDoc.c"
//#include <wx/mstream.h>
#include "scintilla/SciTEIco.c"
#include "scintilla/styledmargin.c"
#include "scintilla/annotations.c"
//#include <wx/wfstream.h>
//#include "test.c"

#include "Editors.h"

#include "wxWidgets/doxygen.c"
#include "wxWidgets/extra_stylesheet.c"
#include "wxWidgets/wxStyledTextCtrl.c"
//



propgridtest03Frame::propgridtest03Frame(wxFrame *frame): GUIFrameWEnum(frame)
{
    //m_mgr.LoadPerspective("layout2|name=m_scintilla1;caption=;state=768;dir=5;layer=0;row=0;pos=0;prop=100000;bestw=196;besth=79;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_propgrid;caption=;state=392;dir=2;layer=0;row=0;pos=0;prop=100000;bestw=450;besth=-1;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_EventLog;caption=;state=2098684;dir=3;layer=0;row=1;pos=0;prop=100000;bestw=96;besth=76;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=392;floaty=459;floatw=104;floath=102|name=m_browser;caption=;state=12584876;dir=3;layer=0;row=0;pos=0;prop=100000;bestw=-1;besth=200;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_STCDoc;caption=;state=14682108;dir=3;layer=0;row=0;pos=1;prop=100000;bestw=16;besth=16;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|dock_size(5,0,0)=198|dock_size(2,0,0)=444|dock_size(3,0,0)=180|dock_size(3,0,1)=152|");

    eventLogInfo = m_mgr.GetPane(m_EventLog);
    sciDocInfo   = m_mgr.GetPane(m_browser);
    stcDocInfo   = m_mgr.GetPane(m_STCDoc);
    codeLogInfo = m_mgr.GetPane(m_CodeLog);

    toBeDetached=nullptr;

    m_CodeLog->SetMarginWidth(1,0);
    m_CodeLog->SetLexer(wxSTC_LEX_CPP);
    m_CodeLog->StyleSetFaceName(wxSTC_STYLE_DEFAULT,"Courier New");
    m_CodeLog->StyleSetSize(wxSTC_STYLE_DEFAULT,8);
	m_CodeLog->StyleClearAll();
    m_CodeLog->SetKeyWords(0,"if else switch case default break goto return for while do continue typedef sizeof NULL new delete throw try catch namespace");
    m_CodeLog->SetKeyWords(1,"void struct union enum char short int long double float signed unsigned const static extern auto register volatile bool class private protected public friend inline template virtual asm explicit typename mutable");

    m_CodeLog->StyleSetForeground(wxSTC_C_COMMENT,               wxColor(0,128,0));
    m_CodeLog->StyleSetForeground(wxSTC_C_COMMENTLINE,           wxColor(0,128,0)  );
    m_CodeLog->StyleSetForeground(wxSTC_C_COMMENTDOC,            wxColor(0,128,128)  );
    m_CodeLog->StyleSetForeground(wxSTC_C_NUMBER,                wxColor(255,128,0) );
    m_CodeLog->StyleSetForeground(wxSTC_C_WORD,                  wxColor(0,0,255));
	m_CodeLog->StyleSetBold(wxSTC_C_WORD,true);
    m_CodeLog->StyleSetForeground(wxSTC_C_STRING,                wxColor(128,128,128) );
    m_CodeLog->StyleSetForeground(wxSTC_C_CHARACTER,             wxColor(128,128,128) );
    m_CodeLog->StyleSetForeground(wxSTC_C_PREPROCESSOR,          wxColor(128,64,0) );
    m_CodeLog->StyleSetForeground(wxSTC_C_OPERATOR,              wxColor(0,0,128));
	m_CodeLog->StyleSetBold(wxSTC_C_OPERATOR,true);
    m_CodeLog->StyleSetForeground(wxSTC_C_REGEX,                 wxColor(0,0,0) );
    m_CodeLog->StyleSetForeground(wxSTC_C_COMMENTLINEDOC,        wxColor(0,128,128));
    m_CodeLog->StyleSetForeground(wxSTC_C_WORD2,                 wxColor(128,0,255));
    m_CodeLog->StyleSetForeground(wxSTC_C_COMMENTDOCKEYWORD,     wxColor(0,128,128));
    m_CodeLog->StyleSetForeground(wxSTC_C_COMMENTDOCKEYWORDERROR,wxColor(0,128,128) );
    m_CodeLog->SetProperty("lexer.cpp.track.preprocessor","0");
    m_CodeLog->SetExtraAscent(1);
    m_CodeLog->SetExtraDescent(1);

    m_CodeLog->Show(false);
    m_mgr.DetachPane(m_CodeLog);



    m_mgr.LoadPerspective("layout2|name=m_scintilla1;caption=;state=768;dir=5;layer=0;row=0;pos=0;prop=100000;bestw=196;besth=79;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_propgrid;caption=;state=392;dir=2;layer=0;row=0;pos=0;prop=100000;bestw=450;besth=-1;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_EventLog;caption=Event Log;state=6292988;dir=3;layer=0;row=3;pos=0;prop=100000;bestw=96;besth=76;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_browser;caption=Scintilla Documentation;state=6292988;dir=3;layer=0;row=0;pos=0;prop=100000;bestw=-1;besth=200;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_STCDoc;caption=wxStyledTextCtrl Documentation;state=6292988;dir=3;layer=0;row=0;pos=1;prop=100000;bestw=16;besth=16;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|dock_size(5,0,0)=198|dock_size(2,0,0)=443|dock_size(3,0,3)=120|dock_size(3,0,0)=180|",true);


    //m_mgr.LoadPerspective("layout2|name=m_scintilla1;caption=;state=444;dir=5;layer=0;row=0;pos=0;prop=100000;bestw=196;besth=79;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_propgrid;caption=;state=396;dir=2;layer=0;row=0;pos=0;prop=100000;bestw=400;besth=-1;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_browser;caption=;state=12584876;dir=3;layer=0;row=0;pos=0;prop=100000;bestw=-1;besth=200;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_STCDoc;caption=;state=14682108;dir=3;layer=0;row=0;pos=1;prop=100000;bestw=16;besth=16;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|dock_size(5,0,0)=196|dock_size(2,0,0)=450|dock_size(3,0,0)=180|",true);

    //m_mgr.LoadPerspective("layout2|name=m_scintilla1;caption=;state=444;dir=5;layer=0;row=0;pos=0;prop=100000;bestw=196;besth=79;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_propgrid;caption=;state=908;dir=2;layer=0;row=0;pos=0;prop=100000;bestw=400;besth=-1;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|name=m_browser;caption=;state=12584876;dir=3;layer=0;row=0;pos=0;prop=100000;bestw=-1;besth=200;minw=-1;minh=-1;maxw=-1;maxh=-1;floatx=-1;floaty=-1;floatw=-1;floath=-1|dock_size(5,0,0)=196|dock_size(2,0,0)=450|dock_size(3,0,0)=192|",true);
    //wxInitAllImageHandlers();

//    m_scintilla1->Connect(wxEVT_STC_CHANGE, wxStyledTextEventHandler( propgridtest03Frame::onSTCChange ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_AUTOCOMP_CANCELLED, wxStyledTextEventHandler( propgridtest03Frame::onSTCAutocCancelled ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_AUTOCOMP_CHAR_DELETED, wxStyledTextEventHandler( propgridtest03Frame::onSTCAutocCharDeleted ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_AUTOCOMP_SELECTION, wxStyledTextEventHandler( propgridtest03Frame::onSTCAutocSelection ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_CALLTIP_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCCallTipClick ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_CHARADDED, wxStyledTextEventHandler( propgridtest03Frame::onSTCCharAdded ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_DOUBLECLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCDoubleClick ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_DWELLEND, wxStyledTextEventHandler( propgridtest03Frame::onSTCDwellEnd ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_DWELLSTART, wxStyledTextEventHandler( propgridtest03Frame::onSTCDwellStart ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_HOTSPOT_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCHotspotClick ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_HOTSPOT_DCLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCHotspotDoubleClick ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_HOTSPOT_RELEASE_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCHotspotReleaseClick ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_INDICATOR_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCIndicatorClick ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_INDICATOR_RELEASE, wxStyledTextEventHandler( propgridtest03Frame::onSTCIndicatorRelease ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_KEY, wxStyledTextEventHandler( propgridtest03Frame::onSTCKey ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_MACRORECORD, wxStyledTextEventHandler( propgridtest03Frame::onSTCMacroRecord ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_MARGINCLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCMarginClick ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_MODIFIED, wxStyledTextEventHandler( propgridtest03Frame::onSTCModified ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_ROMODIFYATTEMPT, wxStyledTextEventHandler( propgridtest03Frame::onSTCModifyAttemptRO ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_NEEDSHOWN, wxStyledTextEventHandler( propgridtest03Frame::onSTCNeedShown ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_PAINTED, wxStyledTextEventHandler( propgridtest03Frame::onSTCPainted ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_SAVEPOINTLEFT, wxStyledTextEventHandler( propgridtest03Frame::onSTCSavepointLeft ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_SAVEPOINTREACHED, wxStyledTextEventHandler( propgridtest03Frame::onSTCSavePointReached ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_STYLENEEDED, wxStyledTextEventHandler( propgridtest03Frame::onSTCStyleNeeded ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_UPDATEUI, wxStyledTextEventHandler( propgridtest03Frame::onSTCUpdateUI ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_URIDROPPED, wxStyledTextEventHandler( propgridtest03Frame::onSTCURIDropped ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_USERLISTSELECTION, wxStyledTextEventHandler( propgridtest03Frame::onSTCUserListSelection ), NULL, this);
//    m_scintilla1->Connect(wxEVT_STC_ZOOM, wxStyledTextEventHandler( propgridtest03Frame::onSTCZoom ), NULL, this);


    //getter = wxColor(227,255,231);
//    getterParm = wxColor(230,255,233);
//    //setter = wxColor(245,245,255);
//    //setterParm = wxColor(235,235,255);
//    setter = wxColor(254,255,227);
//    setterParm = wxColor(254,255,207);
//    //doer = wxColor(240,240,240);
//    doer = wxColor(245,245,255);
//    doerParm = wxColor(235,235,255);
    notImplemented = wxColor(240,240,240);
    mainProp = wxColor(240,255,242);

    wxFileSystem::AddHandler(new wxMemoryFSHandler);

    wxMemoryFSHandler::AddFileWithMimeType("ScintillaDoc.html", ScintillaDoc_html, sizeof(ScintillaDoc_html), "text/html");
    wxMemoryFSHandler::AddFileWithMimeType("SciTEIco.png",SciTEIco_png,sizeof(SciTEIco_png),"image/png");
    wxMemoryFSHandler::AddFileWithMimeType("annotations.png",annotations_png,sizeof(annotations_png),"image/png");
    wxMemoryFSHandler::AddFileWithMimeType("styledmargin.png",styledmargin_png,sizeof(styledmargin_png),"image/png");

    wxMemoryFSHandler::AddFileWithMimeType("wxStyledTextCtrl.html", wxStyledTextCtrl_html, sizeof(wxStyledTextCtrl_html), "text/html");
    wxMemoryFSHandler::AddFileWithMimeType("doxygen.css", doxygen_css, sizeof(doxygen_css), "text/css");
    wxMemoryFSHandler::AddFileWithMimeType("extra_stylesheet.css", extra_stylesheet_css, sizeof(extra_stylesheet_css), "text/css");

    m_browser->LoadURL("memory:ScintillaDoc.html");
    m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html");


    m_propgrid->RegisterAdditionalEditors();

    m_pSampleMultiButtonEditor =
        wxPropertyGrid::DoRegisterEditorClass(new wxSampleMultiButtonEditor(this),"1");

    m_pSampleMultiButtonEditor2 =
        wxPropertyGrid::DoRegisterEditorClass(new wxSampleMultiButtonEditor2(this),"2");

    m_StyledTextEditor =
        wxPropertyGrid::DoRegisterEditorClass(new wxSampleStyledTextEditor(this),"3");

    stylingPosition=0;

    m_propgrid->Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler( propgridtest03Frame::OnPGChanged ) ,NULL,this);
    m_propgrid->Connect( wxEVT_PG_SELECTED, wxPropertyGridEventHandler( propgridtest03Frame::OnPGSelected ) ,NULL,this);

    //getLexerInfo();

    currentDocument=nullptr;
    //documentRefCnt.insert(std::pair<void*,int>(currentDocument,1));

    lexerInfo = new lexerDB();

    //in order to get the default values for some of the properties in the grid,
    //we need to use several stc getters.  But it seems to me that even calling getters
    //(and no setters) can change the state of the stc.  (for example getting some of
    //the style definition properties (I'm not sure which ones) turns the text white
    //so that typed text doesn't seem to be appearing)  Since I want the stc to be
    //completely unmodified at the start, I'm going to create a second one here and
    //use that to get all the defaults for the propgrid.  It's deleted at the end
    //of the constructor.
    wxStyledTextCtrl* stc_def = new wxStyledTextCtrl(this);


    addTextRetrievalAndModification(stc_def);
    addSearching();
    addOvertype(stc_def);
    addCutCopyAndPaste(stc_def);
    addErrorHandling(stc_def);
    addUndoAndRedo(stc_def);

    addSelectionAndInformation(stc_def);
    addMultipleSelectionAndVirtualSpace(stc_def);
    addScrollingAndAutomaticScrolling(stc_def);

    addWhiteSpace(stc_def);
    addCursor(stc_def);
    addMouseCapture(stc_def);

    addLineEndings(stc_def);
    addStyling(stc_def);
    addStyleDefinition(stc_def);

    addCaretSelectionAndHotspotStyles(stc_def);
    addMargins(stc_def);
    addAnnotations(stc_def);

    addOtherSettings(stc_def);
    addBraceHighlighting(stc_def);
    addTabsAndIndentationGuides(stc_def);

    addMarkers(stc_def);
    addIndicators(stc_def);
    addAutocompletion(stc_def);

    addUserLists(stc_def);
    addCallTips(stc_def);
    addKeyboardCommands(stc_def);

    addKeyBindings(stc_def);
    addPopupEditMenu(stc_def);
    addMacrrecording(stc_def);

    addPrinting(stc_def);
    addDirectAccess(stc_def);
    addMultipleViews(stc_def);

    addBackgroundLoadingAndSaving(stc_def);
    addFolding(stc_def);
    addLineWrapping(stc_def);

    addZooming(stc_def);
    addLongLines(stc_def);
    addLexer(stc_def);

    addLexerObjects(stc_def);
    addNotifications(stc_def);

    stc_def->Destroy();

//    addImages();
//
//    addGTK();
//    addDeprecatedMessages();
//    addEditMessagesNeverSupportedByScintilla();
//
//    addBuildingScintilla();

    for(int i=0;i<=wxSTC_MARKER_MAX;i++)
    {
        markerRGBAData[i]=nullptr;
    }
}

propgridtest03Frame::~propgridtest03Frame()
{

    delete lexerInfo;

    //clear the current document and reduce its ref count in our map
    if(currentDocument!=nullptr)
    {
        m_scintilla1->SetDocPointer(0);
        documentRefCnt[currentDocument]=documentRefCnt[currentDocument]-1;
    }

    //for each item in the map, release it one time for each time
    //create or AddRefDocument was called.
    int rc;
    for(std::map<void*,int>::iterator it= documentRefCnt.begin();it!=documentRefCnt.end();it++)
    {
        rc=it->second;

        while(rc>0)
        {
            m_scintilla1->ReleaseDocument(it->first);
            rc--;
        }

//        if(it->first!=currentDocument)
//        {
//            delete it->first;
//        }
    }
    documentRefCnt.clear();

    for(std::vector<keyBinding*>::iterator it=keyBindings.begin();it!=keyBindings.end();it++)
    {
        delete *it;
    }
    keyBindings.clear();


    //markers.clear();

    for(std::vector<marker*>::iterator it =markers.begin() ;it!=markers.end();it++)
    {
        delete *it;
    }
    markers.clear();

    for(int i=0;i<=wxSTC_MARKER_MAX;i++)
    {
        if(markerRGBAData[i]!=nullptr)
        {
            free(markerRGBAData[i]);
        }
    }

    registeredACImages.clear();

    for(std::map<int,unsigned char*>::iterator it = registeredACRGBAData.begin();it!=registeredACRGBAData.end();it++)
    {
        free(it->second);
    }
    registeredACRGBAData.clear();


//    statesVec1.clear();
//    statesVec2.clear();
//    statesVec3.clear();

}

void propgridtest03Frame::OnClose(wxCloseEvent &event)
{
    Destroy();
}

void propgridtest03Frame::OnQuit(wxCommandEvent &event)
{
    Destroy();
}

void propgridtest03Frame::OnAbout(wxCommandEvent &event)
{
    //wxString msg = wxbuildinfo(long_f);
    //wxMessageBox(msg, _("Welcome to..."));
}




void propgridtest03Frame::OnPGChanged(wxPropertyGridEvent& event)
{
    handle_property( event.GetProperty() );
}

void propgridtest03Frame::OnAuiPaneMaxemize( wxAuiManagerEvent& event )
{
//    //restoreString = m_mgr.SavePerspective ();
//    restoreString = m_mgr.SavePaneInfo( *event.GetPane() );

   //event.Skip();

   restoreString = m_mgr.SavePerspective ();
}

void propgridtest03Frame::OnAuiPaneRestore( wxAuiManagerEvent& event )
{
//    //m_mgr.LoadPerspective(restoreString);
//    m_mgr.LoadPaneInfo(restoreString, *event.GetPane());
//    m_mgr.Update();
    //event.Skip();

    m_mgr.LoadPerspective(restoreString);

}

void propgridtest03Frame::onAuiPaneClose( wxAuiManagerEvent& event )
{
    wxAuiPaneInfo* pi = event.GetPane();

    if( pi->name=="m_EventLog" )
    {
        m_menuItem33->Check(false);
        eventLogInfo = m_mgr.GetPane(m_EventLog);
        toBeDetached=m_EventLog;
    }
    else if( pi->name=="m_browser" )
    {
        m_menuItem34->Check(false);
        sciDocInfo = m_mgr.GetPane(m_browser);
        toBeDetached=m_browser;
    }
    else if( pi->name=="m_STCDoc" )
    {
        m_menuItem35->Check(false);
        stcDocInfo = m_mgr.GetPane(m_STCDoc);
        toBeDetached=m_STCDoc;
    }
    else if( pi->name=="m_CodeLog" )
    {
        m_menuItem36->Check(false);
        stcDocInfo = m_mgr.GetPane(m_CodeLog);
        toBeDetached=m_CodeLog;
    }


    this->Connect( wxEVT_IDLE, wxIdleEventHandler( propgridtest03Frame::onIdleDetach ) );

    //I'm not sure why, but skipping this will cause this event
    //handler to be called a second time and not skipping seems to be OK,
    //so I'm not going to skip this event.
    //event.Skip();
}

void propgridtest03Frame::onIdleDetach( wxIdleEvent& event )
{
    if(toBeDetached)
    {
        m_mgr.DetachPane(toBeDetached);
        toBeDetached=nullptr;
    }

    this->Disconnect( wxEVT_IDLE, wxIdleEventHandler( propgridtest03Frame::onIdleDetach ) );
}

void propgridtest03Frame::OnShowCode( wxCommandEvent& event )
{
    wxMenuItem* mi=m_menu1->FindItem( event.GetId() );

    if(mi->IsChecked())
    {
        m_CodeLog->Show(true);
        codeLogInfo.MaximizeButton(false);
        codeLogInfo.CloseButton(false);
        m_mgr.InsertPane(m_CodeLog, codeLogInfo);
    }
    else
    {
        codeLogInfo = m_mgr.GetPane(m_CodeLog);
        m_mgr.DetachPane(m_CodeLog);
        m_CodeLog->Show(false);
    }

    m_mgr.Update();



}

void propgridtest03Frame::onViewEventLog(wxCommandEvent& event)
{
    wxMenuItem* mi=m_menu1->FindItem( event.GetId() );

    if(mi->IsChecked())
    {
        eventLogInfo.MaximizeButton(false);
        eventLogInfo.CloseButton(false);
        m_mgr.InsertPane(m_EventLog, eventLogInfo);
    }
    else
    {
        eventLogInfo = m_mgr.GetPane(m_EventLog);
        m_mgr.DetachPane(m_EventLog);
        m_EventLog->Show(false);
    }

    m_mgr.Update();
}

void propgridtest03Frame::onViewSciDoc(wxCommandEvent& event)
{
    wxMenuItem* mi=m_menu1->FindItem( event.GetId() );

    if(mi->IsChecked())
    {
        sciDocInfo.MaximizeButton(false);
        sciDocInfo.CloseButton(false);
        m_mgr.InsertPane(m_browser, sciDocInfo);
    }
    else
    {
        sciDocInfo = m_mgr.GetPane(m_browser);
        m_mgr.DetachPane(m_browser);
        m_browser->Show(false);
    }

    m_mgr.Update();
}

void propgridtest03Frame::onViewStcDoc(wxCommandEvent& event)
{
    wxMenuItem* mi=m_menu1->FindItem( event.GetId() );

    if(mi->IsChecked())
    {
        stcDocInfo.MaximizeButton(false);
        stcDocInfo.CloseButton(false);
        m_mgr.InsertPane(m_STCDoc, stcDocInfo);
    }
    else
    {
        stcDocInfo = m_mgr.GetPane(m_STCDoc);
        m_mgr.DetachPane(m_STCDoc);
        m_STCDoc->Show(false);
    }

    m_mgr.Update();
}

void propgridtest03Frame::setColorString(wxPGProperty* property, const wxColor& c)
{
    //wxColour c = m_scintilla1->GetAdditionalCaretForeground ();
    wxString s = c.GetAsString();
    s.Replace("rgb","");

    property->SetValueFromString(s);

    wxBitmap test_bitmap(20,15);
    wxMemoryDC temp_dc;
    temp_dc.SelectObject(test_bitmap);

    temp_dc.SetPen(*wxBLACK_PEN);
    temp_dc.SetBrush( wxBrush(c) );
    temp_dc.DrawRectangle( 0,0,20,15);
    temp_dc.SelectObject(wxNullBitmap);

    property->SetValueImage(test_bitmap);
}




void propgridtest03Frame::On3rdColumnMenu( wxCommandEvent& event )
{
    if( event.IsChecked() )
    {
        m_propgrid->SetColumnCount(3);
        //m_propgrid->SetColumnTitle(0, "STC Method");
        //m_propgrid->SetColumnTitle(1, "");
        //m_propgrid->SetColumnTitle(2, "Scintilla Message");

        //m_propgrid->ShowHeader(false);


        m_propgrid->SetColumnProportion (0, 1);
        m_propgrid->SetColumnProportion (1, 1);
        m_propgrid->SetColumnProportion (2, 1);
        m_propgrid->ResetColumnSizes();
        //m_propgrid->ShowHeader(true);

        wxPropertyGridIterator it=m_propgrid->GetIterator (wxPG_ITERATE_ALL, wxTOP);
        wxString s;

        while(!it.AtEnd ())
        {
            s=it.GetProperty()->GetBaseName();
            if(s.Find("zzz")==wxNOT_FOUND)
            {
                m_propgrid->SetPropertyCell(it.GetProperty(),2, s);
            }


            it++;
        }





        //m_button1->SetLabel("Hide 3rd Column");
    }
    else
    {
        m_propgrid->SetColumnCount(2);
        //m_propgrid->ShowHeader(false);
        m_propgrid->SetColumnProportion (0, 1);
        m_propgrid->SetColumnProportion (1, 1);
        m_propgrid->ResetColumnSizes();

        //m_button1->SetLabel("Show 3rd Column");
    }
}

//void propgridtest03Frame::onSTCMarginClick(wxStyledTextEvent& event){logEvent("wxEVT_STC_MARGINCLICK");}

void propgridtest03Frame::onSTCLogMenu(wxCommandEvent& event)
{
    int i=event.GetId();

    if(i==MENU_STC_AUTOCOMP_CANCELLED)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_AUTOCOMP_CANCELLED, wxStyledTextEventHandler( propgridtest03Frame::onSTCAutocCancelled ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_AUTOCOMP_CANCELLED, wxStyledTextEventHandler( propgridtest03Frame::onSTCAutocCancelled ), NULL, this);
        }
    }
    else if(i==MENU_STC_AUTOCOMP_CHAR_DELETED)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_AUTOCOMP_CHAR_DELETED, wxStyledTextEventHandler( propgridtest03Frame::onSTCAutocCharDeleted ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_AUTOCOMP_CHAR_DELETED, wxStyledTextEventHandler( propgridtest03Frame::onSTCAutocCharDeleted ), NULL, this);
        }
    }
    else if(i==MENU_STC_AUTOCOMP_SELECTION)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_AUTOCOMP_SELECTION, wxStyledTextEventHandler( propgridtest03Frame::onSTCAutocSelection ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_AUTOCOMP_SELECTION, wxStyledTextEventHandler( propgridtest03Frame::onSTCAutocSelection ), NULL, this);
        }
    }
    else if(i==MENU_STC_CALLTIP_CLICK)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_CALLTIP_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCCallTipClick ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_CALLTIP_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCCallTipClick ), NULL, this);
        }
    }
    else if(i==MENU_STC_CHANGE)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_CHANGE, wxStyledTextEventHandler( propgridtest03Frame::onSTCChange ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_CHANGE, wxStyledTextEventHandler( propgridtest03Frame::onSTCChange ), NULL, this);
        }
    }
    else if(i==MENU_STC_CHARADDED)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_CHARADDED, wxStyledTextEventHandler( propgridtest03Frame::onSTCCharAdded ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_CHARADDED, wxStyledTextEventHandler( propgridtest03Frame::onSTCCharAdded ), NULL, this);
        }
    }
    else if(i==MENU_STC_DOUBLECLICK)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_DOUBLECLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCDoubleClick ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_DOUBLECLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCDoubleClick ), NULL, this);
        }
    }
    else if(i==MENU_STC_DWELLEND)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_DWELLEND, wxStyledTextEventHandler( propgridtest03Frame::onSTCDwellEnd ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_DWELLEND, wxStyledTextEventHandler( propgridtest03Frame::onSTCDwellEnd ), NULL, this);
        }
    }
    else if(i==MENU_STC_DWELLSTART)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_DWELLSTART, wxStyledTextEventHandler( propgridtest03Frame::onSTCDwellStart ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_DWELLSTART, wxStyledTextEventHandler( propgridtest03Frame::onSTCDwellStart ), NULL, this);
        }
    }
    else if(i==MENU_STC_HOTSPOT_CLICK)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_HOTSPOT_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCHotspotClick ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_HOTSPOT_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCHotspotClick ), NULL, this);
        }
    }
    else if(i==MENU_STC_HOTSPOT_DCLICK)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_HOTSPOT_DCLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCHotspotDoubleClick ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_HOTSPOT_DCLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCHotspotDoubleClick ), NULL, this);
        }
    }
    else if(i==MENU_STC_HOTSPOT_RELEASE_CLICK)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_HOTSPOT_RELEASE_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCHotspotReleaseClick ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_HOTSPOT_RELEASE_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCHotspotReleaseClick ), NULL, this);
        }
    }
    else if(i==MENU_STC_INDICATOR_CLICK)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_INDICATOR_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCIndicatorClick ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_INDICATOR_CLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCIndicatorClick ), NULL, this);
        }
    }
    else if(i==MENU_STC_INDICATOR_RELEASE)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_INDICATOR_RELEASE, wxStyledTextEventHandler( propgridtest03Frame::onSTCIndicatorRelease ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_INDICATOR_RELEASE, wxStyledTextEventHandler( propgridtest03Frame::onSTCIndicatorRelease ), NULL, this);
        }
    }
    else if(i==MENU_STC_KEY)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_KEY, wxStyledTextEventHandler( propgridtest03Frame::onSTCKey ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_KEY, wxStyledTextEventHandler( propgridtest03Frame::onSTCKey ), NULL, this);
        }
    }
    else if(i==MENU_STC_MACRORECORD)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_MACRORECORD, wxStyledTextEventHandler( propgridtest03Frame::onSTCMacroRecord ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_MACRORECORD, wxStyledTextEventHandler( propgridtest03Frame::onSTCMacroRecord ), NULL, this);
        }
    }
    else if(i==MENU_STC_MARGINCLICK)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_MARGINCLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCMarginClick ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_MARGINCLICK, wxStyledTextEventHandler( propgridtest03Frame::onSTCMarginClick ), NULL, this);
        }
    }
    else if(i==MENU_STC_MODIFIED)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_MODIFIED, wxStyledTextEventHandler( propgridtest03Frame::onSTCModified ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_MODIFIED, wxStyledTextEventHandler( propgridtest03Frame::onSTCModified ), NULL, this);
        }
    }


    else if(i==MENU_STC_NEEDSHOWN)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_NEEDSHOWN, wxStyledTextEventHandler( propgridtest03Frame::onSTCNeedShown ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_NEEDSHOWN, wxStyledTextEventHandler( propgridtest03Frame::onSTCNeedShown ), NULL, this);
        }
    }
    else if(i==MENU_STC_PAINTED)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_PAINTED, wxStyledTextEventHandler( propgridtest03Frame::onSTCPainted ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_PAINTED, wxStyledTextEventHandler( propgridtest03Frame::onSTCPainted ), NULL, this);
        }
    }
    else if(i==MENU_STC_ROMODIFYATTEMPT)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_ROMODIFYATTEMPT, wxStyledTextEventHandler( propgridtest03Frame::onSTCModifyAttemptRO ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_ROMODIFYATTEMPT, wxStyledTextEventHandler( propgridtest03Frame::onSTCModifyAttemptRO ), NULL, this);
        }
    }





    else if(i==MENU_STC_SAVEPOINTLEFT)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_SAVEPOINTLEFT, wxStyledTextEventHandler( propgridtest03Frame::onSTCSavepointLeft ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_SAVEPOINTLEFT, wxStyledTextEventHandler( propgridtest03Frame::onSTCSavepointLeft ), NULL, this);
        }
    }
    else if(i==MENU_STC_SAVEPOINTREACHED)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_SAVEPOINTREACHED, wxStyledTextEventHandler( propgridtest03Frame::onSTCSavePointReached ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_SAVEPOINTREACHED, wxStyledTextEventHandler( propgridtest03Frame::onSTCSavePointReached ), NULL, this);
        }
    }
    else if(i==MENU_STC_STYLENEEDED)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_STYLENEEDED, wxStyledTextEventHandler( propgridtest03Frame::onSTCStyleNeeded ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_STYLENEEDED, wxStyledTextEventHandler( propgridtest03Frame::onSTCStyleNeeded ), NULL, this);
        }
    }
    else if(i==MENU_STC_UPDATEUI)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_UPDATEUI, wxStyledTextEventHandler( propgridtest03Frame::onSTCUpdateUI ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_UPDATEUI, wxStyledTextEventHandler( propgridtest03Frame::onSTCUpdateUI ), NULL, this);
        }
    }
    else if(i==MENU_STC_URIDROPPED)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_URIDROPPED, wxStyledTextEventHandler( propgridtest03Frame::onSTCURIDropped ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_URIDROPPED, wxStyledTextEventHandler( propgridtest03Frame::onSTCURIDropped ), NULL, this);
        }
    }
    else if(i==MENU_STC_USERLISTSELECTION)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_USERLISTSELECTION, wxStyledTextEventHandler( propgridtest03Frame::onSTCUserListSelection ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_USERLISTSELECTION, wxStyledTextEventHandler( propgridtest03Frame::onSTCUserListSelection ), NULL, this);
        }
    }
    else if(i==MENU_STC_ZOOM)
    {
        if(event.IsChecked())
        {
            m_scintilla1->Connect(wxEVT_STC_ZOOM, wxStyledTextEventHandler( propgridtest03Frame::onSTCZoom ), NULL, this);
        }
        else
        {
            m_scintilla1->Disconnect(wxEVT_STC_ZOOM, wxStyledTextEventHandler( propgridtest03Frame::onSTCZoom ), NULL, this);
        }
    }



}


void propgridtest03Frame::onSTCChange(wxStyledTextEvent& event){logEvent("wxEVT_STC_CHANGE",event);}
void propgridtest03Frame::onSTCAutocCancelled(wxStyledTextEvent& event){logEvent("wxEVT_STC_AUTOCOMP_CANCELLED",event);}
void propgridtest03Frame::onSTCAutocCharDeleted(wxStyledTextEvent& event){logEvent("wxEVT_STC_AUTOCOMP_CHAR_DELETED",event);}
void propgridtest03Frame::onSTCAutocSelection(wxStyledTextEvent& event){logEvent("wxEVT_STC_AUTOCOMP_SELECTION",event);}
void propgridtest03Frame::onSTCCallTipClick(wxStyledTextEvent& event){logEvent("wxEVT_STC_CALLTIP_CLICK",event);}
void propgridtest03Frame::onSTCCharAdded(wxStyledTextEvent& event){logEvent("wxEVT_STC_CHARADDED",event);}
void propgridtest03Frame::onSTCDoubleClick(wxStyledTextEvent& event){logEvent("wxEVT_STC_DOUBLECLICK",event);}
void propgridtest03Frame::onSTCDwellEnd(wxStyledTextEvent& event){logEvent("wxEVT_STC_DWELLEND",event);}
void propgridtest03Frame::onSTCDwellStart(wxStyledTextEvent& event){logEvent("wxEVT_STC_DWELLSTART",event);}
void propgridtest03Frame::onSTCHotspotClick(wxStyledTextEvent& event){logEvent("wxEVT_STC_HOTSPOT_CLICK",event);}
void propgridtest03Frame::onSTCHotspotDoubleClick(wxStyledTextEvent& event){logEvent("wxEVT_STC_HOTSPOT_DCLICK",event);}
void propgridtest03Frame::onSTCHotspotReleaseClick(wxStyledTextEvent& event){logEvent("wxEVT_STC_HOTSPOT_RELEASE_CLICK",event);}
void propgridtest03Frame::onSTCIndicatorClick(wxStyledTextEvent& event){logEvent("wxEVT_STC_INDICATOR_CLICK",event);}
void propgridtest03Frame::onSTCIndicatorRelease(wxStyledTextEvent& event){logEvent("wxEVT_STC_INDICATOR_RELEASE",event);}
void propgridtest03Frame::onSTCKey(wxStyledTextEvent& event){logEvent("wxEVT_STC_KEY",event);}
void propgridtest03Frame::onSTCMacroRecord(wxStyledTextEvent& event){logEvent("wxEVT_STC_MACRORECORD",event);}
void propgridtest03Frame::onSTCMarginClick(wxStyledTextEvent& event){logEvent("wxEVT_STC_MARGINCLICK",event);}
void propgridtest03Frame::onSTCModified(wxStyledTextEvent& event){logEvent("wxEVT_STC_MODIFIED",event);}
void propgridtest03Frame::onSTCModifyAttemptRO(wxStyledTextEvent& event){logEvent("wxEVT_STC_ROMODIFYATTEMPT",event);}
void propgridtest03Frame::onSTCNeedShown(wxStyledTextEvent& event){logEvent("wxEVT_STC_NEEDSHOWN",event);}
void propgridtest03Frame::onSTCPainted(wxStyledTextEvent& event){logEvent("wxEVT_STC_PAINTED",event);}
void propgridtest03Frame::onSTCSavepointLeft(wxStyledTextEvent& event){logEvent("wxEVT_STC_SAVEPOINTLEFT",event);}
void propgridtest03Frame::onSTCSavePointReached(wxStyledTextEvent& event){logEvent("wxEVT_STC_SAVEPOINTREACHED",event);}
void propgridtest03Frame::onSTCStyleNeeded(wxStyledTextEvent& event){logEvent("wxEVT_STC_STYLENEEDED",event);}
void propgridtest03Frame::onSTCUpdateUI(wxStyledTextEvent& event){logEvent("wxEVT_STC_UPDATEUI",event);}
void propgridtest03Frame::onSTCURIDropped(wxStyledTextEvent& event){logEvent("wxEVT_STC_URIDROPPED",event);}
void propgridtest03Frame::onSTCUserListSelection(wxStyledTextEvent& event){logEvent("wxEVT_STC_USERLISTSELECTION",event);}
void propgridtest03Frame::onSTCZoom(wxStyledTextEvent& event){logEvent("wxEVT_STC_ZOOM",event);}





void propgridtest03Frame::logEvent(const wxString& s,wxStyledTextEvent& event)
{
    wxVector<wxVariant> data;

    data.push_back( wxDateTime::Now().Format("%X") );
    data.push_back(s);
    data.push_back(event.GetAnnotationsLinesAdded()?wxString::Format("%d",event.GetAnnotationsLinesAdded()):"");
    data.push_back(event.GetKey()?wxString::Format("%d",event.GetKey()):"");
    data.push_back(event.GetFoldLevelNow()?wxString::Format("%d",event.GetFoldLevelNow()):"");
    data.push_back(event.GetFoldLevelPrev()?wxString::Format("%d",event.GetFoldLevelPrev()):"");
    data.push_back(event.GetLength()?wxString::Format("%d",event.GetLength()):"");
    data.push_back(event.GetLine()?wxString::Format("%d",event.GetLine()):"");
    data.push_back(event.GetLinesAdded()?wxString::Format("%d",event.GetLinesAdded()):"");
    data.push_back(event.GetListType()?wxString::Format("%d",event.GetListType()):"");
    data.push_back(event.GetLParam()?wxString::Format("%d",event.GetLParam()):"");
    data.push_back(event.GetMargin()?wxString::Format("%d",event.GetMargin()):"");
    data.push_back(event.GetMessage()?wxString::Format("%d",event.GetMessage()):"");
    data.push_back(event.GetModificationType()?wxString::Format("%d",event.GetModificationType()):"");
    data.push_back(event.GetModifiers()?wxString::Format("%d",event.GetModifiers()):"");
    data.push_back(event.GetPosition()?wxString::Format("%d",event.GetPosition()):"");
    data.push_back(!event.GetText().IsEmpty()?event.GetText():"");
    data.push_back(event.GetToken()?wxString::Format("%d",event.GetToken()):"");
    data.push_back(event.GetUpdated()?wxString::Format("%d",event.GetUpdated()):"");
    data.push_back(event.GetWParam()?wxString::Format("%d",event.GetWParam()):"");
    data.push_back(event.GetX()?wxString::Format("%d",event.GetX()):"");
    data.push_back(event.GetY()?wxString::Format("%d",event.GetY()):"");
    m_EventLog->AppendItem(data);


    unsigned int i=m_EventLog->GetItemCount();

    wxDataViewItem dvi=m_EventLog->RowToItem(i-1);

    m_EventLog->EnsureVisible(dvi);
}
