#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "headers.h"

#define TOTAL_KEYS 47 

void learn()
{
    WINDOW *option_win;
    WINDOW *return_win;
    box1 box;
    option_win = create_win(10 , 35);
    char *menu[3];
    menu[0] = "    Apprendre la dactilographie  ";
    menu[1] = "       Tester votre clavier      ";
    menu[2] = "             Retour              ";
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
        if(choix == 0)
        {

            delwin(option_win);
            touchwin(stdscr);
            refresh();
            type();
        }

         else if(choix == 1)
        {
            delwin(option_win);
            touchwin(stdscr);
            refresh();
            keyboard();
        }
        else if(choix == 2)
        {
            char *menu2[3];

            delwin(option_win);
            touchwin(stdscr);
            refresh();

            return_win = create_win(10 , 35);
            show_menu(return_win , menu2);
            choose_menu(return_win , menu2);
        }
        wrefresh(option_win);
        refresh();
}



void type()
{
    char **text=NULL;
    int typed;
    char realtext[65536];
    char faketext[1024];

    box1 box;
    typetext typing;
    textbox tbox;
    line *textline;

    int i = 1 ;
    int j = 1 , k = 0;
    int tex = 2 , y , x , textlen = 0;
    unsigned int truec[65536];
    int true_c = 0;
    getmaxyx(stdscr , y , x);

    tbox.hei = 20;
    tbox.wid = 120;
    tbox.h = 1;
    tbox.w = 1;

    typing.hei = 10;
    typing.wid = 120;
    typing.h = tbox.hei + 1;
    typing.w = 1;


    WINDOW *type_win;
    WINDOW *text_win;
    WINDOW *return_win;
    WINDOW *nbrcharwin;
    WINDOW *chronowin;

    type_win = newwin( typing.hei ,  typing.wid , typing.h , typing.w);
    text_win = newwin( tbox.hei ,  tbox.wid , tbox.h , tbox.w);
    nbrcharwin = newwin( 4 , 70 ,tbox.hei + 11 , 1);
    chronowin = newwin(3 , 20 , 1 , tbox.wid+1);

    refresh();
    start_color();

    init_pair(1 , COLOR_GREEN , COLOR_BLACK);
    init_pair(2 , COLOR_RED , COLOR_BLACK);

    keypad(type_win , TRUE);
    wrefresh(type_win);
    wrefresh(text_win);
    refresh();
    cbreak();


    FILE *text_to_type;
    text_to_type = fopen("text1" , "r");

    textline = malloc(sizeof(line)*512);

    i = 1 ;
    while(fgets( faketext, 255 ,text_to_type))
    {
        strcat(realtext , faketext);
        strcpy(textline[i].t_line , faketext);
        mvwprintw(text_win , i , 1 , "%s" ,textline[i].t_line);
        for(j = 0 ; j < 256 ;j++)
        {
            if(textline[i].t_line[j] == '\n')
            {
                i++;
            }
        }
        j = 1;
        refresh();
    }

    j = 1;
    i = 1 ;

    wrefresh(text_win);

    while(realtext[textlen] != '\0')
    {
        textlen++;
    }

    wrefresh(text_win);
    refresh();

    cbreak();
    noecho();

    time_t start_time, current_time;
    int elapsed_time;
    time(&start_time);

        wrefresh(chronowin);
        wrefresh(nbrcharwin);


    for(k = 0 ; k < textlen ; k++)
    {
        box(type_win , 0 , 0);
        box(text_win , 0 , 0);
        box(chronowin , 0 , 0);
        box(nbrcharwin , 0 , 0);

        wrefresh(type_win);
        wrefresh(text_win);
        wrefresh(chronowin);
        wrefresh(nbrcharwin);

        curs_set(1);
        typed = getch();

        box(text_win , 0 , 0);
        box(type_win , 0 , 0);
        box(nbrcharwin , 0 , 0);
        true_c = 0;
        for(int temp = 0 ; temp < k ; temp++)
        {
            if(truec[temp] == 1)
            {
                true_c++;
            }
        }

        time(&current_time);
        elapsed_time = difftime(current_time, start_time);

        int minutes = (int)(elapsed_time / 60);
        int seconds = (int)(elapsed_time % 60);
        
        mvwprintw(chronowin , 1 , 1 , "Compteur : %02d:%02d", minutes, seconds);
        wrefresh(chronowin);
        refresh();
        mvwprintw(nbrcharwin , 1 , 1 , "le nombre de caracteres correct est %d sur %d", true_c , textlen);
 
        refresh();
        mvwprintw(type_win , i , j , "%c" , typed);

        if(realtext[k] == '\n')
        {
            i++;
            mvwprintw(text_win , i , 1 , "%s" ,textline[i].t_line);
            wrefresh(text_win);
            j=1;
        }

        if(typed == realtext[k])
        {
            if(j > 119)
            {
                i++;
            }
            else if(j < 0)
            {
                j = 1;
            }
            truec[k] = 1;
            wattron(text_win , A_REVERSE | COLOR_PAIR(1) );
            mvwprintw(text_win ,i ,j , "%c" ,realtext[k]);
            wattroff(text_win , A_REVERSE | COLOR_PAIR(1));

            j++;
            wrefresh(type_win);
            refresh();
        }

        else if(typed == 127)
        {
            truec[k] = 0;
            if(i > 1)
            {
                if(j > 0)
                {
                    j--;
                    k-=2;
 
                    wmove(type_win ,i , j);
                    wdelch(type_win);

                    wattron(text_win , A_REVERSE);
                    mvwprintw(text_win , i , j  , "%c", realtext[k+1]);
                    wattroff(text_win , A_REVERSE);

                    wrefresh(text_win);
                    wrefresh(type_win);
                    refresh();
                }

                else if(j = 0)
                {
                    i--;
                    j = 1;                     
                    k = 0;
                    wmove(type_win ,i , j);
                    
                    wattron(text_win , A_REVERSE);
                    mvwprintw(text_win , i , j  , "%c", realtext[k]);
                    wattroff(text_win , A_REVERSE);

                    wrefresh(text_win);
                    wrefresh(type_win);
                }
            }
        }

        else if(typed == 10)
        {
            j = 1;
            i++;
            refresh();
        }

        else if(typed == 27)
        {
            break;
            refresh();
        }

        else if(typed != realtext[k])
        {
            if(j > 119)
            {
                i++;
                j = 1;
            }
            truec[k] = 0;

            wattron(text_win, A_REVERSE | COLOR_PAIR(2));
            mvwprintw(text_win , i , j ,"%c" , realtext[k]);
            wattroff(text_win,A_REVERSE | COLOR_PAIR(2));
     
            j++;
            wrefresh(type_win);
            refresh();
        }
            wrefresh(chronowin);
            wrefresh(nbrcharwin);
            wrefresh(type_win);
            wrefresh(text_win);
            }
        
            delwin(type_win);
            delwin(text_win);
            refresh();
            touchwin(stdscr);
        
            refresh();
            wrefresh(nbrcharwin);
            refresh();
            delwin(nbrcharwin);
            refresh();
            touchwin(stdscr);

            learn();
}

