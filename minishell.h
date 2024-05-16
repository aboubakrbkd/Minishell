/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:50:37 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/16 18:56:39 by mkimdil          ###   ########.fr       */
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
# include <fcntl.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	int				index;
	struct s_env	*next;
}				t_env;

typedef struct s_global
{
	t_env	*envs;
}				t_global;

typedef struct s_minishell
{
	char	**cmd;
	t_env	*env;
}				t_minishell;

/* tis is an example of the struct i need */
typedef struct s_cmd
{
	char			*cmd;
	char			**argv;
	// int			infile;
	// int			outfile;
	struct s_cmd	*next;
}					t_cmd;

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
char	*ft_strchr(char *s, int c);
char	*ft_strnstr(char *str, char *to_find, int len);
void	pwd(char **envp);
t_env	*env_init(char **envp);
char	*my_getenv(char *name);
t_env	*ft_lstnew(char *name, char *value);
int		is_number(char c);
int		is_upper(char c);
int		is_lower(char c);
void	execution(t_cmd *node, char **envp);

/*************BUILT in**/
int		echo(char **argv);
int		cd(char **argv);
int		exit_function(char **argv);
void	env(t_env *env);
int		unset(char **argv, t_env **envps);
void	pwd(char **argv);

// parsing func
void	parsing(char *line);
void	syn_error(char *line);
void	syn_error2(char **res);
void	syn_error3(char **res);
void	free_array(char **arr);
char	*add_space(char *line);
void	second_case(char *str, char *line, int *i, int *j);
int		count_num_of_special(char *line);
int		is_special_char(char c);

#endif