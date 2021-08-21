#ifndef _MINE_H_
#define _MINE_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#pragma warning(disable:4996)

#define ROW 12
#define COL 12

#define NUM 10

void Game();
void InitBoard(char board[][COL], int row, int col, char elem);
void SetMine(char mine[][COL], int row, int col);
void ShowBoard(char board[][COL], int row, int col);
char GetNum(char mine[][COL], int x, int y); //'0', '1', '2'

#endif