/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 16:07:37 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 15:23:23 by snicolet         ###   ########.fr       */
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
	shell->builtins = minishell_init_builtin();
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
	return (result);
}

t_list	*minishell_init_builtin(void)
{
	t_list			*lst;
	const size_t	s = sizeof(t_builtin);
	t_list			*(*add)(t_list **, t_list *);

	lst = NULL;
	add = &ft_lstadd;
	add(&lst, ft_lstnew(&(t_builtin){"cd", &minishell_cd}, s));
	add(&lst, ft_lstnew(&(t_builtin){"env", &minishell_envcmd}, s));
	add(&lst, ft_lstnew(&(t_builtin){"export", &minishell_export}, s));
	add(&lst, ft_lstnew(&(t_builtin){"setenv", &minishell_setenv}, s));
	add(&lst, ft_lstnew(&(t_builtin){"unsetenv", &minishell_unsetenv}, s));
	add(&lst, ft_lstnew(&(t_builtin){"purgeenv", &minishell_purgeenv}, s));
	add(&lst, ft_lstnew(&(t_builtin){"match", &minishell_match}, s));
	add(&lst, ft_lstnew(&(t_builtin){"help", &minishell_help}, s));
	add(&lst, ft_lstnew(&(t_builtin){"exit", &minishell_exit}, s));
	return (lst);
}
