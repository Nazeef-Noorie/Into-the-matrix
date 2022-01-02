#include <stdio.h>
#include <math.h>

int i, j, q = 0;
float e1, e2, e3;

int singular(float[][25], int, int);
int multiple(float[][25], int, int);
int eqn(float[][25], int);
float determinant(float[][25], float);
void cofactor(float[][25], int, int);
void transpose_adj(float[][25], float[][25], int, int);
void transpose(float[][25], int);
void addition(float[][25], float[][25], int, int, int, int);
void subtraction(float[][25], float[][25], int, int, int, int);
void multiplication(float[][25], float[][25], int, int, int, int);
void gaussian_elimination1(float a[][25], float b[][25], int, int);
void gaussian_elimination(float a[][25], int, int);
void LCM(int a, int b, int *p, int *q);
void eigen3(float[][25]);
void eigen2(float[][25]);
void synthetic_division(float[], float, float[][25]);

int main()
{
	int s, r1, c1, v;
	float a[25][25], o[25][25];
	back:
		printf("Please enter the number of rows and columns of the matrix: \n");
	scanf("%d %d", &r1, &c1);
	printf("\nPlease enter the elements of the matrix: \n");
	for (i = 0; i < r1; i++)
	{
		for (j = 0; j < c1; j++)
		{
			scanf("%f", &a[i][j]);
		}
	}

	if (r1 == c1)
	{
		q = 1;
	}

	back_again:
		printf("\nPlease choose the type of functions: \n 1)singular\t2)multiple\t3)To solve for variables\t4)To perform gaussian eliminations\t5)For Eigen functions\n");
	printf("\nEnter the integer: ");
	scanf("%d", &s);
	switch (s)
	{
		case 1:
			if (q != 0)
				singular(a, r1, 0);
			else
				printf("\nSingular functions are valid only for square matrices.\n");
			break;
		case 2:
			multiple(a, r1, c1);
			break;
		case 3:
			if (q != 0)
				cofactor(a, r1, 1);
			else
				printf("\nThe equations in this matrix cannot be solved.\n");
			break;
		case 4:
			printf("\n\nDoes it have an echelon column/column of constants, type 1 for yes or type 0 for no? ");
			scanf("%d", &v);
			switch (v)
			{
				case 1:
					printf("enter the echelon column/column of constants:\n");

					for (i = 0; i < r1; i++)
					{
						scanf("%f", &o[i][0]);
					}

					gaussian_elimination1(a, o, r1, c1);
					break;

				case 0:
					gaussian_elimination(a, r1, c1);
					break;

				default:
					printf("Bitch get lost!!");
					break;

			}

			break;
		case 5:
			if (r1 == c1)
			{
				if (r1 == 3)
					eigen3(a);
				else if (r1 == 2)
					eigen2(a);
			}
			else
				printf("\nNo Eigen values exists");

			break;
		default:
			printf("\n Please enter a valid number\n");
			break;
	}

	printf("\n\t\t\t\t-Written by CyanidePopcorn and Hiroshima\n\n");
	printf("\n\nEnter 0 to exit ,1 to begin with new matrix, or 2 with begin with same matrix: ");
	scanf("%d", &v);
	if (v == 0)
		return 0;
	else if (v == 1)
	{
		printf("\n\n");
		goto back;
	}
	else if (v == 2)
	{
		goto back_again;
	}
	else
		printf("fuck off!!!");
}

int singular(float a[25][25], int n, int e)
{
	float k, d, t = 0;
	k = n;

	d = determinant(a, k);
	printf("\nTHE DETERMINANT IS: %f\n", d);
	for (i = 0; i < k; i++)
	{
		t += a[i][i];
	}

	printf("THE TRACE OF THE ENTERED MATRIX IS: %f\n", t);
	transpose(a, k);

	if (d == 0)
	{
		printf("\nINVERSE OF ENTERED MATRIX IS NOT POSSIBLE.\n");
	}
	else
	{
		cofactor(a, k, e);
	}
}

int multiple(float a[25][25], int r1, int c1)
{
	float b[25][25];
	int r2, c2;
	printf("Please enter the number of rows and columns of matrix b\n --> ");
	scanf("%d %d", &r2, &c2);
	printf("Please enter the elements of matrix b:\n");
	for (i = 0; i < r2; i++)
	{
		for (j = 0; j < c2; j++)
		{
			scanf("%f", &b[i][j]);
		}
	}

	int o;
	printf("Please select an operation: \n 1) addition \t\t 2)subtraction\t\t3)multiplication\n");
	scanf("%d", &o);
	switch (o)
	{
		case 1:
			addition(a, b, r1, c1, r2, c2);
			break;
		case 2:
			subtraction(a, b, r1, c1, r2, c2);
			break;
		case 3:
			multiplication(a, b, r1, c1, r2, c2);
			break;
		default:
			printf("please select a valid operation.");
			break;
	}
}

