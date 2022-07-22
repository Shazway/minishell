/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:24:29 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/22 17:10:14 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*----------TO DO BEFORE CD:
CHANGE ENVIRONMENT VARIABLE : SWAP $OLDPWD and $PWD*/

char	*concat_path(char *goal, char *folder_name)
{
	char	*temp;

	temp = goal;
	goal = ft_strjoin(goal, "/");
	free(temp);
	if (!goal)
		return (NULL);
	temp = goal;
	goal = ft_strjoin(goal, folder_name);
	free(temp);
	if (!goal)
		return (NULL);
	return (goal);
}

char	*previous_dir(char *path)
{
	int		i;
	char	*tmp;

	i = ft_strlen(path);
	while (path && i > 0 && path[i] == '/')
		i--;
	while (path && i > 0 && path[i] != '/')
		i--;
	tmp = path;
	if (i == 0)
		return (ft_strdup("/"));
	path = ft_substr(path, 0, i);
	free(tmp);
	return (path);
}

char	*next_dir(char *foldername)
{
	int		i;

	i = 0;
	if (foldername && foldername[i] && foldername[i] == '/')
		i++;
	while (foldername && foldername[i] &&foldername[i] != '/')
		i++;
	if (!foldername[i] || !foldername[i + 1])
		return (NULL);
	if (foldername[i] == '/')
		i++;
	foldername = ft_substr(foldername, i, ft_strlen(foldername));
	return (foldername);
}

char	*find_new_pwd(char *foldername, char **goal)
{
	int		i;
	char	*tmp;
	char	*to_go;

	i = 0;
	while (foldername && foldername[i] && foldername[i] != '/')
		i++;
	to_go = ft_substr(foldername, 0, i);
	tmp = to_go;
	to_go = ft_strtrim(to_go, "/");
	free(tmp);
	if (!ft_strncmp(to_go, "..", 3))
	{
		*goal = previous_dir(*goal);
		foldername = next_dir(foldername);
	}
	else
	{
		*goal = concat_path(*goal, to_go);
		foldername = next_dir(foldername);
	}
	free(to_go);
	return (foldername);
}

void	new_pwd(char *foldername, char **new_path)
{
	char	*tmp;

	if (ft_strlen(foldername) > 0
		&& foldername[ft_strlen(foldername) - 1] != '/')
	{
		tmp = foldername;
		foldername = ft_strjoin(foldername, "/");
		free(tmp);
	}
	printf("FOLDERNAME is : %s\n", foldername);
	while (foldername && ft_strchr(foldername, '/'))
	{
		printf("cd .. TEST\n");
		tmp = foldername;
		foldername = find_new_pwd(foldername, new_path);
		free(tmp);
		if (!ft_strchr(foldername, '/'))
			return ;
	}
}


int	change_path(char *goal, char *foldername, t_data *data)
{
	char	*tmp;

	if (chdir(goal) == -1)
	{
		printf("cd: %s: No such file or directory\n", foldername);
		free(goal);
		free(foldername);
		return (-1);
	}
	else
	{
		printf("OLD PWD[%s]\n", data->relative_path);
		if (!foldername)
		{
			tmp = data->relative_path;
			data->relative_path = ft_strdup(goal);
			free(tmp);
		}
		else
		{
			new_pwd(ft_strdup(foldername), &(data->relative_path));
			printf("NEW PWD[%s]\n", data->relative_path);
		}
		free(goal);
		free(foldername);
	}
	return (1);
}

int	cd(t_data *data, int ac, char **str)
{
	char	*path;
	char	*arg;

	arg = NULL;
	if (ac > 2)
		return (printf("minishell: cd: too many arguments\n"));
	if (ac == 1)
		return (cd_home(get_var("HOME", data), "HOME", data));
	arg = ft_strdup(str[1]);
	if (is_dash(arg) != 0)
		return (cd_dash(arg, data));
	if (arg[0] == '/')
		return (change_path(arg, NULL, data));
	path = ft_strdup(data->relative_path);
	path = concat_path(path, arg);
	if (!path)
		return (-1);
	if (change_path(path, arg, data) == -1)
		return (-1);
	return (1);
}
