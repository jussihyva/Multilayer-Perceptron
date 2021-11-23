/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:31 by juhani            #+#    #+#             */
/*   Updated: 2021/11/23 15:21:22 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

size_t	set_number_of_epochs(const t_argc_argv *const argc_argv)
{
	const char		*arg;
	char			*endptr;
	size_t			epochs;

	errno = 0;
	arg = argc_argv->argv[argc_argv->i];
	epochs = ft_strtoi(arg, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -E is not valid");
	if (epochs > 100000)
		FT_LOG_ERROR("Maximum value for epochs (-E) is "
			"100000 (100 thousand)");
	if (epochs <= 0)
		FT_LOG_ERROR("Minimum value for epochs (-E) is >0");
	return (epochs);
}

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
