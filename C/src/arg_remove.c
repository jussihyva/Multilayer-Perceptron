/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 10:30:33 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/18 16:09:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	arg_remove(const t_cmd_args **cmd_args)
{
	ft_logging_release(
		(const t_logging_data **const) &(*cmd_args)->logging_data);
	ft_strdel((char **)&(*cmd_args)->dataset_file);
	ft_strdel((char **)&(*cmd_args)->weight_bias_file);
	ft_memdel((void **)cmd_args);
	return ;
}
