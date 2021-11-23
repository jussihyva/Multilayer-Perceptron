/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_parser_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhani <juhani@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:22:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/23 12:58:57 by juhani           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

t_arg_parser	*ft_arg_parser_init(
							t_argc_argv *const argc_argv,
							t_arg_init fn_arg_init,
							t_arg_analyze fn_arg_analyze,
							t_usage_print fn_usage_print)
{
	t_arg_parser	*arg_parser;

	arg_parser = ft_memalloc(sizeof(*arg_parser));
	arg_parser->argc_argv = argc_argv;
	arg_parser->fn_arg_init = fn_arg_init;
	arg_parser->fn_arg_analyze = fn_arg_analyze;
	arg_parser->fn_usage_print = fn_usage_print;
	return (arg_parser);
}
