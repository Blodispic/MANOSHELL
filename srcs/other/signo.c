#include "../../includes/minishell.h"

void ctrl_c(int n)
{
	(void)n;
	g_errna = 130;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_signal(t_struct *s)
{
	tcgetattr(0, &s->old_termios);
	tcgetattr(0, &s->new_termios);
    s->new_termios.c_lflag &= ~ECHOCTL;
	s->new_termios.c_cc[VQUIT] = 0;
    tcsetattr(0, TCSANOW, &s->new_termios);
	signal(SIGINT, ctrl_c);
}

void ctrl_child(int n)
{
	(void)n;
	printf("\n");
	g_errna = 130;
}