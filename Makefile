CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

TMP = tmp/
SRCS = scripts/

OBJS = 	$(TMP)manager.o \
	 	$(TMP)init.o \
		$(TMP)execute.o \
		$(TMP)commands.o \
		$(TMP)pass.o \
		$(TMP)file.o \
		$(TMP)exit.o \
		$(TMP)inputs.o \
		$(TMP)outputs.o \
		$(TMP)utils.o \

NAME = manager

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(TMP)%.o : $(SRCS)/%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all