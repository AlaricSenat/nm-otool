/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_symbols.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/25 12:40:11 by asenat            #+#    #+#             */
/*   Updated: 2018/10/10 15:10:10 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm/nm.h"
#include "common/common.h"
#include "libft/output/obuff.h"

static void		free_machodata(t_macho_data *mdata)
{
	t_segment	*seg;
	uint32_t	i;

	i = 0;
	while (i < mdata->symbols->nelems)
		free(*((t_symbol**)mdata->symbols->begin + i++));
	ft_memdel(&mdata->symbols->begin);
	while (mdata->segments)
	{
		free(mdata->segments->sections.begin);
		seg = mdata->segments->next;
		free(mdata->segments);
		mdata->segments = seg;
	}
}

static uint8_t	parse_command(const t_command *command, const t_map *map,
					t_macho_data *mdata)
{
	uint32_t command_id;

	command_id = get_uint32(command->cmd, map->type.endian);
	if (command_id == LC_SEGMENT || command_id == LC_SEGMENT_64)
	{
		return (get_sections((const t_segcommand*)command,
					map, &mdata->segments));
	}
	if (command_id == LC_SYMTAB)
	{
		return (get_static_symbols((const t_symcommand*)command,
					map, mdata->symbols));
	}
	return (1);
}

static uint8_t	parse_macho(t_opt opt, const t_map *map, t_macho_data *mdata)
{
	const t_header64	*header;
	const t_command		*command;
	size_t				shift;
	uint32_t			i;

	header = (const t_header64*)map->addr;
	shift = get_struct_size(HEADER, map->type.mtype);
	i = 0;
	(void)opt;
	while (i <= get_uint32(header->ncmds, map->type.endian))
	{
		if (!(command = (const t_command*)safe_access(map->addr, shift,
			get_uint32(header->sizeofcmds, map->type.endian)
			+ get_struct_size(HEADER, map->type.mtype))))
			return (0);
		if (!parse_command(command, map, mdata))
		{
			free_machodata(mdata);
			return (0);
		}
		shift += get_uint32(command->cmdsize, map->type.endian);
		++i;
	}
	return (1);
}

static void		display_symbols(t_opt opt, const t_macho_data *data,
					t_type type)
{
	size_t			i;
	t_obuff			obuff;
	const t_symbol	**sym;

	i = 0;
	(void)opt;
	obuff = (t_obuff){.cursor = 0, .fd = 1};
	while (i < data->symbols->nelems)
	{
		sym = (const t_symbol**)data->symbols->begin + i;
		if ((*sym)->name)
		{
			add_value_to_obuff((*sym)->value, type.mtype,
					(*sym)->nlist, &obuff);
			ft_add_char_to_obuff(' ', &obuff);
			add_type_to_obuff((*sym), data->segments, &obuff);
			ft_add_char_to_obuff(' ', &obuff);
			ft_add_str_to_obuff((*sym)->name, &obuff);
			ft_add_char_to_obuff('\n', &obuff);
			ft_flush_obuff(&obuff);
		}
		++i;
	}
	ft_flush_obuff(&obuff);
}

uint8_t			get_and_display_symbols(t_opt opt, const t_map *map)
{
	t_array			symbols;
	t_macho_data	mdata;

	(void)opt;
	symbols = (t_array){0, sizeof(t_symbol*), NULL};
	mdata = (t_macho_data){&symbols, NULL};
	if (map->type.mtype == NONE)
		return (0);
	if (!parse_macho(opt, map, &mdata))
		return (0);
	sort_symbols(&symbols);
	display_symbols(opt, &mdata, map->type);
	free_machodata(&mdata);
	return (1);
}
