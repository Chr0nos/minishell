/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 00:45:24 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 15:26:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

t_env	*minishell_getenv_byname(t_list *env, const char *key)
{
	while (env)
	{
		if ((env->content) &&
		(ft_strcmp(((t_env*)env->content)->name, key) == 0))
			return ((t_env *)env->content);
		env = env->next;
	}
	return (NULL);
}

void	minishell_editenv(t_env *e, char *val)
{
	free(e->value);
	e->value = val;
}

void	minishell_addenv(t_list **env, const char *name, char *value)
{
	t_env	*e;

	if (!(e = malloc(sizeof(t_env))))
	{
		free(value);
		return ;
	}
	if ((!(e->name = ft_strdup(name))) && (ft_mfree(2, e, value)))
		return ;
	e->value = value;
	ft_lstpush_sort(env, ft_lstnewlink(e, sizeof(t_env)), &minishell_esort);
}

void	minishell_setenvval(const char *name, char *value, t_list **env)
{
	t_env	*e;

	e = minishell_getenv_byname(*env, name);
	if (!e)
		minishell_addenv(env, name, value);
	else
		minishell_editenv(e, value);
}

int		minishell_setenv(int ac, char **av, t_shell *shell)
{
	char	*value;

	if (ac < 2)
	{
		ft_putendl_fd("minishell: error: unsetenv: invalid parameters num", 2);
		return (FLAG_BUILTIN);
	}
	if (ac >= 3)
		value = ft_strunsplit((const char **)(unsigned long)&av[2], ' ');
	else
		value = ft_strdup("");
	minishell_setenvval(av[1], value, &shell->env);
	return (FLAG_BUILTIN);
}
