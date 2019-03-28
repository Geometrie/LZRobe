#ifndef INTERNATIONAL_H
#define INTERNATIONAL_H
#define LANGUAGE_CHINESE_SIMPLIFIED
#ifdef LANGUAGE_CHINESE_SIMPLIFIED
#define STR_NEW "新对局"
#define STR_OPEN "打开"
#define STR_SAVE "保存"
#define STR_EXIT "退出"
#define STR_BACKWARD "撤消"
#define STR_FORWARD "重做"
#define STR_SELECT_ENGINE "选择引擎"
#define STR_SELECT_WEIGHT "选择权重"
#define STR_RUN_ENGINE "启动引擎"
#define STR_CLOSE_ENGINE "关闭引擎"
#define STR_RESULT "计算胜负"
#define STR_STEP "显示棋步序号"
#define	STR_SET_GAMEBOARD_COLOR "设置棋盘颜色"
#define STR_MANUAL "使用手册"
#define STR_ABOUT "关于LZRobe"
#define STR_FILE "文件"
#define STR_EDIT "编辑"
#define STR_VIEW "视图"
#define STR_HELP "帮助"
#define STR_BLACK_DOG "AI执黑"
#define STR_WHITE_DOG "AI执白"
#define STR_TIME "思考时间"
#define STR_SHOW_ANALYZE "显示分析"
#define STR_INTERVAL "刷新间隔"
#define STR_ROUTE_LENGTH "预测长度"
#define STR_NO_ENGINE "引擎未运行"
#define STR_WARNING "提示"
#define STR_CHANGE_RECORD_INQUIRY "确定丢弃前面的变化么？"
#define STR_GAME_RESULT "对局结果"
#define STR_BLACK_RESIGN "黑认输，白中盘胜"
#define STR_WHITE_RESIGN "白认输，黑中盘胜"
#define STR_DISCARD_RECORD_INQUIRY "检测到对局信息，确定要丢弃么？"
#define STR_EXTRA_PARAMETERS "输入其它参数"
#define STR_CLOSE_ENGINE_INQUIRY "确定关闭引擎么？"
#define STR_CHANGE_PATH "检测到你修改了引擎或者权重的路径，是否保存？"
#define STR_RESTART_ENGINE "引擎崩溃，正在重启"
#define STR_ENGINE_OPENING "引擎正在启动，请耐心等待"
#define STR_ENGINE_AVAILABLE "引擎已启动"
#define STR_ENGINE_CLOSING "引擎正在关闭"
#define STR_SELFPLAY "引擎正在自我对局"
#define STR_ANALYZING "局势分析中"
#define STR_VERSION "当前版本：1.00"
#define STR_CLOSE "关闭"
#define STR_DIRECTION "欢迎试用LZRobe！这是一个为人工智能围棋软件LeelaZero提供图形界面的程序。\n\n\
如果你想了解关于LeelaZero更多的信息，请访问下面的网址：\n\n\
zero.sjeng.org\n\n\
LZRobe可以帮助你与LeelaZero对战，或者分析棋谱来提高你的水平。\n\n\
这个程序是基于C++语言写的，并使用了一个叫wxWidgets的图形界面库\n\n\
所以如果你想编译这个程序，你需要先下载并配置wxWidgets库，请浏览下在的网址：\n\n\
www.wxwidgets.org\n\n\
使用Visual Studio或者Code::Blocks编译这个程序并不困难。\n\n\
如果你想试着编译这个程序，首先要建立一个基于Win32图形用户界面的项项目，然后把.h文件、.cpp文件，一个.rc文件，一个.ico文件和.bmp文件包含进去。\n\n\
记得在工程设置中把wxWidgets的包含文件和库文件的路径加进去。\n\n\
Code::Blocks支持创建一个wxWidgets项目，自动包含wxWidgets的相关路径，这样也许可以简化编译流程。\n\n\
在你成功编译好程序以后，告诉你如何用这个程序。\n\n\
这个程序的图标是一个狗的头像，因为围棋的英文“Go”的发音类似于中文里的“狗”。\n\n\
在你打开这个程序以后，你会看到菜单栏下面有一个工具栏，所有的功能都可以在工具栏中找到。\n\n\
主窗口下方的状态栏会显示引擎的状态。\n\n\
鼠标左键用来放棋子，鼠标右键用来悔棋，键盘上的字母P用来停一手。\n\n\
这个程序不支持多分支棋谱，如果你要新开对局或者打开对局文件，程序中的棋谱会被丢弃。\n\n\
如果你想保存棋谱，引擎必须打开，而且菜单或者工具栏中的保存功能只会存当前棋盘上的棋步。\n\n\
所以如果你不想丢失对局信息，请走到对局最后一步再保存棋谱。\n\n\
工具栏里有一个运行按钮，可以使用这个按键启动Leela Zero。\n\n\
如果你没有为LeelaZero设置引擎路径或者权重文件，会有对话框弹出提示你选择可执行文件和权重文件。\n\n\
除非你使用了特殊的引擎，比如动态贴目，你不需要输入其它参数。\n\n\
当LeelaZero成功启动以后，等上数秒，工具栏里的几个灰色按钮会变成彩色，这个运行按钮由变成用来关闭引擎的按钮。\n\n\
如果你想在游戏过程中改变引擎或者权重文件，你需要先关闭引擎，然后在编辑菜单中修改引擎和权重文件路径，最后重启引擎即可。\n\n\
新启动的引擎会自动加载当前的对局进度。即使LeelaZero意外崩溃，LZRobe也会对它重启，并在数秒内自动加载对局进度以确保对局的顺利进行。\n\n\
如果你在撤消几步以后想要新增加棋子，以前的变化不会被保存。\n\n\
带着狗的头像的按钮用来和Leela Zero对局。狗的头像后面的背景表示AI所执棋子的颜色。\n\n\
如果你把两个狗的头像的按钮都按下，那AI会自我对局。\n\n\
在“思考时间”标签右边的数字框表示AI思考时间设置，时间单位是一秒。\n\n\
例如，如果你把这个数字设置成了5，那AI会在对手下子后的5秒之内下出一步棋。\n\n\
如果你改变了思考的时间，它会在你下次让AI走棋时生效。\n\n\
如果你在AI思考期间取消了它所执的一方，它还是会继续思考，直到下出下一步棋。所以你还是要等到下一步棋在棋盘上出现。\n\n\
带着问号的按钮用来分析棋谱，分析结果按一定的频率刷新。\n\n\
刷新频率可以在用“刷新间隔”标签右边的数字框来设置，单位是百分之一秒。\n\n\
例如，你把这个数字认成了50，那分析结果会在1秒内刷新两次。\n\n\
在分析过程中，绿点的颜色是搜索最多的点，其次是蓝点，黄点和红点的搜索较少。\n\n\
彩色点上的数字表示胜率和搜索数。搜索数最多的点通常是最好的选点。\n\n\
如果你把鼠标放到正在分析的点上，这个点下面的分析步数将会自动显示，上面有英文字母表示顺序。\n\n\
首先是小写字母，然后是大写字母。显示的最大步数可以用“预测长度”标签右边的滑杆来设置。\n\n\
带着算盘标识的按钮用来计算对局结果。由于死子不一定被提掉，所以预测结果并不准确。\n\n\
如果你改变了LeelaZero的引擎和权重文件路径，当你退出这个程序的时候，会有对话框问你是否保存。\n\n\
如果你选择了保存这个变化，那LeelaZero的引擎和权重文件路径会被保存到一个名为“config.txt”的文件中，下次启动会自动加载。\n\n\
感谢您读完这个帮助文件。欢迎对程序代码进行膜改，以适应更多的场合！"
#else
#define STR_NEW "new"
#define STR_OPEN "open"
#define STR_SAVE "save"
#define STR_EXIT "exit"
#define STR_BACKWARD "undo"
#define STR_FORWARD "redo"
#define STR_SELECT_ENGINE "select engine"
#define STR_SELECT_WEIGHT "select weight"
#define STR_RUN_ENGINE "run engine"
#define STR_CLOSE_ENGINE "close engine"
#define STR_RESULT "calculate result"
#define STR_STEP "show step index"
#define	STR_SET_GAMEBOARD_COLOR "set game board color"
#define STR_MANUAL "manual"
#define STR_ABOUT "about LZRobe"
#define STR_FILE "File"
#define STR_EDIT "Edit"
#define STR_VIEW "View"
#define STR_HELP "Help"
#define STR_BLACK_DOG "AI plays black"
#define STR_WHITE_DOG "AI plays white"
#define STR_TIME "think time"
#define STR_SHOW_ANALYZE "show analyze"
#define STR_INTERVAL "refresh interval"
#define STR_ROUTE_LENGTH "analyze length"
#define STR_NO_ENGINE "no engine"
#define STR_WARNING "Tip"
#define STR_CHANGE_RECORD_INQUIRY "Are you sure to discard the previous variation?"
#define STR_GAME_RESULT "game result"
#define STR_BLACK_RESIGN "Black has resigned, white win!"
#define STR_WHITE_RESIGN "White has resigned, black win!"
#define STR_DISCARD_RECORD_INQUIRY "Are you sure to discard the previous game record?"
#define STR_EXTRA_PARAMETERS "Input other parameters"
#define STR_CLOSE_ENGINE_INQUIRY "Are you sure to close the engine?"
#define STR_CHANGE_PATH "You have changed the paths of engine or weight file, would you like to save this change?"
#define STR_RESTART_ENGINE "Engine has collapse, it is restarting."
#define STR_ENGINE_OPENING "Engine is starting, please wait."
#define STR_ENGINE_AVAILABLE "Engine is available"
#define STR_ENGINE_CLOSING "Engine is closing"
#define STR_SELFPLAY "Engine is self playing"
#define STR_ANALYZING "Analyzinng"
#define STR_VERSION "Current version: 1.00"
#define STR_CLOSE "Close"
#define STR_DIRECTION "Welcome to try LZRobe! This is a software that provides a graphical user interface of the computer go software Leela Zero.\n\n\
If you're interested in more information about Leela Zero, please browse the following website:\n\n\
zero.sjeng.org\n\n\
LZRobe can help you to play Go againt Leela Zero or analyze the Go game records with Leela Zero to improve your strength of the game.\n\n\
This program is written in C++ pragramming language with a GUI Library named wxWidgets.\n\n\
So if you would like to compile this program, you have to download and install the wxWidgets library first.Please look up the following website :\n\n\
www.wxwidgets.org\n\n\
It is not difficult to compile this program with Visual Studio or Code::Blocks.\n\n\
If you try to compile this program, you should create a Win32 GUI empty project and add the files, including.h files, .cpp files, a .rc file, a .ico file and.bmp files.\n\n\
Don't forget appending include and lib dictionaries of wxWidgets in the setting of your project.\n\n\
Code::Blocks supports creating a wxWidgets project containing the path of wxWidgets, this maybe make it simpler to compile this program.\n\n\
After you have compiled this program successfully, I tell you how to use this program.\n\n\
The icon of this program is a dog's head. Because the pronounciation of \"Go\" means \"dog\" in Chinese.\n\n\
Once you open this program, you will see a tool bar below the menu.All the functions of this program can be found in the tool bar.\n\n\
The status of engine will be shown in the status bar at the bottom of the main frame.\n\n\
The left button of the mouse is used to put stones, while the right button is used to undo a move. \"P\" on the keyboard is used to pass.\n\n\
The program does not support multi-branch game records. So if you try to start a new game or open a new game record from the menu or tool bar, the current record will be deleted\n\n\
If you want to save the game record, the engine must be opening, and the save menu or tool bar only save the records on the gameboard.\n\n\
So if you do not want to lost any game record, please go to the last step of the game before saving the game record.\n\n\
There is a run button in the tool bar.You can start Leela Zero with this button.\n\n\
If you did not set the path of Leela Zero or the weight file, when you push the run button, file dialogs will appear to tip you choose the leela zero executable file and the weight file.\n\n\
You need not to fill any letter into the extra parameters, unless you are using a pecificied engine, such as dynamic komi.\n\n\
When Leela Zero are started successfully, after several seconds, the gray buttons in the tool bar will become colored. The run button will become a close button to stop Leela Zero.\n\n\
If you want to change the engine or the weight file during the game, you can stop the engine first, then change the engine or weight file path in the edit menu, and start the engine last.\n\n\
Then the newly started engin will load the game records automatically. Even if the Leela Zero collapsed, LZRobe will restart it and load the game records with a few second to keep this game.\n\n\
But if you decide to put new stones at different position after canceled several moves, the previous variation will not be kept.\n\n\
The button with dogs' heads are used to play againt Leela Zero. The color of the background under the dogs' heads indicates the stone color that the AI plays.\n\n\
If you push both of the two buttons with dogs' heads, you will see the computer plays agains itself.\n\n\
The number in the spinbox on the right of the \"think time\" label is used to set the think time of computer. The unit of the time is one second.\n\n\
For example, if you set the number as 5, AI will put a stone on the gameboard in 5 seconds after the oppoment's move.\n\n\
If you change the number of thinking time, it will work when you ask the computer play with one side.\n\n\
If you cancel AI to play one side when it is thinking the next move, it will keeping on until it think out this move. So you have to wait for its next move until the newest stone appears on the gamebord.\n\n\
The button with a question mark is used to analyze the game record. The analyze result will be refreshed with a frequency.\n\n\
The frequnecy can be set with the spinbox on the right of the \"refresh interval\" label.The unit of the refresh interval is centisecond.\n\n\
For example, if you set the number as 50, the analyze result will refresh twice in one second.\n\n\
In the analyzation, the points with green color are the most visited points, then come the blue points. The yellow and red points are less visited.\n\n\
The numbers at the points with green color indicates the winrate and visits. The point with highest visits is usually the best point to select.\n\n\
If you put the mouse at the analyzing point, the following steps will automatically be shown, where the letters indicates the consequence.\n\n\
The lower case letters come first, and then the upper case. The maximum number to show of the following steps can be set with the slider on the right of the analyze length.\n\n\
The button with an abcus is used to calculate the result of the game. Since the dead stones may not be removed from the gameboard, the result is not exactly the true result.\n\n\
If you changed the path of Leela Zero or the Weight file path, when you exit this program, a message box will ask you if you want to save this change.\n\n\
If you choose saving this change, the paths of Leela Zero and Weight file will be stored in a file named \"config.txt\".Next time you start LZRobe, it will load the paths automatically.\n\n\
Thanks for reading the introduction file! Welcome to modify these code to adapt more cases!"
#endif
#endif