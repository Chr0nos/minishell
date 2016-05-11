/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 12:33:03 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/11 17:11:51 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <termios.h>

int		minishell_init(t_list **env, struct termios term)
{
	minishell_set_shell_level(env);
	term.c_lflag |= ICANON;
	return (1);
}

int		minishell_quit(t_list *env, struct termios *term)
{
	(void)term;
	return (minishell_envfree(env));
}

int		minishell_prompt(char *buff)
{
	write(1, "$> ", 4);
	return ((int)read(STDIN, buff, BUFF_SIZE));
}
