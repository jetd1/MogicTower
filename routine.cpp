#include "mogicTower.h"
#include "routine.h"
#include <cassert>
#include "init.h"
#include "helpers.h"
#include "damage.h"
#include <queue>
#include <unordered_map>
#include <string>


bool isEnd(const Status &stat)
{
	auto& adj = stat.getNode().adj;
    if (stat.bossDead())
        return true;
	for (auto itr = adj.begin(); itr != adj.end(); ++itr)
	{
		MapObj type = stat.getNode(*itr).getType();
#ifdef DEBUG
		assert(type != safeBlock);
#endif
		if (isMonster(type))
			if (stat.player.canBeat(type))
				return false;

		if (isDoor(type))
			if (stat.player.getKeyCount(keyType(type)) > 0)
				return false;
	}
	return true;
}

static int vis[MAP_LENGTH][MAP_WIDTH];
static string getRouteFromSrcToDest(const Status& stat, Position src, Position dest) { // 返回从src到dest的路径
	const int dx[4] = { 0,-1,1,0 };
	const int dy[4] = { 1,0,0,-1 };
	const char dir[4] = { 'd', 'w', 's', 'a' };

	string route = "";
	map<Position, int> preDir; // [pos, k] k是到达pos的最后一步所走的方向
	queue<Position> q;
	Position cur;

	int colorSrc = stat.mogicTower.colorMap[src.x][src.y];
	int colorDest = stat.mogicTower.colorMap[dest.x][dest.y];

	q.push(src);

	while (!q.empty()) {
		cur = q.front();
		q.pop();
		if (cur == dest) { // cur是目标位置，根据preDir回溯出路径
			if (isMonster(stat.mogicTower.mapContent[dest.x][dest.y])) {
				int k = preDir.find(cur)->second;
				route = dir[k] + route;
			}

			while (!(cur == src)) {
				vis[cur.x][cur.y] = 1;
				int k = preDir.find(cur)->second;
				route = dir[k] + route;
				cur = Position(cur.x - dx[k], cur.y - dy[k]);
			}
			break;
		}
		for (int k = 0; k < 4; ++k) {
			int nx = cur.x + dx[k];
			int ny = cur.y + dy[k];
			Position newPos = Position(nx, ny);
			if (isInRange(nx, ny)
				&& (stat.mogicTower.colorMap[nx][ny] == colorSrc || stat.mogicTower.colorMap[nx][ny] == colorDest)
				&& preDir.find(newPos) == preDir.end()) {
				preDir.insert(pair<Position, int>(newPos, k));
				q.push(newPos);
			}
		}
	}

	return route;

}



string getRoute(Status& stat, int idx) // 返回遍历连通块、到达choice的路径
{
#ifdef DEBUG
//	assert(stat.getNode().adj.find(idx) != stat.getNode().adj.end());
#endif

	string route = "";

	Position playerPos = stat.player.getPos();
	int curColor = stat.mogicTower.colorMap[playerPos.x][playerPos.y];

	for (int i = 0; i < MAP_LENGTH; ++i) 
		for (int j = 0; j < MAP_WIDTH; ++j) 
			if (stat.mogicTower.colorMap[i][j] == curColor && !vis[i][j]) {
				Position tmpPos(i, j);
				route += getRouteFromSrcToDest(stat, playerPos, tmpPos); 
				playerPos = tmpPos;
			}


	route += getRouteFromSrcToDest(stat, playerPos, stat.getNodePtr(idx)->getPos());

	return route;
}

void moveTo(int targetIdx, Status& stat, bool update)
{
	GraphNode& target = stat.getNode(targetIdx);
#ifdef DEBUG
	assert(!target.empty);
#endif

	MapObj type = target.getType();
    auto& player = stat.player;
    auto& map = stat.mogicTower.mapContent;

	if (type == safeBlock)
	{
		Position tPos = target.getPos();
		player.acquire(target.obj);
		player.moveTo(tPos);

		auto& colorMap = stat.mogicTower.colorMap;
		int tColor = colorMap[tPos.x][tPos.y];
		for (int i = 0; i < MAP_LENGTH; ++i)
			for (int j = 0; j < MAP_WIDTH; ++j)
				if (colorMap[i][j] == tColor)
					map[i][j] = road;
	}
	else if (isMonster(type))
	{
		Position tPos = target.getPos();
		assert(player.fight(type));
		player.moveTo(tPos);
        map[tPos.x][tPos.y] = road;
		for (auto itr = target.adj.begin(); itr != target.adj.end(); ++itr)
			if (stat.getNode(*itr).getType() == safeBlock && !target.empty)
				moveTo(*itr, stat, false);
		player.moveTo(tPos);
	}
	else if (isDoor(type))
	{
		Position tPos = target.getPos();
		player.useKey(keyType(type));
		player.moveTo(tPos);
        map[tPos.x][tPos.y] = road;
		for (auto itr = target.adj.begin(); itr != target.adj.end(); ++itr)
			if (stat.getNode(*itr).getType() == safeBlock && !target.empty)
				moveTo(*itr, stat, false);
        player.moveTo(tPos);
	}
	else
		throw runtime_error("Invalid Target!");

	if (update)
		updateStatus(stat);
}