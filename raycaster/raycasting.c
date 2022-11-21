/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:26:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/20 14:51:33 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"


void	lets_do_raycast(t_struct *cub, int j)
{
    (void) j;
    /*cub->FOV = 60;
	double	sostra;
	int		i;
	int		wallBottomPixel ;
	int		wallTopPixel;


	sostra = degrees_to_radians(cub->player.rottAngle) - cub->ray.rayAngle;
	//printf("hadi = %f\n", raycast->ray_looking_angle);
	//printf("soustra = %f\n", sostra);
	if (sostra > degrees_to_radians(360))
		sostra -= degrees_to_radians(360);
	else if (sostra < degrees_to_radians(0.00))
		sostra += degrees_to_radians(360.00);
	 cub->ray.Distance =  cub->ray.Distance * cos(sostra);
	double wallStripHeight= (int)(cub->scaleHeight * (1.00 * W_HEIGHT)) /  cub->ray.Distance;
	if (wallStripHeight> (1.00 * W_HEIGHT))
		wallStripHeight= (1.00 * W_HEIGHT);
	//wallTopPixel is the top of the wall
	wallTopPixel = (W_HEIGHT/ 2) - (int)(wallStripHeight/ 2.00);
	if (wallTopPixel < 0)
		wallTopPixel = 0; // the minimum we can have is 0
		//wallBottomPixel is the Bottom or end of the wall
	wallBottomPixel = (W_HEIGHT/ 2) + (int)(wallStripHeight/ 2.00);
	if (wallBottomPixel >= W_HEIGHT)
		wallBottomPixel = W_HEIGHT - 1;
	i = (wallTopPixel - 1);*/
	//render the wall from wallTopPixel to wallBottomPixel
	/*while (i < wallBottomPixel)
	{
		//copy all the color buffer to an sdl texture
		cub->colorBuffer[i][j] = 0xFFF0000;
		cub->check = 1;
		i++;
	}*/
    // i have a top wall pixel and then i render my wall and i heve the buttom pixel then the floor
    // so from the top wall to the bottom wall i going to render my wall (that is the wall height)
    double distanceProjPlane = (W_WIDTH / 2) / tan( 60/ 2) ; 
    double projectedWallHeight = cub->scaleHeight / cub->ray.Distance * distanceProjPlane;
    int wallStripHeight = (int) projectedWallHeight;
    int wallTopPixel = (W_HEIGHT / 2) - (wallStripHeight) / 2;
    if(wallTopPixel < 0)
    {
        wallTopPixel = 0;
    }
    int wallBottomPixel = (W_HEIGHT / 2) + (wallStripHeight / 2);
    if(wallBottomPixel > W_HEIGHT)
        wallBottomPixel = W_HEIGHT;
    /*int i = 0;
    while(i < wallBottomPixel)
    {
        cub->color_buffer[i] =  0xFFF0000;
        i++;
    }*/
    // so now we should render the wall from wallTopPixel to wallBottomPixel

}



/* cast all rays */
void draw_player(t_struct *cub, int x, int y, int color)
{
    int 	x_1;
	int 	y_1;
	x_1 = x + cos(cub->player.rottAngle) * 42;
    y_1 = y + sin(cub->player.rottAngle) * 42;
    ddaForLine(cub, x, y, x_1, y_1, color);  
}

