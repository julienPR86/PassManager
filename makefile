CC = gcc
TMP = tmp/
SCRIPTS = scripts/
OBJ = $(TMP)manager.o $(TMP)init.o $(TMP)add.o $(TMP)file.o $(TMP)get.o $(TMP)help.o $(TMP)inputs.o $(TMP)list.o $(TMP)command.o $(TMP)remove.o $(TMP)str.o $(TMP)utils.o
EXEC = manager.exe

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o manager $(OBJ)

$(TMP)manager.o : manager.c
	$(CC) -o $(TMP)manager.o -c manager.c

$(TMP)%.o : $(SCRIPTS)%.c
	$(CC) -o $@ -c $<

clean :
	rm -f $(TMP)*.o