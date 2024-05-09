typedef struct {
    int code;
    char* label;
    int row;
    int col;
} KeyMapping;

int is_mouse_device(char *mouse_name);

char* parse_mouse_device(const char* mouse_name);
int print_mouse_test_info(const char* mouse_name);

int is_keyboard_device(char *keyboard_name);

char* parse_keyboard_device(const char* keyboard_name);
int print_keyboard_test_info(const char* keyboard_name);