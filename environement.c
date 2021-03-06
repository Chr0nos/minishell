/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 21:20:13 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/19 21:31:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char		*minishell_envval(t_list *env, const char *key)
{
	if (!key)
		return (NULL);
	while (env)
	{
		if ((env->content) && (!ft_strcmp(((t_env*)env->content)->name, key)))
			return ((char*)((t_env*)env->content)->value);
		env = env->next;
	}
	return (NULL);
}

int			minishell_esort(t_list *a, t_list *b)
{
	return (ft_strcmp(((t_env*)a->content)->name, ((t_env*)b->content)->name));
}

static void	minishell_envloadpath(t_list **env)
{
	t_env	*e;

	e = minishell_getenv_byname(*env, "PATH");
	if (!e)
		minishell_addenv(env, "PATH", ft_strdup(MINISHELL_PATH_DEFAULT));
}

void		minishell_envload(t_list **lst, char **env)
{
	size_t	pos;
	t_env	x;

	if (!env)
		return ;
	*lst = NULL;
	while (*env)
	{
		pos = ft_strsublen(*env, '=');
		if (pos > 0)
		{
			if (!(x.name = malloc(sizeof(char) * pos + 1)))
				return ;
			ft_memcpy(x.name, *env, pos);
			x.name[pos] = '\0';
			x.value = ft_strdup(*env + pos + 1);
			ft_lstpush_sort(lst, ft_lstnew(&x, sizeof(t_env)), minishell_esort);
		}
		env++;
	}
	minishell_envloadpath(lst);
}

int			minishell_envfree(t_list *env)
{
	if (env)
	{
		ft_mfree(3, ((t_env*)env->content)->name,
				((t_env*)env->content)->value, env->content);
		minishell_envfree(env->next);
		free(env);
	}
	return (0);
}
