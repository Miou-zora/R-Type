#!/bin/bash

if [ "$1" = "--correct" ]; then
    clang-format client/**/*.hpp client/**/*.cpp client/main.cpp server/**/*.hpp server/**/*.cpp server/main.cpp libs/**/*.hpp -style=WebKit -i
else
    clang-format client/**/*.hpp client/**/*.cpp client/main.cpp server/**/*.hpp server/**/*.cpp server/main.cpp libs/**/*.hpp -style=WebKit --dry-run --Werror 2> result.txt
    if [ $(grep -c "error:" result.txt) -ne 0 ]; then
        echo "There are some errors in your code style. Please check them."
        rm result.txt
        exit 1
    else
        echo "Your code style is correct."
        rm result.txt
        exit 0
    fi
fi