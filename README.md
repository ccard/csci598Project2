CSCI598 Project2
===============

&nbsp;&nbsp;___Author:___   Chris  Card

&nbsp;&nbsp;Click [here](https://github.com/ccard/csci598Project2/blob/master/README.md) for the cleanly formatted version of this README.

 &nbsp;&nbsp;This README file will explain how to [compile](#compile) the program, 
 the [environment](#environment) you will need, and finally [how to run](#how-to-run) each part of the program.


--- 
# Environment #
 &nbsp;&nbsp;The expected environment is as follows:

 1. _GNU_ g++ compiler (the same one as on the _Mines_ linux computers) or the equivalent.  If using a different compiler than g++ then the program is not garunteed to compile.  If your using a different compiler open the _Makefile_ and modify the line `GCC = g++` -> `GCC = <new compiler>`.
 2. The _LIBSVM_ executables (_svm-predict_,_svm-train_,_svm-scale_) are in the path as they with be called from _run.sh_
 3. The computer has all the standard c++ libraries. If your using _GNU_ g++ compiler this is not a problem.

&nbsp;&nbsp;To check you environment run `./setup.sh` this will check your environment for the the desired commands, files and directories.  It will also create some tempory directories used during [compilation](#compile).

----
# Compile #
&nbsp;&nbsp;To compile the program first run `./setup.sh` this will ensure that all necessary directories, files and commands that
are needed to compile and run exist. Then run `make clean` to ensure that nothing from the submission could prevent the
program from running on the current computer.  Once this is complete then run `make` from the same directory as the 
_Makefile_.

__Note:__ If the _GNU_ g++ compiler is not used to compile this program the program is not guranteed to compile as the program was developed and tested with that compiler. 
 
---
# How to run #
&nbsp;&nbsp;To run the project ensure that everything in the [environment](#environment) and [compile](#compile) is correct and is able to run.
Ensure that _run.sh_ is in the root directory of the project as well as *human_actions.txt* and *test_human_actions.txt* (these files contain all the human actions that each step of the program will train and test with). If `./setup.sh` was executed it will tell you if you are missing anything in your environment. The following will explain how to run the program for each part of the project.

&nbsp;&nbsp;_Note:_ The *human_actions.txt* and *test_human_actions.txt* must be in the following format:
`Class(int),file(string)`

## Execution script ##
&nbsp;&nbsp;_run.sh_ is used to create the training and testing as well as creating and testing the classifiers using libsvm.  _run.sh_ should be called as follows, it will check your parameters and output its usage if any paramaters are incorrect:

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;`./run.sh <method>`
- `<method>` = the string representing each part of the program to run
 - [RAD](#relative-angle-and-distances)
 - [HJPD](#histogram-of-joint-position-differences)
 - [HOD](#histogram-of-oriented-displacements)

During _run.sh_'s execution it will display its status (i.e. 'Creating training data ....', 'Training svm ....') and the output of each stage if there is any.  After 'Running prediction .... ' _run.sh_ will output the classifiers accuracy as well as the confusion matrix (the confusion matrix will also be saved to *confusion_out.txt*). At the end of `./run.sh` call it will ask you if you want it to clean up the output files press n if you would like to save the files.

__Note:__ You should only have to run `make`,`./setup.sh` and `./run.sh` to run and test my program if these don't work please email me.

## Relative Angle and Distances ##
&nbsp;&nbsp;&nbsp; This method creates the skeletel representation based off of
the RAD skeleton as described in the project paper.  To run this method call 
`./run.sh RAD`. The RAD skeleton uses joints: 1 (as centroid), 4,8,12,16,20.

## Histogram of Joint Position Differences ##
&nbsp;&nbsp;&nbsp; This method creates the skeletel representation using the Histogram of Joint Posistion Differeces (HJPD) using joint 3 (the upper torso) as the reference joint, as this is the most reliably detected joint in the skeleton. To run this method call `./run.sh HJPD`.

## Histogram of Oriented Displacements ##
&nbsp;&nbsp;&nbsp; This method uses Histogram of Oriented Displacements (HOD) and a temporal pyramid with 3 levels.  Each level splits the instance set of the previous level in half creating histograms for each half.  In total my temporal pyramid has 7 histograms.  Before the Temporal Histograms (THs) are concatinated they are each normalized.  Once the THs are concatinated the resulting histogram is normalized by divinding by 7.  These normalization steps help to smooth the data and make it less dependent upon the data set size. To run this method call `./run.sh HOD`.

# Results #
&nbsp;&nbsp;My results from _RAD_,_HJPD_ and _HOD_ from my execution of my program are very promissing. Each representation achives a classifier accuracy over 65%.  My _RAD_ skeletel representation achieves a classifier accuracy of 68.75% and the confusion matrix can be seen in __Figure 1__ in the [appendix](#appendix).  My _HJPD_ skeletel representation achieves a classifier accurarcy of 83.33% and the confusion matrix can be seen in __Figure 2__ in the [appendix](#appendix). My _HOD_ skeletel representation achieves a classifier accuracy of 70.83% and the confusion matrix can be seen in __Figure 3__ in the [appendix](#appendix).  

&nbsp;&nbsp;These results are statistically significant because each method produce more than just a random guess.  In this case since there are 6 classes there is a 16.66% (1/6) that the classifier can randomly gues correctly.  But each of my skeletel representations has beter than 66.66% (2/3) chance of being corretly classifing. This means that the classifier is learning my representations and learning them effectively.

&nbsp;&nbsp;Both the classifier accuracy and confusion matrix will be outputed at the end of each call of `./run.sh`.

# References #
1. [Project paper](http://inside.mines.edu/~hzhang/Courses/CSCI498B-598B-Fall14/Projects/Project-2/Project-2.pdf) and attached papers.

# Appendix #
__Figure 1__: RAD confusion matrix
```
           +------------------------------------------------------------------+
           |Predicted                                                         |
+----------+------------------------------------------------------------------+
|Actual    |CheerUp    |TossPaper  |LineOnSofa |Walking   |StandUp |SitDown   |
+----------+-----------+-----------+-----------+----------+--------+----------+
|CheerUp   |8          |0          |0          |0         |0       |0         |
+----------+-----------+-----------+-----------+----------+--------+----------+
|TossPaper |0          |7          |0          |0         |1       |0         |
+----------+-----------+-----------+-----------+----------+--------+----------+
|LineOnSofa|0          |0          |5          |2         |0       |1         |
+----------+-----------+-----------+-----------+----------+--------+----------+
|Walking   |0          |1          |1          |4         |1       |1         |
+----------+-----------+-----------+-----------+----------+--------+----------+
|StandUp   |0          |3          |0          |0         |3       |2         |
+----------+-----------+-----------+-----------+----------+--------+----------+
|SitDown   |0          |0          |0          |2         |0       |6         |
+----------+-----------+-----------+-----------+----------+--------+----------+
```

__Figure 2__: HJPD confusion matrix
```
           +------------------------------------------------------------------+
           |Predicted                                                         |
+----------+------------------------------------------------------------------+
|Actual    |CheerUp    |TossPaper  |LineOnSofa |Walking   |StandUp |SitDown   |
+----------+-----------+-----------+-----------+----------+--------+----------+
|CheerUp   |8          |0          |0          |0         |0       |0         |
+----------+-----------+-----------+-----------+----------+--------+----------+
|TossPaper |1          |5          |1          |1         |0       |0         |
+----------+-----------+-----------+-----------+----------+--------+----------+
|LineOnSofa|0          |0          |7          |0         |1       |0         |
+----------+-----------+-----------+-----------+----------+--------+----------+
|Walking   |0          |0          |0          |7         |0       |1         |
+----------+-----------+-----------+-----------+----------+--------+----------+
|StandUp   |0          |0          |0          |0         |6       |2         |
+----------+-----------+-----------+-----------+----------+--------+----------+
|SitDown   |0          |0          |0          |0         |1       |7         |
+----------+-----------+-----------+-----------+----------+--------+----------+
```

__Figure 3__: HOD confusion matrix
```
           +------------------------------------------------------------------+
           |Predicted                                                         |
+----------+------------------------------------------------------------------+
|Actual    |CheerUp    |TossPaper  |LineOnSofa |Walking  |StandUp  |SitDown   |
+----------+-----------+-----------+-----------+---------+---------+----------+
|CheerUp   |5          |0          |1          |0        |0        |2         |
+----------+-----------+-----------+-----------+---------+---------+----------+
|TossPaper |1          |6          |0          |0        |1        |0         |
+----------+-----------+-----------+-----------+---------+---------+----------+
|LineOnSofa|2          |0          |5          |0        |0        |1         |
+----------+-----------+-----------+-----------+---------+---------+----------+
|Walking   |1          |0          |0          |6        |1        |0         |
+----------+-----------+-----------+-----------+---------+---------+----------+
|StandUp   |1          |0          |0          |1        |5        |1         |
+----------+-----------+-----------+-----------+---------+---------+----------+
|SitDown   |0          |1          |0          |0        |0        |7         |
+----------+-----------+-----------+-----------+---------+---------+----------+
```