CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

TMP = tmp/
SRCS = scripts/

OBJS =	$(TMP)commands.o \
		$(TMP)execute.o \
		$(TMP)exit.o \
		$(TMP)file.o \
	 	$(TMP)init.o \
		$(TMP)inputs.o \
		$(TMP)manager.o \
		$(TMP)outputs.o \
		$(TMP)pass.o \
		$(TMP)settings.o \
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