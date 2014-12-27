#include "stcMain.h"
#include <wx/propgrid/advprops.h>
#include <wx/dcmemory.h>

wxPGProperty*  propgridtest03Frame::addLongStringProp(wxPGProperty* st,const wxString& label,const wxString& name, int cd,bool clearable,bool readonly)
{
    wxPGProperty* np = m_propgrid->AppendIn(st,new wxLongStringProperty(label,name));
    np->SetClientData(reinterpret_cast<void *>(cd));
    m_propgrid->SetPropertyEditor(np, m_pSampleMultiButtonEditor );

    if(readonly)
    {
        m_propgrid->SetPropertyReadOnly(np);
    }

    if(clearable)
    {
        clearables.push_back(np);
    }

    return np;
}

wxPGProperty*  propgridtest03Frame::addStringProp(wxPGProperty* st,const wxString& label,const wxString& name, int cd,bool clearable,bool readonly)
{
    wxPGProperty* np = m_propgrid->AppendIn(st,new wxStringProperty(label,name));
    np->SetClientData(reinterpret_cast<void *>(cd));
    m_propgrid->SetPropertyEditor(np, m_pSampleMultiButtonEditor2 );

    if(readonly)
    {
        m_propgrid->SetPropertyReadOnly(np);
    }

    if(clearable)
    {
        clearables.push_back(np);
    }

    return np;
}

wxPGProperty* propgridtest03Frame::addDotDotDotStringProp(wxPGProperty* st,const wxString& label,const wxString& name, int cd)
{
    wxPGProperty* np = m_propgrid->AppendIn(st,new wxStringProperty(label,name));
    np->SetClientData(reinterpret_cast<void *>(cd));
    m_propgrid->SetPropertyEditor(np, m_StyledTextEditor );
    m_propgrid->SetPropertyReadOnly(np);

    return np;
}

void  propgridtest03Frame::addStringParam(wxPGProperty* np,const wxString& label,bool longstring)
{
    wxPGProperty* np2;

    if(longstring)
    {
        np2 =m_propgrid->AppendIn(np,new wxLongStringProperty(label,"zzz"));
    }
    else
    {
        np2 =m_propgrid->AppendIn(np,new wxStringProperty(label,"zzz"));
    }

    np2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));
}

wxPGProperty* propgridtest03Frame::addStringHeader(wxPGProperty* np,const wxString& label)
{
    wxPGProperty* np2;
    np2 =m_propgrid->AppendIn(np,new wxStringProperty(label,"zzz"));
    np2->SetClientData(reinterpret_cast<void *>(SCI_PARAM));
    m_propgrid->SetPropertyReadOnly(np2,true,wxPG_DONT_RECURSE);

    return np2;
}

void propgridtest03Frame::addIntParam(wxPGProperty* np,const wxString& label,int dv,int min,int max)
{
    addIntProp(np,label,"zzz",SCI_PARAM, dv, min, max);
}

wxPGProperty*  propgridtest03Frame::addIntProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd,int dv,int min,int max)
{
    wxPGProperty* np2 = m_propgrid->AppendIn(np,new wxIntProperty(label,name,dv));
    np2->SetClientData(reinterpret_cast<void *>(cd));
    np2->SetEditor( "SpinCtrl" );
    np2->SetAttribute(  wxT("Step"), (long)1 );
    np2->SetAttribute(  wxT("MotionSpin"), true );
    np2->SetAttribute(  wxPG_ATTR_MIN, (long)min);
    np2->SetAttribute(  wxPG_ATTR_MAX, (long)max );

    return np2;
}

void propgridtest03Frame::addBoolParam(wxPGProperty* np,const wxString& label,bool dv)
{
    addBoolProp(np,label,"zzz",SCI_PARAM,dv);
}

wxPGProperty* propgridtest03Frame::addBoolProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd,bool dv)
{
    wxPGProperty* np2 = m_propgrid->AppendIn(np,new wxBoolProperty(label,name));
    np2->SetClientData(reinterpret_cast<void *>(cd));
    m_propgrid->SetPropertyAttribute( np2,wxPG_BOOL_USE_CHECKBOX,true );
    np2->SetValue(dv);

    return np2;
}

wxPGProperty* propgridtest03Frame::addFlagsProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd,long dv,wxArrayString& cases,wxArrayInt& cases_values)
{
    wxPGProperty* np2 = m_propgrid ->AppendIn(np, new wxFlagsProperty(label,name,cases,cases_values,dv) );
    np2->SetClientData(reinterpret_cast<void *>(cd));
    m_propgrid->SetPropertyAttribute( np2,wxPG_BOOL_USE_CHECKBOX,true,wxPG_RECURSE );
    return np2;
}

void propgridtest03Frame::addFlagsParam(wxPGProperty* np,const wxString& label,long dv,wxArrayString& cases,wxArrayInt& cases_values)
{
    addFlagsProp(np,label,"zzz",SCI_PARAM,dv, cases,cases_values);
}

wxPGProperty* propgridtest03Frame::addEnumProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd,long dv,wxArrayString& cases,wxArrayInt& cases_values)
{
    wxPGProperty* np2 = m_propgrid->AppendIn(np, new wxEnumProperty(label,name,cases,cases_values,dv) );
    np2->SetClientData(reinterpret_cast<void *>(cd));
    return np2;
}

void propgridtest03Frame::addEnumParam(wxPGProperty* np,const wxString& label,long dv,wxArrayString& cases,wxArrayInt& cases_values)
{
    addEnumProp(np,label,"zzz",SCI_PARAM,dv, cases,cases_values);
}

wxPGProperty* propgridtest03Frame::addColorProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd, const wxColor& dv)
{
    wxPGProperty* np2 = m_propgrid->AppendIn(np,new wxColourProperty(label,name,dv  ));
    np2->SetClientData(reinterpret_cast<void *>(cd));
    //np2->SetAttribute( "HasAlpha", false);
    //np2->SetAutoUnspecified();

    return np2;
}


void propgridtest03Frame::addColorParam(wxPGProperty* np,const wxString& label,const wxColor& dv)
{
    addColorProp(np, label,"zzz",SCI_PARAM,dv);
}

void propgridtest03Frame::addColorStringProp(wxPGProperty* np,const wxString& label,const wxString& name,int cd)
{
    wxPGProperty* np2=addStringProp(np, label, name, cd,true,true);

    wxBitmap test_bitmap(20,15);
    wxMemoryDC temp_dc;
    temp_dc.SelectObject(test_bitmap);

    temp_dc.SetPen(*wxWHITE_PEN);
    temp_dc.SetBrush( wxBrush(*wxWHITE) );
    temp_dc.DrawRectangle( 0,0,20,15);
    temp_dc.SelectObject(wxNullBitmap);

    np2->SetValueImage(test_bitmap);
}
