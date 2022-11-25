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
    if (!cub.mlx_ptr)
		return(0);
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
    if (!cub.addr)
		return (0);
    init_textures(cub);
    //cub.img = mlx_xpm_file_to_image()

    player_position(&cub);
    directionOfPlayer(&cub);
    cub.widthofmap = cub.scaleWidth * cub.widthof_minimap;
    cub.heightofmap = cub.scaleHeight * cub.heightof_minimap;
    ft_draw_map(&cub);
    hooking(&cub);
    return (0);
}
int	get_textures_val(char *line, t_struct **scrape, t_garbage **junk_list)
{
	t_struct	*s;

	if (!line)
		return (1);
	s = *scrape;
	if (!ft_strcmp("NO ", garbage(junk_list, ft_substr(line, 0, 3))))
	{
		s->no = check_open(garbage(junk_list, ft_strtrim(&line[3], WHITE_SPACES)), line);
	}
	else if (!ft_strcmp("SO ", garbage(junk_list, ft_substr(line, 0, 3))))
	{
		s->so = check_open(garbage(junk_list, ft_strtrim(&line[3], WHITE_SPACES)), line);
	}
	else
	{
		get_text_val_extra(line, &s, junk_list);
	}
	return (1);
}

void	init_textures(t_struct *cub)
{
	t_textures	*texture_ptr;

	texture_ptr = malloc(sizeof(t_textures) * 20);
	if (texture_ptr == NULL)
		return ;
	cub_>texture = texture_ptr;
	load_texture(cub, cub->no, &cub->texture[0]);
	load_texture(cub, cub->so, &cub->texture[1]);
	load_texture(cub, cub->we, &cub->texture[2]);
	load_texture(cub, cub->ea, &cub->texture[3]);
	load_texture(cub, "textures/door.xpm", &cub->texture[4]);
	load_texture(cub, "textures/wall_frame/1.xpm", &cub->texture[5]);
	load_texture(cub, "textures/wall_frame/2.xpm", &cub->texture[6]);
	load_texture(cub, "textures/wall_frame/3.xpm", &cub->texture[7]);
	load_texture(cub, "textures/wall_frame/4.xpm", &cub->texture[8]);
	load_texture(cub, "textures/wall_frame/5.xpm", &cub->texture[9]);
	load_texture(cub, "textures/wall_frame/6.xpm", &cub->texture[10]);
	load_texture(cub, "textures/wall_frame/7.xpm", &cub->texture[11]);
}
void	load_texture(t_struct *cub, char *filename, t_textures *texture)
{
	texture->img = mlx_xpm_file_to_image(cub->mlx_ptr, filename,&texture->img_width, &texture->img_height);
	if (!texture->img || !filename)
		return ;
	texture->data = mlx_get_data_addr(texture->img, &texture->bits_per_pixel, &texture->size_line, &texture->endian);
	if (! texture->data || texture->img_width != texture->img_height)
		return ;
}
char	*check_open(char *path, char *line)
{
	int		fd;
	char	*new_path;

	new_path = ft_substr(path, 0, ft_strlen(path) - 1);
	fd = open(new_path, O_RDONLY);
	if (fd < 0)
	{
		free(line);
		ft_putstr_fd(ERR_TEXTURES_PATH, 2);
		close(fd);
		exit(FAILED);
	}
	close(fd);
	return (new_path);
}

char	*garbage(t_garbage **junk, char *line)
{
	if (!line)
		return (NULL);
	ft_lstadd_back(junk, ft_lstnew(line));
	return (line);
}