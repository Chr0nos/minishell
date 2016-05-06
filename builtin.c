/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 00:59:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/06 18:22:39 by snicolet         ###   ########.fr       */
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
	if (env)
		ft_lstdel(env, minishell_unsetenv_cb);
	return (-1);
}

static int		minishell_builtin_parse(int ac, char **av, t_list **env,
		const char *cmd)
{
	if (!ft_strcmp(av[0], "exit"))
		return (ERR_EXIT);
	if (!env)
	{
		minishell_error(-999, "no environement address", 0);
		return (-1);
	}
	if (!ft_strcmp(av[0], "cd"))
	{
		if (ac == 1)
			return (minishell_cd_home(*env));
		ft_putendl("unsuported yet");
		return (-1);
	}
	if (!ft_strcmp(av[0], "env"))
	{
		if (ac == 1)
			return ((env) ? minishell_envshow(*env) : -1);
		return (minishell_envcmd(cmd, env));
	}
	return (0);
}

/*
** returns:
** -1 if the runned function is a builtin
** 0 if not
** ERR_EXIT to request the minishell to quit properly
*/

int				minishell_builtin(const char *cmd, t_list **environement)
{
	if (!cmd)
		return (-1);
	if (!ft_strcmp(cmd, "."))
		return (minishell_error(ERR_NOTFOUND, ".", 0));
	else if (!ft_strcmp(cmd, "unsetenv"))
		return (minishell_unsetenv(environement));
	return (minishell_spliter(cmd, environement, &minishell_builtin_parse));
}
