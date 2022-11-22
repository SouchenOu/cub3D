/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/18 15:08:17 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void print(char **str)
{
     int i = 0;
    while (str[i])
    {
        printf("|%s|\n",str[i]);
        i++;
    }
}

void ft_colorBuffer(t_struct *cub)
{
    int i;
    int k;
    i = 0;
	while (i < W_HEIGHT)
	{
		k = 0;
		while (k < W_WIDTH)
        {
            cub->color_buffer[i][k] = 0;
            k++;
        }
        i++;
	}
    cub->check_test = 0;
}

int main(int ac, char **av)
{
    t_struct cub;
    int i ;

    if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
	if (ft_read_maps(av[1], &cub) == 0)
        return (0);
    if (!ft_check_alltextures(&cub))
        return (0);
   if (!ft_check_rgb(&cub))
        return (0);
    if (!ft_check_map(&cub))
        return (0);
    cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, W_WIDTH, W_HEIGHT, "cub3D");
    cub.color_buffer = (unsigned int **)malloc(W_HEIGHT * sizeof(unsigned int *));
	i = -1;
	while (++i < W_HEIGHT)
		cub.color_buffer[i] = (unsigned int *)malloc(W_WIDTH * sizeof(unsigned int));
	ft_colorBuffer(&cub);
    cub.img = mlx_new_image(cub.mlx_ptr, W_WIDTH, W_HEIGHT);
	cub.addr = (int *)mlx_get_data_addr(cub.img, &cub.bits_per_pixel, &cub.line_length, &cub.endian);
    //int i = 0;
    //how much memory do we have to allocate to store this long buffer of colors
    // i will use w_width * w_height pixels
    //cub.color_buffer = (unsigned int *)malloc((unsigned int) W_HEIGHT * (unsigned int) W_WIDTH * sizeof(unsigned int ));
     //cub.color_buffer = (unsigned int **)malloc(W_HEIGHT * sizeof(unsigned int *));
    /*while (i < W_HEIGHT)
    {
        cub.color_buffer[i] = (unsigned int *)malloc(W_WIDTH * sizeof(unsigned int));
        i++;

    }*/
   
    //ft_colorBuffer(&cub);
     //cub.player.position_x = 200;
     //cub.player.position_y = 120;
    find_pos_player_in_gridline(&cub);
    player_position(&cub);
    directionOfPlayer(&cub);
    ft_draw_map(&cub);
    mlx_key_hook(cub.win_ptr, player_move, &cub);
    //mlx_hook(cub.win_ptr,124, 125, player_move, &cub);
    mlx_loop(cub.mlx_ptr);
    return (0);
}