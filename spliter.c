/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 17:28:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/15 16:05:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static char		*minishell_strfix(const char *str, size_t end)
{
	char	*x;

	if (!(x = malloc(sizeof(char) * (end + 1))))
		return (NULL);
	if (end > 0)
		ft_memcpy(x, str, end);
	x[end] = '\0';
	return (x);
}

static t_list	*minishell_lstadd(t_list **lst, const char *str, size_t end)
{
	t_list	*item;

	item = ft_lstnewlink(minishell_strfix(str, end), end);
	ft_lstpush_back(lst, item);
	return (item);
}

static void		minishell_split_while(const char **cmd, t_list **lst)
{
	size_t		pos;
	const char	*seps = " \t\"";

	if (**cmd == DQUOTE)
	{
		(*cmd)++;
		pos = ft_strsublen(*cmd, DQUOTE);
		minishell_lstadd(lst, *cmd, pos);
		*cmd += pos + 1;
	}
	else
	{
		pos = ft_strsublenstr(*cmd, seps);
		minishell_lstadd(lst, *cmd, pos);
		*cmd += pos;
	}
}

char			**minishell_split(const char *cmd)
{
	char		**split;
	t_list		*lst;

	lst = NULL;
	while (*cmd)
	{
		while ((*cmd) && (ft_strany(*cmd, SEPARATORS)))
			cmd++;
		if (*cmd)
			minishell_split_while(&cmd, &lst);
	}
	split = ft_lststrtotab(lst);
	ft_lstdel(&lst, NULL);
	return (split);
}

int				minishell_spliter(const char *cmd, t_list **env,
		int (*f)(int, char **, t_list **))
{
	char	**av;
	size_t	size;
	int		ret;

	if (!(av = minishell_split(cmd)))
		return (1);
	size = ft_tabcount((void**)av);
	ret = f((int)(size) - 1, av, env);
	ft_free_tab(av, (unsigned int)size);
	free(av);
	return (ret);
}
