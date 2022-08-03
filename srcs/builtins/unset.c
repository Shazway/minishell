/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:56 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/04 00:36:06 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_to_del(t_data *data, char **av, char **to_del, int *j)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	while (av && av[i])
	{
		if (is_validid(av[i], ft_strlen(av[i])))
		{
			to_del[*j] = ft_strjoin(av[i], "=");
			if (!to_del[*j])
			{
				str_arr_free(to_del);
				msh_exit(data, 1);
			}
			*j += 1;
		}
		else
			ft_printf("minishell: unset: `%s': not a valid identifier\n",
				av[i + 0 * ret++]);
		i++;
	}
	to_del[*j] = NULL;
	return (ret);
}

int	ft_unset(t_data *data, int ac, char **av)
{
	char	**to_del;
	int		j;
	int		ret;

	j = 0;
	ret = 0;
	to_del = malloc(ac * sizeof(char *));
	if (!to_del)
		msh_exit(data, 1);
	ret = setup_to_del(data, av, to_del, &j);
	data->env_str = str_arr_del(data->env_str, to_del, j);
	str_arr_free(to_del);
	if (!data->env_str)
		msh_exit(data, 1);
	return (ret);
}
