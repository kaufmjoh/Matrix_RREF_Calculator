#ifndef MATRIX_H
#define MATRIX_H

using namespace std;

class Matrix
{
	private:
		int num_rows;
		int num_cols;

		int** entries;

	public:
		Matrix();
		~Matrix();

		void print_Matrix();

		int get_num_rows();
		int get_num_cols();

		void set_user_rows();
		void set_user_cols();	
		
};


#endif
