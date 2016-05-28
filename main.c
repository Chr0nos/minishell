/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 17:34:47 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/27 15:32:47 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <stdlib.h>
#include <termios.h>

static int	minishell_runmulticmd(const char *cmd, t_shell *shell)
{
	char	**commands;
	size_t	p;
	int		ret;

	ret = 0;
	p = 0;
	commands = ft_strsplit(cmd, ';');
	while (commands[p])
	{
		if ((ret = minishell_runcmd(commands[p], shell)) & FLAG_QUIT)
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

static int	minishell_exec_params(int ac, char **av, t_shell *shell)
{
	int		ret;
	char	*cmd;

	if (ac < 2)
		return (0);
	if (!(cmd = ft_strunsplit((const char **)(unsigned long)&av[1], ' ')))
		return (FLAG_QUIT);
	ret = minishell_runmulticmd(cmd, shell);
	free(cmd);
	return (ret);
}

int			main(int ac, char **av, char **env)
{
	t_shell			shell;
	char			buff[BUFF_SIZE];
	int				ret;
	int				r;

	shell.buff = (char*)buff;
	tcgetattr(0, &shell.term);
	minishell_exec_real(NULL, NULL, (t_list *)(unsigned long)&shell.term);
	minishell_init(env, &shell);
	if ((r = minishell_exec_params(ac, av, &shell)) & FLAG_QUIT)
		return (minishell_quit(&shell, r & MASK_RET));
	while (((ret = (int)minishell_prompt(buff, &shell)) >= 0) &&
		(!(ret & FLAG_QUIT)))
	{
		if ((ret > 1) && (ret < BUFF_SIZE))
		{
			buff[ret - 1] = '\0';
			r = minishell_runmulticmd(buff, &shell);
			if (r & FLAG_QUIT)
				break ;
		}
	}
	return (minishell_quit(&shell, r & MASK_RET));
}
