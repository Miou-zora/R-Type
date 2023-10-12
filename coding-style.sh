#!/bin/bash

if [ "$1" = "--correct" ]; then
    clang-format client/**/*.hpp client/**/*.cpp client/main.cpp server/**/*.hpp server/**/*.cpp server/main.cpp libs/**/*.hpp -style=WebKit -i
else
    clang-format client/**/*.hpp client/**/*.cpp client/main.cpp server/**/*.hpp server/**/*.cpp server/main.cpp libs/**/*.hpp -style=WebKit --dry-run --Werror 2> coding-style.log
    if [ $(grep -c "error:" coding-style.log) -ne 0 ]; then
        echo "There are some errors in your code style. Please check them."
        exit 1
    else
        echo "Your code style is correct."
        exit 0
    fi
fi