/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 00:59:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 17:01:21 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int		minishell_builtin_show(int ac, char **av, t_shell *shell)
{
	t_list	*b;

	(void)ac;
	(void)av;
	b = shell->builtins;
	while (b)
	{
		ft_putendl(((t_builtin*)b->content)->name);
		b = b->next;
	}
	return (FLAG_BUILTIN);
}

static int		minishell_builtin_parse(int ac, char **av, t_shell *shell)
{
	t_list	*builtin;

	if ((!av) || (!av[0]))
		return (FLAG_BUILTIN);
	builtin = shell->builtins;
	while (builtin)
	{
		if (!ft_strcmp(av[0], ((t_builtin*)builtin->content)->name))
		{
			return (((t_builtin*)builtin->content)->f(ac, av, shell) |
					FLAG_BUILTIN);
		}
		builtin = builtin->next;
	}
	return (FLAG_UNKNOW);
}

int				minishell_builtin(const char *cmd, t_shell *shell)
{
	if (!cmd)
		return (FLAG_BUILTIN);
	if ((!ft_strcmp(cmd, ".")) || (!ft_strcmp(cmd, "..")))
	{
		minishell_error(ERR_NOTFOUND, ft_strdup(cmd), 1);
		return (FLAG_BUILTIN);
	}
	return (minishell_spliter(cmd, shell, &minishell_builtin_parse));
}

void			minishell_builtin_clear(void *content, size_t size)
{
	free(content);
	(void)size;
}

t_list			*minishell_builtin_init(void)
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
	add(&lst, ft_lstnew(&(t_builtin){"builtins", &minishell_builtin_show}, s));
	if (ENABLE_TERMCAPS)
		add(&lst, ft_lstnew(&(t_builtin){"clear", &minishell_clear}, s));
	return (lst);
}
