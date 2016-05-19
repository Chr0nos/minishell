/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcaps.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 19:27:04 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/19 18:35:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "keycodes.h"
#include <curses.h>
#include <term.h>
#include <unistd.h>

static int	minishell_termcaps_cb(int x)
{
	ft_putchar(x);
	return (0);
}

void		minishell_termcaps_key(int key, t_list *env)
{
	char	*res;

	if (key == MKEY_BACKSPACE)
	{
		tgetent(NULL, minishell_getterm(env));
		res = tgetstr("dc", NULL);
	}
	else if (key == MKEY_CLEAR)
		res = tgetstr("cl", NULL);
	else
		res = NULL;
	if (res)
		tputs(res, 0, &minishell_termcaps_cb);
	if (key == MKEY_CLEAR)
		minishell_showprompt();
}

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

int			minishell_termcap_read(t_list *env, char *buff, int *pos, int x)
{
	if (x == MKEY_CTRL_D)
		return (FLAG_QUIT);
	else if (x == MKEY_CLEAR)
	{
		minishell_termcaps_key(MKEY_CLEAR, env);
		buff[0] = '\0';
		*pos = -1;
	}
	else if (x == MKEY_BACKSPACE)
		minishell_prompt_cbc_backspace(pos, env, buff);
	return (1);
}

int			minishell_termcap_start(t_term term, t_list *env)
{
	const char	*nameterm;

	nameterm = minishell_getterm(env);
	if (tgetent(NULL, nameterm) == ERR)
	{
		ft_putstr_fd("minishell: error: failed to init termcaps\n", 2);
		ft_printf("shell name: %s\n", nameterm);
		return (ERR_EXIT);
	}
	term.c_lflag &= ~((unsigned long)ICANON);
	term.c_lflag &= ~((unsigned long)ECHO);
	tcsetattr(STDIN, TCSANOW, &term);
	return (0);
}
