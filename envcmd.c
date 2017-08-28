/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:51:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/28 02:11:20 by snicolet         ###   ########.fr       */
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

static void		minishell_envcmdset(int ac, char **av, t_shell *shell)
{
	t_shell		subshell;
	size_t		p;
	char		*cmd;

	if (shell->env)
	{
		if ((ac < 2) ||
				(!(subshell.env = ft_lstdup(shell->env, &minishell_envdup))))
			return ;
	}
	else
		subshell.env = NULL;
	p = 1;
	while ((av[p]) && (ft_strany('=', av[p])))
		minishell_envcmdsetval(&subshell.env, av[p++]);
	if (av[p])
	{
		subshell.builtins = shell->builtins;
		cmd = ft_strunsplit((const char**)(unsigned long)&av[p], ' ');
		minishell_runcmd(cmd, &subshell);
		free(cmd);
	}
	else
		minishell_envshow(subshell.env);
	minishell_purgeenv(ac, av, &subshell);
}

static int		minishell_envlessi(int ac, char **av, t_shell *shell)
{
	char		*subcmd;
	int			p;
	t_shell		fakeshell;

	if (ac < 3)
		return (FLAG_BUILTIN);
	p = 2;
	subcmd = NULL;
	fakeshell.env = NULL;
	while ((av[p]) && (ft_strany('=', av[p])))
		minishell_envcmdsetval(&fakeshell.env, av[p++]);
	if (av[p])
	{
		fakeshell.buff = NULL;
		fakeshell.builtins = shell->builtins;
		if ((subcmd = ft_strunsplit((const char **)(unsigned long)&av[p], ' ')))
		{
			minishell_runcmd(subcmd, &fakeshell);
			minishell_envfree(fakeshell.env);
			free(subcmd);
		}
	}
	else
		minishell_envshow(fakeshell.env);
	return (FLAG_BUILTIN);
}

/*
** called by: minishell_builtin
** return : -1 in any case
*/

int				minishell_envcmd(int ac, char **av, t_shell *shell)
{
	if (ac == 1)
		return (minishell_envshow(shell->env) | FLAG_BUILTIN);
	else if (!ft_strcmp(av[1], "-i"))
		return (minishell_envlessi(ac, av, shell));
	else if (av[1][0] != '-')
		minishell_envcmdset((int)ac, av, shell);
	else if (!ft_strcmp(av[1], "-u"))
		minishell_unsetenv((int)ac - 1, &av[1], shell);
	else
		minishell_error(ERR_ENVPARSE_UNKNOW, av[1], 0);
	return (FLAG_BUILTIN);
}
