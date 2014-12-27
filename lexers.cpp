#include "stcMain.h"
#include "lexers.h"
/*preamble:

    the obvious thing to do here is to add data to the maps like this:

        lexerStateName.push_back(makepair( makepair(1,0),"wxSTC_4GL_DEFAULT");
        ...

    (repeated for the 1400+ items)

    but for some reason doing that makes compilation take a long time (6 minutes plus)

    based on these 2 articles
    http://stackoverflow.com/questions/22796198/best-way-to-initialize-large-amount-of-data-into-a-c-container
    http://stackoverflow.com/questions/1639154/how-to-declare-a-static-const-char-in-your-header-file
    (which were solutions for a slightly different problem)

    I'm going to define some static data arrays and then iterate over those arrays to build
    the needed maps. like so:

    static lexerItem stateName[] = {
        {1,0,"wxSTC_4GL_DEFAULT"},
        {1,1,"wxSTC_4GL_NUMBER"},
        {1,2,"wxSTC_4GL_WORD"},
        {1,3,"wxSTC_4GL_STRING"},
        ....

    This brings compilation down to about 30 seconds (which is better, but still longer
    that it probably should be)

    I could reduce compilation time to essentially nothing by defining 3 separate arrays:

    static int stateName1[]={
        1,
        1,
        ...

    static int stateName2[]={
        0,
        1,
        ...

    static char const* const stateName3[]={
        "wxSTC_4GL_DEFAULT",
        "wxSTC_4GL_NUMBER",
        ...

    and then building the map

    for(..)
    {
        lexerStateName.push_back(makepair( makepair(stateName1[i],stateName2[i]),stateName3[i]);
    }

    but then the connections of the data are less obvious.  I think I'll settle for
    what I have here.
*/



struct lexerItem
{
    int first;
    int second;
    const char* const c;
};

static const int maxLexer = 107;

static int  kwSet[]={
    -1,	// = kwSet[  0] = kwSet[wxSTC_LEX_CONTAINER]
    -1,	// = kwSet[  1] = kwSet[wxSTC_LEX_NULL]
    65,	// = kwSet[  2] = kwSet[wxSTC_LEX_PYTHON]
    20,	// = kwSet[  3] = kwSet[wxSTC_LEX_CPP]
    38,	// = kwSet[  4] = kwSet[wxSTC_LEX_HTML]
    38,	// = kwSet[  5] = kwSet[wxSTC_LEX_XML]
    57,	// = kwSet[  6] = kwSet[wxSTC_LEX_PERL]
    76,	// = kwSet[  7] = kwSet[wxSTC_LEX_SQL]
    83,	// = kwSet[  8] = kwSet[wxSTC_LEX_VB]
    -1,	// = kwSet[  9] = kwSet[wxSTC_LEX_PROPERTIES]
    -1,	// = kwSet[ 10] = kwSet[wxSTC_LEX_ERRORLIST]
    -1,	// = kwSet[ 11] = kwSet[wxSTC_LEX_MAKEFILE]
    13,	// = kwSet[ 12] = kwSet[wxSTC_LEX_BATCH]
    -1,	// = kwSet[ 13] = kwSet[wxSTC_LEX_XCODE]
    -1,	// = kwSet[ 14] = kwSet[wxSTC_LEX_LATEX]
    43,	// = kwSet[ 15] = kwSet[wxSTC_LEX_LUA]
    -1,	// = kwSet[ 16] = kwSet[wxSTC_LEX_DIFF]
    19,	// = kwSet[ 17] = kwSet[wxSTC_LEX_CONF]
    55,	// = kwSet[ 18] = kwSet[wxSTC_LEX_PASCAL]
    9,	// = kwSet[ 19] = kwSet[wxSTC_LEX_AVE]
    3,	// = kwSet[ 20] = kwSet[wxSTC_LEX_ADA]
    41,	// = kwSet[ 21] = kwSet[wxSTC_LEX_LISP]
    68,	// = kwSet[ 22] = kwSet[wxSTC_LEX_RUBY]
    27,	// = kwSet[ 23] = kwSet[wxSTC_LEX_EIFFEL]
    27,	// = kwSet[ 24] = kwSet[wxSTC_LEX_EIFFELKW]
    80,	// = kwSet[ 25] = kwSet[wxSTC_LEX_TCL]
    21,	// = kwSet[ 26] = kwSet[wxSTC_LEX_NNCRONTAB]
    15,	// = kwSet[ 27] = kwSet[wxSTC_LEX_BULLANT]
    83,	// = kwSet[ 28] = kwSet[wxSTC_LEX_VBSCRIPT]
    -1,	// = kwSet[ 29] = kwSet[30]
    -1,	// = kwSet[ 30] = kwSet[31]
    11,	// = kwSet[ 31] = kwSet[wxSTC_LEX_BAAN]
    45,	// = kwSet[ 32] = kwSet[wxSTC_LEX_MATLAB]
    70,	// = kwSet[ 33] = kwSet[wxSTC_LEX_SCRIPTOL]
    5,	// = kwSet[ 34] = kwSet[wxSTC_LEX_ASM]
    20,	// = kwSet[ 35] = kwSet[wxSTC_LEX_CPPNOCASE]
    32,	// = kwSet[ 36] = kwSet[wxSTC_LEX_FORTRAN]
    32,	// = kwSet[ 37] = kwSet[wxSTC_LEX_F77]
    23,	// = kwSet[ 38] = kwSet[wxSTC_LEX_CSS]
    60,	// = kwSet[ 39] = kwSet[wxSTC_LEX_POV]
    42,	// = kwSet[ 40] = kwSet[wxSTC_LEX_LOUT]
    29,	// = kwSet[ 41] = kwSet[wxSTC_LEX_ESCRIPT]
    63,	// = kwSet[ 42] = kwSet[wxSTC_LEX_PS]
    51,	// = kwSet[ 43] = kwSet[wxSTC_LEX_NSIS]
    47,	// = kwSet[ 44] = kwSet[wxSTC_LEX_MMIXAL]
    67,	// = kwSet[ 45] = kwSet[wxSTC_LEX_CLW]
    67,	// = kwSet[ 46] = kwSet[wxSTC_LEX_CLWNOCASE]
    -1,	// = kwSet[ 47] = kwSet[wxSTC_LEX_LOT]
    87,	// = kwSet[ 48] = kwSet[wxSTC_LEX_YAML]
    82,	// = kwSet[ 49] = kwSet[wxSTC_LEX_TEX]
    46,	// = kwSet[ 50] = kwSet[wxSTC_LEX_METAPOST]
    56,	// = kwSet[ 51] = kwSet[wxSTC_LEX_POWERBASIC]
    31,	// = kwSet[ 52] = kwSet[wxSTC_LEX_FORTH]
    28,	// = kwSet[ 53] = kwSet[wxSTC_LEX_ERLANG]
    52,	// = kwSet[ 54] = kwSet[wxSTC_LEX_OCTAVE]
    76,	// = kwSet[ 55] = kwSet[wxSTC_LEX_MSSQL]
    84,	// = kwSet[ 56] = kwSet[wxSTC_LEX_VERILOG]
    40,	// = kwSet[ 57] = kwSet[wxSTC_LEX_KIX]
    36,	// = kwSet[ 58] = kwSet[wxSTC_LEX_GUI4CLI]
    74,	// = kwSet[ 59] = kwSet[wxSTC_LEX_SPECMAN]
    8,	// = kwSet[ 60] = kwSet[wxSTC_LEX_AU3]
    4,	// = kwSet[ 61] = kwSet[wxSTC_LEX_APDL]
    12,	// = kwSet[ 62] = kwSet[wxSTC_LEX_BASH]
    6,	// = kwSet[ 63] = kwSet[wxSTC_LEX_ASN1]
    85,	// = kwSet[ 64] = kwSet[wxSTC_LEX_VHDL]
    16,	// = kwSet[ 65] = kwSet[wxSTC_LEX_CAML]
    14,	// = kwSet[ 66] = kwSet[wxSTC_LEX_BLITZBASIC]
    64,	// = kwSet[ 67] = kwSet[wxSTC_LEX_PUREBASIC]
    37,	// = kwSet[ 68] = kwSet[wxSTC_LEX_HASKELL]
    58,	// = kwSet[ 69] = kwSet[wxSTC_LEX_PHPSCRIPT]
    78,	// = kwSet[ 70] = kwSet[wxSTC_LEX_TADS3]
    66,	// = kwSet[ 71] = kwSet[wxSTC_LEX_REBOL]
    71,	// = kwSet[ 72] = kwSet[wxSTC_LEX_SMALLTALK]
    34,	// = kwSet[ 73] = kwSet[wxSTC_LEX_FLAGSHIP]
    22,	// = kwSet[ 74] = kwSet[wxSTC_LEX_CSOUND]
    33,	// = kwSet[ 75] = kwSet[wxSTC_LEX_FREEBASIC]
    39,	// = kwSet[ 76] = kwSet[wxSTC_LEX_INNOSETUP]
    53,	// = kwSet[ 77] = kwSet[wxSTC_LEX_OPAL]
    75,	// = kwSet[ 78] = kwSet[wxSTC_LEX_SPICE]
    25,	// = kwSet[ 79] = kwSet[wxSTC_LEX_D]
    17,	// = kwSet[ 80] = kwSet[wxSTC_LEX_CMAKE]
    35,	// = kwSet[ 81] = kwSet[wxSTC_LEX_GAP]
    59,	// = kwSet[ 82] = kwSet[wxSTC_LEX_PLM]
    30,	// = kwSet[ 83] = kwSet[wxSTC_LEX_PROGRESS]
    2,	// = kwSet[ 84] = kwSet[wxSTC_LEX_ABAQUS]
    7,	// = kwSet[ 85] = kwSet[wxSTC_LEX_ASYMPTOTE]
    69,	// = kwSet[ 86] = kwSet[wxSTC_LEX_R]
    44,	// = kwSet[ 87] = kwSet[wxSTC_LEX_MAGIK]
    62,	// = kwSet[ 88] = kwSet[wxSTC_LEX_POWERSHELL]
    49,	// = kwSet[ 89] = kwSet[wxSTC_LEX_MYSQL]
    -1,	// = kwSet[ 90] = kwSet[wxSTC_LEX_PO]
    79,	// = kwSet[ 91] = kwSet[wxSTC_LEX_TAL]
    18,	// = kwSet[ 92] = kwSet[wxSTC_LEX_COBOL]
    77,	// = kwSet[ 93] = kwSet[wxSTC_LEX_TACL]
    73,	// = kwSet[ 94] = kwSet[wxSTC_LEX_SORCUS]
    61,	// = kwSet[ 95] = kwSet[wxSTC_LEX_POWERPRO]
    50,	// = kwSet[ 96] = kwSet[wxSTC_LEX_NIMROD]
    72,	// = kwSet[ 97] = kwSet[wxSTC_LEX_SML]
    -1,	// = kwSet[ 98] = kwSet[wxSTC_LEX_MARKDOWN]
    -1,	// = kwSet[ 99] = kwSet[wxSTC_LEX_TXT2TAGS]
    1,	// = kwSet[100] = kwSet[wxSTC_LEX_A68K]
    48,	// = kwSet[101] = kwSet[wxSTC_LEX_MODULA]
    24,	// = kwSet[102] = kwSet[wxSTC_LEX_COFFEESCRIPT]
    81,	// = kwSet[103] = kwSet[wxSTC_LEX_TCMD]
    10,	// = kwSet[104] = kwSet[wxSTC_LEX_AVS]
    26,	// = kwSet[105] = kwSet[wxSTC_LEX_ECL]
    54,	// = kwSet[106] = kwSet[wxSTC_LEX_OSCRIPT]
    86	// = kwSet[107] = kwSet[wxSTC_LEX_VISUALPROLOG]
};

static int lexerStateSet[]={
-1,	//wxSTC_LEX_CONTAINER
-1,	//wxSTC_LEX_NULL
57,	//wxSTC_LEX_PYTHON
15,	//wxSTC_LEX_CPP
35,	//wxSTC_LEX_HTML
35,	//wxSTC_LEX_XML
59,	//wxSTC_LEX_PERL
76,	//wxSTC_LEX_SQL
12,	//wxSTC_LEX_VB
65,	//wxSTC_LEX_PROPERTIES
28,	//wxSTC_LEX_ERRORLIST
45,	//wxSTC_LEX_MAKEFILE
14,	//wxSTC_LEX_BATCH
-1,	//wxSTC_LEX_XCODE
39,	//wxSTC_LEX_LATEX
43,	//wxSTC_LEX_LUA
24,	//wxSTC_LEX_DIFF
20,	//wxSTC_LEX_CONF
58,	//wxSTC_LEX_PASCAL
10,	//wxSTC_LEX_AVE
4,	//wxSTC_LEX_ADA
40,	//wxSTC_LEX_LISP
68,	//wxSTC_LEX_RUBY
26,	//wxSTC_LEX_EIFFEL
26,	//wxSTC_LEX_EIFFELKW
79,	//wxSTC_LEX_TCL
53,	//wxSTC_LEX_NNCRONTAB
15,	//wxSTC_LEX_BULLANT
12,	//wxSTC_LEX_VBSCRIPT
-1,	//
-1,	//
13,	//wxSTC_LEX_BAAN
47,	//wxSTC_LEX_MATLAB
70,	//wxSTC_LEX_SCRIPTOL
6,	//wxSTC_LEX_ASM
15,	//wxSTC_LEX_CPPNOCASE
30,	//wxSTC_LEX_FORTRAN
30,	//wxSTC_LEX_F77
22,	//wxSTC_LEX_CSS
62,	//wxSTC_LEX_POV
42,	//wxSTC_LEX_LOUT
29,	//wxSTC_LEX_ESCRIPT
66,	//wxSTC_LEX_PS
54,	//wxSTC_LEX_NSIS
49,	//wxSTC_LEX_MMIXAL
17,	//wxSTC_LEX_CLW
17,	//wxSTC_LEX_CLWNOCASE
41,	//wxSTC_LEX_LOT
86,	//wxSTC_LEX_YAML
81,	//wxSTC_LEX_TEX
48,	//wxSTC_LEX_METAPOST
12,	//wxSTC_LEX_POWERBASIC
31,	//wxSTC_LEX_FORTH
27,	//wxSTC_LEX_ERLANG
47,	//wxSTC_LEX_OCTAVE
51,	//wxSTC_LEX_MSSQL
83,	//wxSTC_LEX_VERILOG
38,	//wxSTC_LEX_KIX
34,	//wxSTC_LEX_GUI4CLI
73,	//wxSTC_LEX_SPECMAN
9,	//wxSTC_LEX_AU3
5,	//wxSTC_LEX_APDL
71,	//wxSTC_LEX_BASH
7,	//wxSTC_LEX_ASN1
84,	//wxSTC_LEX_VHDL
16,	//wxSTC_LEX_CAML
12,	//wxSTC_LEX_BLITZBASIC
12,	//wxSTC_LEX_PUREBASIC
36,	//wxSTC_LEX_HASKELL
35,	//wxSTC_LEX_PHPSCRIPT
78,	//wxSTC_LEX_TADS3
69,	//wxSTC_LEX_REBOL
77,	//wxSTC_LEX_SMALLTALK
32,	//wxSTC_LEX_FLAGSHIP
21,	//wxSTC_LEX_CSOUND
12,	//wxSTC_LEX_FREEBASIC
37,	//wxSTC_LEX_INNOSETUP
55,	//wxSTC_LEX_OPAL
75,	//wxSTC_LEX_SPICE
23,	//wxSTC_LEX_D
18,	//wxSTC_LEX_CMAKE
33,	//wxSTC_LEX_GAP
60,	//wxSTC_LEX_PLM
1,	//wxSTC_LEX_PROGRESS
3,	//wxSTC_LEX_ABAQUS
8,	//wxSTC_LEX_ASYMPTOTE
67,	//wxSTC_LEX_R
44,	//wxSTC_LEX_MAGIK
64,	//wxSTC_LEX_POWERSHELL
52,	//wxSTC_LEX_MYSQL
61,	//wxSTC_LEX_PO
15,	//wxSTC_LEX_TAL
15,	//wxSTC_LEX_COBOL
15,	//wxSTC_LEX_TACL
74,	//wxSTC_LEX_SORCUS
63,	//wxSTC_LEX_POWERPRO
57,	//wxSTC_LEX_NIMROD
72,	//wxSTC_LEX_SML
46,	//wxSTC_LEX_MARKDOWN
82,	//wxSTC_LEX_TXT2TAGS
2,	//wxSTC_LEX_A68K
50,	//wxSTC_LEX_MODULA
19,	//wxSTC_LEX_COFFEESCRIPT
80,	//wxSTC_LEX_TCMD
11,	//wxSTC_LEX_AVS
25,	//wxSTC_LEX_ECL
56,	//wxSTC_LEX_OSCRIPT
85  //wxSTC_LEX_VISUALPROLOG
};

