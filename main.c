/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:45:08 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/16 19:19:39 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*result;
	t_list	*list;
	t_cmd	*cmd;
	t_cmd	*head;

	list = malloc(sizeof(t_list));
	if (!list)
		return (1);
	list->envs = env_init(envp);
	while (1)
	{
		result = readline("minishell$ ");
		if (!result)
			break ;
		add_history(result);
		char **commands = ft_split(result, '|');
		if (!commands)
			break ;
		head = NULL;
		cmd = NULL;
		for (int i = 0; commands[i]; i++)
		{
			char **args = ft_split(commands[i], ' ');
			if (!args)
				break ;
			t_cmd *new_cmd = malloc(sizeof(t_cmd));
			if (!new_cmd)
				break ;
			new_cmd->argv = args;
			new_cmd->next = NULL;
			if (!head)
				head = new_cmd;
			else
				cmd->next = new_cmd;
			cmd = new_cmd;
		}
		if (head)
			execution(head, list);
	}
	return (0);
}


