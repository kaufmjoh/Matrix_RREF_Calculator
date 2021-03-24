#include <iostream>
#include <iomanip>

#include "./matrix.h"

using namespace std;

/************************************************
 * Matrix()
 *
 * Constructor for the matrix class.
 * Initialize all members to a null value.
 * *********************************************/
Matrix::Matrix()
{
	num_rows = 0;
	num_cols = 0;

	entries = NULL;

	working_row_index = -1;
	working_column_index = -1;
	
	valid = false;

}

/************************************************
 *~Matrix()
 *
 * Deconstuctor for matrix class.
 * Free the dynamically allocated memory
 * *********************************************/
Matrix::~Matrix()
{
	for(int i = 0; i < num_rows; i++)
		delete [] entries[i];

	delete [] entries;
}

/************************************************
 * print_Matrix()
 *
 * Print the entries of the matrix to the terminal
 * *********************************************/
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

/**********************************************
 * set_user_rows()
 *
 * Prompt the user for the number of rows in the matrix
 * Store the input in the num_rows member.
 * *******************************************/
void Matrix::set_user_rows()
{
	cout << "Enter the number of rows in the matrix: ";
	cin >> num_rows;
	cout << endl;

}

/**********************************************
 * set_user_cols()
 *
 * Prompt the user for the number of columns in the matrix
 * Store the input in the num_cols member.
 * *******************************************/
void Matrix::set_user_cols()
{
	cout << "Enter the number of columns in the matrix: ";
	cin >> num_cols;
	cout << endl;

}


/************************************************
 * create_matrix()
 *
 * Dynamically allocate a 2d array of floats with
 * size equal to the input provided by the user
 * *********************************************/
void Matrix::create_matrix()
{
	entries = new float*[num_rows];
	for(int i = 0; i < num_rows; i++)
		entries[i] = new float[num_cols];
}

/************************************************
 * fill_matrix()
 *
 * Prompt the user for the entries of the matrix
 * Store the input in the correct index of entries**
 * *********************************************/
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

/************************************************
 * perform_row_operation()
 *
 * First, perform row-operations until the matrix is in row-echelon form
 * Then, perform row-operations until the matrix is in RREF.
 * *********************************************/
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

	//If in the process of row_validation, any zero rows have been produced, sort them so they are on the bottom
	working_column_index = -1;
	working_row_index = -1;
	for(int i = 0; i < num_rows; i++)
		sort_rows();
}

/************************************************
 * sort_rows()
 *
 * Based on the current working row and column position,
 * ensure that the position is non-zero.
 *
 * If it is zero, search in the rows below for a non zero entry.
 * If one is found, swap the rows.
 *
 * Increment the current working row and index 
 * *********************************************/
void Matrix::sort_rows()
{
	bool break_flag = false; //When a swap is performed, break out of the loop

	if(entries[working_row_index+1][working_column_index+1] == 0) //if the entry is 0, search for a row to swap.
		for(int j = working_column_index+1; j < num_cols; j++)
		{
			for(int i = working_row_index+1; i < num_rows; i++)
				if(entries[i][j] != 0) //a nonzero row has been found
				{
					swap_rows(working_row_index+1, i); //swap the two rows
					break_flag = true;
				}
			if(break_flag)
				break;
		}


	working_row_index++;
	working_column_index++;
}

/************************************************
 * swap_rows(x, y)
 *
 * Swap the rows with indices x and y.
 * Store row y in a temp row temp, replace y with x
 * and replace x with temp.
 * ********************************************/
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

/**********************************************
 * scale_row(row_num)
 *
 * For the row with index row_num, divide
 * each entry in the row by the leading
 * non-zero entry.
 * *******************************************/
void Matrix::scale_row(int row_num)
{
	float scalar = 0;
	for(int i = 0; i < num_cols; i++)
	{
		if(entries[row_num][i] != 0 && scalar == 0) //the leading non-zero entry has been found
			scalar = entries[row_num][i];
	
		if(scalar != 0)
			entries[row_num][i] = entries[row_num][i] / scalar;
	}
}


/************************************************
 * validate_column_down(col_num, row_num)
 *
 * col_num and row_num provide the coordinates for an entry in the matrix
 *
 * this function ensures that every entry below the position in the same
 * column becomes 0 via row operations.
 * *********************************************/
void Matrix::validate_column_down(int col_num, int row_num)
{
	for(int i = row_num+1; i < num_rows; i++)
		if(entries[i][col_num] != 0) //The entry must be changed to 0
			subtract_row(entries[i][col_num], row_num, i); //change with row subtraction


	if(row_num+1 == num_rows)
		valid = true;
}


/********************************************
 * determine_indices()
 *
 * Find the position of the rightmost leading entry
 * that has not yet been above validated.
 *
 * Store the indices in working_row_index and working_column_index
 * ******************************************/
void Matrix::determine_indices()
{
	bool break_flag = false;
	
	for(int i = working_row_index-1; i >=0; i--)
	{
		for(int j = 0; j < num_cols; j++)
			if(entries[i][j] != 0) //The lowest (and therefore rightmost) leading entry has been found
			{
				//Store the indices
				working_row_index = i+1;
				working_column_index = j+1;
				
				break_flag = true;	
				break;
			}
	
		if(break_flag == true)
			break;
	}
}

/************************************************
 * validate_column_up(col_num, row_num)
 *
 * Perform row operations to ensure that every
 * entry in the column above the position specified is 0.
 *
 * Decrement working_row_index and working_column_index.
 * *********************************************/
void Matrix::validate_column_up(int col_num, int row_num)
{
	for(int i = row_num-2; i >= 0; i--)
		if(entries[i][col_num-1] != 0) //Entry must be changed to 0
			subtract_row(entries[i][col_num-1], row_num-1, i); //Change to 0 via subtraction


	//Decrement working indices
	working_row_index--;
	working_column_index--;

	//If all rows have validated, the matrix is in RREF.
	if(working_row_index == 0)
		valid = true;
}

/************************************************
 * subtract_row(scale, x, y)
 *
 * Subtract row x multiplied by the scale from row y
 * ********************************************/
void Matrix::subtract_row(float scale, int x, int y)
{
	for(int i = 0; i < num_cols; i++)
		entries[y][i] = entries[y][i] - scale * entries[x][i];

}

/************************************************
 * get_num_rows()
 *
 * Return the private member num_rows
 * *********************************************/
int Matrix::get_num_rows()
{
	return num_rows;
}

/************************************************
 * get_num_cols()
 *
 * Return the private member num_cols
 * ********************************************/
int Matrix::get_num_cols()
{
	return num_cols;
}
