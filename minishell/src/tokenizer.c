#include "../minishell.h"
#include <stdio.h>
#include <unistd.h>

int ft_isspace(char c)
{
    if (c == ' ' || c == '\t' || c == '\n')
        return (1);
    return (0);
}
int count_tokens(char *line)
{
    int count;
    int i;

    if (!line)
        return (0);
    count = 0;
    i = 0;
    while (line[i])
    {
        while (ft_isspace(line[i]))
            i++;
        if (ft_strchr("|>&<()", line[i]))
        {
            i++;
            count++;
        }
        else
        {
            while (!ft_strchr("|>&<()", line[i]) && line[i] && !ft_isspace(line[i]))
                i++;
            count++;
        }
    }
    return (count);
}

int count_word(char *line)
{
    int count;

    if (!line)
        return (0);
    count = 0;
    while (!ft_strchr("|><&()", line[count]) && line[count] && !ft_isspace(line[count]))
        count++;
    return (count);
}
char **tokinize(char *line)
{
    char **tokens;
    int word_len;
    int i;
    int j;
    int z;
    
    tokens = malloc((count_tokens(line) + 1)* sizeof(char *));
    if (!tokens)
        return (write(2, "malloc on drugs\n", 17), NULL);
    i = 0;
    j = 0;
    while (line[i])
    {
        while (ft_isspace(line[i]))
            i++;
        if (ft_strchr("|>&<()", line[i]))
        {
            tokens[j] = malloc(3 * sizeof(char));
            if (!tokens[j])
                return (write(2, "malloc on drugs\n", 17), NULL);
            if (line[i] == line[i + 1] && line[i] != '(' && line[i] != ')')
            {
                tokens[j][0] = line[i];
                tokens[j][1] = line[i];
                tokens[j][2] = '\0';
                i += 2;
            }
            else
            {
                tokens[j][0] = line[i];
                tokens[j][1] = '\0';
                i++;
            }
            j++;
        }
        else
        {
            word_len = count_word(&line[i]);
            tokens[j] = malloc((word_len + 1) * sizeof(char));
            if (!tokens[j])
                return (write(2, "malloc on drugs\n", 17), NULL);
            z = 0;
            while (z < word_len)
                tokens[j][z++] = line[i++];
            tokens[j][z] = '\0';
            j++;
        }
    }
    tokens[j] = NULL;
    return tokens;
}
