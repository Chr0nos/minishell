/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 12:45:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/15 16:06:48 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
** copy the pointers int tab "src" into tab dest
*/

static void			minishell_strtabcpy(char **dest, char **src, size_t size)
{
	while (size--)
		dest[size] = src[size];
}

const char			*minishell_strchr(const char *str, const char *separators)
{
	while ((*str) && (!ft_strany(*str, separators)))
		str++;
	return (str);
}

char				**minishell_arguments_parse(const char *cmd,
		const char *bin_path)
{
	size_t	size;
	char	**split;
	char	**arglist;

	if (!(split = minishell_split(minishell_strchr(cmd, SEPARATORS))))
		return (NULL);
	size = ft_tabcount((void**)split);
	if (!(arglist = malloc(sizeof(char*) * (size + 1))))
	{
		free(split);
		return (NULL);
	}
	arglist[0] = ft_strdup(bin_path);
	minishell_strtabcpy(&arglist[1], split, size);
	free(split);
	return (arglist);
}

void				minishell_arguments_show(char **args)
{
	ft_putendl("arguments:");
	if (!args)
		ft_putendl("no argument... at all");
	else if (!*args)
		ft_putendl("no argument");
	else
		while (*args)
			ft_putendl(*(args++));
}

void				minishell_arguments_free(char **args)
{
	int		p;

	if (!args)
		return ;
	p = 0;
	while (args[p])
		free(args[p++]);
	free(args);
}
