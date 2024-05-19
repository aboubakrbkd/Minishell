/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkimdil <mkimdil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:50:37 by mkimdil           #+#    #+#             */
/*   Updated: 2024/05/19 17:06:47 by mkimdil          ###   ########.fr       */
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

/* tis is an example of the struct i need */
typedef struct s_cmd
{
	char			*cmd; // ls -la
	char			**argv; // argv[0] ls argv[1] = -la argv[2] = NULL
	// int			infile;
	// int			outfile;
	struct s_cmd	*next;
}					t_cmd;

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
int		parsing(char *line);
int		syn_error(char *line);
int		syn_error2(char **res);
int		syn_error3(char **res);
void	free_array(char **arr);
char	*add_space(char *line);
void	second_case(char *str, char *line, int *i, int *j);
int		count_num_of_special(char *line);
int		is_special_char(char c);
int		handle_single_double(char *line);
void	change_to_garb(char *line);
int		build_arr(t_cmd **lst, char **res);
int		ft_strcpy(char *dest, char *src);
void	fill_arr(t_cmd *lst);
t_cmd	*new_list(void *cmd);
void	back_to_ascii(t_cmd *lst);
char	*nops_strdup(char *str);

#endif