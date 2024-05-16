/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:39:12 by aboukdid          #+#    #+#             */
/*   Updated: 2024/05/16 17:26:52 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(char **args, t_list *list)
{
	char	*pwdir;

	pwdir = my_getenv("PWD", list);
	printf("%s\n", pwdir);
}
