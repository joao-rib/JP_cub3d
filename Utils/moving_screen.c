/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 14:08:27 by tbezerra          #+#    #+#             */
/*   Updated: 2025/04/02 19:31:39 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	rotate_vector(double *x, double *y, double angle)
{
	double	old_x;

	old_x = *x;
	*x = *x * cos(angle) - *y * sin(angle);
	*y = old_x * sin(angle) + *y * cos(angle);
}

void	look_direction(t_game *game, const bool is_left)
{
	double	angle;

	if (is_left)
		angle = SCREEN_SENS;
	else
		angle = -SCREEN_SENS;
	rotate_vector(&game->dirx, &game->diry, angle);
	rotate_vector(&game->plane_x, &game->plane_y, angle);
}
