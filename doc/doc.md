## wxStyledTextCtrl Method and Event Explorer 

wxStyledTextCtrl is a wrapper for the Scintilla text editing component.  As such it includes over 600 methods.  This breaks those methods down by the category they are listed in the scintilla documentation and presents them in a property grid.  Each method can take 0, 1, or 2 parameters.  Any parameters are set with child items in the property grid.  Some methods are set automatically, some require the user to press a button in the property grid to take effect.

![wxStyledTextCtrl Method and Event Explorer Screen Shot](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/sc-2.png "Screen Shot 1")

The 5 main components of the application are shown in the screen shot above.
 - in the upper left is a wxStyledTextCtrl window.
 - in the upper right is a property grid.  Setting properties in the property grid changes the state of the wxStyledTextCtrl.
 - in the middle is a listing of the events emitted by the wxStyledTextCtrl.  No events will be logged unless they are selected in from the "Logged Events" menu item.
 - in the lower left is a (slightly modified) version of the scintilla documentation.  As how select an item in the property grid, the documentation for that item is scrolled into view.
 - in the lower right is a (heavily edited) version of the wxStyledTextCtrl documentation.  As with the Scintilla documentation, the appropriate section is scrolled into view when an item is selected in the property grid.

## Making wxStyledTextCtrl look like notepad++ 

The following shows a fragment of the stcMain.cpp file from this repo pasted into a freshly created wxStyledTextCtrl window and the same file opened in notepad++.

![Raw wxStyledTextCtrl vrs notepad++](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/stc_np++comp.png "Comparison 1")

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

#### Translating the properties to code

There are many more options that need to be set.  But before moving on, let me pause for a second to discuss how you can translate the properties that are set in the property grid to code that you use in your program.  In the work above, we changed the margin width for margin 0 to 30.  The code to accomplish this would be `m_stc->SetMarginWidth(0,30)`.  Notice that the name of the method that needs to be called is the same as the key that was set in the property grid.  

This command supposes your wxStyledTextCtrl is named m_stc. You would, of course, replace "m_stc" with the name for the wxStyledTextCtrl used in your code

Next we changed the width and mask of margin 2.  These are accomplished with "m_stc->SetMarginWidth(2,16)" and "m_stc->SetMarginMask(2,wxSTC_MASK_FOLDERS)".  For almost all the things to be set, the name of the method to call is the key in the property grid.
 
#### Setting the lexer (and repairing the damage setting the lexer does)

The next step is to set the lexer to tell the wxStyledTextCtrl that we're working with a c++ file and not just any type of text file.

 - open the lexer group
 - change "SetLexer" from "wx_STC_LEX_CONTAINER" to "wx_STC_LEX_CPP"

Now, somewhat surprisingly, the next time you click in the wxStyledTextCtrl window, all the text seems to disappear.  It's actually been colored white.  That seems to happen the first time a lexer value is set.  I'm not sure why wxStyledTextCtrl/Scintilla does that, but as a programmer, it's good to know that so we can fix it.  With the method and event explorer, we've seen a surprising outcome happen in real time.  We can fix it as follows.

- open the "Style definition" group
- open the "predefined number styles" subgroup.
- open the "wxSTC_STYLE_DEFAULT" group.  As the name suggests, this sets the default style options.  Amongst the options that can be set are the font name, the font size, the font color, whether to use bold, italic, or underline and so on.  
- change the "StyleSetForeground" to black - rgb(0,0,0).  
- while we're here, notepad++ uses "courier new" and font size 10 by default, so we can set those options under "StyleSetFaceName" and "StyleSetSize"
- also while we're in the "Style definition" group, we can fix the colors for the line number margin.  Open the wx_STC_STYLE_LINENUMBER subgroup.
	+ set StyleSetForeground to rgb(128,128,128)
	+ set StyleSetBackground to rgb(228,228,228)
		
I have no clue why those options are set in the style definition group and not the the margin group, but that is a quirk of Scintilla that we have to live with.

#### Coloring constants and keywords

The next step is to color the constants and keywords of the language as notepad++ does.  This is done in 2 parts.  First we return to the lexer group and set the keywords.  

