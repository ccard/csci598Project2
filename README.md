CSCI598 Project2
===============

&nbsp;&nbsp;___Author:___   Chris  Card
 
 &nbsp;&nbsp;This README file will explain how to [Compile]() the program, the [Environment]() you will need, 
 and finally [How to run]() each part of the program.

--- 
 # Environment #
 &nbsp;&nbsp;The expected environment is as follows:

 1. _GNU_ g++ compiler (the same one as on the _Mines_ linux computers) or the equivalent.  If using a different compiler than g++ then the program is not garunteed to compile.  If your using a different compiler open the _Makefile_ and modify the line `GCC = g++` -> `GCC = <new compiler>`.
 2. The _LIBSVM_ executables are in the path as they with be called from _run.sh_
 3. The computer has all the standard c++ libraries. If your using GNU g++ this is not a problem.

----
# Compile #
&nbsp;&nbsp;To compile the program first run `./setup.sh` this will ensure that all necessary directories and commands that
are needed to compile and run exsist. Then run `make clean` to ensure that nothing from the submission could prevent the
program from running on the current computer.  Once this is complete then run `make` from the same directory as the 
_Makefile_.

__Note:__ if the _GNU_ g++ compiler is not used to compile this project is not guranteed to compile as the program was
developed and tested with that compiler. 
 
---
# How to run #
&nbsp;&nbsp;To run the project ensure that everthing in the [Environment]() and [Compile]() is correct and is able to run.
Ensure that the _train.sh_  and _test.sh_ are in the root directory of the project as well as *human_actions.txt* and 
*test_human_actions.txt* (these files contain all the human actions that each step of the program will run on). If 
`./setup.sh` was executed it will tell you if you are missing anything in your environment. The following will explain 
how to run the program for each part of the project.

## Execution scripts ##
&nbsp;&nbsp;To execute the training and testing for each part of the project _train.sh_ and _test.sh_ will be used 
respectively and will be called as follows:

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`./train.sh <part_name>` and `./test.sh <part_name>`
- <part_name> = the string representing each part of the program to run
 - [RAD](Relative Angle and Distances)
 - [HJPD](Histogram of Joint Position Differences)
 - [HOD](Histogram of Oriented Displacements)

## Relative Angle and Distances ##

## Histogram of Joint Position Differences ##

## Histogram of Oriented Displacements ##

# References #
1. [Project paper](http://inside.mines.edu/~hzhang/Courses/CSCI498B-598B-Fall14/Projects/Project-2/Project-2.pdf) and attached papers.