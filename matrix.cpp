#include <iostream>

#include "./matrix.h"

using namespace std;

//Initialize the members of the matrix class
Matrix::Matrix()
{
	num_rows = 0;
	num_cols = 0;

	entries = NULL;
}

//Destruct the matrix
Matrix::~Matrix()
{
	for(int i = 0; i < num_rows; i++)
		delete [] entries[i];

	delete [] entries;
}

//Print the matrix
void Matrix::print_Matrix()
{
	for(int i = 0; i < num_rows; i++)
	{
		cout << "[ ";
		for (int j = 0; j < num_cols; j++)
			cout << entries[i][j] << " ";
		cout << "]" << endl;
	}
}

//Get from the command line the number of rows in the matrix
void Matrix::set_user_rows()
{
	cout << "Enter the number of rows in the matrix: ";
	cin >> num_rows;
	cout << endl;
}

//Ger from the command line the number of cols in the matrix
void Matrix::set_user_cols()
{
	cout << "Enter the number of columns in the matrix: ";
	cin >> num_cols;
	cout << endl;
}


//Create the 2d matrix
void Matrix::create_matrix()
{
	entries = new int*[num_rows];
	for(int i = 0; i < num_rows; i++)
		entries[i] = new int[num_cols];
}

//Fill the matrix with entries from the command line
void Matrix::fill_matrix()
{
	for(int i = 0; i < num_rows; i++)
	{
		for(int j = 0; j < num_cols; j++)
		{
			cout << "Enter the entry at position " << i+1 << ", " << j+1 << ": ";
			cin >> entries[i][j];
			cout << endl;
		}
	}
}


//Determine if the matrix is in RREF form. Return T if yes, F if not.
bool Matrix::terminal_state()
{
	int offset = 0;

	for(int i = 0; i < num_rows; i++)
	{
		for(int j = 0; j < num_cols; j++)
		{
			if(entries[i][j] != 0 && entries[i][j] != 1) //All entries must be either 0 or 1
				return false;

			else if(entries[i][j] == 1)
			{
				if(i == 0)
				{
					offset = j;
				}
				else
				{
					if(j != offset+i)
						return false;
				}
			}
		}
	}
}

//Return the private members num_rows and num_cols
int Matrix::get_num_rows()
{
	return num_rows;
}

int Matrix::get_num_cols()
{
	return num_cols;
}








