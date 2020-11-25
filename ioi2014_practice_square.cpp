#include <bits/stdc++.h>
using namespace std;

int findMaxSquare(vector<vector<int> > material, int materialSize) {
  int s = materialSize; // make name shorter
  int calc[s][s];
  int row[s][s];
  int col[s][s];
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      if (material[i][j] != 0) calc[i][j] = 1; // initially all usable squares can form 1 by 1 squares
      if (material[i][j] != 0) row[i][j] = 1;
      if (material[i][j] != 0) col[i][j] = 1;
      if (material[i][j] == 0) calc[i][j] = 0;
    }
  }
  for (int i = 1; i < s; i++) { //start from second row
    for (int j = 0; j < s; j++) {
      if (material[i][j] == 0)continue;
      if ((j - 1) >= 0 && (material[i - 1][j - 1]) == 1) {
        if (material[i - 1][j] == 1)row[i][j] += row[i - 1][j]++;
        if (material[i][j - 1] == 1)col[i][j] += col[i][j - 1]++;
        if ((row[i][j] > calc[i - 1][j - 1]) && (col[i][j] > calc[i - 1][j - 1])) calc[i][j] = calc[i - 1][j - 1] + 1;
        else if ((row[i][j] == calc[i - 1][j - 1]) && (col[i][j] == calc[i - 1][j - 1])) calc[i][j] = calc[i - 1][j - 1];
        else calc[i][j] = min(row[i][j], col[i][j]);
      }
    }
  }
  int maximum = -1;
  int count = 0;
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      maximum = max(maximum, calc[i][j]);
    }
  }
  for (int i = 0; i < s; i++) {
    for (int j = 0; j < s; j++) {
      if (calc[i][j] == maximum) ++count;
    }
  }
  return count * maximum;
}

int main () {
  int n;
  cin >> n;
  vector<vector<int> > material(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int x; cin >> x;
      material[i].push_back(x);
    }
  }
  cout << findMaxSquare(material, n) << endl;
}
