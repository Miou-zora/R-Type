@echo off

if "%1"=="--correct" (
  clang-format client\*.hpp client\*.cpp client\main.cpp server\*.hpp server\*.cpp server\main.cpp libs\*.hpp -style=WebKit -i
) else (
  clang-format client\*.hpp client\*.cpp client\main.cpp server\*.hpp server\*.cpp server\main.cpp libs\*.hpp -style=WebKit --dry-run --Werror 2> result.txt
  findstr /C:"error:" result.txt > nul
  if %errorlevel%==0 (
    echo There are some errors in your code style. Please check them.
    del result.txt
    exit /b 1
  ) else (
    echo Your code style is correct.
    del result.txt
    exit /b 0
  )
)