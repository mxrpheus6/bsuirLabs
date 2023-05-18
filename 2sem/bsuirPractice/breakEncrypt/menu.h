#pragma once

#include <stdio.h>
#include <conio.h>

#include "structures.h"
#include "files.h"
#include "strings.h"

void pause(void);

void menuInformation(void);

void mainMenu(void);

typedef enum menuOptions {
	BREAK = 1,
	EXIT
}menuOptions;