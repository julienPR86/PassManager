CC = gcc
OBJ = main.o
EXEC = main.exe
TMP = tmp/

all : $(EXEC) clean

$(EXEC) : $(TMP)$(OBJ)
	$(CC) -o $(EXEC) main.c

$(TMP)$(OBJ) : main.c
	$(CC) -o $(TMP)$(OBJ) -c main.c

clean : 
	rm -f $(TMP)*.o