- open the lexer group if its not still open
- open the "SetKeyWords" subgroup
- open the "Primary keywords and identifiers (Keyword set 0) property and set the "keywords" property to:
	+  `if else switch case default break goto return for while do continue typedef sizeof NULL new delete throw try catch namespace`
- open the "Secondary kewyords and identifiers (Keyword set 1) property and set the "keywords" property to:
	+ `void struct union enum char short int long double float signed unsigned const static extern auto register volatile bool class private protected public friend inline template virtual asm explicit typename mutable`

Second, we need to set the style options for each category.  Open the "Style definition" group and then open the "Style 0 ... wxSTC_STYLE_DEFAULT-1" subgroup.  This will give us a list of the categories of words that the lexer recognizes.  For most of them we only need to set the text foreground color.  These are given in the following table:

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

Once all the colors are set, we also need to set wxSTC_C_WORD, wxSTC_C_OPERATOR, wxSTC_C_REGEX, and wxSTC_C_COMMENTDOCKEYWORDERROR to be bold.  Lets focus on the wxSTC_C_WORD category.  Open this category in the propgrid and try setting the StyleSetBold key to be true.  Nothing happens.  What we need to do is   

- select "Courier New" from the "StyleSetFaceName" key (even though that is the same as the default). 
- this then sets the size back to 8, so we need to change it to back to 10.
- now we can toggle the boldness with the the "StyleSetBold" key.

Repeat this process for the other 3 categories.  Now as a programmer, we now know that for each categories some of the style options such as color can be set using the default font, but other such as boldness will require us to respecify the font name before we can set them.  

#### Highlighting the current line	

Notepad++ also highlights the line containing the cursor.  This behavior can be set as follows:

- open the "Caret, selection, and hotspot styles" group.
- set the "SetCaretLineVisible" key to true.
- to match the color that notepad++ uses, set the "SetCaretLineBackground" to rgb(232,232,255)
	
#### Fixing a few more things:

By now the wxStyledTextCtrl is closely resembles the notepad++ window.  Lets look at a comparison: 

![Squigles](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/comp2.png "A second comparison")

One of the remaining differences is that some of the lines in the wxStyledTextCtrl such as lines 11 and 15 have an blue squigle under them.  This is an example of a style byte indicator.  They can be used by wxStyledTextCtrl to indicate syntax errors or other things about the code that should be brought to the user's attention.  But here it's just annoying.  We can turn it off as follows:

- return the the lexer group.
- open the "SetLexer" subgroup.  This subgroup only appears once a lexer has been selected and the options in this subgroup vary from lexer to lexer.
- when the cpp lexer is selected, the option that causes that blue squigle is "lexer.cpp.track.preprocessor".  Set that property to false.  You may have to toggle it a few times to make it go away.
	
Another difference is that notepad++ has 2 extra pixels spacing for each line than wxStyledTextCtrl has by default.  To add these, we do the following:

- open the "White space" group
- set the "SetExtraAscent" key to have value 1
- set the "SetExtraDescent" key to also have value 1
  
#### Using the bookmark margin

Next I want to give an example of how notepad++ uses its bookmark margin.  When the user clicks the bookmark margin it adds a shiny blue circle like so:

![A bookmarked line in notepad++](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/bookmarkedlne.png "A bookmarked line")

The actual adding of the circle is done by an event handler.  Suppose we want to add a blue circle to add a bookmark at line 20.  This is done in 2 steps.  First we define a marker.  That will assign it to a number between 1 and 32.  Next we add that marker to a line.  The step of adding a marker for that blue circle **SHOULD** be as follows:

- open the markers group
- open marker 0
- select the button with the "MarkerDefineBitmap" key to open an image file.  The file corresponding to that shiny blue circle is from the scintilla icon package and is included with this repo as "scintilla\16x16\gem_blue.xpm".
- we can open some some of the files in the "scintilla\16x16\" folder this way, but not that particular one for some reason.
- what wxStyledTextCtrl is trying to do is open the image file, convert it to a wxBitmap, save that bitmap to xpm data, and then pass that xpm data to scintilla.  Since the file is already xpm data, this is 2 unnecessary steps.  And there seems to be a bug in the wxWidgets code for opening xpm files that won't let it open this particular file.
	
