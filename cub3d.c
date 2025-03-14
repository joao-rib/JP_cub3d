/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/03/15 18:21:18 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

static void	default_colours(t_game *g)
{
	if (!g->texture.ceiling)
		g->texture.ceiling = ft_strdup("17,17,132");
	if (!g->texture.floor)
		g->texture.floor = ft_strdup("237,232,208");
}

int	main(int argc, char **argv)
{
	t_game	g;
	int		i;

	if (argc != 2)
		return (ft_error_msg("Insert one argument only"));
	if (ft_strlen(argv[1]) < 4
		|| !ft_strnstr(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (ft_error_msg("Argument must be a .cub file"));
	ft_bzero(&g, sizeof (t_game));
	load_map(&g, argv[1]);
	default_colours(&g);
	validate_map(&g);
	ft_printf("Floor: %s\nCeiling: %s\n", g.texture.floor, g.texture.ceiling);
	ft_printf("NO: %s\nSO: %s\nWE: %s\nEA: %s\n", g.texture.north, g.texture.south, g.texture.west, g.texture.east);
	i = 0;
	while (g.map->layout[i])
	{
		ft_printf("%s$\n", g.map->layout[i]);
		i++;
	}
	// load everything else
	// initialise some variables?
	// run game
	destroy_game(&g);
	return (0);
}

/*int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (error_msg("Insert one argument only"));
	if (ft_strlen(argv[1]) < 4
		|| !ft_strnstr(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4))
		return (error_msg("Argument must be a .ber file"));
	g.nsprites = 5;
	load_map(&g, argv[1]);
	validate_map(&g);
	load_graphics(&g);
	load_sprites(&g, g.nsprites);
	render_map(&g);
	g.moves = 0;
	g.curr = g.map->pos_player;
	g.next = g.map->pos_player;
	mlx_hook(g.display.win, 2, (1L << 0), move_handler, &g);
	mlx_hook(g.display.win, 17, (1L << 17), &destroy_game, &g);
	mlx_loop_hook(g.display.mlx, render_movement, &g);
	mlx_loop(g.display.mlx);
	return (0);
}*/
