
#include "stcMain.h"
#include <wx/propgrid/advprops.h>
#include <wx/fontenum.h>
#include "lexers.h"

#include "scintilla/16x16/arrow_1_disable.xpm"
#include "scintilla/16x16/arrow_1_green.xpm"
#include "scintilla/16x16/arrow_1_yellow.xpm"
#include "scintilla/16x16/arrow_2_blue.xpm"
#include "scintilla/16x16/arrow_2_blue__disable.xpm"
#include "scintilla/16x16/arrow_2_green-disable.xpm"
#include "scintilla/16x16/arrow_2_green.xpm"
#include "scintilla/16x16/arrow_2_yellow.xpm"
#include "scintilla/16x16/arrow_2_yellow_disable.xpm"
#include "scintilla/16x16/arrow_golden.xpm"
#include "scintilla/16x16/breakpoint-disabled.xpm"
#include "scintilla/16x16/breakpoint.xpm"
#include "scintilla/16x16/breakpoint_octogon-disable.xpm"
#include "scintilla/16x16/breakpoint_octogon.xpm"
#include "scintilla/16x16/breakpoint_octogon_grayed.xpm"
#include "scintilla/16x16/breakpoint_rounded_blue.xpm"
#include "scintilla/16x16/breakpoint_rounded_blue_disable.xpm"
#include "scintilla/16x16/breakpoint_rounded_blue_inverted.xpm"
#include "scintilla/16x16/breakpoint_rounded_gray.xpm"
#include "scintilla/16x16/breakpoint_rounded_gray_disable.xpm"
#include "scintilla/16x16/gem_blue.xpm"
#include "scintilla/16x16/gem_red.xpm"
#include "scintilla/16x16/marker_red_round-disabled.xpm"
#include "scintilla/16x16/marker_red_round.xpm"

#include "scintilla/12x12/arrow.h"
#include "scintilla/12x12/arrow2.h"
#include "scintilla/12x12/arrow2-blue.h"
#include "scintilla/12x12/arrow2-red.h"
#include "scintilla/12x12/arrow-blue.h"
#include "scintilla/12x12/arrow-red.h"
#include "scintilla/12x12/box.h"
#include "scintilla/12x12/box-blue.h"
#include "scintilla/12x12/box-red.h"
#include "scintilla/12x12/child.h"
#include "scintilla/12x12/cross.h"
#include "scintilla/12x12/cross2.h"
#include "scintilla/12x12/dot-black.h"
#include "scintilla/12x12/dot-black-locked.h"
#include "scintilla/12x12/dot-blue.h"
#include "scintilla/12x12/dotl-blue-locked.h"
#include "scintilla/12x12/dot-orange.h"
#include "scintilla/12x12/dot-orange-crossed.h"
#include "scintilla/12x12/dot-orange-wlock.h"
#include "scintilla/12x12/dot-orange-wolock.h"
#include "scintilla/12x12/dot-orange-wolock2.h"
#include "scintilla/12x12/dot-red.h"
#include "scintilla/12x12/dot-red-locked.h"
#include "scintilla/12x12/F-unction.h"
#include "scintilla/12x12/F-unction-blue.h"
#include "scintilla/12x12/inherit.h"
#include "scintilla/12x12/inherit2.h"
#include "scintilla/12x12/inherit2-blue.h"
#include "scintilla/12x12/inner-square.h"
#include "scintilla/12x12/inner-square-black.h"
#include "scintilla/12x12/inner-square-blue.h"
#include "scintilla/12x12/key.h"
#include "scintilla/12x12/key-blue.h"
#include "scintilla/12x12/key-red.h"
#include "scintilla/12x12/lock-closed.h"
#include "scintilla/12x12/lock-closed-blue.h"
#include "scintilla/12x12/lock-opened.h"
#include "scintilla/12x12/lock-opened-blue.h"
#include "scintilla/12x12/member.h"
#include "scintilla/12x12/member-blue.h"
#include "scintilla/12x12/noidea.h"
#include "scintilla/12x12/question.h"
#include "scintilla/12x12/recurse-blue.h"
#include "scintilla/12x12/round.h"
#include "scintilla/12x12/round-blue.h"
#include "scintilla/12x12/round-red.h"
#include "scintilla/12x12/semaphore.h"
#include "scintilla/12x12/shuttle.h"
#include "scintilla/12x12/square-blue.h"
#include "scintilla/12x12/square-red.h"
#include "scintilla/12x12/warn.h"
#include "scintilla/12x12/whirl.h"
#include "scintilla/12x12/whirl-blue.h"



