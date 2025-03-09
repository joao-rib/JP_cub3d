/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/15 13:16:08 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*static int	same_pos(t_point pos1, t_point pos2)
{
	if (pos1.x != pos2.x || pos1.y != pos2.y)
		return (0);
	return (1);
}

int	render_movement(t_game *g)
{
	if (same_pos(g->next, g->curr)
		|| g->map->layout[g->next.y][g->next.x] == '1')
		return (0);
	else if (g->map->layout[g->next.y][g->next.x] == 'E'
			&& g->coins != g->map->num_coins)
		return (0);
	else if (g->map->layout[g->next.y][g->next.x] == 'E'
			&& g->coins == g->map->num_coins)
		destroy_game(g);
	g->moves++;
	ft_printf("Number of movements: %d\n", g->moves);
	move_player(g);
	return (0);
}

void	render_map(t_game *g)
{
	t_point	l_pos;
	t_point	s_pos;
	int		i;

	l_pos.y = 0;
	while (g->map->layout[l_pos.y])
	{
		l_pos.x = 0;
		while (g->map->layout[l_pos.y][l_pos.x])
		{
			i = ft_strchr_pos("01CEP", g->map->layout[l_pos.y][l_pos.x]);
			s_pos.x = l_pos.x * g->sprite[i].width;
			s_pos.y = l_pos.y * g->sprite[i].height;
			if (!mlx_put_image_to_window(g->display.mlx, g->display.win,
					g->sprite[i].img, s_pos.x, s_pos.y))
				error_exit("Error during sprite rendering", g);
			l_pos.x++;
		}
		l_pos.y++;
	}
}*/
