void Delay(unsigned int xms)		//@11.0592MHz
	//括号内为毫秒
{
	unsigned char i, j;

	while(xms)
	{	
		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
		xms--;
	}
}