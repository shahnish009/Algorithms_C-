#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <climits>
#include <iomanip>

using namespace std;

void allocate_memory(int);							//allocates memory dynamically
void allocate_values(int);							//allocates random float values
void allocate_zero(int, int);							//allocates additional zeroes when not a power of 2
void print_matrix(float **, int);						//prints out the contents of matrix
void free_memory(int);								//frees the dynamically allocated memory
void strassensMultiplication(float **, float **, int, int);			//implements strassens matrix multiplication
float ** auxiliary_strassens(float **, float **, int);				//auxiliary function that's recursively called as a process of strassens miltiplication
float ** divide_matrix(float **, int, int, int);				//divides matrix
float ** add_matrix(float **, float **, int);					//matrix addition
float ** sub_matrix(float **, float **, int);					//matrix subtraction
float ** compose_matrix(float **, float **, float **, float **, int);		//implements compose so as to get desired result from small instances
void standardMultiplication(float **, float **, int, int);			//implements standard matrix multiplication
float ** auxiliary_standard(float **, float **, int);				//auxiliary function to implement standard matrix multiplication

float ** matrix_a;
float ** matrix_b;
float ** matrix_strassen;
float ** matrix_standard;

int main(int argc, char * argv[])
{
	srand(time(NULL));
	if (argc == 2)
	{
		int n = atoi(argv[1]);

		if (n > 0)
		{
			if ((n & (n - 1)) == 0)					//condition to check if n is a power of 2
			{
				allocate_memory(n);
				allocate_values(n);

				strassensMultiplication(matrix_a, matrix_b, n, n);
				standardMultiplication(matrix_a, matrix_b, n, n);

				free_memory(n);
			}
			else							//condition above is false so n is not a power of 2
			{
				int new_n = 1;					//computes the nearest power of 2 greater than n
				while(new_n < n){ new_n *= 2; }
				cout<<"NEW: "<<new_n<<"\n";

				allocate_memory(new_n);
				allocate_values(n);
				allocate_zero(n, new_n);

				strassensMultiplication(matrix_a, matrix_b, n, new_n);
				standardMultiplication(matrix_a, matrix_b, n, new_n);

				free_memory(new_n);
			}
		}
		else{cout<<"Please enter <value of n> greater than 0\n";}
	}
	else{cout<<"Just Enter: ./strassen.out <value of n>\n";}
	return 0;
}

void allocate_memory(int n)							//allocates memory to matrices dynamically
{
	matrix_a = new float * [n];
        matrix_b = new float * [n];
        matrix_strassen = new float * [n];
        matrix_standard = new float * [n];

	for (int i = 0; i < n; i++)
	{
		matrix_a[i] = new float[n];
                matrix_b[i] = new float[n];
                matrix_strassen[i] = new float[n];
                matrix_standard[i] = new float[n];
	}
}

void free_memory(int n)								//frees the dynamically allocated memory to matrices
{
	for (int i = 0; i < n; ++i)
	{
		delete [] matrix_a[i];
		delete [] matrix_b[i];
		delete [] matrix_strassen[i];
		delete [] matrix_standard[i];
	}
	delete [] matrix_a;
        delete [] matrix_b;
        delete [] matrix_strassen;
        delete [] matrix_standard;
}

void allocate_values(int n)							//allocates float values ranging from -5.00 to 5.00 to the initial 2 matrices
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			matrix_a[i][j] = (((float)rand()/RAND_MAX) * 10) - 5;
			matrix_b[i][j] = (((float)rand()/RAND_MAX) * 10) - 5;
		}
	}
	cout<<"\nMatrix A:\n";
	print_matrix(matrix_a, n);

	cout<<"\nMatrix B:\n";
	print_matrix(matrix_b, n);
}
void allocate_zero(int n, int new_n)						//allocates additional zeroes when n is not a power of 2
{
        for (int i = n; i < new_n; i++)
        {
                for (int j = 0; j < new_n; j++)
                {
                        matrix_a[i][j] = 0;
			matrix_b[i][j] = 0;
                }
        }
        for (int i = 0; i < new_n; i++)
        {
                for (int j = n; j < new_n; j++)
                {
                        matrix_a[i][j] = 0;
                        matrix_b[i][j] = 0;
                }
        }
}
void print_matrix(float ** matrix, int n)					//prints the contents of the matrix
{
	for (int i = 0; i < n; i++)
	{
		cout<<"\n";
		for (int j = 0; j < n; j++)
		{
			cout<<"\t" << fixed << setprecision(2) << matrix[i][j];		//prints float number to 2 decimal places
		}
		cout<<"\n";
	}
}
void strassensMultiplication(float ** matrix1, float ** matrix2, int n, int new_n)	//implements strassens matrix multiplication
{
	if (n == new_n)
	{
		matrix_strassen = auxiliary_strassens(matrix1, matrix2, n);
		cout<<"\n\nStrassen's Multiplication Output: \n";
		print_matrix(matrix_strassen, n);
	}
	else
	{
		matrix_strassen = auxiliary_strassens(matrix1, matrix2, new_n);
		cout<<"\n\nStrassen's Multiplication Output: \n";
		print_matrix(matrix_strassen, n);
	}
}

