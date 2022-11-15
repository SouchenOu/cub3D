/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/15 16:19:43 by souchen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/cub3D.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

char    *ft_search_inmap(t_struct *cub, char *search, int len_ofsrch)
{
    int i;

    i = 0;
    while (cub->map[i])
    {
        if (!ft_strncmp(cub->map[i], search, len_ofsrch))
            return (cub->map[i]);
        i++;
    }
    return (NULL);
}

char    *ft_search_innewmap(char **new_map, char *search, int len_ofsrch)
{
    int i;

    i = 0;
    while (new_map[i])
    {
        if (!ft_strncmp(new_map[i], search, len_ofsrch))
            return (new_map[i]);
        i++;
    }
    return (NULL);
}

char    **ft_split_map(t_struct *cub)
{
    int     i;
    int     j;
    int     len;
    int     k;
    int     l;
    char    **path;

    i = 0;
    k = 0;
    len = 0;
    path = (char **)malloc(sizeof(char *) * cub->height + 1);
    while (cub->height > i)
    {
        j = 0;
        while (cub->map[i][j])
        {
            if (cub->map[i][j] != ' ')
                len++;
            j++;
        }
        j = 0;
        l = 0;
        path[k] = ft_calloc(sizeof(char), len + 1);
        while (cub->map[i][j])
        {
            if (cub->map[i][j] != ' ')
               path[k][l++] = cub->map[i][j];
            j++;
        }
        path[k][l] = '\0';
        k++;
        i++;
    }
    return (path);
}

char    *ft_check_texture(t_struct *cub, char *dirct, int len)
{
    char    *path;
    int     fd;
    char    *ptr;
    char    *srch;
    char    **new_map;

    new_map = ft_split_map(cub);
    srch = ft_search_innewmap(new_map, dirct, len);
    path = ft_strdup(srch);
    if (!path)
    {
        //printf("hey i am her\n");
        return (NULL);
    }
    else
    {
        ptr = path;
        path = ft_substr(path, len + 1, (ft_strlen(path) - (len + 1)));
        free(ptr);
        fd = open(path, O_RDONLY);
        if (fd < 0)
            return (NULL);
    }
    return (path);
}

int ft_check_alltextures(t_struct *cub)
{
    if (ft_check_alldouble(cub) == 0)
        return (ft_putstr_fd("invalide map\n", 2), 0);
    cub->drct.north_path = ft_check_texture(cub, "NO", 1);
    if (cub->drct.north_path == NULL)
        return (ft_putstr_fd("North texureh not fount\n", 2), 0);
    cub->drct.south_path = ft_check_texture(cub, "SO", 1);
    if (cub->drct.south_path== NULL)
        return (ft_putstr_fd("South texure not fount\n", 2), 0);
    cub->drct.west_path = ft_check_texture(cub, "WE", 1);
    if (cub->drct.west_path == NULL)
        return (ft_putstr_fd("West texure not fount\n", 2), 0);
    cub->drct.east_path = ft_check_texture(cub, "EA", 1);
    if (cub->drct.east_path == NULL)
        return (ft_putstr_fd("East texure not fount\n",1), 0);
    return (1);
}

char    **ft_check_florclg(t_struct *cub, char *flor_clg, int len)
{
    char    *data;
    char    *ptr;
    char    **splt_data;
    int     i;
    int     num;

     char    *srch;
    char    **new_map;

    new_map = ft_split_map(cub);
    srch = ft_search_innewmap(new_map,  flor_clg, len);
    data = ft_strdup(srch);
    if (!data)
        return (NULL);
    ptr = data;
    data = ft_substr(data, len + 1, (ft_strlen(data) - (len + 1)));
    free(ptr);
    splt_data = ft_split(data, ',');
    i = 0;
    while (splt_data[i])
    {
        num = ft_atoi(splt_data[i]);
        if (num == -45 || (num < 0 || num > 255))
           return (NULL);
       i++ ;
    }
    if (i < 3 || i > 3)
        return (NULL);
    return (splt_data);
}

int ft_check_rgb(t_struct *cub)
{
    char    **splt_dataflr;
    char    **splt_dataclg;

    if (ft_check_alldouble(cub) == 0)
         return (0);
    splt_dataflr = ft_check_florclg(cub, "F", 1);
    if (splt_dataflr != NULL)
    {
        cub->flr.r = ft_atoi(splt_dataflr[0]);
        cub->flr.g = ft_atoi(splt_dataflr[1]);
        cub->flr.b = ft_atoi(splt_dataflr[2]);
    }
    else
        return (ft_putstr_fd("invalide color\n", 2), 0);
    splt_dataclg = ft_check_florclg(cub, "C", 1);
    if (splt_dataclg != NULL)
    {
        cub->clg.r = ft_atoi(splt_dataclg[0]);
        cub->clg.g = ft_atoi(splt_dataclg[1]);
        cub->clg.b = ft_atoi(splt_dataclg[2]);
    }
    else
        return (ft_putstr_fd("invalide color\n", 2), 0);
    return (1);
}

