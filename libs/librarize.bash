#!/bin/bash

g++ -std=c++11 -c basicFunctions.cpp
ar rcs libbasicfunc.a basicFunctions.o 
rm basicFunctions.o
