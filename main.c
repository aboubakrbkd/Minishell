/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:56:24 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/12 13:55:13 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char **argv, char **envp)
{
	char *result;
	while (1)
	{
		result = readline("mouad: ");
		if (!result)
			break ;
		if (ft_strncmp(result, "pwd", 3) == 0)
			pwd();
		add_history("mouad: ");
	}
}