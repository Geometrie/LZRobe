#ifndef INTERNATIONAL_H
#define INTERNATIONAL_H
//#define LANGUAGE_CHINESE_SIMPLIFIED
#ifdef LANGUAGE_CHINESE_SIMPLIFIED
#define STR_NEW "新对局"
#define STR_HANDICAP "让子对局"
#define STR_HANDICAP_NUM "设置让子数"
#define STR_OPEN "打开"
#define STR_SAVE "保存"
#define STR_EXIT "退出"
#define STR_BACKWARD "撤消"
#define STR_FORWARD "重做"
#define STR_SELECT_ENGINE "选择引擎"
#define STR_SELECT_WEIGHT "选择权重"
#define STR_EXTRA_PARA "附加参数"
#define STR_BOARD_SIZE "改变棋盘大小"
#define STR_RUN_ENGINE "启动引擎"
#define STR_CLOSE_ENGINE "关闭引擎"
#define STR_RESULT "计算胜负"
#define STR_STEP "显示棋步序号"
#define STR_COORDINATE "棋盘坐标"
#define STR_COORD_NULL "隐藏坐标"
#define STR_COORD_NET "网棋客户端坐标"
#define STR_COORD_NUM "纯数字坐标"
#define STR_COORD_SGF "SGF字母坐标"
#define STR_COORD_GTP "GTP协议坐标"
#define	STR_SET_GAMEBOARD_COLOR "设置棋盘颜色"
#define STR_MANUAL "使用说明"
#define STR_ABOUT "关于LZRobe"
#define STR_FILE "文件"
#define STR_EDIT "编辑"
#define STR_VIEW "视图"
#define STR_LINK "连接"
#define STR_HELP "帮助"
#define STR_BLACK_DOG "AI执黑"
#define STR_WHITE_DOG "AI执白"
#define STR_TIME "思考时间"
#define STR_SHOW_ANALYZE "显示分析"
#define STR_TERMINATED_GAME "对局已经结束，需要重新加载才能显示分析，确定重新加载么？"
#define STR_INTERVAL "刷新间隔"
#define STR_ROUTE_LENGTH "预测长度"
#define STR_NO_ENGINE "引擎未运行"
#define STR_TIP "提示"
#define STR_ADD_BRANCH_INQUIRY "确定增加分支么？"
#define STR_DELETE_BRANCH_INQUIRY "确定删除分支么？"
#define STR_GAME_RESULT "对局结果"
#define STR_BLACK_RESIGN "黑认输，白中盘胜"
#define STR_WHITE_RESIGN "白认输，黑中盘胜"
#define STR_DISCARD_RECORD_INQUIRY "检测到对局信息，确定要丢弃么？"
#define STR_EXTRA_PARAMETERS "输入其它参数"
#define STR_CLOSE_ENGINE_INQUIRY "确定关闭引擎么？"
#define STR_CHANGE_PATH "检测到你修改了引擎或者权重的路径，是否保存？"
#define STR_CHANGE_EXTRA_PARA "检测到了你增加了额外参数，是否保存？"
#define STR_RESTART_ENGINE "引擎崩溃，正在重启"
#define STR_ENGINE_OPENING "引擎正在启动，请耐心等待"
#define STR_ENGINE_AVAILABLE "引擎已启动"
#define STR_ENGINE_CLOSING "引擎正在关闭"
#define STR_SELFPLAY "引擎正在与自己对局"
#define STR_ANALYZING "局势分析中"
#define STR_VERSION "当前版本：1.02 测试版"
#define STR_CLOSE "关闭"
#define STR_MOVE_TURN "着子权"
#define STR_PRISONERS "提子"
#define STR_PASS "放弃一手"
#define STR_RESIGN "认输"
#define STR_GAME_PROCESS "对局进程"
#define STR_DIRECTION "欢迎试用LZRobe！这是一个为人工智能围棋软件LeelaZero提供图形界面的程序。\n\n\
如果你想了解关于LeelaZero更多的信息，请访问下面的网址：\n\n\
zero.sjeng.org\n\n\
LZRobe可以帮助你与LeelaZero对战，或者分析棋谱来提高你的水平。\n\n\
LZRobe是基于C++语言写的，并使用了一个叫wxWidgets的图形界面库。\n\n\
所以如果你想编译LZRobe，你需要先下载并配置wxWidgets库，请浏览下在的网址：\n\n\
www.wxwidgets.org\n\n\
使用Visual Studio或者Code::Blocks编译LZRobe并不困难。\n\n\
如果你想试着编译LZRobe，首先要建立一个基于Win32图形用户界面的项项目，然后把.h文件、.cpp文件，一个.rc文件，一个.ico文件和.bmp文件包含进去。\n\n\
记得在工程设置中把wxWidgets的包含文件和库文件的路径加进去。\n\n\
Code::Blocks支持创建一个wxWidgets项目，自动包含wxWidgets的相关路径，这样也许可以简化编译流程。\n\n\
在你成功编译好程序以后，告诉你如何用LZRobe。\n\n\
LZRobe的图标是一个狗的头像，因为围棋的英文“Go”的发音类似于中文里的“狗”。\n\n\
在你打开LZRobe以后，你会看到菜单栏下面有一个工具栏，大多数功能都可以在工具栏中找到。\n\n\
新对局会删除当前的对局信息。让子对局只能在文件菜单栏中选取。\n\n\
LZRobe允许用鼠标把sgf文件拖放到窗口中来打开。也可以把.sgf格式的棋谱文件的打开方式直接设置成LZRobe。\n\n\
但如果你的棋谱文件名或者路径中有非ASCII码字符(比如汉字)，你只能用菜单或者工具栏来打开。\n\n\
棋盘左侧显示了落子一方和提子数量，右侧有放弃一步和认输的选点。主窗口下方的状态栏会显示引擎的状态。\n\n\
鼠标左键用来放棋子，鼠标右键用来悔棋，键盘右下的对局流程可以用来跳转到任意棋步。\n\n\
对局流程按照从左到右的顺序蛇形排列，每一列有25手棋，想跳转到对应的棋步，使用鼠标左键点相应的位置即可。\n\n\
为了避免出现命令扎堆导致LeelaZero崩溃的情况，在引擎开启等待的时间内，悔棋和跳转棋步是不允许的，但可以落子。\n\n\
LZRobe支持多分支棋谱，如果你改变了原来棋谱中的下法，会有提示让你选择是否增加新的分支。把棋谱保存为sgf格式也可以同时存下所有的分支。\n\n\
为了不至于眼花缭乱，多分支棋谱在对局流程中只会显示当前棋步所在的最长链，其中有分支的棋步会分别由原来的黑色与白色变为红色与蓝色。\n\n\
如果你跳转到有分支的棋步，那下一步的不同分支会按长短用暗紫色粗体大写英文字母标注在棋盘上。A代表着最长的分支，越短的分支对应字母表越靠后的位置的字母。\n\n\
用鼠标左键点击相应字母所在的位置可以进入对应的分支，用鼠标右键点击则可以删除相应的分支。\n\n\
多分支链的顺序是保持动态维护的，如果你增加或者删除了分支，可能会对它的上一级分支的排序产生影响。\n\n\
由于Leela Zero的官方权重不支持非19路对局，所以非19路的棋盘只支持打开、修改和保存棋谱。如果要打开非19路棋谱，需要先把棋盘调整到相应大小。\n\n\
棋盘坐标可以选择隐藏，也可以选择几种不同的显示模式。注意GTP协议坐标的横坐标没有字母“I”，纵坐标是从下往上排列的。\n\n\
工具栏里有一个运行按钮，可以使用这个按键启动LeelaZero。\n\n\
如果你没有为LeelaZero设置引擎路径或者权重文件，会有对话框弹出提示你选择可执行文件和权重文件。\n\n\
除非你使用了特殊的引擎，比如动态贴目，你不需要输入其它参数。\n\n\
当LeelaZero成功启动以后，等上数秒，工具栏里的几个灰色按钮会变成彩色，这个运行按钮由变成用来关闭引擎的按钮。\n\n\
如果你想在游戏过程中改变引擎或者权重文件，你需要先关闭引擎，然后在编辑菜单中修改引擎和权重文件路径，最后重启引擎即可。\n\n\
新启动的引擎会自动加载当前的对局进度。即使LeelaZero意外崩溃，LZRobe也会对它重启，并在数秒内自动加载对局进度以确保对局的顺利进行。\n\n\
如果你在撤消几步以后想要新增加棋子，以前的变化不会被保存。\n\n\
带着狗的头像的按钮用来和LeelaZero对局。狗的头像后面的背景表示AI所执棋子的颜色。\n\n\
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
为了防止程序崩溃，在分析棋谱的时候，请不要随意改变窗口大小。\n\n\
如果你把鼠标放到正在分析的点上，这个点下面的分析步数将会自动显示，上面有字母表示顺序。\n\n\
首先是小写英文字母，然后是小写希腊字母。显示的最大步数可以用“预测长度”标签右边的滑杆来设置。\n\n\
如果有连续两手放弃(双方各一手)或者一方认输，则棋局结束，LeelaZero不会对结束的棋局做分析。\n\n\
如果你想分析已结束的棋局，需要从头加载，棋谱的信息不会改变。\n\n\
在对局接近结束或者一方占有绝对的优势的时候，LeeaZero可能会有放弃的步的选点，查看这个选点的分析可以把鼠标放在放弃选项的选点上。\n\n\
带着算盘标识的按钮用来计算对局结果。由于死子不一定被提掉，所以显示结果并不准确。\n\n\
如果你改变了LeelaZero的引擎和权重文件路径，或者改变了附加参数，当你退出LZRobe的时候，会有对话框问你是否保存。\n\n\
如果你选择了保存这个变化，那LeelaZero的引擎和权重文件路径以及你的附加参数会被保存到一个名为“config.txt”的文件中，下次启动会自动加载。\n\n\
虽然程序的作者一直在努力减少程序的Bug，但我们依然无法确保程序不会崩溃。\n\n\
如果程序意外崩溃，LeelaZero依然在运行，请使用任务管理器结束LeelaZero，以免它继续占用你的硬件资源！\n\n\
感谢您读完这个帮助文件。欢迎对程序代码进行膜改，以适应更多的场合！"
#else
#define STR_NEW "new"
#define STR_HANDICAP "handicap game"
#define STR_HANDICAP_NUM "handicap number"
#define STR_OPEN "open"
#define STR_SAVE "save"
#define STR_EXIT "exit"
#define STR_BACKWARD "undo"
#define STR_FORWARD "redo"
#define STR_SELECT_ENGINE "select engine"
#define STR_SELECT_WEIGHT "select weight"
#define STR_EXTRA_PARA "extra parameter"
#define STR_RUN_ENGINE "run engine"
#define STR_CLOSE_ENGINE "close engine"
#define STR_RESULT "calculate result"
#define STR_STEP "show step index"
#define STR_COORDINATE "game board coordinates"
#define STR_COORD_NULL "hide coordinates"
#define STR_COORD_NET "net client coordinates"
#define STR_COORD_NUM "pure digital coordinates"
#define STR_COORD_SGF "sgf alphabet coordinates"
#define STR_COORD_GTP "gtp protocal coordinates"
#define	STR_SET_GAMEBOARD_COLOR "set game board color"
#define STR_MANUAL "manual"
#define STR_ABOUT "about LZRobe"
#define STR_FILE "File"
#define STR_EDIT "Edit"
#define STR_VIEW "View"
#define STR_LINK "Link"
#define STR_HELP "Help"
#define STR_BLACK_DOG "AI plays black"
#define STR_WHITE_DOG "AI plays white"
#define STR_TIME "think time"
#define STR_SHOW_ANALYZE "show analyze"
#define STR_TERMINATED_GAME "The game has terminated. Would you like to reload it for analyzing?"
#define STR_INTERVAL "refresh interval"
#define STR_ROUTE_LENGTH "analyze length"
#define STR_NO_ENGINE "no engine"
#define STR_TIP "Tip"
#define STR_ADD_BRANCH_INQUIRY "Are you sure to add branch?"
#define STR_DELETE_BRANCH_INQUIRY "Are you sure to delete branch?"
#define STR_GAME_RESULT "game result"
#define STR_BLACK_RESIGN "Black has resigned, white win!"
#define STR_WHITE_RESIGN "White has resigned, black win!"
#define STR_DISCARD_RECORD_INQUIRY "Are you sure to discard the previous game record?"
#define STR_EXTRA_PARAMETERS "Input other parameters"
#define STR_BOARD_SIZE "Change Gameboard Size"
#define STR_CLOSE_ENGINE_INQUIRY "Are you sure to close the engine?"
#define STR_CHANGE_PATH "You have changed the paths of engine or weight file, would you like to save this change?"
#define STR_CHANGE_EXTRA_PARA "You have appended extra parameters, would you like to save them?"
#define STR_RESTART_ENGINE "Engine has collapse, it is restarting."
#define STR_ENGINE_OPENING "Engine is starting, please wait."
#define STR_ENGINE_AVAILABLE "Engine is available"
#define STR_ENGINE_CLOSING "Engine is closing"
#define STR_SELFPLAY "Engine is playing against itself"
#define STR_ANALYZING "Analyzinng"
#define STR_VERSION "Current version: 1.02 beta"
#define STR_CLOSE "Close"
#define STR_MOVE_TURN "Move Turn"
#define STR_PRISONERS "Prisoners"
#define STR_PASS "Pass"
#define STR_RESIGN "Resign"
#define STR_GAME_PROCESS "Game Process"
#define STR_DIRECTION "Welcome to try LZRobe! This is a software that provides a graphical user interface of the computer go software Leela Zero.\n\n\
If you're interested in more information about Leela Zero, please browse the following website:\n\n\
zero.sjeng.org\n\n\
LZRobe can help you to play Go againt Leela Zero or analyze the Go game records with Leela Zero to improve your strength of the game.\n\n\
LZRobe is written in C++ pragramming language with a GUI Library named wxWidgets.\n\n\
So if you would like to compile LZRobe, you have to download and install the wxWidgets library first.Please look up the following website:\n\n\
www.wxwidgets.org\n\n\
It is not difficult to compile LZRobe with Visual Studio or Code::Blocks.\n\n\
If you try to compile LZRobe, you should create a Win32 GUI empty project and add the files, including.h files, .cpp files, a .rc file, a .ico file and.bmp files.\n\n\
Don't forget appending include and lib dictionaries of wxWidgets in the setting of your project.\n\n\
Code::Blocks supports creating a wxWidgets project containing the path of wxWidgets, this maybe make it simpler to compile LZRobe.\n\n\
After you have compiled LZRobe successfully, I tell you how to use LZRobe.\n\n\
The icon of LZRobe is a dog's head. Because the pronounciation of \"Go\" means \"dog\" in Chinese.\n\n\
Once you open LZRobe, you will see a tool bar below the menu. Most of the functions of LZRobe can be found in the tool bar.\n\n\
New game will drop all the information of current game. A handicap game can onle be set in the file menu.\n\n\
LZRobe allows dragging a sgf file to the window and open it. You can also set the default open program for an sgf file as LZRobe.\n\n\
But if there are non-ascii chars(e.g. Chinese characters) in your file name or path, you can only open it in menu or tool bar\n\n\
The move turn and number of prisoners are shown in the left of the gameboard. The pass and resign choice are laid on the right of the game board. The status of engine will be shown in the status bar at the bottom of the main frame.\n\n\
The game process are arranged from left to right with a wandering snake shape, where every column contains 25 steps. If you would like to jump to one step, you can click its related position with left button of your mouse.\n\n\
The left button of the mouse is used to put stones, while the right button is used to undo a move. The game progress on the bottom right of the gameboard can be used to jump to any step.\n\n\
In order to avoid a command jam cause Leela Zero collapse, retracting or jumping moves are not allowed during the waiting of the engine's opening. But putting stones on the gameboard is allowed.\n\n\
LZRobe support multi-branch game record. If you change the move in the original game record, there will be a tip to ask you whether add a new branch. If you save the game record, the branches can also be stored in .sgf files.\n\n\
In order to avoid your eye being dazzled, the game process only shows the longest chain containing the current move, where the branch points will separately become red and blue from its original colors black and white.\n\n\
If you jump to a step containing branches, the varation of next step will be marked on the game board with upper case letters in dark purple bold font according its length. A stands for the longest branch, while the shorter the branch is, the later the letter position in the alphabet it relates.\n\n\
You can enter the related branch with click one letter with the left button of your mouse, while the right button of your mouse can be used to delete a branch.\n\n\
The sequence of the branches is dynamically preserved. If you add or delete a branch, this may affect the sequence of its parent branch.\n\n\
Due to the official network weights cannot support games with other board size than 19, so such games can only support opening, editing and saving game recoard. If you would like to open a game record with other board size that 19, place adjust to its related board size first.\n\n\
The coordinates on the game board can be hidden, several modes of coordinates can be selected. Notice that in GTP protocal, there is no letter \"I\" in the horizonal coordinate, and the order of vertical coordinates is arranged from bottom to top.\n\n\
There is a run button in the tool bar. You can start Leela Zero with this button.\n\n\
If you did not set the path of Leela Zero or the weight file, when you push the run button, file dialogs will appear to tip you choose the Leela Zero executable file and the weight file.\n\n\
You need not to fill any letter into the extra parameters, unless you are using a specified engine, such as dynamic komi.\n\n\
When Leela Zero are started successfully, after several seconds, the gray buttons in the tool bar will become colored. The run button will become a close button to stop Leela Zero.\n\n\
If you want to change the engine or the weight file during the game, you can stop the engine first, then change the engine or weight file path in the edit menu, and start the engine last.\n\n\
Then the newly started engine will load the game records automatically. Even if the Leela Zero collapsed, LZRobe will restart it and load the game records with a few second to keep this game.\n\n\
But if you decide to put new stones at different position after canceled several moves, the previous variation will not be kept.\n\n\
The button with dogs' heads are used to play against Leela Zero. The color of the background under the dogs' heads indicates the stone color that the AI plays.\n\n\
If you push both of the two buttons with dogs' heads, you will see the computer plays agains itself.\n\n\
The number in the spinbox on the right of the \"think time\" label is used to set the think time of computer. The unit of the time is one second.\n\n\
For example, if you set the number as 5, AI will put a stone on the gameboard in 5 seconds after the opponent's move.\n\n\
If you change the number of thinking time, it will work when you ask the computer play with one side.\n\n\
If you cancel AI to play one side when it is thinking the next move, it will keeping on until it think out this move. So you have to wait for its next move until the newest stone appears on the gamebord.\n\n\
The button with a question mark is used to analyze the game record. The analyze result will be refreshed with a frequency.\n\n\
The frequency can be set with the spinbox on the right of the \"refresh interval\" label. The unit of the refresh interval is centisecond.\n\n\
For example, if you set the number as 50, the analyze result will refresh twice in one second.\n\n\
In the analyzation, the points with green color are the most visited points, then come the blue points. The yellow and red points are less visited.\n\n\
The numbers at the points with green color indicates the winrate and visits. The point with highest visits is usually the best point to select.\n\n\
In order to avoid LZRobe collapse, please don't change the size of the window when the analyze is opened.\n\n\
If you put the mouse at the analyzing point, the following steps will automatically be shown, where the letters indicates the consequence.\n\n\
The latin letters with lower case come first, and then come the greek letters with lower case. The maximum number to show of the following steps can be set with the slider on the right of the analyze length.\n\n\
If there are two continuous pass (one  for each side), the game will end. Leela Zero would not analyze a terminated game.\n\n\
So if you want to analyze a terminate game, the game record should be reloaded from the start. The information of the game record will not be changed.\n\n\
When the game approaches the end or one side have an extremely advantage, Leela Zero may have the pass choice. If you want to check the relative analyze, you can put the mouse on the pass point.\n\n\
The button with an abcus is used to calculate the result of the game. Since the dead stones may not be removed from the gameboard, the result is not exactly the true result.\n\n\
If you changed the path of Leela Zero or the Weight file path, when you exit LZRobe, a message box will ask you if you want to save this change.\n\n\
If you choose saving this change, the paths of Leela Zero and Weight file will be stored in a file named \"config.txt\".Next time you start LZRobe, it will load the paths automatically.\n\n\
The author is trying to reduce the bugs of the program, but we are sorry that we cannot completely avoid the collapse of the program.\n\n\
If once the program collapse while Leela Zero is running, please terminate Leela Zero with task manager lest it continue to occupy your hardware resource!\n\n\
Thanks for reading the introduction file! Welcome to modify these code to adapt more cases!"
#endif
#endif
