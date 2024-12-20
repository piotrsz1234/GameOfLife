#ifndef GAMEOFLIFE_UTILS_H
#define GAMEOFLIFE_UTILS_H
void CalculateIteration(char* currentBoard, char* nextBoard, int width, int height);
void RandomBoard(char* board, int width, int height);
void PrintBoard(char* board, int width, int height);
char *GetShiftedArray(char *board, int rank, int globalN);
char *GetLastRowArray(char *board, int originalN, int globalN);
char *GetBottomGhostRowArray(char *board, int originalN, int globalN);
void Glider(char* board, int width, int height);
void CalculatePartOfIteration(char *currentBoard, char *nextBoard, int width, int height, int rowStart, int rowEnd);
#endif //GAMEOFLIFE_UTILS_H
