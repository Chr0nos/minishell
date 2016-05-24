/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 15:44:05 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/24 19:33:34 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>

char		**minishell_completion(const char *match, const char *path)
{
	t_list			*lst;
	DIR				*dir;
	struct dirent	*ent;
	char			**split;

	if (!(dir = opendir(path)))
		return (NULL);
	lst = NULL;
	while ((ent = readdir(dir)))
		if (ft_match(ent->d_name, match))
			ft_lstpush_sort(&lst,
					ft_lstnew(ent->d_name, ft_strlen(ent->d_name) + 1),
					&ft_lststrcmp);
	closedir(dir);
	split = ft_lststrtotab(lst);
	ft_lstdel(&lst, NULL);
	return (split);
}

static int	minishell_complete_maxlen(char **tab)
{
	unsigned int	p;
	int				len;
	int				maxlen;

	p = 0;
	maxlen = 0;
	while (tab[p])
	{
		len = (int)ft_strlen(tab[p]);
		if (len > maxlen)
			maxlen = len;
		p++;
	}
	return (maxlen);
}

char		*minishell_complete(const char *buff, const char *path)
{
	char			*complete;
	char			**split;
	char			*pattern;
	size_t			blen;
	size_t			plen;

	(void)&minishell_complete_maxlen;
	if ((!buff) || (!path) || (!(pattern = ft_strmjoin(2, buff, "*"))))
		return (NULL);
	plen = ft_strlen(pattern);
	if ((!(split = minishell_completion(pattern, path))) &&
	(ft_mfree(1, pattern)))
		return (NULL);
	blen = (split[0]) ? ft_strlen(split[0]) : 0;
	if (blen > plen)
		complete = ft_strdup(split[0] + plen - 1);
	else
		complete = NULL;
	ft_free_tab(split, (unsigned int)ft_tabcount((void**)split));
	free(pattern);
	free(split);
	return (complete);
}
