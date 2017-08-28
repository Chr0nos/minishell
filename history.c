/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 22:54:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 23:10:52 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	minishell_history_show(int nb, t_list *history)
{
	if (history)
	{
		minishell_history_show(nb - 1, history->next);
		ft_printf("[%d] %s\n", nb, (char*)history->content);
	}
}

int			minishell_history(int ac, char **av, t_shell *shell)
{
	const int	hs = (int)ft_lstsize(shell->history);

	(void)ac;
	(void)av;
	minishell_history_show(hs, shell->history);
	return (FLAG_BUILTIN);
}
