#### An Introduction to the Event Explorer

Other documentation available:
 - [An Introduction to Scintilla for wxStyledTextCtrl Programmers](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/IntroductionToScintilla.md)
 - [An Introduction to the Method Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/MethodExplorer.md)

In addition, to give some concrete examples of configuring the appearance and behavior of a wxStyledTextCtrl window, I've written a 3 part series on making the window look like the default appearance for notepad++.

 - [Simulating Notepad++ Part1 - Basic Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part1_BasicAppearance.md)
 - [Simulating Notepad++ Part2 - Working with the Margins](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part2_Margins.md)
 - [Simulating Notepad++ Part3 - Advanced Appearance](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/SimulatingNotepad++Part3_AdvancedAppearance.md)

## Introduction 

In the previous section, I introduced the method explorer which can be used to set properties, get information, and perform actions.  In this section I want to talk about the event explorer.  The event explorer looks something like the following:

![The Event Explorer](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/eventLog.png "The Event Explorer") 

A wxStyledTextCtrl window can raise 31 different types of events.  For example, it will cause a wxEVT_STC_MODIFIED when any type of modification is made to the window.  It will cause a wxEVT_STC_ROMODIFYATTEMPT event when the user attempts to modify a window that has been set read only.

If we chose to explore an event type, the event explorer shows us when events of that type are fired and the information that is available for an handler.  To explore an event type, simply open the Logged Events menu and select the type of event you want to explore:

![The Logged Events Menu](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/loggedEvents.png "The Logged Events Menu") 

## Exploring wxEVT_STC_MODIFIED Events

To explore wxEVT_STC_MODIFIED, simply select "Logged Events->wxSTC_MODIFIED" from the menu:

![Logging wxEVT_STC_MODIFIED Events](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/eventLogModified.png "Logging wxEVT_STC_MODIFIED Events") 

Now any modifications we make to the wxStyledTextCtrl will show up in the event explorer.  For example when I type 'a' in the window the, the event explorer looks like the following.

![The Event Explorer After Typing](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/eventLogAfterA.png "The Event Explorer After Typing") 

As we can see, the information available in the event handler are the event type, length, modification type, position, and text.  All of the other fields are blank because they are not relevant to the this event type.

The length information is 1 because only 1 character was typed.  If we had pasted a longer string into the window, the length would give the length of that string.  The position is simply the position in the file where the typing occurred.  And the text is obviously just the text that was entered.

The "modification type" is a little less obvious.  These are flag parameters.  In the example given above, they had values of 1040 and 17.  1040 is 10000010000 in binary or 0x10 & 0x400 in hex.  17 is 10001 in binary or 0x01 & 0x10 in hex.  If we look these up in the Scintilla documentation under the "SCN_MODIFIED" section, we see the following.

|Value|Meaning                                         |
|-----|------------------------------------------------|
|0x01 |Text has been inserted into the document.       |
|0x10 |Information: the operation was done by the user.|
|0x400|Text is about to be inserted into the document. |

Thus, the first entry in the event explorer tells us that the operation was done by the user and text is about to be inserted.  The second entry tells us that text has been inserted and that the operation was done by the user.

## Exploring wxEVT_STC_ZOOM Events

To explore wxEVT_STC_ZOOM, simply select "Logged Events->wxSTC_ZOOM" from the menu:

![Logging wxEVT_STC_ZOOM Events](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/eventLogZoom.png "Logging wxEVT_STC_ZOOM Events") 

Now that this event type is being explored, let's raise a zoom event by selectiong Zoom In from the property grid:

![Zooming In](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/ZoomIn.png "Zooming In") 

Now the event explorer will look something like the following:

![The Event Explorer After Zooming](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/eventLogAfterZoom.png "The Event Explorer After Zooming") 

As we can see, a zoom event has been raised, but all the fields are blank.  So in handler for a zoom event, we will know that a zoom event has occurred, but don't have any other information to use.  

An obvious question to ask is then "how are zoom events useful?"  Here's one thing we might do with a zoom event.  Suppose we want to set a line number marging to be large enough to show "9999".  We can get the number of pixels needed with the TextWidth method in the "Selection and information" group.  Here is an example:

![The TextWidth Method](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/textWidth1.png "The TextWidth Method") 

As we can see, 24 pixels are needed.  Now suppose we zoom in exactly as we did before:

![Zooming In](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/ZoomIn.png "Zooming In") 

Now if we call the TextWidth method again:

![The TextWidth Method](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/img/textWidth2.png "The TextWidth Method") 

As we can see 28 pixels are now needed.  So if we have some elements in our window that rely on text being a certain size, one thing we might do with a zoom event handler is recalculate the size of those text elements with the new zoom factor. 











		 