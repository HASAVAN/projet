typedef struct box
    {
        int h;
        int w;
    }box1;

WINDOW *create_win();

void show_menu(WINDOW *win , char *menu[]);

void choose_menu(WINDOW *win , char *menu[]);

void option();
