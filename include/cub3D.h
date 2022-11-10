/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:56:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/09 10:55:30 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"
# define W_WIDTH 1020
# define W_HEIGHT 580
# define PI 3.14159265359
# define PIH 1.57079632679
# define PIT 4.71238898038
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
# define size 64.00
# define rotationAngle PI / 2

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
	t_wall_cordinate	*next;
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
	double		a;
	int			num;
	t_coord		ray;
	t_coord		offset;
	double		_tan;
	t_coord		h_fcord;
	t_coord		v_fcord;
	double		h_fdis;
	double		v_fdis;
	t_cub_main	*main;
	int			check_num;
	t_coord		wc_temp;
	double		f_dis;
	double		h_line;
	double		h_offset;
	int			dir;
	double		draw_end;
	double		draw_start;
}	t_ray;

typedef struct s_struct
{
	char		**map;
	int			map_height;
	int			map_width;
	int			height;
	int			width;
	int			len_ofmap;
	void	*mlx_ptr;
    void	*win_ptr;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		shift_x;
	int		shift_y;
	float	cos_x;
	float	sin_y;
	int		zom;
	int				NB_rays;
	int FOV;
	int color;
	int checkColorMap;
	unsigned int	**buffer;
	int	horizontal_num;
	int virtical_num;
	t_wall	 *wall;
	t_cordinate cord;
	t_vector	vect;
	t_player player;
	t_mlx 	mlx_info;
	t_ceilling 	clg;
	t_floor		flr;
	t_dirct		drct;
	t_direction dire;
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
void player_position(t_struct *cub);
int	player_move(int key, t_struct *p);
void update_ptayer(t_struct *cub);
void print(char **str);
#endif