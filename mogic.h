#ifndef __MOGIC_H
#define __MOGIC_H

//#define DEBUG

#include <cstdio>
#include <iostream>
using namespace std;

#ifdef DEBUG
#ifdef __linux__
#include <unistd.h>
#define PAUSE getchar();
#else
#ifdef _WIN32
#include <conio.h>
#include <Windows.h>
#define PAUSE cout<<endl;system("pause");
#endif
#endif
#else
#define PAUSE
#endif

const int MAP_WIDTH = 13;
const int MAP_LENGTH = 13;
const int MAX_DEPTH = 8;

const int dx[4] = {-1,1,0,0};
const int dy[4] = {0,0,-1,1};

#ifdef DEBUG
#include "debug.h"
#endif

#endif