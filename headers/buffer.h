/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 20:42:55 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/12 14:08:04 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_H
# define BUFFER_H
# include <string.h>

typedef struct	s_buffer
{
	char		*data;
	size_t		size;
}				t_buffer;

t_buffer		*minishell_buffer_make(size_t size);
void			minishell_buffer_free(t_buffer *buff);
t_buffer		*minishell_buffer_resize(t_buffer **buffer, size_t newsize);

#endif
