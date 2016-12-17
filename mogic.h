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
#define PAUSE getchar();getchar();system("pause");
#endif
#endif
#else
#define PAUSE
#endif

const int MAP_WIDTH = 13;
const int MAP_LENGTH = 13;
const int MAX_DEPTH = 10;

/* 0123:иообвСср */
const int dx[4] = { -1,1,0,0 };
const int dy[4] = { 0,0,-1,1 };


const int HP_Multiple = 5;
const int ATK_Multiple = 4;
const int DEF_Multiple = 7;
const int MDEF_Multiple = 6;

#include "mogicTower.h"


#endif


