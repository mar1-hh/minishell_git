#include "../minishell.h"
#include <stdio.h>

static int ft_is_cmd(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (str[i] == '|' || str[i] == '&' || str[i] == ';' || str[i] == '<' || str[i] == '>')
            return (0);
        i++;
    }
    return (1);
}

int syntax_error(char **args)
{
    int i;
    int j;

    i = 0;

    while (args[i])
    {
        if (!ft_strcmp(args[i], "<") || !ft_strcmp(args[i], ">") || !ft_strcmp(args[i], ">>") || !ft_strcmp(args[i], "<<"))
        {
            if (args[i + 1] == NULL || ft_is_cmd(args[i + 1]) == 0)
            {
                ft_putstr_fd("drugs: syntax error near unexpected token `", 2);
                ft_putstr_fd(args[i], 2);
                ft_putstr_fd("'\n", 2);
                return (1);
            }
        }
        else if (!ft_strcmp(args[i], "|") || !ft_strcmp(args[i], "&&") || !ft_strcmp(args[i], "||"))
        {
            if (args[i + 1] == NULL || ft_is_cmd(args[i + 1]) == 0 || i == 0 || ft_is_cmd(args[i - 1]) == 0)
            {
                ft_putstr_fd("drugs: syntax error near unexpected token `", 2);
                ft_putstr_fd(args[i], 2);
                ft_putstr_fd("'\n", 2);
                return (1);
            }
        }
        else if (!ft_strcmp(args[i], "("))
        {
            if (args[i + 1] == NULL || ft_is_cmd(args[i + 1]) == 0)
            {
                ft_putstr_fd("drugs: syntax error near unexpected token `", 2);
                ft_putstr_fd(args[i], 2);
                ft_putstr_fd("'\n", 2);
                return (1);
            }
        }
        else if (!ft_strcmp(args[i], ")"))
        {
            if (i == 0 || ft_is_cmd(args[i - 1]) == 0)
            {
                ft_putstr_fd("drugs: syntax error near unexpected token `", 2);
                ft_putstr_fd(args[i], 2);
                ft_putstr_fd("'\n", 2);
                return (1);
            }
        
        }
        i++;
    }
    return (0);
}