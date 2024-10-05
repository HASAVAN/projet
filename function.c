#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <termios.h>
#include "headers.h"
#include <time.h>
#include <fcntl.h>
void display()
{
    const char *color = "\033[34m"; 
    const char *reset = "\033[0m";  

    const char *commande = "figlet \tDACTYLO";
    FILE *fp;
    char buffer[128];

    fp = popen(commande, "r");
    if (fp == NULL) {
        perror("Erreur d'ouverture du pipe");
        return;
    }

    printf("%s", color);
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        for (int i = 0; buffer[i] != '\0'; i++) {
            putchar(buffer[i]); 
            fflush(stdout);      
            usleep(10000);      
        }
    }
    printf("%s", reset);
    system("clear");
}

WINDOW *create_win(int height , int width)
{
    box1 box;
    cbreak();
    noecho();
    curs_set(0);
    getmaxyx(stdscr , box.h , box.w);
    WINDOW *win = NULL;
    win = newwin( height ,  width , box.h/4 , box.w/4);
    refresh();
    box(win , 0 , 0);
    wrefresh(win);
    return win;
}


void option()
{
    WINDOW *option_win;
    WINDOW *return_win;
    box1 box;

    option_win = create_win(10 , 35);
    char *menu[3];
    menu[0] = "      Changer le langage      ";
    menu[1] = "     Changer la difficulte     ";
    menu[2] = "            Retour              ";
    wrefresh(option_win);
    int choix ,surbrillance;
    init_pair(1 , COLOR_CYAN , COLOR_BLACK);
    int i;
    keypad(option_win , TRUE);
    choix = 0;
    while(1)
    {
        box(option_win , 0 , 0);
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
            delwin(option_win);
            touchwin(stdscr);


            refresh();
            char *menu2[3];
            return_win = create_win(20 , 35);
            show_menu(return_win , menu2);
            choose_menu(return_win , menu2);
        }
        wrefresh(option_win);
        refresh();
}


/*--------------------------------------------------------------------------------*/
void games()
{
    WINDOW *jeu_win;
    WINDOW *return_win;
    box1 box;
    jeu_win = create_win(10 , 35);
    char *menu[3];
    menu[0] = "    Nouveau jeu    ";
    menu[1] = "   Continuer jeu   ";
    menu[2] = "   Statistiques    "; 
    menu[3] = "      Retour      ";
    wrefresh(jeu_win);
    int choix ,surbrillance;
    init_pair(1 , COLOR_CYAN , COLOR_BLACK);
    int i;
    keypad(jeu_win , TRUE);
    choix = 0;
    while(1)
    {
        box(jeu_win , 0 , 0);
        for(i = 0 ; i < 4 ; i++)
        {
            if(choix == i)
            {
                wattron(jeu_win , A_REVERSE);
                mvwprintw(jeu_win , i+3 , 5 , "%s",menu[i]);
                wattroff(jeu_win , A_REVERSE);
                wrefresh(jeu_win);
            }
            else if( choix != i)
            {
                wattron(jeu_win , A_NORMAL);
                mvwprintw(jeu_win , i+3 , 5 , "%s",menu[i]);
                wattroff(jeu_win , A_NORMAL);
                wrefresh(jeu_win);
            }
        }
        surbrillance=wgetch(jeu_win);

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
    }

        wrefresh(jeu_win);
        refresh();
        if(choix == 3)
        {
            delwin(jeu_win);
            touchwin(stdscr);
            refresh();
            char *menu2[3];
            return_win = create_win(20 , 35);
            show_menu(return_win , menu2);
            choose_menu(return_win , menu2);
        }
        wrefresh(jeu_win);
        refresh();
}
/*--------------------------------------------------------------------------------*/

void configurerTerminal(int active) 
{
    struct termios term;
    tcgetattr(0, &term);
    if (active) {
        term.c_lflag &= ~ICANON;
        term.c_lflag &= ~ECHO;
        tcsetattr(0, TCSANOW, &term);
        fcntl(0, F_SETFL, O_NONBLOCK);
    } else {
        term.c_lflag |= ICANON;
        term.c_lflag |= ECHO;
        tcsetattr(0, TCSANOW, &term);
        fcntl(0, F_SETFL, 0);
    }
}
void chrno()
{
    int heures = 0, minutes = 0, secondes = 0;
    int pause = 0;
    time_t debut, actuel, tempsDePause = 0;

    debut = time(NULL);

    configurerTerminal(1);

            actuel = time(NULL);
            int ecoule = (actuel - debut) - tempsDePause;

            heures = ecoule / 3600;
            minutes = (ecoule % 3600) / 60;
            secondes = ecoule % 60;


    printf("\r		%02d:%02d:%02d", heures, minutes, secondes);
    fflush(stdout);


    configurerTerminal(0);
}