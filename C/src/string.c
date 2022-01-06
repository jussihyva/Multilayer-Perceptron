/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 21:09:32 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/06 21:12:31 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_bool	string_convert_and_validate(
						const char *string,
						const t_data_type data_type,
						void *value)
{
	t_bool		validation_result;
	char		*endptr;

	validation_result = E_TRUE;
	if (data_type == E_SIZE_T)
	{
		errno = 0;
		*(size_t *)value = (size_t)ft_strtoi(string, &endptr, 10);
		if (errno != 0 || *endptr != '\0')
			validation_result = E_FALSE;
	}
	else if (data_type == E_DOUBLE)
	{
		errno = 0;
		*(double *)value = strtod(string, &endptr);
		if (errno != 0 || *endptr != '\0')
			validation_result = E_FALSE;
	}
	else
		validation_result = E_FALSE;
	return (validation_result);
}
