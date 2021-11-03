/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_home_dir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 14:01:42 by jkauppi           #+#    #+#             */
/*   Updated: 2021/09/07 14:02:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_addons.h"

const char	*ft_home_dir(void)
{
	struct passwd	*pw;
	const char		*homedir;

	pw = getpwuid(getuid());
	homedir = pw->pw_dir;
	return (homedir);
}
