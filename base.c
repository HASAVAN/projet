#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>
#include "headers.h"

#define TOTAL_KEYS 47 

/*------------------------------------------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------------------------------------------*/

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
    int j = 1 , k = 0 ,l = 0;
    int last_j = 0;
    int tex = 2 , y , x , textlen = 0;
    unsigned int truec[65536];
    double true_c = 0 , false_c = 0;
    int len;
    double ratio;
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
    WINDOW *nbrchar_win;
    WINDOW *chrono_win;
    WINDOW *ratio_win;
    WINDOW *wpm_win;

    type_win = newwin( typing.hei ,  typing.wid , typing.h , typing.w);
    text_win = newwin( tbox.hei ,  tbox.wid , tbox.h , tbox.w);
    nbrchar_win = newwin( 4 , 70 ,tbox.hei + 11 , 1);
    chrono_win = newwin(3 , 20 , 1 , tbox.wid+1);
    ratio_win = newwin(5 , 30 , 4 , tbox.wid+1);
    wpm_win = newwin(5 , 30 , 10 , tbox.wid+1);

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

    while(fgets( faketext, 255 ,text_to_type))
    {
        strcat(realtext , faketext);
        strcpy(textline[i].t_line , faketext);
        for(j = 0 ; j < 256 ;j++)
        {
            if(textline[i].t_line[j] == '\n')
            {
                mvwprintw(text_win , i , 1, "%s",faketext);
                wrefresh(text_win);
                i++;
                break;
            }
        }
        refresh();
    }

    j = 0;
    i = 1 ;
    wrefresh(text_win);

    while(realtext[textlen] != '\0')
    {
        if(realtext[textlen] == '\n')
        {            
            len++;
        }
        textlen++;
    }
    textlen = textlen - len;

    wrefresh(text_win);
    refresh();

    cbreak();
    noecho();

    time_t start_time, current_time;
    int elapsed_time;
    time(&start_time);

        wrefresh(chrono_win);
        wrefresh(nbrchar_win);
        wrefresh(ratio_win);

                            for(l = 0 ; l < 20 ;l++)
                            {
                                mvwprintw(text_win , l , 1, "%s",textline[l].t_line);
                                l++;
                            }
                                        for(k = 0 ; k < textlen ; k++)
                                        {
                                            box(type_win , 0 , 0);
                                            box(text_win , 0 , 0);
                                            box(chrono_win , 0 , 0);
                                            box(nbrchar_win , 0 , 0);
                                            box(ratio_win , 0 , 0);
                                            box(wpm_win , 0 , 0);

                                            wrefresh(type_win);
                                            wrefresh(text_win);
                                            wrefresh(chrono_win);
                                            wrefresh(nbrchar_win);
                                            wrefresh(ratio_win);
                                            wrefresh(wpm_win);

                                            time(&current_time);
                                            elapsed_time = difftime(current_time, start_time);
                                            

                                            int minutes = (int)(elapsed_time / 60);
                                            int seconds = (int)(elapsed_time % 60);
                                            int words_per_second = elapsed_time;

                                            wrefresh(chrono_win);
                                            refresh();
                                            mvwprintw(chrono_win , 1 , 1 , "Compteur : %02d:%02d", minutes, seconds);
                                            mvwprintw(ratio_win , 1 , 1 ,"ratio d'erreur : ");

                                            if(false_c != 0 && true_c !=0)
                                            {
                                                mvwprintw(ratio_win , 2 , 1 ," %.2lf%%" ,  (false_c / textlen)*100);
                                            }
                                            mvwprintw(ratio_win , 3 , 1 ,"%.0f erreur(s)" ,false_c);

                                            wrefresh(chrono_win);
                                            refresh();
                                    
                                            if(textline[i].t_line[j] == '\n')
                                            {
                                                i++;
                                                last_j = j - 1;
                                                j = 0;
                                            }
                                            refresh();
                                            curs_set(1);
                                            mvwprintw(nbrchar_win , 1 , 1 , "le nombre de caracteres correct est %.0f sur %d", true_c , textlen);
                                            wrefresh(nbrchar_win);
                                            

                                            mvwprintw(wpm_win , 1 , 1 , "Vitesse de frappes :(par seconde)");
                                            mvwprintw(wpm_win , 2 , 1 , "%.2fmots/secondes", (double)(k) / ((double)(words_per_second) * 5));
                                            
                                            typed = getch();
                                            true_c = 0;
                                            false_c = 0 ;

                                            for(int temp = 0 ; temp < k ; temp++)
                                            {
                                                if(truec[temp] == 1)
                                                {
                                                    true_c++;
                                                }
                                                else if(truec[temp] == 0)
                                                {
                                                    false_c++;
                                                }
                                            }

                                    
                                            refresh();
                                            mvwprintw(type_win , i , j+1 , "%c" , typed);


                                            if(typed == textline[i].t_line[j])
                                            {
                                                truec[k] = 1;
                                                wattron(text_win , A_REVERSE | COLOR_PAIR(1) );
                                                mvwprintw(text_win ,i ,j+1 , "%c" ,textline[i].t_line[j]);
                                                wattroff(text_win , A_REVERSE | COLOR_PAIR(1));

                                                wrefresh(type_win);
                                                refresh();
                                                j++;
                                            }

                                            else if(typed == 127)
                                            {
                                                truec[k] = 2;
                                                if(i > 0)
                                                {
                                                    if(j >= 0)
                                                    {
                                                        j--;
                                                        k--;
                                                        wmove(type_win ,i , j);
                                                        wmove(text_win ,i , j);
                                                        wdelch(type_win);

                                                        wattron(text_win , A_REVERSE);
                                                        mvwprintw(text_win , i , j+1  , "%c", textline[i].t_line[j]);
                                                        wattroff(text_win , A_REVERSE);

                                                        wrefresh(text_win);
                                                        wrefresh(type_win);
                                                        refresh();
                                                    }

                                                    else if(j = -1)
                                                    {
                                                        i--;
                                                        k--;
                                                        j = last_j;                  
                                                        wmove(text_win ,i , j);
                                                        wmove(type_win ,i , j);
                                                        
                                                        wattron(text_win , A_REVERSE);
                                                        mvwprintw(text_win , i , j+1  , "%c", textline[i].t_line[j]);
                                                        wattroff(text_win , A_REVERSE);

                                                        wrefresh(text_win);
                                                        wrefresh(type_win);
                                                        refresh();
                                                    }
                                                }
                                            }

                                            else if(typed == 10)
                                            {
                                                refresh();
                                            }

                                            else if(typed == 27)
                                            {
                                                break;
                                                refresh();
                                            }

                                            else if(typed != textline[i].t_line[j])
                                            {
                                                truec[k] = 0;

                                                wattron(text_win, A_REVERSE | COLOR_PAIR(2));
                                                mvwprintw(text_win , i , j+1 ,"%c" , textline[i].t_line[j]);
                                                wattroff(text_win,A_REVERSE | COLOR_PAIR(2));
                                        
                                                j++;
                                                wrefresh(type_win);
                                                refresh();
                                            }
                                            wrefresh(type_win);
                                            wrefresh(text_win);
                                            wrefresh(chrono_win);
                                            wrefresh(nbrchar_win);
                                            wrefresh(ratio_win);
                                            wrefresh(wpm_win);

                                                }
        
            delwin(type_win);
            delwin(text_win);
            refresh();
            touchwin(stdscr);
        
            refresh();
            wrefresh(nbrchar_win);
            refresh();
            delwin(nbrchar_win);
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
