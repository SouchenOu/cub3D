
/*

https://www.desmos.com/calculator/8imkdqdavd

the pos of the player could be any pos 
it could be btwn the gridlines
or on one of the gridline
---> this is just to check if the player pos was btwn
gridlines so we can add the right distance  for the first initial 
gridline hitting 

* >>>> horizontal <<<< *
find where is the pos of the player btwn the horizontal 
lines or on the one of the gridlines
?       (y - 1) < posY && (y + 1) > posY

----- UP
if player was looking up then
? h_initial = posY - (y - 1);
rayY - h_initial;

----- DOWN
if player was looking down then
? h_initial = (y + 1) - posY;
rayY + h_initial;

* >>>> vertical <<<< *
find where is the pos of the player btwn the vertical 
lines or on the one of the gridlines
?       (x - 1) < posX && (x + 1) > posX

----- RIGHT
if player is looking right then 
? v_initial = (x + 1) - posX;
rayX + v_initial;

----- LEFT
if player is looking left then
? v_initial = posX - (x - 1);
rayX - v_initial;

*/



void	initial(t_struct *cub)
{
	cub->mlx_info.height = 0;
	cub->mlx_info.width = 0;
    cub->cord.x = 100.00;
	cub->cord.y = 220.00;
    cub->vect.x = cos(deg_rad(280.00));
	cub->vect.y = -sin(deg_rad(280.00));
	cub->vect.pos = 280.00;
    cub->i_dis.h_down = 0.00;
	cub->dire.up = 0.00;
	cub->dire.left = 0.00;
	cub->dire.right = 0.00;
}

void find_pos(t_struct *cub){

    double	i;
    double  j;
    cub->virtical_num = cub->map_width;
    cub->horizontal_num= cub->map_height; 

	i = 0;
    j = 0;
	while (i <= (double)cub->horizontal_num)
	{
		if (cub->cord.y < ((i + 1) * size) && cub->cord.y > (i * size))
		{
			cub->dire.up = cub->cord.y - (i * size);
			cub->dire.down = ((i + 1) * size) - cub->cord.y;
		}
        i++;
	}

	while (j <= (double)cub->virtical_num)
	{
		if ((j * size) < cub->cord.x && ((j + 1) * size) > cub->cord.x)
		{
			cub->dire.left = cub->cord.x - (j * size);
			cub->dire.right = ((j + 1) * size) - cub->cord.x;
		}
	}
}


