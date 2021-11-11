# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rozhou <rozhou@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/23 14:01:13 by elabasqu          #+#    #+#              #
#    Updated: 2021/11/11 15:47:52 by rozhou           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##############################  SOURCE & OBJETS  ###############################

SRCS = srcs/main.c \
		srcs/ft_check_path.c \

OBJS = $(SRCS:.c=.o)

################################  VARIABLES  ###################################

NAME = MANOSHEll

INCLUDE = includes/minishell.h includes/structure.h

RM = rm -f

GCCF = gcc -lreadline -Wall -Wextra #-Werror

##################################  RULES  #####################################

all :	libf $(NAME)


$(NAME):	$(INCLUDE) $(OBJS)
	$(GCCF) $(OBJS) libft.a -o $(NAME)

%.o: %.c	$(INCLUDE) 
	${GCCF} -c $< -o $@

libf:
	$(MAKE) -C libft
	ln -sf libft/libft.a

############################  CLEAN & RE & phony  ##############################

clean:
	${MAKE}  -C libft/ fclean
	$(RM) libft.a
	${RM} ${OBJS} 

fclean:		clean
	$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus libf


#################################### FIN  ######################################
