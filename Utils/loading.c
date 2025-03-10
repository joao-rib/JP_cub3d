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
		else if (line[0] == '\n') // WIP also check first two letters for "NO" "SO" "EA" "WE" "F " "C "
			g->map->map_on_file++;
		else
			i++;
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
			free(line); //WIP Acrescentar aqui algo que guarda texturas e cores
		else
		{
			g->map->layout[i] = ft_strtrim(line, "\n"); //WIP trim right... for spaces!
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

