CC = gcc
CFLAGS = -Wall -Werror -Wextra
SCRIPTS = scripts
TMP = tmp/
OBJ = $(TMP)manager.o $(TMP)add.o $(TMP)file.o $(TMP)get.o $(TMP)help.o $(TMP)inputs.o $(TMP)list.o $(TMP)remove.o $(TMP)str.o $(TMP)utils.o

all : manager clean

manager : $(OBJ)
	$(CC) -o manager $^

$(TMP)%.o : $(SCRIPTS)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean :
	rm -f $(TMP)*.o