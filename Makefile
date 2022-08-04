main: main.c
	cc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o HisnulMuslim
main2: main2.c
	x86_64-w64-mingw32-gcc main2.c libraylib.a -lgdi32 -lwinmm -static -Iinclude

