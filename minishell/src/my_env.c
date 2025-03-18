#include "../minishell.h"
#include <stdlib.h>


static void free_env(char **env, int i)
{
    while (i > 0)
        free(env[i--]);
    free(env);
}

char **get_env(char **env)
{
    char **my_env;
    int width;
    int i;

    width = 0;
    while (env[width])
        width++;
    my_env = malloc(sizeof(char **) * (width + 1));
    if (!my_env)
        return (NULL);
    i = 0;
    while (i < width) 
    {
        my_env[i] = malloc(sizeof(char *) * (ft_strlen(env[i]) + 1));
        if (!my_env[i])
            return (free_env(env, i), NULL);
        ft_strlcpy(my_env[i], env[i], ft_strlen(env[i]) + 1);
        i++;
    }
    return (my_env);
}
