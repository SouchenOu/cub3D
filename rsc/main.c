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
    //t_textures txt;
    cub.scaleHeight = 64;
    cub.scaleWidth = 64;
    cub.texture_height = 64;
    cub.texture_width = 64;
    //cub.texture->img_height = 64;
    //cub.texture->img_width = 64;
    if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
	if (ft_read_maps(av[1], &cub) == 0)
        return (0);
    ft_jump_lines(&cub);
    //if (!ft_check_alltextures(&cub))
    //    return (0);
   if (!ft_check_rgb(&cub))
        return (0);
    if (!ft_check_map(&cub))
        return (0);
    cub.mlx_ptr = mlx_init();
    if (!cub.mlx_ptr)
		return(0);
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, W_WIDTH, W_HEIGHT, "cub3D");
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
	//mlx_get_data_addr() returns information about the created image, allowing a user to modify it later.
	cub.addr = (int *)mlx_get_data_addr(cub.img, &cub.bits_per_pixel, &cub.line_length, &cub.endian);
    if (!cub.addr)
		return (0);
    player_position(&cub);
    directionOfPlayer(&cub); 
	//  loading_map(&cub);
    init_textures(&cub);
    cub.widthofmap = cub.scaleWidth * cub.widthof_minimap;
    cub.heightofmap = cub.scaleHeight * cub.heightof_minimap;
    /*printf("%d\n",cub.texture->data[0]);
   int i = 0;
    while(cub.texture->data[i])
    {
        printf("txt_data[%d]= %d\n", i,cub.texture->data[i]);
        i++;
        // if(i == 3)
        //     break ;
    }
    printf("%i", i);
    printf("%p", cub.texture->data);*/
    ft_draw_map(&cub,cub.texture);
    hooking(&cub);
    return (0);
}


void	init_textures(t_struct *cub)
{
	//t_textures	*texture_ptr;
    //int i = 0;

	cub->texture = malloc(sizeof(t_textures) * 4);
	// if (cub->texture == NULL)
	// 	return ;
        load_texture(cub, "textures/xpm/1.xpm", cub->texture);
}

int	get_textures_val(char *line, t_struct **cub)
{
	t_struct	*s;

	if (!line)
		return (1);
	s = *cub;
	if (!ft_strncmp("NO ", line, 3))
	{
		s->no = ft_substr(line, 5, ft_strlen(line));
	}
	else if (!ft_strncmp("SO ", line , 3))
	{

		s->so = ft_substr(line, 5, ft_strlen(line));
	}
    else if(!ft_strncmp("WE ", line, 3))
    {
        s->we = ft_substr(line, 5, ft_strlen(line));
    }
    else if(!ft_strncmp("EA ", line, 3))
    {
        s->ea = ft_substr(line, 5, ft_strlen(line));
    }
	return (1);
}



void	loading_map(t_struct *cub)
{

	cub->img2 = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/xpm/1.xpm",&cub->texture_width, &cub->texture_height);
	if (!cub->img2)
		return ;
	cub->data = (int *)mlx_get_data_addr(cub->img2, &cub->bits_per_pixel2, &cub->size_line, &cub->endian2);
	if (!cub->data || cub->texture_width != cub->texture_height)
    {
        return ;
    }
   
}


void	load_texture(t_struct *cub, char *filename, t_textures *texture)
{
    //printf("width text = %d\n", cub->texture_width);
    //printf("height txt = %d\n", cub->texture_height);




    // for(int i = 0; i < 4 ; i++){
	texture[0].img = mlx_xpm_file_to_image(cub->mlx_ptr, filename, &texture[0].img_width, &texture[0].img_height);
	texture[0].data = (int *)mlx_get_data_addr(texture[0].img, &texture[0].bits_per_pixel, &texture[0].size_line, &texture[0].endian);
	texture[1].img = mlx_xpm_file_to_image(cub->mlx_ptr, "textures/xpm/east.xpm", &texture[1].img_width, &texture[1].img_height);
	texture[1].data = (int *)mlx_get_data_addr(texture[1].img, &texture[1].bits_per_pixel, &texture[1].size_line, &texture[1].endian);
    // texture[0].img = mlx_xpm_file_to_image(cub->mlx_ptr, filename, &texture[0].img_width, &texture[0].img_height);
	// texture[0].data = (int *)mlx_get_data_addr(texture[0].img, &texture[0].bits_per_pixel, &texture[0].size_line, &texture[0].endian);
    // texture[0].img = mlx_xpm_file_to_image(cub->mlx_ptr, filename, &texture[0].img_width, &texture[0].img_height);
	// texture[0].data = (int *)mlx_get_data_addr(texture[0].img, &texture[0].bits_per_pixel, &texture[0].size_line, &texture[0].endian);
    
    
    
    
    
    
    
    
    
    // int i = 0;
    // //printf("textdata[0] = %d\n", texture->data[10]);
    // while(texture->data[i] != 100)
    // {
    //     printf("txt_data[%d]= %d\n", i,texture->data[i]);
    //     i++;
    // }
    // exit(0);
    //printf("i = %d\n", i);
	// if (!texture->img || !filename)
    // {
    //     return ;
    // }
	// if (!texture->data || texture->img_width != texture->img_height)
    // {
    //     return ;
    // }
 	
}
