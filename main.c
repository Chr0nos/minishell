/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 17:34:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/03 21:16:55 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#define BUFF_SIZE 4096
#define STDIN 1

/*
** return: pretty much as jon snow knows...
*/

static void	minishell_showenv(char **env)
{
	while (*env)
		ft_putendl(*(env++));
}

static char	*minishell_getenvitem(char **env, const char *item)
{
	const size_t	len = ft_strlen(item);

	while (*env)
	{
		if (!ft_memcmp(*env, item, len))
			return (*env);
		env++;
	}
	return (NULL);
}

static int	minishell_exec(const char *cmd, char **env)
{
	
	return (-1);
}

int			main(int ac, char **av, char **env)
{
	t_list	*environement;
	char	buff[BUFF_SIZE];
	ssize_t	ret;

	(void)av;
	(void)ac;
	while (42)
	{
		ft_putstr("$> ");
		if ((ret = read(STDIN, buff, BUFF_SIZE)) > 0)
		{
			buff[ret - 1] = '\0';
			if (!ft_strcmp(buff, "env"))
				minishell_showenv(env);
			else if (!ft_strcmp(buff, "exit"))
				return (0);
			else if (minishell_exec(buff, env) < 0)
				minishell_error_notfound(buff);
		}
		usleep(42);
	}
	return (0);
}
