/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 15:36:02 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 15:44:41 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <curses.h>
#include <term.h>

int		minishell_clear(int ac, char **av, t_shell *shell)
{
	(void)ac;
	(void)av;
	(void)shell;
	tputs(tgetstr("cl", NULL), 0, minishell_termcaps_cb);
	return (FLAG_BUILTIN);
}
