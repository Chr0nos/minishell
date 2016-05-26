/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 18:49:52 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 15:30:47 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_help(int ac, char **av, t_shell *shell)
{
	(void)ac;
	(void)av;
	(void)shell;
	ft_putstr("Minishell help:\navailables commands: env / cd / unsetenv");
	ft_putstr(" / purgeenv / export / help / exit\n");
	return (FLAG_BUILTIN);
}
