#include <iostream>

#include "./matrix.h"

using namespace std;

//Initialize the members of the matrix class
Matrix::Matrix()
{
	num_rows = 0;
	num_cols = 0;

	rows = NULL;
}

//Destruct the matrix
Matrix::~Matrix()
{
	for(int i = 0; i < num_rows; i++)
		delete [] rows[i].entries;

	delete [] rows;
}

//Print the matrix
void Matrix::print_Matrix()
{
	for(int i = 0; i < num_rows; i++)
	{
		cout << "[ ";
		for (int j = 0; j < num_cols; j++)
			cout << rows[i].entries[j] << " ";
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
	rows = new Row[num_rows];
	for(int i = 0; i < num_rows; i++)
	{
		rows[i].entries = new int[num_cols];
		rows[i].sorted = false;
	}
}

//Fill the matrix with entries from the command line
void Matrix::fill_matrix()
{
	for(int i = 0; i < num_rows; i++)
	{
		for(int j = 0; j < num_cols; j++)
		{
			cout << "Enter the entry at position " << i+1 << ", " << j+1 << ": ";
			cin >> rows[i].entries[j];
			cout << endl;
		}
	}
}


//Determine if the matrix is in RREF form. Return T if yes, F if not.
bool Matrix::terminal_state()
{
	int offset = 0;
	bool flag = false;

	//Any way to reduce complexity below n^3?
	for(int i = 0; i < num_rows; i++)
	{
		flag = false;

		for(int j = 0; j < num_cols; j++)
		{
			if(rows[i].entries[j] != 0 && rows[i].entries[j] != 1) //All entries must be either 0 or 1
				return false;

			else if(rows[i].entries[j] == 1 && flag == false) //The first 1 in a row.
			{
				flag = true;

				//Check column
				for(int k = 0; k < num_rows; k++)
				{
					if(rows[k].entries[j] == 1 && i != k)
						return false;
				}
			}
		}
	}

	return true;
}
/*
//Determine a row operation to perform, and call a corresponding function
void Matrix::perform_row_operation()
{
	int column = 0;

	//Organize the rows so that the leftmost nonzero column has a nonzero entry in the top row, and repeat	
	for(int k = 0; k < num_rows; k++)
	{
		for(int i = k; i < num_rows; i++)
		{
			if(entries[i][0] == 0)
			{
				for(int j = i; j < num_rows; j++)
				{
					if(entries[j][0] != 0)
					{
						swap_rows(i, j);
					}
				}

			}
		}
	}
}
*/

//Return the private members num_rows and num_cols
int Matrix::get_num_rows()
{
	return num_rows;
}

int Matrix::get_num_cols()
{
	return num_cols;
}








