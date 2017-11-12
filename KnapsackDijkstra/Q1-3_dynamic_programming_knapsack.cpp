#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

void dynamic(int, int *, int *, int);
float kwf (int, int, int, int, int);
void auxilliary (int, int, int, int, int);
void sort_density (int);
bool promising (int, int, int, int, int);

struct item
{
        int num, weight, profit; bool selected;
};
int * weight; int * profit; int profit_max; int * best; int * inc;


int main(int argc, char * argv[])
{
        if (argc != 2){cout << "Please enter: ./Q1-1_brute_force_knapsack.out knapsack.txt\n";return 0;}
        int number_of_elements, knapsack_capacity;
        string line[4], temp;
        ifstream myfile (argv[1]);

        if (myfile.is_open())
        {
                int i = 0;
                while (getline (myfile, temp))
                {
                        line[i] = temp;
                        i++;
                }
                myfile.close();
        }
        else cout << "file not opened" << endl;

        number_of_elements = atoi (line[0].c_str());

        weight = new int[number_of_elements];
        profit = new int[number_of_elements];

        char * c = new char[line[1].size() + 1];
        copy(line[1].begin(), line[1].end(), c);
        c[line[1].size()] = '\0';
        char * token = strtok(c, ",");
        int i = 0;
        while (token != NULL)
        {
                weight[i] = atoi (token);
                token = strtok(NULL, ",");
                i++;
        }
        delete[] c;

        c = new char[line[2].size() + 1];
        copy(line[2].begin(), line[2].end(), c);
        c[line[2].size()] = '\0';
        token = strtok(c, ",");
        i = 0;
        while (token != NULL)
        {
                profit[i] = atoi (token);
                token = strtok(NULL, ",");
                i++;
        }
        delete[] c;

        knapsack_capacity = atoi (line[3].c_str());

        dynamic(number_of_elements, weight, profit, knapsack_capacity);

        delete[] weight;
        delete[] profit;

        return 0;
}

float kwf(int z, int w, int p, int number_of_elements, int knapsack_capacity)		//best fractional knapsack counting
{
	float max = p;

	float y[number_of_elements + 1];
	for(int i = z; i <= number_of_elements; i++){y[i] = 0;}

	while (z <= number_of_elements && w < knapsack_capacity)
	{
		if(w + weight[z] <= knapsack_capacity)
		{
			y[z] = 1;
         	w += weight[z];
			max += profit[z];
		}
		else
		{
		    y[z]= ((float) knapsack_capacity - (float) w)/ (float) weight[z];
			w = knapsack_capacity; 
			max += profit[z] * y[z];
		}
		z++;
	}
	return max;
}

void dynamic(int number_of_elements, int* weight, int* profit, int knapsack_capacity)		//dynamic 0/1 knapsack algo
{
	profit_max = 0;
	best = new int[number_of_elements + 1];
	inc = new int[number_of_elements + 1];

	for(int i = 1; i <= number_of_elements; i++){inc[i] = 0;}

	sort_density(number_of_elements);
    auxilliary(0, 0, 0, number_of_elements, knapsack_capacity);
 
	for(int i = 1; i <= number_of_elements; i++)
	{
		if(best[i] == 1){cout << "Item: " << i << "\t\tProfit: " << profit[i] << "\t\tWeight: " << weight[i] << endl;}
	}
	cout << "Maximum Profit: " << profit_max << endl;
}

void auxilliary(int z, int p, int w, int number_of_elements, int knapsack_capacity)		//recursive for dynamic
{
	if ((p > profit_max) && (w <= knapsack_capacity))
	{
		profit_max = p;
		for(int i = 1; i <= number_of_elements; i++){best[i] = inc[i];}
	}
	
	if(promising(z, w, p, number_of_elements, knapsack_capacity))
	{
		inc[z + 1] = 1;
		auxilliary(z+1, p + profit[z + 1], w + weight[z+1], number_of_elements, knapsack_capacity);
   		inc[z + 1] = 0;
		auxilliary(z + 1, p, w, number_of_elements, knapsack_capacity);
	}
}

void sort_density(int n)		//sort as per density
{
	int tempp,tempw;
	float tempd;
	float density[n + 1];
	for(int i = 1; i <= n; i++){density[i] = profit[i] / weight[i];}
	
	for(int i = 1; i < n ; i++)
	{
   		for(int j = i + 1 ; j <= n ; j++)
		{
			if(density[i]  < density[j])
       		{
				tempd = density[j];
				density[j] = density[i];
				density[i] = tempd;

				tempw = weight[j];
       			weight[j] = weight[i];
       			weight[i] =tempw;
				
				tempp = profit[j];
			    profit[j] = profit[i];
         		profit[i] = tempp;
         	}
      	}
    }
}

bool promising(int z, int w, int p, int number_of_elements, int knapsack_capacity)		//find promising or not
{
	if(w >= knapsack_capacity){return false;}
    int max = kwf(z, w, p, number_of_elements, knapsack_capacity);
	return (max > profit_max);
}
