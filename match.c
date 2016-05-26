/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 18:37:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 15:30:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

int		minishell_match(int ac, char **av, t_shell *shell)
{
	char	**tab;
	int		p;
	char	*dir;

	(void)shell;
	if (ac < 2)
	{
		ft_putendl("minishell: match: usage: match [pattern] <folder path>");
		return (FLAG_BUILTIN);
	}
	dir = (ac > 2) ? ft_strdup(av[2]) : getcwd(NULL, 4096);
	tab = minishell_completion(av[1], dir);
	free(dir);
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