//For calculating Determinant of the Matrix 
float determinant(float a[25][25], float k)
{
	float s = 1, det = 0, b[25][25];
	int m, n, c;
	if (k == 1)
	{
		return (a[0][0]);
	}
	else
	{
		det = 0;
		for (c = 0; c < k; c++)
		{
			m = 0;
			n = 0;
			for (i = 0; i < k; i++)
			{
				for (j = 0; j < k; j++)
				{
					b[i][j] = 0;
					if (i != 0 && j != c)
					{
						b[m][n] = a[i][j];
						if (n < (k - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}

			det = det + s *(a[0][c] *determinant(b, k - 1));
			s = -1 * s;
		}
	}

	return (det);
}

//for calculating the cofactor
void cofactor(float num[25][25], int f, int e)
{
	float b[25][25], fac[25][25];
	int p, q, m, n;
	for (q = 0; q < f; q++)
	{
		for (p = 0; p < f; p++)
		{
			m = 0;
			n = 0;
			for (i = 0; i < f; i++)
			{
				for (j = 0; j < f; j++)
				{
					if (i != q && j != p)
					{
						b[m][n] = num[i][j];
						if (n < (f - 2))
							n++;
						else
						{
							n = 0;
							m++;
						}
					}
				}
			}

			fac[q][p] = pow(-1, q + p) *determinant(b, f - 1);
		}
	}

	transpose_adj(num, fac, f, e);
}

/*Finding transpose_adj of matrix*/
void transpose_adj(float num[25][25], float fac[25][25], int r, int e)
{
	float b[25][25], inverse[25][25], c[25][25], d;

	for (i = 0; i < r; i++)
	{
		for (j = 0; j < r; j++)
		{
			b[i][j] = fac[j][i];
		}
	}

	d = determinant(num, r);
	for (i = 0; i < r; i++)
	{
		for (j = 0; j < r; j++)
		{
			inverse[i][j] = b[i][j] / d;
		}
	}

	if (e == 0)
	{
		printf("\nTHE INVERSE OF THE MATRIX IS: \n");
		for (i = 0; i < r; i++)
		{
			for (j = 0; j < r; j++)
				printf("%f\t", inverse[i][j]);

			printf("\n");
		}
	}
	else if (e != 0)
	{
		printf("\nPlease enter the constant matrix\n");
		for (i = 0; i < r; i++)
			scanf("%f", &c[i][0]);

		printf("\nThe values of x, y, z are: \n");
		multiplication(inverse, c, r, r, r, 1);
	}
}

//to get the transpose of any matrix
void transpose(float A[25][25], int n)
{
	float transpose[25][25];
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			transpose[j][i] = A[i][j];
		}
	}

	printf("\nTHE TRANSPOSE OF THE MATRIX IS: \n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%f\t", transpose[i][j]);
		}

		printf("\n");
	}
}

//for adding two matrices
void addition(float a[25][25], float b[25][25], int r1, int c1, int r2, int c2)
{
	int u;
	if ((r1 == r2) && (c1 == c2))
	{
		for (i = 0; i < r1; i++)
		{
			for (j = 0; j < c1; j++)
			{
				a[i][j] = a[i][j] + b[i][j];
			}
		}

		for (i = 0; i < r1; i++)
		{
			for (j = 0; j < c1; j++)
			{
				printf("%.2f\t", a[i][j]);
				if (j == c1 - 1)
					printf("\n");
			}
		}

		printf("\nDo want to apply elimination (useful to obtain eigenvectors)?, press 1 for yes or 0 for no: ");
		scanf("%d", &u);
		if (u == 1)
			gaussian_elimination(a, 3, 3);
		else if (u == 0)
			return;

	}
	else
		printf("These matrices cannot be added.\n");
}

void subtraction(float a[25][25], float b[25][25], int r1, int c1, int r2, int c2)
{
	if ((r1 == r2) && (c1 == c2))
	{
		for (i = 0; i < r2; i++)
		{
			for (j = 0; j < c2; j++)
			{
				b[i][j] = -1 *b[i][j];
			}
		}

		addition(a, b, r1, c1, r2, c2);
	}
	else
	{
		printf("These matrices cannot be subtracted.");
	}
}

