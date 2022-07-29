/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmoragli <tmoragli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:18:23 by tmoragli          #+#    #+#             */
/*   Updated: 2022/07/29 23:50:51 by tmoragli         ###   ########.fr       */
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

int	is_dash(char *str)
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

void	swap_paths(t_data *data)
{
	char	*tmp;

	tmp = data->old_path;
	data->old_path = data->relative_path;
	data->relative_path = tmp;
}

int	cd_dash(char *arg, t_data *data)
{
	int		ret;

	ret = is_dash(arg);
	free(arg);
	if (ret == -1)
	{
		ft_putstr_fd("minishell: --: invalid option\n", 2);
		return (2);
	}
	if (ret == 1)
	{
		ft_printf("%s\n", data->old_path);
		return (cd_home(ft_strdup(data->old_path), "OLDPWD", data));
	}
	if (ret == 2)
		return (cd_home(get_var("HOME", data), "HOME", data));
	return (-1);
}
