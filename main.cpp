/********************************************************************************************************************
 * Program: Matrix Row Reduce Echelon Form Calculator (C++)
 * Author: John Kaufman
 * Date of Program Creation: 3/16/2021
 * Date of Program Competion: Work in Progress
 *
 * Description: This program performs a series of elementary row operations on a matrix
 * 		to transform the matrix into its row redeuced echelon form (RREF)
 *
 * Input: Input is provided in 2 phases:
 * 		First, the user enters the number of vectors in the matrix, and the dimension of the matrix
 * 		Second, the user enters a number of values corresponding to the number of vectors multiplied by the dimension of the matrix.
 *
 * 		(Note on input: Each column corresponds to a vector)
 *
 * Output: After translating the matrix to its RREF, the program will output the resulting matrix to the terminal
***********************************************************************************************************************/

#include <iostream>

#include "./matrix.h"

using namespace std;

//The driving function for the whole program.
int main()
{
	//Variables
	Matrix main;

	//Obtain matrix dimensions from the user
	main.set_user_rows();
	main.set_user_cols();

	cout << main.get_num_rows() << "\t" << main.get_num_cols() << endl;

	//Create an empty 2d array of integers
	main.create_matrix();


	//Obtain matrix entries from the user
	main.fill_matrix();	
	main.print_Matrix();

	cout << "result:";
	cout << main.terminal_state() << endl;

	//Perform matrix operations until the matrix is in RREF
/*	while(main.terminal_state == false)
	{
		main.peform_row_operation();
	}	
*/
	//Output the RREF matrix to the terminal
	cout << "The matrix is now in row reduced echelon form:" << endl;
	main.print_Matrix();

	return 0;
}









