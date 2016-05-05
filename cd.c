/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 18:59:20 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/05 19:24:50 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_cd_home(t_list *env)
{
	char	*home;

	home = minishell_envval(env, "HOME");
	if (home)
		ft_printf("minishell: cd: %s\n", home);
	return (-1);
}

int		minishell_cd(const char *cmd, t_list **env)
{
	ft_putendl("cd requested");
	(void)cmd;
	(void)env;
	return (-1);
}
