/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:46:59 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/27 23:13:57 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*path_finder(char *to_go, char *foldername, char **goal)
{
	if (!ft_strncmp(to_go, "..", 3))
	{
		*goal = previous_dir(*goal);
		foldername = next_dir(foldername);
	}
	else if (!ft_strncmp(to_go, ".", 2))
		foldername = next_dir(foldername);
	else
	{
		*goal = concat_path(*goal, to_go);
		foldername = next_dir(foldername);
	}
	free(to_go);
	if (!*goal || !foldername)
	{
		free(*goal);
		free(foldername);
		return (NULL);
	}
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
	if (!to_go)
		return (NULL);
	foldername = path_finder(to_go, foldername, goal);
	if (!foldername)
		return (NULL);
	return (foldername);
}

int	foldername_loop(char **foldername, char **new_path)
{
	char	*tmp;

	if (*foldername && ft_strchr(*foldername, '/'))
	{
		while (*foldername && ft_strchr(*foldername, '/'))
		{
			tmp = *foldername;
			*foldername = find_new_pwd(*foldername, new_path);
			free(tmp);
			if (!*foldername)
				return (0);
			if (!ft_strchr(*foldername, '/'))
			{
				free(*foldername);
				return (1);
			}
		}
	}
	else
		free(*foldername);
	return (1);
}

int	slash_path(char **foldername, char **new_path)
{
	char	*tmp;

	free(*new_path);
	*new_path = ft_strdup("/");
	if (!new_path)
		return (0);
	tmp = *foldername;
	*foldername = ft_strtrim(*foldername, "/");
	if (!*foldername)
		return (0);
	free(tmp);
	return (1);
}

int	new_pwd(char *foldername, char **new_path)
{
	char	*tmp;

	if (!foldername)
		return (0);
	if (foldername[0] == '/')
		if (!slash_path(&foldername, new_path))
			return (0);
	if (ft_strlen(foldername) > 0
		&& foldername[ft_strlen(foldername) - 1] != '/')
	{
		tmp = foldername;
		foldername = ft_strjoin(foldername, "/");
		free(tmp);
		if (!foldername)
			return (0);
	}
	if (!foldername_loop(&foldername, new_path))
		return (0);
	return (1);
}
