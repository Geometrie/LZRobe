Welcome to try LZRobe! This is a software that provides a graphical user interface of the computer go software Leela Zero.

If you're interested in more information about Leela Zero, please browse the following website:

zero.sjeng.org

LZRobe can help you to play Go againt Leela Zero or analyze the Go game records with Leela Zero to improve your strength of the game.

This program is written in C++ pragramming language with a GUI Library named wxWidgets.

So if you would like to compile this program, you have to download and install the wxWidgets library first.Please look up the following website:

www.wxwidgets.org

It is not difficult to compile this program with Visual Studio or Code::Blocks.

If you try to compile this program, you should create a Win32 GUI empty project and add the files, including.h files, .cpp files, a .rc file, a .ico file and.bmp files.

Don't forget appending include and lib dictionaries of wxWidgets in the setting of your project.

Code::Blocks supports creating a wxWidgets project containing the path of wxWidgets, this maybe make it simpler to compile this program.

After you have compiled this program successfully, I tell you how to use this program.

The icon of this program is a dog's head. Because the pronounciation of \"Go\" means \"dog\" in Chinese.

Once you open this program, you will see a tool bar below the menu. All the functions of this program can be found in the tool bar.

The move turn and number of prisoners are shown in the left of the gameboard. The pass and resign choice are laid on the right of the game board. The status of engine will be shown in the status bar at the bottom of the main frame.

The game process are arranged from left to right with a wandering snake shape, where every column contains 25 steps. If you would like to jump to one step, you can click its related position with left button of your mouse.

The left button of the mouse is used to put stones, while the right button is used to undo a move. The game progress on the bottom right of the gameboard can be used to jump to any step.

In order to avoid a command jam cause Leela Zero collapse, retracting or jumping moves are not allowed during the waiting of the engine's opening. But putting stones on the gameboard is allowed.

The program does not support multi-branch game records. So if you try to start a new game or open a new game record from the menu or tool bar, the current record will be deleted

If you want to save the game record, the engine must be opening, and the save menu or tool bar only save the records on the gameboard.

So if you do not want to lose any game record, please go to the last step of the game before saving the game record.

There is a run button in the tool bar. You can start Leela Zero with this button.

If you did not set the path of Leela Zero or the weight file, when you push the run button, file dialogs will appear to tip you choose the Leela Zero executable file and the weight file.

You need not to fill any letter into the extra parameters, unless you are using a specified engine, such as dynamic komi.

When Leela Zero are started successfully, after several seconds, the gray buttons in the tool bar will become colored. The run button will become a close button to stop Leela Zero.

If you want to change the engine or the weight file during the game, you can stop the engine first, then change the engine or weight file path in the edit menu, and start the engine last.

Then the newly started engine will load the game records automatically. Even if the Leela Zero collapsed, LZRobe will restart it and load the game records with a few second to keep this game.

But if you decide to put new stones at different position after canceled several moves, the previous variation will not be kept.

The button with dogs' heads are used to play against Leela Zero. The color of the background under the dogs' heads indicates the stone color that the AI plays.

If you push both of the two buttons with dogs' heads, you will see the computer plays agains itself.

The number in the spinbox on the right of the \"think time\" label is used to set the think time of computer. The unit of the time is one second.

For example, if you set the number as 5, AI will put a stone on the gameboard in 5 seconds after the opponent's move.

If you change the number of thinking time, it will work when you ask the computer play with one side.

If you cancel AI to play one side when it is thinking the next move, it will keeping on until it think out this move. So you have to wait for its next move until the newest stone appears on the gamebord.

The button with a question mark is used to analyze the game record. The analyze result will be refreshed with a frequency.

The frequency can be set with the spinbox on the right of the \"refresh interval\" label. The unit of the refresh interval is centisecond.

For example, if you set the number as 50, the analyze result will refresh twice in one second.

In the analyzation, the points with green color are the most visited points, then come the blue points. The yellow and red points are less visited.

The numbers at the points with green color indicates the winrate and visits. The point with highest visits is usually the best point to select.

If you put the mouse at the analyzing point, the following steps will automatically be shown, where the letters indicates the consequence.

The lower case letters come first, and then the upper case. The maximum number to show of the following steps can be set with the slider on the right of the analyze length.

If there are two continuous pass (one  for each side), the game will end. Leela Zero would not analyze a terminated game.

So if you want to analyze a terminate game, the game record should be reloaded from the start, and the two pass steps or the resign step will be deleted, but the other moves will not be changed.

When the game approaches the end or one side have an extremely advantage, Leela Zero may have the pass choice. If you want to check the relative analyze, you can put the mouse on the pass point.

The button with an abcus is used to calculate the result of the game. Since the dead stones may not be removed from the gameboard, the result is not exactly the true result.

If you changed the path of Leela Zero or the Weight file path, when you exit this program, a message box will ask you if you want to save this change.

If you choose saving this change, the paths of Leela Zero and Weight file will be stored in a file named \"config.txt\".Next time you start LZRobe, it will load the paths automatically.

The author is trying to reduce the bugs of the program, but we are sorry that we cannot completely avoid the collapse of the program.

If once the program collapse while Leela Zero is running, please terminate Leela Zero with task manager lest it continue to occupy your hardware resource!

Thanks for reading the introduction file! Welcome to modify these code to adapt more cases!
