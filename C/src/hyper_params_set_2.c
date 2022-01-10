/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params_set_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:36:10 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/10 17:36:22 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

double	set_learning_rate(const t_argc_argv *const argc_argv)
{
	const char		*arg;
	char			*endptr;
	double			learning_rate;

	errno = 0;
	arg = argc_argv->argv[argc_argv->i];
	learning_rate = strtod(arg, &endptr);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -A is not valid");
	if (learning_rate > 1)
		FT_LOG_ERROR("Maximum value for learning rate (-A) is 1");
	if (learning_rate <= 0)
		FT_LOG_ERROR("Minimum value for learning rate (-A) is >0");
	return (learning_rate);
}
