/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_special_chars.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:15:12 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/10 13:16:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	count_special_chars(
					const char *special_chars,
					const char *const string)
{
	const char	*ptr;
	size_t		num_of_special_chars;

	num_of_special_chars = 0;
	ptr = string;
	while (*ptr)
	{
		if (ft_strchr(special_chars, *ptr))
			num_of_special_chars++;
		ptr++;
	}
	return (num_of_special_chars);
}

char	*influxdb_special_chars_conv(
					const char *const special_chars,
					const char *const string)
{
	char			*new_string;
	const char		*ptr;
	size_t			num_of_special_chars;
	size_t			i;

	num_of_special_chars = count_special_chars(special_chars, string);
	new_string = ft_strnew(ft_strlen(string) + num_of_special_chars);
	i = 0;
	ptr = string;
	while (*ptr)
	{
		if (ft_strchr(special_chars, *ptr))
			new_string[i++] = '\\';
		new_string[i++] = *ptr;
		ptr++;
	}
	return (new_string);
}
