typedef struct {
    int number;
    char* name;
    int alternate_number;
    char* device_class;
    char* device_subclass;
    int protocol;
} Interface;

Interface* create_interface();
Interface** init_interface_array(int size);
void free_interface(Interface *interface);
void free_interface_array(Interface **interface_array, int size);
void parse_interfaces(Interface **interface_array, const char* path);

int count_interfaces(const char *path);