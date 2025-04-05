/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/04/05 12:18:11 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

static bool	check_file(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

static bool	default_colours(t_game *g)
{
	bool	result;

	result = true;
	if (!g->texture.ceiling)
		g->texture.ceiling = ft_strdup("17,17,132");
	if (!g->texture.floor)
		g->texture.floor = ft_strdup("237,232,208");
	if (!g->texture.north || !g->texture.south
		|| !g->texture.west || !g->texture.east)
		result = false;
	if (result && g->texture.north)
		result = check_file(g->texture.north);
	if (result && g->texture.south)
		result = check_file(g->texture.south);
	if (result && g->texture.west)
		result = check_file(g->texture.west);
	if (result && g->texture.east)
		result = check_file(g->texture.east);
	if (!result)
		destroy_map(g);
	return (result);
}

static void	init_game(t_game *game)
{
	if (game->mlx_ptr == NULL)
		return ;
	game->win_ptr = mlx_new_window(game->mlx_ptr,
			WIDTH, HEIGHT, "cub3d");
	if (game->win_ptr == NULL)
		return ;
	mlx_hook(game->win_ptr, KeyPress, KeyPressMask, &key_handler, game);
	mlx_hook(game->win_ptr, DestroyNotify, StructureNotifyMask,
		&destroy_game, game);
	mlx_loop_hook(game->mlx_ptr, &game_frame_loop, game);
	mlx_loop(game->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (ft_error_msg("Insert one argument only"));
	if (ft_strlen(argv[1]) < 4
		|| !ft_strnstr(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (ft_error_msg("Argument must be a .cub file"));
	ft_bzero(&g, sizeof (t_game));
	load_map(&g, argv[1]);
	if (!default_colours(&g))
		return (ft_error_msg("Texture file not found"));
	validate_map(&g);
	load_graphics(&g);
	init_game(&g);
	destroy_game(&g);
	return (0);
}