void propgridtest03Frame::addTextRetrievalAndModification(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Text retrieval and modification"));
    st->SetClientData(reinterpret_cast<void *>(SCI_TEXTRETRIEVALANDMODIFICATION));

    wxPGProperty* np;

    //SCI_GETTEXT(int length, char *text)
        addLongStringProp(st,"GetText","SCI_GETTEXT", SCI_GETTEXT,true,true);

    //SCI_SETTEXT(<unused>, const char *text)
        np = addStringProp(st,"SetText","SCI_SETTEXT",SCI_SETTEXT ,false,true);
        addStringParam(np,"text",true);
        m_propgrid->Collapse(np);

    //SCI_SETSAVEPOINT
        addStringProp(st,"SetSavePoint","SCI_SETSAVEPOINT",SCI_SETSAVEPOINT ,false,true);

    //SCI_GETLINE(int line, char *text)
        np=addLongStringProp(st,"GetLine","SCI_GETLINE", SCI_GETLINE,true,true);
        addIntParam(np, "line", 0, 0, INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_REPLACESEL(<unused>, const char *text)
        np = addStringProp(st,"ReplaceSelection","SCI_REPLACESEL",SCI_REPLACESEL ,false,true);
        addStringParam(np,"text",true);
        m_propgrid->Collapse(np);

    //SCI_SETREADONLY(bool readOnly)
        addBoolProp(st,"SetReadOnly","SCI_SETREADONLY",SCI_SETREADONLY,stc_def->GetReadOnly());

    //SCI_GETREADONLY
        addStringProp(st,"GetReadOnly","SCI_GETREADONLY",SCI_GETREADONLY ,true,true);

    //SCI_GETTEXTRANGE(<unused>, Sci_TextRange *tr)
        np=addLongStringProp(st,"GetTextRange","SCI_GETTEXTRANGE",SCI_GETTEXTRANGE ,true,true);
        addIntParam(np,"startPos", 0, 0, INT_MAX);
        addIntParam(np,"endPos",-1, -1, INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_ALLOCATE(int bytes, <unused>)
        np=addStringProp(st,"Allocate","SCI_ALLOCATE",SCI_ALLOCATE ,false,true);
        addIntParam(np,"bytes",1024, 0, INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_ADDTEXT(int length, const char *s)
        np=addStringProp(st,"AddText","SCI_ADDTEXT",SCI_ADDTEXT ,false,true);
        addStringParam(np,"text",true);
        m_propgrid->Collapse(np);

    //SCI_ADDSTYLEDTEXT(int length, cell *s)
        np = m_propgrid->Append(new wxStringProperty("AddStyledText","SCI_ADDSTYLEDTEXT"));
        np->SetClientData(reinterpret_cast<void *>(SCI_ADDSTYLEDTEXT));
        m_propgrid->SetPropertyEditor(np, m_StyledTextEditor );
        m_propgrid->SetPropertyReadOnly(np);

    //SCI_APPENDTEXT(int length, const char *s)
        np=addStringProp(st,"AppendText","SCI_APPENDTEXT",SCI_APPENDTEXT ,false,true);
        addStringParam(np, "text",true);
        m_propgrid->Collapse(np);

    //SCI_INSERTTEXT(int pos, const char *text)
        np = addStringProp(st, "InsertText", "SCI_INSERTTEXT", SCI_INSERTTEXT,false,true);
        addIntParam(np,"pos",-1,-1, INT_MAX);
        addStringParam(np, "text",true);
        m_propgrid->Collapse(np);

    //SCI_CLEARALL
        addStringProp(st, "ClearAll", "SCI_CLEARALL", SCI_CLEARALL,false,false);

    //SCI_DELETERANGE(int pos, int deleteLength)
        np=addStringProp(st, "DeleteRange", "SCI_DELETERANGE", SCI_DELETERANGE,false,false);
        addIntParam(np,"pos",0,0, INT_MAX);
        addIntParam(np,"deleteLength", 0, 0, INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_CLEARDOCUMENTSTYLE
        addStringProp(st, "ClearDocumentStyle", "SCI_CLEARDOCUMENTSTYLE", SCI_CLEARDOCUMENTSTYLE,false,false);

    //SCI_GETCHARAT(int position)
        np=addStringProp(st, "GetCharAt", "SCI_GETCHARAT", SCI_GETCHARAT,true,false);
        addIntParam(np,"pos",0,-1, INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETSTYLEAT(int position
        np=addStringProp(st, "GetStyleAt", "SCI_GETSTYLEAT", SCI_GETSTYLEAT,true,false);
        addIntParam(np,"pos",0,-1, INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETSTYLEDTEXT(<unused>, Sci_TextRange *tr)
        np=addStringProp(st,"GetStyledText","SCI_GETSTYLEDTEXT",SCI_GETSTYLEDTEXT ,false,true);
        addIntParam(np,"startPos",0,0,INT_MAX);
        addIntParam(np,"endPos",0,-1, INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETSTYLEBITS(int bits)
        addIntProp(st,"SetStyleBits","SCI_SETSTYLEBITS",SCI_SETSTYLEBITS,stc_def->GetStyleBits(),0,8);

    //SCI_GETSTYLEBITS
        addStringProp(st, "GetStyleBits", "SCI_GETSTYLEBITS", SCI_GETSTYLEBITS,true,true);

    wxPGProperty* st2 = m_propgrid->AppendIn(st,new wxPropertyCategory("GTK+-specific: Access to encoded text"));
    st2->SetClientData(reinterpret_cast<void *>(SCI_ACCESSTOENCODEDTEXT));

    //SCI_TARGETASUTF8(<unused>, char *s)
        addStringProp(st2,"SCI_TARGETASUTF8","SCI_TARGETASUTF8",SCI_TARGETASUTF8 ,true,true);

    //SCI_ENCODEDFROMUTF8(const char *utf8, char *encoded)
        np = addStringProp(st2,"SCI_ENCODEDFROMUTF8","SCI_ENCODEDFROMUTF8",SCI_ENCODEDFROMUTF8 ,true,true);
        addStringParam(np,"utf8",true);
        m_propgrid->Collapse(np);

    //SCI_SETLENGTHFORENCODE(int bytes)
        addIntProp(st2,"SCI_SETLENGTHFORENCODE","SCI_SETLENGTHFORENCODE",SCI_SETLENGTHFORENCODE,-1,-1, INT_MAX);

    st2 = m_propgrid->AppendIn(st,new wxPropertyCategory("Alternative implementations"));
    st2->SetClientData(reinterpret_cast<void *>(SCI_TEXTRETRIEVALANDMODIFICATION));

        np=addLongStringProp(st2,"SCI_GETTEXTRANGE","SCI_GETTEXTRANGE",SCI_GETTEXTRANGEALT ,true,true);
        addIntParam(np,"cpMin", 0, 0, INT_MAX);
        addIntParam(np,"cpMax",-1,-1, INT_MAX);
        m_propgrid->Collapse(np);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addSearching()
{
    wxArrayString cases;
    wxArrayInt cases_values;

    cases.Add("SCFIND_MATCHCASE");
    cases.Add("SCFIND_WHOLEWORD");
    cases.Add("SCFIND_WORDSTART");
    cases.Add("SCFIND_REGEXP");
    cases.Add("SCFIND_POSIX");

    cases_values.Add(wxSTC_FIND_MATCHCASE);
    cases_values.Add(wxSTC_FIND_WHOLEWORD);
    cases_values.Add(wxSTC_FIND_WORDSTART);
    cases_values.Add(wxSTC_FIND_REGEXP);
    cases_values.Add(wxSTC_FIND_POSIX);

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Searching"));
    st->SetClientData(reinterpret_cast<void *>(SCI_SEARCHING));

    //SCI_FINDTEXT(int flags, Sci_TextToFind *ttf)
        wxPGProperty* np = addStringProp(st, "FindText", "SCI_FINDTEXT", SCI_FINDTEXT,true,true);
        addIntParam(np,"minPos",0,0, INT_MAX);
        addIntParam(np,"maxPos,",0,-1, INT_MAX);
        addStringParam(np, "text",true);
        addFlagsParam(np,"searchFlags",0,cases,cases_values);
        m_propgrid->Collapse(np);

    //SCI_SEARCHANCHOR
        addStringProp(st, "SearchAnchor", "SCI_SEARCHANCHOR", SCI_SEARCHANCHOR,false,true);

    //SCI_SEARCHNEXT(int searchFlags, const char *text)
        np=addStringProp(st, "SearchNext", "SCI_SEARCHNEXT", SCI_SEARCHNEXT,true,true);
        addFlagsParam(np,"searchFlags",0,cases,cases_values);
        addStringParam(np, "text",true);
        m_propgrid->Collapse(np);

    //SCI_SEARCHPREV(int searchFlags, const char *text)
        np=addStringProp(st, "SearchPrev", "SCI_SEARCHPREV", SCI_SEARCHPREV,true,true);
        addFlagsParam(np,"searchFlags",0,cases,cases_values);
        addStringParam(np, "text",true);
        m_propgrid->Collapse(np);

    //Search and replace using the target
    wxPGProperty* st2 = m_propgrid->AppendIn(st,new wxPropertyCategory("Search and replace using the target"));

    //SCI_SETTARGETSTART(int pos)
        addIntProp(st2,"SetTargetStart","SCI_SETTARGETSTART",SCI_SETTARGETSTART,0,0, INT_MAX);

    //SCI_GETTARGETSTART
        addStringProp(st2, "GetTargetStart", "SCI_GETTARGETSTART", SCI_GETTARGETSTART,true,true);

    //SCI_SETTARGETEND(int pos)
        addIntProp(st2,"SetTargetEnd","SCI_SETTARGETEND",SCI_SETTARGETEND,0,0, INT_MAX);

    //SCI_GETTARGETEND
        addStringProp(st2, "GetTargetEnd", "SCI_GETTARGETEND", SCI_GETTARGETEND,true,true);

    //SCI_TARGETFROMSELECTION
        addStringProp(st2, "TargetFromSelection", "SCI_TARGETFROMSELECTION", SCI_TARGETFROMSELECTION,true,true);

    //SCI_SETSEARCHFLAGS(int searchFlags)
        addFlagsProp(st2,"SetSearchFlags","SCI_SETSEARCHFLAGS",SCI_SETSEARCHFLAGS,0,cases,cases_values);

    //SCI_GETSEARCHFLAGS
        addStringProp(st2, "GetSearchFlags", "SCI_GETSEARCHFLAGS", SCI_GETSEARCHFLAGS,true,true);

    //SCI_SEARCHINTARGET(int length, const char *text)
        np = addStringProp(st2, "SearchInTarget", "SCI_SEARCHINTARGET", SCI_SEARCHINTARGET,true,true);
        addStringParam(np, "text",true);
        m_propgrid->Collapse(np);

    //SCI_REPLACETARGET(int length, const char *text)
        np = addStringProp(st2, "ReplaceTarget", "SCI_REPLACETARGET", SCI_REPLACETARGET,true,true);
        addStringParam(np, "text",true);
        m_propgrid->Collapse(np);

    //SCI_REPLACETARGETRE(int length, const char *text)
        np = addStringProp(st2, "ReplaceTargetRE", "SCI_REPLACETARGETRE", SCI_REPLACETARGETRE,true,true);
        addStringParam(np, "text",true);
        m_propgrid->Collapse(np);

    //SCI_GETTAG(int tagNumber, char *tagValue)
        np = addStringProp(st2, "GetTag", "SCI_GETTAG", SCI_GETTAG,true,true);
        addIntParam(np,"tagNumber",0,0,9);
        m_propgrid->Collapse(np);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addOvertype(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Overtype"));
    st->SetClientData(reinterpret_cast<void *>(SCI_OVERTYPE));

    //SCI_SETOVERTYPE(bool overType)
        addBoolProp( st, "SetOvertype", "SCI_SETOVERTYPE", SCI_SETOVERTYPE, stc_def->GetOvertype() );

    //SCI_GETOVERTYPE
        addStringProp(st, "GetOvertype", "SCI_GETOVERTYPE", SCI_GETOVERTYPE,true,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addCutCopyAndPaste(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Cut, copy and paste"));
    st->SetClientData(reinterpret_cast<void *>(SCI_CUTCOPYANDPASTE));

    //SCI_CUT
        addStringProp(st, "Cut", "SCI_CUT", SCI_CUT,false,true);

    //SCI_COPY
        addStringProp(st, "Copy", "SCI_COPY", SCI_COPY,false,true);

    //SCI_PASTE
        addStringProp(st, "Paste", "SCI_PASTE", SCI_PASTE,false,true);

    //SCI_CLEAR
        addStringProp(st, "Clear", "SCI_CLEAR", SCI_CLEAR,false,true);

    //SCI_CANPASTE
        addStringProp(st, "CanPaste", "SCI_CANPASTE", SCI_CANPASTE,true,true);

    //SCI_COPYRANGE(int start, int end)
        wxPGProperty* np = addStringProp(st, "CopyRange", "SCI_COPYRANGE", SCI_COPYRANGE,false,true);
        addIntParam(np,"start",0,0, INT_MAX);
        addIntParam(np,"end",0,0, INT_MAX);
        m_propgrid->Collapse (np);

    //SCI_COPYTEXT(int length, const char *text)
        np = addStringProp(st, "CopyText", "SCI_COPYTEXT", SCI_COPYTEXT,false,true);
        addIntParam(np,"length",0,0, INT_MAX);
        addStringParam(np, "text",true);
        m_propgrid->Collapse (np);

    //SCI_COPYALLOWLINE
        addStringProp(st, "CopyAllowLine", "SCI_COPYALLOWLINE", SCI_COPYALLOWLINE,false,true);

    //SCI_SETPASTECONVERTENDINGS(bool convert)
        addBoolProp( st, "SetPasteConvertEndings", "SCI_SETPASTECONVERTENDINGS", SCI_SETPASTECONVERTENDINGS, stc_def->GetPasteConvertEndings() );

    //SCI_GETPASTECONVERTENDINGS
        addStringProp(st, "GetPasteConvertEndings", "SCI_GETPASTECONVERTENDINGS", SCI_GETPASTECONVERTENDINGS,true,true);

    m_propgrid->Collapse (st);
}

void propgridtest03Frame::addErrorHandling(wxStyledTextCtrl* stc_def)
{
    wxArrayString cases;
    wxArrayInt cases_values;

    cases.Add("wxSTC_STATUS_OK");
    cases.Add("wxSTC_STATUS_FAILURE");
    cases.Add("wxSTC_STATUS_BADALLOC");

    cases_values.Add(wxSTC_STATUS_OK);
    cases_values.Add(wxSTC_STATUS_FAILURE);
    cases_values.Add(wxSTC_STATUS_BADALLOC);

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Error handling"));
    st->SetClientData(reinterpret_cast<void *>(SCI_ERRORHANDLING));

    //SCI_SETSTATUS(int status)
        addEnumProp(st,"SetStatus","SCI_SETSTATUS",SCI_SETSTATUS,stc_def->GetStatus(),cases,cases_values);

    //SCI_GETSTATUS
        addStringProp(st, "GetStatus", "SCI_GETSTATUS", SCI_GETSTATUS,true,true);

    m_propgrid->Collapse (st);
}

void propgridtest03Frame::addUndoAndRedo(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Undo and Redo"));
    st->SetClientData(reinterpret_cast<void *>(SCI_UNDOANDREDO));

    //SCI_UNDO
        addStringProp(st, "Undo", "SCI_UNDO", SCI_UNDO,false,true);

    //SCI_CANUNDO
        addStringProp(st, "CanUndo", "SCI_CANUNDO", SCI_CANUNDO,true,true);

    //SCI_EMPTYUNDOBUFFER
        addStringProp(st, "EmptyUndoBuffer", "SCI_EMPTYUNDOBUFFER", SCI_EMPTYUNDOBUFFER,false,true);

    //SCI_REDO
        addStringProp(st, "Redo", "SCI_REDO", SCI_REDO,false,true);

    //SCI_CANREDO
        addStringProp(st, "CanRedo", "SCI_CANREDO", SCI_CANREDO,true,true);

    //SCI_SETUNDOCOLLECTION(bool collectUndo)
        addBoolProp(st,"SetUndoCollection","SCI_SETUNDOCOLLECTION",SCI_SETUNDOCOLLECTION,stc_def->GetUndoCollection());

    //SCI_GETUNDOCOLLECTION
        addStringProp(st, "GetUndoCollection", "SCI_GETUNDOCOLLECTION", SCI_GETUNDOCOLLECTION,true,true);

    //SCI_BEGINUNDOACTION
        addStringProp(st, "BeginUndoAction", "SCI_BEGINUNDOACTION", SCI_BEGINUNDOACTION,false,true);

    //SCI_ENDUNDOACTION
        addStringProp(st, "EndUndoAction", "SCI_ENDUNDOACTION", SCI_ENDUNDOACTION,false,true);

    //SCI_ADDUNDOACTION(int token, int flags)
        wxPGProperty* np = addStringProp(st, "AddUndoAction", "SCI_ADDUNDOACTION", SCI_ADDUNDOACTION,false,true);
        addIntParam( np, "token", 0, INT_MIN, INT_MAX );

        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_UNDO_MAY_COALESCE");
        cases_values.Add(wxSTC_UNDO_MAY_COALESCE);

        addFlagsParam(np,"flags", 0,cases,cases_values);
        m_propgrid->Collapse(np);

    m_propgrid->Collapse (st);
}

void propgridtest03Frame::addSelectionAndInformation(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_SEL_STREAM");
        cases.Add("wxSTC_SEL_RECTANGLE");
        cases.Add("wxSTC_SEL_LINES");
        cases.Add("wxSTC_SEL_THIN");

        cases_values.Add(wxSTC_SEL_STREAM);
        cases_values.Add(wxSTC_SEL_RECTANGLE);
        cases_values.Add(wxSTC_SEL_LINES);
        cases_values.Add(wxSTC_SEL_THIN);


    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Selection and information"));
    st->SetClientData( reinterpret_cast<void*>(SCI_SELECTIONANDINFORMATION) );

    //SCI_GETTEXTLENGTH
        addStringProp(st, "GetTextLength", "SCI_GETTEXTLENGTH", SCI_GETTEXTLENGTH,true,true);

    //SCI_GETLENGTH
        addStringProp(st, "GetLength", "SCI_GETLENGTH", SCI_GETLENGTH,true,true);

    //SCI_GETLINECOUNT
        addStringProp(st, "GetLineCount", "SCI_GETLINECOUNT", SCI_GETLINECOUNT,true,true);

    //SCI_SETFIRSTVISIBLELINE(int lineDisplay)
        addIntProp(st,"SetFirstVisibleLine","SCI_SETFIRSTVISIBLELINE",SCI_SETFIRSTVISIBLELINE,stc_def->GetFirstVisibleLine(),0,INT_MAX);

    //SCI_GETFIRSTVISIBLELINE
        addStringProp(st, "GetFirstVisibleLine", "SCI_GETFIRSTVISIBLELINE", SCI_GETFIRSTVISIBLELINE,true,true);

    //SCI_LINESONSCREEN
        addStringProp(st, "LinesOnScreen", "SCI_LINESONSCREEN", SCI_LINESONSCREEN,true,true);

    //SCI_GETMODIFY
        addStringProp(st, "GetModify", "SCI_GETMODIFY", SCI_GETMODIFY,true,true);

    //SCI_SETSEL(int anchorPos, int currentPos)
        wxPGProperty* np=addStringProp(st, "SCI_SETSEL", "SCI_SETSEL", SCI_SETSEL,false,true);
        addIntParam(np,"anchorPos",0,-1,INT_MAX);
        addIntParam(np,"currentPos",0,-1,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GOTOPOS(int position)
        addIntProp(st,"GotoPos","SCI_GOTOPOS",SCI_GOTOPOS,0,0,INT_MAX);

    //SCI_GOTOLINE(int line)
        addIntProp(st,"GotoLine","SCI_GOTOLINE",SCI_GOTOLINE,0,0,INT_MAX);

    //SCI_SETCURRENTPOS(int position)
        addIntProp(st,"SetCurrentPos","SCI_SETCURRENTPOS",SCI_SETCURRENTPOS,stc_def->GetCurrentPos(),0,INT_MAX);

    //SCI_GETCURRENTPOS
        addStringProp(st, "GetCurrentPos", "SCI_GETCURRENTPOS", SCI_GETCURRENTPOS,true,true);

    //SCI_SETANCHOR(int position)
        addIntProp(st,"SetAnchor","SCI_SETANCHOR",SCI_SETANCHOR,stc_def->GetAnchor(),0,INT_MAX);

    //SCI_GETANCHOR
        addStringProp(st, "GetAnchor", "SCI_GETANCHOR", SCI_GETANCHOR,true,true);

    //SCI_SETSELECTIONSTART(int position)
        addIntProp(st,"SetSelectionStart","SCI_SETSELECTIONSTART",SCI_SETSELECTIONSTART,stc_def->GetSelectionStart(),0,INT_MAX);

    //SCI_GETSELECTIONSTART
        addStringProp(st, "GetSelectionStart", "SCI_GETSELECTIONSTART", SCI_GETSELECTIONSTART,true,true);

    //SCI_SETSELECTIONEND(int position)
        addIntProp(st,"SetSelectionEnd","SCI_SETSELECTIONEND",SCI_SETSELECTIONEND,stc_def->GetSelectionEnd(),0,INT_MAX);

    //SCI_GETSELECTIONEND
        addStringProp(st, "GetSelectionEnd", "SCI_GETSELECTIONEND", SCI_GETSELECTIONEND,true,true);

    //SCI_SETEMPTYSELECTION(int pos)
        np=addStringProp(st, "SetEmptySelection", "SCI_SETEMPTYSELECTION", SCI_SETEMPTYSELECTION,false,true);
        addIntParam(np,"pos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SELECTALL
        addStringProp(st, "SelectAll", "SCI_SELECTALL", SCI_SELECTALL,false,true);

    //SCI_LINEFROMPOSITION(int position)
        np=addStringProp(st, "LineFromPosition", "SCI_LINEFROMPOSITION", SCI_LINEFROMPOSITION,true,true);
        addIntParam(np,"pos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_POSITIONFROMLINE(int line)
        np=addStringProp(st, "PositionFromLine", "SCI_POSITIONFROMLINE", SCI_POSITIONFROMLINE,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETLINEENDPOSITION(int line)
        np=addStringProp(st, "GetLineEndPosition", "SCI_GETLINEENDPOSITION", SCI_GETLINEENDPOSITION,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_LINELENGTH(int line)
        np=addStringProp(st, "LineLength", "SCI_LINELENGTH", SCI_LINELENGTH,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETCOLUMN(int position)
        np=addStringProp(st, "GetColumn", "SCI_GETCOLUMN", SCI_GETCOLUMN,true,true);
        addIntParam(np,"pos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_FINDCOLUMN(int line, int column)
        np=addStringProp(st, "FindColumn", "SCI_FINDCOLUMN", SCI_FINDCOLUMN,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addIntParam(np,"column",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_POSITIONFROMPOINT(int x, int y)
        np=addStringProp(st, "PositionFromPoint", "SCI_POSITIONFROMPOINT", SCI_POSITIONFROMPOINT,true,true);
        addIntParam(np,"x",0,0,INT_MAX);
        addIntParam(np,"y",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_POSITIONFROMPOINTCLOSE(int x, int y)
        np=addStringProp(st, "PositionFromPointClose", "SCI_POSITIONFROMPOINTCLOSE",SCI_POSITIONFROMPOINTCLOSE ,true,true);
        addIntParam(np,"x",0,0,INT_MAX);
        addIntParam(np,"y",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_CHARPOSITIONFROMPOINT(int x, int y)
        np=addStringProp(st, "CharPositionFromPoint", "SCI_CHARPOSITIONFROMPOINT", SCI_CHARPOSITIONFROMPOINT,true,true);
        addIntParam(np,"x",0,0,INT_MAX);
        addIntParam(np,"y",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_CHARPOSITIONFROMPOINTCLOSE(int x, int y)
        np=addStringProp(st, "CharPositionFromPointClose", "SCI_CHARPOSITIONFROMPOINTCLOSE", SCI_CHARPOSITIONFROMPOINTCLOSE,true,true);
        addIntParam(np,"x",0,0,INT_MAX);
        addIntParam(np,"y",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_POINTXFROMPOSITION(<unused>, int position)
        np=addStringProp(st, "SCI_POINTXFROMPOSITION", "SCI_POINTXFROMPOSITION", SCI_POINTXFROMPOSITION,true,true);
        addIntParam(np,"position",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_POINTYFROMPOSITION(<unused>, int position)
        np=addStringProp(st, "SCI_POINTYFROMPOSITION", "SCI_POINTYFROMPOSITION", SCI_POINTYFROMPOSITION,true,true);
        addIntParam(np,"position",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_HIDESELECTION(bool hide)
        addBoolProp(st,"HideSelection","SCI_HIDESELECTION",SCI_HIDESELECTION,false);

    //SCI_GETSELTEXT(<unused>, char *text
        addStringProp(st, "GetSelectedText", "SCI_GETSELTEXT", SCI_GETSELTEXT,true,true);

    //SCI_GETCURLINE(int textLen, char *text)
        addLongStringProp(st, "GetCurLine", "SCI_GETCURLINE", SCI_GETCURLINE,true,true);

    //SCI_SELECTIONISRECTANGLE
        addStringProp(st, "SelectionIsRectangle", "SCI_SELECTIONISRECTANGLE", SCI_SELECTIONISRECTANGLE,true,true);

    //SCI_SETSELECTIONMODE(int mode)
        addEnumProp(st,"SetSelectionMode","SCI_SETSELECTIONMODE",SCI_SETSELECTIONMODE, stc_def->GetSelectionMode(), cases,cases_values);

    //SCI_GETSELECTIONMODE
        addStringProp(st, "GetSelectionMode", "SCI_GETSELECTIONMODE", SCI_GETSELECTIONMODE,true,true);

    //SCI_GETLINESELSTARTPOSITION(int line)
        np=addStringProp(st, "GetLineSelStartPosition", "SCI_GETLINESELSTARTPOSITION", SCI_GETLINESELSTARTPOSITION,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETLINESELENDPOSITION(int line)
        np=addStringProp(st, "GetLineSelEndPosition", "SCI_GETLINESELENDPOSITION", SCI_GETLINESELENDPOSITION,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_MOVECARETINSIDEVIEW
        addStringProp(st, "MoveCaretInsideView", "SCI_MOVECARETINSIDEVIEW", SCI_MOVECARETINSIDEVIEW,false,true);

    //SCI_WORDENDPOSITION(int position, bool onlyWordCharacters)
        np=addStringProp(st, "WordEndPosition", "SCI_WORDENDPOSITION", SCI_WORDENDPOSITION,true,true);
        addIntParam(np,"pos",0,0,INT_MAX);
        addBoolParam(np,"onlyWordCharacters",false);
        m_propgrid->Collapse(np);

    //SCI_WORDSTARTPOSITION(int position, bool onlyWordCharacters)
        np=addStringProp(st, "WordStartPosition", "SCI_WORDSTARTPOSITION", SCI_WORDSTARTPOSITION,true,true);
        addIntParam(np,"pos",0,0,INT_MAX);
        addBoolParam(np,"onlyWordCharacters",false);
        m_propgrid->Collapse(np);

    //SCI_POSITIONBEFORE(int position)
        np=addStringProp(st, "PositionBefore", "SCI_POSITIONBEFORE", SCI_POSITIONBEFORE,true,true);
        addIntParam(np,"pos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_POSITIONAFTER(int position)
        np=addStringProp(st, "PositionAfter", "SCI_POSITIONAFTER", SCI_POSITIONAFTER,true,true);
        addIntParam(np,"pos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_COUNTCHARACTERS(int startPos, int endPos)
        np=addStringProp(st, "CountCharacters", "SCI_COUNTCHARACTERS", SCI_COUNTCHARACTERS,true,true);
        addIntParam(np,"startPos",0,0,INT_MAX);
        addIntParam(np,"endPos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_TEXTWIDTH(int styleNumber, const char *text)
        np=addStringProp(st, "TextWidth", "SCI_TEXTWIDTH", SCI_TEXTWIDTH,true,true);
        addIntParam(np,"style",0,0,wxSTC_STYLE_MAX);
        addStringParam(np, "text",true);
        m_propgrid->Collapse(np);

    //SCI_TEXTHEIGHT(int line)
        np=addStringProp(st, "TextHeight", "SCI_TEXTHEIGHT", SCI_TEXTHEIGHT,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_CHOOSECARETX
        addStringProp(st, "ChooseCaretX", "SCI_CHOOSECARETX", SCI_CHOOSECARETX,false,true);

    //SCI_MOVESELECTEDLINESUP
        addStringProp(st, "MoveSelectedLinesUp", "SCI_MOVESELECTEDLINESUP", SCI_MOVESELECTEDLINESUP,false,true);

    //SCI_MOVESELECTEDLINESDOWN
        addStringProp(st, "MoveSelectedLinesDown", "SCI_MOVESELECTEDLINESDOWN", SCI_MOVESELECTEDLINESDOWN,false,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addMultipleSelectionAndVirtualSpace(wxStyledTextCtrl* stc_def)
{

        wxArrayString cases;
        wxArrayInt cases_values;
        cases.Add("wxSTC_MULTIPASTE_ONCE");
        cases.Add("wxSTC_MULTIPASTE_EACH");
        cases_values.Add(wxSTC_MULTIPASTE_ONCE);
        cases_values.Add(wxSTC_MULTIPASTE_EACH);

        wxArrayString cases2;
        wxArrayInt cases2_values;
        cases2.Add("wxSTC_SCVS_RECTANGULARSELECTION");
        cases2.Add("wxSTC_SCVS_USERACCESSIBLE");
        cases2_values.Add(wxSTC_SCVS_RECTANGULARSELECTION);
        cases2_values.Add(wxSTC_SCVS_USERACCESSIBLE);

        wxArrayString cases3;
        wxArrayInt cases3_values;
        cases3.Add("wxSTC_SCMOD_SHIFT");
        cases3.Add("wxSTC_SCMOD_CTRL");
        cases3.Add("wxSTC_SCMOD_ALT");
        cases3.Add("wxSTC_SCMOD_SUPER");
        cases3.Add("wxSTC_SCMOD_META");
        cases3_values.Add(wxSTC_SCMOD_SHIFT);
        cases3_values.Add(wxSTC_SCMOD_CTRL);
        cases3_values.Add(wxSTC_SCMOD_ALT);
        cases3_values.Add(wxSTC_SCMOD_SUPER);
        cases3_values.Add(wxSTC_SCMOD_META);


    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Multiple Selection and Virtual Space"));
    st->SetClientData( reinterpret_cast<void *>(SCI_MULTIPLESELECTIONANDVIRTUALSPACE) );

    //SCI_SETMULTIPLESELECTION(bool multipleSelection)
        addBoolProp(st,"SetMultipleSelection","SCI_SETMULTIPLESELECTION",SCI_SETMULTIPLESELECTION,stc_def->GetMultipleSelection());

    //SCI_GETMULTIPLESELECTION
        addStringProp(st, "GetMultipleSelection", "SCI_GETMULTIPLESELECTION", SCI_GETMULTIPLESELECTION,true,true);

    //SCI_SETADDITIONALSELECTIONTYPING(bool additionalSelectionTyping)
        addBoolProp(st,"SetAdditionalSelectionTyping","SCI_SETADDITIONALSELECTIONTYPING",SCI_SETADDITIONALSELECTIONTYPING,stc_def->GetAdditionalSelectionTyping());

    //SCI_GETADDITIONALSELECTIONTYPING
        addStringProp(st, "GetAdditionalSelectionTyping", "SCI_GETADDITIONALSELECTIONTYPING", SCI_GETADDITIONALSELECTIONTYPING,true,true);

    //SCI_SETMULTIPASTE(int multiPaste)
        addEnumProp(st,"SetMultiPaste","SCI_SETMULTIPASTE",SCI_SETMULTIPASTE,stc_def->GetMultiPaste(),cases,cases_values);

    //SCI_GETMULTIPASTE
        addStringProp(st, "GetMultiPaste", "SCI_GETMULTIPASTE", SCI_GETMULTIPASTE,true,true);

    //SCI_SETVIRTUALSPACEOPTIONS(int virtualSpaceOptions)
        addFlagsProp(st,"SetVirtualSpaceOptions","SCI_SETVIRTUALSPACEOPTIONS",SCI_SETVIRTUALSPACEOPTIONS,stc_def->GetVirtualSpaceOptions(),cases2,cases2_values);

    //SCI_GETVIRTUALSPACEOPTIONS
        addLongStringProp(st, "GetVirtualSpaceOptions", "SCI_GETVIRTUALSPACEOPTIONS", SCI_GETVIRTUALSPACEOPTIONS,true,true);

    //SCI_SETRECTANGULARSELECTIONMODIFIER(int modifier)
        addFlagsProp(st,"SetRectangularSelectionModifier","SCI_SETRECTANGULARSELECTIONMODIFIER",SCI_SETRECTANGULARSELECTIONMODIFIER,stc_def->GetRectangularSelectionModifier(),cases3,cases3_values);

    //SCI_GETRECTANGULARSELECTIONMODIFIER
        addLongStringProp(st, "GetRectangularSelectionModifier", "SCI_GETRECTANGULARSELECTIONMODIFIER", SCI_GETRECTANGULARSELECTIONMODIFIER,true,true);

    //SCI_GETSELECTIONS
        addStringProp(st, "GetSelections", "SCI_GETSELECTIONS", SCI_GETSELECTIONS,true,true);

    //SCI_CLEARSELECTIONS
        addStringProp(st, "ClearSelections", "SCI_CLEARSELECTIONS", SCI_CLEARSELECTIONS,false,true);

    //SCI_SETSELECTION(int caret, int anchor)
        wxPGProperty* np= addStringProp(st, "SCI_SETSELECTION", "SCI_SETSELECTION", SCI_SETSELECTION,false,true);
        addIntParam(np,"caret",0,0,INT_MAX);
        addIntParam(np,"anchor",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_ADDSELECTION(int caret, int anchor)
        np= addStringProp(st, "AddSelection", "SCI_ADDSELECTION", SCI_ADDSELECTION,false,true);
        addIntParam(np,"caret",0,0,INT_MAX);
        addIntParam(np,"anchor",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETMAINSELECTION(int selection)
        addIntProp(st,"SetMainSelection","SCI_SETMAINSELECTION",SCI_SETMAINSELECTION,0,0,INT_MAX);

    //SCI_GETMAINSELECTION
        addStringProp(st, "GetMainSelection", "SCI_GETMAINSELECTION", SCI_GETMAINSELECTION,true,true);


    //SCI_SETSELECTIONNCARET(int selection, int pos)
        np= addStringProp(st, "SetSelectionNCaret", "SCI_SETSELECTIONNCARET", SCI_SETSELECTIONNCARET,false,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        addIntParam(np,"pos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETSELECTIONNCARET(int selection)
        np= addStringProp(st, "GetSelectionNCaret", "SCI_GETSELECTIONNCARET", SCI_GETSELECTIONNCARET,true,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETSELECTIONNCARETVIRTUALSPACE(int selection, int space)
        np= addStringProp(st, "SetSelectionNCaretVirtualSpace", "SCI_SETSELECTIONNCARETVIRTUALSPACE", SCI_SETSELECTIONNCARETVIRTUALSPACE,false,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        addIntParam(np,"space",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETSELECTIONNCARETVIRTUALSPACE(int selection)
        np= addStringProp(st, "GetSelectionNCaretVirtualSpace", "SCI_GETSELECTIONNCARETVIRTUALSPACE", SCI_GETSELECTIONNCARETVIRTUALSPACE,true,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETSELECTIONNANCHOR(int selection, int posAnchor)
        np= addStringProp(st, "SetSelectionNAnchor", "SCI_SETSELECTIONNANCHOR", SCI_SETSELECTIONNANCHOR,false,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        addIntParam(np,"posAnchor",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETSELECTIONNANCHOR(int selection)
        np= addStringProp(st, "GetSelectionNAnchor", "SCI_GETSELECTIONNANCHOR", SCI_GETSELECTIONNANCHOR,true,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETSELECTIONNANCHORVIRTUALSPACE(int selection, int space)
        np= addStringProp(st, "SetSelectionNAnchorVirtualSpace", "SCI_SETSELECTIONNANCHORVIRTUALSPACE", SCI_SETSELECTIONNANCHORVIRTUALSPACE,false,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        addIntParam(np,"space",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETSELECTIONNANCHORVIRTUALSPACE(int selection)
        np= addStringProp(st, "GetSelectionNAnchorVirtualSpace", "SCI_GETSELECTIONNANCHORVIRTUALSPACE", SCI_GETSELECTIONNANCHORVIRTUALSPACE,true,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETSELECTIONNSTART(int selection, int pos)
        np= addStringProp(st, "SetSelectionNStart", "SCI_SETSELECTIONNSTART", SCI_SETSELECTIONNSTART,false,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        addIntParam(np,"pos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETSELECTIONNSTART(int selection)
        np= addStringProp(st, "GetSelectionNStart", "SCI_GETSELECTIONNSTART", SCI_GETSELECTIONNSTART,true,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETSELECTIONNEND(int selection, int pos)
        np= addStringProp(st, "SetSelectionNEnd", "SCI_SETSELECTIONNEND", SCI_SETSELECTIONNEND,false,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        addIntParam(np,"pos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETSELECTIONNEND(int selection)
        np= addStringProp(st, "GetSelectionNEnd", "SCI_GETSELECTIONNEND", SCI_GETSELECTIONNEND,true,true);
        addIntParam(np,"selection",0,0,INT_MAX);
        m_propgrid->Collapse(np);


    //SCI_SETRECTANGULARSELECTIONCARET(int pos)
        np= addStringProp(st, "SetRectangularSelectionCaret", "SCI_SETRECTANGULARSELECTIONCARET", SCI_SETRECTANGULARSELECTIONCARET,false,true);
        addIntParam(np,"pos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETRECTANGULARSELECTIONCARET
        addStringProp(st, "GetRectangularSelectionCaret", "SCI_GETRECTANGULARSELECTIONCARET", SCI_GETRECTANGULARSELECTIONCARET,true,true);

    //SCI_SETRECTANGULARSELECTIONCARETVIRTUALSPACE(int space)
        np= addStringProp(st, "SetRectangularSelectionCaretVirtualSpace", "SCI_SETRECTANGULARSELECTIONCARETVIRTUALSPACE", SCI_SETRECTANGULARSELECTIONCARETVIRTUALSPACE,false,true);
        addIntParam(np,"space",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETRECTANGULARSELECTIONCARETVIRTUALSPACE
        addStringProp(st, "GetRectangularSelectionCaretVirtualSpace", "SCI_GETRECTANGULARSELECTIONCARETVIRTUALSPACE", SCI_GETRECTANGULARSELECTIONCARETVIRTUALSPACE,true,true);

    //SCI_SETRECTANGULARSELECTIONANCHOR(int posAnchor)
        np= addStringProp(st, "SetRectangularSelectionAnchor", "SCI_SETRECTANGULARSELECTIONANCHOR", SCI_SETRECTANGULARSELECTIONANCHOR,false,true);
        addIntParam(np,"posAnchor",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETRECTANGULARSELECTIONANCHOR
        addStringProp(st, "GetRectangularSelectionAnchor", "SCI_GETRECTANGULARSELECTIONANCHOR", SCI_GETRECTANGULARSELECTIONANCHOR,true,true);

    //SCI_SETRECTANGULARSELECTIONANCHORVIRTUALSPACE(int space)
        np= addStringProp(st, "SetRectangularSelectionAnchorVirtualSpace", "SCI_SETRECTANGULARSELECTIONANCHORVIRTUALSPACE", SCI_SETRECTANGULARSELECTIONANCHORVIRTUALSPACE,false,true);
        addIntParam(np,"space",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETRECTANGULARSELECTIONANCHORVIRTUALSPACE
        addStringProp(st, "GetRectangularSelectionAnchorVirtualSpace", "SCI_GETRECTANGULARSELECTIONANCHORVIRTUALSPACE", SCI_GETRECTANGULARSELECTIONANCHORVIRTUALSPACE,true,true);


    //SCI_SETADDITIONALSELALPHA(int alpha)
        addIntProp(st,"SetAdditionalSelAlpha","SCI_SETADDITIONALSELALPHA",SCI_SETADDITIONALSELALPHA,stc_def->GetAdditionalSelAlpha(),0,256);

    //SCI_GETADDITIONALSELALPHA
        addStringProp(st, "GetAdditionalSelAlpha", "SCI_GETADDITIONALSELALPHA", SCI_GETADDITIONALSELALPHA,true,true);

    //SCI_SETADDITIONALSELFORE(int colour)
        addColorProp(st, "SetAdditionalSelForeground", "SCI_SETADDITIONALSELFORE", SCI_SETADDITIONALSELFORE, wxColour(0,0,0) );

    //SCI_SETADDITIONALSELBACK(int colour)
        addColorProp(st, "SetAdditionalSelBackground", "SCI_SETADDITIONALSELBACK", SCI_SETADDITIONALSELBACK, wxColour(215,215,215) );

    //SCI_SETADDITIONALCARETFORE(int colour)
        addColorProp(st, "SetAdditionalCaretForeground", "SCI_SETADDITIONALCARETFORE", SCI_SETADDITIONALCARETFORE, stc_def->GetAdditionalCaretForeground() );

    //SCI_GETADDITIONALCARETFORE
        addColorStringProp(st,"GetAdditionalCaretForeground","SCI_GETADDITIONALCARETFORE",SCI_GETADDITIONALCARETFORE);

    //SCI_SETADDITIONALCARETSBLINK(bool additionalCaretsBlink)
        addBoolProp(st,"SetAdditionalCaretsBlink","SCI_SETADDITIONALCARETSBLINK",SCI_SETADDITIONALCARETSBLINK,stc_def->GetAdditionalCaretsBlink());

    //SCI_GETADDITIONALCARETSBLINK
        addStringProp(st, "GetAdditionalCaretsBlink", "SCI_GETADDITIONALCARETSBLINK", SCI_GETADDITIONALCARETSBLINK,true,true);

    //SCI_SETADDITIONALCARETSVISIBLE(bool additionalCaretsVisible)
        addBoolProp(st,"SetAdditionalCaretsVisible","SCI_SETADDITIONALCARETSVISIBLE",SCI_SETADDITIONALCARETSVISIBLE,stc_def->GetAdditionalCaretsVisible());

    //SCI_GETADDITIONALCARETSVISIBLE
        addStringProp(st, "GetAdditionalCaretsVisible", "SCI_GETADDITIONALCARETSVISIBLE", SCI_GETADDITIONALCARETSVISIBLE,true,true);


    //SCI_SWAPMAINANCHORCARET
        addStringProp(st, "SwapMainAnchorCaret", "SCI_SWAPMAINANCHORCARET", SCI_SWAPMAINANCHORCARET,false,true);

    //SCI_ROTATESELECTION
        addStringProp(st, "RotateSelection", "SCI_ROTATESELECTION", SCI_ROTATESELECTION,false,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addScrollingAndAutomaticScrolling(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_CARET_SLOP");
        cases.Add("wxSTC_CARET_STRICT");
        cases.Add("wxSTC_CARET_JUMPS");
        cases.Add("wxSTC_CARET_EVEN");

        cases_values.Add(wxSTC_CARET_SLOP);
        cases_values.Add(wxSTC_CARET_STRICT);
        cases_values.Add(wxSTC_CARET_JUMPS);
        cases_values.Add(wxSTC_CARET_EVEN);


    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Scrolling and automatic scrolling"));
    st->SetClientData(reinterpret_cast<void *>(SCI_SCROLLINGANDAUTOMATICSCROLLING));

    //SCI_LINESCROLL(int column, int line)
        wxPGProperty* np=addStringProp(st, "LineScroll", "SCI_LINESCROLL", SCI_LINESCROLL,false,true);
        addIntParam(np,"columns",0,INT_MIN,INT_MAX);
        addIntParam(np,"lines",0,INT_MIN,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SCROLLCARET
        addStringProp(st, "EnsureCaretVisible", "SCI_SCROLLCARET", SCI_SCROLLCARET,false,true);

    //SCI_SETXCARETPOLICY(int caretPolicy, int caretSlop)
        np=addStringProp(st, "SetXCaretPolicy", "SCI_SETXCARETPOLICY", SCI_SETXCARETPOLICY,false,true);
        addFlagsParam(np,"caretPolicy", wxSTC_CARET_SLOP|wxSTC_CARET_JUMPS|wxSTC_CARET_EVEN,cases,cases_values);
        addIntParam(np,"caretSlop",17,0,INT_MAX);
        m_propgrid->Collapse(np);

        //There doesn't seem to be anyway to get the default values, but
        //after some experiments I'm pretty sure
        //the default carrot policy is wxSTC_CARET_SLOP|wxSTC_CARET_JUMPS|wxSTC_CARET_EVEN
        //and the default slop is somewhere between 16 and 17 (it moves 50 pixels, so since
        //the jump is supposed to be 3*UZ, the UZ should be 50/3=16.66666).  But I
        //don't see how to set that since we're restricted to intger values.

    //SCI_SETYCARETPOLICY(int caretPolicy, int caretSlop)
        np=addStringProp(st, "SetYCaretPolicy", "SCI_SETYCARETPOLICY", SCI_SETYCARETPOLICY,false,true);
        addFlagsParam(np,"caretPolicy", wxSTC_CARET_EVEN,cases,cases_values);
        addIntParam(np,"caretSlop",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETVISIBLEPOLICY(int caretPolicy, int caretSlop)
        cases.Clear();
        cases_values.Clear();
        cases.Add("wxSTC_VISIBLE_SLOP");
        cases.Add("wxSTC_VISIBLE_STRICT");
        cases_values.Add(wxSTC_VISIBLE_SLOP);
        cases_values.Add(wxSTC_VISIBLE_STRICT);

        np=addStringProp(st, "SetVisiblePolicy", "SCI_SETVISIBLEPOLICY", SCI_SETVISIBLEPOLICY,false,true);
        addFlagsParam(np,"visiblePolicy", 0, cases,cases_values);
        addIntParam(np,"visibleSlop",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETHSCROLLBAR(bool visible)
        addBoolProp(st,"SetUseHorizontalScrollBar","SCI_SETHSCROLLBAR",SCI_SETHSCROLLBAR, stc_def->GetUseHorizontalScrollBar() );

    //SCI_GETHSCROLLBAR
        addStringProp(st, "GetUseHorizontalScrollBar", "SCI_GETHSCROLLBAR", SCI_GETHSCROLLBAR,true,true);

    //SCI_SETVSCROLLBAR(bool visible)
        addBoolProp(st,"SetUseVerticalScrollBar","SCI_SETVSCROLLBAR",SCI_SETVSCROLLBAR, stc_def->GetUseVerticalScrollBar() );

    //SCI_GETVSCROLLBAR
        addStringProp(st, "GetUseVerticalScrollBar", "SCI_GETVSCROLLBAR", SCI_GETVSCROLLBAR,true,true);

    //SCI_GETXOFFSET
        addStringProp(st, "GetXOffset", "SCI_GETXOFFSET", SCI_GETXOFFSET,true,true);

    //SCI_SETXOFFSET(int xOffset)
        addIntProp(st,"SetXOffset","SCI_SETXOFFSET",SCI_SETXOFFSET,stc_def->GetXOffset(),0,INT_MAX);

    //SCI_SETSCROLLWIDTH(int pixelWidth)
        addIntProp(st,"SetScrollWidth","SCI_SETSCROLLWIDTH",SCI_SETSCROLLWIDTH,stc_def->GetScrollWidth(),0,INT_MAX);

    //SCI_GETSCROLLWIDTH
        addStringProp(st, "GetScrollWidth", "SCI_GETSCROLLWIDTH", SCI_GETSCROLLWIDTH,true,true);

    //SCI_SETSCROLLWIDTHTRACKING(bool tracking)
        addBoolProp(st,"SetScrollWidthTracking","SCI_SETSCROLLWIDTHTRACKING",SCI_SETSCROLLWIDTHTRACKING, stc_def->GetScrollWidthTracking() );

    //SCI_GETSCROLLWIDTHTRACKING
        addStringProp(st, "GetScrollWidthTracking", "SCI_GETSCROLLWIDTHTRACKING", SCI_GETSCROLLWIDTHTRACKING,true,true);

    //SCI_SETENDATLASTLINE(bool endAtLastLine)
        addBoolProp(st,"SetEndAtLastLine","SCI_SETENDATLASTLINE",SCI_SETENDATLASTLINE, stc_def->GetEndAtLastLine() );

    //SCI_GETENDATLASTLINE
        addStringProp(st, "GetEndAtLastLine", "SCI_GETENDATLASTLINE", SCI_GETENDATLASTLINE,true,true);

    m_propgrid->Collapse(st);
}


void propgridtest03Frame::addWhiteSpace(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_WS_INVISIBLE");
        cases.Add("wxSTC_WS_VISIBLEALWAYS");
        cases.Add("wxSTC_WS_VISIBLEAFTERINDENT");

        cases_values.Add(wxSTC_WS_INVISIBLE);
        cases_values.Add(wxSTC_WS_VISIBLEALWAYS);
        cases_values.Add(wxSTC_WS_VISIBLEAFTERINDENT);

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("White space"));
    st->SetClientData(reinterpret_cast<void *>(SCI_WHITESPACE));

    //SCI_SETVIEWWS(int wsMode)
        addEnumProp(st,"SetViewWhiteSpace", "SCI_SETVIEWWS", SCI_SETVIEWWS, stc_def->GetViewWhiteSpace(),cases,cases_values);

    //SCI_GETVIEWWS
        addStringProp(st, "GetViewWhiteSpace", "SCI_GETVIEWWS", SCI_GETVIEWWS,true,true);

    //SCI_SETWHITESPACEFORE(bool useWhitespaceForeColour, int colour)
        wxPGProperty* np=addStringProp(st, "SetWhitespaceForeground", "SCI_SETWHITESPACEFORE", SCI_SETWHITESPACEFORE,false,true);
        addBoolProp(np,"useSetting","zzz",SCI_SETWHITESPACEFOREPARM1,false);
        addColorProp(np, "fore", "zzz", SCI_SETWHITESPACEFOREPARM2, *wxBLACK );
        m_propgrid->Collapse(np);

    //SCI_SETWHITESPACEBACK(bool useWhitespaceBackColour, int colour)
        np=addStringProp(st, "SetWhitespaceBackground", "SCI_SETWHITESPACEBACK", SCI_SETWHITESPACEBACK,false,true);
        addBoolProp(np,"useSetting","zzz",SCI_SETWHITESPACEBACKPARM1,false);
        addColorProp(np, "back", "zzz", SCI_SETWHITESPACEBACKPARM2, *wxWHITE );
        m_propgrid->Collapse(np);

    //SCI_SETWHITESPACESIZE(int size)
        addIntProp(st,"SetWhitespaceSize","SCI_SETWHITESPACESIZE",SCI_SETWHITESPACESIZE,stc_def->GetWhitespaceSize(),0,INT_MAX);

    //SCI_GETWHITESPACESIZE
        addStringProp(st, "GetWhitespaceSize", "SCI_GETWHITESPACESIZE", SCI_GETWHITESPACESIZE,true,true);

    //SCI_SETEXTRAASCENT(int extraAscent)
        addIntProp(st,"SetExtraAscent","SCI_SETEXTRAASCENT",SCI_SETEXTRAASCENT,stc_def->GetExtraAscent(),INT_MIN,INT_MAX);

    //SCI_GETEXTRAASCENT
        addStringProp(st, "GetExtraAscent", "SCI_GETEXTRAASCENT", SCI_GETEXTRAASCENT,true,true);

    //SCI_SETEXTRADESCENT(int extraDescent)
        addIntProp(st,"SetExtraDescent","SCI_SETEXTRADESCENT",SCI_SETEXTRADESCENT,stc_def->GetExtraDescent(),INT_MIN,INT_MAX);

    //SCI_GETEXTRADESCENT
        addStringProp(st, "GetExtraDescent", "SCI_GETEXTRADESCENT", SCI_GETEXTRADESCENT,true,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addCursor(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_CURSORNORMAL");
        cases.Add("wxSTC_CURSORARROW");
        cases.Add("wxSTC_CURSORWAIT");
        cases.Add("wxSTC_CURSORREVERSEARROW");

        cases_values.Add(wxSTC_CURSORNORMAL);
        cases_values.Add(wxSTC_CURSORARROW);
        cases_values.Add(wxSTC_CURSORWAIT);
        cases_values.Add(wxSTC_CURSORREVERSEARROW);

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Cursor"));
    st->SetClientData(reinterpret_cast<void *>(SCI_CURSOR));

    //SCI_SETCURSOR(int curType)
        addEnumProp(st,"SetSTCCursor","SCI_SETCURSOR",SCI_SETCURSOR,stc_def->GetSTCCursor(),cases,cases_values);

    //SCI_GETCURSOR
        addStringProp(st, "GetSTCCursor", "SCI_GETCURSOR", SCI_GETCURSOR,true,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addMouseCapture(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Mouse capture"));
    st->SetClientData(reinterpret_cast<void *>(SCI_MOUSECAPTURE));

    //SCI_SETMOUSEDOWNCAPTURES(bool captures)
        addBoolProp(st,"SetMouseDownCaptures","SCI_SETMOUSEDOWNCAPTURES",SCI_SETMOUSEDOWNCAPTURES,stc_def->GetMouseDownCaptures());

    //SCI_GETMOUSEDOWNCAPTURES
        addStringProp(st, "GetMouseDownCaptures", "SCI_GETMOUSEDOWNCAPTURES", SCI_GETMOUSEDOWNCAPTURES,true,true);

    m_propgrid->Collapse(st);
}


void propgridtest03Frame::addLineEndings(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_EOL_CRLF");
        cases.Add("wxSTC_EOL_CR");
        cases.Add("wxSTC_EOL_LF");

        cases_values.Add(wxSTC_EOL_CRLF);
        cases_values.Add(wxSTC_EOL_CR);
        cases_values.Add(wxSTC_EOL_LF);

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Line endings"));
    st->SetClientData(reinterpret_cast<void *>(SCI_LINEENDINGS));

    //SCI_SETEOLMODE(int eolMode)
        addEnumProp(st,"SetEOLMode","SCI_SETEOLMODE",SCI_SETEOLMODE,stc_def->GetEOLMode(),cases,cases_values);

    //SCI_GETEOLMODE
        addStringProp(st, "GetEOLMode", "SCI_GETEOLMODE", SCI_GETEOLMODE,true,true);

    //SCI_CONVERTEOLS(int eolMode)
        wxPGProperty* np = addStringProp(st, "ConvertEOLs", "SCI_CONVERTEOLS", SCI_CONVERTEOLS,false,true);
        addEnumParam(np,"eolMode", stc_def->GetEOLMode(),cases,cases_values);
        m_propgrid->Collapse(np);

    //SCI_SETVIEWEOL(bool visible)
        addBoolProp(st,"SetViewEOL","SCI_SETVIEWEOL",SCI_SETVIEWEOL,stc_def->GetViewEOL());

    //SCI_GETVIEWEOL
        addStringProp(st, "GetViewEOL", "SCI_GETVIEWEOL", SCI_GETVIEWEOL,true,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addStyling(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("1<<0");
        cases.Add("1<<1");
        cases.Add("1<<2");
        cases.Add("1<<3");
        cases.Add("1<<4");
        cases.Add("1<<5");
        cases.Add("1<<6");
        cases.Add("1<<7");

        cases_values.Add(1<<0);
        cases_values.Add(1<<1);
        cases_values.Add(1<<2);
        cases_values.Add(1<<3);
        cases_values.Add(1<<4);
        cases_values.Add(1<<5);
        cases_values.Add(1<<6);
        cases_values.Add(1<<7);

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Styling"));
    st->SetClientData(reinterpret_cast<void *>(SCI_STYLING));

    //SCI_GETENDSTYLED
        addStringProp(st, "GetEndStyled", "SCI_GETENDSTYLED", SCI_GETENDSTYLED,true,true);

    //SCI_STARTSTYLING(int position, int mask)
        wxPGProperty* np = addStringProp(st, "StartStyling", "SCI_STARTSTYLING", SCI_STARTSTYLING,false,true);
        addIntParam(np,"pos",0,0,INT_MAX);
        addFlagsParam(np,"mask", 0x1f,cases,cases_values);
        m_propgrid->Collapse(np);

    //SCI_SETSTYLING(int length, int style)
        np = addStringProp(st, "SetStyling", "SCI_SETSTYLING", SCI_SETSTYLING,false,true);
        addIntParam(np,"length",1,1,INT_MAX);
        addIntParam(np,"style",0,0,wxSTC_STYLE_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETSTYLINGEX(int length, const char *styles)
        np = m_propgrid->Append(new wxStringProperty("SetStyleBytes","SCI_SETSTYLINGEX"));
        np->SetClientData(reinterpret_cast<void *>(SCI_SETSTYLINGEX));
        m_propgrid->SetPropertyEditor(np, m_StyledTextEditor );
        m_propgrid->SetPropertyReadOnly(np);

        addIntParam(np,"length",1,1,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETLINESTATE(int line, int value)
        np = addStringProp(st, "SetLineState", "SCI_SETLINESTATE", SCI_SETLINESTATE,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addIntParam(np,"state",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETLINESTATE(int line)
        np = addStringProp(st, "GetLineState", "SCI_GETLINESTATE", SCI_GETLINESTATE,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETMAXLINESTATE
        addStringProp(st, "GetMaxLineState", "SCI_GETMAXLINESTATE", SCI_GETMAXLINESTATE,true,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addStyleDefinition(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Style definition"));
    st->SetClientData(reinterpret_cast<void *>(SCI_STYLEDEFINITION));

    //SCI_STYLERESETDEFAULT
        addStringProp(st, "StyleResetDefault", "SCI_STYLERESETDEFAULT", SCI_STYLERESETDEFAULT,false,true);

    //SCI_STYLECLEARALL
        addStringProp(st, "StyleClearAll", "SCI_STYLECLEARALL", SCI_STYLECLEARALL,false,true);

    wxPGProperty* st2 = addStringProp(st, "Style 0 ...wxSTC_STYLE_DEFAULT-1", "zzz", SCI_STYLEDEFINITION,false,false);
    for(int i=0;i<wxSTC_STYLE_DEFAULT;i++)
    {
        addStyle( st2 ,i, lexerInfo->getLexerStyleName(-1,i) , stc_def );
    }
    m_propgrid->Collapse(st2);

    st2 = addStringProp(st, "Predefined numbered styles", "zzz", SCI_STYLEDEFINITION,false,false);
    for(int i=wxSTC_STYLE_DEFAULT;i<wxSTC_STYLE_LASTPREDEFINED;i++)
    {
        addStyle( st2 ,i, lexerInfo->getLexerStyleName(-1,i), stc_def );
    }
    m_propgrid->Collapse(st2);

    st2 = addStringProp(st, "wxSTC_STYLE_LASTPREDEFINED...wxSTC_STYLE_MAX", "zzz", SCI_STYLEDEFINITION,false,false);
    for(int i=wxSTC_STYLE_LASTPREDEFINED;i<=wxSTC_STYLE_MAX;i++)
    {
        addStyle( st2 ,i, lexerInfo->getLexerStyleName(-1,i), stc_def );
    }
    m_propgrid->Collapse(st2);

    st2 = addStringProp(st, "Additional styles", "zzz", SCI_STYLEDEFINITION,false,false);
    for(int i=wxSTC_STYLE_MAX+1;i<wxSTC_STYLE_MAX+11;i++)
    {
        addStyle( st2 ,i, lexerInfo->getLexerStyleName(-1,i), stc_def );
    }
    m_propgrid->Collapse(st2);


    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addStyle(wxPGProperty* st ,int sno,const wxString& desc,wxStyledTextCtrl* stc_def)
{
        wxArrayString cases2;
        wxArrayInt cases2_values;
        cases2.Add("wxSTC_WEIGHT_NORMAL");
        cases2.Add("wxSTC_WEIGHT_SEMIBOLD");
        cases2.Add("wxSTC_WEIGHT_BOLD");
        cases2.Add("(specidied weight)");
        cases2_values.Add(wxSTC_WEIGHT_NORMAL);
        cases2_values.Add(wxSTC_WEIGHT_SEMIBOLD);
        cases2_values.Add(wxSTC_WEIGHT_BOLD);
        cases2_values.Add(-1);

        wxArrayString cases3;
        wxArrayInt cases3_values;

        cases3.Add("wxSTC_CHARSET_ANSI");
        cases3.Add("wxSTC_CHARSET_DEFAULT");
        cases3.Add("wxSTC_CHARSET_BALTIC");
        cases3.Add("wxSTC_CHARSET_CHINESEBIG5");
        cases3.Add("wxSTC_CHARSET_EASTEUROPE");
        cases3.Add("wxSTC_CHARSET_GB2312");
        cases3.Add("wxSTC_CHARSET_GREEK");
        cases3.Add("wxSTC_CHARSET_HANGUL");
        cases3.Add("wxSTC_CHARSET_MAC");
        cases3.Add("wxSTC_CHARSET_OEM");
        cases3.Add("wxSTC_CHARSET_RUSSIAN");
        cases3.Add("wxSTC_CHARSET_CYRILLIC");
        cases3.Add("wxSTC_CHARSET_SHIFTJIS");
        cases3.Add("wxSTC_CHARSET_SYMBOL");
        cases3.Add("wxSTC_CHARSET_TURKISH");
        cases3.Add("wxSTC_CHARSET_JOHAB");
        cases3.Add("wxSTC_CHARSET_HEBREW");
        cases3.Add("wxSTC_CHARSET_ARABIC");
        cases3.Add("wxSTC_CHARSET_VIETNAMESE");
        cases3.Add("wxSTC_CHARSET_THAI");
        cases3.Add("wxSTC_CHARSET_8859_15");
        cases3_values.Add(wxSTC_CHARSET_ANSI);
        cases3_values.Add(wxSTC_CHARSET_DEFAULT);
        cases3_values.Add(wxSTC_CHARSET_BALTIC);
        cases3_values.Add(wxSTC_CHARSET_CHINESEBIG5);
        cases3_values.Add(wxSTC_CHARSET_EASTEUROPE);
        cases3_values.Add(wxSTC_CHARSET_GB2312);
        cases3_values.Add(wxSTC_CHARSET_GREEK);
        cases3_values.Add(wxSTC_CHARSET_HANGUL);
        cases3_values.Add(wxSTC_CHARSET_MAC);
        cases3_values.Add(wxSTC_CHARSET_OEM);
        cases3_values.Add(wxSTC_CHARSET_RUSSIAN);
        cases3_values.Add(wxSTC_CHARSET_CYRILLIC);
        cases3_values.Add(wxSTC_CHARSET_SHIFTJIS);
        cases3_values.Add(wxSTC_CHARSET_SYMBOL);
        cases3_values.Add(wxSTC_CHARSET_TURKISH);
        cases3_values.Add(wxSTC_CHARSET_JOHAB);
        cases3_values.Add(wxSTC_CHARSET_HEBREW);
        cases3_values.Add(wxSTC_CHARSET_ARABIC);
        cases3_values.Add(wxSTC_CHARSET_VIETNAMESE);
        cases3_values.Add(wxSTC_CHARSET_THAI);
        cases3_values.Add(wxSTC_CHARSET_8859_15);

        wxArrayString cases4;
        wxArrayInt cases4_values;
        cases4.Add("wxSTC_CASE_MIXED");
        cases4.Add("wxSTC_CASE_UPPER");
        cases4.Add("wxSTC_CASE_LOWER");
        cases4_values.Add(wxSTC_CASE_MIXED);
        cases4_values.Add(wxSTC_CASE_UPPER);
        cases4_values.Add(wxSTC_CASE_LOWER);

    wxPGProperty* st2 = addStringProp(st, desc, "zzz", SCI_PARAM,false,true);
    st2->SetClientObject( new myStyleData(sno) );
    lexerInfo->setStylesVec(sno,st2);

    //SCI_STYLESETFONT(int styleNumber, char *fontName)
        wxArrayString cases = wxFontEnumerator::GetFacenames();
        cases.Sort();
        wxPGProperty* np = m_propgrid->AppendIn(st2,new wxEnumProperty("StyleSetFaceName","SCI_STYLESETFONT",cases));
        np->SetClientData(reinterpret_cast<void *>(SCI_STYLESETFONT));
        wxString s = stc_def->StyleGetFaceName(sno);
        if(s=="")
        {
            np->SetValueToUnspecified();
        }
        else
        {
            np->SetValueFromString(stc_def->StyleGetFaceName(sno));
        }

    //SCI_STYLEGETFONT(int styleNumber, char *fontName)
        addStringProp(st2, "StyleGetFaceName", "SCI_STYLEGETFONT", SCI_STYLEGETFONT,true,true);

    //SCI_STYLESETSIZE(int styleNumber, int sizeInPoints)
        addIntProp(st2,"StyleSetSize","SCI_STYLESETSIZE",SCI_STYLESETSIZE,stc_def->StyleGetSize(sno),0,INT_MAX);

    //SCI_STYLEGETSIZE(int styleNumber)
        addStringProp(st2, "StyleGetSize", "SCI_STYLEGETSIZE", SCI_STYLEGETSIZE,true,true);

    //SCI_STYLESETSIZEFRACTIONAL(int styleNumber, int sizeInHundredthPoints)
        addIntProp(st2,"StyleSetSizeFractional","SCI_STYLESETSIZEFRACTIONAL",SCI_STYLESETSIZEFRACTIONAL,stc_def->StyleGetSizeFractional(sno),0,INT_MAX);

    //SCI_STYLEGETSIZEFRACTIONAL(int styleNumber)
        addStringProp(st2, "StyleGetSizeFractional", "SCI_STYLEGETSIZEFRACTIONAL", SCI_STYLEGETSIZEFRACTIONAL,true,true);

    //SCI_STYLESETBOLD(int styleNumber, bool bold)
        addBoolProp(st2,"StyleSetBold","SCI_STYLESETBOLD",SCI_STYLESETBOLD,stc_def->StyleGetBold(sno));

    //SCI_STYLEGETBOLD(int styleNumber)
        addStringProp(st2, "StyleGetBold", "SCI_STYLEGETBOLD", SCI_STYLEGETBOLD,true,true);

    //SCI_STYLESETWEIGHT(int styleNumber, int weight)
        np = addEnumProp(st2,"StyleSetWeight","SCI_STYLESETWEIGHT",SCI_STYLESETWEIGHT2,stc_def->StyleGetWeight(sno),cases2,cases2_values);
        wxPGProperty* np2 = addIntProp(np,"weight","zzz",SCI_STYLESETWEIGHT,stc_def->StyleGetWeight(sno),1 ,999);
        np2->Enable(false);
        m_propgrid->Collapse(np);

    //SCI_STYLEGETWEIGHT(int styleNumber)
        addStringProp(st2, "StyleGetWeight", "SCI_STYLEGETWEIGHT", SCI_STYLEGETWEIGHT,true,true);

    //SCI_STYLESETITALIC(int styleNumber, bool italic)
        addBoolProp(st2,"StyleSetItalic","SCI_STYLESETITALIC",SCI_STYLESETITALIC,stc_def->StyleGetItalic(sno));

    //SCI_STYLEGETITALIC(int styleNumber)
        addStringProp(st2, "StyleGetItalic", "SCI_STYLEGETITALIC", SCI_STYLEGETITALIC,true,true);

    //SCI_STYLESETUNDERLINE(int styleNumber, bool underline)
        addBoolProp(st2,"StyleSetUnderline","SCI_STYLESETUNDERLINE",SCI_STYLESETUNDERLINE,stc_def->StyleGetBold(sno));

    //SCI_STYLEGETUNDERLINE(int styleNumber)
        addStringProp(st2, "StyleGetUnderline", "SCI_STYLEGETUNDERLINE", SCI_STYLEGETUNDERLINE,true,true);

    //SCI_STYLESETFORE(int styleNumber, int colour)
        addColorProp(st2, "StyleSetForeground", "SCI_STYLESETFORE", SCI_STYLESETFORE, stc_def->StyleGetForeground(sno)  );

    //SCI_STYLEGETFORE(int styleNumber)
        addColorStringProp(st2, "StyleGetForeground", "SCI_STYLEGETFORE", SCI_STYLEGETFORE);

    //SCI_STYLESETBACK(int styleNumber, int colour)
        addColorProp(st2, "StyleSetBackground", "SCI_STYLESETBACK", SCI_STYLESETBACK, stc_def->StyleGetBackground(sno)  );

    //SCI_STYLEGETBACK(int styleNumber)
        addColorStringProp(st2, "StyleGetBackground", "SCI_STYLEGETBACK", SCI_STYLEGETBACK);

    //SCI_STYLESETEOLFILLED(int styleNumber, bool eolFilled)
        addBoolProp(st2,"StyleSetEOLFilled","SCI_STYLESETEOLFILLED",SCI_STYLESETEOLFILLED,stc_def->StyleGetEOLFilled(sno));

    //SCI_STYLEGETEOLFILLED(int styleNumber)
        addStringProp(st2, "StyleGetEOLFilled", "SCI_STYLEGETEOLFILLED", SCI_STYLEGETEOLFILLED,true,true);

    //SCI_STYLESETCHARACTERSET(int styleNumber, int charSet)
        addEnumProp(st2,"SCI_STYLESETCHARACTERSET","SCI_STYLESETCHARACTERSET",SCI_STYLESETCHARACTERSET,stc_def->StyleGetCharacterSet(sno),cases3,cases3_values);

    //SCI_STYLEGETCHARACTERSET(int styleNumber)
        addStringProp(st2, "StyleGetCharacterSet", "SCI_STYLEGETCHARACTERSET", SCI_STYLEGETCHARACTERSET,true,true);

    //SCI_STYLESETCASE(int styleNumber, int caseMode)
        addEnumProp(st2,"StyleSetCase","SCI_STYLESETCASE",SCI_STYLESETCASE,stc_def->StyleGetCase(sno),cases4,cases4_values);

    //SCI_STYLEGETCASE(int styleNumber)
        addStringProp(st2, "StyleGetCase", "SCI_STYLEGETCASE", SCI_STYLEGETCASE,true,true);

    //SCI_STYLESETVISIBLE(int styleNumber, bool visible)
        addBoolProp(st2,"StyleSetVisible","SCI_STYLESETVISIBLE",SCI_STYLESETVISIBLE,stc_def->StyleGetVisible(sno));

    //SCI_STYLEGETVISIBLE(int styleNumber)
        addStringProp(st2, "StyleGetVisible", "SCI_STYLEGETVISIBLE", SCI_STYLEGETVISIBLE,true,true);

    //SCI_STYLESETCHANGEABLE(int styleNumber, bool changeable)
        addBoolProp(st2,"StyleSetChangeable","SCI_STYLESETCHANGEABLE",SCI_STYLESETCHANGEABLE,stc_def->StyleGetChangeable(sno));

    //SCI_STYLEGETCHANGEABLE(int styleNumber)
        addStringProp(st2, "StyleGetChangeable", "SCI_STYLEGETCHANGEABLE", SCI_STYLEGETCHANGEABLE,true,true);

    //SCI_STYLESETHOTSPOT(int styleNumber, bool hotspot)
        addBoolProp(st2,"StyleSetHotSpot","SCI_STYLESETHOTSPOT",SCI_STYLESETHOTSPOT,stc_def->StyleGetHotSpot(sno));

    //SCI_STYLEGETHOTSPOT(int styleNumber)
        addStringProp(st2, "StyleGetHotSpot", "SCI_STYLEGETHOTSPOT", SCI_STYLEGETHOTSPOT,true,true);

    m_propgrid->Collapse(st2);
}

void propgridtest03Frame::addCaretSelectionAndHotspotStyles(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;
        cases.Add("wxSTC_CARETSTYLE_INVISIBLE");
        cases.Add("wxSTC_CARETSTYLE_LINE");
        cases.Add("wxSTC_CARETSTYLE_BLOCK");
        cases_values.Add(wxSTC_CARETSTYLE_INVISIBLE);
        cases_values.Add(wxSTC_CARETSTYLE_LINE);
        cases_values.Add(wxSTC_CARETSTYLE_BLOCK);

        wxArrayString cases2;
        wxArrayInt cases2_values;
        cases2.Add("wxSTC_CARETSTICKY_OFF");
        cases2.Add("wxSTC_CARETSTICKY_ON");
        cases2.Add("wxSTC_CARETSTICKY_WHITESPACE");
        cases2_values.Add(wxSTC_CARETSTICKY_OFF);
        cases2_values.Add(wxSTC_CARETSTICKY_ON);
        cases2_values.Add(wxSTC_CARETSTICKY_WHITESPACE);

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Caret, selection, and hotspot styles"));
    st->SetClientData(reinterpret_cast<void *>(SCI_CARETSELECTIONANDHOTSPOTSTYLES));

    //SCI_SETSELFORE(bool useSelectionForeColour, int colour)
        wxPGProperty* np=addStringProp(st, "SetSelForeground", "SCI_SETSELFORE", SCI_SETSELFORE,false,true);
        addBoolProp(np,"useSetting","zzz",SCI_SETSELFOREPARM1,false);
        addColorProp(np, "fore", "zzz", SCI_SETSELFOREPARM2, *wxBLACK );
        m_propgrid->Collapse(np);

    //SCI_SETSELBACK(bool useSelectionBackColour, int colour)
        np=addStringProp(st, "SetSelBackground", "SCI_SETSELBACK", SCI_SETSELBACK,false,true);
        addBoolProp(np,"useSetting","zzz",SCI_SETSELBACKPARM1,false);
        addColorProp(np, "fore", "zzz", SCI_SETSELBACKPARM2, wxColor(192,192,192) );
        m_propgrid->Collapse(np);

    //SCI_SETSELALPHA(int alpha)
        addIntProp(st,"SetSelAlpha","SCI_SETSELALPHA",SCI_SETSELALPHA,stc_def->GetSelAlpha() ,0,256);

    //SCI_GETSELALPHA
        addStringProp(st, "GetSelAlpha", "SCI_GETSELALPHA", SCI_GETSELALPHA,true,true);

    //SCI_SETSELEOLFILLED(bool filled)
        addBoolProp(st,"SetSelEOLFilled","SCI_SETSELEOLFILLED",SCI_SETSELEOLFILLED,stc_def->GetSelEOLFilled());

    //SCI_GETSELEOLFILLED
        addStringProp(st, "GetSelEOLFilled", "SCI_GETSELEOLFILLED", SCI_GETSELEOLFILLED,true,true);

    //SCI_SETCARETFORE(int colour)
        addColorProp(st, "SetCaretForeground", "SCI_SETCARETFORE", SCI_SETCARETFORE, stc_def->GetCaretForeground() );

    //SCI_GETCARETFORE
        addColorStringProp(st, "GetCaretForeground", "SCI_GETCARETFORE", SCI_GETCARETFORE);

    //SCI_SETCARETLINEVISIBLE(bool show)
        addBoolProp(st,"SetCaretLineVisible","SCI_SETCARETLINEVISIBLE",SCI_SETCARETLINEVISIBLE,stc_def->GetCaretLineVisible());

    //SCI_GETCARETLINEVISIBLE
        addStringProp(st, "GetCaretLineVisible", "SCI_GETCARETLINEVISIBLE", SCI_GETCARETLINEVISIBLE,true,true);

    //SCI_SETCARETLINEBACK(int colour)
        addColorProp(st, "SetCaretLineBackground", "SCI_SETCARETLINEBACK", SCI_SETCARETLINEBACK, stc_def->GetCaretLineBackground() );

    //SCI_GETCARETLINEBACK
        addColorStringProp(st, "GetCaretLineBackground", "SCI_GETCARETLINEBACK", SCI_GETCARETLINEBACK);

    //SCI_SETCARETLINEBACKALPHA(int alpha)
        addIntProp(st,"SetCaretLineBackAlpha","SCI_SETCARETLINEBACKALPHA",SCI_SETCARETLINEBACKALPHA,stc_def->GetCaretLineBackAlpha() ,0,256);

    //SCI_GETCARETLINEBACKALPHA
        addStringProp(st, "GetCaretLineBackAlpha", "SCI_GETCARETLINEBACKALPHA", SCI_GETCARETLINEBACKALPHA,true,true);

    //SCI_SETCARETPERIOD(int milliseconds)
        addIntProp(st,"SetCaretPeriod","SCI_SETCARETPERIOD",SCI_SETCARETPERIOD,stc_def->GetCaretPeriod() ,0,INT_MAX);

    //SCI_GETCARETPERIOD
        addStringProp(st, "GetCaretPeriod", "SCI_GETCARETPERIOD", SCI_GETCARETPERIOD,true,true);

    //SCI_SETCARETSTYLE(int style)
        addEnumProp(st,"SetCaretStyle","SCI_SETCARETSTYLE",SCI_SETCARETSTYLE,stc_def->GetCaretStyle(),cases,cases_values);

    //SCI_GETCARETSTYLE
        addStringProp(st, "GetCaretStyle", "SCI_GETCARETSTYLE", SCI_GETCARETSTYLE,true,true);

    //SCI_SETCARETWIDTH(int pixels)
        addIntProp(st,"SetCaretWidth","SCI_SETCARETWIDTH",SCI_SETCARETWIDTH,stc_def->GetCaretWidth() ,0,3);

    //SCI_GETCARETWIDTH
        addStringProp(st, "GetCaretWidth", "SCI_GETCARETWIDTH", SCI_GETCARETWIDTH,true,true);

    //SCI_SETHOTSPOTACTIVEFORE(bool useSetting, int colour)
        np=addStringProp(st, "SetHotspotActiveForeground", "SCI_SETHOTSPOTACTIVEFORE", SCI_SETHOTSPOTACTIVEFORE,false,true);
        addBoolProp(np,"useSetting","zzz",SCI_SETHOTSPOTACTIVEFOREPARM1,false);
        addColorProp(np, "fore", "zzz", SCI_SETHOTSPOTACTIVEFOREPARM2, stc_def->GetHotspotActiveForeground() );
        m_propgrid->Collapse(np);

    //SCI_GETHOTSPOTACTIVEFORE
        addColorStringProp(st, "GetHotspotActiveForeground", "SCI_GETHOTSPOTACTIVEFORE", SCI_GETHOTSPOTACTIVEFORE);

    //SCI_SETHOTSPOTACTIVEBACK(bool useSetting, int colour)
        np=addStringProp(st, "SetHotspotActiveBackground", "SCI_SETHOTSPOTACTIVEBACK", SCI_SETHOTSPOTACTIVEBACK,false,true);
        addBoolProp(np,"useSetting","zzz",SCI_SETHOTSPOTACTIVEBACKPARM1,false);
        addColorProp(np, "back", "zzz", SCI_SETHOTSPOTACTIVEBACKPARM2, stc_def->GetHotspotActiveBackground() );
        m_propgrid->Collapse(np);

    //SCI_GETHOTSPOTACTIVEBACK
        addColorStringProp(st, "GetHotspotActiveBackground", "SCI_GETHOTSPOTACTIVEBACK", SCI_GETHOTSPOTACTIVEBACK);

    //SCI_SETHOTSPOTACTIVEUNDERLINE(bool underline)
        addBoolProp(st,"SetHotspotActiveUnderline","SCI_SETHOTSPOTACTIVEUNDERLINE",SCI_SETHOTSPOTACTIVEUNDERLINE,stc_def->GetHotspotActiveUnderline());

    //SCI_GETHOTSPOTACTIVEUNDERLINE
        addStringProp(st, "GetHotspotActiveUnderline", "SCI_GETHOTSPOTACTIVEUNDERLINE", SCI_GETHOTSPOTACTIVEUNDERLINE,true,true);

    //SCI_SETHOTSPOTSINGLELINE(bool singleLine)
        addBoolProp(st,"SetHotspotSingleLine","SCI_SETHOTSPOTSINGLELINE",SCI_SETHOTSPOTSINGLELINE,stc_def->GetHotspotSingleLine());

    //SCI_GETHOTSPOTSINGLELINE
        addStringProp(st, "GetHotspotSingleLine", "SCI_GETHOTSPOTSINGLELINE", SCI_GETHOTSPOTSINGLELINE,true,true);

    //SCI_SETCONTROLCHARSYMBOL(int symbol)
        addIntProp(st,"SetControlCharSymbol","SCI_SETCONTROLCHARSYMBOL",SCI_SETCONTROLCHARSYMBOL,stc_def->GetControlCharSymbol(),0,255);

    //SCI_GETCONTROLCHARSYMBOL
        addStringProp(st, "GetControlCharSymbol", "SCI_GETCONTROLCHARSYMBOL", SCI_GETCONTROLCHARSYMBOL,true,true);

    //SCI_SETCARETSTICKY(int useCaretStickyBehaviour)
        addEnumProp(st,"SetCaretSticky","SCI_SETCARETSTICKY",SCI_SETCARETSTICKY,stc_def->GetCaretSticky(),cases2,cases2_values);

    //SCI_GETCARETSTICKY
        addStringProp(st, "GetCaretSticky", "SCI_GETCARETSTICKY", SCI_GETCARETSTICKY,true,true);

    //SCI_TOGGLECARETSTICKY
        addStringProp(st, "ToggleCaretSticky", "SCI_TOGGLECARETSTICKY", SCI_TOGGLECARETSTICKY,false,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addMargins(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_MARGINOPTION_NONE");
        cases.Add("wxSTC_MARGINOPTION_SUBLINESELECT");

        cases_values.Add(wxSTC_MARGINOPTION_NONE);
        cases_values.Add(wxSTC_MARGINOPTION_SUBLINESELECT);


    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Margins"));
    st->SetClientData(reinterpret_cast<void *>(SCI_MARGINS));

    //SCI_SETMARGINTYPEN(int margin, int type)
    //SCI_GETMARGINTYPEN(int margin)
    //SCI_SETMARGINWIDTHN(int margin, int pixelWidth)
    //SCI_GETMARGINWIDTHN(int margin)
    //SCI_SETMARGINMASKN(int margin, int mask)
    //SCI_GETMARGINMASKN(int margin)
    //SCI_SETMARGINSENSITIVEN(int margin, bool sensitive)
    //SCI_GETMARGINSENSITIVEN(int margin)
    //SCI_SETMARGINCURSORN(int margin, int cursor)
    //SCI_GETMARGINCURSORN(int margin)
        addMargin( st ,0,"",stc_def);
        addMargin( st ,1,"",stc_def);
        addMargin( st ,2,"",stc_def);
        addMargin( st ,3,"",stc_def);
        addMargin( st ,4,"",stc_def);

    //SCI_SETMARGINLEFT(<unused>, int pixels)
        addIntProp(st,"SetMarginLeft","SCI_SETMARGINLEFT",SCI_SETMARGINLEFT,stc_def->GetMarginLeft(),0,INT_MAX);

    //SCI_GETMARGINLEFT
        addStringProp(st, "GetMarginLeft", "SCI_GETMARGINLEFT", SCI_GETMARGINLEFT,true,true);

    //SCI_SETMARGINRIGHT(<unused>, int pixels)
        addIntProp(st,"SetMarginRight","SCI_SETMARGINRIGHT",SCI_SETMARGINRIGHT,stc_def->GetMarginRight(),0,INT_MAX);

    //SCI_GETMARGINRIGHT
        addStringProp(st, "GetMarginRight", "SCI_GETMARGINRIGHT", SCI_GETMARGINRIGHT,true,true);

    //SCI_SETFOLDMARGINCOLOUR(bool useSetting, int colour)
        wxPGProperty* np = addStringProp(st, "SetFoldMarginColour", "SCI_SETFOLDMARGINCOLOUR", SCI_SETFOLDMARGINCOLOUR,false,true);
        addBoolProp(np,"useSetting","zzz",SCI_SETFOLDMARGINCOLOURPARM1,false);
        addColorProp(np, "back", "zzz", SCI_SETFOLDMARGINCOLOURPARM2, wxSYS_COLOUR_3DFACE );
        m_propgrid->Collapse(np);

    //SCI_SETFOLDMARGINHICOLOUR(bool useSetting, int colour)
        np = addStringProp(st, "SetFoldMarginHiColour", "SCI_SETFOLDMARGINHICOLOUR", SCI_SETFOLDMARGINHICOLOUR,false,true);
        addBoolProp(np,"useSetting","zzz",SCI_SETFOLDMARGINHICOLOURPARM1,false);
        addColorProp(np, "fore", "zzz", SCI_SETFOLDMARGINHICOLOURPARM2, wxSYS_COLOUR_3DHIGHLIGHT );
        m_propgrid->Collapse(np);

    //SCI_MARGINSETTEXT(int line, char *text)
        np = addStringProp(st, "MarginSetText", "SCI_MARGINSETTEXT", SCI_MARGINSETTEXT,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addStringParam(np, "label",false);
        m_propgrid->Collapse(np);

    //SCI_MARGINGETTEXT(int line, char *text)
        np = addStringProp(st, "MarginGetText", "SCI_MARGINGETTEXT", SCI_MARGINGETTEXT,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_MARGINSETSTYLE(int line, int style)
        np = addStringProp(st, "MarginSetStyle", "SCI_MARGINSETSTYLE", SCI_MARGINSETSTYLE,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addIntParam(np,"style",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_MARGINGETSTYLE(int line)
        np = addStringProp(st, "MarginGetStyle", "SCI_MARGINGETSTYLE", SCI_MARGINGETSTYLE,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_MARGINSETSTYLES(int line, char *styles)
        np = m_propgrid->Append(new wxStringProperty("MarginSetStyles","SCI_MARGINSETSTYLES"));
        np->SetClientData(reinterpret_cast<void *>(SCI_MARGINSETSTYLES));
        m_propgrid->SetPropertyEditor(np, m_StyledTextEditor );
        m_propgrid->SetPropertyReadOnly(np);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_MARGINGETSTYLES(int line, char *styles)
        np = m_propgrid->Append(new wxStringProperty("MarginGetStyles","SCI_MARGINGETSTYLES"));
        np->SetClientData(reinterpret_cast<void *>(SCI_MARGINGETSTYLES));
        m_propgrid->SetPropertyEditor(np, m_StyledTextEditor );
        m_propgrid->SetPropertyReadOnly(np);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_MARGINTEXTCLEARALL
        addStringProp(st, "MarginTextClearAll", "SCI_MARGINTEXTCLEARALL", SCI_MARGINTEXTCLEARALL,false,true);

    //SCI_MARGINSETSTYLEOFFSET(int style)
        addIntProp(st,"MarginSetStyleOffset","SCI_MARGINSETSTYLEOFFSET",SCI_MARGINSETSTYLEOFFSET,stc_def->MarginGetStyleOffset(),0,INT_MAX);

    //SCI_MARGINGETSTYLEOFFSET
        addStringProp(st, "MarginGetStyleOffset", "SCI_MARGINGETSTYLEOFFSET", SCI_MARGINGETSTYLEOFFSET,true,true);

    //SCI_SETMARGINOPTIONS(int marginOptions)
        addEnumProp(st,"SetMarginOptions","SCI_SETMARGINOPTIONS",SCI_SETMARGINOPTIONS,stc_def->GetMarginOptions(),cases,cases_values);

    //SCI_GETMARGINOPTIONS
        addStringProp(st, "GetMarginOptions", "SCI_GETMARGINOPTIONS", SCI_GETMARGINOPTIONS,true,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addMargin(wxPGProperty* st ,int sno,const wxString& desc,wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;
        cases.Add("wxSTC_MARGIN_SYMBOL");
        cases.Add("wxSTC_MARGIN_NUMBER");
        cases.Add("wxSTC_MARGIN_BACK");
        cases.Add("wxSTC_MARGIN_FORE");
        cases.Add("wxSTC_MARGIN_TEXT");
        cases.Add("wxSTC_MARGIN_RTEXT");
        cases_values.Add(wxSTC_MARGIN_SYMBOL);
        cases_values.Add(wxSTC_MARGIN_NUMBER);
        cases_values.Add(wxSTC_MARGIN_BACK);
        cases_values.Add(wxSTC_MARGIN_FORE);
        cases_values.Add(wxSTC_MARGIN_TEXT);
        cases_values.Add(wxSTC_MARGIN_RTEXT);

        wxArrayString cases2;
        wxArrayInt cases2_values;
        cases2.Add("0");
        cases2.Add("wxSTC_MASK_FOLDERS");
        cases2.Add("~wxSTC_MASK_FOLDERS");
        cases2.Add("(set bits)");
        cases2_values.Add(0);
        cases2_values.Add(wxSTC_MASK_FOLDERS);
        cases2_values.Add(~wxSTC_MASK_FOLDERS);
        cases2_values.Add(-1);

        wxArrayString cases3;
        wxArrayInt cases3_values;

        for(int i=0;i<32;i++)
        {
            if(i==wxSTC_MARKNUM_FOLDEREND)
            {
                cases3.Add(wxString::Format("wxSTC_MARKNUM_FOLDEREND (bit %d)",i));
            }
            else if(i==wxSTC_MARKNUM_FOLDEROPENMID)
            {
                cases3.Add(wxString::Format("wxSTC_MARKNUM_FOLDEROPENMID (bit %d)",i));
            }
            else if(i==wxSTC_MARKNUM_FOLDERMIDTAIL)
            {
                cases3.Add(wxString::Format("wxSTC_MARKNUM_FOLDERMIDTAIL (bit %d)",i));
            }
            else if(i==wxSTC_MARKNUM_FOLDERTAIL)
            {
                cases3.Add(wxString::Format("wxSTC_MARKNUM_FOLDERTAIL (bit %d)",i));
            }
            else if(i==wxSTC_MARKNUM_FOLDERSUB)
            {
                cases3.Add(wxString::Format("wxSTC_MARKNUM_FOLDERSUB (bit %d)",i));
            }
            else if(i==wxSTC_MARKNUM_FOLDER)
            {
                cases3.Add(wxString::Format("wxSTC_MARKNUM_FOLDER (bit %d)",i));
            }
            else if(i==wxSTC_MARKNUM_FOLDEROPEN)
            {
                cases3.Add(wxString::Format("wxSTC_MARKNUM_FOLDEROPEN (bit %d)",i));
            }
            else
            {
                cases3.Add(wxString::Format("bit %d",i));
            }

            cases3_values.Add(1<<i);
        }

        wxArrayString cases4;
        wxArrayInt cases4_values;

        cases4.Add("wxSTC_CURSORNORMAL");
        cases4.Add("wxSTC_CURSORARROW");
        cases4.Add("wxSTC_CURSORWAIT");
        cases4.Add("wxSTC_CURSORREVERSEARROW");

        cases4_values.Add(wxSTC_CURSORNORMAL);
        cases4_values.Add(wxSTC_CURSORARROW);
        cases4_values.Add(wxSTC_CURSORWAIT);
        cases4_values.Add(wxSTC_CURSORREVERSEARROW);


    wxPGProperty* st2 = addStringProp(st, wxString::Format("Margin %d",sno), "zzz", SCI_PARAM,false,true);
    st2->SetClientObject( new myStyleData(sno) );

    //SCI_SETMARGINTYPEN(int margin, int type)
        addEnumProp(st2,"SetMarginType","SCI_SETMARGINTYPEN",SCI_SETMARGINTYPEN,stc_def->GetMarginType(sno),cases,cases_values);

    //SCI_GETMARGINTYPEN(int margin)
        addStringProp(st2, "GetMarginType", "SCI_GETMARGINTYPEN", SCI_GETMARGINTYPEN,true,true);

    //SCI_SETMARGINWIDTHN(int margin, int pixelWidth)
        addIntProp(st2,"SetMarginWidth","SCI_SETMARGINWIDTHN",SCI_SETMARGINWIDTHN,stc_def->GetMarginWidth(sno),0,INT_MAX);

    //SCI_GETMARGINWIDTHN(int margin)
        addStringProp(st2, "GetMarginWidth", "SCI_GETMARGINWIDTHN", SCI_GETMARGINWIDTHN,true,true);

    //SCI_SETMARGINMASKN(int margin, int mask)
        wxPGProperty* np = addEnumProp(st2,"SetMarginMask","SCI_SETMARGINMASKN",SCI_SETMARGINMASKN,-1,cases2,cases2_values);
        np->SetValueToUnspecified();
        wxPGProperty* np2 =addFlagsProp(np,"bits","zzz",SCI_SETMARGINMASKN2,stc_def->GetMarginMask(sno),cases3,cases3_values);
        np2->Enable(false);
        m_propgrid->Collapse(np);

    //SCI_GETMARGINMASKN(int margin)
        addStringProp(st2, "GetMarginMask", "SCI_GETMARGINMASKN", SCI_GETMARGINMASKN,true,true);

    //SCI_SETMARGINSENSITIVEN(int margin, bool sensitive)
        addBoolProp(st2,"SetMarginSensitive","SCI_SETMARGINSENSITIVEN",SCI_SETMARGINSENSITIVEN,stc_def->GetMarginSensitive(sno));

    //SCI_GETMARGINSENSITIVEN(int margin)
        addStringProp(st2, "GetMarginSensitive", "SCI_GETMARGINSENSITIVEN", SCI_GETMARGINSENSITIVEN,true,true);

    //SCI_SETMARGINCURSORN(int margin, int cursor)
        addEnumProp(st2,"SetMarginCursor","SCI_SETMARGINCURSORN",SCI_SETMARGINCURSORN,stc_def->GetMarginCursor(sno),cases4,cases4_values);

    //SCI_GETMARGINCURSORN(int margin)
        addStringProp(st2, "GetMarginCursor", "SCI_GETMARGINCURSORN", SCI_GETMARGINCURSORN,true,true);

    m_propgrid->Collapse(st2);
}


void propgridtest03Frame::addAnnotations(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_ANNOTATION_HIDDEN");
        cases.Add("wxSTC_ANNOTATION_STANDARD");
        cases.Add("wxSTC_ANNOTATION_BOXED");

        cases_values.Add(wxSTC_ANNOTATION_HIDDEN);
        cases_values.Add(wxSTC_ANNOTATION_STANDARD);
        cases_values.Add(wxSTC_ANNOTATION_BOXED);

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Annotations"));
    st->SetClientData(reinterpret_cast<void *>(SCI_ANNOTATIONS));

    //SCI_ANNOTATIONSETTEXT(int line, char *text)
        wxPGProperty* np = addStringProp(st, "AnnotationSetText", "SCI_ANNOTATIONSETTEXT", SCI_ANNOTATIONSETTEXT,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addStringParam(np, "text",true);
        m_propgrid->Collapse(np);

    //SCI_ANNOTATIONGETTEXT(int line, char *text)
        np = addStringProp(st, "AnnotationGetText", "SCI_ANNOTATIONGETTEXT", SCI_ANNOTATIONGETTEXT,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_ANNOTATIONSETSTYLE(int line, int style)
        np = addStringProp(st, "AnnotationSetStyle", "SCI_ANNOTATIONSETSTYLE", SCI_ANNOTATIONSETSTYLE,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addIntParam(np,"style",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_ANNOTATIONGETSTYLE(int line)
        np = addStringProp(st, "AnnotationGetStyle", "SCI_ANNOTATIONGETSTYLE", SCI_ANNOTATIONGETSTYLE,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_ANNOTATIONSETSTYLES(int line, char *styles)
        np = addStringProp(st, "AnnotationSetStyles", "SCI_ANNOTATIONSETSTYLES", SCI_ANNOTATIONSETSTYLES,false,true);
        m_propgrid->SetPropertyEditor(np, m_StyledTextEditor );
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_ANNOTATIONGETSTYLES(int line, char *styles)
        np = addStringProp(st, "AnnotationGetStyles", "SCI_ANNOTATIONGETSTYLES", SCI_ANNOTATIONGETSTYLES,false,true);
        m_propgrid->SetPropertyEditor(np, m_StyledTextEditor );
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_ANNOTATIONGETLINES(int line)
        np = addStringProp(st, "AnnotationGetLines", "SCI_ANNOTATIONGETLINES", SCI_ANNOTATIONGETLINES,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_ANNOTATIONCLEARALL
        addStringProp(st, "AnnotationClearAll", "SCI_ANNOTATIONCLEARALL", SCI_ANNOTATIONCLEARALL,false,true);

    //SCI_ANNOTATIONSETVISIBLE(int visible)
        addEnumProp(st,"AnnotationSetVisible","SCI_ANNOTATIONSETVISIBLE",SCI_ANNOTATIONSETVISIBLE,stc_def->AnnotationGetVisible(),cases,cases_values);

    //SCI_ANNOTATIONGETVISIBLE
        addStringProp(st, "AnnotationGetVisible", "SCI_ANNOTATIONGETVISIBLE", SCI_ANNOTATIONGETVISIBLE,true,true);

    //SCI_ANNOTATIONSETSTYLEOFFSET(int style)
        addIntProp(st,"AnnotationSetStyleOffset","SCI_ANNOTATIONSETSTYLEOFFSET",SCI_ANNOTATIONSETSTYLEOFFSET,0,0,INT_MAX);

    //SCI_ANNOTATIONGETSTYLEOFFSET
        addStringProp(st, "AnnotationGetStyleOffset", "SCI_ANNOTATIONGETSTYLEOFFSET", SCI_ANNOTATIONGETSTYLEOFFSET,true,true);

    m_propgrid->Collapse(st);
}


void propgridtest03Frame::addOtherSettings(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_TECHNOLOGY_DEFAULT");
        cases.Add("wxSTC_TECHNOLOGY_DIRECTWRITE");

        cases_values.Add(wxSTC_TECHNOLOGY_DEFAULT);
        cases_values.Add(wxSTC_TECHNOLOGY_DIRECTWRITE);

        wxArrayString cases2;
        wxArrayInt cases_values2;

        cases2.Add("wxSTC_EFF_QUALITY_DEFAULT");
        cases2.Add("wxSTC_EFF_QUALITY_NON_ANTIALIASED");
        cases2.Add("wxSTC_EFF_QUALITY_ANTIALIASED");
        cases2.Add("wxSTC_EFF_QUALITY_LCD_OPTIMIZED");

        cases_values2.Add(wxSTC_EFF_QUALITY_DEFAULT);
        cases_values2.Add(wxSTC_EFF_QUALITY_NON_ANTIALIASED);
        cases_values2.Add(wxSTC_EFF_QUALITY_ANTIALIASED);
        cases_values2.Add(wxSTC_EFF_QUALITY_LCD_OPTIMIZED);

        wxArrayString cases3;
        wxArrayInt cases3_values;

        cases3.Add("0");
        cases3.Add("wxSTC_CP_UTF8");
        cases3.Add("Japanese Shift-JIS");
        cases3.Add("Simplified Chinese GBK");
        cases3.Add("Korean Unified Hangul Code");
        cases3.Add("Traditional Chinese Big5");
        cases3.Add("Korean Johab");

        cases3_values.Add(0);
        cases3_values.Add(wxSTC_CP_UTF8);
        cases3_values.Add(932);
        cases3_values.Add(936);
        cases3_values.Add(949);
        cases3_values.Add(950);
        cases3_values.Add(1361);


    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Other settings"));
    st->SetClientData(reinterpret_cast<void *>(SCI_OTHERSETTINGS));

    //SCI_SETUSEPALETTE(bool allowPaletteUse)
        wxPGProperty* np = m_propgrid->Append(new wxStringProperty("SCI_SETUSEPALETTE","SCI_SETUSEPALETTE"));
        np->SetClientData(reinterpret_cast<void *>(SCI_SETUSEPALETTE));
        m_propgrid->SetPropertyReadOnly(np);
        np->SetBackgroundColour(notImplemented);

    //SCI_GETUSEPALETTE
        np = m_propgrid->Append(new wxStringProperty("SCI_GETUSEPALETTE","SCI_GETUSEPALETTE"));
        np->SetClientData(reinterpret_cast<void *>(SCI_GETUSEPALETTE));
        m_propgrid->SetPropertyReadOnly(np);
        np->SetBackgroundColour(notImplemented);

    //SCI_SETBUFFEREDDRAW(bool isBuffered)
        addBoolProp(st,"SetBufferedDraw","SCI_SETBUFFEREDDRAW",SCI_SETBUFFEREDDRAW,stc_def->GetBufferedDraw() );

    //SCI_GETBUFFEREDDRAW
        addStringProp(st, "GetBufferedDraw", "SCI_GETBUFFEREDDRAW", SCI_GETBUFFEREDDRAW,true,true);

    //SCI_SETTWOPHASEDRAW(bool twoPhase)
        addBoolProp(st,"SetTwoPhaseDraw","SCI_SETTWOPHASEDRAW",SCI_SETTWOPHASEDRAW,stc_def->GetTwoPhaseDraw() );

    //SCI_GETTWOPHASEDRAW
        addStringProp(st, "GetTwoPhaseDraw", "SCI_GETTWOPHASEDRAW", SCI_GETTWOPHASEDRAW,true,true);

    //SCI_SETTECHNOLOGY(int technology)
        addEnumProp(st,"SetTechnology","SCI_SETTECHNOLOGY",SCI_SETTECHNOLOGY,stc_def->GetTechnology(),cases,cases_values);

    //SCI_GETTECHNOLOGY
        addStringProp(st, "GetTechnology", "SCI_GETTECHNOLOGY", SCI_GETTECHNOLOGY,true,true);

    //SCI_SETFONTQUALITY(int fontQuality)
        addEnumProp(st,"SCI_SETFONTQUALITY","SCI_SETFONTQUALITY",SCI_SETFONTQUALITY,stc_def->SendMsg(2612,0,0),cases2,cases_values2);

    //SCI_GETFONTQUALITY
        addStringProp(st, "SCI_GETFONTQUALITY", "SCI_GETFONTQUALITY", SCI_GETFONTQUALITY,true,true);

    //SCI_SETCODEPAGE(int codePage)
        addEnumProp(st,"SetCodePage","SCI_SETCODEPAGE",SCI_SETCODEPAGE,stc_def->SendMsg(2612,0,0),cases3,cases3_values);

    //SCI_GETCODEPAGE
        addStringProp(st, "GetCodePage", "SCI_GETCODEPAGE", SCI_GETCODEPAGE,true,true);

    //SCI_SETKEYSUNICODE(bool keysUnicode)
        addBoolProp(st,"SetKeysUnicode","SCI_SETKEYSUNICODE",SCI_SETKEYSUNICODE,stc_def->GetKeysUnicode());

    //SCI_GETKEYSUNICODE
        addStringProp(st, "GetKeysUnicode", "SCI_GETKEYSUNICODE", SCI_GETKEYSUNICODE,true,true);

    //SCI_SETWORDCHARS(<unused>, const char *characters)
        np=addStringProp(st, "SetWordChars", "SCI_SETWORDCHARS", SCI_SETWORDCHARS,false,true);
        addStringParam(np, "characters",true);
        m_propgrid->Collapse(np);

    //SCI_GETWORDCHARS(<unused>, char *characters)
        addLongStringProp(st, "GetWordChars", "SCI_GETWORDCHARS", SCI_GETWORDCHARS,true,true);

    //SCI_SETWHITESPACECHARS(<unused>, const char *characters)
        np = addStringProp(st, "SetWhitespaceChars", "SCI_SETWHITESPACECHARS", SCI_SETWHITESPACECHARS,false,true);
        addStringParam(np, "characters",true);
        m_propgrid->Collapse(np);

    //SCI_GETWHITESPACECHARS(<unused>, char *characters)
        addLongStringProp(st, "GetWhitespaceChars", "SCI_GETWHITESPACECHARS", SCI_GETWHITESPACECHARS,true,true);

    //SCI_SETPUNCTUATIONCHARS(<unused>, const char *characters)
        np = addStringProp(st, "SetPunctuationChars", "SCI_SETPUNCTUATIONCHARS", SCI_SETPUNCTUATIONCHARS,false,true);
        addStringParam(np, "characters",true);
        m_propgrid->Collapse(np);

    //SCI_GETPUNCTUATIONCHARS(<unused>, char *characters
        addLongStringProp(st, "GetPunctuationChars", "SCI_GETPUNCTUATIONCHARS", SCI_GETPUNCTUATIONCHARS,true,true);

    //SCI_SETCHARSDEFAULT
        addStringProp(st, "SetCharsDefault", "SCI_SETCHARSDEFAULT", SCI_SETCHARSDEFAULT,false,true);

    //SCI_GRABFOCUS
        addStringProp(st, "SCI_GRABFOCUS", "SCI_GRABFOCUS", SCI_GRABFOCUS,false,true);

    //SCI_SETFOCUS(bool focus)
        addBoolProp(st,"SetSTCFocus","SCI_SETFOCUS",SCI_SETFOCUS,stc_def->GetSTCFocus());

    //SCI_GETFOCUS
        addStringProp(st, "GetSTCFocus", "SCI_GETFOCUS", SCI_GETFOCUS,true,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addBraceHighlighting(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Brace highlighting"));
    st->SetClientData(reinterpret_cast<void *>(SCI_BRACEHIGHLIGHTING));

    //SCI_BRACEHIGHLIGHT(int pos1, int pos2)
        wxPGProperty* np = addStringProp(st, "BraceHighlight", "SCI_BRACEHIGHLIGHT", SCI_BRACEHIGHLIGHT,false,true);
        addIntParam(np,"pos1",0,-1,INT_MAX);
        addIntParam(np,"pos2",0,-1,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_BRACEBADLIGHT(int pos1)
        np = addStringProp(st, "BraceBadLight", "SCI_BRACEBADLIGHT", SCI_BRACEBADLIGHT,false,true);
        addIntParam(np,"pos",0,-1,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_BRACEHIGHLIGHTINDICATOR(bool useBraceHighlightIndicator, int indicatorNumber)
        np = m_propgrid->Append(new wxStringProperty("BraceHighlightIndicator", "SCI_BRACEHIGHLIGHTINDICATOR"));
        np->SetClientData(reinterpret_cast<void *>(SCI_BRACEHIGHLIGHTINDICATOR));
        m_propgrid->SetPropertyReadOnly(np);
        addBoolProp(np,"useBraceHighlightIndicator","zzz",SCI_BRACEHIGHLIGHTINDICATORPARM1,false);
        addIntProp(np,"indicator","zzz",SCI_BRACEHIGHLIGHTINDICATORPARM2,0,0,wxSTC_INDIC_MAX);
        m_propgrid->Collapse(np);

    //SCI_BRACEBADLIGHTINDICATOR(bool useBraceBadLightIndicator, int indicatorNumber)
        np = m_propgrid->Append(new wxStringProperty("BraceBadLightIndicator", "SCI_BRACEBADLIGHTINDICATOR"));
        np->SetClientData(reinterpret_cast<void *>(SCI_BRACEBADLIGHTINDICATOR));
        m_propgrid->SetPropertyReadOnly(np);
        addBoolProp(np,"useBraceBadLightIndicator","zzz",SCI_BRACEBADLIGHTINDICATORPARM1,false);
        addIntProp(np,"indicator","zzz",SCI_BRACEBADLIGHTINDICATORPARM2,0,0,wxSTC_INDIC_MAX);
        m_propgrid->Collapse(np);

    //SCI_BRACEMATCH(int position, int maxReStyle)
        np = addStringProp(st, "BraceMatch", "SCI_BRACEMATCH", SCI_BRACEMATCH,true,true);
        addIntParam(np,"pos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addTabsAndIndentationGuides(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;
        cases.Add("wxSTC_IV_NONE");
        cases.Add("wxSTC_IV_REAL");
        cases.Add("wxSTC_IV_LOOKFORWARD");
        cases.Add("wxSTC_IV_LOOKBOTH");
        cases_values.Add(wxSTC_IV_NONE);
        cases_values.Add(wxSTC_IV_REAL);
        cases_values.Add(wxSTC_IV_LOOKFORWARD);
        cases_values.Add(wxSTC_IV_LOOKBOTH);

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Tabs and Indentation Guides"));
    st->SetClientData(reinterpret_cast<void *>(SCI_TABSANDINDENTATIONGUIDES));

    //SCI_SETTABWIDTH(int widthInChars)
        addIntProp(st,"SetTabWidth","SCI_SETTABWIDTH",SCI_SETTABWIDTH,stc_def->GetTabWidth(),0,INT_MAX);

    //SCI_GETTABWIDTH
        addStringProp(st, "GetTabWidth", "SCI_GETTABWIDTH", SCI_GETTABWIDTH,true,true);

    //SCI_SETUSETABS(bool useTabs)
        addBoolProp(st,"SetUseTabs","SCI_SETUSETABS",SCI_SETUSETABS,stc_def->GetUseTabs());

    //SCI_GETUSETABS
        addStringProp(st, "GetUseTabs", "SCI_GETUSETABS", SCI_GETUSETABS,true,true);

    //SCI_SETINDENT(int widthInChars)
        addIntProp(st,"SetIndent","SCI_SETINDENT",SCI_SETINDENT,stc_def->GetIndent(),0,INT_MAX);

    //SCI_GETINDENT
        addStringProp(st, "GetIndent", "SCI_GETINDENT", SCI_GETINDENT,true,true);

    //SCI_SETTABINDENTS(bool tabIndents)
        addBoolProp(st,"SetTabIndents","SCI_SETTABINDENTS",SCI_SETTABINDENTS,stc_def->GetTabIndents());

    //SCI_GETTABINDENTS
        addStringProp(st, "GetTabIndents", "SCI_GETTABINDENTS", SCI_GETTABINDENTS,true,true);

    //SCI_SETBACKSPACEUNINDENTS(bool bsUnIndents)
        addBoolProp(st,"SetBackSpaceUnIndents","SCI_SETBACKSPACEUNINDENTS",SCI_SETBACKSPACEUNINDENTS,stc_def->GetBackSpaceUnIndents());

    //SCI_GETBACKSPACEUNINDENTS
        addStringProp(st, "GetBackSpaceUnIndents", "SCI_GETBACKSPACEUNINDENTS", SCI_GETBACKSPACEUNINDENTS,true,true);

    //SCI_SETLINEINDENTATION(int line, int indentation)
        wxPGProperty* np = addStringProp(st, "SetLineIndentation", "SCI_SETLINEINDENTATION", SCI_SETLINEINDENTATION,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addIntParam(np,"indentSize",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETLINEINDENTATION(int line)
        np = addStringProp(st, "GetLineIndentation", "SCI_GETLINEINDENTATION", SCI_GETLINEINDENTATION,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETLINEINDENTPOSITION(int line)
        np = addStringProp(st, "GetLineIndentPosition", "SCI_GETLINEINDENTPOSITION", SCI_GETLINEINDENTPOSITION,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETINDENTATIONGUIDES(int indentView)
        addEnumProp(st,"SetIndentationGuides","SCI_SETINDENTATIONGUIDES",SCI_SETINDENTATIONGUIDES,stc_def->GetIndentationGuides(),cases,cases_values);

    //SCI_GETINDENTATIONGUIDES
        addStringProp(st, "GetIndentationGuides", "SCI_GETINDENTATIONGUIDES", SCI_GETINDENTATIONGUIDES,true,true);

    //SCI_SETHIGHLIGHTGUIDE(int column)
        addIntProp(st,"SetHighlightGuide","SCI_SETHIGHLIGHTGUIDE",SCI_SETHIGHLIGHTGUIDE,stc_def->GetHighlightGuide(),0,INT_MAX);

    //SCI_GETHIGHLIGHTGUIDE
        addStringProp(st, "GetHighlightGuide", "SCI_GETHIGHLIGHTGUIDE", SCI_GETHIGHLIGHTGUIDE,true,true);

    m_propgrid->Collapse(st);
}


void propgridtest03Frame::addMarkers(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        wxString s;
        for(int i=0;i<=wxSTC_MARKER_MAX;i++)
        {
            if(i==wxSTC_MARKNUM_FOLDEREND)
            {
                s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDEREND",i);
            }
            else if(i==wxSTC_MARKNUM_FOLDEROPENMID)
            {
                s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDEROPENMID",i);
            }
            else if(i==wxSTC_MARKNUM_FOLDERMIDTAIL)
            {
                s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDERMIDTAIL",i);
            }
            else if(i==wxSTC_MARKNUM_FOLDERTAIL)
            {
                s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDERTAIL",i);
            }
            else if(i==wxSTC_MARKNUM_FOLDERSUB)
            {
                s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDERSUB",i);
            }
            else if(i==wxSTC_MARKNUM_FOLDER)
            {
                s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDER",i);
            }
            else if(i==wxSTC_MARKNUM_FOLDEROPEN)
            {
                s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDEROPEN",i);
            }
            else
            {
                s=wxString::Format("Marker %d",i);
            }

            cases.Add(s);
            cases_values.Add(1<<i);
        }

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Markers"));
    st->SetClientData(reinterpret_cast<void *>(SCI_MARKERS));

    wxPGProperty* st2 = addStringHeader(st,"Marker definitions");


    //SCI_MARKERDEFINE(int markerNumber, int markerSymbols)
    //SCI_MARKERDEFINEPIXMAP(int markerNumber, const char *xpm)
    //SCI_RGBAIMAGESETWIDTH(int width)
    //SCI_RGBAIMAGESETHEIGHT(int height)
    //SCI_MARKERDEFINERGBAIMAGE(int markerNumber, const char *pixels)
    //SCI_MARKERSYMBOLDEFINED(int markerNumber)
    //SCI_MARKERSETFORE(int markerNumber, int colour)
    //SCI_MARKERSETBACK(int markerNumber, int colour)
    //SCI_MARKERSETBACKSELECTED(int markerNumber, int colour)
    //SCI_MARKERENABLEHIGHLIGHT(int enabled)
    //SCI_MARKERSETALPHA(int markerNumber, int alpha)
    for(int i=0;i<=wxSTC_MARKER_MAX;i++)
    {
        if(i==wxSTC_MARKNUM_FOLDEREND)
        {
            s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDEREND",i);
        }
        else if(i==wxSTC_MARKNUM_FOLDEROPENMID)
        {
            s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDEROPENMID",i);
        }
        else if(i==wxSTC_MARKNUM_FOLDERMIDTAIL)
        {
            s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDERMIDTAIL",i);
        }
        else if(i==wxSTC_MARKNUM_FOLDERTAIL)
        {
            s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDERTAIL",i);
        }
        else if(i==wxSTC_MARKNUM_FOLDERSUB)
        {
            s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDERSUB",i);
        }
        else if(i==wxSTC_MARKNUM_FOLDER)
        {
            s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDER",i);
        }
        else if(i==wxSTC_MARKNUM_FOLDEROPEN)
        {
            s=wxString::Format("%s (Marker %d)","wxSTC_MARKNUM_FOLDEROPEN",i);
        }
        else
        {
            s=wxString::Format("Marker %d",i);
        }

        addMarker(st2 ,i,s,stc_def);
    }

    m_propgrid->Collapse(st2);

    //SCI_MARKERADD(int line, int markerNumber)
        wxPGProperty* np = addStringProp(st, "MarkerAdd", "SCI_MARKERADD", SCI_MARKERADD,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addIntParam(np,"markerNumber",0,0,wxSTC_MARKER_MAX);
        m_propgrid->Collapse(np);

    //SCI_MARKERADDSET(int line, int markerMask)
        np = addStringProp(st, "MarkerAddSet", "SCI_MARKERADDSET", SCI_MARKERADDSET,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addFlagsParam(np,"set", 0,cases,cases_values);
        m_propgrid->Collapse(np);

    //SCI_MARKERDELETE(int line, int markerNumber)
        np = addStringProp(st, "MarkerDelete", "SCI_MARKERDELETE", SCI_MARKERDELETE,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addIntParam(np,"markerNumber",0,-1,wxSTC_MARKER_MAX);
        m_propgrid->Collapse(np);

    //SCI_MARKERDELETEALL(int markerNumber)
        np = addStringProp(st, "MarkerDeleteAll", "SCI_MARKERDELETEALL", SCI_MARKERDELETEALL,false,true);
        addIntParam(np,"markerNumber",0,-1,wxSTC_MARKER_MAX);
        m_propgrid->Collapse(np);

    //SCI_MARKERGET(int line)
        np = addStringProp(st, "MarkerGet", "SCI_MARKERGET", SCI_MARKERGET,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_MARKERNEXT(int lineStart, int markerMask)
        np = addStringProp(st, "MarkerNext", "SCI_MARKERNEXT", SCI_MARKERNEXT,true,true);
        addIntParam(np,"lineStart",0,0,INT_MAX);
        addFlagsParam(np,"markerMask", 0,cases,cases_values);
        m_propgrid->Collapse(np);

    //SCI_MARKERPREVIOUS(int lineStart, int markerMask)
        np = addStringProp(st, "MarkerPrevious", "SCI_MARKERPREVIOUS", SCI_MARKERPREVIOUS,true,true);

        addIntParam(np,"lineStart",0,0,INT_MAX);
        addFlagsParam(np,"markerMask", 0,cases,cases_values);
        m_propgrid->Collapse(np);

    //SCI_MARKERLINEFROMHANDLE(int handle)
        np = addStringProp(st, "MarkerLineFromHandle", "SCI_MARKERLINEFROMHANDLE", SCI_MARKERLINEFROMHANDLE,false,true);
        wxPGProperty* np2 =m_propgrid->AppendIn(np,new wxStringProperty("handle","zzz"));
        SCI_MARKERLINEFROMHANDLEENUM=np2;
        m_propgrid->Collapse(np);

    //SCI_MARKERDELETEHANDLE(int handle)
        np = addStringProp(st, "MarkerDeleteHandle", "SCI_MARKERDELETEHANDLE", SCI_MARKERDELETEHANDLE,false,true);
        np2 =m_propgrid->AppendIn(np,new wxStringProperty("handle","zzz"));
        SCI_MARKERDELETEHANDLEENUM=np2;
        m_propgrid->Collapse(np);

    buildMarkerEnums();
    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addMarker(wxPGProperty* st ,int sno,const wxString& desc,wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_MARK_CIRCLE");
        cases.Add("wxSTC_MARK_ROUNDRECT");
        cases.Add("wxSTC_MARK_ARROW");
        cases.Add("wxSTC_MARK_SMALLRECT");
        cases.Add("wxSTC_MARK_SHORTARROW");
        cases.Add("wxSTC_MARK_EMPTY");
        cases.Add("wxSTC_MARK_ARROWDOWN");
        cases.Add("wxSTC_MARK_MINUS");
        cases.Add("wxSTC_MARK_PLUS");
        cases.Add("wxSTC_MARK_VLINE");
        cases.Add("wxSTC_MARK_LCORNER");
        cases.Add("wxSTC_MARK_TCORNER");
        cases.Add("wxSTC_MARK_BOXPLUS");
        cases.Add("wxSTC_MARK_BOXPLUSCONNECTED");
        cases.Add("wxSTC_MARK_BOXMINUS");
        cases.Add("wxSTC_MARK_BOXMINUSCONNECTED");
        cases.Add("wxSTC_MARK_LCORNERCURVE");
        cases.Add("wxSTC_MARK_TCORNERCURVE");
        cases.Add("wxSTC_MARK_CIRCLEPLUS");
        cases.Add("wxSTC_MARK_CIRCLEPLUSCONNECTED");
        cases.Add("wxSTC_MARK_CIRCLEMINUS");
        cases.Add("wxSTC_MARK_CIRCLEMINUSCONNECTED");
        cases.Add("wxSTC_MARK_BACKGROUND");
        cases.Add("wxSTC_MARK_DOTDOTDOT");
        cases.Add("wxSTC_MARK_ARROWS");
        //cases.Add("wxSTC_MARK_PIXMAP");
        cases.Add("wxSTC_MARK_FULLRECT");
        cases.Add("wxSTC_MARK_LEFTRECT");
        cases.Add("wxSTC_MARK_AVAILABLE");
        cases.Add("wxSTC_MARK_UNDERLINE");
        cases.Add("wxSTC_MARK_CHARACTER");
        //cases.Add("wxSTC_MARK_RGBAIMAGE");

        cases_values.Add(wxSTC_MARK_CIRCLE);
        cases_values.Add(wxSTC_MARK_ROUNDRECT);
        cases_values.Add(wxSTC_MARK_ARROW);
        cases_values.Add(wxSTC_MARK_SMALLRECT);
        cases_values.Add(wxSTC_MARK_SHORTARROW);
        cases_values.Add(wxSTC_MARK_EMPTY);
        cases_values.Add(wxSTC_MARK_ARROWDOWN);
        cases_values.Add(wxSTC_MARK_MINUS);
        cases_values.Add(wxSTC_MARK_PLUS);
        cases_values.Add(wxSTC_MARK_VLINE);
        cases_values.Add(wxSTC_MARK_LCORNER);
        cases_values.Add(wxSTC_MARK_TCORNER);
        cases_values.Add(wxSTC_MARK_BOXPLUS);
        cases_values.Add(wxSTC_MARK_BOXPLUSCONNECTED);
        cases_values.Add(wxSTC_MARK_BOXMINUS);
        cases_values.Add(wxSTC_MARK_BOXMINUSCONNECTED);
        cases_values.Add(wxSTC_MARK_LCORNERCURVE);
        cases_values.Add(wxSTC_MARK_TCORNERCURVE);
        cases_values.Add(wxSTC_MARK_CIRCLEPLUS);
        cases_values.Add(wxSTC_MARK_CIRCLEPLUSCONNECTED);
        cases_values.Add(wxSTC_MARK_CIRCLEMINUS);
        cases_values.Add(wxSTC_MARK_CIRCLEMINUSCONNECTED);
        cases_values.Add(wxSTC_MARK_BACKGROUND);
        cases_values.Add(wxSTC_MARK_DOTDOTDOT);
        cases_values.Add(wxSTC_MARK_ARROWS);
        //cases_values.Add(wxSTC_MARK_PIXMAP);
        cases_values.Add(wxSTC_MARK_FULLRECT);
        cases_values.Add(wxSTC_MARK_LEFTRECT);
        cases_values.Add(wxSTC_MARK_AVAILABLE);
        cases_values.Add(wxSTC_MARK_UNDERLINE);
        //cases_values.Add(wxSTC_MARK_RGBAIMAGE);
        cases_values.Add(wxSTC_MARK_CHARACTER);

        wxArrayString cases2;
        wxArrayInt cases2_values;
        cases2.push_back("arrow_1_disable.xpm");
        cases2.push_back("arrow_1_green.xpm");
        cases2.push_back("arrow_1_yellow.xpm");
        cases2.push_back("arrow_2_blue.xpm");
        cases2.push_back("arrow_2_blue__disable.xpm");
        cases2.push_back("arrow_2_green-disable.xpm");
        cases2.push_back("arrow_2_green.xpm");
        cases2.push_back("arrow_2_yellow.xpm");
        cases2.push_back("arrow_2_yellow_disable.xpm");
        cases2.push_back("arrow_golden.xpm");
        cases2.push_back("breakpoint-disabled.xpm");
        cases2.push_back("breakpoint.xpm");
        cases2.push_back("breakpoint_octogon-disable.xpm");
        cases2.push_back("breakpoint_octogon.xpm");
        cases2.push_back("breakpoint_octogon_grayed.xpm");
        cases2.push_back("breakpoint_rounded_blue.xpm");
        cases2.push_back("breakpoint_rounded_blue_disable.xpm");
        cases2.push_back("breakpoint_rounded_blue_inverted.xpm");
        cases2.push_back("breakpoint_rounded_gray.xpm");
        cases2.push_back("breakpoint_rounded_gray_disable.xpm");
        cases2.push_back("gem_blue.xpm");
        cases2.push_back("gem_red.xpm");
        cases2.push_back("marker_red_round-disabled.xpm");
        cases2.push_back("marker_red_round.xpm");
        cases2_values.push_back(reinterpret_cast<int>(arrow_1_disable_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow_1_green_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow_1_yellow_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow_2_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow_2_blue__disable_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow_2_green_disable_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow_2_green_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow_2_yellow_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow_2_yellow_disable_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow_golden_xpm));
        cases2_values.push_back(reinterpret_cast<int>(breakpoint_disabled_xpm));
        cases2_values.push_back(reinterpret_cast<int>(breakpoint_xpm));
        cases2_values.push_back(reinterpret_cast<int>(breakpoint_octogon_disable_xpm));
        cases2_values.push_back(reinterpret_cast<int>(breakpoint_octogon2_xpm));
        cases2_values.push_back(reinterpret_cast<int>(breakpoint_octogon_grayed_xpm));
        cases2_values.push_back(reinterpret_cast<int>(breakpoint_rounded_blue2_xpm));
        cases2_values.push_back(reinterpret_cast<int>(breakpoint_rounded_blue_disable_xpm));
        cases2_values.push_back(reinterpret_cast<int>(breakpoint_rounded_blue_inverted2_xpm));
        cases2_values.push_back(reinterpret_cast<int>(breakpoint_rounded_gray_xpm));
        cases2_values.push_back(reinterpret_cast<int>(breakpoint_rounded_gray_disable_xpm));
        cases2_values.push_back(reinterpret_cast<int>(bookmarkBluegem));
        cases2_values.push_back(reinterpret_cast<int>(bookmarkRedgem));
        cases2_values.push_back(reinterpret_cast<int>(marker_red_round_disabled_xpm));
        cases2_values.push_back(reinterpret_cast<int>(marker_red_round2_xpm));


    wxPGProperty* st2=addStringHeader(st,desc);
    st2->SetClientObject(new myStyleData(sno));

    //SCI_MARKERDEFINE(int markerNumber, int markerSymbols)
        wxPGProperty* np = addEnumProp(st2,"MarkerDefine","SCI_MARKERDEFINE",SCI_MARKERDEFINE,stc_def->GetMarkerSymbolDefined(sno),cases,cases_values);
        markerDefinitions[sno]=np;

        np=addDotDotDotStringProp(np, "character", "zzz", SCI_MARKERDEFINECHARACTER);
        markerDefineCharacter[sno]=np;
        m_propgrid->HideProperty(np, true);

    //SCI_MARKERDEFINEPIXMAP(int markerNumber, const char *xpm)
        np = m_propgrid->AppendIn(st2,new wxImageFileProperty("MarkerDefineBitmap","SCI_MARKERDEFINEPIXMAP"));
        np->SetClientData(reinterpret_cast<void *>(SCI_MARKERDEFINEPIXMAP));
        markerDefinePixmap[sno]=np;

    //SCI_RGBAIMAGESETWIDTH(int width)
        np=addIntProp(st2,"RGBAImageSetWidth","SCI_RGBAIMAGESETWIDTH",SCI_RGBAIMAGESETWIDTH,0,0,INT_MAX);
        markerRGBAWidth[sno]=np;

    //SCI_RGBAIMAGESETHEIGHT(int height)
        np=addIntProp(st2,"RGBAImageSetHeight","SCI_RGBAIMAGESETHEIGHT",SCI_RGBAIMAGESETHEIGHT,0,0,INT_MAX);
        markerRGBAHeight[sno]=np;

    //SCI_MARKERDEFINERGBAIMAGE(int markerNumber, const char *pixels)
        np=addDotDotDotStringProp(st2, "MarkerDefineRGBAImage", "SCI_MARKERDEFINERGBAIMAGE", SCI_MARKERDEFINERGBAIMAGE);
        markerDefineRGBAImage[sno]=np;

    //SCI_MARKERSYMBOLDEFINED(int markerNumber)
        addStringProp(st2, "GetMarkerSymbolDefined", "SCI_MARKERSYMBOLDEFINED", SCI_MARKERSYMBOLDEFINED,true,true);

    //SCI_MARKERSETFORE(int markerNumber, int colour)
        addColorProp(st2, "MarkerSetForeground", "SCI_MARKERSETFORE", SCI_MARKERSETFORE, *wxBLACK );

    //SCI_MARKERSETBACK(int markerNumber, int colour)
        addColorProp(st2, "MarkerSetBackground", "SCI_MARKERSETBACK", SCI_MARKERSETBACK, *wxWHITE );

    //SCI_MARKERSETBACKSELECTED(int markerNumber, int colour)
        addColorProp(st2, "MarkerSetBackgroundSelected", "SCI_MARKERSETBACKSELECTED", SCI_MARKERSETBACKSELECTED, *wxRED );

    //SCI_MARKERENABLEHIGHLIGHT(int enabled)
        np=addBoolProp(st2,"MarkerEnableHighlight","SCI_MARKERENABLEHIGHLIGHT",SCI_MARKERENABLEHIGHLIGHT,false);
        markerEnableHighlight[sno]=np;

    //SCI_MARKERSETALPHA(int markerNumber, int alpha)
        addIntProp(st2,"MarkerSetAlpha","SCI_MARKERSETALPHA",SCI_MARKERSETALPHA,256,0,256);

    np= addStringHeader(st2,"Alternative implementations");

    np= addEnumProp(np,"SCI_MARKERDEFINEPIXMAP","SCI_MARKERDEFINEPIXMAP",SCI_MARKERDEFINEPIXMAP2,-1,cases2,cases2_values);
    np->SetValueToUnspecified();
    markerDefinePixmap2[sno]=np;

    m_propgrid->Collapse(st2);
}

void propgridtest03Frame::addIndicators(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Indicators"));
    st->SetClientData(reinterpret_cast<void *>(SCI_INDICATORS));

    wxPGProperty* st2 = m_propgrid->AppendIn(st,new wxPropertyCategory("Lexer Indicators"));
    st2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));
    for(int i=0;i<wxSTC_INDIC_CONTAINER;i++)
    {
        addIndicator(st2 ,i,wxString::Format("indicator %d",i),stc_def);
    }
    m_propgrid->Collapse(st2);

    st2 = m_propgrid->AppendIn(st,new wxPropertyCategory("Container Indicators"));
    st2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));
    for(int i=wxSTC_INDIC_CONTAINER;i<=wxSTC_INDIC_MAX;i++)
    {
        if(i==wxSTC_INDIC_CONTAINER)
        {
            addIndicator(st2 ,i,wxString::Format("indicator %d (wxSTC_INDIC_CONTAINER)",i),stc_def);
        }
        else if(i==wxSTC_INDIC_MAX)
        {
            addIndicator(st2 ,i,wxString::Format("indicator %d (wxSTC_INDIC_MAX)",i),stc_def);
        }
        else
        {
            addIndicator( st2 ,i,wxString::Format("indicator %d",i),stc_def );
        }

    }
    m_propgrid->Collapse(st2);

    st2 = m_propgrid->AppendIn(st,new wxPropertyCategory("Modern Indicators"));
    st2->SetClientData(reinterpret_cast<void *>(SCI_MODERNINDICATORS));

    //SCI_SETINDICATORCURRENT(int indicator)
        addIntProp(st2,"SetIndicatorCurrent","SCI_SETINDICATORCURRENT",SCI_SETINDICATORCURRENT,stc_def->GetIndicatorCurrent(),0,wxSTC_INDIC_MAX);

    //SCI_GETINDICATORCURRENT
        addStringProp(st2, "GetIndicatorCurrent", "SCI_GETINDICATORCURRENT", SCI_GETINDICATORCURRENT,true,true);

    //SCI_SETINDICATORVALUE(int value)
        addIntProp(st2,"SetIndicatorValue","SCI_SETINDICATORVALUE",SCI_SETINDICATORVALUE,stc_def->GetIndicatorValue(),INT_MIN,INT_MAX);

    //SCI_GETINDICATORVALUE
        addStringProp(st2, "GetIndicatorValue", "SCI_GETINDICATORVALUE", SCI_GETINDICATORVALUE,true,true);

    //SCI_INDICATORFILLRANGE(int position, int fillLength)
        wxPGProperty* np = addStringProp(st2, "IndicatorFillRange", "SCI_INDICATORFILLRANGE", SCI_INDICATORFILLRANGE,false,true);
        addIntParam(np,"position",0,0,INT_MAX);
        addIntParam(np,"fillLength",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_INDICATORCLEARRANGE(int position, int clearLength)
        np = addStringProp(st2, "IndicatorClearRange", "SCI_INDICATORCLEARRANGE", SCI_INDICATORCLEARRANGE,false,true);
        addIntParam(np,"position",0,0,INT_MAX);
        addIntParam(np,"clearLength",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_INDICATORALLONFOR(int position)
        np = addLongStringProp(st2, "IndicatorAllOnFor", "SCI_INDICATORALLONFOR", SCI_INDICATORALLONFOR,true,true);
        addIntParam(np,"position",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_INDICATORVALUEAT(int indicator, int position)
        np = addStringProp(st2, "IndicatorValueAt", "SCI_INDICATORVALUEAT", SCI_INDICATORVALUEAT,true,true);
        addIntParam(np,"indicator",0,0,wxSTC_INDIC_MAX);
        addIntParam(np,"position",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_INDICATORSTART(int indicator, int position)
        np = addStringProp(st2, "IndicatorStart", "SCI_INDICATORSTART", SCI_INDICATORSTART,true,true);
        addIntParam(np,"indicator",0,0,wxSTC_INDIC_MAX);
        addIntParam(np,"position",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_INDICATOREND(int indicator, int position)
        np = addStringProp(st2, "IndicatorEnd", "SCI_INDICATOREND", SCI_INDICATOREND,true,true);
        addIntParam(np,"indicator",0,0,wxSTC_INDIC_MAX);
        addIntParam(np,"position",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //OS X Find Indicator
        st2 = m_propgrid->AppendIn(st, new wxPropertyCategory("OS X Find Indicator"));
        st2->SetClientData(reinterpret_cast<void *>(SCI_OSXFINDINDICATOR));

    //SCI_FINDINDICATORSHOW(int start, int end)
        np = addStringProp(st2, "SCI_FINDINDICATORSHOW", "SCI_FINDINDICATORSHOW", SCI_FINDINDICATORSHOW,false,true);
        addIntParam(np,"start",0,0,INT_MAX);
        addIntParam(np,"end",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_FINDINDICATORFLASH(int start, int end)
        np = addStringProp(st2, "SCI_FINDINDICATORFLASH", "SCI_FINDINDICATORFLASH", SCI_FINDINDICATORFLASH,false,true);
        addIntParam(np,"start",0,0,INT_MAX);
        addIntParam(np,"end",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_FINDINDICATORHIDE
        np = addStringProp(st2, "SCI_FINDINDICATORHIDE", "SCI_FINDINDICATORHIDE", SCI_FINDINDICATORHIDE,false,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addIndicator(wxPGProperty* st ,int sno,const wxString& desc,wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_INDIC_PLAIN");
        cases.Add("wxSTC_INDIC_SQUIGGLE");
        cases.Add("wxSTC_INDIC_TT");
        cases.Add("wxSTC_INDIC_DIAGONAL");
        cases.Add("wxSTC_INDIC_STRIKE");
        cases.Add("wxSTC_INDIC_HIDDEN");
        cases.Add("wxSTC_INDIC_BOX");
        cases.Add("wxSTC_INDIC_ROUNDBOX");
        cases.Add("wxSTC_INDIC_STRAIGHTBOX");
        cases.Add("wxSTC_INDIC_DASH");
        cases.Add("wxSTC_INDIC_DOTS");
        cases.Add("wxSTC_INDIC_SQUIGGLELOW");
        cases.Add("wxSTC_INDIC_DOTBOX");

        cases_values.Add(wxSTC_INDIC_PLAIN);
        cases_values.Add(wxSTC_INDIC_SQUIGGLE);
        cases_values.Add(wxSTC_INDIC_TT);
        cases_values.Add(wxSTC_INDIC_DIAGONAL);
        cases_values.Add(wxSTC_INDIC_STRIKE);
        cases_values.Add(wxSTC_INDIC_HIDDEN);
        cases_values.Add(wxSTC_INDIC_BOX);
        cases_values.Add(wxSTC_INDIC_ROUNDBOX);
        cases_values.Add(wxSTC_INDIC_STRAIGHTBOX);
        cases_values.Add(wxSTC_INDIC_DASH);
        cases_values.Add(wxSTC_INDIC_DOTS);
        cases_values.Add(wxSTC_INDIC_SQUIGGLELOW);
        cases_values.Add(wxSTC_INDIC_DOTBOX);

    wxPGProperty* st2 = addStringProp(st, desc, "zzz", SCI_PARAM,false,true);
    st2->SetClientObject( new myStyleData(sno) );

    //SCI_INDICSETSTYLE(int indicatorNumber, int indicatorStyle)
        addEnumProp(st2,"IndicatorSetStyle","SCI_INDICSETSTYLE",SCI_INDICSETSTYLE,stc_def->IndicatorGetStyle(sno),cases,cases_values);

    //SCI_INDICGETSTYLE(int indicatorNumber)
        addStringProp(st2, "IndicatorGetStyle", "SCI_INDICGETSTYLE", SCI_INDICGETSTYLE,true,true);

    //SCI_INDICSETFORE(int indicatorNumber, int colour)
        addColorProp(st2, "IndicatorSetForeground", "SCI_INDICSETFORE", SCI_INDICSETFORE, stc_def->IndicatorGetForeground(sno) );

    //SCI_INDICGETFORE(int indicatorNumber)
        addColorStringProp(st2, "IndicatorGetForeground", "SCI_INDICGETFORE", SCI_INDICGETFORE);

    //SCI_INDICSETALPHA(int indicatorNumber, int alpha)
        addIntProp(st2,"IndicatorSetAlpha","SCI_INDICSETALPHA",SCI_INDICSETALPHA,stc_def->IndicatorGetAlpha(sno),0,256);

    //SCI_INDICGETALPHA(int indicatorNumber)
        addStringProp(st2, "IndicatorGetAlpha", "SCI_INDICGETALPHA", SCI_INDICGETALPHA,true,true);

    //SCI_INDICSETOUTLINEALPHA(int indicatorNumber, int alpha)
        addIntProp(st2,"IndicatorSetOutlineAlpha","SCI_INDICSETOUTLINEALPHA",SCI_INDICSETOUTLINEALPHA,stc_def->IndicatorGetOutlineAlpha(sno),0,256);

    //SCI_INDICGETOUTLINEALPHA(int indicatorNumber)
        addStringProp(st2, "IndicatorGetOutlineAlpha", "SCI_INDICGETOUTLINEALPHA", SCI_INDICGETOUTLINEALPHA,true,true);

    //SCI_INDICSETUNDER(int indicatorNumber, bool under)
        addBoolProp(st2,"IndicatorSetUnder","SCI_INDICSETUNDER",SCI_INDICSETUNDER, stc_def->IndicatorGetUnder(sno) );

    //SCI_INDICGETUNDER(int indicatorNumber)
        addStringProp(st2, "IndicatorGetUnder", "SCI_INDICGETUNDER", SCI_INDICGETUNDER,true,true);

    m_propgrid->Collapse(st2);
}


void propgridtest03Frame::addAutocompletion(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_CASEINSENSITIVEBEHAVIOUR_RESPECTCASE");
        cases.Add("wxSTC_CASEINSENSITIVEBEHAVIOUR_IGNORECASE");

        cases_values.Add(wxSTC_CASEINSENSITIVEBEHAVIOUR_RESPECTCASE);
        cases_values.Add(wxSTC_CASEINSENSITIVEBEHAVIOUR_IGNORECASE);

        wxArrayString cases2;
        wxArrayInt cases2_values;
        cases2.push_back("arrow.xpm");
        cases2.push_back("arrow2.xpm");
        cases2.push_back("arrow2-blue.xpm");
        cases2.push_back("arrow2-red.xpm");
        cases2.push_back("arrow-blue.xpm");
        cases2.push_back("arrow-red.xpm");
        cases2.push_back("box.xpm");
        cases2.push_back("box-blue.xpm");
        cases2.push_back("box-red.xpm");
        cases2.push_back("child.xpm");
        cases2.push_back("cross.xpm");
        cases2.push_back("cross2.xpm");
        cases2.push_back("dot-black.xpm");
        cases2.push_back("dot-black-locked.xpm");
        cases2.push_back("dot-blue.xpm");
        cases2.push_back("dotl-blue-locked.xpm");
        cases2.push_back("dot-orange.xpm");
        cases2.push_back("dot-orange-crossed.xpm");
        cases2.push_back("dot-orange-wlock.xpm");
        cases2.push_back("dot-orange-wolock.xpm");
        cases2.push_back("dot-orange-wolock2.xpm");
        cases2.push_back("dot-red.xpm");
        cases2.push_back("dot-red-locked.xpm");
        cases2.push_back("F-unction.xpm");
        cases2.push_back("F-unction-blue.xpm");
        cases2.push_back("inherit.xpm");
        cases2.push_back("inherit2.xpm");
        cases2.push_back("inherit2-blue.xpm");
        cases2.push_back("inner-square.xpm");
        cases2.push_back("inner-square-black.xpm");
        cases2.push_back("inner-square-blue.xpm");
        cases2.push_back("key.xpm");
        cases2.push_back("key-blue.xpm");
        cases2.push_back("key-red.xpm");
        cases2.push_back("lock-closed.xpm");
        cases2.push_back("lock-closed-blue.xpm");
        cases2.push_back("lock-opened.xpm");
        cases2.push_back("lock-opened-blue.xpm");
        cases2.push_back("member.xpm");
        cases2.push_back("member-blue.xpm");
        cases2.push_back("noidea.xpm");
        cases2.push_back("question.xpm");
        cases2.push_back("recurse-blue.xpm");
        cases2.push_back("round.xpm");
        cases2.push_back("round-blue.xpm");
        cases2.push_back("round-red.xpm");
        cases2.push_back("semaphore.xpm");
        cases2.push_back("shuttle.xpm");
        cases2.push_back("square-blue.xpm");
        cases2.push_back("square-red.xpm");
        cases2.push_back("warn.xpm");
        cases2.push_back("whirl.xpm");
        cases2.push_back("whirl-blue.xpm");


        cases2_values.push_back(reinterpret_cast<int>(arrow_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow2_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow2_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow2_red_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(arrow_red_xpm));
        cases2_values.push_back(reinterpret_cast<int>(box_xpm));
        cases2_values.push_back(reinterpret_cast<int>(box_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(box_red_xpm));
        cases2_values.push_back(reinterpret_cast<int>(child_xpm));
        cases2_values.push_back(reinterpret_cast<int>(cross_xpm));
        cases2_values.push_back(reinterpret_cast<int>(cross2_xpm));
        cases2_values.push_back(reinterpret_cast<int>(dot_black_xpm));
        cases2_values.push_back(reinterpret_cast<int>(dot_black_locked_xpm));
        cases2_values.push_back(reinterpret_cast<int>(dot_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(dotl_blue_locked_xpm));
        cases2_values.push_back(reinterpret_cast<int>(dot_orange_xpm));
        cases2_values.push_back(reinterpret_cast<int>(dot_orange_crossed_xpm));
        cases2_values.push_back(reinterpret_cast<int>(dot_orange_wlock_xpm));
        cases2_values.push_back(reinterpret_cast<int>(dot_orange_wolock_xpm));
        cases2_values.push_back(reinterpret_cast<int>(dot_orange_wolock2_xpm));
        cases2_values.push_back(reinterpret_cast<int>(dot_red_xpm));
        cases2_values.push_back(reinterpret_cast<int>(dot_red_locked_xpm));
        cases2_values.push_back(reinterpret_cast<int>(F_unction_xpm));
        cases2_values.push_back(reinterpret_cast<int>(F_unction_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(inherit_xpm));
        cases2_values.push_back(reinterpret_cast<int>(inherit2_xpm));
        cases2_values.push_back(reinterpret_cast<int>(inherit2_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(inner_square_xpm));
        cases2_values.push_back(reinterpret_cast<int>(inner_square_black_xpm));
        cases2_values.push_back(reinterpret_cast<int>(inner_square_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(key_xpm));
        cases2_values.push_back(reinterpret_cast<int>(key_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(key_red_xpm));
        cases2_values.push_back(reinterpret_cast<int>(lock_closed_xpm));
        cases2_values.push_back(reinterpret_cast<int>(lock_closed_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(lock_opened_xpm));
        cases2_values.push_back(reinterpret_cast<int>(lock_opened_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(member_xpm));
        cases2_values.push_back(reinterpret_cast<int>(member_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(noidea_xpm));
        cases2_values.push_back(reinterpret_cast<int>(question_xpm));
        cases2_values.push_back(reinterpret_cast<int>(recurse_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(round_xpm));
        cases2_values.push_back(reinterpret_cast<int>(round_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(round_red_xpm));
        cases2_values.push_back(reinterpret_cast<int>(semaphore_xpm));
        cases2_values.push_back(reinterpret_cast<int>(shuttle_xpm));
        cases2_values.push_back(reinterpret_cast<int>(square_blue_xpm));
        cases2_values.push_back(reinterpret_cast<int>(square_red_xpm));
        cases2_values.push_back(reinterpret_cast<int>(warn_xpm));
        cases2_values.push_back(reinterpret_cast<int>(whirl_xpm));
        cases2_values.push_back(reinterpret_cast<int>(whirl_blue_xpm));

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Autocompletion"));
    st->SetClientData(reinterpret_cast<void *>(SCI_AUTOCOMPLETION));

    //SCI_AUTOCSHOW(int lenEntered, const char *list)
        wxPGProperty* np = addStringProp(st, "AutoCompShow", "SCI_AUTOCSHOW", SCI_AUTOCSHOW,false,true);
        addIntParam(np,"lenEntered",0,0,INT_MAX);
        addStringParam(np, "itemList",true);
        m_propgrid->Collapse(np);

    //SCI_AUTOCCANCEL
        addStringProp(st, "AutoCompCancel", "SCI_AUTOCCANCEL", SCI_AUTOCCANCEL,false,true);

    //SCI_AUTOCACTIVE
        addStringProp(st, "AutoCompActive", "SCI_AUTOCACTIVE", SCI_AUTOCACTIVE,true,true);

    //SCI_AUTOCPOSSTART
        addStringProp(st, "AutoCompPosStart", "SCI_AUTOCPOSSTART", SCI_AUTOCPOSSTART,true,true);

    //SCI_AUTOCCOMPLETE
        addStringProp(st, "AutoCompComplete", "SCI_AUTOCCOMPLETE", SCI_AUTOCCOMPLETE,false,true);

    //SCI_AUTOCSTOPS(<unused>, const char *chars)
        np = addStringProp(st, "AutoCompStops", "SCI_AUTOCSTOPS", SCI_AUTOCSTOPS,false,true);
        addStringParam(np, "characterSet",true);
        m_propgrid->Collapse(np);

    //SCI_AUTOCSETSEPARATOR(char separator)
        np=addDotDotDotStringProp(st, "AutoCompSetSeparator", "SCI_AUTOCSETSEPARATOR", SCI_AUTOCSETSEPARATOR);
        clearables.push_back(np);

    //SCI_AUTOCGETSEPARATOR
        addStringProp(st, "AutoCompGetSeparator", "SCI_AUTOCGETSEPARATOR", SCI_AUTOCGETSEPARATOR,true,true);

    //SCI_AUTOCSELECT(<unused>, const char *select)
        np = addStringProp(st, "AutoCompSelect", "SCI_AUTOCSELECT", SCI_AUTOCSELECT,false,true);
        addStringParam(np, "text",true);
        m_propgrid->Collapse(np);

    //SCI_AUTOCGETCURRENT
        addStringProp(st, "AutoCompGetCurrent", "SCI_AUTOCGETCURRENT", SCI_AUTOCGETCURRENT,true,true);

    //SCI_AUTOCGETCURRENTTEXT(<unused>, char *text)
        addStringProp(st, "SCI_AUTOCGETCURRENTTEXT", "SCI_AUTOCGETCURRENTTEXT", SCI_AUTOCGETCURRENTTEXT,true,true);

    //SCI_AUTOCSETCANCELATSTART(bool cancel)
        addBoolProp(st,"AutoCompSetCancelAtStart","SCI_AUTOCSETCANCELATSTART",SCI_AUTOCSETCANCELATSTART,stc_def->AutoCompGetCancelAtStart());

    //SCI_AUTOCGETCANCELATSTART
        addStringProp(st, "AutoCompGetCancelAtStart", "SCI_AUTOCGETCANCELATSTART", SCI_AUTOCGETCANCELATSTART,true,true);

    //SCI_AUTOCSETFILLUPS(<unused>, const char *chars)
        np = m_propgrid->AppendIn(st,new wxStringProperty("AutoCompSetFillUps","SCI_AUTOCSETFILLUPS"));
        np->SetClientData(reinterpret_cast<void *>(SCI_AUTOCSETFILLUPS));

    //SCI_AUTOCSETCHOOSESINGLE(bool chooseSingle)
        addBoolProp(st,"AutoCompSetChooseSingle","SCI_AUTOCSETCHOOSESINGLE",SCI_AUTOCSETCHOOSESINGLE,stc_def->AutoCompGetChooseSingle());

    //SCI_AUTOCGETCHOOSESINGLE
        addStringProp(st, "AutoCompGetChooseSingle", "SCI_AUTOCGETCHOOSESINGLE", SCI_AUTOCGETCHOOSESINGLE,true,true);

    //SCI_AUTOCSETIGNORECASE(bool ignoreCase)
        addBoolProp(st,"AutoCompSetIgnoreCase","SCI_AUTOCSETIGNORECASE",SCI_AUTOCSETIGNORECASE,stc_def->AutoCompGetIgnoreCase());

    //SCI_AUTOCGETIGNORECASE
        addStringProp(st, "AutoCompGetIgnoreCase", "SCI_AUTOCGETIGNORECASE", SCI_AUTOCGETIGNORECASE,true,true);

    //SCI_AUTOCSETCASEINSENSITIVEBEHAVIOUR(int behaviour)
        addEnumProp(st,"AutoCompSetCaseInsensitiveBehaviour","SCI_AUTOCSETCASEINSENSITIVEBEHAVIOUR",SCI_AUTOCSETCASEINSENSITIVEBEHAVIOUR,stc_def->AutoCompGetCaseInsensitiveBehaviour(),cases,cases_values);

    //SCI_AUTOCGETCASEINSENSITIVEBEHAVIOUR
        addStringProp(st, "AutoCompGetCaseInsensitiveBehaviour", "SCI_AUTOCGETCASEINSENSITIVEBEHAVIOUR", SCI_AUTOCGETCASEINSENSITIVEBEHAVIOUR,true,true);

    //SCI_AUTOCSETAUTOHIDE(bool autoHide)
        addBoolProp(st,"AutoCompSetAutoHide","SCI_AUTOCSETAUTOHIDE",SCI_AUTOCSETAUTOHIDE,stc_def->AutoCompGetAutoHide());

    //SCI_AUTOCGETAUTOHIDE
        addStringProp(st, "AutoCompGetAutoHide", "SCI_AUTOCGETAUTOHIDE", SCI_AUTOCGETAUTOHIDE,true,true);

    //SCI_AUTOCSETDROPRESTOFWORD(bool dropRestOfWord)
        addBoolProp(st,"AutoCompSetDropRestOfWord","SCI_AUTOCSETDROPRESTOFWORD",SCI_AUTOCSETDROPRESTOFWORD,stc_def->AutoCompGetDropRestOfWord());

    //SCI_AUTOCGETDROPRESTOFWORD
        addStringProp(st, "AutoCompGetDropRestOfWord", "SCI_AUTOCGETDROPRESTOFWORD", SCI_AUTOCGETDROPRESTOFWORD,true,true);

    //SCI_REGISTERIMAGE(int type, const char *xpmData)
        np = addStringProp(st, "RegisterImage", "SCI_REGISTERIMAGE", SCI_REGISTERIMAGE,false,true);
        addIntParam(np,"type",0,0,INT_MAX);
        wxPGProperty* np2 = m_propgrid->AppendIn(np,new wxImageFileProperty("bmp","zzz"));
        np2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));
        m_propgrid->Collapse(np);

    //SCI_REGISTERRGBAIMAGE(int type, const char *pixels)
        np = addDotDotDotStringProp(st, "RegisterRGBAImage", "SCI_REGISTERRGBAIMAGE", SCI_REGISTERRGBAIMAGE);
        addIntParam(np,"type",0,0,INT_MAX);
        addIntParam(np,"width",12,1,INT_MAX);
        addIntParam(np,"height",12,1,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_CLEARREGISTEREDIMAGES
        addStringProp(st, "ClearRegisteredImages", "SCI_CLEARREGISTEREDIMAGES", SCI_CLEARREGISTEREDIMAGES,false,true);

    //SCI_AUTOCSETTYPESEPARATOR(char separatorCharacter)
        np = addDotDotDotStringProp(st, "AutoCompSetTypeSeparator", "SCI_AUTOCSETTYPESEPARATOR", SCI_AUTOCSETTYPESEPARATOR);
        clearables.push_back(np);

    //SCI_AUTOCGETTYPESEPARATOR
        addStringProp(st, "AutoCompGetTypeSeparator", "SCI_AUTOCGETTYPESEPARATOR", SCI_AUTOCGETTYPESEPARATOR,true,true);

    //SCI_AUTOCSETMAXHEIGHT(int rowCount)
        addIntProp(st,"AutoCompSetMaxHeight","SCI_AUTOCSETMAXHEIGHT",SCI_AUTOCSETMAXHEIGHT,stc_def->AutoCompGetMaxHeight(),0,INT_MAX);

    //SCI_AUTOCGETMAXHEIGHT
        addStringProp(st, "AutoCompGetMaxHeight", "SCI_AUTOCGETMAXHEIGHT", SCI_AUTOCGETMAXHEIGHT,true,true);

    //SCI_AUTOCSETMAXWIDTH(int characterCount)
        addIntProp(st,"AutoCompSetMaxWidth","SCI_AUTOCSETMAXWIDTH",SCI_AUTOCSETMAXWIDTH,stc_def->AutoCompGetMaxWidth(),0,INT_MAX);

    //SCI_AUTOCGETMAXWIDTH
        addStringProp(st, "AutoCompGetMaxWidth", "SCI_AUTOCGETMAXWIDTH", SCI_AUTOCGETMAXWIDTH,true,true);

    //add a new category for an alternate implementations of SCI_REGISTERIMAGE
    wxPGProperty* st2 = m_propgrid->AppendIn(st,new wxPropertyCategory("Alternative implementations","Alternative implementations2"));
    st2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));

        np = addStringProp(st2, "SCI_REGISTERIMAGE", "SCI_REGISTERIMAGE", SCI_REGISTERIMAGE2,false,true);
        addIntParam(np,"type",0,0,INT_MAX);
        addEnumParam(np,"xpmData", cases2_values[0],cases2,cases2_values);
        m_propgrid->Collapse(np);

    //add a new category where registered images will be tracked but hide it until
    //at least one image is registered
        st2 = m_propgrid->AppendIn(st,new wxPropertyCategory("Registered images"));
        st2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));
        registerdACImageHeader=st2;
        m_propgrid->HideProperty(st2, true);

    m_propgrid->Collapse(st);
}


void propgridtest03Frame::addUserLists(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("User lists"));
    st->SetClientData(reinterpret_cast<void *>(SCI_USERLISTS));

    //SCI_USERLISTSHOW(int listType, const char *list)
        wxPGProperty* np = addStringProp(st, "UserListShow", "SCI_USERLISTSHOW", SCI_USERLISTSHOW,false,true);
        addIntParam(np,"listType",1,1,INT_MAX);
        addStringParam(np, "itemList",true);
        m_propgrid->Collapse(np);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addCallTips(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Call tips"));
    st->SetClientData(reinterpret_cast<void *>(SCI_CALLTIPS));

    //SCI_CALLTIPSHOW(int posStart, const char *definition)
        wxPGProperty* np = addStringProp(st, "CallTipShow", "SCI_CALLTIPSHOW", SCI_CALLTIPSHOW,false,true);
        addIntParam(np,"pos",0,0,INT_MAX);
        addStringParam(np, "definition",true);
        m_propgrid->Collapse(np);

    //SCI_CALLTIPCANCEL
        addStringProp(st, "CallTipCancel", "SCI_CALLTIPCANCEL", SCI_CALLTIPCANCEL,false,true);

    //SCI_CALLTIPACTIVE
        addStringProp(st, "CallTipActive", "SCI_CALLTIPACTIVE", SCI_CALLTIPACTIVE,true,true);

    //SCI_CALLTIPPOSSTART
        addStringProp(st, "CallTipPosAtStart", "SCI_CALLTIPPOSSTART", SCI_CALLTIPPOSSTART,true,true);

    //SCI_CALLTIPSETHLT(int highlightStart, int highlightEnd)
        np = addStringProp(st, "CallTipSetHighlight", "SCI_CALLTIPSETHLT", SCI_CALLTIPSETHLT,false,true);
        addIntParam(np,"start",0,0,INT_MAX);
        addIntParam(np,"end",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_CALLTIPSETBACK(int colour)
        addColorProp(st, "CallTipSetBackground", "SCI_CALLTIPSETBACK", SCI_CALLTIPSETBACK, *wxWHITE );

    //SCI_CALLTIPSETFORE(int colour)
        addColorProp(st, "CallTipSetForeground", "SCI_CALLTIPSETFORE", SCI_CALLTIPSETFORE, wxColor(128,128,128) );

    //SCI_CALLTIPSETFOREHLT(int colour)
        addColorProp(st, "CallTipSetForegroundHighlight", "SCI_CALLTIPSETFOREHLT", SCI_CALLTIPSETFOREHLT, wxColor(0,0,128) );

    //SCI_CALLTIPUSESTYLE(int tabsize)
        np = addStringProp(st, "CallTipUseStyle", "SCI_CALLTIPUSESTYLE", SCI_CALLTIPUSESTYLE,true,true);
        addIntParam(np,"tabSize",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_CALLTIPSETPOSITION(bool above)
        addBoolProp(st,"CallTipSetPosition","SCI_CALLTIPSETPOSITION",SCI_CALLTIPSETPOSITION,false);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addKeyboardCommands(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Keyboard commands"));
    st->SetClientData(reinterpret_cast<void *>(SCI_KEYBOARDCOMMANDS));

    //SCI_LINEDOWN
        addStringProp(st, "LineDown","SCI_LINEDOWN",SCI_LINEDOWN,false,true);

    //SCI_LINEDOWNEXTEND
        addStringProp(st, "LineDownExtend","SCI_LINEDOWNEXTEND",SCI_LINEDOWNEXTEND,false,true);

    //SCI_LINEDOWNRECTEXTEND
        addStringProp(st, "LineDownRectExtend","SCI_LINEDOWNRECTEXTEND",SCI_LINEDOWNRECTEXTEND,false,true);

    //SCI_LINESCROLLDOWN
        addStringProp(st, "LineScrollDown","SCI_LINESCROLLDOWN",SCI_LINESCROLLDOWN,false,true);

    //SCI_LINEUP
        addStringProp(st, "LineUp","SCI_LINEUP",SCI_LINEUP,false,true);

    //SCI_LINEUPEXTEND
        addStringProp(st, "LineUpExtend","SCI_LINEUPEXTEND",SCI_LINEUPEXTEND,false,true);

    //SCI_LINEUPRECTEXTEND
        addStringProp(st, "LineUpRectExtend","SCI_LINEUPRECTEXTEND",SCI_LINEUPRECTEXTEND,false,true);

    //SCI_LINESCROLLUP
        addStringProp(st, "LineScrollUp","SCI_LINESCROLLUP",SCI_LINESCROLLUP,false,true);

    //SCI_PARADOWN
        addStringProp(st, "ParaDown","SCI_PARADOWN",SCI_PARADOWN,false,true);

    //SCI_PARADOWNEXTEND
        addStringProp(st, "ParaDownExtend","SCI_PARADOWNEXTEND",SCI_PARADOWNEXTEND,false,true);

    //SCI_PARAUP
        addStringProp(st, "ParaUp","SCI_PARAUP",SCI_PARAUP,false,true);

    //SCI_PARAUPEXTEND
        addStringProp(st, "ParaUpExtend","SCI_PARAUPEXTEND",SCI_PARAUPEXTEND,false,true);

    //SCI_CHARLEFT
        addStringProp(st, "CharLeft","SCI_CHARLEFT",SCI_CHARLEFT,false,true);

    //SCI_CHARLEFTEXTEND
        addStringProp(st, "CharLeftExtend","SCI_CHARLEFTEXTEND",SCI_CHARLEFTEXTEND,false,true);

    //SCI_CHARLEFTRECTEXTEND
        addStringProp(st, "CharLeftRectExtend","SCI_CHARLEFTRECTEXTEND",SCI_CHARLEFTRECTEXTEND,false,true);

    //SCI_CHARRIGHT
        addStringProp(st, "CharRight","SCI_CHARRIGHT",SCI_CHARRIGHT,false,true);

    //SCI_CHARRIGHTEXTEND
        addStringProp(st, "CharRightExtend","SCI_CHARRIGHTEXTEND",SCI_CHARRIGHTEXTEND,false,true);

    //SCI_CHARRIGHTRECTEXTEND
        addStringProp(st, "CharRightRectExtend","SCI_CHARRIGHTRECTEXTEND",SCI_CHARRIGHTRECTEXTEND,false,true);

    //SCI_WORDLEFT
        addStringProp(st, "WordLeft","SCI_WORDLEFT",SCI_WORDLEFT,false,true);

    //SCI_WORDLEFTEXTEND
        addStringProp(st, "WordLeftExtend","SCI_WORDLEFTEXTEND",SCI_WORDLEFTEXTEND,false,true);

    //SCI_WORDRIGHT
        addStringProp(st, "WordRight","SCI_WORDRIGHT",SCI_WORDRIGHT,false,true);

    //SCI_WORDRIGHTEXTEND
        addStringProp(st, "WordRightExtend","SCI_WORDRIGHTEXTEND",SCI_WORDRIGHTEXTEND,false,true);

    //SCI_WORDLEFTEND
        addStringProp(st, "WordLeftEnd","SCI_WORDLEFTEND",SCI_WORDLEFTEND,false,true);

    //SCI_WORDLEFTENDEXTEND
        addStringProp(st, "WordLeftEndExtend","SCI_WORDLEFTENDEXTEND",SCI_WORDLEFTENDEXTEND,false,true);

    //SCI_WORDRIGHTEND
        addStringProp(st, "WordRightEnd","SCI_WORDRIGHTEND",SCI_WORDRIGHTEND,false,true);

    //SCI_WORDRIGHTENDEXTEND
        addStringProp(st, "WordRightEndExtend","SCI_WORDRIGHTENDEXTEND",SCI_WORDRIGHTENDEXTEND,false,true);

    //SCI_WORDPARTLEFT
        addStringProp(st, "WordPartLeft","SCI_WORDPARTLEFT",SCI_WORDPARTLEFT,false,true);

    //SCI_WORDPARTLEFTEXTEND
        addStringProp(st, "WordPartLeftExtend","SCI_WORDPARTLEFTEXTEND",SCI_WORDPARTLEFTEXTEND,false,true);

    //SCI_WORDPARTRIGHT
        addStringProp(st, "WordPartRight","SCI_WORDPARTRIGHT",SCI_WORDPARTRIGHT,false,true);

    //SCI_WORDPARTRIGHTEXTEND
        addStringProp(st, "WordPartRightExtend","SCI_WORDPARTRIGHTEXTEND",SCI_WORDPARTRIGHTEXTEND,false,true);

    //SCI_HOME
        addStringProp(st, "Home","SCI_HOME",SCI_HOME,false,true);

    //SCI_HOMEEXTEND
        addStringProp(st, "HomeExtend","SCI_HOMEEXTEND",SCI_HOMEEXTEND,false,true);

    //SCI_HOMERECTEXTEND
        addStringProp(st, "HomeRectExtend","SCI_HOMERECTEXTEND",SCI_HOMERECTEXTEND,false,true);

    //SCI_HOMEDISPLAY
        addStringProp(st, "HomeDisplay","SCI_HOMEDISPLAY",SCI_HOMEDISPLAY,false,true);

    //SCI_HOMEDISPLAYEXTEND
        addStringProp(st, "HomeDisplayExtend","SCI_HOMEDISPLAYEXTEND",SCI_HOMEDISPLAYEXTEND,false,true);

    //SCI_HOMEWRAP
        addStringProp(st, "HomeWrap","SCI_HOMEWRAP",SCI_HOMEWRAP,false,true);

    //SCI_HOMEWRAPEXTEND
        addStringProp(st, "HomeWrapExtend","SCI_HOMEWRAPEXTEND",SCI_HOMEWRAPEXTEND,false,true);

    //SCI_VCHOME
        addStringProp(st, "VCHome","SCI_VCHOME",SCI_VCHOME,false,true);

    //SCI_VCHOMEEXTEND
        addStringProp(st, "VCHomeExtend","SCI_VCHOMEEXTEND",SCI_VCHOMEEXTEND,false,true);

    //SCI_VCHOMERECTEXTEND
        addStringProp(st, "VCHomeRectExtend","SCI_VCHOMERECTEXTEND",SCI_VCHOMERECTEXTEND,false,true);

    //SCI_VCHOMEWRAP
        addStringProp(st, "VCHomeWrap","SCI_VCHOMEWRAP",SCI_VCHOMEWRAP,false,true);

    //SCI_VCHOMEWRAPEXTEND
        addStringProp(st, "VCHomeWrapExtend","SCI_VCHOMEWRAPEXTEND",SCI_VCHOMEWRAPEXTEND,false,true);

    //SCI_LINEEND
        addStringProp(st, "LineEnd","SCI_LINEEND",SCI_LINEEND,false,true);

    //SCI_LINEENDEXTEND
        addStringProp(st, "LineEndExtend","SCI_LINEENDEXTEND",SCI_LINEENDEXTEND,false,true);

    //SCI_LINEENDRECTEXTEND
        addStringProp(st, "LineEndRectExtend","SCI_LINEENDRECTEXTEND",SCI_LINEENDRECTEXTEND,false,true);

    //SCI_LINEENDDISPLAY
        addStringProp(st, "LineEndDisplay","SCI_LINEENDDISPLAY",SCI_LINEENDDISPLAY,false,true);

    //SCI_LINEENDDISPLAYEXTEND
        addStringProp(st, "LineEndDisplayExtend","SCI_LINEENDDISPLAYEXTEND",SCI_LINEENDDISPLAYEXTEND,false,true);

    //SCI_LINEENDWRAP
        addStringProp(st, "LineEndWrap","SCI_LINEENDWRAP",SCI_LINEENDWRAP,false,true);

    //SCI_LINEENDWRAPEXTEND
        addStringProp(st, "LineEndWrapExtend","SCI_LINEENDWRAPEXTEND",SCI_LINEENDWRAPEXTEND,false,true);

    //SCI_DOCUMENTSTART
        addStringProp(st, "DocumentStart","SCI_DOCUMENTSTART",SCI_DOCUMENTSTART,false,true);

    //SCI_DOCUMENTSTARTEXTEND
        addStringProp(st, "DocumentStartExtend","SCI_DOCUMENTSTARTEXTEND",SCI_DOCUMENTSTARTEXTEND,false,true);

    //SCI_DOCUMENTEND
        addStringProp(st, "DocumentEnd","SCI_DOCUMENTEND",SCI_DOCUMENTEND,false,true);

    //SCI_DOCUMENTENDEXTEND
        addStringProp(st, "DocumentEndExtend","SCI_DOCUMENTENDEXTEND",SCI_DOCUMENTENDEXTEND,false,true);

    //SCI_PAGEUP
        addStringProp(st, "PageUp","SCI_PAGEUP",SCI_PAGEUP,false,true);

    //SCI_PAGEUPEXTEND
        addStringProp(st, "PageUpExtend","SCI_PAGEUPEXTEND",SCI_PAGEUPEXTEND,false,true);

    //SCI_PAGEUPRECTEXTEND
        addStringProp(st, "PageUpRectExtend","SCI_PAGEUPRECTEXTEND",SCI_PAGEUPRECTEXTEND,false,true);

    //SCI_PAGEDOWN
        addStringProp(st, "PageDown","SCI_PAGEDOWN",SCI_PAGEDOWN,false,true);

    //SCI_PAGEDOWNEXTEND
        addStringProp(st, "PageDownExtend","SCI_PAGEDOWNEXTEND",SCI_PAGEDOWNEXTEND,false,true);

    //SCI_PAGEDOWNRECTEXTEND
        addStringProp(st, "PageDownRectExtend","SCI_PAGEDOWNRECTEXTEND",SCI_PAGEDOWNRECTEXTEND,false,true);

    //SCI_STUTTEREDPAGEUP
        addStringProp(st, "StutteredPageUp","SCI_STUTTEREDPAGEUP",SCI_STUTTEREDPAGEUP,false,true);

    //SCI_STUTTEREDPAGEUPEXTEND
        addStringProp(st, "StutteredPageUpExtend","SCI_STUTTEREDPAGEUPEXTEND",SCI_STUTTEREDPAGEUPEXTEND,false,true);

    //SCI_STUTTEREDPAGEDOWN
        addStringProp(st, "StutteredPageDown","SCI_STUTTEREDPAGEDOWN",SCI_STUTTEREDPAGEDOWN,false,true);

    //SCI_STUTTEREDPAGEDOWNEXTEND
        addStringProp(st, "StutteredPageDownExtend","SCI_STUTTEREDPAGEDOWNEXTEND",SCI_STUTTEREDPAGEDOWNEXTEND,false,true);

    //SCI_DELETEBACK
        addStringProp(st, "DeleteBack","SCI_DELETEBACK",SCI_DELETEBACK,false,true);

    //SCI_DELETEBACKNOTLINE
        addStringProp(st, "DeleteBackNotLine","SCI_DELETEBACKNOTLINE",SCI_DELETEBACKNOTLINE,false,true);

    //SCI_DELWORDLEFT
        addStringProp(st, "DelWordLeft","SCI_DELWORDLEFT",SCI_DELWORDLEFT,false,true);

    //SCI_DELWORDRIGHT
        addStringProp(st, "DelWordRight","SCI_DELWORDRIGHT",SCI_DELWORDRIGHT,false,true);

    //SCI_DELWORDRIGHTEND
        addStringProp(st, "DelWordRightEnd","SCI_DELWORDRIGHTEND",SCI_DELWORDRIGHTEND,false,true);

    //SCI_DELLINELEFT
        addStringProp(st, "DelLineLeft","SCI_DELLINELEFT",SCI_DELLINELEFT,false,true);

    //SCI_DELLINERIGHT
        addStringProp(st, "DelLineRight","SCI_DELLINERIGHT",SCI_DELLINERIGHT,false,true);

    //SCI_LINEDELETE
        addStringProp(st, "LineDelete","SCI_LINEDELETE",SCI_LINEDELETE,false,true);

    //SCI_LINECUT
        addStringProp(st, "LineCut","SCI_LINECUT",SCI_LINECUT,false,true);

    //SCI_LINECOPY
        addStringProp(st, "LineCopy","SCI_LINECOPY",SCI_LINECOPY,false,true);

    //SCI_LINETRANSPOSE
        addStringProp(st, "LineTranspose","SCI_LINETRANSPOSE",SCI_LINETRANSPOSE,false,true);

    //SCI_LINEDUPLICATE
        addStringProp(st, "LineDuplicate","SCI_LINEDUPLICATE",SCI_LINEDUPLICATE,false,true);

    //SCI_LOWERCASE
        addStringProp(st, "LowerCase","SCI_LOWERCASE",SCI_LOWERCASE,false,true);

    //SCI_UPPERCASE
        addStringProp(st, "UpperCase","SCI_UPPERCASE",SCI_UPPERCASE,false,true);

    //SCI_CANCEL
        addStringProp(st, "Cancel","SCI_CANCEL",SCI_CANCEL,false,true);

    //SCI_EDITTOGGLEOVERTYPE
        addStringProp(st, "EditToggleOvertype","SCI_EDITTOGGLEOVERTYPE",SCI_EDITTOGGLEOVERTYPE,false,true);

    //SCI_NEWLINE
        addStringProp(st, "NewLine","SCI_NEWLINE",SCI_NEWLINE,false,true);

    //SCI_FORMFEED
        addStringProp(st, "FormFeed","SCI_FORMFEED",SCI_FORMFEED,false,true);

    //SCI_TAB
        addStringProp(st, "Tab","SCI_TAB",SCI_TAB,false,true);

    //SCI_BACKTAB
        addStringProp(st, "BackTab","SCI_BACKTAB",SCI_BACKTAB,false,true);

    //SCI_SELECTIONDUPLICATE
        addStringProp(st, "SelectionDuplicate","SCI_SELECTIONDUPLICATE",SCI_SELECTIONDUPLICATE,false,true);

    //SCI_VERTICALCENTRECARET
        addStringProp(st, "VerticalCentreCaret","SCI_VERTICALCENTRECARET",SCI_VERTICALCENTRECARET,false,true);

    //SCI_MOVESELECTEDLINESUP
        addStringProp(st, "MoveSelectedLinesUp","SCI_MOVESELECTEDLINESUP",SCI_MOVESELECTEDLINESUP,false,true);

    //SCI_MOVESELECTEDLINESDOWN
        addStringProp(st, "MoveSelectedLinesDown","SCI_MOVESELECTEDLINESDOWN",SCI_MOVESELECTEDLINESDOWN,false,true);

    //SCI_SCROLLTOSTART
        addStringProp(st, "ScrollToStart","SCI_SCROLLTOSTART",SCI_SCROLLTOSTART,false,true);

    //SCI_SCROLLTOEND
        addStringProp(st, "ScrollToEnd","SCI_SCROLLTOEND",SCI_SCROLLTOEND,false,true);

    m_propgrid->Collapse(st);
}


void propgridtest03Frame::addKeyBindings(wxStyledTextCtrl* stc_def)
{

        wxArrayString cases2;
        wxArrayInt cases_values2;

        cases2.Add("wxSTC_CMD_BACKTAB");
        cases2.Add("wxSTC_CMD_CANCEL");
        cases2.Add("wxSTC_CMD_CHARLEFT");
        cases2.Add("wxSTC_CMD_CHARLEFTEXTEND");
        cases2.Add("wxSTC_CMD_CHARLEFTRECTEXTEND");
        cases2.Add("wxSTC_CMD_CHARRIGHT");
        cases2.Add("wxSTC_CMD_CHARRIGHTEXTEND");
        cases2.Add("wxSTC_CMD_CHARRIGHTRECTEXTEND");
        cases2.Add("wxSTC_CMD_CLEAR");
        cases2.Add("wxSTC_CMD_COPY");
        cases2.Add("wxSTC_CMD_CUT");
        cases2.Add("wxSTC_CMD_DELETEBACK");
        cases2.Add("wxSTC_CMD_DELETEBACKNOTLINE");
        cases2.Add("wxSTC_CMD_DELLINELEFT");
        cases2.Add("wxSTC_CMD_DELLINERIGHT");
        cases2.Add("wxSTC_CMD_DELWORDLEFT");
        cases2.Add("wxSTC_CMD_DELWORDRIGHT");
        cases2.Add("wxSTC_CMD_DELWORDRIGHTEND");
        cases2.Add("wxSTC_CMD_DOCUMENTEND");
        cases2.Add("wxSTC_CMD_DOCUMENTENDEXTEND");
        cases2.Add("wxSTC_CMD_DOCUMENTSTART");
        cases2.Add("wxSTC_CMD_DOCUMENTSTARTEXTEND");
        cases2.Add("wxSTC_CMD_EDITTOGGLEOVERTYPE");
        cases2.Add("wxSTC_CMD_FORMFEED");
        cases2.Add("wxSTC_CMD_HOME");
        cases2.Add("wxSTC_CMD_HOMEDISPLAY");
        cases2.Add("wxSTC_CMD_HOMEDISPLAYEXTEND");
        cases2.Add("wxSTC_CMD_HOMEEXTEND");
        cases2.Add("wxSTC_CMD_HOMERECTEXTEND");
        cases2.Add("wxSTC_CMD_HOMEWRAP");
        cases2.Add("wxSTC_CMD_HOMEWRAPEXTEND");
        cases2.Add("wxSTC_CMD_LINECOPY");
        cases2.Add("wxSTC_CMD_LINECUT");
        cases2.Add("wxSTC_CMD_LINEDELETE");
        cases2.Add("wxSTC_CMD_LINEDOWN");
        cases2.Add("wxSTC_CMD_LINEDOWNEXTEND");
        cases2.Add("wxSTC_CMD_LINEDOWNRECTEXTEND");
        cases2.Add("wxSTC_CMD_LINEDUPLICATE");
        cases2.Add("wxSTC_CMD_LINEEND");
        cases2.Add("wxSTC_CMD_LINEENDDISPLAY");
        cases2.Add("wxSTC_CMD_LINEENDDISPLAYEXTEND");
        cases2.Add("wxSTC_CMD_LINEENDEXTEND");
        cases2.Add("wxSTC_CMD_LINEENDRECTEXTEND");
        cases2.Add("wxSTC_CMD_LINEENDWRAP");
        cases2.Add("wxSTC_CMD_LINEENDWRAPEXTEND");
        cases2.Add("wxSTC_CMD_LINESCROLLDOWN");
        cases2.Add("wxSTC_CMD_LINESCROLLUP");
        cases2.Add("wxSTC_CMD_LINETRANSPOSE");
        cases2.Add("wxSTC_CMD_LINEUP");
        cases2.Add("wxSTC_CMD_LINEUPEXTEND");
        cases2.Add("wxSTC_CMD_LINEUPRECTEXTEND");
        cases2.Add("wxSTC_CMD_LOWERCASE");
        cases2.Add("wxSTC_CMD_MOVESELECTEDLINESDOWN");
        cases2.Add("wxSTC_CMD_MOVESELECTEDLINESUP");
        cases2.Add("wxSTC_CMD_NEWLINE");
        cases2.Add("wxSTC_CMD_PAGEDOWN");
        cases2.Add("wxSTC_CMD_PAGEDOWNEXTEND");
        cases2.Add("wxSTC_CMD_PAGEDOWNRECTEXTEND");
        cases2.Add("wxSTC_CMD_PAGEUP");
        cases2.Add("wxSTC_CMD_PAGEUPEXTEND");
        cases2.Add("wxSTC_CMD_PAGEUPRECTEXTEND");
        cases2.Add("wxSTC_CMD_PARADOWN");
        cases2.Add("wxSTC_CMD_PARADOWNEXTEND");
        cases2.Add("wxSTC_CMD_PARAUP");
        cases2.Add("wxSTC_CMD_PARAUPEXTEND");
        cases2.Add("wxSTC_CMD_PASTE");
        cases2.Add("wxSTC_CMD_REDO");
        cases2.Add("wxSTC_CMD_SCROLLTOEND");
        cases2.Add("wxSTC_CMD_SCROLLTOSTART");
        cases2.Add("wxSTC_CMD_SELECTALL");
        cases2.Add("wxSTC_CMD_STUTTEREDPAGEDOWN");
        cases2.Add("wxSTC_CMD_STUTTEREDPAGEDOWNEXTEND");
        cases2.Add("wxSTC_CMD_STUTTEREDPAGEUP");
        cases2.Add("wxSTC_CMD_STUTTEREDPAGEUPEXTEND");
        cases2.Add("wxSTC_CMD_TAB");
        cases2.Add("wxSTC_CMD_UNDO");
        cases2.Add("wxSTC_CMD_UPPERCASE");
        cases2.Add("wxSTC_CMD_VCHOME");
        cases2.Add("wxSTC_CMD_VCHOMEEXTEND");
        cases2.Add("wxSTC_CMD_VCHOMERECTEXTEND");
        cases2.Add("wxSTC_CMD_VCHOMEWRAP");
        cases2.Add("wxSTC_CMD_VCHOMEWRAPEXTEND");
        cases2.Add("wxSTC_CMD_VERTICALCENTRECARET");
        cases2.Add("wxSTC_CMD_WORDLEFT");
        cases2.Add("wxSTC_CMD_WORDLEFTEND");
        cases2.Add("wxSTC_CMD_WORDLEFTENDEXTEND");
        cases2.Add("wxSTC_CMD_WORDLEFTEXTEND");
        cases2.Add("wxSTC_CMD_WORDPARTLEFT");
        cases2.Add("wxSTC_CMD_WORDPARTLEFTEXTEND");
        cases2.Add("wxSTC_CMD_WORDPARTRIGHT");
        cases2.Add("wxSTC_CMD_WORDPARTRIGHTEXTEND");
        cases2.Add("wxSTC_CMD_WORDRIGHT");
        cases2.Add("wxSTC_CMD_WORDRIGHTEND");
        cases2.Add("wxSTC_CMD_WORDRIGHTENDEXTEND");
        cases2.Add("wxSTC_CMD_WORDRIGHTEXTEND");
        cases2.Add("wxSTC_CMD_ZOOMIN");
        cases2.Add("wxSTC_CMD_ZOOMOUT");

        cases_values2.Add(wxSTC_CMD_BACKTAB);
        cases_values2.Add(wxSTC_CMD_CANCEL);
        cases_values2.Add(wxSTC_CMD_CHARLEFT);
        cases_values2.Add(wxSTC_CMD_CHARLEFTEXTEND);
        cases_values2.Add(wxSTC_CMD_CHARLEFTRECTEXTEND);
        cases_values2.Add(wxSTC_CMD_CHARRIGHT);
        cases_values2.Add(wxSTC_CMD_CHARRIGHTEXTEND);
        cases_values2.Add(wxSTC_CMD_CHARRIGHTRECTEXTEND);
        cases_values2.Add(wxSTC_CMD_CLEAR);
        cases_values2.Add(wxSTC_CMD_COPY);
        cases_values2.Add(wxSTC_CMD_CUT);
        cases_values2.Add(wxSTC_CMD_DELETEBACK);
        cases_values2.Add(wxSTC_CMD_DELETEBACKNOTLINE);
        cases_values2.Add(wxSTC_CMD_DELLINELEFT);
        cases_values2.Add(wxSTC_CMD_DELLINERIGHT);
        cases_values2.Add(wxSTC_CMD_DELWORDLEFT);
        cases_values2.Add(wxSTC_CMD_DELWORDRIGHT);
        cases_values2.Add(wxSTC_CMD_DELWORDRIGHTEND);
        cases_values2.Add(wxSTC_CMD_DOCUMENTEND);
        cases_values2.Add(wxSTC_CMD_DOCUMENTENDEXTEND);
        cases_values2.Add(wxSTC_CMD_DOCUMENTSTART);
        cases_values2.Add(wxSTC_CMD_DOCUMENTSTARTEXTEND);
        cases_values2.Add(wxSTC_CMD_EDITTOGGLEOVERTYPE);
        cases_values2.Add(wxSTC_CMD_FORMFEED);
        cases_values2.Add(wxSTC_CMD_HOME);
        cases_values2.Add(wxSTC_CMD_HOMEDISPLAY);
        cases_values2.Add(wxSTC_CMD_HOMEDISPLAYEXTEND);
        cases_values2.Add(wxSTC_CMD_HOMEEXTEND);
        cases_values2.Add(wxSTC_CMD_HOMERECTEXTEND);
        cases_values2.Add(wxSTC_CMD_HOMEWRAP);
        cases_values2.Add(wxSTC_CMD_HOMEWRAPEXTEND);
        cases_values2.Add(wxSTC_CMD_LINECOPY);
        cases_values2.Add(wxSTC_CMD_LINECUT);
        cases_values2.Add(wxSTC_CMD_LINEDELETE);
        cases_values2.Add(wxSTC_CMD_LINEDOWN);
        cases_values2.Add(wxSTC_CMD_LINEDOWNEXTEND);
        cases_values2.Add(wxSTC_CMD_LINEDOWNRECTEXTEND);
        cases_values2.Add(wxSTC_CMD_LINEDUPLICATE);
        cases_values2.Add(wxSTC_CMD_LINEEND);
        cases_values2.Add(wxSTC_CMD_LINEENDDISPLAY);
        cases_values2.Add(wxSTC_CMD_LINEENDDISPLAYEXTEND);
        cases_values2.Add(wxSTC_CMD_LINEENDEXTEND);
        cases_values2.Add(wxSTC_CMD_LINEENDRECTEXTEND);
        cases_values2.Add(wxSTC_CMD_LINEENDWRAP);
        cases_values2.Add(wxSTC_CMD_LINEENDWRAPEXTEND);
        cases_values2.Add(wxSTC_CMD_LINESCROLLDOWN);
        cases_values2.Add(wxSTC_CMD_LINESCROLLUP);
        cases_values2.Add(wxSTC_CMD_LINETRANSPOSE);
        cases_values2.Add(wxSTC_CMD_LINEUP);
        cases_values2.Add(wxSTC_CMD_LINEUPEXTEND);
        cases_values2.Add(wxSTC_CMD_LINEUPRECTEXTEND);
        cases_values2.Add(wxSTC_CMD_LOWERCASE);
        cases_values2.Add(wxSTC_CMD_MOVESELECTEDLINESDOWN);
        cases_values2.Add(wxSTC_CMD_MOVESELECTEDLINESUP);
        cases_values2.Add(wxSTC_CMD_NEWLINE);
        cases_values2.Add(wxSTC_CMD_PAGEDOWN);
        cases_values2.Add(wxSTC_CMD_PAGEDOWNEXTEND);
        cases_values2.Add(wxSTC_CMD_PAGEDOWNRECTEXTEND);
        cases_values2.Add(wxSTC_CMD_PAGEUP);
        cases_values2.Add(wxSTC_CMD_PAGEUPEXTEND);
        cases_values2.Add(wxSTC_CMD_PAGEUPRECTEXTEND);
        cases_values2.Add(wxSTC_CMD_PARADOWN);
        cases_values2.Add(wxSTC_CMD_PARADOWNEXTEND);
        cases_values2.Add(wxSTC_CMD_PARAUP);
        cases_values2.Add(wxSTC_CMD_PARAUPEXTEND);
        cases_values2.Add(wxSTC_CMD_PASTE);
        cases_values2.Add(wxSTC_CMD_REDO);
        cases_values2.Add(wxSTC_CMD_SCROLLTOEND);
        cases_values2.Add(wxSTC_CMD_SCROLLTOSTART);
        cases_values2.Add(wxSTC_CMD_SELECTALL);
        cases_values2.Add(wxSTC_CMD_STUTTEREDPAGEDOWN);
        cases_values2.Add(wxSTC_CMD_STUTTEREDPAGEDOWNEXTEND);
        cases_values2.Add(wxSTC_CMD_STUTTEREDPAGEUP);
        cases_values2.Add(wxSTC_CMD_STUTTEREDPAGEUPEXTEND);
        cases_values2.Add(wxSTC_CMD_TAB);
        cases_values2.Add(wxSTC_CMD_UNDO);
        cases_values2.Add(wxSTC_CMD_UPPERCASE);
        cases_values2.Add(wxSTC_CMD_VCHOME);
        cases_values2.Add(wxSTC_CMD_VCHOMEEXTEND);
        cases_values2.Add(wxSTC_CMD_VCHOMERECTEXTEND);
        cases_values2.Add(wxSTC_CMD_VCHOMEWRAP);
        cases_values2.Add(wxSTC_CMD_VCHOMEWRAPEXTEND);
        cases_values2.Add(wxSTC_CMD_VERTICALCENTRECARET);
        cases_values2.Add(wxSTC_CMD_WORDLEFT);
        cases_values2.Add(wxSTC_CMD_WORDLEFTEND);
        cases_values2.Add(wxSTC_CMD_WORDLEFTENDEXTEND);
        cases_values2.Add(wxSTC_CMD_WORDLEFTEXTEND);
        cases_values2.Add(wxSTC_CMD_WORDPARTLEFT);
        cases_values2.Add(wxSTC_CMD_WORDPARTLEFTEXTEND);
        cases_values2.Add(wxSTC_CMD_WORDPARTRIGHT);
        cases_values2.Add(wxSTC_CMD_WORDPARTRIGHTEXTEND);
        cases_values2.Add(wxSTC_CMD_WORDRIGHT);
        cases_values2.Add(wxSTC_CMD_WORDRIGHTEND);
        cases_values2.Add(wxSTC_CMD_WORDRIGHTENDEXTEND);
        cases_values2.Add(wxSTC_CMD_WORDRIGHTEXTEND);
        cases_values2.Add(wxSTC_CMD_ZOOMIN);
        cases_values2.Add(wxSTC_CMD_ZOOMOUT);

        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_KEY_DOWN");
        cases.Add("wxSTC_KEY_UP");
        cases.Add("wxSTC_KEY_LEFT");
        cases.Add("wxSTC_KEY_RIGHT");
        cases.Add("wxSTC_KEY_HOME");
        cases.Add("wxSTC_KEY_END");
        cases.Add("wxSTC_KEY_PRIOR");
        cases.Add("wxSTC_KEY_NEXT");
        cases.Add("wxSTC_KEY_DELETE");
        cases.Add("wxSTC_KEY_INSERT");
        cases.Add("wxSTC_KEY_ESCAPE");
        cases.Add("wxSTC_KEY_BACK");
        cases.Add("wxSTC_KEY_TAB");
        cases.Add("wxSTC_KEY_RETURN");
        cases.Add("wxSTC_KEY_ADD");
        cases.Add("wxSTC_KEY_SUBTRACT");
        cases.Add("wxSTC_KEY_DIVIDE");
        cases.Add("wxSTC_KEY_WIN");
        cases.Add("wxSTC_KEY_RWIN");
        cases.Add("wxSTC_KEY_MENU");
        cases.Add("(specify key)");

        cases_values.Add(wxSTC_KEY_DOWN);
        cases_values.Add(wxSTC_KEY_UP);
        cases_values.Add(wxSTC_KEY_LEFT);
        cases_values.Add(wxSTC_KEY_RIGHT);
        cases_values.Add(wxSTC_KEY_HOME);
        cases_values.Add(wxSTC_KEY_END);
        cases_values.Add(wxSTC_KEY_PRIOR);
        cases_values.Add(wxSTC_KEY_NEXT);
        cases_values.Add(wxSTC_KEY_DELETE);
        cases_values.Add(wxSTC_KEY_INSERT);
        cases_values.Add(wxSTC_KEY_ESCAPE);
        cases_values.Add(wxSTC_KEY_BACK);
        cases_values.Add(wxSTC_KEY_TAB);
        cases_values.Add(wxSTC_KEY_RETURN);
        cases_values.Add(wxSTC_KEY_ADD);
        cases_values.Add(wxSTC_KEY_SUBTRACT);
        cases_values.Add(wxSTC_KEY_DIVIDE);
        cases_values.Add(wxSTC_KEY_WIN);
        cases_values.Add(wxSTC_KEY_RWIN);
        cases_values.Add(wxSTC_KEY_MENU);
        cases_values.Add(-1);

        wxArrayString cases3;
        wxArrayInt cases_values3;

        cases3.Add("wxSTC_SCMOD_NORM");
        cases3.Add("(specified bits)");

        cases_values3.Add(wxSTC_SCMOD_NORM);
        cases_values3.Add(-1);

        wxArrayString cases4;
        wxArrayInt cases_values4;

        cases4.Add("wxSTC_SCMOD_SHIFT");
        cases4.Add("wxSTC_SCMOD_CTRL");
        cases4.Add("wxSTC_SCMOD_ALT");
        cases4.Add("wxSTC_SCMOD_SUPER");
        cases4.Add("wxSTC_SCMOD_META");

        cases_values4.Add(wxSTC_SCMOD_SHIFT);
        cases_values4.Add(wxSTC_SCMOD_CTRL);
        cases_values4.Add(wxSTC_SCMOD_ALT);
        cases_values4.Add(wxSTC_SCMOD_SUPER);
        cases_values4.Add(wxSTC_SCMOD_META);

        wxArrayString cases5;
        wxArrayInt cases_values5;
        cases5.Add("no keys are currently bound");
        cases_values5.Add(-1);


    wxPGProperty* np,*np2,*np3;
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Key bindings"));
    st->SetClientData(reinterpret_cast<void *>(SCI_KEYBINDINGS));

    //SCI_ASSIGNCMDKEY(int keyDefinition, int sciCommand)
        np = addStringProp(st, "CmdKeyAssign", "SCI_ASSIGNCMDKEY", SCI_ASSIGNCMDKEY,false,true);
        np2 = addEnumProp(np,"key","zzz",SCI_ASSIGNCMDKEY2,wxSTC_KEY_DOWN,cases,cases_values);
            np3 = addDotDotDotStringProp(np2, "key code", "zzz", SCI_ASSIGNCMDKEY3);
            m_propgrid->HideProperty(np3,true);
        np2 = addEnumProp(np,"modifiers","zzz",SCI_ASSIGNCMDKEY4,wxSTC_SCMOD_NORM,cases3,cases_values3);
            np3 = addFlagsProp(np2,"bits","zzz",SCI_PARAM,0,cases4,cases_values4);
            np3->Enable(false);
            m_propgrid->Collapse(np2);
        addEnumParam(np,"cmd", wxSTC_CMD_BACKTAB,cases2,cases_values2);
        m_propgrid->Collapse(np);

    //SCI_CLEARCMDKEY(int keyDefinition)
        np=addStringProp(st, "CmdKeyClear", "SCI_CLEARCMDKEY", SCI_CLEARCMDKEY,false,true);
        np2=addEnumProp(np,"binding","zzz",SCI_PARAM,-1,cases5,cases_values5);
        m_propgrid->Collapse(np);
        SCI_CLEARCMDKEYENUM=np2;

    //SCI_CLEARALLCMDKEYS
        addStringProp(st,"CmdKeyClearAll","SCI_CLEARALLCMDKEYS",SCI_CLEARALLCMDKEYS ,false,true);

    //SCI_NULL
        addStringProp(st,"SCI_NULL","SCI_NULL",SCI_NULL ,false,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addPopupEditMenu(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Popup edit menu"));
    st->SetClientData(reinterpret_cast<void *>(SCI_POPUPEDITMENU));

    //SCI_USEPOPUP(bool bEnablePopup)
        addBoolProp(st,"UsePopUp","SCI_USEPOPUP",SCI_USEPOPUP,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addMacrrecording(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Macro recording"));
    st->SetClientData(reinterpret_cast<void *>(SCI_MACRORECORDING));

    //SCI_STARTRECORD
        addStringProp(st, "StartRecord", "SCI_STARTRECORD", SCI_STARTRECORD,false,true);

    //SCI_STOPRECORD
        addStringProp(st, "StopRecord", "SCI_STOPRECORD", SCI_STOPRECORD,false,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addPrinting(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_PRINT_NORMAL");
        cases.Add("wxSTC_PRINT_INVERTLIGHT");
        cases.Add("wxSTC_PRINT_BLACKONWHITE");
        cases.Add("wxSTC_PRINT_COLOURONWHITE");
        cases.Add("wxSTC_PRINT_COLOURONWHITEDEFAULTBG");

        cases_values.Add(wxSTC_PRINT_NORMAL);
        cases_values.Add(wxSTC_PRINT_INVERTLIGHT);
        cases_values.Add(wxSTC_PRINT_BLACKONWHITE);
        cases_values.Add(wxSTC_PRINT_COLOURONWHITE);
        cases_values.Add(wxSTC_PRINT_COLOURONWHITEDEFAULTBG);

        wxArrayString cases2;
        wxArrayInt cases2_values;

        cases2.Add("wxSTC_WRAP_NONE");
        cases2.Add("wxSTC_WRAP_WORD");
        cases2.Add("wxSTC_WRAP_CHAR");

        cases2_values.Add(wxSTC_WRAP_NONE);
        cases2_values.Add(wxSTC_WRAP_WORD);
        cases2_values.Add(wxSTC_WRAP_CHAR);

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Printing"));
    st->SetClientData(reinterpret_cast<void *>(SCI_PRINTING));

    //SCI_FORMATRANGE(bool bDraw, Sci_RangeToFormat *pfr)
        wxPGProperty* np = addStringProp(st, "FormatRange", "SCI_FORMATRANGE", SCI_FORMATRANGE,false,true);
        addIntParam(np,"startPos",0,0,INT_MAX);
        addIntParam(np,"endPos",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETPRINTMAGNIFICATION(int magnification)
        addIntProp(st,"SetPrintMagnification","SCI_SETPRINTMAGNIFICATION",SCI_SETPRINTMAGNIFICATION,stc_def->GetPrintMagnification(),0,INT_MAX);

    //SCI_GETPRINTMAGNIFICATION
        addStringProp(st, "GetPrintMagnification", "SCI_GETPRINTMAGNIFICATION", SCI_GETPRINTMAGNIFICATION,true,true);

    //SCI_SETPRINTCOLOURMODE(int mode)
        addEnumProp(st,"SetPrintColourMode","SCI_SETPRINTCOLOURMODE",SCI_SETPRINTCOLOURMODE,stc_def->GetPrintColourMode(),cases,cases_values);

    //SCI_GETPRINTCOLOURMODE
        addStringProp(st, "GetPrintColourMode", "SCI_GETPRINTCOLOURMODE", SCI_GETPRINTCOLOURMODE,true,true);

    //SCI_SETPRINTWRAPMODE
        addEnumProp(st,"SetPrintWrapMode","SCI_SETPRINTWRAPMODE",SCI_SETPRINTWRAPMODE,stc_def->GetPrintWrapMode(),cases2,cases2_values);

    //SCI_GETPRINTWRAPMODE
        addStringProp(st, "GetPrintWrapMode", "SCI_GETPRINTWRAPMODE", SCI_GETPRINTWRAPMODE,true,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addDirectAccess(wxStyledTextCtrl* stc_def)
{
    wxPGProperty *np,*st = m_propgrid->Append(new wxPropertyCategory("Direct access"));
    st->SetClientData(reinterpret_cast<void *>(SCI_DIRECTACCESS));

    //SCI_GETDIRECTFUNCTION
        np = m_propgrid->Append(new wxStringProperty("SCI_GETDIRECTFUNCTION"));
        np->SetClientData(reinterpret_cast<void *>(SCI_GETDIRECTFUNCTION));
        m_propgrid->SetPropertyReadOnly(np);
        np->SetBackgroundColour(notImplemented);
        np->Enable(false);

    //SCI_GETDIRECTPOINTER
        np = m_propgrid->Append(new wxStringProperty("SCI_GETDIRECTPOINTER"));
        np->SetClientData(reinterpret_cast<void *>(SCI_GETDIRECTPOINTER));
        m_propgrid->SetPropertyReadOnly(np);
        np->SetBackgroundColour(notImplemented);
        np->Enable(false);

    //SCI_GETCHARACTERPOINTER
        addStringProp(st, "GetCharacterPointer", "SCI_GETCHARACTERPOINTER", SCI_GETCHARACTERPOINTER,true,true);

    //SCI_GETRANGEPOINTER(int position, int rangeLength)
        np = addStringProp(st, "GetRangePointer", "SCI_GETRANGEPOINTER", SCI_GETRANGEPOINTER,true,true);
        addIntParam(np,"position",0,0,INT_MAX);
        addIntParam(np,"rangeLength",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETGAPPOSITION
        addStringProp(st, "GetGapPosition", "SCI_GETGAPPOSITION", SCI_GETGAPPOSITION,true,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addMultipleViews(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases;
        wxArrayInt cases_values;
        cases.Add("0");
        cases_values.Add(0);

        wxArrayString cases2;
        wxArrayInt cases2_values;
        cases2.Add("(current unreferenced document)");
        cases2_values.Add(-1);


    wxPGProperty *np, *np2,*st = m_propgrid->Append(new wxPropertyCategory("Multiple views"));
    st->SetClientData(reinterpret_cast<void *>(SCI_MULTIPLEVIEWS));

    //SCI_GETDOCPOINTER
        addStringProp(st, "GetDocPointer", "SCI_GETDOCPOINTER", SCI_GETDOCPOINTER,true,true);

    //SCI_SETDOCPOINTER(<unused>, document *pDoc)
        np=addStringProp(st, "SetDocPointer", "SCI_SETDOCPOINTER", SCI_SETDOCPOINTER,false,true);
        np2=addEnumProp(np,"docPointer","zzz",SCI_PARAM,0,cases,cases_values);
        SCI_SETDOCPOINTERENUM=np2;
        m_propgrid->Collapse(np);

    //SCI_CREATEDOCUMENT
        addStringProp(st, "CreateDocument", "SCI_CREATEDOCUMENT", SCI_CREATEDOCUMENT,true,true);

    //SCI_ADDREFDOCUMENT(<unused>, document *pDoc)
        np=addStringProp(st, "AddRefDocument", "SCI_ADDREFDOCUMENT", SCI_ADDREFDOCUMENT,false,true);
        np2=addEnumProp(np,"docPointer","zzz",SCI_PARAM,-1,cases2,cases2_values);
        SCI_ADDREFDOCUMENTENUM=np2;
        m_propgrid->Collapse(np);

    //SCI_RELEASEDOCUMENT(<unused>, document *pDoc)
        np=addStringProp(st, "ReleaseDocument", "SCI_RELEASEDOCUMENT", SCI_RELEASEDOCUMENT,false,true);
        np2=addEnumProp(np,"docPointer","zzz",SCI_PARAM,-1,cases2,cases2_values);
        np2->SetValueToUnspecified();
        np2->Enable(false);
        SCI_RELEASEDOCUMENTENUM=np2;
        m_propgrid->Collapse(np);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addBackgroundLoadingAndSaving(wxStyledTextCtrl* stc_def)
{
    wxPGProperty *np,*st = m_propgrid->Append(new wxPropertyCategory("Background loading and saving"));
    st->SetClientData(reinterpret_cast<void *>(SCI_BACKGROUNDLOADINGANDSAVING));

    //SCI_CREATELOADER(int bytes)
        np=addLongStringProp(st, "CreateLoader", "SCI_CREATELOADER", SCI_CREATELOADER,true,true);
        addStringParam(np, "text to load",true);
        m_propgrid->Collapse(np);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addFolding(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases,cases2;
        wxArrayInt cases_values,cases2_values;

        cases.Add("wxSTC_FOLDLEVELWHITEFLAG");
        cases.Add("wxSTC_FOLDLEVELHEADERFLAG");
        cases_values.Add(wxSTC_FOLDLEVELWHITEFLAG);
        cases_values.Add(wxSTC_FOLDLEVELHEADERFLAG);

        cases2.Add("wxSTC_FOLDFLAG_LINEBEFORE_EXPANDED");
        cases2.Add("wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED");
        cases2.Add("wxSTC_FOLDFLAG_LINEAFTER_EXPANDED");
        cases2.Add("wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED");
        cases2.Add("wxSTC_FOLDFLAG_LEVELNUMBERS");
        cases2_values.Add(wxSTC_FOLDFLAG_LINEBEFORE_EXPANDED);
        cases2_values.Add(wxSTC_FOLDFLAG_LINEBEFORE_CONTRACTED);
        cases2_values.Add(wxSTC_FOLDFLAG_LINEAFTER_EXPANDED);
        cases2_values.Add(wxSTC_FOLDFLAG_LINEAFTER_CONTRACTED);
        cases2_values.Add(wxSTC_FOLDFLAG_LEVELNUMBERS);

    wxPGProperty *np,*st = m_propgrid->Append(new wxPropertyCategory("Folding"));
    st->SetClientData(reinterpret_cast<void *>(SCI_FOLDING));

    //SCI_VISIBLEFROMDOCLINE(int docLine)
        np=addStringProp(st, "VisibleFromDocLine", "SCI_VISIBLEFROMDOCLINE", SCI_VISIBLEFROMDOCLINE,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_DOCLINEFROMVISIBLE(int displayLine)
        np=addStringProp(st, "DocLineFromVisible", "SCI_DOCLINEFROMVISIBLE", SCI_DOCLINEFROMVISIBLE,true,true);
        addIntParam(np,"lineDisplay",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SHOWLINES(int lineStart, int lineEnd)
        np=addStringProp(st, "ShowLines", "SCI_SHOWLINES", SCI_SHOWLINES,false,true);
        addIntParam(np,"lineStart",0,0,INT_MAX);
        addIntParam(np,"lineEnd",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_HIDELINES(int lineStart, int lineEnd)
        np=addStringProp(st, "HideLines", "SCI_HIDELINES", SCI_HIDELINES,false,true);
        addIntParam(np,"lineStart",0,0,INT_MAX);
        addIntParam(np,"lineEnd",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETLINEVISIBLE(int line)
        np=addStringProp(st, "GetLineVisible", "SCI_GETLINEVISIBLE", SCI_GETLINEVISIBLE,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_GETALLLINESVISIBLE
        addStringProp(st, "GetAllLinesVisible", "SCI_GETALLLINESVISIBLE", SCI_GETALLLINESVISIBLE,true,true);

    //SCI_SETFOLDLEVEL(int line, int level)
        np=addStringProp(st, "SetFoldLevel", "SCI_SETFOLDLEVEL", SCI_SETFOLDLEVEL,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addIntParam(np,"fold level",wxSTC_FOLDLEVELBASE,0,wxSTC_FOLDLEVELNUMBERMASK);
        addFlagsParam(np, "flag bits", 0, cases, cases_values);
        m_propgrid->Collapse(np);

    //SCI_GETFOLDLEVEL(int line)
        np=addLongStringProp(st, "GetFoldLevel", "SCI_GETFOLDLEVEL", SCI_GETFOLDLEVEL,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETFOLDFLAGS(int flags)
        addFlagsProp(st,"SetFoldFlags","SCI_SETFOLDFLAGS",SCI_SETFOLDFLAGS,0,cases2,cases2_values);

    //SCI_GETLASTCHILD(int line, int level)
        np=addStringProp(st, "GetLastChild", "SCI_GETLASTCHILD", SCI_GETLASTCHILD,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addIntParam(np,"level",wxSTC_FOLDLEVELBASE,-1,wxSTC_FOLDLEVELNUMBERMASK);
        m_propgrid->Collapse(np);

    //SCI_GETFOLDPARENT(int line)
        np=addStringProp(st, "GetFoldParent", "SCI_GETFOLDPARENT", SCI_GETFOLDPARENT,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_SETFOLDEXPANDED(int line, bool expanded)
        np=addStringProp(st, "SetFoldExpanded", "SCI_SETFOLDEXPANDED", SCI_SETFOLDEXPANDED,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        addBoolParam(np,"expanded",false);
        m_propgrid->Collapse(np);

    //SCI_GETFOLDEXPANDED(int line)
        np=addStringProp(st, "GetFoldExpanded", "SCI_GETFOLDEXPANDED", SCI_GETFOLDEXPANDED,true,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_CONTRACTEDFOLDNEXT(int lineStart)
        np=addStringProp(st, "ContractedFoldNext", "SCI_CONTRACTEDFOLDNEXT", SCI_CONTRACTEDFOLDNEXT,false,true);
        addIntParam(np,"lineStart",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_TOGGLEFOLD(int line)
        np=addStringProp(st, "ToggleFold", "SCI_TOGGLEFOLD", SCI_TOGGLEFOLD,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_ENSUREVISIBLE(int line)
        np=addStringProp(st, "EnsureVisible", "SCI_ENSUREVISIBLE", SCI_ENSUREVISIBLE,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_ENSUREVISIBLEENFORCEPOLICY(int line)
        np=addStringProp(st, "EnsureVisibleEnforcePolicy", "SCI_ENSUREVISIBLEENFORCEPOLICY", SCI_ENSUREVISIBLEENFORCEPOLICY,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addLineWrapping(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases,cases2,cases3,cases4,cases5,cases6,cases7;
        wxArrayInt cases_values,cases2_values,cases3_values,cases4_values,cases5_values,cases6_values,cases7_values;

        cases.Add("wxSTC_WRAP_NONE");
        cases.Add("wxSTC_WRAP_WORD");
        cases.Add("wxSTC_WRAP_CHAR");
        cases_values.Add(wxSTC_WRAP_NONE);
        cases_values.Add(wxSTC_WRAP_WORD);
        cases_values.Add(wxSTC_WRAP_CHAR);

        cases2.Add("wxSTC_WRAPVISUALFLAG_NONE");
        cases2.Add("(specified bits)");
        cases2_values.Add(wxSTC_WRAPVISUALFLAG_NONE);
        cases2_values.Add(-1);

        cases3.Add("wxSTC_WRAPVISUALFLAG_END");
        cases3.Add("wxSTC_WRAPVISUALFLAG_START");
        cases3.Add("wxSTC_WRAPVISUALFLAG_MARGIN");

        cases3_values.Add(wxSTC_WRAPVISUALFLAG_END);
        cases3_values.Add(wxSTC_WRAPVISUALFLAG_START);
        cases3_values.Add(wxSTC_WRAPVISUALFLAG_MARGIN);

        cases4.Add("wxSTC_WRAPVISUALFLAGLOC_DEFAULT");
        cases4.Add("(specified bits)");
        cases4_values.Add(wxSTC_WRAPVISUALFLAGLOC_DEFAULT);
        cases4_values.Add(-1);

        cases5.Add("wxSTC_WRAPVISUALFLAGLOC_END_BY_TEXT");
        cases5.Add("wxSTC_WRAPVISUALFLAGLOC_START_BY_TEXT");
        cases5_values.Add(wxSTC_WRAPVISUALFLAGLOC_END_BY_TEXT);
        cases5_values.Add(wxSTC_WRAPVISUALFLAGLOC_START_BY_TEXT);

        cases6.Add("wxSTC_WRAPINDENT_FIXED");
        cases6.Add("wxSTC_WRAPINDENT_SAME");
        cases6.Add("wxSTC_WRAPINDENT_INDENT");
        cases6_values.Add(wxSTC_WRAPINDENT_FIXED);
        cases6_values.Add(wxSTC_WRAPINDENT_SAME);
        cases6_values.Add(wxSTC_WRAPINDENT_INDENT);

        cases7.Add("wxSTC_CACHE_NONE");
        cases7.Add("wxSTC_CACHE_CARET");
        cases7.Add("wxSTC_CACHE_PAGE");
        cases7.Add("wxSTC_CACHE_DOCUMENT");
        cases7_values.Add(wxSTC_CACHE_NONE);
        cases7_values.Add(wxSTC_CACHE_CARET);
        cases7_values.Add(wxSTC_CACHE_PAGE);
        cases7_values.Add(wxSTC_CACHE_DOCUMENT);

    wxPGProperty *np,*np2,*st = m_propgrid->Append(new wxPropertyCategory("Line wrapping"));
    st->SetClientData(reinterpret_cast<void *>(SCI_LINEWRAPPING));

    //SCI_SETWRAPMODE(int wrapMode)
        addEnumProp(st,"SetWrapMode","SCI_SETWRAPMODE",SCI_SETWRAPMODE,stc_def->GetWrapMode(),cases,cases_values);

    //SCI_GETWRAPMODE
        addStringProp(st, "GetWrapMode", "SCI_GETWRAPMODE", SCI_GETWRAPMODE,true,true);

    //SCI_SETWRAPVISUALFLAGS(int wrapVisualFlags)
        np=addEnumProp(st,"SetWrapVisualFlags","SCI_SETWRAPVISUALFLAGS",SCI_SETWRAPVISUALFLAGS,stc_def->GetWrapVisualFlags(),cases2,cases2_values);
        np2=addFlagsProp(np,"bits","zzz",SCI_SETWRAPVISUALFLAGS2, stc_def->GetWrapVisualFlags(),cases3,cases3_values);
        np2->Enable(false);
        m_propgrid->Collapse(np);

    //SCI_GETWRAPVISUALFLAGS
        addLongStringProp(st, "GetWrapVisualFlags", "SCI_GETWRAPVISUALFLAGS", SCI_GETWRAPVISUALFLAGS,true,true);

    //SCI_SETWRAPVISUALFLAGSLOCATION(int wrapVisualFlagsLocation)
        np=addEnumProp(st,"SetWrapVisualFlagsLocation","SCI_SETWRAPVISUALFLAGSLOCATION",SCI_SETWRAPVISUALFLAGSLOCATION,stc_def->GetWrapVisualFlagsLocation(),cases4,cases4_values);
        np2=addFlagsProp(np,"bits","zzz",SCI_SETWRAPVISUALFLAGSLOCATION2, stc_def->GetWrapVisualFlagsLocation(),cases5,cases5_values);
        np2->Enable(false);
        m_propgrid->Collapse(np);

    //SCI_GETWRAPVISUALFLAGSLOCATION
        addLongStringProp(st, "GetWrapVisualFlagsLocation", "SCI_GETWRAPVISUALFLAGSLOCATION", SCI_GETWRAPVISUALFLAGSLOCATION,true,true);

    //SCI_SETWRAPINDENTMODE(int indentMode)
        addEnumProp(st,"SetWrapIndentMode","SCI_SETWRAPINDENTMODE",SCI_SETWRAPINDENTMODE,stc_def->GetWrapIndentMode(),cases6,cases6_values);

    //SCI_GETWRAPINDENTMODE
        addStringProp(st, "GetWrapIndentMode", "SCI_GETWRAPINDENTMODE", SCI_GETWRAPINDENTMODE,true,true);

    //SCI_SETWRAPSTARTINDENT(int indent)
        addIntProp(st,"SetWrapStartIndent","SCI_SETWRAPSTARTINDENT",SCI_SETWRAPSTARTINDENT,stc_def->GetWrapStartIndent(),0,INT_MAX);

    //SCI_GETWRAPSTARTINDENT
        addStringProp(st, "GetWrapStartIndent", "SCI_GETWRAPSTARTINDENT", SCI_GETWRAPSTARTINDENT,true,true);

    //SCI_SETLAYOUTCACHE(int cacheMode)
        addEnumProp(st,"SetLayoutCache","SCI_SETLAYOUTCACHE",SCI_SETLAYOUTCACHE,stc_def->GetLayoutCache(),cases7,cases7_values);

    //SCI_GETLAYOUTCACHE
        addStringProp(st, "GetLayoutCache", "SCI_GETLAYOUTCACHE", SCI_GETLAYOUTCACHE,true,true);

    //SCI_SETPOSITIONCACHE(int size)
        addIntProp(st,"SetPositionCacheSize","SCI_SETPOSITIONCACHE",SCI_SETPOSITIONCACHE,stc_def->GetPositionCacheSize(),0,INT_MAX);

    //SCI_GETPOSITIONCACHE
        addStringProp(st, "GetPositionCacheSize", "SCI_GETPOSITIONCACHE", SCI_GETPOSITIONCACHE,true,true);

    //SCI_LINESSPLIT(int pixelWidth)
        np=addStringProp(st, "LinesSplit", "SCI_LINESSPLIT", SCI_LINESSPLIT,false,true);
        addIntParam(np,"pixelWidth",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_LINESJOIN
        addStringProp(st, "LinesJoin", "SCI_LINESJOIN", SCI_LINESJOIN,false,true);

    //SCI_WRAPCOUNT(int docLine)
        np=addStringProp(st, "WrapCount", "SCI_WRAPCOUNT", SCI_WRAPCOUNT,false,true);
        addIntParam(np,"line",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    m_propgrid->Collapse(st);
}


void propgridtest03Frame::addZooming(wxStyledTextCtrl* stc_def)
{
    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Zooming"));
    st->SetClientData(reinterpret_cast<void *>(SCI_ZOOMING));

    //SCI_ZOOMIN
        addStringProp(st, "ZoomIn", "SCI_ZOOMIN", SCI_ZOOMIN,false,true);

    //SCI_ZOOMOUT
        addStringProp(st, "ZoomOut", "SCI_ZOOMOUT", SCI_ZOOMOUT,false,true);

    //SCI_SETZOOM(int zoomInPoints)
        addIntProp(st,"SetZoom","SCI_SETZOOM",SCI_SETZOOM,stc_def->GetZoom(),-10,20);

    //SCI_GETZOOM
        addStringProp(st, "GetZoom", "SCI_GETZOOM", SCI_GETZOOM,true,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addLongLines(wxStyledTextCtrl* stc_def)
{

        wxArrayString cases;
        wxArrayInt cases_values;

        cases.Add("wxSTC_EDGE_NONE");
        cases.Add("wxSTC_EDGE_LINE");
        cases.Add("wxSTC_EDGE_BACKGROUND");

        cases_values.Add(wxSTC_EDGE_NONE);
        cases_values.Add(wxSTC_EDGE_LINE);
        cases_values.Add(wxSTC_EDGE_BACKGROUND);

    wxPGProperty* st = m_propgrid->Append(new wxPropertyCategory("Long lines"));
    st->SetClientData(reinterpret_cast<void *>(SCI_LONGLINES));


    //SCI_SETEDGEMODE(int mode)
        addEnumProp(st,"SetEdgeMode","SCI_SETEDGEMODE",SCI_SETEDGEMODE,stc_def->GetEdgeMode(),cases,cases_values);

    //SCI_GETEDGEMODE
        addStringProp(st, "GetEdgeMode", "SCI_GETEDGEMODE", SCI_GETEDGEMODE,true,true);

    //SCI_SETEDGECOLUMN(int column)
        addIntProp(st,"SetEdgeColumn","SCI_SETEDGECOLUMN",SCI_SETEDGECOLUMN,stc_def->GetEdgeColumn(),0,INT_MAX);

    //SCI_GETEDGECOLUMN
        addStringProp(st, "GetEdgeColumn", "SCI_GETEDGECOLUMN", SCI_GETEDGECOLUMN,true,true);

    //SCI_SETEDGECOLOUR(int colour)
        addColorProp(st, "SetEdgeColour", "SCI_SETEDGECOLOUR", SCI_SETEDGECOLOUR, stc_def->GetEdgeColour() );

    //SCI_GETEDGECOLOUR
        addColorStringProp(st, "GetEdgeColour", "SCI_GETEDGECOLOUR", SCI_GETEDGECOLOUR);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addLexer(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases,cases2;
        wxArrayInt cases_values,cases2_values;

        cases.Add("wxSTC_LEX_CONTAINER");
        cases.Add("wxSTC_LEX_NULL");
        cases.Add("wxSTC_LEX_PYTHON");
        cases.Add("wxSTC_LEX_CPP");
        cases.Add("wxSTC_LEX_HTML");
        cases.Add("wxSTC_LEX_XML");
        cases.Add("wxSTC_LEX_PERL");
        cases.Add("wxSTC_LEX_SQL");
        cases.Add("wxSTC_LEX_VB");
        cases.Add("wxSTC_LEX_PROPERTIES");
        cases.Add("wxSTC_LEX_ERRORLIST");
        cases.Add("wxSTC_LEX_MAKEFILE");
        cases.Add("wxSTC_LEX_BATCH");
        cases.Add("wxSTC_LEX_XCODE");
        cases.Add("wxSTC_LEX_LATEX");
        cases.Add("wxSTC_LEX_LUA");
        cases.Add("wxSTC_LEX_DIFF");
        cases.Add("wxSTC_LEX_CONF");
        cases.Add("wxSTC_LEX_PASCAL");
        cases.Add("wxSTC_LEX_AVE");
        cases.Add("wxSTC_LEX_ADA");
        cases.Add("wxSTC_LEX_LISP");
        cases.Add("wxSTC_LEX_RUBY");
        cases.Add("wxSTC_LEX_EIFFEL");
        cases.Add("wxSTC_LEX_EIFFELKW");
        cases.Add("wxSTC_LEX_TCL");
        cases.Add("wxSTC_LEX_NNCRONTAB");
        cases.Add("wxSTC_LEX_BULLANT");
        cases.Add("wxSTC_LEX_VBSCRIPT");
        cases.Add("wxSTC_LEX_BAAN");
        cases.Add("wxSTC_LEX_MATLAB");
        cases.Add("wxSTC_LEX_SCRIPTOL");
        cases.Add("wxSTC_LEX_ASM");
        cases.Add("wxSTC_LEX_CPPNOCASE");
        cases.Add("wxSTC_LEX_FORTRAN");
        cases.Add("wxSTC_LEX_F77");
        cases.Add("wxSTC_LEX_CSS");
        cases.Add("wxSTC_LEX_POV");
        cases.Add("wxSTC_LEX_LOUT");
        cases.Add("wxSTC_LEX_ESCRIPT");
        cases.Add("wxSTC_LEX_PS");
        cases.Add("wxSTC_LEX_NSIS");
        cases.Add("wxSTC_LEX_MMIXAL");
        cases.Add("wxSTC_LEX_CLW");
        cases.Add("wxSTC_LEX_CLWNOCASE");
        cases.Add("wxSTC_LEX_LOT");
        cases.Add("wxSTC_LEX_YAML");
        cases.Add("wxSTC_LEX_TEX");
        cases.Add("wxSTC_LEX_METAPOST");
        cases.Add("wxSTC_LEX_POWERBASIC");
        cases.Add("wxSTC_LEX_FORTH");
        cases.Add("wxSTC_LEX_ERLANG");
        cases.Add("wxSTC_LEX_OCTAVE");
        cases.Add("wxSTC_LEX_MSSQL");
        cases.Add("wxSTC_LEX_VERILOG");
        cases.Add("wxSTC_LEX_KIX");
        cases.Add("wxSTC_LEX_GUI4CLI");
        cases.Add("wxSTC_LEX_SPECMAN");
        cases.Add("wxSTC_LEX_AU3");
        cases.Add("wxSTC_LEX_APDL");
        cases.Add("wxSTC_LEX_BASH");
        cases.Add("wxSTC_LEX_ASN1");
        cases.Add("wxSTC_LEX_VHDL");
        cases.Add("wxSTC_LEX_CAML");
        cases.Add("wxSTC_LEX_BLITZBASIC");
        cases.Add("wxSTC_LEX_PUREBASIC");
        cases.Add("wxSTC_LEX_HASKELL");
        cases.Add("wxSTC_LEX_PHPSCRIPT");
        cases.Add("wxSTC_LEX_TADS3");
        cases.Add("wxSTC_LEX_REBOL");
        cases.Add("wxSTC_LEX_SMALLTALK");
        cases.Add("wxSTC_LEX_FLAGSHIP");
        cases.Add("wxSTC_LEX_CSOUND");
        cases.Add("wxSTC_LEX_FREEBASIC");
        cases.Add("wxSTC_LEX_INNOSETUP");
        cases.Add("wxSTC_LEX_OPAL");
        cases.Add("wxSTC_LEX_SPICE");
        cases.Add("wxSTC_LEX_D");
        cases.Add("wxSTC_LEX_CMAKE");
        cases.Add("wxSTC_LEX_GAP");
        cases.Add("wxSTC_LEX_PLM");
        cases.Add("wxSTC_LEX_PROGRESS");
        cases.Add("wxSTC_LEX_ABAQUS");
        cases.Add("wxSTC_LEX_ASYMPTOTE");
        cases.Add("wxSTC_LEX_R");
        cases.Add("wxSTC_LEX_MAGIK");
        cases.Add("wxSTC_LEX_POWERSHELL");
        cases.Add("wxSTC_LEX_MYSQL");
        cases.Add("wxSTC_LEX_PO");
        cases.Add("wxSTC_LEX_TAL");
        cases.Add("wxSTC_LEX_COBOL");
        cases.Add("wxSTC_LEX_TACL");
        cases.Add("wxSTC_LEX_SORCUS");
        cases.Add("wxSTC_LEX_POWERPRO");
        cases.Add("wxSTC_LEX_NIMROD");
        cases.Add("wxSTC_LEX_SML");
        cases.Add("wxSTC_LEX_MARKDOWN");
        cases.Add("wxSTC_LEX_TXT2TAGS");
        cases.Add("wxSTC_LEX_A68K");
        cases.Add("wxSTC_LEX_MODULA");
        cases.Add("wxSTC_LEX_COFFEESCRIPT");
        cases.Add("wxSTC_LEX_TCMD");
        cases.Add("wxSTC_LEX_AVS");
        cases.Add("wxSTC_LEX_ECL");
        cases.Add("wxSTC_LEX_OSCRIPT");
        cases.Add("wxSTC_LEX_VISUALPROLOG");

        cases_values.Add(wxSTC_LEX_CONTAINER);
        cases_values.Add(wxSTC_LEX_NULL);
        cases_values.Add(wxSTC_LEX_PYTHON);
        cases_values.Add(wxSTC_LEX_CPP);
        cases_values.Add(wxSTC_LEX_HTML);
        cases_values.Add(wxSTC_LEX_XML);
        cases_values.Add(wxSTC_LEX_PERL);
        cases_values.Add(wxSTC_LEX_SQL);
        cases_values.Add(wxSTC_LEX_VB);
        cases_values.Add(wxSTC_LEX_PROPERTIES);
        cases_values.Add(wxSTC_LEX_ERRORLIST);
        cases_values.Add(wxSTC_LEX_MAKEFILE);
        cases_values.Add(wxSTC_LEX_BATCH);
        cases_values.Add(wxSTC_LEX_XCODE);
        cases_values.Add(wxSTC_LEX_LATEX);
        cases_values.Add(wxSTC_LEX_LUA);
        cases_values.Add(wxSTC_LEX_DIFF);
        cases_values.Add(wxSTC_LEX_CONF);
        cases_values.Add(wxSTC_LEX_PASCAL);
        cases_values.Add(wxSTC_LEX_AVE);
        cases_values.Add(wxSTC_LEX_ADA);
        cases_values.Add(wxSTC_LEX_LISP);
        cases_values.Add(wxSTC_LEX_RUBY);
        cases_values.Add(wxSTC_LEX_EIFFEL);
        cases_values.Add(wxSTC_LEX_EIFFELKW);
        cases_values.Add(wxSTC_LEX_TCL);
        cases_values.Add(wxSTC_LEX_NNCRONTAB);
        cases_values.Add(wxSTC_LEX_BULLANT);
        cases_values.Add(wxSTC_LEX_VBSCRIPT);
        cases_values.Add(wxSTC_LEX_BAAN);
        cases_values.Add(wxSTC_LEX_MATLAB);
        cases_values.Add(wxSTC_LEX_SCRIPTOL);
        cases_values.Add(wxSTC_LEX_ASM);
        cases_values.Add(wxSTC_LEX_CPPNOCASE);
        cases_values.Add(wxSTC_LEX_FORTRAN);
        cases_values.Add(wxSTC_LEX_F77);
        cases_values.Add(wxSTC_LEX_CSS);
        cases_values.Add(wxSTC_LEX_POV);
        cases_values.Add(wxSTC_LEX_LOUT);
        cases_values.Add(wxSTC_LEX_ESCRIPT);
        cases_values.Add(wxSTC_LEX_PS);
        cases_values.Add(wxSTC_LEX_NSIS);
        cases_values.Add(wxSTC_LEX_MMIXAL);
        cases_values.Add(wxSTC_LEX_CLW);
        cases_values.Add(wxSTC_LEX_CLWNOCASE);
        cases_values.Add(wxSTC_LEX_LOT);
        cases_values.Add(wxSTC_LEX_YAML);
        cases_values.Add(wxSTC_LEX_TEX);
        cases_values.Add(wxSTC_LEX_METAPOST);
        cases_values.Add(wxSTC_LEX_POWERBASIC);
        cases_values.Add(wxSTC_LEX_FORTH);
        cases_values.Add(wxSTC_LEX_ERLANG);
        cases_values.Add(wxSTC_LEX_OCTAVE);
        cases_values.Add(wxSTC_LEX_MSSQL);
        cases_values.Add(wxSTC_LEX_VERILOG);
        cases_values.Add(wxSTC_LEX_KIX);
        cases_values.Add(wxSTC_LEX_GUI4CLI);
        cases_values.Add(wxSTC_LEX_SPECMAN);
        cases_values.Add(wxSTC_LEX_AU3);
        cases_values.Add(wxSTC_LEX_APDL);
        cases_values.Add(wxSTC_LEX_BASH);
        cases_values.Add(wxSTC_LEX_ASN1);
        cases_values.Add(wxSTC_LEX_VHDL);
        cases_values.Add(wxSTC_LEX_CAML);
        cases_values.Add(wxSTC_LEX_BLITZBASIC);
        cases_values.Add(wxSTC_LEX_PUREBASIC);
        cases_values.Add(wxSTC_LEX_HASKELL);
        cases_values.Add(wxSTC_LEX_PHPSCRIPT);
        cases_values.Add(wxSTC_LEX_TADS3);
        cases_values.Add(wxSTC_LEX_REBOL);
        cases_values.Add(wxSTC_LEX_SMALLTALK);
        cases_values.Add(wxSTC_LEX_FLAGSHIP);
        cases_values.Add(wxSTC_LEX_CSOUND);
        cases_values.Add(wxSTC_LEX_FREEBASIC);
        cases_values.Add(wxSTC_LEX_INNOSETUP);
        cases_values.Add(wxSTC_LEX_OPAL);
        cases_values.Add(wxSTC_LEX_SPICE);
        cases_values.Add(wxSTC_LEX_D);
        cases_values.Add(wxSTC_LEX_CMAKE);
        cases_values.Add(wxSTC_LEX_GAP);
        cases_values.Add(wxSTC_LEX_PLM);
        cases_values.Add(wxSTC_LEX_PROGRESS);
        cases_values.Add(wxSTC_LEX_ABAQUS);
        cases_values.Add(wxSTC_LEX_ASYMPTOTE);
        cases_values.Add(wxSTC_LEX_R);
        cases_values.Add(wxSTC_LEX_MAGIK);
        cases_values.Add(wxSTC_LEX_POWERSHELL);
        cases_values.Add(wxSTC_LEX_MYSQL);
        cases_values.Add(wxSTC_LEX_PO);
        cases_values.Add(wxSTC_LEX_TAL);
        cases_values.Add(wxSTC_LEX_COBOL);
        cases_values.Add(wxSTC_LEX_TACL);
        cases_values.Add(wxSTC_LEX_SORCUS);
        cases_values.Add(wxSTC_LEX_POWERPRO);
        cases_values.Add(wxSTC_LEX_NIMROD);
        cases_values.Add(wxSTC_LEX_SML);
        cases_values.Add(wxSTC_LEX_MARKDOWN);
        cases_values.Add(wxSTC_LEX_TXT2TAGS);
        cases_values.Add(wxSTC_LEX_A68K);
        cases_values.Add(wxSTC_LEX_MODULA);
        cases_values.Add(wxSTC_LEX_COFFEESCRIPT);
        cases_values.Add(wxSTC_LEX_TCMD);
        cases_values.Add(wxSTC_LEX_AVS);
        cases_values.Add(wxSTC_LEX_ECL);
        cases_values.Add(wxSTC_LEX_OSCRIPT);
        cases_values.Add(wxSTC_LEX_VISUALPROLOG);

        cases2.Add("");
        cases2.Add("null");
        cases2.Add("python");
        cases2.Add("cpp");
        cases2.Add("hypertext");
        cases2.Add("xml");
        cases2.Add("perl");
        cases2.Add("sql");
        cases2.Add("vb");
        cases2.Add("props");
        cases2.Add("errorlist");
        cases2.Add("makefile");
        cases2.Add("batch");
        cases2.Add("latex");
        cases2.Add("lua");
        cases2.Add("diff");
        cases2.Add("conf");
        cases2.Add("pascal");
        cases2.Add("ave");
        cases2.Add("ada");
        cases2.Add("lisp");
        cases2.Add("ruby");
        cases2.Add("eiffel");
        cases2.Add("eiffelkw");
        cases2.Add("tcl");
        cases2.Add("nncrontab");
        cases2.Add("bullant");
        cases2.Add("vbscript");
        cases2.Add("baan");
        cases2.Add("matlab");
        cases2.Add("scriptol");
        cases2.Add("asm");
        cases2.Add("cppnocase");
        cases2.Add("fortran");
        cases2.Add("f77");
        cases2.Add("css");
        cases2.Add("pov");
        cases2.Add("lout");
        cases2.Add("escript");
        cases2.Add("ps");
        cases2.Add("nsis");
        cases2.Add("mmixal");
        cases2.Add("clarion");
        cases2.Add("clarionnocase");
        cases2.Add("lot");
        cases2.Add("yaml");
        cases2.Add("tex");
        cases2.Add("metapost");
        cases2.Add("powerbasic");
        cases2.Add("forth");
        cases2.Add("erlang");
        cases2.Add("octave");
        cases2.Add("mssql");
        cases2.Add("verilog");
        cases2.Add("kix");
        cases2.Add("gui4cli");
        cases2.Add("specman");
        cases2.Add("au3");
        cases2.Add("apdl");
        cases2.Add("bash");
        cases2.Add("asn1");
        cases2.Add("vhdl");
        cases2.Add("caml");
        cases2.Add("blitzbasic");
        cases2.Add("purebasic");
        cases2.Add("haskell");
        cases2.Add("phpscript");
        cases2.Add("tads3");
        cases2.Add("rebol");
        cases2.Add("smalltalk");
        cases2.Add("flagship");
        cases2.Add("csound");
        cases2.Add("freebasic");
        cases2.Add("inno");
        cases2.Add("opal");
        cases2.Add("spice");
        cases2.Add("d");
        cases2.Add("cmake");
        cases2.Add("gap");
        cases2.Add("PL/M");
        cases2.Add("progress");
        cases2.Add("abaqus");
        cases2.Add("asy");
        cases2.Add("r");
        cases2.Add("magiksf");
        cases2.Add("powershell");
        cases2.Add("mysql");
        cases2.Add("po");
        cases2.Add("TAL");
        cases2.Add("COBOL");
        cases2.Add("TACL");
        cases2.Add("sorcins");
        cases2.Add("powerpro");
        cases2.Add("nimrod");
        cases2.Add("SML");
        cases2.Add("markdown");
        cases2.Add("txt2tags");
        cases2.Add("a68k");
        cases2.Add("modula");
        cases2.Add("coffeescript");
        cases2.Add("tcmd");
        cases2.Add("avs");
        cases2.Add("ecl");
        cases2.Add("oscript");
        cases2.Add("visualprolog");

        cases2_values.Add(wxSTC_LEX_CONTAINER);
        cases2_values.Add(wxSTC_LEX_NULL);
        cases2_values.Add(wxSTC_LEX_PYTHON);
        cases2_values.Add(wxSTC_LEX_CPP);
        cases2_values.Add(wxSTC_LEX_HTML);
        cases2_values.Add(wxSTC_LEX_XML);
        cases2_values.Add(wxSTC_LEX_PERL);
        cases2_values.Add(wxSTC_LEX_SQL);
        cases2_values.Add(wxSTC_LEX_VB);
        cases2_values.Add(wxSTC_LEX_PROPERTIES);
        cases2_values.Add(wxSTC_LEX_ERRORLIST);
        cases2_values.Add(wxSTC_LEX_MAKEFILE);
        cases2_values.Add(wxSTC_LEX_BATCH);
        cases2_values.Add(wxSTC_LEX_LATEX);
        cases2_values.Add(wxSTC_LEX_LUA);
        cases2_values.Add(wxSTC_LEX_DIFF);
        cases2_values.Add(wxSTC_LEX_CONF);
        cases2_values.Add(wxSTC_LEX_PASCAL);
        cases2_values.Add(wxSTC_LEX_AVE);
        cases2_values.Add(wxSTC_LEX_ADA);
        cases2_values.Add(wxSTC_LEX_LISP);
        cases2_values.Add(wxSTC_LEX_RUBY);
        cases2_values.Add(wxSTC_LEX_EIFFEL);
        cases2_values.Add(wxSTC_LEX_EIFFELKW);
        cases2_values.Add(wxSTC_LEX_TCL);
        cases2_values.Add(wxSTC_LEX_NNCRONTAB);
        cases2_values.Add(wxSTC_LEX_BULLANT);
        cases2_values.Add(wxSTC_LEX_VBSCRIPT);
        cases2_values.Add(wxSTC_LEX_BAAN);
        cases2_values.Add(wxSTC_LEX_MATLAB);
        cases2_values.Add(wxSTC_LEX_SCRIPTOL);
        cases2_values.Add(wxSTC_LEX_ASM);
        cases2_values.Add(wxSTC_LEX_CPPNOCASE);
        cases2_values.Add(wxSTC_LEX_FORTRAN);
        cases2_values.Add(wxSTC_LEX_F77);
        cases2_values.Add(wxSTC_LEX_CSS);
        cases2_values.Add(wxSTC_LEX_POV);
        cases2_values.Add(wxSTC_LEX_LOUT);
        cases2_values.Add(wxSTC_LEX_ESCRIPT);
        cases2_values.Add(wxSTC_LEX_PS);
        cases2_values.Add(wxSTC_LEX_NSIS);
        cases2_values.Add(wxSTC_LEX_MMIXAL);
        cases2_values.Add(wxSTC_LEX_CLW);
        cases2_values.Add(wxSTC_LEX_CLWNOCASE);
        cases2_values.Add(wxSTC_LEX_LOT);
        cases2_values.Add(wxSTC_LEX_YAML);
        cases2_values.Add(wxSTC_LEX_TEX);
        cases2_values.Add(wxSTC_LEX_METAPOST);
        cases2_values.Add(wxSTC_LEX_POWERBASIC);
        cases2_values.Add(wxSTC_LEX_FORTH);
        cases2_values.Add(wxSTC_LEX_ERLANG);
        cases2_values.Add(wxSTC_LEX_OCTAVE);
        cases2_values.Add(wxSTC_LEX_MSSQL);
        cases2_values.Add(wxSTC_LEX_VERILOG);
        cases2_values.Add(wxSTC_LEX_KIX);
        cases2_values.Add(wxSTC_LEX_GUI4CLI);
        cases2_values.Add(wxSTC_LEX_SPECMAN);
        cases2_values.Add(wxSTC_LEX_AU3);
        cases2_values.Add(wxSTC_LEX_APDL);
        cases2_values.Add(wxSTC_LEX_BASH);
        cases2_values.Add(wxSTC_LEX_ASN1);
        cases2_values.Add(wxSTC_LEX_VHDL);
        cases2_values.Add(wxSTC_LEX_CAML);
        cases2_values.Add(wxSTC_LEX_BLITZBASIC);
        cases2_values.Add(wxSTC_LEX_PUREBASIC);
        cases2_values.Add(wxSTC_LEX_HASKELL);
        cases2_values.Add(wxSTC_LEX_PHPSCRIPT);
        cases2_values.Add(wxSTC_LEX_TADS3);
        cases2_values.Add(wxSTC_LEX_REBOL);
        cases2_values.Add(wxSTC_LEX_SMALLTALK);
        cases2_values.Add(wxSTC_LEX_FLAGSHIP);
        cases2_values.Add(wxSTC_LEX_CSOUND);
        cases2_values.Add(wxSTC_LEX_FREEBASIC);
        cases2_values.Add(wxSTC_LEX_INNOSETUP);
        cases2_values.Add(wxSTC_LEX_OPAL);
        cases2_values.Add(wxSTC_LEX_SPICE);
        cases2_values.Add(wxSTC_LEX_D);
        cases2_values.Add(wxSTC_LEX_CMAKE);
        cases2_values.Add(wxSTC_LEX_GAP);
        cases2_values.Add(wxSTC_LEX_PLM);
        cases2_values.Add(wxSTC_LEX_PROGRESS);
        cases2_values.Add(wxSTC_LEX_ABAQUS);
        cases2_values.Add(wxSTC_LEX_ASYMPTOTE);
        cases2_values.Add(wxSTC_LEX_R);
        cases2_values.Add(wxSTC_LEX_MAGIK);
        cases2_values.Add(wxSTC_LEX_POWERSHELL);
        cases2_values.Add(wxSTC_LEX_MYSQL);
        cases2_values.Add(wxSTC_LEX_PO);
        cases2_values.Add(wxSTC_LEX_TAL);
        cases2_values.Add(wxSTC_LEX_COBOL);
        cases2_values.Add(wxSTC_LEX_TACL);
        cases2_values.Add(wxSTC_LEX_SORCUS);
        cases2_values.Add(wxSTC_LEX_POWERPRO);
        cases2_values.Add(wxSTC_LEX_NIMROD);
        cases2_values.Add(wxSTC_LEX_SML);
        cases2_values.Add(wxSTC_LEX_MARKDOWN);
        cases2_values.Add(wxSTC_LEX_TXT2TAGS);
        cases2_values.Add(wxSTC_LEX_A68K);
        cases2_values.Add(wxSTC_LEX_MODULA);
        cases2_values.Add(wxSTC_LEX_COFFEESCRIPT);
        cases2_values.Add(wxSTC_LEX_TCMD);
        cases2_values.Add(wxSTC_LEX_AVS);
        cases2_values.Add(wxSTC_LEX_ECL);
        cases2_values.Add(wxSTC_LEX_OSCRIPT);
        cases2_values.Add(wxSTC_LEX_VISUALPROLOG);


    wxPGProperty *np,*np2,*st = m_propgrid->Append(new wxPropertyCategory("Lexer"));
    st->SetClientData(reinterpret_cast<void *>(SCI_LEXER));

    //SCI_SETLEXER(int lexer)
        np=addEnumProp(st,"SetLexer","SCI_SETLEXER",SCI_SETLEXER,stc_def->GetLexer(),cases,cases_values);
        LexerProp=np;

    //SCI_GETLEXER
        addStringProp(st, "GetLexer", "SCI_GETLEXER", SCI_GETLEXER,true,true);

    //SCI_SETLEXERLANGUAGE(<unused>, const char *name)
        addEnumProp(st,"SetLexerLanguage","SCI_SETLEXERLANGUAGE",SCI_SETLEXERLANGUAGE,stc_def->GetLexer(),cases2,cases2_values);

    //SCI_GETLEXERLANGUAGE(<unused>, char *name)
        addStringProp(st, "SCI_GETLEXERLANGUAGE", "SCI_GETLEXERLANGUAGE", SCI_GETLEXERLANGUAGE,true,true);

    //SCI_LOADLEXERLIBRARY(<unused>, const char *path)
        np = m_propgrid->Append(new wxStringProperty("SCI_LOADLEXERLIBRARY","SCI_LOADLEXERLIBRARY"));
        np->SetClientData(reinterpret_cast<void *>(SCI_LOADLEXERLIBRARY));
        np->Enable(false);
        np->SetBackgroundColour(notImplemented);

    //SCI_COLOURISE(int start, int end)
        np=addStringProp(st, "Colourise", "SCI_COLOURISE", SCI_COLOURISE,false,true);
        addIntParam(np,"start",0,0,INT_MAX);
        addIntParam(np,"end",0,-1,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_CHANGELEXERSTATE(int start, int end)
        np=addStringProp(st, "ChangeLexerState", "SCI_CHANGELEXERSTATE", SCI_CHANGELEXERSTATE,false,true);
        addIntParam(np,"start",0,0,INT_MAX);
        addIntParam(np,"end",0,0,INT_MAX);
        m_propgrid->Collapse(np);

    //SCI_PROPERTYNAMES(<unused>, char *names)
        addLongStringProp(st,"PropertyNames","SCI_PROPERTYNAMES", SCI_PROPERTYNAMES,true,true);

    //SCI_PROPERTYTYPE(const char *name)
        np=addStringProp(st, "PropertyType", "SCI_PROPERTYTYPE", SCI_PROPERTYTYPE,true,true);
        addStringParam(np, "name",false);
        m_propgrid->Collapse(np);

    //SCI_DESCRIBEPROPERTY(const char *name, char *description)
        np=addLongStringProp(st, "DescribeProperty", "SCI_DESCRIBEPROPERTY", SCI_DESCRIBEPROPERTY,true,true);
        addStringParam(np, "name",false);
        m_propgrid->Collapse(np);

    //SCI_SETPROPERTY(const char *key, const char *value)
        np=addStringProp(st, "SetProperty", "SCI_SETPROPERTY", SCI_SETPROPERTY,false,true);
        addStringParam(np, "key",false);
        addStringParam(np, "value",false);
        m_propgrid->Collapse(np);

    //SCI_GETPROPERTY(const char *key, char *value)
        np=addStringProp(st, "GetProperty", "SCI_GETPROPERTY", SCI_GETPROPERTY,true,true);
        addStringParam(np, "key",false);
        m_propgrid->Collapse(np);

    //SCI_GETPROPERTYEXPANDED(const char *key, char *value)
        np=addStringProp(st, "GetPropertyExpanded", "SCI_GETPROPERTYEXPANDED", SCI_GETPROPERTYEXPANDED,true,true);
        addStringParam(np, "key",false);
        m_propgrid->Collapse(np);

    //SCI_GETPROPERTYINT(const char *key, int default)
        np=addStringProp(st, "GetPropertyInt", "SCI_GETPROPERTYINT", SCI_GETPROPERTYINT,true,true);
        addStringParam(np, "key",false);
        m_propgrid->Collapse(np);

    //SCI_DESCRIBEKEYWORDSETS(<unused>, char *descriptions)
        addLongStringProp(st,"DescribeKeyWordSets","SCI_DESCRIBEKEYWORDSETS", SCI_DESCRIBEKEYWORDSETS,true,true);

    //SCI_SETKEYWORDS(int keyWordSet, const char *keyWordList)
        np=addStringProp(st,"SetKeyWords","SCI_SETKEYWORDS", SCI_SETKEYWORDS,false,true);
        for(int i=0;i<=wxSTC_KEYWORDSET_MAX;i++)
        {
            //np2=addLongStringProp(np,lexerInfo->getKWName(-1,i),"zzz", SCI_SETKEYWORDS2,false,false);

            np2 = m_propgrid->AppendIn(np,new wxLongStringProperty(lexerInfo->getKWName(-1,i),"zzz"));
            np2->SetClientData(reinterpret_cast<void *>(SCI_SETKEYWORDS2));
            //np2=addStringProp(np,lexerInfo->getKWName(-1,i),"zzz", SCI_SETKEYWORDS2,false,true);
            np2->SetClientObject(new myStyleData(i));
            //addStringParam(np2, "keyWords",true);
            lexerInfo->setKWVec(i,np2);
            //m_propgrid->Collapse(np2);
        }
        m_propgrid->Collapse(np);

    //SCI_GETSTYLEBITSNEEDED
        addStringProp(st, "GetStyleBitsNeeded", "SCI_GETSTYLEBITSNEEDED", SCI_GETSTYLEBITSNEEDED,true,true);

    m_propgrid->Collapse(st);
}

void propgridtest03Frame::addLexerObjects(wxStyledTextCtrl* stc_def)
{
    wxPGProperty *np,*st = m_propgrid->Append(new wxPropertyCategory("Lexer Objects"));
    st->SetClientData(reinterpret_cast<void *>(SCI_LEXEROBJECTS));

    //SCI_PRIVATELEXERCALL
        np=addStringProp(st, "PrivateLexerCall", "SCI_PRIVATELEXERCALL", SCI_PRIVATELEXERCALL,true,true);
        addIntParam(np,"operation",0,0,INT_MAX);
        addStringParam(np, "pointer",true);
        m_propgrid->Collapse(np);

    m_propgrid->Collapse(st);
}


void propgridtest03Frame::addNotifications(wxStyledTextCtrl* stc_def)
{
        wxArrayString cases,cases2,cases3;
        wxArrayInt cases_values,cases2_values,cases3_values;

        cases.Add("wxSTC_MODEVENTMASKALL");
        cases.Add("(specified bits)");
        cases_values.Add(wxSTC_MODEVENTMASKALL);
        cases_values.Add(-1);

        cases2.Add("wxSTC_MOD_INSERTTEXT");
        cases2.Add("wxSTC_MOD_DELETETEXT");
        cases2.Add("wxSTC_MOD_CHANGESTYLE");
        cases2.Add("wxSTC_MOD_CHANGEFOLD");
        cases2.Add("wxSTC_PERFORMED_USER");
        cases2.Add("wxSTC_PERFORMED_UNDO");
        cases2.Add("wxSTC_PERFORMED_REDO");
        cases2.Add("wxSTC_MULTISTEPUNDOREDO");
        cases2.Add("wxSTC_LASTSTEPINUNDOREDO");
        cases2.Add("wxSTC_MOD_CHANGEMARKER");
        cases2.Add("wxSTC_MOD_BEFOREINSERT");
        cases2.Add("wxSTC_MOD_BEFOREDELETE");
        cases2.Add("wxSTC_MULTILINEUNDOREDO");
        cases2.Add("wxSTC_STARTACTION");
        cases2.Add("wxSTC_MOD_CHANGEINDICATOR");
        cases2.Add("wxSTC_MOD_CHANGELINESTATE");
        cases2.Add("wxSTC_MOD_CHANGEMARGIN");
        cases2.Add("wxSTC_MOD_CHANGEANNOTATION");
        cases2.Add("wxSTC_MOD_CONTAINER");
        cases2.Add("wxSTC_MOD_LEXERSTATE");
        //cases2.Add("wxSTC_MODEVENTMASKALL");

        cases2_values.Add(wxSTC_MOD_INSERTTEXT);
        cases2_values.Add(wxSTC_MOD_DELETETEXT);
        cases2_values.Add(wxSTC_MOD_CHANGESTYLE);
        cases2_values.Add(wxSTC_MOD_CHANGEFOLD);
        cases2_values.Add(wxSTC_PERFORMED_USER);
        cases2_values.Add(wxSTC_PERFORMED_UNDO);
        cases2_values.Add(wxSTC_PERFORMED_REDO);
        cases2_values.Add(wxSTC_MULTISTEPUNDOREDO);
        cases2_values.Add(wxSTC_LASTSTEPINUNDOREDO);
        cases2_values.Add(wxSTC_MOD_CHANGEMARKER);
        cases2_values.Add(wxSTC_MOD_BEFOREINSERT);
        cases2_values.Add(wxSTC_MOD_BEFOREDELETE);
        cases2_values.Add(wxSTC_MULTILINEUNDOREDO);
        cases2_values.Add(wxSTC_STARTACTION);
        cases2_values.Add(wxSTC_MOD_CHANGEINDICATOR);
        cases2_values.Add(wxSTC_MOD_CHANGELINESTATE);
        cases2_values.Add(wxSTC_MOD_CHANGEMARGIN);
        cases2_values.Add(wxSTC_MOD_CHANGEANNOTATION);
        cases2_values.Add(wxSTC_MOD_CONTAINER);
        cases2_values.Add(wxSTC_MOD_LEXERSTATE);
        //cases2_values.Add(wxSTC_MODEVENTMASKALL);

        cases3.Add("wxSTC_TIME_FOREVER");
        cases3.Add("(specified time)");
        cases3_values.Add(wxSTC_TIME_FOREVER);
        cases3_values.Add(-1);

    wxPGProperty *np,*np2,*st = m_propgrid->Append(new wxPropertyCategory("Notifications"));
    st->SetClientData(reinterpret_cast<void *>(SCI_NOTIFICATIONS));

    //SCI_SETMODEVENTMASK(int eventMask)
        np=addEnumProp(st,"SetModEventMask","SCI_SETMODEVENTMASK",SCI_SETMODEVENTMASK,stc_def->GetModEventMask(),cases,cases_values);
        np2=addFlagsProp(np,"bits","zzz",SCI_SETMODEVENTMASK2,stc_def->GetModEventMask(),cases2,cases2_values);
        np2->Enable(false);
        m_propgrid->Collapse(np);

    //SCI_GETMODEVENTMASK
        addLongStringProp(st, "GetModEventMask", "SCI_GETMODEVENTMASK", SCI_GETMODEVENTMASK,true,true);

    //SCI_SETMOUSEDWELLTIME(int milliseconds)
        np=addEnumProp(st,"SetMouseDwellTime","SCI_SETMOUSEDWELLTIME",SCI_SETMOUSEDWELLTIME,stc_def->GetMouseDwellTime(),cases3,cases3_values);
        np2=addIntProp(np,"periodMilliseconds","zzz",SCI_SETMOUSEDWELLTIME2,stc_def->GetMouseDwellTime(),0,INT_MAX);
        np2->Enable(false);
        m_propgrid->Collapse(np);

    //SCI_GETMOUSEDWELLTIME
        addStringProp(st, "GetMouseDwellTime", "SCI_GETMOUSEDWELLTIME", SCI_GETMOUSEDWELLTIME,true,true);

    //SCI_SETIDENTIFIER(int identifier)
        addIntProp(st,"SetIdentifier","SCI_SETIDENTIFIER",SCI_SETIDENTIFIER,stc_def->GetIdentifier(),0,INT_MAX);

    //SCI_GETIDENTIFIER
        addStringProp(st, "GetIdentifier", "SCI_GETIDENTIFIER", SCI_GETIDENTIFIER,true,true);

    m_propgrid->Collapse(st);
}
