/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   purgeenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/25 23:16:15 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 15:28:57 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		minishell_purgeenv_cb(void *content, size_t size)
{
	t_env	*e;

	e = (t_env*)content;
	(void)size;
	ft_mfree(3, e->name, e->value, e);
}

int				minishell_purgeenv(int ac, char **av, t_shell *shell)
{
	(void)ac;
	(void)av;
	if (shell->env)
		ft_lstdel(&shell->env, minishell_purgeenv_cb);
	return (FLAG_BUILTIN);
}
