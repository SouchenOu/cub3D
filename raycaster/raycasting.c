/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:26:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/24 19:31:19 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

/* cast all rays */
/// we use raycasting transform a limited form of data (a very simplified map or floor plan) into a 3D projection by tracing rays from the view point into the viewing volume
void drawRaysOfplyer(t_struct *cub,t_textures *txt,int x, int y, int color)
{
    int i = -1;
  //  double	sostra;
	int		wallBottomPixel ;
	double		wallTopPixel;
    int j;
    //int k;
    int o;
    o = 0;
    (void) x;
    (void) y;
    (void) color;
    cub->wallStripHeight = 0;
    double angleIncrem = (M_PI / 3) / cub->numOfRays;
    cub->ray.rayAngle = cub->player.rottAngle - (M_PI / 6); 
    (void) txt;
    //printf("data here = %d\n", txt[2].data[0]);
 
    //render ray by ray
    j = 0;
    /*while(txt[0].data[j])
    {
        printf("txt_data[%d]= %d\n", j,txt[0].data[j]);
        j++;
    }*/

    while (++i < cub->numOfRays)
    { 
        cub->ray.rayAngle = normalizeAngle(cub->ray.rayAngle);
        castAllRays(cub);
	    double correctDistance = cub->ray.Distance * cos(cub->ray.rayAngle - cub->player.rottAngle);
	    cub->wallStripHeight = (cub->scaleHeight * (W_HEIGHT)) /  correctDistance;
        double len = cub->wallStripHeight;
	    if (cub->wallStripHeight > W_HEIGHT)
		     cub->wallStripHeight = W_HEIGHT;
	    wallTopPixel = (W_HEIGHT/ 2) - ( cub->wallStripHeight/ 2);
	    if (wallTopPixel < 0)
		    wallTopPixel = 0;
	    wallBottomPixel = (W_HEIGHT / 2) + (cub->wallStripHeight / 2);
	    if (wallBottomPixel >= W_HEIGHT)
		    wallBottomPixel = W_HEIGHT - 1;
        /*if(txt->img_height > 64)
            txt->img_height = 64;
        if(txt->img_width > 64)
            txt->img_width = 64;*/
	    o = (wallTopPixel - 1);
        double textureOffsetX ;
        double textureOffsetY;
        if(cub->ray.check == 1)
        {
                textureOffsetX = cub->ray.vrtclWallHitY;
        }else{
                textureOffsetX = cub->ray.horzWallHitX;
        }

        int j = 0;
        while(j < wallTopPixel)
        {
            cub->addr[(W_WIDTH * j) + i] = (cub->clg.r << 16) + (cub->clg.g << 8) + (cub->clg.b);
            j++;
        }
        textureOffsetX /= cub->scaleHeight;
        textureOffsetX -= floor(textureOffsetX);
        textureOffsetX *= cub->texture_width;
        o = wallTopPixel;
        while (o < wallBottomPixel)
        {
            int distanceFromTop = o + ((len / 2) - (W_HEIGHT/2));
            if (distanceFromTop < 0)
                distanceFromTop = 0;

            textureOffsetY = (distanceFromTop) * ((double)cub->texture_height/ len);
            textureOffsetY = floor(textureOffsetY);

            unsigned int texturecolor = 0;
            //= cub->wallTexture[(cub->texture_width * textureOffsetY) + textureOffsetX];
            // printf("*** X : %d - Y : %d\n", (int)textureOffsetX, (int)(cub->texture_width * textureOffsetY));
            // printf("texture_offsetx = %f\n", textureOffsetX);
            // printf("texture_offsetY = %f\n", textureOffsetY);
            // printf("img_width = %d\n",txt->img_width);
            // printf("img_width = %d\n",txt->img_height);
            //printf("data[0] = %d\n", txt[0].data[(int)(txt[0].img_width * textureOffsetY) + (int)textureOffsetX]);
            if(cub->ray.check == 1)
            {
                //printf("here1\n");
                // texturecolor = cub->data[(int)(cub->texture_width * textureOffsetY) + (int)textureOffsetX];
                texturecolor = cub->texture[0].data[(int)(cub->texture[0].img_width * textureOffsetY) + (int)textureOffsetX];
                //printf("width_txt = %d\n", txt[0].img_width);
                //printf("here txt data = %d\n",txt[0].data[(int)(txt->img_width * textureOffsetY) + (int)textureOffsetX] );
            }
            else if(cub->ray.check  == 2)
            {
      
                //printf("here2\n");
                // texturecolor = cub->data[(int)(cub->texture_width * textureOffsetY) + (int)textureOffsetX];
                texturecolor = cub->texture[1].data[(int)(cub->texture[1].img_width * textureOffsetY) + (int)textureOffsetX];
                // texturecolor = cub->wallTexture[(int)(cub->texture_width * textureOffsetY) + (int)textureOffsetX];

            }
            // printf("yes\n");

            cub->addr[(W_WIDTH * o) + i] = texturecolor;
            cub->check_test = 1;
            o++;
        }
        int n = wallBottomPixel;
        while(n < W_HEIGHT)
        {
            cub->addr[(W_WIDTH * n) + i] = (cub->flr.r << 16) + (cub->flr.g << 8) + (cub->flr.b);
            n++;
        }
        cub->ray.rayAngle += angleIncrem;
        //printf("finishe\n");
    }
	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr, cub->img, 0, 0);
} 

