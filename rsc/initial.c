void	initial(t_struct *cub)
{
	cub->mlx_info.height = 0;
	cub->mlx_info.width = 0;
    cub->cord.x = 100.00;
	cub->cord.y = 220.00;
    cub->vect.x = cos(deg_rad(280.00));
	cub->vect.y = -sin(deg_rad(280.00));
	cub->vect.pos = 280.00;
    cub->i_dis.h_down = 0.00;
	cub->dire.up = 0.00;
	cub->dire.left = 0.00;
	cub->dire.right = 0.00;
}