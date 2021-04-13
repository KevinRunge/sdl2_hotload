@echo off

set PROJECT_NAME=app
set INCLUDES=/ISDL2-2.0.14\include
set LIBS=shell32.lib SDL2-2.0.14\lib\x64\SDL2.lib SDL2-2.0.14\lib\x64\SDL2main.lib
set COMMON_FLAGS=/nologo /FC
set LIB_EXPORT=/EXPORT:GetLibCodeAPI

REM ======================== DEBUG BUILD ============================= 
ECHO === Windows x64 Debug Build ===
cl %COMMON_FLAGS% /Z7 /Fe%PROJECT_NAME%.dll /DDEBUG %INCLUDES% /Od src\libcode.cpp /LD /link %LIB_EXPORT% %LIBS% /DEBUG:FULL /incremental:no /opt:ref 
cl %COMMON_FLAGS% /Z7 /Fe%PROJECT_NAME%.exe /DDEBUG %INCLUDES% /Od src\%PROJECT_NAME%.cpp /link %LIBS% /DEBUG:FULL /incremental:no /opt:ref /SUBSYSTEM:CONSOLE
IF NOT EXIST SDL2.dll copy SDL2-2.0.14\lib\x64\SDL2.dll /Y
