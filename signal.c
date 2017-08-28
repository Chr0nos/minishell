/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 16:21:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/06/02 13:50:11 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <signal.h>

void		minishell_signal(int num)
{
	if (num == SIGINT)
		minishell_termread_reset(NULL, NULL);
}
