#include "../../includes/minishell.h"

char	*one_token(char *cmd, int *i, t_struct *s);

int	ft_countwords(char *s)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (s[i])
	{
		while (s[i] && s[i] == ' ')
			i++;
		if (ft_is_chevron(s[i]) == 1)
		{
			while (ft_is_chevron(s[i]) == 1)
				i++;
			nb++;
		}
		if (s[i] && s[i] != ' ')
			nb++;
		while (s[i] && s[i] != ' ')
		{
			if (s[i] && s[i] == '|' && (s[i - 1] != ' ' || s[i + 1] != ' '))
			{
				if (s[i - 1] != ' ' && s[i + 1] != ' ')
					nb++;
				nb++;
			}
			if (s[i] && ft_is_quote(s[i]) == 1)
			{
				if (s[i] == ' ')
					nb++;
				skip_quote(s, s[i], &i);
			}
			else if (s[i] && ft_is_chevron(s[i]) == 1)
			{
				nb++;
				while (s[i] && ft_is_chevron(s[i]) == 1)
					i++;
				if (s[i] && s[i] != ' ' && ft_is_quote(s[i]) == 0 && ft_is_chevron(s[i]) == 0)
					nb++;
			}
			else
			{
				i++;
			}
		}
	}
	return (nb);
}
/*
 * params	: la commande
 * return	: le nb de token
 * def		: skipe les spaces prend bien les quotes
 *			  ignore les chevron et nom des redirection
 *			  (">> lol" pas pris en compte)
 *			  norme rend degeu le else if et while devrais etre ensemble;
 */

int	size_of_token(char *cmd, int i)
{
	int	tmp;

	tmp = i;
	if (ft_is_chevron(cmd[i]) == 1)
	{
		if (ft_is_chevron(cmd[i + 1]) == 1)
			return (2);
		return (1);
	}
	while (cmd[i] && cmd[i] != ' ')
	{
		if (cmd[i] == '\'' || cmd[i] == '\"' )
		{
			skip_quote(cmd, cmd[i], &i);
			return (i - tmp);
		}
		else if (ft_is_chevron(cmd[i]) == 1)
			return (i - tmp);
		else
			i++;
	}
	return (i - tmp);
}


void dollar_in_quote(char *cpy, char *cmd, int *i, int *j, t_struct *s)
{
	char *dollars;
	int k;

	k = 0;
	dollars = one_token(cmd, j, s);
	while (dollars[k])
		add_char(cpy, dollars, i, &k);
	free(dollars);
}

void	cpy_quote(char *cpy, char *cmd, int *i, int *j, t_struct *s)
{
	char	quote;

	quote = cmd[*j];
	add_char(cpy, cmd, i, j);
	//		(*j)++;
	while (cmd[*j] && cmd[*j] != quote)
	{
		if (cmd[*j] == '$' && quote == '\"')
			dollar_in_quote(cpy, cmd, i, j, s);
		else
			add_char(cpy, cmd, i, j);
	}
	//		(*j)++;
	add_char(cpy, cmd, i, j);
	if (cmd[*j] && ft_is_quote(cmd[*j]) == 1)
		cpy_quote(cpy, cmd, i, j, s);
	while (cmd[*j] && cmd[*j] != ' ' && ft_is_chevron(cmd[*j]) == 0 && ft_is_quote(cmd[*j]) == 0 && cmd[*i] != '|')
		add_char(cpy, cmd, i, j);
	if (cmd[*j] && ft_is_quote(cmd[*j]) == 1)
		cpy_quote(cpy, cmd, i, j, s);
	cpy[*i] = 0;
}

char	*cpy_chevron(char *cmd, int *i)
{
	int		j;
	char	*a_token;

	j = (*i) + 1;
	if (ft_is_chevron(cmd[j]) == 1)
		j++;
	a_token = malloc(sizeof(char) * (j + 1));
	if (a_token == NULL)
		return (NULL);
	j = 0;
	//	a_token[j] = cmd[*i];
	//	j++;
	//	(*i)++;
	add_char(a_token, cmd, &j, i);
	if (ft_is_chevron(cmd[*i]) == 1)
	{
		add_char(a_token, cmd, &j, i);
		//	a_token[j] = cmd[*i];
		//	j++;
		//	(*i)++;
	}
	a_token[j] = 0;
	return (a_token);
}

