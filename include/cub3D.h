/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:56:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/05 16:37:49 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"

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

typedef struct s_coordinate
{
	float x;
	float x_1;
	float y;
	float y_1;
	float	z;
	float z_1;
	
}	t_coordinate;
typedef struct s_vector
{
	int	x;
	int	y;
}t_vector;
typedef struct s_img
{
	t_vector size;
	void		*img_path;

}t_img;
typedef struct s_struct
{
	char		**map;
	char		**data;
	t_ceilling 	clg;
	t_floor		flr;
	t_dirct		drct;
	int			height;
	int			width;
	int			x;
	int			y;
	int			len_ofmap;
	t_coordinate cordnt;
	void	*mlx_ptr;
    void	*win_ptr;
	t_img		img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		shift_x;
	int		shift_y;
	float	cos_x;
	float	sin_y;
	int		zom;
	void 	*win;
	void 	*mlx;
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
void print(char **str);
int	print_map(t_struct cub);
int	loading_map(t_struct cub, int ligne, int colone);
int	get_x_y(t_struct *cub);
#endif