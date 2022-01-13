/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_remove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 20:29:55 by juhani            #+#    #+#             */
/*   Updated: 2022/01/13 11:37:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	layer_remove_input(t_layer_input **layer)
{
	ml_matrix_remove((t_matrix **)&(*layer)->a_test);
	ml_matrix_remove((t_matrix **)&(*layer)->a_train);
	ft_memdel((void **)layer);
	return ;
}

void	layer_remove_hidden(t_layer_hidden **layer)
{
	ml_matrix_remove((t_matrix **)&(*layer)->weight_bias.weight);
	ml_matrix_remove((t_matrix **)&(*layer)->g_prime);
	ml_matrix_remove((t_matrix **)&(*layer)->d_z);
	ml_matrix_remove((t_matrix **)&(*layer)->a_test);
	ml_matrix_remove((t_matrix **)&(*layer)->a_train);
	ml_matrix_remove((t_matrix **)&(*layer)->z_test);
	ml_matrix_remove((t_matrix **)&(*layer)->z_train);
	ml_matrix_remove((t_matrix **)&(*layer)->weight_transposed);
	ml_matrix_remove((t_matrix **)&(*layer)->weight_bias.weight);
	ml_vector_remove((t_vector **)&(*layer)->weight_bias.bias);
	ml_matrix_remove((t_matrix **)&(*layer)->d_weight_bias.weight);
	ml_vector_remove((t_vector **)&(*layer)->d_weight_bias.bias);
	ft_memdel((void **)layer);
	return ;
}

void	layer_remove_output(t_layer_output **layer)
{
	ml_matrix_remove((t_matrix **)&(*layer)->weight_bias.weight);
	ml_vector_remove((t_vector **)&(*layer)->cost[0]);
	ml_vector_remove((t_vector **)&(*layer)->cost[1]);
	ml_matrix_remove((t_matrix **)&(*layer)->d_z);
	ml_matrix_remove((t_matrix **)&(*layer)->y_hat_test);
	ml_matrix_remove((t_matrix **)&(*layer)->y_hat_train);
	ml_matrix_remove((t_matrix **)&(*layer)->z_test);
	ml_matrix_remove((t_matrix **)&(*layer)->z_train);
	ml_matrix_remove((t_matrix **)&(*layer)->weight_bias.weight);
	ml_vector_remove((t_vector **)&(*layer)->weight_bias.bias);
	ml_matrix_remove((t_matrix **)&(*layer)->d_weight_bias.weight);
	ml_vector_remove((t_vector **)&(*layer)->d_weight_bias.bias);
	ml_matrix_remove((t_matrix **)&(*layer)->softmax);
	ml_vector_remove((t_vector **)&(*layer)->argmax);
	ml_vector_remove((t_vector **)&(*layer)->argmax_values);
	ft_memdel((void **)layer);
	return ;
}
