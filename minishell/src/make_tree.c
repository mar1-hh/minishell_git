#include "../minishell.h"

// Push node to AST node stack
static void push_node(t_node_stack **stack, t_ast_node *node)
{
    t_node_stack *new_node;

    if (!node)
        return;
    new_node = malloc(sizeof(t_node_stack));
    if (!new_node)
        return;
    new_node->node = node;
    new_node->next = *stack;
    *stack = new_node;
}

// Pop node from AST node stack
static t_ast_node *pop_node(t_node_stack **stack)
{
    t_node_stack *temp;
    t_ast_node *node;

    if (!*stack)
        return (NULL);
    temp = *stack;
    node = temp->node;
    *stack = temp->next;
    free(temp);
    return (node);
}

// Convert token type to AST type
static t_ast_type token_to_ast_type(t_token_type type)
{
    if (type == TOKEN_COMMAND)
        return AST_CMD;
    else if (type == TOKEN_PIPE)
        return AST_PIPE;
    else if (type == TOKEN_AND)
        return AST_AND;
    else if (type == TOKEN_OR)
        return AST_OR;
    else if (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT || 
             type == TOKEN_APPEND || type == TOKEN_HEREDOC)
        return AST_REDIRECTION;
    else if (type == TOKEN_PAREN_OPEN || type == TOKEN_PAREN_CLOSE)
        return AST_GROUP;
    return AST_CMD; // Default
}

// Create node if flag 0 type = cmd if flag = 1 type operation
static t_ast_node *create_node(t_stack *stack, int flag)
{
    t_ast_node *node;
    
    node = malloc(sizeof(t_ast_node));
    if (!node)
        return NULL;
    if (!flag)
    {
        node->type = AST_CMD;
        node->args = ft_split(stack->token->cmd, " ");
        node->redirections = stack->token->redirections;
    }
    else
    {
        node->type = token_to_ast_type(stack->token->type);
        node->args = NULL;
        node->redirections = NULL;
    }
    node->next = stack->next;
    node->is_wait = 0;
    node->ar_pipe = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}


// Main function to build the AST
t_ast_node *make_tree(t_stack *stack)
{
    t_node_stack *node_stack;
    t_ast_node *new_node;
    t_stack *current;
    
    node_stack = NULL;
    current = stack;
    while (current)
    {
        if (current->token->type == TOKEN_COMMAND)
        {
            new_node = create_node(current, 0);
            push_node(&node_stack, new_node);
        }
        else if (current->token->type == TOKEN_PIPE || 
                 current->token->type == TOKEN_AND || 
                 current->token->type == TOKEN_OR)
        {
            new_node = create_node(current, 1);
            new_node->right = pop_node(&node_stack);
            new_node->left = pop_node(&node_stack);
            push_node(&node_stack, new_node);
        }
        current = current->next;
    }
    return pop_node(&node_stack);
}
