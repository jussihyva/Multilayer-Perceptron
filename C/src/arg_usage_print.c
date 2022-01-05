/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_usage_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 19:05:59 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/05 22:17:30 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	examples_training(void)
{
	ft_printf("\n\n Examples:\n");
	ft_printf("\n   1:\n");
	ft_printf("    ./training ../Data/data.csv\n");
	ft_printf("\n   2:\n");
	ft_printf("    ./training -E 2000 -A 0.2 ../Data/data.csv\n");
	ft_printf("\n   3:\n");
	ft_printf("    ./training -E 2000 -s E70 ../Data/data.csv\n");
	return ;
}

static void	additional_info(void)
{
	ft_printf("<dataset_split_mode>\n");
	ft_printf("  Bxx --> B specify that xx percentages of dataset records "
		"(from the begin of the file) are used for TRAIN dataset and the rest "
		"for TEST dataset.\n");
	ft_printf("  Exx --> E specify that xx percentages of dataset records "
		"(from the end of the file) are used for TRAIN dataset and the rest "
		"for TEST dataset.\n");
	ft_printf("  Rxx --> R specify that xx percentages of dataset records "
		"(randomly selected) are used for TRAIN dataset and the rest for "
		"TEST dataset.\n");
	ft_printf("  xx --> Value between 0 <= xx <= 100.\n");
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
	ft_printf("  -E <num of epochs>        Number of epochs\n");
	ft_printf("  -A <learning rate>        Learning rate\n");
	ft_printf("  -M <number of layers>     Number of layers in neural network (2-5)\n");
	ft_printf("  -s <dataset_split_mode>   Split input dataset file to \
TRAIN and TEST parts\n");
	ft_printf("  -w <weight init mode>     Set init values for weight matrix \
0->ZERO and 1->RAND\n");
	ft_printf("  -h                        Help printout\n");
	ft_printf("  -l                        %s\n",
		"Print leaks. Only in MAC-OS");
	additional_info();
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
		"A file with data for predict.\n");
	ft_printf("Optional parameter:\n");
	ft_printf("  -h                        Help printout\n");
	ft_printf("  -l                        %s\n",
		"Print leaks. Only in MAC-OS");
	exit(42);
}
