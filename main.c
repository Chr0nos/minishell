/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 17:34:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/03 22:51:08 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#define BUFF_SIZE 4096
#define STDIN 1

static int	minishell_exec(const char *cmd, t_list *env)
{
	(void)env;
	(void)cmd;
	return (-1);
}

int			main(int ac, char **av, char **env)
{
	t_list	*environement;
	char	buff[BUFF_SIZE];
	ssize_t	ret;

	(void)av;
	(void)ac;
	minishell_envload(&environement, env);
	while (42)
	{
		ft_putstr("$> ");
		if ((ret = read(STDIN, buff, BUFF_SIZE)) > 0)
		{
			buff[ret - 1] = '\0';
			if (!ft_strcmp(buff, "env"))
				minishell_envshow(environement);
			else if (!ft_strcmp(buff, "exit"))
				break ;
			else if (minishell_exec(buff, environement) < 0)
				minishell_error_notfound(buff);
		}
		usleep(42);
	}
	minishell_envfree(environement);
	return (0);
}
