## Simulating Notepad++ Part1 - Basic Appearance

Other documentation available:
 - [An Introduction to Scintilla for wxStyledTextCtrl Programmers](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/DocPart1_IntroductionToScintilla.md)
 - [An Introduction to the Method Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/DocPart2_MethodExplorer.md)
 - [An Introduction to the Event Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/DocPart3_EventExplorer.md)
 
In addition, to give some concrete examples of configuring the appearance and behavior of a wxStyledTextCtrl window, I've written a 3 part series on making the window look like the default appearance for notepad++.

 - [Simulating Notepad++ Part2 - Working with the Margins](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part2_Margins.md)
 - [Simulating Notepad++ Part3 - Advanced Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part3_AdvancedAppearance.md)

#### Introduction 
 
The following shows a fragment of the sample.cpp file from this repo pasted into a freshly created wxStyledTextCtrl window and the same file opened in notepad++.

![Raw wxStyledTextCtrl vrs notepad++](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/stc_np++comp2.png "Comparison 1")

The wxStyledTextCtrl window is using a variable width font and has a smaller font size.  In contrast, the notepad++ window has a fixed width font, has colored the comments and keywords of the language to help us identify them, and has some nice margins on the left showing the line numbers and allowing us to collapse code.  I think most coders would agree that the version presented by notepad++ is much more readable.  

Lets work through the process of making a wxStyledTextCtrl window show code in the same way notepad++ does.    

#### Fixing the margins

Lets begin with the margins.  Notepad++ actually has 3 margins visible: a margin for the line numbers, a margin for bookmarks, and a margin with the boxes we click to collapse code.  The wxStyledTextCtrl options for setting these things are in the "Margins" area of the propgrid.  

 - open the "Margins" group in the propgrid.  It's towards the middle of the propgrid: <br>![margins group location in the propgrid](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/margins.png "Margins group")
 - open the "Margin 0" subgroup
	+ change the value for the property "SetMarginWidth" to 30: <br>![margin0 setting](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/margin0a.png "Margins0a")
 - the defaults for the margin 1 (the bookmark margin) are fine, so we move on to the fold margin
 - open the "Margin 2" subgroup
	+ change "SetMarginWidth" to 14
	+ from the dropdown list in "SetMarginMask" select "wxSTC_MASK_FOLDERS": <br>![margin2 setting](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/margin2.png "Margins2")
 
Our wxStyledTextCtrl window now has 3 margins with the correct widths.  Those margins however have the wrong colors.  We can we fix the color of the fold margin as follows: 

 - open the "SetFoldMarginColour" item
 	+ set the useSetting parameter to true
	+ set the back parameter to "white" or (255,255,255).  (You can either type/paste (255,255,255) into the value area or press the button labeled '...' to open a color setting dialog where you can enter those values.)
 - open the "SetFoldMarginHiColour" item
 	+ set the useSetting parameter to true
	+ set the fore parameter to rgb (233,233,233)<br>![fold margin color settings](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/foldmargin.png "Fold Margin Colors")

For whatever reason, the colors for the other margins are set in a different property group, so I'll cover that when we get there.

#### Setting the lexer (and repairing the damage setting the lexer does)

The next step is to set the lexer to tell the wxStyledTextCtrl that we're working with a c++ file and not just any type of text file.

 - open the lexer group
 - change "SetLexer" from "wx_STC_LEX_CONTAINER" to "wx_STC_LEX_CPP"<br>![Setting the lexer option](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/setLexer.png "Setting the lexer option")
 
Now, somewhat surprisingly, the next time you click in the wxStyledTextCtrl window, all the text seems to disappear.  It's actually been colored white.  That seems to happen the first time a lexer value is set.  I'm not sure why wxStyledTextCtrl/Scintilla does that, but as a programmer, it's good to know that so we can fix it.  With the method and event explorer, we've seen a surprising outcome happen in real time.  We can fix it as follows.

- open the "Style definition" group
- open the "predefined number styles" subgroup.
- open the "wxSTC_STYLE_DEFAULT" group.  As the name suggests, this sets the default style options.  Amongst the options that can be set are the font name, the font size, the font color, whether to use bold, italic, or underline and so on.  <br>![The Style Definition Group](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/styleDefinitionGroup.png "The Style Definition Group")  
- Change "StyleSetFaceName" to "Courier new"
- Change "StyleSetSize" to 10<br>![The Style Definition Settings](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/styleDefinitionSettings.png "The Style Definition Settings")

After making these changes to the default group, it's important to call the StyleClearAll method.  Select this item in the property grid and press the button in the value area to call the method:

