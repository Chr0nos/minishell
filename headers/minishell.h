/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 21:09:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/07 02:11:29 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# define MINISHELL_PATH1 "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:"
# define MINISHELL_PATH2 "/opt/X11/bin:/usr/local/go/bin:/usr/local/munki:"
# define MINISHELL_PATH3 "/Library/TeX/texbin"
# define MINISHELL_PATH_DEFAULT MINISHELL_PATH1 MINISHELL_PATH2 MINISHELL_PATH3

typedef struct	s_env
{
	char		*name;
	char		*value;
}				t_env;

enum			e_errors
{
	ERR_NOTFOUND = -1,
	ERR_PERMS = -2,
	ERR_NOPATH = -3,
	ERR_EXEC = -4,
	ERR_EXIT = -5,
	ERR_ENVPARSE_UNKNOW = -6
};

const char		*minishell_strchr(const char *str, const char c);
int				minishell_runcmd(const char *cmd, t_list **environement);
int				main(int ac, char **av, char **env);
int				minishell_error(int errorn, char *suffix, int delsuffix);
void			minishell_envload(t_list **lst, char **env);
int				minishell_envshow(t_list *env);
int				minishell_envfree(t_list *env);
char			*minishell_envval(t_list *env, const char *key);

char			**minishell_arguments_parse(const char *cmd,
		const char *bin_path);
void			minishell_arguments_free(char **args);
void			minishell_arguments_show(char **args);
char			*minishell_getapp_path(const char *app, const char *pathlist);
char			**minishell_envmake(t_list *env);
void			minishell_envtabfree(char **env);
int				minishell_envcmd(const char *cmd, t_list **env);

int				minishell_builtin(const char *cmd, t_list **evironement);
void			minishell_cd_real(t_list **env, const char *dir);
int				minishell_cd(int ac, char **av, t_list **env);
int				minishell_cd_home(t_list **env);
int				minishell_spliter(const char *cmd, t_list **env,
		int (*f)(int, char **, t_list **, const char *));
int				minishell_setenv(int ac, char **av, t_list **env);
void			minishell_setenv_val(t_list **env, t_env *e);
void			minishell_addenv(t_list **env, const char *name, char *value);
void			minishell_editenv(t_env *e, char *val);
int				minishell_esort(t_list *a, t_list *b);
t_env			*minishell_getenv_byname(t_list *env, const char *key);

#endif
