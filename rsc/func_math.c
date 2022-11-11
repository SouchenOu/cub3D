double	deg_rad(double a)
{
	return ((a * 3.14159265359) / 180.000);
}

double	lmt_angle(double a)
{
	if (a > 359.00)
		a -= 360.00;
	else if (a < 0.00)
		a += 360.00;
	return (a);
}

double	pythg(double x1, double x2, double y1, double y2)
{
	return (sqrt(((y2 - y1) * (y2 - y1)) + ((x2 - x1) * (x2 - x1))));
}