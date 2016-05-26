/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 12:33:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 20:38:45 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keycodes.h"
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

/*
** this function should not return anything until a new line was made
** in non termcaps mode it's waiting for read() to return
** in the termcaps mode: sleep is used to prevent cpu to boil eggs util the line
** is done
** return: the size of the line
*/

int			minishell_prompt(char *buff, t_shell *shell)
{
	int		ret;

	minishell_showprompt();
	if (ENABLE_TERMCAPS)
		ret = minishell_termread(buff, shell);
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
