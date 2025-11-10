CC = gcc
ARGS = -Wall -Werror -Wextra -g
OBJ = $(TMP)manager.o $(TMP)init.o $(TMP)data.o $(TMP)generator.o $(TMP)add.o $(TMP)file.o $(TMP)get.o $(TMP)help.o $(TMP)inputs.o $(TMP)list.o $(TMP)execute.o $(TMP)remove.o $(TMP)str.o $(TMP)utils.o
EXEC = manager
TMP = tmp/
SCRIPTS = scripts/

all : $(EXEC)

$(EXEC) : $(OBJ)
	$(CC) $(ARGS) -o $@ $(OBJ)

$(TMP)manager.o : manager.c
	$(CC) $(ARGS) -o $@ -c $<

$(TMP)%.o : $(SCRIPTS)%.c
	$(CC) $(ARGS) -o $@ -c $<

clean :
	rm -f $(OBJ)

fclean : clean
	rm -f $(EXEC)

re : fclean all