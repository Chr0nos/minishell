/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termread.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 02:49:12 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 17:21:56 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keycodes.h"
#include "libft.h"
#include <unistd.h>
#include <curses.h>
#include <term.h>

static void		minishell_termread_empty(char *buff, int *pos, size_t len)
{
	*pos = 0;
	buff[0] = '\0';
	while (len--)
		minishell_termcap_backspace();
}

static void		minishell_termread_clear(char *buff, int *pos)
{
	char	*res;

	buff[0] = '\0';
	*pos = 0;
	if (!(res = tgetstr("cl", NULL)))
		return ;
	tputs(res, 0, &minishell_termcaps_cb);
	minishell_showprompt();
}

static int		minishell_termread_char(unsigned short keycode, t_list *env,
	int *pos, char *buff)
{
	if (keycode == '\n')
	{
		buff[*pos] = '\0';
		*pos += 1;
		write(1, "\n", 1);
		return (READ_OK);
	}
	else if (keycode == MKEY_BACKSPACE)
	{
		if (*pos > 0)
		{
			*pos -= 1;
			minishell_termcap_backspace();
		}
		buff[*pos] = '\0';
	}
	else if (keycode == MKEY_CLEAR)
		minishell_termread_clear(buff, pos);
	else if ((keycode >= 32) && (keycode <= 127))
	{
		buff[(*pos)++] = (char)keycode;
		write(1, &keycode, 1);
	}
	return (minishell_termcap_completion(keycode, pos, buff, env));
}

/*
** singleton function needed by minishell_signal
** purpose: delete the current command line properly
*/

void			minishell_termread_reset(char *buff, int *pos)
{
	static char		*b;
	static int		*p;

	if ((buff) && (pos))
	{
		b = buff;
		p = pos;
	}
	else
		minishell_termread_empty(b, p, ft_strlen(b));
}

int				minishell_termread(char *buff, t_list *env)
{
	char			key[4];
	int				pos;
	int				ret;
	unsigned short	keycode;

	pos = 0;
	minishell_termread_reset(buff, &pos);
	*(unsigned short*)(unsigned long)key = 0;
	while ((pos < BUFF_SIZE) && (ret = read(STDIN_FILENO, key, 4) > 0))
	{
		keycode = *(unsigned short*)(unsigned long)key;
		if (keycode == MKEY_CTRL_D)
			return (0);
		if (minishell_termread_char(keycode, env, &pos, buff) == READ_OK)
			return (pos);
		*(unsigned short*)(unsigned long)key = 0;
	}
	if (pos >= BUFF_SIZE)
		ft_putendl_fd("minishell: error: line is too long", 2);
	return (FLAG_ERROR);
}
