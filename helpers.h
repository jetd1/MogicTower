#ifndef __HELPERS_H
#define __HELPERS_H

inline bool isMonster(MapObj type)
{
    return (type >= monster51 &&
            type <= monster70) ||
        type == boss;
}

inline bool isMonster(const Tower& mogicTower, int x, int y)
{
    return isMonster(mogicTower.mapContent[x][y]);
}

inline bool isDoor(MapObj type)
{
    return type >= yellowDoor &&
        type <= redDoor;
}

inline bool isDoor(const Tower& mogicTower, int x, int y)
{
    return isDoor(mogicTower.mapContent[x][y]);
}

inline bool isItem(MapObj type)
{
    return type >= yellowKey &&
        type <= largeBottle;
}

inline bool isItem(const Tower& mogicTower, int x, int y)
{
    return isItem(mogicTower.mapContent[x][y]);
}

inline bool isInRange(int x, int y)
{
    return x >= 0 && x < MAP_LENGTH && y >= 0 && y < MAP_WIDTH;
}

#endif