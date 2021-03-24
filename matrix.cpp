#include <iostream>
#include <iomanip>

#include "./matrix.h"

using namespace std;

//Initialize the members of the matrix class
Matrix::Matrix()
{
	num_rows = 0;
	num_cols = 0;

	entries = NULL;

	working_row_index = -1;
	working_column_index = -1;
	
	valid = false;

}

//Deconstruct the matrix
Matrix::~Matrix()
{
	for(int i = 0; i < num_rows; i++)
		delete [] entries[i];

	delete [] entries;
}

//Print the matrix
void Matrix::print_Matrix()
{
	cout << endl;
	for(int i = 0; i < num_rows; i++)
	{
		cout << "[ ";
		for (int j = 0; j < num_cols; j++)
			cout << fixed << setprecision(3) << entries[i][j] << " ";
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
	entries = new float*[num_rows];
	for(int i = 0; i < num_rows; i++)
		entries[i] = new float[num_cols];
}

//Fill the matrix with entries from the command line
void Matrix::fill_matrix()
{
	for(int i = 0; i < num_rows; i++)
		for(int j = 0; j < num_cols; j++)
		{
			cout << "Enter the entry at position row: " << i+1 << ", column: " << j+1 << ": ";
			cin >> entries[i][j];
			cout << endl;
		}
}

//Determine a row operation to perform, and call a corresponding function
void Matrix::perform_row_operation()
{
	//Perform row operations until the matrix is in row-echelon form
	while(valid == false)
	{	
		sort_rows();
		scale_row(working_row_index);
		validate_column_down(working_column_index, working_row_index);
	}

	//The matrix is now in row-echelon form (not row reduced echelon form)
	cout << "The matrix is now in row-echelon form: " << endl;
	print_Matrix();

	valid = false;

	working_column_index = num_cols;
	working_row_index = num_rows;

	//Perform row operations until the matrix is in row-reduced echelon form	
	while(valid == false)
	{
		determine_indices();
		validate_column_up(working_column_index, working_row_index);
	}	
}

//Sort the rows of the matrix
void Matrix::sort_rows()
{
	bool break_flag = false;

	if(entries[working_row_index+1][working_column_index+1] == 0)
		for(int j = working_column_index+1; j < num_cols; j++)
		{
			for(int i = working_row_index+1; i < num_rows; i++)
				if(entries[i][j] != 0)
				{
					swap_rows(working_row_index+1, i);
					break_flag = true;
				}
			if(break_flag)
				break;
		}


	working_row_index++;
	working_column_index++;
}

//Swap the rows provided by the arguments x and y
void Matrix::swap_rows(int x, int y)
{
	float temp[num_cols];
	for(int i = 0; i < num_cols; i++)
	{
		temp[i] = entries[y][i];
		entries[y][i] = entries[x][i];
		entries[x][i] = temp[i];
	}

}

//Scale the highest row where the leading entry is not 1
void Matrix::scale_row(int row_num)
{
	float scalar = 0;
	for(int i = 0; i < num_cols; i++)
	{
		if(entries[row_num][i] != 0 && scalar == 0)
			scalar = entries[row_num][i];
	
		if(scalar != 0)
			entries[row_num][i] = entries[row_num][i] / scalar;
	}
}


//Ensure all rows below row_num in column col_num have 0's.
void Matrix::validate_column_down(int col_num, int row_num)
{

	for(int i = row_num+1; i < num_rows; i++)
		if(entries[i][col_num] != 0)
			subtract_row(entries[i][col_num], row_num, i);


	if(row_num+1 == num_rows)
		valid = true;
}


//Find the rightmost column with a leading 1 that has not yet been validated.
void Matrix::determine_indices()
{
	bool break_flag = false;
	
	for(int i = working_row_index-1; i >=0; i--)
	{
		for(int j = 0; j < num_cols; j++)
			if(entries[i][j] != 0)
			{

				working_row_index = i+1;
				working_column_index = j+1;
				
				break_flag = true;	
				break;
			}
	
		if(break_flag == true)
			break;
	}
}

//Ensure all rows above row_num in the column col_num have 0's.
void Matrix::validate_column_up(int col_num, int row_num)
{
	for(int i = row_num-2; i >= 0; i--)
		if(entries[i][col_num-1] != 0)
			subtract_row(entries[i][col_num-1], row_num-1, i);


	working_row_index--;
	working_column_index--;


	if(working_row_index == 0)
		valid = true;
}

//Substract row x scale times from row y
void Matrix::subtract_row(float scale, int x, int y)
{
	for(int i = 0; i < num_cols; i++)
		entries[y][i] = entries[y][i] - scale * entries[x][i];

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
