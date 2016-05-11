/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 17:34:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/11 13:57:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

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
	if (!(cmd = ft_strunsplit((const char **)(unsigned long)&av[1], ' ')))
		return (ERR_EXIT);
	ret = minishell_runmulticmd(cmd, env);
	free(cmd);
	return (ret);
}

static void	minishell_set_shell_level(t_list **env)
{
	t_env	*e;
	int		val;

	if ((e = minishell_getenv_byname(*env, "SHLVL")))
	{
		val = ft_atoi(e->value);
		minishell_editenv(e, ft_itoa(val + 1));
	}
	else if (CFG_SETSHLVL)
		minishell_addenv(env, "SHLVL", ft_strdup("1"));
}

int			main(int ac, char **av, char **env)
{
	t_list	*environement;
	char	buff[BUFF_SIZE];
	ssize_t	ret;

	signal(SIGINT, &minishell_nope);
	minishell_envload(&environement, env);
	minishell_set_shell_level(&environement);
	if (minishell_exec_params(ac, av, &environement) == ERR_EXIT)
		return (minishell_envfree(environement));
	while ((ret = minishell_prompt(buff)) >= 0)
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
