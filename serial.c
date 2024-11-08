#include <stdlib.h>
#include <unistd.h>
#include "Utils.h"

int main(int argc, char *argv[])
{
	int N = argc > 1 ? atoi(argv[1]) : 5;
	int iterations = argc > 2 ? atoi(argv[2]) : 5;

	int *board = malloc(N * N * sizeof(int));
	int *newBoard = malloc(N * N * sizeof(int));

	RandomBoard(board, N, N);

	for (int i = 0; i < iterations; i++)
	{
		CalculateIteration(board, newBoard, N, N);
		sleep(1);
		int *temp = board;
		board = newBoard;
		newBoard = temp;
	}

	free(board);
	free(newBoard);

	return 0;
}
