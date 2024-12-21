CC = gcc
ARGS = -Wall -Werror -Wextra
OBJ = $(TMP)manager.o $(TMP)init.o $(TMP)data.o $(TMP)add.o $(TMP)file.o $(TMP)get.o $(TMP)help.o $(TMP)inputs.o $(TMP)list.o $(TMP)execute.o $(TMP)remove.o $(TMP)str.o $(TMP)utils.o
EXEC = manager.exe
TMP = tmp/
SCRIPTS = scripts/

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) -o manager $(OBJ) $(ARGS)

$(TMP)manager.o : manager.c
	$(CC) -o $@ -c $<

$(TMP)%.o : $(SCRIPTS)%.c
	$(CC) -o $@ -c $<

clean :
	rm -f $(TMP)*.o