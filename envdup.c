/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 14:37:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/08 14:44:43 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

void	*minishell_envdup(void *content)
{
	t_env	*es;
	t_env	*ed;

	es = (t_env*)content;
	if (!(ed = malloc(sizeof(t_env))))
		return (NULL);
	if ((!(ed->name = ft_strdup(es->name))) && (ft_mfree(1, ed)))
		return (NULL);
	if ((!(ed->value = ft_strdup(es->value))) && (ft_mfree(2, ed->name, ed)))
		return (NULL);
	return ((void*)ed);
}
