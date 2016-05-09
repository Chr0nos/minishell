/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/04 12:45:25 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/09 18:45:39 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

const char			*minishell_strchr(const char *str, const char *separators)
{
	while ((*str) && (!ft_strany(*str, separators)))
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

	len = ft_strsplitstr_count(cmd, SEPARATORS);
	if (!(arglist = malloc(sizeof(char*) * len + 2)))
		return (NULL);
	arglist[0] = ft_strdup(bin_path);
	cmd = minishell_strchr(cmd, SEPARATORS);
	if ((!cmd) && (!(arglist[1] = NULL)))
		return (arglist);
	space = 1;
	while (*cmd)
	{
		while (ft_strany(*cmd, SEPARATORS))
			cmd++;
		if (*cmd)
		{
			len = ft_strsublenstr(cmd, SEPARATORS);
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
