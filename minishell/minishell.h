#ifndef MINISHELL_H

#define MINISHELL_H

#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
       #include <sys/wait.h>
typedef struct s_redirection {
	char    *file;            // Filename (for >, <, etc.)
	int     type;             // Type (REDIR_IN, REDIR_OUT, HEREDOC, etc.)
	struct s_redirection *next;
} t_redirection;


typedef enum e_ast_type {    // AST == Abstract Syntax Tree
	AST_CMD,     // Simple command (`ls -la`)
	AST_PIPE,    // Pipe operator `|`
	AST_AND,     // Logical AND `&&`
	AST_OR,      // Logical OR `||`
	AST_REDIRECTION,  // Redirection operator `>`, `<`, `>>`, `<<`
	AST_GROUP    // Parentheses `(...)` to group commands
} t_ast_type;

typedef enum e_token_type {
    TOKEN_COMMAND,    // Regular command or argument
    TOKEN_PIPE,       // |
    TOKEN_AND,        // &&
    TOKEN_OR,         // ||
    TOKEN_REDIR_IN,   // <
    TOKEN_REDIR_OUT,  // >
    TOKEN_APPEND,     // >>
    TOKEN_HEREDOC,    // <<
    TOKEN_PAREN_OPEN, // (
    TOKEN_PAREN_CLOSE // )
} t_token_type;





typedef struct s_tokens {
	t_token_type type;
	char *cmd;
	t_redirection *redirections;
	struct s_tokens *next;
} t_tokens;

typedef struct s_stack
{
	t_tokens *token;
	struct s_stack *next;
}	t_stack;

typedef struct s_ast_node {
	t_ast_type      type;
	struct s_ast_node *left;
	struct s_ast_node *right;
	int		pid;
	// For AST_CMD:
	char            **args;
	char			**env;
	t_stack			*next;
	int				is_wait;
	t_redirection   *redirections;
} t_ast_node;

typedef struct s_node_stack
{
    t_ast_node *node;
    struct s_node_stack *next;
} t_node_stack;

char **tokinize(char *line);
t_tokens *tokens_list(char **args);
void open_heredocs(t_tokens *tokens);
t_stack *shuntin_yard(t_tokens *tokens);
t_ast_node *make_tree(t_stack *stack);
int syntax_error(char **args);

#endif
