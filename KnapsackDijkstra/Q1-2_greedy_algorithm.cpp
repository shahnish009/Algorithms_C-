#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

void greedy1(int, int *, int *, int);
void greedy2(int, int *, int *, int);
void greedy3(int, int *, int *, int);
void greedy4(int, int *, int *, int);

struct item
{
        int num, weight, profit; bool selected;
        float density;
};

int * weight; int * profit;

int main(int argc, char * argv[])
{
        if (argc != 2){cout << "Please enter: ./Q1-2_greedy_algorithm.out knapsack.txt\n";return 0;}
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

	cout << "\n\n\t\t***Greedy1: Maximum Benefit First***\n\n";
	greedy1(number_of_elements, weight, profit, knapsack_capacity);

        cout << "\n\n\t\t***Greedy2: Minimum Weight First***\n\n";
        greedy2(number_of_elements, weight, profit, knapsack_capacity);

        cout << "\n\n\t\t***Greedy3: Maximum Weight First***\n\n";
        greedy3(number_of_elements, weight, profit, knapsack_capacity);

        cout << "\n\n\t\t***Greedy4: Maximum Density First***\n\n";
        greedy4(number_of_elements, weight, profit, knapsack_capacity);

	delete[] profit;
	delete[] weight;

        return 0;
}

void greedy1(int number_of_elements, int * weight, int * profit, int knapsack_capacity)		//max profit first greedy algo
{
	int count = number_of_elements, p = 0, w = knapsack_capacity, prof[number_of_elements + 1], items[number_of_elements + 1], profit_max;

	for (int i = 1; i <= number_of_elements; i++)
	{
		items[i] = 0;
		prof[i] = profit[i];
	}

	while (count > 0)
	{
		profit_max = 1;
		for (int i = 1; i <= number_of_elements; i++)
		{
			if (prof[profit_max] == -20){profit_max++;}
			else if (prof[profit_max] < prof[i]){profit_max = i;}
		}
		if (weight[profit_max] <= w && w != 0)
		{
			w -= weight[profit_max];
			p += prof[profit_max];
			items[profit_max] = profit_max;
		}
		prof[profit_max] = -20;
		count--;
	}
	if (w == 0){cout << "Total Weight: " << knapsack_capacity << endl << "Total Profit: " << p << endl << endl;}
	else{cout << "Total Weight: " << knapsack_capacity - w << endl << "Total Profit: " << p << endl << endl;}

	for (int i = 1; i <= number_of_elements; i++)
	{
		if (items[i] != 0){cout << "Item: " << i << "\t\tWeight: " << weight[i] << "\t\tProfit: " << profit[i] << endl;}
	}
}

void greedy2 (int number_of_elements, int * weight, int * profit, int knapsack_capacity)		//min weight frst greedy algo
{
	int count = number_of_elements, p = 0, w = knapsack_capacity, wt[number_of_elements + 1], items[number_of_elements + 1], profit_min;

	for (int i = 1; i <= number_of_elements; i++)
	{
		wt[i] = weight[i];
		items[i] = 0;
	}

	while (count > 0)
	{
		profit_min = 1;

		for (int i = 1; i <= number_of_elements; i++)
		{
			if (wt[profit_min] == -20){profit_min++;}
			else if (wt[profit_min] > wt[i]){profit_min = i;}
		}

		if (w != 0 && weight[profit_min] <= w)
		{
			p += profit[profit_min];
			w -= weight[profit_min];
			items[profit_min] = profit_min;
		}
		wt[profit_min] = -20;
		count--;
	}
	if (w == 0){cout << "Total Weight: " << knapsack_capacity << endl << "Total Profit: " << p << endl << endl;}
	else{cout << "Total Weight: " << knapsack_capacity - w << endl << "Total Profit: " << p << endl << endl;}

	for (int i = 1; i <= number_of_elements; i++)
	{
		if (items[i] != 0){cout << "Item: " << i << "\t\tWeight: " << weight[i] << "\t\tProfit: " << profit[i] << endl;}
	}
}

void greedy3 (int number_of_elements, int * weight, int * profit, int knapsack_capacity)		//max weight first greedy algo
{
        int count = number_of_elements, p = 0, w = knapsack_capacity, wt[number_of_elements + 1], items[number_of_elements + 1], profit_max;

        for (int i = 1; i <= number_of_elements; i++){wt[i] = weight[i]; items[i] = 0;}

        while (count > 0)
        {
                profit_max = 1;

                for (int i = 1; i <= number_of_elements; i++)
                {
                        if (wt[profit_max] == -20){profit_max++;}
                        else if (wt[profit_max] < wt[i]){profit_max = i;}
                }

                if (w != 0 && weight[profit_max] <= w)
                {
                        p += profit[profit_max];
                        w -= weight[profit_max];
                        items[profit_max] = profit_max;
                }
                wt[profit_max] = -20;
                count--;
        }
        if (w == 0){cout << "Total Weight: " << knapsack_capacity << endl << "Total Profit: " << p << endl << endl;}
        else{cout << "Total Weight: " << knapsack_capacity - w << endl << "Total Profit: " << p << endl << endl;}

        for (int i = 1; i <= number_of_elements; i++)
        {
                if (items[i] != 0){cout << "Item: " << i << "\t\tWeight: " << weight[i] << "\t\tProfit: " << profit[i] << endl;}
        }
}

void greedy4 (int number_of_elements, int * weight, int * profit, int knapsack_capacity)		//Max density first greedy algo
{
        int count = number_of_elements, p = 0, w = knapsack_capacity, prof[number_of_elements + 1], items[number_of_elements + 1], profit_max;

        for (int i = 1; i <= number_of_elements; i++){prof[i] = (profit[i] / weight[i]); items[i] = 0;}

        while (count > 0)
        {
                profit_max = 1;

                for (int i = 1; i <= number_of_elements; i++)
                {
                        if (prof[profit_max] == -20){profit_max++;}
                        else if (prof[profit_max] < prof[i]){profit_max = i;}
                }

                if (w != 0 && weight[profit_max] <= w)
                {
                        p += profit[profit_max];
                        w -= weight[profit_max];
                        items[profit_max] = profit_max;
                }
                prof[profit_max] = -20;
                count--;
        }

        if (w == 0){cout << "Total Weight: " << knapsack_capacity << endl << "Total Profit: " << p << endl << endl;}
        else{cout << "Total Weight: " << knapsack_capacity - w << endl << "Total Profit: " << p << endl << endl;}

        for (int i = 1; i <= number_of_elements; i++)
        {
                if (items[i] != 0){cout << "Item: " << i << "\t\tWeight: " << weight[i] << "\t\tProfit: " << profit[i] << endl;}
        }
}
