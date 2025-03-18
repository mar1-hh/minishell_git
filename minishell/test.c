// First fix the ft_is_cmd function

#include "minishell.h"
static int ft_is_cmd(char *arg)
{
    if (!ft_strcmp(arg, "||") || !ft_strcmp(arg, "&&") || !ft_strcmp(arg, "|") 
    || !ft_strcmp(arg, "<<") || !ft_strcmp(arg, ">>") || !ft_strcmp(arg, "<") 
    || !ft_strcmp(arg, ">")) {
        return (0);
    }
    return (1);
}

t_tokens *tokens_list(char **args)
{
    t_tokens *head = NULL;
    t_tokens *current = NULL;
    t_tokens *new_node = NULL;
    int i = 0;
    char *cmd_str = NULL;
    
    if (!args)
        return (NULL);
        
    while (args[i])
    {
        // Handle regular commands and their redirections
        if (ft_is_cmd(args[i]))
        {
            // Build command string
            cmd_str = ft_strdup("");
            while (args[i] && ft_is_cmd(args[i]))
            {
                char *temp = cmd_str;
                if (strlen(cmd_str) > 0)
                    cmd_str = ft_strjoin(temp, " ");
                else
                    cmd_str = ft_strdup("");
                free(temp);
                
                temp = cmd_str;
                cmd_str = ft_strjoin(temp, args[i]);
                free(temp);
                
                i++;
            }
            
            // Create node for command
            new_node = ft_new_node(cmd_str, TOKEN_CMD);
            
            // Process any redirections that follow
            while (args[i] && (!ft_strcmp(args[i], "<") || !ft_strcmp(args[i], ">") ||
                   !ft_strcmp(args[i], "<<") || !ft_strcmp(args[i], ">>")))
            {
                if (!ft_strcmp(args[i], "<"))
                {
                    if (args[i+1])
                        put_redir(new_node, args[i+1], TOKEN_REDIR_IN);
                }
                else if (!ft_strcmp(args[i], ">"))
                {
                    if (args[i+1])
                        put_redir(new_node, args[i+1], TOKEN_REDIR_OUT);
                }
                else if (!ft_strcmp(args[i], "<<"))
                {
                    if (args[i+1])
                        put_redir(new_node, args[i+1], TOKEN_HEREDOC);
                }
                else if (!ft_strcmp(args[i], ">>"))
                {
                    if (args[i+1])
                        put_redir(new_node, args[i+1], TOKEN_APPEND);
                }
                
                i += 2; // Skip redirection token and its argument
                
                // Safety check
                if (!args[i])
                    break;
            }
        }
        // Handle special tokens (|, ||, &&, (, ))
        else if (args[i])
        {
            if (!ft_strcmp(args[i], "|"))
                new_node = ft_new_node(args[i], TOKEN_PIPE);
            else if (!ft_strcmp(args[i], "||"))
                new_node = ft_new_node(args[i], TOKEN_OR);
            else if (!ft_strcmp(args[i], "&&"))
                new_node = ft_new_node(args[i], TOKEN_AND);
            else if (!ft_strcmp(args[i], "("))
                new_node = ft_new_node(args[i], TOKEN_PAREN_OPEN);
            else if (!ft_strcmp(args[i], ")"))
                new_node = ft_new_node(args[i], TOKEN_PAREN_CLOSE);
            else
                new_node = NULL; // Skip unrecognized tokens
                
            i++; // Move to next token
        }
        
        // Add the new node to our list
        if (new_node)
        {
            if (!head)
            {
                head = new_node;
                current = head;
            }
            else
            {
                current->next = new_node;
                current = current->next;
            }
            new_node = NULL;
        }
    }
    
    return head; // Return the head of the list
}