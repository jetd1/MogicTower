#define DEBUG

#include <iostream>
#include <fstream>
#include "mogic.h"
#include "damage.h"

using namespace std;

/*全局记录塔信息的数据结构*/
struct
{
    /*楼层地图大小和楼层数，当前固定为1 * 13 * 13 */
    //int height;
    //int len, wid;
    MapObj floorMap[MAP_LENGTH][MAP_WIDTH];

}mogicTower;


int main()
{
    

    PAUSE;
}

void readTower()
{
    ifstream fin("input.txt");
    if (!fin)
    {
        

    }
}
