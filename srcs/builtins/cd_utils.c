/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:18:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/20 17:24:12 by tmoragli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_double_dash(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] == '-')
		i++;
	if (i == 2 && str[i] == '\0')
		return (2);
	if (i > 2 || (i == 2 && str[i]))
		return (-1);
	return (0);
}

int	is_dash(char	*str)
{
	int	i;
	int	ret;

	i = 0;
	ret = is_double_dash(str);
	while (str[i] && str[i] == '-')
		i++;
	if (i == 1 && str[i] == '\0')
		return (1);
	return (ret);
}

int	cd_home(char *path, char *name)
{
	if (!ft_strncmp(name, "HOME", ft_strlen("HOME")))
	{
		if (chdir(path) == -1)
			printf("minishell: cd: HOME not set\n");
		free(path);
		return (1);
	}
	if (!ft_strncmp(name, "OLDPWD", ft_strlen("OLDPWD")))
	{
		if (chdir(path) == -1)
			printf("minishell: cd: OLDPWD not set\n");
		free(path);
		return (1);
	}
	return (0);
}

int	cd_dash(char *arg, t_data *data)
{
	int		ret;
	char	*tmp;

	ret = is_dash(arg);
	free(arg);
	if (ret == -1)
		printf("minishell: --: invalid option\n");
	if (ret == 1)
	{
		tmp = ft_strdup(data->relative_path);
		printf("%s\n", tmp);
		return (cd_home(tmp, "HOME"));
	}
	if (ret == 2)
		return (cd_home(get_var("OLDPWD", data), "OLDPWD"));
	return (-1);
}
