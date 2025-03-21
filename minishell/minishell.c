#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

void print_ast(t_ast_node *node, int depth)
{
    int i;
    
    if (!node)
        return;
    for (i = 0; i < depth; i++)
        printf("  ");
    if (node->type == AST_CMD)
        printf("CMD: %s %p\n", node->args[0], node->next);
    else if (node->type == AST_PIPE)
        printf("PIPE\n");
    else if (node->type == AST_AND)
        printf("AND\n");
    else if (node->type == AST_OR)
        printf("OR\n");
    
    // Print children
    if (node->left)
    {
        print_ast(node->left, depth + 1);

        for (i = 0; node->left->args[i]; i++)
        {
            for (int j = 0; j < depth + 1; j++)
                printf("  ");
            printf("ARG: %s\n", node->left->args[i]);
        }
    }
    if (node->right)
        print_ast(node->right, depth + 1);
}
void free_args(char **args)
{
    int i;

    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);
}

// int	ft_strcmp(char *str1, char *str2)
// {
// 	int	i;

// 	i = 0;
// 	while (str1[i] || str2[i])
// 	{
// 		if (str1[i] > str2[i])
// 			return (1);
// 		else if (str1[i] < str2[i])
// 			return (-1);
// 		i++;
// 	}
// 	return (0);
// }

// void	open_herdoc(t_redirection *node)
// {
// 	int		new_in_fd;
// 	char	*line;

// 	new_in_fd = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	// if (new_in_fd == -1)
// 	// 	t_error("pipex: input", data, 1);
// 	line = get_next_line(0);
// 	line[ft_strlen(line) - 1] = 0;
// 	while (ft_strcmp(node->file, line))
// 	{
// 		line[ft_strlen(line)] = '\n';
// 		write(new_in_fd, line, ft_strlen(line));
// 		free(line);
// 		line = get_next_line(0);
// 		line[ft_strlen(line) - 1] = 0;
// 	}
// 	free(line);
// 	close(new_in_fd);
// }

