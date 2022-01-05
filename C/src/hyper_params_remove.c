/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyper_params_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 23:30:34 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/06 00:21:37 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	hyper_params_remove(t_hyper_params **hyper_params)
{
	ft_memdel((void **)&(*hyper_params)->activation_types);
	ft_memdel((void **)&(*hyper_params)->num_of_nodes);
	ft_memdel((void **)&(*hyper_params)->bias_weight_init_values);
	ft_memdel((void **)hyper_params);
	return ;
}
