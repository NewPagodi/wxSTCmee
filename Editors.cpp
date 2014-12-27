#include "Editors.h"
#include "stcMain.h"

wxPGWindowList wxSampleMultiButtonEditor::CreateControls( wxPropertyGrid* propGrid,
                                                          wxPGProperty* property,
                                                          const wxPoint& pos,
                                                          const wxSize& sz ) const
{
    // Create and populate buttons-subwindow
    wxPGMultiButton* buttons = new wxPGMultiButton( propGrid, sz );

    // Add two regular buttons
    buttons->Add( "..." );
    buttons->Add( " " );

    // Create the 'primary' editor control (textctrl in this case)
    wxPGWindowList wndList = wxPGTextCtrlEditor::CreateControls
                             ( propGrid, property, pos,
                               buttons->GetPrimarySize() );

    // Finally, move buttons-subwindow to correct position and make sure
    // returned wxPGWindowList contains our custom button list.
    buttons->Finalize(propGrid, pos);

    wndList.SetSecondary( buttons );
    return wndList;
}

bool wxSampleMultiButtonEditor::OnEvent( wxPropertyGrid* propGrid,
                                         wxPGProperty* property,
                                         wxWindow* ctrl,
                                         wxEvent& event ) const
{
    if ( event.GetEventType() == wxEVT_BUTTON )
    {
        wxPGMultiButton* buttons = (wxPGMultiButton*) propGrid->GetEditorControlSecondary();

        if ( event.GetId() == buttons->GetButtonId(0) )
        {
            return false;  // Return false since value did not change
        }
        if ( event.GetId() == buttons->GetButtonId(1) )
        {
            return mf->handle_property(property);
        }
    }
    return wxPGTextCtrlEditor::OnEvent(propGrid, property, ctrl, event);
}

wxPGWindowList wxSampleMultiButtonEditor2::CreateControls( wxPropertyGrid* propGrid,
                                                          wxPGProperty* property,
                                                          const wxPoint& pos,
                                                          const wxSize& sz ) const
{
    // Create and populate buttons-subwindow
    wxPGMultiButton* buttons2 = new wxPGMultiButton( propGrid, sz );

    // Add two regular buttons
    buttons2->Add( " " );
    //buttons->Add( "A" );
    // Add a bitmap button
    //buttons->Add( wxArtProvider::GetBitmap(wxART_FOLDER) );

    // Create the 'primary' editor control (textctrl in this case)
    wxPGWindowList wndList = wxPGTextCtrlEditor::CreateControls
                             ( propGrid, property, pos,
                               buttons2->GetPrimarySize() );

    // Finally, move buttons-subwindow to correct position and make sure
    // returned wxPGWindowList contains our custom button list.
    buttons2->Finalize(propGrid, pos);

    wndList.SetSecondary( buttons2 );
    return wndList;
}

bool wxSampleMultiButtonEditor2::OnEvent( wxPropertyGrid* propGrid,
                                         wxPGProperty* property,
                                         wxWindow* ctrl,
                                         wxEvent& event ) const
{
    if ( event.GetEventType() == wxEVT_BUTTON )
    {
        wxPGMultiButton* buttons = (wxPGMultiButton*) propGrid->GetEditorControlSecondary();

        if ( event.GetId() == buttons->GetButtonId(0) )
        {
            return mf->handle_property(property);
        }
    }
    return wxPGTextCtrlEditor::OnEvent(propGrid, property, ctrl, event);
}



//bool myPGTextCtrlAndButtonEditor::OnEvent( wxPropertyGrid* propGrid,
//                          wxPGProperty* property,
//                          wxWindow* ctrl,
//                          wxEvent& event ) const
//{
//
//    if(event.GetEventType()==wxEVT_BUTTON)
//    {
//        int i = reinterpret_cast<int>(property->GetClientData());
//
//        if(i==1)
//        {
//            wxMessageBox("button pressed with client data 1");
//        }
//        else
//        {
//            wxMessageBox("button pressed");
//        }
//
//
//    }
//
////    if(event.GetId()==wxPG_SUBID2)
////    {
////        wxMessageBox("button pressed");
////    }
//
//    return false;
//}


wxPGWindowList wxSampleStyledTextEditor::CreateControls( wxPropertyGrid* propGrid,
                                                          wxPGProperty* property,
                                                          const wxPoint& pos,
                                                          const wxSize& sz ) const
{
    // Create and populate buttons-subwindow
    wxPGMultiButton* buttons = new wxPGMultiButton( propGrid, sz );

    // Add two regular buttons
    buttons->Add( "..." );

    // Create the 'primary' editor control (textctrl in this case)
    wxPGWindowList wndList = wxPGTextCtrlEditor::CreateControls
                             ( propGrid, property, pos,
                               buttons->GetPrimarySize() );

    // Finally, move buttons-subwindow to correct position and make sure
    // returned wxPGWindowList contains our custom button list.
    buttons->Finalize(propGrid, pos);

    wndList.SetSecondary( buttons );
    return wndList;
}





bool wxSampleStyledTextEditor::OnEvent( wxPropertyGrid* propGrid,
                                         wxPGProperty* property,
                                         wxWindow* ctrl,
                                         wxEvent& event ) const
{
    if ( event.GetEventType() == wxEVT_BUTTON )
    {
        wxPGMultiButton* buttons = (wxPGMultiButton*) propGrid->GetEditorControlSecondary();

        if ( event.GetId() == buttons->GetButtonId(0) )
        {
            mf->handle_property(property);

            return false;
        }
    }
    return wxPGTextCtrlEditor::OnEvent(propGrid, property, ctrl, event);
}

