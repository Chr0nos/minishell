/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 12:33:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/15 18:01:49 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keycodes.h"
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

static void	minishell_prompt_cbc_backspace(int *pos, t_list *env)
{
	if (*pos > 0)
	{
		(*pos)--;
		minishell_termcaps_key(MKEY_BACKSPACE, env);
	}
}

static int	minishell_prompt_cbc(char *buff, t_list *env)
{
	int			pos;

	pos = 0;
	while ((pos < BUFF_SIZE) && (read(STDIN_FILENO, &buff[pos], 1) > 0))
	{
		if (buff[pos] == MKEY_CTRL_D)
			return (0);
		else if (buff[pos] == MKEY_CLEAR)
			minishell_termcaps_key(MKEY_CLEAR, env);
		else if (buff[pos] == MKEY_BACKSPACE)
			minishell_prompt_cbc_backspace(&pos, env);
		else if (buff[pos++] == '\n')
		{
			buff[pos] = '\0';
			write(1, "\n", 1);
			return (pos);
		}
		else
			write(1, &buff[pos - 1], 1);
	}
	if (pos >= BUFF_SIZE)
		ft_putendl_fd("minishell: error: line is too long", 2);
	return (-1);
}

/*
** this function should not return anything until a new line was made
** in non termcaps mode it's waiting for read() to return
** in the termcaps mode: sleep is used to prevent cpu to boil eggs util the line
** is done
** return: the size of the line
*/

int			minishell_prompt(char *buff, t_list *env)
{
	int		ret;

	minishell_showprompt();
	if (ENABLE_TERMCAPS)
		ret = minishell_prompt_cbc(buff, env);
	else
		ret = (int)read(STDIN, buff, BUFF_SIZE);
	if (ret == 0)
	{
		write(1, "\n", 1);
		return (ERR_EXIT);
	}
	return (ret);
}

int			minishell_showprompt(void)
{
	char	*cwd;
	char	*dir;
	char	*path;

	if (!(cwd = getcwd(NULL, 4096)))
	{
		write(1, "$> ", 4);
		return (1);
	}
	dir = ft_strrchr(cwd, '/') + 1;
	if (*dir == '\0')
		dir--;
	path = ft_strmjoin(2, dir, " $> ");
	ft_putstr(path);
	free(cwd);
	free(path);
	return (1);
}
