/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 17:28:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/09 18:46:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		minishell_spliter(const char *cmd, t_list **env,
		int (*f)(int, char **, t_list **, const char *cmd))
{
	char	**av;
	size_t	size;
	int		ret;

	if (!(av = ft_strsplitstr(cmd, SEPARATORS)))
		return (1);
	size = ft_tabcount((void**)av);
	ret = f((int)(size) - 1, av, env, cmd);
	ft_free_tab(av, (unsigned int)size);
	free(av);
	return (ret);
}
