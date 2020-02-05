#!/bin/bash
EXE=test
MODULES="Board.cpp Memory.cpp"
HARNESS="test.cpp"

g++ -I. -o $EXE $MODULES $HARNESS

