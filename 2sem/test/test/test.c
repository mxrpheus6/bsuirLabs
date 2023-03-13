#include <stdio.h>
#include <string.h>

typedef struct {
    char from[50];
    char to[50];
} Replacement;

int main() {
    Replacement replacements[] = {
        {"apple", "orange"},
        {"car", "truck"}
    };
    char input_string[] = "I like to eat apple and drive a car.";
    char output_string[1000] = "";

    char* word = (char*)malloc(1000);
    char* token = strtok(input_string, " ");
    while (token != NULL) {
        for (int i = 0; i < sizeof(replacements) / sizeof(replacements[0]); i++) {
            if (strcmp(token, replacements[i].from) == 0) {
                word = replacements[i].to;
                break;
            }
            else {
                word = token;
            }
        }
        strcat(output_string, word);
        strcat(output_string, " ");
        token = strtok(NULL, " ");
    }

    printf("%s\n", output_string);

    return 0;
}