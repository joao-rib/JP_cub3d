/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/04/05 11:49:35 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	load_into_layout(t_game *g, int i, char *line)
{
	int		extra_len;
	char	*temp;

	g->map->layout[i] = ft_strtrim(line, "\n");
	if (!g->map->layout[i])
		error_map("Map layout error", g, 0);
	extra_len = g->map->map_size.x - ft_strlen(g->map->layout[i]);
	if (extra_len <= 0)
		return (free(line));
	temp = ft_calloc(extra_len + 1, sizeof(char));
	if (!temp)
	{
		free(line);
		return (error_map("Map allocation error", g, 0));
	}
	temp = ft_memset(temp, ' ', extra_len);
	g->map->layout[i] = ft_strbuild(g->map->layout[i], temp);
	free(temp);
	free(line);
}

static void	load_texture(t_game *g, char *line, size_t l)
{
	if (l == 1)
		;
	else if (ft_strnstr(line, "NO ", 3))
		g->texture.north = ft_substr(line, count_ws(line, 3),
				l - count_ws(line, 3) - 1);
	else if (ft_strnstr(line, "SO ", 3))
		g->texture.south = ft_substr(line, count_ws(line, 3),
				l - count_ws(line, 3) - 1);
	else if (ft_strnstr(line, "WE ", 3))
		g->texture.west = ft_substr(line, count_ws(line, 3),
				l - count_ws(line, 3) - 1);
	else if (ft_strnstr(line, "EA ", 3))
		g->texture.east = ft_substr(line, count_ws(line, 3),
				l - count_ws(line, 3) - 1);
	else if (ft_strnstr(line, "F ", 2))
		g->texture.floor = ft_substr(line, count_ws(line, 2),
				l - count_ws(line, 2) - 1);
	else if (ft_strnstr(line, "C ", 2))
		g->texture.ceiling = ft_substr(line, count_ws(line, 2),
				l - count_ws(line, 2) - 1);
	free(line);
}

static int	count_rows(char *file, t_game *g, char *line)
{
	int		fd;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_map("Cannot open .cub file", g, 1);
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (i == 0 && (ft_isemptystr(line) || ft_strnstr(line, "NO ", 3)
				|| ft_strnstr(line, "SO ", 3) || ft_strnstr(line, "WE ", 3)
				|| ft_strnstr(line, "EA ", 3) || ft_strnstr(line, "F ", 2)
				|| ft_strnstr(line, "C ", 2)))
			g->map->map_on_file++;
		else
			i++;
		if (i > 0 && (int)ft_strlen(line) > (g->map->map_size.x + 1))
			g->map->map_size.x = (int)ft_strlen(line) - 1;
		free(line);
	}
	close(fd);
	return (i);
}

static void	map_mem(t_game *g, char *file)
{
	g->map = (t_map *)malloc(sizeof(t_map));
	if (!g->map)
		error_map("Map allocation error", g, 0);
	g->map->map_on_file = 1;
	g->map->map_size.x = 0;
	g->map->map_size.y = count_rows(file, g, "temp");
	g->map->layout = (char **)ft_calloc(g->map->map_size.y + 1, sizeof(char *));
	if (!g->map->layout)
		error_map("Map layout error", g, 0);
}

void	load_map(t_game *g, char *file)
{
	char	*line;
	int		fd;
	int		i;

	map_mem(g, file);
	i = g->map->map_on_file * (-1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_map("Cannot open .cub file", g, 1);
	while (++i < g->map->map_size.y)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (i < 0)
			load_texture(g, line, ft_strlen(line));
		else
			load_into_layout(g, i, line);
	}
	g->map->layout[i] = NULL;
	close(fd);
}
