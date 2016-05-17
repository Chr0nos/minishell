/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 17:58:08 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/17 18:01:37 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "keycodes.h"

int		minishell_prompt_skip(char *buff, int *pos, int x)
{
	if ((buff[*pos] == 65) || (buff[*pos] == 66) || buff[*pos] == 27 ||
			x == MKEY_LEFT || x == MKEY_RIGHT)
	{
		buff[(*pos)--] = '\0';
		return (1);
	}
	return (0);
}
