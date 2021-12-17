/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:37:31 by juhani            #+#    #+#             */
/*   Updated: 2021/12/17 16:27:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

t_weigth_init_mode	set_weigth_init_mode(const t_argc_argv *const argc_argv)
{
	t_weigth_init_mode		weigth_init_mode;
	const char				*arg;

	weigth_init_mode = 0;
	arg = argc_argv->argv[argc_argv->i];
	if (ft_strequ(arg, "0"))
		weigth_init_mode = E_ZERO;
	else if (ft_strequ(arg, "1"))
		weigth_init_mode = E_RAND_0_TO_1;
	else
		FT_LOG_ERROR("Weigth mode %s is not supported.", arg);
	return (weigth_init_mode);
}

static t_dataset_split_mode	set_split_mode(const char mode_char)
{
	t_dataset_split_mode	dataset_split_mode;

	dataset_split_mode = 0;
	if (mode_char == 'B')
		dataset_split_mode = E_BEGIN;
	else if (mode_char == 'E')
		dataset_split_mode = E_END;
	else if (mode_char == 'R')
		dataset_split_mode = E_RAND;
	else
		FT_LOG_ERROR("Split mode %c is not supported.", mode_char);
	return (dataset_split_mode);
}

const t_dataset_split_order	*set_dataset_split_mode(
								const t_argc_argv *const argc_argv)
{
	const char				*arg;
	char					*endptr;
	t_dataset_split_order	*dataset_split_order;
	char					mode_char;

	dataset_split_order = ft_memalloc(sizeof(*dataset_split_order));
	arg = argc_argv->argv[argc_argv->i];
	mode_char = *arg;
	arg++;
	dataset_split_order->dataset_split_mode = set_split_mode(mode_char);
	errno = 0;
	dataset_split_order->extra_info = strtoul(arg, &endptr, 10);
	if (errno != 0 || *endptr != '\0')
		FT_LOG_ERROR("Value of param -s is not valid");
	else if (dataset_split_order->extra_info > 100)
		FT_LOG_ERROR("Maximum value for split mode (-s) is 100");
	return (dataset_split_order);
}

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
