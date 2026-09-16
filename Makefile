CC = gcc
CFLAGS = -Wall -Wextra -Werror

INCLUDES = includes

LIBSDIR = libs

LIBSTRDIR = $(LIBSDIR)/libstr
LIBSTR = $(LIBSTRDIR)/libstr.h

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

$(OBJDIR)/%.o : %.c | $(OBJDIR) $(LIBSTR)
	$(CC) $(CFLAGS) -o $@ -c $< -I $(INCLUDES) -I $(LIBSTRDIR)

$(LIBSTR) : | $(LIBSTRDIR)
	git clone https://github.com/julienPR86/libstr.git $(LIBSTRDIR)

$(LIBSTRDIR) : | $(LIBSDIR)
	mkdir -p $@

$(LIBSDIR) :
	mkdir -p $@

$(OBJDIR) :
	mkdir -p $@

clean :
	rm -rf $(OBJDIR)

fclean : clean
	rm -f $(NAME)

lclean :
	rm -rf $(LIBSDIR)

re : fclean all

.PHONY : all clean fclean lclean re
