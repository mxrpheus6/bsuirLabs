#define _DEFAULT_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <regex.h>
#include <ncurses.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>

#include "input_test.h"

#define DEV_INPUT "/dev/input/by-id/"

KeyMapping key_mappings[] = {
    {KEY_ESC, "[Esc]", 3, 5},
    {KEY_F1, "[F1]", 3, 11},
    {KEY_F2, "[F2]", 3, 15},
    {KEY_F3, "[F3]", 3, 19},
    {KEY_F4, "[F4]", 3, 23},
    {KEY_F5, "[F5]", 3, 27},
    {KEY_F6, "[F6]", 3, 31},
    {KEY_F7, "[F7]", 3, 35},
    {KEY_F8, "[F8]", 3, 39},
    {KEY_F9, "[F9]", 3, 43},
    {KEY_F10, "[F10]", 3, 47},
    {KEY_F11, "[F11]", 3, 53},
    {KEY_F12, "[F12]", 3, 57},
    {KEY_GRAVE, "[~`]", 5, 4},
    {KEY_1, "[1]", 5, 8},
    {KEY_2, "[2]", 5, 11},
    {KEY_3, "[3]", 5, 14},
    {KEY_4, "[4]", 5, 17},
    {KEY_5, "[5]", 5, 20},
    {KEY_6, "[6]", 5, 23},
    {KEY_7, "[7]", 5, 26},
    {KEY_8, "[8]", 5, 29},
    {KEY_9, "[9]", 5, 32},
    {KEY_0, "[0]", 5, 35},
    {KEY_MINUS, "[-]", 5, 38},
    {KEY_EQUAL, "[=]", 5, 41},
    {KEY_BACKSPACE, "[_<_]", 5, 44},
    {KEY_INSERT, "[I]", 5, 50},
    {KEY_HOME, "[H]", 5, 53},
    {KEY_PAGEUP, "[U]", 5, 56},
    {KEY_NUMLOCK, "[N]", 5, 60},
    {KEY_KPSLASH, "[/]", 5, 63},
    {KEY_KPASTERISK, "[*]", 5, 66},
    {KEY_KPMINUS, "[-]", 5, 69},
    {KEY_TAB, "[Tab]", 6, 4},
    {KEY_Q, "[Q]", 6, 9},
    {KEY_W, "[W]", 6, 12},
    {KEY_E, "[E]", 6, 15},
    {KEY_R, "[R]", 6, 18},
    {KEY_T, "[T]", 6, 21},
    {KEY_Y, "[Y]", 6, 24},
    {KEY_U, "[U]", 6, 27},
    {KEY_I, "[I]", 6, 30},
    {KEY_O, "[O]", 6, 33},
    {KEY_P, "[P]", 6, 36},
    {KEY_LEFTBRACE, "[{]", 6, 39},
    {KEY_RIGHTBRACE, "[}]", 6, 42},
    {KEY_DELETE, "[D]", 6, 50},
    {KEY_END, "[E]", 6, 53},
    {KEY_PAGEDOWN, "[D]", 6, 56},
    {KEY_KP7, "[7]", 6, 60},
    {KEY_KP8, "[8]", 6, 63},
    {KEY_KP9, "[9]", 6, 66},
    {KEY_KPPLUS, "|+|", 6, 69},
    {KEY_CAPSLOCK, "[Caps]", 7, 4},
    {KEY_A, "[A]", 7, 10},
    {KEY_S, "[S]", 7, 13},
    {KEY_D, "[D]", 7, 16},
    {KEY_F, "[F]", 7, 19},
    {KEY_G, "[G]", 7, 22},
    {KEY_H, "[H]", 7, 25},
    {KEY_J, "[J]", 7, 28},
    {KEY_K, "[K]", 7, 31},
    {KEY_L, "[L]", 7, 34},
    {KEY_SEMICOLON, "[;]", 7, 37},
    {KEY_APOSTROPHE, "[']", 7, 40},
    {KEY_ENTER, "[Entr|", 7, 43},
    {KEY_KP4, "[4]", 7, 60},
    {KEY_KP5, "[5]", 7, 63},
    {KEY_KP6, "[6]", 7, 66},
    {KEY_LEFTSHIFT, "[^   ]", 8, 4},
    {KEY_Z, "[Z]", 8, 11},
    {KEY_X, "[X]", 8, 14},
    {KEY_C, "[C]", 8, 17},
    {KEY_V, "[V]", 8, 20},
    {KEY_B, "[B]", 8, 23},
    {KEY_N, "[N]", 8, 26},
    {KEY_M, "[M]", 8, 29},
    {KEY_COMMA, "[,]", 8, 32},
    {KEY_DOT, "[.]", 8, 35},
    {KEY_SLASH, "[/]", 8, 38},
    {KEY_RIGHTSHIFT, "[^   ]", 8, 43},
    {KEY_UP, "[^]", 8, 53},
    {KEY_KP1, "[1]", 8, 60},
    {KEY_KP2, "[2]", 8, 63},
    {KEY_KP3, "[3]", 8, 66},
    {KEY_LEFTCTRL, "[Ctl]", 9, 4},
    {KEY_LEFTALT, "[Alt]", 9, 9},
    {KEY_SPACE, "[________________________]", 9, 14},
    {KEY_RIGHTALT, "[Alt]", 9, 40},
    {KEY_RIGHTALT, "[Ctl]", 9, 45},
    {KEY_LEFT, "[<]", 9, 50},
    {KEY_DOWN, "[v]", 9, 53},
    {KEY_RIGHT, "[>]", 9, 56},
    {KEY_RIGHT, "[ 0  ]", 9, 60},
    {KEY_KP3, "[.]", 9, 66},
};

