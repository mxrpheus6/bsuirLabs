#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "hash.h"
#include "file.h"
#include "menu.h"

int main(void) {
	Cache* cache = createCache(5);
    mainMenu(cache);
    return 0;
}