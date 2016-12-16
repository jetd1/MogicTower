#ifndef __HELPERS_H
#define __HELPERS_H

inline bool isMonster(const Tower& mogicTower, int x, int y)
{
    return (mogicTower.mapContent[x][y] >= monster51 &&
            mogicTower.mapContent[x][y] <= monster70) ||
        mogicTower.mapContent[x][y] == boss;
}

inline bool isDoor(const Tower& mogicTower, int x, int y)
{
    return mogicTower.mapContent[x][y] >= yellowDoor &&
        mogicTower.mapContent[x][y] <= redDoor;
}

inline bool isItem(const Tower& mogicTower, int x, int y)
{
    return mogicTower.mapContent[x][y] >= yellowKey &&
        mogicTower.mapContent[x][y] <= largeBottle;
}

inline bool isInRange(int x, int y)
{
    return x >= 0 && x < MAP_LENGTH && y >= 0 && y < MAP_WIDTH;
}

#endif