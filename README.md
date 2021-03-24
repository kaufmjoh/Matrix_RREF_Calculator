# Matrix_RREF_Calculator

This program is a calculator that converts a matrix to its row reduced echelon form (RREF).

A RREF matrix has leading 1 in every column, up to the dimension of the vectors.

Read more about row-reduced echelon form at this link: https://en.wikipedia.org/wiki/Row_echelon_form


To convert a matrix to RREF, the program follows this algoritm:
- Arrange the rows of the matrix such that the leading entry of each row is to the right or eqal to the rows above it, and left or equal to the rows below it.
- Starting at the first row, scale a row such that the leading entry is 1, and then perform row operations such that every entry in the lower rows in the same column are 0, and repeat.
- Once the leading entry in every row is 1, start at the rightmost leading entry, and perform row operations such that every entry in the upper rows in the same column are 0, and repeat.
- The matrix will now be in RREF.

This program operates by asking the user for the number of rows and columns from the user, then asking for the entries of the matrix. The program then converts the matrix to RREF, and displays the result.