static int  propSet[]={
    -1,	//propSet[  0] = propSet[wxSTC_LEX_CONTAINER]
    37,	//propSet[  1] = propSet[wxSTC_LEX_NULL]
    46,	//propSet[  2] = propSet[wxSTC_LEX_PYTHON]
    3,	//propSet[  3] = propSet[wxSTC_LEX_CPP]
    26,	//propSet[  4] = propSet[wxSTC_LEX_HTML]
    26,	//propSet[  5] = propSet[wxSTC_LEX_XML]
    5,	//propSet[  6] = propSet[wxSTC_LEX_PERL]
    6,	//propSet[  7] = propSet[wxSTC_LEX_SQL]
    -1,	//propSet[  8] = propSet[wxSTC_LEX_VB]
    37,	//propSet[  9] = propSet[wxSTC_LEX_PROPERTIES]
    37,	//propSet[ 10] = propSet[wxSTC_LEX_ERRORLIST]
    37,	//propSet[ 11] = propSet[wxSTC_LEX_MAKEFILE]
    37,	//propSet[ 12] = propSet[wxSTC_LEX_BATCH]
    -1,	//propSet[ 13] = propSet[wxSTC_LEX_XCODE]
    37,	//propSet[ 14] = propSet[wxSTC_LEX_LATEX]
    28,	//propSet[ 15] = propSet[wxSTC_LEX_LUA]
    37,	//propSet[ 16] = propSet[wxSTC_LEX_DIFF]
    -1,	//propSet[ 17] = propSet[wxSTC_LEX_CONF]
    38,	//propSet[ 18] = propSet[wxSTC_LEX_PASCAL]
    12,	//propSet[ 19] = propSet[wxSTC_LEX_AVE]
    -1,	//propSet[ 20] = propSet[wxSTC_LEX_ADA]
    -1,	//propSet[ 21] = propSet[wxSTC_LEX_LISP]
    48,	//propSet[ 22] = propSet[wxSTC_LEX_RUBY]
    -1,	//propSet[ 23] = propSet[wxSTC_LEX_EIFFEL]
    -1,	//propSet[ 24] = propSet[wxSTC_LEX_EIFFELKW]
    54,	//propSet[ 25] = propSet[wxSTC_LEX_TCL]
    -1,	//propSet[ 26] = propSet[wxSTC_LEX_NNCRONTAB]
    16,	//propSet[ 27] = propSet[wxSTC_LEX_BULLANT]
    -1,	//propSet[ 28] = propSet[wxSTC_LEX_VBSCRIPT]
    -1,	//propSet[ 29] = propSet[]
    -1,	//propSet[ 30] = propSet[]
    14,	//propSet[ 31] = propSet[wxSTC_LEX_BAAN]
    -1,	//propSet[ 32] = propSet[wxSTC_LEX_MATLAB]
    49,	//propSet[ 33] = propSet[wxSTC_LEX_SCRIPTOL]
    1,	//propSet[ 34] = propSet[wxSTC_LEX_ASM]
    3,	//propSet[ 35] = propSet[wxSTC_LEX_CPPNOCASE]
    24,	//propSet[ 36] = propSet[wxSTC_LEX_FORTRAN]
    24,	//propSet[ 37] = propSet[wxSTC_LEX_F77]
    21,	//propSet[ 38] = propSet[wxSTC_LEX_CSS]
    41,	//propSet[ 39] = propSet[wxSTC_LEX_POV]
    27,	//propSet[ 40] = propSet[wxSTC_LEX_LOUT]
    22,	//propSet[ 41] = propSet[wxSTC_LEX_ESCRIPT]
    45,	//propSet[ 42] = propSet[wxSTC_LEX_PS]
    35,	//propSet[ 43] = propSet[wxSTC_LEX_NSIS]
    -1,	//propSet[ 44] = propSet[wxSTC_LEX_MMIXAL]
    -1,	//propSet[ 45] = propSet[wxSTC_LEX_CLW]
    -1,	//propSet[ 46] = propSet[wxSTC_LEX_CLWNOCASE]
    31,	//propSet[ 47] = propSet[wxSTC_LEX_LOT]
    58,	//propSet[ 48] = propSet[wxSTC_LEX_YAML]
    55,	//propSet[ 49] = propSet[wxSTC_LEX_TEX]
    30,	//propSet[ 50] = propSet[wxSTC_LEX_METAPOST]
    39,	//propSet[ 51] = propSet[wxSTC_LEX_POWERBASIC]
    -1,	//propSet[ 52] = propSet[wxSTC_LEX_FORTH]
    -1,	//propSet[ 53] = propSet[wxSTC_LEX_ERLANG]
    -1,	//propSet[ 54] = propSet[wxSTC_LEX_OCTAVE]
    32,	//propSet[ 55] = propSet[wxSTC_LEX_MSSQL]
    56,	//propSet[ 56] = propSet[wxSTC_LEX_VERILOG]
    -1,	//propSet[ 57] = propSet[wxSTC_LEX_KIX]
    25,	//propSet[ 58] = propSet[wxSTC_LEX_GUI4CLI]
    51,	//propSet[ 59] = propSet[wxSTC_LEX_SPECMAN]
    11,	//propSet[ 60] = propSet[wxSTC_LEX_AU3]
    8,	//propSet[ 61] = propSet[wxSTC_LEX_APDL]
    15,	//propSet[ 62] = propSet[wxSTC_LEX_BASH]
    9,	//propSet[ 63] = propSet[wxSTC_LEX_ASN1]
    57,	//propSet[ 64] = propSet[wxSTC_LEX_VHDL]
    17,	//propSet[ 65] = propSet[wxSTC_LEX_CAML]
    2,	//propSet[ 66] = propSet[wxSTC_LEX_BLITZBASIC]
    2,	//propSet[ 67] = propSet[wxSTC_LEX_PUREBASIC]
    -1,	//propSet[ 68] = propSet[wxSTC_LEX_HASKELL]
    26,	//propSet[ 69] = propSet[wxSTC_LEX_PHPSCRIPT]
    -1,	//propSet[ 70] = propSet[wxSTC_LEX_TADS3]
    -1,	//propSet[ 71] = propSet[wxSTC_LEX_REBOL]
    -1,	//propSet[ 72] = propSet[wxSTC_LEX_SMALLTALK]
    23,	//propSet[ 73] = propSet[wxSTC_LEX_FLAGSHIP]
    -1,	//propSet[ 74] = propSet[wxSTC_LEX_CSOUND]
    2,	//propSet[ 75] = propSet[wxSTC_LEX_FREEBASIC]
    -1,	//propSet[ 76] = propSet[wxSTC_LEX_INNOSETUP]
    -1,	//propSet[ 77] = propSet[wxSTC_LEX_OPAL]
    -1,	//propSet[ 78] = propSet[wxSTC_LEX_SPICE]
    4,	//propSet[ 79] = propSet[wxSTC_LEX_D]
    18,	//propSet[ 80] = propSet[wxSTC_LEX_CMAKE]
    -1,	//propSet[ 81] = propSet[wxSTC_LEX_GAP]
    40,	//propSet[ 82] = propSet[wxSTC_LEX_PLM]
    44,	//propSet[ 83] = propSet[wxSTC_LEX_PROGRESS]
    7,	//propSet[ 84] = propSet[wxSTC_LEX_ABAQUS]
    10,	//propSet[ 85] = propSet[wxSTC_LEX_ASYMPTOTE]
    47,	//propSet[ 86] = propSet[wxSTC_LEX_R]
    29,	//propSet[ 87] = propSet[wxSTC_LEX_MAGIK]
    43,	//propSet[ 88] = propSet[wxSTC_LEX_POWERSHELL]
    33,	//propSet[ 89] = propSet[wxSTC_LEX_MYSQL]
    37,	//propSet[ 90] = propSet[wxSTC_LEX_PO]
    53,	//propSet[ 91] = propSet[wxSTC_LEX_TAL]
    19,	//propSet[ 92] = propSet[wxSTC_LEX_COBOL]
    52,	//propSet[ 93] = propSet[wxSTC_LEX_TACL]
    -1,	//propSet[ 94] = propSet[wxSTC_LEX_SORCUS]
    42,	//propSet[ 95] = propSet[wxSTC_LEX_POWERPRO]
    34,	//propSet[ 96] = propSet[wxSTC_LEX_NIMROD]
    50,	//propSet[ 97] = propSet[wxSTC_LEX_SML]
    -1,	//propSet[ 98] = propSet[wxSTC_LEX_MARKDOWN]
    -1,	//propSet[ 99] = propSet[wxSTC_LEX_TXT2TAGS]
    -1,	//propSet[100] = propSet[wxSTC_LEX_A68K]
    -1,	//propSet[101] = propSet[wxSTC_LEX_MODULA]
    20,	//propSet[102] = propSet[wxSTC_LEX_COFFEESCRIPT]
    -1,	//propSet[103] = propSet[wxSTC_LEX_TCMD]
    13,	//propSet[104] = propSet[wxSTC_LEX_AVS]
    -1,	//propSet[105] = propSet[wxSTC_LEX_ECL]
    36,	//propSet[106] = propSet[wxSTC_LEX_OSCRIPT]
    -1	//propSet[107] = propSet[wxSTC_LEX_VISUALPROLOG]
};

static lexerItem kwSetName[]={
{1,0,"CPU instructions"},
{1,1,"Registers"},
{1,2,"Directives"},
{1,3,"Extended instructions"},
{1,4,"Comment special words"},
{1,5,"Doxygen keywords"},
{2,0,"processors"},
{2,1,"commands"},
{2,2,"slashommands"},
{2,3,"starcommands"},
{2,4,"arguments"},
{2,5,"functions"},
{3,0,"Keywords"},
{4,0,"processors"},
{4,1,"commands"},
{4,2,"slashommands"},
{4,3,"starcommands"},
{4,4,"arguments"},
{4,5,"functions"},
{5,0,"CPU instructions"},
{5,1,"FPU instructions"},
{5,2,"Registers"},
{5,3,"Directives"},
{5,4,"Directive operands"},
{5,5,"Extended instructions"},
{5,6,"Directives4Foldstart"},
{5,7,"Directives4Foldend"},
{6,0,"Keywords"},
{6,1,"Attributes"},
{6,2,"Descriptors"},
{6,3,"Types"},
{7,0,"Primary keywords and identifiers"},
{7,1,"Secondary keywords and identifiers"},
{8,0,"#autoit keywords"},
{8,1,"#autoit functions"},
{8,2,"#autoit macros"},
{8,3,"#autoit Sent keys"},
{8,4,"#autoit Pre-processors"},
{8,5,"#autoit Special"},
{8,6,"#autoit Expand"},
{8,7,"#autoit UDF"},
{9,0,"SCE_AVE_WORD1"},
{9,1,"SCE_AVE_WORD2"},
{9,2,"SCE_AVE_WORD3"},
{9,3,"SCE_AVE_WORD4"},
{9,4,"SCE_AVE_WORD5"},
{9,5,"SCE_AVE_WORD6"},
{10,0,"Keywords"},
{10,1,"Filters"},
{10,2,"Plugins"},
{10,3,"Functions"},
{10,4,"Clip properties"},
{10,5,"User defined functions"},
{11,0,"SCE_BAAN_WORD"},
{11,1,"SCE_BAAN_WORD2"},
{12,0,"Keywords"},
{13,0,"Internal Commands"},
{13,1,"External Commands"},
{14,0,"BlitzBasic Keywords"},
{14,1,"user1"},
{14,2,"user2"},
{14,3,"user3"},
{15,0,"Keywords"},
{16,0,"Keywords"},
{16,1,"Keywords2"},
{16,2,"Keywords3"},
{17,0,"Commands"},
{17,1,"Parameters"},
{17,2,"UserDefined"},
{18,0,"A Keywords"},
{18,1,"B Keywords"},
{18,2,"Extended Keywords"},
{19,0,"Directives"},
{19,1,"Parameters"},
{20,0,"Primary keywords and identifiers"},
{20,1,"Secondary keywords and identifiers"},
{20,2,"Documentation comment keywords"},
{20,3,"Global classes and typedefs"},
{20,4,"Preprocessor definitions"},
{21,0,"Section keywords and Forth words"},
{21,1,"nnCrontab keywords"},
{21,2,"Modifiers"},
{22,0,"Opcodes"},
{22,1,"Header Statements"},
{22,2,"User keywords"},
{23,0,"CSS1 Properties"},
{23,1,"Pseudo-classes"},
{23,2,"CSS2 Properties"},
{23,3,"CSS3 Properties"},
{23,4,"Pseudo-elements"},
{23,5,"Browser-Specific CSS Properties"},
{23,6,"Browser-Specific Pseudo-classes"},
{23,7,"Browser-Specific Pseudo-elements"},
{24,0,"Keywords"},
{25,0,"Primary keywords and identifiers"},
{25,1,"Secondary keywords and identifiers"},
{25,2,"Documentation comment keywords"},
{25,3,"Type definitions and aliases"},
{25,4,"Keywords 5"},
{25,5,"Keywords 6"},
{25,6,"Keywords 7"},
{26,0,"Keywords"},
{27,0,"Keywords"},
{28,0,"Erlang Reserved words"},
{28,1,"Erlang BIFs"},
{28,2,"Erlang Preprocessor"},
{28,3,"Erlang Module Attributes"},
{28,4,"Erlang Documentation"},
{28,5,"Erlang Documentation Macro"},
{29,0,"Primary keywords and identifiers"},
{29,1,"Intrinsic functions"},
{29,2,"Extended and user defined functions"},
{30,0,"Primary keywords and identifiers"},
{30,1,"Secondary keywords and identifiers"},
{30,2,"Documentation comment keywords"},
{30,3,"Unused"},
{30,4,"Global classes and typedefs"},
{31,0,"control keywords"},
{31,1,"keywords"},
{31,2,"definition words"},
{31,3,"prewords with one argument"},
{31,4,"prewords with two arguments"},
{31,5,"string definition keywords"},
{32,0,"Primary keywords and identifiers"},
{32,1,"Intrinsic functions"},
{32,2,"Extended and user defined functions"},
{33,0,"FreeBasic Keywords"},
{33,1,"FreeBasic PreProcessor Keywords"},
{33,2,"user defined 1"},
{33,3,"user defined 2"},
{34,0,"Keywords Commands"},
{34,1,"Std Library Functions"},
{34,2,"Procedure, return, exit"},
{34,3,"Class (oop)"},
{34,4,"Doxygen keywords"},
{35,0,"Keywords 1"},
{35,1,"Keywords 2"},
{35,2,"Keywords 3 (unused)"},
{35,3,"Keywords 4 (unused)"},
{36,0,"Globals"},
{36,1,"Events"},
{36,2,"Attributes"},
{36,3,"Control"},
{36,4,"Commands"},
{37,0,"SCE_HA_KEYWORD"},
{37,1,"SCE_HA_KEYWORD (used for ffi)"},
{38,0,"HTML elements and attributes"},
{38,1,"JavaScript keywords"},
{38,2,"VBScript keywords"},
{38,3,"Python keywords"},
{38,4,"PHP keywords"},
{38,5,"SGML and DTD keywords"},
{39,0,"Sections"},
{39,1,"Keywords"},
{39,2,"Parameters"},
{39,3,"Preprocessor directives"},
{39,4,"Pascal keywords"},
{39,5,"User defined keywords"},
{40,0,"SCE_KIX_KEYWORD"},
{40,1,"SCE_KIX_FUNCTIONS"},
{40,2,"SCE_KIX_MACRO"},
{41,0,"Functions and special operators"},
{41,1,"Keywords"},
{42,0,"Predefined identifiers"},
{42,1,"Predefined delimiters"},
{42,2,"Predefined keywords"},
{43,0,"Keywords"},
{43,1,"Basic functions"},
{43,2,"String, (table) & math functions"},
{43,3,"(coroutines), I/O & system facilities"},
{43,4,"user1"},
{43,5,"user2"},
{43,6,"user3"},
{43,7,"user4"},
{44,0,"Accessors (local, global, self, super, thisthread)"},
{44,1,"Pragmatic (pragma, private)"},
{44,2,"Containers (method, block, proc)"},
{44,3,"Flow (if, then, elif, else)"},
{44,4,"Characters (space, tab, newline, return)"},
{44,5,"Fold Containers (method, proc, block, if, loop)"},
{45,0,"Keywords"},
{46,0,"MetaPost"},
{46,1,"MetaFun"},
{47,0,"Operation Codes"},
{47,1,"Special Register"},
{47,2,"Predefined Symbols"},
{48,0,"Keywords"},
{48,1,"ReservedKeywords"},
{48,2,"Operators"},
{48,3,"PragmaKeyswords"},
{48,4,"EscapeCodes"},
{48,5,"DoxygeneKeywords"},
{49,0,"Major Keywords"},
{49,1,"Keywords"},
{49,2,"Database Objects"},
{49,3,"Functions"},
{49,4,"System Variables"},
{49,5,"Procedure keywords"},
{49,6,"User Keywords 1"},
{49,7,"User Keywords 2"},
{49,8,"User Keywords 3"},
{50,0,"Keywords"},
{51,0,"Functions"},
{51,1,"Variables"},
{51,2,"Lables"},
{51,3,"UserDefined"},
{52,0,"Keywords"},
{53,0,"Keywords"},
{53,1,"Sorts"},
{54,0,"Keywords and reserved words"},
{54,1,"Literal constants"},
{54,2,"Literal operators"},
{54,3,"Built-in value and reference types"},
{54,4,"Built-in global functions"},
{54,5,"Built-in static objects"},
{55,0,"Keywords"},
{56,0,"Keywords"},
{57,0,"Keywords"},
{58,0,"PHP keywords"},
{59,0,"Keywords"},
{60,0,"Language directives"},
{60,1,"Objects & CSG & Appearance"},
{60,2,"Types & Modifiers & Items"},
{60,3,"Predefined Identifiers"},
{60,4,"Predefined Functions"},
{60,5,"User defined 1"},
{60,6,"User defined 2"},
{60,7,"User defined 3"},
{61,0,"Keyword list 1"},
{61,1,"Keyword list 2"},
{61,2,"Keyword list 3"},
{61,3,"Keyword list 4"},
{62,0,"Commands"},
{62,1,"Cmdlets"},
{62,2,"Aliases"},
{62,3,"Functions"},
{62,4,"User1"},
{63,0,"PS Level 1 operators"},
{63,1,"PS Level 2 operators"},
{63,2,"PS Level 3 operators"},
{63,3,"RIP-specific operators"},
{63,4,"User-defined operators"},
{64,0,"PureBasic Keywords"},
{64,1,"PureBasic PreProcessor Keywords"},
{64,2,"user defined 1"},
{64,3,"user defined 2"},
{65,0,"Keywords"},
{65,1,"Highlighted identifiers"},
{66,0,"Keywords"},
{67,0,"Clarion Keywords"},
{67,1,"Compiler Directives"},
{67,2,"Built-in Procedures and Functions"},
{67,3,"Runtime Expressions"},
{67,4,"Structure and Data Types"},
{67,5,"Attributes"},
{67,6,"Standard Equates"},
{67,7,"Reserved Words (Labels)"},
{67,8,"Reserved Words (Procedure Labels)"},
{68,0,"Keywords"},
{69,0,"Language Keywords"},
{69,1,"Base / Default package function"},
{69,2,"Other Package Functions"},
{69,3,"Unused"},
{69,4,"Unused"},
{70,0,"SCE_SCRIPTOL_KEYWORD"},
{71,0,"Special selectors"},
{72,0,"Keywords"},
{72,1,"Keywords2"},
{72,2,"Keywords3"},
{73,0,"Command"},
{73,1,"Parameter"},
{73,2,"Constant"},
{74,0,"Primary keywords and identifiers"},
{74,1,"Secondary keywords and identifiers"},
{74,2,"Sequence keywords and identifiers"},
{74,3,"User defined keywords and identifiers"},
{74,4,"Unused"},
{75,0,"Keywords"},
{75,1,"Keywords2"},
{75,2,"Keywords3"},
{76,0,"Keywords"},
{76,1,"Database Objects"},
{76,2,"PLDoc"},
{76,3,"SQL*Plus"},
{76,4,"User Keywords 1"},
{76,5,"User Keywords 2"},
{76,6,"User Keywords 3"},
{76,7,"User Keywords 4"},
{77,0,"Builtins"},
{77,1,"Labels"},
{77,2,"Commands"},
{78,0,"TADS3 Keywords"},
{78,1,"User defined 1"},
{78,2,"User defined 2"},
{78,3,"User defined 3"},
{79,0,"Keywords"},
{79,1,"Builtins"},
{80,0,"TCL Keywords"},
{80,1,"TK Keywords"},
{80,2,"iTCL Keywords"},
{80,3,"tkCommands"},
{80,4,"expanduser1"},
{80,5,"user2"},
{80,6,"user3"},
{80,7,"user4"},
{81,0,"Internal Commands"},
{81,1,"Aliases"},
{82,0,"TeX, eTeX, pdfTeX, Omega"},
{82,1,"ConTeXt Dutch"},
{82,2,"ConTeXt English"},
{82,3,"ConTeXt German"},
{82,4,"ConTeXt Czech"},
{82,5,"ConTeXt Italian"},
{82,6,"ConTeXt Romanian"},
{83,0,"Keywords"},
{83,1,"user1"},
{83,2,"user2"},
{83,3,"user3"},
{84,0,"Primary keywords and identifiers"},
{84,1,"Secondary keywords and identifiers"},
{84,2,"System Tasks"},
{84,3,"User defined tasks and identifiers"},
{84,4,"Unused"},
{85,0,"Keywords"},
{85,1,"Operators"},
{85,2,"Attributes"},
{85,3,"Standard Functions"},
{85,4,"Standard Packages"},
{85,5,"Standard Types"},
{85,6,"User Words"},
{86,0,"Major keywords (class, predicates, ...)"},
{86,1,"Minor keywords (if, then, try, ...)"},
{86,2,"Directive keywords without the '#' (include, requires, ...)"},
{86,3,"Documentation keywords without the '@' (short, detail, ...)"},
{87,0,"Keywords"}
};

