/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:45:08 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/19 16:18:42 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*result;
	t_list	*list;
	t_cmd	*cmd;
	t_cmd	*head;
	char	**commands;
	t_cmd	*new_cmd;

	list = malloc(sizeof(t_list));
	if (!list)
		return (1);
	if(envp)
		list->envs = env_init(envp);
	else
		list->envs = NULL;
	while (1)
	{
		result = readline("minishell$ ");
		if (!result)
			break;
		add_history(result);
		commands = ft_split(result, '|');
		if (!commands)
			break;
		head = NULL;
		cmd = NULL;
	for (int i = 0; commands[i]; i++)
		{
			char **args = ft_split(commands[i], ' ');
			if (!args)
				break;
			new_cmd = malloc(sizeof(t_cmd));
			if (!new_cmd)
				break;
			new_cmd->argv = args;
			new_cmd->infile = 0;
			new_cmd->outfile = 1;
			new_cmd->next = NULL;
			if (!head)
				head = new_cmd;
			else
				cmd->next = new_cmd;
			cmd = new_cmd;
		}
		if (head)
			execution(head, list);
		free(commands);
		free(result);
	}
	return (0);
}
