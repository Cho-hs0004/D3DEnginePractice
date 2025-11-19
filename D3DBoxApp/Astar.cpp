

#include "Astar.h"

namespace Astar
{
    const int INF = std::numeric_limits<int>::max();

    struct Cell
    {
        int x, y;
        int f, g, h;
        bool operator>(const Cell& other) const
        {
            return f > other.f;
        }
    };

    // 맨해튼 거리 휴리스틱
    int heuristic(int x1, int y1, int x2, int y2)
    {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }

    const std::array<std::pair<int, int>, 4> directions = { {{0, 1}, {1, 0}, {0, -1}, {-1, 0}} }; // 동, 서, 남, 북

    //const std::array<std::pair<int, int>, 8> directions = { {{0, 1}, {1, 0}, {0, -1}, {-1, 0}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1}} }; // 동, 서, 남, 북, 남동, 남서, 북동, 북서


    // 거리 맵 출력
    void PrintDistances(const std::vector<std::vector<int>>& dist)
    {
        std::cout << "\nDistance grid:\n";
        for (const auto& row : dist)
        {
            for (const auto& cell : row)
            {
                if (cell == INF)
                {
                    std::cout << "__ ";
                }
                else {
                    std::cout << std::setw(2) << std::setfill('0') << cell << " ";
                }
            }
            std::cout << "\n";
        }

    }


    // A* 알고리즘
    std::vector<std::pair<int, int>> AStar(
        const std::vector<std::vector<int>>& maze,
        int startX, int startY,
        int goalX, int goalY)
    {
        int rows = maze.size();
        int cols = maze[0].size();

        std::vector<std::vector<int>> dist(rows, std::vector<int>(cols, INF));
        std::vector<std::vector<std::pair<int, int>>> parent(rows, std::vector<std::pair<int, int>>(cols, { -1, -1 }));

        dist[startX][startY] = 0;

        std::priority_queue<Cell, std::vector<Cell>, std::greater<Cell>> open_list;
        std::unordered_set<int> closed_list;
        auto encode = [](int x, int y) { return x * 1000 + y; }; // 좌표 인코딩

        open_list.push({ startX, startY,
            heuristic(startX, startY, goalX, goalY),
            0,
            heuristic(startX, startY, goalX, goalY)
            });

        while (!open_list.empty())
        {
            Cell current = open_list.top();
            open_list.pop();

            int code = encode(current.x, current.y);
            if (closed_list.find(code) != closed_list.end()) continue;
            closed_list.insert(code);

            // 목표 지점 도달
            if (current.x == goalX && current.y == goalY)
                break;

            for (auto [dx, dy] : directions)
            {
                int nx = current.x + dx;
                int ny = current.y + dy;

                // 맵 경계 및 장애물 체크
                if (nx < 0 || nx >= rows || ny < 0 || ny >= cols) continue;
                if (maze[nx][ny] != 0) continue; // 0: 통로, 1: 벽

                int newG = current.g + 1;
                int newH = heuristic(nx, ny, goalX, goalY);
                int newF = newG + newH;

                if (newG < dist[nx][ny])
                {
                    dist[nx][ny] = newG;
                    parent[nx][ny] = { current.x, current.y };
                    open_list.push({ nx, ny, newF, newG, newH });
                }
            }
        }

        // 경로 복원
        std::vector<std::pair<int, int>> path;
        int x = goalX;
        int y = goalY;
        while (x != -1 && y != -1)
        {
            path.push_back({ x, y });
            auto [px, py] = parent[x][y];
            x = px;
            y = py;
        }
        std::reverse(path.begin(), path.end());

        // 결과 출력
        //PrintDistances(dist);

       /* std::cout << "\n=== Shortest Path ===\n";
        for (auto [px, py] : path)
            std::cout << "(" << py << "," << px << ") ";
        std::cout << "\n";*/

        return path;
    }
} // namespace Astar