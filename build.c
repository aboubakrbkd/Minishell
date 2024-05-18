/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:20:17 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/18 18:15:36 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_num_of_command(char **res)
{
	int	i;

	i = 0;
	while (res[i])
		i++;
	return (i);
}

// void	build_arr(t_list **lst, char **res)
// {
// 	int		i;
// 	t_list	*new_node;
// 	t_list	*curr;

// 	new_node = NULL;
// 	curr = new_node;
// 	i = 0;
// 	while (res[i])
// 	{
// 		new_node = malloc(sizeof(t_list));
// 		new_node->res = malloc(sizeof(char *) + 1);
// 		if (!new_node)
// 			return ;
// 		new_node->str = ft_strdup(res[i]);
// 		new_node->res[i] = ft_strdup(res[i]);
// 		new_node = new_node->next;
// 		i++;
// 	}
	
// 	*lst = curr;
// }

void	build_arr(t_list **lst, char **res)
{
	int		i;
	int		count;
	t_list	*new_node;
	t_list	*curr;

	new_node = NULL;
	curr = NULL;
	i = 0;
	count = count_num_of_command(res);
	while (res[i])
	{
		new_node = malloc(sizeof(t_list));
		new_node->res = malloc(sizeof(char *) + 1);
		if (!new_node)
			return ;
		// printf("inside: -> %s\n", res[i]);
		new_node->str = ft_strdup(res[i]);
		new_node->res[i] = ft_strdup(res[i]);
		if (!*lst)
			*lst = new_node;
		else
			curr->next = new_node;
		curr = new_node;
		printf("curr-> %s\n", curr->str);
		i++;
	}
	new_node->res[i] = NULL;
}
