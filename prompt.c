/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 12:33:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/17 16:29:17 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keycodes.h"
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

static void	minishell_prompt_cbc_backspace(int *pos, t_list *env, char *buff)
{
	if (*pos > 0)
	{
		*pos -= 1;
		minishell_termcaps_key(MKEY_BACKSPACE, env);
		write(1, "\b \b", 3);
	}
	buff[*pos] = '\0';
	(*pos)--;
}

static int	minishell_prompt_line(char *buff, int pos)
{
	buff[++pos] = '\0';
	write(1, "\n", 1);
	return (pos);
}

static int	minishell_prompt_cbc(char *buff, t_list *env)
{
	int			pos;
	ssize_t		ret;

	ret = 0;
	pos = 0;
	while ((pos < BUFF_SIZE) && ((ret = read(STDIN_FILENO, &buff[pos], 1)) > 0))
	{
		if (buff[pos] == MKEY_CTRL_D)
			return (0);
		else if (buff[pos] == MKEY_CLEAR)
			minishell_termcaps_key(MKEY_CLEAR, env);
		else if (buff[pos] == MKEY_BACKSPACE)
			minishell_prompt_cbc_backspace(&pos, env, buff);
		else if (buff[pos] == '\n')
			return (minishell_prompt_line(buff, pos));
		else
			write(1, &buff[pos], 1);
		pos++;
	}
	if (pos >= BUFF_SIZE)
		ft_putendl_fd("minishell: error: line is too long", 2);
	return (FLAG_ERROR);
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
		return (FLAG_QUIT | FLAG_ERROR);
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
