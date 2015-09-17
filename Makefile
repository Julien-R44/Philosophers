NAME	= philosophers
DEBUG	= yes
ifeq ($(DEBUG),no)
	FLAGS= -Wall -Wextra -Werror
else
	FLAGS= -g -std=c99
endif
SRC		= \
			main.c thread.c misc.c

OBJ		= $(SRC:.c=.o)
SRCDIR	= ./src/
OBJDIR	= ./obj/
INCDIR	= ./inc/
SRCS	= $(addprefix $(SRCDIR), $(SRC))
OBJS	= $(addprefix $(OBJDIR), $(OBJ))
INCS	= $(addprefix $(INCDIR), $(INC))
LIBFLAG = -L./libft/ -lft -L ~/.brew/lib -lSDLmain -lSDL -Wl,-framework,Cocoa
LDFLAGS	= -I./inc/ -I./libft/include/ `sdl-config --prefix=" ~/.brew/" --cflags`

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
