/*
  PROB: castle
  USER: ogbonna2
  LANG: C++11
 */

// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
// #pragma comment(linker,"/stack:200000000")
#include <bits/stdc++.h>
using namespace std;

#define PI 2*acos(0.0)
#define print(x) return cout<<x<<endl,0
#define watch(x) cerr<<#x<<"-> "<<x<<endl
#define CLEAR(x,val) memset(x,val,sizeof(x))
// #define int long long

typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;

const int INF = 1000000000;
const int MOD = 1000000007; //998244353
const int MAXN = 55;
const int MAXM = 55;

int n, m;

const int v[] = {8, 4, 2, 1};

int cc[MAXN * MAXM], mp[MAXN][MAXM],
    vis[MAXN][MAXM], grid[MAXN][MAXM], dir[MAXN][MAXM][4];

bool ok(int x, int y) {
  return x < n && y < m && x >= 0 && y >= 0;
}

int dfs(int x, int y, int color) {
  vis[x][y] = 1, mp[x][y] = color;

  int res = 1;

  if (ok(x, y + 1) && !vis[x][y + 1] && !dir[x][y + 1][0]) // going east
    res += dfs(x, y + 1, color);
  if (ok(x + 1, y) && !vis[x + 1][y] && !dir[x + 1][y][1]) // going south
    res += dfs(x + 1, y, color);
  if (ok(x, y - 1) && !vis[x][y - 1] && !dir[x][y - 1][2]) // going west
    res += dfs(x, y - 1, color);
  if (ok(x - 1, y) && !vis[x - 1][y] && !dir[x - 1][y][3]) // going north
    res += dfs(x - 1, y, color);

  return res;
}

struct Wall {
 public:
  int sum;
  int x;
  int y;
  char direction;
  Wall(int sum, int x, int y, char direction) {
    this->sum = sum;
    this->x = x;
    this->y = y;
    this->direction = direction;
  }
  bool operator<(Wall wall) {
    if (sum == wall.sum) {
      if (y == wall.y) {
        if (x == wall.x) {
          if (direction == 'N')
            return true;
          return false;
        }
        return x > wall.x;
      }
      return y < wall.y;
    }
    return sum > wall.sum;
  }
};

signed main() {
  freopen("castle.in", "r", stdin);
  freopen("castle.out", "w", stdout);
  cin.tie(0), cout.tie(0);
  ios::sync_with_stdio(0);
  cin >> m >> n;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) {
      cin >> grid[i][j];

      int sum = 0;

      for (int k = 0; k < 4; k++)
        if (sum + v[k] <= grid[i][j])
          dir[i][j][4 - k - 1] = 1, sum += v[k];

    }

  int cur = 0, maxi = 0;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (!vis[i][j])
        cc[cur] = dfs(i, j, cur), maxi = max(cc[cur], maxi), ++cur;

  vector<Wall> walls;

  for (int x = 0; x < n; x++)
    for (int y = 0; y < m; y++) {
      if (ok(x, y + 1) && (mp[x][y + 1] != mp[x][y]) && dir[x][y + 1][0]) { // going east
        int sum = cc[mp[x][y]] + cc[mp[x][y + 1]];
        walls.push_back(Wall(sum, x, y + 1, 'W'));
      }
      if (ok(x + 1, y) && (mp[x + 1][y] != mp[x][y]) && dir[x + 1][y][1]) { // going south
        int sum = cc[mp[x][y]] + cc[mp[x + 1][y]];
        walls.push_back(Wall(sum, x + 1, y, 'N'));
      }
      if (ok(x, y - 1) && (mp[x][y - 1] != mp[x][y]) && dir[x][y - 1][2]) { // going west
        int sum = cc[mp[x][y]] + cc[mp[x][y - 1]];
        walls.push_back(Wall(sum, x, y - 1, 'E'));
      }
      if (ok(x - 1, y) && (mp[x - 1][y] != mp[x][y]) && dir[x - 1][y][3]) { // going north
        int sum = cc[mp[x][y]] + cc[mp[x - 1][y]];
        walls.push_back(Wall(sum, x - 1, y, 'S'));
      }
    }

  sort(walls.begin(), walls.end());

  printf("%d\n%d\n%d\n%d %d %c\n", cur, maxi, walls[0].sum, walls[0].x + 1, walls[0].y + 1, walls[0].direction);

  return 0;
}
