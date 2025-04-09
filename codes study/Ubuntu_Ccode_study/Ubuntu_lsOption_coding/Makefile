# Makefile

CC=gcc
CFLAGS=-Wall -Wextra

RM_CHECK_SRC=check_empty_dir.c
CUST_LS_SRC=custom_ls.c
FILE_CHECK_SRC=file_check.c


RM_CHECK_OBJ=check_empty_dir.o
CUST_LS_OBJ=custom_ls.o
FILE_CHECK_OBJ=file_check.o

EXE1=rmcheck
EXE2=custls
EXE3=fcheck


all: $(EXE1) $(EXE2) $(EXE3)

$(EXE1): $(RM_CHECK_OBJ)
	$(CC) $(CFLAGS) -o $(EXE1) $(RM_CHECK_OBJ)

$(EXE2): $(CUST_LS_OBJ)
	$(CC) $(CFLAGS) -o $(EXE2) $(CUST_LS_OBJ)

$(EXE3): $(FILE_CHECK_OBJ)
	$(CC) $(CFLAGS) -o $(EXE3) $(FILE_CHECK_OBJ)

$(RM_CHECK_OBJ): $(RM_CHECK_SRC)
	$(CC) $(CFLAGS) -c $(RM_CHECK_SRC)

$(CUST_LS_OBJ): $(CUST_LS_SRC)
	$(CC) $(CFLAGS) -c $(CUST_LS_SRC)

$(FILE_CHECK_OBJ): $(FILE_CHECK_SRC)
	$(CC) $(CFLAGS) -c $(FILE_CHECK_SRC)

clean:
	rm -f *.o $(EXE1) $(EXE2) $(EXE3)

# $(all)과 $(clean)의 타겟 충돌 방지
.PHONY: all clean
