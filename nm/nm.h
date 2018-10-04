/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 12:33:19 by asenat            #+#    #+#             */
/*   Updated: 2018/10/04 15:09:06 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "common/data_structures.h"
# include "opt/opt.h"

# include "libft/output/obuff.h"

typedef struct 	s_symbol
{
	const char		*name;
	const t_nlist	*nlist;
	uint64_t 		value;
}				t_symbol;

typedef struct	s_macho_data
{
	t_array		*symbols;
	t_segment	*segments;
}				t_macho_data;

uint8_t	get_and_display_symbols(t_opt opt, const t_map *map);
uint8_t	get_static_symbols(const t_symcommand *cmd, const t_map *map,
			t_array *symbold);
void	add_value_to_obuff(uint64_t value, t_mtype mtype, t_obuff *obuff);
void	add_type_to_obuff(const t_nlist *nlist, const t_segment* segments,
			t_obuff *obuff);
void	add_name_to_obuff(const char *name, t_endianness e, t_obuff *obuff);
void	sort_symbols(t_array *symbols);
#endif
