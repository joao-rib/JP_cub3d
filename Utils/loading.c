/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/11 13:23:46 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	fill_with_spaces(t_game *g, int i)
{
	int		extra_len;
	char	*temp;

	extra_len = g->map->map_size.x - ft_strlen(g->map->layout[i]);
	if (extra_len <= 0)
		return ;
	temp = ft_calloc(extra_len + 1, sizeof(char));
	if (!temp)
		return (error_map("Map allocation error", g));
	temp = ft_memset(temp, ' ', extra_len);
	g->map->layout[i] = ft_strbuild(g->map->layout[i], temp);
	free(temp);
}

static void load_texture(t_game *g, char *line, size_t l)
{
	if (l == 1)
		;
	else if (ft_strnstr(line, "NO ", 3))
		g->texture.NO = ft_substr(line, 3, l - 4);
	else if (ft_strnstr(line, "SO ", 3))
		g->texture.SO = ft_substr(line, 3, l - 4);
	else if (ft_strnstr(line, "WE ", 3))
		g->texture.WE = ft_substr(line, 3, l - 4);
	else if (ft_strnstr(line, "EA ", 3))
		g->texture.EA = ft_substr(line, 3, l - 4);
	else if (ft_strnstr(line, "F ", 2))
		g->texture.EA = ft_substr(line, 2, l - 3);
	else if (ft_strnstr(line, "C ", 2))
		g->texture.EA = ft_substr(line, 2, l - 3);
	free(line);
}

static int	count_rows(char *file, t_game *g)
{
	char	*line;
	int		fd;
	int		i;

	line = "exist";
	i = 0;
	g->map->map_on_file = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		ft_error_msg("Cannot open .cub file");
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (line[0] == '\n' || ft_strnstr(line, "NO ", 3)
				|| ft_strnstr(line, "SO ", 3) || ft_strnstr(line, "WE ", 3)
				|| ft_strnstr(line, "EA ", 3) || ft_strnstr(line, "F ", 2)
				|| ft_strnstr(line, "C ", 2)) // WIP Se for tema para norminette, passar para função //WIP também quando for só whitespaces... antes do layout
			g->map->map_on_file++;
		else
			i++;
		if (i > 0 && (int)ft_strlen(line) > g->map->map_size.x)
			g->map->map_size.x = (int)ft_strlen(line);
		free(line);
	}
	close(fd);
	return (i);
}

static void	map_mem(t_game *g, char *file)
{
	g->map = (t_map *)malloc(sizeof(t_map));
	if (!g->map)
		error_map("Map allocation error", g);
	g->map->map_size.y = count_rows(file, g);
	g->map->layout = (char **)ft_calloc(g->map->map_size.y + 1, sizeof(char *));
	if (!g->map->layout)
		error_map("Map layout error", g);
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
		error_map("Cannot open .cub file", g);
	while (++i < g->map->map_size.y)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (i < 0)
			load_texture(g, line, ft_strlen(line));
		else
		{
			g->map->layout[i] = ft_strtrim(line, "\n");
			if (!g->map->layout[i] || !g->map->layout[i][0])
				error_map("Map layout error", g);
			if ((int)ft_strlen(g->map->layout[i]) < g->map->map_size.x)
				fill_with_spaces(g, i);
			free(line);
		}
	}
	g->map->layout[i] = NULL;
	close(fd);
}

