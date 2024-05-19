/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:38:59 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/15 16:55:50 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_global	g_global;

int	is_upper(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int	is_lower(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}

int	is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	swap_the_nodes(t_env *tmp1, t_env *tmp2)
{
	char	*temp_name;
	char	*temp_value;
	int		temp_index;

	temp_name = tmp1->name;
	temp_value = tmp1->value;
	temp_index = tmp1->index;
	tmp1->name = tmp2->name;
	tmp1->value = tmp2->value;
	tmp1->index = tmp2->index;
	tmp2->name = temp_name;
	tmp2->value = temp_value;
	tmp2->index = temp_index;
}

void	sort_env(t_env *env)
{
	t_env	*tmp1;
	t_env	*tmp2;
	char	*temp_name;
	char	*temp_value;
	int		temp_index;

	tmp1 = env;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		while (tmp2)
		{
			if (strcmp(tmp1->name, tmp2->name) > 0)
				swap_the_nodes(tmp1, tmp2);
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

void	index_env(t_env *env)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = env;
	while (tmp)
	{
		tmp->index = 0;
		tmp = tmp->next;
	}
	tmp = env;
	while (tmp)
	{
		tmp2 = env;
		while (tmp2)
		{
			if (strcmp(tmp->name, tmp2->name) > 0)
				tmp->index++;
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	sort_env(env);
}

void	print_export(t_env *env)
{
	int	size;
	int	i;

	i = 0;
	size = env_size(env);
	index_env(env);
	while (i < size)
	{
		if (env && env->index != size)
		{
			printf("declare -x %s", env->name);
			if (env->value)
				printf("=\"%s\"\n", env->value);
			else
				printf("\n");
			i++;
		}
		env = env->next;
	}
}

char	*get_name(char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '=') || (str[i] == '+' && str[i + 1] == '='))
			break ;
		i++;
	}
	result = malloc(i + 1);
	if (!result)
		return (NULL);
	while (j < i)
	{
		result[j] = str[j];
		j++;
	}
	result[i] = '\0';
	return (result);
}

char	*get_value(char *str)
{
	char	*find;

	find = ft_strchr(str, '=');
	if (!find)
		return (NULL);
	return (find + 1);
}


// export z x-= y=oooo 

int	update_the_value(char *name, char *value)
{
	t_env	*env;
	char	*temp;

	env = g_global.envs;
	if (!value)
		return (0);
	while (env)
	{
		if (!strcmp(env->name, name))
		{
			temp = env->value;
			env->value = ft_strjoin(temp, value);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

int	add_the_value(char *name, char *value)
{
	t_env	*env;

	env = g_global.envs;
	if (!value)
		return (1);
	while (env)
	{
		if (!strcmp(env->name, name))
		{
			env->value = ft_strdup(value);
			return (0);
		}
		env = env->next;
	}
	return (1);
}
void	add_env(t_env **env, char *name, char *value)
{
	t_env	*new_node;
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!strcmp(tmp->name, name))
		{
			if (value != NULL)
			{
				free(tmp->value);
				tmp->value = ft_strdup(value);
			}
			return ;
		}
		tmp = tmp->next;
	}
	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->name = ft_strdup(name);
	if (!value)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->index = 0;
	new_node->next = NULL;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	tmp = *env;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_node;
}

int	is_valid_to_export(char *str)
{
	int	i;

	i = 0;
	if (!is_lower(*str) && !is_upper(*str) && *str != '_')
		return (-1);
	while (str[i])
	{
		if (str[i] == '=')
			return (i + 1);
		if (str[i] == '+' && str[i + 1] == '=')
			return (i + 2);
		if (!(is_upper(str[i]) || is_lower(str[i])
				|| is_number(str[i]) || str[i] == '_'))
			return (-1);
		i++;
	}
	return (0);
}

void	checking_and_add(int is_valid, char *argv)
{
	char	*name;
	char	*value;
	int		is_modified;

	name = get_name(argv);
	value = get_value(argv);
	is_valid = ft_strlen(name);
	if (!(*argv + is_valid))
		is_modified = 1;
	else if (*(argv + is_valid) == '+')
		is_modified = update_the_value(name, value);
	else
		is_modified = add_the_value(name, value);
	if (is_modified == 1)
		add_env(&g_global.envs, name, value);
}

void	export(char **argv)
{
	int		is_valid;
	t_env	*env;

	if (!*(argv + 1))
	{
		env = g_global.envs;
		print_export(env);
		return ;
	}
	argv++;
	while (*argv)
	{
		is_valid = is_valid_to_export(*argv);
		if (is_valid == -1)
			printf("minishell: export: `%s': not a valid identifier\n", *argv);
		else
			checking_and_add(is_valid, *argv);
		argv++;
	}
}

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
		if (!strcmp(*argv, "export"))
			export(argv);
		else if (!strcmp(*argv, "echo"))
			echo(argv);
		else if (!strcmp(*argv, "cd"))
			cd(argv);
		else if (!strcmp(*argv, "exit"))
			exit_function(argv);
		else if (!strcmp(*argv, "pwd"))
			pwd(envp);
		else if (!strcmp(*argv, "unset"))
			unset(argv, &g_global.envs);
		else if (!strcmp(*argv, "env"))
			env(g_global.envs);
		// else
		// 	printf("minishell: %s: command not found\n", *argv);
		else
			execution(cmd, envp);

	}
}
