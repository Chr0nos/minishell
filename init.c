/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 16:07:37 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/27 00:55:51 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>
#include <curses.h>
#include <unistd.h>
#include <signal.h>

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

int			minishell_init(char **environement, t_shell *shell)
{
	signal(SIGINT, &minishell_signal);
	shell->history = NULL;
	shell->history_pos = NULL;
	shell->builtins = minishell_builtin_init();
	minishell_envload(&shell->env, environement);
	minishell_set_shell_level(&shell->env);
	if (!ENABLE_TERMCAPS)
		return (1);
	return (minishell_termcap_start(shell->term, shell->env));
}

/*
** actualy quit the minishell, properly
** only used by main (and should not be used by any other function)
** jobs: re-configure the terminal to disable termcaps
** (if they where not enabled)
*/

int			minishell_quit(t_shell *shell, int result)
{
	if (ENABLE_TERMCAPS)
		tcsetattr(STDIN, 0, &shell->term);
	minishell_envfree(shell->env);
	if (shell->builtins)
		ft_lstdel(&shell->builtins, &minishell_builtin_clear);
	if (shell->history)
		ft_lstdel(&shell->history, &minishell_builtin_clear);
	return (result);
}
