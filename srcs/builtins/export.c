/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdkhissi <mdkhissi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 20:27:42 by tmoragli          #+#    #+#             */
/*   Updated: 2022/08/03 00:34:13 by mdkhissi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_data *data, int ac, char **av)
{
	int	i;
	int	*lens_id;

	if (ac == 1)
		return (export_display(data->env_str));
	lens_id = malloc(ac * sizeof(int));
	if (!lens_id)
		msh_exit(data, 1);
	ft_fill_iarr(lens_id, -2, ac);
	av[0] = ft_str_zero(av[0]);
	ac--;
	i = 0;
	while (data->env_str && data->env_str[i])
	{
		data->env_str[i] = export_worker(data->env_str[i], av, &ac, lens_id);
		i++;
	}
	if (ac > 0)
		data->env_str = str_arr_add(data->env_str, i, av, ac);
	return (0);
}

char	*export_worker(char *env_entry, char **av, int *ac, int *lens_id)
{
	int	j;
	int	valid;

	j = -1;
	while (av[++j])
	{
		if (av[j][0])
		{
			if (lens_id[j] == -2)
				lens_id[j] = get_id_len(av[j]);
			valid = is_validid(av[j], lens_id[j]);
			if (lens_id[j] > 0 && valid)
			{
				env_entry = compare_replace(env_entry, &av[j], lens_id[j]);
				if (!av[j][0])
					*ac -= 1;
			}
			if (!valid)
				av[j] = export_error(av[j], ac);
			if (lens_id[j] < 0 && valid)
				av[j] = ft_str_zero(av[j]) + 0 * (*ac)--;
		}
	}
	return (env_entry);
}

char	*compare_replace(char *env_entry, char **entry, int len_id)
{
	char	*p_entry;

	p_entry = *entry;
	if (!ft_strncmp(env_entry, p_entry, len_id)
		&& (p_entry[len_id] == '+' || p_entry[len_id] == '='))
	{
		env_entry = replace_env_entry(env_entry,
				len_id, p_entry);
		p_entry = ft_str_zero(p_entry);
	}
	*entry = p_entry;
	return (env_entry);
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
