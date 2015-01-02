/***************************************************************
 * Name:      propgridtest03Main.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2014-08-16
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef PROPGRIDTEST03MAIN_H
#define PROPGRIDTEST03MAIN_H

#include "Enums.h"
#include <vector>
#include <deque>
#include <map>

class lexerDB;

class marker
{
    public:
        marker(int h,int l,int m):markerNo(m),lineNo(l),handle(h){}
        int lineNo;
        int markerNo;
        int handle;
};

class keyBinding
{
    public:
        keyBinding(int kc,int m,int c,const wxString& b):keyCode(kc),modifiers(m),command(c),binding(b){}
        int getKeyCode(){return keyCode;}
        int getModifiers(){return modifiers;}
        int getCommand(){return command;}
        wxString getBinding(){return binding;}

    private:
        int keyCode;
        int modifiers;
        int command;
        wxString binding;
};

class myStyleData:public wxClientData
{
    public:
        myStyleData(int i){style=i;}
        int get_style(){return style;}

    private:
        int style;
};

class MyProjectMyDialog1 : public MyDialog1
{
	public:
		MyProjectMyDialog1( wxWindow* parent ):MyDialog1(parent){};
		void setbm(const wxBitmap& b){bm=b;}


    private:
        void OnPaint( wxPaintEvent& event );
        wxBitmap bm;
};




class propgridtest03Frame: public GUIFrameWEnum
{
    public:
        propgridtest03Frame(wxFrame *frame);
        ~propgridtest03Frame();

        bool handle_property(wxPGProperty*);
        //void setStyledText(const wxString& _styledText){styledText=_styledText;}
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);

		void OnAuiPaneMaxemize( wxAuiManagerEvent& event );
		void OnAuiPaneRestore( wxAuiManagerEvent& event );
		void onAuiPaneClose( wxAuiManagerEvent& event );
		void onIdleDetach( wxIdleEvent& event );

		void onViewEventLog(wxCommandEvent& event);
		void onViewSciDoc(wxCommandEvent& event);
		void onViewStcDoc(wxCommandEvent& event);

        wxString restoreString;
        wxWindow* toBeDetached;
        wxAuiPaneInfo codeLogInfo;
        wxAuiPaneInfo eventLogInfo;
		wxAuiPaneInfo sciDocInfo;
		wxAuiPaneInfo stcDocInfo;

		void onSTCLogMenu(wxCommandEvent& event);

		void On3rdColumnMenu( wxCommandEvent& event );
		void OnShowCode( wxCommandEvent& event );



        void OnPGSelected(wxPropertyGridEvent& event);
        void OnPGChanged(wxPropertyGridEvent& event);

        void addTextRetrievalAndModification(wxStyledTextCtrl* stc_def);
        void addSearching();
        void addOvertype(wxStyledTextCtrl* stc_def);

        void addCutCopyAndPaste(wxStyledTextCtrl* stc_def);
        void addErrorHandling(wxStyledTextCtrl* stc_def);
        void addUndoAndRedo(wxStyledTextCtrl* stc_def);

        void addSelectionAndInformation(wxStyledTextCtrl* stc_def);
        void addMultipleSelectionAndVirtualSpace(wxStyledTextCtrl* stc_def);
        void addScrollingAndAutomaticScrolling(wxStyledTextCtrl* stc_def);

        void addWhiteSpace(wxStyledTextCtrl* stc_def);
        void addCursor(wxStyledTextCtrl* stc_def);
        void addMouseCapture(wxStyledTextCtrl* stc_def);

        void addLineEndings(wxStyledTextCtrl* stc_def);
        void addStyling(wxStyledTextCtrl* stc_def);
        void addStyleDefinition(wxStyledTextCtrl* stc_def);
        void addStyle(wxPGProperty*,int,const wxString&,wxStyledTextCtrl* stc_def);

        void addCaretSelectionAndHotspotStyles(wxStyledTextCtrl* stc_def);
        void addMargins(wxStyledTextCtrl* stc_def);
        void addMargin(wxPGProperty*,int,const wxString&,wxStyledTextCtrl* stc_def);
        void addAnnotations(wxStyledTextCtrl* stc_def);

        void addOtherSettings(wxStyledTextCtrl* stc_def);
        void addBraceHighlighting(wxStyledTextCtrl* stc_def);
        void addTabsAndIndentationGuides(wxStyledTextCtrl* stc_def);

        void addMarkers(wxStyledTextCtrl* stc_def);
        void addMarker(wxPGProperty*,int,const wxString&,wxStyledTextCtrl* stc_def);
        void addIndicators(wxStyledTextCtrl* stc_def);
        void addIndicator(wxPGProperty*,int,const wxString&,wxStyledTextCtrl* stc_def);

        void addAutocompletion(wxStyledTextCtrl* stc_def);

        void addUserLists(wxStyledTextCtrl* stc_def);
        void addCallTips(wxStyledTextCtrl* stc_def);
        void addKeyboardCommands(wxStyledTextCtrl* stc_def);

        void addKeyBindings(wxStyledTextCtrl* stc_def);
        void addPopupEditMenu(wxStyledTextCtrl* stc_def);
        void addMacrrecording(wxStyledTextCtrl* stc_def);

        void addPrinting(wxStyledTextCtrl* stc_def);
        void addDirectAccess(wxStyledTextCtrl* stc_def);
        void addMultipleViews(wxStyledTextCtrl* stc_def);

        void addBackgroundLoadingAndSaving(wxStyledTextCtrl* stc_def);
        void addFolding(wxStyledTextCtrl* stc_def);
        void addLineWrapping(wxStyledTextCtrl* stc_def);

        void addZooming(wxStyledTextCtrl* stc_def);
        void addLongLines(wxStyledTextCtrl* stc_def);
        void addLexer(wxStyledTextCtrl* stc_def);

        void addLexerObjects(wxStyledTextCtrl* stc_def);
        void addNotifications(wxStyledTextCtrl* stc_def);

//        void getLexerInfo();
//        void addImages();
//
//        void addGTK();
//        void addDeprecatedMessages();
//        void addEditMessagesNeverSupportedByScintilla();
//
//        void addBuildingScintilla();

        void onSTCChange(wxStyledTextEvent& event);
        void onSTCAutocCancelled(wxStyledTextEvent& event);
        void onSTCAutocCharDeleted(wxStyledTextEvent& event);
        void onSTCAutocSelection(wxStyledTextEvent& event);
        void onSTCCallTipClick(wxStyledTextEvent& event);
        void onSTCCharAdded(wxStyledTextEvent& event);
        void onSTCDoubleClick(wxStyledTextEvent& event);
        void onSTCDwellEnd(wxStyledTextEvent& event);
        void onSTCDwellStart(wxStyledTextEvent& event);
        void onSTCHotspotClick(wxStyledTextEvent& event);
        void onSTCHotspotDoubleClick(wxStyledTextEvent& event);
        void onSTCHotspotReleaseClick(wxStyledTextEvent& event);
        void onSTCIndicatorClick(wxStyledTextEvent& event);
        void onSTCIndicatorRelease(wxStyledTextEvent& event);
        void onSTCKey(wxStyledTextEvent& event);
        void onSTCMacroRecord(wxStyledTextEvent& event);
        void onSTCMarginClick(wxStyledTextEvent& event);
        void onSTCModified(wxStyledTextEvent& event);
        void onSTCModifyAttemptRO(wxStyledTextEvent& event);
        void onSTCNeedShown(wxStyledTextEvent& event);
        void onSTCPainted(wxStyledTextEvent& event);
        void onSTCSavepointLeft(wxStyledTextEvent& event);
        void onSTCSavePointReached(wxStyledTextEvent& event);
        void onSTCStyleNeeded(wxStyledTextEvent& event);
        void onSTCUpdateUI(wxStyledTextEvent& event);
        void onSTCURIDropped(wxStyledTextEvent& event);
        void onSTCUserListSelection(wxStyledTextEvent& event);
        void onSTCZoom(wxStyledTextEvent& event);

        void logEvent(const wxString&,wxStyledTextEvent& event);


        std::vector<wxPGProperty*> clearables;
        std::deque<wxPGProperty*> lexerProps;


        //wxString styledText;
        wxPGEditor*     m_pSampleMultiButtonEditor;
        wxPGEditor*     m_pSampleMultiButtonEditor2;
        wxPGEditor*     m_StyledTextEditor;

        int stylingPosition;

        void* currentDocument;
        std::map<void*,int> documentRefCnt;
        wxPGProperty* SCI_SETDOCPOINTERENUM;
        wxPGProperty* SCI_ADDREFDOCUMENTENUM;
        wxPGProperty* SCI_RELEASEDOCUMENTENUM;

        wxPGProperty* LexerProp;
        void lexerSetHelper(int);

        void buildMultipleViewsEnums();

        std::vector<keyBinding*> keyBindings;
        wxPGProperty* SCI_CLEARCMDKEYENUM;
        void buildCmdKeyClearEnum();

        std::vector<marker*> markers;
        wxPGProperty* SCI_MARKERLINEFROMHANDLEENUM;
        wxPGProperty* SCI_MARKERDELETEHANDLEENUM;
        void buildMarkerEnums();
        wxPGProperty* markerDefinitions[wxSTC_MARKER_MAX+1];
        wxPGProperty* markerDefinePixmap[wxSTC_MARKER_MAX+1];
        wxPGProperty* markerRGBAWidth[wxSTC_MARKER_MAX+1];
        wxPGProperty* markerRGBAHeight[wxSTC_MARKER_MAX+1];
        wxPGProperty* markerDefineRGBAImage[wxSTC_MARKER_MAX+1];
        wxPGProperty* markerEnableHighlight[wxSTC_MARKER_MAX+1];
        wxPGProperty* markerDefinePixmap2[wxSTC_MARKER_MAX+1];
        //int           markerPrevDef[wxSTC_MARKER_MAX+1];
        wxPGProperty* markerDefineCharacter[wxSTC_MARKER_MAX+1];
        unsigned char* markerRGBAData[wxSTC_MARKER_MAX+1];

        std::map<int,wxPGProperty*> registeredACImages;
        std::map<int,unsigned char*> registeredACRGBAData;
        wxPGProperty* registerdACImageHeader;
        void addRegisteredImage(int,const wxString&);
        void clearRegisteredImages();

        lexerDB* lexerInfo;

        wxColor mainProp;
        wxColor notImplemented;



        wxPGProperty* addLongStringProp(wxPGProperty* st,const wxString& label,const wxString& name, int cd,bool clearable,bool readonly);
        wxPGProperty* addStringProp(wxPGProperty* st,const wxString& label,const wxString& name, int cd,bool clearable,bool readonly);
        void          addStringParam(wxPGProperty* np,const wxString& label,bool longstring);
        wxPGProperty* addStringHeader(wxPGProperty* np,const wxString& label);
        wxPGProperty* addDotDotDotStringProp(wxPGProperty* st,const wxString& label,const wxString& name, int cd);

        wxPGProperty* addIntProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd,int dv,int min,int max);
        void          addIntParam(wxPGProperty* np,const wxString& label,int dv,int min,int max);

        wxPGProperty* addBoolProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd,bool dv);
        void          addBoolParam(wxPGProperty* np,const wxString& label,bool dv);

        wxPGProperty* addFlagsProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd,long dv,wxArrayString& cases,wxArrayInt& cases_values);
        void          addFlagsParam(wxPGProperty* np,const wxString& label,long dv,wxArrayString& cases,wxArrayInt& cases_values);

        wxPGProperty* addEnumProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd,long dv,wxArrayString& cases,wxArrayInt& cases_values);
        void          addEnumParam(wxPGProperty* np,const wxString& label,long dv,wxArrayString& cases,wxArrayInt& cases_values);

        wxPGProperty* addColorProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd, const wxColor& dv);
        void          addColorParam(wxPGProperty* np,const wxString& label,const wxColor& dv);
        void          addColorStringProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd);

        void setColorString(wxPGProperty*, const wxColor&);


};

#endif // PROPGRIDTEST03MAIN_H
