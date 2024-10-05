#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include "headers.h"


void show_menu(WINDOW *win , char *menu[])
{
    box1 box;
    int i;
    menu[0] = "    Base de la dactylographie    ";
    menu[1] = "              Jeu                ";
    menu[2] = "             Option              ";
    menu[3] = "             Quitter             ";

    wrefresh(win);

}

void choose_menu(WINDOW *win , char *menu[])
{
    int choix ,surbrillance;
    box1 box;
    init_pair(1 , COLOR_CYAN , COLOR_BLACK);
    int i;
    keypad(win , TRUE);
    choix = 0;

    while(1)
    {
        box(win , 0 , 0);
        wrefresh(win);
        for(i = 0 ; i < 4 ; i++)
        {
            if(choix == i)
            {
                wattron(win , A_REVERSE);
                mvwprintw(win , i+2 , 1 , "%s",menu[i]);
                wattroff(win , A_REVERSE);
                wrefresh(win);
            }
            else if( choix != i)
            {
                wattron(win , A_NORMAL);
                mvwprintw(win , i+2 , 1 , "%s",menu[i]);
                wattroff(win , A_NORMAL);
                wrefresh(win);
            }
        }
        surbrillance=wgetch(win);

        switch((surbrillance))
        {
            case KEY_DOWN :
                choix++;
                if(choix == 4)
                {
                    choix = 0;
                }
                break;
            
            case KEY_UP :
                choix--;
                if(choix == -1)
                {
                    choix = 3;
                }
                break;

            default:
                break;
        }


        if(surbrillance == 10)
        {
            break;
        }

        wrefresh(win);
        refresh();
    }
    
    if(choix == 0)
    {
        delwin(win);
        touchwin(stdscr);
        learn();
    }


    else if(choix == 1)
    {
        delwin(win);
        touchwin(stdscr);
        refresh();
        wrefresh(stdscr);
        games();
    }

    else if(choix == 2)
    {
        delwin(win);
        touchwin(stdscr);
        refresh();
        wrefresh(stdscr);
        option();
    }

    else if(choix == 3)
    {
        delwin(win);
        touchwin(stdscr);

        refresh();
        wrefresh(stdscr);
        endwin();
        exit(EXIT_SUCCESS);
    }
}
