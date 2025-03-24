# Makefile

CC=gcc
CFLAGS=-Wall
PATCH=func.c
OBJ=main.o add.o sub.o mul.o div.o
EXE=calc.out

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

main.o: main.c $(PATCH)
	gcc -c main.c

add.o: add.c $(PATCH)
	gcc -c add.c

sub.o: sub.c $(PATCH)
	gcc -c sub.c

mul.o: mul.c $(PATCH)
	gcc -c mul.c

div.o: div.c $(PATCH)
	gcc -c div.c

clean:
	rm -f *.o $(EXE)