static lexerItem stateName[] = {
{1,0,"wxSTC_4GL_DEFAULT"},
{1,1,"wxSTC_4GL_NUMBER"},
{1,2,"wxSTC_4GL_WORD"},
{1,3,"wxSTC_4GL_STRING"},
{1,4,"wxSTC_4GL_CHARACTER"},
{1,5,"wxSTC_4GL_PREPROCESSOR"},
{1,6,"wxSTC_4GL_OPERATOR"},
{1,7,"wxSTC_4GL_IDENTIFIER"},
{1,8,"wxSTC_4GL_BLOCK"},
{1,9,"wxSTC_4GL_END"},
{1,10,"wxSTC_4GL_COMMENT1"},
{1,11,"wxSTC_4GL_COMMENT2"},
{1,12,"wxSTC_4GL_COMMENT3"},
{1,13,"wxSTC_4GL_COMMENT4"},
{1,14,"wxSTC_4GL_COMMENT5"},
{1,15,"wxSTC_4GL_COMMENT6"},
{1,16,"wxSTC_4GL_DEFAULT_"},
{1,17,"wxSTC_4GL_NUMBER_"},
{1,18,"wxSTC_4GL_WORD_"},
{1,19,"wxSTC_4GL_STRING_"},
{1,20,"wxSTC_4GL_CHARACTER_"},
{1,21,"wxSTC_4GL_PREPROCESSOR_"},
{1,22,"wxSTC_4GL_OPERATOR_"},
{1,23,"wxSTC_4GL_IDENTIFIER_"},
{1,24,"wxSTC_4GL_BLOCK_"},
{1,25,"wxSTC_4GL_END_"},
{1,26,"wxSTC_4GL_COMMENT1_"},
{1,27,"wxSTC_4GL_COMMENT2_"},
{1,28,"wxSTC_4GL_COMMENT3_"},
{1,29,"wxSTC_4GL_COMMENT4_"},
{1,30,"wxSTC_4GL_COMMENT5_"},
{1,31,"wxSTC_4GL_COMMENT6_"},
{2,0,"wxSTC_A68K_DEFAULT"},
{2,1,"wxSTC_A68K_COMMENT"},
{2,2,"wxSTC_A68K_NUMBER_DEC"},
{2,3,"wxSTC_A68K_NUMBER_BIN"},
{2,4,"wxSTC_A68K_NUMBER_HEX"},
{2,5,"wxSTC_A68K_STRING1"},
{2,6,"wxSTC_A68K_OPERATOR"},
{2,7,"wxSTC_A68K_CPUINSTRUCTION"},
{2,8,"wxSTC_A68K_EXTINSTRUCTION"},
{2,9,"wxSTC_A68K_REGISTER"},
{2,10,"wxSTC_A68K_DIRECTIVE"},
{2,11,"wxSTC_A68K_MACRO_ARG"},
{2,12,"wxSTC_A68K_LABEL"},
{2,13,"wxSTC_A68K_STRING2"},
{2,14,"wxSTC_A68K_IDENTIFIER"},
{2,15,"wxSTC_A68K_MACRO_DECLARATION"},
{2,16,"wxSTC_A68K_COMMENT_WORD"},
{2,17,"wxSTC_A68K_COMMENT_SPECIAL"},
{2,18,"wxSTC_A68K_COMMENT_DOXYGEN"},
{3,0,"wxSTC_ABAQUS_DEFAULT"},
{3,1,"wxSTC_ABAQUS_COMMENT"},
{3,2,"wxSTC_ABAQUS_COMMENTBLOCK"},
{3,3,"wxSTC_ABAQUS_NUMBER"},
{3,4,"wxSTC_ABAQUS_STRING"},
{3,5,"wxSTC_ABAQUS_OPERATOR"},
{3,6,"wxSTC_ABAQUS_WORD"},
{3,7,"wxSTC_ABAQUS_PROCESSOR"},
{3,8,"wxSTC_ABAQUS_COMMAND"},
{3,9,"wxSTC_ABAQUS_SLASHCOMMAND"},
{3,10,"wxSTC_ABAQUS_STARCOMMAND"},
{3,11,"wxSTC_ABAQUS_ARGUMENT"},
{3,12,"wxSTC_ABAQUS_FUNCTION"},
{4,0,"wxSTC_ADA_DEFAULT"},
{4,1,"wxSTC_ADA_WORD"},
{4,2,"wxSTC_ADA_IDENTIFIER"},
{4,3,"wxSTC_ADA_NUMBER"},
{4,4,"wxSTC_ADA_DELIMITER"},
{4,5,"wxSTC_ADA_CHARACTER"},
{4,6,"wxSTC_ADA_CHARACTEREOL"},
{4,7,"wxSTC_ADA_STRING"},
{4,8,"wxSTC_ADA_STRINGEOL"},
{4,9,"wxSTC_ADA_LABEL"},
{4,10,"wxSTC_ADA_COMMENTLINE"},
{4,11,"wxSTC_ADA_ILLEGAL"},
{5,0,"wxSTC_APDL_DEFAULT"},
{5,1,"wxSTC_APDL_COMMENT"},
{5,2,"wxSTC_APDL_COMMENTBLOCK"},
{5,3,"wxSTC_APDL_NUMBER"},
{5,4,"wxSTC_APDL_STRING"},
{5,5,"wxSTC_APDL_OPERATOR"},
{5,6,"wxSTC_APDL_WORD"},
{5,7,"wxSTC_APDL_PROCESSOR"},
{5,8,"wxSTC_APDL_COMMAND"},
{5,9,"wxSTC_APDL_SLASHCOMMAND"},
{5,10,"wxSTC_APDL_STARCOMMAND"},
{5,11,"wxSTC_APDL_ARGUMENT"},
{5,12,"wxSTC_APDL_FUNCTION"},
{6,0,"wxSTC_ASM_DEFAULT"},
{6,1,"wxSTC_ASM_COMMENT"},
{6,2,"wxSTC_ASM_NUMBER"},
{6,3,"wxSTC_ASM_STRING"},
{6,4,"wxSTC_ASM_OPERATOR"},
{6,5,"wxSTC_ASM_IDENTIFIER"},
{6,6,"wxSTC_ASM_CPUINSTRUCTION"},
{6,7,"wxSTC_ASM_MATHINSTRUCTION"},
{6,8,"wxSTC_ASM_REGISTER"},
{6,9,"wxSTC_ASM_DIRECTIVE"},
{6,10,"wxSTC_ASM_DIRECTIVEOPERAND"},
{6,11,"wxSTC_ASM_COMMENTBLOCK"},
{6,12,"wxSTC_ASM_CHARACTER"},
{6,13,"wxSTC_ASM_STRINGEOL"},
{6,14,"wxSTC_ASM_EXTINSTRUCTION"},
{6,15,"wxSTC_ASM_COMMENTDIRECTIVE"},
{7,0,"wxSTC_ASN1_DEFAULT"},
{7,1,"wxSTC_ASN1_COMMENT"},
{7,2,"wxSTC_ASN1_IDENTIFIER"},
{7,3,"wxSTC_ASN1_STRING"},
{7,4,"wxSTC_ASN1_OID"},
{7,5,"wxSTC_ASN1_SCALAR"},
{7,6,"wxSTC_ASN1_KEYWORD"},
{7,7,"wxSTC_ASN1_ATTRIBUTE"},
{7,8,"wxSTC_ASN1_DESCRIPTOR"},
{7,9,"wxSTC_ASN1_TYPE"},
{7,10,"wxSTC_ASN1_OPERATOR"},
{8,0,"wxSTC_ASY_DEFAULT"},
{8,1,"wxSTC_ASY_COMMENT"},
{8,2,"wxSTC_ASY_COMMENTLINE"},
{8,3,"wxSTC_ASY_NUMBER"},
{8,4,"wxSTC_ASY_WORD"},
{8,5,"wxSTC_ASY_STRING"},
{8,6,"wxSTC_ASY_CHARACTER"},
{8,7,"wxSTC_ASY_OPERATOR"},
{8,8,"wxSTC_ASY_IDENTIFIER"},
{8,9,"wxSTC_ASY_STRINGEOL"},
{8,10,"wxSTC_ASY_COMMENTLINEDOC"},
{8,11,"wxSTC_ASY_WORD2"},
{9,0,"wxSTC_AU3_DEFAULT"},
{9,1,"wxSTC_AU3_COMMENT"},
{9,2,"wxSTC_AU3_COMMENTBLOCK"},
{9,3,"wxSTC_AU3_NUMBER"},
{9,4,"wxSTC_AU3_FUNCTION"},
{9,5,"wxSTC_AU3_KEYWORD"},
{9,6,"wxSTC_AU3_MACRO"},
{9,7,"wxSTC_AU3_STRING"},
{9,8,"wxSTC_AU3_OPERATOR"},
{9,9,"wxSTC_AU3_VARIABLE"},
{9,10,"wxSTC_AU3_SENT"},
{9,11,"wxSTC_AU3_PREPROCESSOR"},
{9,12,"wxSTC_AU3_SPECIAL"},
{9,13,"wxSTC_AU3_EXPAND"},
{9,14,"wxSTC_AU3_COMOBJ"},
{9,15,"wxSTC_AU3_UDF"},
{10,0,"wxSTC_AVE_DEFAULT"},
{10,1,"wxSTC_AVE_COMMENT"},
{10,2,"wxSTC_AVE_NUMBER"},
{10,3,"wxSTC_AVE_WORD"},
{10,6,"wxSTC_AVE_STRING"},
{10,7,"wxSTC_AVE_ENUM"},
{10,8,"wxSTC_AVE_STRINGEOL"},
{10,9,"wxSTC_AVE_IDENTIFIER"},
{10,10,"wxSTC_AVE_OPERATOR"},
{10,11,"wxSTC_AVE_WORD1"},
{10,12,"wxSTC_AVE_WORD2"},
{10,13,"wxSTC_AVE_WORD3"},
{10,14,"wxSTC_AVE_WORD4"},
{10,15,"wxSTC_AVE_WORD5"},
{10,16,"wxSTC_AVE_WORD6"},
{11,0,"wxSTC_AVS_DEFAULT"},
{11,1,"wxSTC_AVS_COMMENTBLOCK"},
{11,2,"wxSTC_AVS_COMMENTBLOCKN"},
{11,3,"wxSTC_AVS_COMMENTLINE"},
{11,4,"wxSTC_AVS_NUMBER"},
{11,5,"wxSTC_AVS_OPERATOR"},
{11,6,"wxSTC_AVS_IDENTIFIER"},
{11,7,"wxSTC_AVS_STRING"},
{11,8,"wxSTC_AVS_TRIPLESTRING"},
{11,9,"wxSTC_AVS_KEYWORD"},
{11,10,"wxSTC_AVS_FILTER"},
{11,11,"wxSTC_AVS_PLUGIN"},
{11,12,"wxSTC_AVS_FUNCTION"},
{11,13,"wxSTC_AVS_CLIPPROP"},
{11,14,"wxSTC_AVS_USERDFN"},
{12,0,"wxSTC_B_DEFAULT"},
{12,1,"wxSTC_B_COMMENT"},
{12,2,"wxSTC_B_NUMBER"},
{12,3,"wxSTC_B_KEYWORD"},
{12,4,"wxSTC_B_STRING"},
{12,5,"wxSTC_B_PREPROCESSOR"},
{12,6,"wxSTC_B_OPERATOR"},
{12,7,"wxSTC_B_IDENTIFIER"},
{12,8,"wxSTC_B_DATE"},
{12,9,"wxSTC_B_STRINGEOL"},
{12,10,"wxSTC_B_KEYWORD2"},
{12,11,"wxSTC_B_KEYWORD3"},
{12,12,"wxSTC_B_KEYWORD4"},
{12,13,"wxSTC_B_CONSTANT"},
{12,14,"wxSTC_B_ASM"},
{12,15,"wxSTC_B_LABEL"},
{12,16,"wxSTC_B_ERROR"},
{12,17,"wxSTC_B_HEXNUMBER"},
{12,18,"wxSTC_B_BINNUMBER"},
{13,0,"wxSTC_BAAN_DEFAULT"},
{13,1,"wxSTC_BAAN_COMMENT"},
{13,2,"wxSTC_BAAN_COMMENTDOC"},
{13,3,"wxSTC_BAAN_NUMBER"},
{13,4,"wxSTC_BAAN_WORD"},
{13,5,"wxSTC_BAAN_STRING"},
{13,6,"wxSTC_BAAN_PREPROCESSOR"},
{13,7,"wxSTC_BAAN_OPERATOR"},
{13,8,"wxSTC_BAAN_IDENTIFIER"},
{13,9,"wxSTC_BAAN_STRINGEOL"},
{13,10,"wxSTC_BAAN_WORD2"},
{14,0,"wxSTC_BAT_DEFAULT"},
{14,1,"wxSTC_BAT_COMMENT"},
{14,2,"wxSTC_BAT_WORD"},
{14,3,"wxSTC_BAT_LABEL"},
{14,4,"wxSTC_BAT_HIDE"},
{14,5,"wxSTC_BAT_COMMAND"},
{14,6,"wxSTC_BAT_IDENTIFIER"},
{14,7,"wxSTC_BAT_OPERATOR"},
{15,0,"wxSTC_C_DEFAULT"},
{15,1,"wxSTC_C_COMMENT"},
{15,2,"wxSTC_C_COMMENTLINE"},
{15,3,"wxSTC_C_COMMENTDOC"},
{15,4,"wxSTC_C_NUMBER"},
{15,5,"wxSTC_C_WORD"},
{15,6,"wxSTC_C_STRING"},
{15,7,"wxSTC_C_CHARACTER"},
{15,8,"wxSTC_C_UUID"},
{15,9,"wxSTC_C_PREPROCESSOR"},
{15,10,"wxSTC_C_OPERATOR"},
{15,11,"wxSTC_C_IDENTIFIER"},
{15,12,"wxSTC_C_STRINGEOL"},
{15,13,"wxSTC_C_VERBATIM"},
{15,14,"wxSTC_C_REGEX"},
{15,15,"wxSTC_C_COMMENTLINEDOC"},
{15,16,"wxSTC_C_WORD2"},
{15,17,"wxSTC_C_COMMENTDOCKEYWORD"},
{15,18,"wxSTC_C_COMMENTDOCKEYWORDERROR"},
{15,19,"wxSTC_C_GLOBALCLASS"},
{15,20,"wxSTC_C_STRINGRAW"},
{15,21,"wxSTC_C_TRIPLEVERBATIM"},
{15,22,"wxSTC_C_HASHQUOTEDSTRING"},
{15,23,"wxSTC_C_PREPROCESSORCOMMENT"},
{16,0,"wxSTC_CAML_DEFAULT"},
{16,1,"wxSTC_CAML_IDENTIFIER"},
{16,2,"wxSTC_CAML_TAGNAME"},
{16,3,"wxSTC_CAML_KEYWORD"},
{16,4,"wxSTC_CAML_KEYWORD2"},
{16,5,"wxSTC_CAML_KEYWORD3"},
{16,6,"wxSTC_CAML_LINENUM"},
{16,7,"wxSTC_CAML_OPERATOR"},
{16,8,"wxSTC_CAML_NUMBER"},
{16,9,"wxSTC_CAML_CHAR"},
{16,10,"wxSTC_CAML_WHITE"},
{16,11,"wxSTC_CAML_STRING"},
{16,12,"wxSTC_CAML_COMMENT"},
{16,13,"wxSTC_CAML_COMMENT1"},
{16,14,"wxSTC_CAML_COMMENT2"},
{16,15,"wxSTC_CAML_COMMENT3"},
{17,0,"wxSTC_CLW_DEFAULT"},
{17,1,"wxSTC_CLW_LABEL"},
{17,2,"wxSTC_CLW_COMMENT"},
{17,3,"wxSTC_CLW_STRING"},
{17,4,"wxSTC_CLW_USER_IDENTIFIER"},
{17,5,"wxSTC_CLW_INTEGER_CONSTANT"},
{17,6,"wxSTC_CLW_REAL_CONSTANT"},
{17,7,"wxSTC_CLW_PICTURE_STRING"},
{17,8,"wxSTC_CLW_KEYWORD"},
{17,9,"wxSTC_CLW_COMPILER_DIRECTIVE"},
{17,10,"wxSTC_CLW_RUNTIME_EXPRESSIONS"},
{17,11,"wxSTC_CLW_BUILTIN_PROCEDURES_FUNCTION"},
{17,12,"wxSTC_CLW_STRUCTURE_DATA_TYPE"},
{17,13,"wxSTC_CLW_ATTRIBUTE"},
{17,14,"wxSTC_CLW_STANDARD_EQUATE"},
{17,15,"wxSTC_CLW_ERROR"},
{17,16,"wxSTC_CLW_DEPRECATED"},
{18,0,"wxSTC_CMAKE_DEFAULT"},
{18,1,"wxSTC_CMAKE_COMMENT"},
{18,2,"wxSTC_CMAKE_STRINGDQ"},
{18,3,"wxSTC_CMAKE_STRINGLQ"},
{18,4,"wxSTC_CMAKE_STRINGRQ"},
{18,5,"wxSTC_CMAKE_COMMANDS"},
{18,6,"wxSTC_CMAKE_PARAMETERS"},
{18,7,"wxSTC_CMAKE_VARIABLE"},
{18,8,"wxSTC_CMAKE_USERDEFINED"},
{18,9,"wxSTC_CMAKE_WHILEDEF"},
{18,10,"wxSTC_CMAKE_FOREACHDEF"},
{18,11,"wxSTC_CMAKE_IFDEFINEDEF"},
{18,12,"wxSTC_CMAKE_MACRODEF"},
{18,13,"wxSTC_CMAKE_STRINGVAR"},
{18,14,"wxSTC_CMAKE_NUMBER"},
{19,0,"wxSTC_COFFEESCRIPT_DEFAULT"},
{19,1,"wxSTC_COFFEESCRIPT_COMMENT"},
{19,2,"wxSTC_COFFEESCRIPT_COMMENTLINE"},
{19,3,"wxSTC_COFFEESCRIPT_COMMENTDOC"},
{19,4,"wxSTC_COFFEESCRIPT_NUMBER"},
{19,5,"wxSTC_COFFEESCRIPT_WORD"},
{19,6,"wxSTC_COFFEESCRIPT_STRING"},
{19,7,"wxSTC_COFFEESCRIPT_CHARACTER"},
{19,8,"wxSTC_COFFEESCRIPT_UUID"},
{19,9,"wxSTC_COFFEESCRIPT_PREPROCESSOR"},
{19,10,"wxSTC_COFFEESCRIPT_OPERATOR"},
{19,11,"wxSTC_COFFEESCRIPT_IDENTIFIER"},
{19,12,"wxSTC_COFFEESCRIPT_STRINGEOL"},
{19,13,"wxSTC_COFFEESCRIPT_VERBATIM"},
{19,14,"wxSTC_COFFEESCRIPT_REGEX"},
{19,15,"wxSTC_COFFEESCRIPT_COMMENTLINEDOC"},
{19,16,"wxSTC_COFFEESCRIPT_WORD2"},
{19,17,"wxSTC_COFFEESCRIPT_COMMENTDOCKEYWORD"},
{19,18,"wxSTC_COFFEESCRIPT_COMMENTDOCKEYWORDERROR"},
{19,19,"wxSTC_COFFEESCRIPT_GLOBALCLASS"},
{19,20,"wxSTC_COFFEESCRIPT_STRINGRAW"},
{19,21,"wxSTC_COFFEESCRIPT_TRIPLEVERBATIM"},
{19,22,"wxSTC_COFFEESCRIPT_HASHQUOTEDSTRING"},
{19,22,"wxSTC_COFFEESCRIPT_COMMENTBLOCK"},
{19,23,"wxSTC_COFFEESCRIPT_VERBOSE_REGEX"},
{19,24,"wxSTC_COFFEESCRIPT_VERBOSE_REGEX_COMMENT"},
{20,0,"wxSTC_CONF_DEFAULT"},
{20,1,"wxSTC_CONF_COMMENT"},
{20,2,"wxSTC_CONF_NUMBER"},
{20,3,"wxSTC_CONF_IDENTIFIER"},
{20,4,"wxSTC_CONF_EXTENSION"},
{20,5,"wxSTC_CONF_PARAMETER"},
{20,6,"wxSTC_CONF_STRING"},
{20,7,"wxSTC_CONF_OPERATOR"},
{20,8,"wxSTC_CONF_IP"},
{20,9,"wxSTC_CONF_DIRECTIVE"},
{21,0,"wxSTC_CSOUND_DEFAULT"},
{21,1,"wxSTC_CSOUND_COMMENT"},
{21,2,"wxSTC_CSOUND_NUMBER"},
{21,3,"wxSTC_CSOUND_OPERATOR"},
{21,4,"wxSTC_CSOUND_INSTR"},
{21,5,"wxSTC_CSOUND_IDENTIFIER"},
{21,6,"wxSTC_CSOUND_OPCODE"},
{21,7,"wxSTC_CSOUND_HEADERSTMT"},
{21,8,"wxSTC_CSOUND_USERKEYWORD"},
{21,9,"wxSTC_CSOUND_COMMENTBLOCK"},
{21,10,"wxSTC_CSOUND_PARAM"},
{21,11,"wxSTC_CSOUND_ARATE_VAR"},
{21,12,"wxSTC_CSOUND_KRATE_VAR"},
{21,13,"wxSTC_CSOUND_IRATE_VAR"},
{21,14,"wxSTC_CSOUND_GLOBAL_VAR"},
{21,15,"wxSTC_CSOUND_STRINGEOL"},
{22,0,"wxSTC_CSS_DEFAULT"},
{22,1,"wxSTC_CSS_TAG"},
{22,2,"wxSTC_CSS_CLASS"},
{22,3,"wxSTC_CSS_PSEUDOCLASS"},
{22,4,"wxSTC_CSS_UNKNOWN_PSEUDOCLASS"},
{22,5,"wxSTC_CSS_OPERATOR"},
{22,6,"wxSTC_CSS_IDENTIFIER"},
{22,7,"wxSTC_CSS_UNKNOWN_IDENTIFIER"},
{22,8,"wxSTC_CSS_VALUE"},
{22,9,"wxSTC_CSS_COMMENT"},
{22,10,"wxSTC_CSS_ID"},
{22,11,"wxSTC_CSS_IMPORTANT"},
{22,12,"wxSTC_CSS_DIRECTIVE"},
{22,13,"wxSTC_CSS_DOUBLESTRING"},
{22,14,"wxSTC_CSS_SINGLESTRING"},
{22,15,"wxSTC_CSS_IDENTIFIER2"},
{22,16,"wxSTC_CSS_ATTRIBUTE"},
{22,17,"wxSTC_CSS_IDENTIFIER3"},
{22,18,"wxSTC_CSS_PSEUDOELEMENT"},
{22,19,"wxSTC_CSS_EXTENDED_IDENTIFIER"},
{22,20,"wxSTC_CSS_EXTENDED_PSEUDOCLASS"},
{22,21,"wxSTC_CSS_EXTENDED_PSEUDOELEMENT"},
{22,22,"wxSTC_CSS_MEDIA"},
{22,23,"wxSTC_CSS_VARIABLE"},
{23,0,"wxSTC_D_DEFAULT"},
{23,1,"wxSTC_D_COMMENT"},
{23,2,"wxSTC_D_COMMENTLINE"},
{23,3,"wxSTC_D_COMMENTDOC"},
{23,4,"wxSTC_D_COMMENTNESTED"},
{23,5,"wxSTC_D_NUMBER"},
{23,6,"wxSTC_D_WORD"},
{23,7,"wxSTC_D_WORD2"},
{23,8,"wxSTC_D_WORD3"},
{23,9,"wxSTC_D_TYPEDEF"},
{23,10,"wxSTC_D_STRING"},
{23,11,"wxSTC_D_STRINGEOL"},
{23,12,"wxSTC_D_CHARACTER"},
{23,13,"wxSTC_D_OPERATOR"},
{23,14,"wxSTC_D_IDENTIFIER"},
{23,15,"wxSTC_D_COMMENTLINEDOC"},
{23,16,"wxSTC_D_COMMENTDOCKEYWORD"},
{23,17,"wxSTC_D_COMMENTDOCKEYWORDERROR"},
{23,18,"wxSTC_D_STRINGB"},
{23,19,"wxSTC_D_STRINGR"},
{23,20,"wxSTC_D_WORD5"},
{23,21,"wxSTC_D_WORD6"},
{23,22,"wxSTC_D_WORD7"},
{24,0,"wxSTC_DIFF_DEFAULT"},
{24,1,"wxSTC_DIFF_COMMENT"},
{24,2,"wxSTC_DIFF_COMMAND"},
{24,3,"wxSTC_DIFF_HEADER"},
{24,4,"wxSTC_DIFF_POSITION"},
{24,5,"wxSTC_DIFF_DELETED"},
{24,6,"wxSTC_DIFF_ADDED"},
{24,7,"wxSTC_DIFF_CHANGED"},
{25,0,"wxSTC_ECL_DEFAULT"},
{25,1,"wxSTC_ECL_COMMENT"},
{25,2,"wxSTC_ECL_COMMENTLINE"},
{25,3,"wxSTC_ECL_NUMBER"},
{25,4,"wxSTC_ECL_STRING"},
{25,5,"wxSTC_ECL_WORD0"},
{25,6,"wxSTC_ECL_OPERATOR"},
{25,7,"wxSTC_ECL_CHARACTER"},
{25,8,"wxSTC_ECL_UUID"},
{25,9,"wxSTC_ECL_PREPROCESSOR"},
{25,10,"wxSTC_ECL_UNKNOWN"},
{25,11,"wxSTC_ECL_IDENTIFIER"},
{25,12,"wxSTC_ECL_STRINGEOL"},
{25,13,"wxSTC_ECL_VERBATIM"},
{25,14,"wxSTC_ECL_REGEX"},
{25,15,"wxSTC_ECL_COMMENTLINEDOC"},
{25,16,"wxSTC_ECL_WORD1"},
{25,17,"wxSTC_ECL_COMMENTDOCKEYWORD"},
{25,18,"wxSTC_ECL_COMMENTDOCKEYWORDERROR"},
{25,19,"wxSTC_ECL_WORD2"},
{25,20,"wxSTC_ECL_WORD3"},
{25,21,"wxSTC_ECL_WORD4"},
{25,22,"wxSTC_ECL_WORD5"},
{25,23,"wxSTC_ECL_COMMENTDOC"},
{25,24,"wxSTC_ECL_ADDED"},
{25,25,"wxSTC_ECL_DELETED"},
{25,26,"wxSTC_ECL_CHANGED"},
{25,27,"wxSTC_ECL_MOVED"},
{26,0,"wxSTC_EIFFEL_DEFAULT"},
{26,1,"wxSTC_EIFFEL_COMMENTLINE"},
{26,2,"wxSTC_EIFFEL_NUMBER"},
{26,3,"wxSTC_EIFFEL_WORD"},
{26,4,"wxSTC_EIFFEL_STRING"},
{26,5,"wxSTC_EIFFEL_CHARACTER"},
{26,6,"wxSTC_EIFFEL_OPERATOR"},
{26,7,"wxSTC_EIFFEL_IDENTIFIER"},
{26,8,"wxSTC_EIFFEL_STRINGEOL"},
{27,0,"wxSTC_ERLANG_DEFAULT"},
{27,1,"wxSTC_ERLANG_COMMENT"},
{27,2,"wxSTC_ERLANG_VARIABLE"},
{27,3,"wxSTC_ERLANG_NUMBER"},
{27,4,"wxSTC_ERLANG_KEYWORD"},
{27,5,"wxSTC_ERLANG_STRING"},
{27,6,"wxSTC_ERLANG_OPERATOR"},
{27,7,"wxSTC_ERLANG_ATOM"},
{27,8,"wxSTC_ERLANG_FUNCTION_NAME"},
{27,9,"wxSTC_ERLANG_CHARACTER"},
{27,10,"wxSTC_ERLANG_MACRO"},
{27,11,"wxSTC_ERLANG_RECORD"},
{27,12,"wxSTC_ERLANG_PREPROC"},
{27,13,"wxSTC_ERLANG_NODE_NAME"},
{27,14,"wxSTC_ERLANG_COMMENT_FUNCTION"},
{27,15,"wxSTC_ERLANG_COMMENT_MODULE"},
{27,16,"wxSTC_ERLANG_COMMENT_DOC"},
{27,17,"wxSTC_ERLANG_COMMENT_DOC_MACRO"},
{27,18,"wxSTC_ERLANG_ATOM_QUOTED"},
{27,19,"wxSTC_ERLANG_MACRO_QUOTED"},
{27,20,"wxSTC_ERLANG_RECORD_QUOTED"},
{27,21,"wxSTC_ERLANG_NODE_NAME_QUOTED"},
{27,22,"wxSTC_ERLANG_BIFS"},
{27,23,"wxSTC_ERLANG_MODULES"},
{27,24,"wxSTC_ERLANG_MODULES_ATT"},
{27,31,"wxSTC_ERLANG_UNKNOWN"},
{28,0,"wxSTC_ERR_DEFAULT"},
{28,1,"wxSTC_ERR_PYTHON"},
{28,2,"wxSTC_ERR_GCC"},
{28,3,"wxSTC_ERR_MS"},
{28,4,"wxSTC_ERR_CMD"},
{28,5,"wxSTC_ERR_BORLAND"},
{28,6,"wxSTC_ERR_PERL"},
{28,7,"wxSTC_ERR_NET"},
{28,8,"wxSTC_ERR_LUA"},
{28,9,"wxSTC_ERR_CTAG"},
{28,10,"wxSTC_ERR_DIFF_CHANGED"},
{28,11,"wxSTC_ERR_DIFF_ADDITION"},
{28,12,"wxSTC_ERR_DIFF_DELETION"},
{28,13,"wxSTC_ERR_DIFF_MESSAGE"},
{28,14,"wxSTC_ERR_PHP"},
{28,15,"wxSTC_ERR_ELF"},
{28,16,"wxSTC_ERR_IFC"},
{28,17,"wxSTC_ERR_IFORT"},
{28,18,"wxSTC_ERR_ABSF"},
{28,19,"wxSTC_ERR_TIDY"},
{28,20,"wxSTC_ERR_JAVA_STACK"},
{28,21,"wxSTC_ERR_VALUE"},
{29,0,"wxSTC_ESCRIPT_DEFAULT"},
{29,1,"wxSTC_ESCRIPT_COMMENT"},
{29,2,"wxSTC_ESCRIPT_COMMENTLINE"},
{29,3,"wxSTC_ESCRIPT_COMMENTDOC"},
{29,4,"wxSTC_ESCRIPT_NUMBER"},
{29,5,"wxSTC_ESCRIPT_WORD"},
{29,6,"wxSTC_ESCRIPT_STRING"},
{29,7,"wxSTC_ESCRIPT_OPERATOR"},
{29,8,"wxSTC_ESCRIPT_IDENTIFIER"},
{29,9,"wxSTC_ESCRIPT_BRACE"},
{29,10,"wxSTC_ESCRIPT_WORD2"},
{29,11,"wxSTC_ESCRIPT_WORD3"},
{30,0,"wxSTC_F_DEFAULT"},
{30,1,"wxSTC_F_COMMENT"},
{30,2,"wxSTC_F_NUMBER"},
{30,3,"wxSTC_F_STRING1"},
{30,4,"wxSTC_F_STRING2"},
{30,5,"wxSTC_F_STRINGEOL"},
{30,6,"wxSTC_F_OPERATOR"},
{30,7,"wxSTC_F_IDENTIFIER"},
{30,8,"wxSTC_F_WORD"},
{30,9,"wxSTC_F_WORD2"},
{30,10,"wxSTC_F_WORD3"},
{30,11,"wxSTC_F_PREPROCESSOR"},
{30,12,"wxSTC_F_OPERATOR2"},
{30,13,"wxSTC_F_LABEL"},
{30,14,"wxSTC_F_CONTINUATION"},
{31,0,"wxSTC_FORTH_DEFAULT"},
{31,1,"wxSTC_FORTH_COMMENT"},
{31,2,"wxSTC_FORTH_COMMENT_ML"},
{31,3,"wxSTC_FORTH_IDENTIFIER"},
{31,4,"wxSTC_FORTH_CONTROL"},
{31,5,"wxSTC_FORTH_KEYWORD"},
{31,6,"wxSTC_FORTH_DEFWORD"},
{31,7,"wxSTC_FORTH_PREWORD1"},
{31,8,"wxSTC_FORTH_PREWORD2"},
{31,9,"wxSTC_FORTH_NUMBER"},
{31,10,"wxSTC_FORTH_STRING"},
{31,11,"wxSTC_FORTH_LOCALE"},
{32,0,"wxSTC_FS_DEFAULT"},
{32,1,"wxSTC_FS_COMMENT"},
{32,2,"wxSTC_FS_COMMENTLINE"},
{32,3,"wxSTC_FS_COMMENTDOC"},
{32,4,"wxSTC_FS_COMMENTLINEDOC"},
{32,5,"wxSTC_FS_COMMENTDOCKEYWORD"},
{32,6,"wxSTC_FS_COMMENTDOCKEYWORDERROR"},
{32,7,"wxSTC_FS_KEYWORD"},
{32,8,"wxSTC_FS_KEYWORD2"},
{32,9,"wxSTC_FS_KEYWORD3"},
{32,10,"wxSTC_FS_KEYWORD4"},
{32,11,"wxSTC_FS_NUMBER"},
{32,12,"wxSTC_FS_STRING"},
{32,13,"wxSTC_FS_PREPROCESSOR"},
{32,14,"wxSTC_FS_OPERATOR"},
{32,15,"wxSTC_FS_IDENTIFIER"},
{32,16,"wxSTC_FS_DATE"},
{32,17,"wxSTC_FS_STRINGEOL"},
{32,18,"wxSTC_FS_CONSTANT"},
{32,19,"wxSTC_FS_WORDOPERATOR"},
{32,20,"wxSTC_FS_DISABLEDCODE"},
{32,21,"wxSTC_FS_DEFAULT_C"},
{32,22,"wxSTC_FS_COMMENTDOC_C"},
{32,23,"wxSTC_FS_COMMENTLINEDOC_C"},
{32,24,"wxSTC_FS_KEYWORD_C"},
{32,25,"wxSTC_FS_KEYWORD2_C"},
{32,26,"wxSTC_FS_NUMBER_C"},
{32,27,"wxSTC_FS_STRING_C"},
{32,28,"wxSTC_FS_PREPROCESSOR_C"},
{32,29,"wxSTC_FS_OPERATOR_C"},
{32,30,"wxSTC_FS_IDENTIFIER_C"},
{32,31,"wxSTC_FS_STRINGEOL_C"},
{33,0,"wxSTC_GAP_DEFAULT"},
{33,1,"wxSTC_GAP_IDENTIFIER"},
{33,2,"wxSTC_GAP_KEYWORD"},
{33,3,"wxSTC_GAP_KEYWORD2"},
{33,4,"wxSTC_GAP_KEYWORD3"},
{33,5,"wxSTC_GAP_KEYWORD4"},
{33,6,"wxSTC_GAP_STRING"},
{33,7,"wxSTC_GAP_CHAR"},
{33,8,"wxSTC_GAP_OPERATOR"},
{33,9,"wxSTC_GAP_COMMENT"},
{33,10,"wxSTC_GAP_NUMBER"},
{33,11,"wxSTC_GAP_STRINGEOL"},
{34,0,"wxSTC_GC_DEFAULT"},
{34,1,"wxSTC_GC_COMMENTLINE"},
{34,2,"wxSTC_GC_COMMENTBLOCK"},
{34,3,"wxSTC_GC_GLOBAL"},
{34,4,"wxSTC_GC_EVENT"},
{34,5,"wxSTC_GC_ATTRIBUTE"},
{34,6,"wxSTC_GC_CONTROL"},
{34,7,"wxSTC_GC_COMMAND"},
{34,8,"wxSTC_GC_STRING"},
{34,9,"wxSTC_GC_OPERATOR"},
{35,0,"wxSTC_H_DEFAULT"},
{35,1,"wxSTC_H_TAG"},
{35,2,"wxSTC_H_TAGUNKNOWN"},
{35,3,"wxSTC_H_ATTRIBUTE"},
{35,4,"wxSTC_H_ATTRIBUTEUNKNOWN"},
{35,5,"wxSTC_H_NUMBER"},
{35,6,"wxSTC_H_DOUBLESTRING"},
{35,7,"wxSTC_H_SINGLESTRING"},
{35,8,"wxSTC_H_OTHER"},
{35,9,"wxSTC_H_COMMENT"},
{35,10,"wxSTC_H_ENTITY"},
{35,11,"wxSTC_H_TAGEND"},
{35,12,"wxSTC_H_XMLSTART"},
{35,13,"wxSTC_H_XMLEND"},
{35,14,"wxSTC_H_SCRIPT"},
{35,15,"wxSTC_H_ASP"},
{35,16,"wxSTC_H_ASPAT"},
{35,17,"wxSTC_H_CDATA"},
{35,18,"wxSTC_H_QUESTION"},
{35,19,"wxSTC_H_VALUE"},
{35,20,"wxSTC_H_XCCOMMENT"},
{35,21,"wxSTC_H_SGML_DEFAULT"},
{35,22,"wxSTC_H_SGML_COMMAND"},
{35,23,"wxSTC_H_SGML_1ST_PARAM"},
{35,24,"wxSTC_H_SGML_DOUBLESTRING"},
{35,25,"wxSTC_H_SGML_SIMPLESTRING"},
{35,26,"wxSTC_H_SGML_ERROR"},
{35,27,"wxSTC_H_SGML_SPECIAL"},
{35,28,"wxSTC_H_SGML_ENTITY"},
{35,29,"wxSTC_H_SGML_COMMENT"},
{35,30,"wxSTC_H_SGML_1ST_PARAM_COMMENT"},
{35,31,"wxSTC_H_SGML_BLOCK_DEFAULT"},
{35,40,"wxSTC_HJ_START"},
{35,41,"wxSTC_HJ_DEFAULT"},
{35,42,"wxSTC_HJ_COMMENT"},
{35,43,"wxSTC_HJ_COMMENTLINE"},
{35,44,"wxSTC_HJ_COMMENTDOC"},
{35,45,"wxSTC_HJ_NUMBER"},
{35,46,"wxSTC_HJ_WORD"},
{35,47,"wxSTC_HJ_KEYWORD"},
{35,48,"wxSTC_HJ_DOUBLESTRING"},
{35,49,"wxSTC_HJ_SINGLESTRING"},
{35,50,"wxSTC_HJ_SYMBOLS"},
{35,51,"wxSTC_HJ_STRINGEOL"},
{35,52,"wxSTC_HJ_REGEX"},
{35,55,"wxSTC_HJA_START"},
{35,56,"wxSTC_HJA_DEFAULT"},
{35,57,"wxSTC_HJA_COMMENT"},
{35,58,"wxSTC_HJA_COMMENTLINE"},
{35,59,"wxSTC_HJA_COMMENTDOC"},
{35,60,"wxSTC_HJA_NUMBER"},
{35,61,"wxSTC_HJA_WORD"},
{35,62,"wxSTC_HJA_KEYWORD"},
{35,63,"wxSTC_HJA_DOUBLESTRING"},
{35,64,"wxSTC_HJA_SINGLESTRING"},
{35,65,"wxSTC_HJA_SYMBOLS"},
{35,66,"wxSTC_HJA_STRINGEOL"},
{35,67,"wxSTC_HJA_REGEX"},
{35,70,"wxSTC_HB_START"},
{35,71,"wxSTC_HB_DEFAULT"},
{35,72,"wxSTC_HB_COMMENTLINE"},
{35,73,"wxSTC_HB_NUMBER"},
{35,74,"wxSTC_HB_WORD"},
{35,75,"wxSTC_HB_STRING"},
{35,76,"wxSTC_HB_IDENTIFIER"},
{35,77,"wxSTC_HB_STRINGEOL"},
{35,80,"wxSTC_HBA_START"},
{35,81,"wxSTC_HBA_DEFAULT"},
{35,82,"wxSTC_HBA_COMMENTLINE"},
{35,83,"wxSTC_HBA_NUMBER"},
{35,84,"wxSTC_HBA_WORD"},
{35,85,"wxSTC_HBA_STRING"},
{35,86,"wxSTC_HBA_IDENTIFIER"},
{35,87,"wxSTC_HBA_STRINGEOL"},
{35,90,"wxSTC_HP_START"},
{35,91,"wxSTC_HP_DEFAULT"},
{35,92,"wxSTC_HP_COMMENTLINE"},
{35,93,"wxSTC_HP_NUMBER"},
{35,94,"wxSTC_HP_STRING"},
{35,95,"wxSTC_HP_CHARACTER"},
{35,96,"wxSTC_HP_WORD"},
{35,97,"wxSTC_HP_TRIPLE"},
{35,98,"wxSTC_HP_TRIPLEDOUBLE"},
{35,99,"wxSTC_HP_CLASSNAME"},
{35,100,"wxSTC_HP_DEFNAME"},
{35,101,"wxSTC_HP_OPERATOR"},
{35,102,"wxSTC_HP_IDENTIFIER"},
{35,104,"wxSTC_HPHP_COMPLEX_VARIABLE"},
{35,105,"wxSTC_HPA_START"},
{35,106,"wxSTC_HPA_DEFAULT"},
{35,107,"wxSTC_HPA_COMMENTLINE"},
{35,108,"wxSTC_HPA_NUMBER"},
{35,109,"wxSTC_HPA_STRING"},
{35,110,"wxSTC_HPA_CHARACTER"},
{35,111,"wxSTC_HPA_WORD"},
{35,112,"wxSTC_HPA_TRIPLE"},
{35,113,"wxSTC_HPA_TRIPLEDOUBLE"},
{35,114,"wxSTC_HPA_CLASSNAME"},
{35,115,"wxSTC_HPA_DEFNAME"},
{35,116,"wxSTC_HPA_OPERATOR"},
{35,117,"wxSTC_HPA_IDENTIFIER"},
{35,118,"wxSTC_HPHP_DEFAULT"},
{35,119,"wxSTC_HPHP_HSTRING"},
{35,120,"wxSTC_HPHP_SIMPLESTRING"},
{35,121,"wxSTC_HPHP_WORD"},
{35,122,"wxSTC_HPHP_NUMBER"},
{35,123,"wxSTC_HPHP_VARIABLE"},
{35,124,"wxSTC_HPHP_COMMENT"},
{35,125,"wxSTC_HPHP_COMMENTLINE"},
{35,126,"wxSTC_HPHP_HSTRING_VARIABLE"},
{35,127,"wxSTC_HPHP_OPERATOR"},
{36,0,"wxSTC_HA_DEFAULT"},
{36,1,"wxSTC_HA_IDENTIFIER"},
{36,2,"wxSTC_HA_KEYWORD"},
{36,3,"wxSTC_HA_NUMBER"},
{36,4,"wxSTC_HA_STRING"},
{36,5,"wxSTC_HA_CHARACTER"},
{36,6,"wxSTC_HA_CLASS"},
{36,7,"wxSTC_HA_MODULE"},
{36,8,"wxSTC_HA_CAPITAL"},
{36,9,"wxSTC_HA_DATA"},
{36,10,"wxSTC_HA_IMPORT"},
{36,11,"wxSTC_HA_OPERATOR"},
{36,12,"wxSTC_HA_INSTANCE"},
{36,13,"wxSTC_HA_COMMENTLINE"},
{36,14,"wxSTC_HA_COMMENTBLOCK"},
{36,15,"wxSTC_HA_COMMENTBLOCK2"},
{36,16,"wxSTC_HA_COMMENTBLOCK3"},
{37,0,"wxSTC_INNO_DEFAULT"},
{37,1,"wxSTC_INNO_COMMENT"},
{37,2,"wxSTC_INNO_KEYWORD"},
{37,3,"wxSTC_INNO_PARAMETER"},
{37,4,"wxSTC_INNO_SECTION"},
{37,5,"wxSTC_INNO_PREPROC"},
{37,6,"wxSTC_INNO_INLINE_EXPANSION"},
{37,7,"wxSTC_INNO_COMMENT_PASCAL"},
{37,8,"wxSTC_INNO_KEYWORD_PASCAL"},
{37,9,"wxSTC_INNO_KEYWORD_USER"},
{37,10,"wxSTC_INNO_STRING_DOUBLE"},
{37,11,"wxSTC_INNO_STRING_SINGLE"},
{37,12,"wxSTC_INNO_IDENTIFIER"},
{38,0,"wxSTC_KIX_DEFAULT"},
{38,1,"wxSTC_KIX_COMMENT"},
{38,2,"wxSTC_KIX_STRING1"},
{38,3,"wxSTC_KIX_STRING2"},
{38,4,"wxSTC_KIX_NUMBER"},
{38,5,"wxSTC_KIX_VAR"},
{38,6,"wxSTC_KIX_MACRO"},
{38,7,"wxSTC_KIX_KEYWORD"},
{38,8,"wxSTC_KIX_FUNCTIONS"},
{38,9,"wxSTC_KIX_OPERATOR"},
{38,31,"wxSTC_KIX_IDENTIFIER"},
{39,0,"wxSTC_L_DEFAULT"},
{39,1,"wxSTC_L_COMMAND"},
{39,2,"wxSTC_L_TAG"},
{39,3,"wxSTC_L_MATH"},
{39,4,"wxSTC_L_COMMENT"},
{39,5,"wxSTC_L_TAG2"},
{39,6,"wxSTC_L_MATH2"},
{39,7,"wxSTC_L_COMMENT2"},
{39,8,"wxSTC_L_VERBATIM"},
{39,9,"wxSTC_L_SHORTCMD"},
{39,10,"wxSTC_L_SPECIAL"},
{39,11,"wxSTC_L_CMDOPT"},
{39,12,"wxSTC_L_ERROR"},
{40,0,"wxSTC_LISP_DEFAULT"},
{40,1,"wxSTC_LISP_COMMENT"},
{40,2,"wxSTC_LISP_NUMBER"},
{40,3,"wxSTC_LISP_KEYWORD"},
{40,4,"wxSTC_LISP_KEYWORD_KW"},
{40,5,"wxSTC_LISP_SYMBOL"},
{40,6,"wxSTC_LISP_STRING"},
{40,8,"wxSTC_LISP_STRINGEOL"},
{40,9,"wxSTC_LISP_IDENTIFIER"},
{40,10,"wxSTC_LISP_OPERATOR"},
{40,11,"wxSTC_LISP_SPECIAL"},
{40,12,"wxSTC_LISP_MULTI_COMMENT"},
{41,0,"wxSTC_LOT_DEFAULT"},
{41,1,"wxSTC_LOT_HEADER"},
{41,2,"wxSTC_LOT_BREAK"},
{41,3,"wxSTC_LOT_SET"},
{41,4,"wxSTC_LOT_PASS"},
{41,5,"wxSTC_LOT_FAIL"},
{41,6,"wxSTC_LOT_ABORT"},
{42,0,"wxSTC_LOUT_DEFAULT"},
{42,1,"wxSTC_LOUT_COMMENT"},
{42,2,"wxSTC_LOUT_NUMBER"},
{42,3,"wxSTC_LOUT_WORD"},
{42,4,"wxSTC_LOUT_WORD2"},
{42,5,"wxSTC_LOUT_WORD3"},
{42,6,"wxSTC_LOUT_WORD4"},
{42,7,"wxSTC_LOUT_STRING"},
{42,8,"wxSTC_LOUT_OPERATOR"},
{42,9,"wxSTC_LOUT_IDENTIFIER"},
{42,10,"wxSTC_LOUT_STRINGEOL"},
{43,0,"wxSTC_LUA_DEFAULT"},
{43,1,"wxSTC_LUA_COMMENT"},
{43,2,"wxSTC_LUA_COMMENTLINE"},
{43,3,"wxSTC_LUA_COMMENTDOC"},
{43,4,"wxSTC_LUA_NUMBER"},
{43,5,"wxSTC_LUA_WORD"},
{43,6,"wxSTC_LUA_STRING"},
{43,7,"wxSTC_LUA_CHARACTER"},
{43,8,"wxSTC_LUA_LITERALSTRING"},
{43,9,"wxSTC_LUA_PREPROCESSOR"},
{43,10,"wxSTC_LUA_OPERATOR"},
{43,11,"wxSTC_LUA_IDENTIFIER"},
{43,12,"wxSTC_LUA_STRINGEOL"},
{43,13,"wxSTC_LUA_WORD2"},
{43,14,"wxSTC_LUA_WORD3"},
{43,15,"wxSTC_LUA_WORD4"},
{43,16,"wxSTC_LUA_WORD5"},
{43,17,"wxSTC_LUA_WORD6"},
{43,18,"wxSTC_LUA_WORD7"},
{43,19,"wxSTC_LUA_WORD8"},
{43,20,"wxSTC_LUA_LABEL"},
{44,0,"wxSTC_MAGIK_DEFAULT"},
{44,1,"wxSTC_MAGIK_COMMENT"},
{44,2,"wxSTC_MAGIK_STRING"},
{44,3,"wxSTC_MAGIK_CHARACTER"},
{44,4,"wxSTC_MAGIK_NUMBER"},
{44,5,"wxSTC_MAGIK_IDENTIFIER"},
{44,6,"wxSTC_MAGIK_OPERATOR"},
{44,7,"wxSTC_MAGIK_FLOW"},
{44,8,"wxSTC_MAGIK_CONTAINER"},
{44,9,"wxSTC_MAGIK_BRACKET_BLOCK"},
{44,10,"wxSTC_MAGIK_BRACE_BLOCK"},
{44,11,"wxSTC_MAGIK_SQBRACKET_BLOCK"},
{44,12,"wxSTC_MAGIK_UNKNOWN_KEYWORD"},
{44,13,"wxSTC_MAGIK_KEYWORD"},
{44,14,"wxSTC_MAGIK_PRAGMA"},
{44,15,"wxSTC_MAGIK_SYMBOL"},
{44,16,"wxSTC_MAGIK_HYPER_COMMENT"},
{45,0,"wxSTC_MAKE_DEFAULT"},
{45,1,"wxSTC_MAKE_COMMENT"},
{45,2,"wxSTC_MAKE_PREPROCESSOR"},
{45,3,"wxSTC_MAKE_IDENTIFIER"},
{45,4,"wxSTC_MAKE_OPERATOR"},
{45,5,"wxSTC_MAKE_TARGET"},
{45,9,"wxSTC_MAKE_IDEOL"},
{46,0,"wxSTC_MARKDOWN_DEFAULT"},
{46,1,"wxSTC_MARKDOWN_LINE_BEGIN"},
{46,2,"wxSTC_MARKDOWN_STRONG1"},
{46,3,"wxSTC_MARKDOWN_STRONG2"},
{46,4,"wxSTC_MARKDOWN_EM1"},
{46,5,"wxSTC_MARKDOWN_EM2"},
{46,6,"wxSTC_MARKDOWN_HEADER1"},
{46,7,"wxSTC_MARKDOWN_HEADER2"},
{46,8,"wxSTC_MARKDOWN_HEADER3"},
{46,9,"wxSTC_MARKDOWN_HEADER4"},
{46,10,"wxSTC_MARKDOWN_HEADER5"},
{46,11,"wxSTC_MARKDOWN_HEADER6"},
{46,12,"wxSTC_MARKDOWN_PRECHAR"},
{46,13,"wxSTC_MARKDOWN_ULIST_ITEM"},
{46,14,"wxSTC_MARKDOWN_OLIST_ITEM"},
{46,15,"wxSTC_MARKDOWN_BLOCKQUOTE"},
{46,16,"wxSTC_MARKDOWN_STRIKEOUT"},
{46,17,"wxSTC_MARKDOWN_HRULE"},
{46,18,"wxSTC_MARKDOWN_LINK"},
{46,19,"wxSTC_MARKDOWN_CODE"},
{46,20,"wxSTC_MARKDOWN_CODE2"},
{46,21,"wxSTC_MARKDOWN_CODEBK"},
{47,0,"wxSTC_MATLAB_DEFAULT"},
{47,1,"wxSTC_MATLAB_COMMENT"},
{47,2,"wxSTC_MATLAB_COMMAND"},
{47,3,"wxSTC_MATLAB_NUMBER"},
{47,4,"wxSTC_MATLAB_KEYWORD"},
{47,5,"wxSTC_MATLAB_STRING"},
{47,6,"wxSTC_MATLAB_OPERATOR"},
{47,7,"wxSTC_MATLAB_IDENTIFIER"},
{47,8,"wxSTC_MATLAB_DOUBLEQUOTESTRING"},
{48,0,"wxSTC_METAPOST_DEFAULT"},
{48,1,"wxSTC_METAPOST_SPECIAL"},
{48,2,"wxSTC_METAPOST_GROUP"},
{48,3,"wxSTC_METAPOST_SYMBOL"},
{48,4,"wxSTC_METAPOST_COMMAND"},
{48,5,"wxSTC_METAPOST_TEXT"},
{48,6,"wxSTC_METAPOST_EXTRA"},
{49,0,"wxSTC_MMIXAL_LEADWS"},
{49,1,"wxSTC_MMIXAL_COMMENT"},
{49,2,"wxSTC_MMIXAL_LABEL"},
{49,3,"wxSTC_MMIXAL_OPCODE"},
{49,4,"wxSTC_MMIXAL_OPCODE_PRE"},
{49,5,"wxSTC_MMIXAL_OPCODE_VALID"},
{49,6,"wxSTC_MMIXAL_OPCODE_UNKNOWN"},
{49,7,"wxSTC_MMIXAL_OPCODE_POST"},
{49,8,"wxSTC_MMIXAL_OPERANDS"},
{49,9,"wxSTC_MMIXAL_NUMBER"},
{49,10,"wxSTC_MMIXAL_REF"},
{49,11,"wxSTC_MMIXAL_CHAR"},
{49,12,"wxSTC_MMIXAL_STRING"},
{49,13,"wxSTC_MMIXAL_REGISTER"},
{49,14,"wxSTC_MMIXAL_HEX"},
{49,15,"wxSTC_MMIXAL_OPERATOR"},
{49,16,"wxSTC_MMIXAL_SYMBOL"},
{49,17,"wxSTC_MMIXAL_INCLUDE"},
{50,0,"wxSTC_MODULA_DEFAULT"},
{50,1,"wxSTC_MODULA_COMMENT"},
{50,2,"wxSTC_MODULA_DOXYCOMM"},
{50,3,"wxSTC_MODULA_DOXYKEY"},
{50,4,"wxSTC_MODULA_KEYWORD"},
{50,5,"wxSTC_MODULA_RESERVED"},
{50,6,"wxSTC_MODULA_NUMBER"},
{50,7,"wxSTC_MODULA_BASENUM"},
{50,8,"wxSTC_MODULA_FLOAT"},
{50,9,"wxSTC_MODULA_STRING"},
{50,10,"wxSTC_MODULA_STRSPEC"},
{50,11,"wxSTC_MODULA_CHAR"},
{50,12,"wxSTC_MODULA_CHARSPEC"},
{50,13,"wxSTC_MODULA_PROC"},
{50,14,"wxSTC_MODULA_PRAGMA"},
{50,15,"wxSTC_MODULA_PRGKEY"},
{50,16,"wxSTC_MODULA_OPERATOR"},
{50,17,"wxSTC_MODULA_BADSTR"},
{51,0,"wxSTC_MSSQL_DEFAULT"},
{51,1,"wxSTC_MSSQL_COMMENT"},
{51,2,"wxSTC_MSSQL_LINE_COMMENT"},
{51,3,"wxSTC_MSSQL_NUMBER"},
{51,4,"wxSTC_MSSQL_STRING"},
{51,5,"wxSTC_MSSQL_OPERATOR"},
{51,6,"wxSTC_MSSQL_IDENTIFIER"},
{51,7,"wxSTC_MSSQL_VARIABLE"},
{51,8,"wxSTC_MSSQL_COLUMN_NAME"},
{51,9,"wxSTC_MSSQL_STATEMENT"},
{51,10,"wxSTC_MSSQL_DATATYPE"},
{51,11,"wxSTC_MSSQL_SYSTABLE"},
{51,12,"wxSTC_MSSQL_GLOBAL_VARIABLE"},
{51,13,"wxSTC_MSSQL_FUNCTION"},
{51,14,"wxSTC_MSSQL_STORED_PROCEDURE"},
{51,15,"wxSTC_MSSQL_DEFAULT_PREF_DATATYPE"},
{51,16,"wxSTC_MSSQL_COLUMN_NAME_2"},
{52,0,"wxSTC_MYSQL_DEFAULT"},
{52,1,"wxSTC_MYSQL_COMMENT"},
{52,2,"wxSTC_MYSQL_COMMENTLINE"},
{52,3,"wxSTC_MYSQL_VARIABLE"},
{52,4,"wxSTC_MYSQL_SYSTEMVARIABLE"},
{52,5,"wxSTC_MYSQL_KNOWNSYSTEMVARIABLE"},
{52,6,"wxSTC_MYSQL_NUMBER"},
{52,7,"wxSTC_MYSQL_MAJORKEYWORD"},
{52,8,"wxSTC_MYSQL_KEYWORD"},
{52,9,"wxSTC_MYSQL_DATABASEOBJECT"},
{52,10,"wxSTC_MYSQL_PROCEDUREKEYWORD"},
{52,11,"wxSTC_MYSQL_STRING"},
{52,12,"wxSTC_MYSQL_SQSTRING"},
{52,13,"wxSTC_MYSQL_DQSTRING"},
{52,14,"wxSTC_MYSQL_OPERATOR"},
{52,15,"wxSTC_MYSQL_FUNCTION"},
{52,16,"wxSTC_MYSQL_IDENTIFIER"},
{52,17,"wxSTC_MYSQL_QUOTEDIDENTIFIER"},
{52,18,"wxSTC_MYSQL_USER1"},
{52,19,"wxSTC_MYSQL_USER2"},
{52,20,"wxSTC_MYSQL_USER3"},
{52,21,"wxSTC_MYSQL_HIDDENCOMMAND"},
{53,0,"wxSTC_NNCRONTAB_DEFAULT"},
{53,1,"wxSTC_NNCRONTAB_COMMENT"},
{53,2,"wxSTC_NNCRONTAB_TASK"},
{53,3,"wxSTC_NNCRONTAB_SECTION"},
{53,4,"wxSTC_NNCRONTAB_KEYWORD"},
{53,5,"wxSTC_NNCRONTAB_MODIFIER"},
{53,6,"wxSTC_NNCRONTAB_ASTERISK"},
{53,7,"wxSTC_NNCRONTAB_NUMBER"},
{53,8,"wxSTC_NNCRONTAB_STRING"},
{53,9,"wxSTC_NNCRONTAB_ENVIRONMENT"},
{53,10,"wxSTC_NNCRONTAB_IDENTIFIER"},
{54,0,"wxSTC_NSIS_DEFAULT"},
{54,1,"wxSTC_NSIS_COMMENT"},
{54,2,"wxSTC_NSIS_STRINGDQ"},
{54,3,"wxSTC_NSIS_STRINGLQ"},
{54,4,"wxSTC_NSIS_STRINGRQ"},
{54,5,"wxSTC_NSIS_FUNCTION"},
{54,6,"wxSTC_NSIS_VARIABLE"},
{54,7,"wxSTC_NSIS_LABEL"},
{54,8,"wxSTC_NSIS_USERDEFINED"},
{54,9,"wxSTC_NSIS_SECTIONDEF"},
{54,10,"wxSTC_NSIS_SUBSECTIONDEF"},
{54,11,"wxSTC_NSIS_IFDEFINEDEF"},
{54,12,"wxSTC_NSIS_MACRODEF"},
{54,13,"wxSTC_NSIS_STRINGVAR"},
{54,14,"wxSTC_NSIS_NUMBER"},
{54,15,"wxSTC_NSIS_SECTIONGROUP"},
{54,16,"wxSTC_NSIS_PAGEEX"},
{54,17,"wxSTC_NSIS_FUNCTIONDEF"},
{54,18,"wxSTC_NSIS_COMMENTBOX"},
{55,0,"wxSTC_OPAL_SPACE"},
{55,1,"wxSTC_OPAL_COMMENT_BLOCK"},
{55,2,"wxSTC_OPAL_COMMENT_LINE"},
{55,3,"wxSTC_OPAL_INTEGER"},
{55,4,"wxSTC_OPAL_KEYWORD"},
{55,5,"wxSTC_OPAL_SORT"},
{55,6,"wxSTC_OPAL_STRING"},
{55,7,"wxSTC_OPAL_PAR"},
{55,8,"wxSTC_OPAL_BOOL_CONST"},
{55,32,"wxSTC_OPAL_DEFAULT"},
{56,0,"wxSTC_OSCRIPT_DEFAULT"},
{56,1,"wxSTC_OSCRIPT_LINE_COMMENT"},
{56,2,"wxSTC_OSCRIPT_BLOCK_COMMENT"},
{56,3,"wxSTC_OSCRIPT_DOC_COMMENT"},
{56,4,"wxSTC_OSCRIPT_PREPROCESSOR"},
{56,5,"wxSTC_OSCRIPT_NUMBER"},
{56,6,"wxSTC_OSCRIPT_SINGLEQUOTE_STRING"},
{56,7,"wxSTC_OSCRIPT_DOUBLEQUOTE_STRING"},
{56,8,"wxSTC_OSCRIPT_CONSTANT"},
{56,9,"wxSTC_OSCRIPT_IDENTIFIER"},
{56,10,"wxSTC_OSCRIPT_GLOBAL"},
{56,11,"wxSTC_OSCRIPT_KEYWORD"},
{56,12,"wxSTC_OSCRIPT_OPERATOR"},
{56,13,"wxSTC_OSCRIPT_LABEL"},
{56,14,"wxSTC_OSCRIPT_TYPE"},
{56,15,"wxSTC_OSCRIPT_FUNCTION"},
{56,16,"wxSTC_OSCRIPT_OBJECT"},
{56,17,"wxSTC_OSCRIPT_PROPERTY"},
{56,18,"wxSTC_OSCRIPT_METHOD"},
{57,0,"wxSTC_P_DEFAULT"},
{57,1,"wxSTC_P_COMMENTLINE"},
{57,2,"wxSTC_P_NUMBER"},
{57,3,"wxSTC_P_STRING"},
{57,4,"wxSTC_P_CHARACTER"},
{57,5,"wxSTC_P_WORD"},
{57,6,"wxSTC_P_TRIPLE"},
{57,7,"wxSTC_P_TRIPLEDOUBLE"},
{57,8,"wxSTC_P_CLASSNAME"},
{57,9,"wxSTC_P_DEFNAME"},
{57,10,"wxSTC_P_OPERATOR"},
{57,11,"wxSTC_P_IDENTIFIER"},
{57,12,"wxSTC_P_COMMENTBLOCK"},
{57,13,"wxSTC_P_STRINGEOL"},
{57,14,"wxSTC_P_WORD2"},
{57,15,"wxSTC_P_DECORATOR"},
{58,0,"wxSTC_PAS_DEFAULT"},
{58,1,"wxSTC_PAS_IDENTIFIER"},
{58,2,"wxSTC_PAS_COMMENT"},
{58,3,"wxSTC_PAS_COMMENT2"},
{58,4,"wxSTC_PAS_COMMENTLINE"},
{58,5,"wxSTC_PAS_PREPROCESSOR"},
{58,6,"wxSTC_PAS_PREPROCESSOR2"},
{58,7,"wxSTC_PAS_NUMBER"},
{58,8,"wxSTC_PAS_HEXNUMBER"},
{58,9,"wxSTC_PAS_WORD"},
{58,10,"wxSTC_PAS_STRING"},
{58,11,"wxSTC_PAS_STRINGEOL"},
{58,12,"wxSTC_PAS_CHARACTER"},
{58,13,"wxSTC_PAS_OPERATOR"},
{58,14,"wxSTC_PAS_ASM"},
{59,0,"wxSTC_PL_DEFAULT"},
{59,1,"wxSTC_PL_ERROR"},
{59,2,"wxSTC_PL_COMMENTLINE"},
{59,3,"wxSTC_PL_POD"},
{59,4,"wxSTC_PL_NUMBER"},
{59,5,"wxSTC_PL_WORD"},
{59,6,"wxSTC_PL_STRING"},
{59,7,"wxSTC_PL_CHARACTER"},
{59,8,"wxSTC_PL_PUNCTUATION"},
{59,9,"wxSTC_PL_PREPROCESSOR"},
{59,10,"wxSTC_PL_OPERATOR"},
{59,11,"wxSTC_PL_IDENTIFIER"},
{59,12,"wxSTC_PL_SCALAR"},
{59,13,"wxSTC_PL_ARRAY"},
{59,14,"wxSTC_PL_HASH"},
{59,15,"wxSTC_PL_SYMBOLTABLE"},
{59,16,"wxSTC_PL_VARIABLE_INDEXER"},
{59,17,"wxSTC_PL_REGEX"},
{59,18,"wxSTC_PL_REGSUBST"},
{59,19,"wxSTC_PL_LONGQUOTE"},
{59,20,"wxSTC_PL_BACKTICKS"},
{59,21,"wxSTC_PL_DATASECTION"},
{59,22,"wxSTC_PL_HERE_DELIM"},
{59,23,"wxSTC_PL_HERE_Q"},
{59,24,"wxSTC_PL_HERE_QQ"},
{59,25,"wxSTC_PL_HERE_QX"},
{59,26,"wxSTC_PL_STRING_Q"},
{59,27,"wxSTC_PL_STRING_QQ"},
{59,28,"wxSTC_PL_STRING_QX"},
{59,29,"wxSTC_PL_STRING_QR"},
{59,30,"wxSTC_PL_STRING_QW"},
{59,31,"wxSTC_PL_POD_VERB"},
{59,40,"wxSTC_PL_SUB_PROTOTYPE"},
{59,41,"wxSTC_PL_FORMAT_IDENT"},
{59,42,"wxSTC_PL_FORMAT"},
{59,43,"wxSTC_PL_STRING_VAR"},
{59,44,"wxSTC_PL_XLAT"},
{59,54,"wxSTC_PL_REGEX_VAR"},
{59,55,"wxSTC_PL_REGSUBST_VAR"},
{59,57,"wxSTC_PL_BACKTICKS_VAR"},
{59,61,"wxSTC_PL_HERE_QQ_VAR"},
{59,62,"wxSTC_PL_HERE_QX_VAR"},
{59,64,"wxSTC_PL_STRING_QQ_VAR"},
{59,65,"wxSTC_PL_STRING_QX_VAR"},
{59,66,"wxSTC_PL_STRING_QR_VAR"},
{60,0,"wxSTC_PLM_DEFAULT"},
{60,1,"wxSTC_PLM_COMMENT"},
{60,2,"wxSTC_PLM_STRING"},
{60,3,"wxSTC_PLM_NUMBER"},
{60,4,"wxSTC_PLM_IDENTIFIER"},
{60,5,"wxSTC_PLM_OPERATOR"},
{60,6,"wxSTC_PLM_CONTROL"},
{60,7,"wxSTC_PLM_KEYWORD"},
{61,0,"wxSTC_PO_DEFAULT"},
{61,1,"wxSTC_PO_COMMENT"},
{61,2,"wxSTC_PO_MSGID"},
{61,3,"wxSTC_PO_MSGID_TEXT"},
{61,4,"wxSTC_PO_MSGSTR"},
{61,5,"wxSTC_PO_MSGSTR_TEXT"},
{61,6,"wxSTC_PO_MSGCTXT"},
{61,7,"wxSTC_PO_MSGCTXT_TEXT"},
{61,8,"wxSTC_PO_FUZZY"},
{62,0,"wxSTC_POV_DEFAULT"},
{62,1,"wxSTC_POV_COMMENT"},
{62,2,"wxSTC_POV_COMMENTLINE"},
{62,3,"wxSTC_POV_NUMBER"},
{62,4,"wxSTC_POV_OPERATOR"},
{62,5,"wxSTC_POV_IDENTIFIER"},
{62,6,"wxSTC_POV_STRING"},
{62,7,"wxSTC_POV_STRINGEOL"},
{62,8,"wxSTC_POV_DIRECTIVE"},
{62,9,"wxSTC_POV_BADDIRECTIVE"},
{62,10,"wxSTC_POV_WORD2"},
{62,11,"wxSTC_POV_WORD3"},
{62,12,"wxSTC_POV_WORD4"},
{62,13,"wxSTC_POV_WORD5"},
{62,14,"wxSTC_POV_WORD6"},
{62,15,"wxSTC_POV_WORD7"},
{62,16,"wxSTC_POV_WORD8"},
{63,0,"wxSTC_POWERPRO_DEFAULT"},
{63,1,"wxSTC_POWERPRO_COMMENTBLOCK"},
{63,2,"wxSTC_POWERPRO_COMMENTLINE"},
{63,3,"wxSTC_POWERPRO_NUMBER"},
{63,4,"wxSTC_POWERPRO_WORD"},
{63,5,"wxSTC_POWERPRO_WORD2"},
{63,6,"wxSTC_POWERPRO_WORD3"},
{63,7,"wxSTC_POWERPRO_WORD4"},
{63,8,"wxSTC_POWERPRO_DOUBLEQUOTEDSTRING"},
{63,9,"wxSTC_POWERPRO_SINGLEQUOTEDSTRING"},
{63,10,"wxSTC_POWERPRO_LINECONTINUE"},
{63,11,"wxSTC_POWERPRO_OPERATOR"},
{63,12,"wxSTC_POWERPRO_IDENTIFIER"},
{63,13,"wxSTC_POWERPRO_STRINGEOL"},
{63,14,"wxSTC_POWERPRO_VERBATIM"},
{63,15,"wxSTC_POWERPRO_ALTQUOTE"},
{63,16,"wxSTC_POWERPRO_FUNCTION"},
{64,0,"wxSTC_POWERSHELL_DEFAULT"},
{64,1,"wxSTC_POWERSHELL_COMMENT"},
{64,2,"wxSTC_POWERSHELL_STRING"},
{64,3,"wxSTC_POWERSHELL_CHARACTER"},
{64,4,"wxSTC_POWERSHELL_NUMBER"},
{64,5,"wxSTC_POWERSHELL_VARIABLE"},
{64,6,"wxSTC_POWERSHELL_OPERATOR"},
{64,7,"wxSTC_POWERSHELL_IDENTIFIER"},
{64,8,"wxSTC_POWERSHELL_KEYWORD"},
{64,9,"wxSTC_POWERSHELL_CMDLET"},
{64,10,"wxSTC_POWERSHELL_ALIAS"},
{64,11,"wxSTC_POWERSHELL_FUNCTION"},
{64,12,"wxSTC_POWERSHELL_USER1"},
{64,13,"wxSTC_POWERSHELL_COMMENTSTREAM"},
{65,0,"wxSTC_PROPS_DEFAULT"},
{65,1,"wxSTC_PROPS_COMMENT"},
{65,2,"wxSTC_PROPS_SECTION"},
{65,3,"wxSTC_PROPS_ASSIGNMENT"},
{65,4,"wxSTC_PROPS_DEFVAL"},
{65,5,"wxSTC_PROPS_KEY"},
{66,0,"wxSTC_PS_DEFAULT"},
{66,1,"wxSTC_PS_COMMENT"},
{66,2,"wxSTC_PS_DSC_COMMENT"},
{66,3,"wxSTC_PS_DSC_VALUE"},
{66,4,"wxSTC_PS_NUMBER"},
{66,5,"wxSTC_PS_NAME"},
{66,6,"wxSTC_PS_KEYWORD"},
{66,7,"wxSTC_PS_LITERAL"},
{66,8,"wxSTC_PS_IMMEVAL"},
{66,9,"wxSTC_PS_PAREN_ARRAY"},
{66,10,"wxSTC_PS_PAREN_DICT"},
{66,11,"wxSTC_PS_PAREN_PROC"},
{66,12,"wxSTC_PS_TEXT"},
{66,13,"wxSTC_PS_HEXSTRING"},
{66,14,"wxSTC_PS_BASE85STRING"},
{66,15,"wxSTC_PS_BADSTRINGCHAR"},
{67,0,"wxSTC_R_DEFAULT"},
{67,1,"wxSTC_R_COMMENT"},
{67,2,"wxSTC_R_KWORD"},
{67,3,"wxSTC_R_BASEKWORD"},
{67,4,"wxSTC_R_OTHERKWORD"},
{67,5,"wxSTC_R_NUMBER"},
{67,6,"wxSTC_R_STRING"},
{67,7,"wxSTC_R_STRING2"},
{67,8,"wxSTC_R_OPERATOR"},
{67,9,"wxSTC_R_IDENTIFIER"},
{67,10,"wxSTC_R_INFIX"},
{67,11,"wxSTC_R_INFIXEOL"},
{68,0,"wxSTC_RB_DEFAULT"},
{68,1,"wxSTC_RB_ERROR"},
{68,2,"wxSTC_RB_COMMENTLINE"},
{68,3,"wxSTC_RB_POD"},
{68,4,"wxSTC_RB_NUMBER"},
{68,5,"wxSTC_RB_WORD"},
{68,6,"wxSTC_RB_STRING"},
{68,7,"wxSTC_RB_CHARACTER"},
{68,8,"wxSTC_RB_CLASSNAME"},
{68,9,"wxSTC_RB_DEFNAME"},
{68,10,"wxSTC_RB_OPERATOR"},
{68,11,"wxSTC_RB_IDENTIFIER"},
{68,12,"wxSTC_RB_REGEX"},
{68,13,"wxSTC_RB_GLOBAL"},
{68,14,"wxSTC_RB_SYMBOL"},
{68,15,"wxSTC_RB_MODULE_NAME"},
{68,16,"wxSTC_RB_INSTANCE_VAR"},
{68,17,"wxSTC_RB_CLASS_VAR"},
{68,18,"wxSTC_RB_BACKTICKS"},
{68,19,"wxSTC_RB_DATASECTION"},
{68,20,"wxSTC_RB_HERE_DELIM"},
{68,21,"wxSTC_RB_HERE_Q"},
{68,22,"wxSTC_RB_HERE_QQ"},
{68,23,"wxSTC_RB_HERE_QX"},
{68,24,"wxSTC_RB_STRING_Q"},
{68,25,"wxSTC_RB_STRING_QQ"},
{68,26,"wxSTC_RB_STRING_QX"},
{68,27,"wxSTC_RB_STRING_QR"},
{68,28,"wxSTC_RB_STRING_QW"},
{68,29,"wxSTC_RB_WORD_DEMOTED"},
{68,30,"wxSTC_RB_STDIN"},
{68,31,"wxSTC_RB_STDOUT"},
{68,40,"wxSTC_RB_STDERR"},
{68,41,"wxSTC_RB_UPPER_BOUND"},
{69,0,"wxSTC_REBOL_DEFAULT"},
{69,1,"wxSTC_REBOL_COMMENTLINE"},
{69,2,"wxSTC_REBOL_COMMENTBLOCK"},
{69,3,"wxSTC_REBOL_PREFACE"},
{69,4,"wxSTC_REBOL_OPERATOR"},
{69,5,"wxSTC_REBOL_CHARACTER"},
{69,6,"wxSTC_REBOL_QUOTEDSTRING"},
{69,7,"wxSTC_REBOL_BRACEDSTRING"},
{69,8,"wxSTC_REBOL_NUMBER"},
{69,9,"wxSTC_REBOL_PAIR"},
{69,10,"wxSTC_REBOL_TUPLE"},
{69,11,"wxSTC_REBOL_BINARY"},
{69,12,"wxSTC_REBOL_MONEY"},
{69,13,"wxSTC_REBOL_ISSUE"},
{69,14,"wxSTC_REBOL_TAG"},
{69,15,"wxSTC_REBOL_FILE"},
{69,16,"wxSTC_REBOL_EMAIL"},
{69,17,"wxSTC_REBOL_URL"},
{69,18,"wxSTC_REBOL_DATE"},
{69,19,"wxSTC_REBOL_TIME"},
{69,20,"wxSTC_REBOL_IDENTIFIER"},
{69,21,"wxSTC_REBOL_WORD"},
{69,22,"wxSTC_REBOL_WORD2"},
{69,23,"wxSTC_REBOL_WORD3"},
{69,24,"wxSTC_REBOL_WORD4"},
{69,25,"wxSTC_REBOL_WORD5"},
{69,26,"wxSTC_REBOL_WORD6"},
{69,27,"wxSTC_REBOL_WORD7"},
{69,28,"wxSTC_REBOL_WORD8"},
{70,0,"wxSTC_SCRIPTOL_DEFAULT"},
{70,1,"wxSTC_SCRIPTOL_WHITE"},
{70,2,"wxSTC_SCRIPTOL_COMMENTLINE"},
{70,3,"wxSTC_SCRIPTOL_PERSISTENT"},
{70,4,"wxSTC_SCRIPTOL_CSTYLE"},
{70,5,"wxSTC_SCRIPTOL_COMMENTBLOCK"},
{70,6,"wxSTC_SCRIPTOL_NUMBER"},
{70,7,"wxSTC_SCRIPTOL_STRING"},
{70,8,"wxSTC_SCRIPTOL_CHARACTER"},
{70,9,"wxSTC_SCRIPTOL_STRINGEOL"},
{70,10,"wxSTC_SCRIPTOL_KEYWORD"},
{70,11,"wxSTC_SCRIPTOL_OPERATOR"},
{70,12,"wxSTC_SCRIPTOL_IDENTIFIER"},
{70,13,"wxSTC_SCRIPTOL_TRIPLE"},
{70,14,"wxSTC_SCRIPTOL_CLASSNAME"},
{70,15,"wxSTC_SCRIPTOL_PREPROCESSOR"},
{71,0,"wxSTC_SH_DEFAULT"},
{71,1,"wxSTC_SH_ERROR"},
{71,2,"wxSTC_SH_COMMENTLINE"},
{71,3,"wxSTC_SH_NUMBER"},
{71,4,"wxSTC_SH_WORD"},
{71,5,"wxSTC_SH_STRING"},
{71,6,"wxSTC_SH_CHARACTER"},
{71,7,"wxSTC_SH_OPERATOR"},
{71,8,"wxSTC_SH_IDENTIFIER"},
{71,9,"wxSTC_SH_SCALAR"},
{71,10,"wxSTC_SH_PARAM"},
{71,11,"wxSTC_SH_BACKTICKS"},
{71,12,"wxSTC_SH_HERE_DELIM"},
{71,13,"wxSTC_SH_HERE_Q"},
{72,0,"wxSTC_SML_DEFAULT"},
{72,1,"wxSTC_SML_IDENTIFIER"},
{72,2,"wxSTC_SML_TAGNAME"},
{72,3,"wxSTC_SML_KEYWORD"},
{72,4,"wxSTC_SML_KEYWORD2"},
{72,5,"wxSTC_SML_KEYWORD3"},
{72,6,"wxSTC_SML_LINENUM"},
{72,7,"wxSTC_SML_OPERATOR"},
{72,8,"wxSTC_SML_NUMBER"},
{72,9,"wxSTC_SML_CHAR"},
{72,11,"wxSTC_SML_STRING"},
{72,12,"wxSTC_SML_COMMENT"},
{72,13,"wxSTC_SML_COMMENT1"},
{72,14,"wxSTC_SML_COMMENT2"},
{72,15,"wxSTC_SML_COMMENT3"},
{73,0,"wxSTC_SN_DEFAULT"},
{73,1,"wxSTC_SN_CODE"},
{73,2,"wxSTC_SN_COMMENTLINE"},
{73,3,"wxSTC_SN_COMMENTLINEBANG"},
{73,4,"wxSTC_SN_NUMBER"},
{73,5,"wxSTC_SN_WORD"},
{73,6,"wxSTC_SN_STRING"},
{73,7,"wxSTC_SN_WORD2"},
{73,8,"wxSTC_SN_WORD3"},
{73,9,"wxSTC_SN_PREPROCESSOR"},
{73,10,"wxSTC_SN_OPERATOR"},
{73,11,"wxSTC_SN_IDENTIFIER"},
{73,12,"wxSTC_SN_STRINGEOL"},
{73,13,"wxSTC_SN_REGEXTAG"},
{73,14,"wxSTC_SN_SIGNAL"},
{73,19,"wxSTC_SN_USER"},
{74,0,"wxSTC_SORCUS_DEFAULT"},
{74,1,"wxSTC_SORCUS_COMMAND"},
{74,2,"wxSTC_SORCUS_PARAMETER"},
{74,3,"wxSTC_SORCUS_COMMENTLINE"},
{74,4,"wxSTC_SORCUS_STRING"},
{74,5,"wxSTC_SORCUS_STRINGEOL"},
{74,6,"wxSTC_SORCUS_IDENTIFIER"},
{74,7,"wxSTC_SORCUS_OPERATOR"},
{74,8,"wxSTC_SORCUS_NUMBER"},
{74,9,"wxSTC_SORCUS_CONSTANT"},
{75,0,"wxSTC_SPICE_DEFAULT"},
{75,1,"wxSTC_SPICE_IDENTIFIER"},
{75,2,"wxSTC_SPICE_KEYWORD"},
{75,3,"wxSTC_SPICE_KEYWORD2"},
{75,4,"wxSTC_SPICE_KEYWORD3"},
{75,5,"wxSTC_SPICE_NUMBER"},
{75,6,"wxSTC_SPICE_DELIMITER"},
{75,7,"wxSTC_SPICE_VALUE"},
{75,8,"wxSTC_SPICE_COMMENTLINE"},
{76,0,"wxSTC_SQL_DEFAULT"},
{76,1,"wxSTC_SQL_COMMENT"},
{76,2,"wxSTC_SQL_COMMENTLINE"},
{76,3,"wxSTC_SQL_COMMENTDOC"},
{76,4,"wxSTC_SQL_NUMBER"},
{76,5,"wxSTC_SQL_WORD"},
{76,6,"wxSTC_SQL_STRING"},
{76,7,"wxSTC_SQL_CHARACTER"},
{76,8,"wxSTC_SQL_SQLPLUS"},
{76,9,"wxSTC_SQL_SQLPLUS_PROMPT"},
{76,10,"wxSTC_SQL_OPERATOR"},
{76,11,"wxSTC_SQL_IDENTIFIER"},
{76,13,"wxSTC_SQL_SQLPLUS_COMMENT"},
{76,15,"wxSTC_SQL_COMMENTLINEDOC"},
{76,16,"wxSTC_SQL_WORD2"},
{76,17,"wxSTC_SQL_COMMENTDOCKEYWORD"},
{76,18,"wxSTC_SQL_COMMENTDOCKEYWORDERROR"},
{76,19,"wxSTC_SQL_USER1"},
{76,20,"wxSTC_SQL_USER2"},
{76,21,"wxSTC_SQL_USER3"},
{76,22,"wxSTC_SQL_USER4"},
{76,23,"wxSTC_SQL_QUOTEDIDENTIFIER"},
{77,0,"wxSTC_ST_DEFAULT"},
{77,1,"wxSTC_ST_STRING"},
{77,2,"wxSTC_ST_NUMBER"},
{77,3,"wxSTC_ST_COMMENT"},
{77,4,"wxSTC_ST_SYMBOL"},
{77,5,"wxSTC_ST_BINARY"},
{77,6,"wxSTC_ST_BOOL"},
{77,7,"wxSTC_ST_SELF"},
{77,8,"wxSTC_ST_SUPER"},
{77,9,"wxSTC_ST_NIL"},
{77,10,"wxSTC_ST_GLOBAL"},
{77,11,"wxSTC_ST_RETURN"},
{77,12,"wxSTC_ST_SPECIAL"},
{77,13,"wxSTC_ST_KWSEND"},
{77,14,"wxSTC_ST_ASSIGN"},
{77,15,"wxSTC_ST_CHARACTER"},
{77,16,"wxSTC_ST_SPEC_SEL"},
{78,0,"wxSTC_T3_DEFAULT"},
{78,1,"wxSTC_T3_X_DEFAULT"},
{78,2,"wxSTC_T3_PREPROCESSOR"},
{78,3,"wxSTC_T3_BLOCK_COMMENT"},
{78,4,"wxSTC_T3_LINE_COMMENT"},
{78,5,"wxSTC_T3_OPERATOR"},
{78,6,"wxSTC_T3_KEYWORD"},
{78,7,"wxSTC_T3_NUMBER"},
{78,8,"wxSTC_T3_IDENTIFIER"},
{78,9,"wxSTC_T3_S_STRING"},
{78,10,"wxSTC_T3_D_STRING"},
{78,11,"wxSTC_T3_X_STRING"},
{78,12,"wxSTC_T3_LIB_DIRECTIVE"},
{78,13,"wxSTC_T3_MSG_PARAM"},
{78,14,"wxSTC_T3_HTML_TAG"},
{78,15,"wxSTC_T3_HTML_DEFAULT"},
{78,16,"wxSTC_T3_HTML_STRING"},
{78,17,"wxSTC_T3_USER1"},
{78,18,"wxSTC_T3_USER2"},
{78,19,"wxSTC_T3_USER3"},
{78,20,"wxSTC_T3_BRACE"},
{79,0,"wxSTC_TCL_DEFAULT"},
{79,1,"wxSTC_TCL_COMMENT"},
{79,2,"wxSTC_TCL_COMMENTLINE"},
{79,3,"wxSTC_TCL_NUMBER"},
{79,4,"wxSTC_TCL_WORD_IN_QUOTE"},
{79,5,"wxSTC_TCL_IN_QUOTE"},
{79,6,"wxSTC_TCL_OPERATOR"},
{79,7,"wxSTC_TCL_IDENTIFIER"},
{79,8,"wxSTC_TCL_SUBSTITUTION"},
{79,9,"wxSTC_TCL_SUB_BRACE"},
{79,10,"wxSTC_TCL_MODIFIER"},
{79,11,"wxSTC_TCL_EXPAND"},
{79,12,"wxSTC_TCL_WORD"},
{79,13,"wxSTC_TCL_WORD2"},
{79,14,"wxSTC_TCL_WORD3"},
{79,15,"wxSTC_TCL_WORD4"},
{79,16,"wxSTC_TCL_WORD5"},
{79,17,"wxSTC_TCL_WORD6"},
{79,18,"wxSTC_TCL_WORD7"},
{79,19,"wxSTC_TCL_WORD8"},
{79,20,"wxSTC_TCL_COMMENT_BOX"},
{79,21,"wxSTC_TCL_BLOCK_COMMENT"},
{80,0,"wxSTC_TCMD_DEFAULT"},
{80,1,"wxSTC_TCMD_COMMENT"},
{80,2,"wxSTC_TCMD_WORD"},
{80,3,"wxSTC_TCMD_LABEL"},
{80,4,"wxSTC_TCMD_HIDE"},
{80,5,"wxSTC_TCMD_COMMAND"},
{80,6,"wxSTC_TCMD_IDENTIFIER"},
{80,7,"wxSTC_TCMD_OPERATOR"},
{80,8,"wxSTC_TCMD_ENVIRONMENT"},
{80,9,"wxSTC_TCMD_EXPANSION"},
{80,10,"wxSTC_TCMD_CLABEL"},
{81,0,"wxSTC_TEX_DEFAULT"},
{81,1,"wxSTC_TEX_SPECIAL"},
{81,2,"wxSTC_TEX_GROUP"},
{81,3,"wxSTC_TEX_SYMBOL"},
{81,4,"wxSTC_TEX_COMMAND"},
{81,5,"wxSTC_TEX_TEXT"},
{82,0,"wxSTC_TXT2TAGS_DEFAULT"},
{82,1,"wxSTC_TXT2TAGS_LINE_BEGIN"},
{82,2,"wxSTC_TXT2TAGS_STRONG1"},
{82,3,"wxSTC_TXT2TAGS_STRONG2"},
{82,4,"wxSTC_TXT2TAGS_EM1"},
{82,5,"wxSTC_TXT2TAGS_EM2"},
{82,6,"wxSTC_TXT2TAGS_HEADER1"},
{82,7,"wxSTC_TXT2TAGS_HEADER2"},
{82,8,"wxSTC_TXT2TAGS_HEADER3"},
{82,9,"wxSTC_TXT2TAGS_HEADER4"},
{82,10,"wxSTC_TXT2TAGS_HEADER5"},
{82,11,"wxSTC_TXT2TAGS_HEADER6"},
{82,12,"wxSTC_TXT2TAGS_PRECHAR"},
{82,13,"wxSTC_TXT2TAGS_ULIST_ITEM"},
{82,14,"wxSTC_TXT2TAGS_OLIST_ITEM"},
{82,15,"wxSTC_TXT2TAGS_BLOCKQUOTE"},
{82,16,"wxSTC_TXT2TAGS_STRIKEOUT"},
{82,17,"wxSTC_TXT2TAGS_HRULE"},
{82,18,"wxSTC_TXT2TAGS_LINK"},
{82,19,"wxSTC_TXT2TAGS_CODE"},
{82,20,"wxSTC_TXT2TAGS_CODE2"},
{82,21,"wxSTC_TXT2TAGS_CODEBK"},
{82,22,"wxSTC_TXT2TAGS_COMMENT"},
{82,23,"wxSTC_TXT2TAGS_OPTION"},
{82,24,"wxSTC_TXT2TAGS_PREPROC"},
{82,25,"wxSTC_TXT2TAGS_POSTPROC"},
{83,0,"wxSTC_V_DEFAULT"},
{83,1,"wxSTC_V_COMMENT"},
{83,2,"wxSTC_V_COMMENTLINE"},
{83,3,"wxSTC_V_COMMENTLINEBANG"},
{83,4,"wxSTC_V_NUMBER"},
{83,5,"wxSTC_V_WORD"},
{83,6,"wxSTC_V_STRING"},
{83,7,"wxSTC_V_WORD2"},
{83,8,"wxSTC_V_WORD3"},
{83,9,"wxSTC_V_PREPROCESSOR"},
{83,10,"wxSTC_V_OPERATOR"},
{83,11,"wxSTC_V_IDENTIFIER"},
{83,12,"wxSTC_V_STRINGEOL"},
{83,19,"wxSTC_V_USER"},
{84,0,"wxSTC_VHDL_DEFAULT"},
{84,1,"wxSTC_VHDL_COMMENT"},
{84,2,"wxSTC_VHDL_COMMENTLINEBANG"},
{84,3,"wxSTC_VHDL_NUMBER"},
{84,4,"wxSTC_VHDL_STRING"},
{84,5,"wxSTC_VHDL_OPERATOR"},
{84,6,"wxSTC_VHDL_IDENTIFIER"},
{84,7,"wxSTC_VHDL_STRINGEOL"},
{84,8,"wxSTC_VHDL_KEYWORD"},
{84,9,"wxSTC_VHDL_STDOPERATOR"},
{84,10,"wxSTC_VHDL_ATTRIBUTE"},
{84,11,"wxSTC_VHDL_STDFUNCTION"},
{84,12,"wxSTC_VHDL_STDPACKAGE"},
{84,13,"wxSTC_VHDL_STDTYPE"},
{84,14,"wxSTC_VHDL_USERWORD"},
{85,0,"wxSTC_VISUALPROLOG_DEFAULT"},
{85,1,"wxSTC_VISUALPROLOG_KEY_MAJOR"},
{85,2,"wxSTC_VISUALPROLOG_KEY_MINOR"},
{85,3,"wxSTC_VISUALPROLOG_KEY_DIRECTIVE"},
{85,4,"wxSTC_VISUALPROLOG_COMMENT_BLOCK"},
{85,5,"wxSTC_VISUALPROLOG_COMMENT_LINE"},
{85,6,"wxSTC_VISUALPROLOG_COMMENT_KEY"},
{85,7,"wxSTC_VISUALPROLOG_COMMENT_KEY_ERROR"},
{85,8,"wxSTC_VISUALPROLOG_IDENTIFIER"},
{85,9,"wxSTC_VISUALPROLOG_VARIABLE"},
{85,10,"wxSTC_VISUALPROLOG_ANONYMOUS"},
{85,11,"wxSTC_VISUALPROLOG_NUMBER"},
{85,12,"wxSTC_VISUALPROLOG_OPERATOR"},
{85,13,"wxSTC_VISUALPROLOG_CHARACTER"},
{85,14,"wxSTC_VISUALPROLOG_CHARACTER_TOO_MANY"},
{85,15,"wxSTC_VISUALPROLOG_CHARACTER_ESCAPE_ERROR"},
{85,16,"wxSTC_VISUALPROLOG_STRING"},
{85,17,"wxSTC_VISUALPROLOG_STRING_ESCAPE"},
{85,18,"wxSTC_VISUALPROLOG_STRING_ESCAPE_ERROR"},
{85,19,"wxSTC_VISUALPROLOG_STRING_EOL_OPEN"},
{85,20,"wxSTC_VISUALPROLOG_STRING_VERBATIM"},
{85,21,"wxSTC_VISUALPROLOG_STRING_VERBATIM_SPECIAL"},
{85,22,"wxSTC_VISUALPROLOG_STRING_VERBATIM_EOL"},
{86,0,"wxSTC_YAML_DEFAULT"},
{86,1,"wxSTC_YAML_COMMENT"},
{86,2,"wxSTC_YAML_IDENTIFIER"},
{86,3,"wxSTC_YAML_KEYWORD"},
{86,4,"wxSTC_YAML_NUMBER"},
{86,5,"wxSTC_YAML_REFERENCE"},
{86,6,"wxSTC_YAML_DOCUMENT"},
{86,7,"wxSTC_YAML_TEXT"},
{86,8,"wxSTC_YAML_ERROR"},
{86,9,"wxSTC_YAML_OPERATOR"}
};

