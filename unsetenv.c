/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 02:42:51 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 15:27:56 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	minishell_unsetenv_lst(t_env *e)
{
	ft_mfree(3, e->name, e->value, e);
}

int			minishell_unsetenv(int ac, char **av, t_shell *shell)
{
	t_list	*lst;
	char	*name;

	if ((ac < 2) || (!shell->env) || (!av) || (!av[1]))
		return (FLAG_BUILTIN);
	lst = shell->env;
	while (lst)
	{
		name = ((t_env*)lst->content)->name;
		if ((name) && (ft_strcmp(name, av[1]) == 0))
		{
			ft_lstremove(&lst, &shell->env, &minishell_unsetenv_lst);
			return (FLAG_BUILTIN);
		}
		lst = lst->next;
	}
	return (FLAG_BUILTIN);
}
