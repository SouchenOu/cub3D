void	initial_raycast(t_struct *cub, t_ray *raycast, double angle)
{
	raycast->cub = cub;
	raycast->a = deg_rad(lmt_angle(angle));
	raycast->ray_cordinate.x = -1.00;
	raycast->ray_cordinate.y = -1.00;
	raycast->offset.x = -1.00;
	raycast->offset.y = -1.00;
	raycast->num = 0;
	raycast->tang = 0.00;
	raycast->v_fcord.x = 0.00;
	raycast->v_fcord.y = 0.00;
	raycast->v_fdis = 0.00;
	raycast->h_fcord.y = 0.00;
	raycast->h_fcord.x = 0.00;
	raycast->h_fdis = 0.00;
	raycast->check_num = -2;
	raycast->wc_temp.x = 0.00;
	raycast->wc_temp.y = 0.00;
	raycast->f_dis = 0.00;
	raycast->h_line = 0.00;
	raycast->h_offset = 0.00;
	raycast->dir = 0;
}

void	check_gridline(t_ray *raycast)
{
	horizontal_checker(raycast);
	vertical_checker(raycast);
	if (raycast->v_fdis < raycast->h_fdis)
		get_fray_coord(raycast, 'v');
	else if (raycast->v_fdis > raycast->h_fdis)
		get_fray_coord(raycast, 'h');
	raycast->f_dis = pythg(raycast->cub->cord.x, raycast->ray_cordinate.x, raycast->cub->cord.y, raycast->ray_cordinate.y);
}
//Vertical check
/*void	vertical_checker(t_ray *raycast)
{
	raycast->tang = -tan(raycast->a);
	if (raycast->a > PIH && raycast->a < PIT)
	{
		raycast->ray_cordinate.x = ((raycast->cub->cord.x / size) * size) - (raycast->cub->dire.left);
		raycast->ray_cordinate.y = ((raycast->cub->cord.x - raycast->ray_cordinate.x) * raycast->tang) + raycast->cub->cord.y;
		raycast->check_num = raycast->cub->virtical_num;
		set_offset(raycast, LEFT);
	}
	else if (raycast->a < PIH || raycast->a > PIT)
	{
		raycast->ray_cordinate.x = ((raycast->cub->cord.x / size) * size) + (raycast->cub->dire.right);
		raycast->ray_cordinate.y = (raycast->cub->cord.x - raycast->ray_cordinate.x) * raycast->tang + raycast->cub->cord.y;
		raycast->check_num = raycast->cub->virtical_num;
		set_offset(raycast, RIGHT);
	}
	else if (raycast->a == PI || raycast->a == 0)
	{
		raycast->ray_cordinate.x = raycast->cub->cord.x;
		raycast->ray_cordinate.y = raycast->cub->cord.y;
		raycast->check_num = -2;
		raycast->dir = UD;
	}
	check_loop(raycast, 'v');
}
// horizontal check
void	horizontal_checker(t_ray *raycast)
{
	raycast->tang = -1 / tan(raycast->a);
	if (raycast->a > PI)
	{
		raycast->ray_cordinate.y = ((raycast->cub->cord.y / size) * size) - (raycast->cub->dire.up);
		raycast->ray_cordinate.x = (raycast->cub->cord.y - raycast->ray_cordinate.y) * raycast->tang + raycast->cub->cord.x;
		raycast->check_num = raycast->cub->horizontal_num;
		set_offset(raycast, UP);
	}
	else if (raycast->a < PI)
	{
		raycast->ray_cordinate.y = ((raycast->cub->cord.y / size) * size) + (raycast->cub->dire.down);
		raycast->ray_cordinate.x = (raycast->cub->cord.y - raycast->ray_cordinate.y) * raycast->tang + raycast->cub->cord.x;
		raycast->check_num = raycast->cub->horizontal_num;
		set_offset(raycast, DOWN);
	}
	else if (raycast->a == PI || raycast->a == 0)
	{
		raycast->ray_cordinate.x = raycast->cub->cord.x;
		raycast->ray_cordinate.y = raycast->cub->cord.y;
		raycast->check_num = -2;
		raycast->dir = LR;
	}
	check_loop(raycast, 'h');
}

void	set_offset(t_ray *ray, int direction)
{
	if (direction == UP)
	{
		ray->offset.y = -size;
		ray->offset.x = -(ray->offset.y) * ray->tang;
		ray->dir = UP;
	}
	else if (direction == DOWN)
	{
		ray->offset.y = size;
		ray->offset.x = -(ray->offset.y) * ray->tang;
		ray->dir = DOWN;
	}
	else if (direction == LEFT)
	{
		ray->offset.x = -size;
		ray->offset.y = -(ray->offset.x) * ray->tang;
		ray->dir = LEFT;
	}
	else if (direction == RIGHT)
	{
		ray->offset.x = size;
		ray->offset.y = -(ray->offset.x) * ray->tang;
		ray->dir = RIGHT;
	}
}*/

