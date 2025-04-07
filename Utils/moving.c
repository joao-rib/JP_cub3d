/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbezerra <tbezerra@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/04/07 17:56:55 by tbezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_up(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.player_x + (game->dirx * PLAYER_SPEED);
	new_y = game->player.player_y + (game->diry * PLAYER_SPEED);
	if (game->map->layout[(int)new_x][(int)game->player.player_y] == '0')
		game->player.player_x = new_x;
	if (game->map->layout[(int)game->player.player_x][(int)new_y] == '0')
		game->player.player_y = new_y;
}

void	move_down(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.player_x - (game->dirx * PLAYER_SPEED);
	new_y = game->player.player_y - (game->diry * PLAYER_SPEED);
	if (game->map->layout[(int)new_x][(int)game->player.player_y] == '0')
		game->player.player_x = new_x;
	if (game->map->layout[(int)game->player.player_x][(int)new_y] == '0')
		game->player.player_y = new_y;
}

void	move_left(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = -game->diry * PLAYER_SPEED;
	new_y = game->dirx * PLAYER_SPEED;
	if (game->map->layout[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == '0')
		game->player.player_x += new_x;
	if (game->map->layout[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == '0')
		game->player.player_y += new_y;
}

void	move_right(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->diry * PLAYER_SPEED;
	new_y = -game->dirx * PLAYER_SPEED;
	if (game->map->layout[(int)(game->player.player_x + new_x)]
		[(int)(game->player.player_y)] == '0')
		game->player.player_x += new_x;
	if (game->map->layout[(int)(game->player.player_x)]
		[(int)(game->player.player_y + new_y)] == '0')
		game->player.player_y += new_y;
}

int	key_handler(const int key, t_game *game)
{
	(void)game;
	if (key == ESC)
	{
		ft_printf("\n'ESC' pressed, game closed...\nThanks for playing!\n");
		destroy_game(game);
	}
	if (key == W)
		move_up(game);
	if (key == S)
		move_down(game);
	if (key == A)
		move_left(game);
	if (key == D)
		move_right(game);
	if (key == LEFT)
		look_direction(game, true);
	if (key == RIGHT)
		look_direction(game, false);
	return (0);
}
