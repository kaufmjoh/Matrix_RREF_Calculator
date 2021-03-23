#ifndef MATRIX_H
#define MATRIX_H

using namespace std;

#include "./row.h"

class Matrix
{
	private:
		int num_rows;
		int num_cols;

		Row* rows;

		int lowest_scaled_row;
		int leftmost_valid_column;

		int highest_scaled_row;
		int rightmost_valid_column;	
	
		bool valid;

	public:
		Matrix();
		~Matrix();

		void print_Matrix();

		int get_num_rows();
		int get_num_cols();

		void set_user_rows();
		void set_user_cols();	

		void create_matrix();		

		void fill_matrix();

		bool terminal_state();

		void perform_row_operation();

		void sort_rows();
		void swap_rows(int, int);

		void prep_row_scale();
		void scale_row(int);

		void validate_column_down(int, int);
		void validate_column_up(int, int);
		void subtract_row(float, int, int);
};


#endif
