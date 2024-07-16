/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 04:01:04 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/16 07:54:23 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_qoutes(t_cmd **lst)
{
	t_cmd	*current;
	char	**argv;
	char	*arg;
	int		len;
	int		i;
	int		j;

	current = *lst;
	while (current != NULL)
	{
		argv = current->argv;
		while (*argv != NULL)
		{
			arg = *argv;
			len = ft_strlen(arg);
			i = 0;
			j = 0;
			while (i < len)
			{
				if (arg[i] != '"' && arg[i] != '\'')
					arg[j++] = arg[i];
				i++;
			}
			arg[j] = '\0';
			argv++;
		}
		current = current->next;
	}
}

void	function_sigint(int sig)
{
	if (sig == SIGINT && g_signal_status == 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ex_st(1, 1);
	}
	else if (sig == SIGINT && g_signal_status == 1)
		write(1, "\n", 1);
}

void	function_sigwuit(int sig)
{
	if (sig == SIGQUIT && g_signal_status ==1)
		write(1, "Quit: 3\n", 8);
}

void	check_signals()
{
	signal(SIGINT, function_sigint);
	signal(SIGQUIT, function_sigwuit);
}

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

int main(int ac, char **av, char **env)
{
	(void)av;
	char		*temp;
	t_cmd		*lst;
	t_list		*list;
	char		*str;
	char		**res;

	g_signal_status = 0;
	lst = malloc(sizeof(t_cmd));
	list = malloc(sizeof(t_list));
	if (ac != 1 || !lst || !list)
		return (1);
	list->envs = env_init(env);
	while (1)
	{
		rl_catch_signals = 0;
		check_signals();
		temp = readline("Minishell-$ ");
		if (!temp)
		{
			printf("exit\n");
			break ;
		}
		add_history(temp);
		if (!ft_strlen(temp))
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
		expand(lst, list);
		remove_qoutes(&lst);
		g_signal_status = 1;
		if (is_heredoc(lst))
			heredoc(lst);
		execution(lst, list);
		g_signal_status = 0;
		free_cmd_lst(lst);
		free(str);
		free(temp);
		free_all(res);
	}
	free_list(list);
}
