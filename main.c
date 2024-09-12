#include <stdio.h>
#include <ncurses.h>
#include "headers.h"

int main()
{
    initscr();
    WINDOW *win;
    char *menu[3];

    win = create_win();
    show_menu(win , menu);
    choose_menu(win , menu);

    endwin();
    return 0;
}