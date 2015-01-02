#### An Introduction to Scintilla for wxStyledTextCtrl Programmers

Other documentation available:

 - [An Introduction to the Method Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/MethodExplorer.md)
 - [An Introduction to the Event Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/EventExplorer.md)
 
In addition, to give some concrete examples of configuring the appearance and behavior of a wxStyledTextCtrl window, I've written a 3 part series on making the window look like the default appearance for notepad++.

 - [Simulating Notepad++ Part1 - Basic Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part1_BasicAppearance.md)
 - [Simulating Notepad++ Part2 - Working with the Margins](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part2_Margins.md)
 - [Simulating Notepad++ Part3 - Advanced Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part3_AdvancedAppearance.md)

## Scintilla and wxStyledTextCtrl

wxStyledTextCtrl is a wrapper for [the Scintilla text editing component](http://www.scintilla.org/). So I thought I'd begin with a discussion of what Scintilla is and some of the features it offers.

Scintilla is a control for displaying text files similar to wxTextCtrl or wxRichTextCtrl.  But it has a number of features that make it ideal for displaying source code for developers.  The following shows a fragment of code displayed in a scintilla window:

![Scintilla Example](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/scintillaexample.png "Scintilla Example") 

As we can see, the Scintilla window colors the comments green to help differentiate them from the rest of the code and colors keywords like 'delete' and 'for' blue to help distinguish them.  

## Setting a Character's Style

The way Scintilla assigns colors and other properties to the characters is a file is as follows:
 1. Scintilla allows us to define has 256 style categories (numbered 0 - 255). 
 2. Each byte in the source file is assigned a style number.
 3. Each character in the file is then rendered with the style options in the category of its style number.
 
For example, if character 0 is assigned style number 32, character 0 is rendered with all of the all of the style options in category 32.
 
For each of those style categories, here is the long list of style properties that can be set: 

![Style Properties](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/styleOptions.png "Properties") 

All of the common familiar options such as font name, font size, bold, italic, and underline are available.  In addition:
 - a foreground and background color can be set.  
 - If you need a font size between 10 and 11, you can use the StyleSetSizeFractional.  For example, StyleSetSizeFractional(1050) would be roughly equivalent to setting the size to be 10.5.   
 - StyleSetCase can be used to force the characters with that style to be discplayed as all upper case or all lower case.  The original file is not modified.
 - if StyleSetVisible is set to false, characters with that style will invisible.
 - if StyleSetHotSpot is set to true, then clicking on characters with that style will generate an WXSTC_HOTSPOT_CLICK event that can be handled by your program.
 
With each of these options there is a "Get" command to allow us to query Scintilla about the value currently assigned.

## Lexers

The upshot of the preceding section is that each character is the source file needs to be assigned a style number.  Scintilla offers methods to allow us to do this character by character.  However this process is usually done by assigning a lexer based on the programming language of the source file.  A lexer is a sub-program that reads through the source file and trys to assign style numbers to the characters based on the syntactic category of those characters.  

Out of the box, Scintilla includes lexers for 105 language families such as C, python, html, perl, vb, sql, and so on.  Additional lexers can be added in as a shared library.

Lets consider the C lexer.  It will try to assign the style numbers to characters in a file as follows:   
 
|Category                      |Style Number|
|------------------------------|------------|
|wxSTC_C_DEFAULT               |0           |
|wxSTC_C_COMMENT               |1           |
|wxSTC_C_COMMENTLINE           |2           |
|wxSTC_C_COMMENTDOC            |3           |
|wxSTC_C_NUMBER                |4           |
|wxSTC_C_WORD                  |5           |
|wxSTC_C_STRING                |6           |
|wxSTC_C_CHARACTER             |7           |
|wxSTC_C_UUID                  |8           |
|wxSTC_C_PREPROCESSOR          |9           |
|wxSTC_C_OPERATOR              |10          |
|wxSTC_C_IDENTIFIER            |11          |
|wxSTC_C_STRINGEOL             |12          |
|wxSTC_C_VERBATIM              |13          |
|wxSTC_C_REGEX                 |14          |
|wxSTC_C_COMMENTLINEDOC        |15          |
|wxSTC_C_WORD2                 |16          |
|wxSTC_C_COMMENTDOCKEYWORD     |17          |
|wxSTC_C_COMMENTDOCKEYWORDERROR|18          |
|wxSTC_C_GLOBALCLASS           |19          |
|wxSTC_C_STRINGRAW             |20          |
|wxSTC_C_TRIPLEVERBATIM        |21          |
|wxSTC_C_HASHQUOTEDSTRING      |22          |
|wxSTC_C_PREPROCESSORCOMMENT   |23          |

So, if it thinks a character is part of a COMMENTDOC, (ie a comment like '/* this is a comment*/'), it will assign it style number 3.  If it thinks a character is part of a string literal, it will assign it style number 6.

Note that the category names in this table such as 'wxSTC_C_DEFAULT' are actually preprocessor directives defined in "stc.h" such as `#define wxSTC_C_DEFAULT 0`.

<!---
Additional sections I hope to write:
keywords
margins and folding
annotations
calltips
cut,copy,paste, undo,redo, etc
selection

-->


