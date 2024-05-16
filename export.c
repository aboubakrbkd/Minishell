/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:38:59 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/15 16:46:59 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

t_global	g_global;

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
