/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2025/04/05 11:46:23 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	error_map(char *msg, t_game *g, bool fd_error)
{
	ft_error_msg(msg);
	if (fd_error)
		free(g->map);
	else if (g->map)
		destroy_map(g);
	exit(1);
}

void	error_exit(char *msg, t_game *g)
{
	ft_error_msg(msg);
	destroy_game(g);
	exit(1);
}
