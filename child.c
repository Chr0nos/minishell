/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <snicolet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 21:46:07 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/19 21:54:36 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void	minishell_child(const char *app, char **args, char **env)
{
	signal(SIGINT, SIG_DFL);
	if (execve(app, args, env) == -1)
	{
		minishell_error(ERR_EXEC, NULL, 0);
		exit(0);
	}
}
