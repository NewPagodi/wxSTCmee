#include "dialogs.h"
#include <wx/clipbrd.h>
#include <wx/tokenzr.h>
#include <wx/valnum.h>

wxDEFINE_EVENT(CLICKY_EVENT, wxCommandEvent);

clickyPanel::clickyPanel(wxWindow *parent,
                         clickyData* _cd,
                         wxWindowID id,
                         const wxPoint &pos,
                         const wxSize &size,
                         long style,
                         const wxString &name)
:wxPanel(parent,  id, pos, size,  style, name),cd(_cd),red(255),green(255),blue(255),alpha(0)
{
    this->Connect(  wxEVT_PAINT, wxPaintEventHandler( clickyPanel::onPaint ) );
    this->Connect(  wxEVT_ENTER_WINDOW, wxMouseEventHandler( clickyPanel::onMouseEnter ) );
    this->Connect(  wxEVT_LEFT_DOWN, wxMouseEventHandler( clickyPanel::onLeftDown ) );

    setBM(false);
}

void clickyPanel::setBM(bool fill)
{
    wxImage im(12,12);
    im.SetRGB(wxRect(0,0,11,1),0,0,0);
    im.SetRGB(wxRect(0,0,1,11),0,0,0);
    im.SetRGB(wxRect(11,0,1,12),255,255,255);
    im.SetRGB(wxRect(0,11,12,1),255,255,255);
    if(fill)
    {
        im.SetRGB(wxRect(1,1,10,10),red,green,blue);
    }

    im.InitAlpha ();

    for(int i=0;i<12;i++)
    {
        for(int j=0;j<12;j++)
        {
            im.SetAlpha(i, j, (i==0||i==11||j==0||j==11)?wxIMAGE_ALPHA_OPAQUE:alpha);
        }
    }

    SetToolTip(wxString::Format("(%d,%d,%d,%d)",red,green,blue,alpha));
    bm=wxBitmap(im);
}

void clickyPanel::onLeftDown(wxMouseEvent& event)
{
    setInfo();
}

void clickyPanel::onMouseEnter(wxMouseEvent& event)
{
    if(event.LeftIsDown())
    {
        setInfo();
    }
}

void clickyPanel::onPaint( wxPaintEvent& event )
{
    wxPaintDC mydc(this);
    mydc.DrawBitmap(bm,0,0,true);
}

void clickyPanel::setInfo()
{
    red = cd->getRed();
    green = cd->getGreen();
    blue = cd->getBlue();
    alpha = cd->getAlpha();

    setBM(true);
    Refresh();

    wxCommandEvent event2(CLICKY_EVENT,GetId());
    ProcessWindowEvent(event2);
}


RGBADialog::RGBADialog( wxWindow* parent,int rows, int cols ):GUIRGBADialog(parent)
{
    Connect( CLICKY_EVENT, wxCommandEventHandler( RGBADialog::onClickyEvent ) );

    //initialize clickyData with the values from the dialog.
    wxColor c=m_colourPicker1->GetColour();
    cd.setRed(c.Red());
    cd.setGreen(c.Green());
    cd.setBlue(c.Blue());
    cd.setAlpha(m_slider1->GetValue());

    //now:
    //1) add a panel to the scrolled window (to serve as a border for the
    //   set of clickyPanels).
    //2) add rows*cols clickyPanels to that panel
    //3) set the size of the scrolled window to accomodate the clickyPanels

    int vScrWid=wxSystemSettings::GetMetric(wxSYS_VSCROLL_X );
    int hScrHt = wxSystemSettings::GetMetric(wxSYS_HSCROLL_Y );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	wxPanel* m_panel5 = new wxPanel( m_scrolledWindow1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSIMPLE_BORDER );
	bSizer7->Add( m_panel5, 0, wxLEFT, vScrWid );

    wxGridSizer* gSizer1;
	gSizer1 = new wxGridSizer( 0, cols, 0, 0 );

	clickyPanel* cp;

	for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            cp = new clickyPanel( m_panel5, &cd,wxID_ANY, wxDefaultPosition, wxSize( 12,12 ),0 );
            gSizer1->Add( cp, 0, 0, 5 );
            panelSet.push_back(cp);
        }
    }

	m_panel5->SetSizer( gSizer1 );
	m_panel5->Layout();
	gSizer1->Fit( m_panel5 );

	m_scrolledWindow1->SetSizer( bSizer7 );
	wxSize sz=m_panel5->GetSize();
    int w1=sz.GetWidth()+2*vScrWid;
    int h1 = sz.GetHeight()+hScrHt;
	m_scrolledWindow1->SetMaxSize(wxSize(w1,h1));
	m_scrolledWindow1->Layout();
	bSizer7->Fit( m_scrolledWindow1 );

    //finally the scrolled window doesn't have an inherent best size, so we can't
    //just layout the window.  So the goal is to set the dialog large enough to fit
    //everything or to a maximus of 800x600.
    //m_panel3->SetSize(cols,rows);
    m_panel3->SetSize( cols,rows);
    m_panel3->SetMinSize( wxSize(cols,rows) );
    bSizer14->Layout();

    int frameLR=wxSystemSettings::GetMetric(wxSYS_FRAMESIZE_X  );
    int frameTB = wxSystemSettings::GetMetric(wxSYS_FRAMESIZE_Y  );
    int frameCap = wxSystemSettings::GetMetric(wxSYS_CAPTION_Y  );

    int width,w2,h2,height;
    wxSize sz2 = bSizer14->GetSize();

    w1=w1+10; //the scrolled window has a padding of 5 on both the left and right side.
    w2=sz2.GetWidth();
    width=w1>w2?w1:w2;
    width = width+2*frameLR;
    width=width>800?800:width;

    h1=h1+10;//the scrolled window has a padding of 5 on both the top and bottom.
    h2=sz2.GetHeight();
    height=h1+h2+2*frameTB+frameCap;
    height=height>600?600:height;

    SetSize(width,height);
}

RGBADialog::~RGBADialog()
{
    panelSet.clear();
}

void RGBADialog::onColorChanged( wxColourPickerEvent& event )
{
    cd.setRed(event.GetColour().Red());
    cd.setGreen(event.GetColour().Green());
    cd.setBlue(event.GetColour().Blue());
}

void RGBADialog::onSlider( wxScrollEvent& event )
{
    m_staticText4->SetLabel(wxString::Format("%d",event.GetPosition()));
    cd.setAlpha(event.GetPosition());
}

void RGBADialog::onSetTransparent( wxCommandEvent& event )
{
    for(std::vector<clickyPanel*>::iterator it=panelSet.begin();it!=panelSet.end();it++)
    {
        (*it)->setAlpha(0);
        (*it)->setBM(false);
        (*it)->Refresh();
    }

    drawPanels();
}

void RGBADialog::onSetWhite( wxCommandEvent& event )
{
    for(std::vector<clickyPanel*>::iterator it=panelSet.begin();it!=panelSet.end();it++)
    {
        (*it)->setRed(255);
        (*it)->setGreen(255);
        (*it)->setBlue(255);
        (*it)->setAlpha(255);
        (*it)->setBM(true);
        (*it)->Refresh();
    }

    drawPanels();
}

