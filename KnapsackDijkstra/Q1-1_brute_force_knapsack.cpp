#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

void bruteforce(int, int *, int *, int);

struct item
{
	int num, weight, profit; bool selected;
};
int * weight; int * profit; int xxx = 0;


int main(int argc, char * argv[])			//main function and file input and manips
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

	bruteforce(number_of_elements, weight, profit, knapsack_capacity);

	delete[] weight;
	delete[] profit;

	return 0;
}

void bruteforce(int number_of_elements, int* weight, int* profit, int knapsack_capacity)
{


	int profit_max = 0, w = 0, p = 0, k = 0;
	item * sel;
	int possibilities = 1;
	for (int i = 0; i < number_of_elements; i++){possibilities *= 2;}

	int count = 0;
	item * itm = new item[number_of_elements];
	for (int i = 0; i < number_of_elements; i++)
	{
		itm[i].num = i + 1;
		itm[i].weight = weight[i];
		itm[i].profit = profit[i];
		itm[i].selected = false;
	}
	for (int i = 1; i < possibilities; i++)
	{
		w = 0; p = 0; k = 0;
		item * tmp = new item[number_of_elements];
		int temp_count = 0;
		for (int j = 0; j < number_of_elements; j++)
		{
			if (((i >> j) & 1) != 1)
			{
				continue;
			}
			w = w + itm[j].weight;
			p = p + itm[j].profit;
			temp_count++;
			tmp[k] = itm[j];
			k++;
		}
		if (w <= knapsack_capacity)
		{
			if (p >= profit_max)
			{
				profit_max = p;
				sel = new item[temp_count];
				for (int x = 0; x < temp_count; x++)
				{
					sel[x] = tmp[x];
					sel[x].selected = true;
					count++;
				}
			}
		}
	}
	for (int i = 0; i < count; i++)
	{
		if ((sel[i].selected))
		{
			cout << "Item: " << i+1;
			cout << "\tWeight: " << sel[i].weight;
			cout << "\tProfit: " << sel[i].profit << endl;
			xxx += sel[i].weight;
		}
	}
	cout << "Total Profit: " << profit_max << "\t\tTotal Weight: " << xxx  << endl;
}
