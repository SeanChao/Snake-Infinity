@echo off
cd C:\star\Snake-Infinity\build-qsnake-Desktop_Qt_5_12_3_MinGW_64_bit-Debug\
qmake "C:\star\Snake-Infinity\qsnake\qsnake.pro" -spec win32-g++ "CONFIG+=debug" "CONFIG+=qml_debug"  
make
REM make clean
cd C:\star\Snake-Infinity\build-qsnake-Desktop_Qt_5_12_3_MinGW_64_bit-Debug\debug
.\qsnake.exe