void print_key(WINDOW* win, int row, int col, char* label) {
    mvwprintw(win, row, col, "%s", label);
    wrefresh(win);
    usleep(100000);
}

int num_key_mappings = sizeof(key_mappings) / sizeof(key_mappings[0]);
int is_mouse_device(char *mouse_name) {
    return strstr(mouse_name, "event-mouse") != NULL && strstr(mouse_name, "if") == NULL;
}

int is_keyboard_device(char *keyboard_name) {
    return strstr(keyboard_name, "event-kbd") != NULL && strstr(keyboard_name, "if") == NULL;
}

void replace_chars(char *str, char old_char, char new_char) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == old_char) {
            str[i] = new_char;
        }
    }
}

void draw_mouse(WINDOW* mouse_win) {
    mvwprintw(mouse_win, 1, 12, "   SCROLL UP  ");
    mvwprintw(mouse_win, 2, 12, "               ");
    mvwprintw(mouse_win, 3, 12, "     _._._     ");
    mvwprintw(mouse_win, 4, 12, "   .'  |  '.   ");
    mvwprintw(mouse_win, 5, 12, "  /    |    \\  ");
    mvwprintw(mouse_win, 6, 12, " |    [_]    | ");
    mvwprintw(mouse_win, 7, 12, " |     |     | ");
    mvwprintw(mouse_win, 8, 12, " |-----'-----| ");
    mvwprintw(mouse_win, 9, 12, " |           | ");
    mvwprintw(mouse_win, 10, 12, " |           | ");
    mvwprintw(mouse_win, 11, 12, " |.         .| ");
    mvwprintw(mouse_win, 12, 12, "  \\         /  ");
    mvwprintw(mouse_win, 13, 12, "   \\'._ _.'/   ");
    mvwprintw(mouse_win, 14, 12, "    '-...-'    ");
    mvwprintw(mouse_win, 15, 12, "               ");
    mvwprintw(mouse_win, 16, 12, "  SCROLL DOWN  ");
    mvwprintw(mouse_win, 18, 17, "3x left button to exit");
}

