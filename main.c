/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 17:34:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/19 17:15:01 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <termios.h>

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
		if ((ret = minishell_runcmd(commands[p], env)) & FLAG_QUIT)
		{
			ft_free_tab(commands, (unsigned int)ft_tabcount((void**)commands));
			free(commands);
			return (ret);
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
		return (FLAG_QUIT);
	ret = minishell_runmulticmd(cmd, env);
	free(cmd);
	return (ret);
}

int			main(int ac, char **av, char **env)
{
	t_term			term;
	t_list			*environement;
	char			buff[BUFF_SIZE];
	int				ret;
	int				r;

	tcgetattr(0, &term);
	minishell_exec_real(NULL, NULL, (t_list *)(unsigned long)&term);
	signal(SIGINT, &minishell_signal);
	minishell_envload(&environement, env);
	minishell_init(&environement, term);
	if ((r = minishell_exec_params(ac, av, &environement)) & FLAG_QUIT)
		return (minishell_quit(environement, &term, r & MASK_RET));
	while ((ret = (int)minishell_prompt(buff, environement)) >= 0)
	{
		if (ret & FLAG_QUIT)
			break ;
		if ((ret > 1) && (ret < BUFF_SIZE))
		{
			buff[ret - 1] = '\0';
			r = minishell_runmulticmd(buff, &environement);
			if (r & FLAG_QUIT)
				break ;
		}
	}
	return (minishell_quit(environement, &term, r & MASK_RET));
}
