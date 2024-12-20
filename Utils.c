#include "Utils.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

int CountNeighbours(char *board, int x, int y, int width, int height)
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

void CalculateIteration(char *currentBoard, char *nextBoard, int width, int height)
{
	#pragma omp parallel for
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
}

void CalculatePartOfIteration(char *currentBoard, char *nextBoard, int width, int height, int rowStart, int rowEnd)
{
	#pragma omp parallel for
	for (int y = rowStart; y < rowEnd; y++)
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
}

void RandomBoard(char *board, int width, int height)
{
	srand(time(NULL));
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int index = j + i * width;
			board[index] = rand() % 2;
			board[index] = 0;
		}
	}
}

void Glider(char* board, int width, int height) 
{
	board[3 + width] = 1;
	board[width * 2 + 4] = 1;
	board[width* 3 + 2] = 1;
	board[width* 3 + 3] = 1;
	board[width* 3 + 4] = 1;
}

void PrintBoard(char *board, int width, int height)
{
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = x + y * width;
			if(board[index] == 1)
			printf("*");
			else 
			printf(" ");
		}
		printf("|\n");
	}
	printf("------\n");
}

char *GetShiftedArray(char *board, int rank, int globalN)
{
	return board + (rank > 0 ? globalN : 0);
}

char *GetLastRowArray(char *board, int originalN, int globalN)
{
	return board + ((originalN - 1) + globalN);
}

char *GetBottomGhostRowArray(char *board, int originalN, int globalN)
{
	return board + ((originalN) + globalN);
}