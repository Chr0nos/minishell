/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 17:34:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/05 02:01:01 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <stdlib.h>
#define BUFF_SIZE 4096
#define STDIN 1

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
		if (execve(app, args, environement) == -1)
			minishell_error(ERR_EXEC, NULL, 0);
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
	char			*pathlist;
	char			*fullpath;
	struct stat		st;
	int				ret;

	ret = 0;
	app = ft_strndup(cmd, ft_strsublen(cmd, ' '));
	if (lstat(app, &st) >= 0)
	{
		if (!(st.st_mode & X_OK))
			return (minishell_error(ERR_PERMS, app, 0));
		return (minishell_exec_real(app, cmd, env) + ft_mfree(1, app) - 1);
	}
	if ((!(pathlist = minishell_envval(env, "PATH"))) && (ft_mfree(1, app)))
		return (minishell_error(ERR_NOPATH, NULL, 0));
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

int			main(int ac, char **av, char **env)
{
	t_list	*environement;
	char	buff[BUFF_SIZE];
	ssize_t	ret;

	(void)av[ac - 1];
	minishell_envload(&environement, env);
	while (write(1, "$> ", 4))
	{
		if ((ret = read(STDIN, buff, BUFF_SIZE)) > 1)
		{
			buff[ret - 1] = '\0';
			if ((ret = minishell_builtin(buff, environement)) < 0)
			{
				if (ret == ERR_EXIT)
					return (minishell_envfree(environement));
			}
			else if (minishell_exec(buff, environement) == ERR_NOTFOUND)
				minishell_error(ERR_NOTFOUND,
						ft_strndup(buff, ft_strsublen(buff, ' ')), 1);
		}
		else if (ret <= 0)
			break ;
	}
	return (minishell_envfree(environement));
}
