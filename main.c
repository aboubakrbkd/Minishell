/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:56:24 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/18 14:30:07 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_minishell *mini;
	t_env	*env_s;

	mini->cmd = malloc(10000000);
	mini->cmd[0] = "cd";
	mini->cmd[1] = NULL;
}
	// while (1)
	// {
	// 	// printf("\033[0;31m");
	// 	// result = readline("mmouad: ");
	// 	// printf("\033[0m");
	// 	// if (!result)
	// 	// 	break ;
	// 	// if (ft_strncmp(result, "pwd", ft_strlen(result) + 3) == 0)
	// 	// 	pwd();
	// 	// if (ft_strncmp(result, "env", ft_strlen(result) + 3) == 0)
	// 	// 	env(env_s, envp);
		
	// 	add_history(result);
	// }