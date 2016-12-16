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

#endif


