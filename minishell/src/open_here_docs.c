#include "../minishell.h"
#include <unistd.h>


static int calcul_here_docs(t_tokens *tokens)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (tokens)
    {
        if (ft_strcmp(tokens->cmd, "<<"))
            count++;
        tokens = tokens->next;
    }
    return (count);
}



void open_heredocs(t_tokens *tokens)
{
    t_redirection *red;
    int *fds;
    int count;
    int i;

    red = NULL;
    count = calcul_here_docs(tokens);
    fds = malloc(sizeof(int) * count);
    i = 0;
    while (tokens)
    {
        if (ft_strcmp(tokens->cmd, "<<"))
        {
            fds[i] = open("here_docs", O_CREAT | O_RDWR | O_TRUNC, 0644);
            red = malloc(sizeof(t_redirection));
            red->deli = tokens->next->cmd;
            red->type = REDIR_HEREDOC;
            red->next = NULL;
            i++;
        }
        tokens = tokens->next->next; // skip the delimiter
    }
}