CC = gcc
CFLAGS = -Wall -Werror -Wextra
OBJ = $(TMP)manager.o $(TMP)add.o $(TMP)file.o $(TMP)get.o $(TMP)help.o $(TMP)inputs.o $(TMP)list.o $(TMP)remove.o $(TMP)str.o $(TMP)utils.o
EXEC = manager.exe
SCRIPTS = scripts/
TMP = tmp/

all : $(EXEC) clean

$(EXEC) : $(OBJ)
	$(CC) -o $(EXEC) $^

$(TMP)%.o : $(SCRIPTS)%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	rm -f $(TMP)*.o