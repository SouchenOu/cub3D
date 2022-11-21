/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:56:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/19 21:36:47 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>
# include "../libft/libft.h"
# define W_WIDTH 1080
# define W_HEIGHT 700

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
	char 	*north_path;
	char 	*south_path;
	char 	*west_path;
	char 	*east_path;
	
}	t_dirct;
typedef struct  s_player{
	
	double	position_x;
	double 	position_y;
	double 	rottAngle;
	double  rottSpeed;
	int 	walkDrctn;
	int		walkDown;
	
}  t_player;

typedef struct  s_ray{
	
	double 	rayAngle;
	double 	wallHit_x;
	double	wallHit_y;
	double 	Distance;
	double  rayFacingDown;
	double	rayFacingUp;
	double  rayFacingRight;
	double	rayFacingLeft;
	int		foundHorzWallHit;
	int		foundvrtclWallHit;
	double  horzWallHitX;
    double  horzWallHitY;
	double  vrticlWallHitX;
    double  vrtclWallHitY;
	double aquale;
	
}  t_ray;
typedef struct s_direction {

	double left;
	double right;
	double up;
	double down;

}t_direction;

typedef struct s_struct
{
	char		**map;
	t_ceilling 	clg;
	t_floor		flr;
	t_dirct		drct;
	int			height;
	int			width;
	int			len_ofmap;
	void		*mlx_ptr;
    void		*win_ptr;
	void		*img;
	int			*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int 		checkColorMap;
	int 		scaleHeight;
	int 		scaleWidth;
	t_player 	player;
	double		numOfRays;
	double 		rayAngle;
	unsigned int 		**color_buffer;
	t_ray       ray;
	double		rays[100000];
	int FOV;
	int check;
	double fovAngle;
	double tang;
	t_direction 	dire;
	double wallStripHeight;
	int check_test;
	double x_nextVrtcl;
	double y_nextVrtcl;
	double x_nextHrzntal;
	double y_nextHrzntal;
	double hrzntlDstnc;
	double vrtclDstnc;


	double rayx;
	double rayy;
}	t_struct;





int     get_height(char *map_file);
int		get_width(char *map_file, int height);
int	    ft_check_map(t_struct *cub);
char	*get_next_line(int fd);
int		ft_read_maps(char *map_file, t_struct *ptr);
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
void 	directionOfPlayer(t_struct *cub);
void 	draw_player(t_struct *cub, int x, int y, int color);
void 	ddaForLine(t_struct *cub,int x_0, int y_0, int x_1, int y_1, int color);
int 	check_wall(t_struct *cub, double x, double y);
void 	drawRaysOfplyer(t_struct *cub, int x, int y, int color);
int		castRays(t_struct *cub);
void 	check_nextSteep(t_struct *cub);
void	my_mlx_pixel_put(t_struct *ptr, int x, int y, long color);
void	check_downSteep(t_struct *cub);
double	normalizeAngle(double angle);
double 	calculDistance(double wallHit_X, double wallHit_y, double x, double y);
void 	castHrzntalRays(t_struct *cub);
void 	castVrtcalRays(t_struct *cub);
void 	castAllRays(t_struct *cub);
void	print(char **str);
void	lets_do_raycast(t_struct *cub, int j);
void 	ft_colorBuffer(t_struct *cub);
double	degrees_to_radians(double a);
void find_pos_player_in_gridline(t_struct *cub);
double	limite_angle(double a);
int	is_ceiling(unsigned int **buffer, int i, int k);
int	is_floor(unsigned int **buffer, int i, int k);
int	limits(t_struct *cub , double x, double y);

void calcule_distance(t_struct *cub, int test);

void	check_func(t_struct *cub, int op);





#endif