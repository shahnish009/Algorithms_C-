#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<climits>
#include<string>

using namespace std;

void create(string file_name);
void sort_contact(string *, int, int);
void search(char *, int, int);
void deletee(char *);
void insert(char *);

void print_directory(string *);
void delete_search(char *, int, int);
string * directory;
int records, search_index;

int main(int argc, char * argv[])     //This is the main function. Enter the choices as per the descriptiption provided in the Project.
{
	string text_file = argv[1];
	int choice, choice_flag = 1;
	char name[100];

	create(text_file);

	while(choice_flag == 1)
	{
		cout<<"\n1) sort_contact";
		cout<<"\n2) search";
		cout<<"\n3) delete";
		cout<<"\n4) insert";
		cout<<"\n5) exit";
		cout<<"\nEnter your choice\n";
		cin>>choice;

		switch(choice)					//Switch cases for selecting different choices.
		{
			case 1:
			sort_contact(directory, 0, records-1);
			print_directory(directory);
			break;

			case 2:
			cin.ignore();
			cout<<"\nEnter the name -> ";
			cin.getline(name, 100);
			search(name, 0, records - 1);
			break;

			case 3:
			cin.ignore();
                        cout<<"\nEnter the name -> ";
                        cin.getline(name, 100);
			deletee(name);
			break;

			case 4:
			cin.ignore();
                        cout<<"\nEnter the name -> ";
                        cin.getline(name, 100);
			insert(name);
			break;

			case 5:
			delete[] directory;
			choice_flag = 0;
			break;
		}
	}
        return 0;
}

void create(string text_file)					//Creates the directory reading the contact information i.e. FirstName LastName, PhoneNumber from the text file.
{
	string line;
        int row_flag = 0;
	std::ifstream open_file1(text_file.c_str());

	if(open_file1.is_open())
	{
		while(getline(open_file1, line))
		{
			if(line[line.size()-1] == '\r'){
			line.erase(line.length()-1);}
			row_flag++;
		}
	}
	open_file1.close();

	directory = new string[row_flag];
	row_flag = 0;
        std::ifstream open_file2(text_file.c_str());

	if(open_file2.is_open())
	{
		while(getline(open_file2, line))
		{
			if(line[line.size()-1] == '\r'){
			line.erase(line.length()-1);}
			directory[row_flag] = line;
			row_flag++;
		}
	}
	open_file2.close();

	records = row_flag;
}

void sort_contact(string  * array, int left, int right)			//Function to sort the directory using Randomzed Quicksort Algorithm.
{
	int left_flag = left;
	int right_flag = right;
	int size = right - left;
	if(size > 1)
	{
        	string pivot = array[rand() % size + left_flag];

		while (left_flag < right_flag)
		{
			while (array[right_flag] > pivot && right_flag > left_flag)
	    		{
                		right_flag--;
			}

			while (array[left_flag] < pivot && left_flag <= right_flag)
			{
                		left_flag++;
            		}

            		if (left_flag < right_flag)
	    		{
                		swap(array[left_flag], array[right_flag]);
                		left_flag++;
            		}
        	}

        	sort_contact(array, left, left_flag);
        	sort_contact(array, right_flag, right);
    	}
}
void print_directory(string * array)			//Simple Display function to print the contents of the Directory
{
	cout<<"\n";
	for(int i = 0; i< records; i++)
	{
		cout<<array[i]<<"\n";
	}
	cout<<"\n";
}
void search(char * name, int low, int high)		//Implemented searching from the directory using Binary Search Algorithm. Took a reference from Binary Search Pseudo Code from Professor's slides - Chapter 4
{							//Enter the 'Firstname Lastname' or 'Firstname Lastname, Phonenumber' both formats supported
	string search_name = name;

	if(low > high)
	{
		cout<<"\nName not Found\n";
	}

	else
	{
		search_index = floor((low + high)/2);

		if (directory[search_index].find(search_name)!= string::npos)
		{
			cout<<directory[search_index]<<"\n";
		}
		else if (search_name < directory[search_index])
		{
			search(name, low, search_index - 1);
		}
		else if (search_name > directory[search_index])
		{
			search(name, search_index + 1, high);
		}
		else
		{
			cout<<"Name not Found\n";
		}
	}
}
void deletee(char * name)						//Delete Function implemented removing the given entry from the Directory. (Named as 'deletee' as 'delete' is a reserved keyword in c++
{									//Enter 'Firstname Lastname' 0r 'Firstname Lastname, Phonenumber' both formats supported.
	delete_search(name, 0, records - 1);
	int i;
	if(search_index != -1)
	{
		--records;
		string * new_directory = new string[records];

		for(i = 0; i <= search_index - 1; i++)
		{
			new_directory[i] = directory[i];
		}
        	for(i = search_index + 1; i < records + 1; i++)
		{
                        new_directory[i - 1] = directory[i];
        	}
		delete[] directory;
		directory = new_directory;
		new_directory = NULL;;
		print_directory(directory);
	}
}

void delete_search(char * name, int low, int high)			//This is a helper function to deletee. making this a seperate function looks more systematic.
{									//Even this uses the Binary Search Algorithm and has similar working as search function. Before the last update to the FAQ, the inputs of search and delete were different formats, hence made a different function
	string search_name = name;

        if(low > high)
        {
                cout<<"\nName not Found\n";
		search_index = -1;
		return;
        }

        else
        {
                search_index = floor((low + high)/2);

		if (directory[search_index].find(search_name)!= string::npos)
                {
                        return;
                }
                else if (search_name < directory[search_index])
                {
                        delete_search(name, low, search_index - 1);
                }
                else if (search_name > directory[search_index])
                {
                        delete_search(name, search_index + 1, high);
                }
                else
                {
                        cout<<"\nName not Found\n";
			search_index = -1;
			return;
                }
        }
}
void insert(char * name)					//Insert function to insert an entry into the directory. Once inserted, it prints out the sorted Directory.
{
        ++records;
        string * new_directory = new string[records];

        for(int i = 0; i < records - 1; i++)
	{
		new_directory[i] = directory[i];
        }

	new_directory[records - 1] = name;
	delete[] directory;
	directory = new_directory;
	new_directory = NULL;
	sort_contact(directory, 0, records - 1);
        print_directory(directory);
}
