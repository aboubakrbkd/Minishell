/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:50:37 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/15 15:58:55 by mkimdil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}				t_env;

typedef struct s_minishell
{
	char	**cmd;
	t_env	*env;
}				t_minishell;

// #define malloc(x) NULL 

typedef struct s_parse
{
	char			*data;
	struct s_list	*left;
	struct s_list	*right;
}	t_parse;

char	**ft_split(char *s, char c);
char	**ft_help(char *s, char c, int len, char **final);
void	ft_free(char **ptr, int i);
char	*ft_strndup(char *src, int n);
int		countword(char *s, char c);
int		ft_strncmp(char *s1, char *s2, int len);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);

#endif