/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 23:53:32 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/02 13:26:50 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

static int	minishell_exec_result(t_runcmd *rcmd)
{
	int		ret;

	waitpid(rcmd->child_pid, &ret, 0);
	minishell_termcap_start(*rcmd->term, rcmd->env);
	minishell_arguments_free(rcmd->args);
	minishell_envtabfree(rcmd->environement);
	signal(SIGINT, &minishell_signal);
	if (WEXITSTATUS(ret))
		return (FLAG_ERROR | ret);
	return (ret);
}

/*
** singletone setup:
** call exec real with APP = null , cmd = NULL and env = address of termis
** this use a very nasty cast, please future me: forgive me...
*/

int			minishell_exec_real(const char *app, const char *cmd, t_list *env)
{
	t_runcmd		rcmd;
	static t_term	*term = NULL;

	if ((!app) && (!cmd) && (env) && ((term = (t_term*)(unsigned long)env)))
		return (0);
	rcmd.args = NULL;
	rcmd.environement = NULL;
	rcmd.term = term;
	rcmd.env = env;
	tcsetattr(STDIN, 0, term);
	if ((rcmd.child_pid = fork()) == 0)
	{
		rcmd.args = minishell_arguments_parse(cmd, app);
		rcmd.environement = minishell_envmake(env);
		minishell_child(app, rcmd.args, rcmd.environement);
	}
	else if ((rcmd.child_pid < 0) && (!minishell_termcap_start(*term, env)))
	{
		ft_putendl_fd("minishell: error: failed to fork", 2);
		return (FLAG_ERROR);
	}
	else
		return (minishell_exec_result(&rcmd));
	return (0);
}

static int	minishell_execpath(char *app, t_list *env, const char *cmd)
{
	int		ret;
	char	*fullpath;
	char	*cwd;

	if (app[0] != '/')
	{
		cwd = getcwd(NULL, 4096);
		fullpath = ft_strmjoin(3, cwd, "/", app);
		free(cwd);
	}
	else
		fullpath = ft_strdup(app);
	if (((access(fullpath, X_OK) < 0)) && (ft_mfree(2, app, fullpath)))
		return (minishell_error(ERR_PERMS, app, 0));
	ret = minishell_exec_real(app, cmd, env);
	free(app);
	free(fullpath);
	return (ret);
}

static int	minishell_exec(const char *cmd, t_list *env)
{
	char			*app;
	const char		*pathlist;
	char			*fullpath;
	struct stat		st;
	int				ret;

	ret = 0;
	if (!(app = ft_strndup(cmd, ft_strsublenstr(cmd, SEPARATORS))))
		return (FLAG_QUIT | FLAG_ERROR);
	if (((app[0] == '/') || (app[0] == '.')) &&
			(lstat(app, &st) >= 0))
		return (minishell_execpath(app, env, cmd));
	if (((pathlist = minishell_envval(env, "PATH")) != NULL) &&
			((fullpath = minishell_getapp_path(app, pathlist)) != NULL))
	{
		ret = minishell_exec_real(fullpath, cmd, env);
		free(fullpath);
	}
	else
		ret = FLAG_ERROR | FLAG_NOTFOUND;
	free(app);
	return (ret);
}

/*
** called by: main() / minishell_envcmd()
*/

int			minishell_runcmd(const char *cmd, t_shell *shell)
{
	int	ret;

	while ((*cmd) && (ft_strany(*cmd, SEPARATORS)))
		cmd++;
	ret = minishell_builtin(cmd, shell);
	if ((ret & FLAG_QUIT) || (ret & FLAG_BUILTIN))
		return (ret);
	else if ((ret = minishell_exec(cmd, shell->env)) & FLAG_NOTFOUND)
		minishell_error(ERR_NOTFOUND,
				ft_strndup(cmd, ft_strsublenstr(cmd, SEPARATORS)), 1);
	return (ret & MASK_RET);
}
