/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:34:56 by mkimdil           #+#    #+#             */
/*   Updated: 2024/03/12 12:01:32 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*temp;

	if (ac < 1)
		return (0);
	while (1)
	{
		write (0, "~$ ", 3);
		temp = get_next_line(0);
		if (!temp)
			break ;
	}
}