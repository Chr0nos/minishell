/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcomplete.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/26 17:21:01 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/26 20:44:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

int				minishell_termcap_completion(unsigned int keycode,
	int *pos, char *buff, t_shell *shell)
{
	char	*complete;
	char	*path;
	char	*subbuff;
	size_t	cl;

	(void)shell;
	if (keycode != 9)
		return (READ_AGAIN);
	if ((path = getcwd(NULL, 4096)))
	{
		buff[*pos] = '\0';
		subbuff = ft_strrchr(buff, ' ');
		if ((subbuff) && (*subbuff == ' '))
			subbuff++;
		if ((!(complete = minishell_complete(subbuff,
		path))) && (ft_mfree(1, path)))
			return (READ_AGAIN);
		if (!(cl = ft_strlen(complete)))
			return (READ_AGAIN);
		write(1, complete, cl);
		ft_memcpy(&buff[*pos], complete, cl + 1);
		*pos += (int)cl;
		ft_mfree(2, path, complete);
	}
	return (READ_AGAIN);
}
