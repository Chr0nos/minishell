/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 21:09:49 by snicolet          #+#    #+#             */
/*   Updated: 2016/05/16 13:59:07 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "libft.h"
# include "limits.h"
# include <termios.h>
# define MINISHELL_PATH1 "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:"
# define MINISHELL_PATH2 "/opt/X11/bin:/usr/local/go/bin:/usr/local/munki:"
# define MINISHELL_PATH3 "/Library/TeX/texbin"
# define MINISHELL_PATH_DEFAULT MINISHELL_PATH1 MINISHELL_PATH2 MINISHELL_PATH3
# define BUFF_SIZE _POSIX_ARG_MAX
# define DEFAULT_TERM "xterm-256color"
# define SEPARATORS " \t"
# define DQUOTE (char)34
# define STDIN STDIN_FILENO
# define CFG_SETSHLVL 1
# define ENABLE_TERMCAPS 0
# define FLAG_NOTFOUND 1 << 26
# define FLAG_UNKNOW 1 << 27
# define FLAG_ERROR 1 << 28
# define FLAG_BUILTIN 1 << 29
# define FLAG_QUIT 1 << 30
# define MASK_RET 255

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

const char		*minishell_strchr(const char *str, const char *separators);
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
int				minishell_envcmd(int ac, char **av, t_list **env);
int				minishell_unsetenv(int ac, char **av, t_list **env);
int				minishell_builtin(const char *cmd, t_list **evironement);
void			minishell_cd_real(t_list **env, const char *dir);
int				minishell_cd(int ac, char **av, t_list **env);
int				minishell_cd_home(t_list **env);
int				minishell_spliter(const char *cmd, t_list **env,
		int (*f)(int, char **, t_list **));
int				minishell_setenv(int ac, char **av, t_list **env);
void			minishell_setenv_val(t_list **env, t_env *e);
void			minishell_addenv(t_list **env, const char *name, char *value);
void			minishell_editenv(t_env *e, char *val);
int				minishell_esort(t_list *a, t_list *b);
t_env			*minishell_getenv_byname(t_list *env, const char *key);
void			*minishell_envdup(void *content);
int				minishell_purgeenv(t_list **env);
void			minishell_setenvval(const char *name, char *value,
		t_list **env);
int				minishell_help(int ac, char **av, t_list **env);
int				minishell_prompt(char *buff, t_list *env);
int				minishell_quit(t_list *env, struct termios *term, int result);
int				minishell_init(t_list **env, struct termios term);
void			minishell_set_shell_level(t_list **env);
void			minishell_termcaps_clear(void);
void			minishell_termcaps_key(int key, t_list *env);
int				minishell_showprompt(void);
void			minishell_signal(int num);
char			**minishell_split(const char *cmd);
const char		*minishell_getterm(t_list *env);
int				minishell_export(int ac, char **av, t_list **env);
void			minishell_envcmdsetval(t_list **subenv, char *str);
int				minishell_exit(int ac, char **av, t_list **env);

#endif
