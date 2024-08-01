/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 04:01:04 by mkimdil           #+#    #+#             */
/*   Updated: 2024/08/01 04:25:22 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status;

void	print_args(t_cmd *lst)
{
	static int	x;
	int	i;

	while (lst)
	{
		printf("lst %d :\n", x);
		i = 0;
		while (lst->argv[i])
		{
			printf("lst->argv[%d]: %s\n", i, lst->argv[i]);
			i++;
		}
		lst = lst->next;
		x++;
	}
	printf("\n");
}

void secure_path(t_list *list)
{
	char	*path;
	char	*pwd;
	t_env	*new_env;

	path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	pwd = getcwd(NULL, 0);
	new_env = NULL;
	if (!pwd)
		return;
	new_env = ft_lstnew("PWD", pwd);
	if(new_env)
		ft_lstadd_back(&list->envs, new_env);
	new_env = ft_lstnew("SHLVL", "1");
	if(new_env)
		ft_lstadd_back(&list->envs, new_env);
	new_env = ft_lstnew("_", "/usr/bin/env");
	if(new_env)
		ft_lstadd_back(&list->envs, new_env);
	new_env = ft_lstnew("PATH", path);
	if(new_env)
		ft_lstadd_back(&list->envs, new_env);
	free(pwd);
}

void	free_envs(t_env *envs)
{
	t_env	*next;

	while (envs)
	{
		next = envs->next;
		free(envs->name);
		free(envs->value);
		free(envs);
		envs = next;
	}
	envs = NULL;
}

// int	parsing()
// {
	
// }

int	main(int ac, char **av, char **env)
{
	char			*temp;
	t_cmd			*lst;
	t_list			*list;
	char			*str;
	char			**res;
	struct termios	copy;

	if (ac != 1)
		return (1);
	(1) && ((void)av, g_signal_status = 0, list = malloc(sizeof(t_list)), 0);
	list->envs = env_init(env);
	if (!list->envs)
		secure_path(list);
	while (1)
	{
		(1) && (rl_catch_signals = 0, check_signals(), 0);
		temp = readline("Minishell-$ ");
		if (!temp || !isatty(0))
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		add_history(temp);
		if (!ft_strlen(temp) || is_blank(temp))
		{
			free(temp);
			continue ;
		}
		str = add_space(temp);
		if (!str)
			continue ;
		if (syn_error(str))
		{
			free(str);
			continue ;
		}
		change_to_garb(str);
		if (handle_single_double(str))
		{
			free(str);
			continue ;
		}
		res = ft_split(str, '|');
		if (!res)
			continue ; 
		lst = build_arr(res);
		if (!lst)
		{
			free(str);
			continue ;
		}
		back_to_ascii(lst);
		if (is_heredoc(lst))
			heredoc(lst, list);
		expand(lst, list);
		remove_qoutes(&lst);
		g_signal_status = 1;
		tcgetattr(0, &copy);
		execution(lst, list);
		tcsetattr(0, 0, &copy);
		g_signal_status = 0;
		free(str);
		free_all(res);
		free_cmd_lst(&lst);
	}
	free_envs(list->envs);
	free(list);
	return (0);
}
