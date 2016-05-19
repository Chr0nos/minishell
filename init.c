/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 16:07:37 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/19 18:36:23 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <curses.h>
#include <unistd.h>

const char	*minishell_getterm(t_list *env)
{
	t_env		*e;

	e = minishell_getenv_byname(env, "TERM");
	if (!e)
		return (DEFAULT_TERM);
	return ((const char*)e->value);
}

/*
** for the termcaps: the structure is volutary not pointed but copied
** because the main still keep the original environement for the cleanup stage
*/

int			minishell_init(t_list **env, struct termios term)
{
	minishell_set_shell_level(env);
	if (!ENABLE_TERMCAPS)
		return (1);
	return (minishell_termcap_start(term, *env));
}

/*
** actualy quit the minishell, properly
** only used by main (and should not be used by any other function)
** jobs: re-configure the terminal to disable termcaps
** (if they where not enabled)
*/

int			minishell_quit(t_list *env, struct termios *term, int result)
{
	if (ENABLE_TERMCAPS)
		tcsetattr(STDIN, 0, term);
	minishell_envfree(env);
	return (result);
}
