void	ray_cordinate(t_ray *raycast, int direction)
{
	if (direction == 'v')
	{
		if (raycast->virt_cord.x > 0 && raycast->virt_cord.y > 0)
		{
			raycast->ray_cordinate.x = raycast->virt_cord.x;
			raycast->ray_cordinate.y = raycast->virt_cord.y;
		}
		else
		{
			raycast->ray_cordinate.x = raycast->horizontal_cord.x;
			raycast->ray_cordinate.y = raycast->horizontal_cord.y;
		}
	}
	else if (direction == 'h')
	{
		if (raycast->horizontal_cord.x > 0 && raycast->horizontal_cord.y> 0)
		{
			raycast->ray_cordinate.x = raycast->horizontal_cord.x;
			raycast->ray_cordinate.y = raycast->horizontal_cord.y;
		}
		else
		{
			raycast->ray_cordinate.x = raycast->horizontal_cord.x;
			raycast->ray_cordinate.y = raycast->horizontal_cord.y;
		}
	}
}