//for multiplying two matrices
void multiplication(float a[25][25], float b[25][25], int r1, int c1, int r2, int c2)
{
	int k;
	float c[25][25];

	for (i = 0; i < 25; i++)
	{
		for (j = 0; j < 25; j++)
		{
			c[i][j] = 0;
		}
	}

	if (c1 == r2)
	{
		for (i = 0; i < r1; i++)
		{
			for (j = 0; j < c2; j++)
			{
				for (k = 0; k < c1; k++)
				{
					c[i][j] += a[i][k] *b[k][j];
				}
			}
		}

		for (i = 0; i < r1; i++)
		{
			for (j = 0; j < c2; j++)
			{
				printf("%.2f\t", c[i][j]);
				if (j == c2 - 1)
					printf("\n");
			}
		}
	}
	else
		printf("These matrices cannot be multiplied.\n");
}

//for gaussian elimination for echelon matrix
void gaussian_elimination1(float a[][25], float b[][25], int r, int c)
{
	int i, j, p, q, o;

	for (j = 0; j < c; j++)
	{
		for (i = r - 1; i >= 0; i--)
		{
			if (j < i)
			{
				{
					if (a[i][j] > 0 && a[i - 1][j] > 0)
					{
						LCM(a[i][j], a[i - 1][j], &p, &q);
						for (o = 0; o < r; o++)
						{
							a[i][o] = p *a[i][o] - q *a[i - 1][o];

						}

						b[i][0] = p *b[i][0] - q *b[i - 1][0];
					}

					if (a[i][j] < 0 && a[i - 1][j] > 0)
					{
						LCM(-a[i][j], a[i - 1][j], &p, &q);
						for (o = 0; o < r; o++)
						{
							a[i][o] = p *a[i][o] + q *a[i - 1][o];

						}

						b[i][0] = p *b[i][0] + q *b[i - 1][0];
					}

					if (a[i][j] > 0 && a[i - 1][j] < 0)
					{
						LCM(a[i][j], -a[i - 1][j], &p, &q);
						for (o = 0; o < r; o++)
						{
							a[i][o] = p *a[i][o] + q *a[i - 1][o];

						}

						b[i][0] = p *b[i][0] + q *b[i - 1][0];
					}

					if (a[i][j] < 0 && a[i - 1][j] < 0)
					{
						LCM(-a[i][j], -a[i - 1][j], &p, &q);
						for (o = 0; o < r; o++)
						{
							a[i][o] = p *a[i][o] - q *a[i - 1][o];

						}

						b[i][0] = p *b[i][0] - q *b[i - 1][0];

					}
				}
			}
		}
	}

	printf("This is the augmented matrix:- \n");
	for (i = 0; i < r; i++)
	{
		printf("\t");
		for (j = 0; j < c; j++)
		{
			if (a[i][i] != 0)
				printf("%0.2f ", a[i][j] / a[i][i]);

			else
				printf("%0.2f ", a[i][j]);
			if (j == c - 1)
			{
				if (a[i][i] != 0)
					printf("%0.2f", b[i][0] / a[i][i]);
				else
					printf("%0.2f", b[i][0]);
				printf("\n");
			}
		}
	}
}

void LCM(int a, int b, int *p, int *q)
{
	*p = 1;
	*q = 1;
	for (*p = 1;
		(*p) < 100;
		(*p) ++)
	{
		for (*q = 1;
			(*q) < 100;
			(*q) ++)
		{
			if ((*p) *a == (*q) *b)
			{
				goto there;
			}
		}
	}

	there:
		return;
}

//for gaussian elimination for standard matrix
void gaussian_elimination(float a[][25], int r, int c)
{
	int i, j, p, q, o;
	for (j = 0; j < c; j++)
	{
		for (i = r - 1; i >= 0; i--)
		{
			if (j < i)
			{
				if (a[i][j] > 0 && a[i - 1][j] > 0)
				{
					LCM(a[i][j], a[i - 1][j], &p, &q);
					for (o = 0; o < r; o++)
					{
						a[i][o] = p *a[i][o] - q *a[i - 1][o];
					}
				}

				if (a[i][j] < 0 && a[i - 1][j] > 0)
				{
					LCM(-a[i][j], a[i - 1][j], &p, &q);
					for (o = 0; o < r; o++)
					{
						a[i][o] = p *a[i][o] + q *a[i - 1][o];
					}
				}

				if (a[i][j] > 0 && a[i - 1][j] < 0)
				{
					LCM(a[i][j], -a[i - 1][j], &p, &q);
					for (o = 0; o < r; o++)
					{
						a[i][o] = p *a[i][o] + q *a[i - 1][o];
					}
				}

				if (a[i][j] < 0 && a[i - 1][j] < 0)
				{
					LCM(-a[i][j], -a[i - 1][j], &p, &q);
					for (o = 0; o < r; o++)
					{
						a[i][o] = p *a[i][o] - q *a[i - 1][o];
					}
				}
			}
		}
	}

	printf("This is the augmented matrix:- \n");
	for (i = 0; i < r; i++)
	{
		printf("\t");
		for (j = 0; j < c; j++)
		{
			if (a[i][i] != 0)
				printf("%0.2f ", a[i][j] / a[i][i]);
			else
				printf("%0.2f ", a[i][j]);
			if (j == c - 1)
			{
				printf("\n");
			}
		}
	}
}

