# qtres2dox

Link to original source code and creator: https://www.linux-apps.com/content/show.php/qtres2dox?content=160538

This app can be used to create a .dox input file from Qt .ui and .qrc files.
It is slightly modified so it will take more commandline arguments and it's ported to Windows.
The GUI was not updated so I would not recommend using it.

This app was built with VisualStudio 2015 and Qt 5.9 and tested under Windows 7/10


## Usage:
qres2dox -qrc [qt-resource File] -ui-path [path to ui files] -image-path [where to store UI mages] -dox [Doxygenout-file] -qt-version [Qt version e.g. 5.9] -qt-dir [Qt directory on drive]
