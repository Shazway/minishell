/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 23:12:42 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/27 23:12:50 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		free(path);
		return (ft_strdup("/"));
	}
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
	while (foldername && foldername[i] && foldername[i] != '/')
		i++;
	if (!foldername[i] || !foldername[i + 1])
		return (ft_strdup(""));
	if (foldername[i] == '/')
		i++;
	foldername = ft_substr(foldername, i, ft_strlen(foldername));
	return (foldername);
}
