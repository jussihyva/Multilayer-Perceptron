/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   influxdb_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:24:07 by jkauppi           #+#    #+#             */
/*   Updated: 2022/01/10 13:24:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "multilayer_perceptron.h"

void	influxdb_elem_remove(t_influxdb_elem *influxdb_elem)
{
	ft_strdel((char **)&influxdb_elem->measurement);
	ft_strdel((char **)&influxdb_elem->tag_set);
	ft_strdel((char **)&influxdb_elem->field_set);
	ft_strdel((char **)&influxdb_elem->timestamp);
	return ;
}
