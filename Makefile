# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/05 14:54:26 by ralves-g          #+#    #+#              #
#    Updated: 2022/11/15 11:57:05 by ralves-g         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
FLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

NAME		=	philo

INCLUDE		=	-I ./
SRCS_		=	\
				philosophers.c \
				args_check.c \
				init_philos.c \
				utils.c

SRCS		=	$(addprefix $(_SRC), $(SRCS_))

_OBJ		=	./obj/
_SRC		= 	./src/
OBJS		=	$(patsubst $(_SRC)%.c, $(_OBJ)%.o, $(SRCS))

all:		$(NAME)

$(_OBJ)%.o: $(_SRC)%.c
	$(CC) $(FLAGS) -c $< -o $@
	
$(NAME): $(_OBJ) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INCLUDE) -pthread

#bonus:		$(SRCS_B) $(OBJS_B)
#			$(CC) $(FLAGS) $(SRCS_B) -o $(NAME_B)
#			$(CC) $(FLAGS) $(SRCS_B) -c

$(_OBJ):
	mkdir $@

clean:
	$(RM) -r $(_OBJ)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all clean flean re
