#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

void dijikstra(int);

int mat[5][5];						//main distance matrix

int main(int argc, char * argv[])										//main function and all the manipulations to take input file and transform to matrix
{
        if (argc != 2){cout << "Please enter: ./Q2_dijikstra.out matrix_input.txt\n";return 0;}
        int number_of_elements, knapsack_capacity;
        string line[5], temp;
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

	char * c = new char[line[0].size() + 1];
        copy(line[0].begin(), line[0].end(), c);
        c[line[0].size()] = '\0';
        char * token = strtok(c, ",");
        int i = 0;
        while (token != NULL)
        {
                mat[0][i] = atoi (token);
                token = strtok(NULL, ",");
                i++;
        }
        delete[] c;

        c = new char[line[1].size() + 1];
        copy(line[1].begin(), line[1].end(), c);
        c[line[1].size()] = '\0';
        token = strtok(c, ",");
        i = 0;
        while (token != NULL)
        {
                mat[1][i] = atoi (token);
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
                mat[2][i] = atoi (token);
                token = strtok(NULL, ",");
                i++;
        }
        delete[] c;

	c = new char[line[3].size() + 1];
        copy(line[3].begin(), line[3].end(), c);
        c[line[3].size()] = '\0';
        token = strtok(c, ",");
        i = 0;
        while (token != NULL)
        {
                mat[3][i] = atoi (token);
                token = strtok(NULL, ",");
                i++;
        }
        delete[] c;

	c = new char[line[4].size() + 1];
        copy(line[4].begin(), line[4].end(), c);
        c[line[4].size()] = '\0';
        token = strtok(c, ",");
        i = 0;
        while (token != NULL)
        {
                mat[4][i] = atoi (token);
                token = strtok(NULL, ",");
                i++;
        }
        delete[] c;

        dijikstra(mat[0][0]);

        return 0;
}

void dijikstra(int startnode)							//Implement dijkstra algo for shortest path
{
    int cost[5][5], distance[5], pred[5]; int visited[5], count, mindistance, nextnode;

    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(mat[i][j]==-99)
                cost[i][j]=9999;
            else
                cost[i][j]=mat[i][j];

    for(int i=0;i<5;i++)
    {
        distance[i]=cost[startnode][i];
        pred[i]=startnode;
        visited[i]=0;
    }

    distance[startnode]=0;
    visited[startnode]=1;
    count=1;

    while(count<4)
    {
        mindistance=9999;

        for(int i=0;i<5;i++)
            if(distance[i]<mindistance&&!visited[i])
            {
                mindistance=distance[i];
                nextnode=i;
            }

            visited[nextnode]=1;
            for(int i=0;i<5;i++)
                if(!visited[i])
                    if(mindistance+cost[nextnode][i]<distance[i])
                    {
                        distance[i]=mindistance+cost[nextnode][i];
                        pred[i]=nextnode;
                    }
        count++;
    }

    for(int i=0;i<5;i++)
        if(i!=startnode)
        {
		cout << "\nDistance of node" << i+1 <<  "from node 1 = " << distance[i] << endl << "Path = " << i;

	        int j=i;
                do
                {
                	j=pred[j];
			cout << "<-" << j;
            	}
		while(j!=startnode);
        }
}
