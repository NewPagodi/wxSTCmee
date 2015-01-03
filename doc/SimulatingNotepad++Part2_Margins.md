## Simulating Notepad++ Part2 - Working with the Margins

Other documentation available:
 - [An Introduction to Scintilla for wxStyledTextCtrl Programmers](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/DocPart1_IntroductionToScintilla.md)
 - [An Introduction to the Method Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/DocPart2_MethodExplorer.md)
 - [An Introduction to the Event Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/DocPart3_EventExplorer.md)
 
In addition, to give some concrete examples of configuring the appearance and behavior of a wxStyledTextCtrl window, I've written a 3 part series on making the window look like the default appearance for notepad++.

 - [Simulating Notepad++ Part1 - Basic Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part1_BasicAppearance.md)
 - [Simulating Notepad++ Part3 - Advanced Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part3_AdvancedAppearance.md)

 
## Introduction

In the previous tutorial, I discussed how to make a wxStyledTextCtrl window have the same basic appearance as notepad++.  In this part of the tutorial I want to discuss how to use information from the event explorer to write event handlers for the margins. 
  
#### Using the Bookmark Margin

Next I want to give an example of how notepad++ uses its bookmark margin.  When the user clicks the bookmark margin it adds a shiny blue circle like so:

![A bookmarked line in notepad++](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/bookmarkedlne.png "A bookmarked line")

The actual adding of the circle is done by an event handler.  Suppose we want to add a blue circle to add a bookmark at line 18.  This is done in 2 steps.  First we define a marker.  That will assign it to a number between 0 and 31.  Next we add that marker to a line.  The step of adding a marker for that blue circle **SHOULD** be as follows:

- open the markers group
- open the marker definitions
- open marker 0
- select the button with the "MarkerDefineBitmap" key to open an image file.  The file corresponding to that shiny blue circle is from the scintilla icon package and is included with this repo as "scintilla\16x16\gem_blue.xpm".
- we can open some some of the files in the "scintilla\16x16\" folder this way, but not that particular one for some reason.
- what wxStyledTextCtrl is trying to do is open the image file, convert it to a wxBitmap, save that bitmap to xpm data, and then pass that xpm data to scintilla.  Since the file is already xpm data, this is 2 unnecessary steps.  And there seems to be a bug in the wxWidgets code for opening xpm files that won't let it open this particular file.

###### Defining the Marker

To get around this, with this method and event explorer, I've included the xpm data for all of those files directly into the program and provided an alternate implementation "SCI_MARKERDEFINEPIXMAP" that calls the scintilla method directly with that xpm data.  So instead:

- open the "Markers" group
- open the "Marker definitions" subgroup
- open the "Marker 0" item
- scroll down to "Alternative implimentations -> SCI_MARKERDEFINEPIXMAP"
- from the drop down list, select "gem_blue.xpm" <br>![SCI_MARKERDEFINEPIXMAP](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/MarkerDefineBitmap.png "SCI_MARKERDEFINEPIXMAP")
	
###### Adding the Marker to a Line
	
That defines the contents of that file to be marker 0.  We can add that marker to a line as follows:

- in the marker group, open the "MarkerAdd" key
- set the line key to be the line number we want to add the marker to.  The lines for this method start at zero, so to add the marker to the line with line number 18, we use line=17.
- set the marker key to be the marker we want to add.  In this case, that's marker 0, and the key already has that value; so we don't actually need to change anything.
- press the button in the "MarkerAdd" key to call the method. <br>![MarkerAdd](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/MarkerAdd3.png "MarkerAdd")

###### Deleting the Marker from a Line

If we want to delete the marker, we

- open the MarkerDelete item
- set line to 17
- set marker to 0
- press the button in the MarkerDelete value area <br> ![MarkerDelete](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/MarkerDelete.png "MarkerDelete")

###### Detecting a Marker

So now we know how to add a marker to the symbol margin, and we know how to delete it when we don't want it any more.  How can we tell if a line number has a certain marker?  We can use the MarkerGet method.  When this method is called with a line number, it returns a 32 bit integer such that bit 0 is 1 if that line has marker 0, bit 1 is 1 if that line has marker 1, and so on.  So if we called it with line 17 now, we would get the following:

![MarkerGet2](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/MarkerGet2.png "MarkerGet2")

All the bits are 0 since we just deleted the only marker that line had.  If we add marker 0 back, we would get the following:

![MarkerGet1](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/MarkerGet1.png "MarkerGet1")
 
Now bit 0 is 1 since that line has marker 0.  

If we look at the Code Log window, we would see lines like:

```c++
m_stc->MarkerAdd(17,0);
m_stc->MarkerDelete(17,0);
m_stc->MarkerGet(17);
```

###### Detecting Mouse Clicks in the Symbol Margin

A wxStyledTextCtrl window won't raise an event for a mouse click in a margin unless that margin has been made sensitive.  This can be done as follows:

- open the "Margins" group
- in our case, the symbol margin is margin 1, so open the margin 1 item
- change the "SetMarginSensitive" item to true <br> ![SetMarginSensitive](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/SetMarginSensitive.png "SetMarginSensitive")

###### Observing a Margin Click Event

Now we want to see what kind of information we get in an wxEVT_STC_MARGINCLICK event.  Make sure the event explorer is show and then select "Logged Events->wxSTC_MARGINCLICK" from the menu:

![wxSTC_MARGINCLICK](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/wxSTC_MARGINCLICK.png "wxSTC_MARGINCLICK")

Now if we click the symbol margin on line number 18 (ie line 17) like so:

![Clicking in the Margin](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/MarginCursor.png "Clicking in the Margin")

We might see something like the following in the event log:

![The Event Log After a Margin Click](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/marginClickEvent.png "The Event Log After a Margin Click")

I had the file "sample.cpp" from this repo pasted into the wxStyledTextCtrl window.  If you had other content in the window, you would obviously see different output.

As we can see the event type, the margin, and the position are given.  All of the other pieces of information are blank since they are not used by this event type.  Notice that the event does not supply the line number of the margin click.  Instead it gives a position that is the first position of the line next to the place that was clicked.  

###### Recovering the Line Number

In the example above, it was position information available in the event handler was 404.  I obviously know that this belongs to line number 18 (ie line 17) since I just clicked there.  But the event handler wouldn't know that.  

We can convert the position to a line using the LineFromPosition method as follows:

- open the "Selection and information" group
- scroll all the way down to LineFromPosition and open that item
- enter 404 for that position
- press the button for the LineFromPosition item <br> ![LineFromPosition](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/LineFromPosition.png "LineFromPosition")

In the case above, the method has returned line 17 (ie line number 18).

###### Putting This All Together

Now what we want to do is when the symbol margin is clicked, we want to check if the line next to that click has the blue gem marker.  If it does not, then we want to add it to indicate that that line is bookmarked.  If it is already there, then we want to remove it to indicate that the bookmark has been removed.

We can put all of the pieces above together to do this.  An event handler that accomplishes this might look something like the following:

```c++
void m_STCFrame::onMarginClick(wxStyledTextEvent& event)
{
    int mar = event.GetMargin();
    int pos = event.GetPosition();
    int line = m_stc->LineFromPosition(pos );

    if(mar==1)
    {
        if( (m_stc->MarkerGet(line)&1)==1 )
        {
            m_stc->MarkerDelete(line,0);
        }
        else
        {
            m_stc->MarkerAdd(line,0);
        }
    }
}
```
  
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
  