void drawRaysOfplyer_mini(t_struct *cub, int x, int y, int color)
{
    int i = 0;
    double angleIncrem = (M_PI / 3) / cub->numOfRays;
    cub->ray.rayAngle = cub->player.rottAngle - (M_PI / 6);  
    while (i < cub->numOfRays)
    {  
        cub->ray.rayAngle = normalizeAngle(cub->ray.rayAngle);
        castAllRays(cub);
        cub->ray.wallHit_x = (cub->ray.wallHit_x / cub->scaleWidth) * cub->mini_map.mini_scaleWidth;
        cub->ray.wallHit_y = (cub->ray.wallHit_y / cub->scaleHeight) * cub->mini_map.mini_scaleHeight;
        ddaForLine(cub, x, y, cub->ray.wallHit_x , cub->ray.wallHit_y ,color);
        cub->ray.rayAngle += angleIncrem;
        i++;
   } 
}

int abs(int n) 
{ 
    if (n > 0){
        return (n);
    }
    else {
        return (n *(-1));
    }
}
// DDA Function for line generation
void ddaForLine(t_struct *cub,int x_0, int y_0, int x_1, int y_1, int color)
{
    // calculate dstnc_x & dstnc_y
    int dstnc_x = x_1 - x_0;
    int dstnc_y = y_1 - y_0;
 
    // calculate steps required for generating pixels
    int steps;
    if (abs(dstnc_x) > abs(dstnc_y))
        steps = abs(dstnc_x);
    else
        steps = abs(dstnc_y);
    // calculate increment in x & y for each steps
    float x_inc = dstnc_x / (float)steps;
    float y_inc = dstnc_y / (float)steps;
    // Put pixel for each step
    float x = x_0;
    float y = y_0;
    int i = 0;
    while (i <= steps)
    {
       my_mlx_pixel_put(cub, x, y, color);
       x += x_inc; // increment in x at each step
       y += y_inc; // increment in y at each step
       i++;
    }
}
 
 int check_wall(t_struct *cub, double x, double y)
 {
    int gred_y = (int)(y/cub->scaleHeight); /*The value to round down to the nearest integer*/
    int gred_x = (int)(x/cub->scaleWidth);
    if (gred_y < cub->heightof_minimap  && gred_x <  cub->widthof_minimap){
        if (cub->my_map[gred_y][gred_x] == '1')
            return (1);   
    }
    return (0);
 }

 double normalizeAngle(double angle)
 {
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += (2 * M_PI);
    if (angle == M_PI || angle == 0)
        angle += 0.000000000001;
    return (angle);
 }
 

double calculDistance(double wallHit_x, double wallHit_y, double x, double y)
{
    return (sqrt(pow((x - wallHit_x ),2) + pow((y - wallHit_y),2)));  
}
    
void castHrzntalRays(t_struct *cub)
{
    double x_hrzntlIntrsctn;
    double y_hrzntlIntrsctn;
    double y_incrmnt;
    double x_incrmnt;
    
    y_hrzntlIntrsctn =  floor(cub->player.position_y / cub->scaleHeight) * cub->scaleHeight;
    if (cub->ray.rayFacingDown)
        y_hrzntlIntrsctn += cub->scaleHeight;
    x_hrzntlIntrsctn = cub->player.position_x + (y_hrzntlIntrsctn - cub->player.position_y) / tan(cub->ray.rayAngle);
    y_incrmnt = cub->scaleHeight;
    if (cub->ray.rayFacingUp)
        y_incrmnt *= -1;
    if (cub->ray.rayFacingUp)
        y_hrzntlIntrsctn -= 1;
    x_incrmnt =  y_incrmnt / (tan(cub->ray.rayAngle));
    if (cub->ray.rayFacingLeft && x_incrmnt > 0)
        x_incrmnt *= -1;
    if (cub->ray.rayFacingRight && x_incrmnt < 0)
        x_incrmnt *= -1;
    bool check = false;
    while (x_hrzntlIntrsctn >= 0 && x_hrzntlIntrsctn < cub->widthofmap && y_hrzntlIntrsctn >= 0 &&y_hrzntlIntrsctn < cub->heightofmap)
    {
        if (check_wall(cub, x_hrzntlIntrsctn,y_hrzntlIntrsctn))
        {
            if (cub->ray.rayFacingUp)
                y_hrzntlIntrsctn += 1;
            cub->ray.horzWallHitY = y_hrzntlIntrsctn;
            cub->ray.horzWallHitX = x_hrzntlIntrsctn;
            check = true;
            break;
        }
        x_hrzntlIntrsctn += x_incrmnt;
        y_hrzntlIntrsctn += y_incrmnt;
     }
     if (!check)
     {
        cub->ray.horzWallHitX = 1e9;
        cub->ray.horzWallHitY = 1e9;
     }
}

