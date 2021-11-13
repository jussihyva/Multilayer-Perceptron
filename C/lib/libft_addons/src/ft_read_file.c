/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:37:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/13 20:24:50 by jkauppi          ###   ########.fr       */
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
		array = ft_strsplit_ex(read_attributes->line, ',', &len, E_TRUE);
		ft_strdel(&read_attributes->line);
		add_array_to_queue(array, queue);
		read_attributes->ret = ft_get_next_line(read_attributes->fd,
				&read_attributes->line);
	}
	if (read_attributes->ret < 0)
		read_failure = E_TRUE;
	ft_strdel(&read_attributes->line);
	return (read_failure);
}

static const char	***move_rows_from_queue_to_array(t_queue *queue)
{
	const char		***array;
	size_t			i;

	array = ft_memalloc(sizeof(*array) * queue->len);
	i = 0;
	while (!ft_is_queue_empty(queue))
	{
		array[i] = (const char **)ft_dequeue(queue);
		i++;
	}
	return (array);
}

t_file_attributes	*ft_read_file(
							const char *const file_path,
							const t_file_type file_type)
{
	t_file_attributes		*file_attributes;
	t_read_attributes		*read_attributes;
	t_queue					*queue;

	read_attributes = ft_memalloc(sizeof(*read_attributes));
	file_attributes = ft_memalloc(sizeof(*file_attributes));
	file_attributes->file_type = file_type;
	queue = ft_queue_init();
	read_attributes->fd = ft_open_fd(file_path);
	if (read_attributes->fd && file_type == E_CSV)
		file_attributes->read_failure = read_csv_file(read_attributes, queue);
	else
		file_attributes->read_failure = E_TRUE;
	file_attributes->rows = queue->len;
	file_attributes->row_array = move_rows_from_queue_to_array(queue);
	ft_queue_remove(&queue);
	ft_memdel((void **)&read_attributes);
	return (file_attributes);
}
