
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "structure.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~PARSING~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*main fct of parsing*/
int			parsing(char *str, t_struct *s);
/*syntax*/
int			skip_quote(const char *s, char quote, int *i);
int			command_syntax(char *str);
/*split*/
int			ft_countwords(const char *s);
char		**shell_split(char *str, t_struct *s);



/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~EXEC~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/







/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~UTILS~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void		ft_check_path(t_struct *s, char **envp);

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#endif