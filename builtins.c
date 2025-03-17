/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msaadaou <msaadaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 17:27:47 by msaadaou          #+#    #+#             */
/*   Updated: 2025/03/15 17:28:33 by msaadaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_env(t_list **lst, char **env)
{
	int		i;
	char	**mtr;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		mtr = ft_split(env[i], '=');
		ft_lstadd_back(lst, ft_lstnew(mtr[1], mtr[0]));
		free(mtr);
		i++;
	}
}

int ft_env(t_list *lst)
{
	while (lst)
	{
		printf("%s=%s\n", lst->name, lst->value);
		lst = lst->next;
	}
	return (0);
}

int ft_export(t_list **lst, char *export_param)
{
	char	**mtr;
	char	*value;
	t_list	*temp;
	
	if (!export_param)
	{
		ft_env(*lst);
		return (1);
	}
	//validation of mtr[0]
	mtr = ft_split(export_param, '=');
	value = ft_substr(mtr[1], 1, ft_strlen(mtr[1]) - 2);
	free(mtr[1]);
	temp = *lst;
	while (temp)
	{
		if (!ft_strncmp(temp->name, mtr[0], ft_strlen(mtr[0])))
		{
			free(temp->value);
			temp->value = value;
			return (0);
		}
		temp = temp->next;
	}
	ft_lstadd_back(lst, ft_lstnew(value, mtr[0]));
	return (0);
}

void	rm_node(t_list *lst, char *str)
{
	t_list	*tmp;
	
	while (lst->next)
	{
		if (!ft_strncmp(lst->next->name, str, ft_strlen(str)))
		{
			tmp = lst->next;
			lst->next = tmp->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		lst = lst->next;
	}
}

int	ft_unset(t_list **lst, char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		rm_node(*lst, argv[i]);
		i++;
	}
	return (0);
}

int	ft_pwd()
{
	char	*ptr;

	ptr = getcwd(NULL, 0);
	if (!ptr)
	{
		perror("pwd");
		return (1);
	}
	printf("%s\n", ptr);
	free(ptr);
	return (0);
}

int	ft_cd(t_list *head, char *path)
{
	char	*old_pwd;
	char	*pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(path) == -1)
	{
		perror("cd");
		free(old_pwd);
		return 1;
	}
	pwd = getcwd(NULL, 0);
	while (head)
	{
		if (!ft_strncmp("OLDPWD", head->name, ft_strlen(head->name)))
		{
			free(head->value);
			head->value = old_pwd;
		}
		else if (!ft_strncmp("PWD", head->name, ft_strlen(head->name)))
		{
			free(head->value);
			head->value = pwd;
		}
		head = head->next;
	}
	return (0);
}

int ft_echo(char **args)
{
	int	i;
	int	flag;

	flag = 0;
	i = 1;
	if (!ft_strncmp(args[1], "-n", ft_strlen(args[1])))
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		if (i)
			printf(" ");
		printf("%s", args[i]);
		i++;
	}
	if (!flag)
		printf("\n");
	return (0);
}