void RGBADialog::getRGBAData(unsigned char** c)
{
    if(*c!=nullptr)
    {
        return;
    }
    else
    {
        *c = reinterpret_cast<unsigned char*>(malloc(4*panelSet.size()));
    }

    int i(0);

    //unsigned char* c1=*c;

    for(std::vector<clickyPanel*>::iterator it=panelSet.begin();it!=panelSet.end();it++)
    {
//        *(*c+3*i) = (*it)->getRed();
//        *(*c+3*i+1) = (*it)->getGreen();
//        *(*c+3*i+2) = (*it)->getBlue();
//        *(*c+3*i+3) = (*it)->getAlpha();

        *(*c+4*i+0) = (*it)->getRed();
        *(*c+4*i+1) = (*it)->getGreen();
        *(*c+4*i+2) = (*it)->getBlue();
        *(*c+4*i+3) = (*it)->getAlpha();

        i++;
    }
}

void RGBADialog::drawPanels()
{
    unsigned char* c = reinterpret_cast<unsigned char *>(malloc(3*panelSet.size()));
    unsigned char* a = reinterpret_cast<unsigned char *>(malloc(panelSet.size()));
    int i(0);

    for(std::vector<clickyPanel*>::iterator it=panelSet.begin();it!=panelSet.end();it++)
    {
        *(c+3*i) = (*it)->getRed();
        *(c+3*i+1) = (*it)->getGreen();
        *(c+3*i+2) = (*it)->getBlue();

        *(a+i) = (*it)->getAlpha();
        i++;
    }

    wxImage im(m_panel3->GetSize().GetWidth(),m_panel3->GetSize().GetHeight(),c,a,false);
    bm = wxBitmap(im);
    m_panel3->Refresh();

//    wxMemoryBuffer c(3*panelSet.size());
//    wxMemoryBuffer a(panelSet.size());
//
//    for(std::vector<clickyPanel*>::iterator it=panelSet.begin();it!=panelSet.end();it++)
//    {
//        c.AppendByte((*it)->getRed());
//        c.AppendByte((*it)->getGreen());
//        c.AppendByte((*it)->getBlue());
//        a.AppendByte((*it)->getAlpha());
//    }
//
//    wxImage im(m_panel3->GetSize().GetWidth(),m_panel3->GetSize().GetHeight(),reinterpret_cast<unsigned char *>(c.GetData()),reinterpret_cast<unsigned char *>(a.GetData()),true);
//    bm = wxBitmap(im);
//    m_panel3->Refresh();
}

void RGBADialog::onClickyEvent( wxCommandEvent& event )
{
    drawPanels();
}

void RGBADialog::onSetBlack( wxCommandEvent& event )
{
    for(std::vector<clickyPanel*>::iterator it=panelSet.begin();it!=panelSet.end();it++)
    {
        (*it)->setRed(0);
        (*it)->setGreen(0);
        (*it)->setBlue(0);
        (*it)->setAlpha(255);
        (*it)->setBM(true);
        (*it)->Refresh();
    }

    drawPanels();
}

void RGBADialog::onPreviewPaint( wxPaintEvent& event )
{
    wxPaintDC mydc(m_panel3);
    mydc.DrawBitmap(bm,0,0,false);
}






class myGridCellStringRenderer:public wxGridCellStringRenderer
{
    //taken from:http://forums.wxwidgets.org/viewtopic.php?f=1&t=26104&p=111679&hilit=wxgrid+selection#p111679

    public:
        myGridCellStringRenderer():wxGridCellStringRenderer(){};
        void Draw(wxGrid& grid, wxGridCellAttr& attr, wxDC& dc, const wxRect& rect, int row, int col, bool WXUNUSED(isSelected))
        {
            wxGridCellStringRenderer::Draw(grid, attr, dc, rect, row, col, false); // always tell it it's deselected
        }
};

class myGridCellTextEditor:public wxGridCellTextEditor
{
    public:
        myGridCellTextEditor(size_t maxChars=0):wxGridCellTextEditor(maxChars){}
        virtual void StartingKey(wxKeyEvent &event);
        virtual void BeginEdit(int row, int col, wxGrid *grid);

    private:
        wxGrid* m_grid1;
};

void myGridCellTextEditor::StartingKey(wxKeyEvent &event)
{
    int kc = event.GetKeyCode();

    if( 48<=kc && kc <=57 )
    {
        wxGridCellTextEditor::StartingKey(event);
    }
    else
    {
        wxBell();
        m_grid1->DisableCellEditControl();
    }
}

void myGridCellTextEditor::BeginEdit (int row, int col, wxGrid *grid)
{
    //*tc << "BeginEdit\n";

    m_grid1=grid;
    wxGridCellTextEditor::BeginEdit(row, col, grid);
}


class MyGridCellAttrProvider : public wxGridCellAttrProvider
{
    public:
        MyGridCellAttrProvider();
        virtual ~MyGridCellAttrProvider();

        virtual wxGridCellAttr *GetAttr(int row, int col, wxGridCellAttr::wxAttrKind  kind) const;

    private:
        wxGridCellAttr *m_attrForOddRows;
};

MyGridCellAttrProvider::MyGridCellAttrProvider()
{
    m_attrForOddRows = new wxGridCellAttr;
    m_attrForOddRows->SetBackgroundColour(*wxLIGHT_GREY);
}

MyGridCellAttrProvider::~MyGridCellAttrProvider()
{
    m_attrForOddRows->DecRef();
}

wxGridCellAttr *MyGridCellAttrProvider::GetAttr(int row, int col,
                           wxGridCellAttr::wxAttrKind  kind /* = wxGridCellAttr::Any */) const
{
    wxGridCellAttr *attr = wxGridCellAttrProvider::GetAttr(row, col, kind);

    if ( row % 2 )
    {
        if ( !attr )
        {
            attr = m_attrForOddRows;
            attr->IncRef();
        }
        else
        {
            if ( !attr->HasBackgroundColour() )
            {
                wxGridCellAttr *attrNew = attr->Clone();
                attr->DecRef();
                attr = attrNew;
                attr->SetBackgroundColour(wxColour(247,247,247));
            }
        }
    }

    return attr;
}


