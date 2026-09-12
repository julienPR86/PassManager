CC = gcc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = includes

VPATH = sources:
SRCS =	commands.c \
		execute.c \
		exit.c \
		file.c \
		init.c \
		inputs.c \
		history.c \
		manager.c \
		outputs.c \
		pass.c \
		settings.c \
		generator.c \
		utils.c

OBJDIR = objs
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

NAME = manager

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJDIR)/%.o : %.c | $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES)

$(OBJDIR) :
	mkdir -p $@

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean clean re
