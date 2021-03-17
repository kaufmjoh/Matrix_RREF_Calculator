#ifndef VECTOR_H
#define VECTOR_H

using namespace std;

class Vector
{
	private:
		int dimension;
		int* entries;

	public:

		Vector();
		~Vector();

		int get_dimension();
		int* get_entries();

		void set_dimension(int input_dimension);
		void set_entries(int* input_entries);
}

#endif
