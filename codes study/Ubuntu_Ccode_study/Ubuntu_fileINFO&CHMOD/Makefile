# Makefile

CC=gcc
CFLAGS=-Wall -Wextra

FILE_INFO_SRC=file_info.c
CHG_ACS_SRC=change_access.c


FILE_INFO_OBJ=file_info.o
CHG_ACS_OBJ=change_access.o


EXE1=f_info
EXE2=chg_acs


all: $(EXE1) $(EXE2)

$(EXE1): $(FILE_INFO_OBJ)
	$(CC) $(CFLAGS) -o $(EXE1) $(FILE_INFO_OBJ)

$(EXE2): $(CHG_ACS_OBJ)
	$(CC) $(CFLAGS) -o $(EXE2) $(CHG_ACS_OBJ)

$(FILE_INFO_OBJ): $(FILE_INFO_SRC)
	$(CC) $(CFLAGS) -c $(FILE_INFO_SRC)

$(CHG_ACS_OBJ): $(CHG_ACS_SRC)
	$(CC) $(CFLAGS) -c $(CHG_ACS_SRC)

clean:
	rm -f *.o $(EXE1) $(EXE2)

# $(all)과 $(clean)의 타겟 충돌 방지
.PHONY: all clean