static lexerProperty props[]={
{1,"lexer.asm.comment.delimiter",2,""},
{1,"fold",0,"0"},
{1,"fold.asm.syntax.based",0,"1"},
{1,"fold.asm.comment.multiline",0,"0"},
{1,"fold.asm.comment.explicit",0,"0"},
{1,"fold.asm.explicit.start",2,""},
{1,"fold.asm.explicit.end",2,""},
{1,"fold.asm.explicit.anywhere",0,"0"},
{1,"fold.compact",0,"1"},
{2,"fold",0,"0"},
{2,"fold.basic.syntax.based",0,"1"},
{2,"fold.basic.comment.explicit",0,"0"},
{2,"fold.basic.explicit.start",2,""},
{2,"fold.basic.explicit.end",2,""},
{2,"fold.basic.explicit.anywhere",0,"0"},
{2,"fold.compact",0,"1"},
{3,"styling.within.preprocessor",0,"0"},
{3,"lexer.cpp.allow.dollars",0,"1"},
{3,"lexer.cpp.track.preprocessor",0,"1"},
{3,"lexer.cpp.update.preprocessor",0,"1"},
{3,"lexer.cpp.triplequoted.strings",0,"0"},
{3,"lexer.cpp.hashquoted.strings",0,"0"},
{3,"fold",0,"0"},
{3,"fold.cpp.syntax.based",0,"1"},
{3,"fold.comment",0,"0"},
{3,"fold.cpp.comment.multiline",0,"1"},
{3,"fold.cpp.comment.explicit",0,"1"},
{3,"fold.cpp.explicit.start",2,""},
{3,"fold.cpp.explicit.end",2,""},
{3,"fold.cpp.explicit.anywhere",0,"0"},
{3,"fold.preprocessor",0,"0"},
{3,"fold.compact",0,"0"},
{3,"fold.at.else",0,"0"},
{4,"fold",0,"0"},
{4,"fold.d.syntax.based",0,"1"},
{4,"fold.comment",0,"1"},
{4,"fold.d.comment.multiline",0,"1"},
{4,"fold.d.comment.explicit",0,"1"},
{4,"fold.d.explicit.start",2,""},
{4,"fold.d.explicit.end",2,""},
{4,"fold.d.explicit.anywhere",0,"0"},
{4,"fold.compact",0,"1"},
{4,"lexer.d.fold.at.else",1,"-1"},
{4,"fold.at.else",0,"0"},
{5,"fold",0,"0"},
{5,"fold.comment",0,"0"},
{5,"fold.compact",0,"1"},
{5,"fold.perl.pod",0,"1"},
{5,"fold.perl.package",0,"1"},
{5,"fold.perl.comment.explicit",0,"1"},
{5,"fold.perl.at.else",0,"0"},
{6,"fold",0,"0"},
{6,"fold.sql.at.else",0,"0"},
{6,"fold.comment",0,"0"},
{6,"fold.compact",0,"0"},
{6,"fold.sql.only.begin",0,"0"},
{6,"lexer.sql.backticks.identifier",0,"0"},
{6,"lexer.sql.numbersign.comment",0,"0"},
{6,"sql.backslash.escapes",0,"0"},
{6,"lexer.sql.allow.dotted.word",0,"0"},
{7,"fold.compact",0,"1"},
{8,"fold.compact",0,"1"},
{9,"fold",0,"0"},
{10,"fold.at.else",0,"0"},
{10,"fold.compact",0,"1"},
{10,"fold.comment",0,"0"},
{11,"fold.compact",0,"1"},
{11,"fold.comment",0,"0"},
{11,"fold.comment",0,"0"},
{11,"fold.preprocessor",0,"0"},
{12,"fold.compact",0,"1"},
{13,"fold.compact",0,"1"},
{13,"fold.comment",0,"0"},
{14,"fold.compact",0,"1"},
{14,"fold.comment",0,"0"},
{14,"styling.within.preprocessor",0,"0"},
{15,"fold.compact",0,"1"},
{15,"fold.comment",0,"0"},
{16,"fold",0,"0"},
{17,"lexer.caml.magic",1,"0"},
{18,"fold.at.else",0,"0"},
{18,"fold",0,"0"},
{19,"fold.compact",0,"1"},
{20,"lexer.cpp.allow.dollars",0,"1"},
{20,"fold.coffeescript.comment",0,"0"},
{20,"fold.compact",0,"0"},
{20,"styling.within.preprocessor",0,"0"},
{21,"fold.compact",0,"1"},
{21,"fold.comment",0,"0"},
{21,"lexer.css.hss.language",0,"0"},
{21,"lexer.css.less.language",0,"0"},
{21,"lexer.css.scss.language",0,"0"},
{22,"escript.case.sensitive",0,"0"},
{22,"fold.compact",0,"1"},
{22,"fold.comment",0,"0"},
{23,"lexer.flagship.styling.within.preprocessor",0,"1"},
{24,"fold.compact",0,"1"},
{24,"fold.comment",0,"0"},
{25,"fold.compact",0,"1"},
{26,"html.tags.case.sensitive",0,"0"},
{26,"fold",0,"0"},
{26,"fold.hypertext.comment",0,"0"},
{26,"fold.hypertext.heredoc",0,"0"},
{26,"fold.html",0,"0"},
{26,"lexer.html.django",0,"0"},
{26,"lexer.html.mako",0,"0"},
{26,"lexer.xml.allow.scripts",0,"1"},
{26,"fold.compact",0,"1"},
{26,"fold.html.preprocessor",0,"1"},
{26,"asp.default.language",1,"1"},
{27,"fold.compact",0,"1"},
{28,"fold.compact",0,"1"},
{29,"fold.compact",0,"0"},
{30,"lexer.metapost.comment.process",0,"0"},
{30,"fold.compact",0,"1"},
{30,"lexer.metapost.interface.default",1,"1"},
{31,"fold.compact",0,"0"},
{32,"fold.compact",0,"1"},
{32,"fold",0,"0"},
{32,"fold.comment",0,"0"},
{33,"fold.sql.only.begin",0,"0"},
{33,"fold.compact",0,"1"},
{33,"fold.comment",0,"0"},
{34,"fold.comment.nimrod",0,"0"},
{34,"fold.quotes.nimrod",0,"0"},
{35,"fold.at.else",0,"0"},
{35,"nsis.foldutilcmd",0,"1"},
{35,"nsis.ignorecase",0,"0"},
{35,"nsis.ignorecase",0,"0"},
{35,"nsis.uservars",0,"0"},
{35,"nsis.uservars",0,"0"},
{35,"fold",0,"0"},
{36,"fold.compact",0,"1"},
{36,"fold.comment",0,"0"},
{36,"fold.preprocessor",0,"0"},
{37,"lexer.errorlist.value.separate",0,"0"},
{37,"lexer.props.allow.initial.spaces",0,"1"},
{37,"fold.compact",0,"1"},
{38,"lexer.pascal.smart.highlighting",0,"1"},
{38,"fold.compact",0,"1"},
{38,"fold.comment",0,"0"},
{38,"fold.preprocessor",0,"0"},
{39,"fold",0,"0"},
{40,"fold.compact",0,"1"},
{40,"fold.comment",0,"0"},
{41,"fold.compact",0,"1"},
{41,"fold.comment",0,"0"},
{41,"fold.directive",0,"0"},
{42,"fold.comment",0,"0"},
{42,"fold.comment",0,"0"},
{43,"fold.at.else",0,"0"},
{43,"fold.compact",0,"1"},
{43,"fold.comment",0,"0"},
{44,"fold.at.else",0,"0"},
{44,"fold.compact",0,"1"},
{44,"fold.comment",0,"0"},
{45,"fold.at.else",0,"0"},
{45,"fold.compact",0,"1"},
{45,"ps.level",1,"3"},
{45,"ps.tokenize",0,"0"},
{46,"lexer.python.strings.b",0,"1"},
{46,"lexer.python.literals.binary",0,"1"},
{46,"lexer.python.strings.u",0,"1"},
{46,"fold.compact",0,"0"},
{46,"fold.quotes.python",0,"0"},
{46,"lexer.python.keywords2.no.sub.identifiers",0,"0"},
{46,"lexer.python.strings.over.newline",0,"0"},
{46,"tab.timmy.whinge.level",1,"0"},
{47,"fold.at.else",0,"0"},
{47,"fold.compact",0,"1"},
{48,"fold.compact",0,"1"},
{48,"fold.comment",0,"0"},
{49,"tab.timmy.whinge.level",1,"0"},
{50,"lexer.caml.magic",1,"0"},
{51,"fold.at.else",0,"0"},
{51,"fold.compact",0,"1"},
{51,"fold.comment",0,"0"},
{52,"fold.compact",0,"1"},
{52,"fold.comment",0,"0"},
{52,"fold.preprocessor",0,"0"},
{53,"fold.compact",0,"1"},
{53,"fold.comment",0,"0"},
{53,"fold.preprocessor",0,"0"},
{54,"fold.comment",0,"0"},
{55,"lexer.tex.comment.process",0,"0"},
{55,"lexer.tex.auto.if",0,"1"},
{55,"fold.compact",0,"1"},
{55,"lexer.tex.use.keywords",0,"1"},
{55,"lexer.tex.interface.default",1,"1"},
{55,"fold.comment",0,"0"},
{56,"fold.at.else",0,"0"},
{56,"fold.verilog.flags",0,"0"},
{56,"fold.compact",0,"1"},
{56,"fold.comment",0,"0"},
{56,"fold.preprocessor",0,"0"},
{57,"fold.at.When",0,"1"},
{57,"fold.at.Begin",0,"1"},
{57,"fold.at.else",0,"1"},
{57,"fold.at.Parenthese",0,"1"},
{57,"fold.comment",0,"1"},
{57,"fold.compact",0,"1"},
{58,"fold.comment.yaml",0,"0"}
};

