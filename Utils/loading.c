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

/*void	load_sprites(t_game *g, int nsprites)
{
	int		i;
	char	*n;
	char	*filename;

	i = 0;
	g->sprite = ft_calloc(nsprites, sizeof(t_sprite));
	if (!g->sprite)
		error_exit("Sprite allocation error", g);
	while (i < nsprites)
	{
		n = ft_itoa(i);
		filename = ft_strjoin("Sprites/img", n);
		filename = ft_strbuild(filename, ".xpm");
		g->sprite[i].img = mlx_xpm_file_to_image(g->display.mlx, filename,
				&(g->sprite[i].width), &(g->sprite[i].height));
		free(filename);
		free(n);
		i++;
	}
}*/

/*void	load_graphics(t_game *g)
{
	int	width;
	int	height;

	width = g->map->map_size.x * 32;
	height = g->map->map_size.y * 32;
	g->display.mlx = mlx_init();
	if (!g->display.mlx)
		error_exit("Display allocation error", g);
	g->display.win = mlx_new_window(g->display.mlx, width, height, "so_long");
	if (!g->display.win)
		error_exit("Window allocation error", g);
}*/

static void load_texture(char *line, t_game *g, size_t l)
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
		error_msg("Cannot open .cub file");
	while (line)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		else if (line[0] == '\n' || ft_strnstr(line, "NO ", 3)
				|| ft_strnstr(line, "SO ", 3) || ft_strnstr(line, "WE ", 3)
				|| ft_strnstr(line, "EA ", 3) || ft_strnstr(line, "F ", 2)
				|| ft_strnstr(line, "C ", 2)) // WIP Se for tema para norminette, passar para função
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
			g->map->layout[i] = ft_strtrim(line, "\n"); //WIP add spaces in accordance with g->map->map_size.x
			if (!g->map->layout[i])
				error_map("Map layout error", g);
			//if (i == 0)
			//	g->map->map_size.x = (int)ft_strlen(g->map->layout[i]);
			//else if ((int)ft_strlen(g->map->layout[i]) != g->map->map_size.x)
			//	error_map("Map is not rectangular", g);
			free(line);
		}
	}
	g->map->layout[i] = NULL;
	close(fd);
}

