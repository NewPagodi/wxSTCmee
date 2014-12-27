#include "stcMain.h"
#include "lexers.h"

void propgridtest03Frame::buildMarkerEnums()
{
    wxArrayString cases;
    wxArrayInt cases_values;

    wxPGProperty* np2,*np3 ;

    if(markers.empty())
    {
        cases.Add("(no markers are currently defined)");
        cases_values.Add(-1);
    }
    else
    {
        int handle;
        int line;
        int found_line;

        for(std::vector<marker*>::iterator it =markers.begin() ;it!=markers.end();it++)
        {
            //since editing the text can change the line numbers of markers, we'll take this
            //oportunity to make any necessary updates

            handle = (*it)->handle;
            line = handle,(*it)->lineNo;
            found_line=m_scintilla1->MarkerLineFromHandle(handle);

            if(found_line!=line)
            {
                (*it)->lineNo=found_line;
            }

            cases.Add(wxString::Format("%d (line %d - marker %d)",handle,found_line,(*it)->markerNo));
            cases_values.Add((*it)->handle);
        }
    }

    np2 = new wxEnumProperty("handle","zzz",cases,cases_values,cases_values[0]);
    np2->SetClientData(reinterpret_cast<void*>(SCI_PARAM));
    np2->Enable(!markers.empty());
    m_propgrid->ReplaceProperty(SCI_MARKERLINEFROMHANDLEENUM,np2);
    SCI_MARKERLINEFROMHANDLEENUM=np2;

    np3 = new wxEnumProperty("handle","zzz",cases,cases_values,cases_values[0]);
    np3->SetClientData(reinterpret_cast<void*>(SCI_PARAM));
    np3->Enable(!markers.empty());
    m_propgrid->ReplaceProperty(SCI_MARKERDELETEHANDLEENUM,np3);
    SCI_MARKERDELETEHANDLEENUM=np3;
}

void propgridtest03Frame::buildCmdKeyClearEnum()
{
    wxArrayString cases;
    wxArrayInt cases_values;

    wxPGProperty* np2 ;

    if(keyBindings.empty())
    {
        cases.Add("no keys are currently bound");
        cases_values.Add(-1);

        np2 = new wxEnumProperty("binding",wxPG_LABEL,cases,cases_values,-1);
        np2->Enable(false);
    }
    else
    {
        int i=0;
        for(std::vector<keyBinding*>::iterator it=keyBindings.begin();it!=keyBindings.end();it++)
        {
            cases.Add((*it)->getBinding());
            cases_values.Add(i);
            i++;
        }

        np2 = new wxEnumProperty("binding",wxPG_LABEL,cases,cases_values,0);
    }

    np2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));
    m_propgrid->ReplaceProperty(SCI_CLEARCMDKEYENUM,np2);

    SCI_CLEARCMDKEYENUM=np2;
}


void propgridtest03Frame::buildMultipleViewsEnums()
{
    wxArrayString cases;
    wxArrayInt cases_values;
    cases.Add("0");
    cases_values.Add(0);

    for(std::map<void*,int>::iterator it= documentRefCnt.begin();it!=documentRefCnt.end();it++)
    {
        if(it->first!=currentDocument)
        {
            cases.Add(wxString::Format("%d",reinterpret_cast<int>(it->first) ));
            cases_values.Add(reinterpret_cast<int>(it->first));
        }
    }


    wxPGProperty* np2 = new wxEnumProperty("docPointer",wxPG_LABEL,cases,cases_values,0);
    np2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));

    m_propgrid->ReplaceProperty(SCI_SETDOCPOINTERENUM,np2);
    SCI_SETDOCPOINTERENUM=np2;

    if(documentRefCnt.empty())
    {
        cases.Clear();
        cases_values.Clear();
        cases.Add("(current unreferenced document)");
        cases_values.Add(-1);

        np2 = new wxEnumProperty("docPointer",wxPG_LABEL,cases,cases_values,-1);
        np2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));

        m_propgrid->ReplaceProperty(SCI_ADDREFDOCUMENTENUM,np2);
        SCI_ADDREFDOCUMENTENUM=np2;

        np2 = new wxEnumProperty("docPointer",wxPG_LABEL,cases,cases_values,-1);
        np2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));
        np2->SetValueToUnspecified();
        np2->Enable(false);

        m_propgrid->ReplaceProperty(SCI_RELEASEDOCUMENTENUM,np2);
        SCI_RELEASEDOCUMENTENUM=np2;
    }
    else
    {
        cases.Clear();
        cases_values.Clear();

        for(std::map<void*,int>::iterator it= documentRefCnt.begin();it!=documentRefCnt.end();it++)
        {
            cases.Add(wxString::Format("%d (rc%d)",reinterpret_cast<int>(it->first),it->second ));
            cases_values.Add(reinterpret_cast<int>(it->first));
        }

        if(currentDocument==nullptr)
        {
            cases.Add("(current unreferenced document)");
            cases_values.Add(-1);
        }

        np2 = new wxEnumProperty("docPointer",wxPG_LABEL,cases,cases_values,cases_values[0]);
        np2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));

        m_propgrid->ReplaceProperty(SCI_ADDREFDOCUMENTENUM,np2);
        SCI_ADDREFDOCUMENTENUM=np2;


        cases.Clear();
        cases_values.Clear();

        for(std::map<void*,int>::iterator it= documentRefCnt.begin();it!=documentRefCnt.end();it++)
        {
            if(it->first!=currentDocument || it->second!=1)
            {
                cases.Add(wxString::Format("%d (rc%d)",reinterpret_cast<int>(it->first),it->second ));
                cases_values.Add(reinterpret_cast<int>(it->first));
            }
        }

        if( cases.GetCount()!=0)
        {
            np2 = new wxEnumProperty("docPointer",wxPG_LABEL,cases,cases_values,cases_values[0]);
        }
        else
        {
            np2 = new wxStringProperty("docPointer");
            np2->Enable(false);
        }
        np2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));

        m_propgrid->ReplaceProperty(SCI_RELEASEDOCUMENTENUM,np2);
        SCI_RELEASEDOCUMENTENUM=np2;
    }
}