void eigen2(float a[][25])
{
	float c[10];
	c[0] = 1;
	c[1] = -1 *(a[0][0] + a[1][1]);
	c[2] = a[0][0] *a[1][1] - a[0][1] *a[1][0];
	e1 = (-1 *c[1] + sqrt((pow(c[1], 2) - 4 *c[0] *c[2]))) / (2 *c[0]);
	e2 = (-1 *c[1] - sqrt((pow(c[1], 2) - 4 *c[0] *c[2]))) / (2 *c[0]);
	printf("\n\nThe eigen values are %.2f and %.2f \n", e1, e2);
}

void eigen3(float a[][25])
{
	float c[10], x, p;
	int b = 0;
	c[0] = -1;
	c[1] = a[0][0] + a[1][1] + a[2][2];
	c[2] = -1 *(a[0][0] *a[2][2] + a[1][1] *a[2][2] + a[0][0] *a[1][1] - a[0][1] *a[1][0] - a[1][2] *a[2][1] - a[0][2] *a[2][0]);
	c[3] = a[0][0] *a[1][1] *a[2][2] - a[0][0] *a[1][2] *a[2][1] - a[0][2] *a[1][1] *a[2][0] - a[0][1] *a[1][0] *a[2][2] + a[0][1] *a[1][2] *a[2][0] + a[0][2] *a[2][1] *a[1][0];

	for (x = -10; x <= 10; x++)
	{
		p = pow(x, 3) *c[0] + pow(x, 2) *c[1] + x *c[2] + c[3];
		b++;
		if (p == 0)
		{
			e1 = x;
			synthetic_division(c, e1, a);
			break;
		}
		else if (b == 20)
			printf("\nYou're fucked.\n");
	}
}

void synthetic_division(float c[], float e1, float a[][25])
{
	int poly[6], m, r, i, q[6], j;
	float x[25][25], y[25][25], z[25][25];

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			x[i][j] = a[i][j];
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			y[i][j] = a[i][j];
		}
	}

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			z[i][j] = a[i][j];
		}
	}

	m = 3;
	float b[25][25];

	for (i = 0; i <= 3; i++)
	{
		poly[i] = c[i];
	}

	r = e1;
	q[0] = poly[0];
	for (i = 1; i <= 3; i++)
	{
		q[i] = (q[i - 1] *r) + poly[i];
	}

	for (i = 0; i < m; i++)
	{
		c[i] = q[i];
	}

	printf("\nThe eigen values are %.2f, %.2f and %.2f \n", e1, (-1 *c[1] + sqrt((pow(c[1], 2) - 4 *c[0] *c[2]))) / (2 *c[0]), (-1 *c[1] - sqrt((pow(c[1], 2) - 4 *c[0] *c[2]))) / (2 *c[0]));
	e2 = (-1 *c[1] + sqrt((pow(c[1], 2) - 4 *c[0] *c[2]))) / (2 *c[0]);
	e3 = (-1 *c[1] - sqrt((pow(c[1], 2) - 4 *c[0] *c[2]))) / (2 *c[0]);

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (i == j)
				b[i][j] = e1;
			else
				b[i][j] = 0;
		}
	}

	printf("\nA- I(e1) is: \n");
	subtraction(x, b, 3, 3, 3, 3);

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (i == j)
				b[i][j] = e2;
			else
				b[i][j] = 0;
		}
	}

	printf("\nA- I(e2) is: \n");
	subtraction(y, b, 3, 3, 3, 3);

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (i == j)
				b[i][j] = e3;
			else
				b[i][j] = 0;
		}
	}

	printf("\nA- I(e3) is: \n");
	subtraction(z, b, 3, 3, 3, 3);
}

/*THANKS FOR USING THIS PIECE OF CODE.
        WRITTEN BY CyanidePopcorn AND Hiroshima. */