//class MyGridCellAttrProvider : public wxGridCellAttrProvider
//{
//public:
//    MyGridCellAttrProvider();
//    virtual ~MyGridCellAttrProvider();
//
//    virtual wxGridCellAttr *GetAttr(int row, int col,
//                                    wxGridCellAttr::wxAttrKind  kind) const;
//
//private:
//    wxGridCellAttr *m_attrForOddRows01;
//    wxGridCellAttr *m_attrForOddRows23;
//    wxGridCellAttr *m_attrROAC;
//    wxGridCellAttr *m_attrAC;
//
//
//};
//
//// ----------------------------------------------------------------------------
//// MyGridCellAttrProvider
//// ----------------------------------------------------------------------------
//
//MyGridCellAttrProvider::MyGridCellAttrProvider()
//{
//    m_attrForOddRows01 = new wxGridCellAttr;
//    m_attrForOddRows01->SetBackgroundColour(wxColour(247,247,247));
//    m_attrForOddRows01->SetReadOnly(true);
//    m_attrForOddRows01->SetAlignment(wxALIGN_CENTRE,wxALIGN_TOP);
//
//    m_attrForOddRows23 = new wxGridCellAttr;
//    m_attrForOddRows23->SetBackgroundColour(wxColour(247,247,247));
//    m_attrForOddRows23->SetAlignment(wxALIGN_CENTRE,wxALIGN_TOP);
//
//    m_attrROAC = new wxGridCellAttr;
//    m_attrROAC->SetReadOnly(true);
//    m_attrROAC->SetAlignment(wxALIGN_CENTRE,wxALIGN_TOP);
//
//    m_attrAC = new wxGridCellAttr;
//    m_attrAC->SetAlignment(wxALIGN_CENTRE,wxALIGN_TOP);
//}
//
//MyGridCellAttrProvider::~MyGridCellAttrProvider()
//{
//    m_attrForOddRows01->DecRef();
//    m_attrForOddRows23->DecRef();
//    m_attrROAC->DecRef();
//    m_attrAC->DecRef();
//}
//
//wxGridCellAttr *MyGridCellAttrProvider::GetAttr(int row, int col,
//                           wxGridCellAttr::wxAttrKind  kind /* = wxGridCellAttr::Any */) const
//{
//    wxGridCellAttr *attr = wxGridCellAttrProvider::GetAttr(row, col, kind);
//
//    if ( row % 2 )
//    {
//        if ( !attr )
//        {
//            if( col==0 || col==1 )
//            {
//                attr = m_attrForOddRows01;
//            }
//            else
//            {
//                attr = m_attrForOddRows23;
//            }
//            attr->IncRef();
//        }
//        else
//        {
////            if ( !attr->HasBackgroundColour() )
////            {
////                wxGridCellAttr *attrNew = attr->Clone();
////                attr->DecRef();
////                attr = attrNew;
////                attr->SetBackgroundColour(wxColour(247,247,247));
////            }
//
//            attr->SetBackgroundColour(wxColour(247,247,247));
//            attr->SetAlignment(wxALIGN_CENTRE,wxALIGN_TOP);
//            if( col==0 || col==1 )
//            {
//                attr->SetReadOnly(true);
//            }
//        }
//    }
//    else
//    {
//        if ( !attr )
//        {
//            if( col==0 || col==1 )
//            {
//                attr = m_attrROAC;
//            }
//            else
//            {
//                attr = m_attrAC;
//            }
//            attr->IncRef();
//        }
//        else
//        {
//            attr->SetAlignment(wxALIGN_CENTRE,wxALIGN_TOP);
//            if( col==0 || col==1 )
//            {
//                attr->SetReadOnly(true);
//            }
//        }
//    }
//
//    return attr;
//}




MyProjectMyDialog5::MyProjectMyDialog5(wxFrame *frame,int styleBits,int offst, dialogType dT): MyDialog5(frame)
{
//#if wxUSE_STATUSBAR
//    statusBar->SetStatusText(_("Hello Code::Blocks user!"), 0);
//    statusBar->SetStatusText(wxbuildinfo(short_f), 1);
//#endif

    //initialize private data:
    offset = offst;
    stylebits=styleBits;

    stmin = offset;
    stmax = offset+(1<<stylebits)-1;
    indmin = 0;
    indmax = (1<<(8-stylebits))-1;
    spinsInUse=false;
    editCtrl=nullptr;


    val = new wxIntegerValidator<unsigned long>(&m_value, wxNUM_VAL_DEFAULT );
    val->SetRange (0, stmax); //If we set the validator min to stmin, it is a real pain
                              //I'll handle values outside of stmin in the on changing event handler
    m_spinCtrl1->SetRange(stmin, stmax);
    m_spinCtrl1->SetValue(stmin);

    indval = new wxIntegerValidator<unsigned long>(&m_value, wxNUM_VAL_DEFAULT );
    indval->SetRange(indmin, indmax);
    m_spinCtrl2->SetRange(indmin, indmax);
    m_spinCtrl2->SetValue(indmin);

    stylemask=0;
    indmask=0;

    for(int i=0;i<8;i++)
    {
        if(i<stylebits)
        {
            stylemask=stylemask|(1<<i);
        }
        else
        {
            indmask=indmask|(1<<i);
        }

        fullmask=fullmask|(1<<i);
    }

    //initialize the STC.
    m_STC->Connect(wxEVT_STC_UPDATEUI,wxStyledTextEventHandler( MyProjectMyDialog5::onSTCUpdateUI ), NULL, this );
    m_STC->Connect(wxEVT_STC_MODIFIED,wxStyledTextEventHandler( MyProjectMyDialog5::onSTCModified ), NULL, this );
    m_STC->SetModEventMask(wxSTC_MOD_INSERTTEXT|wxSTC_MOD_DELETETEXT);

    m_STC->SetMarginWidth(1,0);
    m_STC->SetMarginLeft(5);
    m_STC->SetMarginRight(5);
    m_STC->SetScrollWidthTracking(true);
    m_STC->SetScrollWidth(1);
    m_STC->StyleClearAll();

    m_STC->SetStyleBits(styleBits);


    //Initialize the grid
    m_grid1->Connect(wxEVT_GRID_CELL_CHANGING,wxGridEventHandler( MyProjectMyDialog5::onGridChanging), NULL, this );
    m_grid1->Connect(wxEVT_GRID_EDITOR_SHOWN,wxGridEventHandler( MyProjectMyDialog5::onGridEditorShown), NULL, this );
    m_grid1->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MyProjectMyDialog5::OnGridKeyDown),NULL,this);
    m_grid1->Connect( wxEVT_GRID_EDITOR_CREATED, wxGridEditorCreatedEventHandler( MyProjectMyDialog5::onGridEditorCreated ), NULL, this );

    m_grid1->Connect(wxEVT_GRID_RANGE_SELECT,wxGridRangeSelectEventHandler( MyProjectMyDialog5::onGridRangeSelect), NULL, this );
    m_grid1->Connect(wxEVT_GRID_CELL_RIGHT_CLICK,wxGridEventHandler( MyProjectMyDialog5::onGridRightClick), NULL, this );
    m_grid1->Connect(wxEVT_GRID_CELL_LEFT_CLICK,wxGridEventHandler( MyProjectMyDialog5::onGridLeftClick), NULL, this );
    m_grid1->Connect(wxEVT_GRID_CELL_CHANGED,wxGridEventHandler( MyProjectMyDialog5::onGridCellChanged), NULL, this );

    mcte   = new myGridCellTextEditor();
    c0Attr = new wxGridCellAttr;
    c1Attr = new wxGridCellAttr;
    ROAttr = new wxGridCellAttr;
    RORend = new myGridCellStringRenderer();
    mgcne  = new wxGridCellNumberEditor(stmin, stmax);
    mgcne2 = new wxGridCellNumberEditor(indmin, indmax);

    c0Attr->SetEditor( mcte.get() );
    c0Attr->SetAlignment( wxALIGN_CENTRE,wxALIGN_TOP);

    c1Attr->SetEditor( mcte.get() );
    c1Attr->SetAlignment( wxALIGN_CENTRE,wxALIGN_TOP);

    if(dT==SCI_GETSTYLEDTEXT)
    {
        c0Attr->SetReadOnly(true);
        c1Attr->SetReadOnly(true);
    }

    ROAttr->SetReadOnly(true);
    ROAttr->SetRenderer(RORend.get());

    mcte->IncRef();
    mcte->IncRef();

    m_grid1->GetTable()->SetAttrProvider(new MyGridCellAttrProvider());

    m_grid1->SetColAttr(0, ROAttr.get() );
    m_grid1->SetColAttr(1, ROAttr.get() );
    m_grid1->SetColAttr(2, c0Attr.get());
    m_grid1->SetColAttr(3, c1Attr.get());

    //What I want is for the grid to be exactly wide enough that a vertical scroll bar
    //can be added without causing a horizontal scroll bar to appear on the bottom.
    //I also want each column to be as narrow as possible.  It turns out that AutoSize()
    //should do exactly that.
    //So it would seem that the process should be 1) call autosize, 2)get the width of
    //each column, 3)add them up, 4)add the width of the scroll bar, and finaly 5)set the
    //grid to be that width.
    //As usual, it's not as easy as it should be:

    //It seems grids can't be resized after creation (or at least calling
    //SetSize won't do the change and I cant think of what else will do the change).
    //So what I've done is is made the grid stretch, but
    //enclosed it in 2 panels that don't stretch (the panels are also simulating a 2 color
    //border - if I didn't need two colors, one panel [or even just a sizer that was not
    //set to stretch] would be enough).  So the containing
    //panels want to shrink down as much as they can and then the grid will fill what little
    //space those panels give it).

    //So what I'll do is  add a horizontal spacer to the grid's sizer.
    //That forces the panels to stretch exactly that much.  Then the
    //grid stretches to fill all remaining space.  So the grid will end up exactly as
    //wide as the sizer that is added.

    //A second (and much smaller) complication is that I have to add 2 extra pixels.
    //I think (but I'm not 100% sure) that the extra 2 pixels are because the grid insists
    //drawing a 2 pixel column separator after the last column even though there is no
    //next column.



    //This almost works, is much simpler that what I do below, and produces a narrower
    //table that looks better.  But it has 2 drawbacks: 1-the header doeesn't go all the
    //way to the right border which looks kinda bad when no scroll bar is shown.  And 2,
    //the behavior when a column header is clicked is not really what I want.

