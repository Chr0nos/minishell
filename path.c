/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 01:58:41 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/05 02:04:33 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

static char	*minishell_mkpath(const char *root, const char *app, size_t lenapp)
{
	const size_t	len_root = ft_strlen(root);
	char			*fullpath;

	if (!(fullpath = malloc(sizeof(char) * (lenapp + len_root + 2))))
		return (NULL);
	ft_memcpy(fullpath, root, len_root);
	fullpath[len_root] = '/';
	ft_memcpy(fullpath + len_root + 1, app, lenapp + 1);
	return (fullpath);
}

char		*minishell_getapp_path(const char *app, char *pathlist)
{
	char			*fullpath;
	struct stat		st;
	char			**paths;
	char			*ptr;
	size_t			p;

	ptr = NULL;
	p = 0;
	paths = ft_strsplit(pathlist, ':');
	while (paths[p])
	{
		fullpath = minishell_mkpath(paths[p], app, ft_strlen(app));
		if ((!ptr) && (lstat(fullpath, &st) >= 0) && (st.st_mode & X_OK))
			ptr = fullpath;
		else
			free(fullpath);
		free(paths[p]);
		p++;
	}
	free(paths);
	return (ptr);
}
