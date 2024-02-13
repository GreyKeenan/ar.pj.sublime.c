
app: main.c
	gcc -o app.exe \
		*.c \
		-lSDL2

run:
	make
	@echo "\n...\n"
	@./app.exe

clean:
	rm app.exe
