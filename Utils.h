#ifndef GAMEOFLIFE_UTILS_H
#define GAMEOFLIFE_UTILS_H
void CalculateIteration(int* currentBoard, int* nextBoard, int width, int height);
void RandomBoard(int* board, int width, int height);
void PrintBoard(int* board, int width, int height);
int *GetShiftedArray(const int *board, int rank, int globalN);
int *GetLastRowArray(const int *board, int originalN, int globalN);
int *GetBottomGhostRowArray(const int *board, int originalN, int globalN);
#endif //GAMEOFLIFE_UTILS_H