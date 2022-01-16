# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: coop <coop@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 17:35:27 by rokupin           #+#    #+#              #
#    Updated: 2021/09/07 02:04:29 by rokupin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

SRC = \
ft_atoi.c      ft_itoa.c           ft_putchar_fd.c  ft_strlcat.c  ft_substr.c \
ft_bzero.c     ft_lstsize_bonus.c  ft_putendl_fd.c  ft_strlcpy.c  ft_tolower.c \
ft_calloc.c    ft_memccpy.c        ft_putnbr_fd.c   ft_strlen.c   ft_toupper.c \
ft_isalnum.c   ft_memchr.c         ft_putstr_fd.c   ft_strmapi.c  get_next_line.c \
ft_isalpha.c   ft_memcmp.c         ft_split.c       ft_strncmp.c  get_next_line_utils.c \
ft_isascii.c   ft_memcpy.c         ft_strchr.c      ft_strnstr.c 	ft_sort.c\
ft_isdigit.c   ft_memmove.c        ft_strdup.c      ft_strrchr.c \
ft_isprint.c   ft_memset.c         ft_strjoin.c     ft_strtrim.c
BNS = ft_lstnew_bonus.c ft_lstdelone_bonus.c ft_lstadd_front_bonus.c ft_lstadd_back_bonus.c ft_lstsize_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c ft_lstlast_bonus.c  ft_lstclear_bonus.c

HEAD = libft.h

OBS = ${SRC:.c=.o}

BBS = ${BNS:.c=.o}

CC = gcc

FLAGS = -Wall -Wextra -Werror

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
