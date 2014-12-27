wxStyledTextCtrl is a wrapper for the Scintilla text editing component.  As such it includes over 600 methods.  This breaks those methods down by the category they are listed in the scintilla documentation and presents them in a property grid.  Each method can take 0, 1, or 2 parameters.  Any parameters are set with child items in the property grid.  Some methods are set automatically, some require the user to press a button in the property grid to take effect.

![wxStyledTextCtrl Method and Event Explorer Screen Shot](https://github.com/NewPagodi/wxSTCmee/blob/master/doc/sc.png "Screen Shot 1")

The 5 main components of the application are shown in the screen shot above.
 - in the upper left is a wxStyledTextCtrl window.  Initially it is its default state.
 - in the upper right is a property grid.  Setting properties in the property grid changes the state of the wxStyledTextCtrl.
 - in the middle is a listing of the events emitted by the wxStyledTextCtrl.  No events will be logged unless they are selected in from the "Logged Events" menu item.
 - in the lower left is a (slightly modified) version of the scintilla documentation.  As how select an item in the property grid, the documentation for that item is scrolled into view.
 - in the lower right is a (heavily edited) version of the wxStyledTextCtrl documentation.  As with the Scintilla documentation, the appropriate section is scrolled into view when an item is selected in the property grid.