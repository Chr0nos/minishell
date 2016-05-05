/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 12:45:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/05 16:53:26 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

const char			*minishell_strchr(const char *str, const char c)
{
	while ((*str) && (*str != c))
		str++;
	if (*str)
		return (str);
	return (NULL);
}

char				**minishell_arguments_parse(const char *cmd,
		const char *bin_path)
{
	char		**arglist;
	size_t		len;
	size_t		space;

	len = ft_strsplit_count(cmd, ' ');
	if (!(arglist = malloc(sizeof(char*) * len + 2)))
		return (NULL);
	arglist[0] = ft_strdup(bin_path);
	cmd = minishell_strchr(cmd, ' ');
	if ((!cmd) && (!(arglist[1] = NULL)))
		return (arglist);
	space = 1;
	while (*cmd)
	{
		while (*cmd == ' ')
			cmd++;
		if (*cmd)
		{
			len = ft_strsublen(cmd, ' ');
			arglist[space++] = ft_strndup(cmd, len);
			cmd += len;
		}
	}
	arglist[space] = NULL;
	return (arglist);
}

void				minishell_arguments_show(char **args)
{
	ft_putendl("arguments:");
	if (!args)
		ft_putendl("no arguments... at all");
	else if (!*args)
		ft_putendl("no arguments");
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
