/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/11 13:13:36 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/cub3d.h"

int	main(int argc, char **argv)
{
	t_game	g;

	if (argc != 2)
		return (ft_error_msg("Insert one argument only"));
	if (ft_strlen(argv[1]) < 4
		|| !ft_strnstr(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4))
		return (ft_error_msg("Argument must be a .cub file"));
	g.map->map_on_file = 0;
	load_map(&g, argv[1]);
	validate_map(&g);
	// load everything else
	// initialise some variables
	// run game
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
