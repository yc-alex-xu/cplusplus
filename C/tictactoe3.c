/*
小游戏,一个3*3的五子棋
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int board[3][3];  // -1 = empty, 0 = O, 1 = X
  int turn;         // O first
} state;

void init(state* s) {
  memset(&(s->board), -1, sizeof(s->board));
  s->turn = 0;
}

void display(const state* s) {
  int i, j;
  for (j = 0; j < 3; printf(++j < 3 ? "---+---+---\n" : "\n"))
    for (i = 0; i < 3; putchar("||\n"[i++]))
      printf(" %c ",
             s->board[j][i] == -1 ? '1' + j * 3 + i : "OX"[s->board[j][i]]);
}

int move_alex(state* s, int idx) {
  int * p = (int *) &(s->board) ; 
  if (p[idx] != -1) return 0;
  p[idx] = s->turn++ % 2;
  return 1;
}


int move(state* s, int i, int j) {
  if (s->board[j][i] != -1) return 0;
  s->board[j][i] = s->turn++ % 2;
  return 1;
}

void human(state* s) {
  char c;
  do {
    printf("%c: ", "OX"[s->turn % 2]);
    c = getchar();
    while (getchar() != '\n')
      ;
    printf("\n");
  } while (c < '1' || c > '9' || !move_alex(s, (c - '1')));
}

#define CHECK(j1, i1, j2, i2, j3, i3)                                   \
  if (s->board[j1][i1] != -1 && s->board[j1][i1] == s->board[j2][i2] && \
      s->board[j1][i1] == s->board[j3][i3])                             \
    return s->board[j1][i1] == 0 ? 1 : -1;

int evaluate(const state* s) {
  int i;
  for (i = 0; i < 3; i++) {
    CHECK(i, 0, i, 1, i, 2);  // horizontal
    CHECK(0, i, 1, i, 2, i);  // vertical
  }
  CHECK(0, 0, 1, 1, 2, 2);  // diagonal
  CHECK(0, 2, 1, 1, 2, 0);  // diagonal
  return 0;
}

int main() {
  state s;

  init(&s);

  display(&s);
  while (s.turn < 9) {
    human(&s);
    display(&s);
    switch (evaluate(&s)) {
      case 1:
        printf("O win\n");
        return 0;
      case -1:
        printf("X win\n");
        return 0;
    }
  }
  printf("Draw\n");
}
