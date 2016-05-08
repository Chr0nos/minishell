/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:51:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/08 18:38:30 by snicolet         ###   ########.fr       */
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

static void			minishell_envcmdset(int ac, char **av, t_list *env,
		const char *cmd)
{
	t_list	*subenv;
	char	*name;
	char	*value;
	size_t	seek;

	if ((!cmd) || (ac < 2) || (!(subenv = ft_lstdup(env, &minishell_envdup))))
		return ;
	seek = ft_strsublen(av[1], '=');
	if (av[1][seek] != '\0')
	{
		name = ft_strndup(av[1], seek);
		value = ft_strdup(&av[1][seek + 1]);
	}
	else
	{
		name = ft_memdup(av[1], seek + 1);
		value = ft_strdup("");
	}
	minishell_setenvval(name, value, &subenv);
	minishell_runcmd(cmd, &subenv);
	minishell_purgeenv(&subenv);
	free(name);
}

/*
** called by: minishell_builtin
** return : -1 in any case
*/

int					minishell_envcmd(const char *cmd, t_list **env)
{
	char	**av;
	size_t	ac;
	t_list	*fakeenv;

	if ((!env) || (!*env))
		return (-1);
	av = ft_strsplit(cmd, ' ');
	ac = ft_tabcount((void**)av);
	if (!ft_strcmp(av[1], "-i"))
	{
		fakeenv = NULL;
		if (ac < 4)
			ft_putendl_fd("minishell: error: env: missing parameter", 2);
		else
			minishell_runcmd(minishell_strnchr(cmd, ' ', 2), &fakeenv);
	}
	else if (av[1][0] != '-')
		minishell_envcmdset((int)ac, av, *env, minishell_strnchr(cmd, ' ', 2));
	else if (!ft_strcmp(av[1], "-u"))
		minishell_unsetenv((int)ac - 1, &av[1], env);
	else
		minishell_error(ERR_ENVPARSE_UNKNOW, av[1], 0);
	ft_free_tab(av, (unsigned int)ac);
	free(av);
	return (-1);
}
