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

propgridtest03Frame::propgridtest03Frame(wxFrame *frame): GUIFrameWEnum(frame)
{
    m_CodeLog->StyleSetForeground(wxSTC_C_COMMENT, wxColor(0,128,0));

    m_CodeLog->Show(false);
    m_mgr.DetachPane(m_CodeLog);
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
}


