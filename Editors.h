#ifndef EDITORS_H_INCLUDED
#define EDITORS_H_INCLUDED

#include <wx/propgrid/propgrid.h>

class propgridtest03Frame;

// -----------------------------------------------------------------------
// wxSampleMultiButtonEditor
//   A sample editor class that has multiple buttons.
// -----------------------------------------------------------------------

class wxSampleMultiButtonEditor : public wxPGTextCtrlEditor
{
    //DECLARE_DYNAMIC_CLASS(wxSampleMultiButtonEditor)
public:
    wxSampleMultiButtonEditor(propgridtest03Frame* _mf):mf(_mf) {}
    virtual ~wxSampleMultiButtonEditor() {}

    virtual wxPGWindowList CreateControls( wxPropertyGrid* propGrid,
                                           wxPGProperty* property,
                                           const wxPoint& pos,
                                           const wxSize& sz ) const;
    virtual bool OnEvent( wxPropertyGrid* propGrid,
                          wxPGProperty* property,
                          wxWindow* ctrl,
                          wxEvent& event ) const;

private:
    propgridtest03Frame* mf;
};

class wxSampleMultiButtonEditor2 : public wxPGTextCtrlEditor
{
public:
    wxSampleMultiButtonEditor2(propgridtest03Frame* _mf):mf(_mf) {}
    virtual ~wxSampleMultiButtonEditor2() {}

    virtual wxPGWindowList CreateControls( wxPropertyGrid* propGrid,
                                           wxPGProperty* property,
                                           const wxPoint& pos,
                                           const wxSize& sz ) const;
    virtual bool OnEvent( wxPropertyGrid* propGrid,
                          wxPGProperty* property,
                          wxWindow* ctrl,
                          wxEvent& event ) const;

private:
    propgridtest03Frame* mf;
};

class wxSampleStyledTextEditor : public wxPGTextCtrlEditor
{
    //DECLARE_DYNAMIC_CLASS(wxSampleMultiButtonEditor)
public:
    wxSampleStyledTextEditor(propgridtest03Frame* _mf):mf(_mf) {}
    virtual ~wxSampleStyledTextEditor() {}

    virtual wxPGWindowList CreateControls( wxPropertyGrid* propGrid,
                                           wxPGProperty* property,
                                           const wxPoint& pos,
                                           const wxSize& sz ) const;
    virtual bool OnEvent( wxPropertyGrid* propGrid,
                          wxPGProperty* property,
                          wxWindow* ctrl,
                          wxEvent& event ) const;

private:
    propgridtest03Frame* mf;
};

#endif // EDITORS_H_INCLUDED
