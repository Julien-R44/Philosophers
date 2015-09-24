NAME	= philosophers
DEBUG	= yes
ifeq ($(DEBUG),no)
	FLAGS= -Wall -Wextra -Werror
else
	FLAGS= -g -std=c99 -Wno-deprecated
endif
SRC		= \
			main.c thread.c misc.c init.c

OBJ		= $(SRC:.c=.o)
SRCDIR	= ./src/
OBJDIR	= ./obj/
INCDIR	= ./inc/
SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(OBJ))
INCS	= $(addprefix $(INCDIR), $(INC))

LDFLAGS	= -I./inc/ -I./libft/include/ -I./glfw/include/

.SILENT:

all: $(NAME)

$(NAME): $(OBJS) $(INCS)
	make -C libft/
	gcc $(FLAGS) -o $@ $^ $(LIBFLAG)
	echo "\\033[1;32mSuccess.\\033[0;39m"

$(OBJS): $(SRCS)
ifeq ($(DEBUG),yes)
	echo "\\033[1;31mDEBUG COMPILATION.. (no flags except -g)\\033[0;39m"
else
	echo "\\033[1;31mCompilation with -Wall -Wextra -Werror...\\033[0;39m"
endif
	echo "\\033[1;34mGenerating objects... Please wait.\\033[0;39m"
	# git submodule init
	# git submodule update
	# cd glfw/ ; ~/.brew/bin/cmake .
	# make -C glfw/
	gcc $(FLAGS) -c $(SRCS) $(LDFLAGS)
	mkdir -p $(OBJDIR)
	mv $(OBJ) $(OBJDIR)

.PHONY: clean fclean re

clean:
	echo "\\033[1;34mDeleting objects...\\033[0;39m"
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft/
	echo "\\033[1;34mDeleting $(NAME)\\033[0;39m"
	rm -f $(NAME)

re: fclean all
