##############################  SOURCE & OBJETS  ###############################

SRCS = srcs/other/main.c \
		srcs/other/ft_getpwd.c \
		srcs/other/ft_check_path.c \
		srcs/other/ft_check_path2.c \
		srcs/other/heredocs.c \
		srcs/other/heredocs_utils.c \
		srcs/other/signo.c \
		srcs/other/dollars_herede.c \
		srcs/parsing/parsing.c \
		srcs/parsing/tokenisation.c \
		srcs/parsing/syntax.c \
		srcs/parsing/var_first_token.c \
		srcs/parsing/utils.c \
		srcs/parsing/quotes.c \
		srcs/parsing/chevron.c \
		srcs/parsing/again_dollars.c \
		srcs/parsing/lst_bob.c \
		srcs/parsing/count.c \
		srcs/parsing/utils_dollars.c \
		srcs/parsing/dollars.c \
		srcs/parsing/fake_dollars.c \
		srcs/execute/ft_exec.c \
		srcs/execute/ft_fork_exec.c \
		srcs/execute/is_builtin.c \
		srcs/execute/ft_pathfinder.c \
		srcs/execute/ft_redirect.c \
		srcs/execute/ft_splitone.c \
		srcs/execute/ft_utils_exec.c \
		srcs/execute/ft_utils_exec2.c \
		srcs/execute/ft_strjoinfree.c \
		srcs/execute/builtin/ft_echo.c \
		srcs/execute/builtin/ft_pwd.c \
		srcs/execute/builtin/ft_cd.c \
		srcs/execute/builtin/ft_cd_utils.c \
		srcs/execute/builtin/ft_export.c \
		srcs/execute/builtin/ft_export_dup.c \
		srcs/execute/builtin/ft_export_print.c \
		srcs/execute/builtin/ft_export_lst.c \
		srcs/execute/builtin/ft_unset.c \
		srcs/execute/builtin/ft_env.c \
		srcs/execute/builtin/ft_exit.c \

		

OBJS = $(SRCS:.c=.o)

################################  VARIABLES  ###################################

NAME = minishell

INCLUDE = includes/minishell.h includes/structure.h libft/libft.h

RM = rm -f

GCCF = gcc -Wall -Wextra -Werror

POINT_A = libft/libft.a

##################################  RULES  #####################################

all :	libf $(NAME)

$(NAME):	$(POINT_A) $(INCLUDE) $(OBJS)
	$(GCCF) $(OBJS) -lreadline libft.a -o $(NAME)

%.o: %.c	$(INCLUDE) 
	${GCCF} -c $< -o $@ 

libf:
	$(MAKE) -C libft
	ln -sf libft/libft.a

$(POINT_A) : libf

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