![StyleClearAll](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/styleClearAll.png "StyleClearAll")
                                                                        
While we're in the "Style definition" group, we can fix the colors for the line number margin.  
 - open the wx_STC_STYLE_LINENUMBER subgroup.
 - set StyleSetForeground to "Grey" or (128,128,128)
 - set StyleSetBackground to (228,228,228) <br>![Line Number Margins Styles](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/styleDefinitionLineNo.png "Line Number Margins Styles") 

I have no clue why those options are set in the style definition group and not the the margin group, but that is a quirk of Scintilla that we have to live with.

#### Coloring constants and keywords

The next step is to color the constants and keywords of the language as notepad++ does.  This is done in 2 parts.  First we return to the lexer group and set the keywords.  

- open the lexer group if its not still open
- open the "SetKeyWords" subgroup
- open the "Primary keywords and identifiers (Keyword set 0) property and set the "keywords" property to:
	+  `if else switch case default break goto return for while do continue typedef sizeof NULL new delete throw try catch namespace`
- open the "Secondary kewyords and identifiers (Keyword set 1) property and set the "keywords" property to:
	+ `void struct union enum char short int long double float signed unsigned const static extern auto register volatile bool class private protected public friend inline template virtual asm explicit typename mutable`
	+ note that these are properties are a little different that most of the others and after you enter the keywords you will need to press the button in the property area to make the changes take effect: <br>![SetKeyWords](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/SetKeyWords.png "SetKeyWords") 
	
Second, we need to set the style options for each category.  If you didn't press the button in the "StyleClearAll" item earlier, make sure to do that now or else some of the following may not work.
 - open the "Style definition" group 
 - open the "Style 0 ... wxSTC_STYLE_DEFAULT-1" subgroup  
 - open the "wxSTC_C_COMMENT - (style 0)" item
 - set the "StyleSetForeground" item to have value (0,128,0):<br>![Comment Style](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/commentStyle.png "Comment Style") 
 - repeat this process setting the foreground colors for the categories as follows:

| Style Number                   | StyleSetForeground| OtherOptions  |
|--------------------------------|-------------------|---------------|
| wxSTC_C_COMMENT                | (0,128,0)         |               |
| wxSTC_C_COMMENTLINE            | (0,128,0)         |               |
| wxSTC_C_COMMENTDOC             | (0,128,128)       |               |
| wxSTC_C_NUMBER                 | (255,128,0)       |               |
| wxSTC_C_WORD                   | (0,0,255)         | bold          |
| wxSTC_C_STRING                 | (128,128,128)     |               |
| wxSTC_C_CHARACTER              | (128,128,128)     |               |
| wxSTC_C_PREPROCESSOR           | (128,64,0)        |               |
| wxSTC_C_OPERATOR               | (0,0,128)         | bold          |
| wxSTC_C_REGEX                  | (0,0,0)           | bold          |
| wxSTC_C_COMMENTLINEDOC         | (0,128,128)       |               |
| wxSTC_C_WORD2                  | (128,0,255)       |               |
| wxSTC_C_COMMENTDOCKEYWORD      | (0,128,128)       | bold          |
| wxSTC_C_COMMENTDOCKEYWORDERROR | (0,128,128)       |               |	

Note that with the wxSTC_C_WORD, wxSTC_C_OPERATOR, wxSTC_C_REGEX, and wxSTC_C_COMMENTDOCKEYWORDERROR categories we should also make sure StyleSetBold is set to true as follows:

![Word Style](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/wordStyle.png "Word Style")

#### Highlighting the current line	

Another nice thing notepad++ does is that it highlights the line containing the cursor.  

![Current Line Highlighting](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/curLineHighlite.png "Current Line Highlighting")

This behavior can be set as follows:

- open the "Caret, selection, and hotspot styles" group.
- set the "SetCaretLineVisible" key to true.
- set the "SetCaretLineBackground" to (232,232,255) <br>![SetCaretLineVisible](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/SetCaretLineVisible.png "SetCaretLineVisible")

#### Fixing a Few More Things

By now the wxStyledTextCtrl closely resembles the notepad++ window.  Lets look at a comparison: 

![A Comparison](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/stc_np++comp3.png "A Comparison")

I think there are 2 main differences remaining.  First some of the lines in the wxStyledTextCtrl such as lines 11 and 15 have an blue squiggle under them.  Second, the lines in notepad++ have a little extra space between them.

###### Removing the Squiggles

The squiggles are an example of a style byte indicator.  They can be used by wxStyledTextCtrl to indicate syntax errors or other things about the code that should be brought to the user's attention.  But here it's just annoying.  

