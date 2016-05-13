/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 12:33:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/13 22:39:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keycodes.h"
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>

/*
** for the termcaps: the structure is volutary not pointed but copied
** because the main still keep the original environement for the cleanup stage
*/

int			minishell_init(t_list **env, struct termios term)
{
	t_env		*e;
	const char	*nameterm;

	minishell_set_shell_level(env);
	if (!ENABLE_TERMCAPS)
		return (1);
	nameterm = NULL;
	e = minishell_getenv_byname(*env, "TERM");
	nameterm = ((e) && (e->value)) ? (const char*)e->value : DEFAULT_TERM;
	if (tgetent(NULL, nameterm) == ERR)
	{
		ft_putstr_fd("minishell: error: failed to init termcaps\n", 2);
		ft_printf("shell name: %s\n", nameterm);
		return (ERR_EXIT);
	}
	term.c_lflag &= ~((unsigned long)ICANON);
	term.c_lflag &= ~((unsigned long)ECHO);
	tcsetattr(STDIN, TCSANOW, &term);
	return (1);
}

/*
** actualy quit the minishell, properly
** only used by main (and should not be used by any other function)
** jobs: re-configure the terminal to disable termcaps
** (if they where not enabled)
*/

int			minishell_quit(t_list *env, struct termios *term)
{
	if (ENABLE_TERMCAPS)
		tcsetattr(STDIN, 0, term);
	return (minishell_envfree(env));
}

static int	minishell_prompt_cbc(char *buff)
{
	int		pos;

	pos = 0;
	while ((pos < BUFF_SIZE) && (read(STDIN_FILENO, &buff[pos], 1) > 0))
	{
		if (buff[pos] == MKEY_CTRL_D)
			return (0);
		else if (buff[pos] == MKEY_CLEAR)
			minishell_termcaps_key(MKEY_CLEAR);
		else if (buff[pos] == MKEY_BACKSPACE)
		{
			if (pos > 0)
			{
				pos -= 1;
				minishell_termcaps_key(MKEY_BACKSPACE);
			}
		}
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

int			minishell_prompt(char *buff)
{
	int		ret;

	minishell_showprompt();
	if (ENABLE_TERMCAPS)
		ret = minishell_prompt_cbc(buff);
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