float ** auxiliary_strassens(float ** matrix1, float ** matrix2, int n)			//auxiliary function used for the recursive calls as a part of the strassens multiplication algo
{
	if (n == 1)									//if n = 1; simply return the multiplication
	{
		matrix_strassen[0][0] = matrix1[0][0] * matrix2[0][0];
		return matrix_strassen;
	}
	if (n == 2)									//if n = 2; compute the values
	{
		float m1 = (matrix1[0][0] + matrix1[1][1]) * (matrix2[0][0] + matrix2[1][1]);
		float m2 = (matrix1[1][0] + matrix1[1][1]) * matrix2[0][0];
		float m3 = matrix1[0][0] * (matrix2[0][1] - matrix2[1][1]);
		float m4 = matrix1[1][1] * (matrix2[1][0] - matrix2[0][0]);
		float m5 = (matrix1[0][0] + matrix1[0][1]) * matrix2[1][1];
		float m6 = (matrix1[1][0] - matrix1[0][0]) * (matrix2[0][0] + matrix2[0][1]);
		float m7 = (matrix1[0][1] - matrix1[1][1]) * (matrix2[1][0] + matrix2[1][1]);

		float c11 = m1 + m4 + m7 - m5;
		float c12 = m3 + m5;
		float c21 = m2 + m4;
		float c22 = m1 + m3 + m6 - m2;
		float * t11 = &c11;
                float * t12 = &c12;
                float * t21 = &c21;
                float * t22 = &c22;

		return compose_matrix(&t11, &t12, &t21, &t22, n);


	}
	else										//if n > 2; divides matrices appropriately and calls the function recursively
	{
		float ** a11 = divide_matrix(matrix1, 0, 0, n/2);
		float ** a12 = divide_matrix(matrix1, 0, n/2, n/2);
		float ** a21 = divide_matrix(matrix1, n/2, 0, n/2);
                float ** a22 = divide_matrix(matrix1, n/2, n/2, n/2);

                float ** b11 = divide_matrix(matrix2, 0, 0, n/2);
                float ** b12 = divide_matrix(matrix2, 0, n/2, n/2);
                float ** b21 = divide_matrix(matrix2, n/2, 0, n/2);
                float ** b22 = divide_matrix(matrix2, n/2, n/2, n/2);

		float ** m1 = auxiliary_strassens(add_matrix(a11, a22, n/2), add_matrix(b11, b22, n/2), n/2);
                float ** m2 = auxiliary_strassens(add_matrix(a21, a22, n/2), b11, n/2);
                float ** m3 = auxiliary_strassens(a11, sub_matrix(b12, b22, n/2), n/2);
                float ** m4 = auxiliary_strassens(a22, sub_matrix(b21, b11, n/2), n/2);
                float ** m5 = auxiliary_strassens(add_matrix(a11, a12, n/2), b22, n/2);
                float ** m6 = auxiliary_strassens(sub_matrix(a21, a11, n/2), add_matrix(b11, b12, n/2), n/2);
                float ** m7 = auxiliary_strassens(sub_matrix(a12, a22, n/2), add_matrix(b21, b22, n/2), n/2);

		float ** c11 = sub_matrix(add_matrix(add_matrix(m1, m4, n/2), m7, n/2), m5, n/2);
		float ** c12 = add_matrix(m3, m5, n/2);
		float ** c21 = add_matrix(m2, m4, n/2);
		float ** c22 = sub_matrix(add_matrix(add_matrix(m1, m3, n/2), m6, n/2), m2, n/2);

		return compose_matrix(c11, c12, c21, c22, n);
	}
}

float ** divide_matrix(float ** matrix, int row, int col, int size)			//function to divide the matrix
{
	float ** div;
	div = new float * [size];
        for (int i = 0; i < size; i++)
        {
		div[i] = new float[size];
        }
	for (int i = row; i < row + size; i++)
	{
		for (int j = col; j < col + size; j++)
		{
			div[i - row][j - col] = matrix[i][j];
		}
	}
	return div;
}
float ** add_matrix(float ** matrix1, float ** matrix2, int size)			//function to add two matrices
{
	float ** add;
        add = new float * [size];
        for (int i = 0; i < size; i++)
        {
                add[i] = new float[size];
        }
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			add[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
	return add;
}

float ** sub_matrix(float ** matrix1, float ** matrix2, int size)			//function to subtract two matrices
{
        float ** sub;
        sub = new float * [size];
        for (int i = 0; i < size; i++)
        {
                sub[i] = new float[size];
        }
        for (int i = 0; i < size; i++)
        {
                for (int j = 0; j < size; j++)
                {
                        sub[i][j] = matrix1[i][j] - matrix2[i][j];
                }
        }
        return sub;
}
float ** compose_matrix(float **a, float **b, float **c, float **d, int size)		//function to compose large matrix from the smaller ones
{
        float ** compose;
        compose = new float * [size];
        for (int i = 0; i < size; i++)
        {
                compose[i] = new float[size];
        }

	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			if(i < size/2)
			{
				if(j < size/2)
				{
					compose[i][j] = a[i][j];
				}
				else
                                {
                                        compose[i][j] = b[i][j - size/2];
                                }

			}
                        else
                        {
                                if(j < size/2)
                                {
                                        compose[i][j] = c[i-size/2][j];
                                }
                                else
                                {
                                        compose[i][j] = d[i-size/2][j - size/2];
                                }
			}

		}
	}
	return compose;
}

void standardMultiplication(float ** matrix1, float ** matrix2, int n, int new_n)	//implements standard matrix multiplication
{
        matrix_standard = auxiliary_standard(matrix1, matrix2, new_n);
        cout<<"\n\nStandard Multiplication Output: \n";
        print_matrix(matrix_standard, n);
}

float ** auxiliary_standard(float ** matrix1, float **matrix2, int n)			//auxiliary function to implement standard matrix multiplication
{
	float ** standard;
	standard = new float * [n];
        for (int i = 0; i < n; i++)
        {
		standard[i] = new float[n];
        }

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			standard[i][j] = 0;
			for(int k = 0; k < n; k++)
			{
				standard[i][j] = standard[i][j] + matrix1[i][k] * matrix2[k][j];
			}
		}
	}
	return standard;
}