void propgridtest03Frame::lexerSetHelper(int lexerno)
{
    lexerInfo->renameStyles(lexerno);
    lexerInfo->renameKWs(lexerno);

    wxPGProperty* p;
    while(!lexerProps.empty())
    {
        p=lexerProps.back();
        lexerProps.pop_back();
        m_propgrid->DeleteProperty(p);
    }

    std::vector<lexerProperty*> propset;
    lexerInfo->getLexerProps(lexerno,&propset);
    wxPGProperty* np;
    wxString label,dv;

    for(std::vector<lexerProperty*>::iterator it= propset.begin();it!=propset.end();it++)
    {
        //s = wxString::Format( "property:%s  type:%d  defaultvalue:%s\n" , (*it)->propery_name,(*it)->property_type, (*it)->default_value );

        dv=(*it)->default_value;
        label=(*it)->propery_name;

        if((*it)->property_type==0)
        {
            np = m_propgrid->AppendIn(LexerProp,new wxBoolProperty(label));
            np->SetClientData(reinterpret_cast<void *>(SCI_SETLEXERBOOLPROPERTY));
            m_propgrid->SetPropertyAttribute( np,wxPG_BOOL_USE_CHECKBOX,true );
            np->SetValue( dv=="0" );


        }
        else if((*it)->property_type==1)
        {
            np = m_propgrid->AppendIn(LexerProp,new wxIntProperty(label) );
            np->SetClientData(reinterpret_cast<void *>(SCI_SETLEXERINTPROPERTY));
            np->SetEditor( "SpinCtrl" );
            //np2->SetAttribute(  wxPG_ATTR_MIN, (long)0 );  // Use constants instead of string
            np->SetAttribute(  wxT("Step"), (long)1 );
            np->SetAttribute(  wxT("MotionSpin"), true );

            long tlong;
            dv.ToLong(&tlong);
            np->SetValueFromInt(tlong);

            //lexerProps.push_back(np);

        }
        else
        {
            np = m_propgrid->AppendIn(LexerProp,new wxLongStringProperty(label));
            np->SetClientData(reinterpret_cast<void *>(SCI_SETLEXERSTRINGPROPERTY));
        }

        lexerProps.push_back(np);
    }

    propset.clear();
}

void propgridtest03Frame::clearRegisteredImages()
{
    for(std::map<int,wxPGProperty*>::iterator it=registeredACImages.begin();it!=registeredACImages.end();it++)
    {
        m_propgrid->RemoveProperty(it->second);
    }
}

void propgridtest03Frame::addRegisteredImage(int l1,const wxString& s)
{
    std::map<int,wxPGProperty*>::iterator it2=registeredACImages.find(l1);
    if(it2!=registeredACImages.end())
    {
        m_propgrid->DeleteProperty(it2->second);
        registeredACImages.erase(it2);
    }

    std::map<int,unsigned char*>::iterator it3=registeredACRGBAData.find(l1);
    if(it3!=registeredACRGBAData.end())
    {
        free(it3->second);
        registeredACRGBAData.erase(it3);
    }

    wxPGProperty* np = new wxStringProperty(wxString::Format("%d",l1));
    np->SetClientData(reinterpret_cast<void *>(SCI_PARAM));
    np->SetValueFromString(s);

    clearRegisteredImages();
    registeredACImages.insert(std::pair<int,wxPGProperty*>(l1,np));

    m_propgrid->HideProperty(registerdACImageHeader, false);

    for(std::map<int,wxPGProperty*>::iterator it=registeredACImages.begin();it!=registeredACImages.end();it++)
    {
        m_propgrid->AppendIn(registerdACImageHeader,it->second);
    }
}




