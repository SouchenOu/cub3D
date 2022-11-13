/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:56:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/13 20:22:26 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# define PI 3.14159265359
# define W_WIDTH 1020
# define W_HEIGHT 580
# define RIGHT 82
# define LEFT 76
# define UP 85
# define DOWN 68
# define UD 50
# define LR 60
# define N 0
# define S 1
# define W 2
# define E 3
# define H 8
# define V 10
# define size_GRID 64.00
# define rotationAngle 3.14159265359 / 2

typedef struct wall t_wall;
typedef struct s_struct t_struct;

typedef struct s_floor
{
	int r;
	int g;
	int b;
}	t_floor;

typedef struct s_ceilling
{
	int r;
	int g;
	int b;
}	t_ceilling;

typedef struct s_dirct
{
	char *north_path;
	char *south_path;
	char *west_path;
	char *east_path;
}	t_dirct;
typedef struct  s_player{
	int position_x;
	int position_y;
	int rotation_angle;
	
}  t_player;

typedef struct vector
{
	double	pos;
	double	x;
	double	y;
}	t_vector;
typedef struct cordinate
{
	double	x;
	double	y;
}	t_cordinate;

typedef struct wall
{
	t_cordinate			*wall_c;
	t_wall				*next;
}	t_wall;

typedef struct mlx
{
	void	*window;
	void	*mlx;
	void	*width;
	void	*height;
}	t_mlx;

typedef struct direction
{
	double	up;
	double	down;
	double	right;
	double	left;
}	t_direction;

typedef struct ray
{
	double			ray_looking_angle;
	int				num;
	t_cordinate		ray_cordinate;
	t_cordinate		offset;
	double			tang;
	t_cordinate		horizontal_cord;
	t_cordinate		virt_cord;
	t_cordinate		ray_cord_temp;
	double			horizontal_distance;
	double			virtical_distance;
	t_struct		*cub;
	int				number_to_check;
	double			final_distance;
	int				dir;
	char	 		test;
}	t_ray;

typedef struct s_struct
{
	char			**map;
	int				map_height;
	int				map_width;
	int				height;
	int				width;
	int				len_ofmap;
	void			*mlx_ptr;
    void			*win_ptr;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				shift_x;
	int				shift_y;
	float			cos_x;
	float			sin_y;
	int				zom;
	int				direction;
	int				check_buffer;
	int 			looking_angle;
	int				NB_rays;
	int 			FOV;
	int 			color;
	int 			checkColorMap;
	unsigned int	**buffer;
	int				horizontal_num;
	int 			virtical_num;
	unsigned int 			**array;
	t_wall	 		*wall;
	t_cordinate 	cord;
	t_vector		vect;
	t_player 		player;
	t_mlx 			mlx_info;
	t_ray			*raycast;
	t_ceilling 		clg;
	t_floor			flr;
	t_dirct			drct;
	t_direction 	dire;
}	t_struct;




int     get_height(char *map_file);
int		get_width(char *map_file, int height);
char    *ft_check_map(t_struct *cub);
char	*get_next_line(int fd);
void	ft_read_maps(char *map_file, t_struct *ptr);
char    *ft_check_texture(t_struct *cub, char *dirct, int len);
char    *ft_search_innewmap(char **new_map, char *search, int len_ofsrch);
int		ft_check_alltextures(t_struct *cub);
char    **ft_check_florclg(t_struct *cub, char *flor_clg, int len);
int		ft_check_rgb(t_struct *cub);
int		ft_check_double(t_struct *cub, char *dirct, int len);
int		ft_check_alldouble(t_struct *cub);
char    **ft_jump_lines(t_struct *cub);
int 	ft_check_bgnend(char *data);
char	*ft_strdup_map(const char *s1, int len);
int		ft_check_openmap(char **data);
char    **ft_split_map(t_struct *cub);
char    *ft_search_inmap(t_struct *cub, char *search, int len_ofsrch);
void    ft_draw_map(t_struct *cub);
void 	player_position(t_struct *cub);
int		player_move(int key, t_struct *p);
void 	update_ptayer(t_struct *cub);
void 	print(char **str);
double	degrees_to_radians(double a);
double	limite_angle(double a);
double	pyt(double x1, double x2, double y1, double y2);
void 	find_pos_player(t_struct *cub);
void	check_horizontal_vertical(t_ray *raycast);
int		check_limits(t_ray *raycast);
void	ray_cordinate(t_ray *raycast, int direction);
void	check_if_wall_and_cal_dis(t_ray *raycast, int direction);
void	raycast(t_struct *cub);
t_wall	*create_Wall_node(void);
void	wall_cordinate(t_wall *wall, double x, double y);
t_wall	*add_wall(t_wall *wall, double x, double y);
void	ft_get_wall_cordinate(t_struct *cub);
void ft_buffer(t_struct *cub);
#endif