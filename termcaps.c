/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 19:47:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/13 21:19:03 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "keycodes.h"
#include <term.h>
#include <curses.h>

static int	minishell_termcaps_cb(int x)
{
	ft_putchar(x);
	return (0);
}

void		minishell_termcaps_key(int key)
{
	char	*res;

	if (key == MKEY_BACKSPACE)
		res = tgetstr("dc", NULL);
	else if (key == MKEY_CLEAR)
		res = tgetstr("cl", NULL);
	else
		res = NULL;
	if (res)
		tputs(res, 0, &minishell_termcaps_cb);
	if (key == MKEY_CLEAR)
		minishell_showprompt();
}
