/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/18 16:20:50 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/18 16:26:25 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

void	minishell_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 4096);
	if (cwd)
	{
		ft_putendl(cwd);
		free(cwd);
	}
}
