#define PATH_LEN 4096

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <getopt.h>

extern int scandir(const char *dirp, struct dirent ***namelist,
            int (*filter)(const struct dirent*),
            int (*compar)(const struct dirent**, const struct dirent**));

extern int lstat(const char* restrict path, struct stat *restrict buf);

struct Options 
{
    int symlinks;
    int directories;
    int files;
    int sort;
};

void init_options(struct Options* opt) {
    opt->symlinks = 0;
    opt->directories = 0;
    opt->files = 0;
    opt->sort = 0;
}

int compare_lc(const struct dirent** a, const struct dirent** b) {
    return strcoll((*a)->d_name, (*b)->d_name);
}

void process_catalog(const char* catalog, const struct Options* opt) {
    struct dirent** dnt;
    int num_dnt;

    if (opt->sort)
        num_dnt = scandir(catalog, &dnt, NULL, compare_lc);
    else
        num_dnt = scandir(catalog, &dnt, NULL, NULL);

    char full_path[PATH_LEN];
    struct stat buf;
    for (int i = 0; i < num_dnt; i++) {
        
        if (strcmp(dnt[i]->d_name, ".") == 0 || strcmp(dnt[i]->d_name, "..") == 0) {
            continue;
        }

        sprintf(full_path, "%s/%s", catalog, dnt[i]->d_name);
        if (lstat(full_path, &buf) == 0) {  
            if (S_ISLNK(buf.st_mode) && opt->symlinks)
                printf("%s\n", full_path);
            else if (S_ISDIR(buf.st_mode) && opt->directories)
                printf("%s\n", full_path);
            else if (S_ISREG(buf.st_mode) && opt->files)
                printf("%s\n", full_path);
            else if (opt->symlinks == 0 && opt->directories == 0 && opt->files == 0)
                printf("%s\n", full_path);

            if (S_ISDIR(buf.st_mode)) {
                process_catalog(full_path, opt);
            }
        }
    }
   
}
int main(int argc, char* argv[]) 
{
    struct Options* options = (struct Options*)malloc(sizeof(struct Options)); 
    init_options(options);

    char catalog[PATH_LEN];
    catalog[0] = '.';
    catalog[1] = '\0';

    struct stat buf;
    int i;
    for (i = 1; i < argc; i++) {
        if (stat(argv[i], &buf) == 0) {
            if (S_ISDIR(buf.st_mode)) {
                strcpy(catalog, argv[i]);

                int len = strlen(catalog);
                if (catalog[len - 1] == '/') {
                    catalog[len - 1] = '\0';
                }
                break;
            }
        }
    }

    int option;
    while ((option = getopt(argc, argv, "ldfs")) != -1) {
        switch (option) {
            case 'l':
                options->symlinks = 1;
                break;
            case 'd':
                options->directories = 1;
                break;
            case 'f':
                options->files = 1;
                break;
            case 's':
                options->sort = 1;
                break;
        }
    }

    process_catalog(catalog, options);   

    free(options);
    return 0;
}