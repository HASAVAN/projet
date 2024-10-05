#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "headers.h"



void display_time(WINDOW *win, int start_time) {
    int current_time = time(NULL) - start_time;
    int minutes = current_time / 60;
    int seconds = current_time % 60;

    mvwprintw(win, 1, 1, "Chrono: %02d:%02d", minutes, seconds);  // Afficher le chrono formaté
    wrefresh(win);
}
         