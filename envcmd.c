/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:51:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/05 16:52:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int			minishell_envcmd(const char *cmd, t_list *env)
{
	char	**av;
	size_t	ac;

	(void)env;
	av = ft_strsplit(cmd, ' ');
	ac = ft_tabcount((void**)av);
	if (ft_strcmp(av[1], "-i"))
		minishell_runcmd(minishell_strchr(cmd, ' '), NULL);
	ft_free_tab(av, (unsigned int)ac);
	free(av);
	return (-1);
}