//    m_grid1->SetUseNativeColLabels(true);
//    m_grid1->AutoSize();
//    int c0 = m_grid1->GetColSize(0);
//    int c1 = m_grid1->GetColSize(1);
//    int c2 = m_grid1->GetColSize(2);
//    int c3 = m_grid1->GetColSize(3);
//    bSizer5->Add( c0+c1+c2+c3+17+2, 0, 0, 0, 0 );


    //I want the look and behavior we get when UseNativeColHeader is called, but when it is
    //called, the headers require more space than with the generic headers.
    //You would think AutoSize() would account for that, but it doesn't seem to.
    //After experimentation, adding 18 pixels seems to give enough space for each
    //column header.
    m_grid1->UseNativeColHeader(true);
    m_grid1->AutoSize();

    int c0 = m_grid1->GetColSize(0)+18;
    int c1 = m_grid1->GetColSize(1)+18;
    int c2 = m_grid1->GetColSize(2)+18;
    int c3;
    if(stylebits==8)
    {
        c3=0;
    }
    else
    {
        c3= m_grid1->GetColSize(3)+18;
    }

    m_grid1->SetColSize(0, c0 );
    m_grid1->SetColSize(1, c1);
    m_grid1->SetColSize(2, c2);
    m_grid1->SetColSize(3, c3);

    //Now we know the width of the 4 columns, so I'll add a spacer
    //for the total column width+the scroll bar width+2 pixels:
    int vScrWid=wxSystemSettings::GetMetric(wxSYS_VSCROLL_X );
    bSizer5->Add( c0+c1+c2+c3+vScrWid+2, 0, 0, 0, 0 );


    //configure the visibility of controls based on the dialog type
    if(dT==SCI_GETSTYLEDTEXT)
    {
        bSizer22->Add( 0, m_grid1->GetGridColLabelWindow()->GetSize().GetHeight()-3, 0, 0, 0 );

        m_button2->Show(false);
        m_button3->Show(false);
        m_button14->Show(true);

        m_staticText1->Show(false);
        m_spinCtrl1->Show(false);
        m_staticText2->Show(false);
        m_spinCtrl2->Show(false);
        m_button1->Show(false);
    }

    if(styleBits==8)
    {
        m_staticText2->Show(false);
        m_spinCtrl2->Show(false);
    }



    //Set the focus to the STC (otherise it will be needlessly on the first
    //spin control)
    m_STC->SetFocus();
}

wxMemoryBuffer MyProjectMyDialog5::GetStyledText()
{
    return m_STC->GetStyledText( 0, m_STC->GetTextLength() );
}

wxString MyProjectMyDialog5::GetStyleString()
{
    int len=m_STC->GetTextLength();

    if(len==0)
    {
        return wxEmptyString;
    }

    char* s = new char[len];

    for(int i=0;i<len;i++)
    {
        s[i] = static_cast<char>( m_STC->GetStyleAt(i) );
    }

    wxString str = wxString::From8BitData( s,len);

    delete[] s;

    return str;
}

void MyProjectMyDialog5::SetReadOnly()
{
    m_STC->SetReadOnly(true);
}

void MyProjectMyDialog5::AddStyledText(const wxMemoryBuffer& data)
{
    m_STC->AddStyledText(data);

    for(int i =0;i<m_STC->GetTextLength();i++)
    {
        fillGrid(i);
    }

}

void MyProjectMyDialog5::addStyle(const wxString& s)
{
    for(size_t i=0;i<s.length();i++)
    {
        m_STC->StartStyling(i,fullmask);
        m_STC->SetStyling( 1, s[i].GetValue() );
        fillGrid(i);
    }
}

//void MyProjectMyDialog5::copyStyledText(wxStyledTextCtrl* m)
//{
//    m->AddStyledText( m_STC->GetStyledText( 0, m_STC->GetTextLength() ) );
//}

void MyProjectMyDialog5::addText(const wxString& s)
{
    m_STC->AddText(s);
}

MyProjectMyDialog5::~MyProjectMyDialog5()
{
    delete val;
    delete indval;

    if(m_grid1->IsCellEditControlEnabled() )
    {
        m_grid1->DisableCellEditControl();
    }

    mgcne->DecRef();
    mgcne2->DecRef();
    mcte->DecRef();
    mcte->DecRef();

    styles.clear();
    indicators.clear();
}

//void MyProjectMyDialog5::OnClose(wxCloseEvent &event)
//{
//    Destroy();
//}
//
//void MyProjectMyDialog5::OnQuit(wxCommandEvent &event)
//{
//    Destroy();
//}
//
//void MyProjectMyDialog5::OnAbout(wxCommandEvent &event)
//{
//    wxString msg = wxbuildinfo(long_f);
//    wxMessageBox(msg, _("Welcome to..."));
//}


