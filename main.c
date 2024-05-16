/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:45:08 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/16 13:32:46 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_global;

int	main(int argc, char **argv, char **envp)
{
	char	*result;
	t_cmd	*cmd;

	(void)argc;
	(void)argv;
	(void)envp;
	g_global.envs = env_init(envp);
	while (1)
	{
		result = readline("minishell$ ");
		if (!result)
			break ;
		add_history(result);
		argv = ft_split(result, ' ');
		if (!argv)
			break ;
		if (!ft_strcmp(*argv, "export"))
			export(argv);
		else if (!ft_strcmp(*argv, "echo"))
			echo(argv);
		else if (!ft_strcmp(*argv, "cd"))
			cd(argv);
		else if (!ft_strcmp(*argv, "exit"))
			exit_function(argv);
		else if (!ft_strcmp(*argv, "pwd"))
			pwd(envp);
		else if (!ft_strcmp(*argv, "unset"))
			unset(argv, &g_global.envs);
		else if (!ft_strcmp(*argv, "env"))
			env(g_global.envs);
		else
			printf("minishell: %s: command not found\n", *argv);
	}
}