void keyboard()
{ 
    WINDOW *kb_win;
    int y , x , typed , i , j;
Key keys[TOTAL_KEYS] = {
    // Ligne 1 (chiffres et symboles)
    {"1", 2, 1}, {"2", 6, 1}, {"3", 10, 1}, {"4", 14, 1}, {"5", 18, 1},
    {"6", 22, 1}, {"7", 26, 1}, {"8", 30, 1}, {"9", 34, 1}, {"0", 38, 1},
    // Ligne 2 (lettres)
    {"Q", 3, 3}, {"W", 7, 3}, {"E", 11, 3}, {"R", 15, 3}, {"T", 19, 3},
    {"Y", 23, 3}, {"U", 27, 3}, {"I", 31, 3}, {"O", 35, 3}, {"P", 39, 3},
    // Ligne 3 (lettres)
    {"A", 4, 5}, {"S", 8, 5}, {"D", 12, 5}, {"F", 16, 5}, {"G", 20, 5},
    {"H", 24, 5}, {"J", 28, 5}, {"K", 32, 5}, {"L", 36, 5},
    // Ligne 4 (lettres et touches spéciales)
    {"Z", 6, 7}, {"X", 10, 7}, {"C", 14, 7}, {"V", 18, 7}, {"B", 22, 7},
    {"N", 26, 7}, {"M", 30, 7},
    // Espace et touches spéciales
    {"SPACE", 14, 9}, {"ENTER", 35, 9}, {"CTRL", 2, 9}, {"ALT", 5, 9},
    {"SHIFT", 9, 9}, {"TAB", 2, 7}, {"ESC", 2, 1}, {"BACKSPACE", 42, 1},
    // Flèches
    {"UP", 50, 7}, {"LEFT", 46, 9}, {"DOWN", 50, 9}, {"RIGHT", 54, 9}
};

int find_key(const char *label) {
    for (int i = 0; i < TOTAL_KEYS; i++) {
        if (strcmp(keys[i].label, label) == 0) {
            return i;
        }
    }
    return -1;
}

void display_keys(WINDOW *win) {
    for (int i = 0; i < TOTAL_KEYS; i++) {
        mvwprintw(win, keys[i].y, keys[i].x, "[%s]", keys[i].label);
    }
    wrefresh(win);
}

    WINDOW *keyboard_win = newwin(12, 60, 0, 0);
    box(keyboard_win, 0, 0);

    display_keys(keyboard_win);

    int ch;
    while ((ch = getch()) != 127) {
        werase(keyboard_win);
        box(keyboard_win, 0, 0);
        display_keys(keyboard_win);

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            char letter[2] = {(char)toupper(ch), '\0'};
            int idx = find_key(letter);
            if (idx != -1) {
                wattron(keyboard_win, A_STANDOUT);
                mvwprintw(keyboard_win, keys[idx].y, keys[idx].x, "[%s]", keys[idx].label);
                wattroff(keyboard_win, A_STANDOUT);
            }
        }
        else if (ch >= '0' && ch <= '9')
        {
            char num[2] = {(char)ch, '\0'};
            int idx = find_key(num);
            if (idx != -1) {
                wattron(keyboard_win, A_STANDOUT);
                mvwprintw(keyboard_win, keys[idx].y, keys[idx].x, "[%s]", keys[idx].label);
                wattroff(keyboard_win, A_STANDOUT);
            }
        }
        else if (ch == ' ') {
            int idx = find_key("SPACE");
            wattron(keyboard_win, A_STANDOUT);
            mvwprintw(keyboard_win, keys[idx].y, keys[idx].x, "[%s]", keys[idx].label);
            wattroff(keyboard_win, A_STANDOUT);
        }
        else if (ch == 10) {  // Touche Entrée
            int idx = find_key("ENTER");
            wattron(keyboard_win, A_STANDOUT);
            mvwprintw(keyboard_win, keys[idx].y, keys[idx].x, "[%s]", keys[idx].label);
            wattroff(keyboard_win, A_STANDOUT);
        }
        else if (ch == KEY_UP) {
            int idx = find_key("UP");
            wattron(keyboard_win, A_STANDOUT);
            mvwprintw(keyboard_win, keys[idx].y, keys[idx].x, "[%s]", keys[idx].label);
            wattroff(keyboard_win, A_STANDOUT);
        }
        else if (ch == KEY_DOWN) {
            int idx = find_key("DOWN");
            wattron(keyboard_win, A_STANDOUT);
            mvwprintw(keyboard_win, keys[idx].y, keys[idx].x, "[%s]", keys[idx].label);
            wattroff(keyboard_win, A_STANDOUT);
        }
        else if (ch == KEY_LEFT) {
            int idx = find_key("LEFT");
            wattron(keyboard_win, A_STANDOUT);
            mvwprintw(keyboard_win, keys[idx].y, keys[idx].x, "[%s]", keys[idx].label);
            wattroff(keyboard_win, A_STANDOUT);
        }
        else if (ch == KEY_RIGHT) {
            int idx = find_key("RIGHT");
            wattron(keyboard_win, A_STANDOUT);
            mvwprintw(keyboard_win, keys[idx].y, keys[idx].x, "[%s]", keys[idx].label);
            wattroff(keyboard_win, A_STANDOUT);
        }
        wrefresh(keyboard_win);
    }

    while(typed != 27)
    {
        touchwin(stdscr);
        refresh();
        learn();
    }   

}
