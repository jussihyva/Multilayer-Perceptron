/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_usage_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:05:59 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/18 12:33:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	examples_training(void)
{
	ft_printf("\n\n Examples:\n");
	ft_printf("\n   1:\n");
	ft_printf("    ./training ../Data/data.csv\n");
	return ;
}

void	arg_usage_training(void)
{
	ft_printf("Usage:\n");
	ft_printf("  ./training <input file>\n");
	examples_training();
	ft_printf("\n\nMandatory parameter:\n");
	ft_printf("  <input file>              "
		"A file with data for learning a ML model.\n");
	ft_printf("Optional parameter:\n");
	ft_printf("  -S                        Send data to an influxdb\n");
	ft_printf("  -I <iter loops>           Number of iteration loops\n");
	ft_printf("  -A <learning rate>        Learning rate\n");
	ft_printf("  -h                        Help printout\n");
	ft_printf("  -l                        %s\n",
		"Print leaks. Only in MAC-OS");
	exit(42);
}

static void	examples_prediction(void)
{
	ft_printf("\n\n Examples:\n");
	ft_printf("\n   1:\n");
	ft_printf("    ./prediction ../Data/data.csv\n");
	return ;
}

void	arg_usage_prediction(void)
{
	ft_printf("Usage:\n");
	ft_printf("  ./prediction <input file>\n");
	examples_prediction();
	ft_printf("\n\nMandatory parameter:\n");
	ft_printf("  <input file>              "
		"A file with data for learning a ML model.\n");
	ft_printf("Optional parameter:\n");
	ft_printf("  -S                        Send data to an influxdb\n");
	ft_printf("  -I <iter loops>           Number of iteration loops\n");
	ft_printf("  -A <learning rate>        Learning rate\n");
	ft_printf("  -h                        Help printout\n");
	ft_printf("  -l                        %s\n",
		"Print leaks. Only in MAC-OS");
	exit(42);
}
