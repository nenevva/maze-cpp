#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
private:
    int n, m;
    int sx, sy;
    int ex, ey;
    vector<vector<char>>& map;
    vector<vector<int>> path;
    vector<int> dx{-1, 0, 0, 1};
    vector<int> dy{0, -1, 1, 0};

public:
    Solution(vector<vector<char>>& map_, int n_, int m_, int sx_, int sy_, int ex_, int ey_) : map(map_), n(n_), m(m_), sx(sx_), sy(sy_), ex(ex_), ey(ey_) {
        path = vector<vector<int>>(n, vector<int>(m, INT32_MAX));
        path[sx][sy] = 0;
    }

    int dfs() {
        dfs(sx, sy);
        return path[ex][ey];
    }

    void dfs(int ox, int oy) {
        for (int i = 0; i < 4; i++) {
            int x = ox + dx[i];
            int y = oy + dy[i];
            if (x < 0 || x >= n || y < 0 || y >= m || map[x][y] == '#') {
                continue;
            }
            if (path[ox][oy] + 1 < path[x][y]) {
                path[x][y] = path[ox][oy] + 1;
                if (x == ex && y == ey) {
                    continue;
                }
                dfs(x, y);
            }
        }
    }

    int bfs() {
        queue<vector<int>> q;
        q.push({sx, sy});

        while (!q.empty()) {
            int ox = q.front()[0];
            int oy = q.front()[1];
            q.pop();
            for (int i = 0; i < 4; i++) {
                int x = ox + dx[i];
                int y = oy + dy[i];
                if (x < 0 || x >= n || y < 0 || y >= m || map[x][y] == '#' || path[x][y] != INT32_MAX) {
                    continue;
                }
                path[x][y] = path[ox][oy] + 1;
                if (x == ex && y == ey) {
                    return path[ex][ey];
                }
                q.push({x, y});
            }
        }
        return -1;
    }
};

int main() {
    int n, m;
    int sx, sy;
    int ex, ey;
    cin >> n;
    cin >> m;
    vector<vector<char>> map(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            char t;
            cin >> t;
            if (t == 'S') {
                sx = i;
                sy = j;
            } else if (t == 'E') {
                ex = i;
                ey = j;
            }
            map[i][j] = t;
        }
    }
    Solution solution(map, n, m, sx, sy, ex, ey);
    cout << solution.bfs() << endl;
    cout << solution.dfs() << endl;
    return 0;
}