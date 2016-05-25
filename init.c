/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 16:07:37 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/25 15:08:28 by snicolet         ###   ########.fr       */
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

int			minishell_init(t_list **env, struct termios term,
	char **environement)
{
	signal(SIGINT, &minishell_signal);
	minishell_envload(env, environement);
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

t_list	*minishell_init_builtin(void)
{
	t_list			*lst;
	const size_t	s = sizeof(t_builtin);
	char			*(*d)(const char *);
	t_list			*(*add)(t_list **, t_list *);

	lst = NULL;
	d = &ft_strdup;
	add = &ft_lstadd;
	add(&lst, ft_lstnew(&(t_builtin){d("cd"), &minishell_cd}, s));
	add(&lst, ft_lstnew(&(t_builtin){d("env"), &minishell_envcmd}, s));
	add(&lst, ft_lstnew(&(t_builtin){d("export"), &minishell_export}, s));
	add(&lst, ft_lstnew(&(t_builtin){d("setenv"), &minishell_setenv}, s));
	add(&lst, ft_lstnew(&(t_builtin){d("unsetenv"), &minishell_unsetenv}, s));
	add(&lst, ft_lstnew(&(t_builtin){d("purgeenv"), &minishell_purgeenv}, s));
	add(&lst, ft_lstnew(&(t_builtin){d("match"), &minishell_match}, s));
	add(&lst, ft_lstnew(&(t_builtin){d("help"), &minishell_help}, s));
	return (lst);
}
