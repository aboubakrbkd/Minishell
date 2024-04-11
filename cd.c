/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:54:47 by aboukdid          #+#    #+#             */
/*   Updated: 2024/04/11 09:54:39 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

/*
	i need to build 2 functions;
	1- function to give the env i want like i f i want home it will print me home path;
	2- FUNCTION TO UPDATE ENV
	3-i need a fcuntion to update the pwd whenever i make cd 
	
*/

char	*my_getenv(char *name, char **envp)
{
	t_env *env;
	
	env = env_init(envp);
	while (env)
	{
		if (!ft_strncmp(env->name, name, ft_strlen(name)))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int cd(char **argv, char **envp)
{
	int i = 1;
	char *home;
	while(argv[i])
		i++;
	if (i == 1)
	{
		home = my_getenv("HOME", envp);
		if (chdir(home) == -1)
			printf("cd: %s: No such file or directory\n", home);
		
	}
}

int main(int argc, char **argv, char **envp)
{
	// printf("%s\n", my_getenv("HOME", envp));
	cd(argv, envp);
}