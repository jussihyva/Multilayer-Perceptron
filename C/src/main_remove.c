/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_remove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 10:19:03 by juhani            #+#    #+#             */
/*   Updated: 2021/11/23 10:21:56 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static void	arg_parser_remove(t_arg_parser **arg_parser)
{
	ft_strdel((char **)&(*arg_parser)->options);
	ft_memdel((void **)arg_parser);
	return ;
}

void	main_remove(t_prediction **prediction, const char *const prog_name)
{
	t_bool					print_leaks;
	const t_cmd_args		*cmd_args;
	t_grad_descent_attr		*grad_descent_attr;
	t_arg_parser			*arg_parser;

	cmd_args = (*prediction)->cmd_args;
	grad_descent_attr = (*prediction)->grad_descent_attr;
	arg_parser = (*prediction)->arg_parser;
	print_leaks = cmd_args->print_leaks;
	grad_descent_attr_remove(&grad_descent_attr);
	arg_remove(&cmd_args);
	arg_parser_remove(&arg_parser);
	ft_memdel((void **)prediction);
	if (print_leaks)
		ft_print_leaks(prog_name);
	return ;
}
