/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/15 15:01:19 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void	move_player(t_struct *cub)
{
	int	i;

	i = -1;
	cub->looking_angle = cub->vect.pos - ((double)cub->FOV / 2.00);
	while (++i < cub->NB_rays)
	{
		cub->raycast[i].ray_looking_angle = degrees_to_radians(limite_angle(cub->looking_angle));
		cub->looking_angle += (cub->FOV / (double)cub->NB_rays);
	}
	mlx_clear_window(cub->mlx.mlx_ptr, cub->mlx.window);
	raycast(cub);
}

int	move(int key, void *param)
{
	t_struct	*cub;

	cub = (t_struct *) param;
	if (key == K_W)
	{
		cub->cord.y += (cub->p.vect.y * 5);
		cub->cord.x += (cub->p.vect.x * 5);
	}
	else if (key == K_S)
	{
		cub->cord.y -= (cub->p.vect.y * 5);
		cub->cord.x -= (cub->p.vect.x * 5);
	}
	else if (key == K_AR_R)
	{
		cub->p.vect.pos -= 1;
		cub->p.vect.pos = limite_angle(cub->p.vect.pos);
		cub->p.vect.x = cos(degrees_to_radians(cub->p.vect.pos));
		cub->p.vect.y = -sin(degrees_to_radians(cub->p.vect.pos));
	}
	else if (key == K_AR_L)
	{
		cub->p.vect.pos += 1;
		cub->p.vect.pos = limite_angle(cub->p.vect.pos);
		cub->p.vect.x = cos(degrees_to_radians(cub->p.vect.pos));
		cub->p.vect.y = -sin(degrees_to_radians(cub->p.vect.pos));
	}
	else if (key == K_A)
	{
		cub->cord.y += (cub->p.vect.y * 5);
		cub->cord.x += (cub->p.vect.x * 5) - 5;
	}
	else if (key == K_D)
	{
		cub->cord.y += (cub->p.vect.y * 5);
		cub->cord.x += (cub->p.vect.x * 5) + 5;
	}
	if (key == K_ESC)
		endgame(cub);
	find_pos_player(cub);
	move_player(cub);
	return (0);
}
