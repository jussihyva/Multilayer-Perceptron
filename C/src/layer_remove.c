/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:29:55 by juhani            #+#    #+#             */
/*   Updated: 2021/12/13 11:39:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	layer_remove_input(const t_layer_input **const layer)
{
	ml_matrix_remove((t_matrix **)&(*layer)->a);
	ft_memdel((void **)layer);
	return ;
}

void	layer_remove_hidden(const t_layer_hidden **const layer)
{
	ml_matrix_remove((t_matrix **)&(*layer)->weight_bias.weight);
	ml_matrix_remove((t_matrix **)&(*layer)->g_prime);
	ml_matrix_remove((t_matrix **)&(*layer)->d_z);
	ml_matrix_remove((t_matrix **)&(*layer)->a);
	ml_matrix_remove((t_matrix **)&(*layer)->z);
	ml_matrix_remove((t_matrix **)&(*layer)->weight_transposed);
	ml_matrix_remove((t_matrix **)&(*layer)->weight_bias.weight);
	ml_vector_remove((t_vector **)&(*layer)->weight_bias.bias);
	ml_matrix_remove((t_matrix **)&(*layer)->d_weight_bias.weight);
	ml_vector_remove((t_vector **)&(*layer)->d_weight_bias.bias);
	ft_memdel((void **)layer);
	return ;
}

void	layer_remove_output(const t_layer_output **const layer)
{
	ml_matrix_remove((t_matrix **)&(*layer)->weight_bias.weight);
	ml_vector_remove((t_vector **)&(*layer)->cost);
	ml_matrix_remove((t_matrix **)&(*layer)->d_z);
	ml_matrix_remove((t_matrix **)&(*layer)->y_hat);
	ml_matrix_remove((t_matrix **)&(*layer)->z);
	ml_matrix_remove((t_matrix **)&(*layer)->weight_bias.weight);
	ml_vector_remove((t_vector **)&(*layer)->weight_bias.bias);
	ml_matrix_remove((t_matrix **)&(*layer)->d_weight_bias.weight);
	ml_vector_remove((t_vector **)&(*layer)->d_weight_bias.bias);
	ft_memdel((void **)layer);
	return ;
}
