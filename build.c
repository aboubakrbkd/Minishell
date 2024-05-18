/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:20:17 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/18 15:52:01 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_arr(t_list **lst, char **res)
{
	int		i;
	t_list	*new_node;
	t_list	*curr;

	new_node = NULL;
	curr = NULL;
	i = 0;
	while (res[i])
	{
		new_node = malloc(sizeof(t_list));
		if (!new_node)
			return ;
		new_node->str = ft_strdup(res[i]);
		new_node->res = malloc(sizeof(char *));
		new_node->res[i] = ft_strdup(res[i]);
		if (!*lst)
			*lst = new_node;
		else
			curr->next = new_node;
		curr = new_node;
		i++;
	}
	new_node->res[i] = NULL;
}

// void build_arr(t_list **lst, char **res)
// {
//     int i;
//     t_list *new_node;
//     t_list *curr;

//     curr = NULL;
//     i = 0;
//     while (res[i])
//     {
//         new_node = malloc(sizeof(t_list));
//         if (!new_node)
//             return;
//         new_node->str = ft_strdup(res[i]);
//         new_node->res = malloc(2 * sizeof(char *));
//         if (!new_node->res)
//         {
//             free(new_node->str);
//             free(new_node);
//             return;
//         }
//         new_node->res[0] = ft_strdup(res[i]);
//         new_node->res[1] = NULL;
//         new_node->next = NULL;
//         if (!*lst)
//             *lst = new_node;
//         else
//             curr->next = new_node;
//         curr = new_node;
//         i++;
//     }
// }