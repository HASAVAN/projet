typedef struct box
    {
        int h;
        int w;
    }box1;


typedef struct typetext
    {
        int h;
        int w;
        int hei;
        int wid;
    }typetext;


typedef struct textbox
    {
        int h;
        int w;
        int hei;
        int wid;
    }textbox;

typedef struct text_l
{
    char t_line[2048];
}line;


typedef struct {
    const char *label;
    int x, y;
} Key;

void display();

WINDOW *create_win(int height , int width);

void show_menu(WINDOW *win , char *menu[]);

void choose_menu(WINDOW *win , char *menu[]);

void option();

void type();

void learn();

void games();

void keyboard();

int find_key(const char *label);

void display_keys(WINDOW *win);

void display_time(WINDOW *win, int start_time);
