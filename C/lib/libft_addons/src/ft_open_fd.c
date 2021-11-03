/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 17:18:39 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/02 17:52:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

int	ft_open_fd(const char *const file_path)
{
	int		fd;

	fd = 0;
	if (file_path)
	{
		fd = open(file_path, O_RDONLY);
		if (fd == -1)
		{
			ft_printf("%s (%s) failed! errno=%d. %s: %s\n",
				"Opening of a file", file_path, errno, "Detail info",
				strerror(errno));
			exit(42);
		}
	}
	return (fd);
}
