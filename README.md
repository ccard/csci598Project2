CSCI598 Project2
===============

&nbsp;&nbsp;___Author:___   Chris  Card
 
 &nbsp;&nbsp;This README file will explain how to [compile](#compile) the program, 
 the [environment](#environment) you will need, and finally [how to run](#how-to-run) each part of the program.


--- 
# Environment #
 &nbsp;&nbsp;The expected environment is as follows:

 1. _GNU_ g++ compiler (the same one as on the _Mines_ linux computers) or the equivalent.  If using a different compiler than g++ then the program is not garunteed to compile.  If your using a different compiler open the _Makefile_ and modify the line `GCC = g++` -> `GCC = <new compiler>`.
 2. The _LIBSVM_ executables (_svm-predict_,_svm-train_,_svm-scale_) are in the path as they with be called from _run.sh_
 3. The computer has all the standard c++ libraries. If your using _GNU_ g++ compiler this is not a problem.

----
# Compile #
&nbsp;&nbsp;To compile the program first run `./setup.sh` this will ensure that all necessary directories, files and commands that
are needed to compile and run exist. Then run `make clean` to ensure that nothing from the submission could prevent the
program from running on the current computer.  Once this is complete then run `make` from the same directory as the 
_Makefile_.

__Note:__ if the _GNU_ g++ compiler is not used to compile this project is not guranteed to compile as the program was
developed and tested with that compiler. 
 
---
# How to run #
&nbsp;&nbsp;To run the project ensure that everything in the [environment](#environment) and [compile](#compile) is correct and is able to run.
Ensure that _run.sh_ is in the root directory of the project as well as *human_actions.txt* and 
*test_human_actions.txt* (these files contain all the human actions that each step of the program will run on). If 
`./setup.sh` was executed it will tell you if you are missing anything in your environment. The following will explain 
how to run the program for each part of the project.

&nbsp;&nbsp;_Note:_ The *human_actions.txt* and *test_human_actions.txt* must be in the following format:
`Class(int),file(string)`

## Execution script ##
&nbsp;&nbsp;To execute the program and create and test the classifiers _run.sh_  will be used and will be called as follows:

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;'./run.sh <method>'
- `<method>` = the string representing each part of the program to run
 - [RAD](#relative-angle-and-distances)
 - [HJPD](#histogram-of-joint-position-differences)
 - [HOD](#histogram-of-oriented-displacements)

At the end of `./run.sh` call it will ask you if you want it to clean up the  
output files press n if you would like to save the files. 

## Relative Angle and Distances ##
&nbsp;&nbsp;&nbsp; This method creates the skeletel representation based off of
the RAD skeleton as described in the project paper.  To run this method call 
`./run.sh RAD`

## Histogram of Joint Position Differences ##

## Histogram of Oriented Displacements ##

# References #
1. [Project paper](http://inside.mines.edu/~hzhang/Courses/CSCI498B-598B-Fall14/Projects/Project-2/Project-2.pdf) and attached papers.