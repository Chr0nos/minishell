/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 21:09:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/03 22:50:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include "libft.h"

typedef struct	s_env
{
	char		*name;
	char		*value;
}				t_env;

int				main(int ac, char **av, char **env);
void			minishell_error_notfound(const char *buff);
void			minishell_envload(t_list **lst, char **env);
void			minishell_envshow(t_list *env);
void			minishell_envfree(t_list *env);
char			*minishell_envval(t_list *env, const char *key);

#endif
