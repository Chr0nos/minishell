/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 18:59:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/06 20:36:14 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_cd_home(t_list *env)
{
	char	*home;

	home = minishell_envval(env, "HOME");
	if (!home)
		ft_putendl_fd("minishell: cd: error: no HOME environement variable", 2);
	else
	{
		ft_printf("minishell: cd: %s\n", home);
	}
	return (-1);
}

int		minishell_cd(int ac, char **av, t_list **env, const char *cmd)
{
	ft_putendl("cd requested");
	if (ac == 1)
		return (minishell_cd_home(*env));
	else if (ac > 2)
	{
		ft_putendl_fd("minishell: error: cd: too many parameters", 2);
		return (-1);
	}
	if (ft_strcmp(av[1], "."))
		return (-1);
	(void)cmd;
	(void)env;
	(void)av;
	return (-1);
}
