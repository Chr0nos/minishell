/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 00:59:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/16 03:10:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		minishell_purgeenv_cb(void *content, size_t size)
{
	t_env	*e;

	e = (t_env*)content;
	(void)size;
	ft_mfree(3, e->name, e->value, e);
}

int				minishell_purgeenv(t_list **env)
{
	if (env)
		ft_lstdel(env, minishell_purgeenv_cb);
	return (FLAG_BUILTIN);
}

static int		minishell_builtin_parse2(int ac, char **av, t_list **env)
{
	if (!ft_strcmp(av[0], "help"))
		return (minishell_help(ac, av, env));
	else if (!ft_strcmp(av[0], "nope"))
		return (FLAG_BUILTIN);
	return (0);
}

static int		minishell_builtin_parse(int ac, char **av, t_list **env)
{
	if ((!av) || (!av[0]))
		return (FLAG_BUILTIN);
	if (!ft_strcmp(av[0], "exit"))
		return (FLAG_QUIT);
	if (!env)
	{
		minishell_error(-999, "no environement address", 0);
		return (FLAG_BUILTIN);
	}
	if (!ft_strcmp(av[0], "cd"))
		return (minishell_cd(ac, av, env));
	if (!ft_strcmp(av[0], "env"))
		return (minishell_envcmd(ac, av, env));
	else if ((!ft_strcmp(av[0], "setenv")) || (!ft_strcmp(av[0], "export")))
		return (minishell_setenv(ac, av, env));
	else if (!ft_strcmp(av[0], "unsetenv"))
		return (minishell_unsetenv(ac, av, env));
	else if (!ft_strcmp(av[0], "purgeenv"))
		return (minishell_purgeenv(env));
	return (minishell_builtin_parse2(ac, av, env));
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
		return (FLAG_BUILTIN);
	if ((!ft_strcmp(cmd, ".")) || (!ft_strcmp(cmd, "..")))
	{
		minishell_error(ERR_NOTFOUND, ft_strdup(cmd), 1);
		return (FLAG_BUILTIN);
	}
	return (minishell_spliter(cmd, environement, &minishell_builtin_parse));
}
