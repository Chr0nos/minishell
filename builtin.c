/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 00:59:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/07 01:00:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		minishell_unsetenv_cb(void *content, size_t size)
{
	t_env	*e;

	e = (t_env*)content;
	(void)size;
	ft_mfree(3, e->name, e->value, e);
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
		return (minishell_cd(ac, av, env, cmd));
	if (!ft_strcmp(av[0], "env"))
	{
		if (ac == 1)
			return ((env) ? minishell_envshow(*env) : -1);
		return (minishell_envcmd(cmd, env));
	}
	else if (!ft_strcmp(av[0], "setenv"))
		return (minishell_setenv(ac, av, env));
	return (0);
}

/*
** returns:
** -1 if the runned function is a builtin
** 0 if not
** ERR_EXIT to request the minishell to quit properly
** hey dude, let's have a little word about minishell_spliter
** this thing is not here to make coffe or something, it's my super main's like
** environement preparator, it call the minishell_builtin_parse but it may
** call any other function BUT thoses MUST return -1 in any cases, the -1
** is just here to say "ok i found the command do not report an error"
** the only valid other case is ERR_EXIT to request to the main a complete exit
** in case of 0 return: the called function DONT KNOWS the requested command
** deal with it !
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
