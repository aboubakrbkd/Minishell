/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:34:56 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/20 16:34:41 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	(void) ac;
	(void) av;
	char	*temp;

	if (ac != 1)
		return (1);
	while (1)
	{
		temp = readline("Minishell-$ ");
		if (!temp)
			break ;
		add_history(temp);
		if (parsing(temp, env))
			continue ;
	}
}
