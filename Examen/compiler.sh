#!/usr/bin/bash

g++ $1.cpp -o $1 -pthread -std=c++20
./$1