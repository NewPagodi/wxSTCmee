#ifndef DIALOGS_H_INCLUDED
#define DIALOGS_H_INCLUDED

#include "GUIFrame.h"
#include <vector>


class myGridCellTextEditor;
class myGridCellStringRenderer;

template <class T>
class wxIntegerValidator;

class clickyData
{
    public:
        clickyData():red(0),green(0),blue(0),alpha(wxIMAGE_ALPHA_OPAQUE){}
        void setRed(unsigned char r){red=r;}
        void setGreen(unsigned char g){green=g;}
        void setBlue(unsigned char b){blue=b;}
        void setAlpha(unsigned char a){alpha=a;}
        unsigned char getRed(){return red;}
        unsigned char getGreen(){return green;}
        unsigned char getBlue(){return blue;}
        unsigned char getAlpha(){return alpha;}

    private:
        unsigned char red;
        unsigned char green;
        unsigned char blue;
        unsigned char alpha;
};

wxDECLARE_EVENT(CLICKY_EVENT, wxCommandEvent);

class clickyPanel : public wxPanel
{

	public:
		clickyPanel(wxWindow *parent, clickyData* _cd,wxWindowID id=wxID_ANY, const wxPoint &pos=wxDefaultPosition, const wxSize &size=wxDefaultSize, long style=0, const wxString &name=wxPanelNameStr);
        unsigned char getRed(){return red;}
        unsigned char getGreen(){return green;}
        unsigned char getBlue(){return blue;}
        unsigned char getAlpha(){return alpha;}
        void setRed(unsigned char r){red=r;}
        void setGreen(unsigned char g){green=g;}
        void setBlue(unsigned char b){blue=b;}
        void setAlpha(unsigned char a){alpha=a;}
        void setBM(bool fill);

    private:
		void onPaint( wxPaintEvent& event );
		//void onLeftUp(wxMouseEvent& event);
		void onLeftDown(wxMouseEvent& event);
		void onMouseEnter(wxMouseEvent& event);



		void setInfo();

		unsigned char red;
		unsigned char green;
		unsigned char blue;
		unsigned char alpha;
		//bool draw;

		wxBitmap bm;
		clickyData* cd;
};



class RGBADialog : public GUIRGBADialog
{
	public:
		RGBADialog( wxWindow* parent ,int rows, int cols);
		~RGBADialog();

		void getRGBAData(unsigned char**);
	private:
		void onColorChanged( wxColourPickerEvent& event );
		void onSlider( wxScrollEvent& event );
		void onSetTransparent( wxCommandEvent& event );
		void onSetWhite( wxCommandEvent& event );
		void onSetBlack( wxCommandEvent& event );
		void onPreviewPaint( wxPaintEvent& event );
		void onClickyEvent( wxCommandEvent& event );

		void drawPanels();

		std::vector<clickyPanel*> panelSet;
		clickyData cd;
		wxBitmap bm;
};


class MyProjectMyDialog5 : public MyDialog5
{
    enum pasteType
    {
        singeStyle2singleStyle,
        singeInd2singleInd,
        singePair2singlePair,
        styleRange2singleCell,
        indRange2singleCell,
        pairRange2singleCell,
        singleStyle2styleRange,
        singleInd2indRange,
        singlePair2pairRange
    };

    public:
        enum dialogType
	    {
	        SCI_ADDSTYLEDTEXT,
	        SCI_GETSTYLEDTEXT,
	        SCI_SETSTYLINGEX
	    };


        MyProjectMyDialog5(wxFrame *frame,int styleBits,int offst,dialogType);
        ~MyProjectMyDialog5();

        //void copyStyledText(wxStyledTextCtrl*);
        wxMemoryBuffer GetStyledText();
        wxString GetStyleString();

        void AddStyledText(const wxMemoryBuffer& data);
        void addText(const wxString&);
        void addStyle(const wxString&);


        void SetReadOnly();

    private:
//        virtual void OnClose(wxCloseEvent& event);
//        virtual void OnQuit(wxCommandEvent& event);
//        virtual void OnAbout(wxCommandEvent& event);

        void onCopy(wxCommandEvent& event);
        void onPaste(wxCommandEvent& event);
        void onUseSpins(wxCommandEvent& event);

        void onGridLeftClick( wxGridEvent& event );
        void onGridRangeSelect(wxGridRangeSelectEvent& event);
        void onGridRightClick(wxGridEvent& event);
        void onGridCellChanged( wxGridEvent& event );

/*
things that needs tracked for validation purposes:
1) grid onkey            - to catch enter,return and tab
2) editors onkey         - to catch up/down arrow
3) ongrid editor created - to record the text control and attach the validator the first time
4) on grid editor shown  - to attach the correct validator every time after the first time.
5) on grid cell changing - to catch when editing is ended by clicking another cell.
*/
        void OnGridKeyDown(wxKeyEvent& event);
        void onEditorKey( wxKeyEvent& event);
        void onGridEditorCreated( wxGridEditorCreatedEvent& event );
        void onGridEditorShown( wxGridEvent& event );
        void onGridChanging( wxGridEvent& event );

        bool isEditorValueAcceptable();


        void onB( wxCommandEvent& event ) ;

        void onSTCUpdateUI(wxStyledTextEvent& event);
        void onSTCModified(wxStyledTextEvent& event);

        int getRawStyle(int,int);
        void getStyleAndIndicator(int,int*,int*);

        void fillGrid(int);

        wxIntegerValidator<unsigned long>* val;
        wxIntegerValidator<unsigned long>* indval;
        unsigned long m_value;

        wxObjectDataPtr<myGridCellStringRenderer> RORend;
        wxObjectDataPtr<wxGridCellNumberEditor> mgcne;
        wxObjectDataPtr<wxGridCellNumberEditor> mgcne2;
        wxObjectDataPtr<myGridCellTextEditor> mcte;

        wxObjectDataPtr<wxGridCellAttr> c0Attr;
        wxObjectDataPtr<wxGridCellAttr> c1Attr;
        wxObjectDataPtr<wxGridCellAttr> ROAttr;

        wxTextCtrl* editCtrl;
        bool spinsInUse;

        int stmin;
        int stmax;
        int indmin;
        int indmax;

        int stylebits;
        int offset;
        int stylemask;
        int indmask;
        int fullmask;

        std::vector<long> styles;
        std::vector<long> indicators;
        pasteType currentPaste;
};





#endif // DIALOGS_H_INCLUDED
