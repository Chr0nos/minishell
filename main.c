/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 17:34:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/04 20:54:16 by snicolet         ###   ########.fr       */
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

static int	minishell_exec_real(const char *app, const char *cmd,
		struct stat *st, t_list *env)
{
	char	**args;
	char	**environement;
	int		ret;
	pid_t	pid;

	args = NULL;
	environement = NULL;
	if (ft_strcmp(app, "/usr/bin/emacs") == 0)
		ft_putendl("it's not gonna happen !");
	else if ((pid = fork()) == 0)
	{
		args = minishell_arguments_parse(cmd, app);
		environement = minishell_envmake(env);
		execve(app, args, environement);
	}
	else
	{
		wait(&ret);
		minishell_arguments_free(args);
		minishell_envtabfree(environement);
	}
	(void)st;
	return (0);
}

static char	*minishell_mkpath(const char *root, const char *app, size_t lenapp)
{
	const size_t	len_root = ft_strlen(root);
	char			*fullpath;

	if (!(fullpath = malloc(sizeof(char) * (lenapp + len_root + 2))))
		return (NULL);
	ft_memcpy(fullpath, root, len_root);
	fullpath[len_root] = '/';
	ft_memcpy(fullpath + len_root + 1, app, lenapp + 1);
	return (fullpath);
}

static char	*minishell_getapp_path(const char *app, char *pathlist)
{
	char			*fullpath;
	struct stat		st;
	char			**paths;
	char			*ptr;
	size_t			p;

	ptr = NULL;
	p = 0;
	paths = ft_strsplit(pathlist, ':');
	while (paths[p])
	{
		fullpath = minishell_mkpath(paths[p], app, ft_strlen(app));
		if ((!ptr) && (lstat(fullpath, &st) >= 0))
			ptr = fullpath;
		else
			free(fullpath);
		free(paths[p]);
		p++;
	}
	free(paths);
	return (ptr);
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
		return (minishell_exec_real(app, cmd, &st, env) + ft_mfree(1, app) - 1);
	if ((!(pathlist = minishell_envval(env, "PATH"))) && (ft_mfree(1, app)))
		return (minishell_error_custom(
					"warning: no PATH environement variable found.", -2));
	if ((fullpath = minishell_getapp_path(app, pathlist)) != NULL)
	{
		ret = minishell_exec_real(fullpath, cmd, &st, env);
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
	while (42)
	{
		ft_putstr("$> ");
		if ((ret = read(STDIN, buff, BUFF_SIZE)) > 1)
		{
			buff[ret - 1] = '\0';
			if (!ft_strcmp(buff, "env"))
				minishell_envshow(environement);
			else if (!ft_strcmp(buff, "exit"))
				return (minishell_envfree(environement));
			else if (minishell_exec(buff, environement) < 0)
				minishell_error_notfound(buff);
		}
		else if (ret <= 0)
			break ;
	}
	return (minishell_envfree(environement));
}
