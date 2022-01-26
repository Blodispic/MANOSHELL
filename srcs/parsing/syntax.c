#include "../../includes/minishell.h"


/*
 * params	:	la commande entiere qui vient d'etre taper
 * return	:	-1 si erreur, 0 si tout est ok
 * def		:	check les erreur de syntax chevron "<<< << <> >< <| >|"
 */
int	chevron(char *str)
{
		int	i;

		i = 0;
		while (str[i] && ft_is_chevron(str[i]))
				i++;
		if (i > 2)
		{
				if (str[i] == 0)
						i--;
				if (str[0] == '<' && str[1] == '<' && str[2] == '<')
						printf("this operator is not support `<<<' \n");
				else
						printf("syntax error near unexpected token `%c'\n", str[i]);
				return (-1);
		}
		if (i == 2 && str[0] != str[1])
		{
				printf("syntax error near unexpected token `%c'\n", str[1]);
				return (-1);
		}
		while (str[i] && ft_is_ispaces(str[i]))
				i++;
		if (str[i] && (ft_is_chevron(str[i]) || str[i] == '|'))
		{
				printf("syntax error near unexpected token `%c'\n", str[i]);
				return (-1);
		}
		return (0);
}

int	check_double_pipe(char *str)
{
		int i;

		i = 0;
		while (str[i])
		{
				if (str[i] && str[i] == '|')
				{
						i++;
						while (str[i] && str[i] == ' ')
								i++;
						if (str[i] && str[i] == '|')
						{
								printf("syntax error near unexpected token `%c'\n", str[i]);
								return (-1);
						}
				}
				if (str[i])
						i++;
		}
		return (0);
}

/*
 * params	:	la commande entiere qui vient d'etre taper
 * return	:	-1 si erreur, 0 si tout est ok
 * def		:	vas check la syntax premier et dernier caracteres
 */
int	specific_case_syntax(char *str)
{
		int last_caract;

		if (check_double_pipe(str) == -1)
				return (-1);
		last_caract = ft_strlen(str) - 1;
		if (str[0] == '|')
		{
				printf("syntax error near unexpected token `%c'\n", str[0]);
				return (-1);
		}
		while (last_caract > 0 && ft_is_ispaces(str[last_caract]))
				last_caract--;
		if (str[last_caract] == '|' || ft_is_chevron(str[last_caract]))
		{
				printf("syntax error near unexpected token");
				printf(" `%c'\n", str[last_caract]);
				return (-1);
		}
		return (0);
}

/*
 * params	:	la commande entiere qui vient d'etre taper
 * return	:	-1 si erreur, 0 si tout est ok
 * def		:	vas check la syyntax de chaques commande
 */

int	drole_de_chevron(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (ft_isascii(cmd[i]) == 0)
		{
			printf("ascci etendu not supported sorry\n");
			return (-1);
		}
		i++;
	}
	return (0);
}
int	command_syntax(char *str)
{
	int	i;

	i = 0;
	if (specific_case_syntax(str) == -1 || drole_de_chevron(str) == -1)
		return (-1);
	while (str[i])
	{
		if (ft_is_chevron(str[i]))
		{
			if (chevron(&str[i]) == -1)
				return (-1);
		}
		if (ft_is_quote(str[i]) == 1)
		{
			if (skip_quote(str, str[i], &i) == -1)
				return (-1);
		}
		if (str[i] && ft_is_quote(str[i]) == 0)
			i++;
	}
	return (0);
}

/*
 * params	: la commande qui viens d'etre taper
 * return	: -1 si erreur, 0 si tout est ok
 * def		: check si ligne vide
 */

int	no_commande(char *str)
{
	int i;

	i = 0;
	if (str[i] == 0)
		return (-1);
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (-1);
}
