/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 20:44:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/11 20:53:06 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include <stdlib.h>

t_buffer	*minishell_buffer_make(size_t size)
{
	t_buffer	*buff;

	if (!(buff = malloc(sizeof(t_buffer))))
		return (NULL);
	if (!(buff->data = malloc((sizeof(char) * size))))
	{
		free(buff);
		return (NULL);
	}
	buff->size = size;
	return (buff);
}

void		minishell_buffer_free(t_buffer *buff)
{
	if (!buff)
		return ;
	else if (buff->data)
		free(buff->data);
	free(buff);
}
