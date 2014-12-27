
#include "stcMain.h"
#include <wx/richtext/richtextsymboldlg.h>
//#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include "lexers.h"
#include <wx/dataview.h>
#include "dialogs.h"
#include <wx/wfstream.h>
#include <wx/mstream.h>
#include <wx/file.h>
#include <wx/msgdlg.h>
//#include "12x12/arrow-blue.xpm"

#ifdef MAXULONG_PTR
typedef ULONG_PTR uptr_t;
typedef LONG_PTR sptr_t;
#else
typedef unsigned long uptr_t;
typedef long sptr_t;
#endif

struct Sci_CharacterRange {
	long cpMin;
	long cpMax;
};

struct Sci_TextRange {
	struct Sci_CharacterRange chrg;
	char *lpstrText;
};

#ifdef _WIN32
	#define SCI_METHOD __stdcall
#else
	#define SCI_METHOD
#endif

class ILoader {
public:
        virtual int SCI_METHOD Release() = 0;
        // Returns a status code from SC_STATUS_*
        virtual int SCI_METHOD AddData(char *data, int length) = 0;
        virtual void * SCI_METHOD ConvertToDocument() = 0;
};

void MyProjectMyDialog1::OnPaint( wxPaintEvent& event )
{
    wxPaintDC mydc(m_panel1);
    mydc.DrawBitmap(bm,0,0,true);
};

class MyProjectMyDialog2 : public MyDialog2
{
	public:
	    enum dialogType
	    {
	        SCI_ADDSTYLEDTEXT,
	        SCI_GETSTYLEDTEXT,
	        SCI_SETSTYLINGEX
	    };

		MyProjectMyDialog2( wxWindow* parent,dialogType);
		wxString getStyledText();
		void setStyledText(wxMemoryBuffer&);



	private:
		void onText( wxCommandEvent& event );
		void onCancel( wxCommandEvent& event ){EndModal(wxID_CANCEL);}
		void onOK( wxCommandEvent& event ){EndModal(wxID_OK);}
		void onClose( wxCommandEvent& event ){EndModal(wxID_CANCEL);}
};

MyProjectMyDialog2::MyProjectMyDialog2( wxWindow* parent,dialogType type):MyDialog2(parent)
{
    if(type==SCI_ADDSTYLEDTEXT)
    {
        wxDataViewSpinRenderer* sr = new wxDataViewSpinRenderer(0,255);
        wxDataViewColumn* dvc = new wxDataViewColumn("Style no", sr, 1,60);

        m_dataView1->AppendColumn(dvc);
    }
    else if(type==SCI_GETSTYLEDTEXT)
    {
        m_dataView1->AppendTextColumn ("Style no", 1,wxDATAVIEW_CELL_INERT,60, wxALIGN_LEFT);
        m_button5->Show(true);
        m_button1->Show(false);
        m_button2->Show(false);

        //m_textCtrl1 =
        wxTextCtrl* t = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE|wxTE_READONLY );

        sbSizer1->Replace (m_textCtrl1, t);

        m_staticText1->Show(false);
        m_spinCtrl1->Show(false);
        m_textCtrl1->Destroy();

        m_textCtrl1=t;
    }
    else if(type==SCI_SETSTYLINGEX)
    {
        wxDataViewSpinRenderer* sr = new wxDataViewSpinRenderer(0,255);
        wxDataViewColumn* dvc = new wxDataViewColumn("Style no", sr, 1,60);

        m_dataView1->AppendColumn(dvc);

        m_button5->Show(false);
        m_button1->Show(false);
        m_button2->Show(true);

        wxTextCtrl* t = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_DONTWRAP|wxTE_MULTILINE|wxTE_READONLY );

        sbSizer1->Replace (m_textCtrl1, t);

        m_staticText1->Show(false);
        m_spinCtrl1->Show(false);
        m_textCtrl1->Destroy();

        m_textCtrl1=t;
    }

}

void MyProjectMyDialog2::setStyledText(wxMemoryBuffer& b)
{
 	char* c = reinterpret_cast<char*>(b.GetData());
    size_t l=b.GetDataLen();

    wxString s,s1;
    long j;

    wxVector<wxVariant> data;

    for(size_t i=0;i<l;i=i+2)
    {
        data.clear();
        s1 = *(c+i);
        s<<s1;

        j=static_cast<long>( static_cast<int>( *(c+i+1) ) );

        data.push_back( s1 );
        data.push_back( j );

        dvlsModel->AppendItem(data);
    }

    m_textCtrl1->SetValue(s);
}


void MyProjectMyDialog2::onText( wxCommandEvent& event )
{
    int len = m_textCtrl1->GetValue().length();

    int dvlen = dvlsModel->GetCount();
    //wxVariant v;
    //dvlsModel->GetValueByRow(v, dvlen-1, 1) ;
    //int ls = v.GetLong();
    int ls=m_spinCtrl1->GetValue();

    //*m_textCtrl2 << "on text: text length=" << len << " list length=" << dvlen << " last style=" << ls << "\n";

    if(len!=dvlen)
    {
        if(len>dvlen)
        {
            wxVector<wxVariant> data;

            data.push_back( "" );
            data.push_back( ls );

            for(int i=len-dvlen;i>0;i--)
            {
                dvlsModel->AppendItem(data);
            }
        }
        else
        {
            for(int i=dvlen;i>len;i--)
            {
                dvlsModel->DeleteItem(i-1);
            }
        }


        wxString s = m_textCtrl1->GetValue();
        wxString s2;

        for(int i=0;i<len;i++)
        {
            char c=s[i].GetValue();

            if(c=='\n')
            {
                s2="\\n";
            }
            else if(c=='\t')
            {
                s2="\\t";
            }
            else
            {
                s2=c;
            }
            dvlsModel->SetValueByRow(s2,i,0);
        }
    }
}

wxString MyProjectMyDialog2::getStyledText()
{
    int dvlen = dvlsModel->GetCount();
    int strl = 2*dvlen;

    char* buf=reinterpret_cast<char *>(malloc(strl));
    wxString s = m_textCtrl1->GetValue();
    char c,c2;
    wxVariant v;

    for(int i=0;i<dvlen;i++)
    {
        c=s[i].GetValue();

        dvlsModel->GetValueByRow(v,i,1);
        c2=static_cast<char>(v.GetLong());

        *(buf+(2*i)) = c;
        *(buf+(2*i)+1) = c2;
    }

    wxString s2 = wxString::From8BitData(static_cast<char*>(buf),strl);

    free(buf);

    return s2;
}



class MyProjectMyDialog3 : public MyDialog3
{
	public:
		MyProjectMyDialog3( wxWindow* parent );
		int getKeyCode(){return keycode;}
		wxString getKeyName(){return m_textCtrl2->GetValue();}
	protected:
		void onCancel( wxCommandEvent& event ){EndModal(wxID_CANCEL);}
		void onOK( wxCommandEvent& event ){EndModal(wxID_OK);}
		void OnCharHook(wxKeyEvent& event);

        const char* GetVirtualKeyCodeName(int keycode);
        wxString GetKeyName(const wxKeyEvent &event);

        int keycode;
};


MyProjectMyDialog3::MyProjectMyDialog3( wxWindow* parent ):MyDialog3(parent)
{
    Connect(wxEVT_CHAR_HOOK, wxKeyEventHandler(MyProjectMyDialog3::OnCharHook));
    m_panel2->SetFocus();
}

void MyProjectMyDialog3::OnCharHook(wxKeyEvent& event)
{
    keycode=event.GetKeyCode();

    m_textCtrl2->SetValue(GetKeyName(event));
    m_textCtrl3->SetValue( wxString::Format("%d",keycode) );

    if( keycode==WXK_SHIFT || keycode==WXK_ALT || keycode==WXK_RAW_CONTROL
       || keycode==WXK_CONTROL|| keycode==WXK_WINDOWS_LEFT|| keycode==WXK_WINDOWS_RIGHT)
    {
        m_button4->Enable(false);
    }
    else
    {
        m_button4->Enable(true);
    }


    //event.Skip();
}

// helper function that returns textual description of wx virtual keycode
const char* MyProjectMyDialog3::GetVirtualKeyCodeName(int keycode)
{
    switch ( keycode )
    {
#define WXK_(x) \
        case WXK_##x: return #x;

        WXK_(BACK)
        WXK_(TAB)
        WXK_(RETURN)
        WXK_(ESCAPE)
        WXK_(SPACE)
        WXK_(DELETE)
        WXK_(START)
        WXK_(LBUTTON)
        WXK_(RBUTTON)
        WXK_(CANCEL)
        WXK_(MBUTTON)
        WXK_(CLEAR)
        WXK_(SHIFT)
        WXK_(ALT)
        WXK_(CONTROL)
        WXK_(MENU)
        WXK_(PAUSE)
        WXK_(CAPITAL)
        WXK_(END)
        WXK_(HOME)
        WXK_(LEFT)
        WXK_(UP)
        WXK_(RIGHT)
        WXK_(DOWN)
        WXK_(SELECT)
        WXK_(PRINT)
        WXK_(EXECUTE)
        WXK_(SNAPSHOT)
        WXK_(INSERT)
        WXK_(HELP)
        WXK_(NUMPAD0)
        WXK_(NUMPAD1)
        WXK_(NUMPAD2)
        WXK_(NUMPAD3)
        WXK_(NUMPAD4)
        WXK_(NUMPAD5)
        WXK_(NUMPAD6)
        WXK_(NUMPAD7)
        WXK_(NUMPAD8)
        WXK_(NUMPAD9)
        WXK_(MULTIPLY)
        WXK_(ADD)
        WXK_(SEPARATOR)
        WXK_(SUBTRACT)
        WXK_(DECIMAL)
        WXK_(DIVIDE)
        WXK_(F1)
        WXK_(F2)
        WXK_(F3)
        WXK_(F4)
        WXK_(F5)
        WXK_(F6)
        WXK_(F7)
        WXK_(F8)
        WXK_(F9)
        WXK_(F10)
        WXK_(F11)
        WXK_(F12)
        WXK_(F13)
        WXK_(F14)
        WXK_(F15)
        WXK_(F16)
        WXK_(F17)
        WXK_(F18)
        WXK_(F19)
        WXK_(F20)
        WXK_(F21)
        WXK_(F22)
        WXK_(F23)
        WXK_(F24)
        WXK_(NUMLOCK)
        WXK_(SCROLL)
        WXK_(PAGEUP)
        WXK_(PAGEDOWN)
        WXK_(NUMPAD_SPACE)
        WXK_(NUMPAD_TAB)
        WXK_(NUMPAD_ENTER)
        WXK_(NUMPAD_F1)
        WXK_(NUMPAD_F2)
        WXK_(NUMPAD_F3)
        WXK_(NUMPAD_F4)
        WXK_(NUMPAD_HOME)
        WXK_(NUMPAD_LEFT)
        WXK_(NUMPAD_UP)
        WXK_(NUMPAD_RIGHT)
        WXK_(NUMPAD_DOWN)
        WXK_(NUMPAD_PAGEUP)
        WXK_(NUMPAD_PAGEDOWN)
        WXK_(NUMPAD_END)
        WXK_(NUMPAD_BEGIN)
        WXK_(NUMPAD_INSERT)
        WXK_(NUMPAD_DELETE)
        WXK_(NUMPAD_EQUAL)
        WXK_(NUMPAD_MULTIPLY)
        WXK_(NUMPAD_ADD)
        WXK_(NUMPAD_SEPARATOR)
        WXK_(NUMPAD_SUBTRACT)
        WXK_(NUMPAD_DECIMAL)
        WXK_(NUMPAD_DIVIDE)

        WXK_(WINDOWS_LEFT)
        WXK_(WINDOWS_RIGHT)
#ifdef __WXOSX__
        WXK_(RAW_CONTROL)
#endif
#undef WXK_

    default:
        return NULL;
    }
}

// helper function that returns textual description of key in the event
wxString MyProjectMyDialog3::GetKeyName(const wxKeyEvent &event)
{
    int keycode = event.GetKeyCode();
    const char* virt = GetVirtualKeyCodeName(keycode);
    if ( virt )
        return virt;
    if ( keycode > 0 && keycode < 32 )
        return wxString::Format("Ctrl-%c", (unsigned char)('A' + keycode - 1));
    if ( keycode >= 32 && keycode < 128 )
        return wxString::Format("'%c'", (unsigned char)keycode);

#if wxUSE_UNICODE
    int uc = event.GetUnicodeKey();
    if ( uc != WXK_NONE )
        return wxString::Format("'%c'", uc);
#endif

    return "unknown";
}


//int getNextInteger(wxPropertyGrid* propGrid, wxPGProperty* property)
//{
//    wxPropertyGridIterator it = propGrid->GetIterator(wxPG_ITERATE_DEFAULT,property);
//    it++;
//
//    long l = it.GetProperty ()->GetValue();
//    return (int) l;
//}

bool propgridtest03Frame::handle_property(wxPGProperty* property)
{
    int i = reinterpret_cast<int>(property->GetClientData());
    bool rv;

    for(std::vector<wxPGProperty*>::iterator it=clearables.begin();it!=clearables.end();it++)
    {
        (*it)->SetValueToUnspecified();
    }
    statusBar->SetStatusText("", 1);


    switch(i)
    {
        case SCI_PARAM:
            rv=false;
            break;

        case SCI_GETTEXT:
            {
                property->SetValue( m_scintilla1->GetText() );
                statusBar->SetStatusText("Text received.", 1);
                rv=true;

//                wxString stcnames,scinames;
//                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_ALL,property);
//                int i;
//
//                while(!it.AtEnd())
//                {
//
//                    i=reinterpret_cast<int>(it.GetProperty()->GetClientData());
//
//                    if(SCI_TEXTRETRIEVALANDMODIFICATION<=i && i<=SCI_GETIDENTIFIER )
//                    {
//                        if(it.GetProperty()->GetBaseName()!="zzz")
//                        {
//                            stcnames << it.GetProperty()->GetLabel() << "\n";
//                            scinames << it.GetProperty()->GetBaseName() << "\n";
//                        }
//                    }
//                    it++;
//                }
//
//                m_scintilla1->SetText( stcnames + "\n\n" + scinames);
            }
            break;

        case SCI_SETTEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty ()->GetValue();
                m_scintilla1->SetText( s );
                rv= false;
                //m_scintilla1->SetText( m_mgr.SavePerspective() );
            }
            break;
        case SCI_SETSAVEPOINT:
            {
                m_scintilla1->SetSavePoint();
                statusBar->SetStatusText("Save point set.", 1);
                rv=false;
            }
            break;
        case SCI_GETLINE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty()->GetValue();

                property->SetValueFromString( m_scintilla1->GetLine(l1) );
                rv=true;
            }
            break;
        case SCI_REPLACESEL:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty ()->GetValue();
                m_scintilla1->ReplaceSelection( s );
                rv=false;
            }
            break;
        case SCI_SETREADONLY:
            {
                bool b = property->GetValue();
                m_scintilla1->SetReadOnly(b);
                rv=false;
            }
            break;
        case SCI_GETREADONLY:
            {
                bool b = m_scintilla1->GetReadOnly ();

                property->SetValueFromString(b?"True":"False");
                rv=true;
            }
            break;
        case SCI_GETTEXTRANGE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                it++;
                long l2 = it.GetProperty ()->GetValue();

                property->SetValueFromString(m_scintilla1->GetTextRange (l1, l2));
                rv=true;
            }
            break;
        case SCI_ALLOCATE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 =it.GetProperty ()->GetValue();

                m_scintilla1->Allocate( l1 );

                statusBar->SetStatusText(wxString::Format("%d bytes allocated",l1), 1);
                rv=true;
            }
            break;
        case SCI_ADDTEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty ()->GetValue();

                m_scintilla1->AddText(s);
                rv=false;
            }
            break;
        case SCI_ADDSTYLEDTEXT:
            {
                //MyProjectMyDialog2 md(this,MyProjectMyDialog2::SCI_ADDSTYLEDTEXT);

                MyProjectMyDialog5 md( this, m_scintilla1->GetStyleBits(), 0, MyProjectMyDialog5::SCI_ADDSTYLEDTEXT );

                //md.ShowModal();
                //md.copyStyledText(m_scintilla1);



                int i=md.ShowModal();



                if(i==wxID_OK)
                {
                    m_scintilla1->AddStyledText(md.GetStyledText());
//
//                    wxString styledText = md.getStyledText();
//
//                    int l=styledText.length();
//                    wxMemoryBuffer buf(l);
//
//                    char c;
//                    for(int i=0;i<l;i++)
//                    {
//                        c=styledText[i].GetValue();
//                        buf.AppendByte(c);
//                    }
//
//                    m_scintilla1->AddStyledText(buf);
//                    styledText.Clear();
                    statusBar->SetStatusText("Styled text added", 1);

                }
                rv=false;
            }
            break;
        case SCI_APPENDTEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty ()->GetValue();

                m_scintilla1->AppendText(s);
                rv=false;
            }
            break;
        case SCI_INSERTTEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                it++;
                wxString s = it.GetProperty ()->GetValue();

                m_scintilla1->InsertText (l1, s);
                rv=false;
            }
            break;
        case SCI_CLEARALL:
            {
                m_scintilla1->ClearAll ();
                rv=false;
            }
            break;
        case SCI_DELETERANGE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                it++;
                long l2 = it.GetProperty ()->GetValue();

                m_scintilla1->DeleteRange (l1, l2);
                rv=false;
            }
            break;
        case SCI_CLEARDOCUMENTSTYLE:
            {
                m_scintilla1->ClearDocumentStyle();
                statusBar->SetStatusText("All style bits cleared.", 1);
                rv=false;
            }
            break;
        case SCI_GETCHARAT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();

                char c = m_scintilla1->GetCharAt (l1);
                if(c=='\0')
                {
                    property->SetValueFromString("(no character)");
                }
                else
                {
                    wxString s = c;
                    property->SetValueFromString(s);
                }

                rv=true;
            }
            break;
        case SCI_GETSTYLEAT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();

                int i = m_scintilla1->GetStyleAt (l1);


//                wxString s="";
//
//                for(int j=0;j<8;j++)
//                {
//                    if(i&(1<<j))
//                    {
//                        s.Prepend("1");
//                    }
//                    else
//                    {
//                        s.Prepend("0");
//                    }
//                }



                int mask=0;
                int sb = m_scintilla1->GetStyleBits();

                for(int j=0;j<8;j++)
                {
                    if(j<sb)
                    {
                        mask = mask|(1<<j);
                    }
                }

                int st=i&mask;

                mask=0;
                for(int j=0;j<8;j++)
                {
                    if(j>=sb)
                    {
                        mask = mask|(1<<j);
                    }
                }

                int ind = i&mask;
                ind = ind >>sb;

                wxString s = wxString::Format("style=%d indicator=%d",st,ind);

                property->SetValue(s);

                rv=true;
            }
            break;
        case SCI_GETSTYLEDTEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                it++;
                long l2 = it.GetProperty ()->GetValue();

