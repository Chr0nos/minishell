/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:51:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/06 18:22:32 by snicolet         ###   ########.fr       */
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
	(void)env;
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
	else
		minishell_error(ERR_ENVPARSE_UNKNOW, av[1], 0);
	ft_free_tab(av, (unsigned int)ac);
	free(av);
	return (-1);
}
