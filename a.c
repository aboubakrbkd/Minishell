void	append_it(char *arg, t_cmd **lst, int i)
{
	char	**splited;
	int		j;

	splited = ft_split(arg, ' ');
	j = 0;
	while (splited[j])
	{
		lst->argv[i] = splited[j];
		i++;
		j++;
	}
}

void	expand(t_cmd *lst, t_list *envp)
{
	int		i;

	while (lst)
	{
		i = 0;
		while (lst->argv[i])
		{
			if (ft_strchr(lst->argv[i], '$'))
			{
				lst->argv[i] = expand_cmd(lst, envp, i);
				if (ft_strsearch(lst->argv[i], ' '))
					append_it(lst->argv[i], &lst, i);
			}
			i++;
		}
		lst = lst->next;
	}
}
typedef struct s_cmd
{
	char			*cmd;
	char			**argv;
	char			**delim;
	int				is_qoute;
	int				fd;
	int				infile;
	int				outfile;
	int				is_heredoc;
	struct s_cmd	*next;
}					t_cmd;
➜  Minishell git:(parsing) ✗ make
cc -Wall -Wextra -Werror -fsanitize=address -g -I/Users/mkimdil/.brew/opt/readline/include -c expand.c -o obj/expand.o
expand.c:153:6: error: member reference base type 't_cmd *' (aka 'struct s_cmd *') is not a
      structure or union
                lst->argv[i] = splited[j];
                ~~~^ ~~~~
1 error generated.
make: *** [obj/expand.o] Error 1