static const int totalProperties=sizeof(props) / sizeof(lexerProperty);


lexerDB::lexerDB()
{
    int count = sizeof(stateName) / sizeof(lexerItem);

    for (int i = 0; i < count; i++)
    {
        lexerStateName.emplace( std::move(std::make_pair(std::make_pair(stateName[i].first,stateName[i].second),stateName[i].c) ));
    }

    count = sizeof(kwSetName) / sizeof(lexerItem);
    for (int i = 0; i < count; i++)
    {
        lexerKWSetName.emplace( std::move(std::make_pair(std::make_pair(kwSetName[i].first,kwSetName[i].second),kwSetName[i].c)) );
    }

    for(int i=0;i<9;i++)
    {
        kwVec[i]=nullptr;
    }

    for(int i=0;i<wxSTC_STYLE_MAX+11;i++)
    {
        stylesVec[i]=nullptr;
    }
}

lexerDB::~lexerDB()
{
    lexerKWSetName.clear();
    lexerStateName.clear();
}

void lexerDB::setKWVec(int i,wxPGProperty* p)
{
    if(0<=i && i<9)
    {
        kwVec[i]=p;
    }
}

int lexerDB::getKWSetNo(int lexer)
{
    if(0<=lexer && lexer<=maxLexer)
    {
        return kwSet[lexer];
    }
    else
    {
        return -1;
    }
}

