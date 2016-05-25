#include "minishell.h"

static void		minishell_purgeenv_cb(void *content, size_t size)
{
	t_env	*e;

	e = (t_env*)content;
	(void)size;
	ft_mfree(3, e->name, e->value, e);
}

int				minishell_purgeenv(int ac, char **av, t_list **env)
{
	(void)ac;
	(void)av;
	if (env)
		ft_lstdel(env, minishell_purgeenv_cb);
	return (FLAG_BUILTIN);
}