char *dollars_in_normal_token(char *str, char *cmd, int *i, t_struct *s)
{
	char	*dollars;
	char	*retur;

	dollars = one_token(cmd, i, s);
	retur = ft_strjoin(str, dollars);
	free(dollars);
	free(str);
	return(retur);
}

char	*normal_token(char *cmd, int *i, t_struct *s)
{
	int		j;
	char	*a_token;

	j = *i;
	while (cmd[*i] && cmd[*i] != ' ' && ft_is_chevron(cmd[*i]) == 0 && cmd[*i] != '|' && cmd[*i] != '$')
	{
		if (cmd[*i] == '\'' || cmd[*i] == '\"' )
			skip_quote(cmd, cmd[*i], i);
		else
			(*i)++;
	}
	a_token = malloc(sizeof(char) * (*i - j + 1));
	if (a_token == NULL)
		return (NULL);
	*i = j;
	j = 0;
	while (cmd[*i] && cmd[*i] != ' ' && ft_is_chevron(cmd[*i]) == 0 && ft_is_quote(cmd[*i]) == 0 && cmd[*i] != '|' && cmd[*i] != '$')
		add_char(a_token, cmd, &j, i);
	if (cmd[*i] != '$' && ft_is_quote(cmd[*i]) == 1)
		cpy_quote(a_token, cmd, &j, i, s);
	a_token[j] = 0;
	if (cmd[*i] == '$')
		return (dollars_in_normal_token(a_token, cmd, i, s));
	return (a_token);
}

char	*one_token(char *cmd, int *i, t_struct *s)
{
	char	*a_token;
	int		j;

	if (ft_is_chevron(cmd[*i]) == 1)
	{
		a_token = cpy_chevron(cmd, i);
		if (a_token == NULL)
			return (NULL);
	}
	else if (ft_is_quote(cmd[*i]) == 1)
	{
		j = *i;
		skip_quote(cmd, cmd[*i], i);
		*i += resize_len_for_dollar(cmd, j, *i, s);
		a_token = malloc(sizeof(char) * (*i - j + 1));
		if (a_token == NULL)
			return (NULL);
		*i = j;
		j = 0;
		cpy_quote(a_token, cmd, &j, i, s);
	}
	else if (cmd[*i] == '$')
	{
		a_token = one_token_dollars(cmd, i);
		if (a_token == NULL)
			return (NULL);
		if (search_dollars(a_token, s) == -1)
			return (NULL);
		a_token = change_dollars(a_token, s->env.content);
		if (a_token == NULL)
			return (NULL);
	}
	else if (cmd[*i] == '|')
	{
		(*i)++;
		a_token = malloc(sizeof(char) * 2);
		if (a_token == NULL)
			return (NULL);
		a_token[0] = '|';
		a_token[1] = 0;
	}
	else
	{
		a_token = normal_token(cmd, i, s);
		if (a_token == NULL)
			return (NULL);
		//peut y avoir $ dans quote normal token change le malloc aussi
	}
	return (a_token);
}

char **split_shell(char *cmd, t_struct *s)
{
	char	**token;
	int		i;
	int		word;

	token = malloc(sizeof(char *) * (ft_countwords(cmd) + 1));
	if (token == NULL)
		return (NULL);
	i = 0;
	word = 0;
	while (cmd[i])
	{
		while (cmd[i] && cmd[i] == ' ')
			i++;
		if (cmd[i])
		{
			token[word] = one_token(cmd, &i, s);
			if (token[word] == NULL)
			{
				//free
				return (NULL);
			}
			word++;
		}
	}
	token[word] = 0;
	return (token);
}
