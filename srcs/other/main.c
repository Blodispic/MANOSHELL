#include "../../includes/minishell.h"

int	g_errna = 0;

void	destroy_bob(t_struct *s)
{
	s->bob = s->first_bob;
	while (s->bob != NULL)
	{
		ft_free_double_char(s->bob->token);
		if (s->bob->fd_out != 1)
			close(s->bob->fd_out);
		if (s->bob->fd_in != 0)
			close(s->bob->fd_in);
		free(s->bob);
		s->bob = s->bob->next;
	}
	free(s->data.id1);
}

void	str_zero(t_struct *s)
{
	int		i;
	t_list	*tmp;

	i = 0;
	printf("exit\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_errna = 0;
	if (s->data.env_path)
	{
		free(s->data.env_path[i++] - 5);
		while (s->data.env_path[i])
		{
			free(s->data.env_path[i]);
			i++;
		}
		free(s->data.env_path);
	}
	while (s->env)
	{
		tmp = s->env->next;
		free(s->env);
		s->env = tmp;
	}
	free(s->prompt);
	free(s->first);
	if (s->data.n == 1)
	{
		free(s->old_pwd.content);
		free(s->pwd.content);
		free(s->data.pwdpos.content);
		free(s->data.oldpwdpos.content);
	}
	if (s->data.n2 == 1)
		free(s->env->content);
}

int	main(int ac, char **av, char **envp)
{
	char			*str;
	t_struct		s;

	ft_check_path(&s, envp, ac, av);
	if (!isatty(0) || !isatty(1))
		return (1);
	while (1)
	{
		ft_get_pwd(&s, s.pwd.content);
		ft_signal(&s);
		str = readline(s.prompt);
		tcsetattr(0, TCSANOW, &s.old_termios);
		if (str == 0)
		{
			str_zero(&s);
			break ;
		}
		if (str[0] != '\0')
			add_history(str);
		if (parsing(str, &s) == -1)
			g_errna = 0;
		else
		{
			ft_exec(&s, 0, 0, 0);
			destroy_bob(&s);
		}
		free(str);
		free(s.prompt);
	}
}
/*
 * int	main(int ac, char **av, char **envp)
{
	char			*str;
	t_struct		s;

	ft_check_path(&s, envp, ac, av);
	if (!isatty(0) || !isatty(1))
		return (1);
	while (1)
	{
		ft_get_pwd(&s, s.pwd.content);
		ft_signal(&s);
		str = readline(s.prompt);
		tcsetattr(0, TCSANOW, &s.old_termios);
		if (str == 0)
		{
			str_zero();
			break ;
		}
		add_history(str);
		if (parsing(str, &s) == -1)
		{
			g_errna = 0;
			printf ("\033[31;01mERROR\033[00m\n");
		}
		else
		{
			printf("gerrna = %d\n", g_errna);
			printf ("\033[34;01mPERFECT\033[00m\n");
			ft_exec(&s, 0, 0, 0);
			s.env = s.first;
			destroy_bob(&s);
		}
		free(str);
		free(s.prompt);
	}
}
*/
