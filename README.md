# список файлов:
-  taskfive.cpp - пятый урок - функции
-  taskfour.cpp - четвертый урок - циклы и условия.
-  taskthree - задание для третьего урока, массивы, указатели, внешние файлы, библиотеки
-  secondtask.cpp - задание для второго урока, энум, структуры, юнион 
-  madpython.cpp - задание для первого урока, введение 

## madpython.cpp - игра змейка, первое практическое задание
Перемещение выполняется по WSAD, выход через Esc.
При проигрыше нажатие R перезагружает игру.

0.1- работает общий игровой цикл, механия удлинения хвоста и столкновения с препятствиями/яблоками.
 
### Текущие проблемы / TODO LIST:
* код для курсорных клавиш это три нажатия сразу, одно из которых равен escape, что роняет игру.
* неадекватные столновения из-за разницы между рациональными игровыми данными и дискретными экранными (не знаю, зачем я их сделал разными)
* грубо реализован цикл через задержку, без привязки к скорости обработки, может съедать быстрое нажатие клавиш
* код какой попало, нужно реализовать ООП для структур и разделить обновление графики и обновление данных
* закончить столкновения для собственного хвоста и респавн фруктов, может быть запись/считывание очков из файла.
