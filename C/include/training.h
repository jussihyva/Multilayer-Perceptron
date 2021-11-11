/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 15:25:55 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/11 20:55:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRAINING_H
# define TRAINING_H
# include "libml.h"

static char		*g_dataset_file_main_column_names[12]
					= {"ID number", "Diagnosis", "Radius", "Texture",
						"Perimeter", "Area", "Smoothness", "Compactness",
						"Concavity", "Concave points", "Symmetry",
						"Fractal dimension"};
static char		*g_dataset_file_sub_column_names[3] = {"Mean", "SE", "Worst"};

t_matrix	*read_dataset(const char *const file_path);
void		file_attributes_remove(t_file_attributes **file_attributes);

#endif