//                MyProjectMyDialog2 md(this,MyProjectMyDialog2::SCI_GETSTYLEDTEXT);
//                md.setStyledText( m_scintilla1->GetStyledText(l1,l2) );
//                md.ShowModal();

                MyProjectMyDialog5 md(this,m_scintilla1->GetStyleBits(),0,MyProjectMyDialog5::SCI_GETSTYLEDTEXT);

                md.AddStyledText(m_scintilla1->GetStyledText(l1,l2));

                md.SetReadOnly();
                md.ShowModal();

                rv=false;
            }
            break;
        case SCI_SETSTYLEBITS:
            {
                m_scintilla1->SetStyleBits( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETSTYLEBITS:
            {
                property->SetValue(wxString::Format( "%d",m_scintilla1->GetStyleBits() ));
                rv= true;
            }
            break;
        case SCI_ACCESSTOENCODEDTEXT:
            {
                rv= false;
            }
            break;
        case SCI_TARGETASUTF8:
            {
                property->SetValueFromInt( m_scintilla1->SendMsg(2447,0,0) );
                rv= false;
            }
            break;
        case SCI_ENCODEDFROMUTF8:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty ()->GetValue();

                const char* c = s;

                //property->SetValue(wxString::Format( "%d",m_scintilla1->GetStyleBits() ));
                property->SetValueFromInt( m_scintilla1->SendMsg(2449,(sptr_t)c,0) );
                rv= false;
            }
            break;
        case SCI_SETLENGTHFORENCODE:
            {
                m_scintilla1->SendMsg(2448,0,0);
                rv= false;
            }
            break;
        case SCI_GETTEXTRANGEALT:
            {
                //property->SetValue(wxString::Format( "%d",m_scintilla1->GetStyleBits() ));

                //this is a slightly different implimentation for SCI_GETTEXTRANGE
                //currently the program will crash if cpMin is larger than the
                //document length.

                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long cpMin = it.GetProperty ()->GetValue();
                it++;
                long cpMax = it.GetProperty ()->GetValue();

                if(cpMax==-1)
                {
                    int total_len = m_scintilla1->SendMsg(2182, 0, 0);
                    int needed_len = total_len-cpMin;

                    wxMemoryBuffer mbuf(needed_len);
                    char* buf = (char*)mbuf.GetWriteBuf(needed_len);
                    Sci_TextRange tr;
                    tr.lpstrText = buf;
                    tr.chrg.cpMin = cpMin;
                    tr.chrg.cpMax = cpMax;
                    m_scintilla1->SendMsg(2162, 0, (sptr_t)&tr);

                    property->SetValueFromString(wxString(buf,needed_len-1));
                }
                else
                {
                    property->SetValueFromString(m_scintilla1->GetTextRange(cpMin,cpMax));
                }

                rv= true;
            }
            break;

        case SCI_SEARCHING:
            {
                rv= false;
            }
            break;
        case SCI_FINDTEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();

                it++;
                long l2 = it.GetProperty ()->GetValue();

                it++;
                wxString s = it.GetProperty ()->GetValue();

                it++;
                long l3 = it.GetProperty ()->GetValue();

                property->SetValue(wxString::Format("%d",m_scintilla1->FindText(l1, l2, s, l3)));

                rv=true;
            }
            break;
        case SCI_SEARCHANCHOR:
            {
                m_scintilla1->SearchAnchor();
                statusBar->SetStatusText("The search anchor has been set.", 1);
                rv=false;
            }
            break;
        case SCI_SEARCHNEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();

                it++;
                wxString s = it.GetProperty ()->GetValue();

                property->SetValue(wxString::Format("%d",m_scintilla1->SearchNext(l1, s)));

                rv=true;
            }
            break;
        case SCI_SEARCHPREV:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();

                it++;
                wxString s = it.GetProperty ()->GetValue();

                property->SetValue(wxString::Format("%d",m_scintilla1->SearchPrev(l1, s)));

                rv=true;
            }
            break;
        case SCI_SETTARGETSTART:
            {
                m_scintilla1->SetTargetStart( property->GetValue().GetLong() );
                rv= false;
            }
            break;
        case SCI_GETTARGETSTART:
            {
                property->SetValue( wxString::Format( "%d",m_scintilla1->GetTargetStart() ) );
                rv= true;
            }
            break;
        case SCI_SETTARGETEND:
            {
                m_scintilla1->SetTargetEnd( property->GetValue().GetLong() );
                rv= false;
            }
            break;
        case SCI_GETTARGETEND:
            {
                property->SetValue( wxString::Format( "%d",m_scintilla1->GetTargetEnd() ) );
                rv= true;
            }
            break;
        case SCI_TARGETFROMSELECTION:
            {
                m_scintilla1->TargetFromSelection();
                statusBar->SetStatusText("The target has been set from the current selection.", 1);
                rv=false;
            }
            break;
        case SCI_SETSEARCHFLAGS:
            {
                m_scintilla1->SetSearchFlags( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETSEARCHFLAGS:
            {
                long l= m_scintilla1->GetSearchFlags();

                wxString s;
                bool already_added(false);

                if(l&wxSTC_FIND_MATCHCASE)
                {
                    s<<"wxSTC_FIND_MATCHCASE";
                    already_added=true;
                }

                if(l&wxSTC_FIND_WHOLEWORD)
                {
                    s<< (already_added?"|":"")<<"wxSTC_FIND_WHOLEWORD";
                    already_added=true;
                }

                if(l&wxSTC_FIND_WORDSTART)
                {
                    s<< (already_added?"|":"")<<"wxSTC_FIND_WORDSTART";
                    already_added=true;
                }

                if(l&wxSTC_FIND_REGEXP)
                {
                    s << (already_added?"|":"") <<"wxSTC_FIND_REGEXP";
                    already_added=true;
                }

                if(l&wxSTC_FIND_POSIX)
                {
                    s<< (already_added?"|":"")<<"wxSTC_FIND_POSIX";
                    already_added=true;
                }

                property->SetValueFromString(s);
                rv= true;
            }
            break;
        case SCI_SEARCHINTARGET:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty ()->GetValue();

                property->SetValueFromString( wxString::Format("%d",m_scintilla1->SearchInTarget(s) ));
                rv=true;
            }
            break;
        case SCI_REPLACETARGET:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty ()->GetValue();

                property->SetValueFromString( wxString::Format("%d",m_scintilla1->ReplaceTarget(s) ));
                rv=true;
            }
            break;
        case SCI_REPLACETARGETRE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty ()->GetValue();

                property->SetValueFromString( wxString::Format("%d",m_scintilla1->ReplaceTargetRE(s) ));
                rv=true;
            }
            break;
        case SCI_GETTAG:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;

                property->SetValueFromString( m_scintilla1->GetTag( it.GetProperty ()->GetValue().GetLong() ) );
                rv=true;
            }
            break;

        case SCI_OVERTYPE:
              rv=false;
            break;
        case SCI_SETOVERTYPE:
            {
                m_scintilla1->SetOvertype( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETOVERTYPE:
            {
                property->SetValueFromString(m_scintilla1->GetOvertype()?"True":"False");
                rv=true;
            }
            break;

        case SCI_CUTCOPYANDPASTE:
                rv=false;
            break;
        case SCI_CUT:
            {
                m_scintilla1->Cut();
                rv=false;
            }
            break;
        case SCI_COPY:
            {
                m_scintilla1->Copy();
                statusBar->SetStatusText("Selection copied to clipboard.", 1);
                rv=false;
            }
            break;
        case SCI_PASTE:
            {
                m_scintilla1->Paste();
                rv=false;
            }
            break;
        case SCI_CLEAR:
            {
                m_scintilla1->Clear();
                rv=false;
            }
            break;
        case SCI_CANPASTE:
            {
                property->SetValueFromString(m_scintilla1->CanPaste()?"True":"False");
                rv=true;
            }
            break;
        case SCI_COPYRANGE:
            {
                wxPropertyGridIterator it = m_propgrid->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                it++;
                long l2 = it.GetProperty ()->GetValue();

                m_scintilla1->CopyRange(l1,l2);
                statusBar->SetStatusText("Range copied to clipboard.", 1);
                rv=false;
            }
            break;
        case SCI_COPYTEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                it++;
                wxString s = it.GetProperty ()->GetValue();

                m_scintilla1->CopyText(l1,s);
                statusBar->SetStatusText("Text copied to clipboard.", 1);

                rv=false;
            }
            break;
        case SCI_COPYALLOWLINE:
            {
                m_scintilla1->CopyAllowLine();
                statusBar->SetStatusText("Selection or current line copied to clipboard.", 1);
                rv=false;
            }
            break;
        case SCI_SETPASTECONVERTENDINGS:
            {
                m_scintilla1->SetPasteConvertEndings( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETPASTECONVERTENDINGS:
            {
                property->SetValueFromString(m_scintilla1->GetPasteConvertEndings()?"True":"False");
                rv=true;
            }
            break;

        case SCI_ERRORHANDLING:
                rv=false;
            break;
        case SCI_SETSTATUS:
            {
                m_scintilla1->SetStatus( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETSTATUS:
            {
                wxString s;
                long l = m_scintilla1->GetStatus();

                if(l==wxSTC_STATUS_OK)
                {
                    s="wxSTC_STATUS_OK";
                }
                else if(l==wxSTC_STATUS_FAILURE)
                {
                    s="wxSTC_STATUS_FAILURE";
                }
                else if(l==wxSTC_STATUS_BADALLOC)
                {
                    s="wxSTC_STATUS_BADALLOC";
                }
                else
                {
                    s=wxString::Format("%d - unknown status",l);
                }

                property->SetValueFromString(s);
                rv=true;
            }
            break;

        case SCI_UNDOANDREDO:
                rv=false;
            break;
        case SCI_UNDO:
            {
                m_scintilla1->Undo();
                rv=false;
            }
            break;
        case SCI_CANUNDO:
            {
                property->SetValueFromString(m_scintilla1->CanUndo()?"True":"False");
                rv=true;
            }
            break;
        case SCI_REDO:
            {
                m_scintilla1->Redo ();
                rv=false;
            }
            break;
        case SCI_CANREDO:
            {
                property->SetValueFromString(m_scintilla1->CanRedo()?"True":"False");
                rv=true;
            }
            break;
        case SCI_EMPTYUNDOBUFFER:
            {
                m_scintilla1->EmptyUndoBuffer();
                statusBar->SetStatusText("The Undo buffer has been cleared.", 1);
                rv=false;
            }
            break;
        case SCI_SETUNDOCOLLECTION:
            {
                m_scintilla1->SetUndoCollection( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETUNDOCOLLECTION:
            {
                property->SetValueFromString(m_scintilla1->GetUndoCollection()?"True":"False");
                rv=true;
            }
            break;
        case SCI_BEGINUNDOACTION:
            {
                m_scintilla1->BeginUndoAction();
                statusBar->SetStatusText("Undo action begun.", 1);
                rv=false;
            }
            break;
        case SCI_ENDUNDOACTION:
            {
                m_scintilla1->EndUndoAction();
                statusBar->SetStatusText("Undo action finished.", 1);
                rv=false;
            }
            break;
        case SCI_ADDUNDOACTION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                it++;
                long l2 = it.GetProperty ()->GetValue();

                m_scintilla1->AddUndoAction(l1,l2);

                wxString msg = wxString::Format("Undo action added with token %d",l1);

                if(l2&wxSTC_UNDO_MAY_COALESCE)
                {
                    msg << " and flags wxSTC_UNDO_MAY_COALESCE";
                }
                msg <<".";

                statusBar->SetStatusText(msg, 1);

                rv=false;
            }
            break;

        case SCI_SELECTIONANDINFORMATION:
                rv=false;
            break;
        case SCI_GETTEXTLENGTH:
            {
                property->SetValueFromInt(m_scintilla1->GetTextLength ());
                rv=true;
            }
            break;
        case SCI_GETLENGTH:
            {
                property->SetValueFromInt(m_scintilla1->GetLength());
                rv=true;
            }
            break;
        case SCI_GETLINECOUNT:
            {
                property->SetValueFromInt(m_scintilla1->GetLineCount());
                rv=true;
            }
            break;
        case SCI_SETFIRSTVISIBLELINE:
            {
                m_scintilla1->SetFirstVisibleLine( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETFIRSTVISIBLELINE:
            {
                property->SetValueFromInt(m_scintilla1->GetFirstVisibleLine());
                rv=true;
            }
            break;
        case SCI_LINESONSCREEN:
            {
                property->SetValueFromInt(m_scintilla1->LinesOnScreen());
                rv=true;
            }
            break;
        case SCI_GETMODIFY:
            {
                property->SetValueFromString(m_scintilla1->GetModify()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETSEL:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                it++;
                long l2 = it.GetProperty ()->GetValue();

                //m_scintilla1->SetSelection(l1,l2);
                m_scintilla1->SendMsg(2160,l1,l2);

                rv=false;
            }
            break;
        case SCI_GOTOPOS:
            {
                m_scintilla1->GotoPos ( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GOTOLINE:
            {
                m_scintilla1->GotoLine( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_SETCURRENTPOS:
            {
                m_scintilla1->SetCurrentPos( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETCURRENTPOS:
            {
                property->SetValueFromInt( m_scintilla1->GetCurrentPos() );
                rv=true;
            }
            break;
        case SCI_SETANCHOR:
            {
                m_scintilla1->SetAnchor( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETANCHOR:
            {
                property->SetValueFromInt( m_scintilla1->GetAnchor() );
                rv=true;
            }
            break;
        case SCI_SETSELECTIONSTART:
            {
                m_scintilla1->SetSelectionStart( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETSELECTIONSTART:
            {
                property-> SetValueFromInt( m_scintilla1->GetSelectionStart() );
                rv=true;
            }
            break;
        case SCI_SETSELECTIONEND:
            {
                m_scintilla1->SetSelectionEnd( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETSELECTIONEND:
            {
                property->SetValueFromInt ( m_scintilla1->GetSelectionEnd() );
                rv=true;
            }
            break;
        case SCI_SETEMPTYSELECTION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();

                m_scintilla1->SetEmptySelection(l1);

                rv=false;
            }
            break;
        case SCI_SELECTALL:
            {
                m_scintilla1->SelectAll();
                rv=false;
            }
            break;
        case SCI_LINEFROMPOSITION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                property->SetValueFromInt ( m_scintilla1->LineFromPosition(l1) );
                rv=true;
            }
            break;
        case SCI_POSITIONFROMLINE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                property->SetValueFromInt ( m_scintilla1->PositionFromLine(l1) );
                rv=true;
            }
            break;
        case SCI_GETLINEENDPOSITION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                property->SetValueFromInt ( m_scintilla1->GetLineEndPosition(l1) );
                rv=true;
            }
            break;
        case SCI_LINELENGTH:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();
                property->SetValueFromInt ( m_scintilla1->LineLength(l1) );
                rv=true;
            }
            break;

        case SCI_GETSELTEXT:
            {
                property->SetValueFromString( m_scintilla1->GetSelectedText() );
                rv=true;
            }
            break;
        case SCI_GETCURLINE:
            {
                int linePos;
                wxString s = m_scintilla1->GetCurLine(&linePos);
                property->SetValueFromString( wxString::Format("The caret is at position %d in the line \"%s\"",linePos,s) );

                rv=true;
            }
            break;
        case SCI_SELECTIONISRECTANGLE:
            {
                property->SetValueFromString(m_scintilla1->SelectionIsRectangle()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETSELECTIONMODE:
            {
                m_scintilla1->SetSelectionMode( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETSELECTIONMODE:
            {
                int l=m_scintilla1->GetSelectionMode();

                if(l==wxSTC_SEL_STREAM)
                {
                    property->SetValueFromString("wxSTC_SEL_STREAM");
                }
                else if(l==wxSTC_SEL_RECTANGLE)
                {
                    property->SetValueFromString("wxSTC_SEL_RECTANGLE");
                }
                else if(l==wxSTC_SEL_LINES)
                {
                    property->SetValueFromString("wxSTC_SEL_LINES");
                }
                else if(l==wxSTC_SEL_THIN)
                {
                    property->SetValueFromString("wxSTC_SEL_THIN");
                }
                else
                {
                    property->SetValueFromString("(unknown selection mode)");
                }

                rv=true;
            }
            break;
        case SCI_GETLINESELSTARTPOSITION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                int i=m_scintilla1->GetLineSelStartPosition(l1);

                if(i==wxSTC_INVALID_POSITION)
                {
                    property->SetValueFromString("wxSTC_INVALID_POSITION");
                }
                else
                {
                    property->SetValueFromInt(i);
                }

                rv=true;
            }
            break;
        case SCI_GETLINESELENDPOSITION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                int i=m_scintilla1->GetLineSelEndPosition(l1);

                if(i==wxSTC_INVALID_POSITION)
                {
                    property->SetValueFromString("wxSTC_INVALID_POSITION");
                }
                else
                {
                    property->SetValueFromInt(i);
                }

                rv=true;
            }
            break;
        case SCI_MOVECARETINSIDEVIEW:
            {
                m_scintilla1->MoveCaretInsideView ();
                rv=false;
            }
            break;
        case SCI_WORDENDPOSITION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                bool b = it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->WordEndPosition(l1,b) );

                rv=true;
            }
            break;
        case SCI_WORDSTARTPOSITION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                bool b = it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->WordStartPosition(l1,b) );

                rv=true;
            }
            break;
        case SCI_POSITIONBEFORE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->PositionBefore(l1) );

                rv=true;
            }
            break;
        case SCI_POSITIONAFTER:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->PositionAfter(l1) );

                rv=true;
            }
            break;
        case SCI_COUNTCHARACTERS:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->CountCharacters(l1,l2) );

                rv=true;
            }
            break;
        case SCI_TEXTWIDTH:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                wxString s=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->TextWidth(l1,s) );

                rv=true;
            }
            break;
        case SCI_TEXTHEIGHT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->TextHeight(l1) );

                rv=true;
            }
            break;

        case SCI_GETCOLUMN:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                property->SetValueFromInt( m_scintilla1->GetColumn(l1) );
                rv=true;
            }
            break;
        case SCI_FINDCOLUMN:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();
                property->SetValueFromInt( m_scintilla1->FindColumn(l1,l2) );
                rv=true;
            }
            break;
        case SCI_POSITIONFROMPOINT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();
                property->SetValueFromInt( m_scintilla1->PositionFromPoint(wxPoint(l1,l2)) );
                rv=true;
            }
            break;
        case SCI_POSITIONFROMPOINTCLOSE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();
                property->SetValueFromInt( m_scintilla1->PositionFromPointClose(l1,l2) );
                rv=true;
            }
            break;
        case SCI_CHARPOSITIONFROMPOINT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();
                property->SetValueFromInt( m_scintilla1->CharPositionFromPoint(l1,l2) );
                rv=true;
            }
            break;
        case SCI_CHARPOSITIONFROMPOINTCLOSE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();
                property->SetValueFromInt( m_scintilla1->CharPositionFromPointClose(l1,l2) );
                rv=true;
            }
            break;
        case SCI_POINTXFROMPOSITION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->SendMsg(2164,0,l1) );
                rv=true;