wxString lexerDB::getKWName(int lexerno,int kwsetno)
{
    if(lexerno==-1)
    {
        return wxString::Format("Keyword Set %d",kwsetno);
    }

    int statesetno=getKWSetNo(lexerno);

    if(statesetno==-1)
    {
        return wxString::Format("Keyword Set %d",kwsetno);
    }

    std::map<std::pair<int,int>, char const* const>::iterator it= lexerKWSetName.find(std::pair<int,int>(statesetno,kwsetno));

    if(it==lexerKWSetName.end())
    {
        return wxString::Format("Keyword Set %d",kwsetno);
    }
    else
    {
        wxString s = it->second;
        s << wxString::Format(" - (Keyword Set %d)",kwsetno);

        return s;
    }
}

void lexerDB::renameKWs(int lexer)
{
    wxPGProperty* p;

    for(int i=0;i<9;i++)
    {
        p=kwVec[i];
        if(!p)
        {
            continue;
        }

        p->SetLabel( getKWName(lexer,i) );
    }
}


void lexerDB::setStylesVec(int i,wxPGProperty* p)
{
    if(0<=i && i<=wxSTC_STYLE_MAX+10)
    {
        stylesVec[i]=p;
    }
}

int lexerDB::getStateSetNo(int lexer)
{
    if(0<=lexer && lexer<=maxLexer)
    {
        return lexerStateSet[lexer];
    }
    else
    {
        return -1;
    }
}

