/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 00:59:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 15:43:53 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int		minishell_builtin_parse2(int ac, char **av, t_shell *shell)
{
	if (!ft_strcmp(av[0], "help"))
		return (minishell_help(ac, av, shell));
	else if (!ft_strcmp(av[0], "nope"))
		return (FLAG_BUILTIN);
	else if (!ft_strcmp(av[0], "match"))
		return (minishell_match(ac, av, shell));
	else if ((ENABLE_TERMCAPS) && (!ft_strcmp(av[0], "clear")))
		return (minishell_clear(ac, av, shell));
	return (0);
}

static int		minishell_builtin_parse(int ac, char **av, t_shell *shell)
{
	if ((!av) || (!av[0]))
		return (FLAG_BUILTIN);
	if (!ft_strcmp(av[0], "exit"))
		return (minishell_exit(ac, av, shell));
	if (!ft_strcmp(av[0], "cd"))
		return (minishell_cd(ac, av, shell));
	if (!ft_strcmp(av[0], "env"))
		return (minishell_envcmd(ac, av, shell));
	else if (!ft_strcmp(av[0], "export"))
		return (minishell_export(ac, av, shell));
	else if (!ft_strcmp(av[0], "setenv"))
		return (minishell_setenv(ac, av, shell));
	else if (!ft_strcmp(av[0], "unsetenv"))
		return (minishell_unsetenv(ac, av, shell));
	else if (!ft_strcmp(av[0], "purgeenv"))
		return (minishell_purgeenv(ac, av, shell));
	return (minishell_builtin_parse2(ac, av, shell));
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