//                wxPoint p = m_scintilla1->PointFromPosition(l1);
//
//                property->SetValueFromString( wxString::Format("(%d,%d)",p.x,p.y) );
//                rv=true;
            }
            break;
        case SCI_POINTYFROMPOSITION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->SendMsg(2165,0,l1) );
                rv=true;
            }
            break;
        case SCI_HIDESELECTION:
            {
                m_scintilla1->HideSelection( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_CHOOSECARETX:
            {
                m_scintilla1->ChooseCaretX();
                rv=false;
            }
            break;
        case SCI_MOVESELECTEDLINESUP:
            {
                m_scintilla1->MoveSelectedLinesUp();
                rv=false;
            }
            break;
        case SCI_MOVESELECTEDLINESDOWN:
            {
                m_scintilla1->MoveSelectedLinesDown();
                rv=false;
            }
            break;

        case SCI_MULTIPLESELECTIONANDVIRTUALSPACE:
            {
                rv=false;
            }
            break;
        case SCI_SETMULTIPLESELECTION:
            {
                m_scintilla1->SetMultipleSelection( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETMULTIPLESELECTION:
            {
                property->SetValueFromString(m_scintilla1->GetMultipleSelection()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETADDITIONALSELECTIONTYPING:
            {
                m_scintilla1->SetAdditionalSelectionTyping( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETADDITIONALSELECTIONTYPING:
            {
                property->SetValueFromString(m_scintilla1->GetAdditionalSelectionTyping()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETMULTIPASTE:
            {
                m_scintilla1->SetMultiPaste( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETMULTIPASTE:
            {
                int i=m_scintilla1->GetMultiPaste();

                if(i==wxSTC_MULTIPASTE_ONCE)
                {
                    property->SetValueFromString("wxSTC_MULTIPASTE_ONCE");
                }
                else if(i==wxSTC_MULTIPASTE_EACH)
                {
                    property->SetValueFromString("wxSTC_MULTIPASTE_EACH");
                }
                else
                {
                    property->SetValueFromString("(unknown multipaste mode");
                }

                rv=true;
            }
            break;
        case SCI_SETVIRTUALSPACEOPTIONS:
            {
                m_scintilla1->SetVirtualSpaceOptions( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETVIRTUALSPACEOPTIONS:
            {
                long l=m_scintilla1->GetVirtualSpaceOptions();
                wxString s;


                if(l==wxSTC_SCVS_NONE)
                {
                    s="wxSTC_SCVS_NONE";
                }
                else
                {
                    bool already_added(false);

                    if(l&wxSTC_SCVS_RECTANGULARSELECTION)
                    {
                        s<<"wxSTC_SCVS_RECTANGULARSELECTION";
                        already_added=true;
                    }

                    if(l&wxSTC_SCVS_USERACCESSIBLE)
                    {
                        s<< (already_added?"|":"")<<"wxSTC_SCVS_USERACCESSIBLE";
                        already_added=true;
                    }
                }

                if(s.IsEmpty())
                {
                    s="(unknown virtual space option)";
                }

                property->SetValueFromString(s);
            }
            break;
        case SCI_SETRECTANGULARSELECTIONMODIFIER:
            {
                m_scintilla1->SetRectangularSelectionModifier( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETRECTANGULARSELECTIONMODIFIER:
            {
                long l=m_scintilla1->GetRectangularSelectionModifier();
                wxString s;

                if(l==wxSTC_SCMOD_NORM)
                {
                    s="wxSTC_SCMOD_NORM";
                }
                else
                {
                    bool already_added(false);

                    if(l&wxSTC_SCMOD_SHIFT)
                    {
                        s<<"wxSTC_SCMOD_SHIFT";
                        already_added=true;
                    }

                    if(l&wxSTC_SCMOD_CTRL)
                    {
                        s<< (already_added?"|":"")<<"wxSTC_SCMOD_CTRL";
                        already_added=true;
                    }

                    if(l&wxSTC_SCMOD_ALT)
                    {
                        s<< (already_added?"|":"")<<"wxSTC_SCMOD_ALT";
                        already_added=true;
                    }

                    if(l&wxSTC_SCMOD_SUPER)
                    {
                        s<< (already_added?"|":"")<<"wxSTC_SCMOD_SUPER";
                        already_added=true;
                    }

                    if(l&wxSTC_SCMOD_META)
                    {
                        s<< (already_added?"|":"")<<"wxSTC_SCMOD_META";
                        already_added=true;
                    }
                }

                if(s.IsEmpty())
                {
                    s="(unknown Rectangular Selection Modifier)";
                }

                property->SetValueFromString(s);
            }
            break;
        case SCI_GETSELECTIONS:
            {
                property->SetValueFromInt(m_scintilla1->GetSelections());
                rv=true;
            }
            break;
        case SCI_CLEARSELECTIONS:
            {
                m_scintilla1->ClearSelections();
                statusBar->SetStatusText("Selections Cleared", 1);
                rv=false;
            }
            break;
        case SCI_SETSELECTION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->SendMsg(2572, l1, l2);
                rv=false;
            }
            break;
        case SCI_ADDSELECTION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->AddSelection( l1, l2);
                rv=false;
            }
            break;
        case SCI_SETMAINSELECTION:
            {
                m_scintilla1->SetMainSelection( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETMAINSELECTION:
            {
                property->SetValueFromInt( m_scintilla1->GetMainSelection() );
                rv=true;
            }
            break;
        case SCI_SETSELECTIONNCARET:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->SetSelectionNCaret( l1,l2 );
                rv=false;
            }
            break;
        case SCI_GETSELECTIONNCARET:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetSelectionNCaret(l1) );
                rv=true;
            }
            break;
        case SCI_SETSELECTIONNCARETVIRTUALSPACE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->SetSelectionNCaretVirtualSpace( l1,l2 );
                rv=false;
            }
            break;
        case SCI_GETSELECTIONNCARETVIRTUALSPACE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetSelectionNCaretVirtualSpace(l1) );
                rv=true;
            }
            break;
        case SCI_SETSELECTIONNANCHOR:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->SetSelectionNAnchor( l1,l2 );
                rv=false;
            }
            break;
        case SCI_GETSELECTIONNANCHOR:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetSelectionNAnchor(l1) );
                rv=true;
            }
            break;
        case SCI_SETSELECTIONNANCHORVIRTUALSPACE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->SetSelectionNAnchorVirtualSpace( l1,l2 );
                rv=false;
            }
            break;
        case SCI_GETSELECTIONNANCHORVIRTUALSPACE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetSelectionNAnchorVirtualSpace(l1) );
                rv=true;
            }
            break;
        case SCI_SETSELECTIONNSTART:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->SetSelectionNStart( l1,l2 );
                rv=false;
            }
            break;
        case SCI_GETSELECTIONNSTART:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetSelectionNStart(l1) );
                rv=true;
            }
            break;
        case SCI_SETSELECTIONNEND:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->SetSelectionNEnd( l1,l2 );
                rv=false;
            }
            break;
        case SCI_GETSELECTIONNEND:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetSelectionNEnd(l1) );
                rv=true;
            }
            break;
        case SCI_SETRECTANGULARSELECTIONCARET:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                m_scintilla1->SetRectangularSelectionCaret( l1 );
                rv=false;
            }
            break;
        case SCI_GETRECTANGULARSELECTIONCARET:
            {
                property->SetValueFromInt( m_scintilla1->GetRectangularSelectionCaret() );
                rv=true;
            }
            break;
        case SCI_SETRECTANGULARSELECTIONCARETVIRTUALSPACE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                m_scintilla1->SetRectangularSelectionCaretVirtualSpace( l1 );
                rv=false;
            }
            break;
        case SCI_GETRECTANGULARSELECTIONCARETVIRTUALSPACE:
            {
                property->SetValueFromInt( m_scintilla1->GetRectangularSelectionCaretVirtualSpace() );
                rv=true;
            }
            break;
        case SCI_SETRECTANGULARSELECTIONANCHOR:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                m_scintilla1->SetRectangularSelectionAnchor( l1 );
                rv=false;
            }
            break;
        case SCI_GETRECTANGULARSELECTIONANCHOR:
            {
                property->SetValueFromInt( m_scintilla1->GetRectangularSelectionAnchor() );
                rv=true;
            }
            break;
        case SCI_SETRECTANGULARSELECTIONANCHORVIRTUALSPACE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                m_scintilla1->SetRectangularSelectionAnchorVirtualSpace( l1 );
                rv=false;
            }
            break;
        case SCI_GETRECTANGULARSELECTIONANCHORVIRTUALSPACE:
            {
                property->SetValueFromInt( m_scintilla1->GetRectangularSelectionAnchorVirtualSpace() );
                rv=true;
            }
            break;
        case SCI_SETADDITIONALSELALPHA:
            {
                m_scintilla1->SetAdditionalSelAlpha( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETADDITIONALSELALPHA:
            {
                property->SetValueFromInt( m_scintilla1->GetAdditionalSelAlpha() );
                rv=true;
            }
            break;
        case SCI_SETADDITIONALSELFORE:
            {
                wxAny value = property->GetValue();
                m_scintilla1->SetAdditionalSelForeground( value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_SETADDITIONALSELBACK:
            {
                wxAny value = property->GetValue();
                m_scintilla1->SetAdditionalSelBackground( value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_SETADDITIONALCARETFORE:
            {
                wxAny value = property->GetValue();
                m_scintilla1->SetAdditionalCaretForeground( value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_GETADDITIONALCARETFORE:
            {
                setColorString( property, m_scintilla1->GetAdditionalCaretForeground() );
                rv=true;
            }
            break;
        case SCI_SETADDITIONALCARETSBLINK:
            {
                m_scintilla1->SetAdditionalCaretsBlink( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETADDITIONALCARETSBLINK:
            {
                property->SetValueFromString(m_scintilla1->GetAdditionalCaretsBlink()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETADDITIONALCARETSVISIBLE:
            {
                m_scintilla1->SetAdditionalCaretsVisible( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETADDITIONALCARETSVISIBLE:
            {
                property->SetValueFromString(m_scintilla1->GetAdditionalCaretsVisible()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SWAPMAINANCHORCARET:
            {
                m_scintilla1->SwapMainAnchorCaret( );
                rv=false;
            }
            break;
        case SCI_ROTATESELECTION:
            {
                m_scintilla1->RotateSelection( );
                rv=false;
            }
            break;

        case SCI_LINESCROLL:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->LineScroll(l1,l2);
                rv=false;
            }
            break;
        case SCI_SCROLLCARET:
            {
                m_scintilla1->EnsureCaretVisible();
                rv=false;
            }
            break;
        case SCI_SETXCARETPOLICY:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->SetXCaretPolicy(l1,l2);
                statusBar->SetStatusText("X caret policy set.", 1);
                rv=false;
            }
            break;
        case SCI_SETYCARETPOLICY:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->SetYCaretPolicy(l1,l2);
                statusBar->SetStatusText("Y caret policy set.", 1);
                rv=false;
            }
            break;
        case SCI_SETVISIBLEPOLICY:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->SetVisiblePolicy(l1,l2);

                statusBar->SetStatusText("Visible policy set.", 1);
                rv=false;
            }
            break;
        case SCI_SETHSCROLLBAR:
            {
                m_scintilla1->SetUseHorizontalScrollBar( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETHSCROLLBAR:
            {
                property->SetValueFromString(m_scintilla1->GetUseHorizontalScrollBar()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETVSCROLLBAR:
            {
                m_scintilla1->SetUseVerticalScrollBar( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETVSCROLLBAR:
            {
                property->SetValueFromString(m_scintilla1->GetUseVerticalScrollBar()?"True":"False");
                rv=true;
            }
            break;
        case SCI_GETXOFFSET:
            {
                property->SetValueFromInt( m_scintilla1->GetXOffset() );
                rv=true;
            }
            break;
        case SCI_SETXOFFSET:
            {
                m_scintilla1->SetXOffset( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_SETSCROLLWIDTH:
            {
                m_scintilla1->SetScrollWidth( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETSCROLLWIDTH:
            {
                property->SetValueFromInt( m_scintilla1->GetScrollWidth() );
                rv=true;
            }
            break;
        case SCI_SETSCROLLWIDTHTRACKING:
            {
                m_scintilla1->SetScrollWidthTracking( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETSCROLLWIDTHTRACKING:
            {
                property->SetValueFromString(m_scintilla1->GetScrollWidthTracking()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETENDATLASTLINE:
            {
                m_scintilla1->SetEndAtLastLine( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETENDATLASTLINE:
            {
                property->SetValueFromString(m_scintilla1->GetEndAtLastLine()?"True":"False");
                rv=true;
            }
            break;

        case SCI_SETVIEWWS:
            {
                m_scintilla1->SetViewWhiteSpace( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETVIEWWS:
            {
                int i=m_scintilla1->GetViewWhiteSpace();

                if(i==wxSTC_WS_INVISIBLE)
                {
                    property->SetValueFromString("wxSTC_WS_INVISIBLE");
                }
                else if(i==wxSTC_WS_VISIBLEALWAYS)
                {
                    property->SetValueFromString("wxSTC_WS_VISIBLEALWAYS");
                }
                else if(i==wxSTC_WS_VISIBLEAFTERINDENT)
                {
                    property->SetValueFromString("wxSTC_WS_VISIBLEAFTERINDENT");
                }
                else
                {
                    property->SetValueFromString("(unknown whitespace mode");
                }
                rv=true;
            }
            break;
        case SCI_SETWHITESPACEFORE:
            {
                rv=false;
            }
            break;
        case SCI_SETWHITESPACEFOREPARM1:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxAny value=it.GetProperty ()->GetValue();

                bool b = property->GetValue();

                m_scintilla1->SetWhitespaceForeground(b,value.As<wxColour>());

                rv=false;
            }
            break;
        case SCI_SETWHITESPACEFOREPARM2:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it--;
                bool b=it.GetProperty ()->GetValue();

                wxAny value = property->GetValue();

                m_scintilla1->SetWhitespaceForeground(b,value.As<wxColour>());

                rv=false;
            }
            break;
        case SCI_SETWHITESPACEBACK:
            {
                rv=false;
            }
            break;
        case SCI_SETWHITESPACEBACKPARM1:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxAny value=it.GetProperty ()->GetValue();

                bool b = property->GetValue();

                m_scintilla1->SetWhitespaceBackground(b,value.As<wxColour>());

                rv=false;
            }
            break;
        case SCI_SETWHITESPACEBACKPARM2:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it--;
                bool b=it.GetProperty ()->GetValue();

                wxAny value = property->GetValue();

                m_scintilla1->SetWhitespaceBackground(b,value.As<wxColour>());

                rv=false;
            }
            break;
        case SCI_SETWHITESPACESIZE:
            {
                m_scintilla1->SetWhitespaceSize( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETWHITESPACESIZE:
            {
                property->SetValueFromInt( m_scintilla1->GetWhitespaceSize() );
                rv=true;
            }
            break;
        case SCI_SETEXTRAASCENT:
            {
                m_scintilla1->SetExtraAscent( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETEXTRAASCENT:
            {
                property->SetValueFromInt( m_scintilla1->GetExtraAscent() );
                rv=true;
            }
            break;
        case SCI_SETEXTRADESCENT:
            {
                m_scintilla1->SetExtraDescent( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETEXTRADESCENT:
            {
                property->SetValueFromInt( m_scintilla1->GetExtraDescent() );
                rv=true;
            }
            break;

        case SCI_SETCURSOR:
            {
                m_scintilla1->SetSTCCursor( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETCURSOR:
            {
                int i=m_scintilla1->GetSTCCursor();

                if(i==wxSTC_CURSORNORMAL)
                {
                    property->SetValueFromString("wxSTC_CURSORNORMAL");
                }
                else if(i==wxSTC_CURSORARROW)
                {
                    property->SetValueFromString("wxSTC_CURSORARROW");
                }
                else if(i==wxSTC_CURSORWAIT)
                {
                    property->SetValueFromString("wxSTC_CURSORWAIT");
                }
                else if(i==wxSTC_CURSORREVERSEARROW)
                {
                    property->SetValueFromString("wxSTC_CURSORREVERSEARROW");
                }
                else
                {
                    property->SetValueFromString("(unknown cursor)");
                }
                rv=true;
            }
            break;
        case SCI_SETMOUSEDOWNCAPTURES:
            {
                m_scintilla1->SetMouseDownCaptures( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETMOUSEDOWNCAPTURES:
            {
                property->SetValueFromString(m_scintilla1->GetMouseDownCaptures()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETEOLMODE:
            {
                m_scintilla1->SetEOLMode( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETEOLMODE:
            {
                int i=m_scintilla1->GetEOLMode();

                if(i==wxSTC_EOL_CRLF)
                {
                    property->SetValueFromString("wxSTC_EOL_CRLF");
                }
                else if(i==wxSTC_EOL_CR)
                {
                    property->SetValueFromString("wxSTC_EOL_CR");
                }
                else if(i==wxSTC_EOL_LF)
                {
                    property->SetValueFromString("wxSTC_EOL_LF");
                }
                else
                {
                    property->SetValueFromString("(unknown EOL mode)");
                }
                rv=false;
            }
            break;
        case SCI_CONVERTEOLS:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                m_scintilla1->ConvertEOLs(l1);
                rv=false;
            }
            break;
        case SCI_SETVIEWEOL:
            {
                m_scintilla1->SetViewEOL( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETVIEWEOL:
            {
                property->SetValueFromString(m_scintilla1->GetViewEOL()?"True":"False");
                rv=true;
            }
            break;
        case SCI_GETENDSTYLED:
            {
                property->SetValueFromInt( m_scintilla1->GetEndStyled() );
                rv=true;
            }
            break;
        case SCI_STARTSTYLING:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                stylingPosition=l1;

                m_scintilla1->StartStyling(l1,l2);

                statusBar->SetStatusText(wxString::Format("Styling begun at position %d",stylingPosition), 1);

                rv=false;
            }
            break;
        case SCI_SETSTYLING:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                stylingPosition=stylingPosition+l1;

                statusBar->SetStatusText(wxString::Format("Styling from %d to %d set to %d.",stylingPosition-l1,stylingPosition-1,l2), 1);

                m_scintilla1->SetStyling(l1,l2);
                rv=false;
            }
            break;
        case SCI_SETSTYLINGEX:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty ()->GetValue();

                //I really should add some checks here to make sure that
                //stylingPosition+l1-1 is not past the end of the document.


//                MyProjectMyDialog2 md(this,MyProjectMyDialog2::SCI_SETSTYLINGEX);
//                md.setStyledText( m_scintilla1->GetStyledText(stylingPosition,stylingPosition+l1) );
//                md.ShowModal();
//
//                wxString s=md.getStyledText();
//                wxMemoryBuffer buf(l1);
//                for(int i=0;i<l1;i++)
//                {
//                    buf.AppendByte( s[2*i+1].GetValue() );
//                }

                MyProjectMyDialog5 md(this,m_scintilla1->GetStyleBits(), 0,MyProjectMyDialog5::SCI_SETSTYLINGEX);

                md.AddStyledText(m_scintilla1->GetStyledText(stylingPosition,stylingPosition+l1));
                md.SetReadOnly();

                int i = md.ShowModal();

                if( i== wxID_OK)
                {
                    m_scintilla1->SetStyleBytes( l1, const_cast<char *>(static_cast<const char*>(md.GetStyleString() )));

                    stylingPosition=stylingPosition+l1;
                    statusBar->SetStatusText(wxString::Format("Styling bits from %d to %d have been set.",stylingPosition-l1,stylingPosition-1), 1);
                }


//                m_scintilla1->SetStyleBytes(l1,reinterpret_cast<char*>(buf.GetData()));
//
//                stylingPosition=stylingPosition+l1;
//                statusBar->SetStatusText(wxString::Format("Styling bits from %d to %d have been set.",stylingPosition-l1,stylingPosition-1), 1);

                rv=false;
            }
            break;
        case SCI_SETLINESTATE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();
                it++;
                long l2=it.GetProperty ()->GetValue();

                m_scintilla1->SetLineState(l1,l2);
                rv=false;
            }
            break;
        case SCI_GETLINESTATE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1=it.GetProperty ()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetLineState(l1) );
                rv=true;
            }
            break;
        case SCI_GETMAXLINESTATE:
            {
                property->SetValueFromInt( m_scintilla1->GetMaxLineState() );
                rv=true;
            }
            break;

        case SCI_STYLERESETDEFAULT:
            {
                m_scintilla1->StyleResetDefault();
                statusBar->SetStatusText("wxSTC_STYLE_DEFAULT has been reset to its initial state.", 1);
                rv=false;
            }
            break;
        case SCI_STYLECLEARALL:
            {
                m_scintilla1->StyleClearAll();
                statusBar->SetStatusText("All style bytes have been set to 0.", 1);
                rv=false;
            }
            break;
        case SCI_STYLESETFONT:
            {
                myStyleData* msd = dynamic_cast<myStyleData*>(property->GetParent()->GetClientObject());
                m_scintilla1->StyleSetFaceName( msd->get_style() , m_propgrid->GetPropertyValueAsString(property) );

                rv=false;
            }
            break;
        case SCI_STYLEGETFONT:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromString( m_scintilla1->StyleGetFaceName(msd->get_style()) );
                rv=true;
            }
            break;
        case SCI_STYLESETSIZE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->StyleSetSize( msd->get_style() , property->GetValue().GetLong() );

                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                it++;
                it.GetProperty ()->SetValueFromInt(property->GetValue().GetLong() * wxSTC_FONT_SIZE_MULTIPLIER );

                rv=false;
            }
            break;
        case SCI_STYLEGETSIZE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromInt( m_scintilla1->StyleGetSize(msd->get_style()) );
                rv=true;
            }
            break;
        case SCI_STYLESETSIZEFRACTIONAL:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->StyleSetSizeFractional( msd->get_style() , property->GetValue().GetLong() );

//                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
//                it--;
//                it--;
//                it.GetProperty ()->SetValueFromInt(property->GetValue().GetLong() / wxSTC_FONT_SIZE_MULTIPLIER );

                rv=false;
            }
            break;
        case SCI_STYLEGETSIZEFRACTIONAL:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromInt( m_scintilla1->StyleGetSizeFractional(msd->get_style()) );

                rv=true;
            }
            break;
        case SCI_STYLESETBOLD:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->StyleSetBold( msd->get_style() , property->GetValue().GetBool() );

                rv=false;
            }
            break;
        case SCI_STYLEGETBOLD:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromString(m_scintilla1->StyleGetBold( msd->get_style() )?"True":"False");
                rv=true;
            }
            break;
        case SCI_STYLESETWEIGHT2:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());


                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;

                long l1 = property->GetValue().GetLong();

                if(l1==-1)
                {
                    it.GetProperty()->Enable(true);
                    //m_scintilla1->StyleSetWeight( msd->get_style() , property->GetValue().GetLong() );
                }
                else
                {
                    m_scintilla1->StyleSetWeight( msd->get_style() , property->GetValue().GetLong() );
                    it.GetProperty()->Enable(false);
                    it.GetProperty()->SetValueFromInt(property->GetValue().GetLong());
                }

                rv=false;
            }
            break;
        case SCI_STYLESETWEIGHT:
            {
                wxPGProperty* par = property->GetParent()->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->StyleSetWeight( msd->get_style() , property->GetValue().GetLong() );

                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_ALL,property);
                it--;
                it.GetProperty()->SetValueToUnspecified();

                rv=false;
            }
            break;
        case SCI_STYLEGETWEIGHT:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromInt(m_scintilla1->StyleGetWeight( msd->get_style() ) );
                rv=true;
            }
            break;
        case SCI_STYLESETITALIC:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->StyleSetItalic( msd->get_style() , property->GetValue().GetBool() );

                rv=false;
            }
            break;
        case SCI_STYLEGETITALIC:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromString(m_scintilla1->StyleGetItalic( msd->get_style() )?"True":"False");
                rv=true;
            }
            break;
        case SCI_STYLESETUNDERLINE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->StyleSetUnderline( msd->get_style() , property->GetValue().GetBool() );

                rv=false;
            }
            break;
        case SCI_STYLEGETUNDERLINE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromString(m_scintilla1->StyleGetUnderline( msd->get_style() )?"True":"False");
                rv=true;
            }
            break;
        case SCI_STYLESETFORE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                wxAny value = property->GetValue();
                m_scintilla1->StyleSetForeground( msd->get_style(),value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_STYLEGETFORE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());


                setColorString(property, m_scintilla1->StyleGetForeground( msd->get_style() ));
                rv=true;
            }
            break;
        case SCI_STYLESETBACK:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                wxAny value = property->GetValue();
                m_scintilla1->StyleSetBackground( msd->get_style(),value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_STYLEGETBACK:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                setColorString(property, m_scintilla1->StyleGetBackground( msd->get_style() ));
                rv=true;
            }
            break;
        case SCI_STYLESETEOLFILLED:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->StyleSetEOLFilled( msd->get_style() , property->GetValue().GetBool() );

                rv=false;
            }
            break;
        case SCI_STYLEGETEOLFILLED:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromString(m_scintilla1->StyleGetEOLFilled( msd->get_style() )?"True":"False");
                rv=true;
            }
            break;
        case SCI_STYLESETCHARACTERSET:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                //m_scintilla1->StyleSetCharacterSet( msd->get_style() , m_propgrid->GetPropertyValueAsInt(property) );
                m_scintilla1->SendMsg(2066,msd->get_style(),property->GetValue().GetLong() );

                rv=false;
            }
            break;
        case SCI_STYLEGETCHARACTERSET:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                int i=m_scintilla1->StyleGetCharacterSet( msd->get_style() );

                if(i==wxSTC_CHARSET_ANSI)
                {
                    property->SetValueFromString("wxSTC_CHARSET_ANSI");
                }
                else if(i==wxSTC_CHARSET_DEFAULT)
                {
                    property->SetValueFromString("wxSTC_CHARSET_DEFAULT");
                }
                else if(i==wxSTC_CHARSET_BALTIC)
                {
                    property->SetValueFromString("wxSTC_CHARSET_BALTIC");
                }
                else if(i==wxSTC_CHARSET_CHINESEBIG5)
                {
                    property->SetValueFromString("wxSTC_CHARSET_CHINESEBIG5");
                }
                else if(i==wxSTC_CHARSET_EASTEUROPE)
                {
                    property->SetValueFromString("wxSTC_CHARSET_EASTEUROPE");
                }
                else if(i==wxSTC_CHARSET_GB2312)
                {
                    property->SetValueFromString("wxSTC_CHARSET_GB2312");
                }
                else if(i==wxSTC_CHARSET_GREEK)
                {
                    property->SetValueFromString("wxSTC_CHARSET_GREEK");
                }
                else if(i==wxSTC_CHARSET_HANGUL)
                {
                    property->SetValueFromString("wxSTC_CHARSET_HANGUL");
                }
                else if(i==wxSTC_CHARSET_MAC)
                {
                    property->SetValueFromString("wxSTC_CHARSET_MAC");
                }
                else if(i==wxSTC_CHARSET_OEM)
                {
                    property->SetValueFromString("wxSTC_CHARSET_OEM");
                }
                else if(i==wxSTC_CHARSET_RUSSIAN)
                {
                    property->SetValueFromString("wxSTC_CHARSET_RUSSIAN");
                }
                else if(i==wxSTC_CHARSET_CYRILLIC)
                {
                    property->SetValueFromString("wxSTC_CHARSET_CYRILLIC");
                }
                else if(i==wxSTC_CHARSET_SHIFTJIS)
                {
                    property->SetValueFromString("wxSTC_CHARSET_SHIFTJIS");
                }
                else if(i==wxSTC_CHARSET_SYMBOL)
                {
                    property->SetValueFromString("wxSTC_CHARSET_SYMBOL");
                }
                else if(i==wxSTC_CHARSET_TURKISH)
                {
                    property->SetValueFromString("wxSTC_CHARSET_TURKISH");
                }
                else if(i==wxSTC_CHARSET_JOHAB)
                {
                    property->SetValueFromString("wxSTC_CHARSET_JOHAB");
                }
                else if(i==wxSTC_CHARSET_HEBREW)
                {
                    property->SetValueFromString("wxSTC_CHARSET_HEBREW");
                }
                else if(i==wxSTC_CHARSET_ARABIC)
                {
                    property->SetValueFromString("wxSTC_CHARSET_ARABIC");
                }
                else if(i==wxSTC_CHARSET_VIETNAMESE)
                {
                    property->SetValueFromString("wxSTC_CHARSET_VIETNAMESE");
                }
                else if(i==wxSTC_CHARSET_THAI)
                {
                    property->SetValueFromString("wxSTC_CHARSET_THAI");
                }
                else if(i==wxSTC_CHARSET_8859_15)
                {
                    property->SetValueFromString("wxSTC_CHARSET_8859_15");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown character set)",i));
                }

                rv=true;
            }
            break;
        case SCI_STYLESETCASE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->StyleSetCase( msd->get_style() , property->GetValue().GetLong() );

                rv=false;
            }
            break;
        case SCI_STYLEGETCASE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                int i=m_scintilla1->StyleGetCase( msd->get_style() );

                if(i==wxSTC_CASE_MIXED)
                {
                    property->SetValueFromString("wxSTC_CASE_MIXED");
                }
                else if(i==wxSTC_CASE_UPPER)
                {
                    property->SetValueFromString("wxSTC_CASE_UPPER");
                }
                else if(i==wxSTC_CASE_LOWER)
                {
                    property->SetValueFromString("wxSTC_CASE_LOWER");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown case)",i));
                }

                rv=true;
            }
            break;
        case SCI_STYLESETVISIBLE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->StyleSetVisible( msd->get_style() , property->GetValue().GetBool() );

                rv=false;
            }
            break;
        case SCI_STYLEGETVISIBLE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromString(m_scintilla1->StyleGetVisible( msd->get_style() )?"True":"False");
                rv=true;
            }
            break;
        case SCI_STYLESETCHANGEABLE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->StyleSetChangeable( msd->get_style() , property->GetValue().GetBool() );

                rv=false;
            }
            break;
        case SCI_STYLEGETCHANGEABLE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromString(m_scintilla1->StyleGetChangeable( msd->get_style() )?"True":"False");
                rv=true;
            }
            break;
        case SCI_STYLESETHOTSPOT:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->StyleSetHotSpot( msd->get_style() , property->GetValue().GetBool() );

                rv=false;
            }
            break;
        case SCI_STYLEGETHOTSPOT:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromString(m_scintilla1->StyleGetHotSpot( msd->get_style() )?"True":"False");
                rv=true;
            }
            break;

        case SCI_SETSELFORE:
            {
                rv=false;
            }
            break;
        case SCI_SETSELFOREPARM1:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxAny value = it.GetProperty()->GetValue();

                if(property->GetValue().GetBool())
                {
                    m_scintilla1->SetSelForeground( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetSelForeground( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;
        case SCI_SETSELFOREPARM2:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it--;
                wxAny value = property->GetValue();

                if(it.GetProperty()->GetValue().GetBool())
                {
                    m_scintilla1->SetSelForeground( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetSelForeground( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;
        case SCI_SETSELBACK:
            {
                rv=false;
            }
            break;

        case SCI_SETSELBACKPARM1:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxAny value = it.GetProperty()->GetValue();

                if(property->GetValue().GetBool())
                {
                    m_scintilla1->SetSelBackground( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetSelBackground( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;
        case SCI_SETSELBACKPARM2:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it--;
                wxAny value = property->GetValue();

                if(it.GetProperty()->GetValue().GetBool())
                {
                    m_scintilla1->SetSelBackground( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetSelBackground( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;

        case SCI_SETSELALPHA:
            {
                m_scintilla1->SetSelAlpha( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETSELALPHA:
            {
                property->SetValueFromInt(m_scintilla1->GetSelAlpha());
                rv=true;
            }
            break;
        case SCI_SETSELEOLFILLED:
            {
                m_scintilla1->SetSelEOLFilled( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETSELEOLFILLED:
            {
                property->SetValueFromString(m_scintilla1->GetSelEOLFilled()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETCARETFORE:
            {
                wxAny value = property->GetValue();
                m_scintilla1->SetCaretForeground( value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_GETCARETFORE:
            {
                //property->SetValueFromString( m_scintilla1->GetCaretForeground().GetAsString() );
                setColorString( property, m_scintilla1->GetCaretForeground() );
                rv=true;
            }
            break;
        case SCI_SETCARETLINEVISIBLE:
            {
                m_scintilla1->SetCaretLineVisible( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETCARETLINEVISIBLE:
            {
                property->SetValueFromString(m_scintilla1->GetCaretLineVisible()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETCARETLINEBACK:
            {
                wxAny value = property->GetValue();
                m_scintilla1->SetCaretLineBackground( value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_GETCARETLINEBACK:
            {
                //property->SetValueFromString( m_scintilla1->GetCaretLineBackground().GetAsString() );
                setColorString( property, m_scintilla1->GetCaretLineBackground() );
                rv=true;
            }
            break;
        case SCI_SETCARETLINEBACKALPHA:
            {
                m_scintilla1->SetCaretLineBackAlpha( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETCARETLINEBACKALPHA:
            {
                property->SetValueFromInt( m_scintilla1->GetCaretLineBackAlpha() );
                rv=true;
            }
            break;
        case SCI_SETCARETPERIOD:
            {
                m_scintilla1->SetCaretPeriod( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETCARETPERIOD:
            {
                property->SetValueFromInt( m_scintilla1->GetCaretPeriod() );
                rv=true;
            }
            break;
        case SCI_SETCARETSTYLE:
            {
                m_scintilla1->SetCaretStyle( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETCARETSTYLE:
            {
                int i=m_scintilla1->GetCaretStyle();

                if(i==wxSTC_CARETSTYLE_INVISIBLE)
                {
                    property->SetValueFromString("wxSTC_CARETSTYLE_INVISIBLE");
                }
                else if(i==wxSTC_CARETSTYLE_LINE)
                {
                    property->SetValueFromString("wxSTC_CARETSTYLE_LINE");
                }
                else if(i==wxSTC_CARETSTYLE_BLOCK)
                {
                    property->SetValueFromString("wxSTC_CARETSTYLE_BLOCK");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown caret style)",i));
                }

                rv=true;
            }
            break;
        case SCI_SETCARETWIDTH:
            {
                m_scintilla1->SetCaretWidth( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETCARETWIDTH:
            {
                property->SetValueFromInt( m_scintilla1->GetCaretWidth() );
                rv=true;
            }
            break;
        case SCI_SETHOTSPOTACTIVEFORE:
            {
                rv=false;
            }
            break;

        case SCI_SETHOTSPOTACTIVEFOREPARM1:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxAny value = it.GetProperty()->GetValue();

                if(property->GetValue().GetBool())
                {
                    m_scintilla1->SetHotspotActiveForeground( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetHotspotActiveForeground( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;

        case SCI_SETHOTSPOTACTIVEFOREPARM2:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it--;
                wxAny value = property->GetValue();

                if(it.GetProperty()->GetValue().GetBool())
                {
                    m_scintilla1->SetHotspotActiveForeground( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetHotspotActiveForeground( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;

        case SCI_GETHOTSPOTACTIVEFORE:
            {
                //property->SetValueFromString( m_scintilla1->GetHotspotActiveForeground().GetAsString() );
                setColorString( property, m_scintilla1->GetHotspotActiveForeground() );
                rv=true;
            }
            break;

        case SCI_SETHOTSPOTACTIVEBACK:
            {
                rv=false;
            }
            break;
        case SCI_SETHOTSPOTACTIVEBACKPARM1:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxAny value = it.GetProperty()->GetValue();

                if(property->GetValue().GetBool())
                {
                    m_scintilla1->SetHotspotActiveBackground( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetHotspotActiveBackground( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;

        case SCI_SETHOTSPOTACTIVEBACKPARM2:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it--;
                wxAny value = property->GetValue();

                if(it.GetProperty()->GetValue().GetBool())
                {
                    m_scintilla1->SetHotspotActiveBackground( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetHotspotActiveBackground( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;

        case SCI_GETHOTSPOTACTIVEBACK:
            {
                //property->SetValueFromString( m_scintilla1->GetHotspotActiveBackground().GetAsString() );
                setColorString( property, m_scintilla1->GetHotspotActiveBackground() );
                rv=true;
            }
            break;
        case SCI_SETHOTSPOTACTIVEUNDERLINE:
            {
                m_scintilla1->SetHotspotActiveUnderline( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETHOTSPOTACTIVEUNDERLINE:
            {
                property->SetValueFromString(m_scintilla1->GetHotspotActiveUnderline()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETHOTSPOTSINGLELINE:
            {
                m_scintilla1->SetHotspotSingleLine( property->GetValue().GetBool() );
                rv=true;
            }
            break;
        case SCI_GETHOTSPOTSINGLELINE:
            {
                property->SetValueFromString(m_scintilla1->GetHotspotSingleLine()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETCONTROLCHARSYMBOL:
            {
                m_scintilla1->SetControlCharSymbol( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETCONTROLCHARSYMBOL:
            {
                property->SetValueFromInt(m_scintilla1->GetControlCharSymbol());
                rv=true;
            }
            break;
        case SCI_SETCARETSTICKY:
            {
                m_scintilla1->SetCaretSticky( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETCARETSTICKY:
            {
                int i=m_scintilla1->GetCaretSticky();

                if(i==wxSTC_CARETSTICKY_OFF)
                {
                    property->SetValueFromString("wxSTC_CARETSTICKY_OFF");
                }
                else if(i==wxSTC_CARETSTICKY_ON)
                {
                    property->SetValueFromString("wxSTC_CARETSTICKY_ON");
                }
                else if(i==wxSTC_CARETSTICKY_WHITESPACE)
                {
                    property->SetValueFromString("wxSTC_CARETSTICKY_WHITESPACE");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown caret sticky value)",i));
                }

                rv=true;
            }
            break;
        case SCI_TOGGLECARETSTICKY:
            {
                m_scintilla1->ToggleCaretSticky();


                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it--;
                it--;

                it.GetProperty()->SetValueToUnspecified();

                rv=false;
            }
            break;

        case SCI_SETMARGINTYPEN:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                m_scintilla1->SetMarginType( msd->get_style(),property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETMARGINTYPEN:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                int i=m_scintilla1->GetMarginType( msd->get_style() );

                if(i==wxSTC_MARGIN_SYMBOL)
                {
                    property->SetValueFromString("wxSTC_MARGIN_SYMBOL");
                }
                else if(i==wxSTC_MARGIN_NUMBER)
                {
                    property->SetValueFromString("wxSTC_MARGIN_NUMBER");
                }
                else if(i==wxSTC_MARGIN_BACK)
                {
                    property->SetValueFromString("wxSTC_MARGIN_BACK");
                }
                else if(i==wxSTC_MARGIN_FORE)
                {
                    property->SetValueFromString("wxSTC_MARGIN_FORE");
                }
                else if(i==wxSTC_MARGIN_TEXT)
                {
                    property->SetValueFromString("wxSTC_MARGIN_TEXT");
                }
                else if(i==wxSTC_MARGIN_RTEXT)
                {
                    property->SetValueFromString("wxSTC_MARGIN_RTEXT");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown margin type)",i));
                }

                rv= true;
            }
            break;
        case SCI_SETMARGINWIDTHN:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->SetMarginWidth( msd->get_style(),property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETMARGINWIDTHN:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                property->SetValueFromInt( m_scintilla1->GetMarginWidth( msd->get_style() ));
                rv= true;
            }
            break;
        case SCI_SETMARGINMASKN:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;

                long l = property->GetValue().GetLong();
                if(l==-1)
                {
                    it.GetProperty()->Enable(true);
                    m_scintilla1->SetMarginMask( msd->get_style() , it.GetProperty()->GetValue().GetLong() );
                }
                else
                {
                    it.GetProperty()->Enable(false);
                    it.GetProperty()->SetValueFromInt(l);
                    m_scintilla1->SetMarginMask( msd->get_style() , property->GetValue().GetLong() );
                }

                rv=false;
            }
            break;
        case SCI_SETMARGINMASKN2:
            {
                wxPGProperty* par = property->GetParent()->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                m_scintilla1->SetMarginMask( msd->get_style() , property->GetValue().GetLong() );
                rv=false;
            }
            break;

        case SCI_GETMARGINMASKN:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                long l = m_scintilla1->GetMarginMask( msd->get_style() );
                wxString s;

                for(int i=0;i<32;i++)
                {
                    if(l&(1<<i))
                    {
                        s.Prepend("1");
                    }
                    else
                    {
                        s.Prepend("0");
                    }
                }

                property->SetValueFromString(s);
                rv= true;
            }
            break;
        case SCI_SETMARGINSENSITIVEN:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                m_scintilla1->SetMarginSensitive( msd->get_style() , property->GetValue().GetBool());
                rv=false;
            }
            break;
        case SCI_GETMARGINSENSITIVEN:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                property->SetValueFromString(m_scintilla1->GetMarginSensitive(msd->get_style())?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETMARGINCURSORN:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                m_scintilla1->SetMarginCursor( msd->get_style() , property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETMARGINCURSORN:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                int i=m_scintilla1->GetMarginCursor(msd->get_style());

                if(i==wxSTC_CURSORNORMAL)
                {
                    property->SetValueFromString("wxSTC_CURSORNORMAL");
                }
                else if(i==wxSTC_CURSORARROW)
                {
                    property->SetValueFromString("wxSTC_CURSORARROW");
                }
                else if(i==wxSTC_CURSORWAIT)
                {
                    property->SetValueFromString("wxSTC_CURSORWAIT");
                }
                else if(i==wxSTC_CURSORREVERSEARROW)
                {
                    property->SetValueFromString("wxSTC_CURSORREVERSEARROW");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown cursor number)",i));
                }
                rv=true;
            }
            break;
        case SCI_SETMARGINLEFT:
            {
                m_scintilla1->SetMarginLeft( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETMARGINLEFT:
            {
                property->SetValueFromInt(m_scintilla1->GetMarginLeft());
                rv=true;
            }
            break;
        case SCI_SETMARGINRIGHT:
            {
                m_scintilla1->SetMarginRight( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETMARGINRIGHT:
            {
                property->SetValueFromInt(m_scintilla1->GetMarginRight());
                rv=true;
            }
            break;
        case SCI_SETFOLDMARGINCOLOUR:
            {
                rv=false;
            }
            break;

        case SCI_SETFOLDMARGINCOLOURPARM1:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxAny value = it.GetProperty()->GetValue();

                if(property->GetValue().GetBool())
                {
                    m_scintilla1->SetFoldMarginColour( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetFoldMarginColour( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;

        case SCI_SETFOLDMARGINCOLOURPARM2:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it--;
                wxAny value = property->GetValue();

                if(it.GetProperty()->GetValue().GetBool())
                {
                    m_scintilla1->SetFoldMarginColour( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetFoldMarginColour( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;

        case SCI_SETFOLDMARGINHICOLOUR:
            {
                rv=false;
            }
            break;

        case SCI_SETFOLDMARGINHICOLOURPARM1:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxAny value = it.GetProperty()->GetValue();

                if(property->GetValue().GetBool())
                {
                    m_scintilla1->SetFoldMarginHiColour( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetFoldMarginHiColour( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;

        case SCI_SETFOLDMARGINHICOLOURPARM2:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it--;
                wxAny value = property->GetValue();

                if(it.GetProperty()->GetValue().GetBool())
                {
                    m_scintilla1->SetFoldMarginHiColour( true,value.As<wxColour>() );
                }
                else
                {
                    m_scintilla1->SetFoldMarginHiColour( false,value.As<wxColour>() );
                }

                rv=false;
            }
            break;

        case SCI_MARGINSETTEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                wxString s = it.GetProperty()->GetValue();

                m_scintilla1->MarginSetText( l1,s );

                rv=false;
            }
            break;
        case SCI_MARGINGETTEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromString(m_scintilla1->MarginGetText(l1));
                rv=true;
            }
            break;
        case SCI_MARGINSETSTYLE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->MarginSetStyle( l1,l2 );

                rv=false;
            }
            break;
        case SCI_MARGINGETSTYLE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt(m_scintilla1->MarginGetStyle(l1));
                rv=true;
            }
            break;
        case SCI_MARGINSETSTYLES:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                wxString text=m_scintilla1->MarginGetText(l1);

//                if(text.IsEmpty())
//                {
//                    wxString s = wxString::Format("No margin text has been set for line %d.",l1);
//                    wxMessageBox(s);
//                }
//                else
//                {
                    MyProjectMyDialog5 md(this,8,m_scintilla1->MarginGetStyleOffset(),MyProjectMyDialog5::SCI_SETSTYLINGEX);

                    md.addText(text);
                    md.addStyle(m_scintilla1->MarginGetStyles(l1));
                    md.SetReadOnly();
                    int i = md.ShowModal();

                    if(i==wxID_OK)
                    {
                        m_scintilla1->MarginSetStyles( l1, md.GetStyleString() );
                    }
//                }

                rv=false;
            }
            break;
        case SCI_MARGINGETSTYLES:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                wxString text=m_scintilla1->MarginGetText(l1);
                wxString styles=m_scintilla1->MarginGetStyles(l1);

                MyProjectMyDialog5 md(this,8,m_scintilla1->MarginGetStyleOffset(),MyProjectMyDialog5::SCI_GETSTYLEDTEXT);

                md.addText(text);
                md.addStyle(styles);
                md.SetReadOnly();
                md.ShowModal();

//                wxMemoryBuffer buf(2*text.length());
//
//                for(size_t i=0;i<2*text.length();i=i+2)
//                {
//                    buf.AppendByte(text[i/2].GetValue());
//                    buf.AppendByte(styles[i/2].GetValue());
//                }
//
//                MyProjectMyDialog2 md(this,MyProjectMyDialog2::SCI_GETSTYLEDTEXT);
//                md.setStyledText( buf );
//                md.ShowModal();

                rv=false;
            }
            break;
        case SCI_MARGINTEXTCLEARALL:
            {
                m_scintilla1->MarginTextClearAll();
                rv=false;
            }
            break;
        case SCI_MARGINSETSTYLEOFFSET:
            {
                m_scintilla1->MarginSetStyleOffset(property->GetValue().GetLong());
                rv=false;
            }
            break;
        case SCI_MARGINGETSTYLEOFFSET:
            {
                property->SetValueFromInt(m_scintilla1->MarginGetStyleOffset());
                rv=true;
            }
            break;
        case SCI_SETMARGINOPTIONS:
            {
                m_scintilla1->SetMarginOptions(property->GetValue().GetLong());
                rv=false;
            }
            break;
        case SCI_GETMARGINOPTIONS:
            {
                int i=m_scintilla1->GetMarginOptions();

                if(i==wxSTC_MARGINOPTION_NONE)
                {
                    property->SetValueFromString("wxSTC_MARGINOPTION_NONE");
                }
                else if(i==wxSTC_MARGINOPTION_SUBLINESELECT)
                {
                    property->SetValueFromString("wxSTC_MARGINOPTION_SUBLINESELECT");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - margin options number)",i));
                }
                rv=true;
            }
            break;

        case SCI_ANNOTATIONSETTEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                wxString s = it.GetProperty()->GetValue();
                s.Replace("\\n","\n",true);

                m_scintilla1->AnnotationSetText( l1,s );

                rv=false;
            }
            break;
        case SCI_ANNOTATIONGETTEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromString(m_scintilla1->AnnotationGetText(l1));
                rv=true;
            }
            break;
        case SCI_ANNOTATIONSETSTYLE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->AnnotationSetStyle( l1,l2 );

                rv=false;
            }
            break;
        case SCI_ANNOTATIONGETSTYLE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt(m_scintilla1->AnnotationGetStyle(l1));
                rv=true;
            }
            break;
        case SCI_ANNOTATIONSETSTYLES:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                wxString text=m_scintilla1->AnnotationGetText(l1);

                if(text.IsEmpty())
                {
                    wxMessageBox(wxString::Format("There is no annotation text for line %d.",l1));
                }
                else
                {
                    MyProjectMyDialog5 md(this,8,0,MyProjectMyDialog5::SCI_SETSTYLINGEX);

                    md.addText(text);
                    md.addStyle(m_scintilla1->AnnotationGetStyles(l1));
                    int i = md.ShowModal();

                    if(i==wxID_OK)
                    {
                        m_scintilla1->AnnotationSetStyles(l1,md.GetStyleString());
                    }

                }

                rv=false;
            }
            break;
        case SCI_ANNOTATIONGETSTYLES:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                wxString text=m_scintilla1->AnnotationGetText(l1);
                wxString styles=m_scintilla1->AnnotationGetStyles(l1);

                MyProjectMyDialog5 md(this,8,0,MyProjectMyDialog5::SCI_GETSTYLEDTEXT);
                md.addText(text);
                md.addStyle(styles);
                md.SetReadOnly();

                md.ShowModal();

                rv=false;
            }
            break;
        case SCI_ANNOTATIONGETLINES:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt(m_scintilla1->AnnotationGetLines(l1));
                rv=true;
            }
            break;
        case SCI_ANNOTATIONCLEARALL:
            {
                //if the change event is being logged, this can trigger so many
                //events that the logging will crash the program.
                //I should add something to disconnect the event handler before calling this


                m_scintilla1->AnnotationClearAll();


                rv=false;
            }
            break;
        case SCI_ANNOTATIONSETVISIBLE:
            {
                m_scintilla1->AnnotationSetVisible(property->GetValue().GetLong());
                rv=false;
            }
            break;
        case SCI_ANNOTATIONGETVISIBLE:
            {
                int i=m_scintilla1->AnnotationGetVisible();

                if(i==wxSTC_ANNOTATION_HIDDEN)
                {
                    property->SetValueFromString("wxSTC_ANNOTATION_HIDDEN");
                }
                else if(i==wxSTC_ANNOTATION_STANDARD)
                {
                    property->SetValueFromString("wxSTC_ANNOTATION_STANDARD");
                }
                else if(i==wxSTC_ANNOTATION_BOXED)
                {
                    property->SetValueFromString("wxSTC_ANNOTATION_BOXED");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown attotation visibility option)",i));
                }
                rv=true;
            }
            break;
        case SCI_ANNOTATIONSETSTYLEOFFSET:
            {
                m_scintilla1->AnnotationSetStyleOffset(property->GetValue().GetLong());
                rv=false;
            }
            break;
        case SCI_ANNOTATIONGETSTYLEOFFSET:
            {
                property->SetValueFromInt(m_scintilla1->AnnotationGetStyleOffset());
                rv=true;
            }
            break;

        case SCI_SETUSEPALETTE:
            {
                rv=false;
            }
            break;
        case SCI_GETUSEPALETTE:
            {
                rv=false;
            }
            break;
        case SCI_SETBUFFEREDDRAW:
            {
                m_scintilla1->SetBufferedDraw(property->GetValue().GetBool());
                rv=false;
            }
            break;
        case SCI_GETBUFFEREDDRAW:
            {
                property->SetValueFromString(m_scintilla1->GetBufferedDraw()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETTWOPHASEDRAW:
            {
                m_scintilla1->SetTwoPhaseDraw(property->GetValue().GetBool());
                rv=false;
            }
            break;
        case SCI_GETTWOPHASEDRAW:
            {
                property->SetValueFromString(m_scintilla1->GetTwoPhaseDraw()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETTECHNOLOGY:
            {
                m_scintilla1->SetTechnology(property->GetValue().GetLong());
                rv=false;
            }
            break;
        case SCI_GETTECHNOLOGY:
            {
                int i=m_scintilla1->GetTechnology();

                if(i==wxSTC_TECHNOLOGY_DEFAULT)
                {
                    property->SetValueFromString("wxSTC_TECHNOLOGY_DEFAULT");
                }
                else if(i==wxSTC_TECHNOLOGY_DIRECTWRITE)
                {
                    property->SetValueFromString("wxSTC_TECHNOLOGY_DIRECTWRITE");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown technology)",i));
                }
                rv=true;
            }
            break;
        case SCI_SETFONTQUALITY:
            {
                m_scintilla1->SendMsg(2611,property->GetValue().GetLong(),0);
                rv=false;
            }
            break;
        case SCI_GETFONTQUALITY:
            {
                int i=m_scintilla1->SendMsg(2612,0,0);

                if(i==wxSTC_EFF_QUALITY_DEFAULT)
                {
                    property->SetValueFromString("wxSTC_EFF_QUALITY_DEFAULT");
                }
                else if(i==wxSTC_EFF_QUALITY_NON_ANTIALIASED)
                {
                    property->SetValueFromString("wxSTC_EFF_QUALITY_NON_ANTIALIASED");
                }
                else if(i==wxSTC_EFF_QUALITY_ANTIALIASED)
                {
                    property->SetValueFromString("wxSTC_EFF_QUALITY_ANTIALIASED");
                }
                else if(i==wxSTC_EFF_QUALITY_LCD_OPTIMIZED)
                {
                    property->SetValueFromString("wxSTC_EFF_QUALITY_LCD_OPTIMIZED");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown font quality)",i));
                }
                rv=true;
            }
            break;
        case SCI_SETCODEPAGE:
            {
                m_scintilla1->SetCodePage(property->GetValue().GetLong());
                rv=false;
            }
            break;
        case SCI_GETCODEPAGE:
            {
                int i=m_scintilla1->GetCodePage();

                if(i==0)
                {
                    property->SetValueFromString("0");
                }
                else if(i==wxSTC_CP_UTF8)
                {
                    property->SetValueFromString("wxSTC_CP_UTF8");
                }
                else if(i==932)
                {
                    property->SetValueFromString("Japanese Shift-JIS");
                }
                else if(i==936)
                {
                    property->SetValueFromString("Simplified Chinese GBK");
                }
                else if(i==949)
                {
                    property->SetValueFromString("Korean Unified Hangul Code");
                }
                else if(i==950)
                {
                    property->SetValueFromString("Traditional Chinese Big5");
                }
                else if(i==1361)
                {
                    property->SetValueFromString("Korean Johab");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown code page)",i));
                }
                rv=true;
            }
            break;
        case SCI_SETKEYSUNICODE:
            {
                m_scintilla1->SetKeysUnicode(property->GetValue().GetBool());
                rv=false;
            }
            break;
        case SCI_GETKEYSUNICODE:
            {
                property->SetValueFromString(m_scintilla1->GetKeysUnicode()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETWORDCHARS:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();

                m_scintilla1->SetWordChars(s);
                rv=false;
            }
            break;
        case SCI_GETWORDCHARS:
            {
                property->SetValueFromString( m_scintilla1->GetWordChars() );
                rv=true;
            }
            break;
        case SCI_SETWHITESPACECHARS:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();

                m_scintilla1->SetWhitespaceChars(s);
                rv=false;
            }
            break;
        case SCI_GETWHITESPACECHARS:
            {
                property->SetValueFromString( m_scintilla1->GetWhitespaceChars() );
                rv=true;
            }
            break;
        case SCI_SETPUNCTUATIONCHARS:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();

                m_scintilla1->SetPunctuationChars(s);
                rv=false;
            }
            break;
        case SCI_GETPUNCTUATIONCHARS:
            {
                property->SetValueFromString( m_scintilla1->GetPunctuationChars() );
                rv=true;
            }
            break;
        case SCI_SETCHARSDEFAULT:
            {
                m_scintilla1->SetCharsDefault();
                rv=false;
            }
            break;
        case SCI_GRABFOCUS:
            {
                m_scintilla1->SendMsg(2400,0,0);
                rv=false;
            }
            break;
        case SCI_SETFOCUS:
            {
                m_scintilla1->SetSTCFocus(property->GetValue().GetBool());
                rv=false;
            }
            break;
        case SCI_GETFOCUS:
            {
                property->SetValueFromString(m_scintilla1->GetSTCFocus()?"True":"False");
                rv=true;
            }
            break;

        case SCI_BRACEHIGHLIGHT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->BraceHighlight(l1,l2);
                rv=false;
            }
            break;
        case SCI_BRACEBADLIGHT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                m_scintilla1->BraceBadLight(l1);
                rv=false;
            }
            break;
        case SCI_BRACEHIGHLIGHTINDICATOR:
            {
                rv=false;
            }
            break;
        case SCI_BRACEHIGHLIGHTINDICATORPARM1:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                bool b = property->GetValue().GetBool();
                it++;
                long l1 = it.GetProperty()->GetValue();

                m_scintilla1->BraceHighlightIndicator(b,l1);
                //statusBar->SetStatusText(wxString::Format("parm1:Indicator %d set=%s",l1,(b?"true":"false")), 1);
                rv=false;
            }
            break;
        case SCI_BRACEHIGHLIGHTINDICATORPARM2:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                long l1 = property->GetValue();
                it--;
                bool b = it.GetProperty()->GetValue().GetBool();

                m_scintilla1->BraceHighlightIndicator(b,l1);

                //statusBar->SetStatusText(wxString::Format("parm2:Indicator %d set=%s",l1,(b?"true":"false")), 1);
                rv=false;
            }
        case SCI_BRACEBADLIGHTINDICATOR:
            {
                rv=false;
            }
            break;
        case SCI_BRACEBADLIGHTINDICATORPARM1:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                bool b = property->GetValue().GetBool();
                it++;
                long l1 = it.GetProperty()->GetValue();

                m_scintilla1->BraceBadLightIndicator(b,l1);
                rv=false;
            }
            break;
        case SCI_BRACEBADLIGHTINDICATORPARM2:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                long l1 = property->GetValue();
                it--;
                bool b = it.GetProperty()->GetValue().GetBool();

                m_scintilla1->BraceBadLightIndicator(b,l1);
                rv=false;
            }
        case SCI_BRACEMATCH:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt( m_scintilla1->BraceMatch(l1) );
                rv=true;
            }
            break;

        case SCI_SETTABWIDTH:
            {
                m_scintilla1->SetTabWidth( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETTABWIDTH:
            {
                property->SetValueFromInt( m_scintilla1->GetTabWidth() );
                rv=true;
            }
            break;
        case SCI_SETUSETABS:
            {
                m_scintilla1->SetUseTabs( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETUSETABS:
            {
                property->SetValueFromString(m_scintilla1->GetUseTabs()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETINDENT:
            {
                m_scintilla1->SetIndent( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETINDENT:
            {
                property->SetValueFromInt(m_scintilla1->GetIndent());
                rv=true;
            }
            break;
        case SCI_SETTABINDENTS:
            {
                m_scintilla1->SetTabIndents( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETTABINDENTS:
            {
                property->SetValueFromString(m_scintilla1->GetTabIndents()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETBACKSPACEUNINDENTS:
            {
                m_scintilla1->SetBackSpaceUnIndents( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_GETBACKSPACEUNINDENTS:
            {
                property->SetValueFromString(m_scintilla1->GetBackSpaceUnIndents()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETLINEINDENTATION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->SetLineIndentation(l1,l2);
                rv=false;
            }
            break;
        case SCI_GETLINEINDENTATION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetLineIndentation(l1) );
                rv=true;
            }
            break;
        case SCI_GETLINEINDENTPOSITION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetLineIndentPosition(l1) );
                rv=true;
            }
            break;
        case SCI_SETINDENTATIONGUIDES:
            {
                m_scintilla1->SetIndentationGuides( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETINDENTATIONGUIDES:
            {
                int i=m_scintilla1->GetIndentationGuides();

                if(i==wxSTC_IV_NONE)
                {
                    property->SetValueFromString("wxSTC_IV_NONE");
                }
                else if(i==wxSTC_IV_REAL)
                {
                    property->SetValueFromString("wxSTC_IV_REAL");
                }
                else if(i==wxSTC_IV_LOOKFORWARD)
                {
                    property->SetValueFromString("wxSTC_IV_LOOKFORWARD");
                }
                else if(i==wxSTC_IV_LOOKBOTH)
                {
                    property->SetValueFromString("wxSTC_IV_LOOKBOTH");
                }
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown indentation guides value)",i));
                }
                rv=true;
            }
            break;
        case SCI_SETHIGHLIGHTGUIDE:
            {
//                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
//                it++;
//                long l1 = it.GetProperty()->GetValue();

                m_scintilla1->SetHighlightGuide( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETHIGHLIGHTGUIDE:
            {
                property->SetValueFromInt( m_scintilla1->GetHighlightGuide() );
                rv=true;
            }
            break;
        case SCI_MARKERDEFINE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                int j=msd->get_style();
                long val = property->GetValue().GetLong();

                if(val==wxSTC_MARK_CHARACTER)
                {
                    wxString currentFontName = m_scintilla1->StyleGetFaceName(wxSTC_STYLE_LINENUMBER);
                    if(currentFontName=="")
                    {
                        currentFontName = m_scintilla1->StyleGetFaceName(wxSTC_STYLE_DEFAULT);
                    }

                    wxSymbolPickerDialog dlg(" ", currentFontName, currentFontName, this);

                    if (dlg.ShowModal() == wxID_OK)
                    {
                        m_propgrid->HideProperty(markerDefineCharacter[j], false);
                        markerDefineCharacter[j]->SetValueFromString(wxString::Format("%d - '%s'",dlg.GetSymbolChar(),dlg.GetSymbol()));

                        m_scintilla1->MarkerDefine( j, wxSTC_MARK_CHARACTER + dlg.GetSymbolChar() );

                        markerDefineRGBAImage[j]->SetValueToUnspecified();
                        markerDefinePixmap[j]->SetValueToUnspecified();
                        markerDefinePixmap2[j]->SetValueToUnspecified();

                        //we should return true since the property has changed, but for
                        //some reason, that makes the dialog appear a second time.  returning
                        //false seems to prevent that and doesn't seem to cause any other problems
                    }
                    else
                    {
                        //dialog was cancelled - the choice will now say "wxSTC_MARK_CHARACTER"
                        //but that's incorrect since the dialog was cancelled.  We'll set it to
                        //the previous value if it was a marker or unspecified if the previous
                        //value was a pixmap or rgba data.

                        val=m_scintilla1->GetMarkerSymbolDefined(j);

                        if(val==wxSTC_MARK_PIXMAP || val==wxSTC_MARK_RGBAIMAGE)
                        {
                            property->SetValueToUnspecified();
                        }
                        else
                        {
                            property->SetValueFromInt(val);
                        }
                    }
                }
                else
                {
                    m_scintilla1->MarkerDefine( j , val );
                    m_propgrid->HideProperty(markerDefineCharacter[j], true);

                    markerDefineRGBAImage[j]->SetValueToUnspecified();
                    markerDefinePixmap[j]->SetValueToUnspecified();
                    markerDefinePixmap2[j]->SetValueToUnspecified();
                }

                rv=false;
            }
            break;
        case SCI_MARKERDEFINECHARACTER:
            {
                wxPGProperty* par = property->GetParent()->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                int j=msd->get_style();

                wxString currentFontName = m_scintilla1->StyleGetFaceName(wxSTC_STYLE_LINENUMBER);
                if(currentFontName=="")
                {
                    currentFontName = m_scintilla1->StyleGetFaceName(wxSTC_STYLE_DEFAULT);
                }

                //The previous value was something like "65 - '@'"
                //I want to get the character between the single quotes and use it
                //as the initial choice for the dialog.

                wxString temp=property->GetValueAsString();

                temp=temp.Right(temp.length()-temp.Find("\'")-1);
                temp=temp.Left(1);

                wxSymbolPickerDialog dlg(temp, currentFontName, currentFontName, this);

                if (dlg.ShowModal() == wxID_OK)
                {
                    markerDefineCharacter[j]->SetValueFromString(wxString::Format("%d - '%s'",dlg.GetSymbolChar(),dlg.GetSymbol()));
                    m_scintilla1->MarkerDefine( j, wxSTC_MARK_CHARACTER + dlg.GetSymbolChar() );
                }

                rv=false;
            }
            break;
        case SCI_MARKERDEFINEPIXMAP:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());
                int j=msd->get_style();

                wxBitmap bm(property->GetValueAsString(),wxBITMAP_TYPE_ANY);

                if(bm.IsOk())
                {
                    m_scintilla1->MarkerDefineBitmap( j, bm );

                    m_propgrid->HideProperty(markerDefineCharacter[j], true);
                    markerDefinitions[j]->SetValueToUnspecified();
                    markerDefineRGBAImage[j]->SetValueToUnspecified();
                    markerDefinePixmap2[j]->SetValueToUnspecified();
                }

                rv=false;
            }
            break;
        case SCI_RGBAIMAGESETWIDTH:
            {
                long l=property->GetValue().GetLong();

                for(int i=0;i<=wxSTC_MARKER_MAX;i++)
                {
                    if(markerRGBAWidth[i]!=property)
                    {
                        markerRGBAWidth[i]->SetValueFromInt(l);
                    }
                }
                m_scintilla1->RGBAImageSetWidth( l );
                rv=false;
            }
            break;
        case SCI_RGBAIMAGESETHEIGHT:
            {
                long l=property->GetValue().GetLong();

                for(int i=0;i<=wxSTC_MARKER_MAX;i++)
                {
                    if(markerRGBAHeight[i]!=property)
                    {
                        markerRGBAHeight[i]->SetValueFromInt(l);
                    }
                }
                m_scintilla1->RGBAImageSetHeight( l );
                rv=false;
            }
            break;
        case SCI_MARKERDEFINERGBAIMAGE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                int height,width;

                width = markerRGBAWidth[0]->GetValue().GetLong();
                height = markerRGBAHeight[0]->GetValue().GetLong();

                if(height==0 || width==0)
                {
                    wxMessageBox("You must first set RGBAImageSetWidth and\n"
                                 "RGBAImageSetHeight to nonzero values."
                                 );
                }
                else
                {
                    RGBADialog md(this,height,width);
                    int i=md.ShowModal();

                    if(i==wxID_OK)
                    {
                        int j=msd->get_style();

                        if(markerRGBAData[j]!=nullptr)
                        {
                            free(markerRGBAData[j]);
                            markerRGBAData[j]=nullptr;
                        }

                        md.getRGBAData( &markerRGBAData[j] );
                        m_scintilla1->MarkerDefineRGBAImage( j, markerRGBAData[j] );

                        markerDefinitions[j]->SetValueToUnspecified();
                        markerDefinePixmap[j]->SetValueToUnspecified();
                        markerDefinePixmap2[j]->SetValueToUnspecified();
                        m_propgrid->HideProperty(markerDefineCharacter[j], true);

                        property->SetValueFromString("RGBA data set!");
                    }
                }

                rv=false;
            }
            break;
        case SCI_MARKERSYMBOLDEFINED:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                int i=m_scintilla1->GetMarkerSymbolDefined( msd->get_style() );

                if(i==wxSTC_MARK_CIRCLE)
				{
					property->SetValueFromString("wxSTC_MARK_CIRCLE");
				}
                else if(i==wxSTC_MARK_ROUNDRECT)
				{
					property->SetValueFromString("wxSTC_MARK_ROUNDRECT");
				}
                else if(i==wxSTC_MARK_ARROW)
				{
					property->SetValueFromString("wxSTC_MARK_ARROW");
				}
                else if(i==wxSTC_MARK_SMALLRECT)
				{
					property->SetValueFromString("wxSTC_MARK_SMALLRECT");
				}
                else if(i==wxSTC_MARK_SHORTARROW)
				{
					property->SetValueFromString("wxSTC_MARK_SHORTARROW");
				}
                else if(i==wxSTC_MARK_EMPTY)
				{
					property->SetValueFromString("wxSTC_MARK_EMPTY");
				}
                else if(i==wxSTC_MARK_ARROWDOWN)
				{
					property->SetValueFromString("wxSTC_MARK_ARROWDOWN");
				}
                else if(i==wxSTC_MARK_MINUS)
				{
					property->SetValueFromString("wxSTC_MARK_MINUS");
				}
                else if(i==wxSTC_MARK_PLUS)
				{
					property->SetValueFromString("wxSTC_MARK_PLUS");
				}
                else if(i==wxSTC_MARK_VLINE)
				{
					property->SetValueFromString("wxSTC_MARK_VLINE");
				}
                else if(i==wxSTC_MARK_LCORNER)
				{
					property->SetValueFromString("wxSTC_MARK_LCORNER");
				}
                else if(i==wxSTC_MARK_TCORNER)
				{
					property->SetValueFromString("wxSTC_MARK_TCORNER");
				}
                else if(i==wxSTC_MARK_BOXPLUS)
				{
					property->SetValueFromString("wxSTC_MARK_BOXPLUS");
				}
                else if(i==wxSTC_MARK_BOXPLUSCONNECTED)
				{
					property->SetValueFromString("wxSTC_MARK_BOXPLUSCONNECTED");
				}
                else if(i==wxSTC_MARK_BOXMINUS)
				{
					property->SetValueFromString("wxSTC_MARK_BOXMINUS");
				}
                else if(i==wxSTC_MARK_BOXMINUSCONNECTED)
				{
					property->SetValueFromString("wxSTC_MARK_BOXMINUSCONNECTED");
				}
                else if(i==wxSTC_MARK_LCORNERCURVE)
				{
					property->SetValueFromString("wxSTC_MARK_LCORNERCURVE");
				}
                else if(i==wxSTC_MARK_TCORNERCURVE)
				{
					property->SetValueFromString("wxSTC_MARK_TCORNERCURVE");
				}
                else if(i==wxSTC_MARK_CIRCLEPLUS)
				{
					property->SetValueFromString("wxSTC_MARK_CIRCLEPLUS");
				}
                else if(i==wxSTC_MARK_CIRCLEPLUSCONNECTED)
				{
					property->SetValueFromString("wxSTC_MARK_CIRCLEPLUSCONNECTED");
				}
                else if(i==wxSTC_MARK_CIRCLEMINUS)
				{
					property->SetValueFromString("wxSTC_MARK_CIRCLEMINUS");
				}
                else if(i==wxSTC_MARK_CIRCLEMINUSCONNECTED)
				{
					property->SetValueFromString("wxSTC_MARK_CIRCLEMINUSCONNECTED");
				}
                else if(i==wxSTC_MARK_BACKGROUND)
				{
					property->SetValueFromString("wxSTC_MARK_BACKGROUND");
				}
                else if(i==wxSTC_MARK_DOTDOTDOT)
				{
					property->SetValueFromString("wxSTC_MARK_DOTDOTDOT");
				}
                else if(i==wxSTC_MARK_ARROWS)
				{
					property->SetValueFromString("wxSTC_MARK_ARROWS");
				}
                else if(i==wxSTC_MARK_PIXMAP)
				{
					property->SetValueFromString("wxSTC_MARK_PIXMAP");
				}
                else if(i==wxSTC_MARK_FULLRECT)
				{
					property->SetValueFromString("wxSTC_MARK_FULLRECT");
				}
                else if(i==wxSTC_MARK_LEFTRECT)
				{
					property->SetValueFromString("wxSTC_MARK_LEFTRECT");
				}
                else if(i==wxSTC_MARK_AVAILABLE)
				{
					property->SetValueFromString("wxSTC_MARK_AVAILABLE");
				}
                else if(i==wxSTC_MARK_UNDERLINE)
				{
					property->SetValueFromString("wxSTC_MARK_UNDERLINE");
				}
                else if(i==wxSTC_MARK_RGBAIMAGE)
				{
					property->SetValueFromString("wxSTC_MARK_RGBAIMAGE");
				}
                else if(i>=wxSTC_MARK_CHARACTER)
				{
					property->SetValueFromString( wxString::Format("wxSTC_MARK_CHARACTER - %d",i) );
				}
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown marker symbol)",i));
                }
                rv=true;
            }
            break;
        case SCI_MARKERSETFORE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                wxAny value = property->GetValue();
                m_scintilla1->MarkerSetForeground( msd->get_style(),value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_MARKERSETBACK:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                wxAny value = property->GetValue();
                m_scintilla1->MarkerSetBackground( msd->get_style(),value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_MARKERSETBACKSELECTED:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                wxAny value = property->GetValue();
                m_scintilla1->MarkerSetBackgroundSelected( msd->get_style(),value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_MARKERENABLEHIGHLIGHT:
            {

                long l=property->GetValue().GetLong();

                for(int i=0;i<=wxSTC_MARKER_MAX;i++)
                {
                    if(markerEnableHighlight[i]!=property)
                    {
                        markerEnableHighlight[i]->SetValueFromInt(l);
                    }
                }
                m_scintilla1->MarkerEnableHighlight( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_MARKERSETALPHA:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                m_scintilla1->MarkerSetAlpha( msd->get_style(),property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_MARKERDEFINEALT:
            {
                rv=false;
            }
            break;
        case SCI_MARKERDEFINEPIXMAP2:
            {
                wxPGProperty* par = property->GetParent()->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                int j = msd->get_style();
                long l1 = property->GetValue();

                m_scintilla1->SendMsg( 2049, msd->get_style(), (sptr_t)l1 );

                m_propgrid->HideProperty(markerDefineCharacter[j], true);
                markerDefinitions[j]->SetValueToUnspecified();
                markerDefinePixmap[j]->SetValueToUnspecified();
                markerDefineRGBAImage[j]->SetValueToUnspecified();

                rv=false;
            }
            break;
        case SCI_MARKERADD:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                int i=m_scintilla1->MarkerAdd(l1,l2);
                property->SetValueFromInt(i);

                if(i!=-1)
                {
                    markers.push_back(new marker(i,l1,l2));
                    buildMarkerEnums();
                }

                //if we return true, this method will get called a second time
                rv=false;
            }
            break;
        case SCI_MARKERADDSET:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                //Can we get the handle(s) added here?  Based on past experiments, the
                //handles start at 1 and go sequentially.  And if the last handle assigned
                //by MarkerAdd was 5 and we had 3 bits set here, the next call to MarkerAdd
                //would return 9.  So we can presume that the handles 6,7,and 8 were
                //assigned to the 3 markers coresponding to the 3 bits.

                //Can we always assume the handles are assigned sequentially like this?
                //And if so, which handle is assigned to which marker?  We need a
                //SCI_MARKERMARKERFROMHANDLE message to go along with SCI_MARKERLINEFROMHANDLE.

                m_scintilla1->MarkerAddSet(l1,l2);
                rv=false;
            }
            break;
        case SCI_MARKERDELETE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->MarkerDelete(l1,l2);

                if(l2==-1)
                {
                    bool found(false);

                    for(std::vector<marker*>::iterator it =markers.begin() ;it!=markers.end();)
                    {
                        if((*it)->lineNo==l1)
                        {
                            markers.erase(it);
                            found=true;
                        }
                        else
                        {
                            it++;
                        }
                    }

                    if(found)
                    {
                        buildMarkerEnums();
                    }
                }
                else
                {
                    for(std::vector<marker*>::iterator it =markers.begin() ;it!=markers.end();it++)
                    {
                        //if there is more than one copy of a marker on a line, we won't know
                        //which one to remove form the list.  So in addition to the line and
                        //marker nos, we need to check MarkerLineFromHandle to determine which
                        //one the call to MarkerDelete made invalid.

                        if((*it)->lineNo==l1 && (*it)->markerNo==l2)
                        {
                            if( m_scintilla1->MarkerLineFromHandle((*it)->handle)==-1 )
                            {
                                markers.erase(it);
                                buildMarkerEnums();
                                break;
                            }
                        }
                    }
                }

                rv=false;
            }
            break;
        case SCI_MARKERDELETEALL:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                m_scintilla1->MarkerDeleteAll(l1);

                if(l1==-1)
                {
                    for(std::vector<marker*>::iterator it =markers.begin() ;it!=markers.end();it++)
                    {
                        delete *it;
                    }
                    markers.clear();
                    buildMarkerEnums();
                }
                else
                {
                    bool found(false);

                    for(std::vector<marker*>::iterator it =markers.begin() ;it!=markers.end();)
                    {
                        if((*it)->markerNo==l1)
                        {
                            markers.erase(it);
                            found=true;
                        }
                        else
                        {
                            it++;
                        }
                    }

                    if(found)
                    {
                        buildMarkerEnums();
                    }
                }


                rv=false;
            }
            break;
        case SCI_MARKERGET:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                long l = m_scintilla1->MarkerGet( l1 );
                wxString s;

                for(int i=0;i<32;i++)
                {
                    if(l&(1<<i))
                    {
                        s.Prepend("1");
                    }
                    else
                    {
                        s.Prepend("0");
                    }
                }

                property->SetValueFromString(s);
                rv= true;
            }
            break;
        case SCI_MARKERNEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                property->SetValueFromInt(m_scintilla1->MarkerNext(l1,l2));
                rv= true;
            }
            break;
        case SCI_MARKERPREVIOUS:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                property->SetValueFromInt(m_scintilla1->MarkerPrevious(l1,l2));
                rv= true;
            }
            break;
        case SCI_MARKERLINEFROMHANDLE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt(m_scintilla1->MarkerLineFromHandle(l1));
                rv= true;
            }
            break;
        case SCI_MARKERDELETEHANDLE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                for(std::vector<marker*>::iterator it =markers.begin() ;it!=markers.end();it++)
                {
                    if((*it)->handle==l1)
                    {
                        markers.erase(it);
                        buildMarkerEnums();
                        break;
                    }
                }

                m_scintilla1->MarkerDeleteHandle(l1);
                rv= false;
            }
            break;

        case SCI_INDICSETSTYLE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                m_scintilla1->IndicatorSetStyle( msd->get_style() , property->GetValue().GetLong() );
                rv= false;
            }
            break;
        case SCI_INDICGETSTYLE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                int i=m_scintilla1->IndicatorGetStyle( msd->get_style() );

                if(i==wxSTC_INDIC_PLAIN)
				{
					property->SetValueFromString("wxSTC_INDIC_PLAIN");
				}
                else if(i==wxSTC_INDIC_SQUIGGLE)
				{
					property->SetValueFromString("wxSTC_INDIC_SQUIGGLE");
				}
                else if(i==wxSTC_INDIC_TT)
				{
					property->SetValueFromString("wxSTC_INDIC_TT");
				}
                else if(i==wxSTC_INDIC_DIAGONAL)
				{
					property->SetValueFromString("wxSTC_INDIC_DIAGONAL");
				}
                else if(i==wxSTC_INDIC_STRIKE)
				{
					property->SetValueFromString("wxSTC_INDIC_STRIKE");
				}
                else if(i==wxSTC_INDIC_HIDDEN)
				{
					property->SetValueFromString("wxSTC_INDIC_HIDDEN");
				}
                else if(i==wxSTC_INDIC_BOX)
				{
					property->SetValueFromString("wxSTC_INDIC_BOX");
				}
                else if(i==wxSTC_INDIC_ROUNDBOX)
				{
					property->SetValueFromString("wxSTC_INDIC_ROUNDBOX");
				}
                else if(i==wxSTC_INDIC_STRAIGHTBOX)
				{
					property->SetValueFromString("wxSTC_INDIC_STRAIGHTBOX");
				}
                else if(i==wxSTC_INDIC_DASH)
				{
					property->SetValueFromString("wxSTC_INDIC_DASH");
				}
                else if(i==wxSTC_INDIC_DOTS)
				{
					property->SetValueFromString("wxSTC_INDIC_DOTS");
				}
                else if(i==wxSTC_INDIC_SQUIGGLELOW)
				{
					property->SetValueFromString("wxSTC_INDIC_SQUIGGLELOW");
				}
                else if(i==wxSTC_INDIC_DOTBOX)
				{
					property->SetValueFromString("wxSTC_INDIC_DOTBOX");
				}
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown indicator style)",i));
                }
                rv=true;
            }
            break;
        case SCI_INDICSETFORE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                wxAny value = property->GetValue();
                m_scintilla1->IndicatorSetForeground( msd->get_style() , value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_INDICGETFORE:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                setColorString(property, m_scintilla1->IndicatorGetForeground (msd->get_style()));

//                wxColour c = m_scintilla1->IndicatorGetForeground (msd->get_style());
//                property->SetValueFromString( c.GetAsString() );

                rv=true;
            }
            break;
        case SCI_INDICSETALPHA:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                m_scintilla1->IndicatorSetAlpha( msd->get_style() , property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_INDICGETALPHA:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                property->SetValueFromInt(  m_scintilla1->IndicatorGetAlpha (msd->get_style()) );
                rv=true;
            }
            break;
        case SCI_INDICSETOUTLINEALPHA:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                m_scintilla1->IndicatorSetOutlineAlpha( msd->get_style() , property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_INDICGETOUTLINEALPHA:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                property->SetValueFromInt(  m_scintilla1->IndicatorGetOutlineAlpha (msd->get_style()) );
                rv=true;
            }
            break;
        case SCI_INDICSETUNDER:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                m_scintilla1->IndicatorSetUnder( msd->get_style(), property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_INDICGETUNDER:
            {
                wxPGProperty* par = property->GetParent();
                myStyleData* msd = dynamic_cast<myStyleData*>(par->GetClientObject());

                property->SetValueFromString(m_scintilla1->IndicatorGetUnder(msd->get_style())?"True":"False");
                rv=true;
            }
            break;
        case SCI_MODERNINDICATORS:
            {
                rv=false;
            }
            break;
        case SCI_SETINDICATORCURRENT:
            {
                m_scintilla1->SetIndicatorCurrent( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETINDICATORCURRENT:
            {
                property->SetValueFromInt(m_scintilla1->GetIndicatorCurrent());
                rv=true;
            }
            break;
        case SCI_SETINDICATORVALUE:
            {
                m_scintilla1->SetIndicatorValue( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETINDICATORVALUE:
            {
                property->SetValueFromInt( m_scintilla1->GetIndicatorValue() );
                rv=true;
            }
            break;
        case SCI_INDICATORFILLRANGE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->IndicatorFillRange(l1,l2);
                rv= false;
            }
            break;
        case SCI_INDICATORCLEARRANGE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->IndicatorClearRange(l1,l2);
                rv= false;
            }
            break;
        case SCI_INDICATORALLONFOR:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                long l = m_scintilla1->IndicatorAllOnFor( l1 );
                wxString s;

                for(int i=0;i<32;i++)
                {
                    if(l&(1<<i))
                    {
                        s.Prepend("1");
                    }
                    else
                    {
                        s.Prepend("0");
                    }
                }

                property->SetValueFromString(s);
                rv= true;
            }
            break;
        case SCI_INDICATORVALUEAT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                property->SetValueFromInt(m_scintilla1->IndicatorValueAt(l1,l2));
                rv= true;
            }
            break;
        case SCI_INDICATORSTART:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                property->SetValueFromInt(m_scintilla1->IndicatorStart(l1,l2));
                rv= true;
            }
            break;
        case SCI_INDICATOREND:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                property->SetValueFromInt(m_scintilla1->IndicatorEnd(l1,l2));
                rv= true;
            }
            break;
        case SCI_OSXFINDINDICATOR:
            {
                rv= false;
            }
            break;
        case SCI_FINDINDICATORSHOW:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->SendMsg(2640,l1,l2);
                statusBar->SetStatusText("OS X find indicator shown.", 1);
                rv= false;
            }
            break;
        case SCI_FINDINDICATORFLASH:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->SendMsg(2641,l1,l2);
                statusBar->SetStatusText("OS X find indicator flashing.", 1);
                rv= false;
            }
            break;
        case SCI_FINDINDICATORHIDE:
            {
                m_scintilla1->SendMsg(2642,0,0);
                statusBar->SetStatusText("OS X find indicator hidden.", 1);
                rv= false;
            }
            break;

        case SCI_AUTOCSHOW:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                wxString s = it.GetProperty()->GetValue();

                m_scintilla1->AutoCompShow(l1,s);
                rv= false;
            }
            break;
        case SCI_AUTOCCANCEL:
            {
                m_scintilla1->AutoCompCancel();
                rv= false;
            }
            break;
        case SCI_AUTOCACTIVE:
            {
                property->SetValueFromString(m_scintilla1->AutoCompActive()?"True":"False");
                rv= true;
            }
            break;
        case SCI_AUTOCPOSSTART:
            {
                property->SetValueFromInt( m_scintilla1->AutoCompPosStart() );
                rv= true;
            }
            break;
        case SCI_AUTOCCOMPLETE:
            {
                m_scintilla1->AutoCompComplete();
                rv= false;
            }
            break;
        case SCI_AUTOCSTOPS:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();

                m_scintilla1->AutoCompStops(s);

                rv= false;
            }
            break;
        case SCI_AUTOCSETSEPARATOR:
            {
                wxString currentFontName = m_scintilla1->StyleGetFaceName(wxSTC_STYLE_DEFAULT);
                wxSymbolPickerDialog dlg(" ", currentFontName, currentFontName, this);

                if (dlg.ShowModal() == wxID_OK)
                {
                    if (dlg.HasSelection())
                    {
                        m_scintilla1->AutoCompSetSeparator( dlg.GetSymbolChar() );
                        property->SetValueFromString( wxString::Format("%d - '%s'",dlg.GetSymbolChar(),dlg.GetSymbol()) );

                        //we should return true since the property has changed, but for
                        //some reason, that makes the dialog appear a second time.  returning
                        //false seems to prevent that and doesn't seem to cause any other problems
                        rv= false;
                    }
                    else
                    {
                        rv=false;
                    }
                }
                else
                {
                    rv=false;
                }
            }
            break;
        case SCI_AUTOCGETSEPARATOR:
            {
                wxString s = (char)m_scintilla1->AutoCompGetSeparator();

                property->SetValueFromString( wxString::Format("%d - '%s'",m_scintilla1->AutoCompGetSeparator(),s)  );
                rv= true;
            }
            break;
        case SCI_AUTOCSELECT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();

                m_scintilla1->AutoCompSelect(s);
                rv= false;
            }
            break;
        case SCI_AUTOCGETCURRENT:
            {
                property->SetValueFromInt( m_scintilla1->AutoCompGetCurrent() );
                rv= true;
            }
            break;
        case SCI_AUTOCGETCURRENTTEXT:
            {
                int msg = 2610;
                int len = m_scintilla1->SendMsg(msg, 0, (sptr_t)NULL);
                if (!len)
                {
                    property->SetValueFromString("");
                }
                else
                {
                    wxMemoryBuffer mbuf(len+1);
                    char* buf = (char*)mbuf.GetWriteBuf(len+1);
                    m_scintilla1->SendMsg(msg, 0, (sptr_t)buf);
                    mbuf.UngetWriteBuf(len);
                    mbuf.AppendByte(0);
                    //return stc2wx(buf);
                    property->SetValueFromString(buf);
                }

                rv=true;
            }
            break;
        case SCI_AUTOCSETCANCELATSTART:
            {
                m_scintilla1->AutoCompSetCancelAtStart(property->GetValue().GetBool());
                rv=false;
            }
            break;
        case SCI_AUTOCGETCANCELATSTART:
            {
                property->SetValueFromString(m_scintilla1->AutoCompGetCancelAtStart()?"True":"False");
                rv= true;
            }
            break;
        case SCI_AUTOCSETFILLUPS:
            {
//                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
//                it++;
//                wxString s = it.GetProperty()->GetValue();

                m_scintilla1->AutoCompSetFillUps(property->GetValue().GetString());
                rv= false;
            }
            break;
        case SCI_AUTOCSETCHOOSESINGLE:
            {
                m_scintilla1->AutoCompSetChooseSingle(property->GetValue().GetBool());
                rv=false;
            }
            break;
        case SCI_AUTOCGETCHOOSESINGLE:
            {
                property->SetValueFromString(m_scintilla1->AutoCompGetChooseSingle()?"True":"False");
                rv= true;
            }
            break;
        case SCI_AUTOCSETIGNORECASE:
            {
                m_scintilla1->AutoCompSetIgnoreCase(property->GetValue().GetBool());
                rv=false;
            }
            break;
        case SCI_AUTOCGETIGNORECASE:
            {
                property->SetValueFromString(m_scintilla1->AutoCompGetIgnoreCase()?"True":"False");
                rv= true;
            }
            break;
        case SCI_AUTOCSETCASEINSENSITIVEBEHAVIOUR:
            {
                m_scintilla1->AutoCompSetCaseInsensitiveBehaviour(property->GetValue().GetLong());
                rv=false;
            }
            break;
        case SCI_AUTOCGETCASEINSENSITIVEBEHAVIOUR:
            {
                int i=m_scintilla1->AutoCompGetCaseInsensitiveBehaviour();

                if(i==wxSTC_CASEINSENSITIVEBEHAVIOUR_RESPECTCASE)
				{
					property->SetValueFromString("wxSTC_CASEINSENSITIVEBEHAVIOUR_RESPECTCASE");
				}
                else if(i==wxSTC_CASEINSENSITIVEBEHAVIOUR_IGNORECASE)
				{
					property->SetValueFromString("wxSTC_CASEINSENSITIVEBEHAVIOUR_IGNORECASE");
				}
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown caseinsensitive behaviour)",i));
                }

				rv=true;
            }
            break;
        case SCI_AUTOCSETAUTOHIDE:
            {
                m_scintilla1->AutoCompSetAutoHide(property->GetValue().GetBool());
                rv=false;
            }
            break;
        case SCI_AUTOCGETAUTOHIDE:
            {
                property->SetValueFromString(m_scintilla1->AutoCompGetAutoHide()?"True":"False");
                rv= true;
            }
            break;
        case SCI_AUTOCSETDROPRESTOFWORD:
            {
                m_scintilla1->AutoCompSetDropRestOfWord(property->GetValue().GetBool());
                rv=false;
            }
            break;
        case SCI_AUTOCGETDROPRESTOFWORD:
            {
                property->SetValueFromString(m_scintilla1->AutoCompGetDropRestOfWord()?"True":"False");
                rv= true;
            }
            break;
        case SCI_REGISTERIMAGE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                wxString s = it.GetProperty()->GetValue();

                wxBitmap bm(s,wxBITMAP_TYPE_ANY);

                if(bm.IsOk())
                {
                    addRegisteredImage(l1, s);
                    m_scintilla1->RegisterImage( l1 , bm );
                }

                rv=false;
            }
            break;
        case SCI_REGISTERRGBAIMAGE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long width = it.GetProperty()->GetValue();
                it++;
                long height = it.GetProperty()->GetValue();

                RGBADialog md(this,height,width);
                int i=md.ShowModal();

                if(i==wxID_OK)
                {
                    unsigned char* c(nullptr);
                    md.getRGBAData( &c );

                    addRegisteredImage(l1, "RGBA Data");
                    registeredACRGBAData.insert(std::pair<int,unsigned char*>(l1,c));

                    m_scintilla1->RGBAImageSetWidth(width);
                    m_scintilla1->RGBAImageSetHeight(height);
                    m_scintilla1->RegisterRGBAImage( l1 , c );
                }

                rv=false;
            }
            break;
        case SCI_CLEARREGISTEREDIMAGES:
            {
                m_scintilla1->ClearRegisteredImages();

                clearRegisteredImages();
                m_propgrid->HideProperty(registerdACImageHeader, true);

                for(std::map<int,wxPGProperty*>::iterator it=registeredACImages.begin();it!=registeredACImages.end();it++)
                {
                    delete it->second;
                }
                registeredACImages.clear();

                for(std::map<int,unsigned char*>::iterator it=registeredACRGBAData.begin();it!=registeredACRGBAData.end();it++)
                {
                    free(it->second);
                }
                registeredACRGBAData.clear();

                rv=false;
            }
            break;
        case SCI_AUTOCSETTYPESEPARATOR:
            {
                wxString currentFontName = m_scintilla1->StyleGetFaceName(wxSTC_STYLE_DEFAULT);

                wxSymbolPickerDialog dlg(" ", currentFontName, currentFontName, this);

                if (dlg.ShowModal() == wxID_OK)
                {
                    if (dlg.HasSelection())
                    {
                        m_scintilla1->AutoCompSetTypeSeparator( dlg.GetSymbolChar() );
                        property->SetValueFromString( wxString::Format("%d - '%s'",dlg.GetSymbolChar(),dlg.GetSymbol()) );

                        //we should return true since the property has changed, but for
                        //some reason, that makes the dialog appear a second time.  returning
                        //false seems to prevent that and doesn't seem to cause any other problems
                        rv= false;
                    }
                    else
                    {
                        rv=false;
                    }
                }
                else
                {
                    rv=false;
                }
            }
            break;
        case SCI_AUTOCGETTYPESEPARATOR:
            {
                wxString s = (char)m_scintilla1->AutoCompGetTypeSeparator();

                property->SetValueFromString( wxString::Format("%d - '%s'",m_scintilla1->AutoCompGetTypeSeparator(),s)  );
                rv= true;
            }
            break;
        case SCI_AUTOCSETMAXHEIGHT:
            {
                m_scintilla1->AutoCompSetMaxHeight( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_AUTOCGETMAXHEIGHT:
            {
                property->SetValueFromInt(m_scintilla1->AutoCompGetMaxHeight());
                rv= true;
            }
            break;
        case SCI_AUTOCSETMAXWIDTH:
            {
                m_scintilla1->AutoCompSetMaxWidth( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_AUTOCGETMAXWIDTH:
            {
                property->SetValueFromInt(m_scintilla1->AutoCompGetMaxWidth());
                rv= true;
            }
            break;

        case SCI_REGISTERIMAGE2:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                wxString s = m_propgrid->GetPropertyValueAsString(it.GetProperty());

                addRegisteredImage(l1, s);
                m_scintilla1->SendMsg(2405, l1, l2 );

                rv=false;
            }
            break;
        case SCI_USERLISTSHOW:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                wxString s = it.GetProperty()->GetValue();

                m_scintilla1->UserListShow(l1,s);
                rv= false;
            }
            break;
        case SCI_CALLTIPSHOW:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                wxString s = it.GetProperty()->GetValue();
                s.Replace("\\001","\001",true);
                s.Replace("\\002","\002",true);
                s.Replace("\\n","\n",true);
                s.Replace("\\t","\t",true);

                m_scintilla1->CallTipShow(l1,s);
                rv= false;
            }
            break;
        case SCI_CALLTIPCANCEL:
            {
                m_scintilla1->CallTipCancel();
                rv= false;
            }
            break;
        case SCI_CALLTIPACTIVE:
            {
                property->SetValueFromString(m_scintilla1->CallTipActive()?"True":"False");
                rv= true;
            }
            break;
        case SCI_CALLTIPPOSSTART:
            {
                property->SetValueFromInt(m_scintilla1->CallTipPosAtStart());
                rv= true;
            }
            break;
        case SCI_CALLTIPSETHLT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->CallTipSetHighlight(l1,l2);
                statusBar->SetStatusText(wxString::Format("Call tip highlight set from %d to %d",l1,l2), 1);
                rv= false;
            }
            break;
        case SCI_CALLTIPSETBACK:
            {
                wxAny value = property->GetValue();
                m_scintilla1->CallTipSetBackground( value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_CALLTIPSETFORE:
            {
                wxAny value = property->GetValue();
                m_scintilla1->CallTipSetForeground( value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_CALLTIPSETFOREHLT:
            {
                wxAny value = property->GetValue();
                m_scintilla1->CallTipSetForegroundHighlight( value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_CALLTIPUSESTYLE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                m_scintilla1->CallTipUseStyle(l1);

                statusBar->SetStatusText("Call tip style set to wxSTC_STYLE_CALLTIP.", 1);
                rv= false;
            }
            break;
        case SCI_CALLTIPSETPOSITION:
            {
                m_scintilla1->CallTipSetPosition( property->GetValue().GetBool() );
                rv= false;
            }
            break;

        case SCI_LINEDOWN:
            {
                m_scintilla1->LineDown();
                rv=false;
            }
            break;
        case SCI_LINEDOWNEXTEND:
            {
                m_scintilla1->LineDownExtend();
                rv=false;
            }
            break;
        case SCI_LINEDOWNRECTEXTEND:
            {
                m_scintilla1->LineDownRectExtend();
                rv=false;
            }
            break;
        case SCI_LINESCROLLDOWN:
            {
                m_scintilla1->LineScrollDown();
                rv=false;
            }
            break;
        case SCI_LINEUP:
            {
                m_scintilla1->LineUp();
                rv=false;
            }
            break;
        case SCI_LINEUPEXTEND:
            {
                m_scintilla1->LineUpExtend();
                rv=false;
            }
            break;
        case SCI_LINEUPRECTEXTEND:
            {
                m_scintilla1->LineUpRectExtend();
                rv=false;
            }
            break;
        case SCI_LINESCROLLUP:
            {
                m_scintilla1->LineScrollUp();
                rv=false;
            }
            break;
        case SCI_PARADOWN:
            {
                m_scintilla1->ParaDown();
                rv=false;
            }
            break;
        case SCI_PARADOWNEXTEND:
            {
                m_scintilla1->ParaDownExtend();
                rv=false;
            }
            break;
        case SCI_PARAUP:
            {
                m_scintilla1->ParaUp();
                rv=false;
            }
            break;
        case SCI_PARAUPEXTEND:
            {
                m_scintilla1->ParaUpExtend();
                rv=false;
            }
            break;
        case SCI_CHARLEFT:
            {
                m_scintilla1->CharLeft();
                rv=false;
            }
            break;
        case SCI_CHARLEFTEXTEND:
            {
                m_scintilla1->CharLeftExtend();
                rv=false;
            }
            break;
        case SCI_CHARLEFTRECTEXTEND:
            {
                m_scintilla1->CharLeftRectExtend();
                rv=false;
            }
            break;
        case SCI_CHARRIGHT:
            {
                m_scintilla1->CharRight();
                rv=false;
            }
            break;
        case SCI_CHARRIGHTEXTEND:
            {
                m_scintilla1->CharRightExtend();
                rv=false;
            }
            break;
        case SCI_CHARRIGHTRECTEXTEND:
            {
                m_scintilla1->CharRightRectExtend();
                rv=false;
            }
            break;
        case SCI_WORDLEFT:
            {
                m_scintilla1->WordLeft();
                rv=false;
            }
            break;
        case SCI_WORDLEFTEXTEND:
            {
                m_scintilla1->WordLeftExtend();
                rv=false;
            }
            break;
        case SCI_WORDRIGHT:
            {
                m_scintilla1->WordRight();
                rv=false;
            }
            break;
        case SCI_WORDRIGHTEXTEND:
            {
                m_scintilla1->WordRightExtend();
                rv=false;
            }
            break;
        case SCI_WORDLEFTEND:
            {
                m_scintilla1->WordLeftEnd();
                rv=false;
            }
            break;
        case SCI_WORDLEFTENDEXTEND:
            {
                m_scintilla1->WordLeftEndExtend();
                rv=false;
            }
            break;
        case SCI_WORDRIGHTEND:
            {
                m_scintilla1->WordRightEnd();
                rv=false;
            }
            break;
        case SCI_WORDRIGHTENDEXTEND:
            {
                m_scintilla1->WordRightEndExtend();
                rv=false;
            }
            break;
        case SCI_WORDPARTLEFT:
            {
                m_scintilla1->WordPartLeft();
                rv=false;
            }
            break;
        case SCI_WORDPARTLEFTEXTEND:
            {
                m_scintilla1->WordPartLeftExtend();
                rv=false;
            }
            break;
        case SCI_WORDPARTRIGHT:
            {
                m_scintilla1->WordPartRight();
                rv=false;
            }
            break;
        case SCI_WORDPARTRIGHTEXTEND:
            {
                m_scintilla1->WordPartRightExtend();
                rv=false;
            }
            break;
        case SCI_HOME:
            {
                m_scintilla1->Home();
                rv=false;
            }
            break;
        case SCI_HOMEEXTEND:
            {
                m_scintilla1->HomeExtend();
                rv=false;
            }
            break;
        case SCI_HOMERECTEXTEND:
            {
                m_scintilla1->HomeRectExtend();
                rv=false;
            }
            break;
        case SCI_HOMEDISPLAY:
            {
                m_scintilla1->HomeDisplay();
                rv=false;
            }
            break;
        case SCI_HOMEDISPLAYEXTEND:
            {
                m_scintilla1->HomeDisplayExtend();
                rv=false;
            }
            break;
        case SCI_HOMEWRAP:
            {
                m_scintilla1->HomeWrap();
                rv=false;
            }
            break;
        case SCI_HOMEWRAPEXTEND:
            {
                m_scintilla1->HomeWrapExtend();
                rv=false;
            }
            break;
        case SCI_VCHOME:
            {
                m_scintilla1->VCHome();
                rv=false;
            }
            break;
        case SCI_VCHOMEEXTEND:
            {
                m_scintilla1->VCHomeExtend();
                rv=false;
            }
            break;
        case SCI_VCHOMERECTEXTEND:
            {
                m_scintilla1->VCHomeRectExtend();
                rv=false;
            }
            break;
        case SCI_VCHOMEWRAP:
            {
                m_scintilla1->VCHomeWrap();
                rv=false;
            }
            break;
        case SCI_VCHOMEWRAPEXTEND:
            {
                m_scintilla1->VCHomeWrapExtend();
                rv=false;
            }
            break;
        case SCI_LINEEND:
            {
                m_scintilla1->LineEnd();
                rv=false;
            }
            break;
        case SCI_LINEENDEXTEND:
            {
                m_scintilla1->LineEndExtend();
                rv=false;
            }
            break;
        case SCI_LINEENDRECTEXTEND:
            {
                m_scintilla1->LineEndRectExtend();
                rv=false;
            }
            break;
        case SCI_LINEENDDISPLAY:
            {
                m_scintilla1->LineEndDisplay();
                rv=false;
            }
            break;
        case SCI_LINEENDDISPLAYEXTEND:
            {
                m_scintilla1->LineEndDisplayExtend();
                rv=false;
            }
            break;
        case SCI_LINEENDWRAP:
            {
                m_scintilla1->LineEndWrap();
                rv=false;
            }
            break;
        case SCI_LINEENDWRAPEXTEND:
            {
                m_scintilla1->LineEndWrapExtend();
                rv=false;
            }
            break;
        case SCI_DOCUMENTSTART:
            {
                m_scintilla1->DocumentStart();
                rv=false;
            }
            break;
        case SCI_DOCUMENTSTARTEXTEND:
            {
                m_scintilla1->DocumentStartExtend();
                rv=false;
            }
            break;
        case SCI_DOCUMENTEND:
            {
                m_scintilla1->DocumentEnd();
                rv=false;
            }
            break;
        case SCI_DOCUMENTENDEXTEND:
            {
                m_scintilla1->DocumentEndExtend();
                rv=false;
            }
            break;
        case SCI_PAGEUP:
            {
                m_scintilla1->PageUp();
                rv=false;
            }
            break;
        case SCI_PAGEUPEXTEND:
            {
                m_scintilla1->PageUpExtend();
                rv=false;
            }
            break;
        case SCI_PAGEUPRECTEXTEND:
            {
                m_scintilla1->PageUpRectExtend();
                rv=false;
            }
            break;
        case SCI_PAGEDOWN:
            {
                m_scintilla1->PageDown();
                rv=false;
            }
            break;
        case SCI_PAGEDOWNEXTEND:
            {
                m_scintilla1->PageDownExtend();
                rv=false;
            }
            break;
        case SCI_PAGEDOWNRECTEXTEND:
            {
                m_scintilla1->PageDownRectExtend();
                rv=false;
            }
            break;
        case SCI_STUTTEREDPAGEUP:
            {
                m_scintilla1->StutteredPageUp();
                rv=false;
            }
            break;
        case SCI_STUTTEREDPAGEUPEXTEND:
            {
                m_scintilla1->StutteredPageUpExtend();
                rv=false;
            }
            break;
        case SCI_STUTTEREDPAGEDOWN:
            {
                m_scintilla1->StutteredPageDown();
                rv=false;
            }
            break;
        case SCI_STUTTEREDPAGEDOWNEXTEND:
            {
                m_scintilla1->StutteredPageDownExtend();
                rv=false;
            }
            break;
        case SCI_DELETEBACK:
            {
                m_scintilla1->DeleteBack();
                rv=false;
            }
            break;
        case SCI_DELETEBACKNOTLINE:
            {
                m_scintilla1->DeleteBackNotLine();
                rv=false;
            }
            break;
        case SCI_DELWORDLEFT:
            {
                m_scintilla1->DelWordLeft();
                rv=false;
            }
            break;
        case SCI_DELWORDRIGHT:
            {
                m_scintilla1->DelWordRight();
                rv=false;
            }
            break;
        case SCI_DELWORDRIGHTEND:
            {
                m_scintilla1->DelWordRightEnd();
                rv=false;
            }
            break;
        case SCI_DELLINELEFT:
            {
                m_scintilla1->DelLineLeft();
                rv=false;
            }
            break;
        case SCI_DELLINERIGHT:
            {
                m_scintilla1->DelLineRight();
                rv=false;
            }
            break;
        case SCI_LINEDELETE:
            {
                m_scintilla1->LineDelete();
                rv=false;
            }
            break;
        case SCI_LINECUT:
            {
                m_scintilla1->LineCut();
                rv=false;
            }
            break;
        case SCI_LINECOPY:
            {
                m_scintilla1->LineCopy();
                rv=false;
            }
            break;
        case SCI_LINETRANSPOSE:
            {
                m_scintilla1->LineTranspose();
                rv=false;
            }
            break;
        case SCI_LINEDUPLICATE:
            {
                m_scintilla1->LineDuplicate();
                rv=false;
            }
            break;
        case SCI_LOWERCASE:
            {
                m_scintilla1->LowerCase();
                rv=false;
            }
            break;
        case SCI_UPPERCASE:
            {
                m_scintilla1->UpperCase();
                rv=false;
            }
            break;
        case SCI_CANCEL:
            {
                m_scintilla1->Cancel();
                rv=false;
            }
            break;
        case SCI_EDITTOGGLEOVERTYPE:
            {
                m_scintilla1->EditToggleOvertype();
                rv=false;
            }
            break;
        case SCI_NEWLINE:
            {
                m_scintilla1->NewLine();
                rv=false;
            }
            break;
        case SCI_FORMFEED:
            {
                m_scintilla1->FormFeed();
                rv=false;
            }
            break;
        case SCI_TAB:
            {
                m_scintilla1->Tab();
                rv=false;
            }
            break;
        case SCI_BACKTAB:
            {
                m_scintilla1->BackTab();
                rv=false;
            }
            break;
        case SCI_SELECTIONDUPLICATE:
            {
                m_scintilla1->SelectionDuplicate();
                rv=false;
            }
            break;
        case SCI_VERTICALCENTRECARET:
            {
                m_scintilla1->VerticalCentreCaret();
                rv=false;
            }
            break;
        case SCI_SCROLLTOSTART:
            {
                m_scintilla1->ScrollToStart();
                rv=false;
            }
            break;
        case SCI_SCROLLTOEND:
            {
                m_scintilla1->ScrollToEnd();
                rv=false;
            }
            break;

        case SCI_ASSIGNCMDKEY:
            {
                wxPropertyGridIterator it = m_propgrid->GetIterator(wxPG_ITERATE_ALL,property);

                it++;
                long l1 = it.GetProperty()->GetValue().GetLong();
                wxString keyname = m_propgrid->GetPropertyValueAsString( it.GetProperty() );

                it++;
                wxString kc_str = it.GetProperty()->GetValue().GetString();

                it++;
                long md = it.GetProperty()->GetValue().GetLong();

                it++;
                long bits = it.GetProperty()->GetValue().GetLong();

                it++;//the next 5 are the bit fields for the modifier
                it++;
                it++;
                it++;
                it++;
                it++;
                long cmd = it.GetProperty()->GetValue().GetLong();
                wxString msgName = m_propgrid->GetPropertyValueAsString( it.GetProperty() );

                //m_scintilla1->AddText(wxString::Format("%d %s %d %d %d\n",l1,kc_str,md,bits,cmd));

                int key,mod;
                long kc(0);

                if(l1==-1)
                {
                    wxString temp=kc_str;
                    wxString temp2 = " (keycode ";

                    size_t l = temp.length();
                    size_t l2 = temp2.length();
                    int f = temp.Find (temp2);

                    keyname = temp.Left(f);
                    kc_str = temp.Right(l-f-l2);

                    kc_str.Replace(")","",true);

                    kc_str.ToLong(&kc);
                }
//                else
//                {
//                    keyname
//                }



                key = (l1==-1)?kc:l1;
                mod = (md==-1)?bits:md;
                m_scintilla1->CmdKeyAssign(key, mod, cmd);
                //m_scintilla1->CmdKeyAssign(340,0,wxSTC_CMD_CHARLEFT);


                //m_scintilla1->SetText(wxString::Format("%d %d %d %d %d",cmd,l1,kc,md,bits));

                wxString s;
                bool already_added(false);

                if(mod&wxSTC_SCMOD_SHIFT)
                {
                    s<<"SHIFT";
                    already_added=true;
                }

                if(mod&wxSTC_SCMOD_CTRL)
                {
                    s<< (already_added?"+":"")<<"CTRL";
                    already_added=true;
                }

                if(mod&wxSTC_SCMOD_ALT)
                {
                    s<< (already_added?"+":"")<<"ALT";
                    already_added=true;
                }

                if(mod&wxSTC_SCMOD_SUPER)
                {
                    s << (already_added?"+":"") <<"SUPER";
                    already_added=true;
                }

                if(mod&wxSTC_SCMOD_META)
                {
                    s<< (already_added?"+":"")<<"META";
                    already_added=true;
                }

                s<< (already_added?"+":"")<<keyname;


                //keyBinding* kb = new keyBinding(key,mod,cmd,wxString::Format("%d %d %d %d %d",cmd,l1,kc,md,bits) );
                keyBinding* kb = new keyBinding(key,mod,cmd,s );
                keyBindings.push_back(kb);

                buildCmdKeyClearEnum();
                statusBar->SetStatusText( s + " assigned to " + msgName + ".", 1);

                rv=false;
            }
            break;

        case SCI_ASSIGNCMDKEY2:
            {
                if(property->GetValue().GetLong()==-1)
                {
                    MyProjectMyDialog3 md(this);

                    int i=md.ShowModal();

                    if(i==wxID_OK)
                    {
                        int kc=md.getKeyCode();

                        wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                        it++;

                        if(!m_propgrid->IsPropertyShown(it.GetProperty()))
                        {
                            m_propgrid->HideProperty(it.GetProperty(),false);
                        }

                        //it.GetProperty()->SetValueFromInt(kc);
                        it.GetProperty()->SetValueFromString(wxString::Format("%s (keycode %d)",md.getKeyName(),md.getKeyCode()  ));
                    }
                }
                else
                {
                    wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                    it++;
                    int i2=reinterpret_cast<int>( it.GetProperty()->GetClientData() );

                    if(i2==SCI_ASSIGNCMDKEY3)
                    {
                        //m_propgrid->DeleteProperty (it.GetProperty());
                        m_propgrid->HideProperty(it.GetProperty(),true);
                    }
                }

                rv=false;
            }
            break;

        case SCI_ASSIGNCMDKEY3:
            {
                MyProjectMyDialog3 md(this);

                //int i=md.ShowModal();

                if(md.ShowModal()==wxID_OK)
                {
                    //property->SetValueFromInt(md.getKeyCode());
                    property->SetValueFromString(wxString::Format("%s (keycode %d)",md.getKeyName(),md.getKeyCode()  ));
                }

                rv=false;
            }
            break;

        case SCI_ASSIGNCMDKEY4:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;

                long l = property->GetValue().GetLong();
                if(l==-1)
                {
                    it.GetProperty()->Enable(true);
                    //m_scintilla1->SetMarginMask( msd->get_style() , it.GetProperty()->GetValue().GetLong() );
                }
                else
                {
                    it.GetProperty()->Enable(false);
                    //m_scintilla1->SetMarginMask( msd->get_style() , property->GetValue().GetLong() );
                }

                rv=false;
            }
            break;


        case SCI_CLEARCMDKEY:
            {
                wxPropertyGridIterator it = m_propgrid->GetIterator(wxPG_ITERATE_NORMAL,property);
                it++;
                long l1 = it.GetProperty()->GetValue().GetLong();

                if(l1!=-1)
                {
                    keyBinding* kb = keyBindings[l1];
                    m_scintilla1->CmdKeyClear( kb->getKeyCode(), kb->getModifiers() );
                    delete kb;
                    keyBindings.erase(keyBindings.begin()+l1);
                    buildCmdKeyClearEnum();
                }

                rv=false;
            }
            break;
        case SCI_CLEARALLCMDKEYS:
            {
                m_scintilla1->CmdKeyClearAll();
                for(std::vector<keyBinding*>::iterator it=keyBindings.begin();it!=keyBindings.end();it++)
                {
                    delete *it;
                }
                keyBindings.clear();
                buildCmdKeyClearEnum();
                rv=false;
            }
            break;
        case SCI_NULL:
            {
                //this literally does nothing

                m_scintilla1->SendMsg(2172,0,0);
                rv=false;
            }
            break;

        case SCI_USEPOPUP:
            {
                m_scintilla1->UsePopUp( property->GetValue().GetBool() );
                rv=false;
            }
            break;
        case SCI_STARTRECORD:
            {
                m_scintilla1->StartRecord();
                statusBar->SetStatusText("Macro recording in progress", 1);
                rv=false;
            }
            break;
        case SCI_STOPRECORD:
            {
                m_scintilla1->StopRecord();
                statusBar->SetStatusText("Macro recording stopped", 1);
                rv=false;
            }
            break;
        case SCI_FORMATRANGE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                MyProjectMyDialog1 md(this);
                wxColor c = md.m_panel1->GetBackgroundColour ();
                wxSize sz=md.m_panel1->GetSize();

                int top_margin=50;
                int bot_margin=50;
                int left_margin=50;
                int right_margin=50;


                wxImage im(sz.GetWidth(), sz.GetHeight(), true);
                //im.SetMaskColour(255, 255, 255);
                //im.InitAlpha();

                //What we want to do is start with a transparent bitmap, let FormatRange
                //draw on it, then draw that bitmap onto the panel taking transparency into
                //account.  But for some reason, if we initialize the alpha channel here,
                //anything drawn by FormatRange in black gets drawn transparently.

                //So I'll cheat and fill the bitmap with the panel's background color
                //but no alpha channel, then let FormatRange draw whatever it's going to
                //draw.  Then when that bitmap is drawn onto the panel, the end result
                //should be essentially the same as what we wanted.
                im.SetRGB(wxRect(0,0,sz.GetWidth (),sz.GetHeight()), c.Red (), c.Green (), c.Blue ());

                wxBitmap test_bitmap(im);
                wxMemoryDC temp_dc;
                temp_dc.SelectObject(test_bitmap);

                int i=m_scintilla1->FormatRange( true, l1, l2, &temp_dc, &temp_dc, wxRect(left_margin, top_margin, sz.GetWidth()-left_margin-right_margin, sz.GetHeight()-top_margin-bot_margin), wxRect(0, 0, sz.GetWidth(), sz.GetHeight()));
                property->SetValueFromInt(i);

                temp_dc.SelectObject(wxNullBitmap);
                md.setbm(test_bitmap);
                md.ShowModal();

                rv=false;
            }
            break;
        case SCI_SETPRINTMAGNIFICATION:
            {
                m_scintilla1->SetPrintMagnification( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETPRINTMAGNIFICATION:
            {
                property->SetValueFromInt(m_scintilla1->GetPrintMagnification() );
                rv=true;
            }
            break;
        case SCI_SETPRINTCOLOURMODE:
            {
                m_scintilla1->SetPrintColourMode( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETPRINTCOLOURMODE:
            {
                int i=m_scintilla1->GetPrintColourMode();

                if(i==wxSTC_PRINT_NORMAL)
				{
					property->SetValueFromString("wxSTC_PRINT_NORMAL");
				}
                else if(i==wxSTC_PRINT_INVERTLIGHT)
				{
					property->SetValueFromString("wxSTC_PRINT_INVERTLIGHT");
				}
                else if(i==wxSTC_PRINT_BLACKONWHITE)
				{
					property->SetValueFromString("wxSTC_PRINT_BLACKONWHITE");
				}
                else if(i==wxSTC_PRINT_COLOURONWHITE)
				{
					property->SetValueFromString("wxSTC_PRINT_COLOURONWHITE");
				}
                else if(i==wxSTC_PRINT_COLOURONWHITEDEFAULTBG)
				{
					property->SetValueFromString("wxSTC_PRINT_COLOURONWHITEDEFAULTBG");
				}
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown print colour mode",i));
                }

                rv=true;
            }
            break;
        case SCI_SETPRINTWRAPMODE:
            {
                m_scintilla1->SetPrintWrapMode( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETPRINTWRAPMODE:
            {
                int i=m_scintilla1->GetPrintWrapMode();

                if(i==wxSTC_WRAP_NONE)
				{
					property->SetValueFromString("wxSTC_WRAP_NONE");
				}
                else if(i==wxSTC_WRAP_WORD)
				{
					property->SetValueFromString("wxSTC_WRAP_WORD");
				}
                else if(i==wxSTC_WRAP_CHAR)
				{
					property->SetValueFromString("wxSTC_WRAP_CHAR");
				}
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown print wrap mode",i));
                }

                rv=true;
            }
            break;
        case SCI_GETDIRECTFUNCTION:
            {
                rv=false;
            }
            break;
        case SCI_GETDIRECTPOINTER:
            {
                rv=false;
            }
            break;
        case SCI_GETCHARACTERPOINTER:
            {
                property->SetValueFromInt(reinterpret_cast<int>(const_cast<char*>( m_scintilla1->GetCharacterPointer()) ));
                rv=true;
            }
            break;
        case SCI_GETRANGEPOINTER:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                property->SetValueFromInt(reinterpret_cast<int>(const_cast<char*>( m_scintilla1->GetRangePointer(l1,l2) ) ));
                rv=true;
            }
            break;
        case SCI_GETGAPPOSITION:
            {
                property->SetValueFromInt( m_scintilla1->GetGapPosition() );
                rv=true;
            }
            break;
        case SCI_GETDOCPOINTER:
            {
                property->SetValueFromInt(reinterpret_cast<int>( m_scintilla1->GetCharacterPointer() ));
                rv=true;
            }
            break;
        case SCI_SETDOCPOINTER:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                void* vp = reinterpret_cast<void *>(l1);

                m_scintilla1->SetDocPointer(vp);

                if(currentDocument!=nullptr)
                {
                    documentRefCnt[currentDocument]=documentRefCnt[currentDocument]-1;

                    if(documentRefCnt[currentDocument]==0)
                    {
                        std::map<void*,int>::iterator it= documentRefCnt.find(currentDocument);
                        documentRefCnt.erase(it);

                        //the manual says that
                        //3. If the reference count reaches 0, the document is deleted.
                        //So I'm going to assume that scintilla does the deletion and
                        //not delete it here.  If that assumption is wrong, there
                        //will be a memory leak.
                    }
                }

                if(l1==0)
                {
                    currentDocument=nullptr;
                    //currentDocument=m_scintilla1->GetDocPointer();
                    //documentRefCnt.insert(std::pair<void*,int>(currentDocument,1));
                }
                else
                {
                    currentDocument=vp;
                    documentRefCnt[vp]=documentRefCnt[vp]+1;
                }

                buildMultipleViewsEnums();

                rv=false;
            }
            break;
        case SCI_CREATEDOCUMENT:
            {
                void* p=m_scintilla1->CreateDocument();

                documentRefCnt.insert(std::pair<void*,int>(p,1));



                buildMultipleViewsEnums();

                property->SetValueFromInt(reinterpret_cast<int>(p));
                rv=false;
            }
            break;
        case SCI_ADDREFDOCUMENT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                if(l1==-1)
                {
                    currentDocument = m_scintilla1->GetDocPointer();
                    m_scintilla1->AddRefDocument(currentDocument);
                    documentRefCnt.insert(std::pair<void*,int>(currentDocument,2));
                    //Although it wasn't being tracked in our system, the "current document"
                    //had a refrenece count of 1.  So when we add to our system because the
                    //addref method was called, we need to set it to have a ref count of 2:
                    //1 for its initial count and 1 for the count that was just added

                    //I'm putting "current document" in quotes because if you check
                    //SCI_SETDOCPOINTER with the initial blank document, it can change
                    //many times as the document changes.  It's seems that it's n
                }
                else
                {
                    void* vp = reinterpret_cast<void *>(l1);
                    m_scintilla1->AddRefDocument(vp);
                    documentRefCnt[vp]=documentRefCnt[vp]+1;
                }

                buildMultipleViewsEnums();

                rv=false;
            }
            break;
        case SCI_RELEASEDOCUMENT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                void* vp = reinterpret_cast<void *>(l1);
                m_scintilla1->ReleaseDocument(vp);
                documentRefCnt[vp]=documentRefCnt[vp]-1;

                if(documentRefCnt[vp]==0)
                {
                    std::map<void*,int>::iterator it=documentRefCnt.find(vp);
                    documentRefCnt.erase(it);

                    //delete vp;
                    //It seems that when the reference count hits 0, the document is
                    //deleted aoutmatically.  I inially had

                    //if(documentRefCnt[vp]==-1)
                    // ....

                    //Ie, documents with refcount 0 were kept in the in the map and
                    //only deleted when the refcount hit -1.
                    //But when I then tried to set the document to a pointer that
                    //had a ref count of 0, the program crashed.
                    //Oddly, you can call SCI_RELEASEDOCUMENT and SCI_ADDREFDOCUMENT
                    //with that pointer and not crash the program.
                }


                buildMultipleViewsEnums();

                rv=false;
            }
            break;
        case SCI_CREATELOADER:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();

                int i=s.length();


                void* p=m_scintilla1->CreateLoader(i);

                if( p )
                {
                    ILoader* loader = static_cast<ILoader*>(p);


                    //This demonstrates loading in 10 byte blocks.  Obviously it's silly
                    //to load with such a small block size, but the exact same ideas could
                    //used with a more reasonable block size.

                    const char* s2= s;

                    bool sucess=true;
                    int code;

                    for(int j=i;j>0;j=j-10)
                    {
                        if(j>=10)
                        {
                            code = loader->AddData(const_cast<char*>(s2),10);
                            s2=s2+10;
                        }
                        else
                        {
                            code = loader->AddData(const_cast<char*>(s2),j);
                        }

                        if(code==wxSTC_STATUS_OK)
                        {
                            //nothing - continue iterating
                        }
                        else if(code == wxSTC_STATUS_FAILURE)
                        {
                            property->SetValueFromString("loading failed with wxSTC_STATUS_FAILURE");
                            break;
                        }
                        else if(code ==wxSTC_STATUS_BADALLOC)
                        {
                            property->SetValueFromString("loading failed with wxSTC_STATUS_BADALLOC");
                            break;
                        }
                        else
                        {
                            property->SetValueFromString(wxString::Format("loading failed with unknown code %d",code));
                            break;
                        }
                    }

                    if(sucess)
                    {
                        void* p = loader->ConvertToDocument();
                        documentRefCnt.insert(std::pair<void*,int>(p,1));
                        buildMultipleViewsEnums();



                        property->SetValueFromString( wxString::Format("document loaded - to set it current use SetDocPointer with %d",reinterpret_cast<int>(p)) );
                    }
                    else
                    {
                        loader->Release();
                    }

                    delete p;

                    //m_scintilla1->SetDocPointer ();

                    //property->SetValueFromString("Text Loaded!");
                }
                else
                {
                    property->SetValueFromString("Loader creation failed.");
                }

                rv=false;
            }
            break;

        case SCI_VISIBLEFROMDOCLINE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt( m_scintilla1->VisibleFromDocLine(l1) );
                rv=true;
            }
            break;
        case SCI_DOCLINEFROMVISIBLE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt( m_scintilla1->DocLineFromVisible(l1) );
                rv=true;
            }
            break;
        case SCI_SHOWLINES:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->ShowLines(l1,l2) ;
                rv=false;
            }
            break;
        case SCI_HIDELINES:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->HideLines(l1,l2);
                rv=false;
            }
            break;
        case SCI_GETLINEVISIBLE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromString(m_scintilla1->GetLineVisible(l1)?"True":"False");
                rv=true;
            }
            break;
        case SCI_GETALLLINESVISIBLE:
            {
                property->SetValueFromString(m_scintilla1->GetAllLinesVisible()?"True":"False");
                rv=true;
            }
            break;
        case SCI_SETFOLDLEVEL:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();
                it++;
                long l3 = it.GetProperty()->GetValue();

                m_scintilla1->SetFoldLevel(l1,l2|l3);
                rv=false;
            }
            break;
        case SCI_GETFOLDLEVEL:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                int i = m_scintilla1->GetFoldLevel(l1);

                int foldlevel = i& wxSTC_FOLDLEVELNUMBERMASK;

                bool whiteflag =(i& wxSTC_FOLDLEVELWHITEFLAG)?true:false;
                bool headerflag =(i& wxSTC_FOLDLEVELHEADERFLAG)?true:false;

                wxString s = "Fold level:";
                s<<foldlevel << " ";

                if(whiteflag)
                {
                    if(headerflag)
                    {
                        s << "wxSTC_FOLDLEVELWHITEFLAG | wxSTC_FOLDLEVELHEADERFLAG";
                    }
                    else
                    {
                        s << "wxSTC_FOLDLEVELWHITEFLAG";
                    }

                }
                else
                {
                    if(headerflag)
                    {
                        s << "wxSTC_FOLDLEVELHEADERFLAG";
                    }
                    else
                    {

                    }
                }

                property->SetValueFromString(s);
                rv=true;
            }
            break;
        case SCI_SETFOLDFLAGS:
            {
                m_scintilla1->SetFoldFlags( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETLASTCHILD:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetLastChild(l1,l2) );
                rv=true;
            }
            break;
        case SCI_GETFOLDPARENT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetFoldParent(l1) );
                rv=true;
            }
            break;
        case SCI_SETFOLDEXPANDED:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                bool b = it.GetProperty()->GetValue().GetBool();

                m_scintilla1->SetFoldExpanded(l1,b);
                rv=false;
            }
            break;
        case SCI_GETFOLDEXPANDED:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromString( m_scintilla1->GetFoldExpanded(l1)?"True":"False" );
                rv=true;
            }
            break;
        case SCI_CONTRACTEDFOLDNEXT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt( m_scintilla1->ContractedFoldNext(l1));
                rv=true;
            }
            break;
        case SCI_TOGGLEFOLD:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                m_scintilla1->ToggleFold(l1);
                rv=false;
            }
            break;
        case SCI_ENSUREVISIBLE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                m_scintilla1->EnsureVisible(l1);
                rv=false;
            }
            break;
        case SCI_ENSUREVISIBLEENFORCEPOLICY:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                m_scintilla1->EnsureVisibleEnforcePolicy(l1);
                rv=false;
            }
            break;
        case SCI_SETWRAPMODE:
            {
                m_scintilla1->SetWrapMode(property->GetValue().GetLong());
                rv=false;
            }
            break;
        case SCI_GETWRAPMODE:
            {
                int i=m_scintilla1->GetWrapMode();

                if(i==wxSTC_WRAP_NONE)
				{
					property->SetValueFromString("wxSTC_WRAP_NONE");
				}
                else if(i==wxSTC_WRAP_WORD)
				{
					property->SetValueFromString("wxSTC_WRAP_WORD");
				}
                else if(i==wxSTC_WRAP_CHAR)
				{
					property->SetValueFromString("wxSTC_WRAP_CHAR");
				}
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown wrap mode",i));
                }

                rv= true;
            }
            break;
        case SCI_SETWRAPVISUALFLAGS:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;

                int i = property->GetValue().GetLong();

                if(i==wxSTC_WRAPVISUALFLAG_NONE)
                {
                    it.GetProperty()->SetValueFromInt(wxSTC_WRAPVISUALFLAG_NONE);
                    it.GetProperty()->Enable(false);
                    m_scintilla1->SetWrapVisualFlags(wxSTC_WRAPVISUALFLAG_NONE);
                }
                else
                {
                    long l1 = it.GetProperty()->GetValue();
                    it.GetProperty()->Enable(true);
                    m_scintilla1->SetWrapVisualFlags(l1);
                }

                rv=false;
            }
            break;
        case SCI_SETWRAPVISUALFLAGS2:
            {
                m_scintilla1->SetWrapVisualFlags(property->GetValue().GetLong());
                rv=false;
            }
            break;
        case SCI_GETWRAPVISUALFLAGS:
            {
                long l= m_scintilla1->GetWrapVisualFlags();

                wxString s;
                bool already_added(false);

                if(l==wxSTC_WRAPVISUALFLAG_NONE)
                {
                    s<<"wxSTC_WRAPVISUALFLAG_NONE";
                }

                if(l&wxSTC_WRAPVISUALFLAG_END)
                {
                    s<<"wxSTC_WRAPVISUALFLAG_END";
                    already_added=true;
                }

                if(l&wxSTC_WRAPVISUALFLAG_START)
                {
                    s<< (already_added?"|":"")<<"wxSTC_WRAPVISUALFLAG_START";
                    already_added=true;
                }

                if(l&wxSTC_WRAPVISUALFLAG_MARGIN)
                {
                    s<< (already_added?"|":"")<<"wxSTC_WRAPVISUALFLAG_MARGIN";
                    already_added=true;
                }

                property->SetValueFromString(s);
                rv= true;
            }
            break;
        case SCI_SETWRAPVISUALFLAGSLOCATION:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;

                int i = property->GetValue().GetLong();

                if(i==wxSTC_WRAPVISUALFLAGLOC_DEFAULT)
                {
                    it.GetProperty()->SetValueFromInt(wxSTC_WRAPVISUALFLAGLOC_DEFAULT);
                    it.GetProperty()->Enable(false);
                    m_scintilla1->SetWrapVisualFlagsLocation(wxSTC_WRAPVISUALFLAGLOC_DEFAULT);
                }
                else
                {
                    long l1 = it.GetProperty()->GetValue();
                    it.GetProperty()->Enable(true);
                    m_scintilla1->SetWrapVisualFlagsLocation(l1);
                }

                rv=false;
            }
            break;
        case SCI_SETWRAPVISUALFLAGSLOCATION2:
            {
                m_scintilla1->SetWrapVisualFlagsLocation(property->GetValue().GetLong());
                rv=false;
            }
            break;
        case SCI_GETWRAPVISUALFLAGSLOCATION:
            {
                long l= m_scintilla1->GetWrapVisualFlagsLocation();

                wxString s;
                bool already_added(false);

                if(l==wxSTC_WRAPVISUALFLAGLOC_DEFAULT)
                {
                    s<<"wxSTC_WRAPVISUALFLAGLOC_DEFAULT";
                }

                if(l&wxSTC_WRAPVISUALFLAGLOC_END_BY_TEXT)
                {
                    s<<"wxSTC_WRAPVISUALFLAGLOC_END_BY_TEXT";
                    already_added=true;
                }

                if(l&wxSTC_WRAPVISUALFLAGLOC_START_BY_TEXT)
                {
                    s<< (already_added?"|":"")<<"wxSTC_WRAPVISUALFLAGLOC_START_BY_TEXT";
                    already_added=true;
                }

                property->SetValueFromString(s);
                rv= true;
            }
            break;
        case SCI_SETWRAPINDENTMODE:
            {
                m_scintilla1->SetWrapIndentMode( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETWRAPINDENTMODE:
            {
                int i=m_scintilla1->GetWrapIndentMode();

                if(i==wxSTC_WRAPINDENT_FIXED)
				{
					property->SetValueFromString("wxSTC_WRAPINDENT_FIXED");
				}
                else if(i==wxSTC_WRAPINDENT_SAME)
				{
					property->SetValueFromString("wxSTC_WRAPINDENT_SAME");
				}
                else if(i==wxSTC_WRAPINDENT_INDENT)
				{
					property->SetValueFromString("wxSTC_WRAPINDENT_INDENT");
				}
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown wrap indent mode",i));
                }

                rv= true;
            }
            break;
        case SCI_SETWRAPSTARTINDENT:
            {
                m_scintilla1->SetWrapStartIndent( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETWRAPSTARTINDENT:
            {
                property->SetValueFromInt( m_scintilla1->GetWrapStartIndent() );
                rv=true;
            }
            break;
        case SCI_SETLAYOUTCACHE:
            {
                m_scintilla1->SetLayoutCache( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETLAYOUTCACHE:
            {
                int i=m_scintilla1->GetLayoutCache();

                if(i==wxSTC_CACHE_NONE)
				{
					property->SetValueFromString("wxSTC_CACHE_NONE");
				}
                else if(i==wxSTC_CACHE_CARET)
				{
					property->SetValueFromString("wxSTC_CACHE_CARET");
				}
                else if(i==wxSTC_CACHE_PAGE)
				{
					property->SetValueFromString("wxSTC_CACHE_PAGE");
				}
                else if(i==wxSTC_CACHE_DOCUMENT)
				{
					property->SetValueFromString("wxSTC_CACHE_DOCUMENT");
				}
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown layout cache mode",i));
                }

                rv= true;
            }
            break;
        case SCI_SETPOSITIONCACHE:
            {
                m_scintilla1->SetPositionCacheSize( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETPOSITIONCACHE:
            {
                property->SetValueFromInt( m_scintilla1->GetPositionCacheSize() );
                rv=true;
            }
            break;
        case SCI_LINESSPLIT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                m_scintilla1->LinesSplit(l1);
                rv=false;
            }
            break;
        case SCI_LINESJOIN:
            {
                m_scintilla1->LinesJoin();
                rv=false;
            }
            break;
        case SCI_WRAPCOUNT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();

                property->SetValueFromInt(m_scintilla1->WrapCount(l1));
                rv=false;
            }
            break;
        case SCI_ZOOMIN:
            {
                m_scintilla1->ZoomIn();
                rv=false;
            }
            break;
        case SCI_ZOOMOUT:
            {
                m_scintilla1->ZoomOut();
                rv=false;
            }
            break;
        case SCI_SETZOOM:
            {
                m_scintilla1->SetZoom( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETZOOM:
            {
                property->SetValueFromInt( m_scintilla1->GetZoom() );
                rv=true;
            }
            break;
        case SCI_SETEDGEMODE:
            {
                m_scintilla1->SetEdgeMode( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETEDGEMODE:
            {
                int i=m_scintilla1->GetEdgeMode();

                if( i==wxSTC_EDGE_NONE )
				{
					property->SetValueFromString("wxSTC_EDGE_NONE");
				}
                else if( i==wxSTC_EDGE_LINE )
				{
					property->SetValueFromString("wxSTC_EDGE_LINE");
				}
                else if( i==wxSTC_EDGE_BACKGROUND )
				{
					property->SetValueFromString("wxSTC_EDGE_BACKGROUND");
				}
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown edge mode",i));
                }

                rv= true;
            }
            break;
        case SCI_SETEDGECOLUMN:
            {
                m_scintilla1->SetEdgeColumn( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETEDGECOLUMN:
            {
                property->SetValueFromInt( m_scintilla1->GetEdgeColumn() );
                rv=true;
            }
            break;
        case SCI_SETEDGECOLOUR:
            {
                wxAny value = property->GetValue();
                m_scintilla1->SetEdgeColour( value.As<wxColour>() );
                rv=false;
            }
            break;
        case SCI_GETEDGECOLOUR:
            {
                setColorString(property, m_scintilla1->GetEdgeColour());
                rv=true;
            }
            break;
        case SCI_SETLEXER:
            {
                int lexerno=property->GetValue().GetLong();
                m_scintilla1->SetLexer(lexerno);
                lexerSetHelper(lexerno);

                rv=false;
            }
            break;
        case SCI_SETLEXERBOOLPROPERTY:
            {
                m_scintilla1->SetProperty(property->GetBaseName(),(property->GetValue().GetBool()?"1":"0"));
                rv=false;
            }
            break;
        case SCI_SETLEXERINTPROPERTY:
            {
                m_scintilla1->SetProperty( property->GetBaseName() , wxString::Format("d",property->GetValue().GetLong()) );
                rv=false;
            }
            break;
        case SCI_SETLEXERSTRINGPROPERTY:
            {
                m_scintilla1->SetProperty(property->GetBaseName(),property->GetValue().GetString() );
                rv=false;
            }
            break;
        case SCI_GETLEXER:
            {
                int i = m_scintilla1->GetLexer();

                if(i==wxSTC_LEX_CONTAINER){property->SetValue(wxString::Format("%d - wxSTC_LEX_CONTAINER",i));}
                else if(i==wxSTC_LEX_NULL){property->SetValue(wxString::Format("%d - wxSTC_LEX_NULL",i));}
                else if(i==wxSTC_LEX_PYTHON){property->SetValue(wxString::Format("%d - wxSTC_LEX_PYTHON",i));}
                else if(i==wxSTC_LEX_CPP){property->SetValue(wxString::Format("%d - wxSTC_LEX_CPP",i));}
                else if(i==wxSTC_LEX_HTML){property->SetValue(wxString::Format("%d - wxSTC_LEX_HTML",i));}
                else if(i==wxSTC_LEX_XML){property->SetValue(wxString::Format("%d - wxSTC_LEX_XML",i));}
                else if(i==wxSTC_LEX_PERL){property->SetValue(wxString::Format("%d - wxSTC_LEX_PERL",i));}
                else if(i==wxSTC_LEX_SQL){property->SetValue(wxString::Format("%d - wxSTC_LEX_SQL",i));}
                else if(i==wxSTC_LEX_VB){property->SetValue(wxString::Format("%d - wxSTC_LEX_VB",i));}
                else if(i==wxSTC_LEX_PROPERTIES){property->SetValue(wxString::Format("%d - wxSTC_LEX_PROPERTIES",i));}
                else if(i==wxSTC_LEX_ERRORLIST){property->SetValue(wxString::Format("%d - wxSTC_LEX_ERRORLIST",i));}
                else if(i==wxSTC_LEX_MAKEFILE){property->SetValue(wxString::Format("%d - wxSTC_LEX_MAKEFILE",i));}
                else if(i==wxSTC_LEX_BATCH){property->SetValue(wxString::Format("%d - wxSTC_LEX_BATCH",i));}
                else if(i==wxSTC_LEX_XCODE){property->SetValue(wxString::Format("%d - wxSTC_LEX_XCODE",i));}
                else if(i==wxSTC_LEX_LATEX){property->SetValue(wxString::Format("%d - wxSTC_LEX_LATEX",i));}
                else if(i==wxSTC_LEX_LUA){property->SetValue(wxString::Format("%d - wxSTC_LEX_LUA",i));}
                else if(i==wxSTC_LEX_DIFF){property->SetValue(wxString::Format("%d - wxSTC_LEX_DIFF",i));}
                else if(i==wxSTC_LEX_CONF){property->SetValue(wxString::Format("%d - wxSTC_LEX_CONF",i));}
                else if(i==wxSTC_LEX_PASCAL){property->SetValue(wxString::Format("%d - wxSTC_LEX_PASCAL",i));}
                else if(i==wxSTC_LEX_AVE){property->SetValue(wxString::Format("%d - wxSTC_LEX_AVE",i));}
                else if(i==wxSTC_LEX_ADA){property->SetValue(wxString::Format("%d - wxSTC_LEX_ADA",i));}
                else if(i==wxSTC_LEX_LISP){property->SetValue(wxString::Format("%d - wxSTC_LEX_LISP",i));}
                else if(i==wxSTC_LEX_RUBY){property->SetValue(wxString::Format("%d - wxSTC_LEX_RUBY",i));}
                else if(i==wxSTC_LEX_EIFFEL){property->SetValue(wxString::Format("%d - wxSTC_LEX_EIFFEL",i));}
                else if(i==wxSTC_LEX_EIFFELKW){property->SetValue(wxString::Format("%d - wxSTC_LEX_EIFFELKW",i));}
                else if(i==wxSTC_LEX_TCL){property->SetValue(wxString::Format("%d - wxSTC_LEX_TCL",i));}
                else if(i==wxSTC_LEX_NNCRONTAB){property->SetValue(wxString::Format("%d - wxSTC_LEX_NNCRONTAB",i));}
                else if(i==wxSTC_LEX_BULLANT){property->SetValue(wxString::Format("%d - wxSTC_LEX_BULLANT",i));}
                else if(i==wxSTC_LEX_VBSCRIPT){property->SetValue(wxString::Format("%d - wxSTC_LEX_VBSCRIPT",i));}
                else if(i==wxSTC_LEX_BAAN){property->SetValue(wxString::Format("%d - wxSTC_LEX_BAAN",i));}
                else if(i==wxSTC_LEX_MATLAB){property->SetValue(wxString::Format("%d - wxSTC_LEX_MATLAB",i));}
                else if(i==wxSTC_LEX_SCRIPTOL){property->SetValue(wxString::Format("%d - wxSTC_LEX_SCRIPTOL",i));}
                else if(i==wxSTC_LEX_ASM){property->SetValue(wxString::Format("%d - wxSTC_LEX_ASM",i));}
                else if(i==wxSTC_LEX_CPPNOCASE){property->SetValue(wxString::Format("%d - wxSTC_LEX_CPPNOCASE",i));}
                else if(i==wxSTC_LEX_FORTRAN){property->SetValue(wxString::Format("%d - wxSTC_LEX_FORTRAN",i));}
                else if(i==wxSTC_LEX_F77){property->SetValue(wxString::Format("%d - wxSTC_LEX_F77",i));}
                else if(i==wxSTC_LEX_CSS){property->SetValue(wxString::Format("%d - wxSTC_LEX_CSS",i));}
                else if(i==wxSTC_LEX_POV){property->SetValue(wxString::Format("%d - wxSTC_LEX_POV",i));}
                else if(i==wxSTC_LEX_LOUT){property->SetValue(wxString::Format("%d - wxSTC_LEX_LOUT",i));}
                else if(i==wxSTC_LEX_ESCRIPT){property->SetValue(wxString::Format("%d - wxSTC_LEX_ESCRIPT",i));}
                else if(i==wxSTC_LEX_PS){property->SetValue(wxString::Format("%d - wxSTC_LEX_PS",i));}
                else if(i==wxSTC_LEX_NSIS){property->SetValue(wxString::Format("%d - wxSTC_LEX_NSIS",i));}
                else if(i==wxSTC_LEX_MMIXAL){property->SetValue(wxString::Format("%d - wxSTC_LEX_MMIXAL",i));}
                else if(i==wxSTC_LEX_CLW){property->SetValue(wxString::Format("%d - wxSTC_LEX_CLW",i));}
                else if(i==wxSTC_LEX_CLWNOCASE){property->SetValue(wxString::Format("%d - wxSTC_LEX_CLWNOCASE",i));}
                else if(i==wxSTC_LEX_LOT){property->SetValue(wxString::Format("%d - wxSTC_LEX_LOT",i));}
                else if(i==wxSTC_LEX_YAML){property->SetValue(wxString::Format("%d - wxSTC_LEX_YAML",i));}
                else if(i==wxSTC_LEX_TEX){property->SetValue(wxString::Format("%d - wxSTC_LEX_TEX",i));}
                else if(i==wxSTC_LEX_METAPOST){property->SetValue(wxString::Format("%d - wxSTC_LEX_METAPOST",i));}
                else if(i==wxSTC_LEX_POWERBASIC){property->SetValue(wxString::Format("%d - wxSTC_LEX_POWERBASIC",i));}
                else if(i==wxSTC_LEX_FORTH){property->SetValue(wxString::Format("%d - wxSTC_LEX_FORTH",i));}
                else if(i==wxSTC_LEX_ERLANG){property->SetValue(wxString::Format("%d - wxSTC_LEX_ERLANG",i));}
                else if(i==wxSTC_LEX_OCTAVE){property->SetValue(wxString::Format("%d - wxSTC_LEX_OCTAVE",i));}
                else if(i==wxSTC_LEX_MSSQL){property->SetValue(wxString::Format("%d - wxSTC_LEX_MSSQL",i));}
                else if(i==wxSTC_LEX_VERILOG){property->SetValue(wxString::Format("%d - wxSTC_LEX_VERILOG",i));}
                else if(i==wxSTC_LEX_KIX){property->SetValue(wxString::Format("%d - wxSTC_LEX_KIX",i));}
                else if(i==wxSTC_LEX_GUI4CLI){property->SetValue(wxString::Format("%d - wxSTC_LEX_GUI4CLI",i));}
                else if(i==wxSTC_LEX_SPECMAN){property->SetValue(wxString::Format("%d - wxSTC_LEX_SPECMAN",i));}
                else if(i==wxSTC_LEX_AU3){property->SetValue(wxString::Format("%d - wxSTC_LEX_AU3",i));}
                else if(i==wxSTC_LEX_APDL){property->SetValue(wxString::Format("%d - wxSTC_LEX_APDL",i));}
                else if(i==wxSTC_LEX_BASH){property->SetValue(wxString::Format("%d - wxSTC_LEX_BASH",i));}
                else if(i==wxSTC_LEX_ASN1){property->SetValue(wxString::Format("%d - wxSTC_LEX_ASN1",i));}
                else if(i==wxSTC_LEX_VHDL){property->SetValue(wxString::Format("%d - wxSTC_LEX_VHDL",i));}
                else if(i==wxSTC_LEX_CAML){property->SetValue(wxString::Format("%d - wxSTC_LEX_CAML",i));}
                else if(i==wxSTC_LEX_BLITZBASIC){property->SetValue(wxString::Format("%d - wxSTC_LEX_BLITZBASIC",i));}
                else if(i==wxSTC_LEX_PUREBASIC){property->SetValue(wxString::Format("%d - wxSTC_LEX_PUREBASIC",i));}
                else if(i==wxSTC_LEX_HASKELL){property->SetValue(wxString::Format("%d - wxSTC_LEX_HASKELL",i));}
                else if(i==wxSTC_LEX_PHPSCRIPT){property->SetValue(wxString::Format("%d - wxSTC_LEX_PHPSCRIPT",i));}
                else if(i==wxSTC_LEX_TADS3){property->SetValue(wxString::Format("%d - wxSTC_LEX_TADS3",i));}
                else if(i==wxSTC_LEX_REBOL){property->SetValue(wxString::Format("%d - wxSTC_LEX_REBOL",i));}
                else if(i==wxSTC_LEX_SMALLTALK){property->SetValue(wxString::Format("%d - wxSTC_LEX_SMALLTALK",i));}
                else if(i==wxSTC_LEX_FLAGSHIP){property->SetValue(wxString::Format("%d - wxSTC_LEX_FLAGSHIP",i));}
                else if(i==wxSTC_LEX_CSOUND){property->SetValue(wxString::Format("%d - wxSTC_LEX_CSOUND",i));}
                else if(i==wxSTC_LEX_FREEBASIC){property->SetValue(wxString::Format("%d - wxSTC_LEX_FREEBASIC",i));}
                else if(i==wxSTC_LEX_INNOSETUP){property->SetValue(wxString::Format("%d - wxSTC_LEX_INNOSETUP",i));}
                else if(i==wxSTC_LEX_OPAL){property->SetValue(wxString::Format("%d - wxSTC_LEX_OPAL",i));}
                else if(i==wxSTC_LEX_SPICE){property->SetValue(wxString::Format("%d - wxSTC_LEX_SPICE",i));}
                else if(i==wxSTC_LEX_D){property->SetValue(wxString::Format("%d - wxSTC_LEX_D",i));}
                else if(i==wxSTC_LEX_CMAKE){property->SetValue(wxString::Format("%d - wxSTC_LEX_CMAKE",i));}
                else if(i==wxSTC_LEX_GAP){property->SetValue(wxString::Format("%d - wxSTC_LEX_GAP",i));}
                else if(i==wxSTC_LEX_PLM){property->SetValue(wxString::Format("%d - wxSTC_LEX_PLM",i));}
                else if(i==wxSTC_LEX_PROGRESS){property->SetValue(wxString::Format("%d - wxSTC_LEX_PROGRESS",i));}
                else if(i==wxSTC_LEX_ABAQUS){property->SetValue(wxString::Format("%d - wxSTC_LEX_ABAQUS",i));}
                else if(i==wxSTC_LEX_ASYMPTOTE){property->SetValue(wxString::Format("%d - wxSTC_LEX_ASYMPTOTE",i));}
                else if(i==wxSTC_LEX_R){property->SetValue(wxString::Format("%d - wxSTC_LEX_R",i));}
                else if(i==wxSTC_LEX_MAGIK){property->SetValue(wxString::Format("%d - wxSTC_LEX_MAGIK",i));}
                else if(i==wxSTC_LEX_POWERSHELL){property->SetValue(wxString::Format("%d - wxSTC_LEX_POWERSHELL",i));}
                else if(i==wxSTC_LEX_MYSQL){property->SetValue(wxString::Format("%d - wxSTC_LEX_MYSQL",i));}
                else if(i==wxSTC_LEX_PO){property->SetValue(wxString::Format("%d - wxSTC_LEX_PO",i));}
                else if(i==wxSTC_LEX_TAL){property->SetValue(wxString::Format("%d - wxSTC_LEX_TAL",i));}
                else if(i==wxSTC_LEX_COBOL){property->SetValue(wxString::Format("%d - wxSTC_LEX_COBOL",i));}
                else if(i==wxSTC_LEX_TACL){property->SetValue(wxString::Format("%d - wxSTC_LEX_TACL",i));}
                else if(i==wxSTC_LEX_SORCUS){property->SetValue(wxString::Format("%d - wxSTC_LEX_SORCUS",i));}
                else if(i==wxSTC_LEX_POWERPRO){property->SetValue(wxString::Format("%d - wxSTC_LEX_POWERPRO",i));}
                else if(i==wxSTC_LEX_NIMROD){property->SetValue(wxString::Format("%d - wxSTC_LEX_NIMROD",i));}
                else if(i==wxSTC_LEX_SML){property->SetValue(wxString::Format("%d - wxSTC_LEX_SML",i));}
                else if(i==wxSTC_LEX_MARKDOWN){property->SetValue(wxString::Format("%d - wxSTC_LEX_MARKDOWN",i));}
                else if(i==wxSTC_LEX_TXT2TAGS){property->SetValue(wxString::Format("%d - wxSTC_LEX_TXT2TAGS",i));}
                else if(i==wxSTC_LEX_A68K){property->SetValue(wxString::Format("%d - wxSTC_LEX_A68K",i));}
                else if(i==wxSTC_LEX_MODULA){property->SetValue(wxString::Format("%d - wxSTC_LEX_MODULA",i));}
                else if(i==wxSTC_LEX_COFFEESCRIPT){property->SetValue(wxString::Format("%d - wxSTC_LEX_COFFEESCRIPT",i));}
                else if(i==wxSTC_LEX_TCMD){property->SetValue(wxString::Format("%d - wxSTC_LEX_TCMD",i));}
                else if(i==wxSTC_LEX_AVS){property->SetValue(wxString::Format("%d - wxSTC_LEX_AVS",i));}
                else if(i==wxSTC_LEX_ECL){property->SetValue(wxString::Format("%d - wxSTC_LEX_ECL",i));}
                else if(i==wxSTC_LEX_OSCRIPT){property->SetValue(wxString::Format("%d - wxSTC_LEX_OSCRIPT",i));}
                else if(i==wxSTC_LEX_VISUALPROLOG){property->SetValue(wxString::Format("%d - wxSTC_LEX_VISUALPROLOG",i));}
                else {property->SetValue(wxString::Format("%d - unknown lexer",i));}


                //property->SetValueFromInt( m_scintilla1->GetLexer());
                rv=true;
            }
            break;
        case SCI_SETLEXERLANGUAGE:
            {
                wxString s = m_propgrid->GetPropertyValueAsString (property);

                int oldlexer = m_scintilla1->GetLexer();


                m_scintilla1->SetLexerLanguage( s );

                int newlexer = m_scintilla1->GetLexer();

                if(oldlexer!=newlexer)
                {
                    LexerProp->SetValueFromInt(newlexer);
                    lexerSetHelper(newlexer);
                }

                rv=false;
            }
            break;
        case SCI_GETLEXERLANGUAGE:
            {
                int msg = 4012;
                int len = m_scintilla1->SendMsg(msg, 0, (sptr_t)NULL);
                if (!len)
                {
                    property->SetValueFromString("");
                }
                else
                {
                    wxMemoryBuffer mbuf(len+1);
                    char* buf = (char*)mbuf.GetWriteBuf(len+1);
                    m_scintilla1->SendMsg(msg, 0, (sptr_t)buf);
                    mbuf.UngetWriteBuf(len);
                    mbuf.AppendByte(0);

                    property->SetValueFromString(buf);
                }

                rv=true;
            }
            break;
        case SCI_LOADLEXERLIBRARY:
            {
                rv=false;
            }
            break;
        case SCI_COLOURISE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->Colourise(l1,l2);
                rv=false;
            }
            break;
        case SCI_CHANGELEXERSTATE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                long l2 = it.GetProperty()->GetValue();

                m_scintilla1->ChangeLexerState(l1,l2);
                rv=false;
            }
            break;
        case SCI_PROPERTYNAMES:
            {
                property->SetValueFromString( m_scintilla1->PropertyNames() );
                rv=true;
            }
            break;
        case SCI_PROPERTYTYPE:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();

                int i=m_scintilla1->PropertyType(s);

                if( i==wxSTC_TYPE_BOOLEAN )
				{
					property->SetValueFromString("wxSTC_TYPE_BOOLEAN");
				}
                else if( i==wxSTC_TYPE_INTEGER )
				{
					property->SetValueFromString("wxSTC_TYPE_INTEGER");
				}
                else if( i==wxSTC_TYPE_STRING )
				{
					property->SetValueFromString("wxSTC_TYPE_STRING");
				}
                else
                {
                    property->SetValueFromString(wxString::Format("(%d - unknown property type",i));
                }

                rv= true;
            }
            break;
        case SCI_DESCRIBEPROPERTY:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();

                property->SetValueFromString( m_scintilla1->DescribeProperty(s) );

                rv=true;
            }
            break;
        case SCI_SETPROPERTY:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s1 = it.GetProperty()->GetValue();
                it++;
                wxString s2 = it.GetProperty()->GetValue();
                m_scintilla1->SetProperty(s1,s2);

                rv=false;
            }
            break;
        case SCI_GETPROPERTY:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();

                property->SetValueFromString( m_scintilla1->GetProperty(s) );

                rv=true;
            }
            break;
        case SCI_GETPROPERTYEXPANDED:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();

                property->SetValueFromString( m_scintilla1->GetPropertyExpanded(s) );

                rv=true;
            }
            break;
        case SCI_GETPROPERTYINT:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();

                property->SetValueFromInt( m_scintilla1->GetPropertyInt(s) );

                rv=true;
            }
            break;
        case SCI_DESCRIBEKEYWORDSETS:
            {
                property->SetValueFromString( m_scintilla1->DescribeKeyWordSets() );
                rv=false;
            }
            break;
        case SCI_SETKEYWORDS:
            {
                rv=false;
            }
            break;
        case SCI_SETKEYWORDS2:
            {
                myStyleData* msd = dynamic_cast<myStyleData*>(property->GetClientObject());

                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                wxString s = it.GetProperty()->GetValue();


                m_scintilla1->SetKeyWords( msd->get_style() , s );


                rv=false;
            }
            break;


        case SCI_GETSTYLEBITSNEEDED:
            {
                property->SetValueFromInt(m_scintilla1->GetStyleBitsNeeded());
                rv=true;
            }
            break;
        case SCI_PRIVATELEXERCALL:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;
                long l1 = it.GetProperty()->GetValue();
                it++;
                wxString s = it.GetProperty()->GetValue();

                char* buf= reinterpret_cast<char *>(malloc(s.length()));

                for(size_t i=0;i<s.length();i++)
                {
                    char c = s[i].GetValue();
                    *(buf+i)=c;
                }

                void* p = m_scintilla1->PrivateLexerCall( l1 , reinterpret_cast<void*>(buf) );

                property->SetValueFromInt( reinterpret_cast<int>(p) );

                free(buf);
                rv=false;
            }
            break;
        case SCI_SETMODEVENTMASK:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;

                int i = property->GetValue().GetLong();

                if(i==wxSTC_MODEVENTMASKALL)
                {
                    it.GetProperty()->SetValueFromInt(wxSTC_MODEVENTMASKALL);
                    it.GetProperty()->Enable(false);
                    m_scintilla1->SetModEventMask(wxSTC_MODEVENTMASKALL);
                }
                else
                {
                    long l1 = it.GetProperty()->GetValue();
                    it.GetProperty()->Enable(true);
                    m_scintilla1->SetModEventMask(l1);
                }

                rv=false;
            }
            break;
        case SCI_SETMODEVENTMASK2:
            {
                m_scintilla1->SetModEventMask( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETMODEVENTMASK:
            {
                long l= m_scintilla1->GetModEventMask();

                wxString s;
                bool already_added(false);

                if(l==wxSTC_MODEVENTMASKALL)
                {
                    s<<"wxSTC_MODEVENTMASKALL";
                }
				else
				{
					if(l&wxSTC_MOD_INSERTTEXT)
					{
						s<<"wxSTC_MOD_INSERTTEXT";
						already_added=true;
					}

					if(l&wxSTC_MOD_DELETETEXT)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_DELETETEXT";
						already_added=true;
					}

					if(l&wxSTC_MOD_CHANGESTYLE)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_CHANGESTYLE";
						already_added=true;
					}

					if(l&wxSTC_MOD_CHANGEFOLD)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_CHANGEFOLD";
						already_added=true;
					}

					if(l&wxSTC_PERFORMED_USER)
					{
						s<< (already_added?"|":"")<<"wxSTC_PERFORMED_USER";
						already_added=true;
					}

					if(l&wxSTC_PERFORMED_UNDO)
					{
						s<< (already_added?"|":"")<<"wxSTC_PERFORMED_UNDO";
						already_added=true;
					}

					if(l&wxSTC_PERFORMED_REDO)
					{
						s<< (already_added?"|":"")<<"wxSTC_PERFORMED_REDO";
						already_added=true;
					}

					if(l&wxSTC_MULTISTEPUNDOREDO)
					{
						s<< (already_added?"|":"")<<"wxSTC_MULTISTEPUNDOREDO";
						already_added=true;
					}

					if(l&wxSTC_LASTSTEPINUNDOREDO)
					{
						s<< (already_added?"|":"")<<"wxSTC_LASTSTEPINUNDOREDO";
						already_added=true;
					}

					if(l&wxSTC_MOD_CHANGEMARKER)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_CHANGEMARKER";
						already_added=true;
					}

					if(l&wxSTC_MOD_BEFOREINSERT)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_BEFOREINSERT";
						already_added=true;
					}

					if(l&wxSTC_MOD_BEFOREDELETE)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_BEFOREDELETE";
						already_added=true;
					}

					if(l&wxSTC_MULTILINEUNDOREDO)
					{
						s<< (already_added?"|":"")<<"wxSTC_MULTILINEUNDOREDO";
						already_added=true;
					}

					if(l&wxSTC_STARTACTION)
					{
						s<< (already_added?"|":"")<<"wxSTC_STARTACTION";
						already_added=true;
					}

					if(l&wxSTC_MOD_CHANGEINDICATOR)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_CHANGEINDICATOR";
						already_added=true;
					}

					if(l&wxSTC_MOD_CHANGELINESTATE)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_CHANGELINESTATE";
						already_added=true;
					}

					if(l&wxSTC_MOD_CHANGEMARGIN)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_CHANGEMARGIN";
						already_added=true;
					}

					if(l&wxSTC_MOD_CHANGEANNOTATION)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_CHANGEANNOTATION";
						already_added=true;
					}

					if(l&wxSTC_MOD_CONTAINER)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_CONTAINER";
						already_added=true;
					}

					if(l&wxSTC_MOD_LEXERSTATE)
					{
						s<< (already_added?"|":"")<<"wxSTC_MOD_LEXERSTATE";
						already_added=true;
					}
				}

                property->SetValueFromString(s);
                rv= true;
            }
            break;
        case SCI_SETMOUSEDWELLTIME:
            {
                wxPropertyGridIterator it = m_propgrid->GetGrid ()->GetIterator(wxPG_ITERATE_DEFAULT,property);
                it++;

                int i = property->GetValue().GetLong();

                if(i==wxSTC_TIME_FOREVER)
                {
                    it.GetProperty()->SetValueFromInt(wxSTC_TIME_FOREVER);
                    it.GetProperty()->Enable(false);
                    m_scintilla1->SetMouseDwellTime(wxSTC_TIME_FOREVER);
                }
                else
                {
                    long l1 = it.GetProperty()->GetValue();
                    it.GetProperty()->Enable(true);
                    m_scintilla1->SetMouseDwellTime(l1);
                }

                rv=false;
            }
            break;
        case SCI_SETMOUSEDWELLTIME2:
            {
                m_scintilla1->SetMouseDwellTime( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETMOUSEDWELLTIME:
            {
                int i=m_scintilla1->GetMouseDwellTime();

                if(i==wxSTC_TIME_FOREVER)
                {
                    property->SetValueFromString("wxSTC_TIME_FOREVER");
                }
                else
                {
                    property->SetValueFromInt(i);
                }

                rv=true;
            }
            break;
        case SCI_SETIDENTIFIER:
            {
                m_scintilla1->SetIdentifier( property->GetValue().GetLong() );
                rv=false;
            }
            break;
        case SCI_GETIDENTIFIER:
            {
                property->SetValueFromInt( m_scintilla1->GetIdentifier() );
                rv=true;
            }
            break;
        default:
            wxMessageBox("Property was not handled.\n");
            rv=false;  // Return false since value did not change
            break;
    }

    return rv;
}