void lexerDB::renameStyles(int lexerno)
{
    wxPGProperty* p;

    for(int i=0;i<=wxSTC_STYLE_MAX;i++)
    {
        p=stylesVec[i];
        if(!p)
        {
            continue;
        }

        p->SetLabel( getLexerStyleName(lexerno,i) );
    }
}

wxString lexerDB::getLexerStyleName(int lexerno,int styleno)
{
    if(styleno==wxSTC_STYLE_DEFAULT)
    {
        return wxString::Format("wxSTC_STYLE_DEFAULT - (style %d)",wxSTC_STYLE_DEFAULT);
    }
    else if(styleno==wxSTC_STYLE_LINENUMBER)
    {
        return wxString::Format("wxSTC_STYLE_LINENUMBER - (style %d)",wxSTC_STYLE_LINENUMBER);
    }
    else if(styleno==wxSTC_STYLE_BRACELIGHT)
    {
        return wxString::Format("wxSTC_STYLE_BRACELIGHT - (style %d)",wxSTC_STYLE_BRACELIGHT);
    }
    else if(styleno==wxSTC_STYLE_BRACEBAD)
    {
        return wxString::Format("wxSTC_STYLE_BRACEBAD - (style %d)",wxSTC_STYLE_BRACEBAD);
    }
    else if(styleno==wxSTC_STYLE_CONTROLCHAR)
    {
        return wxString::Format("wxSTC_STYLE_CONTROLCHAR - (style %d)",wxSTC_STYLE_CONTROLCHAR);
    }
    else if(styleno==wxSTC_STYLE_INDENTGUIDE)
    {
        return wxString::Format("wxSTC_STYLE_INDENTGUIDE - (style %d)",wxSTC_STYLE_INDENTGUIDE);
    }
    else if(styleno==wxSTC_STYLE_CALLTIP)
    {
        return wxString::Format("wxSTC_STYLE_CALLTIP - (style %d)",wxSTC_STYLE_CALLTIP);
    }
    else if(styleno==wxSTC_STYLE_LASTPREDEFINED)
    {
        return wxString::Format("wxSTC_STYLE_LASTPREDEFINED - (style %d)",wxSTC_STYLE_LASTPREDEFINED);
    }
    else if(styleno==wxSTC_STYLE_MAX)
    {
        return wxString::Format("wxSTC_STYLE_MAX - (style %d)",wxSTC_STYLE_MAX);
    }

    if(lexerno==-1)
    {
        return wxString::Format("style %d",styleno);
    }

    int statesetno = getStateSetNo(lexerno);


    std::map<std::pair<int,int>, char const* const>::iterator it= lexerStateName.find(std::pair<int,int>(statesetno,styleno));

    if(it==lexerStateName.end())
    {
        return wxString::Format("style %d",styleno);
    }
    else
    {
        wxString s = it->second;
        s << wxString::Format(" - (style %d)",styleno);

        return s;
    }
}

void lexerDB::getLexerProps(int lexer,std::vector<lexerProperty*>* propset)
{
    if(lexer<0 || lexer>maxLexer)
    {
        return;
    }

    int ps = propSet[lexer];

    if(ps==-1)
    {
        return;
    }

    for(int i=0;i<totalProperties;i++)
    {
        if(props[i].set_no==ps)
        {
            propset->push_back( &(props[i]) );
        }
    }
}