int ft_check_double(t_struct *cub, char *dirct, int len)
{
    int cunt;
    int i;

    i = 0;
    cunt = 0;
    while (cub->map[i])
    {
        if (!ft_strncmp(cub->map[i], dirct, len))
            cunt++;
        i++;
    }
    return (cunt);
}

int ft_check_alldouble(t_struct *cub)
{
    if (ft_check_double(cub, "NO", 2) == 2 || ft_check_double(cub, "SO", 2) == 2)
        return (0);
    if (ft_check_double(cub, "WE", 2) == 2 || ft_check_double(cub, "EA", 2) == 2)
        return (0);
    if (ft_check_double(cub, "F", 1) == 2 || ft_check_double(cub, "C", 1) == 2)
        return (0);  
    return (1);
}

char    **ft_jump_lines(t_struct *cub)
{
    int     i;
    char    **data;
    int     len;

    i = 0;
    len = 0;
    while (cub->map[len])
    {
        if (ft_strchr(cub->map[len],'N') || ft_strchr(cub->map[len], 'S') || ft_strchr(cub->map[len], 'W')|| ft_strchr(cub->map[len], 'E')|| ft_strchr(cub->map[len], 'F')|| ft_strchr(cub->map[len], 'C')|| cub->map[len][0] == '\0'|| cub->map[len][0] == '\n')
            len++;
        else
            break;    
    }
    data = ft_calloc(sizeof(char *), (cub->height - len) + 1);
    i = 0;
    while (cub->map[len])
    {
        data[i] = ft_calloc(sizeof(char), cub->width + 1);
        ft_memset(data[i], ' ', cub->width);
        data[i][cub->width] = '\0';
        ft_memmove(data[i], cub->map[len], ft_strlen(cub->map[len]));
        len++;
        i++;
    }
    cub->len_ofmap = i;
    data[i] = NULL;
    return (data);
}

int ft_check_bgnend(char *data)
{
    int i;

    i = 0;
    while (data[i])
    {
        if (data[i] == '0')
            return (0);
            i++;
    }
    return (1);
}
int ft_len_ofline(char *str)
{
    int len;
    int i;

    len = 0;
    i = 0;
    while (str[i])
    {
        if (ft_isalpha(str[i]) || ft_isdigit(str[i]))
            len++;
        i++;
    }
  return (len);  
}

int count_direction(char **str)
{
    int i;
    int len;
    int j;

    i = 0;
    j = 0;
    len = 0;
    while (str[i])
    {
        j = 0;
        while (str[i][j])
        {
            if (ft_isalpha(str[i][j]))
                len++;
            j++;
        }
       i++; 
    }
   return (len); 
}

char    *ft_check_map(t_struct *cub)
{   
    char    **data;
    int i;
    int j;

    data = ft_jump_lines(cub);
    i = 0;
    if (count_direction(data) != 1)
        return (ft_putstr_fd("too many direction", 2), NULL);
    if (ft_check_bgnend(data[0]) == 0)
        return (ft_putstr_fd("Open map\n", 2), NULL);
    if (ft_check_bgnend(data[cub->len_ofmap - 1]) == 0)
        return (ft_putstr_fd("Open map\n", 2), NULL);
    while (data[i])
    {
        j = 0;
        while (data[i][j])
        {
            if (data[i][j] != 'N' && data[i][j] != 'S' && data[i][j] != 'W' && data[i][j] != 'E' && data[i][j] != '1' && data[i][j] != '0' && data[i][j] != '2' && data[i][j] != '\0'  && data[i][j] != '\n' && data[i][j] != ' ')
                return (ft_putstr_fd("Map error\n", 2), NULL);
           j++;
        }
        i++;
    }
    if (ft_check_openmap(data))
        return (ft_putstr_fd("Open map\n", 2), NULL);
    return (NULL);
}

int ft_check_openmap(char **data)
{
    int i;
    int j;

    i = 0;
    while (data[i])
    {
        j = 0;
        while(data[i][j])
        {
            if (data[i][j] == ' ')
            {
                if (data[i][j + 1] != '1' && data[i][j + 1] != ' ' && data[i][j + 1] != '\0')
                    return (1);
            }
            if (data[i][j] == '0')
            {
                if (data[i][j + 1] == ' ' || data[i][j + 1] == '\0' || data[i - 1][j] == ' '  || data[i + 1][j] == ' ' )
                    return (1);
            }
            j++;
        }
        i++;
    }
    return (0);                                                                                                                                                                                                                                                                                    
}