void drawRaysOfplyer(t_struct *cub, int x, int y, int color)
{
    int i = 0;
    double angleIncrem = (M_PI / 3) / cub->numOfRays;
    cub->ray.rayAngle = cub->player.rottAngle - (M_PI / 6); 
    while (i < cub->numOfRays)
    {  
        cub->ray.rayAngle = normalizeAngle(cub->ray.rayAngle);
        castAllRays(cub);
        ddaForLine(cub, x, y, cub->ray.wallHit_x, cub->ray.wallHit_y,color);
        //creat  a 3D projection of our walls (manipulate the pixel colors of our color buffer)
        // drawing the walls
        double distanceProjPlane = (W_WIDTH / 2) / tan( M_PI / 6) ; 
        double projectedWallHeight = cub->scaleHeight / cub->ray.Distance * distanceProjPlane;
        int wallStripHeight = (int) projectedWallHeight;
        int wallTopPixel = (W_HEIGHT / 2) - (wallStripHeight) / 2;
        if(wallTopPixel < 0)
        {
            wallTopPixel = 0;
        }
        int wallBottomPixel = (W_HEIGHT / 2) + (wallStripHeight / 2);
        if(wallBottomPixel > W_HEIGHT)
            wallBottomPixel = W_HEIGHT;
        int y = 0;
        while(y < wallBottomPixel)
        {
            //w_width * y means : how many rows 
            // i how is the shift in horizontal
            // each one of coloms represent each one of rays
            cub->addr[(W_WIDTH * y) + (i)] =  0xFFF0000;
            y++;
        }
            //lets_do_raycast(cub, i);
            cub->ray.rayAngle += angleIncrem;
            i++;
   } 
   /*for(int x = 0; x < W_WIDTH; x++)
   {
        for(int y = 0; y < W_HEIGHT; y++)
        {
            cub->addr[(W_WIDTH * y) + x] = cub->color_buffer[x][y];
        }

   }
   
   	mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr ,cub->img, 0, 0);*/
    /*int j;	
	i = 0;
	while (i < W_HEIGHT)
	{
		j = 0;
		while (j < W_WIDTH)
        {
            cub->addr[i * W_WIDTH + j] = cub->color_buffer[i][j];
			// i: how many pixels and colones i have
			//j is how many rays i have
			//i * W_Width + j to get the dimension in one dimensional array
			//printf("array[%d] = %d \n", i * W_WIDTH + j , cub->array[i * W_WIDTH + j]);
            j++;
        }
        i++;
	}*/
	    mlx_put_image_to_window(cub->mlx_ptr, cub->win_ptr,cub->img, 0, 0);

}



// Function for finding absolute value
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
    char **map;
    map = ft_jump_lines(cub);
    int gred_y = (int)(y/cub->scaleHeight); /*The value to round down to the nearest integer*/
    int gred_x = (int)(x/cub->scaleWidth);
    if (!map[gred_y])
        return (1);
    if ( map[gred_y][gred_x] == '1' ||  !map[gred_y])
        return (1);
    return (0);
 }

 double normalizeAngle(double angle)
 {
    // if (angle > 0)
    //     angle = fmod(angle, 2 * M_PI);
    // else
    //     angle += 2*M_PI;
    angle = fmod(angle, 2 * M_PI);
    if (angle < 0)
        angle += (2 * M_PI);
    if (angle == M_PI || angle == 0)
        angle += 0.000000000001;
    return (angle);
 }
 

double calculDistance(double wallHit_x, double wallHit_y, double x, double y)
{
    return (sqrt(pow((x - wallHit_x ),2) + pow((y- wallHit_y),2)));  
}
    
