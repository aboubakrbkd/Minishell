/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:56:24 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/14 15:58:04 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_s;
	char	*result;

	while (1)
	{
		printf("\033[0;31m");
		result = readline("mouad: ");
		printf("\033[0m");
		if (!result)
			break ;
		if (ft_strncmp(result, "pwd", 3) == 0)
			pwd();
		if (ft_strncmp(result, "env", 3) == 0)
			env(env_s, envp);
		add_history("mouad: ");
	}
}
