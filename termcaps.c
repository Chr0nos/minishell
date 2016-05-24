/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 19:27:04 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/24 04:15:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <curses.h>
#include <term.h>
#include <unistd.h>

int			minishell_termcaps_cb(int x)
{
	ft_putchar(x);
	return (0);
}

int			minishell_termcap_start(t_term term, t_list *env)
{
	const char	*nameterm;

	nameterm = minishell_getterm(env);
	if (tgetent(NULL, nameterm) == ERR)
	{
		ft_putstr_fd("minishell: error: failed to init termcaps\n", 2);
		ft_printf("shell name: %s\n", nameterm);
		return (ERR_EXIT);
	}
	term.c_lflag &= ~((unsigned long)ICANON);
	term.c_lflag &= ~((unsigned long)ECHO);
	tcsetattr(STDIN, TCSANOW, &term);
	return (0);
}
