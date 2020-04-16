CC=g++

HEADERS = $(wildcard *.h)

main: main.o loader.o
	$(CC) loader.o main.o -o main  -lGL -lglut -lGLU -lm

%.o : %.cpp {HEADERS}
	$(CC)  $<  -lGL -lGLU -lglut -lGLEW -o $@

clean:
	rm -rf *.