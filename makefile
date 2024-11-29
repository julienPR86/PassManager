CC = gcc
CFLAGS = -Wall -Werror -Wextra
OBJ = $(TMP)main.o $(TMP)manager.o $(TMP)add.o $(TMP)file.o $(TMP)get.o $(TMP)help.o $(TMP)inputs.o $(TMP)list.o $(TMP)remove.o $(TMP)setup.o $(TMP)str.o $(TMP)utils.o
EXEC = main.exe
SCRIPTS = scripts/
TMP = tmp/

all : $(EXEC) clean

$(EXEC) : $(OBJ)
	$(CC) -o $(EXEC) $^

$(TMP)main.o : main.c
	$(CC) -c -o $@ main.c $(CFLAGS)

$(TMP)%.o : $(SCRIPTS)%.c
	$(CC) -c -o $@ $< $(CFLAGS)
	
clean :
	rm -f $(TMP)*.o main.o