#ifndef LEXERS_H_INCLUDED
#define LEXERS_H_INCLUDED

#include <wx/propgrid/property.h>
#include <vector>
#include <wx/stc/stc.h>
#include <map>

struct lexerProperty
{
    int set_no;
    const char* const propery_name;
    int property_type;
    const char* const default_value;
};

class lexerDB
{
    public:
        lexerDB();
        ~lexerDB();

        void setKWVec(int,wxPGProperty*);
        void renameKWs(int);
        wxString getKWName(int,int);

        void setStylesVec(int,wxPGProperty*);
        void renameStyles(int);
        wxString getLexerStyleName(int,int);
        void getLexerProps(int,std::vector<lexerProperty*>*);

    private:
        int getKWSetNo(int);
        int getStateSetNo(int);

        wxPGProperty* kwVec[9];
        std::map<std::pair<int,int>, char const* const> lexerKWSetName;
        wxPGProperty* stylesVec[wxSTC_STYLE_MAX+11];
        std::map<std::pair<int,int>, char const* const> lexerStateName;

        //in addition, this static data will be defined in the cpp file:
        //static const int maxLexer = 107;
        //static const int totalProperties=sizeof(props) / sizeof(lexerProperty);
        //static int lexerStateSet[]={
        //static int  kwSet[]={
        //static int  propSet[]={
        //static lexerItem stateName[] =
        //static lexerProperty props[]={
        //static lexerItem kwSetName[]={
};

#endif // LEXERS_H_INCLUDED
