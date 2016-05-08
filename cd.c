/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 18:59:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/08 13:12:58 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <sys/stat.h>

int			minishell_cd_home(t_list **env)
{
	char	*home;

	home = minishell_envval(*env, "HOME");
	if (!home)
		ft_putendl_fd("minishell: cd: error: no HOME environement variable", 2);
	else
		minishell_cd_real(env, home);
	return (-1);
}

static int	minishell_cd_error(const char *str, int ret)
{
	ft_putstr_fd("minishell: error: cd: ", 2);
	ft_putendl_fd(str, 2);
	return (ret);
}

/*
** returns:
** 0 in case of success
** -1 : not a dir
** -2 : permission denied
** -3 : no such file or directory
*/

static int	minishell_cd_trydir(const char *dir)
{
	struct stat		st;

	if (lstat(dir, &st) == 0)
	{
		if (!(st.st_mode & (S_IFDIR | S_IFLNK)))
			return (minishell_cd_error("not a directory", -1));
		else if (access(dir, X_OK) < 0)
			return (minishell_cd_error("permission denied", -2));
		return (0);
	}
	else
		return (minishell_cd_error("no such file or directory", -3));
}

void		minishell_cd_real(t_list **env, const char *dir)
{
	t_env	*e;

	if (!ft_strcmp(dir, "."))
		return ;
	if ((!minishell_cd_trydir(dir)) && (chdir(dir) != 0))
		ft_putendl_fd("minishell: error: cd: failed to change directory", 2);
	else
	{
		e = minishell_getenv_byname(*env, "PWD");
		if (e)
			minishell_editenv(e, getcwd(NULL, 4096));
		else
			minishell_addenv(env, "PWD", getcwd(NULL, 4096));
	}
}

int			minishell_cd(int ac, char **av, t_list **env)
{
	if (ac == 1)
		return (minishell_cd_home(env));
	else if (ac > 2)
	{
		ft_putendl_fd("minishell: error: cd: too many parameters", 2);
		return (-1);
	}
	else if (!ft_strcmp(av[1], "~"))
		return (minishell_cd_home(env));
	minishell_cd_real(env, av[1]);
	return (-1);
}
