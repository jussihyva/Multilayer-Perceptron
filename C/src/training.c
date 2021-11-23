/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:23:11 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/23 10:22:22 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// while [ condition ]; do time ./training ; done

#include "multilayer_perceptron.h"

int	main(int argc, char **argv)
{
	t_prediction			*prediction;
	t_grad_descent_attr		*grad_descent_attr;

	prediction = prediction_init(argc, (const char *const *)argv);
	grad_descent_attr = prediction->grad_descent_attr;
	if (grad_descent_attr)
	{
		grad_descent_attr->influxdb_connection
			= ft_influxdb_connect("127.0.0.1", "8086", E_TLS);
		grad_descent(grad_descent_attr);
	}
	main_remove(&prediction, "training");
	return (0);
}
