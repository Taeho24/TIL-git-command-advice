# Makefile

CC=gcc
CFLAGS=-Wall
OBJ=check_empty_dir.o
#OBJ=custom_ls.o
#OBJ=file_check.o
EXE=rmcheck
#EXE=custls
#EXE=fcheck

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ)

check_empty_dir.o: check_empty_dir.c
	gcc -c main.c

clean:
	rm -f *.o $(EXE)
