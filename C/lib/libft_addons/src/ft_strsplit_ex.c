/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_ex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 13:01:33 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/11 13:05:50 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static size_t	count_number_of_values(const char *str, const char delim)
{
	size_t	number_of_values;

	number_of_values = 0;
	if (*str)
		number_of_values++;
	while (*str)
	{
		if (*str == delim)
			number_of_values++;
		str++;
	}
	return (number_of_values);
}

static char	*read_value(
					const char *start_ptr,
					const char *end_ptr,
					t_bool do_trim)
{
	char	*value;
	char	*prel_value;

	if (start_ptr == end_ptr)
		value = ft_strdup("");
	else
	{
		prel_value = ft_strsub(start_ptr, 0, end_ptr - start_ptr);
		if (do_trim)
		{
			value = ft_strtrim(prel_value);
			ft_strdel(&prel_value);
		}
		else
			value = prel_value;
	}
	return (value);
}

static void	parse_and_save_values(
							const char *const str,
							const char delim,
							char **value_array,
							t_bool do_trim)
{
	const char		*start_ptr;
	const char		*end_ptr;
	size_t			i;

	start_ptr = str;
	end_ptr = str;
	i = 0;
	while (*end_ptr)
	{
		if (*end_ptr == delim)
		{
			value_array[i++] = read_value(start_ptr, end_ptr, do_trim);
			start_ptr = end_ptr + 1;
		}
		end_ptr++;
	}
	if (str != end_ptr)
		value_array[i++] = read_value(start_ptr, end_ptr, do_trim);
	return ;
}

const char	**ft_strsplit_ex(
					const char *const str,
					const char delim,
					size_t *const number_of_values,
					t_bool do_trim)
{
	char		**value_array;

	*number_of_values = count_number_of_values(str, delim);
	value_array = ft_memalloc(sizeof(*value_array) * (*number_of_values + 1));
	parse_and_save_values(str, delim, value_array, do_trim);
	return ((const char **)value_array);
}
