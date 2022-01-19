NAME = minishell
ASAN = asan

CC = gcc
FLAGS = -Wall -Wextra -Werror -g
AFLAG = -fsanitize=address
LIB = -lft -L$(LFT_DIR)
INCL = -I$(HEAD_DIR) -I$(LFT_DIR)

LFT_DIR = ./libft/
LFT_HEAD =  $(LFT_DIR)libft.h
LIBFT = $(LFT_DIR)libft.a

HEAD_DIR = ./include/
HEAD = minishell.h
HEADS = $(addprefix $(HEAD_DIR), $(HEAD))

SRC_DIR = ./src/
SRC = main.c splitter.c extender.c variables.c
#SRC = exec.c main.c splitter.c splitter_1.c variables.c ORIGINAL SRC
SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR = ./tmp/
OBJ = $(patsubst %.c, %.o, $(SRC))
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -lreadline $(LIB) $(INCL) -o $(NAME)

$(ASAN): $(LIBFT) $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(AFLAG) $(FLAGS) $(LIB) $(INCL) -o $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HEADS)
	$(CC) -c $< $(FLAGS) $(INCL) -o $@

$(LIBFT):
	$(MAKE) -sC $(LFT_DIR)

clean:
	@$(MAKE) -sC $(LFT_DIR) clean
	@rm -rfd $(OBJ_DIR)*

fclean: clean
	@rm -rfd $(LIBFT)
	@rm -rfd $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all
