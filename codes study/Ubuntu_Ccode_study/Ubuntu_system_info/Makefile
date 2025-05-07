# Makefile

CC=gcc
CFLAGS=-Wall -Wextra

WHOS_LOGIN_SRC=whoslogin.c
MYDATE_SRC=mydate.c

WHOS_LOGIN_OBJ=whoslogin.o
MYDATE_OBJ=mydate.o

EXE1=whoslogin
EXE2=mydate


all: $(EXE1) $(EXE2) $(EXE3)

$(EXE1): $(WHOS_LOGIN_OBJ)
	$(CC) $(CFLAGS) -o $(EXE1) $(WHOS_LOGIN_OBJ)

$(EXE2): $(MYDATE_OBJ)
	$(CC) $(CFLAGS) -o $(EXE2) $(MYDATE_OBJ)

$(WHOS_LOGIN_OBJ): $(WHOS_LOGIN_SRC)
	$(CC) $(CFLAGS) -c $(WHOS_LOGIN_SRC)

$(MYDATE_OBJ): $(MYDATE_SRC)
	$(CC) $(CFLAGS) -c $(MYDATE_SRC)

clean:
	rm -f *.o $(EXE1) $(EXE2) $(EXE3)

# $(all)과 $(clean)의 타겟 충돌 방지
.PHONY: all clean
