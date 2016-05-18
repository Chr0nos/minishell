/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 15:44:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/19 00:10:36 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

char	**minishell_completion(const char *match, const char *path)
{
	t_list			*lst;
	DIR				*dir;
	struct dirent	*ent;
	char			**split;

	if (!(dir = opendir(path)))
		return (NULL);
	lst = NULL;
	while ((ent = readdir(dir)))
	{
		if (ft_match(ent->d_name, match))
			ft_lstpush_sort(&lst,
					ft_lstnew(ent->d_name, ft_strlen(ent->d_name) + 1),
					&ft_lststrcmp);
	}
	closedir(dir);
	split = ft_lststrtotab(lst);
	ft_lstdel(&lst, NULL);
	return (split);
}
