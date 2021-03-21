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


void Matrix::set_user_rows()
{
	cout << "Enter the number of rows in the matrix: " << endl;
	cin >> num_rows;
}

void Matrix::set_user_cols()
{
	cout << "Enter the number of columns in the matrix: " << endl;
	cin >> num_cols;
}



int Matrix::get_num_rows()
{
	return num_rows;
}

int Matrix::get_num_cols()
{
	return num_cols;
}








