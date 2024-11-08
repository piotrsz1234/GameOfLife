#include "Utils.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int CountNeighbours(int *board, int x, int y, int width, int height)
{
	int sum = 0;

	for (int i = -1; i <= 1; i++)
	{
		for (int j = -1; j <= 1; j++)
		{
			int cx = x + j;
			int cy = y + i;
			if (cx < 0 || cx >= width || cy < 0 || cy >= height || (cx == x && cy == y)) continue;

			sum += board[cx + cy * width];
		}
	}

	return sum;
}

void CalculateIteration(int *currentBoard, int *nextBoard, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = x + y * width;
			int nei = CountNeighbours(currentBoard, x, y, width, height);
			nextBoard[index] = 0;

			if (currentBoard[index] == 1)
			{
				if (nei == 2 || nei == 3)
				{
					nextBoard[index] = 1;
				}
			} else if (nei == 3)
			{
				nextBoard[index] = 1;
			}
		}
	}
	printf("\n");
}

void RandomBoard(int *board, int width, int height)
{
	srand(time(NULL));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = j + i * width;
			board[index] = rand() % 2;
		}
	}
}

void PrintBoard(int *board, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = x + y * width;
			printf("%d", board[index]);
		}
		printf("\n");
	}
	printf("\n");
}

int *GetShiftedArray(const int *board, int rank, int globalN)
{
	return board + (rank > 0 ? globalN : 0);
}

int *GetLastRowArray(const int *board, int originalN, int globalN)
{
	return board + ((originalN - 1) + globalN);
}

int *GetBottomGhostRowArray(const int *board, int originalN, int globalN)
{
	return board + ((originalN) + globalN);
}