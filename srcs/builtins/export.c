/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:42 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/03 18:17:39 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_data *data, int ac, char **av)
{
	int	i;
	int	len_id;
	int	valid;

	if (ac == 1)
		return (export_display(data->env_str));
	i = 1;
	while (av && av[i])
	{
		len_id = get_id_len(av[i]);
		valid = is_validid(av[i], len_id);
		if (len_id > 0 && valid)
		{
			data->env_str = update_env(data->env_str, av[i], len_id);
			if (!data->env_str)
				msh_exit(data, 1);
		}
		if (!valid)
		{
			ft_printf("minishell: export: `%s': not a valid identifier\n",
				av[i]);
		}
		i++;
	}
	return (0);
}

char	**update_env(char **envr, char *entry, int len_id)
{
	int		i;
	char	**new;

	i = 0;
	while (envr && envr[i])
	{
		if (!ft_strncmp(envr[i], entry, len_id)
			&& (envr[i][len_id] == '+' || envr[i][len_id] == '='))
		{
			envr[i] = replace_env_entry(envr[i],
					len_id, entry);
			if (!envr[i])
				return (str_arr_free(envr));
			return (envr);
		}
		i++;
	}
	new = str_arr_add(envr, i, NULL, 1);
	if (!new)
		return (str_arr_free(envr));
	new[i] = new_entry(entry, len_id);
	if (!new[i])
		return (ft_free_sars(&new, &envr, NULL, NULL));
	return (new);
}

char	*new_entry(char *entry, int len_id)
{
	int		i;
	int		j;
	char	*new;
	int		len;

	len = ft_strlen(entry);
	if (entry[len_id] == '+')
		len--;
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	j = 0;
	while (entry && entry[i])
	{
		if (entry[i] != '+')
			new[j++] = entry[i];
		i++;
	}
	if (entry[len_id] == '+')
		i--;
	new[i] = '\0';
	return (new);
}

char	*replace_env_entry(char *old, int len_id, char *entry)
{
	int		len;
	char	*new;
	int		append;

	append = 0;
	if (entry[len_id] == '+')
		append = 1;
	if (append)
		len = ft_strlen(old) + ft_strlen(entry + len_id + 2);
	else
		len = ft_strlen(entry);
	new = malloc((len + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, entry, len_id + 1);
	new[len_id] = '=';
	new[len_id + 1] = '\0';
	if (append)
		ft_strcat(new, old + len_id + 1);
	ft_strcat(new, entry + len_id + 1 + 1 * (append == 1));
	free(old);
	return (new);
}

int	get_id_len(char *entry)
{
	char	*p_eq;
	int		len;
	int		append;

	append = 0;
	p_eq = ft_strchr(entry, '=');
	if (p_eq && p_eq != entry && p_eq[-1] == '+')
		append = 1;
	if (p_eq)
		len = p_eq - &entry[0];
	else
		len = -1;
	if (p_eq && append)
		len--;
	return (len);
}
