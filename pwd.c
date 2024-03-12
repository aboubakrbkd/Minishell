/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:39:12 by aboukdid          #+#    #+#             */
/*   Updated: 2024/03/12 13:55:35 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*pwdir;

	pwdir = getenv("PWD");
	if (pwdir == NULL)
	{
		pwdir = getcwd(NULL, 0);
		if (!pwdir)
		{
			perror("eroor");
			exit(1);
		}
		else
			printf("%s\n", pwdir);
	}
	else
		printf("%s\n", pwdir);
}
