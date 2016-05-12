/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 20:44:30 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/12 14:11:16 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"
#include "libft.h"
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

t_buffer	*minishell_buffer_resize(t_buffer **buffer, size_t newsize)
{
	size_t		copysize;
	t_buffer	*newbuff;

	copysize = (newsize > (*buffer)->size) ? (*buffer)->size : newsize;
	if ((newbuff = minishell_buffer_make(newsize)))
	{
		ft_memcpy(newbuff->data, (*buffer)->data, copysize);
		minishell_buffer_free(*buffer);
	}
	*buffer = newbuff;
	return (newbuff);
}
