/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bias_weigth_values_save.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 10:40:09 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/19 13:26:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

static size_t	weight_values_add(
						t_queue *const queue,
						const double *const weight_row,
						const size_t columns)
{
	size_t		string_length;
	char		*substring;
	size_t		i;

	string_length = 0;
	i = -1;
	while (++i < columns)
	{
		ft_enqueue(queue, (void *)ft_strdup(","));
		string_length++;
		substring = ft_strnew(SUB_STRING_MAX_LENGTH);
		ft_sprintf(substring, "%f", weight_row[i]);
		ft_enqueue(queue, (void *)substring);
		string_length += ft_strlen(substring);
	}
	return (string_length);
}

static const char	*strings_merge(
							t_queue *const queue,
							const size_t string_length)
{
	char		*str;
	const char	*substring;

	str = ft_strnew(string_length);
	while (!ft_is_queue_empty(queue))
	{
		substring = (char *)ft_dequeue(queue);
		ft_strcat(str, substring);
		ft_strdel((char **)&substring);
	}
	return (str);
}

static const char	*yaml_string_create(
							const double *const weight_row,
							const double bias,
							const size_t columns)
{
	t_queue		*queue;
	char		*substring;
	size_t		string_length;
	const char	*str;

	queue = ft_queue_init();
	string_length = 0;
	substring = ft_strnew(SUB_STRING_MAX_LENGTH);
	ft_sprintf(substring, "%f", bias);
	ft_enqueue(queue, (void *)substring);
	string_length += ft_strlen(substring);
	string_length += weight_values_add(queue, weight_row, columns);
	ft_enqueue(queue, (void *)ft_strdup("\n"));
	string_length++;
	str = strings_merge(queue, string_length);
	ft_queue_remove(&queue);
	return (str);
}

void	bias_weigth_values_save(
						const t_vector *const bias,
						const t_matrix *const weight,
						const char *const weight_bias_file)
{
	const char		*write_buf;
	int				fd;
	ssize_t			ret;
	size_t			i;

	if (ft_logging_level() <= LOG_INFO)
	{
		ml_matrix_print("WEIGHT", weight);
		ml_vector_print("BIAS", bias);
	}
	remove(weight_bias_file);
	fd = open(weight_bias_file, O_CREAT | O_RDWR, S_IWUSR | S_IRUSR);
	i = -1;
	while (++i < weight->size.rows)
	{
		write_buf = yaml_string_create(((double **)weight->table)[i],
				((double *)bias->data)[i], weight->size.cols);
		ret = write(fd, write_buf, ft_strlen(write_buf));
		ft_strdel((char **)&write_buf);
	}
	ret = close(fd);
	return ;
}
