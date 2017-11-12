#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<climits>

using namespace std;

int power_2(int);								//calculate 2^k for given k
void allocate(int, int, int);							//allocate memory for the complete board dynamically
void print_tromino(int);							//print the contents of board
void free_memory(int);								//frees up the memory that is dynamically allocated
void trominoTile(int, int, int, int, int);					//functon to henerate the tromino tiles

int ** tromino_tile;

int main(int argc, char * argv[])
{
        srand(time(NULL));
        if (argc == 4)
        {
                int k = atoi(argv[1]);
		if (k < 1){cout<<"\n<value of k> should be positive\n";}
		else
		{
			if(atoi(argv[2]) == 0 || atoi(argv[3]) == 0){cout<<"\nThe <row number> and <column number> should be positive integer\n";}
			else
			{
				int n = power_2(k);
				if (n >= atoi(argv[2]) && n >= atoi(argv[3]))
				{int hole_row = atoi(argv[2]) - 1;
				int hole_col = atoi(argv[3]) - 1;

				allocate(n, hole_row, hole_col);

				trominoTile(n, hole_row, hole_col, 0, 0);
				print_tromino(n);
				free_memory(n);}
				else{cout<<"\nInvalid number of Rows and/or Columns\n";}
			}
		}
	}
	else
	{
		cout<<"\nEnterusing format: ./tromino.out <value of k> <hole position row number> <hole position column number>\n";
	}
	return 0;
}

int power_2(int k)							// function to calculate 2^k for given positive k
{
	int result = 1;
	for(int i = 0; i < k; i++)
	{
		result = result * 2;
	}
	return result;
}
void allocate(int n, int x, int y)					//allocate memory dynamically to the board
{
	tromino_tile = new int * [n];
	for (int i = 0; i < n; i++)
	{
		tromino_tile[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			tromino_tile[i][j] = -1;
		}
	}
	tromino_tile[x][y] = 100;
}
void print_tromino(int n)						//prints the contents of the tromino board
{
	for (int i = 0; i < n; i++)
	{
		cout<<"\n";
		for (int j = 0; j < n; j++)
		{
			if (tromino_tile[i][j] == 100)
			{
				cout<<"\t"<<"X";
			}
			else
			{
				cout<<"\t"<<tromino_tile[i][j];
			}
		}
		cout<<"\n";
	}
}
void free_memory(int n)							//frees the memory that is dynamically allocated to the board
{
	for (int i = 0; i < n; ++i)
	{
		delete [] tromino_tile[i];
	}
	delete [] tromino_tile;
}
void trominoTile(int n, int hole_row, int hole_col, int x, int y)	//function to geneate the tromino tiles
{
	int i;
	int half = n/2;
	if (n == 2)							//base case i.e. if n = 2
	{
		if(hole_row < x + half && hole_col < y + half)
                {
                        i = rand() % 10;
                        tromino_tile[x + half][y + half - 1] = i;
                        tromino_tile[x + half][y + half] = i;
                        tromino_tile[x + half - 1][y + half] = i;
                }
                else if(hole_row < x + half && hole_col >= y + half)
                {
                        i = rand() % 10;
                        tromino_tile[x + half][y + half - 1] = i;
                        tromino_tile[x + half][y + half] = i;
                        tromino_tile[x + half - 1][y + half - 1] = i;
                }
                else if(hole_row >= x + half && hole_col < y + half)
                {
                        i = rand() % 10;
                        tromino_tile[x + half - 1][y + half] = i;
                        tromino_tile[x + half][y + half] = i;
                        tromino_tile[x + half - 1][y + half - 1] = i;
                }
                else
                {
                        i = rand() % 10;
                        tromino_tile[x + half - 1][y + half] = i;
                        tromino_tile[x + half][y + half - 1] = i;
                        tromino_tile[x + half - 1][y + half - 1] = i;
		}
	}
	else										//else assign the values to current tromino and call the function recursively
	{
                if(hole_row < x + half && hole_col < y + half)				//Top Left Quadrant
                {
                        i = rand() % 10;
                        tromino_tile[x + half][y + half - 1] = i;
                        tromino_tile[x + half][y + half] = i;
                        tromino_tile[x + half - 1][y + half] = i;

			trominoTile(half, hole_row, hole_col, x, y);
			trominoTile(half, x + half, y + half - 1, x + half, y);
			trominoTile(half, x + half, y + half, x + half, y + half);
			trominoTile(half, x + half - 1, y + half, x, y + half);
                }
                else if(hole_row < x + half && hole_col >= y + half)			//Top Right Quadrant
                {
                        i = rand() % 10;
                        tromino_tile[x + half][y + half - 1] = i;
                        tromino_tile[x + half][y + half] = i;
                        tromino_tile[x + half - 1][y + half - 1] = i;

                        trominoTile(half, hole_row, hole_col, x, y + half);
                        trominoTile(half, x + half, y + half - 1, x + half, y);
                        trominoTile(half, x + half, y + half, x + half, y + half);
                        trominoTile(half, x + half - 1, y + half - 1, x, y);


                }
                else if(hole_row >= x + half && hole_col < y + half)			//Bottom Left Quadrant
                {
                        i = rand() % 10;
                        tromino_tile[x + half - 1][y + half] = i;
                        tromino_tile[x + half][y + half] = i;
                        tromino_tile[x + half - 1][y + half - 1] = i;

                        trominoTile(half, hole_row, hole_col, x + half, y);
                        trominoTile(half, x + half - 1, y + half, x, y + half);
                        trominoTile(half, x + half, y + half, x + half, y + half);
                        trominoTile(half, x + half - 1, y + half - 1, x, y);

                }
                else									//Bottom Right Quadrant
                {
                        i = rand() % 10;
                        tromino_tile[x + half - 1][y + half] = i;
                        tromino_tile[x + half][y + half - 1] = i;
                        tromino_tile[x + half - 1][y + half - 1] = i;

                        trominoTile(half, hole_row, hole_col, x + half, y + half);
                        trominoTile(half, x + half - 1, y + half, x, y + half);
                        trominoTile(half, x + half, y + half - 1, x + half, y);
                        trominoTile(half, x + half - 1, y + half - 1, x, y);

		}
	}
}
