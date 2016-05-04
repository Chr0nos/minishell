/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 21:14:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/04 18:55:31 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>

void	minishell_error_notfound(const char *buff)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	write(2, buff, ft_strsublen(buff, ' '));
	write(2, "\n", 1);
}

int		minishell_error_custom(const char *buff, const int ret)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(buff, 2);
	write(2, "\n", 1);
	return (ret);
}
