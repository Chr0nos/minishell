/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 17:09:37 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/11 17:09:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_set_shell_level(t_list **env)
{
	t_env	*e;
	int		val;

	if ((e = minishell_getenv_byname(*env, "SHLVL")))
	{
		val = ft_atoi(e->value);
		minishell_editenv(e, ft_itoa(val + 1));
	}
	else if (CFG_SETSHLVL)
		minishell_addenv(env, "SHLVL", ft_strdup("1"));
}
