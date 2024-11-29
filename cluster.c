#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>
#include "Utils.h"

void CopyLocalArray(int *board, int originalN, int globalN, int *globalBoard)
{
	for (int y = 0; y < originalN; y++)
	{
		for (int x = 0; x < globalN; x++)
		{
			int index = x + y * globalN;
			globalBoard[index] = board[index];
		}
	}
}

int main(int argc, char *argv[])
{
	int globalN = argc > 1 ? atoi(argv[1]) : 5;
	int iterations = argc > 2 ? atoi(argv[2]) : 5;
	int syncToSave = argc > 3 ? atoi(argv[3]) : 0;

	MPI_Init(&argc, &argv);
	int rank, size;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	double startTime = MPI_Wtime();
	printf("Dzien dobry: %d %d %d", globalN, iterations, syncToSave);
	int N = globalN / size;
	int allocated = N * (rank + 1);
	if (allocated < globalN)
		N == (globalN - allocated);

	int originalN = N;

	if (rank == 0 || rank == size - 1)
	{
		N++;
	}
	else
	{
		N += 2;
	}
	int *globalBoard = NULL;

	int *board = malloc(N * globalN * sizeof(int));
	int *newBoard = malloc(N * globalN * sizeof(int));

	if (rank == 0 && syncToSave > 0)
	{
		globalBoard = malloc(globalN * globalN * sizeof(int));
	}
	RandomBoard((GetShiftedArray(board, rank, globalN)), globalN, originalN);

	if (rank == 0 && syncToSave > 0)
	{
		Glider(board, globalN, originalN);
		globalBoard = malloc(globalN * globalN * sizeof(int));
		CopyLocalArray(board, originalN, globalN, globalBoard);
		PrintBoard(globalBoard, globalN, globalN);
	}

	for (int i = 0; i < iterations; i++)
	{
		if (rank < size - 1)
		{
			MPI_Sendrecv(GetLastRowArray(board, originalN, globalN), globalN, MPI_INT, rank + 1, 0,
						 GetBottomGhostRowArray(board, originalN, globalN), globalN, MPI_INT, rank + 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		}
		if (rank > 0)
		{
			MPI_Sendrecv(GetShiftedArray(board, rank, globalN), globalN, MPI_INT, rank - 1, 0,
						 board, globalN, MPI_INT, rank - 1, 0, MPI_COMM_WORLD,
						 MPI_STATUS_IGNORE);
		}

		CalculateIteration(board, newBoard, globalN, N);
		int *temp = board;
		board = newBoard;
		newBoard = temp;

		if (syncToSave > 0)
		{
			if (rank == 0)
			{
				CopyLocalArray(board, originalN, globalN, globalBoard);

				for (int r = 1; r < size; r++)
				{
					int *shifted = globalBoard + r * globalN;
					MPI_Recv(shifted, globalN, MPI_INT, r, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				}

				PrintBoard(globalBoard, globalN, globalN);
			}
			else
			{
				MPI_Send(GetShiftedArray(board, rank, globalN), originalN * globalN, MPI_INT, 0, 0, MPI_COMM_WORLD);
			}
		}
	}

	double endTime = MPI_Wtime();

	printf("\n\n%f", (endTime - startTime));

	free(board);
	free(newBoard);
	MPI_Finalize();
}