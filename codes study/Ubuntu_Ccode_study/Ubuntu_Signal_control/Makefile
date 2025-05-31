# Makefile

CC=gcc
CFLAGS=-Wall -Wextra

FIRST_SRC=siginfoctrl.c
SECOND_SRC=sigblock.c
THIRD_SRC=sigtimer.c

FIRST_OBJ=siginfoctrl.o
SECOND_OBJ=sigblock.o
THIRD_OBJ=sigtimer.o

EXE1=siginfoctrl
EXE2=sigblock
EXE3=sigtimer


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
