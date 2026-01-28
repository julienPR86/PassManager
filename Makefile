CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

VPATH = sources:
OBJDIR = objs/

OBJS_REFS =	commands.o \
			execute.o \
			exit.o \
			file.o \
	 		init.o \
			inputs.o \
			history.o \
			manager.o \
			outputs.o \
			pass.o \
			settings.o \
			generator.o \
			utils.o

OBJS = $(addprefix $(OBJDIR), $(OBJS_REFS))

NAME = manager

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)%.o : %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJDIR) :
	mkdir -p $@

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean clean re
