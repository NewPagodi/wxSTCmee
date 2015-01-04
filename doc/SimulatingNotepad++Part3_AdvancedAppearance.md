## Simulating Notepad++ Part3 - Advanced Appearance

Other documentation available:
 - [An Introduction to Scintilla for wxStyledTextCtrl Programmers](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/DocPart1_IntroductionToScintilla.md)
 - [An Introduction to the Method Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/DocPart2_MethodExplorer.md)
 - [An Introduction to the Event Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/DocPart3_EventExplorer.md)
 
In addition, to give some concrete examples of configuring the appearance and behavior of a wxStyledTextCtrl window, I've written a 3 part series on making the window look like the default appearance for notepad++.

 - [Simulating Notepad++ Part1 - Basic Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part1_BasicAppearance.md)
 - [Simulating Notepad++ Part2 - Working with the Margins](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part2_Margins.md)

#### Introduction
In this tutorial, I want to give some additional examples of scintilla options.  As in the previous 2 tutorials, I'll use notepad++ as the basis for setting the options.  

#### Setting the Caret Color

Notepad++ uses a bluish caret instead of a black one.  This can be set as follows:

 - open the "Caret, selection, and hotspot styles" group
 - change the "SetCaretForeground" item to (128,0,255) <br> ![SetCaretForeground](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/SetCaretForeground.png "SetCaretForeground")


#### The Long Line Indicator

Notepad++ can optionally display a vertical line

![Long Line Indicator Example](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/longLineInd.png "Long Line Indicator Example")

To get such a vertical line with a wxStyledTextCtrl window, we need to do the following:

 - open the "Long lines" group
 - change "SetEdgeMode" to wxSTC_EDGE_LINE
 - change "SetEdgeColumn" to 100
 - change SetEdgeColour to (128,255,255)

![Long Line Settings](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/longLineSet.png "Long Line Settings")


<!---
Additional sections I hope to write:
carret color
-->