To get around this, with this method and event explorer, I've included the xpm data for all of those files directly into the program and provided an alternate implementation "SCI_MARKERDEFINEPIXMAP" that calls the scintilla method directly with that xpm data.  So instead:

- open the markers group
- open marker 0
- open alternative implimentations -> SCI_MARKERDEFINEPIXMAP
- from the drop down list, select "gem_blue.xpm"
	
That defines the contents of that file to be marker 0.  We can add that marker to a line as follows:

- in the marker group, open the "MarkerAdd" key
- set the line key to be the line number we want to add the marker to.  The lines for this method start at zero, so to add the marker to the line with line number 20, we use line=19.
- set the marker key to be the marker we want to add.  In this case, that's marker 0, and the key already has that value; so we don't actually need to change anything.
- press the button in the "MarkerAdd" key to call the method.
	
If you want, you can now go back and chose other options from SCI_MARKERDEFINEPIXMAP menu and the marker will be updated in real time.  You can also chose an option from MarkerDefine to use one of the options that are included by wxStyledTextCtrl.  Finally you can set width and height options, then select MarkerDefineRGBAImage image and draw your own marker.

#### Drawing the fold margin

The final thing I want to show is how to draw the fold symbols in the fold margin as notepad++ does.  Clicking the symbols won't actually cause the code to fold - that is done by an event handler that is beyond the scope of this method explorer.  Drawing the fold symbols is done in 2 parts.  First we define additional lexer properties so that the lexer tells us how code should be folded.  Secondly, we set additonal markers.

![the fold margin in notepad++](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/folding.png "notepad++ folding")

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

![wxStyledTextCtrl lexer options](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/foldOptions.png "Lexer options")

By now we have something like the following:

![wxStyledTextCtrl with markers set incorrectly](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/foldingInit.png "Wrong markers")

This looks nothing like what we wanted.  The problem is that wxStyledTextCtrl uses a white circle as the default for all markers.  To make the margin look right, we need to tell it to use the markers we want:  
- return to the markers group
- open the marker definitions subgroup if its not still open
- for markers 25 - 31 (wxSTC_MARKNUM_FOLDEREND - wxSTC_MARKNUM_FOLDEROPEN) we need to change:
	+ set MarkerSetForeground to rgb(243,243,243)
	+ set MarkerSetBackground to Grey or rgb(128,128,128)
- for wxSTC_MARKNUM_FOLDEREND set MarkerDefine to wxSTC_MARK_BOXPLUSCONNECTED
- for wxSTC_MARKNUM_FOLDEROPENMID set MarkerDefine to wxSTC_MARK_BOXMINUSCONNECTED
- for wxSTC_MARKNUM_FOLDERMIDTAIL set MarkerDefine to wxSTC_MARK_TCORNER
- for wxSTC_MARKNUM_FOLDERTAIL set MarkerDefine to wxSTC_MARK_LCORNER
- for wxSTC_MARKNUM_FOLDERSUB set MarkerDefine to wxSTC_MARK_VLINE
- for wxSTC_MARKNUM_FOLDER set MarkerDefine to wxSTC_MARK_BOXPLUS
- for wxSTC_MARKNUM_FOLDEROPEN set MarkerDefine to wxSTC_MARK_BOXMINUS 
- for any marker, set the MarkerEnableHighlight key to true.  (In the property grid, setting this key for 1 marker automatically sets all the other markers to have the same value.)  
        
#### Folding

As I mentioned, this makes the fold margin appear correct, but it will not fold on its own without additional programming.  Lets explore what might be required for that programming.  Suppose we want to fold line number 306. As shown in the following snippet:

![wxStyledTextCtrl Method and Event Explorer Screen Shot](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/unfolded.png "Unfolded Code")
  
This is accomplished programmatically as follows:

- open Folding group
- open the ToggleFold property
- recall that lines start at 0 while line numbers start at 1, so the line with line number 306 is line 305.
- enter 305 for the line.  
- press the button next to the ToggleFold key to call the method.

![wxStyledTextCtrl Method and Event Explorer Screen Shot](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/folded.png "Folded Code")
  
#### Putting what we've learned into code

