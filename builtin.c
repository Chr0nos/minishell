/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 00:59:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/05 17:10:42 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** returns:
** -1 if the runned function is a builtin
** 0 if not
** ERR_EXIT to request the minishell to quit properly
*/

int		minishell_builtin(const char *cmd, t_list *environement)
{
	if (!ft_strcmp(cmd, "."))
		return (minishell_error(ERR_NOTFOUND, ".", 0));
	else if (!ft_strcmp(cmd, "env"))
		return (minishell_envshow(environement));
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (minishell_envcmd(cmd, environement));
	else if (!ft_strcmp(cmd, "exit"))
		return (ERR_EXIT);
	return (0);
}
