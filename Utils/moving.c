/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/03/31 12:18:03 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	key_handler(const int key, t_game *game)
{
	(void)game;
	if (key == ESC)
	{
		ft_printf("\n'ESC' pressed, game closed...\nThanks for playing!\n");
		destroy_game(game);
	}
	if (key == W)
		ft_printf("Move Up\n");//move_up(game);
	if (key == S)
		ft_printf("Move down\n");//move_down(game);
	if (key == A)
		ft_printf("Move left\n");//move_left(game);
	if (key == D)
		ft_printf("Move right\n");//move_right(game);
	if (key == LEFT)
		ft_printf("Look left\n");//look_direction(game, true);
	if (key == RIGHT)
		ft_printf("Look right\n");//look_direction(game, false);
	return (0);
}
