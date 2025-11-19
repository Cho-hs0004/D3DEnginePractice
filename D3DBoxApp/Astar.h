#pragma once
#include <iostream>
#include <vector>
#include <array>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <algorithm>
#include <iomanip>

namespace Astar
{
	std::vector<std::pair<int, int>> AStar(
		const std::vector<std::vector<int>>& maze,
		int startX, int startY,
		int goalX, int goalY);
}
