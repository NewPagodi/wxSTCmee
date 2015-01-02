## wxStyledTextCtrl Method and Event Explorer 

The purpose is this piece of software is to allow the user to explore the properties and methods of the wxStyledTextCtrl Class. wxStyledTextCtrl is a great tool for displaying source code documents, but with over 600 methods, it's not always easy to figure out how to do a certain task.  The method explorer groups those methods into categories and presents them in an interactive property grid.  This way you can see the effects of calling various methods with different parameters in real time without having to recompile anything.

![wxStyledTextCtrl Method and Event Explorer ](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/stcmee.png "wxStyledTextCtrl Method and Event Explorer ") 

In addition, once you've gotten your StyledTextCtrl configured the way you want it, there's a code log that will present code can be used in your program (although you may have to change the name of the variable used):

![The Code Log Window](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/codelog.png "The Code Log Window") 

In order to compile, a version of wxWidgets recent enough to include wxAui, wxPropertyGrid, and wxWebView is needed.  I believe most versions since 2.9 should work.  

#### Documentation/Help

I've written 3 pieces of documentation:

 - [An Introduction to Scintilla for wxStyledTextCtrl Programmers](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/IntroductionToScintilla.md)
 - [An Introduction to the Method Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/MethodExplorer.md)
 - [An Introduction to the Event Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/EventExplorer.md)
 
In addition, to give some concrete examples of configuring the appearance and behavior of a wxStyledTextCtrl window, I've written a 3 part series on making the window look like the default appearance for notepad++.

 - [Basic Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part1_BasicAppearance.md)
 - [Working with the Margins](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part2_Margins.md)
 - [Advanced Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part3_AdvancedAppearance.md)

#### Building
No build files are supplied, but no special options are needed to build this tool.  If you can build any other wxWidgets program, you should be able to build this.  Simply compile each of the .cpp files and link them with your wxWidgets library.

#### Credits
This software makes use of the following:
 - the wxStyledTextCtrl documentation is used in accordance with the terms of the wxwindows free documentation licence.  See the files credits.txt and wxWidgets\licendoc.txt for more details.
 - the Scintilla documentation and icons are used in accordance the Scintilla license.  See the files credits.txt and scintilla\License.txt for more details.