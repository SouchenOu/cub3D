/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/24 19:10:48 by yismaili         ###   ########.fr       */
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
void hooking(t_struct *cub)
{
    mlx_hook(cub->win_ptr, 02, 0, KeyPress ,cub);
    mlx_hook(cub->win_ptr, 03, 0, KeyRelease, cub);
    mlx_loop_hook(cub->mlx_ptr, player_move, cub);
    mlx_loop(cub->mlx_ptr);
}
int main(int ac, char **av)
{
    t_struct cub;
    int i;
    cub.scaleHeight = 64;
    cub.scaleWidth = 64;
    cub.texture_height = 64;
    cub.texture_width = 64;
    if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
	if (ft_read_maps(av[1], &cub) == 0)
        return (0);
    ft_jump_lines(&cub);
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
    //here we create a texture in memory (so all this pixels(red, blue, red, blue)) to get a wall texture
    //how do we i know what is the pixel that i have to pic to go and pint my wall strip
    cub.wallTexture = (unsigned int *) malloc (sizeof(unsigned int) * (unsigned int)cub.texture_width * (unsigned int)cub.texture_height);
    for(int x=0; x < cub.texture_width; x++)
    {
        for(int y = 0; y < cub.texture_height;y++)
        {
            //put the value black or blue based on x and y being a multiple
            if(x % 8  && y % 8 )
            {
                cub.wallTexture[(cub.texture_width * y) + x] = 0xadd8e6;
            }
            else{
                cub.wallTexture[(cub.texture_width * y) + x] = 0xFFF0000;
            }
        }
    }
    cub.img = mlx_new_image(cub.mlx_ptr, W_WIDTH, W_HEIGHT);
	cub.addr = (int *)mlx_get_data_addr(cub.img, &cub.bits_per_pixel, &cub.line_length, &cub.endian);
    //cub.img = mlx_xpm_file_to_image()

    player_position(&cub);
    directionOfPlayer(&cub);
    cub.widthofmap = cub.scaleWidth * cub.widthof_minimap;
    cub.heightofmap = cub.scaleHeight * cub.heightof_minimap;
    ft_draw_map(&cub);
    hooking(&cub);
    return (0);
}
