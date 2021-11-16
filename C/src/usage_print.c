/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:05:59 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/16 19:06:50 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	examples_print(void)
{
	ft_printf("\n\n Examples:\n");
	ft_printf("\n   1:\n");
	ft_printf("    ./dslr TRAIN data/dataset_train.csv\n");
	ft_printf("\n   2:\n");
	ft_printf("    ./dslr TEST data/dataset_test.csv\n");
	return ;
}

void	usage_print(void)
{
	ft_printf("Usage:\n");
	ft_printf("  ./dslr <mode> <input file>\n");
	examples_print();
	ft_printf("\n\nMandatory parameter:\n");
	ft_printf("  <mode>                    TRAIN --> Training phase\n");
	ft_printf("                            TEST --> Test phase\n");
	ft_printf("  <input file>              "
		"A file with data for learning or test phases\n");
	ft_printf("Optional parameter:\n");
	ft_printf("  -S                        Send data to an influxdb\n");
	ft_printf("  -I <iter loops>           Number of iteration loops\n");
	ft_printf("  -A <learning rate>        Learning rate\n");
	ft_printf("  -h                        Help printout\n");
	ft_printf("  -l                        %s\n",
		"Print leaks. Only in MAC-OS");
	exit(42);
}
