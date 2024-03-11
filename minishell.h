/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:50:37 by mkimdil           #+#    #+#             */
/*   Updated: 2024/03/11 15:43:50 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_list
{
	int x;
	int y;
	struct s_list *next;
}			t_list;

char	**ft_split(char *s, char c);
char	**ft_help(char *s, char c, int len, char **final);
void	ft_free(char **ptr, int i);
char	*ft_strndup(char *src, int n);
int		countword(char *s, char c);
int 	ft_strncmp(char *s1, char *s2, int len);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);

#endif