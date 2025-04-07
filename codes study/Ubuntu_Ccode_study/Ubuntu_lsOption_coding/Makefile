# Makefile

CC=gcc
CFLAGS=-Wall
PATCH=func.h
OBJ=main.o
EXE=

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

main.o: main.c $(PATCH)
	gcc -c main.c

clean:
	rm -f *.o $(EXE)
