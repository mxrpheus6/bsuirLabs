double my_sqrt(double a)
{
	double x0 = a;
	double accuracy = 0.0000001;
	double x1 = (x0 + a / x0) / 2;
	double d = x0 - x1;
	if (d < 0)
	{
		d = -d;
	}
	while (d >= 2 * accuracy && d * d >= 2 * accuracy)
	{
		x0 = x1;
		x1 = (x0 + a / x0) / 2;
		d = x0 - x1;
		if (d < 0)
		{
			d = -d;
		}
	}
	return x1;
}