/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:56:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/19 00:06:18 by souchen          ###   ########.fr       */
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
# define W_WIDTH 1500
# define W_HEIGHT 1000
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
# define size_GRID 50.00
# define rotationAngle 3.14159265359 / 2


/*
** Keyboard LETTERS
*/

# define K_A 0
# define K_B 11
# define K_C 8
# define K_D 2
# define K_E 14
# define K_F 3
# define K_G 5
# define K_H 4
# define K_I 34
# define K_J 38
# define K_K 40
# define K_L 37
# define K_M 46
# define K_N 45
# define K_O 31
# define K_P 35
# define K_Q 12
# define K_R 15
# define K_S 1
# define K_T 17
# define K_U 32
# define K_V 9
# define K_W 13
# define K_X 7
# define K_Y 16
# define K_Z 6

/*
** Keyboard ARROWS
*/

# define K_AR_L 123
# define K_AR_R 124
# define K_AR_U 126
# define K_AR_D 125

/*
** Keyboard NUMPAD
*/

# define K_NP_DIV 75
# define K_NP_MUL 67
# define K_NP_MIN 78
# define K_NP_PLU 69
# define K_NP_1	83
# define K_NP_2	84
# define K_NP_3	85
# define K_NP_4	86
# define K_NP_5	87
# define K_NP_6	88
# define K_NP_7	89
# define K_NP_8	91
# define K_NP_9	92

/*
** Keyboard MISC
*/

# define K_SP 49
# define K_ESC 53
# define K_TAB 48

/*
** Mouse
*/

# define M_CLK_L 1
# define M_CLK_R 3
# define M_CLK_M 2
# define M_SCR_U 4
# define M_SCR_D 5

typedef struct wall t_wall;
typedef struct s_struct t_struct;
typedef struct s_ray t_ray;

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
	
	double	position_x;
	double 	position_y;
	double 	rottAngle;
	double  rottSpeed;
	int 	walkDrctn;
	int		walkDown;
	
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

typedef struct s_play
{
	t_cordinate	cord;
	t_vector	vect;
}	t_play;



typedef struct wall
{
	t_cordinate			*wall_c;
	t_wall				*next;
}	t_wall;

typedef struct mlx
{
	void	*window;
	void	*mlx_ptr;
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
	int				check;
	double 			looking_angle;
	int				NB_rays;
	int 			FOV;
	int 			color;
	int 			checkColorMap;
	char			*arrayColor;
	unsigned int	**colorBuffer;
	int				horizontal_num;
	int 			virtical_num;
	int 			scaleWidth;
	int 			scaleHeight;
	t_wall	 		*wall;
	t_cordinate 	cord;
	t_vector		vect;
	t_player 		player;
	t_mlx 			mlx;
	t_ray			*raycast;
	t_ceilling 		clg;
	t_floor			flr;
	t_dirct			drct;
	t_direction 	dire;
	t_play 			p;
}	t_struct;


typedef struct s_ray
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
	char	 		*test;
	double 			dest;
	double			wallStripHeight;
	t_wall 			*wall;
}	t_ray;



int 	ft_count_height(char **data);
void    draw_cub(t_struct *ptr, int x, int y, int color);
void    ft_draw_map(t_struct *cub);
void 	player_position(t_struct *cub);
int		player_move(int key, t_struct *p);
void 	update_ptayer(t_struct *cub);
void	check_horizontal_vertical(t_ray *raycast);
int		check_limits(t_ray *raycast);
int		is_it_wall(t_ray *raycast, char *direction);
double	find_x_or_y(t_ray *raycast, char *destination);
void	check_if_wall_and_cal_dis(t_ray *raycast, char *direction);
int		ft_strcmp(char *s1, char *s2);
char    *ft_search_inmap(t_struct *cub, char *search, int len_ofsrch);
char    *ft_search_innewmap(char **new_map, char *search, int len_ofsrch);
char    **ft_split_map(t_struct *cub);
char    *ft_check_texture(t_struct *cub, char *dirct, int len);
int 	ft_check_alltextures(t_struct *cub);
char    **ft_check_florclg(t_struct *cub, char *flor_clg, int len);
int 	ft_check_rgb(t_struct *cub);
int 	ft_check_double(t_struct *cub, char *dirct, int len);
int 	ft_check_alldouble(t_struct *cub);
char    **ft_jump_lines(t_struct *cub);
int 	ft_check_bgnend(char *data);
int 	ft_len_ofline(char *str);
int 	count_direction(char **str);
int		ft_check_map(t_struct *cub);
int 	ft_check_openmap(char **data);
void 	find_pos_player(t_struct *cub);
double	degrees_to_radians(double a);
double	limite_angle(double a);
double	pyt(double x1, double x2, double y1, double y2);
void	ray_cordinate(t_ray *raycast, int direction);
void	lets_do_raycast(t_ray *raycast, int x);
void	raycast(t_struct *cub);
char 	*get_next_line(int fd);
int		get_height(char *map_file);
int		get_width(char *map_file, int height);
int		ft_read_maps(char *map_file, t_struct *cub);
t_wall	*create_Wall_node(void);
void	wall_cordinate(t_wall *wall, double x, double y);
t_wall	*add_wall(t_wall *wall, double x, double y);
void	ft_get_wall_cordinate(t_struct *cub);
void 	ft_colorBuffer(t_struct *cub);
void 	print(char **str);
void 	initial(t_struct *cub);
void	ft_ray(t_struct *cub);
void 	initial_every_ray(t_struct *cub, t_ray *raycast, double looking_angle);
void	my_mlx_pixel_put(t_struct *ptr, int x, int y, long color);
void	print_node(t_wall *wall);
char	*no_new_line(char *line);
void	move_player(t_struct *cub);
int		move(int key, void *param);
void 	check_horizontal(t_ray *raycast);
void	check_vertical(t_ray *raycast);
void check_vertical_horizontal(t_ray *raycast, t_struct *cub);
int check_with_walls(t_wall *wall, t_cordinate cord, char *direction);
void directionOfPlayer(t_struct *cub);
void    ft_draw_map(t_struct *cub);
void ddaForLine(t_struct *cub,int x_0, int y_0, int x_1, int y_1, int color);



















#endif