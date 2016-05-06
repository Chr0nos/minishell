/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 00:45:24 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/07 01:02:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_setenv(int ac, char **av, t_list **env)
{
	t_env	e;

	if (ac < 2)
	{
		ft_putendl_fd("minishell: error: unsetenv: invalid parameters num", 2);
		return (-1);
	}
	e.name = ft_strdup(av[1]);
	if (ac >= 3)
		e.value = ft_strunsplit((const char **)(unsigned long)&av[2], ' ');
	else
		e.value = ft_strdup("");
	if ((e.value) && (e.name))
		ft_lstpush_sort(env, ft_lstnew(&e, sizeof(t_env)), &minishell_esort);
	else
		ft_putendl_fd("minishell: error: failed to setenv: out of memory", 2);
	return (-1);
}
