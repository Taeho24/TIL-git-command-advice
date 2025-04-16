# Makefile

CC=gcc
CFLAGS=-Wall -Wextra

NEWCAT_SRC=newcat.c
NEWCP_SRC=newcp.c
LOAD_DF_SRC=load_dataFile.c


NEWCAT_OBJ=newcat.o
NEWCP_OBJ=newcp.o
LOAD_DF_OBJ=load_dataFile.o

EXE1=newcat
EXE2=newcp
EXE3=load_df


all: $(EXE1) $(EXE2) $(EXE3)

$(EXE1): $(NEWCAT_OBJ)
	$(CC) $(CFLAGS) -o $(EXE1) $(NEWCAT_OBJ)

$(EXE2): $(NEWCP_OBJ)
	$(CC) $(CFLAGS) -o $(EXE2) $(NEWCP_OBJ)

$(EXE3): $(LOAD_DF_OBJ)
	$(CC) $(CFLAGS) -o $(EXE3) $(LOAD_DF_OBJ)

$(NEWCAT_OBJ): $(NEWCAT_SRC)
	$(CC) $(CFLAGS) -c $(NEWCAT_SRC)

$(NEWCP_OBJ): $(NEWCP_SRC)
	$(CC) $(CFLAGS) -c $(NEWCP_SRC)

$(LOAD_DF_OBJ): $(LOAD_DF_SRC)
	$(CC) $(CFLAGS) -c $(LOAD_DF_SRC)

clean:
	rm -f *.o $(EXE1) $(EXE2) $(EXE3)

# $(all)과 $(clean)의 타겟 충돌 방지
.PHONY: all clean
