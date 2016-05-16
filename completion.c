/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 15:44:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/16 18:38:39 by snicolet         ###   ########.fr       */
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
			ft_lstpush_sort(&lst,
					ft_lstnew(ent->d_name, (size_t)ent->d_namlen + 1),
					&ft_lststrcmp);
	}
	closedir(dir);
	free(cwd);
	split = ft_lststrtotab(lst);
	ft_lstdel(&lst, NULL);
	return (split);
}
