/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 18:49:52 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/08 19:02:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		minishell_help(int ac, char **av, t_list **env)
{
	(void)ac;
	(void)av;
	(void)env;
	ft_putstr("Minishell help:\navailables commands: env / cd / unsetenv");
	ft_putstr(" / purgeenv / export / help / exit\n");
	return (-1);
}
