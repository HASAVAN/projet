#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "headers.h"


WINDOW *create_win()
{
    box1 box;
    cbreak();
    noecho();
    curs_set(0);
    getmaxyx(stdscr , box.h , box.w);
    WINDOW *win = NULL;
    win = newwin( 20 ,  40 , box.h/4 , box.w/4);
    refresh();
    box(win , 0 , 0);
    wrefresh(win);
    return win;
}

void show_menu(WINDOW *win , char *menu[])
{
    box1 box;
    int i;
    menu[0] = "Base de la dactylographie";
    menu[1] = "Option";
    menu[2] = "Quitter";

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
        for(i = 0 ; i < 3 ; i++)
        {
            if(choix == i)
            {
                wattron(win , A_REVERSE);
                mvwprintw(win , i+2 , box.h/4 , "%s",menu[i]);
                wattroff(win , A_REVERSE);
                wrefresh(win);
            }
            else if( choix != i)
            {
                wattron(win , A_NORMAL);
                mvwprintw(win , i+2 , box.h/4 , "%s",menu[i]);
                wattroff(win , A_NORMAL);
                wrefresh(win);
            }
        }
        surbrillance=wgetch(win);
        switch((surbrillance))
        {
            case KEY_DOWN :
                choix++;
                if(choix == 3)
                {
                    choix = 0;
                }
                break;
            
            case KEY_UP :
                choix--;
                if(choix == -1)
                {
                    choix = 2;
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

    }
    else if(choix == 1)
    {
        option();
    }
    else if(choix == 2)
    {
        endwin();
        exit(EXIT_SUCCESS);
    }
}


void option()
{
    WINDOW *option_win;
    WINDOW *return_win;
    box1 box;
    option_win = create_win();
    char *menu[3];
    menu[0] = "Changer le langage";
    menu[1] = "Changer la difficulte";
    menu[2] = "Retour";
    wrefresh(option_win);
    int choix ,surbrillance;
    init_pair(1 , COLOR_CYAN , COLOR_BLACK);
    int i;
    keypad(option_win , TRUE);
    choix = 0;
    while(1)
    {
        for(i = 0 ; i < 3 ; i++)
        {
            if(choix == i)
            {
                wattron(option_win , A_REVERSE);
                mvwprintw(option_win , i+2 , 1 , "%s",menu[i]);
                wattroff(option_win , A_REVERSE);
                wrefresh(option_win);
            }
            else if( choix != i)
            {
                wattron(option_win , A_NORMAL);
                mvwprintw(option_win , i+2 , 1 , "%s",menu[i]);
                wattroff(option_win , A_NORMAL);
                wrefresh(option_win);
            }
        }
        surbrillance=wgetch(option_win);

        switch((surbrillance))
        {
            case KEY_DOWN :
                choix++;
                if(choix == 3)
                {
                    choix = 0;
                }
                break;
            
            case KEY_UP :
                choix--;
                if(choix == -1)
                {
                    choix = 2;
                }
                break;

            default:
                break;
        }
        if(surbrillance == 10)
        {
            break;
        }
    }

        wrefresh(option_win);
        refresh();
        if(choix == 2)
        {
            char *menu2[3];
            return_win = create_win();
            show_menu(return_win , menu2);
            choose_menu(return_win , menu2);
        } 
        wrefresh(option_win);
        refresh();
}
