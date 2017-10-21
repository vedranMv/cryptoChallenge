#!/bin/bash

# Compile sources into object files
g++ -std=c++11 -c basicFunctions.cpp
g++ -std=c++11 -c aes-openSSL.cpp -lcrypto
# Merge objects into a linkable library
ar rcs libmycrypto.a basicFunctions.o aes-openSSL.o
# Housekeeping
rm basicFunctions.o
rm aes-openSSL.o