void draw_keyboard(WINDOW* keyboard_win) {
    mvwprintw(keyboard_win, 2, 3, ".--------------------------------------------------------------------.");
    mvwprintw(keyboard_win, 3, 3, "| [Esc] [F1][F2][F3][F4][F5][F6][F7][F8][F9][F10][F11][F12]          |");
    mvwprintw(keyboard_win, 4, 3, "|                                                                    |");
    mvwprintw(keyboard_win, 5, 3, "|[~`][1][2][3][4][5][6][7][8][9][0][-][=][_<_] [I][H][U] [N][/][*][-]|");
    mvwprintw(keyboard_win, 6, 3, "|[Tab][Q][W][E][R][T][Y][U][I][O][P][{][}] | | [D][E][D] [7][8][9]|+||");
    mvwprintw(keyboard_win, 7, 3, "|[Caps][A][S][D][F][G][H][J][K][L][;]['][Entr|           [4][5][6]|_||");
    mvwprintw(keyboard_win, 8, 3, "|[^   ] [Z][X][C][V][B][N][M][,][.][/]  [^   ]    [^]    [1][2][3]| ||");
    mvwprintw(keyboard_win, 9, 3, "|[Ctl][Alt][________________________][Alt][Ctl][<][v][>] [ 0  ][.]|_||");
    mvwprintw(keyboard_win, 10, 3, "'--------------------------------------------------------------------'");
    mvwprintw(keyboard_win, 13, 57, "Press F12 to exit");
}

char* parse_mouse_device(const char* mouse_name) {
    if (mouse_name == NULL) {
        return NULL;
    }

    DIR *dir;
    struct dirent *ent;
    char device_path[512];

    dir = opendir(DEV_INPUT);
    if (dir == NULL) {
        perror("Cannot open input device directory");
        return NULL;
    }

    char* dev_mouse_name = strdup(mouse_name);
    replace_chars(dev_mouse_name, ' ', '_');

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_LNK && is_mouse_device(ent->d_name) && (strstr(ent->d_name, dev_mouse_name) != NULL) ) {
            snprintf(device_path, sizeof(device_path), "%s%s", DEV_INPUT, ent->d_name);
            closedir(dir);
            return strdup(device_path);
        }
    }

    closedir(dir);
    return NULL;
}

char* parse_keyboard_device(const char* keyboard_name) {
    if (keyboard_name == NULL) {
        return NULL;
    }

    DIR *dir;
    struct dirent *ent;
    char device_path[512];

    dir = opendir(DEV_INPUT);
    if (dir == NULL) {
        perror("Cannot open input device directory");
        return NULL;
    }

    char* dev_keyboard_name = strdup(keyboard_name);
    replace_chars(dev_keyboard_name, ' ', '_');

    while ((ent = readdir(dir)) != NULL) {
        if (ent->d_type == DT_LNK && is_keyboard_device(ent->d_name) && strstr(ent->d_name, dev_keyboard_name) != NULL) {
            snprintf(device_path, sizeof(device_path), "%s%s", DEV_INPUT, ent->d_name);
            closedir(dir);
            return strdup(device_path);
        }
    }

    closedir(dir);
    return NULL;
}

