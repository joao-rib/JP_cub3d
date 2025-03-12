/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joao-rib <joao-rib@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 19:30:33 by joao-rib          #+#    #+#             */
/*   Updated: 2024/07/10 16:27:56 by joao-rib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	error_map(char *msg, t_game *g)
{
	ft_error_msg(msg);
	if (g->map)
		destroy_map(g); // WIP incluir texturas
	exit(1);
}

void	error_exit(char *msg, t_game *g)
{
	ft_error_msg(msg);
	destroy_game(g); // WIP pode ser necessário reescrever
	exit(1);
}
