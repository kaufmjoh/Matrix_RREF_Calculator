#ifndef MATRIX_H
#define MATRIX_H

#include "./vector.h"

using namespace std;

class Matrix
{
	private:
		int dimension;
		Vector* vectors;

	public:
		Matrix();
		~Matrix();

		void Print_Matrix();

		int get_dimension();
		Vector* get_vectors();

		void set_dimension(int input_dimension);
		void set_vectors(Vector* input_vectors);
		
}


#endif