int print_mouse_test_info(const char* mouse_name) {
    char* device_path = parse_mouse_device(mouse_name);
    if (device_path == NULL) {
        mvprintw(8, 8, "Mouse not found");
        return 0;
    }

    int win_height = 20;
    int win_width = 40;

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int starty = (max_y - win_height) / 2;
    int startx = (max_x - win_width) / 2;

    WINDOW* mouse_win = newwin(win_height, win_width, starty, startx);
    wbkgd(mouse_win, COLOR_PAIR(3));

    int fd = open(device_path, O_RDONLY);
    if (fd == -1) {
        perror("Cannot open mouse device");
        free(device_path);
        return 0;
    }

    struct input_event ie;
    draw_mouse(mouse_win);
    box(mouse_win, 0, 0);
    wrefresh(mouse_win);

    int left_pressed = 0, right_pressed = 0, middle_pressed = 0, middle_scrolled = 0;
    int exit_counter = 0;

    while (1) {
        draw_mouse(mouse_win);
        box(mouse_win, 0, 0);

        read(fd, &ie, sizeof(struct input_event));

        if (ie.type == EV_KEY && ie.code == BTN_LEFT) {
            left_pressed = ie.value;
            exit_counter++;
            middle_scrolled = 0;
        } else if (ie.type == EV_KEY && ie.code == BTN_RIGHT) {
            right_pressed = ie.value;
            exit_counter = 0;
            middle_scrolled = 0;
        } else if (ie.type == EV_KEY && ie.code == BTN_MIDDLE) {
            middle_pressed = ie.value;
            exit_counter = 0;
            middle_scrolled = 0;
        } else if (ie.type == EV_REL && ie.code == REL_WHEEL) {
            middle_scrolled = ie.value;
            exit_counter = 0;
        } 

        if (left_pressed) {
            wattron(mouse_win, COLOR_PAIR(2));
            mvwprintw(mouse_win, 4, 17, "  ");
            mvwprintw(mouse_win, 5, 15, "    ");
            mvwprintw(mouse_win, 6, 14, "    ");
            mvwprintw(mouse_win, 7, 14, "     ");
            wattroff(mouse_win, COLOR_PAIR(2));
        }

        if (right_pressed) {
            wattron(mouse_win, COLOR_PAIR(2));
            mvwprintw(mouse_win, 4, 20, "  ");
            mvwprintw(mouse_win, 5, 20, "    ");
            mvwprintw(mouse_win, 6, 21, "    ");
            mvwprintw(mouse_win, 7, 20, "     ");
            wattroff(mouse_win, COLOR_PAIR(2));
        }

        if (middle_pressed) {
            wattron(mouse_win, COLOR_PAIR(2));
            mvwprintw(mouse_win, 6, 19, " ");
            wattroff(mouse_win, COLOR_PAIR(2));
        }

        if (middle_scrolled > 0) {
            wattron(mouse_win, COLOR_PAIR(2) | A_BOLD);
            mvwprintw(mouse_win, 1, 15, "SCROLL  UP");
            wattroff(mouse_win, COLOR_PAIR(2) | A_BOLD);
        }
        if (middle_scrolled < 0) {
            wattron(mouse_win, COLOR_PAIR(2) | A_BOLD);
            mvwprintw(mouse_win, 16, 14, "SCROLL  DOWN");
            wattroff(mouse_win, COLOR_PAIR(2) | A_BOLD);
        }

        if (exit_counter == 5) {
            break;
        }
        wrefresh(mouse_win);
    }
    close(fd);
    endwin();
    free(device_path);
    return 1;
}

int print_keyboard_test_info(const char* keyboard_name) {
    char* device_path = parse_keyboard_device(keyboard_name);
    if (device_path == NULL) {
        mvprintw(8, 8, "Keyboard not found");
        return 0;
    }

    int win_height = 15;
    int win_width = 76;

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    int starty = (max_y - win_height) / 2;
    int startx = (max_x - win_width) / 2;

    WINDOW* keyboard_win = newwin(win_height, win_width, starty, startx);
    wbkgd(keyboard_win, COLOR_PAIR(3));

    int fd = open(device_path, O_RDONLY);
    if (fd == -1) {
        perror("Cannot open keyboard device");
        free(device_path);
        return 0;
    }

    struct input_event ie;
    draw_keyboard(keyboard_win);
    box(keyboard_win, 0, 0);
    wrefresh(keyboard_win);

    while (1) {
        draw_keyboard(keyboard_win);
        box(keyboard_win, 0, 0);

        read(fd, &ie, sizeof(struct input_event));

        if (ie.type == EV_KEY && ie.value == 1) {
            if (ie.code == KEY_F12) {
                break;
            }
            for (int i = 0; i < num_key_mappings; ++i) {
                if (ie.code == key_mappings[i].code) {
                    wattron(keyboard_win, COLOR_PAIR(2));
                    print_key(keyboard_win, key_mappings[i].row, key_mappings[i].col, key_mappings[i].label);
                    wattroff(keyboard_win, COLOR_PAIR(2));
                    break;
                }
            }
        }
        wrefresh(keyboard_win);
    }
    close(fd);
    endwin();
    free(device_path);
    return 1;
}