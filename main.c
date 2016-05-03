/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 17:34:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/03 18:57:21 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#define BUFF_SIZE 4096
#define STDIN 1

/*
** print the environement to the stdout
** return: pretty much as john snow knows...
*/

void	minishell_showenv(char **env)
{
	while (*env)
		ft_putendl(*(env++));
}

int		minishell_exec(int ac, char **av, char **env)
{
	pid_t	child;

	(void)minishell_exec;
	(void)ac;
	(void)env;
	(void)av;
	(void)child;
	return (0);
}

int		main(int ac, char **av, char **env)
{
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
		}
		usleep(42);
	}
	return (0);
}
