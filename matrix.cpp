#include <iostream>

#include "./matrix.h"

using namespace std;

//Initialize the members of the matrix class
Matrix::Matrix()
{
	num_rows = 0;
	num_cols = 0;

	rows = NULL;

	lowest_scaled_row = -1;
	scaled = false;

	leftmost_valid_column = -1;
	valid = false;

	sorted = false;
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
		rows[i].entries = new float[num_cols];
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

//Determine a row operation to perform, and call a corresponding function
void Matrix::perform_row_operation()
{
	if(sorted == false)
		sort_rows();

	while(scaled == false)	
		prep_row_scale();

	while(valid == false)
		validify_column();
}

//Sort the rows of the matrix
void Matrix::sort_rows()
{
	for(int i = 0; i < num_rows; i++)
		for(int j = 0; j < num_cols; j++)
			if(rows[i].entries[j] == 0 && rows[i].sorted == false)
				for(int k = i+1; k < num_rows; k++)
					if(rows[k].entries[j] != 0 && rows[k].sorted == false)
					{
						swap_rows(i,k);
						break;
					}
			else if(rows[i].entries[j] != 0)
			{
				rows[i].sorted = true;
				break;
			}

	sorted = true;
}

//Swap the rows provided by the arguments x and y
void Matrix::swap_rows(int x, int y)
{
	float temp[num_cols];
	for(int i = 0; i < num_cols; i++)
	{
		temp[i] = rows[y].entries[i];
		rows[y].entries[i] = rows[x].entries[i];
		rows[x].entries[i] = temp[i];
	}

	rows[x].sorted = true;
}

//scale a row so the first entry is 1
void Matrix::prep_row_scale()
{
	for(int i = 0; i < num_cols; i++)
		if(rows[lowest_scaled_row+1].entries[i] != 0 && rows[lowest_scaled_row+1].entries[i] != 1)
		{
			scale_row(lowest_scaled_row+1, rows[lowest_scaled_row+1].entries[i]);
			break;
		}
		else if(rows[lowest_scaled_row+1].entries[i] == 1)
			break;

	lowest_scaled_row++;

	if(lowest_scaled_row == num_rows)
		scaled = true;
}

//Divide each entry in a row by the scalar
void Matrix::scale_row(int row_num, int scalar)
{
	cout << "scaling row number: " << row_num << " by: " << scalar << endl;

	for(int i = 0; i < num_cols; i++)
		rows[row_num].entries[i] = rows[row_num].entries[i] / scalar;

	print_Matrix();
}

//Replace a row with a linear combination of itself and other rows
void Matrix::validify_column()
{
	for(int i = 0; i < num_rows; i++)
	{
		if(rows[i].entries[leftmost_valid_column+1] == 1)
		{
			for(int j = i; j < num_rows; j++)
			{
				if(rows[j].entries[leftmost_valid_column+1] == 1)
					subtract_row(i, j);
			}
		}
	}

	leftmost_valid_column++;

	if(leftmost_valid_column == num_cols)
		valid = true;
}

//Substract row x from row y
void Matrix::subtract_row(int x, int y)
{
	for(int i = 0; i < num_cols; i++)
	{
		rows[y].entries[i] = rows[y].entries[i] - rows[x].entries[i];
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