There are a few different ways to get rid of the squiggles.  One thing we can do is ask the lexer not to indicate them.  Another think is to simply set that indicator invisible.  I'll show how to do the second approach.  

 - open the "Indicators" group
 - open the "Lexer Indicators" subgroup
 - open the "indicator 1" item
 - change the "IndicatorSetStyle" item from "wxSTC_INDIC_TT" to "wxSTC_INDIC_HIDDEN"<br>![IndicatorSetStyle](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/IndicatorSetStyle.png "IndicatorSetStyle")
 
###### Adding Extra Line Spaces

Another difference is that notepad++ has 2 extra pixels spacing for each line than wxStyledTextCtrl has by default.  To add these, we do the following:

- open the "White space" group
- set the "SetExtraAscent" key to have value 1
- set the "SetExtraDescent" key to also have value 1 <br>![SetExtraDescent](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/SetExtraDescent.png "SetExtraDescent")
  
#### Drawing the fold margin

The final thing I want to show is how to draw the plus and minus boxes in the fold margin as notepad++ does:  

![the fold margin in notepad++](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/folding.png "notepad++ folding")

When we click the minus symbol on line 21, it collapses all the code from line 21 to 26 into a single line:

![Folded Code](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/folded.png "Folded Code")

I should mention that clicking the symbols in the method explorer won't actually cause the code to fold.  However, in the next section of the tutorial, I'll discuss how how can write an event handler for your program to accomplish the folding.  

Drawing the fold symbols is done in 2 parts.  First we define additional lexer properties so that the lexer tells us how code should be folded.  Secondly, we set additonal markers.


The first part is to set set the lexer properties.  
- return to the lexer group and open "SetLexer" subgroup. 
- the values shown in the check boxes may not be 100% correct, so run down the list and
	+ toggle anything true to false
	+ toggle anything false to true and then back to false
- this guarentees that all of the lexer properties are, in fact, set false.
- now to make the code fold as notepad++ does, make the following true: 
	+ styling.within.preprocessor 
	+ lexer.cpp.update.preprocessor 
	+ fold 
	+ fold.cpp.syntax.based
	+ fold.comment 
	+ fold.cpp.comment.multiline
	+ fold.preprocessor
	+ fold.at.else
- without doing that second step, some of these may show as true even if they're not actually true (fixing this is very high on the todo list for this method explorer, but please bear with me for now).

When done the lexer options should look like so:

![wxStyledTextCtrl lexer options](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/foldOptions.png "Lexer options")

By now we have something like the following:

![Bad Folding Markers](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/foldingInit.png "Bad Folding Markers")


This looks nothing like what we wanted.  The problem is that wxStyledTextCtrl uses a white circle as the default for all markers.  To make the margin look right, we need to tell it to use the markers we want:
  
- open the markers group 
- open the marker definitions subgroup <br> ![Markers Group](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/markersGroup.png "Markers Group")
- scroll down to wxSTC_MARKNUM_FOLDEREND (Marker 25) and
	+ set MarkerDefine to wxSTC_MARK_BOXPLUSCONNECTED
	+ set MarkerSetForeground to (243,243,243)
	+ set MarkerSetBackground to Grey or (128,128,128) <br> ![MarkerDefine](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/MarkerDefine.png "MarkerDefine")
- repeat the same process for wxSTC_MARKNUM_FOLDEROPENMID to wxSTC_MARKNUM_FOLDEROPEN using the same colors but change the marker definition as follows

|Marker                     |MarkerDefine                |
|---------------------------|----------------------------|
|wxSTC_MARKNUM_FOLDEROPENMID|wxSTC_MARK_BOXMINUSCONNECTED|
|wxSTC_MARKNUM_FOLDERMIDTAIL|wxSTC_MARK_TCORNER          |
|wxSTC_MARKNUM_FOLDERTAIL   |wxSTC_MARK_LCORNER          |
|wxSTC_MARKNUM_FOLDERSUB    |wxSTC_MARK_VLINE            |
|wxSTC_MARKNUM_FOLDER       |wxSTC_MARK_BOXPLUS          |
|wxSTC_MARKNUM_FOLDEROPEN   |wxSTC_MARK_BOXMINUS         |

- for any marker, set the MarkerEnableHighlight key to true.  (In the property grid, setting this key for 1 marker automatically sets all the other markers to have the same value.) <br> ![MarkerEnableHighlight](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/MarkerEnableHighlight.png "MarkerEnableHighlight")





	

	

 

 