void castVrtcalRays(t_struct *cub)
{
    double y_vrtclIntrsctn;
    double x_vrticlIntrsctn;
    double x_incrmntVrtcl;
    double y_incrmntVrtcl;
    
    x_vrticlIntrsctn =  floor(cub->player.position_x / cub->scaleWidth) * cub->scaleWidth;
    if (cub->ray.rayFacingRight)
        x_vrticlIntrsctn += cub->scaleWidth;
    y_vrtclIntrsctn = cub->player.position_y + ((x_vrticlIntrsctn - cub->player.position_x) * tan(cub->ray.rayAngle));
    x_incrmntVrtcl = cub->scaleWidth;
    if (cub->ray.rayFacingLeft)
        x_incrmntVrtcl *= -1;
    if (cub->ray.rayFacingLeft)
        x_vrticlIntrsctn -= 1;
    y_incrmntVrtcl =  x_incrmntVrtcl  * tan(cub->ray.rayAngle);
    if (cub->ray.rayFacingUp && y_incrmntVrtcl > 0)
        y_incrmntVrtcl *= -1;
    if (cub->ray.rayFacingDown && y_incrmntVrtcl < 0)
        y_incrmntVrtcl *= -1;
    bool check = false;
    while (x_vrticlIntrsctn >= 0 && x_vrticlIntrsctn < cub->widthofmap && y_vrtclIntrsctn >= 0 && y_vrtclIntrsctn <  cub->heightofmap)
    {
        if (check_wall(cub, x_vrticlIntrsctn, y_vrtclIntrsctn))
        {
            if (cub->ray.rayFacingLeft)
                 x_vrticlIntrsctn += 1;
            cub->ray.vrticlWallHitX = x_vrticlIntrsctn;
            cub->ray.vrtclWallHitY = y_vrtclIntrsctn;
            check = true;
            break;
        }
        x_vrticlIntrsctn += x_incrmntVrtcl;
        y_vrtclIntrsctn += y_incrmntVrtcl;
     }
     if (!check)
     {
        cub->ray.vrticlWallHitX = 1e9;
        cub->ray.vrtclWallHitY = 1e9;
     }
}

void castAllRays(t_struct *cub)
{
    double hrzntlDstnc = 0;
    double vrtclDstnc = 0;

    cub->ray.wallHit_x = 0;
    cub->ray.wallHit_y = 0;
    cub->ray.Distance = 0;
    cub->ray.rayFacingDown = 0;
    cub->ray.rayFacingUp = 0;
    cub->ray.rayFacingRight = 0;
    cub->ray.rayFacingLeft = 0;
    cub->ray.vrticlWallHitX = 0;
    cub->ray.vrtclWallHitY = 0;
    cub->ray.horzWallHitX = 0;
    cub->ray.horzWallHitY = 0;
    cub->ray.down = 0;
    cub->ray.up = 0;
    cub->ray.right = 0;
    cub->ray.left = 0;

    if (cub->ray.rayAngle > 0 && cub->ray.rayAngle < M_PI)
    {
        cub->ray.down = 1;
        cub->ray.rayFacingDown = 1;
    }
    else if(cub->ray.rayAngle > M_PI)
    {
        cub->ray.rayFacingUp = 1;
        cub->ray.up = 1;
    }
    if (cub->ray.rayAngle < (M_PI / 2) || cub->ray.rayAngle > ((3 * M_PI) / 2))
    {
        cub->ray.right = 1;
        cub->ray.rayFacingRight = 1;
    }
    else if(cub->ray.rayAngle > (M_PI / 2) || cub->ray.rayAngle < ((3 * M_PI) / 2) )
    {
            cub->ray.rayFacingLeft = 1;
            cub->ray.left = 1;
    }

    castVrtcalRays(cub);
    castHrzntalRays(cub);
    hrzntlDstnc = calculDistance(cub->ray.horzWallHitX, cub->ray.horzWallHitY, cub->player.position_x, cub->player.position_y);
    vrtclDstnc = calculDistance(cub->ray.vrticlWallHitX, cub->ray.vrtclWallHitY, cub->player.position_x, cub->player.position_y);
    if (hrzntlDstnc >= vrtclDstnc)
    {
        cub->ray.wallHit_x = cub->ray.vrticlWallHitX;
        cub->ray.wallHit_y = cub->ray.vrtclWallHitY;
        cub->ray.Distance  = vrtclDstnc;
          cub->ray.check = 1;
    }
    else
    {
        cub->ray.wallHit_x = cub->ray.horzWallHitX;
        cub->ray.wallHit_y = cub->ray.horzWallHitY;
        cub->ray.Distance  = hrzntlDstnc;
          cub->ray.check = 2;
    }
}
