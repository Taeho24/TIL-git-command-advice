# Makefile

CC=gcc
CFLAGS=-Wall -Wextra

FIRST_SRC=divprocess.c
SECOND_SRC=execwho.c
THIRD_SRC=syncproc.c


FIRST_OBJ=divprocess.o
SECOND_OBJ=execwho.o
THIRD_OBJ=syncproc.o

EXE1=divprocess
EXE2=execwho
EXE3=syncproc


all: $(EXE1) $(EXE2) $(EXE3)

$(EXE1): $(FIRST_OBJ)
	$(CC) $(CFLAGS) -o $(EXE1) $(FIRST_OBJ)

$(EXE2): $(SECOND_OBJ)
	$(CC) $(CFLAGS) -o $(EXE2) $(SECOND_OBJ)

$(EXE3): $(THIRD_OBJ)
	$(CC) $(CFLAGS) -o $(EXE3) $(THIRD_OBJ)

$(FIRST_OBJ): $(FIRST_SRC)
	$(CC) $(CFLAGS) -c $(FIRST_SRC)

$(SECOND_OBJ): $(SECOND_SRC)
	$(CC) $(CFLAGS) -c $(SECOND_SRC)

$(THIRD_OBJ): $(THIRD_SRC)
	$(CC) $(CFLAGS) -c $(THIRD_SRC)

clean:
	rm -f *.o $(EXE1) $(EXE2) $(EXE3)

# $(all)과 $(clean)의 타겟 충돌 방지
.PHONY: all clean
