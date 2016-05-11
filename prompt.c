/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 12:33:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/11 18:00:15 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>

int		minishell_init(t_list **env, struct termios term)
{
	char	*nameterm;

	nameterm = getenv("TERM");
	if (tgetent(NULL, nameterm) == ERR)
	{
		ft_putstr_fd("minishell: error: failed to init termcaps\n", 2);
		return (ERR_EXIT);
	}
	minishell_set_shell_level(env);
	//term.c_lflag &= ~((unsigned long)ICANON);
	tcsetattr(STDIN, 0, &term);
	return (1);
}

int		minishell_quit(t_list *env, struct termios *term)
{
	(void)term;
	return (minishell_envfree(env));
}

int		minishell_prompt(char *buff)
{
	write(1, "$> ", 4);
	return ((int)read(STDIN, buff, BUFF_SIZE));
}
