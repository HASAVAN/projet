#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "headers.h"

int main()
{
    display();
    initscr();
    WINDOW *win;
    char *menu[3];

    win = create_win(10 , 35);
    show_menu(win , menu);
    choose_menu(win , menu);

    endwin();
    return 0;
}