void	handle_redirection(t_ast_node *node, int *infd, int *outfd)
{
	t_redirection	*lst;

	lst = node->redirections;
	while (lst)
	{
		if (lst->type == TOKEN_REDIR_IN)
		{
			*infd = open(lst->file, O_RDONLY);
			if (*infd == -1)
			{
				perror("open");
				return ;
			}
		}
		else if (lst->type == TOKEN_APPEND || lst->type == TOKEN_REDIR_OUT)
		{
			if (lst->type == TOKEN_APPEND)
				*outfd = open(lst->file, O_CREAT | O_APPEND | O_WRONLY, 0644);
			else
				*outfd = open(lst->file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (*outfd == -1)
			{
				perror("open");
				return ;
			}
		}
		// else if (lst->type == TOKEN_HEREDOC)
		// {
		// 	open_herdoc(lst);
		// 	*infd = open("here_doc", O_RDONLY);
		// 	if (*outfd == -1)
		// 	{
		// 		perror("open");
		// 		return ;
		// 	}
		// }
		lst = lst->next;
	}
}

// int my_execve(t_ast_node *node)
// {
// 	if (!ft_strcmp(node->cmd_args[0], "echo"))
// 		return (ft_echo(node->cmd_args));
// 	else if (!ft_strcmp(node->cmd_args[0], "cd"))
// 		return (ft_cd(node->env_var, node->cmd_args[1]));
// 	else if (!ft_strcmp(node->cmd_args[0], "pwd"))
// 		return (ft_pwd());
// 	else if (!ft_strcmp(node->cmd_args[0], "export"))
// 		return (ft_export(node->env_var, node->cmd_args[1]));
// 	else if (!ft_strcmp(node->cmd_args[0], "unset"))
// 		return (ft_unset(node->env_var, node->cmd_args));
// 	else if (!ft_strcmp(node->cmd_args[0], "env"))
// 		return (ft_env(*(node->env_var)));
// 	// else if (!ft_strcmp(node->cmd_args[0], "exit")) to do
// 	// 	return (1);
// }

// int execute_builtin(t_ast_node *node, int infd, int outfd)
// {
// 	handle_redirection(node, &infd, &outfd);
// 	if (infd)
// 	{
// 		dup2(infd, 0);
// 		close(infd);
// 	}
// 	if (outfd != 1)
// 	{
// 		dup2(outfd, 1);
// 		close(outfd);
// 	}
// 	my_execve(node);
// }

// int	is_builtin(char *cmd)
// {
// 	if (!ft_strcmp(cmd, "echo"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "cd"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "pwd"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "export"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "unset"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "env"))
// 		return (1);
// 	else if (!ft_strcmp(cmd, "exit"))
// 		return (1);
// 	return (0);
// }

char	*helper_path_cmd(char **commands_path, char *cmd)
{
	int		i;
	char	*command_path;

	i = 0;
	while (commands_path[i])
	{
		command_path = ft_strjoin(commands_path[i], cmd);
		if (!command_path)
		{
			free_args(commands_path);
			free(cmd);
			return (NULL);
		}
		if (!access(command_path, X_OK))
		{
			free_args(commands_path);
			free(cmd);
			return (command_path);
		}
		free(command_path);
		i++;
	}
	free_args(commands_path);
	free(cmd);
	return (NULL);
}

char	*helper_path(char *str, char *cmd, int size)
{
	char	*complete_path;
	char	**commands_path;

	complete_path = ft_substr(str, size, ft_strlen(str) - size);
	if (!complete_path)
		return (NULL);
	commands_path = ft_split(complete_path, ":");
	if (!commands_path)
	{
		free(complete_path);
		return (NULL);
	}
	free(complete_path);
	return (helper_path_cmd(commands_path, cmd));
}

char	*debug_okda(char **env, char *cmd)
{
	char	*str;
	char	*cmdr;
	int		i;

	if (!cmd)
		return (NULL);
	if (!access(cmd, X_OK))
		return (ft_strdup(cmd));
	cmdr = ft_strjoin("/", cmd);
	if (!cmdr)
		return (NULL);
	i = 0;
	while (env[i])
	{
		str = ft_strnstr(env[i], "PATH=", ft_strlen("PATH="));
		if (str)
			return (helper_path(str, cmdr, ft_strlen("PATH=")));
		i++;
	}
	return (NULL);
}

int execute_command(t_ast_node *node, int infd, int outfd, int cs, char **env)
{
	int status;
	
	// if (is_builtin(node->args[0]))
	// 	execute_builtin(node, infd, outfd);
	node->pid = fork();
	if (!node->pid)
	{
		close(cs);

		handle_redirection(node, &infd, &outfd);
		if (infd)
		{
			dup2(infd, 0);
			close(infd);
		}
		if (outfd != 1)
		{
			dup2(outfd, 1);
			close(outfd);
		}
		char *d = debug_okda(env, node->args[0]);
		// fprintf(stderr, "xi7aja\n");
		execve(d, node->args, env);
		exit(1);
	}
	if (node->is_wait)
	{
		if (node->ar_pipe)
		{
			close(node->ar_pipe[0]);
			close(node->ar_pipe[1]);
			free(node->ar_pipe);
			node->ar_pipe = NULL;
		}
		waitpid(node->pid, &status, 0);
    	return (WEXITSTATUS(status));
	}
	return (0);
}

void	ana_m9wd(t_ast_node *node)
{
	//ma kan7tajxe parting m9wd parting ki7tajni
	if (!node->right)
	{
		node->is_wait = 1;
		return ;
	}
	ana_m9wd(node->right);
}

int	execute_tree(t_ast_node *node, int fd, int outfd, int cs, char **env)
{
	int		status;

	if (!node)
		return (1);
	if (node->type == AST_PIPE)
	{
		node->right->ar_pipe = malloc(2 * sizeof(int));
		// TO DO
		pipe(node->right->ar_pipe);
		execute_tree(node->left, fd, node->right->ar_pipe[1], node->right->ar_pipe[0], env);
		status = execute_tree(node->right, node->right->ar_pipe[0], outfd, node->right->ar_pipe[1], env);
		if (node->right->ar_pipe)
		{
			close(node->right->ar_pipe[0]);
			close(node->right->ar_pipe[1]);
			free(node->right->ar_pipe);
			node->right->ar_pipe = NULL;
		}
	}
	else if (node->type == AST_AND)
	{
		ana_m9wd(node->left);
		status = execute_tree(node->left, fd, outfd, cs, env);
		if (!status)
			status = execute_tree(node->right, fd, outfd, cs, env);
	}
	else if (node->type == AST_OR)
	{
		ana_m9wd(node->left);
		status = execute_tree(node->left, fd, outfd, cs, env);
		if (status)
			status = execute_tree(node->right, fd, outfd, cs, env);
	}
	else if (node->type == AST_CMD)
		return (execute_command(node, fd, outfd, cs, env));
	return (status);
}

// void init_data(t_ast_node *ast, int flag)
// {
//     if (!ast)
//         return ;
//     if (ast->type == AST_PIPE)
//         flag = 1;
//     if (flag && ast->type == AST_CMD)
//     {
//         ast->is_wait = 1;
//         flag = 0;
//     }
//     init_data(ast->left, flag);
//     init_data(ast->right, 0);
// }

int waiting(t_ast_node *ast)
{
    int	status;
	
	while (wait(NULL) > 0);
	// if (!ast->right)
	// {
	// 	// waitpid(ast->pid, &status, 0);
	// 	while (wait(NULL) > 0);
	// 	return (0);
    // 	// return (WEXITSTATUS(status));
	// }
	// waiting(ast->right);
	// return (0);
	// wait(NULL);
	// if (!ast)
    //     return ;
    // if(ast->next)
	// {    if (ast->type == AST_CMD && ast->next->token->type == TOKEN_PIPE)
    //     	wait(NULL);
	// }
	// // wait(NULL);
    // waiting(ast->left, counter);
    // waiting(ast->right, counter);
}

int main(int ac, char **av, char **env)
{
    char *line;
    char **args;
    t_stack *stack;
    t_tokens *tokens;
    t_ast_node *ast;
    int counter = 0;
    while (1)
    {
        line = readline("minishell> ");
        if (!line)
            break;
        args = tokinize(line);
        if (syntax_error(args))
        {
            (free_args(args), free(line));
            continue;
        }
        add_history(line);
        tokens = tokens_list(args);
        stack = shuntin_yard(tokens);
        ast = make_tree(stack);
		// print_ast(ast, 0);
        execute_tree(ast, 0, 1, -1, env);
        waiting(ast);
    }
    return 0;
}
