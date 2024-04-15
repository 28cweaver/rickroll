windres rickroll.rc -o rickroll.o
g++ rickroll.cpp rickroll.o -o rickroll.exe -lole32 -lwinmm -static -mwindows