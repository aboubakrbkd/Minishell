/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 04:01:04 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/25 02:42:18 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status;

void	print_args(t_cmd *lst)
{
	int	x;
	int	i;

	x = 0;
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

int	main(int ac, char **av, char **env)
{
	char			*temp;
	t_cmd			*lst;
	t_list			*list;
	char			*str;
	char			**res;
	// struct termios	copy;

	(void)av;
	g_signal_status = 0;
	lst = malloc(sizeof(t_cmd));
	list = malloc(sizeof(t_list));
	list->envs = env_init(env);
	if (ac != 1 || !lst || !list || !list->envs)
        return (free(lst), free(list), 1);
	// handling_shlvl(list);
	while (1)
	{
		rl_catch_signals = 0;
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
			free(temp);
			continue ;
		}
		str = add_space(temp);
		if (!str)
		{
			free(temp);
			continue ;
		}
		if (syn_error(str))
		{
			free(temp), free(str);
			continue ;
		}
		change_to_garb(str);
		if (handle_single_double(str))
		{
			free(temp), free(str);
			continue ;
		}
		res = ft_split(str, '|');
		if (!res)
		{
			free(temp), free(str);
			continue ;
		}
		lst = build_arr(res);
		if (!lst)
		{
			free(temp), free(str);
			continue ;
		}
		back_to_ascii(lst);
		if (is_heredoc(lst))
			heredoc(lst, list);
		expand(lst, list);
		// remove_qoutes(&lst);
		// g_signal_status = 1;
		// tcgetattr(0, &copy);
		// execution(lst, list);
		// tcsetattr(0, 0, &copy);
		// g_signal_status = 0;
		free(temp), free(str);
	}
	free_envp(&list->envs), free(list), free_cmd_lst(&lst);
	return (0);
}
