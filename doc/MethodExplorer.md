#### An Introduction to the Method Explorer

Other documentation available:
 - [An Introduction to Scintilla for wxStyledTextCtrl Programmers](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/IntroductionToScintilla.md)
 - [An Introduction to the Event Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/EventExplorer.md)
 
In addition, to give some concrete examples of configuring the appearance and behavior of a wxStyledTextCtrl window, I've written a 3 part series on making the window look like the default appearance for notepad++.

 - [Simulating Notepad++ Part1 - Basic Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part1_BasicAppearance.md)
 - [Simulating Notepad++ Part2 - Working with the Margins](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part2_Margins.md)
 - [Simulating Notepad++ Part3 - Advanced Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part3_AdvancedAppearance.md)

## Introduction 
In this part of the documentation I want to describe how you can call wxStyledTextCtrl methods to set Scintilla properties, get various kinds of information, and perform various actions.  The main window of the wxStyledTextCtrl Method and Event Explorer looks like the following:

![wxStyledTextCtrl Method and Event Explorer ](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/stcmee.png "wxStyledTextCtrl Method and Event Explorer ") 

There are 5 separate windows.  On the upper left is a wxStyledTextCtrl window.  On the upper right is a property grid used for setting properties for the wxStyledTextCtrl window.  In the middle is the event information window.  The bottom 2 windows show the Scintilla and wxStyledTextCtrl documentation.  

There's a 6th window named the code log.  It can be shown by selecting "View->Show Code" from the menu. 

![The Show Code Menu Item](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/stcmee.png "The Show Code Menu Item") 

The code log window will look something like the following:

![The Code Log Window](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/codelog.png "The Code Log Window") 

As might be expected from its name, this window will give the code you can use in your program to configure a wxStyledTextCtrl window in the same way that is done with the property grid.

## An Overview of the wxStyledTextCtrl methods

Most of the methods in the wxStyledTextCtrl class are either "setters" that set a Scintilla property, "getter" which get a piece of information about the window, or "do-ers" that perform some action.  There are a few methods that don't quite fall into one of those categories and some other methods might be considered both a setter and a do-er, but I think that's a generally useful breakdown of classes.

Most of the methods take 0, 1, or 2 parameters.  There are only a few methods that take more than 2 parameters.

## Setting Scintilla Properties with the Property Grid

In this section, I want to focus on how to use the property grid to set various things.  Open the "Text retrieval and modification" group in the property grid.  Let's consider the "SetText" method.

![The Set Text Property](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/settextSel.png "The Set Text Property") 

When the selection is made, the relevant portions of the Scintilla and wxStyledTextCtrl documentation are scrolled into view:

![The Set Text Help](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/settextHelp.png "The Set Text Help") 

As we can see from the documentation, the method takes one string parameter.  The parameter is set as a child item for the property.  To call this method, simply enter some text such as "abc" into the child item, and then press the button.  This will call SetText with that string as a parameter.

![the Set Text method](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/settext.png "the Set Text method") 

Next consider the "SetReadOnly" item.  As you might see by selecting the item and viewing the documentation, this method takes 1 boolean parameter.  In this case the property has a check box, and the method is called with true when the box is checked, and it is called with false when the box is unchecked.  There is no need to press a button to call the method:

![the SetReadOnly method](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/setReadOnly.png "the SetReadOnly method") 

For a final example, consider the "SetStyleBits" item towards the end of the group.  This method, takes a single int parameter.  The property has a spin control for setting an integer, and the method is called every time the integer is changed either by typing a new integer or using spin control.  So again there is no need to press a button to call the method.  

![the SetStyleBits method](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/SetStyleBits.png "the SetStyleBits method")

There are many, many other methods for setting properties.  But the basic idea with all will be similar to one of these 3 examples.

<!---
Additional sections I hope to write:
enum properties
color properties
flags properties
-->

## Getting Information with the Property Grid

Most of the methods for getting infomation about the wxStyledTextCtrl window conveniently start with the word "Get".  Examples in the "Text retrieval and modification" group include GetText, GetLine, GetReadOnly, GetTextRange, GetCharAt, GetStyleAt, GetStyledText, and GetStyleBits.  For all of these methods, it is necessary to press the button in the property grid to call the method.  If the method needs any parameters, they can be set with child items for the property.

Consider the "GetText" item.  To call this method, simply select the item, and press the button.

![the GetText method](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/GetText.png "the GetText method")

After the method is called, the result is displayed in the properties value area.

## Performing Actions with the Property Grid

Performing actions is very similar to getting information.  To call all of the methods of this type will reqire pressing a button in the property grid.  

Consider the "SetSavePoint" item.  To call this method, simply select the item, and press the button.

![the SetSavePoint method](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/SetSavePoint.png "the SetSavePoint method")

<!---
Additional sections I hope to write:
use an example that doesn't begin with the word "Set" since that makes it seem like a setter instead of a do-er
-->




