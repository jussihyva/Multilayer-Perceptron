/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_and_prediction_variable.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 10:33:51 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/19 10:58:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	width_and_prediction_variable(t_substring *substring, va_list *ap,
											int *attrs)
{
	if (substring->width == INT_MIN)
	{
		(*attrs)++;
		substring->width = (int)va_arg(*ap, int);
	}
	if (substring->precision == INT_MIN)
	{
		(*attrs)++;
		substring->precision = (int)va_arg(*ap, int);
	}
	return ;
}
