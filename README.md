# GraphProject
This project searches hierarchical structure in sequential data
The program is developed using C++11 and Python.
Ukkonen's algorithm is developed in C++ and then called as a process from python module
Python is used to develop actual DAG 

Build Instructions:

1. First need to build Ukkonen's algorithm implementation which is in sufixtree directory
2. a Makefile is provided so running make command should be enough (do a make clean first).
3. System must have C++ 11
4. The python module digraph.py can be run in python interpreter using python 3.5
5. Must need installed Networkx library in system
5. The code is written so that it can be run on three different data sets (simple input, yeast & igem)
6. Proper line should be uncommented in the beginning of main to select data set
 