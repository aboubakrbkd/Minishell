/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 04:01:04 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/20 10:43:00 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status;

// void	print_args(t_cmd *lst)
// {
// 	int	x = 0;

// 	while (lst)
// 	{
// 		printf("lst %d :\n", x);
// 		int	i = 0;
// 		while (lst->argv[i])
// 		{
// 			printf("lst->argv[%d]: %s\n", i, lst->argv[i]);
// 			i++;
// 		}
// 		lst = lst->next;
// 		x++;
// 	}
// 	printf("\n");
// }

void	free_cmd_lst(t_cmd *lst)
{
	t_cmd	*current;
	t_cmd	*next;

	current = lst;
	while (current)
	{
		next = current->next;
		free(current->cmd);
		free_all(current->argv);
		free(current);
		current = next;
	}
}

void	free_list(t_list *list)
{
	t_env	*current;
	t_env	*next;

	current = list->envs;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
	free(list);
}

void	handling_shlvl(t_list *list)
{
	char	*shl_lvl;

	shl_lvl = my_getenv("SHLVL", list);
	if (!shl_lvl)
		update_env("SHLVL", "1", list);
	else if (ft_atoi(shl_lvl) > 999)
	{
		printf("Minishell: warning: shell level ");
		printf("(%d) too high, resetting to 1\n", ft_atoi(shl_lvl));
		update_env("SHLVL", "1", list);
	}
	else if (ft_atoi(shl_lvl) < 0)
		update_env("SHLVL", "0", list);
	else if (ft_atoi(shl_lvl) == 999)
		update_env("SHLVL", "", list);
	else
		add_the_value("SHLVL", ft_itoa(ft_atoi(shl_lvl) + 1), list);
}

int	main(int ac, char **av, char **env)
{
	char			*temp;
	t_cmd			*lst;
	t_list			*list;
	char			*str;
	char			**res;
	struct termios	copy;

	(void)av;
	g_signal_status = 0;
	lst = NULL;
	list = malloc(sizeof(t_list));
	if (ac != 1 || !list)
		return (1);
	list->envs = env_init(env);
	rl_catch_signals = 0;
	handling_shlvl(list);
	while (1)
	{
		check_signals();
		temp = readline("Minishell-$ ");
		if (!temp || !isatty(0))
		{
			printf("exit\n");
			break ;
		}
		add_history(temp);
		if (!ft_strlen(temp) || is_blank(temp))
		{
			ex_st(0, 1);
			free(temp);
			continue ;
		}
		if (syn_error(temp))
		{
			ex_st(258, 1);
			free(temp);
			continue ;
		}
		str = add_space(temp);
		if (!str)
			continue ;
		change_to_garb(str);
		if (handle_single_double(str))
			continue ;
		res = ft_split(str, '|');
		if (!res)
			continue ;
		lst = build_arr(res);
		if (!lst)
			continue ;
		back_to_ascii(lst);
		if (is_heredoc(lst))
			heredoc(lst);
		expand(lst, list);
		remove_qoutes(&lst);
		g_signal_status = 1;
		handling_my_argv(lst);
		tcgetattr(0, &copy);
		execution(lst, list);
		tcsetattr(0, 0, &copy);
		g_signal_status = 0;
		free_cmd_lst(lst);
		free(str);
		free(temp);
		free_all(res);
	}
	free_list(list);
	exit(ex_st(0, 0));
}
