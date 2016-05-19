/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:58:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/19 19:58:19 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keycodes.h"

int		minishell_prompt_skip(char *buff, int *pos, int x)
{
	char	c;

	(void)x;
	c = buff[*pos];
	if (c == 27)
	{
		buff[(*pos)--] = '\0';
		return (1);
	}
	return (0);
}
