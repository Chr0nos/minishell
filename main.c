/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 17:34:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/10 19:47:32 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#define BUFF_SIZE 4096

static void	minishell_nope(int num)
{
	(void)num;
	write(1, "\n$> ", 4);
}

static int	minishell_runmulticmd(const char *cmd, t_list **env)
{
	char	**commands;
	size_t	p;
	int		ret;

	ret = 0;
	p = 0;
	commands = ft_strsplit(cmd, ';');
	while (commands[p])
	{
		if ((ret = minishell_runcmd(commands[p], env)) == ERR_EXIT)
		{
			ft_free_tab(commands, (unsigned int)ft_tabcount((void**)commands));
			free(commands);
			return (ERR_EXIT);
		}
		p++;
	}
	ft_free_tab(commands, (unsigned int)p);
	free(commands);
	return (ret);
}

static int	minishell_exec_params(int ac, char **av, t_list **env)
{
	int		ret;
	char	*cmd;

	if (ac < 2)
		return (0);
	cmd = ft_strunsplit((const char **)(unsigned long)&av[1], ' ');
	ret = minishell_runmulticmd(cmd, env);
	free(cmd);
	return (ret);
}

int			main(int ac, char **av, char **env)
{
	t_list	*environement;
	char	buff[BUFF_SIZE];
	ssize_t	ret;

	signal(SIGINT, &minishell_nope);
	minishell_envload(&environement, env);
	if (minishell_exec_params(ac, av, &environement) == ERR_EXIT)
		return (minishell_envfree(environement));
	while ((write(1, "$> ", 4)) && ((ret = read(STDIN, buff, BUFF_SIZE)) >= 0))
	{
		if (ret > 1)
		{
			buff[ret - 1] = '\0';
			if (minishell_runmulticmd(buff, &environement) == ERR_EXIT)
				break ;
		}
	}
	return (minishell_envfree(environement));
}
