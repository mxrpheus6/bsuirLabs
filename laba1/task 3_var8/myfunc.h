double my_sqrt(double a)
{
	double accuracy = 0.00001;
	double x0 = a;
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