Assuming our wxStyledTextCtrl is named m_stc, we can translate everything we've done above directly into code.  For each step of the process, the method to call has the same name as the key that was set in the propgrid.  Any arguments needed  for the method are either given by the value of the key or the value of child properties of that key.  The complete code is as follows:

```c++
    m_stc->SetMarginWidth(0,30);
    m_stc->SetMarginWidth(2,14);
    m_stc->SetMarginMask(2,wxSTC_MASK_FOLDERS);
    m_stc->SetFoldMarginColour(true,wxColor(255,255,255));
    m_stc->SetFoldMarginHiColour(true,wxColor(233,233,233));
    m_stc->SetLexer(wxSTC_LEX_CPP);

    m_stc->StyleSetFaceName(wxSTC_STYLE_DEFAULT,"Courier New");
    m_stc->StyleSetSize(wxSTC_STYLE_DEFAULT,10);
    m_stc->StyleSetForeground(wxSTC_STYLE_LINENUMBER,wxColor(128,128,128));
    m_stc->StyleSetBackground(wxSTC_STYLE_LINENUMBER,wxColor(228,228,228));

    m_stc->SetKeyWords(0,"if else switch case default break goto return for while do continue typedef sizeof NULL new delete throw try catch namespace");
    m_stc->SetKeyWords(1,"void struct union enum char short int long double float signed unsigned const static extern auto register volatile bool class private protected public friend inline template virtual asm explicit typename mutable");

    m_stc->StyleSetForeground(wxSTC_C_COMMENT,               wxColor(0,128,0));
    m_stc->StyleSetForeground(wxSTC_C_COMMENTLINE,           wxColor(0,128,0)  );
    m_stc->StyleSetForeground(wxSTC_C_COMMENTDOC,            wxColor(0,128,128)  );
    m_stc->StyleSetForeground(wxSTC_C_NUMBER,                wxColor(255,128,0) );
    m_stc->StyleSetForeground(wxSTC_C_WORD,                  wxColor(0,0,255));
    m_stc->StyleSetForeground(wxSTC_C_STRING,                wxColor(128,128,128) );
    m_stc->StyleSetForeground(wxSTC_C_CHARACTER,             wxColor(128,128,128) );
    m_stc->StyleSetForeground(wxSTC_C_PREPROCESSOR,          wxColor(128,64,0) );
    m_stc->StyleSetForeground(wxSTC_C_OPERATOR,              wxColor(0,0,128));
    m_stc->StyleSetForeground(wxSTC_C_REGEX,                 wxColor(0,0,0) );
    m_stc->StyleSetForeground(wxSTC_C_COMMENTLINEDOC,        wxColor(0,128,128));
    m_stc->StyleSetForeground(wxSTC_C_WORD2,                 wxColor(128,0,255));
    m_stc->StyleSetForeground(wxSTC_C_COMMENTDOCKEYWORD,     wxColor(0,128,128));
    m_stc->StyleSetForeground(wxSTC_C_COMMENTDOCKEYWORDERROR,wxColor(0,128,128) );

    m_stc->StyleSetFaceName(wxSTC_C_WORD,"Courier New");
    m_stc->StyleSetSize(wxSTC_C_WORD,10);
    m_stc->StyleSetBold(wxSTC_C_WORD,true);

    m_stc->StyleSetFaceName(wxSTC_C_OPERATOR,"Courier New");
    m_stc->StyleSetSize(wxSTC_C_OPERATOR,10);
    m_stc->StyleSetBold(wxSTC_C_OPERATOR,true);

    m_stc->StyleSetFaceName(wxSTC_C_REGEX,"Courier New");
    m_stc->StyleSetSize(wxSTC_C_REGEX,10);
    m_stc->StyleSetBold(wxSTC_C_REGEX,true);

    m_stc->StyleSetFaceName(wxSTC_C_COMMENTDOCKEYWORD,"Courier New");
    m_stc->StyleSetSize(wxSTC_C_COMMENTDOCKEYWORD,10);
    m_stc->StyleSetBold(wxSTC_C_COMMENTDOCKEYWORD,true);

    m_stc->SetCaretLineVisible(true);
    m_stc->SetCaretLineBackground(wxColor(232,232,255));

    m_stc->SetProperty("lexer.cpp.track.preprocessor","0");
    m_stc->SetExtraAscent(1);
    m_stc->SetExtraDescent(1);

    m_stc->SetProperty("styling.within.preprocessor",   "1");
    m_stc->SetProperty("lexer.cpp.allow.dollars",       "0");
    //m_stc->SetProperty("lexer.cpp.track.preprocessor","");
    m_stc->SetProperty("lexer.cpp.update.preprocessor", "1");
    m_stc->SetProperty("lexer.cpp.triplequoted.strings","0");
    m_stc->SetProperty("lexer.cpp.hashquoted.strings",  "0");
    m_stc->SetProperty("fold",                          "1");
    m_stc->SetProperty("fold.cpp.syntax.based",         "1");
    m_stc->SetProperty("fold.comment",                  "1");
    m_stc->SetProperty("fold.cpp.comment.multiline",    "1");
    m_stc->SetProperty("fold.cpp.comment.explicit",     "0");
    m_stc->SetProperty("fold.cpp.explicit.start",       "");
    m_stc->SetProperty("fold.cpp.explicit.end",         "");
    m_stc->SetProperty("fold.cpp.explicit.anywhere",    "0");
    m_stc->SetProperty("fold.preprocessor",             "1");
    m_stc->SetProperty("fold.compact",                  "0");
    m_stc->SetProperty("fold.at.else",                  "1");

    m_stc->MarkerDefine(wxSTC_MARKNUM_FOLDEREND,wxSTC_MARK_BOXPLUSCONNECTED);
    m_stc->MarkerSetForeground(wxSTC_MARKNUM_FOLDEREND,wxColor(243,243,243));
    m_stc->MarkerSetBackground(wxSTC_MARKNUM_FOLDEREND,wxColor(128,128,128));

    m_stc->MarkerDefine(wxSTC_MARKNUM_FOLDEROPENMID,wxSTC_MARK_BOXMINUSCONNECTED);
    m_stc->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPENMID,wxColor(243,243,243));
    m_stc->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPENMID,wxColor(128,128,128));

    m_stc->MarkerDefine(wxSTC_MARKNUM_FOLDERMIDTAIL, wxSTC_MARK_TCORNER);
    m_stc->MarkerSetForeground(wxSTC_MARKNUM_FOLDERMIDTAIL,wxColor(243,243,243));
    m_stc->MarkerSetBackground(wxSTC_MARKNUM_FOLDERMIDTAIL,wxColor(128,128,128));

    m_stc->MarkerDefine(wxSTC_MARKNUM_FOLDERTAIL,wxSTC_MARK_LCORNER);
    m_stc->MarkerSetForeground(wxSTC_MARKNUM_FOLDERTAIL,wxColor(243,243,243));
    m_stc->MarkerSetBackground(wxSTC_MARKNUM_FOLDERTAIL,wxColor(128,128,128));

    m_stc->MarkerDefine(wxSTC_MARKNUM_FOLDERSUB,wxSTC_MARK_VLINE);
    m_stc->MarkerSetForeground(wxSTC_MARKNUM_FOLDERSUB,wxColor(243,243,243));
    m_stc->MarkerSetBackground(wxSTC_MARKNUM_FOLDERSUB,wxColor(128,128,128));

    m_stc->MarkerDefine(wxSTC_MARKNUM_FOLDER,wxSTC_MARK_BOXPLUS);
    m_stc->MarkerSetForeground(wxSTC_MARKNUM_FOLDER,wxColor(243,243,243));
    m_stc->MarkerSetBackground(wxSTC_MARKNUM_FOLDER,wxColor(128,128,128));

    m_stc->MarkerDefine(wxSTC_MARKNUM_FOLDEROPEN,wxSTC_MARK_BOXMINUS);
    m_stc->MarkerSetForeground(wxSTC_MARKNUM_FOLDEROPEN,wxColor(243,243,243));
    m_stc->MarkerSetBackground(wxSTC_MARKNUM_FOLDEROPEN,wxColor(128,128,128));

    m_stc->MarkerEnableHighlight(true);
``` 




	

	

 
