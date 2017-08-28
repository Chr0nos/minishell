/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 04:27:37 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 15:21:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		minishell_export(int ac, char **av, t_shell *shell)
{
	char	*cmd;

	if (ac > 1)
	{
		cmd = ft_strunsplit((const char**)(unsigned long)&av[1], ' ');
		minishell_envcmdsetval(&shell->env, cmd);
		free(cmd);
	}
	else
		minishell_envshow(shell->env);
	return (FLAG_BUILTIN);
}
