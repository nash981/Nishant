#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define EMPTY_TILE 0
#define ROWS 4
#define COLUMNS 4

void stack_horizontaly(int board[ROWS][COLUMNS], int rows, int columns)
{
  int a = columns;
  int tmp;


  for (; a < COLUMNS - 1; ++a) {
    tmp = board[rows][a];
    board[rows][a] = board[rows][a+1];
    board[rows][a+1] = tmp;
  }
}

void stack_verticaly(int board[ROWS][COLUMNS], int columns, int rows)
{
  int a = rows;
  int tmp;

  for (; a < ROWS - 1; ++a) {
    tmp = board[a][columns];
    board[a][columns] = board[a+1][columns];
    board[a+1][columns] = tmp;
  }
}

void add_horizontaly(int board[ROWS][COLUMNS])
{
  int a, b, flag;

  for (a = 0; a < ROWS; ++a) {
    for (b = 0, flag = 0; b < COLUMNS - 1 && flag != 4; ++b) {
      if (board[a][b] == EMPTY_TILE) {
	stack_horizontaly(board, a, b);
	--b;
	++flag;
      }
      else {
	if (board[a][b+1] == EMPTY_TILE) {
	  board[a][b+1] = board[a][b];
	  board[a][b] = EMPTY_TILE;
	  --b;
	} else if (board[a][b] == board[a][b+1]) {
	  board[a][b] += board[a][b+1];
	  board[a][b+1] = EMPTY_TILE;
	}
      }
    }
  }
}

void add_verticaly(int board[ROWS][COLUMNS])
{
  int a, b, flag;

  for (a = 0; a < COLUMNS; ++a) {
    for (b = 0, flag = 0; b < ROWS-1 && flag != 4; ++b) {
      if (board[b][a] == EMPTY_TILE) {
	stack_verticaly(board, a, b);
	--b;
	++flag;
      }
      else {
	if (board[b+1][a] == EMPTY_TILE) {
	  board[b+1][a] = board[b][a];
	  board[b][a] = EMPTY_TILE;
	  --b;
	} else if (board[b][a] == board[b+1][a]) {
	  board[b][a] += board[b+1][a];
	  board[b+1][a] = EMPTY_TILE;
	}
      }
    }
  }
}

void print_board(int board[ROWS][COLUMNS])
{
  system("clear");
  int a, b;

  for (a = 0; a < ROWS; ++a) {
    printf("\n");
    for (b = 0; b < COLUMNS; ++b) {
      printf("%5i", board[a][b]);
    }
  }
  printf("\n");
}


void reverse_board(char input[], int board[ROWS][COLUMNS])
{
  int a, b, c, tmp;

  if (!strcmp(input, "d")) {
    for (a = 0; a < ROWS; ++a) {
      for (b = 0, c = 3; b < 2; ++b, --c) {
	tmp = board[a][b];
	board[a][b] = board[a][c];
	board[a][c] = tmp;
      }
    }
  }
  else if  (!strcmp(input, "s")) {
    for (a = 0; a < COLUMNS; ++a) {
      for (b = 0, c = 3; b < 2; ++b, --c) {
	tmp = board[b][a];
	board[b][a] = board[c][a];
	board[c][a] = tmp;
      }
    }
  }
}

int check_board (int board[ROWS][COLUMNS])
{
  int a, b;

  int result = 0;
  int empty_tiles = 0;


  for (a = 0; a < ROWS; ++a)
    for (b = 0; b < COLUMNS; ++b)
      if (board[a][b] == 2048)
	result = -1;
      else if (board[a][b] == EMPTY_TILE)
	++empty_tiles;

  result = result == -1 ? result : empty_tiles;

  return result;
}

void generate(int board[ROWS][COLUMNS], int empty_tiles )
{

  srand(time(NULL));

  int a, b;
  int random = 0;
  int tile = 0;

  random = rand() % empty_tiles;
  tile = (rand() % 9 == 4) ? 4 : 2;

  for (a = 0; a < ROWS; ++a)
    for (b = 0; b < COLUMNS; ++b)
      if (board[a][b] == EMPTY_TILE && random != 0)
	--random;
      else if (board[a][b] == EMPTY_TILE && random == 0) {
	board[a][b] = tile;
	return;
      }
}



int play_game(int board[ROWS][COLUMNS])
{

  char movement[81];
  int tiles = 0;

  print_board(board);
  while (1) {
    printf("(enter: a->left,d->right,w->up,s->down,e->exit)>> ");
    scanf("%s", movement);
    if (!strcmp(movement, "s")) {
      reverse_board(movement,board);
      add_verticaly(board);
      tiles = check_board(board);
      if (tiles == -1)
	return -1;
      else if (tiles == 0)
	return 0;
      generate(board,tiles);
      reverse_board(movement, board);
    }
    else if (!strcmp(movement, "w")) {
      add_verticaly(board);
      tiles = check_board(board);
      if (tiles == -1)
	return -1;
      else if (tiles == 0)
	return 0;
      generate(board,tiles);
    }
    else if (!strcmp(movement, "d")) {
      reverse_board(movement,board);
      add_horizontaly(board);
      tiles = check_board(board);
      if (tiles == -1)
	return -1;
      else if (tiles == 0)
	return 0;
      generate(board,tiles);
      reverse_board(movement, board);
    }
    else if (!strcmp(movement, "a")) {
      add_horizontaly(board);
      tiles = check_board(board);
      if (tiles == -1)
	return -1;
      else if (tiles == 0)
	return 0;
      generate(board,tiles);
    }
    else if (!strcmp(movement, "e")) {
      return 1;
    }
    else {
      printf("Do not recognize this movement please type again\n");
      continue;
    }
    print_board(board);
  }
}


int main(void)
{

  int win_condition;
  int board[ROWS][COLUMNS] = {
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0},
    {0,0,0,0}
  };


  generate(board, 16);

  win_condition = play_game(board);
  switch (win_condition) {
  case 1:
    printf("But you are not done yet!!!\n"	\
	   "Fine, see you another day\n");
    break;
  case 0:
    printf("Ohh noo, you run out of tiles\n"	\
	   "Restart the program to play again\n");
    break;
  case -1:
    printf("You win\n");
    break;
  }

  return 0;
}

