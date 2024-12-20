#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include "Utils.h"

int main(int argc, char *argv[])
{
	clock_t startTime = clock();
	int N = argc > 1 ? atoi(argv[1]) : 5;
	int iterations = argc > 2 ? atoi(argv[2]) : 5;
	printf("Table size: %d\nIterations: %d\n", N, iterations);
	char *board = malloc(N * N * sizeof(char));
	char *newBoard = malloc(N * N * sizeof(char));

	RandomBoard(board, N, N);

	for (int i = 0; i < iterations; i++)
	{
		CalculateIteration(board, newBoard, N, N);
		char *temp = board;
		board = newBoard;
		newBoard = temp;
	}

	free(board);
	free(newBoard);
	clock_t endTime = clock();
	double dur = (double)(endTime - startTime) / CLOCKS_PER_SEC / iterations;
	printf("CPU time used (per clock()): %.2f s\n", dur);

	return 0;
}
