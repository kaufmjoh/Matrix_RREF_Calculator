#ifndef MATRIX_H
#define MATRIX_H

using namespace std;

class Matrix
{
	private:
		int num_rows; //Number of rows in the matrix
		int num_cols; //NUmber of columns in the matrix

		float** entries; //The entries of the matrix

		int working_row_index;    //The row index operations are currently being performed on
		int working_column_index; //The column index operations are currently being performed on
	
		bool valid; //Whether the matrix is in RREF form

	public:
		//Matrix constructors and destructors
		Matrix();
		~Matrix();

		//print the matrix to the terminal
		void print_Matrix();

		//Get the private members num_rows and num_cols
		int get_num_rows();
		int get_num_cols();

		//Prompt the user for the number of rows and columns in the matrix
		void set_user_rows();
		void set_user_cols();	

		//Dynamically allocate a 2d array of floats
		void create_matrix();		

		//Prompt the user for the entries of the matrix
		void fill_matrix();

		//Perform row operations until the matrix is in RREF
		void perform_row_operation();

		void sort_rows();

		//Swap the 2 rows of the matrix provided as arguments
		void swap_rows(int, int);

		//Divide each entry in the row provided as an argument by the row's leading entry
		void scale_row(int);

		//Make sure that every entry directly below the position specifed are 0
		void validate_column_down(int, int);
	
		//Determine the position of the rightmost leading 1 that has not yet been validated
		void determine_indices();

		//Make sure that every entry directly above the position specified are 0
		void validate_column_up(int, int);

		//Subtract a certain row scaled from another row 
		void subtract_row(float, int, int);
};


#endif
