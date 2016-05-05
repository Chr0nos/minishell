/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 21:14:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/05 17:19:00 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static const char	*minishell_error_str(int errorn)
{
	const char	*str;

	if (errorn == ERR_NOTFOUND)
		str = "command not found";
	else if (errorn == ERR_PERMS)
		str = "permission denied";
	else if (errorn == ERR_NOPATH)
		str = "no PATH environement variable found";
	else if (errorn == ERR_EXEC)
		str = "child process has returned an error";
	else if (errorn == ERR_ENVPARSE_UNKNOW)
		str = "env: unknow argument";
	else
		str = "unknow error";
	return (str);
}

int					minishell_error(int errorn, char *suffix, int delsuffix)
{
	const char	*str = minishell_error_str(errorn);

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (suffix)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(suffix, 2);
	}
	write(2, "\n", 1);
	if (delsuffix)
		free(suffix);
	return (errorn);
}
