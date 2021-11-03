/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 13:27:14 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/07 13:29:38 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

char	*ft_file_create(
					const char *const folder,
					const char *const file_name)
{
	char			*file_path;
	size_t			str_len;

	str_len = ft_strlen(folder) + 1 + ft_strlen(file_name);
	file_path = ft_memalloc(sizeof(*file_path) * (str_len + 1));
	ft_strcat(file_path, folder);
	ft_strcat(file_path, "/");
	ft_strcat(file_path, file_name);
	return (file_path);
}