/*void	check_loop(t_ray *raycast, int direction)
{
	int	i;

	i = -1;
	while (++i < raycast->check_num && limits(raycast))
	{
		if (is_wall(raycast, direction))
		{
			get_fray_dis(raycast, direction);
			break ;
		}
		else
		{
			raycast->ray_cordinate.x += raycast->offset.x;
			raycast->ray_cordinate.y += raycast->offset.y;
		}
	}
	if (!limits(raycast))
		get_fray_dis(raycast, direction);
}*/
/*int	limits(t_ray *raycast)
{
	if ((raycast->ray_cordinate.x > 0.00 && raycast->ray_cordinate.y > 0.00))
	{
		if (raycast->ray_cordinate.x < ((double)raycast->main->virtical_num) * size)
		{
			if (raycast->ray_cordinate.y < ((double)raycast->cub->horizontal_num) * size)
				return (1);
		}
	}
	return (0);
}

void	get_fray_dis(t_ray *raycast, int direction)
{
	if (direction == 'v')
	{
		raycast->v_fcord.x = raycast->ray_cordinate.x;
		raycast->v_fcord.y = raycast->ray_cordinate.y;
		raycast->v_fdis = pythg(raycast->cub->cord.x, raycast->v_fcord.x, raycast->cub->cord.y, raycast->v_fcord.y);
	}
	else if (direction == 'h')
	{
		raycast->h_fcord.x = raycast->ray.x;
		raycast->h_fcord.y = raycast->ray.y;
		raycast->h_fdis = pythg(raycast->cub->cord.x, raycast->h_fcord.x, raycast->cub->cord.y, raycast->h_fcord.y);
	}
}*/
/*void	get_fray_coord(t_ray *raycast, int direction)
{
	if (direction == 'v')
	{
		if (raycast->v_fcord.x > 0.00 && raycast->v_fcord.y > 0.00)
		{
			raycast->ray_cordinate.x = raycast->v_fcord.x;
			raycast->ray_cordinate.y = raycast->v_fcord.y;
		}
		else
		{
			raycast->ray_cordinate.x = raycast->h_fcord.x;
			raycast->ray_cordinate.y = raycast->h_fcord.y;
		}
	}
	else if (direction == 'h')
	{
		if (raycast->h_fcord.x > 0.00 && raycast->h_fcord.y > 0.00)
		{
			raycast->ray_cordinate.x = raycast->h_fcord.x;
			raycast->ray_cordinate.y = raycast->h_fcord.y;
		}
		else
		{
			raycast->ray_cordinate.x = raycast->v_fcord.x;
			raycast->ray_cordinate.y = raycast->v_fcord.y;
		}
	}
}*/

void	raycast(t_struct *cub)
{
	int	i;
    int j;
    i = 0;

	cub->FOV = 60;
	cub->NB_rays = WIN_W;
	cub->angle = cub->vect.pos - ((double)cub->FOV / 2.00);
	cub->raycast = (t_ray *)malloc(sizeof(t_ray) * cub->NB_rays);

	while (i < cub->NB_rays)
	{
		initial_raycast(cub, &cub->raycast[i], cub->angle);
		cub->angle = cub->angle +  (cub->FOV / (double)cub->NB_rays);
        i++;
	}

    //start raycasting
	i = 0;
	if (cub->check_buffer)
		buffer(cub);
	while (i < cub->NB_rays)
	{
		check_gridline(&cub->raycast[i]);
		//lets_do_raycast(&cub->raycast[i], i);
        i++;
	}
}