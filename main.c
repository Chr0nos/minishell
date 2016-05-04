/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 17:34:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/03 22:51:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#define BUFF_SIZE 4096
#define STDIN 1

static int	minishell_exec_real(const char *app, char *args, struct stat *st)
{
	pid_t	pid;

	ft_printf("real run: %s\n", app);
	if ((pid = fork()) == 0)
	{
		ft_putendl("CHILD OK");
	}
	//wait(-1);
	(void)app;
	(void)args;
	(void)st;
	return (0);
}

static char	*minishell_mkpath(const char *root, const char *app, size_t lenapp)
{
	size_t	len_root = ft_strlen(root);
	char	*fullpath;

	if (!(fullpath = malloc(sizeof(char) * (lenapp + len_root + 2))))
		return (NULL);
	ft_memcpy(fullpath, root, len_root);
	fullpath[len_root] = '/';
	ft_memcpy(fullpath + len_root + 1, app, lenapp + 1);
	ft_printf("mkpath: %s\n", fullpath);
	return (fullpath);

}

static char	*minishell_getapp_path(const char *app, char *pathlist)
{
	char			*fullpath;
	struct stat		st;
	char			**paths;
	char			*ptr;
	size_t			applen;

	ptr = NULL;
	applen = ft_strlen(app);
	paths = ft_strsplit(pathlist, ':');
	while (*paths)
	{
		fullpath = minishell_mkpath(*paths, app, applen);
		if ((!ptr) && (lstat(fullpath, &st)))
		{
			ft_printf("found app at: %s\n", fullpath);
			ptr = fullpath;
		}
		else
			free(fullpath);
		free(*paths);
		paths++;
	}
	//free(paths);
	return (ptr);
}

static int	minishell_exec(const char *cmd, t_list *env)
{
	char			*app;
	char			*pathlist;
	char			*fullpath;
	struct stat 	st;
	int				ret;

	app = ft_strndup(cmd, ft_strsublen(cmd, ' '));
	if (lstat(app, &st) >= 0)
		ret = minishell_exec_real(app, NULL, &st);
	if (!(pathlist = minishell_envval(env, "PATH")))
	{
		ft_putendl("warning: no PATH environement variable found.");
		ret = -2;
	}
	else
	{
		fullpath = minishell_getapp_path(app, pathlist);
		if (fullpath != NULL)
		{
			ret = minishell_exec_real(fullpath, NULL, &st);
			free(fullpath);
		}
		else
			ret = -1;
	}
	free(app);
	return (ret);
}

int			main(int ac, char **av, char **env)
{
	t_list	*environement;
	char	buff[BUFF_SIZE];
	ssize_t	ret;

	(void)av;
	(void)ac;
	minishell_envload(&environement, env);
	while (42)
	{
		ft_putstr("$> ");
		if ((ret = read(STDIN, buff, BUFF_SIZE)) > 0)
		{
			buff[ret - 1] = '\0';
			if (!ft_strcmp(buff, "env"))
				minishell_envshow(environement);
			else if (!ft_strcmp(buff, "exit"))
				break ;
			else if (minishell_exec(buff, environement) < 0)
				minishell_error_notfound(buff);
		}
		else
			break ;
		usleep(42);
	}
	minishell_envfree(environement);
	return (0);
}
