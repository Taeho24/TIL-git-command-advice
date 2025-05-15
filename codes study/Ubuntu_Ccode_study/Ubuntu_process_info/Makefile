# Makefile

CC=gcc
CFLAGS=-Wall -Wextra

MY_PID_SRC=getmypid.c
RUN_TIME_SRC=diffruntime.c
PATH_SET_SRC=getpathset.c


MY_PID_OBJ=getmypid.o
RUN_TIME_OBJ=diffruntime.o
PATH_SET_OBJ=getpathset.o

EXE1=getmypid
EXE2=diffruntime
EXE3=getpathset


all: $(EXE1) $(EXE2) $(EXE3)

$(EXE1): $(MY_PID_OBJ)
	$(CC) $(CFLAGS) -o $(EXE1) $(MY_PID_OBJ)

$(EXE2): $(RUN_TIME_OBJ)
	$(CC) $(CFLAGS) -o $(EXE2) $(RUN_TIME_OBJ)

$(EXE3): $(PATH_SET_OBJ)
	$(CC) $(CFLAGS) -o $(EXE3) $(PATH_SET_OBJ)

$(MY_PID_OBJ): $(MY_PID_SRC)
	$(CC) $(CFLAGS) -c $(MY_PID_SRC)

$(RUN_TIME_OBJ): $(RUN_TIME_SRC)
	$(CC) $(CFLAGS) -c $(RUN_TIME_SRC)

$(PATH_SET_OBJ): $(PATH_SET_SRC)
	$(CC) $(CFLAGS) -c $(PATH_SET_SRC)

clean:
	rm -f *.o $(EXE1) $(EXE2) $(EXE3)

# $(all)과 $(clean)의 타겟 충돌 방지
.PHONY: all clean
