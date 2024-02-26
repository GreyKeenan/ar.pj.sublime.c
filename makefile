
static: main.c build/
	gcc -o build/app.exe \
		*.c \
		-lSDL2
allDynamic: main.c

run: build/app.exe
	build/app.exe

clean: build/
	rm build/*
