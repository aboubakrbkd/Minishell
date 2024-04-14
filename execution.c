#include "minishell.h"
#include <stdio.h>
/*
typedef struct s_cmd
{
	char	*cmd;
	char	**argv;
	int		infile;
	int		outfile;
}				t_cmd;
*/

void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	*check(char *my_argv)
{
	if (my_argv[0] == '/')
	{
		if (access(my_argv, F_OK | X_OK) == 0)
			return (my_argv);
		else
		{
            printf("error in acces /\n");
            exit(1);
        }
	}
	return (0);
}

char	**get_path(char **envp)
{
	int		i;
	char	**s;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			break ;
		i++;
	}
	s = ft_split(envp[i] + 5, ':');
	return (s);
}

char	*command(char *my_argv, char **envp)
{
	char	**path;
	char	*joiner;
	char	*command_path;
	int		i;

	path = get_path(envp);
	i = 0;
	check(my_argv);
	while (path[i])
	{
		if (access(my_argv, F_OK | X_OK) == 0)
			return (my_argv);
		joiner = ft_strjoin(path[i], "/");
		command_path = ft_strjoin(joiner, my_argv);
		free(joiner);
		if (access(command_path, F_OK | X_OK) == 0)
			return (free_all(path), command_path);
		free(command_path);
		i++;
	}
	return (free_all(path), NULL);
}

void	close_files(t_cmd *node)
{
	if (close(node->infile) == -1)
    {
        perror("close");
        exit(1);
    }
	if (close(node->outfile) == -1)
    {
        perror("close");
        exit(1);
    }
    
}

void    execution(t_cmd *node, char **envp)
{
    // t_cmd *node;
    int fd[2];
    int id;

    while (node->next)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(1);
        }
        id = fork();
        if (id == -1)
        {
            perror("fork");
            exit(1);
        }
        if (id == 0)
        {
            
            node->cmd = command(node->argv[0], envp);
            if (execve(node->cmd, node->argv, envp) == -1)
            {
                perror("execve");
                exit(1);
            }
        }
        node= node->next;
    }
    if (node)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(1);
        }
        id = fork();
        if (id == -1)
        {
            perror("fork");
            exit(1);
        }
        if (id == 0)
        {
            node->cmd = command(node->argv[0], envp);
            if (execve(node->cmd, node->argv, envp) == -1)
            {
                perror("execve");
                exit(1);
            }
        }
    }
    while (wait(NULL) != -1)
        ;
    close_files(node);
}

int main(int argc, char **argv,  char **envp)
{
    t_cmd *node;
    node = (t_cmd *)malloc(sizeof(t_cmd));
    node->argv = (char **)malloc(sizeof(char *) * 3);
    node->argv[0] = ft_strdup("ls");
    node->argv[1] = NULL;
    node->argv[2] = NULL;
    node->infile = 0;
    node->outfile = 1;
    node->next = (t_cmd *)malloc(sizeof(t_cmd));
    node->next->argv = (char **)malloc(sizeof(char *) * 3);
    node->next->argv[0] = ft_strdup("wc");
    node->next->argv[1] = NULL;
    node->next->argv[2] = NULL;
    node->next->infile = 0;
    node->next->outfile = 1;
    node->next->next = NULL;
    execution(node, envp);
}