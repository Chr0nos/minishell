/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 23:53:32 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/10 14:16:01 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

static int	minishell_exec_real(const char *app, const char *cmd, t_list *env)
{
	char	**args;
	char	**environement;
	int		ret;
	pid_t	pid;

	args = NULL;
	environement = NULL;
	if ((pid = fork()) == 0)
	{
		args = minishell_arguments_parse(cmd, app);
		environement = minishell_envmake(env);
		signal(SIGINT, SIG_DFL);
		if (execve(app, args, environement) == -1)
		{
			minishell_error(ERR_EXEC, NULL, 0);
			exit(0);
		}
	}
	else
	{
		wait(&ret);
		minishell_arguments_free(args);
		minishell_envtabfree(environement);
	}
	return (0);
}

static int	minishell_exec(const char *cmd, t_list *env)
{
	char			*app;
	const char		*pathlist;
	char			*fullpath;
	struct stat		st;
	int				ret;

	ret = 0;
	app = ft_strndup(cmd, ft_strsublenstr(cmd, SEPARATORS));
	if (lstat(app, &st) >= 0)
	{
		if (!(access(app, X_OK)))
			return (minishell_error(ERR_PERMS, app, 0));
		return (minishell_exec_real(app, cmd, env) + ft_mfree(1, app) - 1);
	}
	if (!(pathlist = minishell_envval(env, "PATH")))
		pathlist = MINISHELL_PATH_DEFAULT;
	if ((fullpath = minishell_getapp_path(app, pathlist)) != NULL)
	{
		ret = minishell_exec_real(fullpath, cmd, env);
		free(fullpath);
	}
	else if (ft_mfree(1, app))
		return (-1);
	free(app);
	return (ret);
}

/*
** called by: main() / minishell_envcmd()
*/

int			minishell_runcmd(const char *cmd, t_list **environement)
{
	int	ret;

	while ((*cmd) && (ft_strany(*cmd, SEPARATORS)))
		cmd++;
	if ((ret = minishell_builtin(cmd, environement)) < 0)
	{
		if (ret == ERR_EXIT)
			return (ERR_EXIT);
	}
	else if (minishell_exec(cmd, *environement) == ERR_NOTFOUND)
		minishell_error(ERR_NOTFOUND,
				ft_strndup(cmd, ft_strsublenstr(cmd, SEPARATORS)), 1);
	return (0);
}
