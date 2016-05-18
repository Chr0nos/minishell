/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envshow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 01:27:44 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/19 01:28:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			minishell_envshow(t_list *env)
{
	t_env	*e;

	while (env)
	{
		e = (t_env*)env->content;
		ft_printf("%s=%s\n", e->name, e->value);
		env = env->next;
	}
	return (0);
}
