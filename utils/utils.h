/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 11:30:35 by asenat            #+#    #+#             */
/*   Updated: 2018/09/24 19:35:04 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "utils/data_structures.h"

uint8_t	open_file(const char *filename, int oflags, t_file *file);
void	close_file(t_file *file);
t_map	map_file(const t_file *file);
void	unmap_file(t_map *map, const t_file *file);

#endif
