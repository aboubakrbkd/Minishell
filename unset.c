/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 10:23:59 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/06 16:13:20 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <ctype.h>

/*i have a conflict type in function env in env.c
	 and unset.c i need to untilizate in merge*/
void	free_env(char *name, t_env **envps)
{
	t_env	*prev;
	t_env	*tmp;

	tmp = *envps;
	prev = NULL;
	while (tmp)
	{
		if (!strcmp(tmp->name, name))
		{
			if (!prev)
				*envps = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	env(t_env *envps)
{
	t_env	*tmp;

	tmp = envps;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

int	check_is_unsetablle(char *name, t_env **envps)
{
	int	i;

	i = 0;
	while (name[i])
	{
		if (!isalnum(name[i]) && name[i] != '_')
		{
			printf("minishell: unset: `%s': not a valid identifier\n", name);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset(char **argv, t_env **envps)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (check_is_unsetablle(argv[i], envps))
			return (0);
		free_env(argv[i], envps);
		i++;
	}
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_env *envps = env_init(envp);
// 	env(envps);
// 	printf("-------------\n");
// 	unset(argv, &envps);
// 	env(envps);
// 	return 0;
// }