void MyProjectMyDialog5::onCopy(wxCommandEvent& event)
{
    wxString s;

    if( m_grid1->IsSelection() )
    {
        int topRow = (m_grid1->GetSelectionBlockTopLeft())[0].GetRow();
        int leftCol = (m_grid1->GetSelectionBlockTopLeft())[0].GetCol();
        int bottomRow = (m_grid1->GetSelectionBlockBottomRight())[0].GetRow();
        int rightCol = (m_grid1->GetSelectionBlockBottomRight())[0].GetCol();

        bool isfirst;
        bool isfirstrow(true);

        for(int i=topRow;i<=bottomRow;i++)
        {
            if(isfirstrow)
            {
                isfirstrow=false;
            }
            else
            {
                s << "\n";
            }

            isfirst=true;

            for(int j = leftCol;j<=rightCol;j++)
            {
                if(isfirst)
                {
                    isfirst=false;
                }
                else
                {
                    s << "\t";
                }

                s << m_grid1->GetCellValue (i, j);
            }
        }
    }
    else
    {
        int j=m_grid1->GetGridCursorCol();
        int i=m_grid1->GetGridCursorRow();

        s= m_grid1->GetCellValue(i, j);
    }

    if (wxTheClipboard->Open())
    {
        // This data objects are held by the clipboard,
        // so do not delete them in the app.
        wxTheClipboard->SetData( new wxTextDataObject(s) );
        wxTheClipboard->Close();
    }
}

