/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:51:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/10 19:26:16 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static const char	*minishell_strnchr(const char *str, const char c, size_t n)
{
	if (c == '\0')
	{
		while (*str)
			str++;
		return (str);
	}
	while (*str)
		if ((*(str++) == c) && (!--n))
			return (str);
	return (NULL);
}

static void			minishell_envcmdsetval(t_list **subenv, char *str)
{
	size_t	seek;
	char	*name;
	char	*value;

	seek = ft_strsublen(str, '=');
	if (str[seek] != '\0')
	{
		name = ft_strndup(str, seek);
		value = ft_strdup(&str[seek + 1]);
	}
	else
	{
		name = ft_memdup(str, seek + 1);
		value = ft_strdup("");
	}
	minishell_setenvval(name, value, subenv);
	free(name);
}

static void			minishell_envcmdset(int ac, char **av, t_list *env)
{
	t_list		*subenv;
	size_t		p;
	char		*cmd;

	if (env)
	{
		if ((ac < 2) || (!(subenv = ft_lstdup(env, &minishell_envdup))))
			return ;
	}
	else
		subenv = NULL;
	p = 1;
	while ((av[p]) && (ft_strany('=', av[p])))
		minishell_envcmdsetval(&subenv, av[p++]);
	if (av[p])
	{
		cmd = ft_strunsplit((const char**)(unsigned long)&av[p], ' ');
		minishell_runcmd(cmd, &subenv);
		free(cmd);
	}
	else
		minishell_envshow(subenv);
	minishell_purgeenv(&subenv);
}

/*
** called by: minishell_builtin
** return : -1 in any case
*/

int					minishell_envcmd(int ac, char **av, t_list **env,
		const char *cmd)
{
	t_list	*fakeenv;

	if (!env)
		return (-1);
	if (!ft_strcmp(av[1], "-i"))
	{
		fakeenv = NULL;
		if (ac < 3)
			return (-1);
		cmd = minishell_strnchr(cmd, ' ', 2);
		minishell_runcmd(cmd, &fakeenv);
	}
	else if (av[1][0] != '-')
		minishell_envcmdset((int)ac, av, *env);
	else if (!ft_strcmp(av[1], "-u"))
		minishell_unsetenv((int)ac - 1, &av[1], env);
	else
		minishell_error(ERR_ENVPARSE_UNKNOW, av[1], 0);
	return (-1);
}
