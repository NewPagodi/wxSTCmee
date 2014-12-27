#include "stcMain.h"

void propgridtest03Frame::OnPGSelected(wxPropertyGridEvent& event)
{
    wxPGProperty* p = event.GetProperty();


    if(!p)
    {
        return;
    }

    statusBar->SetStatusText("", 1);
    int i = reinterpret_cast<int>(p->GetClientData());

    while( (i<SCI_TEXTRETRIEVALANDMODIFICATION || i>SCI_GETIDENTIFIER)&& p)
    {
        p=p->GetParent();
        i = reinterpret_cast<int>(p->GetClientData());

    }

    if(i<SCI_TEXTRETRIEVALANDMODIFICATION || i>SCI_GETIDENTIFIER || !p)
    {
        return;
    }

    switch(i)
    {
        case SCI_TEXTRETRIEVALANDMODIFICATION:
            m_browser->LoadURL("memory:ScintillaDoc.html#TextRetrievalAndModification");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_GETTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#1");
            break;
        case SCI_SETTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#2");
            break;
        case SCI_SETSAVEPOINT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSAVEPOINT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#3");
            break;
        case SCI_GETLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#4");
            break;
        case SCI_REPLACESEL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_REPLACESEL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#5");
            break;
        case SCI_SETREADONLY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETREADONLY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#6");
            break;
        case SCI_GETREADONLY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETREADONLY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#7");
            break;
        case SCI_GETTEXTRANGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETTEXTRANGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#8");
            break;
        case SCI_ALLOCATE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ALLOCATE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#9");
            break;
        case SCI_ADDTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ADDTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#10");
            break;
        case SCI_ADDSTYLEDTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ADDSTYLEDTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#11");
            break;
        case SCI_APPENDTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_APPENDTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#12");
            break;
        case SCI_INSERTTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INSERTTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#13");
            break;
        case SCI_CLEARALL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CLEARALL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#14");
            break;
        case SCI_DELETERANGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_DELETERANGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#15");
            break;
        case SCI_CLEARDOCUMENTSTYLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CLEARDOCUMENTSTYLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#16");
            break;
        case SCI_GETCHARAT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCHARAT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#17");
            break;
        case SCI_GETSTYLEAT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSTYLEAT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#18");
            break;
        case SCI_GETSTYLEDTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSTYLEDTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#19");
            break;
        case SCI_SETSTYLEBITS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSTYLEBITS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#20");
            break;
        case SCI_GETSTYLEBITS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSTYLEBITS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#21");
            break;
        case SCI_ACCESSTOENCODEDTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#EncodedAccess");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_TARGETASUTF8:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_TARGETASUTF8");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_ENCODEDFROMUTF8:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ENCODEDFROMUTF8");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETLENGTHFORENCODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETLENGTHFORENCODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_GETTEXTRANGEALT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETTEXTRANGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#8");
            break;
        case SCI_SEARCHING:
            m_browser->LoadURL("memory:ScintillaDoc.html#Searching");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_FINDTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_FINDTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#22");
            break;
        case SCI_SEARCHANCHOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SEARCHANCHOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#23");
            break;
        case SCI_SEARCHNEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SEARCHNEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#24");
            break;
        case SCI_SEARCHPREV:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SEARCHPREV");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#25");
            break;
        case SCI_SETTARGETSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETTARGETSTART");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#26");
            break;
        case SCI_GETTARGETSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETTARGETSTART");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#27");
            break;
        case SCI_SETTARGETEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETTARGETEND");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#28");
            break;
        case SCI_GETTARGETEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETTARGETEND");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#29");
            break;
        case SCI_TARGETFROMSELECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_TARGETFROMSELECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#30");
            break;
        case SCI_SETSEARCHFLAGS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSEARCHFLAGS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#31");
            break;
        case SCI_GETSEARCHFLAGS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSEARCHFLAGS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#32");
            break;
        case SCI_SEARCHINTARGET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SEARCHINTARGET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#33");
            break;
        case SCI_REPLACETARGET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_REPLACETARGET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#34");
            break;
        case SCI_REPLACETARGETRE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_REPLACETARGETRE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#35");
            break;
        case SCI_GETTAG:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETTAG");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#36");
            break;

        case SCI_OVERTYPE:
            m_browser->LoadURL("memory:ScintillaDoc.html#Overtype");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETOVERTYPE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETOVERTYPE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#37");
            break;
        case SCI_GETOVERTYPE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETOVERTYPE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#38");
            break;
        case SCI_CUTCOPYANDPASTE:
            m_browser->LoadURL("memory:ScintillaDoc.html#CutCopyAndPaste");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_CUT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CUT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#39");
            break;
        case SCI_COPY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_COPY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#40");
            break;
        case SCI_PASTE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_PASTE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#41");
            break;
        case SCI_CLEAR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CLEAR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#42");
            break;
        case SCI_CANPASTE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CANPASTE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#43");
            break;
        case SCI_COPYRANGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_COPYRANGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#44");
            break;
        case SCI_COPYTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_COPYTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#45");
            break;
        case SCI_COPYALLOWLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_COPYALLOWLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#46");
            break;
        case SCI_SETPASTECONVERTENDINGS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETPASTECONVERTENDINGS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#47");
            break;
        case SCI_GETPASTECONVERTENDINGS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETPASTECONVERTENDINGS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#48");
            break;
        case SCI_ERRORHANDLING:
            m_browser->LoadURL("memory:ScintillaDoc.html#ErrorHandling");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETSTATUS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSTATUS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#49");
            break;
        case SCI_GETSTATUS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSTATUS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#50");
            break;
        case SCI_UNDOANDREDO:
            m_browser->LoadURL("memory:ScintillaDoc.html#UndoAndRedo");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_UNDO:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_UNDO");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#51");
            break;
        case SCI_CANUNDO:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CANUNDO");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#52");
            break;
        case SCI_EMPTYUNDOBUFFER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_EMPTYUNDOBUFFER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#53");
            break;
        case SCI_REDO:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_REDO");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#54");
            break;
        case SCI_CANREDO:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CANREDO");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#55");
            break;
        case SCI_SETUNDOCOLLECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETUNDOCOLLECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#56");
            break;
        case SCI_GETUNDOCOLLECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETUNDOCOLLECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#57");
            break;
        case SCI_BEGINUNDOACTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_BEGINUNDOACTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#58");
            break;
        case SCI_ENDUNDOACTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ENDUNDOACTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#59");
            break;
        case SCI_ADDUNDOACTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ADDUNDOACTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#60");
            break;

        case SCI_SELECTIONANDINFORMATION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SelectionAndInformation");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_GETTEXTLENGTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETTEXTLENGTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#61");
            break;
        case SCI_GETLENGTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLENGTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#62");
            break;
        case SCI_GETLINECOUNT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLINECOUNT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#63");
            break;
        case SCI_SETFIRSTVISIBLELINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFIRSTVISIBLELINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#64");
            break;
        case SCI_GETFIRSTVISIBLELINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETFIRSTVISIBLELINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#65");
            break;
        case SCI_LINESONSCREEN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_LINESONSCREEN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#66");
            break;
        case SCI_GETMODIFY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMODIFY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#67");
            break;
        case SCI_SETSEL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSEL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_GOTOPOS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GOTOPOS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#68");
            break;
        case SCI_GOTOLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GOTOLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#69");
            break;
        case SCI_SETCURRENTPOS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCURRENTPOS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#70");
            break;
        case SCI_GETCURRENTPOS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCURRENTPOS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#71");
            break;
        case SCI_SETANCHOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETANCHOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#72");
            break;
        case SCI_GETANCHOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETANCHOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#73");
            break;
        case SCI_SETSELECTIONSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELECTIONSTART");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#74");
            break;
        case SCI_GETSELECTIONSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELECTIONSTART");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#75");
            break;
        case SCI_SETSELECTIONEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELECTIONEND");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#76");
            break;
        case SCI_GETSELECTIONEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELECTIONEND");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#77");
            break;
        case SCI_SETEMPTYSELECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETEMPTYSELECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#78");
            break;
        case SCI_SELECTALL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SELECTALL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#79");
            break;
        case SCI_LINEFROMPOSITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_LINEFROMPOSITION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#80");
            break;
        case SCI_POSITIONFROMLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_POSITIONFROMLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#81");
            break;
        case SCI_GETLINEENDPOSITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLINEENDPOSITION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#82");
            break;
        case SCI_LINELENGTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_LINELENGTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#83");
            break;
        case SCI_GETCOLUMN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCOLUMN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#84");
            break;
        case SCI_FINDCOLUMN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_FINDCOLUMN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#85");
            break;
        case SCI_POSITIONFROMPOINT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_POSITIONFROMPOINT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#86");
            break;
        case SCI_POSITIONFROMPOINTCLOSE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_POSITIONFROMPOINTCLOSE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#87");
            break;
        case SCI_CHARPOSITIONFROMPOINT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CHARPOSITIONFROMPOINT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#88");
            break;
        case SCI_CHARPOSITIONFROMPOINTCLOSE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CHARPOSITIONFROMPOINTCLOSE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#89");
            break;
        case SCI_POINTXFROMPOSITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_POINTXFROMPOSITION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_POINTYFROMPOSITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_POINTYFROMPOSITION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_HIDESELECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_HIDESELECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#90");
            break;
        case SCI_GETSELTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#91");
            break;
        case SCI_GETCURLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCURLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#92");
            break;
        case SCI_SELECTIONISRECTANGLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SELECTIONISRECTANGLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#93");
            break;
        case SCI_SETSELECTIONMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELECTIONMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#94");
            break;
        case SCI_GETSELECTIONMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELECTIONMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#95");
            break;
        case SCI_GETLINESELSTARTPOSITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLINESELSTARTPOSITION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#96");
            break;
        case SCI_GETLINESELENDPOSITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLINESELENDPOSITION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#97");
            break;
        case SCI_MOVECARETINSIDEVIEW:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MOVECARETINSIDEVIEW");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#98");
            break;
        case SCI_WORDENDPOSITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_WORDENDPOSITION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#99");
            break;
        case SCI_WORDSTARTPOSITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_WORDSTARTPOSITION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#100");
            break;
        case SCI_POSITIONBEFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_POSITIONBEFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#101");
            break;
        case SCI_POSITIONAFTER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_POSITIONAFTER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#102");
            break;
        case SCI_COUNTCHARACTERS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_COUNTCHARACTERS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#103");
            break;
        case SCI_TEXTWIDTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_TEXTWIDTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#104");
            break;
        case SCI_TEXTHEIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_TEXTHEIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#105");
            break;
        case SCI_CHOOSECARETX:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CHOOSECARETX");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#106");
            break;
        case SCI_MOVESELECTEDLINESUP:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MOVESELECTEDLINESUP");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#107");
            break;
        case SCI_MOVESELECTEDLINESDOWN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MOVESELECTEDLINESDOWN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#108");
            break;

        case SCI_MULTIPLESELECTIONANDVIRTUALSPACE:
            m_browser->LoadURL("memory:ScintillaDoc.html#MultipleSelectionAndVirtualSpace");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETMULTIPLESELECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMULTIPLESELECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#109");
            break;
        case SCI_GETMULTIPLESELECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMULTIPLESELECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#110");
            break;
        case SCI_SETADDITIONALSELECTIONTYPING:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETADDITIONALSELECTIONTYPING");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#111");
            break;
        case SCI_GETADDITIONALSELECTIONTYPING:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETADDITIONALSELECTIONTYPING");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#112");
            break;
        case SCI_SETMULTIPASTE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMULTIPASTE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#113");
            break;
        case SCI_GETMULTIPASTE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMULTIPASTE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#114");
            break;
        case SCI_SETVIRTUALSPACEOPTIONS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETVIRTUALSPACEOPTIONS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#115");
            break;
        case SCI_GETVIRTUALSPACEOPTIONS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETVIRTUALSPACEOPTIONS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#116");
            break;
        case SCI_SETRECTANGULARSELECTIONMODIFIER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETRECTANGULARSELECTIONMODIFIER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#117");
            break;
        case SCI_GETRECTANGULARSELECTIONMODIFIER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETRECTANGULARSELECTIONMODIFIER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#118");
            break;
        case SCI_GETSELECTIONS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELECTIONS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#119");
            break;
        case SCI_CLEARSELECTIONS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CLEARSELECTIONS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#120");
            break;
        case SCI_SETSELECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_ADDSELECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ADDSELECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#121");
            break;
        case SCI_SETMAINSELECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMAINSELECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#122");
            break;
        case SCI_GETMAINSELECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMAINSELECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#123");
            break;
        case SCI_SETSELECTIONNCARET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELECTIONNCARET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#124");
            break;
        case SCI_GETSELECTIONNCARET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELECTIONNCARET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#125");
            break;
        case SCI_SETSELECTIONNCARETVIRTUALSPACE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELECTIONNCARETVIRTUALSPACE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#126");
            break;
        case SCI_GETSELECTIONNCARETVIRTUALSPACE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELECTIONNCARETVIRTUALSPACE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#127");
            break;
        case SCI_SETSELECTIONNANCHOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELECTIONNANCHOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#128");
            break;
        case SCI_GETSELECTIONNANCHOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELECTIONNANCHOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#129");
            break;
        case SCI_SETSELECTIONNANCHORVIRTUALSPACE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELECTIONNANCHORVIRTUALSPACE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#130");
            break;
        case SCI_GETSELECTIONNANCHORVIRTUALSPACE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELECTIONNANCHORVIRTUALSPACE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#131");
            break;
        case SCI_SETSELECTIONNSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELECTIONNSTART");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#132");
            break;
        case SCI_GETSELECTIONNSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELECTIONNSTART");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#133");
            break;
        case SCI_SETSELECTIONNEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELECTIONNEND");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#134");
            break;
        case SCI_GETSELECTIONNEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELECTIONNEND");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#135");
            break;
        case SCI_SETRECTANGULARSELECTIONCARET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETRECTANGULARSELECTIONCARET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#136");
            break;
        case SCI_GETRECTANGULARSELECTIONCARET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETRECTANGULARSELECTIONCARET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#137");
            break;
        case SCI_SETRECTANGULARSELECTIONCARETVIRTUALSPACE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETRECTANGULARSELECTIONCARETVIRTUALSPACE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#138");
            break;
        case SCI_GETRECTANGULARSELECTIONCARETVIRTUALSPACE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETRECTANGULARSELECTIONCARETVIRTUALSPACE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#139");
            break;
        case SCI_SETRECTANGULARSELECTIONANCHOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETRECTANGULARSELECTIONANCHOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#140");
            break;
        case SCI_GETRECTANGULARSELECTIONANCHOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETRECTANGULARSELECTIONANCHOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#141");
            break;
        case SCI_SETRECTANGULARSELECTIONANCHORVIRTUALSPACE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETRECTANGULARSELECTIONANCHORVIRTUALSPACE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#142");
            break;
        case SCI_GETRECTANGULARSELECTIONANCHORVIRTUALSPACE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETRECTANGULARSELECTIONANCHORVIRTUALSPACE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#143");
            break;
        case SCI_SETADDITIONALSELALPHA:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETADDITIONALSELALPHA");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#144");
            break;
        case SCI_GETADDITIONALSELALPHA:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETADDITIONALSELALPHA");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#145");
            break;
        case SCI_SETADDITIONALSELFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETADDITIONALSELFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#146");
            break;
        case SCI_SETADDITIONALSELBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETADDITIONALSELBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#147");
            break;
        case SCI_SETADDITIONALCARETFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETADDITIONALCARETFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#148");
            break;
        case SCI_GETADDITIONALCARETFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETADDITIONALCARETFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#149");
            break;
        case SCI_SETADDITIONALCARETSBLINK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETADDITIONALCARETSBLINK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#150");
            break;
        case SCI_GETADDITIONALCARETSBLINK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETADDITIONALCARETSBLINK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#151");
            break;
        case SCI_SETADDITIONALCARETSVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETADDITIONALCARETSVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#152");
            break;
        case SCI_GETADDITIONALCARETSVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETADDITIONALCARETSVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#153");
            break;
        case SCI_SWAPMAINANCHORCARET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SWAPMAINANCHORCARET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#154");
            break;
        case SCI_ROTATESELECTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ROTATESELECTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#155");
            break;
        case SCI_SCROLLINGANDAUTOMATICSCROLLING:
            m_browser->LoadURL("memory:ScintillaDoc.html#ScrollingAndAutomaticScrolling");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_LINESCROLL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_LINESCROLL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#156");
            break;
        case SCI_SCROLLCARET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SCROLLCARET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#157");
            break;
        case SCI_SETXCARETPOLICY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETXCARETPOLICY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#158");
            break;
        case SCI_SETYCARETPOLICY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETYCARETPOLICY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#159");
            break;
        case SCI_SETVISIBLEPOLICY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETVISIBLEPOLICY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#160");
            break;
        case SCI_SETHSCROLLBAR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETHSCROLLBAR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#161");
            break;
        case SCI_GETHSCROLLBAR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETHSCROLLBAR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#162");
            break;
        case SCI_SETVSCROLLBAR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETVSCROLLBAR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#163");
            break;
        case SCI_GETVSCROLLBAR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETVSCROLLBAR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#164");
            break;
        case SCI_GETXOFFSET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETXOFFSET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#165");
            break;
        case SCI_SETXOFFSET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETXOFFSET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#166");
            break;
        case SCI_SETSCROLLWIDTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSCROLLWIDTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#167");
            break;
        case SCI_GETSCROLLWIDTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSCROLLWIDTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#168");
            break;
        case SCI_SETSCROLLWIDTHTRACKING:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSCROLLWIDTHTRACKING");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#169");
            break;
        case SCI_GETSCROLLWIDTHTRACKING:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSCROLLWIDTHTRACKING");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#170");
            break;
        case SCI_SETENDATLASTLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETENDATLASTLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#171");
            break;
        case SCI_GETENDATLASTLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETENDATLASTLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#172");
            break;
        case SCI_WHITESPACE:
            m_browser->LoadURL("memory:ScintillaDoc.html#WhiteSpace");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETVIEWWS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETVIEWWS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#173");
            break;
        case SCI_GETVIEWWS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETVIEWWS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#174");
            break;
        case SCI_SETWHITESPACEFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWHITESPACEFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#175");
            break;
        case SCI_SETWHITESPACEFOREPARM1:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWHITESPACEFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#175");
            break;
        case SCI_SETWHITESPACEFOREPARM2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWHITESPACEFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#175");
            break;
        case SCI_SETWHITESPACEBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWHITESPACEBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#176");
            break;
        case SCI_SETWHITESPACEBACKPARM1:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWHITESPACEBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#176");
            break;
        case SCI_SETWHITESPACEBACKPARM2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWHITESPACEBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#176");
            break;
        case SCI_SETWHITESPACESIZE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWHITESPACESIZE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#177");
            break;
        case SCI_GETWHITESPACESIZE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETWHITESPACESIZE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#178");
            break;
        case SCI_SETEXTRAASCENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETEXTRAASCENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#179");
            break;
        case SCI_GETEXTRAASCENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETEXTRAASCENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#180");
            break;
        case SCI_SETEXTRADESCENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETEXTRADESCENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#181");
            break;
        case SCI_GETEXTRADESCENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETEXTRADESCENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#182");
            break;
        case SCI_CURSOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#Cursor");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETCURSOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCURSOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#183");
            break;
        case SCI_GETCURSOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCURSOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#184");
            break;
        case SCI_MOUSECAPTURE:
            m_browser->LoadURL("memory:ScintillaDoc.html#MouseCapture");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_LINEENDINGS:
            m_browser->LoadURL("memory:ScintillaDoc.html#LineEndings");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETMOUSEDOWNCAPTURES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMOUSEDOWNCAPTURES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#185");
            break;
        case SCI_GETMOUSEDOWNCAPTURES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMOUSEDOWNCAPTURES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#186");
            break;
        case SCI_SETEOLMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETEOLMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#187");
            break;
        case SCI_GETEOLMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETEOLMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#188");
            break;
        case SCI_CONVERTEOLS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CONVERTEOLS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#189");
            break;
        case SCI_SETVIEWEOL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETVIEWEOL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#190");
            break;
        case SCI_GETVIEWEOL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETVIEWEOL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#191");
            break;
        case SCI_STYLING:
            m_browser->LoadURL("memory:ScintillaDoc.html#Styling");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_GETENDSTYLED:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETENDSTYLED");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#192");
            break;
        case SCI_STARTSTYLING:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STARTSTYLING");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#193");
            break;
        case SCI_SETSTYLING:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSTYLING");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#194");
            break;
        case SCI_SETSTYLINGEX:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSTYLINGEX");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#195");
            break;
        case SCI_SETLINESTATE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETLINESTATE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#196");
            break;
        case SCI_GETLINESTATE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLINESTATE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#197");
            break;
        case SCI_GETMAXLINESTATE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMAXLINESTATE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#198");
            break;
        case SCI_STYLEDEFINITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#StyleDefinition");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_STYLERESETDEFAULT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLERESETDEFAULT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#199");
            break;
        case SCI_STYLECLEARALL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLECLEARALL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#200");
            break;
        case SCI_STYLESETFONT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETFONT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#201");
            break;
        case SCI_STYLEGETFONT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETFONT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#202");
            break;
        case SCI_STYLESETSIZE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETSIZE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#203");
            break;
        case SCI_STYLEGETSIZE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETSIZE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#204");
            break;
        case SCI_STYLESETSIZEFRACTIONAL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETSIZEFRACTIONAL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#205");
            break;
        case SCI_STYLEGETSIZEFRACTIONAL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETSIZEFRACTIONAL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#206");
            break;
        case SCI_STYLESETBOLD:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETBOLD");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#207");
            break;
        case SCI_STYLEGETBOLD:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETBOLD");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#208");
            break;
        case SCI_STYLESETWEIGHT2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETWEIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#209");
            break;
        case SCI_STYLESETWEIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETWEIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#209");
            break;
        case SCI_STYLEGETWEIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETWEIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#210");
            break;
        case SCI_STYLESETITALIC:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETITALIC");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#211");
            break;
        case SCI_STYLEGETITALIC:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETITALIC");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#212");
            break;
        case SCI_STYLESETUNDERLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETUNDERLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#213");
            break;
        case SCI_STYLEGETUNDERLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETUNDERLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#214");
            break;
        case SCI_STYLESETFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#215");
            break;
        case SCI_STYLEGETFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#216");
            break;
        case SCI_STYLESETBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#217");
            break;
        case SCI_STYLEGETBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#218");
            break;
        case SCI_STYLESETEOLFILLED:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETEOLFILLED");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#219");
            break;
        case SCI_STYLEGETEOLFILLED:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETEOLFILLED");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#220");
            break;
        case SCI_STYLESETCHARACTERSET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETCHARACTERSET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_STYLEGETCHARACTERSET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETCHARACTERSET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#221");
            break;
        case SCI_STYLESETCASE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETCASE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#222");
            break;
        case SCI_STYLEGETCASE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETCASE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#223");
            break;
        case SCI_STYLESETVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#224");
            break;
        case SCI_STYLEGETVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#225");
            break;
        case SCI_STYLESETCHANGEABLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETCHANGEABLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#226");
            break;
        case SCI_STYLEGETCHANGEABLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETCHANGEABLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#227");
            break;
        case SCI_STYLESETHOTSPOT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLESETHOTSPOT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#228");
            break;
        case SCI_STYLEGETHOTSPOT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STYLEGETHOTSPOT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#229");
            break;
        case SCI_CARETSELECTIONANDHOTSPOTSTYLES:
            m_browser->LoadURL("memory:ScintillaDoc.html#CaretAndSelectionStyles");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETSELFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#230");
            break;
        case SCI_SETSELFOREPARM1:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#230");
            break;
        case SCI_SETSELFOREPARM2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#230");
            break;
        case SCI_SETSELBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#231");
            break;
        case SCI_SETSELBACKPARM1:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#231");
            break;
        case SCI_SETSELBACKPARM2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#231");
            break;
        case SCI_SETSELALPHA:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELALPHA");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#232");
            break;
        case SCI_GETSELALPHA:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELALPHA");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#233");
            break;
        case SCI_SETSELEOLFILLED:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETSELEOLFILLED");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#234");
            break;
        case SCI_GETSELEOLFILLED:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSELEOLFILLED");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#235");
            break;
        case SCI_SETCARETFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCARETFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#236");
            break;
        case SCI_GETCARETFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCARETFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#237");
            break;
        case SCI_SETCARETLINEVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCARETLINEVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#238");
            break;
        case SCI_GETCARETLINEVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCARETLINEVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#239");
            break;
        case SCI_SETCARETLINEBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCARETLINEBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#240");
            break;
        case SCI_GETCARETLINEBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCARETLINEBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#241");
            break;
        case SCI_SETCARETLINEBACKALPHA:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCARETLINEBACKALPHA");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#242");
            break;
        case SCI_GETCARETLINEBACKALPHA:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCARETLINEBACKALPHA");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#243");
            break;
        case SCI_SETCARETPERIOD:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCARETPERIOD");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#244");
            break;
        case SCI_GETCARETPERIOD:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCARETPERIOD");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#245");
            break;
        case SCI_SETCARETSTYLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCARETSTYLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#246");
            break;
        case SCI_GETCARETSTYLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCARETSTYLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#247");
            break;
        case SCI_SETCARETWIDTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCARETWIDTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#248");
            break;
        case SCI_GETCARETWIDTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCARETWIDTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#249");
            break;
        case SCI_SETHOTSPOTACTIVEFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETHOTSPOTACTIVEFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#250");
            break;
        case SCI_SETHOTSPOTACTIVEFOREPARM1:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETHOTSPOTACTIVEFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#250");
            break;
        case SCI_SETHOTSPOTACTIVEFOREPARM2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETHOTSPOTACTIVEFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#250");
            break;
        case SCI_GETHOTSPOTACTIVEFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETHOTSPOTACTIVEFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#251");
            break;
        case SCI_SETHOTSPOTACTIVEBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETHOTSPOTACTIVEBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#252");
            break;
        case SCI_SETHOTSPOTACTIVEBACKPARM1:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETHOTSPOTACTIVEBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#252");
            break;
        case SCI_SETHOTSPOTACTIVEBACKPARM2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETHOTSPOTACTIVEBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#252");
            break;
        case SCI_GETHOTSPOTACTIVEBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETHOTSPOTACTIVEBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#253");
            break;
        case SCI_SETHOTSPOTACTIVEUNDERLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETHOTSPOTACTIVEUNDERLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#254");
            break;
        case SCI_GETHOTSPOTACTIVEUNDERLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETHOTSPOTACTIVEUNDERLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#255");
            break;
        case SCI_SETHOTSPOTSINGLELINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETHOTSPOTSINGLELINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#256");
            break;
        case SCI_GETHOTSPOTSINGLELINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETHOTSPOTSINGLELINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#257");
            break;
        case SCI_SETCONTROLCHARSYMBOL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCONTROLCHARSYMBOL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#258");
            break;
        case SCI_GETCONTROLCHARSYMBOL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCONTROLCHARSYMBOL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#259");
            break;
        case SCI_SETCARETSTICKY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCARETSTICKY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#260");
            break;
        case SCI_GETCARETSTICKY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCARETSTICKY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#261");
            break;
        case SCI_TOGGLECARETSTICKY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_TOGGLECARETSTICKY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#262");
            break;
        case SCI_MARGINS:
            m_browser->LoadURL("memory:ScintillaDoc.html#Margins");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETMARGINTYPEN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMARGINTYPEN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#263");
            break;
        case SCI_GETMARGINTYPEN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMARGINTYPEN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#264");
            break;
        case SCI_SETMARGINWIDTHN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMARGINWIDTHN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#265");
            break;
        case SCI_GETMARGINWIDTHN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMARGINWIDTHN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#266");
            break;
        case SCI_SETMARGINMASKN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMARGINMASKN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#267");
            break;
        case SCI_SETMARGINMASKN2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMARGINMASKN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#267");
            break;
        case SCI_GETMARGINMASKN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMARGINMASKN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#268");
            break;
        case SCI_SETMARGINSENSITIVEN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMARGINSENSITIVEN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#269");
            break;
        case SCI_GETMARGINSENSITIVEN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMARGINSENSITIVEN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#270");
            break;
        case SCI_SETMARGINCURSORN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMARGINCURSORN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#271");
            break;
        case SCI_GETMARGINCURSORN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMARGINCURSORN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#272");
            break;
        case SCI_SETMARGINLEFT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMARGINLEFT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#273");
            break;
        case SCI_GETMARGINLEFT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMARGINLEFT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#274");
            break;
        case SCI_SETMARGINRIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMARGINRIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#275");
            break;
        case SCI_GETMARGINRIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMARGINRIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#276");
            break;
        case SCI_SETFOLDMARGINCOLOUR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFOLDMARGINCOLOUR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#277");
            break;
        case SCI_SETFOLDMARGINCOLOURPARM1:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFOLDMARGINCOLOUR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#277");
            break;
        case SCI_SETFOLDMARGINCOLOURPARM2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFOLDMARGINCOLOUR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#277");
            break;
        case SCI_SETFOLDMARGINHICOLOUR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFOLDMARGINHICOLOUR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#278");
            break;
        case SCI_SETFOLDMARGINHICOLOURPARM1:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFOLDMARGINHICOLOUR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#278");
            break;
        case SCI_SETFOLDMARGINHICOLOURPARM2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFOLDMARGINHICOLOUR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#278");
            break;
        case SCI_MARGINSETTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARGINSETTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#279");
            break;
        case SCI_MARGINGETTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARGINGETTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#280");
            break;
        case SCI_MARGINSETSTYLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARGINSETSTYLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#281");
            break;
        case SCI_MARGINGETSTYLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARGINGETSTYLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#282");
            break;
        case SCI_MARGINSETSTYLES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARGINSETSTYLES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#283");
            break;
        case SCI_MARGINGETSTYLES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARGINGETSTYLES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#284");
            break;
        case SCI_MARGINTEXTCLEARALL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARGINTEXTCLEARALL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#285");
            break;
        case SCI_MARGINSETSTYLEOFFSET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARGINSETSTYLEOFFSET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#286");
            break;
        case SCI_MARGINGETSTYLEOFFSET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARGINGETSTYLEOFFSET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#287");
            break;
        case SCI_SETMARGINOPTIONS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMARGINOPTIONS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#288");
            break;
        case SCI_GETMARGINOPTIONS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMARGINOPTIONS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#289");
            break;
        case SCI_ANNOTATIONS:
            m_browser->LoadURL("memory:ScintillaDoc.html#Annotations");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_ANNOTATIONSETTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONSETTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#290");
            break;
        case SCI_ANNOTATIONGETTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONGETTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#291");
            break;
        case SCI_ANNOTATIONSETSTYLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONSETSTYLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#292");
            break;
        case SCI_ANNOTATIONGETSTYLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONGETSTYLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#293");
            break;
        case SCI_ANNOTATIONSETSTYLES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONSETSTYLES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#294");
            break;
        case SCI_ANNOTATIONGETSTYLES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONGETSTYLES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#295");
            break;
        case SCI_ANNOTATIONGETLINES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONGETLINES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#296");
            break;
        case SCI_ANNOTATIONCLEARALL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONCLEARALL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#297");
            break;
        case SCI_ANNOTATIONSETVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONSETVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#298");
            break;
        case SCI_ANNOTATIONGETVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONGETVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#299");
            break;
        case SCI_ANNOTATIONSETSTYLEOFFSET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONSETSTYLEOFFSET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#300");
            break;
        case SCI_ANNOTATIONGETSTYLEOFFSET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ANNOTATIONGETSTYLEOFFSET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#301");
            break;
        case SCI_OTHERSETTINGS:
            m_browser->LoadURL("memory:ScintillaDoc.html#OtherSettings");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETUSEPALETTE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETUSEPALETTE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_GETUSEPALETTE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETUSEPALETTE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETBUFFEREDDRAW:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETBUFFEREDDRAW");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#302");
            break;
        case SCI_GETBUFFEREDDRAW:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETBUFFEREDDRAW");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#303");
            break;
        case SCI_SETTWOPHASEDRAW:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETTWOPHASEDRAW");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#304");
            break;
        case SCI_GETTWOPHASEDRAW:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETTWOPHASEDRAW");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#305");
            break;
        case SCI_SETTECHNOLOGY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETTECHNOLOGY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#306");
            break;
        case SCI_GETTECHNOLOGY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETTECHNOLOGY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#307");
            break;
        case SCI_SETFONTQUALITY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFONTQUALITY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_GETFONTQUALITY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETFONTQUALITY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETCODEPAGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCODEPAGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#308");
            break;
        case SCI_GETCODEPAGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCODEPAGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#309");
            break;
        case SCI_SETKEYSUNICODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETKEYSUNICODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#310");
            break;
        case SCI_GETKEYSUNICODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETKEYSUNICODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#311");
            break;
        case SCI_SETWORDCHARS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWORDCHARS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#312");
            break;
        case SCI_GETWORDCHARS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETWORDCHARS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#313");
            break;
        case SCI_SETWHITESPACECHARS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWHITESPACECHARS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#314");
            break;
        case SCI_GETWHITESPACECHARS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETWHITESPACECHARS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#315");
            break;
        case SCI_SETPUNCTUATIONCHARS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETPUNCTUATIONCHARS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#316");
            break;
        case SCI_GETPUNCTUATIONCHARS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETPUNCTUATIONCHARS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#317");
            break;
        case SCI_SETCHARSDEFAULT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETCHARSDEFAULT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#318");
            break;
        case SCI_GRABFOCUS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GRABFOCUS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETFOCUS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFOCUS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#319");
            break;
        case SCI_GETFOCUS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETFOCUS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#320");
            break;

        case SCI_BRACEHIGHLIGHTING:
            m_browser->LoadURL("memory:ScintillaDoc.html#BraceHighlighting");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_BRACEHIGHLIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_BRACEHIGHLIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#321");
            break;
        case SCI_BRACEBADLIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_BRACEBADLIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#322");
            break;
        case SCI_BRACEHIGHLIGHTINDICATOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_BRACEHIGHLIGHTINDICATOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#323");
            break;
        case SCI_BRACEHIGHLIGHTINDICATORPARM1:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_BRACEHIGHLIGHTINDICATOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#323");
            break;
        case SCI_BRACEHIGHLIGHTINDICATORPARM2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_BRACEHIGHLIGHTINDICATOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#323");
            break;
        case SCI_BRACEBADLIGHTINDICATOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_BRACEBADLIGHTINDICATOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#324");
            break;
        case SCI_BRACEBADLIGHTINDICATORPARM1:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_BRACEBADLIGHTINDICATOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#324");
            break;
        case SCI_BRACEBADLIGHTINDICATORPARM2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_BRACEBADLIGHTINDICATOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#324");
            break;
        case SCI_BRACEMATCH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_BRACEMATCH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#325");
            break;

        case SCI_TABSANDINDENTATIONGUIDES:
            m_browser->LoadURL("memory:ScintillaDoc.html#TabsAndIndentationGuides");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETTABWIDTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETTABWIDTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#326");
            break;
        case SCI_GETTABWIDTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETTABWIDTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#327");
            break;
        case SCI_SETUSETABS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETUSETABS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#328");
            break;
        case SCI_GETUSETABS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETUSETABS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#329");
            break;
        case SCI_SETINDENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETINDENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#330");
            break;
        case SCI_GETINDENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETINDENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#331");
            break;
        case SCI_SETTABINDENTS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETTABINDENTS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#332");
            break;
        case SCI_GETTABINDENTS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETTABINDENTS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#333");
            break;
        case SCI_SETBACKSPACEUNINDENTS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETBACKSPACEUNINDENTS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#334");
            break;
        case SCI_GETBACKSPACEUNINDENTS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETBACKSPACEUNINDENTS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#335");
            break;
        case SCI_SETLINEINDENTATION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETLINEINDENTATION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#336");
            break;
        case SCI_GETLINEINDENTATION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLINEINDENTATION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#337");
            break;
        case SCI_GETLINEINDENTPOSITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLINEINDENTPOSITION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#338");
            break;
        case SCI_SETINDENTATIONGUIDES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETINDENTATIONGUIDES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#339");
            break;
        case SCI_GETINDENTATIONGUIDES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETINDENTATIONGUIDES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#340");
            break;
        case SCI_SETHIGHLIGHTGUIDE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETHIGHLIGHTGUIDE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#341");
            break;
        case SCI_GETHIGHLIGHTGUIDE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETHIGHLIGHTGUIDE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#342");
            break;
        case SCI_MARKERS:
            m_browser->LoadURL("memory:ScintillaDoc.html#Markers");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_MARKERDEFINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERDEFINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#343");
            break;

        case SCI_MARKERDEFINECHARACTER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERDEFINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#343");
            break;



        case SCI_MARKERDEFINEPIXMAP:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERDEFINEPIXMAP");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#344");
            break;
        case SCI_RGBAIMAGESETWIDTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_RGBAIMAGESETWIDTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#345");
            break;
        case SCI_RGBAIMAGESETHEIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_RGBAIMAGESETHEIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#346");
            break;
        case SCI_MARKERDEFINERGBAIMAGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERDEFINERGBAIMAGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#347");
            break;
        case SCI_MARKERSYMBOLDEFINED:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERSYMBOLDEFINED");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#348");
            break;
        case SCI_MARKERSETFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERSETFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#349");
            break;
        case SCI_MARKERSETBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERSETBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#350");
            break;
        case SCI_MARKERSETBACKSELECTED:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERSETBACKSELECTED");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#351");
            break;
        case SCI_MARKERENABLEHIGHLIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERENABLEHIGHLIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#352");
            break;
        case SCI_MARKERSETALPHA:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERSETALPHA");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#353");
            break;
        case SCI_MARKERDEFINEALT:
            m_browser->LoadURL("memory:ScintillaDoc.html#Markers");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_MARKERDEFINEPIXMAP2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERDEFINEPIXMAP");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#344");
            break;
        case SCI_MARKERADD:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERADD");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#354");
            break;
        case SCI_MARKERADDSET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERADDSET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#355");
            break;
        case SCI_MARKERDELETE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERDELETE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#356");
            break;
        case SCI_MARKERDELETEALL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERDELETEALL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#357");
            break;
        case SCI_MARKERGET:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERGET");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#358");
            break;
        case SCI_MARKERNEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERNEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#359");
            break;
        case SCI_MARKERPREVIOUS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERPREVIOUS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#360");
            break;
        case SCI_MARKERLINEFROMHANDLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERLINEFROMHANDLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#361");
            break;
        case SCI_MARKERDELETEHANDLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_MARKERDELETEHANDLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#362");
            break;
        case SCI_INDICATORS:
            m_browser->LoadURL("memory:ScintillaDoc.html#Indicators");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_INDICSETSTYLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICSETSTYLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#363");
            break;
        case SCI_INDICGETSTYLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICGETSTYLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#364");
            break;
        case SCI_INDICSETFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICSETFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#365");
            break;
        case SCI_INDICGETFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICGETFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#366");
            break;
        case SCI_INDICSETALPHA:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICSETALPHA");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#367");
            break;
        case SCI_INDICGETALPHA:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICGETALPHA");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#368");
            break;
        case SCI_INDICSETOUTLINEALPHA:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICSETOUTLINEALPHA");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#369");
            break;
        case SCI_INDICGETOUTLINEALPHA:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICGETOUTLINEALPHA");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#370");
            break;
        case SCI_INDICSETUNDER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICSETUNDER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#371");
            break;
        case SCI_INDICGETUNDER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICGETUNDER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#372");
            break;
        case SCI_MODERNINDICATORS:
            m_browser->LoadURL("memory:ScintillaDoc.html#ModernIndicators");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETINDICATORCURRENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETINDICATORCURRENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#373");
            break;
        case SCI_GETINDICATORCURRENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETINDICATORCURRENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#374");
            break;
        case SCI_AUTOCOMPLETION:
            m_browser->LoadURL("memory:ScintillaDoc.html#Autocompletion");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETINDICATORVALUE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETINDICATORVALUE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#375");
            break;
        case SCI_GETINDICATORVALUE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETINDICATORVALUE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#376");
            break;
        case SCI_INDICATORFILLRANGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICATORFILLRANGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#377");
            break;
        case SCI_INDICATORCLEARRANGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICATORCLEARRANGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#378");
            break;
        case SCI_INDICATORALLONFOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICATORALLONFOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#379");
            break;
        case SCI_INDICATORVALUEAT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICATORVALUEAT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#380");
            break;
        case SCI_INDICATORSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICATORSTART");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#381");
            break;
        case SCI_INDICATOREND:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_INDICATOREND");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#382");
            break;
        case SCI_OSXFINDINDICATOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#FindIndicators");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_FINDINDICATORSHOW:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_FINDINDICATORSHOW");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_FINDINDICATORFLASH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_FINDINDICATORFLASH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_FINDINDICATORHIDE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_FINDINDICATORHIDE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_AUTOCSHOW:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSHOW");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#383");
            break;
        case SCI_AUTOCCANCEL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCCANCEL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#384");
            break;
        case SCI_AUTOCACTIVE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCACTIVE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#385");
            break;
        case SCI_AUTOCPOSSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCPOSSTART");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#386");
            break;
        case SCI_AUTOCCOMPLETE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCCOMPLETE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#387");
            break;
        case SCI_AUTOCSTOPS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSTOPS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#388");
            break;
        case SCI_AUTOCSETSEPARATOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSETSEPARATOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#389");
            break;
        case SCI_AUTOCGETSEPARATOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETSEPARATOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#390");
            break;
        case SCI_AUTOCSELECT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSELECT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#391");
            break;
        case SCI_AUTOCGETCURRENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETCURRENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#392");
            break;
        case SCI_AUTOCGETCURRENTTEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETCURRENTTEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_AUTOCSETCANCELATSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSETCANCELATSTART");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#393");
            break;
        case SCI_AUTOCGETCANCELATSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETCANCELATSTART");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#394");
            break;
        case SCI_AUTOCSETFILLUPS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSETFILLUPS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#395");
            break;
        case SCI_AUTOCSETCHOOSESINGLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSETCHOOSESINGLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#396");
            break;
        case SCI_AUTOCGETCHOOSESINGLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETCHOOSESINGLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#397");
            break;
        case SCI_AUTOCSETIGNORECASE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSETIGNORECASE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#398");
            break;
        case SCI_AUTOCGETIGNORECASE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETIGNORECASE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#399");
            break;
        case SCI_AUTOCSETCASEINSENSITIVEBEHAVIOUR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSETCASEINSENSITIVEBEHAVIOUR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#400");
            break;
        case SCI_AUTOCGETCASEINSENSITIVEBEHAVIOUR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETCASEINSENSITIVEBEHAVIOUR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#401");
            break;
        case SCI_AUTOCSETAUTOHIDE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSETAUTOHIDE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#402");
            break;
        case SCI_AUTOCGETAUTOHIDE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETAUTOHIDE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#403");
            break;
        case SCI_AUTOCSETDROPRESTOFWORD:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSETDROPRESTOFWORD");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#404");
            break;
        case SCI_AUTOCGETDROPRESTOFWORD:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETDROPRESTOFWORD");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#405");
            break;
        case SCI_REGISTERIMAGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_REGISTERIMAGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#406");
            break;
        case SCI_REGISTERRGBAIMAGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_REGISTERRGBAIMAGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#407");
            break;
        case SCI_CLEARREGISTEREDIMAGES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CLEARREGISTEREDIMAGES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#408");
            break;
        case SCI_AUTOCSETTYPESEPARATOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSETTYPESEPARATOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#409");
            break;
        case SCI_AUTOCGETTYPESEPARATOR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETTYPESEPARATOR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#410");
            break;
        case SCI_AUTOCSETMAXHEIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSETMAXHEIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#411");
            break;
        case SCI_AUTOCGETMAXHEIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETMAXHEIGHT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#412");
            break;
        case SCI_AUTOCSETMAXWIDTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCSETMAXWIDTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#413");
            break;
        case SCI_AUTOCGETMAXWIDTH:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_AUTOCGETMAXWIDTH");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#414");
            break;

        case SCI_REGISTERIMAGE2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_REGISTERIMAGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#406");
            break;

        case SCI_USERLISTS:
            m_browser->LoadURL("memory:ScintillaDoc.html#UserLists");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_USERLISTSHOW:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_USERLISTSHOW");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#415");
            break;
        case SCI_CALLTIPS:
            m_browser->LoadURL("memory:ScintillaDoc.html#CallTips");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_CALLTIPSHOW:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CALLTIPSHOW");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#416");
            break;
        case SCI_CALLTIPCANCEL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CALLTIPCANCEL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#417");
            break;
        case SCI_CALLTIPACTIVE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CALLTIPACTIVE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#418");
            break;
        case SCI_CALLTIPPOSSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CALLTIPPOSSTART");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#419");
            break;
        case SCI_CALLTIPSETHLT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CALLTIPSETHLT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#420");
            break;
        case SCI_CALLTIPSETBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CALLTIPSETBACK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#421");
            break;
        case SCI_CALLTIPSETFORE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CALLTIPSETFORE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#422");
            break;
        case SCI_CALLTIPSETFOREHLT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CALLTIPSETFOREHLT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#423");
            break;
        case SCI_CALLTIPUSESTYLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CALLTIPUSESTYLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#424");
            break;
        case SCI_CALLTIPSETPOSITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CALLTIPSETPOSITION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#425");
            break;
        case SCI_KEYBOARDCOMMANDS:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;

        case SCI_LINEDOWN:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#426");
            break;
        case SCI_LINEDOWNEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#427");
            break;
        case SCI_LINEDOWNRECTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#428");
            break;
        case SCI_LINESCROLLDOWN:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#429");
            break;
        case SCI_LINEUP:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#430");
            break;
        case SCI_LINEUPEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#431");
            break;
        case SCI_LINEUPRECTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#432");
            break;
        case SCI_LINESCROLLUP:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#433");
            break;
        case SCI_PARADOWN:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#434");
            break;
        case SCI_PARADOWNEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#435");
            break;
        case SCI_PARAUP:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#436");
            break;
        case SCI_PARAUPEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#437");
            break;
        case SCI_CHARLEFT:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#438");
            break;
        case SCI_CHARLEFTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#439");
            break;
        case SCI_CHARLEFTRECTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#440");
            break;
        case SCI_CHARRIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#441");
            break;
        case SCI_CHARRIGHTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#442");
            break;
        case SCI_CHARRIGHTRECTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#443");
            break;
        case SCI_WORDLEFT:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#444");
            break;
        case SCI_WORDLEFTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#445");
            break;
        case SCI_WORDRIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#446");
            break;
        case SCI_WORDRIGHTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#447");
            break;
        case SCI_WORDLEFTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#448");
            break;
        case SCI_WORDLEFTENDEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#449");
            break;
        case SCI_WORDRIGHTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#450");
            break;
        case SCI_WORDRIGHTENDEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#451");
            break;
        case SCI_WORDPARTLEFT:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#452");
            break;
        case SCI_WORDPARTLEFTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#453");
            break;
        case SCI_WORDPARTRIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#454");
            break;
        case SCI_WORDPARTRIGHTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#455");
            break;
        case SCI_HOME:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#456");
            break;
        case SCI_HOMEEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#457");
            break;
        case SCI_HOMERECTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#458");
            break;
        case SCI_HOMEDISPLAY:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#459");
            break;
        case SCI_HOMEDISPLAYEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#460");
            break;
        case SCI_HOMEWRAP:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#461");
            break;
        case SCI_HOMEWRAPEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#462");
            break;
        case SCI_VCHOME:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#463");
            break;
        case SCI_VCHOMEEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#464");
            break;
        case SCI_VCHOMERECTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#465");
            break;
        case SCI_VCHOMEWRAP:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#466");
            break;
        case SCI_VCHOMEWRAPEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#467");
            break;
        case SCI_LINEEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#468");
            break;
        case SCI_LINEENDEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#469");
            break;
        case SCI_LINEENDRECTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#470");
            break;
        case SCI_LINEENDDISPLAY:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#471");
            break;
        case SCI_LINEENDDISPLAYEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#472");
            break;
        case SCI_LINEENDWRAP:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#473");
            break;
        case SCI_LINEENDWRAPEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#474");
            break;
        case SCI_DOCUMENTSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#475");
            break;
        case SCI_DOCUMENTSTARTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#476");
            break;
        case SCI_DOCUMENTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#477");
            break;
        case SCI_DOCUMENTENDEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#478");
            break;
        case SCI_PAGEUP:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#479");
            break;
        case SCI_PAGEUPEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#480");
            break;
        case SCI_PAGEUPRECTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#481");
            break;
        case SCI_PAGEDOWN:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#482");
            break;
        case SCI_PAGEDOWNEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#483");
            break;
        case SCI_PAGEDOWNRECTEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#484");
            break;
        case SCI_STUTTEREDPAGEUP:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#485");
            break;
        case SCI_STUTTEREDPAGEUPEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#486");
            break;
        case SCI_STUTTEREDPAGEDOWN:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#487");
            break;
        case SCI_STUTTEREDPAGEDOWNEXTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#488");
            break;
        case SCI_DELETEBACK:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#489");
            break;
        case SCI_DELETEBACKNOTLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#490");
            break;
        case SCI_DELWORDLEFT:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#491");
            break;
        case SCI_DELWORDRIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#492");
            break;
        case SCI_DELWORDRIGHTEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#493");
            break;
        case SCI_DELLINELEFT:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#494");
            break;
        case SCI_DELLINERIGHT:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#495");
            break;
        case SCI_LINEDELETE:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#496");
            break;
        case SCI_LINECUT:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#497");
            break;
        case SCI_LINECOPY:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#498");
            break;
        case SCI_LINETRANSPOSE:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#499");
            break;
        case SCI_LINEDUPLICATE:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#500");
            break;
        case SCI_LOWERCASE:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#501");
            break;
        case SCI_UPPERCASE:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#502");
            break;
        case SCI_CANCEL:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#503");
            break;
        case SCI_EDITTOGGLEOVERTYPE:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#504");
            break;
        case SCI_NEWLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#505");
            break;
        case SCI_FORMFEED:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#506");
            break;
        case SCI_TAB:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#507");
            break;
        case SCI_BACKTAB:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#508");
            break;
        case SCI_SELECTIONDUPLICATE:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#509");
            break;
        case SCI_VERTICALCENTRECARET:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#510");
            break;
        case SCI_SCROLLTOSTART:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#513");
            break;
        case SCI_SCROLLTOEND:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyboardCommands");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#514");
            break;

        case SCI_KEYBINDINGS:
            m_browser->LoadURL("memory:ScintillaDoc.html#KeyBindings");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_ASSIGNCMDKEY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ASSIGNCMDKEY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#515");
            break;
        case SCI_ASSIGNCMDKEY2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ASSIGNCMDKEY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#515");
            break;
        case SCI_ASSIGNCMDKEY3:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ASSIGNCMDKEY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#515");
            break;
        case SCI_ASSIGNCMDKEY4:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ASSIGNCMDKEY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#515");
            break;
        case SCI_CLEARCMDKEY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CLEARCMDKEY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#516");
            break;
        case SCI_CLEARALLCMDKEYS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CLEARALLCMDKEYS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#517");
            break;
        case SCI_NULL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_NULL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_POPUPEDITMENU:
            m_browser->LoadURL("memory:ScintillaDoc.html#PopupEditMenu");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_USEPOPUP:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_USEPOPUP");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#518");
            break;
        case SCI_MACRORECORDING:
            m_browser->LoadURL("memory:ScintillaDoc.html#MacroRecording");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_STARTRECORD:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STARTRECORD");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#519");
            break;
        case SCI_STOPRECORD:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_STOPRECORD");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#520");
            break;
        case SCI_PRINTING:
            m_browser->LoadURL("memory:ScintillaDoc.html#Printing");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_FORMATRANGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_FORMATRANGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#521");
            break;
        case SCI_SETPRINTMAGNIFICATION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETPRINTMAGNIFICATION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#522");
            break;
        case SCI_GETPRINTMAGNIFICATION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETPRINTMAGNIFICATION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#523");
            break;
        case SCI_SETPRINTCOLOURMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETPRINTCOLOURMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#524");
            break;
        case SCI_GETPRINTCOLOURMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETPRINTCOLOURMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#525");
            break;
        case SCI_SETPRINTWRAPMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETPRINTWRAPMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#526");
            break;
        case SCI_GETPRINTWRAPMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETPRINTWRAPMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#527");
            break;
        case SCI_DIRECTACCESS:
            m_browser->LoadURL("memory:ScintillaDoc.html#DirectAccess");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_GETDIRECTFUNCTION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETDIRECTFUNCTION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_GETDIRECTPOINTER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETDIRECTPOINTER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_GETCHARACTERPOINTER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETCHARACTERPOINTER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#528");
            break;
        case SCI_GETRANGEPOINTER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETRANGEPOINTER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#529");
            break;
        case SCI_GETGAPPOSITION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETGAPPOSITION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#530");
            break;
        case SCI_MULTIPLEVIEWS:
            m_browser->LoadURL("memory:ScintillaDoc.html#MultipleViews");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_GETDOCPOINTER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETDOCPOINTER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#531");
            break;
        case SCI_SETDOCPOINTER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETDOCPOINTER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#532");
            break;
        case SCI_CREATEDOCUMENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CREATEDOCUMENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#533");
            break;
        case SCI_ADDREFDOCUMENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ADDREFDOCUMENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#534");
            break;
        case SCI_RELEASEDOCUMENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_RELEASEDOCUMENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#535");
            break;
        case SCI_BACKGROUNDLOADINGANDSAVING:
            m_browser->LoadURL("memory:ScintillaDoc.html#BackgroundLoadSave");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_CREATELOADER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CREATELOADER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#536");
            break;
        case SCI_FOLDING:
            m_browser->LoadURL("memory:ScintillaDoc.html#Folding");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_VISIBLEFROMDOCLINE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_VISIBLEFROMDOCLINE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#537");
            break;
        case SCI_DOCLINEFROMVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_DOCLINEFROMVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#538");
            break;
        case SCI_SHOWLINES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SHOWLINES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#539");
            break;
        case SCI_HIDELINES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_HIDELINES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#540");
            break;
        case SCI_GETLINEVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLINEVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#541");
            break;
        case SCI_GETALLLINESVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETALLLINESVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#542");
            break;
        case SCI_SETFOLDLEVEL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFOLDLEVEL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#543");
            break;
        case SCI_GETFOLDLEVEL:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETFOLDLEVEL");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#544");
            break;
        case SCI_SETFOLDFLAGS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFOLDFLAGS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#545");
            break;
        case SCI_GETLASTCHILD:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLASTCHILD");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#546");
            break;
        case SCI_GETFOLDPARENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETFOLDPARENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#547");
            break;
        case SCI_SETFOLDEXPANDED:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETFOLDEXPANDED");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#548");
            break;
        case SCI_GETFOLDEXPANDED:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETFOLDEXPANDED");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#549");
            break;
        case SCI_CONTRACTEDFOLDNEXT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CONTRACTEDFOLDNEXT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#550");
            break;
        case SCI_TOGGLEFOLD:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_TOGGLEFOLD");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#551");
            break;
        case SCI_ENSUREVISIBLE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ENSUREVISIBLE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#552");
            break;
        case SCI_ENSUREVISIBLEENFORCEPOLICY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ENSUREVISIBLEENFORCEPOLICY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#553");
            break;
        case SCI_LINEWRAPPING:
            m_browser->LoadURL("memory:ScintillaDoc.html#LineWrapping");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETWRAPMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWRAPMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#554");
            break;
        case SCI_GETWRAPMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETWRAPMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#555");
            break;
        case SCI_SETWRAPVISUALFLAGS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWRAPVISUALFLAGS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#556");
            break;
        case SCI_SETWRAPVISUALFLAGS2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWRAPVISUALFLAGS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#556");
            break;
        case SCI_GETWRAPVISUALFLAGS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETWRAPVISUALFLAGS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#557");
            break;
        case SCI_SETWRAPVISUALFLAGSLOCATION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWRAPVISUALFLAGSLOCATION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#558");
            break;
        case SCI_SETWRAPVISUALFLAGSLOCATION2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWRAPVISUALFLAGSLOCATION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#558");
            break;
        case SCI_GETWRAPVISUALFLAGSLOCATION:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETWRAPVISUALFLAGSLOCATION");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#559");
            break;
        case SCI_SETWRAPINDENTMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWRAPINDENTMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#560");
            break;
        case SCI_GETWRAPINDENTMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETWRAPINDENTMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#561");
            break;
        case SCI_SETWRAPSTARTINDENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETWRAPSTARTINDENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#562");
            break;
        case SCI_GETWRAPSTARTINDENT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETWRAPSTARTINDENT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#563");
            break;
        case SCI_SETLAYOUTCACHE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETLAYOUTCACHE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#564");
            break;
        case SCI_GETLAYOUTCACHE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLAYOUTCACHE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#565");
            break;
        case SCI_SETPOSITIONCACHE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETPOSITIONCACHE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#566");
            break;
        case SCI_GETPOSITIONCACHE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETPOSITIONCACHE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#567");
            break;
        case SCI_LINESSPLIT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_LINESSPLIT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#568");
            break;
        case SCI_LINESJOIN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_LINESJOIN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#569");
            break;
        case SCI_WRAPCOUNT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_WRAPCOUNT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#570");
            break;
        case SCI_ZOOMING:
            m_browser->LoadURL("memory:ScintillaDoc.html#Zooming");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_ZOOMIN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ZOOMIN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#571");
            break;
        case SCI_ZOOMOUT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_ZOOMOUT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#572");
            break;
        case SCI_SETZOOM:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETZOOM");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#573");
            break;
        case SCI_GETZOOM:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETZOOM");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#574");
            break;
        case SCI_LONGLINES:
            m_browser->LoadURL("memory:ScintillaDoc.html#LongLines");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETEDGEMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETEDGEMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#575");
            break;
        case SCI_GETEDGEMODE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETEDGEMODE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#576");
            break;
        case SCI_SETEDGECOLUMN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETEDGECOLUMN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#577");
            break;
        case SCI_GETEDGECOLUMN:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETEDGECOLUMN");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#578");
            break;
        case SCI_SETEDGECOLOUR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETEDGECOLOUR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#579");
            break;
        case SCI_GETEDGECOLOUR:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETEDGECOLOUR");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#580");
            break;
        case SCI_LEXER:
            m_browser->LoadURL("memory:ScintillaDoc.html#Lexer");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETLEXERBOOLPROPERTY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETPROPERTY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#589");
            break;
        case SCI_SETLEXERINTPROPERTY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETPROPERTY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#589");
            break;
        case SCI_SETLEXERSTRINGPROPERTY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETPROPERTY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#589");
            break;
        case SCI_SETLEXER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETLEXER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#581");
            break;
        case SCI_GETLEXER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLEXER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#582");
            break;
        case SCI_SETLEXERLANGUAGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETLEXERLANGUAGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#583");
            break;
        case SCI_GETLEXERLANGUAGE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETLEXERLANGUAGE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_LOADLEXERLIBRARY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_LOADLEXERLIBRARY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_COLOURISE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_COLOURISE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#584");
            break;
        case SCI_CHANGELEXERSTATE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_CHANGELEXERSTATE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#585");
            break;
        case SCI_PROPERTYNAMES:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_PROPERTYNAMES");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#586");
            break;
        case SCI_PROPERTYTYPE:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_PROPERTYTYPE");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#587");
            break;
        case SCI_DESCRIBEPROPERTY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_DESCRIBEPROPERTY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#588");
            break;
        case SCI_SETPROPERTY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETPROPERTY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#589");
            break;
        case SCI_GETPROPERTY:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETPROPERTY");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#590");
            break;
        case SCI_GETPROPERTYEXPANDED:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETPROPERTYEXPANDED");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#591");
            break;
        case SCI_GETPROPERTYINT:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETPROPERTYINT");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#592");
            break;
        case SCI_DESCRIBEKEYWORDSETS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_DESCRIBEKEYWORDSETS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#593");
            break;
        case SCI_SETKEYWORDS:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETKEYWORDS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#594");
            break;
        case SCI_SETKEYWORDS2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETKEYWORDS");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#594");
            break;
        case SCI_GETSTYLEBITSNEEDED:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETSTYLEBITSNEEDED");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#595");
            break;
        case SCI_LEXEROBJECTS:
            m_browser->LoadURL("memory:ScintillaDoc.html#LexerObjects");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_PRIVATELEXERCALL:
            m_browser->LoadURL("memory:ScintillaDoc.html#LexerObjects");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#596");
            break;
        case SCI_NOTIFICATIONS:
            m_browser->LoadURL("memory:ScintillaDoc.html#Notifications");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;
        case SCI_SETMODEVENTMASK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMODEVENTMASK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#597");
            break;
        case SCI_SETMODEVENTMASK2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMODEVENTMASK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#597");
            break;
        case SCI_GETMODEVENTMASK:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMODEVENTMASK");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#598");
            break;
        case SCI_SETMOUSEDWELLTIME:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETMOUSEDWELLTIME");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#599");
            break;
        case SCI_GETMOUSEDWELLTIME:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMOUSEDWELLTIME");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#600");
            break;
        case SCI_SETMOUSEDWELLTIME2:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETMOUSEDWELLTIME");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#600");
            break;
        case SCI_SETIDENTIFIER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_SETIDENTIFIER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#601");
            break;
        case SCI_GETIDENTIFIER:
            m_browser->LoadURL("memory:ScintillaDoc.html#SCI_GETIDENTIFIER");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#602");
            break;





        default:
            m_browser->LoadURL("memory:ScintillaDoc.html");
            m_STCDoc->LoadURL("memory:wxStyledTextCtrl.html#");
            break;

    }

    event.Skip();

}
