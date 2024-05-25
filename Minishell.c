/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 04:01:04 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/25 22:28:33 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_qoutes(t_cmd **lst)
{
	t_cmd	*current;
	char	**argv;
	char	*arg;
	int		len;
	int		i;
	int		j;

	current = *lst;
	while (current != NULL)
	{
		argv = current->argv;
		while (*argv != NULL)
		{
			arg = *argv;
			len = ft_strlen(arg);
			i = 0;
			j = 0;
			while (i < len)
			{
				if (arg[i] != '"' && arg[i] != '\'')
					arg[j++] = arg[i];
				i++;
			}
			arg[j] = '\0';
			argv++;
		}
		current = current->next;
	}
}

void	secure_path(t_list *list)
{
	char	*pwd;
	int		i;

	i = 0;
	pwd = getcwd(NULL, 0);
	while (i <= 4)
	{
		if (i == 1)
			list->envs=ft_lstnew("PATH", "/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin");
		else if (i == 2)
			list->envs->next=ft_lstnew("PWD", pwd);
		else if (i == 3)
			list->envs->next->next=ft_lstnew("SHLVL", "1");
		else if (i == 4)
			list->envs->next->next->next=ft_lstnew("_", "usr/bin/env");
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	(void)av;
	char	*temp;
	t_cmd	*lst;
	t_list	*list;
	char	*str;
	char	**res;

	lst = malloc(sizeof(t_cmd));
	list = malloc(sizeof(t_list));
	list->envs = env_init(env);
	if (!list->envs)
		secure_path(list);
	if (ac != 1 || !lst || !list)
		return (1);
	while (1)
	{
		temp = readline("Minishell-$ ");
		add_history(temp);
		if (syn_error(temp))
			continue ;
		str = add_space(temp);
		if (!str)
			continue ;
		change_to_garb(str);
		if (handle_single_double(str))
			continue ;
		res = ft_split(str, '|');
		if (!res)
			continue ;
		lst = build_arr(res);
		if (!lst)
			continue ;
		back_to_ascii(lst);
		remove_qoutes(&lst);
		expand(lst, list);
		execution(lst, list);
	}
}
