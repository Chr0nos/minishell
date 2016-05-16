/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:51:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/16 04:37:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void			minishell_envcmdsetval(t_list **subenv, char *str)
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

static void		minishell_envcmdset(int ac, char **av, t_list *env)
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

static int		minishell_envlessi(int ac, char **av)
{
	char	*subcmd;
	int		p;
	t_list	*fakeenv;

	if (ac < 3)
		return (FLAG_BUILTIN);
	p = 2;
	fakeenv = NULL;
	subcmd = NULL;
	while ((av[p]) && (ft_strany('=', av[p])))
		minishell_envcmdsetval(&fakeenv, av[p++]);
	if (av[p])
	{
		subcmd = ft_strunsplit((const char **)(unsigned long)&av[p], ' ');
		minishell_runcmd(subcmd, &fakeenv);
		minishell_envfree(fakeenv);
		free(subcmd);
	}
	else
		minishell_envshow(fakeenv);
	return (FLAG_BUILTIN);
}

/*
** called by: minishell_builtin
** return : -1 in any case
*/

int				minishell_envcmd(int ac, char **av, t_list **env)
{
	if (!env)
		return (FLAG_BUILTIN);
	if (ac == 1)
		return (minishell_envshow(*env) | FLAG_BUILTIN);
	else if (!ft_strcmp(av[1], "-i"))
		return (minishell_envlessi(ac, av));
	else if (av[1][0] != '-')
		minishell_envcmdset((int)ac, av, *env);
	else if (!ft_strcmp(av[1], "-u"))
		minishell_unsetenv((int)ac - 1, &av[1], env);
	else
		minishell_error(ERR_ENVPARSE_UNKNOW, av[1], 0);
	return (FLAG_BUILTIN);
}
