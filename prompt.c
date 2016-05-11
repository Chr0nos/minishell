/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 12:33:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/11 21:04:15 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>

/*
** for the termcaps: the structure is volutary not pointed but copied
** because the main still keep the original environement for the cleanup stage
*/

int		minishell_init(t_list **env, struct termios term)
{
	t_env		*e;
	const char	*nameterm;

	minishell_set_shell_level(env);
	if (!ENABLE_TERMCAPS)
		return (1);
	nameterm = NULL;
	e = minishell_getenv_byname(*env, "TERM");
	nameterm = ((e) && (e->value)) ? (const char*)e->value : DEFAULT_TERM;
	if (tgetent(NULL, nameterm) == ERR)
	{
		ft_putstr_fd("minishell: error: failed to init termcaps\n", 2);
		ft_printf("shell name: %s\n", nameterm);
		return (ERR_EXIT);
	}
	//term.c_lflag &= ~((unsigned long)ICANON);
	tcsetattr(STDIN, 0, &term);
	return (1);
}

/*
** actualy quit the minishell, properly
** only used by main (and should not be used by any other function)
** jobs: re-configure the terminal to disable termcaps
** (if they where not enabled)
*/

int		minishell_quit(t_list *env, struct termios *term)
{
	if (ENABLE_TERMCAPS)
		tcsetattr(STDIN, 0, term);
	return (minishell_envfree(env));
}

/*
** this function should not return anything until a new line was made
** in non termcaps mode it's waiting for read() to return
** in the termcaps mode: sleep is used to prevent cpu to boil eggs util the line
** is done
** return: the size of the line
*/

int		minishell_prompt(char *buff)
{
	write(1, "$> ", 4);
	return ((int)read(STDIN, buff, BUFF_SIZE));
}
