#!/bin/bash

# Compile sources into object files

## Process basic library (data encodings, XOR implementation...)
g++ -std=c++11 -Wall -fPIC -O -g mycrypto-basic.cpp -c -o mycrypto-basic.o

## Process AES library (EBC/CBD AES encryption/decryption)
g++ -std=c++11 -Wall -fPIC -O -g mycrypto-aes.cpp -c -o mycrypto-aes.o

## Merge
g++ -shared mycrypto-basic.o mycrypto-aes.o -lcrypto -o libmycrypto.so 


# Housekeeping
rm mycrypto-basic.o
rm mycrypto-aes.o
