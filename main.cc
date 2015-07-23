#include <ncurses.h>      /* ncurses.h includes stdio.h */
#include "editor.h"
#include <iostream>

const int ESC = 27;

int cur_row, cur_col;
bool insert_mode = false;

int main() {
  // init screen
  int row, col;
  initscr();       /* start the curses mode */
  getmaxyx(stdscr, row, col);    /* get the number of rows and columns */
  refresh();
  Editor editor(row, col);
  bool running = true;
  while (running) {
    char input = getch(); //getchar doesn't work here?
    bool success = editor.Input(input);
    if (!success) {
      running = false;
    }
  }

  endwin();
  return 0;
}
