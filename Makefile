all:
	gcc main.c biblioteca.c -o main
build:
	./main date.in date.out
clean:
	rm main