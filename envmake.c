/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envmake.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 20:01:56 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/04 20:16:09 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	**minishell_envmake(t_list *env)
{
	char		**e;
	size_t		size;
	size_t		p;
	const char	*x[3];
	t_env		*item;

	size = ft_lstsize(env);
	if (!(e = malloc(sizeof(char*) * (size + 1))))
		return (NULL);
	p = 0;
	x[2] = NULL;
	while (p < size)
	{
		item = (t_env*)env->content;
		x[0] = item->name;
		x[1] = item->value;
		e[p] = ft_strunsplit(x, '=');
		p++;
	}
	e[size] = NULL;
	return (e);
}

void	minishell_envtabfree(char **env)
{
	size_t	p;

	if (!env)
		return ;
	p = 0;
	while (env[p])
		free(env[p++]);
	free(env);
}
