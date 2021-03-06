NAME = minishell

CC = gcc
FLAGS = -Wall -Wextra -Werror
LIB = -lft -L$(LFT_DIR)
INCL = -I$(HEAD_DIR) -I$(LFT_DIR)

LFT_DIR = ./libft/
LFT_HEAD =  $(LFT_DIR)libft.h
LIBFT = $(LFT_DIR)libft.a

HEAD_DIR = ./include/
HEAD = minishell.h
HEADS = $(addprefix $(HEAD_DIR), $(HEAD))

SRC_DIR = ./src/
SRC = main.c splitter.c extender.c token.c variables.c \
	exec_pipe.c exec.c matrice.c print_error.c exec_path.c \
	file_descriptor.c extractor.c extractor_1.c builtin_cd.c \
	builtin_pwd.c builtin_env.c builtin_exit.c builtin_echo.c \
	history.c pid.c input_checker.c unquoter.c extender_1.c \
	matrice_tools.c token_tools.c builtin.c readenv.c files_tools.c \
	signal.c export.c prompt.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR = ./tmp/
OBJ = $(patsubst %.c, %.o, $(SRC))
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	$(CC) $(OBJS) $(FLAGS) -lreadline $(LIB) $(INCL) -o $(NAME)

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
