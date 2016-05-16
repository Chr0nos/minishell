/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 15:44:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/16 16:00:45 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

char	**minishell_completion(const char *match)
{
	char			*cwd;
	t_list			*lst;
	DIR				*dir;
	struct dirent	*ent;
	char			**split;

	if (!(cwd = getcwd(NULL, 4096)))
		return (NULL);
	if ((!(dir = opendir(cwd))) && (ft_mfree(1, cwd)))
		return (NULL);
	lst = NULL;
	while ((ent = readdir(dir)))
	{
		if (ft_match(ent->d_name, match))
			ft_lstpush_back(&lst,
					ft_lstnew(ent->d_name, (size_t)ent->d_namlen));
	}
	closedir(dir);
	free(cwd);
	split = ft_lststrtotab(lst);
	ft_lstdel(&lst, NULL);
	return (split);
}

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
