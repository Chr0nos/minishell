/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 02:42:51 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/16 02:48:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_unsetenv_lst(t_env *e)
{
	ft_mfree(3, e->name, e->value, e);
}

int			minishell_unsetenv(int ac, char **av, t_list **env)
{
	t_list	*lst;
	char	*name;

	if ((ac < 2) || (!env) || (!*env) || (!av) || (!av[1]))
		return (FLAG_BUILTIN);
	lst = *env;
	while (lst)
	{
		name = ((t_env*)lst->content)->name;
		if ((name) && (ft_strcmp(name, av[1]) == 0))
		{
			ft_lstremove(&lst, env, &minishell_unsetenv_lst);
			return (FLAG_BUILTIN);
		}
		lst = lst->next;
	}
	return (FLAG_BUILTIN);
}
