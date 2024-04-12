/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 14:54:47 by aboukdid          #+#    #+#             */
/*   Updated: 2024/04/12 06:37:52 by aboukdid         ###   ########.fr       */
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

void	update_env(char *name, char *value, char **envp)
{
	t_env *tmp = env_init(envp);
	if (!name || !value)
		return ;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, name, ft_strlen(name)))
		{
			tmp->value = value;
			break;
		}
		tmp = tmp->next;
	}
}

void	update_pwd(char *path, char **envp)
{
	update_env("OLDPWD", my_getenv("PWD", envp), envp);
	char *home = getcwd(NULL, 0);
	update_env("PWD", home, envp);
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
		if (!home)
			printf("cd: HOME not set\n");
		if (chdir(home) == -1)
			printf("cd: %s: No such file or directory\n", home);
		update_pwd(my_getenv("HOME", envp), envp);
		return (0);
	}
	else
	{
		if (chdir(argv[1]) == -1)
		{
			printf("cd: %s: No such file or directory\n", argv[1]);
			return (1);
		}
	}
	update_pwd(argv[1], envp);
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	printf("%s\n", getcwd(NULL, 0));
// 	cd(argv, envp);
// 	printf("%s\n", getcwd(NULL, 0));
// }