#include "../minishell.h"

static void push(t_stack **stack, t_tokens *token)
{
    t_stack *new_node;
    t_stack *current;

    if (!token)
        return;
    new_node = malloc(sizeof(t_stack));
    if (!new_node)
        return;
    new_node->token = token;
    new_node->next = NULL;

    if (!*stack)
        *stack = new_node;
    else
    {
        current = *stack;
        while (current->next)
            current = current->next;
        current->next = new_node;
    }
}

static t_tokens *pop(t_stack **stack)
{
    t_stack *temp;
    t_tokens *token;

    if (!*stack)
        return (NULL);

    temp = *stack;
    token = temp->token;
    *stack = temp->next;
    free(temp);
    return (token);
}

static int check_prio(t_tokens *token)
{
    if (token->type == TOKEN_PIPE)
        return (2);
    else if (token->type == TOKEN_AND || token->type == TOKEN_OR)
        return (1);
    return (0);
}

static void push_op(t_stack **stack, t_tokens *token)
{
    t_stack *new_node;

    if (!token)
        return;
    new_node = malloc(sizeof(t_stack));
    if (!new_node)
        return;
    new_node->token = token;
    new_node->next = *stack; 
    *stack = new_node;
}

t_stack *shuntin_yard(t_tokens *tokens)
{
    t_stack *output_queue;  // FIFO STACK
    t_stack *op_stack;      // LIFO STACK
    t_tokens *tmp;

    output_queue = NULL;
    op_stack = NULL;
    
    while (tokens)
    {
        if (tokens->type == TOKEN_COMMAND)
            push(&output_queue, tokens);
        else if (tokens->type == TOKEN_PIPE || tokens->type == TOKEN_AND || tokens->type == TOKEN_OR)
        {
            while (op_stack && op_stack->token->type != TOKEN_PAREN_OPEN && 
                   check_prio(op_stack->token) >= check_prio(tokens))
            {
                tmp = pop(&op_stack);
                push(&output_queue, tmp);
            }
            push_op(&op_stack, tokens);
        }
        else if (tokens->type == TOKEN_PAREN_OPEN)
            push_op(&op_stack, tokens);
        else if (tokens->type == TOKEN_PAREN_CLOSE)
        {
            while (op_stack && op_stack->token->type != TOKEN_PAREN_OPEN)
            {
                tmp = pop(&op_stack);
                push(&output_queue, tmp);
            }
            if (op_stack && op_stack->token->type == TOKEN_PAREN_OPEN)
                pop(&op_stack);
        }
        tokens = tokens->next;
    }
    while (op_stack)
    {
        tmp = pop(&op_stack);
        push(&output_queue, tmp);
    }
    return output_queue;
}
