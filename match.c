/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:37:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/16 18:38:33 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>

int		minishell_match(int ac, char **av, t_list **env)
{
	char	**tab;
	int		p;

	(void)env;
	if (ac < 2)
		return (FLAG_BUILTIN);
	tab = minishell_completion(av[1]);
	p = 0;
	while (tab[p])
	{
		ft_putendl(tab[p]);
		free(tab[p]);
		p++;
	}
	free(tab);
	return (FLAG_BUILTIN);
}
