
t_wall	*create_Wall_node(void)
{
	t_wall	*wall;

	wall = (t_wall*)malloc(sizeof(t_wall));
	wall->wall_c = (t_cordinate *)malloc(sizeof(t_cordinate) * 4);
	wall->next = NULL;
	return (wall);
}
void	wall_cordinate(t_wall *wall, double x, double y)
{
	wall->wall_c[0].x = (x) * size;
	wall->wall_c[0].y = (y) * size;
	wall->wall_c[1].x = (x + 1) * size;
	wall->wall_c[1].y = (y) * size;
	wall->wall_c[2].x = (x) * size;
	wall->wall_c[2].y = (y + 1) * size;
	wall->wall_c[3].x = (x + 1) * size;
	wall->wall_c[3].y = (y + 1) * size;
}
t_wall	*add_wall(t_wall *wall, double x, double y)
{
	t_wall	*wall_node;
	t_wall	*temporaire_wall;

	if (wall->next ==  NULL)
		wall_cordinate(wall, 0, 0);
	temporaire_wall = (t_wall *)malloc(sizeof(t_wall));
	temporaire_wall->next = NULL;
	temporaire_wall->wall_c = (t_cordinate *)malloc(sizeof(t_cordinate) * 4);
	wall_cordinate(temporaire_wall, x, y);
	wall_node = wall;
	while (wall_node->next)
		wall_node = wall_node->next;
	wall_node->next = temporaire_wall;
	return (wall);
}


void	get_wall_coord(t_struct *cub)
{
	int	x;
	int	y;

	cub->wall = create_Wall_node();
	y = -1;
	while (cub->.map[++y])
	{
		x = -1;
		while (cub->map[y][++x])
		{
			if (cub->map[y][x] == '1')
			{
				if (y != 0 || x != 0)
					cub->wall = add_wall(cub->wall, (double)x, (double)y);
			}
		}
	}
}