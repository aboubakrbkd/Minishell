/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:50:37 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/16 17:29:00 by aboukdid         ###   ########.fr       */
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

typedef struct s_list
{
	t_env	*envs;
}				t_list;

typedef struct s_minishell
{
	char	**cmd;
	t_env	*env;
}				t_minishell;

typedef struct s_cmd
{
	char			*cmd;
	char			**argv;
	// int			infile;
	// int			outfile;
	struct s_cmd	*next;
}					t_cmd;

/*************BUILT in**/
int		echo(char **argv);
int		cd(char **argv, t_list *list);
int		exit_function(char **argv);
void	env(char **argv, t_list *list);
int		unset(char **argv, t_env **envps);
void	pwd(char **args, t_list *list);
void	export(char **argv, t_list *list);
/************************/

char	**ft_split(char *s, char c);
char	**ft_help(char *s, char c, int len, char **final);
void	ft_free(char **ptr, int i);
char	*ft_strndup(char *src, int n);
int		countword(char *s, char c);
int		ft_strncmp(char *s1, char *s2, int len);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlen(char *str);
t_env	*env_init(char **envp);
int		is_number(char c);
int		is_upper(char c);
int		is_lower(char c);
void	execution(t_cmd *node, t_list *list);
void	home_function(char *home, t_list *list);
void	old_pwd_function(char *home, t_list *list);
void	error_function(char *home, t_list *list);
int		check_if_flag(char *argv);
char	**env_split(char *s, char c);
char	*my_getenv(char *name, t_list *list);
void	update_env(char *name, char *value, t_list *list);
void	update_pwd(char *path, t_list *list);
t_env	*ft_lstnew(char *name, char *value);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstadd_back(t_env **lst, t_env *new);
int		env_size(t_env *env);
void	swap_the_nodes(t_env *tmp1, t_env *tmp2);
void	sort_env(t_env *env);
void	index_env(t_env *env);
char	*get_name(char *str);
char	*get_value(char *str);
void	add_env(t_env **env, char *name, char *value);
int		add_the_value(char *name, char *value, t_list *list);
int		update_the_value(char *name, char *value, t_list *list);
void	free_all(char **str);
char	*check(char *my_argv);
char	*command(char *my_argv, char **env);
int		checking(t_env *tmp, char *name, char *value);
int		ft_strcmp(char *s1, char *s2);
int		ft_atoi(char *str);
char	*ft_strjoin_with_sep(char *s1, char *s2, char sep);
char	**get_path(char **envr);
char	*ft_strchr(const char *s, int c);
#endif
