/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 02:42:51 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/07 02:57:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_unsetenv_lst(t_env *e)
{
	ft_mfree(3, e->name, e->value, e);
}

int		minishell_unsetenv(int ac, char **av, t_list **env)
{
	t_list	*lst;

	if ((ac < 2) || (!env) || (!*env))
		return (-1);
	lst = *env;
	while ((lst) && (ft_strcmp(((t_env*)lst->content)->name, av[1]) != 0))
		lst = lst->next;
	if (!lst)
		return (-1);
	ft_lstremove(&lst, env, &minishell_unsetenv_lst);
	return (-1);
}