void castHrzntalRays(t_struct *cub)
{
    double x_hrzntlIntrsctn;
    double y_hrzntlIntrsctn;
    double y_incrmnt;
    double x_incrmnt;
    double x_nextHrzntal;
    double y_nextHrzntal;

    cub->ray.horzWallHitX = cub->player.position_x;
    cub->ray.horzWallHitY = cub->player.position_y;
    cub->ray.foundHorzWallHit = 0;
    y_hrzntlIntrsctn =  floor(cub->player.position_y / cub->scaleHeight) * cub->scaleHeight;
    if (cub->ray.rayFacingDown)
        y_hrzntlIntrsctn += cub->scaleHeight;
    x_hrzntlIntrsctn = cub->player.position_x + (y_hrzntlIntrsctn - cub->player.position_y) / tan(cub->ray.rayAngle);
    //    printf("%f\n",x_hrzntlIntrsctn);
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
    x_nextHrzntal = x_hrzntlIntrsctn;
    y_nextHrzntal = y_hrzntlIntrsctn;
    bool check = false;
    while (x_nextHrzntal >= 0 && x_nextHrzntal < W_WIDTH && y_nextHrzntal >= 0 && y_nextHrzntal < W_HEIGHT )
    {
        if (check_wall(cub, x_nextHrzntal, y_nextHrzntal))
        {
            // printf("hrzntal x ---> %f\n", x_nextHrzntal);
            //  printf("hrzntal x ---> %f\n", y_nextHrzntal);
            cub->ray.horzWallHitX = x_nextHrzntal;
            cub->ray.horzWallHitY = y_nextHrzntal;
            check = true;
            break;
        }
        x_nextHrzntal += x_incrmnt;
        y_nextHrzntal += y_incrmnt;
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
    double x_nextVrtcl;
    double y_nextVrtcl;
     
    cub->ray.vrticlWallHitX = 0;
    cub->ray.vrtclWallHitY = 0;
    cub->ray.foundvrtclWallHit = 0;
    x_vrticlIntrsctn =  floor(cub->player.position_x / cub->scaleWidth) * cub->scaleWidth;
    if (cub->ray.rayFacingRight)
        x_vrticlIntrsctn += cub->scaleWidth;
    y_vrtclIntrsctn = cub->player.position_y + ((x_vrticlIntrsctn - cub->player.position_x) * tan(cub->ray.rayAngle));
      //printf("%f\n",y_vrtclIntrsctn);
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
    x_nextVrtcl = x_vrticlIntrsctn;
    y_nextVrtcl = y_vrtclIntrsctn;
    bool check = false;
    while (x_nextVrtcl >= 0 && x_nextVrtcl < W_WIDTH && y_nextVrtcl >= 0 && y_nextVrtcl < W_HEIGHT)
    {
        if (check_wall(cub, x_nextVrtcl, y_nextVrtcl))
        {
            cub->ray.vrticlWallHitX = x_nextVrtcl;
            cub->ray.vrtclWallHitY = y_nextVrtcl;
            check = true;
            break;
        }
        x_nextVrtcl += x_incrmntVrtcl;
        y_nextVrtcl += y_incrmntVrtcl;
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
    if (cub->ray.rayAngle > 0 && cub->ray.rayAngle < M_PI)
        cub->ray.rayFacingDown = 1;
    else
        cub->ray.rayFacingUp = 1;
    if (cub->ray.rayAngle < (M_PI/2) || cub->ray.rayAngle > ((3 * M_PI)/2))
        cub->ray.rayFacingRight = 1;
    else
        cub->ray.rayFacingLeft = 1;
    castVrtcalRays(cub);
    castHrzntalRays(cub);
    if (cub->ray.vrtclWallHitY != 1e9 && cub->ray.vrticlWallHitX != 1e9)
        hrzntlDstnc = calculDistance(cub->ray.horzWallHitX, cub->ray.horzWallHitY, cub->player.position_x, cub->player.position_y);
    if (cub->ray.horzWallHitX != 1e9 && cub->ray.horzWallHitY != 1e9)
        vrtclDstnc = calculDistance(cub->ray.vrticlWallHitX, cub->ray.vrtclWallHitY, cub->player.position_x, cub->player.position_y);
    if (hrzntlDstnc >= vrtclDstnc)
    {
        cub->ray.wallHit_x = cub->ray.vrticlWallHitX;
        cub->ray.wallHit_y = cub->ray.vrtclWallHitY;
        cub->ray.Distance  = vrtclDstnc;
    }
    else
    {
        cub->ray.wallHit_x = cub->ray.horzWallHitX;
        cub->ray.wallHit_y = cub->ray.horzWallHitY;
        cub->ray.Distance  = hrzntlDstnc;
    }
}