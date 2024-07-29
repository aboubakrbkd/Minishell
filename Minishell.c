/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 04:01:04 by mkimdil           #+#    #+#             */
/*   Updated: 2024/07/29 21:46:44 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status;

void	print_args(t_cmd *lst)
{
	int	x;
	int	i;

	x = 0;
	while (lst)
	{
		printf("lst %d :\n", x);
		i = 0;
		while (lst->argv[i])
		{
			printf("lst->argv[%d]: %s\n", i, lst->argv[i]);
			i++;
		}
		lst = lst->next;
		x++;
	}
	printf("\n");
}

void secure_path(t_list *list)
{
	char	*path;
	char	*pwd;
	t_env	*new_env;

	path = "/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	pwd = getcwd(NULL, 0);
	new_env = NULL;
	if (!pwd)
		return;
	new_env = ft_lstnew("PWD", pwd);
	if(new_env)
		ft_lstadd_back(&list->envs, new_env);
	new_env = ft_lstnew("SHLVL", "1");
	if(new_env)
		ft_lstadd_back(&list->envs, new_env);
	new_env = ft_lstnew("_", "/usr/bin/env");
	if(new_env)
		ft_lstadd_back(&list->envs, new_env);
	new_env = ft_lstnew("PATH", path);
	if(new_env)
		ft_lstadd_back(&list->envs, new_env);
	free(pwd);
}
