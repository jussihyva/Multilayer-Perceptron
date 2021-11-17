/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 11:37:52 by jkauppi           #+#    #+#             */
/*   Updated: 2021/11/17 11:37:52 by jkauppi          ###   ########.fr       */
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
						t_read_attr *const read_attr,
						t_queue *const queue)
{
	t_bool			read_failure;
	size_t			len;
	const char		**array;

	read_failure = E_FALSE;
	read_attr->ret = ft_get_next_line(read_attr->fd,
			&read_attr->line);
	while (read_attr->ret > 0)
	{
		array = ft_strsplit_ex(read_attr->line, ',', &len, E_TRUE);
		ft_strdel(&read_attr->line);
		add_array_to_queue(array, queue);
		read_attr->ret = ft_get_next_line(read_attr->fd,
				&read_attr->line);
	}
	if (read_attr->ret < 0)
		read_failure = E_TRUE;
	ft_strdel(&read_attr->line);
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

t_file_attr	*ft_read_file(
					const char *const file_path,
					const t_file_type file_type)
{
	t_file_attr		*file_attr;
	t_read_attr		*read_attr;
	t_queue			*queue;

	if (file_path)
	{
		read_attr = ft_memalloc(sizeof(*read_attr));
		file_attr = ft_memalloc(sizeof(*file_attr));
		file_attr->file_type = file_type;
		queue = ft_queue_init();
		read_attr->fd = ft_open_fd(file_path);
		if (read_attr->fd && file_type == E_CSV)
			file_attr->read_failure = read_csv_file(read_attr, queue);
		else
			file_attr->read_failure = E_TRUE;
		file_attr->rows = queue->len;
		file_attr->row_array = move_rows_from_queue_to_array(queue);
		ft_queue_remove(&queue);
		ft_memdel((void **)&read_attr);
	}
	else
		file_attr = NULL;
	return (file_attr);
}
