/*name:yehudit mendelboim*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#define SIZE 10
#define MAX_VAL 9
#define MIN_VAL 0
typedef enum { FALSE = 0, TRUE }bool;
bool print_Bord(char matrix[][SIZE]);
bool Rand_Matrix(int matrix[][SIZE]);
bool Test_Row(int matrix[][SIZE], int size, int row, int col);
bool Test_Col(int matrix[][SIZE], int size, int row, int col);
bool Game(int matrix[][SIZE], char matrix_see[][SIZE]);
bool chack(int matrix[][SIZE]);
int main() {
	srand(time(NULL));
	char matrix_see[SIZE][SIZE];
	int i, j;
	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			matrix_see[i][j] = '  ';/*Initializes the matrix in a ' '*/
		}
	}
	int matrix[SIZE][SIZE];
	Rand_Matrix(matrix);/*Call to a function that receives submarines*/
	Game(matrix, matrix_see);/*call to the game function*/

	return 0;

}
bool print_Bord(char matrix[][SIZE]) {/*A function that prints the matrix*/
	int i = 0, j;
	printf("\t    %d", i);
	for (i = 1; i < SIZE; ++i) {
		printf("\t  %d", i);
	}
	printf("\t\n");
	for (i = 0; i < SIZE; ++i) {
		printf("\t%d ", i);
		for (j = 0; j < SIZE; ++j) {
			printf("[ %C ]\t", matrix[i][j]);
		}
		printf("\n\n");
	}
	return TRUE;
}
bool Rand_Matrix(int matrix[][SIZE]) { /*A function that randomly accepts submarines*/
	int size, posting, row, col, i, j;
	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j)
			matrix[i][j] = 0;
	}
	for (size = 2; size < 6; ++size) {
		row = (rand() % (MAX_VAL + 1)) + MIN_VAL;/*Receives a random number*/
		col = (rand() % (MAX_VAL + 1)) + MIN_VAL;/*Receives a random number*/
		posting = (rand() % (MIN_VAL + 2)) + MIN_VAL; /*Receives a random number*/
		if (posting == 0) {
			if (!(Test_Row(matrix, size, row, col)))/*A loop that sends values to the submarine reception function*/
				--size;/*If the function return false, reduce the size value*/
		}
		else if (!(Test_Col(matrix, size, row, col))) /*A loop that sends values to the submarine reception function*/
			--size;/*If the function return false, reduce the size value*/

	}
	for (size = 3; size < 4; ++size) {
		row = (rand() % (MAX_VAL + 1)) + MIN_VAL;/*Receives a random number*/
		col = (rand() % (MAX_VAL + 1)) + MIN_VAL;/*Receives a random number*/
		posting = (rand() % (MIN_VAL + 2)) + MIN_VAL;/*Receives a random number*/
		if (posting == 0) {
			if (!(Test_Row(matrix, size, row, col)))/*A loop that sends values to the submarine reception function*/
				--size;/*If the function return false, reduce the size value*/

		}
		else if (!(Test_Col(matrix, size, row, col))) /*A loop that sends values to the submarine reception function*/
			--size;/*If the function return false, reduce the size value*/


	}
	return TRUE;
}
bool Test_Row(int matrix[][SIZE], int size, int row, int col) {/*A function that checks and places a submarine horizontally*/
	int i, j;
	if (matrix[row][col] != MIN_VAL) {/*Check that there is no submarine in this cell*/
		return FALSE;
	}
	if (col + size > MAX_VAL) {/*Checks if there are enough cells to insert the submarine*/
		return FALSE;
	}
	if (row - 1 > 0) {
		for (i = col, j = size; j > 0; ++i, --j) {
			if (matrix[row - 1][i] != MIN_VAL)
				return FALSE;
		}
	}
	if (row + 1 < SIZE) {
		for (i = col, j = size; j > 0; ++i, --j) {
			if (matrix[row + 1][i] != MIN_VAL)
				return FALSE;
		}
	}
	if (col - 1 > -1) {
		if (matrix[row][col - 1] != MIN_VAL)
			return FALSE;
	}
	if (col + size != MAX_VAL) {
		if (matrix[row][col + size] != MIN_VAL)
			return FALSE;
	}
	for (i = col, j = size; j > 0; ++i, --j) {
		if (matrix[row][i] != MIN_VAL)
			return FALSE;
	}
	for (i = col, j = size; j > 0; ++i, --j) {/*A loop that inserts the submarine*/
		matrix[row][i] = size;
	}
	return TRUE;
}
bool Test_Col(int matrix[][SIZE], int size, int row, int col) {/*A function that checks and places a vertical submarine*/
	int i, j;
	if (matrix[row][col] != MIN_VAL) {/*Check that there is no submarine in this cell*/
		return FALSE;
	}
	if (row + size > MAX_VAL) {/*Checks if there are enough cells to insert the submarine*/
		return FALSE;
	}
	if (col - 1 > -1) {
		for (i = row, j = size; j > 0; ++i, --j) {
			if (matrix[i][col - 1] != MIN_VAL)
				return FALSE;
		}
	}
	if (col + 1 < SIZE) {
		for (i = row, j = size; j > 0; ++i, --j) {
			if (matrix[i][col + 1] != MIN_VAL)
				return FALSE;
		}
	}
	if (row - 1 > -1) {
		if ((matrix[row - 1][col]) != MIN_VAL)
			return FALSE;
	}
	for (i = row, j = size; j > 0; ++i, --j) {
		if (matrix[i][col] != MIN_VAL)
			return FALSE;
	}
	if (row + size != MAX_VAL) {
		if (matrix[row + size][col] != MIN_VAL)
			return FALSE;
	}
	for (i = row, j = size; j > 0; ++i, --j) {/*A loop that inserts the submarine*/
		matrix[i][col] = size;
	}
	return TRUE;
}
bool Game(int matrix[][SIZE], char matrix_see[][SIZE]) {/*Game function*/
	int row, col, count = 0;
	printf("\nLet's start the game\n\n");
	print_Bord(matrix_see);
	do {
		printf("\n\n**To exit the game, enter line number -1 and column number -1**\n\n");
		printf("Enter a line number between 0 and 9\n");
		scanf("%d", &row);/*Receiving row number*/
		printf("Enter a column number between 0 and 9\n");
		scanf("%d", &col);/*Receiving column number*/
		++count;
		if ((col > MAX_VAL || col < -1) || (row > MAX_VAL || row < -1)) {/*Checks whether the values received are valid*/
			printf("Illegal values, please try again.\n");
		}
		else {
			if (col != -1 && row != -1) {/*Checks whether the user chose to exit*/
				if (matrix[row][col] == 0) {
					matrix_see[row][col] = '~';
					printf("\nMiss\n\n");
					print_Bord(matrix_see);
				}
				else {
					matrix_see[row][col] = 'x';
					printf("\nHit\n\n");
					print_Bord(matrix_see);/*Prints the matrix*/
					matrix[row][col] *= -1;
					if (count > 16) {
						if ((chack(matrix)) == TRUE) {/*A function that checks whether all submarines have been hit*/
							printf("You win");
							return TRUE;
						}
					}

				}
			}
		}

	} while (row != -1 || col != -1); /*Checks whether the user chose to exit*/

	return TRUE;
}
bool chack(int matrix[][SIZE]) {/*A function that checks whether all submarines have been hit*/
	int i, j;
	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j)
			if (matrix[i][j] > 0) {
				return FALSE;
			}
	}
	return TRUE;
}