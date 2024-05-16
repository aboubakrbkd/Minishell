/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:54:47 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/15 20:23:23 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

void	home_function(char *home)
{
	home = my_getenv("HOME");
	if (!home)
		printf("cd: HOME not set\n");
	if (chdir(home) == -1)
		printf("cd: %s: No such file or directory\n", home);
	update_pwd(my_getenv("HOME"));
}

void	old_pwd_function(char *home)
{
	if (chdir(my_getenv("OLDPWD")) == -1)
		printf("cd: %s: No such file or directory\n",
			my_getenv("OLDPWD"));
	update_pwd(my_getenv("OLDPWD"));
	printf("%s\n", my_getenv("PWD"));
}

void	error_function(char *home)
{
	home = my_getenv("HOME");
	if (!home)
		printf("cd: HOME not set\n");
	if (chdir(home) == -1)
		printf("cd: %s: No such file or directory\n", home);
	printf("cd: error retrieving current directory: ");
	printf("getcwd: cannot access parent directories: ");
	printf ("No such file or directory\n");
	update_pwd(my_getenv("HOME"));
}

int	cd(char **argv)
{
	int		i;
	char	*home;

	i = 1;
	while (argv[i])
		i++;
	if (i == 1)
		return (home_function(home), 0);
	else
	{
		if (!ft_strcmp(argv[1], "~"))
			return (home_function(home), 0);
		else if (!ft_strcmp(argv[1], "-"))
			return (old_pwd_function(home), 0);
		else if (chdir(argv[1]) == -1)
		{
			if (!ft_strcmp(argv[1], ".."))
				return (error_function(home), 0);
			printf("cd: %s: No such file or directory\n", argv[1]);
			return (1);
		}
	}
	update_pwd(argv[1]);
	return (0);
}