void MyProjectMyDialog5::onPaste(wxCommandEvent& event)
{
    int i=m_grid1->GetGridCursorRow();
    int topRow = 0;
    int bottomRow = 0;
    size_t norows = m_grid1->GetNumberRows();

    if( m_grid1->IsSelection() )
    {
        topRow = (m_grid1->GetSelectionBlockTopLeft())[0].GetRow();
        bottomRow = (m_grid1->GetSelectionBlockBottomRight())[0].GetRow();
    }


    switch(currentPaste)
    {
        case singeStyle2singleStyle:
            m_grid1->SetCellValue(i, 2, wxString::Format("%d",styles[0]));
            break;
        case singeInd2singleInd:
            m_grid1->SetCellValue(i, 3, wxString::Format("%d",indicators[0]));
            break;
        case singePair2singlePair:
            m_grid1->SetCellValue(i, 2, wxString::Format("%d",styles[0]));
            m_grid1->SetCellValue(i, 3, wxString::Format("%d",indicators[0]));
            break;
        case styleRange2singleCell:
            {
                for(size_t k=0;k<styles.size();k++)
                {
                    if(i+k<norows)
                    {
                        m_grid1->SetCellValue(i+k, 2, wxString::Format("%d",styles[k]));
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
        case indRange2singleCell:
            {
                for(size_t k=0;k<indicators.size();k++)
                {
                    if(i+k<norows)
                    {
                        m_grid1->SetCellValue(i+k, 3, wxString::Format("%d",indicators[k]));
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
        case pairRange2singleCell:
            {
                for(size_t k=0;k<styles.size();k++)
                {
                    if(i+k<norows)
                    {
                        m_grid1->SetCellValue(i+k, 2, wxString::Format("%d",styles[k]));
                        m_grid1->SetCellValue(i+k, 3, wxString::Format("%d",indicators[k]));
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
        case singleStyle2styleRange:
            {
                wxString s = wxString::Format("%d",styles[0]);

                for(int i=topRow;i<=bottomRow;i++)
                {
                    m_grid1->SetCellValue(i, 2, s);
                }
            }
            break;
        case singleInd2indRange:
            {
                wxString t = wxString::Format("%d",indicators[0]);

                for(int i=topRow;i<=bottomRow;i++)
                {
                    m_grid1->SetCellValue(i, 3, t);
                }
            }
            break;
        case singlePair2pairRange:
            {
                wxString s = wxString::Format("%d",styles[0]);
                wxString t = wxString::Format("%d",indicators[0]);

                for(int i=topRow;i<=bottomRow;i++)
                {
                    m_grid1->SetCellValue(i, 2, s);
                    m_grid1->SetCellValue(i, 3, t);
                }
            }
            break;
    }
}

void MyProjectMyDialog5::onUseSpins(wxCommandEvent& event)
{
    wxMenuItem* mi = m_menu3->FindItem(event.GetId());

    if(mi->IsChecked())
    {
        spinsInUse=true;
        c0Attr->SetEditor( mgcne.get() );
        c1Attr->SetEditor( mgcne2.get() );

        //When SetColFormatNumber is called in the other half of this if-else block
        //it will decrease the ref count of the current editor.  So if we don't bump
        //the refcount to 2, when that call is made, the refcount will fall to 0 and
        //the editors will be deleted.
        mgcne->IncRef();
        mgcne2->IncRef();
    }
    else
    {
        spinsInUse=false;
        c0Attr->SetEditor( mcte.get() );
        c1Attr->SetEditor( mcte.get() );
        mcte->IncRef();
        mcte->IncRef();
    }
}

void MyProjectMyDialog5::onGridLeftClick( wxGridEvent& event )
{
    if(spinsInUse)
    {
        if(event.GetCol()==2 || event.GetCol()==3)
        {
            m_grid1->SetGridCursor( event.GetRow(), event.GetCol() );
            m_grid1->EnableCellEditControl( true );
        }
    }

    event.Skip();
}

void MyProjectMyDialog5::onGridRangeSelect(wxGridRangeSelectEvent& event)
{
    int lc = event.GetLeftCol();
    int rc = event.GetRightCol();
    int tr = event.GetTopRow();
    int br = event.GetBottomRow();


//    *m_textCtrl1 << "onGridRangeSelect" << lc << " " << rc;
//    *m_textCtrl1 << " " << event.GetTopRow() << " " << event.GetBottomRow();
//    *m_textCtrl1 << " " << (event.Selecting()?"Selecting":" not Selecting");
//    *m_textCtrl1 << "\n";

    if( event.AltDown() || event.ControlDown() || event.MetaDown() )
    {
      m_grid1->ClearSelection();
      event.Veto();
      return;
    }

    if(!event.Selecting())
    {
        event.Skip();
        return;
    }

    if(lc<2 && rc<2)
    {
      m_grid1->ClearSelection();
      event.Veto();
      return;
    }




    if(lc<2 || rc <2)
    {

        if(lc<2)
        {
            lc=2;
        }

        if(rc<2)
        {
            rc=2;
        }

        //m_grid1->ClearSelection();
        m_grid1->SelectBlock (tr, lc, br, rc, false);
        event.Veto();
        return;
    }
    else
    {
        event.Skip();
    }
}

void MyProjectMyDialog5::onGridRightClick(wxGridEvent& event)
{

    styles.clear();
    indicators.clear();

    if(event.GetCol()!=2 && event.GetCol()!=3)
    {
        event.Skip();
        return;
    }

    m_grid1->GoToCell(event.GetRow(), event.GetCol() );

    //*m_textCtrl1 << "onGridRightClick.\n";


    //We need to analyze the state of the selection and the
    //state of the clipboard to see if we want to allow pasting in the
    //menu that will popup.
    //There's a surprisingly large number of things to track, but fortunately
    //none of the cases are especially complicated.

    bool enablePaste(false);

    bool selectionIsSingleCol(false),
        selecionIsDoubleCol(false),
        selectionIsSingleRow(false),
        selectionIsMultiRow(false),
        styleColSelected(false),
        indColSelected(false);

    bool isSingleStyle(false),isSingleInd(false),isSinglePair(false),
         isStyleBunch(false),isIndBunch(false),isPairBunch(false);

    if( m_grid1->IsSelection() )
    {
        int topRow = (m_grid1->GetSelectionBlockTopLeft())[0].GetRow();
        int leftCol = (m_grid1->GetSelectionBlockTopLeft())[0].GetCol();
        int bottomRow = (m_grid1->GetSelectionBlockBottomRight())[0].GetRow();
        int rightCol = (m_grid1->GetSelectionBlockBottomRight())[0].GetCol();

        if(topRow==bottomRow)
        {
            selectionIsSingleRow = true;
        }
        else
        {
            selectionIsMultiRow = true;
        }

        if(leftCol==rightCol)
        {
            selectionIsSingleCol = true;

            if(leftCol==2)
            {
                styleColSelected=true;
            }
            else
            {
                indColSelected=true;
            }
        }
        else
        {
            selecionIsDoubleCol = true;
            styleColSelected=true;
            indColSelected=true;
        }

    }
    else
    {
        int j=m_grid1->GetGridCursorCol();
        int i=m_grid1->GetGridCursorRow();

//        if(j!=2 && j!=3)
//        {
//            enablecopy=false;
//        }

            selectionIsSingleRow = true;
            selectionIsSingleCol = true;

            if(j==2)
            {
                styleColSelected=true;
            }
            else
            {
                indColSelected=true;
            }
    }

    if (wxTheClipboard->Open())
    {
        if (wxTheClipboard->IsSupported( wxDF_TEXT ))
        {
            wxTextDataObject data;
            wxTheClipboard->GetData( data );
            wxString s = data.GetText();

            if(s.Find("\n")==wxNOT_FOUND)
            {
                if(s.Find("\t")==wxNOT_FOUND)
                {
                    long tlong;

                    if(s.ToLong(&tlong))
                    {

                        if(stmin<=tlong &&tlong <=stmax)
                        {
                            isSingleStyle = true;
                            styles.push_back(tlong);
                        }

                        if(indmin<=tlong &&tlong <=indmax)
                        {
                            isSingleInd = true;
                            indicators.push_back(tlong);
                        }

                    }
                }
                else
                {
                    wxString temp=s;
                    wxString temp2 = "\t";

                    size_t l = temp.length();
                    size_t l2 = temp2.length();
                    int f = temp.Find (temp2);

                    long tlong1,tlong2;

                    if( temp.Left(f).ToLong(&tlong1) && temp.Right(l-f-l2).ToLong(&tlong2))
                    {
                        if(stmin<=tlong1 &&tlong1 <=stmax && indmin<=tlong2 &&tlong2 <=indmax )
                        {
                            isSinglePair = true;
                            styles.push_back(tlong1);
                            indicators.push_back(tlong2);
                        }
                    }
                }
            }
            else
            {
                if(s.Find("\t")==wxNOT_FOUND)
                {
                    isStyleBunch=true;
                    isIndBunch=true;

                    wxStringTokenizer tokenizer(s, "\n");
                    while ( tokenizer.HasMoreTokens() )
                    {
                        wxString token = tokenizer.GetNextToken();
                        long tlong;

                        if(token.ToLong(&tlong))
                        {
                            if( stmin<=tlong &&tlong <=stmax )
                            {
                                styles.push_back(tlong);
                            }
                            else
                            {
                                isStyleBunch=false;
                            }

                            if( indmin<=tlong &&tlong <=indmax )
                            {
                                indicators.push_back(tlong);
                            }
                            else
                            {
                                isIndBunch=false;
                            }
                        }
                        else
                        {
                            isStyleBunch=false;
                            isIndBunch=false;
                        }

                        if(!isStyleBunch && !isIndBunch)
                        {
                            break;
                        }
                    }
                }
                else
                {
                    isPairBunch=true;

                    wxStringTokenizer tokenizer(s, "\n");
                    while ( tokenizer.HasMoreTokens() )
                    {
                        wxString token = tokenizer.GetNextToken();

                        wxString temp=token;
                        wxString temp2 = "\t";

                        size_t l = temp.length();
                        size_t l2 = temp2.length();
                        int f = temp.Find (temp2);

                        long tlong1,tlong2;

                        if( temp.Left(f).ToLong(&tlong1) && temp.Right(l-f-l2).ToLong(&tlong2))
                        {
                            if(stmin<=tlong1 &&tlong1 <=stmax && indmin<=tlong2 &&tlong2 <=indmax )
                            {
                                styles.push_back(tlong1);
                                indicators.push_back(tlong2);
                            }
                            else
                            {
                                isPairBunch=false;
                                break;
                            }
                        }
                        else
                        {
                            isPairBunch=false;
                            break;
                        }
                    }
                }
            }
        }
        wxTheClipboard->Close();
    }



    //*m_textCtrl1 << "selectionIsSingleCol:" << (selectionIsSingleCol?"true":"false") << "\n";
    //*m_textCtrl1 << "selecionIsDoubleCol:" << (selecionIsDoubleCol?"true":"false") << "\n";
    //*m_textCtrl1 << "selectionIsSingleRow:" << (selectionIsSingleRow?"true":"false") << "\n";
    //*m_textCtrl1 << "selectionIsMultiRow:" << (selectionIsMultiRow?"true":"false") << "\n";
    //*m_textCtrl1 << "styleColSelected:" << (styleColSelected?"true":"false") << "\n";
    //*m_textCtrl1 << "indColSelected:" << (indColSelected?"true":"false") << "\n";
    //*m_textCtrl1 << "isSingleStyle:" << (isSingleStyle?"true":"false") << "\n";
    //*m_textCtrl1 << "isSingleInd:" << (isSingleInd?"true":"false") << "\n";
    //*m_textCtrl1 << "isSinglePair:" << (isSinglePair?"true":"false") << "\n";
    //*m_textCtrl1 << "isStyleBunch:" << (isStyleBunch?"true":"false") << "\n";
    //*m_textCtrl1 << "isIndBunch:" << (isIndBunch?"true":"false") << "\n";
    //*m_textCtrl1 << "isPairBunch:" << (isPairBunch?"true":"false") << "\n";

    //pasting a single style/ind/pair into a single style/ind/pair
    if(isSingleStyle && selectionIsSingleCol && selectionIsSingleRow && styleColSelected)
    {
        currentPaste=singeStyle2singleStyle;
        enablePaste=true;
        //*m_textCtrl1 << "singeStyle2singleStyle\n" ;
    }
    else if(isSingleInd && selectionIsSingleCol && selectionIsSingleRow && indColSelected )
    {
        currentPaste=singeInd2singleInd;
        enablePaste=true;
        //*m_textCtrl1 << "singeInd2singleInd\n" ;
    }
    else if(isSinglePair && selecionIsDoubleCol && selectionIsSingleRow && styleColSelected )
    {
        currentPaste=singePair2singlePair;
        enablePaste=true;
        //*m_textCtrl1 << "singePair2singlePair\n" ;
    }
    else if(isSinglePair && selectionIsSingleCol && selectionIsSingleRow && styleColSelected )
    {
        currentPaste=singePair2singlePair;
        enablePaste=true;
        //*m_textCtrl1 << "singePair2singlePair\n" ;
    }
    //pasting a range of styles/ind/pairs starting at a single cell
    else if(selectionIsSingleCol && selectionIsSingleRow && styleColSelected && isStyleBunch)
    {
        currentPaste=styleRange2singleCell;
        enablePaste=true;
        //*m_textCtrl1 << "styleRange2singleCell\n" ;
    }
    else if(selectionIsSingleCol && selectionIsSingleRow && indColSelected && isIndBunch)
    {
        currentPaste=indRange2singleCell;
        enablePaste=true;
        //*m_textCtrl1 << "indRange2singleCell\n" ;
    }
    else if(selectionIsSingleCol && selectionIsSingleRow && styleColSelected && isPairBunch)
    {
        currentPaste=pairRange2singleCell;
        enablePaste=true;
        //*m_textCtrl1 << "pairRange2singleCell\n" ;
    }
    else if(selecionIsDoubleCol && selectionIsSingleRow && isPairBunch)
    {
        currentPaste=pairRange2singleCell;
        enablePaste=true;
        //*m_textCtrl1 << "pairRange2singleCell\n" ;
    }
    //pasting a single style,ind,pair into a range
    else if(selectionIsSingleCol && selectionIsMultiRow && styleColSelected && isSingleStyle)
    {
        currentPaste=singleStyle2styleRange;
        enablePaste=true;
        //*m_textCtrl1 << "singleStyle2styleRange\n" ;
    }
    else if(selectionIsSingleCol && selectionIsMultiRow && indColSelected && isSingleInd)
    {
        currentPaste=singleInd2indRange;
        enablePaste=true;
        //*m_textCtrl1 << "singleInd2indRange\n" ;
    }
    else if(selecionIsDoubleCol && selectionIsMultiRow  && isSinglePair)
    {
        currentPaste=singlePair2pairRange;
        enablePaste=true;
        //*m_textCtrl1 << "singlePair2pairRange\n" ;
    }

//    bool enablecopy(true),enablePaste(false);
//
//    bool selectionIsSingleCol(false),
//        selecionIsDoubleCol(false),
//        selectionIsSingleRow(false),
//        selectionIsMultiRow(false),
//        styleColSelected(false),
//        indColSelected(false);
//
//    bool isSingleStyle(false),isSingleInd(false),isSinglePair(false),
//         isStyleBunch(false),isIndBunch(false),isPairBunch(false);



    //m_menuItem3->Enable(enablecopy);
    m_menuItem5->Enable(enablePaste);

    m_grid1->PopupMenu( m_menu3, event.GetPosition() );
}


void MyProjectMyDialog5::onGridCellChanged( wxGridEvent& event )
{
    //m_textCtrl2->SetValue(wxString::Format("%d %d changed",event.GetRow(),event.GetCol()) );
    long st,ind;
    int r=event.GetRow();

    m_grid1->GetCellValue( r,2).ToLong(&st);
    m_grid1->GetCellValue( r,3).ToLong(&ind);

    bool ro = m_STC->GetReadOnly();

    if(ro)
    {
        m_STC->SetReadOnly(false);
    }

    m_STC->StartStyling(r,fullmask);
    m_STC->SetStyling( 1, getRawStyle( st,ind) );


    if(ro)
    {
        m_STC->SetReadOnly(true);
    }




}

bool MyProjectMyDialog5::isEditorValueAcceptable()
{
    //there is no need to check the value if the editor is not curently
    //being shown, spins are in use, we've somehow failed to find the
    //editors text control, or we're not in  column2

    if(!m_grid1->IsCellEditControlEnabled())
    {
        return true;
    }

    if(spinsInUse)
    {
        return true;
    }

    if(editCtrl==nullptr)
    {
        return true;
    }

    long tlong;

    if(!editCtrl->GetValue().ToLong(&tlong))
    {
        return false;
    }

    //We only need to check the min for column2
    if(m_grid1->GetGridCursorCol()!=2)
    {
        return true;
    }

    if(tlong < stmin)
    {
        return false;
    }
    else
    {
        return true;
    }
}


void MyProjectMyDialog5::OnGridKeyDown(wxKeyEvent& event)
{
//    *m_textCtrl1 << "OnGridKeyDown\n";

//    if(!m_grid1->IsCellEditControlEnabled())
//    {
//        int c = event.GetKeyCode();
//
//        *m_textCtrl1 << c << " editor not shown\n";
//
//        if(c<32)
//        {
//            event.Skip();
//        }
//        else if(c<48)
//        {
//            return;
//        }
//        else if(c<57)
//        {
//            event.Skip();
//        }
//        else if(c <127)
//        {
//            return;
//        }
//        else
//        {
//            event.Skip();
//        }
//    }


    if (event.GetKeyCode() == WXK_RETURN || event.GetKeyCode() == WXK_NUMPAD_ENTER || event.GetKeyCode() ==WXK_TAB  )
	{
        if(!isEditorValueAcceptable())
        {
            wxBell();
            return;
            //We don't skip this to prevent the editor being closed.
        }
	}


    event.Skip();
}

void MyProjectMyDialog5::onGridEditorShown( wxGridEvent& event )
{
    //For reasons known only to God, the first time an editor is needed, this
    //gets called before ongrideditor created.  So we need  to make sure the editor
    //is not null

    if(editCtrl && !spinsInUse)
    {
        if(event.GetCol()==2)
        {
            editCtrl->SetValidator(*val);
        }
        else if(event.GetCol()==3)
        {
            editCtrl->SetValidator(*indval);
        }
    }


}

void MyProjectMyDialog5::onGridEditorCreated( wxGridEditorCreatedEvent& event )
{
    if( wxTextCtrl* tc = dynamic_cast<wxTextCtrl*>(event.GetControl()) )
    {
        editCtrl=tc;
        editCtrl->Connect(wxEVT_CHAR,wxKeyEventHandler( MyProjectMyDialog5::onEditorKey), NULL, this );

        if(event.GetCol()==2)
        {
            editCtrl->SetValidator(*val);
        }
        else
        {
            editCtrl->SetValidator(*indval);
        }
    }
}

void MyProjectMyDialog5::onGridChanging( wxGridEvent& event )
{
    //If there is an invalid entry in the editor
    //and another cell is clicked with the mouse, this is an oportunity to reject the
    //invalid entry.  There are other ways of accomplishing that, but I'll stick with this

    //This is also a last chance to reject any other invalid entrys although I would hope
    //they were caught earlier by the validator or one of the key handler methods.

    if(!isEditorValueAcceptable())
    {
        wxBell();
        event.Veto();
        return;
    }
    else
    {
        event.Skip();
    }


//    //m_textCtrl4->SetValue( event.GetString() + "changing"  );
//
//    if(event.GetCol()==2)
//    {
//        long tlong;
//        event.GetString().ToLong(&tlong);
//
//        if(tlong<offset)
//        {
//            wxBell();
//            event.Veto();
//            return;
//        }
//        else
//        {
//            event.Skip();
//        }
//    }
//
//    event.Skip();
}

void MyProjectMyDialog5::onEditorKey( wxKeyEvent& event)
{
    int c = event.GetKeyCode();

    if(c==WXK_UP || c==WXK_DOWN  )
    {
        if(!isEditorValueAcceptable())
        {
            wxBell();
            return;
        }

        m_grid1->DisableCellEditControl();
        //int i= m_grid1->GetGridCursorRow();
        //int j= m_grid1->GetGridCursorCol();

        if(c==WXK_UP)
        {
            m_grid1->MoveCursorUp(false);

//            if(i!=0)
//            {
//                m_grid1->GoToCell (i-1,j);
//            }
//            else
//            {
//                wxBell();
//            }
        }
        else
        {
            m_grid1->MoveCursorDown(false);

//            if( i!=m_grid1->GetNumberRows()-1 )
//            {
//                m_grid1->GoToCell (i+1,j);
//            }
//            else
//            {
//                wxBell();
//            }
        }
    }
    else
    {
        event.Skip();
    }

//    int c = event.GetKeyCode();
//
//    if(c==WXK_UP || c==WXK_DOWN  )
//    {
//
//
//        int j= m_grid1->GetGridCursorCol();
//        int i= m_grid1->GetGridCursorRow();
//
//        if(j==2)
//        {
//            //try to get the string value in the editor control and compare
//            //the offset to make sure its valid:
//
//            if(wxTextCtrl* tc=dynamic_cast<wxTextCtrl*>(editCtrl) )
//            {
//                long tlong;
//                tc->GetValue().ToLong(&tlong);
//
//                if(tlong<offset)
//                {
//                    wxBell();
//                    return;
//                }
//            }
//            else
//            {
//                //if the editor wasn't a textctrl, I don't know what can be done.
//            }
//        }
//
//
//        m_grid1->HideCellEditControl();
//
//        if(c==WXK_UP)
//        {
//            if(i!=0)
//            {
//                m_grid1->GoToCell (i-1,j);
//            }
//            else
//            {
//                wxBell();
//            }
//        }
//        else
//        {
//            if( i!=m_grid1->GetNumberRows()-1 )
//            {
//                m_grid1->GoToCell (i+1,j);
//            }
//            else
//            {
//                wxBell();
//            }
//        }
//    }
//    else
//    {
//        event.Skip();
//    }
}

//void MyProjectMyDialog5::OnGridKeyDown(wxKeyEvent& event)
//{
////    *m_textCtrl1 << "OnGridKeyDown\n";
//
////    if(!m_grid1->IsCellEditControlEnabled())
////    {
////        int c = event.GetKeyCode();
////
////        *m_textCtrl1 << c << " editor not shown\n";
////
////        if(c<32)
////        {
////            event.Skip();
////        }
////        else if(c<48)
////        {
////            return;
////        }
////        else if(c<57)
////        {
////            event.Skip();
////        }
////        else if(c <127)
////        {
////            return;
////        }
////        else
////        {
////            event.Skip();
////        }
////    }
//
//
//    if (event.GetKeyCode() == WXK_RETURN || event.GetKeyCode() == WXK_NUMPAD_ENTER || event.GetKeyCode() ==WXK_TAB  )
//	{
//        if(!isEditorValueAcceptable())
//        {
//            wxBell();
//            return;
//            //We don't skip this to prevent the editor being closed.
//        }
//	}
//
//
//    event.Skip();
//}
//


void MyProjectMyDialog5::onB( wxCommandEvent& event )
{
    int sst = m_STC->GetSelectionStart();
    int sen = m_STC->GetSelectionEnd();

    bool ro = m_STC->GetReadOnly();

    if(ro)
    {
        m_STC->SetReadOnly(false);
    }

    m_STC->StartStyling(sst,fullmask);
    m_STC->SetStyling( sen-sst, getRawStyle( m_spinCtrl1->GetValue(),m_spinCtrl2->GetValue()) );

    if(ro)
    {
        m_STC->SetReadOnly(true);
    }

    for(int i=sst;i<sen;i++)
    {
        fillGrid(i);
    }

    m_STC->SetFocus();


}

void MyProjectMyDialog5::onSTCUpdateUI(wxStyledTextEvent& event)
{
    int i= m_STC->GetCurrentPos();
    int j= m_STC->GetTextLength();

    m_textCtrl1->SetValue(wxString::Format("Position %d/%d",i,j));

    int ln = 1+m_STC->LineFromPosition(i);
    int col = 1+m_STC->GetColumn(i);

    m_textCtrl3->SetValue(wxString::Format("Ln:%d Col:%d",ln,col));

    int sst = m_STC->GetSelectionStart();
    int sen = m_STC->GetSelectionEnd();

    if(sst==sen)
    {
        m_button1->Enable(false);
        m_textCtrl2->SetValue("No selection");
    }
    else
    {
        m_button1->Enable(true);
        m_textCtrl2->SetValue( wxString::Format("Selection (%d,%d)",sst,sen) );
    }


}

int MyProjectMyDialog5::getRawStyle(int style,int indicator)
{
    return (style-offset) | (indicator<<stylebits);
}

void MyProjectMyDialog5::getStyleAndIndicator(int rawStyle, int* style, int* indicator)
{
    *style=(rawStyle&stylemask)+offset;
    *indicator = (rawStyle&indmask) >>stylebits;
}

void MyProjectMyDialog5::onSTCModified(wxStyledTextEvent& event)
{
    int pos,len;

    pos = event.GetPosition();
    len = event.GetLength();

    int i=m_grid1->GetNumberRows();
    int j=m_STC->GetTextLength();

    if(i>j)
    {
        m_grid1->DeleteRows (pos, i-j);
    }
    else if(i<j)
    {
        m_grid1->AppendRows(j-i);
    }
    //else nothing

    if( (event.GetModificationType())&wxSTC_MOD_INSERTTEXT )
    {
        m_STC->StartStyling(pos,fullmask);
        m_STC->SetStyling( len, getRawStyle( m_spinCtrl1->GetValue(),m_spinCtrl2->GetValue()) );
    }

    for(int i=pos;i<j;i++)
    {
        fillGrid(i);
    }
}

void MyProjectMyDialog5::fillGrid(int i)
{
    int style,ind,rs;

    char c = m_STC->GetCharAt(i);
    rs = m_STC->GetStyleAt(i);
    getStyleAndIndicator(rs,&style,&ind);

    if(isprint(c))
    {
        m_grid1->SetCellValue(wxString(&c,1), i, 1);
    }
    else
    {
        wxString s;

        if(c=='\n')
        {
            s="\\n";
        }
        else if(c=='\r')
        {
            s="\\r";
        }
        else if(c=='\t')
        {
            s="\\t";
        }
        else
        {
            s = wxString::Format("0x%02x",(int)c);
        }

        m_grid1->SetCellValue(s, i, 1);
    }

    m_grid1->SetCellValue(wxString::Format("%d",i), i, 0);
    m_grid1->SetCellValue(wxString::Format("%d",style), i, 2);
    m_grid1->SetCellValue(wxString::Format("%d",ind), i, 3);
}




