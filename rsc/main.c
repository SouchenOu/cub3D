/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/05 16:23:31 by souchen          ###   ########.fr       */
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

void	ft_initialization(t_struct *ptr)
{
	if (ptr->height < 100 && ptr->width < 100)
		ptr->zom = 10;
	else
		ptr->zom = 2;
	ptr->cos_x = 0.523599;
	ptr->sin_y = 0.523599;
	ptr->shift_x = W_WIDTH / 2;
	ptr->shift_y = W_HEIGHT / 2 - 0;
}
int	loading_map(t_struct cub, int ligne, int colone)
{
    //printf("here %c\n", cub.data[0][0]);
    //printf("colone here %d\n", colone);
   // printf("colone here %d\n", ligne);
	//if (cub.data[ligne][colone] == '1')
    //{
        //printf("data here %c\n", cub.data[ligne][colone]);
		cub.img.img_path = mlx_xpm_file_to_image(cub.mlx_ptr,"wood.xpm",&cub.img.size.x, &cub.img.size.y);
        mlx_put_image_to_window(cub.mlx_ptr, cub.win_ptr, cub.img.img_path ,colone * 64, ligne * 64);
    //}
	/*else if (cub.data[ligne][colone] == '0')
		cub.img.img_path  = mlx_xpm_file_to_image(cub.mlx_ptr, "purplestone.xpm",&cub.img.size.x, &cub.img.size.y);
    else if (cub.data[ligne][colone] == ' ')       
		cub.img.img_path = mlx_xpm_file_to_image(cub.mlx_ptr, "barrel.xpm", &cub.img.size.x, &cub.img.size.y);*/
	//mlx_destroy_image(cub.mlx_ptr, cub.img.img_path);
	return (0);
}
int	print_map(t_struct cub)
{
	    int	ligne;
	    int	colone;

	    ligne = 0;
	    while (ligne < cub.height)
	    {
		    colone = 0;
		    while (colone < cub.width)
		    {
			    loading_map(cub, ligne, colone);
			    colone++;
		    }
		    ligne++;
	    }
        return (0);
}
	

int main(int ac, char **av)
{
    t_struct cub;

    if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
    if (ft_strnstr(&(av[1][ft_strlen(av[1]) - 4]), ".cub", 4) == NULL)
	{
		printf("Invalid map extension. Use .cub\n");
		return (-1);
	}
	ft_read_maps(av[1], &cub);
    cub.data = ft_jump_lines(&cub);
    ft_check_alltextures(&cub);
    ft_check_rgb(&cub);
    ft_check_map(&cub);
    cub.mlx_ptr = mlx_init();
    cub.win_ptr = mlx_new_window(cub.mlx_ptr, cub.y * 64 ,cub.x * 100, "Cub3D");
    print_map(cub);
    mlx_loop(cub.mlx_ptr);
   /* print(ft_jump_lines(&cub));
    printf("F --> %d ",cub.flr.r);
    printf("%d ",cub.flr.g);
    printf("%d \n",cub.flr.b);
    printf("C --> %d ",cub.clg.r);
    printf("%d ",cub.clg.g);
    printf("%d \n",cub.clg.b);
    printf("NO --->%s\n",cub.drct.north_path);
    printf("SO --->%s\n",cub.drct.south_path);
    printf("WE --->%s\n",cub.drct.west_path);
    printf("EA --->%s\n",cub.drct.east_path);*/
}