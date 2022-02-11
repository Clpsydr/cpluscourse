# Basic cpp course comprised of three parts:
/pt1 - basic tasks, ascii tic tac toe game
- ttt           - main executable
- tictac.cpp    - class structure for ttt
- taskseven.cpp - namespaces, directives
-  tasksix.cpp - file io / memory
-  taskfive.cpp - functions
-  taskfour.cpp - cycle/ conditions
-  taskthree - externals, libraries, arrays, pointers
-  secondtask.cpp - enum, union, structs
/pythongame - snake ascii game, within pt1 project time frame
- madpython.cpp 

/pt2 - OOP tasks, plus Black Jack 
- t1.cpp, basic classes
- t2.cpp, basic inheritance
- t3.cpp, abstract classes, diamond of death
- t4.cpp, vectors?
- t5.cpp, template functions, overloading
- t6.cpp, iostream
- t7.cpp, project modularity
- t8.cpp, exception processing
- blackjack.cpp, blackjack.h, cardgame.cpp, Blackjack logic and starting file

/pt3 - 
- t1.cpp, extra types, lambda functions
- t2.cpp, container templates and sorting
- t3.cpp, basic STL
- t4.cpp, STL algorithms, more lambdas
- t5.cpp, assotiative STL containers
- t6.cpp, parallel computing, mutexes, semaphore
- not added: t7-8, protobuf and external libraries.

## for snake game
0.1- basic gameplay, collisions, tail extension
 
### snake TODO LIST:
* sticky key problem, due to ncurses processing cursor keys as three presses at once, including escape
* inadequate collisions, due to coordinate space calculated through float.
* delay based update cycle, not considering computer speed
* lacks OOP classes, no strict divide between graphical and data processing
* lacks collision with tail and fruit respawn.
