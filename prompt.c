/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 12:33:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/17 20:05:11 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keycodes.h"
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

static int	minishell_prompt_line(char *buff, int pos)
{
	buff[++pos] = '\0';
	write(1, "\n", 1);
	return (pos);
}

static void	minishell_prompt_cbc_init(int *ret, int *pos, char *key)
{
	*ret = 0;
	*pos = 0;
	ft_bzero(key, 2);
}

static int	minishell_prompt_cbc(char *buff, t_list *env)
{
	int			pos;
	int			ret;
	char		key[2];
	int			x;

	minishell_prompt_cbc_init(&ret, &pos, key);
	while ((pos < BUFF_SIZE) && ((ret = (int)read(STDIN_FILENO, key, 2)) > 0))
	{
		x = (int)(*(unsigned short*)(unsigned long)key);
		buff[pos] = key[0];
		if (minishell_prompt_skip(buff, &pos, x))
			;
		else if (minishell_termcap_read(env, buff, &pos, x) & FLAG_QUIT)
			return (0);
		else if (x == '\n')
			return (minishell_prompt_line(buff, pos));
		else if ((x != MKEY_BACKSPACE) && (x != MKEY_CLEAR))
			write(1, &x, 1);
		pos++;
		key[1] = '\0';
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
