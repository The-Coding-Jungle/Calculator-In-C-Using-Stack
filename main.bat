if not exist .\build mkdir .\build
if not exist .\data mkdir .\data

gcc src\main.c -o build\main.exe
.\build\main.exe