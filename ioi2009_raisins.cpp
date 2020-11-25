#include <bits/stdc++.h>
using namespace std;

int N, M;
int arr[51][51];
int prefix[51][51];
int memo[51][51][51][51];
int solve(int x1, int y1, int x2, int y2) {
  if (memo[x1][y1][x2][y2] != -1)
    return memo[x1][y1][x2][y2];
  if (x1 == x2 && y1 == y2)
    return memo[x1][y1][x2][y2] = 0;
  int mini = INT_MAX;
  for (int x = x1 + 1; x <= x2; x++) {
    int a = solve(x1, y1, x - 1, y2) + solve(x, y1, x2, y2);
    if (a < mini)
      mini = a;
  }
  for (int y = y1 + 1; y <= y2; y++) {
    int a = solve(x1, y1, x2, y - 1) + solve(x1, y, x2, y2);
    if (a < mini)
      mini = a;
  }
  int b = prefix[x2][y2];
  if (x1 > 0)
    b -= prefix[x1 - 1][y2];
  if (y1 > 0)
    b -= prefix[x2][y1 - 1];
  if (x1 > 0 && y1 > 0)
    b += prefix[x1 - 1][y1 - 1];
  memo[x1][y1][x2][y2] = mini + b;
  return memo[x1][y1][x2][y2];
}
int main() {
  cin >> N >> M;
  for (int i = 0; i < N; i++)
    for (int j = 0; j < M; j++)
      cin >> arr[i][j];
  for (int i = 0; i < 51; i++)
    for (int j = 0; j < 51; j++)
      prefix[i][j] = -1;
  for (int i = 0; i < 51; i++) {
    for (int j = 0; j < 51; j++) {
      for (int k = 0; k < 51; k++) {
        for (int l = 0; l < 51; l++) {
          memo[i][j][k][l] = -1;
        }
      }
    }
  }
  prefix[0][0] = arr[0][0];
  for (int i = 1; i < N; i++)
    prefix[i][0] = arr[i][0] + prefix[i - 1][0];
  for (int j = 1; j < M; j++) {
    prefix[0][j] = arr[0][j] + prefix[0][j - 1];
    for (int i = 1; i < N; i++)
      prefix[i][j] = arr[i][j] + prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1];
  }
  cout << solve(0, 0, N - 1, M - 1) << endl;
}

