/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:24:29 by mdkhissi          #+#    #+#             */
/*   Updated: 2022/07/22 01:54:34 by tmoragli         ###   ########.fr       */
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
	if (i == 0)
		return (ft_strdup("/"));
	tmp = path;
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

	if (foldername && foldername[0] == '/')
	{
		//--PAS TOUCHER, ICI IL N'Y A PAS DE LEAK NI DE DOUBLE FREE è_é !!!--//
		tmp = *new_path;
		*new_path = ft_strdup(foldername);
		free(tmp);
		free(foldername);
		return ;
		//-------------------------------------------------------------------//
	}
	if (ft_strlen(foldername) > 0
		&& foldername[ft_strlen(foldername) - 1] != '/')
		foldername = ft_strjoin(foldername, "/");
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
	free(tmp);
}


int	change_path(char *goal, char *foldername, t_data *data)
{
	char	*tmp;

	if (chdir(goal) == -1)
	{
		printf("cd: %s: No such file or directory\n", foldername);
		free(goal);
		return (-1);
	}
	else
	{
		printf("OLD PWD[%s]\n", data->relative_path);
		tmp = ft_strdup(foldername);
		new_pwd(tmp, &(data->relative_path));
		printf("NEW PWD[%s]\n", data->relative_path);
		//free(tmp);
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
		return (change_path(arg, ft_strdup(arg), data));
	path = ft_strdup(data->relative_path);
	path = concat_path(path, arg);
	if (!path)
		return (-1);
	if (change_path(path, arg, data) == -1)
		return (-1);
	//free(arg);
	return (1);
}
