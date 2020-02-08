#!/bin/bash

g++ -I. -c Board.cpp
g++ -I. -c Memory.cpp
g++ -I. -c tests/test_Board.cpp
g++ -I. -c tests/test_Memory.cpp
g++ -I. -o test test.cpp Board.o Memory.o test_Board.o test_Memory.o

