#ifndef __MOGIC_H
#define __MOGIC_H

#include <cstdio>
#include <iostream>
using namespace std;

#ifdef DEBUG
#ifdef __linux__
#include <unistd.h>
#define PAUSE pause();
#else
#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#define PAUSE system("pause");
#endif
#endif
#else
#define PAUSE
#endif

const int MAP_WIDTH = 13;
const int MAP_LENGTH = 13;
const int MAX_DEPTH = 10;

#include "mogicTower.h"


#endif


