CC = gcc
TMP = tmp/
SCRIPTS = scripts/
OBJ = $(TMP)main.o $(TMP)init.o $(TMP)add.o $(TMP)file.o $(TMP)get.o $(TMP)help.o $(TMP)inputs.o $(TMP)list.o $(TMP)manager.o $(TMP)remove.o $(TMP)str.o $(TMP)utils.o
EXEC = main.exe

all : $(EXEC) clean

$(EXEC) : $(OBJ)
	$(CC) -o main $(OBJ)

$(TMP)main.o : main.c
	$(CC) -o $(TMP)main.o -c main.c

$(TMP)%.o : $(SCRIPTS)%.c
	$(CC) -o $@ -c $<

clean :
	rm -f $(TMP)*.o