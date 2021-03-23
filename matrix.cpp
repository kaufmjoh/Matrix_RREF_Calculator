#include <iostream>
#include <iomanip>

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

	rightmost_valid_column = -1;
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
	cout << endl;
	for(int i = 0; i < num_rows; i++)
	{
		cout << "[ ";
		for (int j = 0; j < num_cols; j++)
			cout << fixed << setprecision(3) << rows[i].entries[j] << " ";
		cout << "]" << endl;
	}
	cout << endl;
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

	//The matrix is now in row-echelon form (not row reduced echelon form)

	while(valid == false)
	{	
		print_Matrix();
		scale_row();
		print_Matrix();
		validify_column();
	}
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

//Scale the highest row where the leading entry is not 1
void Matrix::scale_row()
{
	cout << "lowest scaled row is: " << lowest_scaled_row << endl;

	float scalar = 0;
	for(int i = 0; i < num_cols; i++)
	{
		if(rows[lowest_scaled_row+1].entries[i] != 0 && scalar == 0)
		{
			scalar = rows[lowest_scaled_row+1].entries[i];
			cout << "scalar is: " << scalar << endl;
		}
		if(scalar != 0)
			rows[lowest_scaled_row+1].entries[i] = rows[lowest_scaled_row+1].entries[i] / scalar;
	}

	lowest_scaled_row++;
}


//Replace a row with a linear combination of itself and other rows
void Matrix::validify_column()
{
	for(int i = 0; i < num_rows; i++)
	{
		if(rows[i].entries[rightmost_valid_column+1] != 0 && i != lowest_scaled_row)
			subtract_row(rows[i].entries[rightmost_valid_column+1], lowest_scaled_row, i); 
	}

	rightmost_valid_column++;

	if(rightmost_valid_column+1 == num_cols)
		valid = true;
}

//Substract row x scale times from row y
void Matrix::subtract_row(float scale, int x, int y)
{
	for(int i = 0; i < num_cols; i++)
	{
		rows[y].entries[i] = rows[y].entries[i] - scale * rows[x].entries[i];
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



