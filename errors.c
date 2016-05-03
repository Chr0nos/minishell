/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 21:14:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/03 21:17:25 by snicolet         ###   ########.fr       */
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
