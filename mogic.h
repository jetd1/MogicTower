#ifndef __MOGIC_H
#define __MOGIC_H

#ifdef DEBUG
#ifdef __linux__
#include <unistd.h>
#define PAUSE pause();
#else
#ifdef _WIN32 || _WIN64
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

enum MapObj
{
    road = 10,
    wall = 11,
    yellowKey = 21,
    blueKey = 22,
    redKey = 23,
    redDiamond = 24, 
    blueDiamond = 25,
    greenDiamond = 26,
    smallBottle = 27,
    largeBottle = 28,
    yellowDoor = 31,
    blueDoor = 32,
    redDoor = 33,
    monster51 = 51,
    monster52 = 52,
    monster53 = 53,
    monster54 = 54,
    monster55 = 55,
    monster56 = 56,
    monster57 = 57,
    monster58 = 58,
    monster59 = 59,
    monster60 = 60, 
    monster61 = 61,
    monster62 = 62,
    monster63 = 63,
    monster64 = 64,
    monster65 = 65,
    monster66 = 66,
    monster67 = 67,
    monster68 = 68,
    monster69 = 69,
    monster70 = 70,
    boss = 99
};

#endif


