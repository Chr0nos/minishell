/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 04:27:37 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/16 04:39:10 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		minishell_export(int ac, char **av, t_list **env)
{
	char	*cmd;

	if (ac > 1)
	{
		cmd = ft_strunsplit((const char**)(unsigned long)&av[1], ' ');
		minishell_envcmdsetval(env, cmd);
		free(cmd);
	}
	else
		minishell_envshow(*env);
	return (FLAG_BUILTIN);
}
