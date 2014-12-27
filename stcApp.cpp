/***************************************************************
 * Name:      propgridtest03App.cpp
 * Purpose:   Code for Application Class
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

#include "stcApp.h"
#include "stcMain.h"
//#include <wx/fs_mem.h>
//
//#include "ScintillaDoc.c"
//#include "SciTEIco.c"
//#include "styledmargin.c"
//#include "annotations.c"



IMPLEMENT_APP(propgridtest03App);

bool propgridtest03App::OnInit()
{


    //wxImage::AddHandler(new wxPNGHandler);
//    wxMemoryFSHandler::AddFile("logo.png",
//        wxBitmap(wxlogo_xpm), wxBITMAP_TYPE_PNG);

    wxInitAllImageHandlers();

    propgridtest03Frame* frame = new propgridtest03Frame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();

    return true;
}
