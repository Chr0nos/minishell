/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/16 12:26:48 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/16 21:20:19 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int		minishell_exit(int ac, char **av, t_list **env)
{
	(void)env;
	if (ac > 1)
		return (FLAG_BUILTIN | FLAG_QUIT | (ft_atoi(av[1]) & MASK_RET));
	return (FLAG_BUILTIN | FLAG_QUIT);
}
