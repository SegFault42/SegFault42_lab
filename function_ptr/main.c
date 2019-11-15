int sum(int a, int b);
int subtract(int a, int b);
int mul(int a, int b);
int div(int a, int b);

enum test
{
	exit = 0,
	help = 1,
	cover = 2
};

int main()
{
	int (*p[4]) (int x, int y);

	p[0] = sum;
	p[1] = subtract;
	p[2] = mul;
	p[3] = div;

	return (*p[cover]) (2, 3);
}

int sum(int a, int b)
{
  return a + b;
}

int subtract(int a, int b)
{
  return a - b;
}

int mul(int a, int b)
{
  return a * b;
}

int div(int a, int b)
{
  if(b)
      return a / b;
  else
      return 0;
}


