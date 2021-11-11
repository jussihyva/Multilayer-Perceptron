/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:37:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/11 14:25:53 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

static void	add_array_to_queue(
						const char *const *const array,
						t_queue *const queue)
{
	ft_enqueue(queue, (void *)array);
	return ;
}

static t_bool	read_csv_file(
						t_read_attributes *const read_attributes,
						t_queue *const queue)
{
	t_bool			read_failure;
	size_t			len;
	const char		**array;

	read_failure = E_FALSE;
	read_attributes->ret = ft_get_next_line(read_attributes->fd,
			&read_attributes->line);
	while (read_attributes->ret > 0)
	{
		read_attributes->rows++;
		// ft_printf("%3d: %s\n", read_attributes->rows,
		// 	read_attributes->line);
		array = ft_strsplit_ex(read_attributes->line, ',', &len, E_TRUE);
		add_array_to_queue(array, queue);
		read_attributes->ret = ft_get_next_line(read_attributes->fd,
				&read_attributes->line);
	}
	if (read_attributes->ret < 0)
		read_failure = E_TRUE;
	return (read_failure);
}

t_read_attributes	*ft_read_file(
							const char *const file_path,
							const t_file_type file_type)
{
	t_read_attributes		*read_attributes;
	t_queue					*queue;
	size_t					i;

	read_attributes = ft_memalloc(sizeof(*read_attributes));
	read_attributes->file_type = file_type;
	queue = ft_queue_init();
	read_attributes->fd = ft_open_fd(file_path);
	if (read_attributes->fd && file_type == E_CSV)
		read_attributes->read_failure = read_csv_file(read_attributes, queue);
	else
		read_attributes->read_failure = E_TRUE;
	read_attributes->row_array = ft_memalloc(sizeof(*read_attributes->row_array)
			* read_attributes->rows);
	i = 0;
	while (!ft_is_queue_empty(queue))
	{
		read_attributes->row_array[i] = (const char **)ft_dequeue(queue);
		// ft_strarray_print(read_attributes->row_array[i]);
		i++;
	}
	ft_queue_remove(&queue);
	return (read_attributes);
}
