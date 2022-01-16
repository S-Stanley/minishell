# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rokupin <rokupin@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 17:35:27 by rokupin           #+#    #+#              #
#    Updated: 2022/01/16 19:31:21 by rokupin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

SRC = \
ft_lstlast_bonus.c      ft_strjoin.c\
ft_atoi.c               ft_lstmap_bonus.c       ft_strlcat.c\
ft_bzero.c              ft_lstnew_bonus.c       ft_strlcpy.c\
ft_calloc.c             ft_lstsize_bonus.c      ft_strlen.c\
ft_convert_base.c       ft_memccpy.c            ft_strmapi.c\
ft_convert_base2.c      ft_memchr.c             ft_strncmp.c\
ft_dtoa.c               ft_memcmp.c             ft_strnstr.c\
ft_isalnum.c            ft_memcpy.c             ft_strrchr.c\
ft_isalpha.c            ft_memmove.c            ft_strtrim.c\
ft_isascii.c            ft_memset.c             ft_substr.c\
ft_isdigit.c            ft_putchar_fd.c         ft_swap.c\
ft_isprint.c            ft_putendl_fd.c         ft_tolower.c\
ft_itoa.c               ft_putnbr_fd.c          ft_toupper.c\
ft_lstadd_back_bonus.c  ft_putstr_fd.c          get_next_line.c\
ft_lstadd_front_bonus.c ft_sort.c               get_next_line_utils.c\
ft_lstclear_bonus.c     ft_split.c\
ft_lstdelone_bonus.c    ft_strchr.c\
ft_lstiter_bonus.c      ft_strdup.c\
free_that_matrice.c     ft_strcmp.c

BNS = ft_lstnew_bonus.c ft_lstdelone_bonus.c ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c ft_lstsize_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstlast_bonus.c  ft_lstclear_bonus.c

HEAD = libft.h

OBS = ${SRC:.c=.o}

BBS = ${BNS:.c=.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror -g

all: ${NAME}
	ranlib ${NAME}

$(NAME): ${BBS} ${OBS}
	ar -rcs libft.a ${BBS} ${OBS}

bonus: ${BBS} ${OBS}
	ar -rcs libft.a ${BBS} ${OBS}

${OBS}: ${SRC}
	${CC} -g -c -I ${FLAGS} ${SRC} ${BNS}

clean:
	rm -f ${OBS}
	rm -f ${BBS}
	rm -f libft.h.gch

fclean: clean
	rm -f ${NAME}
	
re: fclean all
