Welcome to try LZRobe! This is a software that provides a graphical user interface of the computer go software Leela Zero.

If you're interested in more information about Leela Zero, please browse the following website:

zero.sjeng.org

LZRobe can help you to play Go againt Leela Zero or analyze the Go game records with Leela Zero to improve your strength of the game.

This program is written in C++ pragramming language with a GUI Library named wxWidgets.

So if you would like to compile this program, you have to download and install the wxWidgets library first. Please look up the following website:

www.wxwidgets.org

It is not difficult to compile this program with Visual Studio or Code::Blocks.

If you try to compile this program, you should create a Win32 GUI empty project and add the files, including .h files, .cpp files, a .rc file and .bmp files.

Don't forget appending include and lib dictionaries of wxWidgets in the setting of your project.

Code::Blocks supports creating a wxWidgets project containing the path of wxWidgets, this maybe make it simpler to compile this program.

After you have compiled this program successfully, I tell you how to use this program.

The icon of this program is a dog's head. Because the pronounciation of "Go" means "dog" in Chinese.

Once you open this program, you will see a tool bar below the menu. All the functions of this program can be found in the tool bar.

There is a run button in the tool bar. You can start Leela Zero with this button.

If you did not set the path of Leela Zero or the weight file, when you push the run button, file dialogs will appear to tip you choose the leela zero executable file and the weight file.

When Leela Zero are started successfully, after several seconds, the gray buttons will become colored. The run button will become a close button to stop Leela Zero.

If you want to change the engine or the weight file during the game, you can stop the engine first, then change the engine or weight file in the edit menu, and start the engine last.

Then the newly started engin will load the game records automatically. Even if the Leela Zero collapsed, LZRobe will restart it and load the game records with a few second to keep this game.

The left button of mouse is used to put stones on the gameboard. The right button of mouse is used to cancel a move.

But if you decide to put new stones at different position after canceled several moves, the previous variation will not be kept.

The button with dogs' heads are used to play again computer. The color of the background under the dogs' heads indicates the stone color that the computer plays.

If you push both of the two buttons with dogs' heads, you will see the computer plays agains itself.

The number in the spinbox on the right of the time label is used to set the think time of computer. The unit of the time is one second.

For example, if you set the number as 5, the computer will put a stone on the gameboard in 5 seconds after the oppoment's move.

If you change the number of thinking time, it will work when you ask the computer play with one side.

The button with a question mark is used to analyze the game record. The analyze result will be refreshed with a frequency.

The frequnecy can be set with the spinbox on the right of the interval label. The unit of the refresh interval is centisecond.

For example, if you set the number as 50, the analyze result will refresh twice in one second.

If you put the mouse at the analyzing point, the following steps will automatically be shown, where the letters indicates the consequence.

The button with an abcus is used to calculate the result of the game. Since the dead stones may not be removed from the gameboard, the result is not exactly the true result.

If you changed the path of Leela Zero or the Weight file, when you exit this program, a message box will ask you if you want to save this change.

If you choose saving this change, the paths of Leela Zero and Weight file will be stored in a file named "config.txt". Next time you start LZRobe, it will load the paths automatically.

Thanks for reading the introduction file! Welcome to modify these code to adapt more cases!
