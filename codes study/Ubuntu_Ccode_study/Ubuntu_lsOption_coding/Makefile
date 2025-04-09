# Makefile

CC=gcc
CFLAGS=-Wall
OBJ=main.o
EXE=rmcheck
#EXE=custls
#EXE=fcheck

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

main.o: main.c
	gcc -c main.c

clean:
	rm -f *.o $(EXE)
