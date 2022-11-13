void	raycast(t_struct *cub)
{
	int	i;
    int j;
    i = 0;
	t_ray raycast;

	cub->FOV = 120;
	cub->NB_rays =  W_WIDTH;
	cub->looking_angle = cub->vect.pos - ((double)cub->FOV / 2);
	cub->raycast = (t_ray *)malloc(sizeof(t_ray) * cub->NB_rays);

	while (i < cub->NB_rays)
	{
		raycast.cub = cub;
		raycast.ray_looking_angle = degrees_to_radians(limite_angle(cub->looking_angle));
		raycast.ray_cordinate.x = -1;
		raycast.ray_cordinate.y = -1;
		raycast.offset.x = -1;
		raycast.offset.y = -1;
		raycast.dir = 0;
		raycast.number_to_check = -2;
		raycast.tang = 0;
		raycast.horizontal_distance = 0;
		raycast.horizontal_cord.y = 0;
		raycast.horizontal_cord.x = 0;
		raycast.virt_cord.x = 0;
		raycast.virt_cord.y = 0;
		raycast.virtical_distance = 0;
        raycast.ray_cord_temp.x = 0;
        raycast.ray_cord_temp.y = 0;

		
		cub->looking_angle = cub->looking_angle +  (cub->FOV / (double)cub->NB_rays);
        i++;
	}

    //start raycasting
	i = 0;
	if (cub->check_buffer)
		ft_buffer(cub);
	while (i < cub->NB_rays)
	{
		check_horizontal_vertical(&cub->raycast[i]);
		//lets_do_raycast(&cub->raycast[i], i);
        i++;
	}
    i = 0;
	while (i < W_Height)
	{
		j = 0;
		while (k < W_Width)
        {
            cub->data[i * W_Width + j] = cub->buffer[i][j];
            j++;
        }
        i++;
	}
	mlx_put_image_to_window(cub->mlx_info.mlx, cub->mlx_info.window,cub->img, 0, 0);
}