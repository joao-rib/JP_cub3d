/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/10 15:53:45 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*static bool	validate_path(t_game *g)
{
	char	**buff;
	bool	resp;
	int		i;

	i = 0;
	resp = false;
	buff = ft_strarrdup(g->map->layout);
	if (!buff)
		return (resp);
	flood_fill_sl(buff, g, g->map->pos_player);
	if (buff[g->map->pos_exit.y][g->map->pos_exit.x + 1] == 'F'
		|| buff[g->map->pos_exit.y][g->map->pos_exit.x - 1] == 'F'
		|| buff[g->map->pos_exit.y + 1][g->map->pos_exit.x] == 'F'
		|| buff[g->map->pos_exit.y - 1][g->map->pos_exit.x] == 'F')
		resp = true;
	if (g->coins != g->map->num_coins)
		resp = false;
	while (buff[i] != NULL)
	{
		free(buff[i]);
		i++;
	}
	free(buff);
	return (resp);
}*/

static bool	validate_chars(t_game *g)
{
	t_point	pos;

	pos.y = 1;
	while (pos.y < g->map->map_size.y)
	{
		pos.x = 1;
		while (g->map->layout[pos.y][pos.x])
		{
			//if (g->map->layout[pos.y][pos.x] == 'E')
			//	g->map->pos_exit = pos;
			//else if (g->map->layout[pos.y][pos.x] == 'C')
			//	g->map->num_coins++;
			if (ft_strchr("01 ", g->map->layout[pos.y][pos.x]))
				pos.x *= 1;
			else if (ft_strchr("NSEW", g->map->layout[pos.y][pos.x]))
				g->map->pos_player = pos;
			else
				return (false);
			pos.x++;
		}
		pos.y++;
	}
	return (true);
}

static bool	validate_player(char **layout, t_point size)
{
	int	c;
	int	r;
	int	p;

	p = 0;
	r = 1;
	while (r < size.y)
	{
		c = 1;
		while (layout[r][c])
		{
			if (ft_strchr("NSEW", layout[r][c]))
				p++;
			c++;
		}
		r++;
	}
	if (p == 1)
		return (true);
	else
		return (false);
}

static bool	validate_walls1(char **layout, t_point size)
{
	int	col;
	int	row;

	col = 0;
	row = 0;
	while (layout[0][col] && ft_strchr(" 1", layout[0][col]))
		col++;
	if (!layout[0][col])
		return (false);
	col = 0;
	while (layout[size.y - 1][col] && ft_strchr(" 1", layout[size.y - 1][col]))
		col++;
	if (!layout[size.y - 1][col])
		return (false);
	while (row < size.y)
	{
		size.x = (int)ft_strlen(layout[row]);
		if (ft_strchr("1 ", layout[row][0]) || layout[row][size.x - 1] != '1')
			return (false);
		row++;
	}
	return (true);
}

void	validate_map(t_game *g)
{
	if (g->map->map_size.y == 0)
		error_map("Map is empty", g);
	if (!validate_player(g->map->layout, g->map->map_size))
		error_map("Map must have one player", g);
	if (!validate_chars(g))
		error_map("Map has unknown entities", g);
	if (!validate_walls1(g->map->layout, g->map->map_size))
		error_map("Map is not walled", g);
	if (!validate_walls2(g->map->layout, g->map->map_size)) // WIP procurar contactos com exterior
		error_map("Map is not walled", g);
	//if (!validate_path(g))
	//	error_map("Map cannot be cleared", g);
}
