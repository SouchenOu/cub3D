/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_cordinate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/17 15:38:43 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	wall_cordinate(t_wall *wall, double x, double y)
{
	wall->wall_c[0].x = (x) * size_GRID;
	wall->wall_c[0].y = (y) * size_GRID;
	wall->wall_c[1].x = (x + 1) * size_GRID;
	wall->wall_c[1].y = (y) * size_GRID;
	wall->wall_c[2].x = (x) * size_GRID;
	wall->wall_c[2].y = (y + 1) * size_GRID;
	wall->wall_c[3].x = (x + 1) * size_GRID;
	wall->wall_c[3].y = (y + 1) * size_GRID;
}
t_wall	*add_wall(t_wall *wall, double x, double y)
{
	t_wall	*wall_node;
	t_wall	*temporaire_wall;
	int i;
	i = 0;
	temporaire_wall = (t_wall *)malloc(sizeof(t_wall));
	temporaire_wall->next = NULL;
	temporaire_wall->wall_c = (t_cordinate *)malloc(sizeof(t_cordinate) * 4);
	wall_cordinate(temporaire_wall, x, y);
	wall_node = wall;
	while (wall_node->next != NULL)
		wall_node = wall_node->next;
	wall_node->next = temporaire_wall;
	return (wall);
}

// each node its an wall , it have cordinate x,y and next node (next wall)
void	ft_get_wall_cordinate(t_struct *cub)
{
	int	i;
	int	j;
	cub->wall = (t_wall*)malloc(sizeof(t_wall));
	cub->wall->wall_c = (t_cordinate *)malloc(sizeof(t_cordinate) * 4);
	cub->wall->next = NULL;
	j = 0;
	while (cub->map[j] != NULL)
	{
		i = 0;
		while (cub->map[j][i])
		{
			if (cub->map[j][i] == '1')
			{
				cub->wall = add_wall(cub->wall, (double)i, (double)j);
			}
			i++;
		}
		j++;
	}
	//print_node(cub->wall);
}
// to check if everythings okey!!
void	print_node(t_wall *wall)
{
	t_wall	*temp;
	int				i;
	int				j;

	temp = wall;
	j = 1;
	while (temp->next != NULL)
	{
		i = 0;
		while (i < 4)
		{
			printf("%d x %f, y %f\n", i + 1, temp->wall_c[i].x, temp->wall_c[i].y);
			i++;
		}
		printf("\n");
		temp = temp->next;
		j++;
	}
}