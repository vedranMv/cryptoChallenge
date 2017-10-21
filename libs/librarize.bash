#!/bin/bash

# Compile sources into object files

## Process basic library (data encodings, XOR implementation...)
g++ -std=c++11 -fPIC -O -g basicFunctions.cpp -c -o basicFunctions.o

## Process AES library (EBC/CBD AES encryption/decryption)
g++ -std=c++11 -fPIC -O -g aes-openSSL.cpp -c -o aes-openSSL.o

## Merge
g++ -shared basicFunctions.o aes-openSSL.o -lcrypto -o libmycrypto.so 


# Housekeeping
rm basicFunctions.o
rm aes-openSSL.o
