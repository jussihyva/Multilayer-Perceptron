/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 17:32:58 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/10 17:34:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_weight_init_mode	set_weight_init_mode(const t_argc_argv *const argc_argv)
{
	t_weight_init_mode		weight_init_mode;
	const char				*arg;

	weight_init_mode = E_ZERO;
	arg = argc_argv->argv[argc_argv->i];
	if (ft_strequ(arg, "0"))
		weight_init_mode = E_ZERO;
	else if (ft_strequ(arg, "1"))
		weight_init_mode = E_RAND_0_TO_1;
	else
		FT_LOG_ERROR("Weight mode %s is not supported.", arg);
	return (weight_init_mode);
}

static t_split_mode	set_mode(const char mode_char)
{
	t_split_mode	split_mode;

	split_mode = 0;
	if (mode_char == 'B')
		split_mode = E_BEGIN;
	else if (mode_char == 'E')
		split_mode = E_END;
	else if (mode_char == 'R')
		split_mode = E_RAND;
	else
		FT_LOG_ERROR("Split mode %c is not supported.", mode_char);
	return (split_mode);
}

const t_split_order	*set_split_mode(
						const t_argc_argv *const argc_argv,
						t_split_order *const split_order)
{
	const char			*arg;
	char				*endptr;
	char				mode_char;

	arg = argc_argv->argv[argc_argv->i];
	mode_char = *arg;
	arg++;
	split_order->split_mode = set_mode(mode_char);
	errno = 0;
	split_order->extra_info = strtoul(arg, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -s is not valid");
	else if (split_order->extra_info > 100)
		FT_LOG_ERROR("Maximum value for split mode (-s) is 100");
	return (split_order);
}

size_t	set_num_of_epochs(const t_argc_argv *const argc_argv)
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

size_t	set_num_of_layers(const t_argc_argv *const argc_argv)
{
	const char		*arg;
	char			*endptr;
	size_t			num_of_layers;

	errno = 0;
	arg = argc_argv->argv[argc_argv->i];
	num_of_layers = ft_strtoi(arg, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -E is not valid");
	if (num_of_layers > 5)
		FT_LOG_ERROR("Maximum number of layers (-M) is 5");
	if (num_of_layers < 2)
		FT_LOG_ERROR("Minimum number of layers (-M) is 2");
	return (num_of_layers);
}
