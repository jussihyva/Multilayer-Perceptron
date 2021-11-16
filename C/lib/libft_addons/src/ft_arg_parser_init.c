/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_parser_init.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 17:22:03 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/16 19:02:04 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

t_arg_parser	*ft_arg_parser_init(
							const t_argc_argv *const argc_argv,
							t_arg_init fn_arg_init,
							t_arg_analyze fn_arg_analyze,
							t_usage_print fn_usage_print)
{
	t_arg_parser	*arg_parser;

	arg_parser = ft_memalloc(sizeof(*arg_parser));
	ft_memcpy(&arg_parser->argc_argv, argc_argv, sizeof(arg_parser->argc_argv));
	arg_parser->fn_arg_init = fn_arg_init;
	arg_parser->fn_arg_analyze = fn_arg_analyze;
	arg_parser->fn_usage_print = fn_usage_print;
	arg_parser->options = ft_strdup("L:hlA:I:S");
	return (arg_parser);
}
