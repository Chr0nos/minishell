/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 00:59:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/05 19:28:07 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		minishell_unsetenv_cb(void *content, size_t size)
{
	t_env	*e;

	e = (t_env*)content;
	(void)size;
	ft_mfree(2, e->name, e->value);
}

static int		minishell_unsetenv(t_list **env)
{
	ft_lstdel(env, minishell_unsetenv_cb);
	return (-1);
}

/*
** returns:
** -1 if the runned function is a builtin
** 0 if not
** ERR_EXIT to request the minishell to quit properly
*/

int				minishell_builtin(const char *cmd, t_list **environement)
{
	if (!ft_strcmp(cmd, "."))
		return (minishell_error(ERR_NOTFOUND, ".", 0));
	else if (!ft_strcmp(cmd, "env"))
		return (minishell_envshow(*environement));
	else if (ft_strncmp(cmd, "env ", 4) == 0)
		return (minishell_envcmd(cmd, environement));
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (minishell_unsetenv(environement));
	else if (!ft_strcmp(cmd, "exit"))
		return (ERR_EXIT);
	else if (!(ft_strcmp(cmd, "cd")))
		minishell_cd_home(*environement);
	return (0);
}
