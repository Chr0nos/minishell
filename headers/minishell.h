/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 21:09:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/04 20:15:31 by snicolet         ###   ########.fr       */
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
int				minishell_error_custom(const char *buff, const int ret);
void			minishell_error_notfound(const char *buff);
void			minishell_envload(t_list **lst, char **env);
void			minishell_envshow(t_list *env);
int				minishell_envfree(t_list *env);
char			*minishell_envval(t_list *env, const char *key);

char			**minishell_arguments_parse(const char *cmd,
		const char *bin_path);
void			minishell_arguments_free(char **args);
void			minishell_arguments_show(char **args);

char			**minishell_envmake(t_list *env);
void			minishell_envtabfree(char **env);

#endif
